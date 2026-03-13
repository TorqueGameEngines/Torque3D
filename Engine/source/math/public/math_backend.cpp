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
