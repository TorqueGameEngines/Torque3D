#pragma once
#ifndef _MAT44_DISPATCH_H_
#define _MAT44_DISPATCH_H_


namespace math_backend::mat44::dispatch
{
   struct Mat44Funcs
   {
      void (*transpose)(float*) = nullptr;
      void (*inverse)(float*) = nullptr;
      void (*inverse_to)(const float*, float*) = nullptr;
      void (*affine_inverse)(float*) = nullptr;
      void (*normalize)(float*) = nullptr;
      void (*mul_mat44)(const float* a, const float* b, float* r) = nullptr;
      void (*mul_pos3)(const float* a, const float* b, float* r) = nullptr;
      void (*mul_vec3)(const float* a, const float* b, float* r) = nullptr;
      void (*mul_float4)(const float* a, const float* b, float* r) = nullptr;
      void (*transform_plane)(const float* m, const float* s, const float* p, float* r) = nullptr;
      float (*determinant)(const float*) = nullptr;
      void (*scale)(float*, const float*) = nullptr;
      void (*get_scale)(const float*, float*) = nullptr;

      void (*batch_mul_pos3)(const float* m, const float* pts, int count, float* result_ptrs) = nullptr;
   };

   // Global dispatch table
   extern Mat44Funcs gMat44;

   // Backend installers (defined in ISA libraries)
   void install_scalar();
   void install_sse2();
   void install_sse41();
   void install_avx();
   void install_avx2();
   void install_neon();
}

#endif // !_MAT44_DISPATCH_H_
