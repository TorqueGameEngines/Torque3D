using System;
using System.Collections.Generic;
using System.Runtime.InteropServices;
using T3DSharpFramework.Engine;
using T3DSharpFramework.Engine.Util;
using T3DSharpFramework.Generated.Classes.Global;
using T3DSharpFramework.Generated.Classes.Reflection;
using T3DSharpFramework.Generated.Classes.Sim;
using T3DSharpFramework.Generated.Classes.Sim.Net;
using T3DSharpFramework.Generated.Enums.Global;
using T3DSharpFramework.Generated.Enums.Reflection;
using T3DSharpFramework.Generated.Structs.Global;
using T3DSharpFramework.Generated.Structs.Gui;
using T3DSharpFramework.Generated.Structs.Math;
using T3DSharpFramework.Interop;

namespace T3DSharpFramework.Generated.Classes.Sim {
    /// <summary>Base class responsible for displaying an OS file browser.</summary>
    /// <description>
    /// FileDialog is a platform agnostic dialog interface for querying the user for file locations. It is designed to be used through the exposed scripting interface.
    /// 
    /// FileDialog is the base class for Native File Dialog controls in Torque. It provides these basic areas of functionality:
    /// 
    ///    - Inherits from SimObject and is exposed to the scripting interface
    ///    - Provides blocking interface to allow instant return to script execution
    ///    - Simple object configuration makes practical use easy and effective
    /// 
    /// FileDialog is *NOT* intended to be used directly in script and is only exposed to script to expose generic file dialog attributes.
    /// 
    /// This base class is usable in TorqueScript, but is does not specify what functionality is intended (open or save?). Its children, OpenFileDialog and SaveFileDialog, do make use of DialogStyle flags and do make use of specific funcationality. These are the preferred classes to use
    /// 
    /// However, the FileDialog base class does contain the key properties and important method for file browing. The most important function is Execute(). This is used by both SaveFileDialog and OpenFileDialog to initiate the browser.
    /// </description>
    /// <code>
    /// // NOTE: This is not he preferred class to use, but this still works
    /// 
    /// // Create the file dialog
    /// %baseFileDialog = new FileDialog()
    /// {
    ///    // Allow browsing of all file types
    ///    filters = "*.*";
    /// 
    ///    // No default file
    ///    defaultFile = ;
    /// 
    ///    // Set default path relative to project
    ///    defaultPath = "./";
    /// 
    ///    // Set the title
    ///    title = "Durpa";
    /// 
    ///    // Allow changing of path you are browsing
    ///    changePath = true;
    /// };
    /// 
    ///  // Launch the file dialog
    ///  %baseFileDialog.Execute();
    ///  
    ///  // Don't forget to cleanup
    ///  %baseFileDialog.delete();
    /// </code>
    /// <remarks> FileDialog and its related classes are only availble in a Tools build of Torque.
    /// 
    /// </remarks>
    /// <see cref="OpenFileDialog for a practical example on opening a file" />
    /// <see cref="SaveFileDialog for a practical example of saving a file" />
    public unsafe class FileDialog : SimObject {
        public FileDialog(bool pRegister = false) 
            : base(pRegister) {
        }
        
        public FileDialog(string pName, bool pRegister) 
            : this(false) {
            Name = pName;
            if (pRegister) {
                RegisterObject();
            }
        }
        
        public FileDialog(string pName) 
            : this(pName, false) {
        }
        
        public FileDialog(string pName, string pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(Engine.Sim.FindObject<SimObject>(pParent));
        }
        
        public FileDialog(string pName, SimObject pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(pParent);
        }
        
        public FileDialog(SimObject pObj) 
            : base(pObj) {
        }
        
        public FileDialog(IntPtr pObj) 
            : base(pObj) {
        }
        
		protected override void CreateObjectPtr()
		{
			ObjectPtr = InternalUnsafeMethods.Create()(new InternalUnsafeMethods.Create__Args());
		}

        #region UnsafeNativeMethods
        new internal struct InternalUnsafeMethods {
            [StructLayout(LayoutKind.Sequential)]
            internal struct Execute__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            [return: MarshalAs(UnmanagedType.I1)]
            internal delegate bool _Execute(IntPtr _this, Execute__Args args);
            private static _Execute _ExecuteFunc;
            internal static _Execute Execute() {
                if (_ExecuteFunc == null) {
                    _ExecuteFunc =
                        (_Execute)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnFileDialog_Execute"), typeof(_Execute));
                }
                
                return _ExecuteFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct StaticGetType__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate IntPtr _StaticGetType(StaticGetType__Args args);
            private static _StaticGetType _StaticGetTypeFunc;
            internal static _StaticGetType StaticGetType() {
                if (_StaticGetTypeFunc == null) {
                    _StaticGetTypeFunc =
                        (_StaticGetType)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnFileDialog_staticGetType"), typeof(_StaticGetType));
                }
                
                return _StaticGetTypeFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct Create__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate IntPtr _Create(Create__Args args);
            private static _Create _CreateFunc;
            internal static _Create Create() {
                if (_CreateFunc == null) {
                    _CreateFunc =
                        (_Create)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnFileDialog_create"), typeof(_Create));
                }
                
                return _CreateFunc;
            }
        }
        #endregion

        /// <summary>Launches the OS file browser</summary>
        /// <description>
        /// After an Execute() call, the chosen file name and path is available in one of two areas.  If only a single file selection is permitted, the results will be stored in the
        /// </description>
        /// <paramref name="" /> fileName attribute.
        /// 
        /// If multiple file selection is permitted, the results will be stored in the <code>
        /// // NOTE: This is not he preferred class to use, but this still works
        /// 
        /// // Create the file dialog
        /// %baseFileDialog = new FileDialog()
        /// {
        ///    // Allow browsing of all file types
        ///    filters = "*.*";
        /// 
        ///    // No default file
        ///    defaultFile = ;
        /// 
        ///    // Set default path relative to project
        ///    defaultPath = "./";
        /// 
        ///    // Set the title
        ///    title = "Durpa";
        /// 
        ///    // Allow changing of path you are browsing
        ///    changePath = true;
        /// };
        /// 
        ///  // Launch the file dialog
        ///  %baseFileDialog.Execute();
        ///  
        ///  // Don't forget to cleanup
        ///  %baseFileDialog.delete();
        /// 
        /// 
        ///  // A better alternative is to use the 
        ///  // derived classes which are specific to file open and save
        /// 
        ///  // Create a dialog dedicated to opening files
        ///  %openFileDlg = new OpenFileDialog()
        ///  {
        ///     // Look for jpg image files
        ///     // First part is the descriptor|second part is the extension
        ///     Filters = "Jepg Files|*.jpg";
        ///     // Allow browsing through other folders
        ///     ChangePath = true;
        /// 
        ///     // Only allow opening of one file at a time
        ///     MultipleFiles = false;
        ///  };
        /// 
        ///  // Launch the open file dialog
        ///  %result = %openFileDlg.Execute();
        /// 
        ///  // Obtain the chosen file name and path
        ///  if ( %result )
        ///  {
        ///     %seletedFile = %openFileDlg.file;
        ///  }
        ///  else
        ///  {
        ///     %selectedFile = "";
        ///  }
        ///  // Cleanup
        ///  %openFileDlg.delete();
        /// 
        /// 
        ///  // Create a dialog dedicated to saving a file
        ///  %saveFileDlg = new SaveFileDialog()
        ///  {
        ///     // Only allow for saving of COLLADA files
        ///     Filters = "COLLADA Files (*.dae)|*.dae|";
        /// 
        ///     // Default save path to where the WorldEditor last saved
        ///     DefaultPath = $pref::WorldEditor::LastPath;
        /// 
        ///     // No default file specified
        ///     DefaultFile = "";
        /// 
        ///     // Do not allow the user to change to a new directory
        ///     ChangePath = false;
        /// 
        ///     // Prompt the user if they are going to overwrite an existing file
        ///     OverwritePrompt = true;
        ///  };
        /// 
        ///  // Launch the save file dialog
        ///  %result = %saveFileDlg.Execute();
        /// 
        ///  // Obtain the file name
        ///  %selectedFile = "";
        ///  if ( %result )
        ///     %selectedFile = %saveFileDlg.file;
        /// 
        ///  // Cleanup
        ///  %saveFileDlg.delete();
        /// </code>
        /// <returns>True if the file was selected was successfully found (opened) or declared (saved).</returns>
        public bool Execute() {
             InternalUnsafeMethods.Execute__Args _args = new InternalUnsafeMethods.Execute__Args() {
             };
             bool _engineResult = InternalUnsafeMethods.Execute()(ObjectPtr, _args);
             return _engineResult;
        }

        /// <description>
        /// Get the type info object for the FileDialog class.
        /// </description>
        /// <returns>The type info object for FileDialog</returns>
        public static EngineTypeInfo StaticGetType() {
             InternalUnsafeMethods.StaticGetType__Args _args = new InternalUnsafeMethods.StaticGetType__Args() {
             };
             IntPtr _engineResult = InternalUnsafeMethods.StaticGetType()(_args);
             return new EngineTypeInfo(_engineResult);
        }


        /// <value>
        /// <description>
        /// The default directory path when the dialog is shown.
        /// </description>
        /// </value>
        public string DefaultPath {
            get => GenericMarshal.StringTo<string>(GetFieldValue("defaultPath"));
            set => SetFieldValue("defaultPath", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// The default file path when the dialog is shown.
        /// </description>
        /// </value>
        public string DefaultFile {
            get => GenericMarshal.StringTo<string>(GetFieldValue("defaultFile"));
            set => SetFieldValue("defaultFile", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// The default file name when the dialog is shown.
        /// </description>
        /// </value>
        public string FileName {
            get => GenericMarshal.StringTo<string>(GetFieldValue("fileName"));
            set => SetFieldValue("fileName", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// The filter string for limiting the types of files visible in the dialog.  It makes use of the pipe symbol '|' as a delimiter.  For example:
        /// 
        /// 'All Files|*.*'
        /// 
        /// 'Image Files|*.png;*.jpg|Png Files|*.png|Jepg Files|*.jpg'
        /// </description>
        /// </value>
        public string Filters {
            get => GenericMarshal.StringTo<string>(GetFieldValue("filters"));
            set => SetFieldValue("filters", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// The title for the dialog.
        /// </description>
        /// </value>
        public string Title {
            get => GenericMarshal.StringTo<string>(GetFieldValue("title"));
            set => SetFieldValue("title", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// True/False whether to set the working directory to the directory returned by the dialog.
        /// </description>
        /// </value>
        public bool ChangePath {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("changePath"));
            set => SetFieldValue("changePath", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// True/False whether to the path returned is always made to be relative.
        /// </description>
        /// </value>
        public bool ForceRelativePath {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("forceRelativePath"));
            set => SetFieldValue("forceRelativePath", GenericMarshal.ToString(value));
        }
    }
}