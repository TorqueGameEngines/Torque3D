#include "math/public/float4_dispatch.h"
#include "math/public/float3_dispatch.h"
#include "math/public/mat44_dispatch.h"
#include "math/mConstants.h"
#include <cmath>   // for sqrtf, etc.

namespace math_backend::float4::dispatch
{
   void install_scalar()
   {
      gFloat4.add = [](const float* a, const float* b, float* r) {
         for (int i = 0; i < 4; i++) r[i] = a[i] + b[i];
      };

      gFloat4.sub = [](const float* a, const float* b, float* r) {
         for (int i = 0; i < 4; i++) r[i] = a[i] - b[i];
      };

      gFloat4.mul = [](const float* a, const float* b, float* r) {
         for (int i = 0; i < 4; i++) r[i] = a[i] * b[i];
      };

      gFloat4.mul_scalar = [](const float* a, float s, float* r) {
         for (int i = 0; i < 4; i++) r[i] = a[i] * s;
      };

      gFloat4.div = [](const float* a, const float* b, float* r) {
         for (int i = 0; i < 4; i++) r[i] = a[i] / b[i];
      };

      gFloat4.div_scalar = [](const float* a, float s, float* r) {
         float denom = 1.0f / s;
         for (int i = 0; i < 4; i++) r[i] = a[i] * denom;
      };

      gFloat4.dot = [](const float* a, const float* b) {
         float sum = 0.f;
         for (int i = 0; i < 4; i++) sum += a[i] * b[i];
         return sum;
      };

      gFloat4.length = [](const float* a) {
         float sum = 0.f;
         for (int i = 0; i < 4; i++) sum += a[i] * a[i];
         return std::sqrt(sum);
      };

      gFloat4.lengthSquared = [](const float* a) {
         float sum = 0.f;
         for (int i = 0; i < 4; i++) sum += a[i] * a[i];
         return (sum);
      };

      gFloat4.normalize = [](float* a) {
         float len = gFloat4.length(a);
         if (len > POINT_EPSILON)
         {
            float denom = 1.0f / len;
            for (int i = 0; i < 4; i++)
               a[i] *= denom;
         }
      };

      gFloat4.normalize_mag = [](float* a, float f) {
         float len = gFloat4.length(a);
         if (len > POINT_EPSILON)
         {
            float denom = f / len;
            for (int i = 0; i < 4; i++) a[i] *= denom;
         }
      };

      gFloat4.lerp = [](const float* from, const float* to, float f, float* r) {
         for (int i = 0; i < 4; i++) r[i] = from[i] + (to[i] - from[i]) * f;
      };

      gFloat4.cross = [](const float* a, const float* b, float* r) {
         const float ax = a[0];
         const float ay = a[1];
         const float az = a[2];

         const float bx = b[0];
         const float by = b[1];
         const float bz = b[2];

         r[0] = ay * bz - az * by;
         r[1] = az * bx - ax * bz;
         r[2] = ax * by - ay * bx;
      };
   }
}

namespace math_backend::float3::dispatch
{
   void install_scalar()
   {
      gFloat3.add = [](const float* a, const float* b, float* r) {
         for (int i = 0; i < 3; i++) r[i] = a[i] + b[i];
      };

      gFloat3.sub = [](const float* a, const float* b, float* r) {
         for (int i = 0; i < 3; i++) r[i] = a[i] - b[i];
      };

      gFloat3.mul = [](const float* a, const float* b, float* r) {
         for (int i = 0; i < 3; i++) r[i] = a[i] * b[i];
      };

      gFloat3.mul_scalar = [](const float* a, float s, float* r) {
         for (int i = 0; i < 3; i++) r[i] = a[i] * s;
      };

      gFloat3.div = [](const float* a, const float* b, float* r) {
         for (int i = 0; i < 3; i++) r[i] = a[i] / b[i];
      };

      gFloat3.div_scalar = [](const float* a, float s, float* r) {
         float denom = 1.0f / s;
         for (int i = 0; i < 3; i++) r[i] = a[i] * denom;
      };

      gFloat3.dot = [](const float* a, const float* b) {
         float sum = 0.f;
         for (int i = 0; i < 3; i++) sum += a[i] * b[i];
         return sum;
      };

      gFloat3.length = [](const float* a) {
         float sum = 0.f;
         for (int i = 0; i < 3; i++) sum += a[i] * a[i];
         return std::sqrt(sum);
      };

      gFloat3.lengthSquared = [](const float* a) {
         float sum = 0.f;
         for (int i = 0; i < 3; i++) sum += a[i] * a[i];
         return (sum);
      };

      gFloat3.normalize = [](float* a) {
         float len = gFloat3.length(a);
         if (len > POINT_EPSILON)
         {
            float denom = 1.0 / len;
            for (int i = 0; i < 3; i++) a[i] *= denom;
         }
      };

      gFloat3.normalize_mag = [](float* a, float f) {
         float len = gFloat3.length(a);
         if (len > POINT_EPSILON)
         {
            float denom = f / len;
            for (int i = 0; i < 3; i++) a[i] *= denom;
         }
      };

      gFloat3.lerp = [](const float* from, const float* to, float f, float* r) {
         for (int i = 0; i < 3; i++) r[i] = from[i] + (to[i] - from[i]) * f;
      };

      gFloat3.cross = [](const float* a, const float* b, float* r) {
         const float ax = a[0];
         const float ay = a[1];
         const float az = a[2];

         const float bx = b[0];
         const float by = b[1];
         const float bz = b[2];

         r[0] = ay * bz - az * by;
         r[1] = az * bx - ax * bz;
         r[2] = ax * by - ay * bx;
      };
   }
}

inline void swap(float& a, float& b)
{
   float temp = a;
   a = b;
   b = temp;
}


namespace math_backend::mat44::dispatch
{
   void install_scalar()
   {
      gMat44.transpose = [](float* a) {
         swap(a[1], a[4]);
         swap(a[2], a[8]);
         swap(a[3], a[12]);
         swap(a[6], a[9]);
         swap(a[7], a[13]);
         swap(a[11], a[14]);
      };

      gMat44.scale = [](float* a, const float* s) {
         // Note, doesn't allow scaling w...

         a[0] *= s[0];  a[1] *= s[1];  a[2] *= s[2];
         a[4] *= s[0];  a[5] *= s[1];  a[6] *= s[2];
         a[8] *= s[0];  a[9] *= s[1];  a[10] *= s[2];
         a[12] *= s[0];  a[13] *= s[1];  a[14] *= s[2];
      };
   }
}
