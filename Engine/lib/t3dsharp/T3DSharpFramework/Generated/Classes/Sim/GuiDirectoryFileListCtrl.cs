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
    /// <summary>A control that displays a list of files from within a single directory in the game file system.</summary>
    /// <description>
    /// 
    /// </description>
    /// <code>
    /// new GuiDirectoryFileListCtrl()
    /// {
    ///    filePath = "art/shapes";
    ///    fileFilter = "*.dts" TAB "*.dae";
    ///    //Properties not specific to this control have been omitted from this example.
    /// };
    /// </code>
    public unsafe class GuiDirectoryFileListCtrl : GuiListBoxCtrl {
        public GuiDirectoryFileListCtrl(bool pRegister = false) 
            : base(pRegister) {
        }
        
        public GuiDirectoryFileListCtrl(string pName, bool pRegister) 
            : this(false) {
            Name = pName;
            if (pRegister) {
                RegisterObject();
            }
        }
        
        public GuiDirectoryFileListCtrl(string pName) 
            : this(pName, false) {
        }
        
        public GuiDirectoryFileListCtrl(string pName, string pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(Engine.Sim.FindObject<SimObject>(pParent));
        }
        
        public GuiDirectoryFileListCtrl(string pName, SimObject pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(pParent);
        }
        
        public GuiDirectoryFileListCtrl(SimObject pObj) 
            : base(pObj) {
        }
        
        public GuiDirectoryFileListCtrl(IntPtr pObj) 
            : base(pObj) {
        }
        
		protected override void CreateObjectPtr()
		{
			ObjectPtr = InternalUnsafeMethods.Create()(new InternalUnsafeMethods.Create__Args());
		}

        #region UnsafeNativeMethods
        new internal struct InternalUnsafeMethods {
            [StructLayout(LayoutKind.Sequential)]
            internal struct GetSelectedFile__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            
            internal delegate IntPtr _GetSelectedFile(IntPtr _this, GetSelectedFile__Args args);
            private static _GetSelectedFile _GetSelectedFileFunc;
            internal static _GetSelectedFile GetSelectedFile() {
                if (_GetSelectedFileFunc == null) {
                    _GetSelectedFileFunc =
                        (_GetSelectedFile)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnGuiDirectoryFileListCtrl_getSelectedFile"), typeof(_GetSelectedFile));
                }
                
                return _GetSelectedFileFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct GetSelectedFiles__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            
            internal delegate IntPtr _GetSelectedFiles(IntPtr _this, GetSelectedFiles__Args args);
            private static _GetSelectedFiles _GetSelectedFilesFunc;
            internal static _GetSelectedFiles GetSelectedFiles() {
                if (_GetSelectedFilesFunc == null) {
                    _GetSelectedFilesFunc =
                        (_GetSelectedFiles)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnGuiDirectoryFileListCtrl_getSelectedFiles"), typeof(_GetSelectedFiles));
                }
                
                return _GetSelectedFilesFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct SetPath__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string path;
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string filter;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            [return: MarshalAs(UnmanagedType.I1)]
            internal delegate bool _SetPath(IntPtr _this, SetPath__Args args);
            private static _SetPath _SetPathFunc;
            internal static _SetPath SetPath() {
                if (_SetPathFunc == null) {
                    _SetPathFunc =
                        (_SetPath)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnGuiDirectoryFileListCtrl_setPath"), typeof(_SetPath));
                }
                
                return _SetPathFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct Reload__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _Reload(IntPtr _this, Reload__Args args);
            private static _Reload _ReloadFunc;
            internal static _Reload Reload() {
                if (_ReloadFunc == null) {
                    _ReloadFunc =
                        (_Reload)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnGuiDirectoryFileListCtrl_reload"), typeof(_Reload));
                }
                
                return _ReloadFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct SetFilter__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string filter;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _SetFilter(IntPtr _this, SetFilter__Args args);
            private static _SetFilter _SetFilterFunc;
            internal static _SetFilter SetFilter() {
                if (_SetFilterFunc == null) {
                    _SetFilterFunc =
                        (_SetFilter)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnGuiDirectoryFileListCtrl_setFilter"), typeof(_SetFilter));
                }
                
                return _SetFilterFunc;
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
                                "fnGuiDirectoryFileListCtrl_staticGetType"), typeof(_StaticGetType));
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
                                "fnGuiDirectoryFileListCtrl_create"), typeof(_Create));
                }
                
                return _CreateFunc;
            }
        }
        #endregion

        /// <description>
        /// Get the currently selected filename.
        /// </description>
        /// <returns>The filename of the currently selected file</returns>
        public string GetSelectedFile() {
             InternalUnsafeMethods.GetSelectedFile__Args _args = new InternalUnsafeMethods.GetSelectedFile__Args() {
             };
             IntPtr _engineResult = InternalUnsafeMethods.GetSelectedFile()(ObjectPtr, _args);
             return StringMarshal.IntPtrToUtf8String(_engineResult);
        }

        /// <description>
        /// Get the list of selected files.
        /// </description>
        /// <returns>A space separated list of selected files</returns>
        public string GetSelectedFiles() {
             InternalUnsafeMethods.GetSelectedFiles__Args _args = new InternalUnsafeMethods.GetSelectedFiles__Args() {
             };
             IntPtr _engineResult = InternalUnsafeMethods.GetSelectedFiles()(ObjectPtr, _args);
             return StringMarshal.IntPtrToUtf8String(_engineResult);
        }

        /// <description>
        /// Set the search path and file filter.
        /// </description>
        /// <param name="path">Path in game directory from which to list files.</param>
        /// <param name="filter">Tab-delimited list of file name patterns. Only matched files will be displayed.</param>
        public bool SetPath(string path, string filter) {
             InternalUnsafeMethods.SetPath__Args _args = new InternalUnsafeMethods.SetPath__Args() {
                path = path,
                filter = filter,
             };
             bool _engineResult = InternalUnsafeMethods.SetPath()(ObjectPtr, _args);
             return _engineResult;
        }

        /// <description>
        /// Update the file list.
        /// </description>
        public void Reload() {
             InternalUnsafeMethods.Reload__Args _args = new InternalUnsafeMethods.Reload__Args() {
             };
             InternalUnsafeMethods.Reload()(ObjectPtr, _args);
        }

        /// <description>
        /// Set the file filter.
        /// </description>
        /// <param name="filter">Tab-delimited list of file name patterns. Only matched files will be displayed.</param>
        public void SetFilter(string filter) {
             InternalUnsafeMethods.SetFilter__Args _args = new InternalUnsafeMethods.SetFilter__Args() {
                filter = filter,
             };
             InternalUnsafeMethods.SetFilter()(ObjectPtr, _args);
        }

        /// <description>
        /// Get the type info object for the GuiDirectoryFileListCtrl class.
        /// </description>
        /// <returns>The type info object for GuiDirectoryFileListCtrl</returns>
        public static EngineTypeInfo StaticGetType() {
             InternalUnsafeMethods.StaticGetType__Args _args = new InternalUnsafeMethods.StaticGetType__Args() {
             };
             IntPtr _engineResult = InternalUnsafeMethods.StaticGetType()(_args);
             return new EngineTypeInfo(_engineResult);
        }


        /// <value>
        /// <description>
        /// Path in game directory from which to list files.
        /// </description>
        /// </value>
        public string FilePath {
            get => GenericMarshal.StringTo<string>(GetFieldValue("filePath"));
            set => SetFieldValue("filePath", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Tab-delimited list of file name patterns. Only matched files will be displayed.
        /// </description>
        /// </value>
        public string FileFilter {
            get => GenericMarshal.StringTo<string>(GetFieldValue("fileFilter"));
            set => SetFieldValue("fileFilter", GenericMarshal.ToString(value));
        }
    }
}