//-----------------------------------------------------------------------------
// Copyright (c) 2016 GarageGames, LLC
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to
// deal in the Software without restriction, including without limitation the
// rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
// sell copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
// FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
// IN THE SOFTWARE.
//-----------------------------------------------------------------------------

#include "platform/platform.h"
#include "gfx/gl/screenshotGL.h"
#include "gfx/gl/gfxGLDevice.h"
#include "gfx/bitmap/gBitmap.h"

//Note if MSAA is ever enabled this will need fixing
GBitmap* ScreenShotGL::_captureBackBuffer()
{
   glPixelStorei(GL_PACK_ALIGNMENT, 1);
   glReadBuffer(GL_BACK);

   Point2I size = GFX->getViewport().extent;
   U8* pixels = new U8[size.x * size.y * 4];
   glReadPixels(0, 0, size.x, size.y, GL_RGB, GL_UNSIGNED_BYTE, pixels);

   GBitmap* bitmap = new GBitmap(size.x, size.y);

   for (U32 y = 0; y < (U32)size.y; y++)
      dMemcpy(bitmap->getAddress(0, y), pixels + y * size.x * 3, U32(size.x * 3));

   delete[] pixels;

   return bitmap;
}

