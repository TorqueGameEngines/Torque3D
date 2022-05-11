// MIT License

// Copyright (c) 2019 Erin Catto

// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:

// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.

// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#include "settings.h"
#include "test.h"
#include "imgui/imgui.h"

enum
{
	e_maxBodies = 256
};

// This test demonstrates how to use the world ray-cast feature.
// NOTE: we are intentionally filtering one of the polygons, therefore
// the ray will always miss one type of polygon.

// This callback finds the closest hit. Polygon 0 is filtered.
class RayCastClosestCallback : public b2RayCastCallback
{
public:
	RayCastClosestCallback()
	{
		m_hit = false;
	}

	float ReportFixture(b2Fixture* fixture, const b2Vec2& point, const b2Vec2& normal, float fraction) override
	{
		uintptr_t index = fixture->GetUserData().pointer;
		if (index == 1)
		{
			// By returning -1, we instruct the calling code to ignore this fixture and
			// continue the ray-cast to the next fixture.
			return -1.0f;
		}

		m_hit = true;
		m_point = point;
		m_normal = normal;

		// By returning the current fraction, we instruct the calling code to clip the ray and
		// continue the ray-cast to the next fixture. WARNING: do not assume that fixtures
		// are reported in order. However, by clipping, we can always get the closest fixture.
		return fraction;
	}
	
	bool m_hit;
	b2Vec2 m_point;
	b2Vec2 m_normal;
};

// This callback finds any hit. Polygon 0 is filtered. For this type of query we are usually
// just checking for obstruction, so the actual fixture and hit point are irrelevant. 
class RayCastAnyCallback : public b2RayCastCallback
{
public:
	RayCastAnyCallback()
	{
		m_hit = false;
	}

	float ReportFixture(b2Fixture* fixture, const b2Vec2& point, const b2Vec2& normal, float) override
	{
		uintptr_t index = fixture->GetUserData().pointer;
		if (index == 1)
		{
			// By returning -1, we instruct the calling code to ignore this fixture and
			// continue the ray-cast to the next fixture.
			return -1.0f;
		}

		m_hit = true;
		m_point = point;
		m_normal = normal;

		// At this point we have a hit, so we know the ray is obstructed.
		// By returning 0, we instruct the calling code to terminate the ray-cast.
		return 0.0f;
	}

	bool m_hit;
	b2Vec2 m_point;
	b2Vec2 m_normal;
};

// This ray cast collects multiple hits along the ray. Polygon 0 is filtered.
// The fixtures are not necessary reported in order, so we might not capture
// the closest fixture.
class RayCastMultipleCallback : public b2RayCastCallback
{
public:
	enum
	{
		e_maxCount = 3
	};

	RayCastMultipleCallback()
	{
		m_count = 0;
	}

	float ReportFixture(b2Fixture* fixture, const b2Vec2& point, const b2Vec2& normal, float) override
	{
		uintptr_t index = fixture->GetUserData().pointer;
		if (index == 1)
		{
			// By returning -1, we instruct the calling code to ignore this fixture and
			// continue the ray-cast to the next fixture.
			return -1.0f;
		}

		b2Assert(m_count < e_maxCount);

		m_points[m_count] = point;
		m_normals[m_count] = normal;
		++m_count;

		if (m_count == e_maxCount)
		{
			// At this point the buffer is full.
			// By returning 0, we instruct the calling code to terminate the ray-cast.
			return 0.0f;
		}

		// By returning 1, we instruct the caller to continue without clipping the ray.
		return 1.0f;
	}

	b2Vec2 m_points[e_maxCount];
	b2Vec2 m_normals[e_maxCount];
	int32 m_count;
};


class RayCast : public Test
{
public:

	enum Mode
	{
		e_any = 0,
		e_closest = 1,
		e_multiple = 2
	};

	RayCast()
	{
		// Ground body
		{
			b2BodyDef bd;
			b2Body* ground = m_world->CreateBody(&bd);

			b2EdgeShape shape;
			shape.SetTwoSided(b2Vec2(-40.0f, 0.0f), b2Vec2(40.0f, 0.0f));
			ground->CreateFixture(&shape, 0.0f);
		}

		{
			b2Vec2 vertices[3];
			vertices[0].Set(-0.5f, 0.0f);
			vertices[1].Set(0.5f, 0.0f);
			vertices[2].Set(0.0f, 1.5f);
			m_polygons[0].Set(vertices, 3);
		}

		{
			b2Vec2 vertices[3];
			vertices[0].Set(-0.1f, 0.0f);
			vertices[1].Set(0.1f, 0.0f);
			vertices[2].Set(0.0f, 1.5f);
			m_polygons[1].Set(vertices, 3);
		}

		{
			float w = 1.0f;
			float b = w / (2.0f + b2Sqrt(2.0f));
			float s = b2Sqrt(2.0f) * b;

			b2Vec2 vertices[8];
			vertices[0].Set(0.5f * s, 0.0f);
			vertices[1].Set(0.5f * w, b);
			vertices[2].Set(0.5f * w, b + s);
			vertices[3].Set(0.5f * s, w);
			vertices[4].Set(-0.5f * s, w);
			vertices[5].Set(-0.5f * w, b + s);
			vertices[6].Set(-0.5f * w, b);
			vertices[7].Set(-0.5f * s, 0.0f);

			m_polygons[2].Set(vertices, 8);
		}

		{
			m_polygons[3].SetAsBox(0.5f, 0.5f);
		}

		{
			m_circle.m_radius = 0.5f;
		}

		{
			m_edge.SetTwoSided(b2Vec2(-1.0f, 0.0f), b2Vec2(1.0f, 0.0f));
		}

		m_bodyIndex = 0;
		memset(m_bodies, 0, sizeof(m_bodies));

		m_degrees = 0.0f;

		m_mode = e_closest;
	}

	void Create(int32 index)
	{
		if (m_bodies[m_bodyIndex] != NULL)
		{
			m_world->DestroyBody(m_bodies[m_bodyIndex]);
			m_bodies[m_bodyIndex] = NULL;
		}

		b2BodyDef bd;

		float x = RandomFloat(-10.0f, 10.0f);
		float y = RandomFloat(0.0f, 20.0f);
		bd.position.Set(x, y);
		bd.angle = RandomFloat(-b2_pi, b2_pi);

		if (index == 4)
		{
			bd.angularDamping = 0.02f;
		}

		m_bodies[m_bodyIndex] = m_world->CreateBody(&bd);

		if (index < 4)
		{
			b2FixtureDef fd;
			fd.shape = m_polygons + index;
			fd.friction = 0.3f;
			fd.userData.pointer = index + 1;
			m_bodies[m_bodyIndex]->CreateFixture(&fd);
		}
		else if (index < 5)
		{
			b2FixtureDef fd;
			fd.shape = &m_circle;
			fd.friction = 0.3f;
			fd.userData.pointer = index + 1;
			m_bodies[m_bodyIndex]->CreateFixture(&fd);
		}
		else
		{
			b2FixtureDef fd;
			fd.shape = &m_edge;
			fd.friction = 0.3f;
			fd.userData.pointer = index + 1;

			m_bodies[m_bodyIndex]->CreateFixture(&fd);
		}

		m_bodyIndex = (m_bodyIndex + 1) % e_maxBodies;
	}

	void DestroyBody()
	{
		for (int32 i = 0; i < e_maxBodies; ++i)
		{
			if (m_bodies[i] != NULL)
			{
				m_world->DestroyBody(m_bodies[i]);
				m_bodies[i] = NULL;
				return;
			}
		}
	}

	void UpdateUI() override
	{
		ImGui::SetNextWindowPos(ImVec2(10.0f, 100.0f));
		ImGui::SetNextWindowSize(ImVec2(210.0f, 285.0f));
		ImGui::Begin("Ray-cast Controls", nullptr, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize);

		if (ImGui::Button("Shape 1"))
		{
			Create(0);
		}

		if (ImGui::Button("Shape 2"))
		{
			Create(1);
		}

		if (ImGui::Button("Shape 3"))
		{
			Create(2);
		}

		if (ImGui::Button("Shape 4"))
		{
			Create(3);
		}

		if (ImGui::Button("Shape 5"))
		{
			Create(4);
		}

		if (ImGui::Button("Shape 6"))
		{
			Create(5);
		}

		if (ImGui::Button("Destroy Shape"))
		{
			DestroyBody();
		}

		ImGui::RadioButton("Any", &m_mode, e_any);
		ImGui::RadioButton("Closest", &m_mode, e_closest);
		ImGui::RadioButton("Multiple", &m_mode, e_multiple);

		ImGui::SliderFloat("Angle", &m_degrees, 0.0f, 360.0f, "%.0f");

		ImGui::End();
	}

	void Step(Settings& settings) override
	{
		Test::Step(settings);

		g_debugDraw.DrawString(5, m_textLine, "Shape 1 is intentionally ignored by the ray");
		m_textLine += m_textIncrement;
		switch (m_mode)
		{
		case e_closest:
			g_debugDraw.DrawString(5, m_textLine, "Ray-cast mode: closest - find closest fixture along the ray");
			break;
		
		case e_any:
			g_debugDraw.DrawString(5, m_textLine, "Ray-cast mode: any - check for obstruction");
			break;

		case e_multiple:
			g_debugDraw.DrawString(5, m_textLine, "Ray-cast mode: multiple - gather multiple fixtures");
			break;
		}

		m_textLine += m_textIncrement;

		float angle = b2_pi * m_degrees / 180.0f;
		float L = 11.0f;
		b2Vec2 point1(0.0f, 10.0f);
		b2Vec2 d(L * cosf(angle), L * sinf(angle));
		b2Vec2 point2 = point1 + d;

		if (m_mode == e_closest)
		{
			RayCastClosestCallback callback;
			m_world->RayCast(&callback, point1, point2);

			if (callback.m_hit)
			{
				g_debugDraw.DrawPoint(callback.m_point, 5.0f, b2Color(0.4f, 0.9f, 0.4f));
				g_debugDraw.DrawSegment(point1, callback.m_point, b2Color(0.8f, 0.8f, 0.8f));
				b2Vec2 head = callback.m_point + 0.5f * callback.m_normal;
				g_debugDraw.DrawSegment(callback.m_point, head, b2Color(0.9f, 0.9f, 0.4f));
			}
			else
			{
				g_debugDraw.DrawSegment(point1, point2, b2Color(0.8f, 0.8f, 0.8f));
			}
		}
		else if (m_mode == e_any)
		{
			RayCastAnyCallback callback;
			m_world->RayCast(&callback, point1, point2);

			if (callback.m_hit)
			{
				g_debugDraw.DrawPoint(callback.m_point, 5.0f, b2Color(0.4f, 0.9f, 0.4f));
				g_debugDraw.DrawSegment(point1, callback.m_point, b2Color(0.8f, 0.8f, 0.8f));
				b2Vec2 head = callback.m_point + 0.5f * callback.m_normal;
				g_debugDraw.DrawSegment(callback.m_point, head, b2Color(0.9f, 0.9f, 0.4f));
			}
			else
			{
				g_debugDraw.DrawSegment(point1, point2, b2Color(0.8f, 0.8f, 0.8f));
			}
		}
		else if (m_mode == e_multiple)
		{
			RayCastMultipleCallback callback;
			m_world->RayCast(&callback, point1, point2);
			g_debugDraw.DrawSegment(point1, point2, b2Color(0.8f, 0.8f, 0.8f));

			for (int32 i = 0; i < callback.m_count; ++i)
			{
				b2Vec2 p = callback.m_points[i];
				b2Vec2 n = callback.m_normals[i];
				g_debugDraw.DrawPoint(p, 5.0f, b2Color(0.4f, 0.9f, 0.4f));
				g_debugDraw.DrawSegment(point1, p, b2Color(0.8f, 0.8f, 0.8f));
				b2Vec2 head = p + 0.5f * n;
				g_debugDraw.DrawSegment(p, head, b2Color(0.9f, 0.9f, 0.4f));
			}
		}

#if 0
		// This case was failing.
		{
			b2Vec2 vertices[4];
			//vertices[0].Set(-22.875f, -3.0f);
			//vertices[1].Set(22.875f, -3.0f);
			//vertices[2].Set(22.875f, 3.0f);
			//vertices[3].Set(-22.875f, 3.0f);

			b2PolygonShape shape;
			//shape.Set(vertices, 4);
			shape.SetAsBox(22.875f, 3.0f);

			b2RayCastInput input;
			input.p1.Set(10.2725f,1.71372f);
			input.p2.Set(10.2353f,2.21807f);
			//input.maxFraction = 0.567623f;
			input.maxFraction = 0.56762173f;

			b2Transform xf;
			xf.SetIdentity();
			xf.position.Set(23.0f, 5.0f);

			b2RayCastOutput output;
			bool hit;
			hit = shape.RayCast(&output, input, xf);
			hit = false;

			b2Color color(1.0f, 1.0f, 1.0f);
			b2Vec2 vs[4];
			for (int32 i = 0; i < 4; ++i)
			{
				vs[i] = b2Mul(xf, shape.m_vertices[i]);
			}

			g_debugDraw.DrawPolygon(vs, 4, color);
			g_debugDraw.DrawSegment(input.p1, input.p2, color);
		}
#endif
	}

	static Test* Create()
	{
		return new RayCast;
	}

	int32 m_bodyIndex;
	b2Body* m_bodies[e_maxBodies];
	b2PolygonShape m_polygons[4];
	b2CircleShape m_circle;
	b2EdgeShape m_edge;
	float m_degrees;
	int32 m_mode;
};

static int testIndex = RegisterTest("Collision", "Ray Cast", RayCast::Create);
