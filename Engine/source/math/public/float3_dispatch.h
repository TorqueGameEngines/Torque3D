#pragma once
#ifndef _FLOAT3_DISPATCH_H_
#define _FLOAT3_DISPATCH_H_


#include <cstdint>

namespace math_backend::float3::dispatch
{
   struct Float3Funcs
   {
      void (*add)(const float*, const float*, float*) = nullptr;
      void (*sub)(const float*, const float*, float*) = nullptr;
      void (*mul)(const float*, const float*, float*) = nullptr;
      void (*mul_scalar)(const float*, float, float*) = nullptr;
      void (*div)(const float*, const float*, float*) = nullptr;
      void (*div_scalar)(const float*, float, float*) = nullptr;
      float (*dot)(const float*, const float*) = nullptr;
      float (*length)(const float*) = nullptr;
      float (*lengthSquared)(const float*) = nullptr;
      void (*normalize)(float*) = nullptr;
      void (*normalize_mag)(float*, float) = nullptr;
      void (*lerp)(const float*, const float*, float, float*) = nullptr;
      void (*cross)(const float*, const float*, float*) = nullptr;
   };

   // Global dispatch table
   extern Float3Funcs gFloat3;

   // Backend installers (defined in ISA libraries)
   void install_scalar();
   void install_sse2();
   void install_sse41();
   void install_avx();
   void install_avx2();
   void install_neon();
}

#endif // !_FLOAT4_DISPATCH_H_
