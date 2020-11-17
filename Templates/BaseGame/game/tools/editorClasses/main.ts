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

function initializeEditorClasses()
{
   echo(" % - Initializing Tools Base");


   $EditorClassesGroup = "EditorClassesCleanup";
   if( !isObject( $EditorClassesGroup ) )
      new SimGroup( $EditorClassesGroup );


   //-----------------------------------------------------------------------------
   // Load Editor Profiles
   //-----------------------------------------------------------------------------
   
   exec("./scripts/fileLoader.ed.ts");   
   
   loadDirectory( expandFilename("./gui/panels") );
   

   //-----------------------------------------------------------------------------
   // Setup Preferences Manager
   //-----------------------------------------------------------------------------
   
   exec("./scripts/preferencesManager.ed.ts");
   initPreferencesManager();
   
   //-----------------------------------------------------------------------------
   // Load Form Managers
   //-----------------------------------------------------------------------------
   
   exec("./scripts/guiFormLibraryManager.ed.ts");
   exec("./scripts/guiFormContentManager.ed.ts");
   exec("./scripts/guiFormReferenceManager.ed.ts");
   exec("./scripts/guiFormLayoutManager.ed.ts");
   exec("./scripts/guiFormMessageManager.ed.ts");
   exec("./scripts/expandos.ed.ts");
   exec("./scripts/utility.ed.ts");
   setupBaseExpandos();

   // User Display
   exec("./scripts/contextPopup.ed.ts");

   // Project Support   
   exec("./scripts/projects/projectEvents.ed.ts");
   exec("./scripts/projects/projectInternalInterface.ed.ts");
   
   // Input
   exec("./scripts/input/inputEvents.ed.ts");
   exec("./scripts/input/dragDropEvents.ed.ts");
   exec("./scripts/input/applicationEvents.ed.ts");
   
   // Form Class
   exec("./scripts/guiFormClass.ed.ts");
   exec("./scripts/guiClasses/guiThumbnailPopup.ed.ts");
   exec("./scripts/guiClasses/guiThumbnail.ed.ts");
   exec("./scripts/RSSNews/RSSFeedScript.ed.ts");

   loadDirectory( expandFilename("./scripts/core") );
   loadDirectory( expandFilename("./scripts/platform") );
}

function destroyEditorClasses()
{
}
