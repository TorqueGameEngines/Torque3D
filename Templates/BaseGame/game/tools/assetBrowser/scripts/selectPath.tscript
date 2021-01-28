function SelectAssetPath::onWake(%this)
{
}

//SelectAssetPath.showDialog();
function SelectAssetPath::showDialog(%this, %startingPath, %callback)
{
   if(!isObject(%this.dirHandler))
      %this.dirHandler = makedirectoryHandler(SelectAssetPath-->folderTree, "Core,Tools,cache,shaderCache", ""); 
      
   SelectAssetPath-->folderTree.clear();

   SelectAssetPath-->folderTree.buildIconTable( ":tools/classIcons/Prefab:tools/classIcons/Prefab" @
                                             ":tools/classIcons/SimSet:tools/classIcons/SimSet");
      
   %this.dirHandler.currentPath = %startingPath;
   %this.callback = %callback;
   
   %dataItem = SelectAssetPath-->folderTree.insertItem(0, "Data");
   %this.dirHandler.loadFolders("Data", %dataItem);
   
   %this.dirHandler.expandTreeToAddress(%startingPath);
   %id = %this.dirHandler.getFolderTreeItemFromAddress(%startingPath);
   %this.dirHandler.treeCtrl.clearSelection();
   %this.dirHandler.treeCtrl.selectItem(%id);
   
   Canvas.pushDialog(SelectAssetPath);
}

function selectAssetPathTree::onSelect(%this, %itemId)
{
	if(%itemId == 1)
		//can't select root
		return;
		
   SelectAssetPath.selectedTreeItem = %itemId;
}


function SelectAssetPath::selectPath(%this)
{
   //do callback
   %selectedId = %this.selectedTreeItem;
   %selectedPath = %this-->folderTree.getItemValue(%selectedId) @ "/" @ %this-->folderTree.getItemText(%selectedId);
   
   if(%this.callback !$= "")
   {
      eval( "" @ %this.callback @ "(\"" @ %selectedPath  @ "\");");   
   }
   
   Canvas.popDialog(SelectAssetPath);
}

function SelectAssetPath::newFolder(%this)
{   
   AssetBrowser_newFolderNameTxt.text = "NewFolder";
   Canvas.pushDialog(AssetBrowser_newFolder);
}