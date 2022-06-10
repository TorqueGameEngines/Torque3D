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

   ConsoleValue forEach5 = RunScript(R"(
      function SimObject::ret1(%this)
      {
         return 1;
      }

      function SimSet::doForeach5(%this)
      {
         %count = 0;
         foreach (%obj in %this)
         {
            %count += %obj.ret1();
         }
         return %count;
      }

      function a()
      {
         %set = new SimSet();
         %set.add(new SimObject());
         %set.add(new SimObject());
         %set.add(new SimObject());

         return %set.doForeach5();
      }

      return a();
   )");

   ASSERT_EQ(forEach5.getInt(), 3);

   ConsoleValue forEachContinue = RunScript(R"(
      function SimSet::foreach6(%this)
      {
         %count = 0;
         foreach (%obj in %this)
         {
            if (%obj.getName() $= "A")
               continue;

             %count++;
         }
         return %count;
      }

      function a()
      {
         %set = new SimSet();
         %set.add(new SimObject(A));
         %set.add(new SimObject());
         %set.add(new SimObject());

         return %set.foreach6();
      }

      return a();
   )");

   ASSERT_EQ(forEachContinue.getInt(), 2);

   ConsoleValue forEachReturn = RunScript(R"(
      function SimSet::findA(%this)
      {
         foreach (%obj in %this)
         {
            if (%obj.getName() $= "A")
               return 76;
         }
         return 0;
      }

      function a()
      {
         %set = new SimSet();
         %set.add(new SimObject(A));
         %set.add(new SimObject());
         %set.add(new SimObject());

         return %set.findA();
      }

      return a();
   )");

   ASSERT_EQ(forEachReturn.getInt(), 76);

   ConsoleValue forEachNestedReturn = RunScript(R"(
      function SimSet::findA(%this)
      {
         foreach (%obj in %this)
         {
            foreach (%innerObj in %this)
            {
               if (%innerObj.getName() $= "A")
                  return 42;
            }
         }
         return 0;
      }

      function a()
      {
         %set = new SimSet();
         %set.add(new SimObject(A));
         %set.add(new SimObject());
         %set.add(new SimObject());

         %group = new SimGroup();
         %group.add(%set);

         return %set.findA();
      }

      return a();
   )");

   ASSERT_EQ(forEachNestedReturn.getInt(), 42);
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

TEST(Script, SimObject_Tests)
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

   ConsoleValue simpleFieldTest = RunScript(R"(
         function a()
         {
            FudgeCollector.field = "A";
            return FudgeCollector.field;
         }
         return a();
   )");

   ASSERT_STREQ(simpleFieldTest.getString(), "A");

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

   ConsoleValue inheritedObjectTest = RunScript(R"(
      function SimObject::testClass(%this)
      {
         return 4;
      }

      function SuperFooBar::doSuperTest(%this)
      {
         return 5;
      }

      function FooBar::test(%this)
      {
         return 2;
      }

      new SimObject(GrandFooBar)
      {
         superClass = "SuperFooBar";
      };

      new SimObject(Foo : GrandFooBar)
      {
         class = "FooBar";
      };

      new SimObject(Bar : Foo);

      function Bar::doTheAddition(%this)
      {
         return %this.testClass() + %this.test() + %this.doSuperTest(); 
      }

      return Bar.doTheAddition();
   )");

   ASSERT_EQ(inheritedObjectTest.getInt(), 11);
}

TEST(Script, Internal_Name)
{
   ConsoleValue value = RunScript(R"(
         function TheFirstInner::_internalCall(%this)
         {
            return 5;
         }

         function a()
         {
            %grp = new SimGroup();
            %obj = new SimObject(TheFirstInner)
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

   ConsoleValue recursiveValue = RunScript(R"(
         function SimGroup::doTheInternalCall(%this)
         {
            return %this-->Yeah._internalCall2();
         }

         function TheAnotherObject::_internalCall2(%this)
         {
            return %this.property;
         }

         function a()
         {
            %grp = new SimGroup();
            %obj = new SimGroup()
            {
               internalName = "Yay2";

               new SimObject(TheAnotherObject)
               {
                  internalName = "Yeah";
                  property = 12;
               };
            };
            %grp.add(%obj);

            %val = %grp.doTheInternalCall();

            %grp.delete();

            return %val;
         }
         return a();      
   )");

   ASSERT_EQ(recursiveValue.getInt(), 12);
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

TEST(Script, Sugar_Syntax)
{
   ConsoleValue value = RunScript(R"(
         function a()
         {
            %vector = "1 2 3";
            return %vector.y;
         }
         return a();
   )");

   ASSERT_EQ(value.getInt(), 2);

   ConsoleValue setValue = RunScript(R"(
         function a()
         {
            %vector = "1 2 3";
            %vector.y = 4;
            return %vector.y;
         }
         return a();
   )");

   ASSERT_EQ(setValue.getInt(), 4);

   ConsoleValue valueArray = RunScript(R"(
         function a()
         {
            %vector[0] = "1 2 3";
            return %vector[0].y;
         }
         return a();
   )");

   ASSERT_EQ(valueArray.getInt(), 2);

   ConsoleValue valueSetArray = RunScript(R"(
         function a()
         {
            %vector[0] = "1 2 3";
            %vector[0].z = 5;
            return %vector[0].z;
         }
         return a();
   )");

   ASSERT_EQ(valueSetArray.getInt(), 5);

   ConsoleValue valueStoreCalculated = RunScript(R"(
      function a()
      {
         %extent = 10 SPC 20;
         %scaling = 1;
         %size = %extent.x * %scaling;
         return %size;
      }

      return a();
   )");

   ASSERT_EQ(valueStoreCalculated.getInt(), 10);

   ConsoleValue globalValueGet = RunScript(R"(
      new SimObject(AAAA);
      AAAA.doSomething = false;
      $vec = "1 2 3";
      return $vec.x * 4;
   )");

   ASSERT_EQ(globalValueGet.getFloat(), 4);

   ConsoleValue globalValueSet = RunScript(R"(
      new SimObject(AAAAB);
      AAAAB.doSomething = false;
      $vec2 = "1 2 3";
      $vec2.x *= 4;
      return $vec2.x;
   )");

   ASSERT_EQ(globalValueSet.getFloat(), 4);
}

TEST(Script, InnerObjectTests)
{
   ConsoleValue theObject = RunScript(R"(
      function a()
      {
         %obj = new SimObject(TheOuterObject)
         {
            innerObject = new SimObject(TheInnerObject)
            {
               testField = 123;
               position = "1 2 3";
            };
         };
         return %obj;
      }
      return a();
   )");

   SimObject* outerObject = Sim::findObject("TheOuterObject");
   ASSERT_NE(outerObject, (SimObject*)NULL);
   if (outerObject)
   {
      ASSERT_EQ(theObject.getInt(), Sim::findObject("TheOuterObject")->getId());
   }
   ASSERT_NE(Sim::findObject("TheInnerObject"), (SimObject*)NULL);

   ConsoleValue positionValue = RunScript(R"(
      function TheOuterObject::getInnerPosition(%this)
      {
         return %this.innerObject.position;
      }

      function a()
      {
         %position = TheOuterObject.getInnerPosition();
         return %position.y;
      }
      return a();
   )");

   ASSERT_EQ(positionValue.getInt(), 2);

   ConsoleValue nestedFuncCall = RunScript(R"(
      function TheInnerObject::test(%this)
      {
         return %this.testField;
      }

      return TheOuterObject.innerObject.test();
   )");

   ASSERT_EQ(nestedFuncCall.getInt(), 123);
}

TEST(Script, MiscTesting)
{
   ConsoleValue test1 = RunScript(R"(
      function testNotPassedInParameters(%a, %b, %c, %d)
      {
         if (%d $= "")
            return true;
         return false;
      }

      return testNotPassedInParameters(1, 2); // skip passing in %c and %d
   )");

   ASSERT_EQ(test1.getBool(), true);

   ConsoleValue test2 = RunScript(R"(
      function SimObject::concatNameTest(%this)
      {
         return true;
      }

      new SimObject(WeirdTestObject1);

      function testObjectNameConcatination(%i)
      {
         return (WeirdTestObject @ %i).concatNameTest();
      }

      return testObjectNameConcatination(1);
   )");

   ASSERT_EQ(test2.getBool(), true);
}

TEST(Script, MiscRegressions)
{
   ConsoleValue regression1 = RunScript(R"(
      new SimObject(TheRegressionObject);

      function doTest()
      {
          TheRegressionObject.hidden = false;

          %previewSize = 100 SPC 100;
          %previewScaleSize = 2;
          %size = %previewSize.x * %previewScaleSize;

          return %size;
      }

      return doTest();
   )");

   ASSERT_EQ(regression1.getInt(), 200);

   ConsoleValue regression2 = RunScript(R"(
      new SimObject(TheRegressionObject2) 
      {
         extent = "100 200";
      };

      function doTest()
      {
          %scale = 2;
          %position = TheRegressionObject2.extent.x SPC TheRegressionObject2.extent.y * %scale;
          return %position.y;
      }

      return doTest();
   )");

   ASSERT_EQ(regression2.getInt(), 400);

   ConsoleValue regression3 = RunScript(R"(
      function doTest()
      {
          %button = new GuiIconButtonCtrl()
          {
              active = true;
          };

          %button.setExtent(120, 20);

          %button.setExtent("120 20");

          %button.extent = "120 20";

          %button.extent.x = 120;
          %button.extent.y = 20;
          return %button.extent;
      }
      return doTest();
   )");

   ASSERT_STREQ(regression3.getString(), "120 20");
   
   ConsoleValue regression4 = RunScript(R"(
    function doTest()
    {
        %slider = new GuiSliderCtrl()
        {
            range = "0 2";
            ticks = 5;
            active = true;
        };

        %slider.setValue(0.5);
        return %slider.getValue();
    }
    return doTest();
   )");
   
   ASSERT_EQ(regression4.getFloat(), 0.5);

   ConsoleValue regression5 = RunScript(R"(
      function noOpInc()
      {
         %count = 0;
         %var[%count++] = 2;
         return %var[1];
      }
      return noOpInc();
   )");

   ASSERT_EQ(regression5.getInt(), 2);

   ConsoleValue regression6 = RunScript(R"(
      function SimObject::crashMe(%this, %line)
      {
         return %line @ "1";
      }

      function doTest()
      {
         %obj = new SimObject();
         for (%i = 0; %i < 99999; %i++)
         {
            %function = "crashMe";
            if (%obj.isMethod(%function))
            {
               %line = "abcdefg";
               %output = %obj.call(%function, %line); 
            }
         }

         return true;
      }

      return doTest();
   )");

   ASSERT_EQ(regression6.getBool(), true);

   ConsoleValue regression7 = RunScript(R"(
      function Tween::vectorAdd(%v1, %v2)
      {
         %temp = "";
         for (%i = 0; %i < getWordCount(%v1); %i++) {
            %e = getWord(%v1, %i) + getWord(%v2, %i);
            %temp = %i == 0 ? %e : %temp SPC %e;
         }

         return %temp;
      }
      return Tween::vectorAdd("1 2 3", "4 5 6");
   )");

   ASSERT_STREQ(regression7.getString(), "5 7 9");
}

#endif
