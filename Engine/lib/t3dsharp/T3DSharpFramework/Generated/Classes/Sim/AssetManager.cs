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
    public unsafe class AssetManager : SimObject {
        public AssetManager(bool pRegister = false) 
            : base(pRegister) {
        }
        
        public AssetManager(string pName, bool pRegister) 
            : this(false) {
            Name = pName;
            if (pRegister) {
                RegisterObject();
            }
        }
        
        public AssetManager(string pName) 
            : this(pName, false) {
        }
        
        public AssetManager(string pName, string pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(Engine.Sim.FindObject<SimObject>(pParent));
        }
        
        public AssetManager(string pName, SimObject pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(pParent);
        }
        
        public AssetManager(SimObject pObj) 
            : base(pObj) {
        }
        
        public AssetManager(IntPtr pObj) 
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
                                "fnAssetManager_staticGetType"), typeof(_StaticGetType));
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
                                "fnAssetManager_create"), typeof(_Create));
                }
                
                return _CreateFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct DumpDeclaredAssets__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _DumpDeclaredAssets(IntPtr _this, DumpDeclaredAssets__Args args);
            private static _DumpDeclaredAssets _DumpDeclaredAssetsFunc;
            internal static _DumpDeclaredAssets DumpDeclaredAssets() {
                if (_DumpDeclaredAssetsFunc == null) {
                    _DumpDeclaredAssetsFunc =
                        (_DumpDeclaredAssets)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnAssetManager_dumpDeclaredAssets"), typeof(_DumpDeclaredAssets));
                }
                
                return _DumpDeclaredAssetsFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct GetMaxLoadedExternalAssetCount__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            [return: MarshalAs(UnmanagedType.I1)]
            internal delegate bool _GetMaxLoadedExternalAssetCount(IntPtr _this, GetMaxLoadedExternalAssetCount__Args args);
            private static _GetMaxLoadedExternalAssetCount _GetMaxLoadedExternalAssetCountFunc;
            internal static _GetMaxLoadedExternalAssetCount GetMaxLoadedExternalAssetCount() {
                if (_GetMaxLoadedExternalAssetCountFunc == null) {
                    _GetMaxLoadedExternalAssetCountFunc =
                        (_GetMaxLoadedExternalAssetCount)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnAssetManager_getMaxLoadedExternalAssetCount"), typeof(_GetMaxLoadedExternalAssetCount));
                }
                
                return _GetMaxLoadedExternalAssetCountFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct GetLoadedExternalAssetCount__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            [return: MarshalAs(UnmanagedType.I1)]
            internal delegate bool _GetLoadedExternalAssetCount(IntPtr _this, GetLoadedExternalAssetCount__Args args);
            private static _GetLoadedExternalAssetCount _GetLoadedExternalAssetCountFunc;
            internal static _GetLoadedExternalAssetCount GetLoadedExternalAssetCount() {
                if (_GetLoadedExternalAssetCountFunc == null) {
                    _GetLoadedExternalAssetCountFunc =
                        (_GetLoadedExternalAssetCount)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnAssetManager_getLoadedExternalAssetCount"), typeof(_GetLoadedExternalAssetCount));
                }
                
                return _GetLoadedExternalAssetCountFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct GetMaxLoadedInternalAssetCount__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            [return: MarshalAs(UnmanagedType.I1)]
            internal delegate bool _GetMaxLoadedInternalAssetCount(IntPtr _this, GetMaxLoadedInternalAssetCount__Args args);
            private static _GetMaxLoadedInternalAssetCount _GetMaxLoadedInternalAssetCountFunc;
            internal static _GetMaxLoadedInternalAssetCount GetMaxLoadedInternalAssetCount() {
                if (_GetMaxLoadedInternalAssetCountFunc == null) {
                    _GetMaxLoadedInternalAssetCountFunc =
                        (_GetMaxLoadedInternalAssetCount)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnAssetManager_getMaxLoadedInternalAssetCount"), typeof(_GetMaxLoadedInternalAssetCount));
                }
                
                return _GetMaxLoadedInternalAssetCountFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct GetLoadedInternalAssetCount__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            [return: MarshalAs(UnmanagedType.I1)]
            internal delegate bool _GetLoadedInternalAssetCount(IntPtr _this, GetLoadedInternalAssetCount__Args args);
            private static _GetLoadedInternalAssetCount _GetLoadedInternalAssetCountFunc;
            internal static _GetLoadedInternalAssetCount GetLoadedInternalAssetCount() {
                if (_GetLoadedInternalAssetCountFunc == null) {
                    _GetLoadedInternalAssetCountFunc =
                        (_GetLoadedInternalAssetCount)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnAssetManager_getLoadedInternalAssetCount"), typeof(_GetLoadedInternalAssetCount));
                }
                
                return _GetLoadedInternalAssetCountFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct GetReferencedAssetCount__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            [return: MarshalAs(UnmanagedType.I1)]
            internal delegate bool _GetReferencedAssetCount(IntPtr _this, GetReferencedAssetCount__Args args);
            private static _GetReferencedAssetCount _GetReferencedAssetCountFunc;
            internal static _GetReferencedAssetCount GetReferencedAssetCount() {
                if (_GetReferencedAssetCountFunc == null) {
                    _GetReferencedAssetCountFunc =
                        (_GetReferencedAssetCount)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnAssetManager_getReferencedAssetCount"), typeof(_GetReferencedAssetCount));
                }
                
                return _GetReferencedAssetCountFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct GetDeclaredAssetCount__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            [return: MarshalAs(UnmanagedType.I1)]
            internal delegate bool _GetDeclaredAssetCount(IntPtr _this, GetDeclaredAssetCount__Args args);
            private static _GetDeclaredAssetCount _GetDeclaredAssetCountFunc;
            internal static _GetDeclaredAssetCount GetDeclaredAssetCount() {
                if (_GetDeclaredAssetCountFunc == null) {
                    _GetDeclaredAssetCountFunc =
                        (_GetDeclaredAssetCount)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnAssetManager_getDeclaredAssetCount"), typeof(_GetDeclaredAssetCount));
                }
                
                return _GetDeclaredAssetCountFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct FindAssetLooseFile__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string assetQuery;
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string assetLooseFile;
                [MarshalAs(UnmanagedType.I1)]
                internal bool assetQueryAsSource;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate int _FindAssetLooseFile(IntPtr _this, FindAssetLooseFile__Args args);
            private static _FindAssetLooseFile _FindAssetLooseFileFunc;
            internal static _FindAssetLooseFile FindAssetLooseFile() {
                if (_FindAssetLooseFileFunc == null) {
                    _FindAssetLooseFileFunc =
                        (_FindAssetLooseFile)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnAssetManager_findAssetLooseFile"), typeof(_FindAssetLooseFile));
                }
                
                return _FindAssetLooseFileFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct FindTaggedAssets__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string assetQuery;
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string assetTagNames;
                [MarshalAs(UnmanagedType.I1)]
                internal bool assetQueryAsSource;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate int _FindTaggedAssets(IntPtr _this, FindTaggedAssets__Args args);
            private static _FindTaggedAssets _FindTaggedAssetsFunc;
            internal static _FindTaggedAssets FindTaggedAssets() {
                if (_FindTaggedAssetsFunc == null) {
                    _FindTaggedAssetsFunc =
                        (_FindTaggedAssets)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnAssetManager_findTaggedAssets"), typeof(_FindTaggedAssets));
                }
                
                return _FindTaggedAssetsFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct FindInvalidAssetReferences__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string assetQuery;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate int _FindInvalidAssetReferences(IntPtr _this, FindInvalidAssetReferences__Args args);
            private static _FindInvalidAssetReferences _FindInvalidAssetReferencesFunc;
            internal static _FindInvalidAssetReferences FindInvalidAssetReferences() {
                if (_FindInvalidAssetReferencesFunc == null) {
                    _FindInvalidAssetReferencesFunc =
                        (_FindInvalidAssetReferences)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnAssetManager_findInvalidAssetReferences"), typeof(_FindInvalidAssetReferences));
                }
                
                return _FindInvalidAssetReferencesFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct FindAssetIsDependedOn__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string assetQuery;
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string assetId;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate int _FindAssetIsDependedOn(IntPtr _this, FindAssetIsDependedOn__Args args);
            private static _FindAssetIsDependedOn _FindAssetIsDependedOnFunc;
            internal static _FindAssetIsDependedOn FindAssetIsDependedOn() {
                if (_FindAssetIsDependedOnFunc == null) {
                    _FindAssetIsDependedOnFunc =
                        (_FindAssetIsDependedOn)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnAssetManager_findAssetIsDependedOn"), typeof(_FindAssetIsDependedOn));
                }
                
                return _FindAssetIsDependedOnFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct FindAssetDependsOn__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string assetQuery;
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string assetId;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate int _FindAssetDependsOn(IntPtr _this, FindAssetDependsOn__Args args);
            private static _FindAssetDependsOn _FindAssetDependsOnFunc;
            internal static _FindAssetDependsOn FindAssetDependsOn() {
                if (_FindAssetDependsOnFunc == null) {
                    _FindAssetDependsOnFunc =
                        (_FindAssetDependsOn)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnAssetManager_findAssetDependsOn"), typeof(_FindAssetDependsOn));
                }
                
                return _FindAssetDependsOnFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct FindAssetType__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string assetQuery;
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string assetType;
                [MarshalAs(UnmanagedType.I1)]
                internal bool assetQueryAsSource;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate int _FindAssetType(IntPtr _this, FindAssetType__Args args);
            private static _FindAssetType _FindAssetTypeFunc;
            internal static _FindAssetType FindAssetType() {
                if (_FindAssetTypeFunc == null) {
                    _FindAssetTypeFunc =
                        (_FindAssetType)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnAssetManager_findAssetType"), typeof(_FindAssetType));
                }
                
                return _FindAssetTypeFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct FindAssetPrivate__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string assetQuery;
                [MarshalAs(UnmanagedType.I1)]
                internal bool assetPrivate;
                [MarshalAs(UnmanagedType.I1)]
                internal bool assetQueryAsSource;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate int _FindAssetPrivate(IntPtr _this, FindAssetPrivate__Args args);
            private static _FindAssetPrivate _FindAssetPrivateFunc;
            internal static _FindAssetPrivate FindAssetPrivate() {
                if (_FindAssetPrivateFunc == null) {
                    _FindAssetPrivateFunc =
                        (_FindAssetPrivate)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnAssetManager_findAssetPrivate"), typeof(_FindAssetPrivate));
                }
                
                return _FindAssetPrivateFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct FindAssetInternal__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string assetQuery;
                [MarshalAs(UnmanagedType.I1)]
                internal bool assetInternal;
                [MarshalAs(UnmanagedType.I1)]
                internal bool assetQueryAsSource;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate int _FindAssetInternal(IntPtr _this, FindAssetInternal__Args args);
            private static _FindAssetInternal _FindAssetInternalFunc;
            internal static _FindAssetInternal FindAssetInternal() {
                if (_FindAssetInternalFunc == null) {
                    _FindAssetInternalFunc =
                        (_FindAssetInternal)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnAssetManager_findAssetInternal"), typeof(_FindAssetInternal));
                }
                
                return _FindAssetInternalFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct FindAssetAutoUnload__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string assetQuery;
                [MarshalAs(UnmanagedType.I1)]
                internal bool assetAutoUnload;
                [MarshalAs(UnmanagedType.I1)]
                internal bool assetQueryAsSource;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate int _FindAssetAutoUnload(IntPtr _this, FindAssetAutoUnload__Args args);
            private static _FindAssetAutoUnload _FindAssetAutoUnloadFunc;
            internal static _FindAssetAutoUnload FindAssetAutoUnload() {
                if (_FindAssetAutoUnloadFunc == null) {
                    _FindAssetAutoUnloadFunc =
                        (_FindAssetAutoUnload)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnAssetManager_findAssetAutoUnload"), typeof(_FindAssetAutoUnload));
                }
                
                return _FindAssetAutoUnloadFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct FindAssetCategory__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string assetQuery;
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string assetCategory;
                [MarshalAs(UnmanagedType.I1)]
                internal bool assetQueryAsSource;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate int _FindAssetCategory(IntPtr _this, FindAssetCategory__Args args);
            private static _FindAssetCategory _FindAssetCategoryFunc;
            internal static _FindAssetCategory FindAssetCategory() {
                if (_FindAssetCategoryFunc == null) {
                    _FindAssetCategoryFunc =
                        (_FindAssetCategory)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnAssetManager_findAssetCategory"), typeof(_FindAssetCategory));
                }
                
                return _FindAssetCategoryFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct FindAssetName__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string assetQuery;
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string assetName;
                [MarshalAs(UnmanagedType.I1)]
                internal bool partialName;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate int _FindAssetName(IntPtr _this, FindAssetName__Args args);
            private static _FindAssetName _FindAssetNameFunc;
            internal static _FindAssetName FindAssetName() {
                if (_FindAssetNameFunc == null) {
                    _FindAssetNameFunc =
                        (_FindAssetName)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnAssetManager_findAssetName"), typeof(_FindAssetName));
                }
                
                return _FindAssetNameFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct FindAllAssets__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string assetQuery;
                [MarshalAs(UnmanagedType.I1)]
                internal bool ignoreInternal;
                [MarshalAs(UnmanagedType.I1)]
                internal bool ignorePrivate;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate int _FindAllAssets(IntPtr _this, FindAllAssets__Args args);
            private static _FindAllAssets _FindAllAssetsFunc;
            internal static _FindAllAssets FindAllAssets() {
                if (_FindAllAssetsFunc == null) {
                    _FindAllAssetsFunc =
                        (_FindAllAssets)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnAssetManager_findAllAssets"), typeof(_FindAllAssets));
                }
                
                return _FindAllAssetsFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct GetAssetTags__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate int _GetAssetTags(IntPtr _this, GetAssetTags__Args args);
            private static _GetAssetTags _GetAssetTagsFunc;
            internal static _GetAssetTags GetAssetTags() {
                if (_GetAssetTagsFunc == null) {
                    _GetAssetTagsFunc =
                        (_GetAssetTags)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnAssetManager_getAssetTags"), typeof(_GetAssetTags));
                }
                
                return _GetAssetTagsFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct RestoreAssetTags__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            [return: MarshalAs(UnmanagedType.I1)]
            internal delegate bool _RestoreAssetTags(IntPtr _this, RestoreAssetTags__Args args);
            private static _RestoreAssetTags _RestoreAssetTagsFunc;
            internal static _RestoreAssetTags RestoreAssetTags() {
                if (_RestoreAssetTagsFunc == null) {
                    _RestoreAssetTagsFunc =
                        (_RestoreAssetTags)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnAssetManager_restoreAssetTags"), typeof(_RestoreAssetTags));
                }
                
                return _RestoreAssetTagsFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct SaveAssetTags__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            [return: MarshalAs(UnmanagedType.I1)]
            internal delegate bool _SaveAssetTags(IntPtr _this, SaveAssetTags__Args args);
            private static _SaveAssetTags _SaveAssetTagsFunc;
            internal static _SaveAssetTags SaveAssetTags() {
                if (_SaveAssetTagsFunc == null) {
                    _SaveAssetTagsFunc =
                        (_SaveAssetTags)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnAssetManager_saveAssetTags"), typeof(_SaveAssetTags));
                }
                
                return _SaveAssetTagsFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct RefreshAllAssets__Args
            {
                [MarshalAs(UnmanagedType.I1)]
                internal bool includeUnloaded;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _RefreshAllAssets(IntPtr _this, RefreshAllAssets__Args args);
            private static _RefreshAllAssets _RefreshAllAssetsFunc;
            internal static _RefreshAllAssets RefreshAllAssets() {
                if (_RefreshAllAssetsFunc == null) {
                    _RefreshAllAssetsFunc =
                        (_RefreshAllAssets)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnAssetManager_refreshAllAssets"), typeof(_RefreshAllAssets));
                }
                
                return _RefreshAllAssetsFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct RefreshAsset__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string assetId;
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
                                "fnAssetManager_refreshAsset"), typeof(_RefreshAsset));
                }
                
                return _RefreshAssetFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct DeleteAsset__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string assetId;
                [MarshalAs(UnmanagedType.I1)]
                internal bool deleteLooseFiles;
                [MarshalAs(UnmanagedType.I1)]
                internal bool deleteDependencies;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            [return: MarshalAs(UnmanagedType.I1)]
            internal delegate bool _DeleteAsset(IntPtr _this, DeleteAsset__Args args);
            private static _DeleteAsset _DeleteAssetFunc;
            internal static _DeleteAsset DeleteAsset() {
                if (_DeleteAssetFunc == null) {
                    _DeleteAssetFunc =
                        (_DeleteAsset)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnAssetManager_deleteAsset"), typeof(_DeleteAsset));
                }
                
                return _DeleteAssetFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct PurgeAssets__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _PurgeAssets(IntPtr _this, PurgeAssets__Args args);
            private static _PurgeAssets _PurgeAssetsFunc;
            internal static _PurgeAssets PurgeAssets() {
                if (_PurgeAssetsFunc == null) {
                    _PurgeAssetsFunc =
                        (_PurgeAssets)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnAssetManager_purgeAssets"), typeof(_PurgeAssets));
                }
                
                return _PurgeAssetsFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct ReleaseAsset__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string assetId;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            [return: MarshalAs(UnmanagedType.I1)]
            internal delegate bool _ReleaseAsset(IntPtr _this, ReleaseAsset__Args args);
            private static _ReleaseAsset _ReleaseAssetFunc;
            internal static _ReleaseAsset ReleaseAsset() {
                if (_ReleaseAssetFunc == null) {
                    _ReleaseAssetFunc =
                        (_ReleaseAsset)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnAssetManager_releaseAsset"), typeof(_ReleaseAsset));
                }
                
                return _ReleaseAssetFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct AcquireAsset__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string assetId;
                [MarshalAs(UnmanagedType.I1)]
                internal bool asPrivate;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            
            internal delegate IntPtr _AcquireAsset(IntPtr _this, AcquireAsset__Args args);
            private static _AcquireAsset _AcquireAssetFunc;
            internal static _AcquireAsset AcquireAsset() {
                if (_AcquireAssetFunc == null) {
                    _AcquireAssetFunc =
                        (_AcquireAsset)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnAssetManager_acquireAsset"), typeof(_AcquireAsset));
                }
                
                return _AcquireAssetFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct RenameReferencedAsset__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string assetIdFrom;
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string assetIdTo;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            [return: MarshalAs(UnmanagedType.I1)]
            internal delegate bool _RenameReferencedAsset(IntPtr _this, RenameReferencedAsset__Args args);
            private static _RenameReferencedAsset _RenameReferencedAssetFunc;
            internal static _RenameReferencedAsset RenameReferencedAsset() {
                if (_RenameReferencedAssetFunc == null) {
                    _RenameReferencedAssetFunc =
                        (_RenameReferencedAsset)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnAssetManager_renameReferencedAsset"), typeof(_RenameReferencedAsset));
                }
                
                return _RenameReferencedAssetFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct RenameDeclaredAsset__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string assetIdFrom;
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string assetIdTo;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            [return: MarshalAs(UnmanagedType.I1)]
            internal delegate bool _RenameDeclaredAsset(IntPtr _this, RenameDeclaredAsset__Args args);
            private static _RenameDeclaredAsset _RenameDeclaredAssetFunc;
            internal static _RenameDeclaredAsset RenameDeclaredAsset() {
                if (_RenameDeclaredAssetFunc == null) {
                    _RenameDeclaredAssetFunc =
                        (_RenameDeclaredAsset)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnAssetManager_renameDeclaredAsset"), typeof(_RenameDeclaredAsset));
                }
                
                return _RenameDeclaredAssetFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct IsReferencedAsset__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string assetId;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            [return: MarshalAs(UnmanagedType.I1)]
            internal delegate bool _IsReferencedAsset(IntPtr _this, IsReferencedAsset__Args args);
            private static _IsReferencedAsset _IsReferencedAssetFunc;
            internal static _IsReferencedAsset IsReferencedAsset() {
                if (_IsReferencedAssetFunc == null) {
                    _IsReferencedAssetFunc =
                        (_IsReferencedAsset)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnAssetManager_isReferencedAsset"), typeof(_IsReferencedAsset));
                }
                
                return _IsReferencedAssetFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct IsDeclaredAsset__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string assetId;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            [return: MarshalAs(UnmanagedType.I1)]
            internal delegate bool _IsDeclaredAsset(IntPtr _this, IsDeclaredAsset__Args args);
            private static _IsDeclaredAsset _IsDeclaredAssetFunc;
            internal static _IsDeclaredAsset IsDeclaredAsset() {
                if (_IsDeclaredAssetFunc == null) {
                    _IsDeclaredAssetFunc =
                        (_IsDeclaredAsset)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnAssetManager_isDeclaredAsset"), typeof(_IsDeclaredAsset));
                }
                
                return _IsDeclaredAssetFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct IsAssetLoaded__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string assetId;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            [return: MarshalAs(UnmanagedType.I1)]
            internal delegate bool _IsAssetLoaded(IntPtr _this, IsAssetLoaded__Args args);
            private static _IsAssetLoaded _IsAssetLoadedFunc;
            internal static _IsAssetLoaded IsAssetLoaded() {
                if (_IsAssetLoadedFunc == null) {
                    _IsAssetLoadedFunc =
                        (_IsAssetLoaded)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnAssetManager_isAssetLoaded"), typeof(_IsAssetLoaded));
                }
                
                return _IsAssetLoadedFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct IsAssetAutoUnload__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string assetId;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            [return: MarshalAs(UnmanagedType.I1)]
            internal delegate bool _IsAssetAutoUnload(IntPtr _this, IsAssetAutoUnload__Args args);
            private static _IsAssetAutoUnload _IsAssetAutoUnloadFunc;
            internal static _IsAssetAutoUnload IsAssetAutoUnload() {
                if (_IsAssetAutoUnloadFunc == null) {
                    _IsAssetAutoUnloadFunc =
                        (_IsAssetAutoUnload)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnAssetManager_isAssetAutoUnload"), typeof(_IsAssetAutoUnload));
                }
                
                return _IsAssetAutoUnloadFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct IsAssetPrivate__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string assetId;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            [return: MarshalAs(UnmanagedType.I1)]
            internal delegate bool _IsAssetPrivate(IntPtr _this, IsAssetPrivate__Args args);
            private static _IsAssetPrivate _IsAssetPrivateFunc;
            internal static _IsAssetPrivate IsAssetPrivate() {
                if (_IsAssetPrivateFunc == null) {
                    _IsAssetPrivateFunc =
                        (_IsAssetPrivate)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnAssetManager_isAssetPrivate"), typeof(_IsAssetPrivate));
                }
                
                return _IsAssetPrivateFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct IsAssetInternal__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string assetId;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            [return: MarshalAs(UnmanagedType.I1)]
            internal delegate bool _IsAssetInternal(IntPtr _this, IsAssetInternal__Args args);
            private static _IsAssetInternal _IsAssetInternalFunc;
            internal static _IsAssetInternal IsAssetInternal() {
                if (_IsAssetInternalFunc == null) {
                    _IsAssetInternalFunc =
                        (_IsAssetInternal)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnAssetManager_isAssetInternal"), typeof(_IsAssetInternal));
                }
                
                return _IsAssetInternalFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct GetAssetModule__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string assetId;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            
            internal delegate IntPtr _GetAssetModule(IntPtr _this, GetAssetModule__Args args);
            private static _GetAssetModule _GetAssetModuleFunc;
            internal static _GetAssetModule GetAssetModule() {
                if (_GetAssetModuleFunc == null) {
                    _GetAssetModuleFunc =
                        (_GetAssetModule)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnAssetManager_getAssetModule"), typeof(_GetAssetModule));
                }
                
                return _GetAssetModuleFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct GetAssetPath__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string assetId;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            
            internal delegate IntPtr _GetAssetPath(IntPtr _this, GetAssetPath__Args args);
            private static _GetAssetPath _GetAssetPathFunc;
            internal static _GetAssetPath GetAssetPath() {
                if (_GetAssetPathFunc == null) {
                    _GetAssetPathFunc =
                        (_GetAssetPath)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnAssetManager_getAssetPath"), typeof(_GetAssetPath));
                }
                
                return _GetAssetPathFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct GetAssetFilePath__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string assetId;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            
            internal delegate IntPtr _GetAssetFilePath(IntPtr _this, GetAssetFilePath__Args args);
            private static _GetAssetFilePath _GetAssetFilePathFunc;
            internal static _GetAssetFilePath GetAssetFilePath() {
                if (_GetAssetFilePathFunc == null) {
                    _GetAssetFilePathFunc =
                        (_GetAssetFilePath)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnAssetManager_getAssetFilePath"), typeof(_GetAssetFilePath));
                }
                
                return _GetAssetFilePathFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct GetAssetType__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string assetId;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            
            internal delegate IntPtr _GetAssetType(IntPtr _this, GetAssetType__Args args);
            private static _GetAssetType _GetAssetTypeFunc;
            internal static _GetAssetType GetAssetType() {
                if (_GetAssetTypeFunc == null) {
                    _GetAssetTypeFunc =
                        (_GetAssetType)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnAssetManager_getAssetType"), typeof(_GetAssetType));
                }
                
                return _GetAssetTypeFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct GetAssetCategory__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string assetId;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            
            internal delegate IntPtr _GetAssetCategory(IntPtr _this, GetAssetCategory__Args args);
            private static _GetAssetCategory _GetAssetCategoryFunc;
            internal static _GetAssetCategory GetAssetCategory() {
                if (_GetAssetCategoryFunc == null) {
                    _GetAssetCategoryFunc =
                        (_GetAssetCategory)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnAssetManager_getAssetCategory"), typeof(_GetAssetCategory));
                }
                
                return _GetAssetCategoryFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct GetAssetDescription__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string assetId;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            
            internal delegate IntPtr _GetAssetDescription(IntPtr _this, GetAssetDescription__Args args);
            private static _GetAssetDescription _GetAssetDescriptionFunc;
            internal static _GetAssetDescription GetAssetDescription() {
                if (_GetAssetDescriptionFunc == null) {
                    _GetAssetDescriptionFunc =
                        (_GetAssetDescription)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnAssetManager_getAssetDescription"), typeof(_GetAssetDescription));
                }
                
                return _GetAssetDescriptionFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct GetAssetName__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string assetId;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            
            internal delegate IntPtr _GetAssetName(IntPtr _this, GetAssetName__Args args);
            private static _GetAssetName _GetAssetNameFunc;
            internal static _GetAssetName GetAssetName() {
                if (_GetAssetNameFunc == null) {
                    _GetAssetNameFunc =
                        (_GetAssetName)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnAssetManager_getAssetName"), typeof(_GetAssetName));
                }
                
                return _GetAssetNameFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct RemoveDeclaredAsset__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string assetId;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            [return: MarshalAs(UnmanagedType.I1)]
            internal delegate bool _RemoveDeclaredAsset(IntPtr _this, RemoveDeclaredAsset__Args args);
            private static _RemoveDeclaredAsset _RemoveDeclaredAssetFunc;
            internal static _RemoveDeclaredAsset RemoveDeclaredAsset() {
                if (_RemoveDeclaredAssetFunc == null) {
                    _RemoveDeclaredAssetFunc =
                        (_RemoveDeclaredAsset)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnAssetManager_removeDeclaredAsset"), typeof(_RemoveDeclaredAsset));
                }
                
                return _RemoveDeclaredAssetFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct RemoveDeclaredAssets__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string moduleDefinition;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            [return: MarshalAs(UnmanagedType.I1)]
            internal delegate bool _RemoveDeclaredAssets(IntPtr _this, RemoveDeclaredAssets__Args args);
            private static _RemoveDeclaredAssets _RemoveDeclaredAssetsFunc;
            internal static _RemoveDeclaredAssets RemoveDeclaredAssets() {
                if (_RemoveDeclaredAssetsFunc == null) {
                    _RemoveDeclaredAssetsFunc =
                        (_RemoveDeclaredAssets)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnAssetManager_removeDeclaredAssets"), typeof(_RemoveDeclaredAssets));
                }
                
                return _RemoveDeclaredAssetsFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct AddPrivateAsset__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string assetObject;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            
            internal delegate IntPtr _AddPrivateAsset(IntPtr _this, AddPrivateAsset__Args args);
            private static _AddPrivateAsset _AddPrivateAssetFunc;
            internal static _AddPrivateAsset AddPrivateAsset() {
                if (_AddPrivateAssetFunc == null) {
                    _AddPrivateAssetFunc =
                        (_AddPrivateAsset)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnAssetManager_addPrivateAsset"), typeof(_AddPrivateAsset));
                }
                
                return _AddPrivateAssetFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct AddDeclaredAsset__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string moduleDefinition;
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string assetFilePath;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            [return: MarshalAs(UnmanagedType.I1)]
            internal delegate bool _AddDeclaredAsset(IntPtr _this, AddDeclaredAsset__Args args);
            private static _AddDeclaredAsset _AddDeclaredAssetFunc;
            internal static _AddDeclaredAsset AddDeclaredAsset() {
                if (_AddDeclaredAssetFunc == null) {
                    _AddDeclaredAssetFunc =
                        (_AddDeclaredAsset)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnAssetManager_addDeclaredAsset"), typeof(_AddDeclaredAsset));
                }
                
                return _AddDeclaredAssetFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct AddModuleDeclaredAssets__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string moduleDefinition;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            [return: MarshalAs(UnmanagedType.I1)]
            internal delegate bool _AddModuleDeclaredAssets(IntPtr _this, AddModuleDeclaredAssets__Args args);
            private static _AddModuleDeclaredAssets _AddModuleDeclaredAssetsFunc;
            internal static _AddModuleDeclaredAssets AddModuleDeclaredAssets() {
                if (_AddModuleDeclaredAssetsFunc == null) {
                    _AddModuleDeclaredAssetsFunc =
                        (_AddModuleDeclaredAssets)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnAssetManager_addModuleDeclaredAssets"), typeof(_AddModuleDeclaredAssets));
                }
                
                return _AddModuleDeclaredAssetsFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct CompileReferencedAssets__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string moduleDefinition;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            [return: MarshalAs(UnmanagedType.I1)]
            internal delegate bool _CompileReferencedAssets(IntPtr _this, CompileReferencedAssets__Args args);
            private static _CompileReferencedAssets _CompileReferencedAssetsFunc;
            internal static _CompileReferencedAssets CompileReferencedAssets() {
                if (_CompileReferencedAssetsFunc == null) {
                    _CompileReferencedAssetsFunc =
                        (_CompileReferencedAssets)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnAssetManager_compileReferencedAssets"), typeof(_CompileReferencedAssets));
                }
                
                return _CompileReferencedAssetsFunc;
            }
        }
        #endregion

        /// <description>
        /// Get the type info object for the AssetManager class.
        /// </description>
        /// <returns>The type info object for AssetManager</returns>
        public static EngineTypeInfo StaticGetType() {
             InternalUnsafeMethods.StaticGetType__Args _args = new InternalUnsafeMethods.StaticGetType__Args() {
             };
             IntPtr _engineResult = InternalUnsafeMethods.StaticGetType()(_args);
             return new EngineTypeInfo(_engineResult);
        }

        /// <description>
        /// Dumps a breakdown of all declared assets.
        /// </description>
        /// <returns>No return value.</returns>
        public void DumpDeclaredAssets() {
             InternalUnsafeMethods.DumpDeclaredAssets__Args _args = new InternalUnsafeMethods.DumpDeclaredAssets__Args() {
             };
             InternalUnsafeMethods.DumpDeclaredAssets()(ObjectPtr, _args);
        }

        /// <description>
        /// Gets the maximum number of loaded external assets.
        /// </description>
        /// <returns>Returns the maximum number of loaded external assets.</returns>
        public bool GetMaxLoadedExternalAssetCount() {
             InternalUnsafeMethods.GetMaxLoadedExternalAssetCount__Args _args = new InternalUnsafeMethods.GetMaxLoadedExternalAssetCount__Args() {
             };
             bool _engineResult = InternalUnsafeMethods.GetMaxLoadedExternalAssetCount()(ObjectPtr, _args);
             return _engineResult;
        }

        /// <description>
        /// Gets the number of loaded external assets.
        /// </description>
        /// <returns>Returns the number of loaded external assets.</returns>
        public bool GetLoadedExternalAssetCount() {
             InternalUnsafeMethods.GetLoadedExternalAssetCount__Args _args = new InternalUnsafeMethods.GetLoadedExternalAssetCount__Args() {
             };
             bool _engineResult = InternalUnsafeMethods.GetLoadedExternalAssetCount()(ObjectPtr, _args);
             return _engineResult;
        }

        /// <description>
        /// Gets the maximum number of loaded internal assets.
        /// </description>
        /// <returns>Returns the maximum number of loaded internal assets.</returns>
        public bool GetMaxLoadedInternalAssetCount() {
             InternalUnsafeMethods.GetMaxLoadedInternalAssetCount__Args _args = new InternalUnsafeMethods.GetMaxLoadedInternalAssetCount__Args() {
             };
             bool _engineResult = InternalUnsafeMethods.GetMaxLoadedInternalAssetCount()(ObjectPtr, _args);
             return _engineResult;
        }

        /// <description>
        /// Gets the number of loaded internal assets.
        /// </description>
        /// <returns>Returns the number of loaded internal assets.</returns>
        public bool GetLoadedInternalAssetCount() {
             InternalUnsafeMethods.GetLoadedInternalAssetCount__Args _args = new InternalUnsafeMethods.GetLoadedInternalAssetCount__Args() {
             };
             bool _engineResult = InternalUnsafeMethods.GetLoadedInternalAssetCount()(ObjectPtr, _args);
             return _engineResult;
        }

        /// <description>
        /// Gets the number of asset referenced.
        /// </description>
        /// <returns>Returns the number of asset references.</returns>
        public bool GetReferencedAssetCount() {
             InternalUnsafeMethods.GetReferencedAssetCount__Args _args = new InternalUnsafeMethods.GetReferencedAssetCount__Args() {
             };
             bool _engineResult = InternalUnsafeMethods.GetReferencedAssetCount()(ObjectPtr, _args);
             return _engineResult;
        }

        /// <description>
        /// Gets the number of declared assets.
        /// </description>
        /// <returns>Returns the number of declared assets.</returns>
        public bool GetDeclaredAssetCount() {
             InternalUnsafeMethods.GetDeclaredAssetCount__Args _args = new InternalUnsafeMethods.GetDeclaredAssetCount__Args() {
             };
             bool _engineResult = InternalUnsafeMethods.GetDeclaredAssetCount()(ObjectPtr, _args);
             return _engineResult;
        }

        /// <description>
        /// Performs an asset query searching for the specified loose file.
        /// </description>
        /// <param name="assetQuery">The asset query object that will be populated with the results.</param>
        /// <param name="assetLooseFile">The loose-file used by the asset to search for.</param>
        /// <param name="assetQueryAsSource">Whether to use the asset query as the data-source rather than the asset managers database or not.  Doing this effectively filters the asset query.  Optional: Defaults to false.</param>
        /// <returns>The number of asset Ids found or (-1) if an error occurred.</returns>
        public int FindAssetLooseFile(string assetQuery = "", string assetLooseFile = "", bool assetQueryAsSource = false) {
             InternalUnsafeMethods.FindAssetLooseFile__Args _args = new InternalUnsafeMethods.FindAssetLooseFile__Args() {
                assetQuery = assetQuery,
                assetLooseFile = assetLooseFile,
                assetQueryAsSource = assetQueryAsSource,
             };
             int _engineResult = InternalUnsafeMethods.FindAssetLooseFile()(ObjectPtr, _args);
             return _engineResult;
        }

        /// <description>
        /// Performs an asset query searching for the specified asset tag name(s).
        /// </description>
        /// <param name="assetQuery">The asset query object that will be populated with the results.</param>
        /// <param name="assetTagNames">The asset tag name or names to search for.  Multiple names can be specified using comma, space, tab or newline separation.  Tags use an OR operation i.e. only assets tagged with ANY of the specified tags will be returned.</param>
        /// <param name="assetQueryAsSource">Whether to use the asset query as the data-source rather than the asset managers database or not.  Doing this effectively filters the asset query.  Optional: Defaults to false.</param>
        /// <returns>The number of asset Ids found or (-1) if an error occurred.</returns>
        public int FindTaggedAssets(string assetQuery = "", string assetTagNames = "", bool assetQueryAsSource = false) {
             InternalUnsafeMethods.FindTaggedAssets__Args _args = new InternalUnsafeMethods.FindTaggedAssets__Args() {
                assetQuery = assetQuery,
                assetTagNames = assetTagNames,
                assetQueryAsSource = assetQueryAsSource,
             };
             int _engineResult = InternalUnsafeMethods.FindTaggedAssets()(ObjectPtr, _args);
             return _engineResult;
        }

        /// <description>
        /// Performs an asset query searching for invalid asset references.
        /// </description>
        /// <param name="assetQuery">The asset query object that will be populated with the results.</param>
        /// <returns>The number of asset Ids found that are invalid or (-1) if an error occurred.</returns>
        public int FindInvalidAssetReferences(string assetQuery = "") {
             InternalUnsafeMethods.FindInvalidAssetReferences__Args _args = new InternalUnsafeMethods.FindInvalidAssetReferences__Args() {
                assetQuery = assetQuery,
             };
             int _engineResult = InternalUnsafeMethods.FindInvalidAssetReferences()(ObjectPtr, _args);
             return _engineResult;
        }

        /// <description>
        /// Performs an asset query searching for asset Ids that depend on the specified asset Id.
        /// </description>
        /// <param name="assetQuery">The asset query object that will be populated with the results.</param>
        /// <param name="assetId">The asset Id to query for any asset Ids that may depend on it.</param>
        /// <returns>The number of asset Ids found or (-1) if an error occurred.</returns>
        public int FindAssetIsDependedOn(string assetQuery = "", string assetId = "") {
             InternalUnsafeMethods.FindAssetIsDependedOn__Args _args = new InternalUnsafeMethods.FindAssetIsDependedOn__Args() {
                assetQuery = assetQuery,
                assetId = assetId,
             };
             int _engineResult = InternalUnsafeMethods.FindAssetIsDependedOn()(ObjectPtr, _args);
             return _engineResult;
        }

        /// <description>
        /// Performs an asset query searching for asset Ids that the specified asset Id depends on.
        /// </description>
        /// <param name="assetQuery">The asset query object that will be populated with the results.</param>
        /// <param name="assetId">The asset Id to query for any asset Ids that it depends on.</param>
        /// <returns>The number of asset Ids found or (-1) if an error occurred.</returns>
        public int FindAssetDependsOn(string assetQuery = "", string assetId = "") {
             InternalUnsafeMethods.FindAssetDependsOn__Args _args = new InternalUnsafeMethods.FindAssetDependsOn__Args() {
                assetQuery = assetQuery,
                assetId = assetId,
             };
             int _engineResult = InternalUnsafeMethods.FindAssetDependsOn()(ObjectPtr, _args);
             return _engineResult;
        }

        /// <description>
        /// Performs an asset query searching for the specified asset type.
        /// </description>
        /// <param name="assetQuery">The asset query object that will be populated with the results.</param>
        /// <param name="assetType">The asset type to search for.</param>
        /// <param name="assetQueryAsSource">Whether to use the asset query as the data-source rather than the asset managers database or not.  Doing this effectively filters the asset query.  Optional: Defaults to false.</param>
        /// <returns>The number of asset Ids found or (-1) if an error occurred.</returns>
        public int FindAssetType(string assetQuery = "", string assetType = "", bool assetQueryAsSource = false) {
             InternalUnsafeMethods.FindAssetType__Args _args = new InternalUnsafeMethods.FindAssetType__Args() {
                assetQuery = assetQuery,
                assetType = assetType,
                assetQueryAsSource = assetQueryAsSource,
             };
             int _engineResult = InternalUnsafeMethods.FindAssetType()(ObjectPtr, _args);
             return _engineResult;
        }

        /// <description>
        /// Performs an asset query searching for the specified asset private flag.
        /// </description>
        /// <param name="assetQuery">The asset query object that will be populated with the results.</param>
        /// <param name="assetPrivate">The asset private flag to search for.</param>
        /// <param name="assetQueryAsSource">Whether to use the asset query as the data-source rather than the asset managers database or not.  Doing this effectively filters the asset query.  Optional: Defaults to false.</param>
        /// <returns>The number of asset Ids found or (-1) if an error occurred.</returns>
        public int FindAssetPrivate(string assetQuery = "", bool assetPrivate = false, bool assetQueryAsSource = false) {
             InternalUnsafeMethods.FindAssetPrivate__Args _args = new InternalUnsafeMethods.FindAssetPrivate__Args() {
                assetQuery = assetQuery,
                assetPrivate = assetPrivate,
                assetQueryAsSource = assetQueryAsSource,
             };
             int _engineResult = InternalUnsafeMethods.FindAssetPrivate()(ObjectPtr, _args);
             return _engineResult;
        }

        /// <description>
        /// Performs an asset query searching for the specified asset internal flag.
        /// </description>
        /// <param name="assetQuery">The asset query object that will be populated with the results.</param>
        /// <param name="assetInternal">The asset internal flag to search for.</param>
        /// <param name="assetQueryAsSource">Whether to use the asset query as the data-source rather than the asset managers database or not.  Doing this effectively filters the asset query.  Optional: Defaults to false.</param>
        /// <returns>The number of asset Ids found or (-1) if an error occurred.</returns>
        public int FindAssetInternal(string assetQuery = "", bool assetInternal = false, bool assetQueryAsSource = false) {
             InternalUnsafeMethods.FindAssetInternal__Args _args = new InternalUnsafeMethods.FindAssetInternal__Args() {
                assetQuery = assetQuery,
                assetInternal = assetInternal,
                assetQueryAsSource = assetQueryAsSource,
             };
             int _engineResult = InternalUnsafeMethods.FindAssetInternal()(ObjectPtr, _args);
             return _engineResult;
        }

        /// <description>
        /// Performs an asset query searching for the specified asset auto-unload flag.
        /// </description>
        /// <param name="assetQuery">The asset query object that will be populated with the results.</param>
        /// <param name="assetInternal">The asset internal flag to search for.</param>
        /// <param name="assetQueryAsSource">Whether to use the asset query as the data-source rather than the asset managers database or not.  Doing this effectively filters the asset query.  Optional: Defaults to false.</param>
        /// <returns>The number of asset Ids found or (-1) if an error occurred.</returns>
        public int FindAssetAutoUnload(string assetQuery = "", bool assetAutoUnload = false, bool assetQueryAsSource = false) {
             InternalUnsafeMethods.FindAssetAutoUnload__Args _args = new InternalUnsafeMethods.FindAssetAutoUnload__Args() {
                assetQuery = assetQuery,
                assetAutoUnload = assetAutoUnload,
                assetQueryAsSource = assetQueryAsSource,
             };
             int _engineResult = InternalUnsafeMethods.FindAssetAutoUnload()(ObjectPtr, _args);
             return _engineResult;
        }

        /// <description>
        /// Performs an asset query searching for the specified asset category.
        /// </description>
        /// <param name="assetQuery">The asset query object that will be populated with the results.</param>
        /// <param name="assetCategory">The asset category to search for.</param>
        /// <param name="assetQueryAsSource">Whether to use the asset query as the data-source rather than the asset managers database or not.  Doing this effectively filters the asset query.  Optional: Defaults to false.</param>
        /// <returns>The number of asset Ids found or (-1) if an error occurred.</returns>
        public int FindAssetCategory(string assetQuery = "", string assetCategory = "", bool assetQueryAsSource = false) {
             InternalUnsafeMethods.FindAssetCategory__Args _args = new InternalUnsafeMethods.FindAssetCategory__Args() {
                assetQuery = assetQuery,
                assetCategory = assetCategory,
                assetQueryAsSource = assetQueryAsSource,
             };
             int _engineResult = InternalUnsafeMethods.FindAssetCategory()(ObjectPtr, _args);
             return _engineResult;
        }

        /// <description>
        /// Performs an asset query searching for the specified asset name.
        /// </description>
        /// <param name="assetQuery">The asset query object that will be populated with the results.</param>
        /// <param name="assetName">The asset name to search for.  This may be a partial name if 'partialName' is true.</param>
        /// <param name="partialName">Whether the asset name is to be used as a partial name or not.  Optional: Defaults to false.</param>
        /// <returns>The number of asset Ids found or (-1) if an error occurred.</returns>
        public int FindAssetName(string assetQuery = "", string assetName = "", bool partialName = false) {
             InternalUnsafeMethods.FindAssetName__Args _args = new InternalUnsafeMethods.FindAssetName__Args() {
                assetQuery = assetQuery,
                assetName = assetName,
                partialName = partialName,
             };
             int _engineResult = InternalUnsafeMethods.FindAssetName()(ObjectPtr, _args);
             return _engineResult;
        }

        /// <description>
        /// Performs an asset query searching for all assets optionally ignoring internal assets.
        /// </description>
        /// <param name="assetQuery">The asset query object that will be populated with the results.</param>
        /// <param name="ignoreInternal">Whether to ignore internal assets or not.  Optional: Defaults to true.</param>
        /// <param name="ignorePrivate">Whether to ignore private assets or not.  Optional: Defaults to true.</param>
        /// <returns>The number of asset Ids found or (-1) if an error occurred.</returns>
        public int FindAllAssets(string assetQuery = "", bool ignoreInternal = true, bool ignorePrivate = true) {
             InternalUnsafeMethods.FindAllAssets__Args _args = new InternalUnsafeMethods.FindAllAssets__Args() {
                assetQuery = assetQuery,
                ignoreInternal = ignoreInternal,
                ignorePrivate = ignorePrivate,
             };
             int _engineResult = InternalUnsafeMethods.FindAllAssets()(ObjectPtr, _args);
             return _engineResult;
        }

        /// <description>
        /// Gets the currently loaded asset tags manifest.
        /// </description>
        /// <returns>The currently loaded asset tags manifest or zero if not loaded.</returns>
        public int GetAssetTags() {
             InternalUnsafeMethods.GetAssetTags__Args _args = new InternalUnsafeMethods.GetAssetTags__Args() {
             };
             int _engineResult = InternalUnsafeMethods.GetAssetTags()(ObjectPtr, _args);
             return _engineResult;
        }

        /// <description>
        /// Restore the currently loaded asset tags manifest from disk (replace anything in memory).
        /// </description>
        /// <returns>Whether the restore was successful or not.</returns>
        public bool RestoreAssetTags() {
             InternalUnsafeMethods.RestoreAssetTags__Args _args = new InternalUnsafeMethods.RestoreAssetTags__Args() {
             };
             bool _engineResult = InternalUnsafeMethods.RestoreAssetTags()(ObjectPtr, _args);
             return _engineResult;
        }

        /// <description>
        /// Save the currently loaded asset tags manifest.
        /// </description>
        /// <returns>Whether the save was successful or not.</returns>
        public bool SaveAssetTags() {
             InternalUnsafeMethods.SaveAssetTags__Args _args = new InternalUnsafeMethods.SaveAssetTags__Args() {
             };
             bool _engineResult = InternalUnsafeMethods.SaveAssetTags()(ObjectPtr, _args);
             return _engineResult;
        }

        /// <description>
        /// Refresh all declared assets.
        /// </description>
        /// <param name="Whether">to include currently unloaded assets in the refresh or not.  Optional: Defaults to false.
        /// Refreshing all assets can be an expensive (time-consuming) operation to perform.</param>
        /// <returns>No return value.</returns>
        public void RefreshAllAssets(bool includeUnloaded = false) {
             InternalUnsafeMethods.RefreshAllAssets__Args _args = new InternalUnsafeMethods.RefreshAllAssets__Args() {
                includeUnloaded = includeUnloaded,
             };
             InternalUnsafeMethods.RefreshAllAssets()(ObjectPtr, _args);
        }

        /// <description>
        /// Refresh the specified asset Id.
        /// </description>
        /// <param name="assetId">The selected asset Id.</param>
        /// <returns>No return value.</returns>
        public void RefreshAsset(string assetId = "") {
             InternalUnsafeMethods.RefreshAsset__Args _args = new InternalUnsafeMethods.RefreshAsset__Args() {
                assetId = assetId,
             };
             InternalUnsafeMethods.RefreshAsset()(ObjectPtr, _args);
        }

        /// <description>
        /// Deletes the specified asset Id and optionally its loose files and asset dependencies.
        /// </description>
        /// <param name="assetId">The selected asset Id.</param>
        /// <param name="deleteLooseFiles">Whether to delete an assets loose files or not.</param>
        /// <param name="deleteDependencies">Whether to delete assets that depend on this asset or not.</param>
        /// <returns>Whether the asset deletion was successful or not.  A failure only indicates that the specified asset was not deleted but dependent assets and their loose files may have being deleted.</returns>
        public bool DeleteAsset(string assetId = "", bool deleteLooseFiles = false, bool deleteDependencies = false) {
             InternalUnsafeMethods.DeleteAsset__Args _args = new InternalUnsafeMethods.DeleteAsset__Args() {
                assetId = assetId,
                deleteLooseFiles = deleteLooseFiles,
                deleteDependencies = deleteDependencies,
             };
             bool _engineResult = InternalUnsafeMethods.DeleteAsset()(ObjectPtr, _args);
             return _engineResult;
        }

        /// <description>
        /// Purge all assets that are not referenced even if they are set to not auto-unload.
        /// Assets can be in this state because they are either set to not auto-unload or the asset manager has/is disabling auto-unload.
        /// </description>
        /// <returns>No return value.</returns>
        public void PurgeAssets() {
             InternalUnsafeMethods.PurgeAssets__Args _args = new InternalUnsafeMethods.PurgeAssets__Args() {
             };
             InternalUnsafeMethods.PurgeAssets()(ObjectPtr, _args);
        }

        /// <description>
        /// Release the specified asset Id.
        /// The asset should have been acquired using 'acquireAsset'.
        /// </description>
        /// <param name="assetId">The selected asset Id.</param>
        /// <returns>Whether the asset was released or not.</returns>
        public bool ReleaseAsset(string assetId = "") {
             InternalUnsafeMethods.ReleaseAsset__Args _args = new InternalUnsafeMethods.ReleaseAsset__Args() {
                assetId = assetId,
             };
             bool _engineResult = InternalUnsafeMethods.ReleaseAsset()(ObjectPtr, _args);
             return _engineResult;
        }

        /// <description>
        /// Acquire the specified asset Id.
        /// You must release the asset once you're finish with it using 'releaseAsset'.
        /// </description>
        /// <param name="assetId">The selected asset Id.</param>
        /// <param name="asPrivate">Whether to acquire the asset Id as a private asset.</param>
        /// <returns>The acquired asset or NULL if not acquired.</returns>
        public string AcquireAsset(string assetId = "", bool asPrivate = false) {
             InternalUnsafeMethods.AcquireAsset__Args _args = new InternalUnsafeMethods.AcquireAsset__Args() {
                assetId = assetId,
                asPrivate = asPrivate,
             };
             IntPtr _engineResult = InternalUnsafeMethods.AcquireAsset()(ObjectPtr, _args);
             return StringMarshal.IntPtrToUtf8String(_engineResult);
        }

        /// <description>
        /// Rename referenced asset Id.
        /// </description>
        /// <param name="assetIdFrom">The selected asset Id to rename from.</param>
        /// <param name="assetIdFrom">The selected asset Id to rename to.</param>
        /// <returns>Whether the rename was successful or not.</returns>
        public bool RenameReferencedAsset(string assetIdFrom = "", string assetIdTo = "") {
             InternalUnsafeMethods.RenameReferencedAsset__Args _args = new InternalUnsafeMethods.RenameReferencedAsset__Args() {
                assetIdFrom = assetIdFrom,
                assetIdTo = assetIdTo,
             };
             bool _engineResult = InternalUnsafeMethods.RenameReferencedAsset()(ObjectPtr, _args);
             return _engineResult;
        }

        /// <description>
        /// Rename declared asset Id.
        /// </description>
        /// <param name="assetIdFrom">The selected asset Id to rename from.</param>
        /// <param name="assetIdFrom">The selected asset Id to rename to.</param>
        /// <returns>Whether the rename was successful or not.</returns>
        public bool RenameDeclaredAsset(string assetIdFrom = "", string assetIdTo = "") {
             InternalUnsafeMethods.RenameDeclaredAsset__Args _args = new InternalUnsafeMethods.RenameDeclaredAsset__Args() {
                assetIdFrom = assetIdFrom,
                assetIdTo = assetIdTo,
             };
             bool _engineResult = InternalUnsafeMethods.RenameDeclaredAsset()(ObjectPtr, _args);
             return _engineResult;
        }

        /// <description>
        /// Check whether the specified asset Id is referenced or not.
        /// </description>
        /// <param name="assetId">The selected asset Id.</param>
        /// <returns>Whether the specified asset Id is referenced or not.</returns>
        public bool IsReferencedAsset(string assetId = "") {
             InternalUnsafeMethods.IsReferencedAsset__Args _args = new InternalUnsafeMethods.IsReferencedAsset__Args() {
                assetId = assetId,
             };
             bool _engineResult = InternalUnsafeMethods.IsReferencedAsset()(ObjectPtr, _args);
             return _engineResult;
        }

        /// <description>
        /// Check whether the specified asset Id is declared or not.
        /// </description>
        /// <param name="assetId">The selected asset Id.</param>
        /// <returns>Whether the specified asset Id is declared or not.</returns>
        public bool IsDeclaredAsset(string assetId = "") {
             InternalUnsafeMethods.IsDeclaredAsset__Args _args = new InternalUnsafeMethods.IsDeclaredAsset__Args() {
                assetId = assetId,
             };
             bool _engineResult = InternalUnsafeMethods.IsDeclaredAsset()(ObjectPtr, _args);
             return _engineResult;
        }

        /// <description>
        /// Check whether the specified asset Id is loaded or not.
        /// </description>
        /// <param name="assetId">The selected asset Id.</param>
        /// <returns>Whether the specified asset Id is loaded or not.</returns>
        public bool IsAssetLoaded(string assetId = "") {
             InternalUnsafeMethods.IsAssetLoaded__Args _args = new InternalUnsafeMethods.IsAssetLoaded__Args() {
                assetId = assetId,
             };
             bool _engineResult = InternalUnsafeMethods.IsAssetLoaded()(ObjectPtr, _args);
             return _engineResult;
        }

        /// <description>
        /// Check whether the specified asset Id is auto - unload or not.
        /// </description>
        /// <param name="assetId">The selected asset Id.</param>
        /// <returns>Whether the specified asset Id is auto-unload or not.</returns>
        public bool IsAssetAutoUnload(string assetId = "") {
             InternalUnsafeMethods.IsAssetAutoUnload__Args _args = new InternalUnsafeMethods.IsAssetAutoUnload__Args() {
                assetId = assetId,
             };
             bool _engineResult = InternalUnsafeMethods.IsAssetAutoUnload()(ObjectPtr, _args);
             return _engineResult;
        }

        /// <description>
        /// Check whether the specified asset Id is private or not.
        /// </description>
        /// <param name="assetId">The selected asset Id.</param>
        /// <returns>Whether the specified asset Id is private or not.</returns>
        public bool IsAssetPrivate(string assetId = "") {
             InternalUnsafeMethods.IsAssetPrivate__Args _args = new InternalUnsafeMethods.IsAssetPrivate__Args() {
                assetId = assetId,
             };
             bool _engineResult = InternalUnsafeMethods.IsAssetPrivate()(ObjectPtr, _args);
             return _engineResult;
        }

        /// <description>
        /// Check whether the specified asset Id is internal or not.
        /// </description>
        /// <param name="assetId">The selected asset Id.</param>
        /// <returns>Whether the specified asset Id is internal or not.</returns>
        public bool IsAssetInternal(string assetId = "") {
             InternalUnsafeMethods.IsAssetInternal__Args _args = new InternalUnsafeMethods.IsAssetInternal__Args() {
                assetId = assetId,
             };
             bool _engineResult = InternalUnsafeMethods.IsAssetInternal()(ObjectPtr, _args);
             return _engineResult;
        }

        /// <description>
        /// Gets the module definition where the the specified asset Id is located.
        /// </description>
        /// <param name="assetId">The selected asset Id.</param>
        /// <returns>The module definition where the the specified asset Id is located.</returns>
        public string GetAssetModule(string assetId = "") {
             InternalUnsafeMethods.GetAssetModule__Args _args = new InternalUnsafeMethods.GetAssetModule__Args() {
                assetId = assetId,
             };
             IntPtr _engineResult = InternalUnsafeMethods.GetAssetModule()(ObjectPtr, _args);
             return StringMarshal.IntPtrToUtf8String(_engineResult);
        }

        /// <description>
        /// Gets the asset path (not including the asset file) from the specified asset Id.
        /// </description>
        /// <param name="assetId">The selected asset Id.</param>
        /// <returns>The asset path(not including the asset file) from the specified asset Id.</returns>
        public string GetAssetPath(string assetId = "") {
             InternalUnsafeMethods.GetAssetPath__Args _args = new InternalUnsafeMethods.GetAssetPath__Args() {
                assetId = assetId,
             };
             IntPtr _engineResult = InternalUnsafeMethods.GetAssetPath()(ObjectPtr, _args);
             return StringMarshal.IntPtrToUtf8String(_engineResult);
        }

        /// <description>
        /// Gets the asset file-path from the specified asset Id.
        /// </description>
        /// <param name="assetId">The selected asset Id.</param>
        /// <returns>The asset file - path from the specified asset Id.</returns>
        public string GetAssetFilePath(string assetId = "") {
             InternalUnsafeMethods.GetAssetFilePath__Args _args = new InternalUnsafeMethods.GetAssetFilePath__Args() {
                assetId = assetId,
             };
             IntPtr _engineResult = InternalUnsafeMethods.GetAssetFilePath()(ObjectPtr, _args);
             return StringMarshal.IntPtrToUtf8String(_engineResult);
        }

        /// <description>
        /// Gets the asset type from the specified asset Id.
        /// </description>
        /// <param name="assetId">The selected asset Id.</param>
        /// <returns>The asset type from the specified asset Id.</returns>
        public string GetAssetType(string assetId = "") {
             InternalUnsafeMethods.GetAssetType__Args _args = new InternalUnsafeMethods.GetAssetType__Args() {
                assetId = assetId,
             };
             IntPtr _engineResult = InternalUnsafeMethods.GetAssetType()(ObjectPtr, _args);
             return StringMarshal.IntPtrToUtf8String(_engineResult);
        }

        /// <description>
        /// Gets the asset category from the specified asset Id.
        /// </description>
        /// <param name="assetId">The selected asset Id.</param>
        /// <returns>The asset category from the specified asset Id.</returns>
        public string GetAssetCategory(string assetId = "") {
             InternalUnsafeMethods.GetAssetCategory__Args _args = new InternalUnsafeMethods.GetAssetCategory__Args() {
                assetId = assetId,
             };
             IntPtr _engineResult = InternalUnsafeMethods.GetAssetCategory()(ObjectPtr, _args);
             return StringMarshal.IntPtrToUtf8String(_engineResult);
        }

        /// <description>
        /// Gets the asset description from the specified asset Id.
        /// </description>
        /// <param name="assetId">The selected asset Id.</param>
        /// <returns>The asset description from the specified asset Id.</returns>
        public string GetAssetDescription(string assetId = "") {
             InternalUnsafeMethods.GetAssetDescription__Args _args = new InternalUnsafeMethods.GetAssetDescription__Args() {
                assetId = assetId,
             };
             IntPtr _engineResult = InternalUnsafeMethods.GetAssetDescription()(ObjectPtr, _args);
             return StringMarshal.IntPtrToUtf8String(_engineResult);
        }

        /// <description>
        /// Gets the asset name from the specified asset Id.
        /// </description>
        /// <param name="assetId">The selected asset Id.</param>
        /// <returns>The asset name from the specified asset Id.</returns>
        public string GetAssetName(string assetId = "") {
             InternalUnsafeMethods.GetAssetName__Args _args = new InternalUnsafeMethods.GetAssetName__Args() {
                assetId = assetId,
             };
             IntPtr _engineResult = InternalUnsafeMethods.GetAssetName()(ObjectPtr, _args);
             return StringMarshal.IntPtrToUtf8String(_engineResult);
        }

        /// <description>
        /// Remove the specified declared asset Id.
        /// </description>
        /// <param name="assetId">The selected asset Id.</param>
        /// <returns>Whether removing the declared asset was successful or not.</returns>
        public bool RemoveDeclaredAsset(string assetId = "") {
             InternalUnsafeMethods.RemoveDeclaredAsset__Args _args = new InternalUnsafeMethods.RemoveDeclaredAsset__Args() {
                assetId = assetId,
             };
             bool _engineResult = InternalUnsafeMethods.RemoveDeclaredAsset()(ObjectPtr, _args);
             return _engineResult;
        }

        /// <description>
        /// Remove any the declared assets specified by the module definition.
        /// </description>
        /// <param name="moduleDefinition">The module definition that may contain declared assets.</param>
        /// <returns>Whether removing declared assets was successful or not.</returns>
        public bool RemoveDeclaredAssets(string moduleDefinition = "") {
             InternalUnsafeMethods.RemoveDeclaredAssets__Args _args = new InternalUnsafeMethods.RemoveDeclaredAssets__Args() {
                moduleDefinition = moduleDefinition,
             };
             bool _engineResult = InternalUnsafeMethods.RemoveDeclaredAssets()(ObjectPtr, _args);
             return _engineResult;
        }

        /// <description>
        /// Adds a private asset object.
        /// </description>
        /// <param name="assetObject">The asset object to add as a private asset.</param>
        /// <returns>The allocated private asset Id.</returns>
        public string AddPrivateAsset(string assetObject = "") {
             InternalUnsafeMethods.AddPrivateAsset__Args _args = new InternalUnsafeMethods.AddPrivateAsset__Args() {
                assetObject = assetObject,
             };
             IntPtr _engineResult = InternalUnsafeMethods.AddPrivateAsset()(ObjectPtr, _args);
             return StringMarshal.IntPtrToUtf8String(_engineResult);
        }

        /// <description>
        /// Add the specified asset against the specified module definition.
        /// </description>
        /// <param name="moduleDefinition">The module definition that may contain declared assets.</param>
        /// <returns>Whether adding declared assets was successful or not.</returns>
        public bool AddDeclaredAsset(string moduleDefinition = "", string assetFilePath = "") {
             InternalUnsafeMethods.AddDeclaredAsset__Args _args = new InternalUnsafeMethods.AddDeclaredAsset__Args() {
                moduleDefinition = moduleDefinition,
                assetFilePath = assetFilePath,
             };
             bool _engineResult = InternalUnsafeMethods.AddDeclaredAsset()(ObjectPtr, _args);
             return _engineResult;
        }

        /// <description>
        /// Add any the declared assets specified by the module definition.
        /// </description>
        /// <param name="moduleDefinition">The module definition specifies the asset manifest.</param>
        /// <returns>Whether adding declared assets was successful or not.</returns>
        public bool AddModuleDeclaredAssets(string moduleDefinition = "") {
             InternalUnsafeMethods.AddModuleDeclaredAssets__Args _args = new InternalUnsafeMethods.AddModuleDeclaredAssets__Args() {
                moduleDefinition = moduleDefinition,
             };
             bool _engineResult = InternalUnsafeMethods.AddModuleDeclaredAssets()(ObjectPtr, _args);
             return _engineResult;
        }

        /// <description>
        /// Compile the referenced assets determined by the specified module definition.
        /// </description>
        /// <param name="moduleDefinition">The module definition specifies the asset manifest.</param>
        /// <returns>Whether the compilation was successful or not.</returns>
        public bool CompileReferencedAssets(string moduleDefinition = "") {
             InternalUnsafeMethods.CompileReferencedAssets__Args _args = new InternalUnsafeMethods.CompileReferencedAssets__Args() {
                moduleDefinition = moduleDefinition,
             };
             bool _engineResult = InternalUnsafeMethods.CompileReferencedAssets()(ObjectPtr, _args);
             return _engineResult;
        }


        /// <value>
        /// <description>
        /// Whether the asset manager echos extra information to the console or not.
        /// </description>
        /// </value>
        public DynamicFieldVector<bool> EchoInfo {
            get => new DynamicFieldVector<bool>(
                    this, 
                    "EchoInfo", 
                    608, 
                    val => GenericMarshal.StringTo<bool>(val),
                    obj => GenericMarshal.ToString(obj)
                );
        }


        /// <value>
        /// <description>
        /// Whether the asset manager should ignore unloading of auto-unload assets or not.
        /// </description>
        /// </value>
        public DynamicFieldVector<bool> IgnoreAutoUnload {
            get => new DynamicFieldVector<bool>(
                    this, 
                    "IgnoreAutoUnload", 
                    609, 
                    val => GenericMarshal.StringTo<bool>(val),
                    obj => GenericMarshal.ToString(obj)
                );
        }
    }
}