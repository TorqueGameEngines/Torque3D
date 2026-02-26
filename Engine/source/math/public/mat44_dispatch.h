#pragma once
#ifndef _MAT44_DISPATCH_H_
#define _MAT44_DISPATCH_H_


namespace math_backend::mat44::dispatch
{
   struct Mat44Funcs
   {
      void (*transpose)(float*) = nullptr;
      void (*scale)(float*, const float*) = nullptr;
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
