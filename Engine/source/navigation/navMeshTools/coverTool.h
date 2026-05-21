#pragma once 
#pragma once 
#ifndef _COVERTOOL_H_
#define _COVERTOOL_H_
#include "navigation/navMeshTool.h"

#include "navigation/navPath.h"

class CoverTool : public NavMeshTool
{
   typedef NavMeshTool Parent;
public:
   DECLARE_CONOBJECT(CoverTool);

   CoverTool();

   virtual ~CoverTool() {}

   void onActivated(const Gui3DMouseEvent& evt) override;
   void onDeactivated() override;

   void on3DMouseDown(const Gui3DMouseEvent& evt) override;
   void on3DMouseMove(const Gui3DMouseEvent& evt) override;
   void onRender3D() override;

   bool updateGuiInfo() override;
};

#endif // !_COVERTOOL_H_

