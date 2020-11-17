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
    /// <summary>Derived from FileDialog, this class is responsible for opening a file browser with the intention of saving a file.</summary>
    /// <description>
    /// The core usage of this dialog is to locate a file in the OS and return the path and name. This does not handle the actual file writing or data manipulation. That functionality is left up to the FileObject class.
    /// </description>
    /// <code>
    /// // Create a dialog dedicated to opening file
    ///  %saveFileDlg = new SaveFileDialog()
    ///  {
    ///     // Only allow for saving of COLLADA files
    ///     Filters        = "COLLADA Files (*.dae)|*.dae|";
    /// 
    ///     // Default save path to where the WorldEditor last saved
    ///     DefaultPath    = $pref::WorldEditor::LastPath;
    /// 
    ///     // No default file specified
    ///     DefaultFile    = "";
    /// 
    ///     // Do not allow the user to change to a new directory
    ///     ChangePath     = false;
    /// 
    ///     // Prompt the user if they are going to overwrite an existing file
    ///     OverwritePrompt   = true;
    ///  };
    /// 
    ///  // Launch the save file dialog
    ///  %saveFileDlg.Execute();
    /// 
    ///  if ( %result )
    ///  {
    ///     %seletedFile = %openFileDlg.file;
    ///  }
    ///  else
    ///  {
    ///     %selectedFile = "";
    ///  }
    /// 
    ///  // Cleanup
    ///  %saveFileDlg.delete();
    /// </code>
    /// <remarks> FileDialog and its related classes are only availble in a Tools build of Torque.
    /// 
    /// </remarks>
    /// <see cref="FileDialog" />
    /// <see cref="OpenFileDialog" />
    /// <see cref="FileObject" />
    public unsafe class SaveFileDialog : FileDialog {
        public SaveFileDialog(bool pRegister = false) 
            : base(pRegister) {
        }
        
        public SaveFileDialog(string pName, bool pRegister) 
            : this(false) {
            Name = pName;
            if (pRegister) {
                RegisterObject();
            }
        }
        
        public SaveFileDialog(string pName) 
            : this(pName, false) {
        }
        
        public SaveFileDialog(string pName, string pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(Engine.Sim.FindObject<SimObject>(pParent));
        }
        
        public SaveFileDialog(string pName, SimObject pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(pParent);
        }
        
        public SaveFileDialog(SimObject pObj) 
            : base(pObj) {
        }
        
        public SaveFileDialog(IntPtr pObj) 
            : base(pObj) {
        }
        
		protected override void CreateObjectPtr()
		{
			ObjectPtr = InternalUnsafeMethods.Create()(new InternalUnsafeMethods.Create__Args());
		}

        #region UnsafeNativeMethods
        new internal struct InternalUnsafeMethods {
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
                                "fnSaveFileDialog_staticGetType"), typeof(_StaticGetType));
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
                                "fnSaveFileDialog_create"), typeof(_Create));
                }
                
                return _CreateFunc;
            }
        }
        #endregion

        /// <description>
        /// Get the type info object for the SaveFileDialog class.
        /// </description>
        /// <returns>The type info object for SaveFileDialog</returns>
        public static EngineTypeInfo StaticGetType() {
             InternalUnsafeMethods.StaticGetType__Args _args = new InternalUnsafeMethods.StaticGetType__Args() {
             };
             IntPtr _engineResult = InternalUnsafeMethods.StaticGetType()(_args);
             return new EngineTypeInfo(_engineResult);
        }


        /// <value>
        /// <description>
        /// True/False whether the dialog should prompt before accepting an existing file name
        /// </description>
        /// </value>
        public bool OverwritePrompt {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("OverwritePrompt"));
            set => SetFieldValue("OverwritePrompt", GenericMarshal.ToString(value));
        }
    }
}