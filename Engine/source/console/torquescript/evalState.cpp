
#include "evalState.h"

void ExprEvalState::pushFrame(StringTableEntry frameName, Namespace *ns, S32 registerCount)
{
#ifdef DEBUG_SPEW
   validate();

   Platform::outputDebugString("[ConsoleInternal] Pushing new frame for '%s' at %i",
      frameName, mStackDepth);
#endif

   if (mStackDepth + 1 > stack.size())
   {
#ifdef DEBUG_SPEW
      Platform::outputDebugString("[ConsoleInternal] Growing stack by one frame");
#endif

      stack.push_back(new Dictionary);
   }

   Dictionary& newFrame = *(stack[mStackDepth]);
   newFrame.setState();

   newFrame.scopeName = frameName;
   newFrame.scopeNamespace = ns;

   Con::pushStackFrame(stack[mStackDepth]);
   mStackDepth++;
   currentVariable = NULL;

   AssertFatal(!newFrame.getCount(), "ExprEvalState::pushFrame - Dictionary not empty!");

   ConsoleValue* consoleValArray = new ConsoleValue[registerCount]();
   localStack.push_back(ConsoleValueFrame(consoleValArray, false));
   currentRegisterArray = &localStack.last();

   AssertFatal(mStackDepth == localStack.size(), avar("Stack sizes do not match. mStackDepth = %d, localStack = %d", mStackDepth, localStack.size()));

#ifdef DEBUG_SPEW
   validate();
#endif
}

void ExprEvalState::popFrame()
{
   AssertFatal(mStackDepth > 0, "ExprEvalState::popFrame - Stack Underflow!");

#ifdef DEBUG_SPEW
   validate();

   Platform::outputDebugString("[ConsoleInternal] Popping %sframe at %i",
      getCurrentFrame().isOwner() ? "" : "shared ", mStackDepth - 1);
#endif

   Con::popStackFrame();
   mStackDepth--;
   stack[mStackDepth]->reset();
   currentVariable = NULL;

   const ConsoleValueFrame& frame = localStack.last();
   localStack.pop_back();
   if (!frame.isReference)
      delete[] frame.values;

   currentRegisterArray = localStack.size() ? &localStack.last() : NULL;

   AssertFatal(mStackDepth == localStack.size(), avar("Stack sizes do not match. mStackDepth = %d, localStack = %d", mStackDepth, localStack.size()));

#ifdef DEBUG_SPEW
   validate();
#endif
}

void ExprEvalState::pushFrameRef(S32 stackIndex)
{
   AssertFatal(stackIndex >= 0 && stackIndex < mStackDepth, "You must be asking for a valid frame!");

#ifdef DEBUG_SPEW
   validate();

   Platform::outputDebugString("[ConsoleInternal] Cloning frame from %i to %i",
      stackIndex, mStackDepth);
#endif

   if (mStackDepth + 1 > stack.size())
   {
#ifdef DEBUG_SPEW
      Platform::outputDebugString("[ConsoleInternal] Growing stack by one frame");
#endif

      stack.push_back(new Dictionary);
   }

   Dictionary& newFrame = *(stack[mStackDepth]);
   newFrame.setState(stack[stackIndex]);

   Con::pushStackFrame(stack[mStackDepth]);

   mStackDepth++;
   currentVariable = NULL;

   ConsoleValue* values = localStack[stackIndex].values;
   localStack.push_back(ConsoleValueFrame(values, true));
   currentRegisterArray = &localStack.last();

   AssertFatal(mStackDepth == localStack.size(), avar("Stack sizes do not match. mStackDepth = %d, localStack = %d", mStackDepth, localStack.size()));

#ifdef DEBUG_SPEW
   validate();
#endif
}

void ExprEvalState::pushDebugFrame(S32 stackIndex)
{
   pushFrameRef(stackIndex);

   Dictionary& newFrame = *(stack[mStackDepth - 1]);

   // debugger needs to know this info...
   newFrame.scopeName = stack[stackIndex]->scopeName;
   newFrame.scopeNamespace = stack[stackIndex]->scopeNamespace;
   newFrame.module = stack[stackIndex]->module;
   newFrame.ip = stack[stackIndex]->ip;
}

ExprEvalState::ExprEvalState()
{
   VECTOR_SET_ASSOCIATION(stack);
   currentVariable = NULL;
   mStackDepth = 0;
   stack.reserve(64);
   mShouldReset = false;
   mResetLocked = false;
   copyVariable = NULL;
   currentRegisterArray = NULL;
}

ExprEvalState::~ExprEvalState()
{
   // Delete callframes.

   while (!stack.empty())
   {
      delete stack.last();
      stack.decrement();
   }
}

void ExprEvalState::validate()
{
   AssertFatal(mStackDepth <= stack.size(),
      "ExprEvalState::validate() - Stack depth pointing beyond last stack frame!");

   for (U32 i = 0; i < stack.size(); ++i)
      stack[i]->validate();
}
