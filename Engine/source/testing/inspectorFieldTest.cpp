#include <gtest/gtest.h>

#include "gui/editor/guiInspector.h"
#include "gui/editor/inspector/group.h"
#include "gui/editor/inspector/field.h"
#include "console/script.h"
#include "console/simDatablock.h"

class InspectorTestData : public SimDataBlock
{
   typedef SimDataBlock Parent;

public:
   S32 testInt = 0;
   F32 testFloat = 0.f;
   bool testBool = false;
   StringTableEntry testString;

   DECLARE_CONOBJECT(InspectorTestData);

   static void initPersistFields()
   {
      addField("testInt", TypeS32,        Offset(testInt, InspectorTestData));
      addField("testFloat", TypeF32,      Offset(testFloat, InspectorTestData));
      addField("testBool", TypeBool,      Offset(testBool, InspectorTestData));
      addField("testString", TypeString,  Offset(testString, InspectorTestData));

      Parent::initPersistFields();
   }
};

IMPLEMENT_CO_DATABLOCK_V1(InspectorTestData);

class GuiInspectorFieldFixture : public ::testing::Test
{
protected:
   GuiInspector* inspector{};
   GuiInspectorGroup* group{};

   void SetUp() override
   {
      inspector = new GuiInspector();
      ASSERT_TRUE(inspector->registerObject());

      group = new GuiInspectorGroup("testing", nullptr);
      ASSERT_TRUE(group->registerObject());
   }

   void TearDown() override
   {
      group->deleteObject();
      inspector->deleteObject();
   }

   GuiInspectorField* createField(
      SimObject* object,
      const char* fieldName)
   {
      inspector->addInspectObject(object);

      AbstractClassRep::Field* field =
         const_cast<AbstractClassRep::Field*>(
            object->findField(StringTable->insert(fieldName)));

      EXPECT_NE(field, nullptr);

      GuiInspectorField* inspectorField =  new GuiInspectorField(inspector, group, field);
      EXPECT_TRUE(inspectorField->registerObject());

      return inspectorField;
   }
};

TEST_F(GuiInspectorFieldFixture, SetData_IntField)
{
   InspectorTestData* object = new InspectorTestData();
   ASSERT_TRUE(object->registerObject());

   GuiInspectorField* field = createField(object, "testInt");

   field->setData("12345");

   EXPECT_EQ(object->testInt, 12345);

   field->deleteObject();
   object->deleteObject();
}

TEST_F(GuiInspectorFieldFixture, SetData_FloatField)
{
   InspectorTestData* object = new InspectorTestData();
   ASSERT_TRUE(object->registerObject());

   GuiInspectorField* field = createField(object, "testFloat");

   field->setData("123.5");

   EXPECT_FLOAT_EQ(object->testFloat, 123.5f);

   field->deleteObject();
   object->deleteObject();
}

TEST_F(GuiInspectorFieldFixture, SetData_BoolField)
{
   InspectorTestData* object = new InspectorTestData();
   ASSERT_TRUE(object->registerObject());

   GuiInspectorField* field = createField(object, "testBool");

   field->setData("1");

   EXPECT_TRUE(object->testBool);

   field->deleteObject();
   object->deleteObject();
}

TEST_F(GuiInspectorFieldFixture, SetData_StringField)
{
   InspectorTestData* object = new InspectorTestData();
   ASSERT_TRUE(object->registerObject());

   GuiInspectorField* field = createField(object, "testString");

   field->setData("Hello World");

   EXPECT_STREQ(object->testString, "Hello World");

   field->deleteObject();
   object->deleteObject();
}
