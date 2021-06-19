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

inline ConsoleValue RunScript(const char* str)
{
   return std::move(Con::evaluate(str, false, NULL));
}

TEST(Script, Basic_Arithmetic)
{
   ConsoleValue add = RunScript(R"(
         return 1.0 + 1;
   )");

   ASSERT_EQ(add.getInt(), 2);

   ConsoleValue sub = RunScript(R"(
         return 10 - 1.0;
   )");

   ASSERT_EQ(sub.getInt(), 9);

   ConsoleValue mult = RunScript(R"(
         return 10 * 2.5;
   )");

   ASSERT_EQ(mult.getInt(), 25);

   ConsoleValue div = RunScript(R"(
         return 10.0 / 2;
   )");

   ASSERT_EQ(div.getInt(), 5);

   ConsoleValue mod = RunScript(R"(
         return 4 % 5;
   )");

   ASSERT_EQ(mod.getInt(), 4);

   ConsoleValue add2 = RunScript(R"(
         $a = 0;
         $a += 2;
         return $a;
   )");

   ASSERT_EQ(add2.getInt(), 2);

   ConsoleValue sub2 = RunScript(R"(
         $a = 0;
         $a -= 2;
         return $a;
   )");

   ASSERT_EQ(sub2.getInt(), -2);

   ConsoleValue mult2 = RunScript(R"(
         $a = 2;
         $a *= 3;
         return $a;
   )");

   ASSERT_EQ(mult2.getInt(), 6);

   ConsoleValue div2 = RunScript(R"(
         $a = 10;
         $a /= 2;
         return $a;
   )");

   ASSERT_EQ(div2.getInt(), 5);

   ConsoleValue pp = RunScript(R"(
         $a = 0;
         $a++;
         return $a;
   )");

   ASSERT_EQ(pp.getInt(), 1);

   ConsoleValue mm = RunScript(R"(
         $a = 2;
         $a--;
         return $a;
   )");

   ASSERT_EQ(mm.getInt(), 1);
}

TEST(Script, Complex_Arithmetic)
{
   ConsoleValue result = RunScript(R"(
         return 1 * 2 - (0.5 * 2);
   )");

   ASSERT_EQ(result.getInt(), 1);

   ConsoleValue result2 = RunScript(R"(
         return 1 * 2 * 3 % 2;
   )");

   ASSERT_EQ(result2.getInt(), 0);
}

TEST(Script, Basic_Concatination)
{
   ConsoleValue result1 = RunScript(R"(
         return "a" @ "b";
   )");

   ASSERT_STREQ(result1.getString(), "ab");

   ConsoleValue result2 = RunScript(R"(
         return "a" SPC "b";
   )");

   ASSERT_STREQ(result2.getString(), "a b");

   ConsoleValue result3 = RunScript(R"(
         return "a" TAB "b";
   )");

   ASSERT_STREQ(result3.getString(), "a\tb");

   ConsoleValue result4 = RunScript(R"(
         return "a" NL "b";
   )");

   ASSERT_STREQ(result4.getString(), "a\nb");

   ConsoleValue complex = RunScript(R"(
         return "a" @ "b" @ "c" @ "d";
   )");

   ASSERT_STREQ(complex.getString(), "abcd");
}

TEST(Script, Basic_Global_Variable_Tests)
{
   ConsoleValue value = RunScript(R"(
         $a = 1;
         return $a;
   )");

   ASSERT_EQ(value.getInt(), 1);
}

TEST(Script, Variable_Chaining_And_Usage)
{
   ConsoleValue value = RunScript(R"(
         function t() 
         {
            %a = %b = 2;
            return %a;
         }
         return t();
   )");

   ASSERT_EQ(value.getInt(), 2);

   ConsoleValue valueGlobal = RunScript(R"(
         function t() 
         {
            $a = %b = 2;
         }
         t();
         return $a;
   )");

   ASSERT_EQ(valueGlobal.getInt(), 2);

   ConsoleValue value2 = RunScript(R"(
         function t(%a) 
         {
            if ((%b = 2 * %a) != 5)
               return %b;
            return 5;
         }

         return t(2);
   )");

   ASSERT_EQ(value2.getInt(), 4);
}

TEST(Script, Basic_Function_Call_And_Local_Variable_Testing)
{
   ConsoleValue value = RunScript(R"(
         function t() { %a = 2; return %a; }
         return t();
   )");

   ASSERT_EQ(value.getInt(), 2);

   ConsoleValue value2 = RunScript(R"(
         function add(%a, %b) { return %a + %b; }
         return add(2, 4);
   )");

   ASSERT_EQ(value2.getInt(), 6);

   ConsoleValue value3 = RunScript(R"(
         function fib(%a) {
            if (%a == 0)
               return 0;
            if (%a == 1)
               return 1;
            return fib(%a - 1) + fib(%a - 2);
         }
         return fib(15);
   )");

   ASSERT_EQ(value3.getInt(), 610);

   ConsoleValue staticCall = RunScript(R"(
         function SimObject::bar(%a, %b) {
            return %a + %b;
         }
         return SimObject::bar(1, 2);
   )");

   ASSERT_EQ(staticCall.getInt(), 3);
}

TEST(Script, Basic_Conditional_Statements)
{
   ConsoleValue value = RunScript(R"(
         $a = "hello";
         if ($a $= "hello")
            return 1;
         return 2;
   )");

   ASSERT_EQ(value.getInt(), 1);

   ConsoleValue ternaryValue = RunScript(R"(
         return $a $= "hello" ? "World" : "No U";
   )");

   ASSERT_STREQ(ternaryValue.getString(), "World");
}

TEST(Script, Basic_Loop_Statements)
{
   ConsoleValue whileValue = RunScript(R"(
         $count = 0;
         while ($count < 5)
            $count++;
         return $count;
   )");

   ASSERT_EQ(whileValue.getInt(), 5);

   ConsoleValue forValue = RunScript(R"(
         function t(%times) 
         { 
            %result = "";
            for (%i = 0; %i < %times; %i++)
               %result = %result @ "a";
            return %result;
         }

         return t(3);
   )");

   ASSERT_STREQ(forValue.getString(), "aaa");

   ConsoleValue forReverseLoop = RunScript(R"(
         function t(%times) 
         { 
            %result = "";
            for (%i = %times - 1; %i >= 0; %i--)
               %result = %result @ "b";
            return %result;
         }

         return t(3);
   )");

   ASSERT_STREQ(forReverseLoop.getString(), "bbb");

   ConsoleValue forIfValue = RunScript(R"(
         function t()
         {
            %str = "";
            for (%i = 0; %i < 5; %i++)
            {

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

   ASSERT_STREQ(forIfValue.getString(), "0, 1, 2, 3, 4");
}

TEST(Script, ForEachLoop)
{
   ConsoleValue forEach1 = RunScript(R"(
         $theSimSet = new SimSet();
         $theSimSet.add(new SimObject());
         $theSimSet.add(new SimObject());

         $counter = 0;
         foreach ($obj in $theSimSet)
         {
            $counter++;
         }

         $theSimSet.delete();

         return $counter;
   )");

   ASSERT_EQ(forEach1.getInt(), 2);

   ConsoleValue forEach2 = RunScript(R"(
         $counter = 0;
         foreach$ ($word in "a b c d")
         {
            $counter++;
         }

         return $counter;
   )");

   ASSERT_EQ(forEach2.getInt(), 4);

   ConsoleValue forEach3 = RunScript(R"(
         function SimObject::addOne(%this)
         {
            return 1;
         }

         function test()
         {
            %set = new SimSet();
            %set.add(new SimObject());
            %set.add(new SimObject());

            %count = 0;
            foreach (%obj in %set)
               %count += %obj.addOne();

            %set.delete();

            return %count;
         }

         return test();
   )");

   ASSERT_EQ(forEach3.getInt(), 2);

   ConsoleValue forEach4 = RunScript(R"(
         function test()
         {
            %string = "a b c d e";

            %count = 0;
            foreach$ (%word in %string)
               %count++;

            return %count;
         }

         return test();
   )");

   ASSERT_EQ(forEach4.getInt(), 5);
}

TEST(Script, TorqueScript_Array_Testing)
{
   ConsoleValue value = RunScript(R"(
         function t(%idx) { %a[%idx] = 2; return %a[%idx]; }
         return t(5);
   )");

   ASSERT_EQ(value.getInt(), 2);

   ConsoleValue value2 = RunScript(R"(
         function t(%idx) { %a[%idx, 0] = 2; return %a[%idx, 0]; }
         return t(5);
   )");

   ASSERT_EQ(value2.getInt(), 2);
}

TEST(Script, Basic_SimObject)
{
   ConsoleValue object = RunScript(R"(
         return new SimObject(FudgeCollector)
         {
            fudge = "Chocolate"; 
         };
   )");

   ASSERT_NE(Sim::findObject(object), (SimObject*)NULL);

   ConsoleValue propertyValue = RunScript(R"(
         return FudgeCollector.fudge;
   )");

   ASSERT_STREQ(propertyValue.getString(), "Chocolate");

   ConsoleValue funcReturn = RunScript(R"(
         function SimObject::fooFunc(%this)
         {
            return "Bar";
         }

         return FudgeCollector.fooFunc();
   )");

   ASSERT_STREQ(funcReturn.getString(), "Bar");

   ConsoleValue parentFn = RunScript(R"(
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

   ASSERT_STREQ(parentFn.getString(), "FooBar");

   ConsoleValue grp = RunScript(R"(
         new SimGroup(FudgeCollectorGroup)
         {
            theName = "fudge";

            new SimObject(ChocolateFudge)
            {
               type = "Chocolate";
            };
            new SimObject(PeanutButterFudge)
            {
               type = "Peanut Butter";

               field["a"] = "Yes";
            };
         };

         return FudgeCollectorGroup.getId();
   )");

   SimGroup* simGroup = dynamic_cast<SimGroup*>(Sim::findObject(grp));
   ASSERT_NE(simGroup, (SimGroup*)NULL);
   ASSERT_EQ(simGroup->size(), 2);

   simGroup->deleteObject();

   ConsoleValue fieldTest = RunScript(R"(
         function a()
         {
            %obj = new SimObject();
            %obj.field = "A";
            %obj.val[%obj.field] = "B";

            %value = %obj.val["A"];
            %obj.delete();
            return %value;
         }
         return a();
   )");

   ASSERT_STREQ(fieldTest.getString(), "B");

   ConsoleValue fieldOpTest = RunScript(R"(
         function a()
         {
            %obj = new SimObject();
            %obj.field = 1;
            %obj.field += 2;

            %value = %obj.field;
            %obj.delete();
            return %value;
         }
         return a();
   )");

   ASSERT_EQ(fieldOpTest.getInt(), 3);
}

TEST(Script, Internal_Name)
{
   ConsoleValue value = RunScript(R"(
         function SimObject::_internalCall(%this)
         {
            return 5;
         }

         function a()
         {
            %grp = new SimGroup();
            %obj = new SimObject()
            {
               internalName = "Yay";
            };
            %grp.add(%obj);

            %val = %grp->Yay._internalCall();

            %grp.delete();

            return %val;
         }
         return a();
   )");

   ASSERT_EQ(value.getInt(), 5);
}

TEST(Script, Basic_Package)
{
   ConsoleValue value = RunScript(R"(
         function a() { return 3; }
         package overrides
         {
            function a() { return 5; }
         };
         return a();
   )");

   ASSERT_EQ(value.getInt(), 3);

   ConsoleValue overrideValue = RunScript(R"(
         activatePackage(overrides);
         return a();
   )");

   ASSERT_EQ(overrideValue.getInt(), 5);

   ConsoleValue deactivatedValue = RunScript(R"(
         deactivatePackage(overrides);
         return a();
   )");

   ASSERT_EQ(deactivatedValue.getInt(), 3);
}

#endif
