#include "math/public/float4_dispatch.h"
#include "math/mConstants.h"
#include <math.h>

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
         for (int i = 0; i < 4; i++) r[i] = a[i] / s;
      };

      gFloat4.dot = [](const float* a, const float* b) {
         float sum = 0.f;
         for (int i = 0; i < 4; i++) sum += a[i] * b[i];
         return sum;
      };

      gFloat4.length = [](const float* a) {
         float sum = 0.f;
         for (int i = 0; i < 4; i++) sum += a[i] * a[i];
         return sqrtf(sum);
      };

      gFloat4.lengthSquared = [](const float* a) {
         float sum = 0.f;
         for (int i = 0; i < 4; i++) sum += a[i] * a[i];
         return (sum);
      };

      gFloat4.normalize = [](float* a) {
         float len = gFloat4.length(a);
         if (len > POINT_EPSILON) for (int i = 0; i < 4; i++) a[i] /= len;
      };

      gFloat4.lerp = [](const float* from, const float* to, float f, float* r) {
         for (int i = 0; i < 4; i++) r[i] = from[i] + (to[i] - from[i]) * f;
      };
   }
}
