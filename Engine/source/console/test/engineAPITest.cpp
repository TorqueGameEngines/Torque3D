#ifdef TORQUE_TESTS_ENABLED
#include "testing/unitTesting.h"
#include "platform/platform.h"
#include "console/simBase.h"
#include "console/consoleTypes.h"
#include "console/simBase.h"
#include "console/engineAPI.h"
#include "math/mMath.h"


TEST(EngineAPI, EngineMarshallData)
{
	// Reserve some values
	ConsoleValue values[16];

	// Basic string casting...
	SimObject *foo = new SimObject();
	foo->registerObject();

	const char *value = EngineMarshallData(foo);
	EXPECT_STREQ(value, foo->getIdString())
		<< "SimObject should be casted to its ID";

	U32 unsignedNumber = 123;
	S32 signedNumber = -123;
	value = EngineMarshallData(unsignedNumber);
	EXPECT_STREQ(value, "123")
		<< "Integer should be converted to 123";
	value = EngineMarshallData(signedNumber);
	EXPECT_STREQ(value, "-123")
		<< "Integer should be converted to -123";

	bool boolValue = true;
	value = EngineMarshallData(boolValue);
	EXPECT_STREQ(value, "1")
		<< "Bool should be converted to 1";

	Point3F point(1,2,3);
	value = EngineMarshallData(point);
	EXPECT_STREQ(value, "1 2 3")
		<< "Point3F should be converted to 1 2 3";

	F32 floatValue = 1.23f;
	value = EngineMarshallData(floatValue);
	EXPECT_STREQ(value, "1.23")
		<< "F32 should be converted to 1.23";

	// Argv based casting
	S32 argc = 0;
	EngineMarshallData(foo, argc, values);
	EngineMarshallData((const SimObject*)foo, argc, values);
	EngineMarshallData(point, argc, values);
	EngineMarshallData(unsignedNumber, argc, values);
	EngineMarshallData(signedNumber, argc, values);
	EngineMarshallData(boolValue, argc, values);
	EngineMarshallData(floatValue, argc, values);

	EXPECT_EQ(argc, 7)
		<< "7 args should have been set";

	EXPECT_EQ(values[0].getType(), ConsoleValueType::cvInteger)
	   << "1st arg should be an int";
	EXPECT_EQ(values[0].getInt(), foo->getId())
		<< "1st arg should be foo's id";

	EXPECT_EQ(values[1].getType(), ConsoleValueType::cvInteger)
	   << "2nd arg should be an int";
   EXPECT_EQ(values[1].getInt(), foo->getId())
		<< "2nd arg should be foo's id";

   EXPECT_EQ(values[2].getType(), ConsoleValueType::cvString)
      << "3rd arg should be a string";
	EXPECT_STREQ(values[2].getString(), "1 2 3")
		<< "3rd arg should be 1 2 3";

	EXPECT_EQ(values[3].getType(), ConsoleValueType::cvInteger)
      << "4th arg should be a float";
   EXPECT_EQ(values[3].getInt(), 123)
		<< "4th arg should be 123";

   EXPECT_EQ(values[4].getType(), ConsoleValueType::cvInteger)
      << "5th arg should be a float";
	EXPECT_EQ(values[4].getInt(), -123)
		<< "5th arg should be -123";


   EXPECT_EQ(values[5].getType(), ConsoleValueType::cvInteger)
      << "6th arg should be a float";
	EXPECT_TRUE(values[5].getBool())
		<< "6th arg should be true";

   EXPECT_EQ(values[6].getType(), ConsoleValueType::cvFloat)
      << "7th arg should be a float";
	EXPECT_FLOAT_EQ(values[6].getFloat(), 1.23)
		<< "7th arg should be 1.23";

	foo->deleteObject();
}

TEST(EngineAPI, EngineUnMarshallData)
{
	SimObject *foo = new SimObject();
	foo->registerObject();

	SimObject *testFoo = EngineUnmarshallData<SimObject*>()(foo->getIdString());

	EXPECT_EQ(foo, testFoo)
		<< "Unmarshalling foo's id should return foo";

	testFoo = EngineUnmarshallData<SimObject*>()("ShouldNotExist_Really123");
	EXPECT_TRUE(testFoo == NULL)
		<< "Unmarshalling a bad object should return NULL";

	foo->deleteObject();
}

TEST(EngineAPI, _EngineConsoleCallbackHelper)
{
	Con::evaluate("if (isObject(TestConExec)) {\r\nTestConExec.delete();\r\n}\r\nfunction testExecutef(%a,%b,%c,%d,%e,%f,%g,%h,%i,%j,%k){return %a SPC %b SPC %c SPC %d SPC %e SPC %f SPC %g SPC %h SPC %i SPC %j SPC %k;}\r\nfunction TestConExec::testThisFunction(%this,%a,%b,%c,%d,%e,%f,%g,%h,%i,%j){ return %a SPC %b SPC %c SPC %d SPC %e SPC %f SPC %g SPC %h SPC %i SPC %j;}\r\nnew ScriptObject(TestConExec);\r\n", false, "test");

	SimObject *testObject = NULL;
	Sim::findObject("TestConExec", testObject);

   _EngineConsoleCallbackHelper helper("testExecutef", NULL);
   ConsoleValue returnValue = helper.call<ConsoleValue>("a", "b", "c");

	EXPECT_STREQ(returnValue, "a b c        ") <<
		"All values should be printed in the correct order";

   _EngineConsoleCallbackHelper objectHelper("testThisFunction", testObject);
   returnValue = helper.call<ConsoleValue>("a", "b", "c");

	EXPECT_STREQ(returnValue, "a b c        ") <<
		"All values should be printed in the correct order";
}

// NOTE: this is also indirectly tested by the executef tests
TEST(EngineAPI, _EngineConsoleExecCallbackHelper)
{
	Con::evaluate("if (isObject(TestConExec)) {\r\nTestConExec.delete();\r\n}\r\nfunction testExecutef(%a,%b,%c,%d,%e,%f,%g,%h,%i,%j,%k){return %a SPC %b SPC %c SPC %d SPC %e SPC %f SPC %g SPC %h SPC %i SPC %j SPC %k;}\r\nfunction TestConExec::testThisFunction(%this,%a,%b,%c,%d,%e,%f,%g,%h,%i,%j){ return %a SPC %b SPC %c SPC %d SPC %e SPC %f SPC %g SPC %h SPC %i SPC %j;}\r\nnew ScriptObject(TestConExec);\r\n", false, "test");

	SimObject *testObject = NULL;
	Sim::findObject("TestConExec", testObject);

   _EngineConsoleExecCallbackHelper<const char*> helper("testExecutef");
   ConsoleValue returnValue = helper.call<ConsoleValue>("a", "b", "c");

	EXPECT_STREQ(returnValue, "a b c        ") <<
		"All values should be printed in the correct order";

   _EngineConsoleExecCallbackHelper<SimObject*> objectHelper(testObject);
   returnValue = objectHelper.call<ConsoleValue>("testThisFunction", "a", "b", "c");

	EXPECT_STREQ(returnValue, "a b c       ") <<
		"All values should be printed in the correct order";
}

#endif
