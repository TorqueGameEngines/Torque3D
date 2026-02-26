#pragma once
#ifndef _MATH_BACKEND_H_
#define _MATH_BACKEND_H_

#ifndef _MCONSTANTS_H_
#include "math/mConstants.h"
#endif
#ifndef _PLATFORMASSERT_H_
#include "platform/platformAssert.h"
#endif
#ifndef _FLOAT4_DISPATCH_H_
#include "math/public/float4_dispatch.h"
#endif
#ifndef _FLOAT3_DISPATCH_H_
#include "math/public/float3_dispatch.h"
#endif
#ifndef _MAT44_DISPATCH_H_
#include "math/public/mat44_dispatch.h"
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

#endif // !_MATH_BACKEND_H_
