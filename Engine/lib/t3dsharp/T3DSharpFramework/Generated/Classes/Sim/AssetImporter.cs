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
    /// <summary>Defines properties for an AssetImportObject object.</summary>
    /// <description>
    /// 
    /// </description>
    public unsafe class AssetImporter : SimObject {
        public AssetImporter(bool pRegister = false) 
            : base(pRegister) {
        }
        
        public AssetImporter(string pName, bool pRegister) 
            : this(false) {
            Name = pName;
            if (pRegister) {
                RegisterObject();
            }
        }
        
        public AssetImporter(string pName) 
            : this(pName, false) {
        }
        
        public AssetImporter(string pName, string pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(Engine.Sim.FindObject<SimObject>(pParent));
        }
        
        public AssetImporter(string pName, SimObject pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(pParent);
        }
        
        public AssetImporter(SimObject pObj) 
            : base(pObj) {
        }
        
        public AssetImporter(IntPtr pObj) 
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
                                "fnAssetImporter_staticGetType"), typeof(_StaticGetType));
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
                                "fnAssetImporter_create"), typeof(_Create));
                }
                
                return _CreateFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct SetImportConfig__Args
            {
                internal IntPtr importConfig;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _SetImportConfig(IntPtr _this, SetImportConfig__Args args);
            private static _SetImportConfig _SetImportConfigFunc;
            internal static _SetImportConfig SetImportConfig() {
                if (_SetImportConfigFunc == null) {
                    _SetImportConfigFunc =
                        (_SetImportConfig)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnAssetImporter_setImportConfig"), typeof(_SetImportConfig));
                }
                
                return _SetImportConfigFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct DeleteImportingAsset__Args
            {
                internal IntPtr assetItem;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _DeleteImportingAsset(IntPtr _this, DeleteImportingAsset__Args args);
            private static _DeleteImportingAsset _DeleteImportingAssetFunc;
            internal static _DeleteImportingAsset DeleteImportingAsset() {
                if (_DeleteImportingAssetFunc == null) {
                    _DeleteImportingAssetFunc =
                        (_DeleteImportingAsset)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnAssetImporter_deleteImportingAsset"), typeof(_DeleteImportingAsset));
                }
                
                return _DeleteImportingAssetFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct GetAssetItemChild__Args
            {
                internal IntPtr assetItem;
                internal int index;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate IntPtr _GetAssetItemChild(IntPtr _this, GetAssetItemChild__Args args);
            private static _GetAssetItemChild _GetAssetItemChildFunc;
            internal static _GetAssetItemChild GetAssetItemChild() {
                if (_GetAssetItemChildFunc == null) {
                    _GetAssetItemChildFunc =
                        (_GetAssetItemChild)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnAssetImporter_getAssetItemChild"), typeof(_GetAssetItemChild));
                }
                
                return _GetAssetItemChildFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct GetAssetItemChildCount__Args
            {
                internal IntPtr assetItem;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate int _GetAssetItemChildCount(IntPtr _this, GetAssetItemChildCount__Args args);
            private static _GetAssetItemChildCount _GetAssetItemChildCountFunc;
            internal static _GetAssetItemChildCount GetAssetItemChildCount() {
                if (_GetAssetItemChildCountFunc == null) {
                    _GetAssetItemChildCountFunc =
                        (_GetAssetItemChildCount)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnAssetImporter_getAssetItemChildCount"), typeof(_GetAssetItemChildCount));
                }
                
                return _GetAssetItemChildCountFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct GetAssetItem__Args
            {
                internal int index;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate IntPtr _GetAssetItem(IntPtr _this, GetAssetItem__Args args);
            private static _GetAssetItem _GetAssetItemFunc;
            internal static _GetAssetItem GetAssetItem() {
                if (_GetAssetItemFunc == null) {
                    _GetAssetItemFunc =
                        (_GetAssetItem)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnAssetImporter_getAssetItem"), typeof(_GetAssetItem));
                }
                
                return _GetAssetItemFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct GetAssetItemCount__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate int _GetAssetItemCount(IntPtr _this, GetAssetItemCount__Args args);
            private static _GetAssetItemCount _GetAssetItemCountFunc;
            internal static _GetAssetItemCount GetAssetItemCount() {
                if (_GetAssetItemCountFunc == null) {
                    _GetAssetItemCountFunc =
                        (_GetAssetItemCount)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnAssetImporter_getAssetItemCount"), typeof(_GetAssetItemCount));
                }
                
                return _GetAssetItemCountFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct ImportAssets__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _ImportAssets(IntPtr _this, ImportAssets__Args args);
            private static _ImportAssets _ImportAssetsFunc;
            internal static _ImportAssets ImportAssets() {
                if (_ImportAssetsFunc == null) {
                    _ImportAssetsFunc =
                        (_ImportAssets)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnAssetImporter_importAssets"), typeof(_ImportAssets));
                }
                
                return _ImportAssetsFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct ResolveAssetItemIssues__Args
            {
                internal IntPtr assetItem;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _ResolveAssetItemIssues(IntPtr _this, ResolveAssetItemIssues__Args args);
            private static _ResolveAssetItemIssues _ResolveAssetItemIssuesFunc;
            internal static _ResolveAssetItemIssues ResolveAssetItemIssues() {
                if (_ResolveAssetItemIssuesFunc == null) {
                    _ResolveAssetItemIssuesFunc =
                        (_ResolveAssetItemIssues)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnAssetImporter_resolveAssetItemIssues"), typeof(_ResolveAssetItemIssues));
                }
                
                return _ResolveAssetItemIssuesFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct ValidateImportingAssets__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            [return: MarshalAs(UnmanagedType.I1)]
            internal delegate bool _ValidateImportingAssets(IntPtr _this, ValidateImportingAssets__Args args);
            private static _ValidateImportingAssets _ValidateImportingAssetsFunc;
            internal static _ValidateImportingAssets ValidateImportingAssets() {
                if (_ValidateImportingAssetsFunc == null) {
                    _ValidateImportingAssetsFunc =
                        (_ValidateImportingAssets)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnAssetImporter_validateImportingAssets"), typeof(_ValidateImportingAssets));
                }
                
                return _ValidateImportingAssetsFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct ProcessImportingAssets__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _ProcessImportingAssets(IntPtr _this, ProcessImportingAssets__Args args);
            private static _ProcessImportingAssets _ProcessImportingAssetsFunc;
            internal static _ProcessImportingAssets ProcessImportingAssets() {
                if (_ProcessImportingAssetsFunc == null) {
                    _ProcessImportingAssetsFunc =
                        (_ProcessImportingAssets)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnAssetImporter_processImportingAssets"), typeof(_ProcessImportingAssets));
                }
                
                return _ProcessImportingAssetsFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct AddImportingAssetItem__Args
            {
                internal IntPtr assetItem;
                internal IntPtr parentItem;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _AddImportingAssetItem(IntPtr _this, AddImportingAssetItem__Args args);
            private static _AddImportingAssetItem _AddImportingAssetItemFunc;
            internal static _AddImportingAssetItem AddImportingAssetItem() {
                if (_AddImportingAssetItemFunc == null) {
                    _AddImportingAssetItemFunc =
                        (_AddImportingAssetItem)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnAssetImporter_addImportingAssetItem"), typeof(_AddImportingAssetItem));
                }
                
                return _AddImportingAssetItemFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct AddImportingFile__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string path;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate IntPtr _AddImportingFile(IntPtr _this, AddImportingFile__Args args);
            private static _AddImportingFile _AddImportingFileFunc;
            internal static _AddImportingFile AddImportingFile() {
                if (_AddImportingFileFunc == null) {
                    _AddImportingFileFunc =
                        (_AddImportingFile)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnAssetImporter_addImportingFile"), typeof(_AddImportingFile));
                }
                
                return _AddImportingFileFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct AutoImportFile__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string path;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            
            internal delegate IntPtr _AutoImportFile(IntPtr _this, AutoImportFile__Args args);
            private static _AutoImportFile _AutoImportFileFunc;
            internal static _AutoImportFile AutoImportFile() {
                if (_AutoImportFileFunc == null) {
                    _AutoImportFileFunc =
                        (_AutoImportFile)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnAssetImporter_autoImportFile"), typeof(_AutoImportFile));
                }
                
                return _AutoImportFileFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct GetActivityLogLine__Args
            {
                internal int i;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            
            internal delegate IntPtr _GetActivityLogLine(IntPtr _this, GetActivityLogLine__Args args);
            private static _GetActivityLogLine _GetActivityLogLineFunc;
            internal static _GetActivityLogLine GetActivityLogLine() {
                if (_GetActivityLogLineFunc == null) {
                    _GetActivityLogLineFunc =
                        (_GetActivityLogLine)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnAssetImporter_getActivityLogLine"), typeof(_GetActivityLogLine));
                }
                
                return _GetActivityLogLineFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct GetActivityLogLineCount__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate int _GetActivityLogLineCount(IntPtr _this, GetActivityLogLineCount__Args args);
            private static _GetActivityLogLineCount _GetActivityLogLineCountFunc;
            internal static _GetActivityLogLineCount GetActivityLogLineCount() {
                if (_GetActivityLogLineCountFunc == null) {
                    _GetActivityLogLineCountFunc =
                        (_GetActivityLogLineCount)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnAssetImporter_getActivityLogLineCount"), typeof(_GetActivityLogLineCount));
                }
                
                return _GetActivityLogLineCountFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct DumpActivityLog__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _DumpActivityLog(IntPtr _this, DumpActivityLog__Args args);
            private static _DumpActivityLog _DumpActivityLogFunc;
            internal static _DumpActivityLog DumpActivityLog() {
                if (_DumpActivityLogFunc == null) {
                    _DumpActivityLogFunc =
                        (_DumpActivityLog)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnAssetImporter_dumpActivityLog"), typeof(_DumpActivityLog));
                }
                
                return _DumpActivityLogFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct ResetImportSession__Args
            {
                [MarshalAs(UnmanagedType.I1)]
                internal bool forceResetSession;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _ResetImportSession(IntPtr _this, ResetImportSession__Args args);
            private static _ResetImportSession _ResetImportSessionFunc;
            internal static _ResetImportSession ResetImportSession() {
                if (_ResetImportSessionFunc == null) {
                    _ResetImportSessionFunc =
                        (_ResetImportSession)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnAssetImporter_resetImportSession"), typeof(_ResetImportSession));
                }
                
                return _ResetImportSessionFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct SetTargetPath__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string path;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _SetTargetPath(IntPtr _this, SetTargetPath__Args args);
            private static _SetTargetPath _SetTargetPathFunc;
            internal static _SetTargetPath SetTargetPath() {
                if (_SetTargetPathFunc == null) {
                    _SetTargetPathFunc =
                        (_SetTargetPath)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnAssetImporter_setTargetPath"), typeof(_SetTargetPath));
                }
                
                return _SetTargetPathFunc;
            }
        }
        #endregion

        /// <description>
        /// Get the type info object for the AssetImporter class.
        /// </description>
        /// <returns>The type info object for AssetImporter</returns>
        public static EngineTypeInfo StaticGetType() {
             InternalUnsafeMethods.StaticGetType__Args _args = new InternalUnsafeMethods.StaticGetType__Args() {
             };
             IntPtr _engineResult = InternalUnsafeMethods.StaticGetType()(_args);
             return new EngineTypeInfo(_engineResult);
        }

        /// <description>
        /// Creates a new script asset using the targetFilePath.
        /// </description>
        /// <returns>The bool result of calling exec</returns>
        public void SetImportConfig(AssetImportConfig importConfig = null) {
             InternalUnsafeMethods.SetImportConfig__Args _args = new InternalUnsafeMethods.SetImportConfig__Args() {
                importConfig = importConfig.ObjectPtr,
             };
             InternalUnsafeMethods.SetImportConfig()(ObjectPtr, _args);
        }

        /// <description>
        /// Creates a new script asset using the targetFilePath.
        /// </description>
        /// <returns>The bool result of calling exec</returns>
        public void DeleteImportingAsset(AssetImportObject assetItem = null) {
             InternalUnsafeMethods.DeleteImportingAsset__Args _args = new InternalUnsafeMethods.DeleteImportingAsset__Args() {
                assetItem = assetItem.ObjectPtr,
             };
             InternalUnsafeMethods.DeleteImportingAsset()(ObjectPtr, _args);
        }

        /// <description>
        /// Creates a new script asset using the targetFilePath.
        /// </description>
        /// <returns>The bool result of calling exec</returns>
        public AssetImportObject GetAssetItemChild(AssetImportObject assetItem = null, int index = 0) {
             InternalUnsafeMethods.GetAssetItemChild__Args _args = new InternalUnsafeMethods.GetAssetItemChild__Args() {
                assetItem = assetItem.ObjectPtr,
                index = index,
             };
             IntPtr _engineResult = InternalUnsafeMethods.GetAssetItemChild()(ObjectPtr, _args);
             return new AssetImportObject(_engineResult);
        }

        /// <description>
        /// Creates a new script asset using the targetFilePath.
        /// </description>
        /// <returns>The bool result of calling exec</returns>
        public int GetAssetItemChildCount(AssetImportObject assetItem = null) {
             InternalUnsafeMethods.GetAssetItemChildCount__Args _args = new InternalUnsafeMethods.GetAssetItemChildCount__Args() {
                assetItem = assetItem.ObjectPtr,
             };
             int _engineResult = InternalUnsafeMethods.GetAssetItemChildCount()(ObjectPtr, _args);
             return _engineResult;
        }

        /// <description>
        /// Creates a new script asset using the targetFilePath.
        /// </description>
        /// <returns>The bool result of calling exec</returns>
        public AssetImportObject GetAssetItem(int index = 0) {
             InternalUnsafeMethods.GetAssetItem__Args _args = new InternalUnsafeMethods.GetAssetItem__Args() {
                index = index,
             };
             IntPtr _engineResult = InternalUnsafeMethods.GetAssetItem()(ObjectPtr, _args);
             return new AssetImportObject(_engineResult);
        }

        /// <description>
        /// Creates a new script asset using the targetFilePath.
        /// </description>
        /// <returns>The bool result of calling exec</returns>
        public int GetAssetItemCount() {
             InternalUnsafeMethods.GetAssetItemCount__Args _args = new InternalUnsafeMethods.GetAssetItemCount__Args() {
             };
             int _engineResult = InternalUnsafeMethods.GetAssetItemCount()(ObjectPtr, _args);
             return _engineResult;
        }

        /// <description>
        /// Creates a new script asset using the targetFilePath.
        /// </description>
        /// <returns>The bool result of calling exec</returns>
        public void ImportAssets() {
             InternalUnsafeMethods.ImportAssets__Args _args = new InternalUnsafeMethods.ImportAssets__Args() {
             };
             InternalUnsafeMethods.ImportAssets()(ObjectPtr, _args);
        }

        /// <description>
        /// Creates a new script asset using the targetFilePath.
        /// </description>
        /// <returns>The bool result of calling exec</returns>
        public void ResolveAssetItemIssues(AssetImportObject assetItem = null) {
             InternalUnsafeMethods.ResolveAssetItemIssues__Args _args = new InternalUnsafeMethods.ResolveAssetItemIssues__Args() {
                assetItem = assetItem.ObjectPtr,
             };
             InternalUnsafeMethods.ResolveAssetItemIssues()(ObjectPtr, _args);
        }

        /// <description>
        /// Creates a new script asset using the targetFilePath.
        /// </description>
        /// <returns>The bool result of calling exec</returns>
        public bool ValidateImportingAssets() {
             InternalUnsafeMethods.ValidateImportingAssets__Args _args = new InternalUnsafeMethods.ValidateImportingAssets__Args() {
             };
             bool _engineResult = InternalUnsafeMethods.ValidateImportingAssets()(ObjectPtr, _args);
             return _engineResult;
        }

        /// <description>
        /// Creates a new script asset using the targetFilePath.
        /// </description>
        /// <returns>The bool result of calling exec</returns>
        public void ProcessImportingAssets() {
             InternalUnsafeMethods.ProcessImportingAssets__Args _args = new InternalUnsafeMethods.ProcessImportingAssets__Args() {
             };
             InternalUnsafeMethods.ProcessImportingAssets()(ObjectPtr, _args);
        }

        /// <description>
        /// Creates a new script asset using the targetFilePath.
        /// </description>
        /// <returns>The bool result of calling exec</returns>
        public void AddImportingAssetItem(AssetImportObject assetItem = null, AssetImportObject parentItem = null) {
             InternalUnsafeMethods.AddImportingAssetItem__Args _args = new InternalUnsafeMethods.AddImportingAssetItem__Args() {
                assetItem = assetItem.ObjectPtr,
                parentItem = parentItem.ObjectPtr,
             };
             InternalUnsafeMethods.AddImportingAssetItem()(ObjectPtr, _args);
        }

        /// <description>
        /// Creates a new script asset using the targetFilePath.
        /// </description>
        /// <returns>The bool result of calling exec</returns>
        public AssetImportObject AddImportingFile(string path = "") {
             InternalUnsafeMethods.AddImportingFile__Args _args = new InternalUnsafeMethods.AddImportingFile__Args() {
                path = path,
             };
             IntPtr _engineResult = InternalUnsafeMethods.AddImportingFile()(ObjectPtr, _args);
             return new AssetImportObject(_engineResult);
        }

        /// <description>
        /// Creates a new script asset using the targetFilePath.
        /// </description>
        /// <returns>The bool result of calling exec</returns>
        public string AutoImportFile(string path = "") {
             InternalUnsafeMethods.AutoImportFile__Args _args = new InternalUnsafeMethods.AutoImportFile__Args() {
                path = path,
             };
             IntPtr _engineResult = InternalUnsafeMethods.AutoImportFile()(ObjectPtr, _args);
             return StringMarshal.IntPtrToUtf8String(_engineResult);
        }

        /// <description>
        /// Creates a new script asset using the targetFilePath.
        /// </description>
        /// <returns>The bool result of calling exec</returns>
        public string GetActivityLogLine(int i = 0) {
             InternalUnsafeMethods.GetActivityLogLine__Args _args = new InternalUnsafeMethods.GetActivityLogLine__Args() {
                i = i,
             };
             IntPtr _engineResult = InternalUnsafeMethods.GetActivityLogLine()(ObjectPtr, _args);
             return StringMarshal.IntPtrToUtf8String(_engineResult);
        }

        /// <description>
        /// Creates a new script asset using the targetFilePath.
        /// </description>
        /// <returns>The bool result of calling exec</returns>
        public int GetActivityLogLineCount() {
             InternalUnsafeMethods.GetActivityLogLineCount__Args _args = new InternalUnsafeMethods.GetActivityLogLineCount__Args() {
             };
             int _engineResult = InternalUnsafeMethods.GetActivityLogLineCount()(ObjectPtr, _args);
             return _engineResult;
        }

        /// <description>
        /// Creates a new script asset using the targetFilePath.
        /// </description>
        /// <returns>The bool result of calling exec</returns>
        public void DumpActivityLog() {
             InternalUnsafeMethods.DumpActivityLog__Args _args = new InternalUnsafeMethods.DumpActivityLog__Args() {
             };
             InternalUnsafeMethods.DumpActivityLog()(ObjectPtr, _args);
        }

        /// <description>
        /// Creates a new script asset using the targetFilePath.
        /// </description>
        /// <returns>The bool result of calling exec</returns>
        public void ResetImportSession(bool forceResetSession = false) {
             InternalUnsafeMethods.ResetImportSession__Args _args = new InternalUnsafeMethods.ResetImportSession__Args() {
                forceResetSession = forceResetSession,
             };
             InternalUnsafeMethods.ResetImportSession()(ObjectPtr, _args);
        }

        /// <description>
        /// Creates a new script asset using the targetFilePath.
        /// </description>
        /// <returns>The bool result of calling exec</returns>
        public void SetTargetPath(string path = "") {
             InternalUnsafeMethods.SetTargetPath__Args _args = new InternalUnsafeMethods.SetTargetPath__Args() {
                path = path,
             };
             InternalUnsafeMethods.SetTargetPath()(ObjectPtr, _args);
        }


        /// <value>
        /// <description>
        /// The Id of the module the assets are to be imported into
        /// </description>
        /// </value>
        public string TargetModuleId {
            get => GenericMarshal.StringTo<string>(GetFieldValue("targetModuleId"));
            set => SetFieldValue("targetModuleId", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// The Id of the module the assets are to be imported into
        /// </description>
        /// </value>
        public string FinalImportedAssetPath {
            get => GenericMarshal.StringTo<string>(GetFieldValue("finalImportedAssetPath"));
            set => SetFieldValue("finalImportedAssetPath", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// The path any imported assets are placed in as their destination
        /// </description>
        /// </value>
        public string TargetPath {
            get => GenericMarshal.StringTo<string>(GetFieldValue("targetPath"));
            set => SetFieldValue("targetPath", GenericMarshal.ToString(value));
        }
    }
}