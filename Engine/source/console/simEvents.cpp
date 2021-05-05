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

#include "console/console.h"
#include "console/consoleInternal.h"
#include "platform/threads/semaphore.h"
#include "console/simEvents.h"

// Stupid globals not declared in a header
extern ExprEvalState gEvalState;

SimConsoleEvent::SimConsoleEvent(S32 argc, ConsoleValue *argv, bool onObject)
{
   mOnObject = onObject;
   mArgc = argc;

   mArgv = new ConsoleValue[argc];
   for (int i=0; i<argc; i++)
   {
      if (argv)
      {
         mArgv[i].setString(argv[i].getString());
      }
   }
}

SimConsoleEvent::~SimConsoleEvent()
{
   delete[] mArgv;
}

void SimConsoleEvent::process(SimObject* object)
{
   // #ifdef DEBUG
   //    Con::printf("Executing schedule: %d", sequenceCount);
   // #endif
   if(mOnObject)
      Con::execute(object, mArgc, mArgv );
   else
   {
      // Grab the function name. If '::' doesn't exist, then the schedule is
      // on a global function.
      char funcName[256];
      dStrncpy(funcName, mArgv[0].getString(), 256);
      char* func = dStrstr( funcName, (char*)"::" );
      if( func )
      {
         // Set the first colon to NULL, so we can reference the namespace.
         // This is okay because events are deleted immediately after
         // processing. Maybe a bad idea anyway?
         func[0] = '\0';

         // Move the pointer forward to the function name.
         func += 2;

         // Lookup the namespace and function entry.
         Namespace* ns = Namespace::find( StringTable->insert( funcName ) );
         if( ns )
         {
            Namespace::Entry* nse = ns->lookup( StringTable->insert( func ) );
            if( nse )
               // Execute.
               nse->execute( mArgc, mArgv, &gEvalState );
         }
      }

      else
         Con::execute(mArgc, mArgv );
   }
}

void SimConsoleEvent::populateArgs(ConsoleValue *argv)
{
   for (U32 i=0; i<mArgc; i++)
   {
      argv[i].setString(mArgv[i].getString());
   }
}

//-----------------------------------------------------------------------------

SimConsoleThreadExecCallback::SimConsoleThreadExecCallback()
{
   sem = new Semaphore(0);
}

SimConsoleThreadExecCallback::~SimConsoleThreadExecCallback()
{
   delete sem;
}

void SimConsoleThreadExecCallback::handleCallback(ConsoleValue ret)
{
   // can we move this pls?
   retVal.setString(ret.getString());
   sem->release();
}

ConsoleValue SimConsoleThreadExecCallback::waitForResult()
{
   if(sem->acquire(true))
   {
      return std::move(retVal);
   }

   return ConsoleValue();
}

//-----------------------------------------------------------------------------

SimConsoleThreadExecEvent::SimConsoleThreadExecEvent(S32 argc, ConsoleValue *argv, bool onObject, SimConsoleThreadExecCallback *callback) :
   SimConsoleEvent(argc, argv, onObject), cb(callback)
{
}

void SimConsoleThreadExecEvent::process(SimObject* object)
{
   if (cb)
   {
      if (mOnObject)
         cb->handleCallback(std::move(Con::execute(object, mArgc, mArgv)));
      else
         cb->handleCallback(std::move(Con::execute(mArgc, mArgv)));
   }
   else
   {
      if (mOnObject)
         Con::execute(object, mArgc, mArgv);
      else
         Con::execute(mArgc, mArgv);
   }
}
