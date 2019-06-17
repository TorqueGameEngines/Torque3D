//-----------------------------------------------------------------------------
// Torque Game Engine
//
// Copyright (c) 2001 GarageGames.Com
// Portions Copyright (c) 2001 by Sierra Online, Inc.
//-----------------------------------------------------------------------------

function initRPGDialogEditor()
{
   exec("~/scripts/RPGDialogEditor/ui/MainEditorScreenGui.gui");
   exec("~/scripts/RPGDialogEditor/ui/EditQuestionGui.gui");
   exec("~/scripts/RPGDialogEditor/ui/EditAnswerGui.gui");
   exec("~/scripts/RPGDialogEditor/ui/NewScriptPopup.gui");
   exec("~/scripts/RPGDialogEditor/ui/SetPathsPopup.gui");
   exec("~/scripts/RPGDialogEditor/ui/EditorOpeningGui.gui");

   exec("~/scripts/RPGDialogEditor/defaults.cs");
   exec("~/scripts/RPGDialogEditor/prefs.cs");
   exec("~/scripts/RPGDialogEditor/editorMain.cs");
   
   PopulateActionList();
   PopulateQuestionOptionsList();
   GlobalActionMap.bind(keyboard, "f5", toggleRPGDialogEditor);
}

function openRPGDialogEditor()
{
   $GuiBeforeRPGDialogEditor=Canvas.getContent();
   if(TextScript.getvalue()$="Current Q. Script:")
      Canvas.setContent(EditorOpeningGui);
   else
      Canvas.setContent(MainEditorScreenGui);
   Canvas.setCursor("DefaultCursor");
}

function closeRPGDialogEditor()
{
   Canvas.setContent($GuiBeforeRPGDialogEditor);
   Canvas.setCursor("DefaultCursor");
}


function toggleRPGDialogEditor(%val)
{
   if (%val)
   {
      if (Canvas.getContent() == MainEditorScreenGui.getId() ||
          Canvas.getContent() == EditQuestionGui.getId() ||
          Canvas.getContent() == EditAnswerGui.getId() ||
          Canvas.getContent() == EditorOpeningGui.getId())
         closeRPGDialogEditor();
      else
         openRPGDialogEditor();
   }
}


