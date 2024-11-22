#include "testing/unitTesting.h"

#include "platform/platform.h"
#include "console/simBase.h"
#include "console/consoleTypes.h"
#include "console/scriptObjects.h"
#include "console/simBase.h"
#include "console/engineAPI.h"
#include "math/mMath.h"
#include "math/util/frustum.h"
#include "math/mathUtils.h"

TEST(PointTest, TestInitFunctions)
{
   Point3F test;
   EXPECT_NEAR(test.x, 0.0f, POINT_EPSILON); EXPECT_NEAR(test.y, 0.0f, POINT_EPSILON); EXPECT_NEAR(test.z, 0.0f, POINT_EPSILON);

   Point3F test2(1.0f);
   EXPECT_NEAR(test2.x, 1.0f, POINT_EPSILON); EXPECT_NEAR(test2.y, 1.0f, POINT_EPSILON); EXPECT_NEAR(test2.z, 1.0f, POINT_EPSILON);

   Point3F test3(test2);
   EXPECT_NEAR(test3.x, 1.0f, POINT_EPSILON); EXPECT_NEAR(test3.y, 1.0f, POINT_EPSILON); EXPECT_NEAR(test3.z, 1.0f, POINT_EPSILON);

   Point3F test4(1.0f, 0.5f, 0.25f);
   EXPECT_NEAR(test4.x, 1.0f, POINT_EPSILON); EXPECT_NEAR(test4.y, 0.5f, POINT_EPSILON); EXPECT_NEAR(test4.z, 0.25f, POINT_EPSILON);
}

TEST(PointTest, TestSetFunctions)
{
   Point3F test;
   EXPECT_NEAR(test.x, 0.0f, POINT_EPSILON); EXPECT_NEAR(test.y, 0.0f, POINT_EPSILON); EXPECT_NEAR(test.z, 0.0f, POINT_EPSILON);

   test.set(1.0f);
   EXPECT_NEAR(test.x, 1.0f, POINT_EPSILON); EXPECT_NEAR(test.y, 1.0f, POINT_EPSILON); EXPECT_NEAR(test.z, 1.0f, POINT_EPSILON);

   Point3F test2(1.0f, 0.5f, 0.25f);
   test.set(test2);
   EXPECT_NEAR(test.x, 1.0f, POINT_EPSILON); EXPECT_NEAR(test.y, 0.5f, POINT_EPSILON); EXPECT_NEAR(test.z, 0.25f, POINT_EPSILON);

   test.set(0.25f, 1.0f, 0.5f);
   EXPECT_NEAR(test.x, 0.25f, POINT_EPSILON); EXPECT_NEAR(test.y, 1.0f, POINT_EPSILON); EXPECT_NEAR(test.z, 0.5f, POINT_EPSILON);

   test.zero();
   EXPECT_NEAR(test.x, 0.0f, POINT_EPSILON); EXPECT_NEAR(test.y, 0.0f, POINT_EPSILON); EXPECT_NEAR(test.z, 0.0f, POINT_EPSILON);
   EXPECT_TRUE(test.isZero());
}


TEST(PointTest, TestQueryFunctions)
{
   Point3F test(1.0f, 0.5f, 0.25f);
   Point3F test2(1.0f, 0.5f, 0.25f);
   Point3F test3(5.0f, 0.5f, 0.25f);

   EXPECT_FALSE(test.equal(test3));
   EXPECT_TRUE(test.equal(test2));

   F32 testLen = test.len();
   EXPECT_NEAR(testLen, 1.14564395f, POINT_EPSILON);

   F32 testLenSq = test.lenSquared();
   EXPECT_NEAR(testLenSq, 1.3125f, POINT_EPSILON);

   U32 idx = test.getLeastComponentIndex();

   EXPECT_EQ(idx, 2);

   idx = test.getGreatestComponentIndex();

   EXPECT_EQ(idx, 0);

   EXPECT_FALSE(test.isUnitLength());

   test.normalizeSafe();
   EXPECT_TRUE(test.isUnitLength());
}

TEST(PointTest, TestMutatorFunctions)
{
   Point3F test(1.0f, 0.5f, 0.25f);
   Point3F test2(5.0f, 0.5f, 0.25f);

   test.convolve(test2);
   EXPECT_NEAR(test.x, 5.0f, POINT_EPSILON); EXPECT_NEAR(test.y, 0.25f, POINT_EPSILON); EXPECT_NEAR(test.z, 0.0625f, POINT_EPSILON);

   test.convolveInverse(test2);
   EXPECT_NEAR(test.x, 1.0f, POINT_EPSILON); EXPECT_NEAR(test.y, 0.5f, POINT_EPSILON); EXPECT_NEAR(test.z, 0.25f, POINT_EPSILON);

   test.neg();
   EXPECT_NEAR(test.x, -1.0f, POINT_EPSILON); EXPECT_NEAR(test.y, -0.5f, POINT_EPSILON); EXPECT_NEAR(test.z, -0.25f, POINT_EPSILON);

   test.normalizeSafe();
   EXPECT_NEAR(test.x, -0.872871518f, POINT_EPSILON); EXPECT_NEAR(test.y, -0.436435759f, POINT_EPSILON); EXPECT_NEAR(test.z, -0.218217880f, POINT_EPSILON);

   test.normalize(2.5f);
   EXPECT_NEAR(test.x, -2.18217897f, POINT_EPSILON); EXPECT_NEAR(test.y, -1.09108949f, POINT_EPSILON); EXPECT_NEAR(test.z, -0.545544744f, POINT_EPSILON);
}

