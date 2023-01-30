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

#include "platform/platform.h"
#include "platform/types.h"
#include "console/consoleTypes.h"
#include "console/console.h"
#include "console/engineAPI.h"
#include "gui/core/guiTypes.h"
#include "gui/core/guiControl.h"
#include "gfx/gFont.h"
#include "gfx/bitmap/gBitmap.h"
#include "gfx/gfxDevice.h"
#include "gfx/gfxDrawUtil.h"
#include "sfx/sfxTrack.h"
#include "sfx/sfxTypes.h"
#include "console/engineAPI.h"

//#define DEBUG_SPEW


// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- //
IMPLEMENT_CONOBJECT(GuiCursor);

ConsoleDocClass( GuiCursor,
   "@brief Acts as a skin for the cursor, where each GuiCursor object can have its own look and click-zone.\n\n"

   "GuiCursors act as skins for the cursor in the game, where each individual GuiCursor can have its own defined imagemap,\n"
   "click zone and render offset. This allows a game to easily support a wide range of cursors. The active cursor can de changed\n"
   "for each Canvas using %canvasObj.setCursor(GuiCursor);."

   "@tsexample\n"
	"new GuiCursor(DefaultCursor)\n"
	"{\n"
    "	hotSpot = \"1 1\";\n"
    "	renderOffset = \"0 0\";\n"
    "	bitmapName = \"~/art/gui/images/defaultCursor\";\n"
   "};\n"
   "@endtsexample\n\n"
   "@see GuiCanvas\n\n"
   "@ingroup GuiCore\n"
);

GFX_ImplementTextureProfile(GFXGuiCursorProfile,
                            GFXTextureProfile::DiffuseMap, 
                            GFXTextureProfile::PreserveSize |
                            GFXTextureProfile::Static | GFXTextureProfile::SRGB,
                            GFXTextureProfile::NONE);
GFX_ImplementTextureProfile(GFXDefaultGUIProfile,
                            GFXTextureProfile::DiffuseMap, 
                            GFXTextureProfile::PreserveSize |
                            GFXTextureProfile::Static | GFXTextureProfile::KeepBitmap | GFXTextureProfile::SRGB |
                            GFXTextureProfile::NoPadding, 
                            GFXTextureProfile::NONE);


GuiCursor::GuiCursor()
{
   mHotSpot.set(0,0);
   mRenderOffset.set(0.0f,0.0f);
   mExtent.set(1,1);

   INIT_ASSET(Bitmap);
}

GuiCursor::~GuiCursor()
{
}

void GuiCursor::initPersistFields()
{
   docsURL;
   addField("hotSpot",     TypePoint2I,   Offset(mHotSpot, GuiCursor), "The location of the cursor's hot spot (which pixel carries the click).");
   addField("renderOffset",TypePoint2F,   Offset(mRenderOffset, GuiCursor), "Offset of the bitmap, where 0 signifies left edge of the bitmap, 1, the right. Similarly for the Y-component.");

   addProtectedField("bitmapName",  TypeImageFilename,  Offset(mBitmapName, GuiCursor), _setBitmapData, &defaultProtectedGetFn, "File name of the bitmap for the cursor.");
   INITPERSISTFIELD_IMAGEASSET(Bitmap, GuiCursor, "name of the bitmap for the cursor.");
   Parent::initPersistFields();
}

bool GuiCursor::onAdd()
{
   if(!Parent::onAdd())
      return false;

   Sim::getGuiDataGroup()->addObject(this);

   return true;
}

void GuiCursor::onRemove()
{
   Parent::onRemove();
}

void GuiCursor::render(const Point2I &pos)
{
   if (mBitmap)
   {
      mExtent.set(mBitmap->getWidth(), mBitmap->getHeight());
   }

   // Render the cursor centered according to dimensions of texture
   S32 texWidth = mBitmap.getWidth();
   S32 texHeight = mBitmap.getHeight();

   Point2I renderPos = pos;
   renderPos.x -= (S32)( texWidth  * mRenderOffset.x );
   renderPos.y -= (S32)( texHeight * mRenderOffset.y );

   GFX->getDrawUtil()->clearBitmapModulation();
   GFX->getDrawUtil()->drawBitmap(mBitmap, renderPos);
}

//------------------------------------------------------------------------------
IMPLEMENT_CONOBJECT(GuiControlProfile);

ConsoleDocClass( GuiControlProfile,
   "@brief A collection of properties that determine control behavior and rendering.\n"
   "@ingroup GuiCore\n"
   
   ""
);

ImplementEnumType( GuiAlignmentType,
   "\n\n"
   "@ingroup GuiCore" )
   { GuiControlProfile::LeftJustify,          "Left"      },
   { GuiControlProfile::CenterJustify,        "Center"    },
   { GuiControlProfile::RightJustify,         "Right"     },
   { GuiControlProfile::TopJustify,           "Top"       },
   { GuiControlProfile::BottomJustify,        "Bottom"    }
EndImplementEnumType;

ImplementEnumType( GuiFontCharset,
   "\n\n"
   "@ingroup GuiCore" )
    { TGE_ANSI_CHARSET,         "ANSI" },
    { TGE_SYMBOL_CHARSET,       "SYMBOL" },
    { TGE_SHIFTJIS_CHARSET,     "SHIFTJIS" },
    { TGE_HANGEUL_CHARSET,      "HANGEUL" },
    { TGE_HANGUL_CHARSET,       "HANGUL" },
    { TGE_GB2312_CHARSET,       "GB2312" },
    { TGE_CHINESEBIG5_CHARSET,  "CHINESEBIG5" },
    { TGE_OEM_CHARSET,          "OEM" },
    { TGE_JOHAB_CHARSET,        "JOHAB" },
    { TGE_HEBREW_CHARSET,       "HEBREW" },
    { TGE_ARABIC_CHARSET,       "ARABIC" },
    { TGE_GREEK_CHARSET,        "GREEK" },
    { TGE_TURKISH_CHARSET,      "TURKISH" },
    { TGE_VIETNAMESE_CHARSET,   "VIETNAMESE" },
    { TGE_THAI_CHARSET,         "THAI" },
    { TGE_EASTEUROPE_CHARSET,   "EASTEUROPE" },
    { TGE_RUSSIAN_CHARSET,      "RUSSIAN" },
    { TGE_MAC_CHARSET,          "MAC" },
    { TGE_BALTIC_CHARSET,       "BALTIC" },
EndImplementEnumType;


StringTableEntry GuiControlProfile::sFontCacheDirectory = "";

void GuiControlProfile::setBitmapHandle(GFXTexHandle handle)
{
   mBitmap = handle;

   _setBitmap(StringTable->insert("texhandle"));
}

bool GuiControlProfile::protectedSetBitmap( void *object, const char *index, const char *data )
{
   GuiControlProfile *profile = static_cast<GuiControlProfile*>( object );
   
   profile->_setBitmap(StringTable->insert(data));

   if ( !profile->isProperlyAdded() )
      return true;
      
   if( profile->mLoadCount > 0 )
   {
      profile->mBitmapArrayRects.clear();
      profile->mBitmap = nullptr;

      if (profile->getBitmap() != StringTable->EmptyString())
      {
         if (profile->mBitmapAsset.notNull() && profile->getBitmap() != StringTable->insert("texHandle"))
         {
            profile->mBitmap.set(profile->mBitmapAsset->getImagePath(), profile->mBitmapProfile, avar("%s() - mTextureObject (line %d)", __FUNCTION__, __LINE__));
         }

         //verify the bitmap
         if (!profile->mBitmap)
            Con::errorf("(%s) - Failed to load profile bitmap (%s)", profile->getName(), profile->getBitmap());

         // If we've got a special border, make sure it's usable.
         //if( profile->mBorder == -1 || profile->mBorder == -2 )
         profile->constructBitmapArray();
      }
   }

   return false;
}

GuiControlProfile::GuiControlProfile(void) :
   mFillColor(255,0,255,255),
   mFillColorHL(255,0,255,255),
   mFillColorNA(255,0,255,255),
   mFillColorERR(255,0,0,255),
   mFillColorSEL(255,0,255,255),
   mBorderColor(255,0,255,255),
   mBorderColorHL(255,0,255,255),
   mBorderColorNA(255,0,255,255),
   mBevelColorHL(255,0,255,255),
   mBevelColorLL(255,0,255,255),
   // initialize these references to locations in the font colors array
   // the array is initialized below.
   mFontColor(mFontColors[BaseColor]),
   mFontColorHL(mFontColors[ColorHL]),
   mFontColorNA(mFontColors[ColorNA]),
   mFontColorSEL(mFontColors[ColorSEL]),
   mCursorColor(255,0,255,255),
   mTextOffset(0,0),
   mBitmapArrayRects(0)
{
   INIT_ASSET(SoundButtonDown);
   INIT_ASSET(SoundButtonOver);
   mLoadCount = 0;
   mUseCount = 0;
   
   // event focus behavior
   mTabable = false;
   mCanKeyFocus = false;
   mModal = false;

   // fill and border   
   mOpaque = false;
   mBorder = 1;
   mBorderThickness = 1;

   // font members
   mFontType = "Arial";
   mFontSize = 10;

   for(U32 i = 0; i < 10; i++)
      mFontColors[i].set(255,0,255,255);

   mFontCharset = TGE_ANSI_CHARSET;

   // sizing and alignment
   mAlignment = LeftJustify;
   mAutoSizeWidth = false;
   mAutoSizeHeight= false;
   mReturnTab     = false;
   mNumbersOnly   = false;
   mMouseOverSelected = false;
   
   // bitmap members
   INIT_ASSET(Bitmap);
   mUseBitmapArray = false;

   mChildrenProfileName = NULL;
   mChildrenProfile = NULL;

   // inherit/copy values from GuiDefaultProfile
   GuiControlProfile *def = dynamic_cast<GuiControlProfile*>(Sim::findObject("GuiDefaultProfile"));
   if (def)
   {
      mTabable       = def->mTabable;
      mCanKeyFocus   = def->mCanKeyFocus;

      mOpaque        = def->mOpaque;
      mFillColor     = def->mFillColor;
      mFillColorHL   = def->mFillColorHL;
      mFillColorNA   = def->mFillColorNA;
      mFillColorERR  = def->mFillColorERR;
      mFillColorSEL  = def->mFillColorSEL;

      mBorder        = def->mBorder;
      mBorderThickness = def->mBorderThickness;
      mBorderColor   = def->mBorderColor;
      mBorderColorHL = def->mBorderColorHL;
      mBorderColorNA = def->mBorderColorNA;

      mBevelColorHL = def->mBevelColorHL;
      mBevelColorLL = def->mBevelColorLL;

      // default font
      mFontType      = def->mFontType;
      mFontSize      = def->mFontSize;
      mFontCharset   = def->mFontCharset;

      for(U32 i = 0; i < 10; i++)
         mFontColors[i] = def->mFontColors[i];
		
      // default bitmap
      mBitmapName     = def->mBitmapName;
      mUseBitmapArray = def->mUseBitmapArray;
      mTextOffset     = def->mTextOffset;

      // default sound
      _setSoundButtonDown(def->getSoundButtonDown());
      if (getSoundButtonDown() != StringTable->EmptyString())
      {
         if (!getSoundButtonDownProfile())
            Con::errorf(ConsoleLogEntry::General, "GuiControlProfile: Can't get default button pressed sound asset.");
      }

      _setSoundButtonOver(def->getSoundButtonOver());
      if (getSoundButtonOver() != StringTable->EmptyString())
      {
         if (!getSoundButtonOverProfile())
            Con::errorf(ConsoleLogEntry::General, "GuiControlProfile: Can't get default button hover sound asset.");
      }

      //used by GuiTextCtrl
      mModal         = def->mModal;
      mAlignment     = def->mAlignment;
      mAutoSizeWidth = def->mAutoSizeWidth;
      mAutoSizeHeight= def->mAutoSizeHeight;
      mReturnTab     = def->mReturnTab;
      mNumbersOnly   = def->mNumbersOnly;
      mCursorColor   = def->mCursorColor;
      mChildrenProfileName = def->mChildrenProfileName;
      setChildrenProfile(def->mChildrenProfile);
   }
}

GuiControlProfile::~GuiControlProfile()
{
}


void GuiControlProfile::initPersistFields()
{
   docsURL;
   addGroup( "Behavior" );
   
      addField( "tab",           TypeBool,       Offset(mTabable, GuiControlProfile));
      addField("canKeyFocus",   TypeBool,       Offset(mCanKeyFocus, GuiControlProfile),
         "Whether the control can have the keyboard focus." );
      addField("mouseOverSelected", TypeBool,   Offset(mMouseOverSelected, GuiControlProfile));
      addField("modal",         TypeBool,       Offset(mModal, GuiControlProfile));
   
   endGroup( "Behavior" );
   
   addGroup( "Appearance" );
   
      addField("opaque",        TypeBool,       Offset(mOpaque, GuiControlProfile));
      addField("fillColor",     TypeColorI,     Offset(mFillColor, GuiControlProfile));
      addField("fillColorHL",   TypeColorI,     Offset(mFillColorHL, GuiControlProfile));
      addField("fillColorNA",   TypeColorI,     Offset(mFillColorNA, GuiControlProfile));
      addField("fillColorERR",  TypeColorI,     Offset(mFillColorERR, GuiControlProfile));
      addField("fillColorSEL",  TypeColorI,     Offset(mFillColorSEL, GuiControlProfile));
      addField("border",        TypeS32,        Offset(mBorder, GuiControlProfile),
         "Border type (0=no border)." );
      addField("borderThickness",TypeS32,       Offset(mBorderThickness, GuiControlProfile),
         "Thickness of border in pixels." );
      addField("borderColor",   TypeColorI,     Offset(mBorderColor, GuiControlProfile),
         "Color to draw border with." );
      addField("borderColorHL", TypeColorI,     Offset(mBorderColorHL, GuiControlProfile));
      addField("borderColorNA", TypeColorI,     Offset(mBorderColorNA, GuiControlProfile));

      addField("bevelColorHL", TypeColorI,     Offset(mBevelColorHL, GuiControlProfile));
      addField("bevelColorLL", TypeColorI,     Offset(mBevelColorLL, GuiControlProfile));
   
   endGroup( "Appearance" );
   
   addGroup( "Text" );

      addField("fontType",             TypeString,     Offset(mFontType, GuiControlProfile),
         "Name of font family and typeface (e.g. \"Arial Bold\")." );
      addField("fontSize",             TypeS32,        Offset(mFontSize, GuiControlProfile),
         "Font size in points." );
      addField("fontCharset",          TYPEID< FontCharset >(),       Offset(mFontCharset, GuiControlProfile) );
      addField("fontColors",           TypeColorI,     Offset(mFontColors, GuiControlProfile), 10,
         "Font colors to use for different text types/states." );
      addField("fontColor",            TypeColorI,     Offset(mFontColors[BaseColor], GuiControlProfile),
         "Font color for normal text (same as fontColors[0])." );
      addField("fontColorHL",          TypeColorI,     Offset(mFontColors[ColorHL], GuiControlProfile),
         "Font color for highlighted text (same as fontColors[1])." );
      addField("fontColorNA",          TypeColorI,     Offset(mFontColors[ColorNA], GuiControlProfile),
         "Font color when control is not active/disabled (same as fontColors[2])." );
      addField("fontColorSEL",         TypeColorI,     Offset(mFontColors[ColorSEL], GuiControlProfile),
         "Font color for selected text (same as fontColors[3])." );
      addField("fontColorLink",        TypeColorI,     Offset(mFontColors[ColorUser0], GuiControlProfile),
         "Font color for links in text (same as fontColors[4])." );
      addField("fontColorLinkHL",      TypeColorI,     Offset(mFontColors[ColorUser1], GuiControlProfile),
         "Font color for highlighted links in text (same as fontColors[5])." );
            
      addField( "justify",       TYPEID< GuiControlProfile::AlignmentType >(),       Offset(mAlignment, GuiControlProfile),
         "Horizontal alignment for text." );
      addField( "textOffset",    TypePoint2I,    Offset(mTextOffset, GuiControlProfile));
      addField( "autoSizeWidth", TypeBool,       Offset(mAutoSizeWidth, GuiControlProfile),
         "Automatically adjust width of control to fit contents." );
      addField("autoSizeHeight",TypeBool,       Offset(mAutoSizeHeight, GuiControlProfile),
         "Automatically adjust height of control to fit contents." );
      addField("returnTab",     TypeBool,       Offset(mReturnTab, GuiControlProfile),
         "Whether to add automatic tab event when return is pressed so focus moves on to next control (GuiTextEditCtrl)." );
      addField("numbersOnly",   TypeBool,       Offset(mNumbersOnly, GuiControlProfile),
         "Whether control should only accept numerical data (GuiTextEditCtrl)." );
      addField("cursorColor",   TypeColorI,     Offset(mCursorColor, GuiControlProfile),
         "Color to use for the text cursor." );

   endGroup( "Text" );
   
   addGroup( "Misc" );
#ifdef TORQUE_SHOW_LEGACY_FILE_FIELDS
   addProtectedField("bitmap", TypeImageFilename, Offset(mBitmapName, GuiControlProfile),
      &GuiControlProfile::protectedSetBitmap, &defaultProtectedGetFn,
      "Texture to use for rendering control.");
#else
   addProtectedField("bitmap", TypeImageFilename, Offset(mBitmapName, GuiControlProfile),
      &GuiControlProfile::protectedSetBitmap, &defaultProtectedGetFn,
      "Texture to use for rendering control.", AbstractClassRep::FIELD_HideInInspectors);
#endif

      addProtectedField("bitmapAsset", TypeImageAssetId, Offset(mBitmapAssetId, GuiControlProfile),
         &GuiControlProfile::protectedSetBitmap, &defaultProtectedGetFn,
         "Texture to use for rendering control.");

      addField("hasBitmapArray", TypeBool,      Offset(mUseBitmapArray, GuiControlProfile),
         "If true, 'bitmap' is an array of images." );

      INITPERSISTFIELD_SOUNDASSET(SoundButtonDown, GuiControlProfile, "The sound button down.");
      INITPERSISTFIELD_SOUNDASSET(SoundButtonOver, GuiControlProfile, "The sound button down.");

      addField("profileForChildren", TypeString,      Offset(mChildrenProfileName, GuiControlProfile));
   
   endGroup( "Misc" );
   
   addField( "category", TypeRealString, Offset( mCategory, GuiControlProfile ),
      "Category under which the profile will appear in the editor."
   );

   Parent::initPersistFields();
}

bool GuiControlProfile::onAdd()
{
   if(!Parent::onAdd())
      return false;

   Sim::getGuiDataGroup()->addObject(this);
   
   // Make sure we have an up-to-date children profile
   getChildrenProfile();

   return true;
}

void GuiControlProfile::onStaticModified(const char* slotName, const char* newValue)
{
   if( mLoadCount > 0 )
   {
      if ( !dStricmp(slotName, "fontType") || 
           !dStricmp(slotName, "fontCharset") ||
           !dStricmp(slotName, "fontSize" ) )
      {
         // Reload the font
         mFont = GFont::create(mFontType, mFontSize, sFontCacheDirectory, mFontCharset);
         if ( mFont == NULL )
            Con::errorf("Failed to load/create profile font (%s/%d)", mFontType, mFontSize);
      }
   }
}

void GuiControlProfile::onDeleteNotify(SimObject *object)
{
   if (object == mChildrenProfile)
      mChildrenProfile = NULL;
}

GuiControlProfile* GuiControlProfile::getChildrenProfile()
{
   // We can early out if we still have a valid profile
   if (mChildrenProfile)
      return mChildrenProfile;

   // Attempt to find the profile specified
   if (mChildrenProfileName)
   {
      GuiControlProfile *profile = dynamic_cast<GuiControlProfile*>(Sim::findObject( mChildrenProfileName ));

      if( profile )
         setChildrenProfile(profile);
   }

   return mChildrenProfile;
}

void GuiControlProfile::setChildrenProfile(GuiControlProfile *prof)
{
   if(prof == mChildrenProfile)
      return;

   // Clear the delete notification we previously set up
   if (mChildrenProfile)
      clearNotify(mChildrenProfile);

   mChildrenProfile = prof;

   // Make sure that the new profile will notify us when it is deleted
   if (mChildrenProfile)
      deleteNotify(mChildrenProfile);
}

RectI GuiControlProfile::getBitmapArrayRect(U32 i)
{
   if(!mBitmapArrayRects.size())
      constructBitmapArray();
   
   if( i >= mBitmapArrayRects.size())
      return RectI(0,0,0,0);

   return mBitmapArrayRects[i];
}

S32 GuiControlProfile::constructBitmapArray()
{
   if(mBitmapArrayRects.size())
      return mBitmapArrayRects.size();

   if( mBitmap.isNull() )
   {
      if (!_setBitmap(getBitmap()))
         return 0;

      if (getBitmap() != StringTable->EmptyString() && mBitmapName != StringTable->insert("texhandle"))
      {
         mBitmap.set(getBitmap(), mBitmapProfile, avar("%s() - mTextureObject (line %d)", __FUNCTION__, __LINE__));
      }

      if (getBitmap() == StringTable->EmptyString() || mBitmap.isNull())
         return 0;
   }

   GBitmap *bmp = mBitmap->getBitmap();

   //get the separator color
   ColorI sepColor;
   if ( !bmp || !bmp->getColor( 0, 0, sepColor ) )
	{
      Con::errorf("Failed to create bitmap array from %s for profile %s - couldn't ascertain seperator color!", getBitmap(), getName());
      AssertFatal( false, avar("Failed to create bitmap array from %s for profile %s - couldn't ascertain seperator color!", getBitmap(), getName()));
      return 0;
	}

   //now loop through all the scroll pieces, and find the bounding rectangle for each piece in each state
   S32 curY = 0;

   // ascertain the height of this row...
   ColorI color;
   mBitmapArrayRects.clear();
   while(curY < bmp->getHeight())
   {
      // skip any sep colors
      bmp->getColor( 0, curY, color);
      if(color == sepColor)
      {
         curY++;
         continue;
      }
      // ok, process left to right, grabbing bitmaps as we go...
      S32 curX = 0;
      while(curX < bmp->getWidth())
      {
         bmp->getColor(curX, curY, color);
         if(color == sepColor)
         {
            curX++;
            continue;
         }
         S32 startX = curX;
         while(curX < bmp->getWidth())
         {
            bmp->getColor(curX, curY, color);
            if(color == sepColor)
               break;
            curX++;
         }
         S32 stepY = curY;
         while(stepY < bmp->getHeight())
         {
            bmp->getColor(startX, stepY, color);
            if(color == sepColor)
               break;
            stepY++;
         }
         mBitmapArrayRects.push_back(RectI(startX, curY, curX - startX, stepY - curY));
      }
      // ok, now skip to the next separation color on column 0
      while(curY < bmp->getHeight())
      {
         bmp->getColor(0, curY, color);
         if(color == sepColor)
            break;
         curY++;
      }
   }
   return mBitmapArrayRects.size();
}

void GuiControlProfile::incLoadCount()
{
   if( !mLoadCount )
   {
      #ifdef DEBUG_SPEW
      Platform::outputDebugString( "[GuiControlProfile] Loading profile %i:%s (%s:%s)",
         getId(), getClassName(), getName(), getInternalName() );
      #endif
      
      sFontCacheDirectory = Con::getVariable( "$GUI::fontCacheDirectory" );
         
      // Load font (if not already loaded).
      
      if( mFont == NULL )
         loadFont();

      //
      if (getBitmap() != StringTable->EmptyString())
      {
         if (mBitmapAsset.notNull() && getBitmap() != StringTable->insert("texHandle"))
         {
            mBitmap.set(mBitmapAsset->getImagePath(), mBitmapProfile, avar("%s() - mTextureObject (line %d)", __FUNCTION__, __LINE__));
         }

         //verify the bitmap
         if (!mBitmap)
            Con::errorf("(%s) - Failed to load profile bitmap (%s)", getName(), getBitmap());

         constructBitmapArray();
      }
   }
   
   mLoadCount ++;

   // Quick check to make sure our children profile is up-to-date
   getChildrenProfile();
}

void GuiControlProfile::decLoadCount()
{
   AssertFatal( mLoadCount, "GuiControlProfile::decLoadCount - zero load count" );
   if(!mLoadCount)
      return;

   -- mLoadCount;
   if( !mLoadCount )
   {
      #ifdef DEBUG_SPEW
      Platform::outputDebugString( "[GuiControlProfile] Unloading profile %i:%s (%s:%s)",
         getId(), getClassName(), getName(), getInternalName() );
      #endif

      StringTableEntry bitmapName = getBitmap();
      if(bitmapName == StringTable->EmptyString() || bitmapName == StringTable->insert("texhandle"))
         mBitmap = NULL;
   }
}

bool GuiControlProfile::loadFont()
{
   mFont = GFont::create( mFontType, mFontSize, sFontCacheDirectory, mFontCharset );
   if( mFont == NULL )
   {
      Con::errorf( "GuiControlProfile::loadFont - Failed to load/create profile font (%s/%d)", mFontType, mFontSize );
      return false;
   }
      
   return true;
}

DefineEngineMethod( GuiControlProfile, getStringWidth, S32, (const char* string),,
   "Get the width of the string in pixels.\n"
   "@param string String to get the width of."
   "@return width of the string in pixels." )
{
   return (object->mFont) ? object->mFont->getStrNWidth( string, dStrlen( string ) ) : -1;
}

DefineEngineMethod(GuiControlProfile, getBitmap, const char*, (), , "get name")
{
   return object->getBitmap(); 
}
DefineEngineMethod(GuiControlProfile, getBitmapAsset, const char*, (), , "")
{
   return object->mBitmapAssetId; 
}
DefineEngineMethod(GuiControlProfile, setBitmap, bool, (const char* map), , "")
{
    return object->_setBitmap(StringTable->insert(map));
}

//-----------------------------------------------------------------------------
// TypeRectSpacingI
//-----------------------------------------------------------------------------
IMPLEMENT_STRUCT( RectSpacingI,
   RectSpacingI, GuiAPI,
   "" )
   
      FIELD( left, leftPadding, 1, "" )
      FIELD( right, rightPadding, 1, "" )
      FIELD( top, topPadding, 1, "" )
      FIELD( bottom, bottomPadding, 1, "" )
      
END_IMPLEMENT_STRUCT;

ConsoleType(RectSpacingI, TypeRectSpacingI, RectSpacingI, "")
ImplementConsoleTypeCasters( TypeRectSpacingI, RectSpacingI )

ConsoleGetType( TypeRectSpacingI )
{
   RectSpacingI *rect = (RectSpacingI *) dptr;
   static const U32 bufSize = 256;
   char* returnBuffer = Con::getReturnBuffer(bufSize);
   dSprintf(returnBuffer, bufSize, "%d %d %d %d", rect->top, rect->bottom,
      rect->left, rect->right);
   return returnBuffer;
}

ConsoleSetType( TypeRectSpacingI )
{
   if(argc == 1)
      dSscanf(argv[0], "%d %d %d %d", &((RectSpacingI *) dptr)->top, &((RectSpacingI *) dptr)->bottom,
      &((RectSpacingI *) dptr)->left, &((RectSpacingI *) dptr)->right);
   else if(argc == 4)
      *((RectSpacingI *) dptr) = RectSpacingI(dAtoi(argv[0]), dAtoi(argv[1]), dAtoi(argv[2]), dAtoi(argv[3]));
   else
      Con::printf("RectSpacingI must be set as { t, b, l, r } or \"t b l r\"");
}
