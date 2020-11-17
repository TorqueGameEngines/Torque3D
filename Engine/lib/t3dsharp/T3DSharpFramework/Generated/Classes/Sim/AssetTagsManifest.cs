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
    public unsafe class AssetTagsManifest : SimObject {
        public AssetTagsManifest(bool pRegister = false) 
            : base(pRegister) {
        }
        
        public AssetTagsManifest(string pName, bool pRegister) 
            : this(false) {
            Name = pName;
            if (pRegister) {
                RegisterObject();
            }
        }
        
        public AssetTagsManifest(string pName) 
            : this(pName, false) {
        }
        
        public AssetTagsManifest(string pName, string pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(Engine.Sim.FindObject<SimObject>(pParent));
        }
        
        public AssetTagsManifest(string pName, SimObject pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(pParent);
        }
        
        public AssetTagsManifest(SimObject pObj) 
            : base(pObj) {
        }
        
        public AssetTagsManifest(IntPtr pObj) 
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
                                "fnAssetTagsManifest_staticGetType"), typeof(_StaticGetType));
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
                                "fnAssetTagsManifest_create"), typeof(_Create));
                }
                
                return _CreateFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct HasTag__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string assetId;
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string tagName;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            [return: MarshalAs(UnmanagedType.I1)]
            internal delegate bool _HasTag(IntPtr _this, HasTag__Args args);
            private static _HasTag _HasTagFunc;
            internal static _HasTag HasTag() {
                if (_HasTagFunc == null) {
                    _HasTagFunc =
                        (_HasTag)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnAssetTagsManifest_hasTag"), typeof(_HasTag));
                }
                
                return _HasTagFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct Untag__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string assetId;
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string tagName;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            [return: MarshalAs(UnmanagedType.I1)]
            internal delegate bool _Untag(IntPtr _this, Untag__Args args);
            private static _Untag _UntagFunc;
            internal static _Untag Untag() {
                if (_UntagFunc == null) {
                    _UntagFunc =
                        (_Untag)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnAssetTagsManifest_untag"), typeof(_Untag));
                }
                
                return _UntagFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct Tag__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string assetId;
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string tagName;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            [return: MarshalAs(UnmanagedType.I1)]
            internal delegate bool _Tag(IntPtr _this, Tag__Args args);
            private static _Tag _TagFunc;
            internal static _Tag Tag() {
                if (_TagFunc == null) {
                    _TagFunc =
                        (_Tag)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnAssetTagsManifest_tag"), typeof(_Tag));
                }
                
                return _TagFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct GetAssetTag__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string assetId;
                internal int tagIndex;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            
            internal delegate IntPtr _GetAssetTag(IntPtr _this, GetAssetTag__Args args);
            private static _GetAssetTag _GetAssetTagFunc;
            internal static _GetAssetTag GetAssetTag() {
                if (_GetAssetTagFunc == null) {
                    _GetAssetTagFunc =
                        (_GetAssetTag)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnAssetTagsManifest_getAssetTag"), typeof(_GetAssetTag));
                }
                
                return _GetAssetTagFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct GetAssetTagCount__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string assetId;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate int _GetAssetTagCount(IntPtr _this, GetAssetTagCount__Args args);
            private static _GetAssetTagCount _GetAssetTagCountFunc;
            internal static _GetAssetTagCount GetAssetTagCount() {
                if (_GetAssetTagCountFunc == null) {
                    _GetAssetTagCountFunc =
                        (_GetAssetTagCount)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnAssetTagsManifest_getAssetTagCount"), typeof(_GetAssetTagCount));
                }
                
                return _GetAssetTagCountFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct GetTag__Args
            {
                internal int tagIndex;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            
            internal delegate IntPtr _GetTag(IntPtr _this, GetTag__Args args);
            private static _GetTag _GetTagFunc;
            internal static _GetTag GetTag() {
                if (_GetTagFunc == null) {
                    _GetTagFunc =
                        (_GetTag)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnAssetTagsManifest_getTag"), typeof(_GetTag));
                }
                
                return _GetTagFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct GetTagCount__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate int _GetTagCount(IntPtr _this, GetTagCount__Args args);
            private static _GetTagCount _GetTagCountFunc;
            internal static _GetTagCount GetTagCount() {
                if (_GetTagCountFunc == null) {
                    _GetTagCountFunc =
                        (_GetTagCount)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnAssetTagsManifest_getTagCount"), typeof(_GetTagCount));
                }
                
                return _GetTagCountFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct IsTag__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string tagName;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            [return: MarshalAs(UnmanagedType.I1)]
            internal delegate bool _IsTag(IntPtr _this, IsTag__Args args);
            private static _IsTag _IsTagFunc;
            internal static _IsTag IsTag() {
                if (_IsTagFunc == null) {
                    _IsTagFunc =
                        (_IsTag)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnAssetTagsManifest_isTag"), typeof(_IsTag));
                }
                
                return _IsTagFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct DeleteTag__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string tagName;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            [return: MarshalAs(UnmanagedType.I1)]
            internal delegate bool _DeleteTag(IntPtr _this, DeleteTag__Args args);
            private static _DeleteTag _DeleteTagFunc;
            internal static _DeleteTag DeleteTag() {
                if (_DeleteTagFunc == null) {
                    _DeleteTagFunc =
                        (_DeleteTag)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnAssetTagsManifest_deleteTag"), typeof(_DeleteTag));
                }
                
                return _DeleteTagFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct RenameTag__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string oldTagName;
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string newTagName;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            [return: MarshalAs(UnmanagedType.I1)]
            internal delegate bool _RenameTag(IntPtr _this, RenameTag__Args args);
            private static _RenameTag _RenameTagFunc;
            internal static _RenameTag RenameTag() {
                if (_RenameTagFunc == null) {
                    _RenameTagFunc =
                        (_RenameTag)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnAssetTagsManifest_renameTag"), typeof(_RenameTag));
                }
                
                return _RenameTagFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct CreateTag__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string tagName;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _CreateTag(IntPtr _this, CreateTag__Args args);
            private static _CreateTag _CreateTagFunc;
            internal static _CreateTag CreateTag() {
                if (_CreateTagFunc == null) {
                    _CreateTagFunc =
                        (_CreateTag)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnAssetTagsManifest_createTag"), typeof(_CreateTag));
                }
                
                return _CreateTagFunc;
            }
        }
        #endregion

        /// <description>
        /// Get the type info object for the AssetTagsManifest class.
        /// </description>
        /// <returns>The type info object for AssetTagsManifest</returns>
        public static EngineTypeInfo StaticGetType() {
             InternalUnsafeMethods.StaticGetType__Args _args = new InternalUnsafeMethods.StaticGetType__Args() {
             };
             IntPtr _engineResult = InternalUnsafeMethods.StaticGetType()(_args);
             return new EngineTypeInfo(_engineResult);
        }

        /// <description>
        /// Checks whether the asset Id is tagged with the specified asset tag.
        /// </description>
        /// <param name="assetId">The asset Id to check.</param>
        /// <param name="tagName">The tag name to check.</param>
        /// <returns>Whether the asset Id is tagged with the specified asset tag or not.</returns>
        public bool HasTag(string assetId, string tagName) {
             InternalUnsafeMethods.HasTag__Args _args = new InternalUnsafeMethods.HasTag__Args() {
                assetId = assetId,
                tagName = tagName,
             };
             bool _engineResult = InternalUnsafeMethods.HasTag()(ObjectPtr, _args);
             return _engineResult;
        }

        /// <description>
        /// Un-tags the asset Id from the specified asset tag.
        /// </description>
        /// <param name="assetId">The asset Id to un - tag.</param>
        /// <param name="tagName">The tag name to un - assign.</param>
        /// <returns>Whether the un - tag operation was successful or not.</returns>
        public bool Untag(string assetId, string tagName) {
             InternalUnsafeMethods.Untag__Args _args = new InternalUnsafeMethods.Untag__Args() {
                assetId = assetId,
                tagName = tagName,
             };
             bool _engineResult = InternalUnsafeMethods.Untag()(ObjectPtr, _args);
             return _engineResult;
        }

        /// <description>
        /// Tags the asset Id with the specified asset tag.
        /// </description>
        /// <param name="assetId">The asset Id to tag.</param>
        /// <param name="tagName">The tag name to assign.</param>
        /// <returns>Whether the tag operation was successful or not.</returns>
        public bool Tag(string assetId, string tagName) {
             InternalUnsafeMethods.Tag__Args _args = new InternalUnsafeMethods.Tag__Args() {
                assetId = assetId,
                tagName = tagName,
             };
             bool _engineResult = InternalUnsafeMethods.Tag()(ObjectPtr, _args);
             return _engineResult;
        }

        /// <description>
        /// Gets the asset tag on the specified asset Id at the specified index.
        /// </description>
        /// <param name="assetId">The asset Id to count tags on.</param>
        /// <param name="tagIndex">The asset tag index.This must be 0 to the asset tag count less one.</param>
        /// <returns>The asset tag on the specified asset Id at the specified index or NULL if invalid.</returns>
        public string GetAssetTag(string assetId, int tagIndex) {
             InternalUnsafeMethods.GetAssetTag__Args _args = new InternalUnsafeMethods.GetAssetTag__Args() {
                assetId = assetId,
                tagIndex = tagIndex,
             };
             IntPtr _engineResult = InternalUnsafeMethods.GetAssetTag()(ObjectPtr, _args);
             return StringMarshal.IntPtrToUtf8String(_engineResult);
        }

        /// <description>
        /// Gets the asset tag count on the specified asset Id.
        /// </description>
        /// <param name="assetId">The asset Id to count tags on.</param>
        /// <returns>The asset tag count on the specified asset Id.</returns>
        public int GetAssetTagCount(string assetId) {
             InternalUnsafeMethods.GetAssetTagCount__Args _args = new InternalUnsafeMethods.GetAssetTagCount__Args() {
                assetId = assetId,
             };
             int _engineResult = InternalUnsafeMethods.GetAssetTagCount()(ObjectPtr, _args);
             return _engineResult;
        }

        /// <description>
        /// Gets the asset tag at the specified index.
        /// </description>
        /// <param name="tagIndex">The asset tag index.This must be 0 to the asset tag count less one.</param>
        /// <returns>The asset tag at the specified index or NULL if invalid.</returns>
        public string GetTag(int tagIndex) {
             InternalUnsafeMethods.GetTag__Args _args = new InternalUnsafeMethods.GetTag__Args() {
                tagIndex = tagIndex,
             };
             IntPtr _engineResult = InternalUnsafeMethods.GetTag()(ObjectPtr, _args);
             return StringMarshal.IntPtrToUtf8String(_engineResult);
        }

        /// <description>
        /// Gets the total asset tag count.
        /// </description>
        /// <returns>The total asset tag count.</returns>
        public int GetTagCount() {
             InternalUnsafeMethods.GetTagCount__Args _args = new InternalUnsafeMethods.GetTagCount__Args() {
             };
             int _engineResult = InternalUnsafeMethods.GetTagCount()(ObjectPtr, _args);
             return _engineResult;
        }

        /// <description>
        /// Checks whether the specified asset tag exists or not.
        /// </description>
        /// <param name="tagName">The tag name to check.</param>
        /// <returns>Whether the specified asset tag exists or not.</returns>
        public bool IsTag(string tagName) {
             InternalUnsafeMethods.IsTag__Args _args = new InternalUnsafeMethods.IsTag__Args() {
                tagName = tagName,
             };
             bool _engineResult = InternalUnsafeMethods.IsTag()(ObjectPtr, _args);
             return _engineResult;
        }

        /// <description>
        /// Deletes an asset tag.
        /// </description>
        /// <param name="tagName">The tag name to delete.</param>
        /// <returns>Whether the asset tag was deleted or not.</returns>
        public bool DeleteTag(string tagName) {
             InternalUnsafeMethods.DeleteTag__Args _args = new InternalUnsafeMethods.DeleteTag__Args() {
                tagName = tagName,
             };
             bool _engineResult = InternalUnsafeMethods.DeleteTag()(ObjectPtr, _args);
             return _engineResult;
        }

        /// <description>
        /// Renames an existing asset tag.
        /// </description>
        /// <param name="tagName">The tag name to rename.</param>
        /// <param name="newTagName">The new tag name to assign.</param>
        /// <returns>Whether the asset tag was renamed or not.</returns>
        public bool RenameTag(string oldTagName, string newTagName) {
             InternalUnsafeMethods.RenameTag__Args _args = new InternalUnsafeMethods.RenameTag__Args() {
                oldTagName = oldTagName,
                newTagName = newTagName,
             };
             bool _engineResult = InternalUnsafeMethods.RenameTag()(ObjectPtr, _args);
             return _engineResult;
        }

        /// <description>
        /// Creates an asset tag.
        /// </description>
        /// <param name="tagName">The tag name to create.</param>
        /// <returns>No return value.</returns>
        public void CreateTag(string tagName = "") {
             InternalUnsafeMethods.CreateTag__Args _args = new InternalUnsafeMethods.CreateTag__Args() {
                tagName = tagName,
             };
             InternalUnsafeMethods.CreateTag()(ObjectPtr, _args);
        }
    }
}