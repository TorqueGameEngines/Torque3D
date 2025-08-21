#pragma once
#ifndef SUBSCENE_ASSET_H
#define SUBSCENE_ASSET_H

#ifndef LEVEL_ASSET_H
#include "LevelAsset.h"
#endif

#ifndef _ASSET_DEFINITION_H_
#include "assets/assetDefinition.h"
#endif

#ifndef _GUI_INSPECTOR_TYPES_H_
#include "gui/editor/guiInspectorTypes.h"
#endif

class SubSceneAsset : public LevelAsset
{
   typedef LevelAsset Parent;

public:
   SubSceneAsset();
   virtual ~SubSceneAsset();

   /// Engine.
   static void initPersistFields();

   /// Declare Console Object.
   DECLARE_CONOBJECT(SubSceneAsset);
};

#ifdef TORQUE_TOOLS
class GuiInspectorTypeSubSceneAssetPtr : public GuiInspectorTypeFileName
{
   typedef GuiInspectorTypeFileName Parent;
public:

   GuiBitmapButtonCtrl* mEditButton;

   DECLARE_CONOBJECT(GuiInspectorTypeSubSceneAssetPtr);
   static void consoleInit();

   GuiControl* constructEditControl() override;
   bool updateRects() override;
};

class GuiInspectorTypeSubSceneAssetId : public GuiInspectorTypeSubSceneAssetPtr
{
   typedef GuiInspectorTypeSubSceneAssetPtr Parent;
public:

   DECLARE_CONOBJECT(GuiInspectorTypeSubSceneAssetId);
   static void consoleInit();
};
#endif

DefineConsoleType(TypeSubSceneAssetPtr, SubSceneAsset)
DefineConsoleType(TypeSubSceneAssetId, String)

#pragma region Singular Asset Macros

//Singular assets
/// <Summary>
/// Declares an SubScene asset
/// This establishes the assetId, asset and legacy filepath fields, along with supplemental getter and setter functions
/// </Summary>
#define DECLARE_SUBSCENEASSET(className, name, changeFunc) public: \
   StringTableEntry m##name##AssetId;\
   AssetPtr<SubSceneAsset>  m##name##Asset;\
public: \
   const AssetPtr<SubSceneAsset> & get##name##Asset() const { return m##name##Asset; }\
   void set##name##Asset(const AssetPtr<SubSceneAsset> &_in) { m##name##Asset = _in;}\
   \
   bool _set##name(StringTableEntry _in)\
   {\
      if(m##name##AssetId != _in)\
      {\
         if (m##name##Asset.notNull())\
         {\
            m##name##Asset->getChangedSignal().remove(this, &className::changeFunc);\
         }\
         if (_in == NULL || !String::compare(_in,StringTable->EmptyString()))\
         {\
            m##name##AssetId = StringTable->EmptyString();\
            m##name##Asset = NULL;\
            return true;\
         }\
         if (AssetDatabase.isDeclaredAsset(_in))\
         {\
            m##name##AssetId = _in;\
            m##name##Asset = _in;\
            return true;\
         }\
      }\
      \
      if(get##name() == StringTable->EmptyString())\
         return true;\
      \
      return false;\
   }\
   \
   const StringTableEntry get##name() const\
   {\
      return m##name##AssetId;\
   }\
   bool name##Valid() {return (get##name() != StringTable->EmptyString() && m##name##Asset->getStatus() == AssetBase::Ok); }

#define INITPERSISTFIELD_SUBSCENEASSET(name, consoleClass, docs) \
   addProtectedField(assetText(name, Asset), TypeSubSceneAssetId, Offset(m##name##AssetId, consoleClass), _set##name##Data, &defaultProtectedGetFn, assetDoc(name, asset docs.));

#pragma endregion

#endif // SUBSCENE_ASSET_H
