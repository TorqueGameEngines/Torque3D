#ifdef TORQUE_TESTS_ENABLED

#include "testing/unitTesting.h"
#include "platform/platform.h"
#include "console/simBase.h"
#include "console/consoleTypes.h"
#include "console/simBase.h"
#include "console/engineAPI.h"
#include "math/mMath.h"
#include "console/stringStack.h"
#include "console/consoleInternal.h"

// Stupid globals not declared in a header
extern ExprEvalState gEvalState;

TEST(Con, executef)
{
	char buffer[128];
	Con::evaluate("if (isObject(TestConExec)) {\r\nTestConExec.delete();\r\n}\r\nfunction testExecutef(%a,%b,%c,%d,%e,%f,%g,%h,%i,%j,%k){return %a SPC %b SPC %c SPC %d SPC %e SPC %f SPC %g SPC %h SPC %i SPC %j SPC %k;}\r\nfunction TestConExec::testThisFunction(%this,%a,%b,%c,%d,%e,%f,%g,%h,%i,%j){ return %a SPC %b SPC %c SPC %d SPC %e SPC %f SPC %g SPC %h SPC %i SPC %j;}\r\nnew ScriptObject(TestConExec);\r\n", false, "test");

	SimObject *testObject = NULL;
	Sim::findObject("TestConExec", testObject);

	EXPECT_TRUE(testObject != NULL)
		<< "TestConExec object should exist";

	// Check basic calls with SimObject. We'll do this for every single possible call just to make sure.
	ConsoleValue returnValue;

	returnValue = Con::executef(testObject, "testThisFunction");
	EXPECT_STREQ(returnValue, "         ") <<
		"All values should be printed in the correct order";

	returnValue = Con::executef(testObject, "testThisFunction", "a");
	EXPECT_STREQ(returnValue, "a         ") <<
		"All values should be printed in the correct order";

	returnValue = Con::executef(testObject, "testThisFunction", "a", "b");
	EXPECT_STREQ(returnValue, "a b        ") <<
		"All values should be printed in the correct order";

	returnValue = Con::executef(testObject, "testThisFunction", "a", "b", "c");
	EXPECT_STREQ(returnValue, "a b c       ") <<
		"All values should be printed in the correct order";

	returnValue = Con::executef(testObject, "testThisFunction", "a", "b", "c", "d");
	EXPECT_STREQ(returnValue, "a b c d      ") <<
		"All values should be printed in the correct order";

	returnValue = Con::executef(testObject, "testThisFunction", "a", "b", "c", "d", "e");
	EXPECT_STREQ(returnValue, "a b c d e     ") <<
		"All values should be printed in the correct order";

	returnValue = Con::executef(testObject, "testThisFunction", "a", "b", "c", "d", "e", "f");
	EXPECT_STREQ(returnValue, "a b c d e f    ") <<
		"All values should be printed in the correct order";

	returnValue = Con::executef(testObject, "testThisFunction", "a", "b", "c", "d", "e", "f", "g");
	EXPECT_STREQ(returnValue, "a b c d e f g   ") <<
		"All values should be printed in the correct order";

	returnValue = Con::executef(testObject, "testThisFunction", "a", "b", "c", "d", "e", "f", "g", "h");
	EXPECT_STREQ(returnValue, "a b c d e f g h  ") <<
		"All values should be printed in the correct order";

	returnValue = Con::executef(testObject, "testThisFunction", "a", "b", "c", "d", "e", "f", "g", "h", "i");
	EXPECT_STREQ(returnValue, "a b c d e f g h i ") <<
		"All values should be printed in the correct order";

	// Now test without the object

	returnValue = Con::executef("testExecutef");
	EXPECT_STREQ(returnValue, "          ") <<
		"All values should be printed in the correct order";

	returnValue = Con::executef("testExecutef", "a");
	EXPECT_STREQ(returnValue, "a          ") <<
		"All values should be printed in the correct order";

	returnValue = Con::executef("testExecutef", "a", "b");
	EXPECT_STREQ(returnValue, "a b         ") <<
		"All values should be printed in the correct order";

	returnValue = Con::executef("testExecutef", "a", "b", "c");
	EXPECT_STREQ(returnValue, "a b c        ") <<
		"All values should be printed in the correct order";

	returnValue = Con::executef("testExecutef", "a", "b", "c", "d");
	EXPECT_STREQ(returnValue, "a b c d       ") <<
		"All values should be printed in the correct order";

	returnValue = Con::executef("testExecutef", "a", "b", "c", "d", "e");
	EXPECT_STREQ(returnValue, "a b c d e      ") <<
		"All values should be printed in the correct order";

	returnValue = Con::executef("testExecutef", "a", "b", "c", "d", "e", "f");
	EXPECT_STREQ(returnValue, "a b c d e f     ") <<
		"All values should be printed in the correct order";

	returnValue = Con::executef("testExecutef", "a", "b", "c", "d", "e", "f", "g");
	EXPECT_STREQ(returnValue, "a b c d e f g    ") <<
		"All values should be printed in the correct order";

	returnValue = Con::executef("testExecutef", "a", "b", "c", "d", "e", "f", "g", "h");
	EXPECT_STREQ(returnValue, "a b c d e f g h   ") <<
		"All values should be printed in the correct order";

	returnValue = Con::executef("testExecutef", "a", "b", "c", "d", "e", "f", "g", "h", "i");
	EXPECT_STREQ(returnValue, "a b c d e f g h i  ") <<
		"All values should be printed in the correct order";

	returnValue = Con::executef("testExecutef", "a", "b", "c", "d", "e", "f", "g", "h", "i", "j");
	EXPECT_STREQ(returnValue, "a b c d e f g h i j ") <<
		"All values should be printed in the correct order";

	// Test type conversions with and without SimObject...

	// Integer
	returnValue = Con::executef(testObject, "testThisFunction", 123);
	EXPECT_STREQ(returnValue, "123         ") <<
		"Integer should be converted";
	returnValue = Con::executef("testExecutef", 123);
	EXPECT_STREQ(returnValue, "123          ") <<
		"Integer should be converted";

	// Float
	returnValue = Con::executef(testObject, "testThisFunction", (F32)123.0);
	EXPECT_STREQ(returnValue, "123         ") <<
		"Float should be converted";
	returnValue = Con::executef("testExecutef", (F32)123.0);
	EXPECT_STREQ(returnValue, "123          ") <<
		"Float should be converted";

	// SimObject
	dSprintf(buffer, sizeof(buffer), "%i         ", testObject->getId());
	returnValue = Con::executef(testObject, "testThisFunction", testObject);
	EXPECT_STREQ(returnValue, buffer) <<
		"SimObject should be converted";
	dSprintf(buffer, sizeof(buffer), "%i          ", testObject->getId());
	returnValue = Con::executef("testExecutef", testObject);
	EXPECT_STREQ(returnValue, buffer) <<
		"SimObject should be converted";

	// Point3F
	Point3F point(1,2,3);
	returnValue = Con::executef(testObject, "testThisFunction", point);
	EXPECT_STREQ(returnValue, "1 2 3         ") <<
		"Point3F should be converted";
	returnValue = Con::executef("testExecutef", point);
	EXPECT_STREQ(returnValue, "1 2 3          ") <<
		"Point3F should be converted";

   // Finally test the function arg offset. This should be consistently 0 after each call

	EXPECT_EQ(STR.mFunctionOffset, 0) <<
		"Function offset should be 0";

   const char *floatArg = Con::getFloatArg(1.23);
	EXPECT_GT(STR.mFunctionOffset, 0) <<
		"Function offset should not be 0";

   Con::executef("testExecutef", floatArg);

	EXPECT_EQ(STR.mFunctionOffset, 0) <<
		"Function offset should be 0";

   floatArg = Con::getFloatArg(1.23);
	EXPECT_GT(STR.mFunctionOffset, 0) <<
		"Function offset should not be 0";

   Con::executef("testImaginaryFunction_", floatArg);

	EXPECT_EQ(STR.mFunctionOffset, 0) <<
		"Function offset should be 0";
}

TEST(Con, execute)
{
	Con::evaluate("if (isObject(TestConExec)) {\r\nTestConExec.delete();\r\n}\r\nfunction testScriptExecuteFunction(%a,%b) {return %a SPC %b;}\nfunction TestConExec::testScriptExecuteFunction(%this, %a,%b) {return %a SPC %b;}new ScriptObject(TestConExec);\r\n", false, "testExecute");

	U32 startStackPos = gEvalState.getStackDepth();
	U32 startStringStackPos = STR.mStart;

	SimObject *testObject = NULL;
	Sim::findObject("TestConExec", testObject);

	EXPECT_TRUE(testObject != NULL)
		<< "TestConExec object should exist";

	// const char* versions of execute should maintain stack
	const char *argv[] = {"testScriptExecuteFunction", "1", "2"};
	const char *argvObject[] = {"testScriptExecuteFunction", "", "1", "2"};
	ConsoleValue returnValue = Con::execute(3, argv);

	EXPECT_STREQ(returnValue, "1 2") <<
		"execute should return 1 2";

	EXPECT_EQ(gEvalState.getStackDepth(), startStackPos) <<
		"execute should restore stack";

	returnValue = Con::execute(testObject, 4, argvObject);

	EXPECT_STREQ(returnValue, "1 2") <<
		"execute should return 1 2";

	EXPECT_EQ(gEvalState.getStackDepth(), startStackPos) <<
		"execute should restore stack";
}

#endif
