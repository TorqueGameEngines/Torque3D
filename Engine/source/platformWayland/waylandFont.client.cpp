//-----------------------------------------------------------------------------
// Copyright (c) 2012 GarageGames, LLC
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

#include "gfx/gFont.h"
#include "gfx/bitmap/gBitmap.h"
#include "math/mRect.h"
#include "console/console.h"
#include "core/strings/unicode.h"
#include "core/stringTable.h"
#include "platformPOSIX/platformPOSIX.h"
#include "platformWayland/waylandFont.h"

// This implementation deliberately avoids libX11/Xft. Under Wayland there is
// no guarantee that an X server (or XWayland) is available, and Wayland
// itself has no core font protocol, so font matching and rasterization are
// done entirely with Fontconfig (name -> file matching) and FreeType
// (rasterization), neither of which talks to any display server.
#include <fontconfig/fontconfig.h>
#include <ft2build.h>
#include FT_FREETYPE_H

#include <stdlib.h>

namespace
{
   FT_Library sFTLibrary = NULL;
   bool sFTInitAttempted = false;

   bool ensureFreeTypeInitialized()
   {
      if (!sFTInitAttempted)
      {
         sFTInitAttempted = true;
         if (FT_Init_FreeType(&sFTLibrary) != 0)
         {
            Con::errorf("waylandFont: unable to initialize FreeType library");
            sFTLibrary = NULL;
         }
      }

      return sFTLibrary != NULL;
   }

   // Resolves a logical font request (name/weight/slant) to a concrete font
   // file + face index using Fontconfig - the same matching engine Xft used
   // internally, but without requiring a connection to any windowing system.
   bool resolveFontFile(const char *name, S32 size, String &outFile, S32 &outIndex)
   {
      if (!FcInit())
      {
         Con::errorf("waylandFont: unable to initialize Fontconfig");
         return false;
      }

      const char *family = (name && dStrlen(name) != 0) ? name : "sans-serif";
      bool bold = name && stristr(name, "bold") != NULL;
      bool italic = name && stristr(name, "italic") != NULL;

      FcPattern *pattern = FcPatternCreate();
      FcPatternAddString(pattern, FC_FAMILY, (const FcChar8*)family);
      FcPatternAddDouble(pattern, FC_SIZE, (double)size);
      FcPatternAddInteger(pattern, FC_WEIGHT, bold ? FC_WEIGHT_BOLD : FC_WEIGHT_MEDIUM);
      FcPatternAddInteger(pattern, FC_SLANT, italic ? FC_SLANT_ITALIC : FC_SLANT_ROMAN);

      FcConfigSubstitute(NULL, pattern, FcMatchPattern);
      FcDefaultSubstitute(pattern);

      FcResult result;
      FcPattern *match = FcFontMatch(NULL, pattern, &result);
      FcPatternDestroy(pattern);

      if (!match)
         return false;

      FcChar8 *file = NULL;
      bool ok = (FcPatternGetString(match, FC_FILE, 0, &file) == FcResultMatch) && file != NULL;
      if (ok)
      {
         S32 index = 0;
         FcPatternGetInteger(match, FC_INDEX, 0, &index);
         outFile = String((const char*)file);
         outIndex = index;
      }

      FcPatternDestroy(match);
      return ok;
   }
}

PlatformFont *createPlatformFont(const char *name, dsize_t size, U32 charset /* = TGE_ANSI_CHARSET */)
{
  PlatformFont *retFont = new waylandFont;

  if(retFont->create(name, size, charset))
    return retFont;

  delete retFont;
  return NULL;
}

waylandFont::waylandFont()
   : baseline(0), height(0), mFontName(NULL), mFontIndex(0), mPixelSize(0)
{}

waylandFont::~waylandFont()
{}


bool waylandFont::create(const char *name, dsize_t size, U32 charset)
{
  if (!ensureFreeTypeInitialized())
    return false;

  String fontFile;
  S32 fontIndex = 0;
  if (!resolveFontFile(name, (S32)size, fontFile, fontIndex))
  {
    Con::errorf("Error: Could not resolve font -%s-", name);
    return false;
  }

  FT_Face face;
  if (FT_New_Face(sFTLibrary, fontFile.c_str(), fontIndex, &face) != 0)
  {
    Con::errorf("Error: Could not load font file '%s'", fontFile.c_str());
    return false;
  }

  FT_Set_Pixel_Sizes(face, 0, (FT_UInt)size);

  // store some info about the font
  baseline = (int)(face->size->metrics.ascender >> 6);
  height   = (int)((face->size->metrics.ascender - face->size->metrics.descender) >> 6);
  mFontName = StringTable->insert(fontFile.c_str());
  mFontIndex = fontIndex;
  mPixelSize = (int)size;

#ifdef DEBUG
  Con::printf("CreateFont: request for %s %d, using %s (face %d)", name, (S32)size, fontFile.c_str(), fontIndex);
#endif

  FT_Done_Face(face);

  return true;
}

bool waylandFont::isValidChar(const UTF16 str) const
{
  // 0x20  == 32
  // 0x100 == 256
  if( str < 0x20 || str > 0x100 )
    return false;

  return true;
}

bool waylandFont::isValidChar(const UTF8 *str) const
{

  return isValidChar(oneUTF32toUTF16(oneUTF8toUTF32(str,NULL)));
}

PlatformFont::CharInfo &waylandFont::getCharInfo(const UTF16 ch) const
{
  static PlatformFont::CharInfo c;
  dMemset(&c, 0, sizeof(c));
  c.bitmapIndex = 0;
  c.xOffset     = 0;
  c.yOffset     = 0;

  if (!sFTLibrary || !mFontName)
    return c;

  FT_Face face;
  if (FT_New_Face(sFTLibrary, mFontName, mFontIndex, &face) != 0)
  {
    AssertFatal(false, "waylandFont::getCharInfo - cannot load font face");
    return c;
  }

  FT_Set_Pixel_Sizes(face, 0, (FT_UInt)mPixelSize);

  FT_UInt glyphIndex = FT_Get_Char_Index(face, ch);
  if (glyphIndex == 0 ||
      FT_Load_Glyph(face, glyphIndex, FT_LOAD_RENDER | FT_LOAD_TARGET_NORMAL) != 0)
  {
    FT_Done_Face(face);
    return c;
  }

  FT_GlyphSlot slot = face->glyph;
  FT_Bitmap &bmp = slot->bitmap;

  c.height     = (U32)height;
  c.xOrigin    = 0;
  c.yOrigin    = baseline;
  c.xIncrement = (S32)(slot->advance.x >> 6);
  c.width      = (U32)(c.xIncrement > 0 ? c.xIncrement : (S32)bmp.width);

  // kick out early if the character is undrawable
  if( c.width == 0 || c.height == 0)
  {
    FT_Done_Face(face);
    return c;
  }

  // allocate a greyscale bitmap and clear it.
  U32 bitmapDataSize = c.width * c.height;
  c.bitmapData = new U8[bitmapDataSize];
  dMemset(c.bitmapData, 0, bitmapDataSize);

  const S32 originX = slot->bitmap_left;
  const S32 originY = baseline - slot->bitmap_top;

  // blit the FreeType-rendered glyph bitmap into our bitmap, clipping to
  // bounds. This is the direct FreeType equivalent of the XftDrawGlyphs +
  // XGetImage round trip the old X11 implementation used.
  for (U32 y = 0; y < bmp.rows; y++)
  {
    S32 destY = (S32)y + originY;
    if (destY < 0 || destY >= (S32)c.height)
      continue;

    for (U32 x = 0; x < bmp.width; x++)
    {
      S32 destX = (S32)x + originX;
      if (destX < 0 || destX >= (S32)c.width)
        continue;

      c.bitmapData[destY * c.width + destX] = bmp.buffer[y * bmp.pitch + x];
    }
  }

  FT_Done_Face(face);

  return c;
}


PlatformFont::CharInfo &waylandFont::getCharInfo(const UTF8 *str) const
{
  return getCharInfo(oneUTF32toUTF16(oneUTF8toUTF32(str,NULL)));
}

void PlatformFont::enumeratePlatformFonts( Vector<StringTableEntry>& fonts, UTF16* fontFamily )
{
  // Fontconfig gives us the full system font list without needing to talk
  // to any windowing system (X11 or Wayland).
  (void)fontFamily;

  if (!FcInit())
    return;

  FcPattern *pattern = FcPatternCreate();
  FcObjectSet *os = FcObjectSetBuild(FC_FAMILY, (char*)0);
  FcFontSet *fs = FcFontList(NULL, pattern, os);

  if (fs)
  {
    for (S32 i = 0; i < fs->nfont; i++)
    {
      FcChar8 *family = NULL;
      if (FcPatternGetString(fs->fonts[i], FC_FAMILY, 0, &family) == FcResultMatch && family)
        fonts.push_back(StringTable->insert((const char*)family));
    }

    FcFontSetDestroy(fs);
  }

  FcObjectSetDestroy(os);
  FcPatternDestroy(pattern);
}
