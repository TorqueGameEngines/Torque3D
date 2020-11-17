function MainEditor::onCreate( %this )
{
   echo("\n--------- Initializing MainEditor ---------");
   
   //exec("tools/gui/profiles.ed.cs");
   //exec("./scripts/GuiProfiles.cs");

   exec("./guis/MainEditorWindow.gui");
   
   //exec("./scripts/newEditorGui.cs");
   
   $UsePanelLayout = false;
   $AssetBrowserPanelState = true;
   $AssetBrowserPanelSplit = 0;
   $InspectorPanelState = true;
   $InspectorPanelSplit = 0;
   $ToolsPanelState = true;
   $ToolsPanelSplit = 0;
}

function MainEditor::onDestroy( %this )
{
}

function NewEditorGui::addNewEditorTab(%this, %editorName)
{
   %editorTab = new GuiTabPageCtrl()
   {
      Profile = "ToolsGuiEditorTabPage";
      position = "0 0";
      extent = Editor_MainViewTabBook.extent;
      AnchorTop = "1";
      AnchorBottom = "0";
      AnchorLeft = "1";
      AnchorRight = "0";
      horizSizing = "width";
      vertSizing = "height";
      text = %editorName;
   };
   
   Editor_MainViewTabBook.add(%editorTab);
   
   return %editorTab;
}

function togglePanelLayout()
{
   $UsePanelLayout = !$UsePanelLayout;
   
   if($UsePanelLayout)
   {
      EditorGui.add(NewEditorGui);
      
      //Nudge us down so we show the toolbar
      NewEditorGui.resize(0, EditorGuiToolbar.extent.y, EditorGui.extent.x, EditorGui.extent.y - EditorGuiToolbar.extent.y - EditorGuiStatusBar.extent.y);
      
      %mainEditViewTitle = "Level - " @ getScene(0).getName();
      %mainEditViewCtrl = NewEditorGui.addNewEditorTab(%mainEditViewTitle);
      
      %mainEditViewCtrl.add(EWorldEditor);
      EWorldEditor.position = "0 24";
      EWorldEditor.extent = %mainEditViewCtrl.extent.x SPC %mainEditViewCtrl.extent.y - 24;
      
      Editor_AssetBrowserPanel.add(AssetBrowser);
      AssetBrowser.resize(0,0, Editor_AssetBrowserPanel.extent.x, Editor_AssetBrowserPanel.extent.y);
      AssetBrowser.horizSizing = "width";
      AssetBrowser.vertSizing = "height";
      AssetBrowserWindow.resize(0,0, AssetBrowser.extent.x, AssetBrowser.extent.y);
      AssetBrowserWindow.horizSizing = "width";
      AssetBrowserWindow.vertSizing = "height";
      AssetBrowserWindow.canClose = false;
      AssetBrowserWindow.canCollapse = false;
      AssetBrowserWindow.canMaximize = false;
      AssetBrowserWindow.canMinimize = false;
      AssetBrowserWindow.canMove = false;
      AssetBrowserWindow.resizeWidth = false;
      AssetBrowserWindow.resizeHeight = false;
      
      //Prep it
      AssetBrowser.loadFilters();
     
      Editor_SceneTreePanel.add(EWTreeWindow);
      EWTreeWindow.resize(0,0, Editor_SceneTreePanel.extent.x, Editor_SceneTreePanel.extent.y);
      EWTreeWindow.horizSizing = "width";
      EWTreeWindow.vertSizing = "height";
      EWTreeWindow.canClose = false;
      EWTreeWindow.canCollapse = false;
      EWTreeWindow.canMaximize = false;
      EWTreeWindow.canMinimize = false;
      EWTreeWindow.canMove = false;
      EWTreeWindow.resizeWidth = false;
      EWTreeWindow.resizeHeight = false;
      
      if(!isObject(Scenes))
      {
         $scenesRootGroup = new SimGroup(Scenes);
      
         $scenesRootGroup.add(getScene(0));
      }
      
      EditorTree.open($scenesRootGroup,true);

      Editor_PropertiesPanel.add(EWInspectorWindow);
      EWInspectorWindow.resize(0,0, Editor_PropertiesPanel.extent.x, Editor_PropertiesPanel.extent.y);
      EWInspectorWindow.horizSizing = "width";
      EWInspectorWindow.vertSizing = "height";
      EWInspectorWindow.canClose = false;
      EWInspectorWindow.canCollapse = false;
      EWInspectorWindow.canMaximize = false;
      EWInspectorWindow.canMinimize = false;
      EWInspectorWindow.canMove = false;
      EWInspectorWindow.resizeWidth = false;
      EWInspectorWindow.resizeHeight = false;
   }
   else
   {
      EditorGui.remove(NewEditorGui);
      
      EditorGui.add(EWorldEditor);
      
      EditorGui.add(AssetBrowser);
      AssetBrowserWindow.canClose = false;
      AssetBrowserWindow.canCollapse = false;
      AssetBrowserWindow.canMaximize = false;
      AssetBrowserWindow.canMinimize = false;
      AssetBrowserWindow.canMove = false;
      
      EditorGui.add(EWTreeWindow);
      
      EditorGui.add(EWInspectorWindow);
   }
}

function Editor_AssetBrowserButton::onClick(%this)
{
   $AssetBrowserPanelState = !$AssetBrowserPanelState;
   
   //If we're collapsing
   if(!$AssetBrowserPanelState)
   {
      //Store the original
      $AssetBrowserPanelSplit = Editor_MainViewSplit.splitPoint.y;
      
      //collapse it
      Editor_MainViewSplit.setSplitPoint(Editor_MainViewSplit.splitPoint.x SPC  Editor_MainViewSplit.extent.y - Editor_MainViewSplit.splitterSize);
   }
   else
   {
      //restore the original
      Editor_MainViewSplit.setSplitPoint(Editor_MainViewSplit.splitPoint.x SPC $AssetBrowserPanelSplit);
   }
}

function Editor_InspectorSidebarButton::onClick(%this)
{
   $InspectorPanelState = !$InspectorPanelState;
   
   //If we're collapsing
   if(!$InspectorPanelState)
   {
      //Store the original
      $InspectorPanelSplit = NewEditorGuiLayout.splitPoint.x;
      
      //collapse it
      NewEditorGuiLayout.setSplitPoint(NewEditorGui.extent.x - NewEditorGuiLayout.splitterSize SPC NewEditorGuiLayout.splitPoint.y);
   }
   else
   {
      //restore the original
      NewEditorGuiLayout.setSplitPoint($InspectorPanelSplit SPC NewEditorGuiLayout.splitPoint.y);
   }
}

function Editor_ToolsSidebarButton::onClick(%this)
{
   $ToolsPanelState = !$ToolsPanelState;
   
   //If we're collapsing
   if(!$ToolsPanelState)
   {
      //Store the original
      $ToolsPanelSplit = Editor_ToolsMainSplit.splitPoint.x;
      
      //collapse it
      Editor_ToolsMainSplit.setSplitPoint(Editor_ToolsMainSplit.splitterSize SPC Editor_ToolsMainSplit.splitPoint.y);
   }
   else
   {
      //restore the original
      Editor_ToolsMainSplit.setSplitPoint($ToolsPanelSplit SPC Editor_ToolsMainSplit.splitPoint.y);
   }
}

function Editor_VisibilityOptionsButton::onClick(%this)
{
   if ( EVisibility.visible  )
   {
      EVisibility.setVisible(false);
      //visibilityToggleBtn.setStateOn(0);
   }
   else
   {
      EVisibility.setVisible(true);
      //visibilityToggleBtn.setStateOn(1);
      EVisibility.setExtent("200 540");
   }  
}