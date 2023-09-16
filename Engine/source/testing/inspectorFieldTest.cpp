#include <gtest/gtest.h>
#include <gui/editor/inspector/group.h>

#include "console/script.h"
#include "T3D/fx/particle.h"
#include "T3D/gameBase/gameBase.h"

TEST(InspectoreFieldTest, Datablocks_Can_Be_Overridden)
{
   GuiInspector* inspector = new GuiInspector();
   inspector->registerObject();

   ParticleData* exampleObj = new ParticleData();
   exampleObj->registerObject();
   // Add it to inspector so inspector field can find it
   inspector->addInspectObject(exampleObj);

   AbstractClassRep::Field* field = const_cast<AbstractClassRep::Field*>(exampleObj->findField(StringTable->insert("lifetimeMS")));

   GuiInspectorGroup* group = new GuiInspectorGroup("testing", NULL);
   ASSERT_TRUE(group->registerObject());

   GuiInspectorField* inspectorField = new GuiInspectorField(inspector, group, field);
   ASSERT_TRUE(inspectorField->registerObject());

   inspectorField->setData("12345");
   EXPECT_EQ(exampleObj->lifetimeMS, 12345);

   // Cleanup
   inspectorField->deleteObject();
   group->deleteObject();
   inspector->deleteObject();
   exampleObj->deleteObject();
}
