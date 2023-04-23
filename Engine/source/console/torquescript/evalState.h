#ifndef _EVALSTATE_H
#define _EVALSTATE_H
#include "console/consoleInternal.h"

class ExprEvalState
{
public:
   /// @name Expression Evaluation
   /// @{

   ///

   Dictionary::Entry *currentVariable;
   Dictionary::Entry *copyVariable;

   U32 mStackDepth;
   bool mShouldReset; ///< Designates if the value stack should be reset
   bool mResetLocked; ///< mShouldReset will be set at the end

   ExprEvalState();
   ~ExprEvalState();

   /// @}

   /// @name Stack Management
   /// @{

   /// The stack of callframes.  The extra redirection is necessary since Dictionary holds
   /// an interior pointer that will become invalid when the object changes address.
   Vector< Dictionary* > stack;

   S32 getTopOfStack() { return (S32)mStackDepth; }

   Vector< ConsoleValueFrame > localStack;
   ConsoleValueFrame* currentRegisterArray; // contains array at to top of localStack

   ///

   void setCurVarName(StringTableEntry name);
   void setCurVarNameCreate(StringTableEntry name);

   S32 getIntVariable();
   F64 getFloatVariable();
   const char *getStringVariable();
   void setIntVariable(S32 val);
   void setFloatVariable(F64 val);
   void setStringVariable(const char *str);

   TORQUE_FORCEINLINE S32 getLocalIntVariable(S32 reg)
   {
      return currentRegisterArray->values[reg].getInt();
   }

   TORQUE_FORCEINLINE F64 getLocalFloatVariable(S32 reg)
   {
      return currentRegisterArray->values[reg].getFloat();
   }

   TORQUE_FORCEINLINE const char* getLocalStringVariable(S32 reg)
   {
      return currentRegisterArray->values[reg].getString();
   }

   TORQUE_FORCEINLINE void setLocalIntVariable(S32 reg, S64 val)
   {
      currentRegisterArray->values[reg].setInt(val);
   }

   TORQUE_FORCEINLINE void setLocalFloatVariable(S32 reg, F64 val)
   {
      currentRegisterArray->values[reg].setFloat(val);
   }

   TORQUE_FORCEINLINE void setLocalStringVariable(S32 reg, const char* val, S32 len)
   {
      currentRegisterArray->values[reg].setString(val, len);
   }

   TORQUE_FORCEINLINE void setLocalStringTableEntryVariable(S32 reg, StringTableEntry val)
   {
      currentRegisterArray->values[reg].setStringTableEntry(val);
   }

   TORQUE_FORCEINLINE void moveConsoleValue(S32 reg, ConsoleValue val)
   {
      currentRegisterArray->values[reg] = std::move(val);
   }

   void pushFrame(StringTableEntry frameName, Namespace *ns, S32 regCount);
   void popFrame();

   /// Puts a reference to an existing stack frame
   /// on the top of the stack.
   void pushFrameRef(S32 stackIndex);

   void pushDebugFrame(S32 stackIndex);

   U32 getStackDepth() const
   {
      return mStackDepth;
   }

   Dictionary& getCurrentFrame()
   {
      return *(stack[mStackDepth - 1]);
   }

   Dictionary& getFrameAt(S32 depth)
   {
      return *(stack[depth]);
   }

   /// @}

   /// Run integrity checks for debugging.
   void validate();
};

#endif
