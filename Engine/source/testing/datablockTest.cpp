#include <gtest/gtest.h>

#include "console/script.h"
#include "T3D/fx/particle.h"
#include "T3D/gameBase/gameBase.h"

TEST(DatablockTest, Datablocks_Can_Be_Overridden)
{
   Con::EvalResult result = Con::evaluatef(R"(
      datablock SimDataBlock(testDb) {
         foo = 2;
      };
      datablock SimDataBlock(testDb) {
         foo = 3;
      };
      return testDb.foo;
   )", false, "datablockTest.cpp");

   ASSERT_TRUE(result.valid);
   // Successfully overrode the datablock
   EXPECT_STREQ(result.value, "3");

   // Cleanup
   result = Con::evaluatef(R"(
      testDb.delete();
      return "done";
   )", false, "datablockTest.cpp");
   // Cleanup succesful
   ASSERT_TRUE(result.valid);
}

TEST(DatablockTest, Datablocks_Must_Not_Change_Type)
{
   Con::EvalResult result = Con::evaluatef(R"(
      datablock SimDataBlock(testDb) {
         foo = 2;
      };
      datablock ParticleData(testDb) {
         foo = 3;
      };
      return testDb.foo;
   )", false, "datablockTest.cpp");

   // Not a syntax error
   ASSERT_TRUE(result.valid);
   // Did not override the datablock
   EXPECT_STREQ(result.value, "2");

   // Cleanup
   result = Con::evaluatef(R"(
      testDb.delete();
      return "done";
   )", false, "datablockTest.cpp");
   // Cleanup succesful
   ASSERT_TRUE(result.valid);
}

TEST(DatablockTest, Datablock_Can_Substitute_String)
{
   Con::EvalResult result = Con::evaluatef(R"(
      datablock ParticleData(testDb) {
         lifetimeMS = "$$ %%%%.bar";
      };

      $simObj = new GameBase(testObj) {
         bar = 1234;
      };

      return "done";
    )", false, "datablockTest.cpp");

   EXPECT_TRUE(result.valid);
   EXPECT_STREQ(result.value, "done");

   ParticleData* testDb = NULL;
   Sim::findObject("testDb", testDb);
   GameBase* testObj = NULL;
   Sim::findObject("testObj", testObj);

   testDb->performSubstitutions(testDb, testObj);

   EXPECT_EQ(testDb->lifetimeMS, 1234);

   // Cleanup
   testDb->deleteObject();
   testObj->deleteObject();
}
