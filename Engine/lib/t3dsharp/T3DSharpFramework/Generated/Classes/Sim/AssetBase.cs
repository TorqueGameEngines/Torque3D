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
    /// 
    public unsafe class AssetBase : SimObject {
        public AssetBase(bool pRegister = false) 
            : base(pRegister) {
        }
        
        public AssetBase(string pName, bool pRegister) 
            : this(false) {
            Name = pName;
            if (pRegister) {
                RegisterObject();
            }
        }
        
        public AssetBase(string pName) 
            : this(pName, false) {
        }
        
        public AssetBase(string pName, string pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(Engine.Sim.FindObject<SimObject>(pParent));
        }
        
        public AssetBase(string pName, SimObject pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(pParent);
        }
        
        public AssetBase(SimObject pObj) 
            : base(pObj) {
        }
        
        public AssetBase(IntPtr pObj) 
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
                                "fnAssetBase_staticGetType"), typeof(_StaticGetType));
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
                                "fnAssetBase_create"), typeof(_Create));
                }
                
                return _CreateFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct SaveAsset__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            [return: MarshalAs(UnmanagedType.I1)]
            internal delegate bool _SaveAsset(IntPtr _this, SaveAsset__Args args);
            private static _SaveAsset _SaveAssetFunc;
            internal static _SaveAsset SaveAsset() {
                if (_SaveAssetFunc == null) {
                    _SaveAssetFunc =
                        (_SaveAsset)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnAssetBase_saveAsset"), typeof(_SaveAsset));
                }
                
                return _SaveAssetFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct AddAssetDependencyField__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string pFieldName;
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string pAssetId;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _AddAssetDependencyField(IntPtr _this, AddAssetDependencyField__Args args);
            private static _AddAssetDependencyField _AddAssetDependencyFieldFunc;
            internal static _AddAssetDependencyField AddAssetDependencyField() {
                if (_AddAssetDependencyFieldFunc == null) {
                    _AddAssetDependencyFieldFunc =
                        (_AddAssetDependencyField)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnAssetBase_addAssetDependencyField"), typeof(_AddAssetDependencyField));
                }
                
                return _AddAssetDependencyFieldFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct ClearAssetDependencyFields__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string pFieldName;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _ClearAssetDependencyFields(IntPtr _this, ClearAssetDependencyFields__Args args);
            private static _ClearAssetDependencyFields _ClearAssetDependencyFieldsFunc;
            internal static _ClearAssetDependencyFields ClearAssetDependencyFields() {
                if (_ClearAssetDependencyFieldsFunc == null) {
                    _ClearAssetDependencyFieldsFunc =
                        (_ClearAssetDependencyFields)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnAssetBase_clearAssetDependencyFields"), typeof(_ClearAssetDependencyFields));
                }
                
                return _ClearAssetDependencyFieldsFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct GetAssetDependencyFieldCount__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string pFieldName;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate int _GetAssetDependencyFieldCount(IntPtr _this, GetAssetDependencyFieldCount__Args args);
            private static _GetAssetDependencyFieldCount _GetAssetDependencyFieldCountFunc;
            internal static _GetAssetDependencyFieldCount GetAssetDependencyFieldCount() {
                if (_GetAssetDependencyFieldCountFunc == null) {
                    _GetAssetDependencyFieldCountFunc =
                        (_GetAssetDependencyFieldCount)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnAssetBase_getAssetDependencyFieldCount"), typeof(_GetAssetDependencyFieldCount));
                }
                
                return _GetAssetDependencyFieldCountFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct GetAssetId__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            
            internal delegate IntPtr _GetAssetId(IntPtr _this, GetAssetId__Args args);
            private static _GetAssetId _GetAssetIdFunc;
            internal static _GetAssetId GetAssetId() {
                if (_GetAssetIdFunc == null) {
                    _GetAssetIdFunc =
                        (_GetAssetId)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnAssetBase_getAssetId"), typeof(_GetAssetId));
                }
                
                return _GetAssetIdFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct RefreshAsset__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _RefreshAsset(IntPtr _this, RefreshAsset__Args args);
            private static _RefreshAsset _RefreshAssetFunc;
            internal static _RefreshAsset RefreshAsset() {
                if (_RefreshAssetFunc == null) {
                    _RefreshAssetFunc =
                        (_RefreshAsset)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnAssetBase_refreshAsset"), typeof(_RefreshAsset));
                }
                
                return _RefreshAssetFunc;
            }
        }
        #endregion

        /// <description>
        /// Get the type info object for the AssetBase class.
        /// </description>
        /// <returns>The type info object for AssetBase</returns>
        public static EngineTypeInfo StaticGetType() {
             InternalUnsafeMethods.StaticGetType__Args _args = new InternalUnsafeMethods.StaticGetType__Args() {
             };
             IntPtr _engineResult = InternalUnsafeMethods.StaticGetType()(_args);
             return new EngineTypeInfo(_engineResult);
        }

        /// <description>
        /// Gets the assets' Asset Id.  This is only available if the asset was acquired from the asset manager.
        /// </description>
        /// <returns>The assets' Asset Id.</returns>
        public bool SaveAsset() {
             InternalUnsafeMethods.SaveAsset__Args _args = new InternalUnsafeMethods.SaveAsset__Args() {
             };
             bool _engineResult = InternalUnsafeMethods.SaveAsset()(ObjectPtr, _args);
             return _engineResult;
        }

        /// <description>
        /// Gets the assets' Asset Id.  This is only available if the asset was acquired from the asset manager.
        /// </description>
        /// <returns>The assets' Asset Id.</returns>
        public void AddAssetDependencyField(string pFieldName = "", string pAssetId = "") {
             InternalUnsafeMethods.AddAssetDependencyField__Args _args = new InternalUnsafeMethods.AddAssetDependencyField__Args() {
                pFieldName = pFieldName,
                pAssetId = pAssetId,
             };
             InternalUnsafeMethods.AddAssetDependencyField()(ObjectPtr, _args);
        }

        /// <description>
        /// Gets the assets' Asset Id.  This is only available if the asset was acquired from the asset manager.
        /// </description>
        /// <returns>The assets' Asset Id.</returns>
        public void ClearAssetDependencyFields(string pFieldName = "") {
             InternalUnsafeMethods.ClearAssetDependencyFields__Args _args = new InternalUnsafeMethods.ClearAssetDependencyFields__Args() {
                pFieldName = pFieldName,
             };
             InternalUnsafeMethods.ClearAssetDependencyFields()(ObjectPtr, _args);
        }

        /// <description>
        /// Gets the assets' Asset Id.  This is only available if the asset was acquired from the asset manager.
        /// </description>
        /// <returns>The assets' Asset Id.</returns>
        public int GetAssetDependencyFieldCount(string pFieldName = "") {
             InternalUnsafeMethods.GetAssetDependencyFieldCount__Args _args = new InternalUnsafeMethods.GetAssetDependencyFieldCount__Args() {
                pFieldName = pFieldName,
             };
             int _engineResult = InternalUnsafeMethods.GetAssetDependencyFieldCount()(ObjectPtr, _args);
             return _engineResult;
        }

        /// <description>
        /// Gets the assets' Asset Id.  This is only available if the asset was acquired from the asset manager.
        /// </description>
        /// <returns>The assets' Asset Id.</returns>
        public string GetAssetId() {
             InternalUnsafeMethods.GetAssetId__Args _args = new InternalUnsafeMethods.GetAssetId__Args() {
             };
             IntPtr _engineResult = InternalUnsafeMethods.GetAssetId()(ObjectPtr, _args);
             return StringMarshal.IntPtrToUtf8String(_engineResult);
        }

        /// <description>
        /// Refresh the asset.
        /// </description>
        /// <returns>No return value.</returns>
        public void RefreshAsset() {
             InternalUnsafeMethods.RefreshAsset__Args _args = new InternalUnsafeMethods.RefreshAsset__Args() {
             };
             InternalUnsafeMethods.RefreshAsset()(ObjectPtr, _args);
        }


        /// <value>
        /// <description>
        /// The name of the asset.  The is not a unique identification like an asset Id.
        /// </description>
        /// </value>
        public string AssetName {
            get => GenericMarshal.StringTo<string>(GetFieldValue("AssetName"));
            set => SetFieldValue("AssetName", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// The simple description of the asset contents.
        /// </description>
        /// </value>
        public string AssetDescription {
            get => GenericMarshal.StringTo<string>(GetFieldValue("AssetDescription"));
            set => SetFieldValue("AssetDescription", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// An arbitrary category that can be used to categorized assets.
        /// </description>
        /// </value>
        public string AssetCategory {
            get => GenericMarshal.StringTo<string>(GetFieldValue("AssetCategory"));
            set => SetFieldValue("AssetCategory", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Whether the asset is automatically unloaded when an asset is released and has no other acquisitions or not.
        /// </description>
        /// </value>
        public bool AssetAutoUnload {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("AssetAutoUnload"));
            set => SetFieldValue("AssetAutoUnload", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Whether the asset is used internally only or not.
        /// </description>
        /// </value>
        public bool AssetInternal {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("AssetInternal"));
            set => SetFieldValue("AssetInternal", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Whether the asset is private or not.
        /// </description>
        /// </value>
        public bool AssetPrivate {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("AssetPrivate"));
            set => SetFieldValue("AssetPrivate", GenericMarshal.ToString(value));
        }
    }
}