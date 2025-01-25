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

#ifndef _GFONT_H_
#define _GFONT_H_

//Includes
#ifndef _RESOURCE_H_
#include "core/resource.h"
#endif
#ifndef _PLATFORMFONT_H_
#include "platform/platformFont.h"
#endif
#ifndef _GBITMAP_H_
#include "gfx/bitmap/gBitmap.h"
#endif
#ifndef _GFXDEVICE_H_
#include "gfx/gfxDevice.h"
#endif
#ifndef _GFXTEXTUREHANDLE_H_
#include "gfx/gfxTextureHandle.h"
#endif
#ifndef _TDICTIONARY_H_
#include "core/util/tDictionary.h"
#endif


GFX_DeclareTextureProfile(GFXFontTextureProfile);

class GFont
{
public:
   typedef Map<U32, PlatformFont::CharInfo> typeCharMap;
   enum Constants 
   {
      TabWidthInSpaces = 3,
      TextureSheetSize = 512,
   };

public:
   GFont();
   virtual ~GFont();
   
   static Resource<GFont> create(const String &faceName, const char *cacheDirectory = 0, U32 charset = TGE_ANSI_CHARSET);

   GFXTexHandle getTextureHandle(S32 index) const { return mTextureSheets[index]; }

   ///----------------------------------
   /// SDF Functions
   ///----------------------------------
   U32 getScaledHeight(U32 renderSize) const {
      return static_cast<U32>(mHeight * (static_cast<F32>(renderSize) / mSize) + 0.5f);
   }

   U32 getScaledBaseline(U32 renderSize) const {
      return static_cast<U32>(mBaseline * (static_cast<F32>(renderSize) / mSize) + 0.5f);
   }

   U32 getScaledAscent(U32 renderSize) const {
      return static_cast<U32>(mAscent * (static_cast<F32>(renderSize) / mSize) + 0.5f);
   }

   U32 getScaledDescent(U32 renderSize) const {
      return static_cast<U32>(mDescent * (static_cast<F32>(renderSize) / mSize) + 0.5f);
   }

   U32 getCharHeightScaled(const UTF16 in_charIndex, U32 renderSize) {
      return static_cast<U32>(getCharHeight(in_charIndex) *
         (static_cast<F32>(renderSize) / mSize) + 0.5f);
   }

   U32 getCharWidthScaled(const UTF16 in_charIndex, U32 renderSize) {
      return static_cast<U32>(getCharWidth(in_charIndex) *
         (static_cast<F32>(renderSize) / mSize) + 0.5f);
   }

   U32 getCharXIncrementScaled(const UTF16 in_charIndex, U32 renderSize) {
      return static_cast<U32>(getCharXIncrement(in_charIndex) *
         (static_cast<F32>(renderSize) / mSize) + 0.5f);
   }

   U32 getStringWidthScaled(const String& text, U32 renderSize);
   U32 getStringWidthScaledPrecise(const String& text, U32 renderSize);

   U32 getStringWidthScaled(const String& text, U32 renderSize, U32 length);
   U32 getStringWidthScaledPrecise(const String& text, U32 renderSize, U32 length);

   void wrapStringScaled(const UTF8* txt, U32 lineWidth, U32 renderSize, Vector<U32>& startLineOffset, Vector<U32>& lineLen);
   U32 getBreakPosScaled(const UTF16* str16, U32 slen, U32 width, U32 renderSize, bool breakOnWhitespace);

   const PlatformFont::CharInfo& getCharInfo(const UTF16 in_charIndex);
   PlatformFont::CharInfo getScaledCharInfo(const UTF16 in_charIndex, U32 renderSize);
   static const PlatformFont::CharInfo& getDefaultCharInfo();

   U32  getCharHeight(const UTF16 in_charIndex);
   U32  getCharWidth(const UTF16 in_charIndex);
   U32  getCharXIncrement(const UTF16 in_charIndex);
   
   bool isValidChar(const UTF16 in_charIndex) const;

   const U32 getHeight() const   { return mHeight; }
   const U32 getBaseline() const { return mBaseline; }
   const U32 getAscent() const   { return mAscent; }
   const U32 getDescent() const  { return mDescent; }

   /// Dump information about this font to the console.
   void dumpInfo() const;

   /// Export to an image strip for image processing.
   void exportStrip(const char *fileName, U32 padding, U32 kerning);

   /// Import an image strip generated with exportStrip, make sure parameters match!
   void importStrip(const char *fileName, U32 padding, U32 kerning);

   void  setPlatformFont(PlatformFont *inPlatformFont);

   /// Query as to presence of platform font. If absent, we cannot generate more
   /// chars!
   const bool hasPlatformFont() const
   {
      return mPlatformFont != NULL;
   }

   /// Query to determine if we should use add or modulate (as A8 textures
   /// are treated as having 0 for RGB).
   bool isAlphaOnly() const
   {
      return mTextureSheets[0]->getBitmap()->getFormat() == GFXFormatA8;
   }

   /// Get the filename for a cached font.
   static String getFontCacheFilename(const String &faceName);

   /// Get the face name of the font.
   String   getFontFaceName() const { return mFaceName; };
   U32      getFontSize() const { return mSize; }
   U32      getFontCharSet() const { return mCharSet; }

   bool read(Stream& io_rStream);
   bool write(Stream& io_rStream);

   static GFont* load( const Torque::Path& path );

protected:
   bool loadCharInfo(const UTF16 ch);
   void generateSDF(const U8* bitmap, S32 width, S32 height, U8* sdfBitmap, S32 sdfWidth, S32 sdfHeight, const F32 spreadFactor);
   void padGlyphBitmap(const U8* original, S32 origWidth, S32 origHeight, U8* padded, S32 padWidth, S32 padHeight, S32 padding);
   void addBitmap(PlatformFont::CharInfo &charInfo);
   void addSheet(void);
   void *mMutex;

private:
   static const U32 csm_fileVersion;

   PlatformFont *mPlatformFont;
   Vector<GFXTexHandle>mTextureSheets;

   S32 mCurX;
   S32 mCurY;
   S32 mCurSheet;
   S32 mMaxRowHeight;

   bool mNeedSave;
   Torque::Path mGFTFile;
   String mFaceName;
   U32 mSize;
   U32 mCharSet;

   U32 mHeight;
   U32 mBaseline;
   U32 mAscent;
   U32 mDescent;

   // Cache charinfo into a map.
   typeCharMap mCharMap;
};

inline U32 GFont::getCharXIncrement(const UTF16 in_charIndex)
{
    const PlatformFont::CharInfo& rChar = getCharInfo(in_charIndex);
    return rChar.xIncrement;
}

inline U32 GFont::getCharWidth(const UTF16 in_charIndex)
{
    const PlatformFont::CharInfo& rChar = getCharInfo(in_charIndex);
    return rChar.width;
}

inline U32 GFont::getCharHeight(const UTF16 in_charIndex)
{
    const PlatformFont::CharInfo& rChar = getCharInfo(in_charIndex);
    return rChar.height;
}

inline bool GFont::isValidChar(const UTF16 in_charIndex) const
{
   auto it = mCharMap.find(in_charIndex);
   if (it != mCharMap.end())
      return true;

   if(mPlatformFont)
      return mPlatformFont->isValidChar(in_charIndex);

   return false;
}

#endif //_GFONT_H_
