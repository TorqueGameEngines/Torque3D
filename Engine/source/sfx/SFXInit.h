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
#pragma once

#ifndef _SFXINIT_H_
#define _SFXINIT_H_

#ifndef _SFXDEVICE_H_
#include "sfx/sfxDevice.h"
#endif

#ifndef _SFXAPI_H_
#include "sfx/sfxApi.h"
#endif // !_SFXAPI_H_


#ifndef _ENGINEOBJECT_H_
#include "console/engineObject.h"
#endif

class SFXInit
{
   DECLARE_STATIC_CLASS(SFXInit)

public:
   typedef Signal<void(Vector<SFXProvider*>&)> RegisterProviderSignal;
   static RegisterProviderSignal& getRegisterProviderSignal();
   /// <summary>
   /// Initializes the SFX system this will loop through providers and create devices linked to it.
   /// </summary>
   static void init();

   /// <summary>
   /// Cleanup all our providers.
   /// </summary>
   static void cleanup();

   static void enumerateProviders();

private:
   /// List of known providers.
   static Vector<SFXProvider*> smProviders;
   static RegisterProviderSignal* smRegisterProviderSignal;


};

#endif // !_SFXINIT_H_
