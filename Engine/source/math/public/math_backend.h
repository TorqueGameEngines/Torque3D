#pragma once
#ifndef _MCONSTANTS_H_
#include "math/mConstants.h"
#endif
#ifndef _PLATFORMASSERT_H_
#include "platform/platformAssert.h"
#endif
#ifndef _FLOAT4_DISPATCH_H_
#include "math/public/float4_dispatch.h"
#endif

namespace math_backend
{
   enum class backend
   {
      scalar,
      sse2,
      sse41,
      avx,
      avx2,
      neon
   };

   static backend g_backend = backend::scalar;
   backend choose_backend(U32 cpu_flags);
   void install_from_cpu_flags(uint32_t cpu_flags);
}
