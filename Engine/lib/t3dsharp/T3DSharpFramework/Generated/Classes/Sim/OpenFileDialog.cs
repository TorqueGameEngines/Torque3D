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
    /// <summary>Derived from FileDialog, this class is responsible for opening a file browser with the intention of opening a file.</summary>
    /// <description>
    /// The core usage of this dialog is to locate a file in the OS and return the path and name. This does not handle the actual file parsing or data manipulation. That functionality is left up to the FileObject class.
    /// </description>
    /// <code>
    /// // Create a dialog dedicated to opening files
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
    /// 
    ///  // Cleanup
    ///  %openFileDlg.delete();
    /// </code>
    /// <remarks> FileDialog and its related classes are only availble in a Tools build of Torque.
    /// 
    /// </remarks>
    /// <see cref="FileDialog" />
    /// <see cref="SaveFileDialog" />
    /// <see cref="FileObject" />
    public unsafe class OpenFileDialog : FileDialog {
        public OpenFileDialog(bool pRegister = false) 
            : base(pRegister) {
        }
        
        public OpenFileDialog(string pName, bool pRegister) 
            : this(false) {
            Name = pName;
            if (pRegister) {
                RegisterObject();
            }
        }
        
        public OpenFileDialog(string pName) 
            : this(pName, false) {
        }
        
        public OpenFileDialog(string pName, string pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(Engine.Sim.FindObject<SimObject>(pParent));
        }
        
        public OpenFileDialog(string pName, SimObject pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(pParent);
        }
        
        public OpenFileDialog(SimObject pObj) 
            : base(pObj) {
        }
        
        public OpenFileDialog(IntPtr pObj) 
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
                                "fnOpenFileDialog_staticGetType"), typeof(_StaticGetType));
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
                                "fnOpenFileDialog_create"), typeof(_Create));
                }
                
                return _CreateFunc;
            }
        }
        #endregion

        /// <description>
        /// Get the type info object for the OpenFileDialog class.
        /// </description>
        /// <returns>The type info object for OpenFileDialog</returns>
        public static EngineTypeInfo StaticGetType() {
             InternalUnsafeMethods.StaticGetType__Args _args = new InternalUnsafeMethods.StaticGetType__Args() {
             };
             IntPtr _engineResult = InternalUnsafeMethods.StaticGetType()(_args);
             return new EngineTypeInfo(_engineResult);
        }


        /// <value>
        /// <description>
        /// True/False whether the file returned must exist or not
        /// </description>
        /// </value>
        public bool MustExist {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("MustExist"));
            set => SetFieldValue("MustExist", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// True/False whether multiple files may be selected and returned or not
        /// </description>
        /// </value>
        public bool MultipleFiles {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("MultipleFiles"));
            set => SetFieldValue("MultipleFiles", GenericMarshal.ToString(value));
        }
    }
}