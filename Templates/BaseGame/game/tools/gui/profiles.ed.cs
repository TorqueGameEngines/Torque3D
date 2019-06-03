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

function execEditorProfilesCS()
{
   exec("./profiles.ed.cs");   
}

$Gui::clipboardFile = expandFilename("./clipboard.gui");


if( !isObject( ToolsGuiDefaultProfile ) )
new GuiControlProfile (ToolsGuiDefaultProfile)
{
   tab = false;
   canKeyFocus = false;
   hasBitmapArray = false;
   mouseOverSelected = false;

   // fill color
   opaque = true;
   fillColor = "50 50 50";
   fillColorHL = "91 101 116";
   fillColorSEL = "91 101 116";
   fillColorNA = "255 0 255 ";

   // border color
   border = 0;
   borderColor   = "34 34 34"; 
   borderColorHL = "91 101 116";
   borderColorNA = "32 32 32"; 

   // font
   fontType = "Noto Sans";
   fontSize = 14;
   fontCharset = ANSI;

   fontColor = "215 215 215";
   fontColorHL = "215 215 215";
   fontColorNA = "215 215 215";
   fontColorSEL= "255 255 255";

   // bitmap information
   bitmap = "";
   bitmapBase = "";
   textOffset = "0 0";

   // used by guiTextControl
   modal = true;
   justify = "left";
   autoSizeWidth = false;
   autoSizeHeight = false;
   returnTab = false;
   numbersOnly = false;
   cursorColor = "215 215 215 255";

   // sounds
   //soundButtonDown = "";
   //soundButtonOver = "";
};

if( !isObject( ToolsGuiSolidDefaultProfile ) )
new GuiControlProfile (ToolsGuiSolidDefaultProfile)
{
   opaque = true;
   border = true;
   category = "Tools";
};

if( !isObject( ToolsGuiTransparentProfile ) )
new GuiControlProfile (ToolsGuiTransparentProfile)
{
   opaque = false;
   border = false;
   category = "Tools";
};

if( !isObject( ToolsGuiGroupBorderProfile ) )
new GuiControlProfile( ToolsGuiGroupBorderProfile )
{
   border = false;
   opaque = false;
   hasBitmapArray = true;
   bitmap = "./images/group-border";
   category = "Tools";
};

if( !isObject( ToolsGuiTabBorderProfile ) )
new GuiControlProfile( ToolsGuiTabBorderProfile )
{
   border = false;
   opaque = false;
   hasBitmapArray = true;
   bitmap = "./images/tab-border";
   category = "Tools";
};

if( !isObject( ToolsGuiToolTipProfile ) )
new GuiControlProfile (ToolsGuiToolTipProfile)
{
   // fill color
   fillColor = "255 255 255";

   // border color
   borderColor   = "0 0 0";

   // font
   fontType = "Noto Sans";
   fontSize = 14;
   fontColor = "24 24 24";

   category = "Tools";
};

if( !isObject( ToolsGuiModelessDialogProfile ) )
new GuiControlProfile( ToolsGuiModelessDialogProfile )
{
   modal = false;
   category = "Tools";
};

if( !isObject( ToolsGuiFrameSetProfile ) )
new GuiControlProfile (ToolsGuiFrameSetProfile)
{
   fillColor = "48 48 48";
   borderColor = "246 245 244";
   border = 1;
   opaque = true;
   border = true;
   category = "Tools";
};

if( !isObject( ToolsGuiWindowProfile ) )
new GuiControlProfile (ToolsGuiWindowProfile)
{
   opaque = false;
   border = 1;
   fillColor = EditorSettings.value("WorldEditor/Theme/windowTitleBGColor");
   fillColorHL = EditorSettings.value("WorldEditor/Theme/windowTitleBGHLColor");
   fillColorNA = EditorSettings.value("WorldEditor/Theme/windowTitleBGNAColor");
   fontColor = EditorSettings.value("WorldEditor/Theme/windowTitleFontColor");
   fontColorHL = EditorSettings.value("WorldEditor/Theme/windowTitleFontHLColor");
   bevelColorHL = "255 255 255";
   bevelColorLL = "0 0 0";
   text = "untitled";
   bitmap = "./images/window";
   textOffset = "10 4";
   hasBitmapArray = true;
   justify = "left";
   category = "Tools";
};

if( !isObject( ToolsGuiToolbarWindowProfile ) )
new GuiControlProfile(ToolsGuiToolbarWindowProfile : ToolsGuiWindowProfile)
{
      bitmap = "./images/toolbar-window";
      text = "";
      category = "Tools";
}; 

if( !isObject( ToolsGuiWindowCollapseProfile ) )
new GuiControlProfile (ToolsGuiWindowCollapseProfile : ToolsGuiWindowProfile)
{
   category = "Tools";
};

if( !isObject( ToolsGuiTextProfile ) )
new GuiControlProfile (ToolsGuiTextProfile)
{
   justify = "left";
   fontColor = "185 185 185";
   category = "Tools";
};

if( !isObject( ToolsGuiTextBoldCenterProfile ) )
new GuiControlProfile (ToolsGuiTextBoldCenterProfile : ToolsGuiTextProfile)
{
   fontColor = "165 165 165";
   fontType = "Noto Sans Bold";
   fontSize = 16;
   justify = "center";
   category = "Tools";
};

if( !isObject( ToolsGuiTextRightProfile ) )
new GuiControlProfile (ToolsGuiTextRightProfile : ToolsGuiTextProfile)
{
   justify = "right";
   category = "Tools";
};

if( !isObject( ToolsGuiTextCenterProfile ) )
new GuiControlProfile (ToolsGuiTextCenterProfile : ToolsGuiTextProfile)
{
   justify = "center";
   category = "Tools";
};

if( !isObject( ToolsGuiInspectorTitleTextProfile ) )
new GuiControlProfile (ToolsGuiInspectorTitleTextProfile)
{
   fontColor = "100 100 100";
   category = "Tools";
};

if( !isObject( ToolsGuiAutoSizeTextProfile ) )
new GuiControlProfile (ToolsGuiAutoSizeTextProfile)
{
   fontColor = "215 215 215";
   autoSizeWidth = true;
   autoSizeHeight = true;   
   category = "Tools";
};

if( !isObject( ToolsGuiMLTextProfile ) )
new GuiControlProfile( ToolsGuiMLTextProfile )
{
   fontColorLink = "100 100 100";
   fontColorLinkHL = "255 255 255";
   autoSizeWidth = true;
   autoSizeHeight = true;  
   border = false;
   category = "Tools";
};

if( !isObject( ToolsGuiTextArrayProfile ) )
new GuiControlProfile( ToolsGuiTextArrayProfile : ToolsGuiTextProfile )
{
   fontColor = "165 165 165";
   fontColorHL = "215 215 215";
   fontColorSEL = "215 215 215";
   fillColor = "200 200 200";
   fillColorHL = "228 228 235";
   fillColorSEL = "200 200 200";
   border = false;
   category = "Tools";
};

if( !isObject( ToolsGuiTextListProfile ) )
new GuiControlProfile( ToolsGuiTextListProfile : ToolsGuiTextProfile ) 
{
   tab = true;
   canKeyFocus = true;
   category = "Tools";
};

if( !isObject( ToolsGuiTextEditProfile ) )
new GuiControlProfile( ToolsGuiTextEditProfile )
{
   opaque = true;
   bitmap = "./images/textEditFrame";
   hasBitmapArray = true; 
   border = -2; // fix to display textEdit img
   //borderWidth = "1";  // fix to display textEdit img
   //borderColor = "100 100 100";
   fillColor = "42 42 42 0";
   fillColorHL = "91 101 116";
   fontColor = "215 215 215";
   fontColorHL = "115 115 115";
   fontColorSEL = "98 100 137";
   fontColorNA = "200 200 200";
   textOffset = "4 2";
   autoSizeWidth = false;
   autoSizeHeight = true;
   justify = "left";
   tab = true;
   canKeyFocus = true;   
   category = "Tools";
};

if( !isObject( ToolsGuiNumericTextEditProfile ) )
new GuiControlProfile( ToolsGuiNumericTextEditProfile : ToolsGuiTextEditProfile )
{
   numbersOnly = true;
   category = "Tools";
};

if( !isObject( ToolsGuiNumericDropSliderTextProfile ) )
new GuiControlProfile( ToolsGuiNumericDropSliderTextProfile : ToolsGuiTextEditProfile )
{
   bitmap = "./images/textEditSliderBox";
   category = "Tools";
};

if( !isObject( ToolsGuiRLProgressBitmapProfile ) )
new GuiControlProfile( ToolsGuiRLProgressBitmapProfile )
{
   border = false;
   hasBitmapArray = true;
   bitmap = "./images/rl-loadingbar";
   category = "Tools";
};

if( !isObject( ToolsGuiProgressTextProfile ) )
new GuiControlProfile( ToolsGuiProgressTextProfile )
{
   fontSize = "14";
	fontType = "Noto Sans";
   fontColor = "215 215 215";
   justify = "center";
   category = "Tools";   
};

if( !isObject( ToolsGuiButtonProfile ) )
new GuiControlProfile( ToolsGuiButtonProfile )
{
   opaque = true;
   border = true;
   fontColor = "165 165 165";
   fontColorHL = "215 215 215";
   fontColorNA = "200 200 200";
   fixedExtent = false;
   justify = "center";
   canKeyFocus = false;
	bitmap = "./images/button";
   hasBitmapArray = false;
   category = "Tools";
};

if( !isObject( ToolsGuiThumbHighlightButtonProfile ) )
new GuiControlProfile( ToolsGuiThumbHighlightButtonProfile : ToolsGuiButtonProfile )
{
   bitmap = "./images/thumbHightlightButton";
   category = "Tools";
};

if( !isObject( ToolsGuiIconButtonProfile ) )
new GuiControlProfile( ToolsGuiIconButtonProfile )
{
   opaque = true;
   border = true;
   fontColor = "165 165 165";
   fontColorHL = "215 215 215";
   fontColorNA = "200 200 200";
   fixedExtent = false;
   justify = "center";
   canKeyFocus = false;
	bitmap = "./images/iconbutton";
   hasBitmapArray = true;
   category = "Tools";
};

if( !isObject( ToolsGuiIconButtonSmallProfile ) )
new GuiControlProfile( ToolsGuiIconButtonSmallProfile : ToolsGuiIconButtonProfile )
{
   bitmap = "./images/iconbuttonsmall";
   category = "Tools";
};

if( !isObject( ToolsGuiEditorTabPage ) )
new GuiControlProfile(ToolsGuiEditorTabPage)
{
   opaque = true;
   border = false;
   fillColor = "48 48 48";
   fontColor = "215 215 215";
   fontColorHL = "150 150 150";
   borderColor = "34 34 34";
   fixedExtent = false;
   justify = "left";
   canKeyFocus = false;
   bitmap = "./images/tab";
   hasBitmapArray = true;
   category = "Tools";
};

if( !isObject( ToolsGuiCheckBoxProfile ) )
new GuiControlProfile( ToolsGuiCheckBoxProfile )
{
   opaque = false;
   fillColor = "232 232 232";
   border = false;
   borderColor = "100 100 100";
   fontSize = 14;
   fontColor = "185 185 185";
   fontColorHL = "80 80 80";
	fontColorNA = "200 200 200";
   fixedExtent = true;
   justify = "left";
   bitmap = "./images/checkbox";
   hasBitmapArray = true;
   category = "Tools";
};

if( !isObject( ToolsGuiCheckBoxListProfile ) )
new GuiControlProfile( ToolsGuiCheckBoxListProfile : ToolsGuiCheckBoxProfile)
{
   bitmap = "./images/checkbox-list";
   category = "Tools";
};

if( !isObject( ToolsGuiCheckBoxListFlipedProfile ) )
new GuiControlProfile( ToolsGuiCheckBoxListFlipedProfile : ToolsGuiCheckBoxProfile)
{
   bitmap = "./images/checkbox-list_fliped";
   category = "Tools";
};

if( !isObject( ToolsGuiInspectorCheckBoxTitleProfile ) )
new GuiControlProfile( ToolsGuiInspectorCheckBoxTitleProfile : ToolsGuiCheckBoxProfile ){
   fontColor = "100 100 100";
   category = "Tools";
};

if( !isObject( ToolsGuiRadioProfile ) )
new GuiControlProfile( ToolsGuiRadioProfile )
{
   fontSize = 14;
   fillColor = "232 232 232";
   fontColor = "185 185 185";
   fontColorHL = "80 80 80";
   fixedExtent = true;
   bitmap = "./images/radioButton";
   hasBitmapArray = true;
   category = "Tools";
};

if( !isObject( ToolsGuiScrollProfile ) )
new GuiControlProfile( ToolsGuiScrollProfile )
{
   opaque = true;
   fillColor = "48 48 48";
   fontColor = "215 215 215";
   fontColorHL = "150 150 150";
   borderColor = "34 34 34";
   border = true;
   bitmap = "./images/scrollBar";
   hasBitmapArray = true;
   category = "Tools";
};

if( !isObject( ToolsGuiOverlayProfile ) )
new GuiControlProfile( ToolsGuiOverlayProfile )
{
   opaque = true;
   fillColor = "48 48 48";
   fontColor = "215 215 215";
   fontColorHL = "255 255 255";
   fillColor = "0 0 0 100";
   category = "Tools";
};

if( !isObject( ToolsGuiSliderProfile ) )
new GuiControlProfile( ToolsGuiSliderProfile )
{
   bitmap = "./images/slider";
   category = "Tools";
};

if( !isObject( ToolsGuiSliderBoxProfile ) )
new GuiControlProfile( ToolsGuiSliderBoxProfile )
{
   bitmap = "./images/slider-w-box";
   category = "Tools";
};

if( !isObject( ToolsGuiPopupMenuItemBorder ) )
new GuiControlProfile( ToolsGuiPopupMenuItemBorder : ToolsGuiButtonProfile )
{
   opaque = true;
   border = true;
   fontColor = "215 215 215";
   fontColorHL = "215 215 215";
   fontColorNA = "255 255 255";
   fixedExtent = false;
   justify = "center";
   canKeyFocus = false;
   bitmap = "./images/button";
   category = "Tools";
};

if( !isObject( ToolsGuiPopUpMenuDefault ) )
new GuiControlProfile( ToolsGuiPopUpMenuDefault : ToolsGuiDefaultProfile )
{
   opaque = true;
   mouseOverSelected = true;
   textOffset = "3 3";
   border = 0;
   borderThickness = 0;
   fixedExtent = true;
   bitmap = "./images/scrollbar";
   hasBitmapArray = true;
   profileForChildren = ToolsGuiPopupMenuItemBorder;
   fillColor = "48 48 48";//"255 255 255";//100
   fillColorHL = "228 228 235 ";//"91 101 116";
   fillColorSEL = "98 100 137 ";//"91 101 116";
   // font color is black
   fontColorHL = "215 215 215 ";//"215 215 215";
   fontColorSEL = "255 255 255";//"215 215 215";
   borderColor = "100 100 100";
   category = "Tools";
};

if( !isObject( ToolsGuiPopUpMenuProfile ) )
new GuiControlProfile( ToolsGuiPopUpMenuProfile : ToolsGuiPopUpMenuDefault )
{
   textOffset         = "6 4";
   bitmap             = "./images/dropDown";
   hasBitmapArray     = true;
   border             = 1;
   profileForChildren = ToolsGuiPopUpMenuDefault;
   category = "Tools";
};

if( !isObject( ToolsGuiPopUpMenuTabProfile ) )
new GuiControlProfile( ToolsGuiPopUpMenuTabProfile : ToolsGuiPopUpMenuDefault )
{
   bitmap             = "./images/dropDown-tab";
   textOffset         = "6 4";
   canKeyFocus        = true;
   hasBitmapArray     = true;
   border             = 1;
   profileForChildren = ToolsGuiPopUpMenuDefault;
   category = "Tools";
};

if( !isObject( ToolsGuiPopUpMenuEditProfile ) )
new GuiControlProfile( ToolsGuiPopUpMenuEditProfile : ToolsGuiPopUpMenuDefault )
{
   textOffset         = "6 4";
   canKeyFocus        = true;
   bitmap             = "./images/dropDown";
   hasBitmapArray     = true;
   border             = 1;
   profileForChildren = ToolsGuiPopUpMenuDefault;
   category = "Tools";
};

if( !isObject( ToolsGuiListBoxProfile ) )
new GuiControlProfile( ToolsGuiListBoxProfile )
{
   fillColorHL = "100 100 100";
   fillColorNA = "150 150 150";
   fontColor = "215 215 215";
   fontColorHL = "215 215 215";
   fontColorNA = "50 50 50";
   
   tab = true;
   canKeyFocus = true;
   category = "Tools";
};

if( !isObject( ToolsGuiTabBookProfile ) )
new GuiControlProfile( ToolsGuiTabBookProfile )
{
   fillColorHL = "100 100 100";
   fillColorNA = "150 150 150";
   fontColor = "215 215 215";
   fontColorHL = "215 215 215";
   fontColorNA = "50 50 50";
   fontType = "Noto Sans";
   fontSize = 14;
   justify = "center";
   bitmap = "./images/tab";
   tabWidth = 65;
   tabHeight = 25;
   tabPosition = "Top";
   tabRotation = "Horizontal";
   textOffset = "10 0";
   tab = true;
   cankeyfocus = true;
   category = "Tools";
};

if( !isObject( ToolsGuiTabBookNoBitmapProfile ) )
new GuiControlProfile( ToolsGuiTabBookNoBitmapProfile : ToolsGuiTabBookProfile )
{
   bitmap = "";
   category = "Tools";
};

if( !isObject( ToolsGuiTabPageProfile ) )
new GuiControlProfile( ToolsGuiTabPageProfile : ToolsGuiDefaultProfile )
{
   fontType = "Noto Sans";
   fontSize = 10;
   justify = "center";
   bitmap = "./images/tab";
   opaque = false;
   fillColor = "240 239 238";
   category = "Tools";
};

if( !isObject( ToolsGuiTreeViewProfile ) )
new GuiControlProfile( ToolsGuiTreeViewProfile )
{  
   bitmap = "./images/treeView";
   autoSizeHeight = true;
   canKeyFocus = true;
   fillColor = "48 48 48"; 
   fillColorHL = "116 116 116";
   fillColorSEL = "91 101 116";
   fillColorNA = "40 40 40";
   fontColor = "215 215 215";
   fontColorHL = "240 240 240";   
   fontColorSEL= "240 240 240";
   fontColorNA = "150 150 150";
   borderColor = "34 34 34";
   borderColorHL = "34 34 34";
   fontSize = 14;   
   opaque = false;
   border = false;
   category = "Tools";
};

if( !isObject( ToolsGuiTextPadProfile ) )
new GuiControlProfile( ToolsGuiTextPadProfile )
{
   fontType = ($platform $= "macos") ? "Monaco" : "Lucida Console";
   fontSize = ($platform $= "macos") ? 13 : 12;
   tab = true;
   canKeyFocus = true;
   
   // Deviate from the Default
   opaque=true;  
   fillColor = "48 48 48";   
   border = 0;
   category = "Tools";
};

if( !isObject( ToolsGuiFormProfile ) )
new GuiControlProfile( ToolsGuiFormProfile : ToolsGuiTextProfile )
{
   opaque = false;
   border = 5;
   justify = "center";
   profileForChildren = ToolsGuiButtonProfile;
   opaque = false;
   hasBitmapArray = true;
   bitmap = "./images/button";
   category = "Tools";
};

// ----------------------------------------------------------------------------

singleton GuiControlProfile( GuiEditorClassProfile )
{
   opaque = true;
   fillColor = "232 232 232";
   border = 1;
   borderColor   = "42 42 42 140";
   borderColorHL = "127 127 127";
   fontColor = "215 215 215";
   fontColorHL = "50 50 50";
   fixedExtent = true;
   justify = "center";
   bitmap = "tools/gui/images/scrollBar";
   hasBitmapArray = true;
   category = "Editor";
};

singleton GuiControlProfile( GuiBackFillProfile )
{
   opaque = true;
   fillColor = "0 94 94";
   border = true;
   borderColor = "255 128 128";
   fontType = "Noto Sans";
   fontSize = 12;
   fontColor = "215 215 215";
   fontColorHL = "50 50 50";
   fixedExtent = true;
   justify = "center";
   category = "Editor";
};

singleton GuiControlProfile( GuiControlListPopupProfile )
{
   opaque = true;
   fillColor = "48 48 48";
   fillColorHL = "91 101 116";
   border = false;
   //borderColor = "0 0 0";
   fontColor = "215 215 215";
   fontColorHL = "240 240 240";
   fontColorNA = "50 50 50";
   textOffset = "0 2";
   autoSizeWidth = false;
   autoSizeHeight = true;
   tab = true;
   canKeyFocus = true;
   bitmap = "tools/gui/images/scrollBar";
   hasBitmapArray = true;
   category = "Editor";
};

singleton GuiControlProfile( GuiSceneGraphEditProfile )
{
   canKeyFocus = true;
   tab = true;
   category = "Editor";
};

singleton GuiControlProfile( GuiInspectorButtonProfile : ToolsGuiButtonProfile )
{
   //border = 1;
   justify = "Center";
   category = "Editor";
};

singleton GuiControlProfile( GuiInspectorSwatchButtonProfile )
{
   borderColor = "100 100 100 255";
   borderColorNA = "200 200 200 255";
   fillColorNA = "255 255 255 0";
   borderColorHL = "0 0 0 255";
   category = "Editor";
};

singleton GuiControlProfile( GuiInspectorTextEditProfile )
{
   // Transparent Background
   opaque = true;
   fillColor = "0 0 0 0";
   fillColorHL = "91 101 116";

   // No Border (Rendered by field control)
   border = false;

   tab = true;
   canKeyFocus = true;

   // font
   fontType = "Noto Sans";
   fontSize = 14;

   fontColor = "215 215 215";
   fontColorSEL = "0 140 220";
   fontColorHL = "240 240 240";
   fontColorNA = "100 100 100";
   category = "Editor";
};
singleton GuiControlProfile( GuiDropdownTextEditProfile :  ToolsGuiTextEditProfile )
{
   bitmap = "tools/gui/images/dropdown-textEdit";
   category = "Editor";
};
singleton GuiControlProfile( GuiInspectorTextEditRightProfile : GuiInspectorTextEditProfile )
{
   justify = "right";
   category = "Editor";
};

singleton GuiControlProfile( GuiInspectorGroupProfile )
{
   fontType    = "Noto Sans";
   fontSize    = "14";
   
   fontColor = "215 215 215 150";
   fontColorHL = "215 215 215 220";
   fontColorNA = "128 128 128";
   
   justify = "left";
   opaque = false;
   border = false;
  
   bitmap = "tools/editorClasses/gui/images/rollout";
   
   textOffset = "20 0";

   category = "Editor";
};

singleton GuiControlProfile( GuiInspectorFieldProfile)
{
   // fill color
   opaque = false;
   fillColor = "48 48 48";
   fillColorHL = "91 101 116";
   fillColorNA = "244 244 244";

   // border color
   border = false;
   borderColor   = "190 190 190";
   borderColorHL = "156 156 156";
   borderColorNA = "200 200 200";
   
   //bevelColorHL = "255 255 255";
   //bevelColorLL = "0 0 0";

   // font
   fontType = "Noto Sans";
   fontSize = 14;

   fontColor = "240 240 240";
   fontColorHL = "240 240 240";
   fontColorNA = "190 190 190";
   textOffset = "10 0";

   tab = true;
   canKeyFocus = true;
   category = "Editor";
};

/*
singleton GuiControlProfile( GuiInspectorMultiFieldProfile : GuiInspectorFieldProfile )
{
   opaque = true;
   fillColor = "50 50 230 30";
};
*/

singleton GuiControlProfile( GuiInspectorMultiFieldDifferentProfile : GuiInspectorFieldProfile )
{
   border = true;
   borderColor = "190 100 100";
};

singleton GuiControlProfile( GuiInspectorDynamicFieldProfile : GuiInspectorFieldProfile )
{
   // Transparent Background
   opaque = true;
   fillColor = "0 0 0 0";
   fillColorHL = "91 101 116";

   // No Border (Rendered by field control)
   border = false;

   tab = true;
   canKeyFocus = true;

   // font
   fontType = "Noto Sans";
   fontSize = 14;

   fontColor = "215 215 215";
   fontColorSEL = "0 140 220";
   fontColorHL = "240 240 240";
   fontColorNA = "100 100 100";
   category = "Editor";
};

singleton GuiControlProfile( GuiRolloutProfile )
{
   border = 0;
   borderColor = "200 200 200";
   
   fontColor = "240 240 240";
   fontColorHL = "240 240 240";
   fontColorNA = "190 190 190";
   
   hasBitmapArray = true;
   bitmap = "tools/editorClasses/gui/images/rollout";
   
   textoffset = "17 0";
   category = "Editor";
};

singleton GuiControlProfile( GuiInspectorRolloutProfile0 )
{
   // font
   fontType = "Noto Sans";
   fontSize = 14;

   fontColor = "32 32 32";
   fontColorHL = "32 100 100";
   fontColorNA = "215 215 215";
   
   justify = "left";
   opaque = false;
   
   border = 0;
   borderColor   = "190 190 190";
   borderColorHL = "156 156 156";
   borderColorNA = "64 64 64";
  
   bitmap = "tools/editorclasses/gui/images/rollout_plusminus_header";
   
   textOffset = "20 0";
   category = "Editor";
};

singleton GuiControlProfile( GuiInspectorStackProfile )
{
   opaque = false;
   border = false;
   category = "Editor";
};

singleton GuiControlProfile( GuiInspectorProfile  : GuiInspectorFieldProfile )
{
   opaque = true;
   fillColor = "42 42 42 255";
   border = 0;
   cankeyfocus = true;
   tab = true;
   category = "Editor";
};
singleton GuiControlProfile( GuiInspectorInfoProfile  : GuiInspectorFieldProfile )
{
   opaque = true;
   fillColor = "48 48 48";
   border = 0;
   cankeyfocus = true;
   tab = true;
   category = "Editor";
};

singleton GuiControlProfile( GuiInspectorBackgroundProfile : GuiInspectorFieldProfile )
{
   border = 0;
   cankeyfocus=true;
   tab = true;
   category = "Editor";
};

singleton GuiControlProfile( GuiInspectorTypeFileNameProfile )
{
   // Transparent Background
   opaque = false;

   // No Border (Rendered by field control)
   border = 0;

   tab = true;
   canKeyFocus = true;

   // font
   fontType = "Noto Sans";
   fontSize = 14;
   
   // Center text
   justify = "center";

   fontColor = "240 240 240";
   fontColorHL = "240 240 240";
   fontColorNA = "215 215 215";

   fillColor = "48 48 48";
   fillColorHL = "91 101 116";
   fillColorNA = "244 244 244";

   borderColor   = "190 190 190";
   borderColorHL = "156 156 156";
   borderColorNA = "64 64 64";
   category = "Editor";
};

singleton GuiControlProfile( GuiInspectorColumnCtrlProfile : GuiInspectorFieldProfile )
{
   opaque = true;
   fillColor = "210 210 210"; 
   border = 0;
   category = "Editor";
};

singleton GuiControlProfile( InspectorTypeEnumProfile : GuiInspectorFieldProfile )
{
   mouseOverSelected = true;
   bitmap = "tools/gui/images/scrollBar";
   hasBitmapArray = true;
   opaque=true;
   border=true;
   textOffset = "4 0";
   category = "Editor";
};

singleton GuiControlProfile( InspectorTypeCheckboxProfile : GuiInspectorFieldProfile )
{
   bitmap = "tools/gui/images/checkBox";
   hasBitmapArray = true;
   opaque=false;
   border=false;
   textOffset = "4 0";
   category = "Editor";
};

singleton GuiControlProfile( GuiToolboxButtonProfile : ToolsGuiButtonProfile )
{
   justify = "center";
   fontColor = "215 215 215";
   border = 0;
   textOffset = "0 0";   
   category = "Editor";
};

singleton GuiControlProfile( GuiDirectoryTreeProfile : ToolsGuiTreeViewProfile )
{
   fontColor = "240 240 240";
   fontColorSEL= "250 250 250 175"; 
   fillColorHL = "0 60 150";
   fontColorNA = "240 240 240";
   fontType = "Noto Sans";
   fontSize = 14;
   category = "Editor";
};

singleton GuiControlProfile( GuiDirectoryFileListProfile )
{
   fontColor = "240 240 240";
   fontColorSEL= "250 250 250 175"; 
   fillColorHL = "0 60 150";
   fontColorNA = "240 240 240";
   fontType = "Noto Sans";
   fontSize = 14;
   category = "Editor";
};

singleton GuiControlProfile( GuiDragAndDropProfile )
{
   category = "Editor";
};

singleton GuiControlProfile( GuiInspectorFieldInfoPaneProfile )
{
   opaque = false;
   fillcolor = GuiInspectorBackgroundProfile.fillColor;
   borderColor = ToolsGuiDefaultProfile.borderColor;
   border = 1;
   category = "Editor";
};

singleton GuiControlProfile( GuiInspectorFieldInfoMLTextProfile : ToolsGuiMLTextProfile )
{
   opaque = false;   
   border = 0;   
   textOffset = "5 0";
   category = "Editor";
};

singleton GuiControlProfile( GuiEditorScrollProfile )
{
   opaque = true;
   fillcolor = GuiInspectorBackgroundProfile.fillColor;
   borderColor = ToolsGuiDefaultProfile.borderColor;
   border = 1;
   bitmap = "tools/gui/images/scrollBar";
   hasBitmapArray = true;
   category = "Editor";
};

singleton GuiControlProfile( GuiCreatorIconButtonProfile )
{
   opaque = true;       
   fillColor = "225 243 252 255";
   fillColorHL = "225 243 252 0";
   fillColorNA = "225 243 252 0";
   fillColorSEL = "225 243 252 0";
      
   //tab = true;
   //canKeyFocus = true;

   fontType = "Noto Sans";
   fontSize = 14;

   fontColor = "215 215 215";
   fontColorSEL = "43 107 206";
   fontColorHL = "244 244 244";
   fontColorNA = "100 100 100";
   
   border = 1;
   borderColor   = "153 222 253 255";
   borderColorHL = "156 156 156";
   borderColorNA = "153 222 253 0";
   
   //bevelColorHL = "255 255 255";
   //bevelColorLL = "0 0 0";
   category = "Editor";
};

singleton GuiControlProfile( GuiMenuBarProfile )
{
   fillColor = "48 48 48";
   fillcolorHL = "42 42 42";
   borderColor = "30 30 30 255";
   borderColorHL = "30 30 30 255";
   fontColor = "215 215 215";
   fontColorSEL = "43 107 206";
   fontColorHL = "244 244 244";
   fontColorNA = "100 100 100";
   border = 0;
   borderThickness = 1;
   opaque = true;
   mouseOverSelected = true;
   category = "Editor";
   bitmap = "tools/gui/images/checkbox-menubar";
};
