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

#ifdef TORQUE_TESTS_ENABLED
#include "testing/unitTesting.h"
#include "platform/platform.h"
#include "console/simBase.h"
#include "console/consoleTypes.h"
#include "console/simBase.h"
#include "console/engineAPI.h"
#include "math/mMath.h"
#include "console/stringStack.h"

template<typename T>
inline T Convert(ConsoleValueRef);

template<>
inline U32 Convert(ConsoleValueRef val)
{
   return val.getIntValue();
}

template<>
inline S32 Convert(ConsoleValueRef val)
{
   return val.getSignedIntValue();
}

template<>
inline bool Convert(ConsoleValueRef val)
{
   return val.getBoolValue();
}

template<>
inline F32 Convert(ConsoleValueRef val)
{
   return val.getFloatValue();
}

template<>
inline const char* Convert(ConsoleValueRef val)
{
   return val.getStringValue();
}

template<>
inline SimObject* Convert(ConsoleValueRef val)
{
   return Sim::findObject(val);
}

template<typename T>
inline T RunScript(const char* str)
{
   return Convert<T>(Con::evaluate(str, false, NULL));
}

TEST(Script, Basic_Arithmetic)
{
   S32 add = RunScript<S32>(R"(
         return 1.0 + 1;
   )");

   EXPECT_EQ(add, 2);

   S32 sub = RunScript<S32>(R"(
         return 10 - 1.0;
   )");

   EXPECT_EQ(sub, 9);

   S32 mult = RunScript<S32>(R"(
         return 10 * 2.5;
   )");

   EXPECT_EQ(mult, 25);

   S32 div = RunScript<S32>(R"(
         return 10.0 / 2;
   )");

   EXPECT_EQ(div, 5);
}

TEST(Script, Complex_Arithmetic)
{
   S32 result = RunScript<S32>(R"(
         return 1 * 2 - (0.5 * 2);
   )");

   EXPECT_EQ(result, 1);

   S32 result2 = RunScript<S32>(R"(
         return 1 * 2 * 3 % 2;
   )");

   EXPECT_EQ(result2, 0);
}

TEST(Script, Basic_Concatination)
{
   const char* result1 = RunScript<const char*>(R"(
         return "a" @ "b";
   )");

   EXPECT_STREQ(result1, "ab");

   const char* result2 = RunScript<const char*>(R"(
         return "a" SPC "b";
   )");

   EXPECT_STREQ(result2, "a b");

   const char* result3 = RunScript<const char*>(R"(
         return "a" TAB "b";
   )");

   EXPECT_STREQ(result3, "a\tb");

   const char* result4 = RunScript<const char*>(R"(
         return "a" NL "b";
   )");

   EXPECT_STREQ(result4, "a\nb");

   const char* complex = RunScript<const char*>(R"(
         return "a" @ "b" @ "c" @ "d";
   )");

   EXPECT_STREQ(complex, "abcd");
}

TEST(Script, Basic_Global_Variable_Tests)
{
   S32 value = RunScript<S32>(R"(
         $a = 1;
         return $a;
   )");

   EXPECT_EQ(value, 1);
}

TEST(Script, Variable_Chaining_And_Usage)
{
   S32 value = RunScript<S32>(R"(
         function t() 
         {
            %a = %b = 2;
            return %a;
         }
         return t();
   )");

   EXPECT_EQ(value, 2);

   S32 valueGlobal = RunScript<S32>(R"(
         function t() 
         {
            $a = %b = 2;
         }
         t();
         return $a;
   )");

   EXPECT_EQ(valueGlobal, 2);

   S32 value2 = RunScript<S32>(R"(
         function t(%a) 
         {
            if ((%b = 2 * %a) != 5)
               return %b;
            return 5;
         }

         return t(2);
   )");

   EXPECT_EQ(value2, 4);
}

TEST(Script, Basic_Function_Call_And_Local_Variable_Testing)
{
   S32 value = RunScript<S32>(R"(
         function t() { %a = 2; return %a; }
         return t();
   )");

   EXPECT_EQ(value, 2);

   S32 value2 = RunScript<S32>(R"(
         function add(%a, %b) { return %a + %b; }
         return add(2, 4);
   )");

   EXPECT_EQ(value2, 6);

   S32 value3 = RunScript<S32>(R"(
         function fib(%a) {
            if (%a == 0)
               return 0;
            if (%a == 1)
               return 1;
            return fib(%a - 1) + fib(%a - 2);
         }
         return fib(15);
   )");

   EXPECT_EQ(value3, 610);

   S32 staticCall = RunScript<S32>(R"(
         function SimObject::bar(%a, %b) {
            return %a + %b;
         }
         return SimObject::bar(1, 2);
   )");

   EXPECT_EQ(staticCall, 3);
}

TEST(Script, Basic_Conditional_Statements)
{
   S32 value = RunScript<S32>(R"(
         $a = "hello";
         if ($a $= "hello")
            return 1;
         return 2;
   )");

   EXPECT_EQ(value, 1);

   const char* ternaryValue = RunScript<const char*>(R"(
         return $a $= "hello" ? "World" : "No U";
   )");

   EXPECT_STREQ(ternaryValue, "World");
}

TEST(Script, Basic_Loop_Statements)
{
   S32 whileValue = RunScript<S32>(R"(
         $count = 0;
         while ($count < 5)
            $count++;
         return $count;
   )");

   EXPECT_EQ(whileValue, 5);

   const char* forValue = RunScript<const char*>(R"(
         function t(%times) 
         { 
            %result = "";
            for (%i = 0; %i < %times; %i++)
               %result = %result @ "a";
            return %result;
         }

         return t(3);
   )");

   EXPECT_STREQ(forValue, "aaa");

   const char* forIfValue = RunScript<const char*>(R"(
         function t() {
            %str = "";
            for (%i = 0; %i < 5; %i++) {

               %loopValue = %i;

               if (%str $= "") 
                  %str = %loopValue;
               else 
                  %str = %str @ "," SPC %loopValue;
            }
            return %str;
         }

         return t();
   )");

   EXPECT_STREQ(forIfValue, "0, 1, 2, 3, 4");
}

TEST(Script, TorqueScript_Array_Testing)
{
   S32 value = RunScript<S32>(R"(
         function t(%idx) { %a[idx] = 2; return %a[idx]; }
         return t(5);
   )");

   EXPECT_EQ(value, 2);

   S32 value2 = RunScript<S32>(R"(
         function t(%idx) { %a[idx, 0] = 2; return %a[idx, 0]; }
         return t(5);
   )");

   EXPECT_EQ(value2, 2);
}

TEST(Script, Basic_SimObject)
{
   SimObject* object = RunScript<SimObject*>(R"(
         return new SimObject(FudgeCollector) {
            fudge = "Chocolate"; 
         };
   )");

   EXPECT_NE(object, (SimObject*)NULL);

   const char* propertyValue = RunScript<const char*>(R"(
         return FudgeCollector.fudge;
   )");

   EXPECT_STREQ(propertyValue, "Chocolate");

   const char* funcReturn = RunScript<const char*>(R"(
         function SimObject::fooFunc(%this)
         {
            return "Bar";
         }

         return FudgeCollector.fooFunc();
   )");

   EXPECT_STREQ(funcReturn, "Bar");

   const char* parentFn = RunScript<const char*>(R"(
         new SimObject(Hello);

         function SimObject::fooFunc2(%this)
         {
            return "Bar";
         }

         function Hello::fooFunc2(%this)
         {
            %bar = Parent::fooFunc2(%this);
            return "Foo" @ %bar;
         }

         return Hello.fooFunc2();
   )");

   EXPECT_STREQ(parentFn, "FooBar");
}

TEST(Script, Basic_Package)
{
   S32 value = RunScript<S32>(R"(
         function a() { return 3; }
         package overrides {
            function a() { return 5; }
         };
         return a();
   )");

   EXPECT_EQ(value, 3);

   S32 overrideValue = RunScript<S32>(R"(
         activatePackage(overrides);
         return a();
   )");

   EXPECT_EQ(overrideValue, 5);

   S32 deactivatedValue = RunScript<S32>(R"(
         deactivatePackage(overrides);
         return a();
   )");

   EXPECT_EQ(deactivatedValue, 3);
}

#endif
