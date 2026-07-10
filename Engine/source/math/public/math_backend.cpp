#include "math/public/math_backend.h"

namespace math_backend::float4::dispatch
{
   // Single definition of the global dispatch table
   Float4Funcs gFloat4{};
}

namespace math_backend::float3::dispatch
{
   // Single definition of the global dispatch table
   Float3Funcs gFloat3{};
}

namespace math_backend::mat44::dispatch
{
   Mat44Funcs gMat44{};
}

namespace math_backend
{
   // Use an anonymous namespace for the static initializer
   namespace {
      struct ScalarInitializer
      {
         ScalarInitializer()
         {
            // Install scalar defaults immediately for all types
            float4::dispatch::install_scalar();
            float3::dispatch::install_scalar();
            mat44::dispatch::install_scalar();
         }
      };

      // Static instance ensures constructor runs before main()
      ScalarInitializer g_scalarInitializer;
   }
}


math_backend::backend math_backend::choose_backend(U32 cpu_flags)
{
#if defined(__x86_64__) || defined(_M_X64) || defined(_M_IX86)

   if (cpu_flags & CPU_PROP_AVX2)  return backend::avx2;
   if (cpu_flags & CPU_PROP_AVX)   return backend::avx;
   if (cpu_flags & CPU_PROP_SSE4_1) return backend::sse41;
   if (cpu_flags & CPU_PROP_SSE2)  return backend::sse2;

#elif defined(__aarch64__) || defined(__ARM_NEON)

   if (cpu_flags & CPU_PROP_NEON) return backend::neon;

#endif
   return backend::scalar;
}

void math_backend::install_from_cpu_flags(uint32_t cpu_flags)
{
   {
      g_backend = choose_backend(cpu_flags);

      switch (g_backend)
      {
#if defined(__x86_64__) || defined(_M_X64) || defined(_M_IX86)
      case backend::avx2:
         float4::dispatch::install_avx2();
         float3::dispatch::install_avx2();
         mat44::dispatch::install_avx2();
         break;

      case backend::avx:
         float4::dispatch::install_avx();
         float3::dispatch::install_avx();
         mat44::dispatch::install_avx();
         break;

      case backend::sse41:
         float4::dispatch::install_sse41();
         float3::dispatch::install_sse41();
         mat44::dispatch::install_sse41();
         break;

      case backend::sse2:
         float4::dispatch::install_sse2();
         float3::dispatch::install_sse2();
         mat44::dispatch::install_sse2();
         break;
#elif defined(__aarch64__) || defined(__ARM_NEON)
      case backend::neon:
         float4::dispatch::install_neon();
         float3::dispatch::install_neon();
         mat44::dispatch::install_neon();
         break;
#endif
      default:
         float4::dispatch::install_scalar();
         float3::dispatch::install_scalar();
         mat44::dispatch::install_scalar();
         break;
      }
   }
}

#if defined(TORQUE_DEBUG) || defined(TORQUE_MATH_BENCH)

#include "console/console.h"
#include "console/engineAPI.h"
#include <chrono>

namespace math_backend::bench
{
   template<typename T>
   inline void doNotOptimize(T& value)
   {
#if defined(_MSC_VER)
      // Escaping the address (rather than copying the value into a volatile
      // local) sidesteps array types not being copy-constructible, and is
      // enough to stop MSVC from proving the result is dead and eliding the call.
      void const* volatile sink = static_cast<void const*>(&value);
      (void)sink;
#else
      asm volatile("" : : "r,m"(value) : "memory");
#endif
   }

   template<typename Fn>
   double timeNs(U32 iterations, Fn&& fn)
   {
      auto start = std::chrono::high_resolution_clock::now();
      for (U32 i = 0; i < iterations; ++i)
         fn();
      auto end = std::chrono::high_resolution_clock::now();
      return std::chrono::duration<double, std::nano>(end - start).count() / iterations;
   }

   template<typename ScalarFn, typename IsaFn>
   void benchOp(const char* typeName, const char* opName, U32 iterations,
      ScalarFn&& scalarCall, IsaFn&& isaCall)
   {
      double sNs = timeNs(iterations, scalarCall);
      double iNs = timeNs(iterations, isaCall);
      Con::printf("[math_bench] %s.%-16s scalar=%9.2f ns  isa=%9.2f ns  (%.2fx)",
         typeName, opName, sNs, iNs, sNs / iNs);
   }

   //--------------------------------------------------------------
   // Installs one named ISA into all three dispatch tables so a
   // single console command drives every bench consistently.
   // NOTE: this does NOT check CPUID - only pass an ISA your test
   // machine actually supports, or you'll crash on an illegal
   // instruction the moment the ISA function pointers get called.
   //--------------------------------------------------------------
   static bool installIsaByName(const char* isaName)
   {
      String name(isaName);

      if (name.equal("sse2", String::NoCase))
      {
#if defined(__x86_64__) || defined(_M_X64) || defined(_M_IX86)
         float3::dispatch::install_sse2();
         float4::dispatch::install_sse2();
         mat44::dispatch::install_sse2();
         return true;
#endif
      }
      else if (name.equal("sse41", String::NoCase))
      {
#if defined(__x86_64__) || defined(_M_X64) || defined(_M_IX86)
         float3::dispatch::install_sse41();
         float4::dispatch::install_sse41();
         mat44::dispatch::install_sse41();
         return true;
#endif
      }
      else if (name.equal("avx", String::NoCase))
      {
#if defined(__x86_64__) || defined(_M_X64) || defined(_M_IX86)
         float3::dispatch::install_avx();
         float4::dispatch::install_avx();
         mat44::dispatch::install_avx();
         return true;
#endif
      }
      else if (name.equal("avx2", String::NoCase))
      {
#if defined(__x86_64__) || defined(_M_X64) || defined(_M_IX86)
         float3::dispatch::install_avx2();
         float4::dispatch::install_avx2();
         mat44::dispatch::install_avx2();
         return true;
#endif
      }
      else if (name.equal("neon", String::NoCase))
      {
#if defined(__aarch64__) || defined(__ARM_NEON)
         float3::dispatch::install_neon();
         float4::dispatch::install_neon();
         mat44::dispatch::install_neon();
         return true;
#endif
      }

      Con::errorf("[math_bench] Unknown or unavailable ISA '%s' on this build/platform", isaName);
      return false;
   }

   //================================================================
   // Float3
   //================================================================
   void runFloat3Bench(U32 iterations, const char* isaName)
   {
      using namespace math_backend::float3::dispatch;

      install_scalar();
      Float3Funcs scalarFuncs = gFloat3;

      if (!installIsaByName(isaName))
         return;
      Float3Funcs isaFuncs = gFloat3;

      float a[3] = { 1.2f, 3.4f, -2.1f };
      float b[3] = { -0.7f, 2.2f, 5.5f };
      float r[3];
      float s = 0.0f;
      const float scalar = 2.5f;
      const float lerpT = 0.35f;

      benchOp("float3", "add", iterations,
         [&] { scalarFuncs.add(a, b, r); doNotOptimize(r); },
         [&] { isaFuncs.add(a, b, r);    doNotOptimize(r); });

      benchOp("float3", "sub", iterations,
         [&] { scalarFuncs.sub(a, b, r); doNotOptimize(r); },
         [&] { isaFuncs.sub(a, b, r);    doNotOptimize(r); });

      benchOp("float3", "mul", iterations,
         [&] { scalarFuncs.mul(a, b, r); doNotOptimize(r); },
         [&] { isaFuncs.mul(a, b, r);    doNotOptimize(r); });

      benchOp("float3", "mul_scalar", iterations,
         [&] { scalarFuncs.mul_scalar(a, scalar, r); doNotOptimize(r); },
         [&] { isaFuncs.mul_scalar(a, scalar, r);    doNotOptimize(r); });

      benchOp("float3", "div", iterations,
         [&] { scalarFuncs.div(a, b, r); doNotOptimize(r); },
         [&] { isaFuncs.div(a, b, r);    doNotOptimize(r); });

      benchOp("float3", "div_scalar", iterations,
         [&] { scalarFuncs.div_scalar(a, scalar, r); doNotOptimize(r); },
         [&] { isaFuncs.div_scalar(a, scalar, r);    doNotOptimize(r); });

      benchOp("float3", "dot", iterations,
         [&] { s = scalarFuncs.dot(a, b); doNotOptimize(s); },
         [&] { s = isaFuncs.dot(a, b);    doNotOptimize(s); });

      benchOp("float3", "length", iterations,
         [&] { s = scalarFuncs.length(a); doNotOptimize(s); },
         [&] { s = isaFuncs.length(a);    doNotOptimize(s); });

      benchOp("float3", "lengthSquared", iterations,
         [&] { s = scalarFuncs.lengthSquared(a); doNotOptimize(s); },
         [&] { s = isaFuncs.lengthSquared(a);    doNotOptimize(s); });

      benchOp("float3", "normalize", iterations,
         [&] { float tmp[3] = { a[0],a[1],a[2] }; scalarFuncs.normalize(tmp); doNotOptimize(tmp); },
         [&] { float tmp[3] = { a[0],a[1],a[2] }; isaFuncs.normalize(tmp);    doNotOptimize(tmp); });

      benchOp("float3", "normalize_mag", iterations,
         [&] { float tmp[3] = { a[0],a[1],a[2] }; scalarFuncs.normalize_mag(tmp, 3.0f); doNotOptimize(tmp); },
         [&] { float tmp[3] = { a[0],a[1],a[2] }; isaFuncs.normalize_mag(tmp, 3.0f);    doNotOptimize(tmp); });

      benchOp("float3", "lerp", iterations,
         [&] { scalarFuncs.lerp(a, b, lerpT, r); doNotOptimize(r); },
         [&] { isaFuncs.lerp(a, b, lerpT, r);    doNotOptimize(r); });

      benchOp("float3", "cross", iterations,
         [&] { scalarFuncs.cross(a, b, r); doNotOptimize(r); },
         [&] { isaFuncs.cross(a, b, r);    doNotOptimize(r); });
   }

   //================================================================
   // Float4
   //================================================================
   void runFloat4Bench(U32 iterations, const char* isaName)
   {
      using namespace math_backend::float4::dispatch;

      install_scalar();
      Float4Funcs scalarFuncs = gFloat4;

      if (!installIsaByName(isaName))
         return;
      Float4Funcs isaFuncs = gFloat4;

      float a[4] = { 1.2f, 3.4f, -2.1f, 0.8f };
      float b[4] = { -0.7f, 2.2f, 5.5f, -1.1f };
      float r[4];
      float s = 0.0f;
      const float scalar = 2.5f;
      const float lerpT = 0.35f;

      benchOp("float4", "add", iterations,
         [&] { scalarFuncs.add(a, b, r); doNotOptimize(r); },
         [&] { isaFuncs.add(a, b, r);    doNotOptimize(r); });

      benchOp("float4", "sub", iterations,
         [&] { scalarFuncs.sub(a, b, r); doNotOptimize(r); },
         [&] { isaFuncs.sub(a, b, r);    doNotOptimize(r); });

      benchOp("float4", "mul", iterations,
         [&] { scalarFuncs.mul(a, b, r); doNotOptimize(r); },
         [&] { isaFuncs.mul(a, b, r);    doNotOptimize(r); });

      benchOp("float4", "mul_scalar", iterations,
         [&] { scalarFuncs.mul_scalar(a, scalar, r); doNotOptimize(r); },
         [&] { isaFuncs.mul_scalar(a, scalar, r);    doNotOptimize(r); });

      benchOp("float4", "div", iterations,
         [&] { scalarFuncs.div(a, b, r); doNotOptimize(r); },
         [&] { isaFuncs.div(a, b, r);    doNotOptimize(r); });

      benchOp("float4", "div_scalar", iterations,
         [&] { scalarFuncs.div_scalar(a, scalar, r); doNotOptimize(r); },
         [&] { isaFuncs.div_scalar(a, scalar, r);    doNotOptimize(r); });

      benchOp("float4", "dot", iterations,
         [&] { s = scalarFuncs.dot(a, b); doNotOptimize(s); },
         [&] { s = isaFuncs.dot(a, b);    doNotOptimize(s); });

      benchOp("float4", "length", iterations,
         [&] { s = scalarFuncs.length(a); doNotOptimize(s); },
         [&] { s = isaFuncs.length(a);    doNotOptimize(s); });

      benchOp("float4", "lengthSquared", iterations,
         [&] { s = scalarFuncs.lengthSquared(a); doNotOptimize(s); },
         [&] { s = isaFuncs.lengthSquared(a);    doNotOptimize(s); });

      benchOp("float4", "normalize", iterations,
         [&] { float tmp[4] = { a[0],a[1],a[2],a[3] }; scalarFuncs.normalize(tmp); doNotOptimize(tmp); },
         [&] { float tmp[4] = { a[0],a[1],a[2],a[3] }; isaFuncs.normalize(tmp);    doNotOptimize(tmp); });

      benchOp("float4", "normalize_mag", iterations,
         [&] { float tmp[4] = { a[0],a[1],a[2],a[3] }; scalarFuncs.normalize_mag(tmp, 3.0f); doNotOptimize(tmp); },
         [&] { float tmp[4] = { a[0],a[1],a[2],a[3] }; isaFuncs.normalize_mag(tmp, 3.0f);    doNotOptimize(tmp); });

      benchOp("float4", "lerp", iterations,
         [&] { scalarFuncs.lerp(a, b, lerpT, r); doNotOptimize(r); },
         [&] { isaFuncs.lerp(a, b, lerpT, r);    doNotOptimize(r); });

      benchOp("float4", "cross", iterations,
         [&] { scalarFuncs.cross(a, b, r); doNotOptimize(r); },
         [&] { isaFuncs.cross(a, b, r);    doNotOptimize(r); });
   }

   //================================================================
   // Mat44
   //================================================================
   void runMat44Bench(U32 iterations, const char* isaName)
   {
      using namespace math_backend::mat44::dispatch;

      install_scalar();
      Mat44Funcs scalarFuncs = gMat44;

      if (!installIsaByName(isaName))
         return;
      Mat44Funcs isaFuncs = gMat44;

      float m[16] = {
          0.8f, -0.5f, 0.1f, 2.0f,
          0.5f,  0.8f, 0.0f, -1.0f,
         -0.1f,  0.0f, 1.0f, 3.5f,
          0.0f,  0.0f, 0.0f, 1.0f
      };
      float m2[16] = {
         1.0f, 0.0f, 0.0f, 0.5f,
         0.0f, 1.0f, 0.0f, -0.5f,
         0.0f, 0.0f, 1.0f, 1.0f,
         0.0f, 0.0f, 0.0f, 1.0f
      };
      float out16[16];
      float pos3[3] = { 1.0f, 2.0f, 3.0f };
      float out3[3];
      float out4[4];
      float scaleVec[3] = { 1.0f, 1.0f, 1.0f };
      float planeS[3] = { 1.0f, 1.0f, 1.0f };
      float planeIn[4] = { 0.0f, 1.0f, 0.0f, -2.0f };
      float planeOut[4];
      float det = 0.0f;

      const int kBatchCount = 64;
      float batchPts[kBatchCount * 3];
      float batchOut[kBatchCount * 3];
      for (int i = 0; i < kBatchCount; ++i)
      {
         batchPts[i * 3 + 0] = (float)i * 0.1f;
         batchPts[i * 3 + 1] = (float)i * 0.2f - 1.0f;
         batchPts[i * 3 + 2] = (float)i * 0.05f + 0.5f;
      }

      benchOp("mat44", "transpose", iterations,
         [&] { float tmp[16]; memcpy(tmp, m, sizeof(tmp)); scalarFuncs.transpose(tmp); doNotOptimize(tmp); },
         [&] { float tmp[16]; memcpy(tmp, m, sizeof(tmp)); isaFuncs.transpose(tmp);    doNotOptimize(tmp); });

      benchOp("mat44", "inverse", iterations,
         [&] { float tmp[16]; memcpy(tmp, m, sizeof(tmp)); scalarFuncs.inverse(tmp); doNotOptimize(tmp); },
         [&] { float tmp[16]; memcpy(tmp, m, sizeof(tmp)); isaFuncs.inverse(tmp);    doNotOptimize(tmp); });

      benchOp("mat44", "inverse_to", iterations,
         [&] { scalarFuncs.inverse_to(m, out16); doNotOptimize(out16); },
         [&] { isaFuncs.inverse_to(m, out16);    doNotOptimize(out16); });

      benchOp("mat44", "affine_inverse", iterations,
         [&] { float tmp[16]; memcpy(tmp, m, sizeof(tmp)); scalarFuncs.affine_inverse(tmp); doNotOptimize(tmp); },
         [&] { float tmp[16]; memcpy(tmp, m, sizeof(tmp)); isaFuncs.affine_inverse(tmp);    doNotOptimize(tmp); });

      benchOp("mat44", "mul_mat44", iterations,
         [&] { scalarFuncs.mul_mat44(m, m2, out16); doNotOptimize(out16); },
         [&] { isaFuncs.mul_mat44(m, m2, out16);    doNotOptimize(out16); });

      benchOp("mat44", "mul_pos3", iterations,
         [&] { scalarFuncs.mul_pos3(m, pos3, out3); doNotOptimize(out3); },
         [&] { isaFuncs.mul_pos3(m, pos3, out3);    doNotOptimize(out3); });

      benchOp("mat44", "mul_vec3", iterations,
         [&] { scalarFuncs.mul_vec3(m, pos3, out3); doNotOptimize(out3); },
         [&] { isaFuncs.mul_vec3(m, pos3, out3);    doNotOptimize(out3); });

      benchOp("mat44", "mul_float4", iterations,
         [&] { float p4[4] = { 1,2,3,1 }; scalarFuncs.mul_float4(m, p4, out4); doNotOptimize(out4); },
         [&] { float p4[4] = { 1,2,3,1 }; isaFuncs.mul_float4(m, p4, out4);    doNotOptimize(out4); });

      // transform_plane is a known gap in install_avx2/install_neon (unrelated to this
      // bench) - guard so the harness doesn't crash on a null function pointer there.
      if (scalarFuncs.transform_plane && isaFuncs.transform_plane)
      {
         benchOp("mat44", "transform_plane", iterations,
            [&] { scalarFuncs.transform_plane(m, planeS, planeIn, planeOut); doNotOptimize(planeOut); },
            [&] { isaFuncs.transform_plane(m, planeS, planeIn, planeOut);    doNotOptimize(planeOut); });
      }
      else
      {
         Con::warnf("[math_bench] mat44.transform_plane not installed for '%s' - skipping", isaName);
      }

      benchOp("mat44", "scale", iterations,
         [&] { float tmp[16]; memcpy(tmp, m, sizeof(tmp)); scalarFuncs.scale(tmp, scaleVec); doNotOptimize(tmp); },
         [&] { float tmp[16]; memcpy(tmp, m, sizeof(tmp)); isaFuncs.scale(tmp, scaleVec);    doNotOptimize(tmp); });

      benchOp("mat44", "get_scale", iterations,
         [&] { scalarFuncs.get_scale(m, out3); doNotOptimize(out3); },
         [&] { isaFuncs.get_scale(m, out3);    doNotOptimize(out3); });

      benchOp("mat44", "normalize", iterations,
         [&] { float tmp[16]; memcpy(tmp, m, sizeof(tmp)); scalarFuncs.normalize(tmp); doNotOptimize(tmp); },
         [&] { float tmp[16]; memcpy(tmp, m, sizeof(tmp)); isaFuncs.normalize(tmp);    doNotOptimize(tmp); });

      benchOp("mat44", "determinant", iterations,
         [&] { det = scalarFuncs.determinant(m); doNotOptimize(det); },
         [&] { det = isaFuncs.determinant(m);    doNotOptimize(det); });

      if (scalarFuncs.batch_mul_pos3 && isaFuncs.batch_mul_pos3)
      {
         benchOp("mat44", "batch_mul_pos3(64)", iterations,
            [&] { scalarFuncs.batch_mul_pos3(m, batchPts, kBatchCount, batchOut); doNotOptimize(batchOut); },
            [&] { isaFuncs.batch_mul_pos3(m, batchPts, kBatchCount, batchOut);    doNotOptimize(batchOut); });
      }
   }
}

DefineEngineFunction(testMathBackendPerf, void, (const char* isa, S32 iterations), ("sse2", 0),
   "testMathBackendPerf([isa], [iterations]) - benchmarks scalar vs a named ISA "
   "(sse2/sse41/avx/avx2/neon) across Float3, Float4 and Mat44. Only pass an ISA "
   "your current CPU actually supports.")
{
   if (iterations < 1)
      iterations = 2000000;

   Con::printf("==== math_backend perf: isa=%s iterations=%d ====", isa, iterations);
   math_backend::bench::runFloat3Bench((U32)iterations, isa);
   math_backend::bench::runFloat4Bench((U32)iterations, isa);
   math_backend::bench::runMat44Bench((U32)iterations, isa);
}

DefineEngineFunction(testFloat3BackendPerf, void, (const char* isa, S32 iterations), ("sse2", 0), "")
{
   math_backend::bench::runFloat3Bench((U32)(iterations < 1 ? 2000000 : iterations), isa);
}

DefineEngineFunction(testFloat4BackendPerf, void, (const char* isa, S32 iterations), ("sse2", 0), "")
{
   math_backend::bench::runFloat4Bench((U32)(iterations < 1 ? 2000000 : iterations), isa);
}

DefineEngineFunction(testMat44BackendPerf, void, (const char* isa, S32 iterations), ("sse2", 0), "")
{
   math_backend::bench::runMat44Bench((U32)(iterations < 1 ? 2000000 : iterations), isa);
}

#endif // TORQUE_DEBUG || TORQUE_MATH_BENCH
