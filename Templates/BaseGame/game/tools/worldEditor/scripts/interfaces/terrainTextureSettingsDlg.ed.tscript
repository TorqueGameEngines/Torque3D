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

$TerrainTextureSettingsDlg::TerrainTextureFormat = 
   "R8G8B8 10" TAB 
   "R8G8B8_SRGB 11" TAB 
   "R8G8B8A8 12" TAB 
   "R8G8B8A8_SRGB 15" TAB
   "BC5 33";

//-----------------------------------------------------------------------------

function TerrainTextureSettingsDlg::show( %this )
{
   Canvas.pushDialog( %this );
}

function TerrainTextureSettingsDlg::onWake( %this ) {
   %this-->lerpBlendCheckBox.setStateOn(ProjectSettings.value("Terrain/LerpBlend"));
   %this-->blendDepthSlider.setValue(ProjectSettings.value("Terrain/BlendDepth"));
   
   %this-->detailTextureFormatPopUpMenu.clear();
   %this-->macroTextureFormatPopUpMenu.clear();
   %this-->normalTextureFormatPopUpMenu.clear();
   %this-->ormTextureFormatPopUpMenu.clear();
   
   for(%i = 0; %i < getFieldCount($TerrainTextureSettingsDlg::TerrainTextureFormat); %i++) {
      %field = getField($TerrainTextureSettingsDlg::TerrainTextureFormat, %i);
      
      %this-->detailTextureFormatPopUpMenu.add(getWord(%field, 0), getWord(%field, 1));
      %this-->macroTextureFormatPopUpMenu.add(getWord(%field, 0), getWord(%field, 1));
      %this-->normalTextureFormatPopUpMenu.add(getWord(%field, 0), getWord(%field, 1));
      %this-->ormTextureFormatPopUpMenu.add(getWord(%field, 0), getWord(%field, 1));
   }
   
   %this-->detailTextureFormatPopUpMenu.setSelected(ProjectSettings.value("Terrain/DetailTextureFormat", 12), false);
   %this-->macroTextureFormatPopUpMenu.setSelected(ProjectSettings.value("Terrain/MacroTextureFormat", 12), false);
   %this-->normalTextureFormatPopUpMenu.setSelected(ProjectSettings.value("Terrain/NormalTextureFormat", 12), false);
   %this-->ormTextureFormatPopUpMenu.setSelected(ProjectSettings.value("Terrain/OrmTextureFormat", 12), false);
   
   %this-->detailTextureSizeTextEdit.setText(ProjectSettings.value("Terrain/DetailTextureSize"));
   %this-->macroTextureSizeTextEdit.setText(ProjectSettings.value("Terrain/MacroTextureSize"));
   %this-->normalTextureSizeTextEdit.setText(ProjectSettings.value("Terrain/NormalTextureSize"));
   %this-->ormTextureSizeTextEdit.setText(ProjectSettings.value("Terrain/OrmTextureSize"));
}

function TerrainTextureSettingsDlg::updateBlendDepth( %this ) {
   $Terrain::BlendDepth = %this-->blendDepthSlider.getValue();
}

function TerrainTextureSettingsDlg::apply( %this ) {
   $Terrain::LerpBlend = %this-->lerpBlendCheckBox.isStateOn();
   $Terrain::BlendDepth = %this-->blendDepthSlider.getValue();
   
   $Terrain::DetailTextureFormat = %this-->detailTextureFormatPopUpMenu.getSelected();
   $Terrain::MacroTextureFormat = %this-->macroTextureFormatPopUpMenu.getSelected();
   $Terrain::NormalTextureFormat = %this-->normalTextureFormatPopUpMenu.getSelected();
   $Terrain::OrmTextureFormat = %this-->ormTextureFormatPopUpMenu.getSelected();
   
   if (%this-->detailTextureSizeTextEdit.getText() $= "" || mIsPow2(%this-->detailTextureSizeTextEdit.getText())) {
      $Terrain::DetailTextureSize = %this-->detailTextureSizeTextEdit.getText();
   }
   if (%this-->macroTextureSizeTextEdit.getText() $= "" || mIsPow2(%this-->macroTextureSizeTextEdit.getText())) {
      $Terrain::MacroTextureSize = %this-->macroTextureSizeTextEdit.getText();
   }
   if (%this-->normalTextureSizeTextEdit.getText() $= "" || mIsPow2(%this-->normalTextureSizeTextEdit.getText())) {
      $Terrain::NormalTextureSize = %this-->normalTextureSizeTextEdit.getText();
   }
   if (%this-->ormTextureSizeTextEdit.getText() $= "" || mIsPow2(%this-->ormTextureSizeTextEdit.getText())) {
      $Terrain::OrmTextureSize = %this-->ormTextureSizeTextEdit.getText();
   }
   
   ETerrainEditor.getActiveTerrain().getClientObject().setMaterialsDirty();
}


function TerrainTextureSettingsDlg::validate( %this ) {
   if (%this-->detailTextureSizeTextEdit.getText() !$= "" && !mIsPow2(%this-->detailTextureSizeTextEdit.getText())) {
      toolsMessageBoxOK("Detail Texture Error!", "Detail texture resolution must be a power of 2");
      return false;
   }
   if (%this-->macroTextureSizeTextEdit.getText() !$= "" && !mIsPow2(%this-->macroTextureSizeTextEdit.getText())) {
      toolsMessageBoxOK("Macro Texture Error!", "Macro texture resolution must be a power of 2");
      return false;
   }
   if (%this-->normalTextureSizeTextEdit.getText() !$= "" && !mIsPow2(%this-->normalTextureSizeTextEdit.getText())) {
      toolsMessageBoxOK("Normal Texture Error!", "Normal texture resolution must be a power of 2");
      return false;
   }
   if (%this-->ormTextureSizeTextEdit.getText() !$= "" && !mIsPow2(%this-->ormTextureSizeTextEdit.getText())) {
      toolsMessageBoxOK("ORM Texture Error!", "ORM texture resolution must be a power of 2");
      return false;
   }
   
   return true;
}


function TerrainTextureSettingsDlg::cancel( %this ) {
   $Terrain::LerpBlend = ProjectSettings.value("Terrain/LerpBlend");
   $Terrain::BlendDepth = ProjectSettings.value("Terrain/BlendDepth");
   
   $Terrain::DetailTextureFormat = ProjectSettings.value("Terrain/DetailTextureFormat");
   $Terrain::MacroTextureFormat = ProjectSettings.value("Terrain/MacroTextureFormat");
   $Terrain::NormalTextureFormat = ProjectSettings.value("Terrain/NormalTextureFormat");
   $Terrain::OrmTextureFormat = ProjectSettings.value("Terrain/OrmTextureFormat");
   
   $Terrain::DetailTextureSize = ProjectSettings.value("Terrain/DetailTextureSize");
   $Terrain::MacroTextureSize = ProjectSettings.value("Terrain/MacroTextureSize");
   $Terrain::NormalTextureSize = ProjectSettings.value("Terrain/NormalTextureSize");
   $Terrain::OrmTextureSize = ProjectSettings.value("Terrain/OrmTextureSize");
   
   ETerrainEditor.getActiveTerrain().getClientObject().setMaterialsDirty();
   Canvas.popDialog(%this);
}

function TerrainTextureSettingsDlg::applyAndSave( %this ) {
   if (!%this.validate()) {
      return;
   }
   %this.apply();
   
   ProjectSettings.setValue("Terrain/LerpBlend", $Terrain::LerpBlend);
   ProjectSettings.setValue("Terrain/BlendDepth", $Terrain::BlendDepth);

   ProjectSettings.setValue("Terrain/DetailTextureFormat", $Terrain::DetailTextureFormat);
   ProjectSettings.setValue("Terrain/MacroTextureFormat", $Terrain::MacroTextureFormat);
   ProjectSettings.setValue("Terrain/NormalTextureFormat", $Terrain::NormalTextureFormat);
   ProjectSettings.setValue("Terrain/OrmTextureFormat", $Terrain::OrmTextureFormat);
   
   ProjectSettings.setValue("Terrain/DetailTextureSize", $Terrain::DetailTextureSize);
   ProjectSettings.setValue("Terrain/MacroTextureSize", $Terrain::MacroTextureSize);
   ProjectSettings.setValue("Terrain/NormalTextureSize", $Terrain::NormalTextureSize);
   ProjectSettings.setValue("Terrain/OrmTextureSize", $Terrain::OrmTextureSize);
   
   ProjectSettings.write();
   
   Canvas.popDialog(%this);
}