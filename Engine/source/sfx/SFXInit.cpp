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
#include "sfx/SFXInit.h"

#include "console/console.h"
#include "core/module.h"

Vector<SFXProvider*> SFXInit::smProviders(__FILE__, __LINE__);
SFXInit::RegisterProviderSignal* SFXInit::smRegisterProviderSignal;

MODULE_BEGIN(SFXNEW)

   MODULE_INIT_BEFORE(Sim)
   MODULE_SHUTDOWN_BEFORE(Sim)

   MODULE_INIT
   {
      SFXInit::init();
      if (engineAPI::gUseConsoleInterop)
         SFXDevice::initConsole();
}

   MODULE_SHUTDOWN
   {
      SFXDevice::destroy();
      SFXInit::cleanup();
   }

MODULE_END;

IMPLEMENT_STATIC_CLASS(SFXInit, SFXAPI,
   "Functions for tracking SFX providers and adapters and initializing them into devices."
);

ConsoleDoc(
   "@class SFXInit\n"
   "@ingroup SFX\n"
   "@brief Functions for tracking SFX providers and adapters and initializing them into devices.\n"
);

inline static void _SFXInitReportProviders(Vector<SFXProvider*>& providers)
{
   for (SFXProvider* provider : providers)
   {
      switch (provider->mType)
      {
      case SFXProviderType::OpenAL:
         Con::printf("   OpenAL Provider found");
         break;
      case SFXProviderType::NullProvider:
         Con::printf("   NULL Provider found");
         break;
      case SFXProviderType::XAudio:
         Con::printf("   XAudio Provider found");
         break;
      case SFXProviderType::DirectSound:
         Con::printf("   DirectSound Provider found");
         break;
      default:
         Con::printf("   Unknown Provider found");
         break;
      }
   }
}

SFXInit::RegisterProviderSignal& SFXInit::getRegisterProviderSignal()
{
   if (smRegisterProviderSignal)
      return *smRegisterProviderSignal;

   smRegisterProviderSignal = new RegisterProviderSignal();
   return *smRegisterProviderSignal;
}

void SFXInit::init()
{
   // init only once.
   static bool doneOnce = false;
   if (doneOnce)
      return;
   doneOnce = true;

   Con::printf("SFX Init:");
   SFXInit::enumerateProviders();

   if (!smProviders.size())
      Con::errorf("Could not find audio provider");

   _SFXInitReportProviders(smProviders);

   Con::printf("");
}

void SFXInit::cleanup()
{
   while (smProviders.size())
   {
      SFXProvider* prov = smProviders.last();
      smProviders.decrement();
      delete prov;
   }

   if (smRegisterProviderSignal)
      SAFE_DELETE(smRegisterProviderSignal);
}

void SFXInit::enumerateProviders()
{
   if (smProviders.size())
   {
      return;
   }

   getRegisterProviderSignal().trigger(SFXInit::smProviders);
}
