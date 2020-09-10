function makedirectoryHandler(%targetTree, %folderExclusionList, %searchFilter)
{
   %newHandler = new ScriptObject()
   {
      class = "directoryHandler";
   };
   
   %newHandler.currentAddress = "";
   %newHandler.treeCtrl = %targetTree;
   %newHandler.folderExclusionList = %folderExclusionList;
   %newHandler.searchFilter = %searchFilter;
   
   %newHandler.prevHistoryList = new ArrayObject();
   %newHandler.foreHistoryList = new ArrayObject();
   
   return %newHandler;
}

function directoryHandler::loadFolders(%this, %path, %parentId)
{
   %modulesList = ModuleDatabase.findModules();
   
   //utilize home dir project setting here
   %paths = getDirectoryList(%path);
   for(%i=0; %i < getFieldCount(%paths); %i++)
   {
      %childPath = getField(%paths, %i);
      
      %fullChildPath = makeFullPath(%path @ "/" @ %childPath);
      
      %folderCount = getTokenCount(%childPath, "/");
      
      for(%f=0; %f < %folderCount; %f++)
      {
         %folderName = getToken(%childPath, "/", %f);
         
         %parentName = %this.treeCtrl.getItemText(%parentId);
         
         //we don't need to display the shadercache folder
         if(%parentName $= "Data" && (%folderName $= "shaderCache" || %folderName $= "cache"))
            continue;
            
         if(%folderName $= ".git")
            continue;
         
         %iconIdx = 3;
         
         //Lets see if any modules match our current path)
         for(%m=0; %m < getWordCount(%modulesList); %m++)
         {
            %moduleDef = getWord(%modulesList, %m);
            
            if(%moduleDef.modulePath $= %fullChildPath)
            {
               %iconIdx = 1;
               break;
            }
         }
         
         //if(ModuleDatabase.findModule(%folderName) !$= "")
         //   %iconIdx = 1;
         
         %searchFoldersText = %this.searchFilter;
         if(%searchFoldersText !$= "")
         {
            if(strstr(strlwr(%folderName), strlwr(%searchFoldersText)) != -1)
            {
               %folderID = %this.treeCtrl.insertItem(%parentId, %folderName, %path, "", %iconIdx, %iconIdx+1);
         
               %this.loadFolders(%path @ "/" @ %folderName, %folderID);  
            }
         }
         else
         {
            %folderID = %this.treeCtrl.insertItem(%parentId, %folderName, %path, "", %iconIdx, %iconIdx);
         
            %this.loadFolders(%path @ "/" @ %folderName, %folderID);
         }
      }
   }
}

function directoryHandler::navigateTo(%this, %address, %historyNav, %selectionNav)
{
   //Don't bother navigating if it's to the place we already are
   if(%this.currentAddress $= %address)
      return;
      
   //clear the breadcrumb bar
   AssetBrowser_BreadcrumbBar.clear();
   
   //break down the address
   %folderCount = getTokenCount(%address, "/");
      
   /*%rebuiltPath = "";
   for(%f=0; %f < %folderCount; %f++)
   {
      %folderName = getToken(%address, "/", %f);
      
      %rebuiltPath = %f == 0 ? %folderName : %rebuiltPath @ "/" @ %folderName;
      
      %folderNavButton = new GuiButtonCtrl()
      {
         profile = ToolsGuiButtonProfile;
         text = %folderName;
         command = "AssetBrowser.navigateTo(\"" @ %rebuiltPath @ "\");";
         extent = "100" SPC AssetBrowser_BreadcrumbBar.extent.y;
      };
      
      AssetBrowser_BreadcrumbBar.add(%folderNavButton);
      
      if(%f != %folderCount-1)
      {
         %folderSpacerButton = new GuiBitmapButtonCtrl()
         {
            profile = ToolsGuiButtonProfile;
            bitmap = "tools/gui/images/rightArrowWhite";
            bitmapMode = "Centered";
            extent = "25" SPC AssetBrowser_BreadcrumbBar.extent.y;
            //command = "AssetBrowser.navigateTo(\"" @ %rebuiltPath @ "\");";
         };
         
         AssetBrowser_BreadcrumbBar.add(%folderSpacerButton);
      }
   }*/

   //find our folder tree and action on it tree
   %folderId = %this.getFolderTreeItemFromAddress(%address);

   %this.oldAddress = %this.currentAddress;   
   %this.currentAddress = %address;
   %this.selectedItem = %folderId;
   
   //This lets us update the tree selection if we didn't get here because of that
   if(%selectionNav $= "")
   {
      %this.treeCtrl.clearSelection();
      %this.treeCtrl.selectItem(%folderId);
   }
   
   //remove any history records that are 'newer' than this one
   if(%historyNav $= "")
   {
      %this.foreHistoryList.empty();  
      
      if(%this.oldAddress !$= "") 
         %this.prevHistoryList.push_front(%this.oldAddress);
   }
   
   %this.treeCtrl.buildVisibleTree(true);
}

function directoryHandler::navigateHistoryForward(%this)
{
   if(%this.foreHistoryList.count() == 0)
      return;
      
   %newAddress = %this.foreHistoryList.getKey(0);
   %prevHistory = %this.currentAddress;
      
   %this.prevHistoryList.push_front(%prevHistory);
   %this.foreHistoryList.pop_front();
   
   %this.navigateTo(%newAddress, true);
}

function directoryHandler::navigateHistoryBack(%this)
{
   if(%this.prevHistoryList.count() == 0)
      return;
      
   %newAddress = %this.prevHistoryList.getKey(0);
   %foreHistory = %this.currentAddress;
      
   %this.foreHistoryList.push_front(%foreHistory);
   %this.prevHistoryList.pop_front();
   
   %this.navigateTo(%newAddress, true);
}

function directoryHandler::getModuleFromAddress(%this, %address)
{
   %moduleList = ModuleDatabase.findModules();
   
   for(%i=0; %i < getWordCount(%moduleList); %i++)
   {
      %module = getWord(%moduleList, %i);
      %modulePath = makeRelativePath(%module.ModulePath);
      
      //We don't want to add stuff directly to the root core or tools modules
      if(%modulePath $= "Core" || %modulePath $= "Tools")
         continue;
         
      if(startsWith(%address, %modulePath))
      {
         return %module;
      }
   }
   /*//break down the address
   %folderCount = getTokenCount(%address, "/");
      
   for(%f=0; %f < %folderCount; %f++)
   {
      %folderName = getToken(%address, "/", %f);

      %module = ModuleDatabase.findModule(%folderName);
      if(%module !$= "")
         return %module;
   }*/
   
   return "";
}

function directoryHandler::getFolderTreeItemFromAddress(%this, %address)
{
   //break down the address
   %folderCount = getTokenCount(%address, "/");

   if(startsWith(%address, "Data/") || startsWith(%address, "Tools/") || startsWith(%address, "Core/"))
   {
      %curItem = %this.treeCtrl.findChildItemByName(1, "Modules");
   }
   else
   {
      %curItem = 1;
   }
   
   %rebuiltPath = "";
   for(%f=0; %f < %folderCount; %f++)
   {
      %folderName = getToken(%address, "/", %f);
      %curItem = %this.treeCtrl.findChildItemByName(%curItem, %folderName);
   }
   
   return %curItem;
}

function directoryHandler::expandTreeToAddress(%this, %address)
{
   //break down the address
   %folderCount = getTokenCount(%address, "/");
   %this.treeCtrl.expandItem(0);

   if(startsWith(%address, "Data/") || startsWith(%address, "Tools/") || startsWith(%address, "Core/"))
   {
      %curItem = %this.treeCtrl.findChildItemByName(1, "Modules");
   }
   else
   {
      %curItem = 1;
   }
   
   %rebuiltPath = "";
   for(%f=0; %f < %folderCount; %f++)
   {
      %folderName = getToken(%address, "/", %f);
      %curItem = %this.treeCtrl.findChildItemByName(%curItem, %folderName);
      %this.treeCtrl.expandItem(%curItem);
   }
   
   %this.treeCtrl.expandItem(0);
}

function directoryHandler::createFolder(%this, %folderPath)
{
   //make a dummy file
   %file = new FileObject();
   %file.openForWrite(%folderPath @ "/test");
   %file.close();
   
   fileDelete(%folderPath @ "/test");
}

function directoryHandler::deleteFolder(%this, %folderPath)
{
   %fullPath = makeFullPath(%folderPath);
   
   //First, wipe out any files inside the folder first
   %file = findFirstFileMultiExpr( %fullPath @ "/*.*", true);

   while( %file !$= "" )
   {      
      %success = fileDelete( %file );
      
      if(!%success)
      {
         error("doDeleteFolder - unable to delete file " @ %file);
         return;         
      }
      
      %file = findNextFileMultiExpr( %fullPath @ "/*.*" );
   }
   
   //next, walk through and delete any subfolders that may be remaining
   while(IsDirectory(%fullPath) && fileDelete(%fullPath) == 0)
   {
      //We couldn't delete the folder, so get a directory list and recurse through it, deleteing them as we go
      %paths = getDirectoryList(%fullPath);
      for(%i=0; %i < getFieldCount(%paths); %i++)
      {
         %childPath = getField(%paths, %i);
         %this.deleteFolder(%fullPath @ "/" @ %childPath);
      }
   }  
}

function directoryHandler::copyFolder(%this, %fromFolder, %toFolder)
{
   if(!isDirectory(%toFolder))
      %this.createFolder(%toFolder);
      
   %file = findFirstFileMultiExpr( %fromFolder @ "/*.*", false);

   while( %file !$= "" )
   {    
      %copiedFile = strreplace(%file, %fromFolder, %toFolder);
      
      %copiedPath = filePath(%copiedFile);
      
      if(!isDirectory(%copiedPath))
         createPath(%copiedPath);
   
      %success = pathCopy(%file, %copiedFile, false);
      if(!%success)
         error("copyProjectFolder() - failed to copy file: " @ %file);
      
      %file = findNextFileMultiExpr( %fullPath @ "/*.*" );
   }
   
   //do sub directories
   %paths = getDirectoryList(%fromFolder);
   for(%i=0; %i < getFieldCount(%paths); %i++)
   {
      %childPath = getField(%paths, %i);
         
      %this.copyFolder(%fromFolder @ %childPath @ "/", %toFolder @ %childPath @ "/");
   }
      
   return true;
}