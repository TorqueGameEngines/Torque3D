//-----------------------------------------------------------------------------
// Copyright (c) 2013 GarageGames, LLC
// Copyright (c) 2021 TGEMIT Authors & Contributors
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

#ifndef _CONSOLE_CONSOLE_VALUE_STACK_H_
#define _CONSOLE_CONSOLE_VALUE_STACK_H_

template<S32 StackSize>
class ConsoleValueStack
{
   constexpr static S32 allocatorSize = sizeof(ConsoleValue) * StackSize;

   struct Frame
   {
      ConsoleValue* values;
      S32 count;
      S32 internalCounter;
   };

   Vector<Frame> stack;
   char* memory;
   S32 sp;

   TORQUE_FORCEINLINE Frame alloc(S32 count)
   {
      AssertFatal(sp + count * sizeof(ConsoleValue) < allocatorSize, "ConsoleValueStack overflow");

      ConsoleValue* ret = reinterpret_cast<ConsoleValue*>(memory + sp);
      sp += count * sizeof(ConsoleValue);

      return { ret, count, 1 };
   }

   TORQUE_FORCEINLINE void deAlloc(S32 count)
   {
      sp -= count * sizeof(ConsoleValue);
      AssertFatal(sp >= 0, "Popped ConsoleValueStack too far, underflow");
   }

public:
   ConsoleValueStack()
   {
      memory = (char*)dMalloc(allocatorSize);
      for (S32 i = 0; i < allocatorSize; i += sizeof(ConsoleValue))
      {
         constructInPlace<ConsoleValue>(reinterpret_cast<ConsoleValue*>(memory + i));
      }
      sp = 0;
   }

   ~ConsoleValueStack()
   {
      dFree(memory);
   }

   TORQUE_FORCEINLINE void pushFrame(S32 count)
   {
      AssertISV(count >= 0, "Must be >= 0 when pushing stack frame");

      // +1 for function name in argv[0]
      const Frame& frame = alloc(count + 1);
      stack.push_back(frame);
   }

   TORQUE_FORCEINLINE void popFrame()
   {
      AssertISV(stack.size() > 0, "Stack Underflow");

      deAlloc(stack.last().count);
      stack.pop_back();
   }

   TORQUE_FORCEINLINE void push(ConsoleValue&& val)
   {
      Frame& frame = stack.last();
      frame.values[frame.internalCounter++] = std::move(val);
   }

   TORQUE_FORCEINLINE void argvc(StringTableEntry fn, S32& argc, ConsoleValue** argv)
   {
      Frame& frame = stack.last();
      argc = frame.count;

      // First param is always function name
      frame.values[0].setStringTableEntry(fn);
      *argv = frame.values;
   }
};

#endif
