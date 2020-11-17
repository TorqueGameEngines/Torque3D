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
    public unsafe class ImageAsset : AssetBase {
        public ImageAsset(bool pRegister = false) 
            : base(pRegister) {
        }
        
        public ImageAsset(string pName, bool pRegister) 
            : this(false) {
            Name = pName;
            if (pRegister) {
                RegisterObject();
            }
        }
        
        public ImageAsset(string pName) 
            : this(pName, false) {
        }
        
        public ImageAsset(string pName, string pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(Engine.Sim.FindObject<SimObject>(pParent));
        }
        
        public ImageAsset(string pName, SimObject pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(pParent);
        }
        
        public ImageAsset(SimObject pObj) 
            : base(pObj) {
        }
        
        public ImageAsset(IntPtr pObj) 
            : base(pObj) {
        }
        
		protected override void CreateObjectPtr()
		{
			ObjectPtr = InternalUnsafeMethods.Create()(new InternalUnsafeMethods.Create__Args());
		}

        #region UnsafeNativeMethods
        new internal struct InternalUnsafeMethods {
            [StructLayout(LayoutKind.Sequential)]
            internal struct GetImageInfo__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            
            internal delegate IntPtr _GetImageInfo(IntPtr _this, GetImageInfo__Args args);
            private static _GetImageInfo _GetImageInfoFunc;
            internal static _GetImageInfo GetImageInfo() {
                if (_GetImageInfoFunc == null) {
                    _GetImageInfoFunc =
                        (_GetImageInfo)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnImageAsset_getImageInfo"), typeof(_GetImageInfo));
                }
                
                return _GetImageInfoFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct GetImagePath__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            
            internal delegate IntPtr _GetImagePath(IntPtr _this, GetImagePath__Args args);
            private static _GetImagePath _GetImagePathFunc;
            internal static _GetImagePath GetImagePath() {
                if (_GetImagePathFunc == null) {
                    _GetImagePathFunc =
                        (_GetImagePath)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnImageAsset_getImagePath"), typeof(_GetImagePath));
                }
                
                return _GetImagePathFunc;
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
                                "fnImageAsset_staticGetType"), typeof(_StaticGetType));
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
                                "fnImageAsset_create"), typeof(_Create));
                }
                
                return _CreateFunc;
            }
        }
        #endregion

        /// <description>
        /// Creates an instance of the given GameObject given the asset definition.
        /// </description>
        /// <returns>The GameObject entity created from the asset.</returns>
        public string GetImageInfo() {
             InternalUnsafeMethods.GetImageInfo__Args _args = new InternalUnsafeMethods.GetImageInfo__Args() {
             };
             IntPtr _engineResult = InternalUnsafeMethods.GetImageInfo()(ObjectPtr, _args);
             return StringMarshal.IntPtrToUtf8String(_engineResult);
        }

        /// <description>
        /// Creates an instance of the given GameObject given the asset definition.
        /// </description>
        /// <returns>The GameObject entity created from the asset.</returns>
        public string GetImagePath() {
             InternalUnsafeMethods.GetImagePath__Args _args = new InternalUnsafeMethods.GetImagePath__Args() {
             };
             IntPtr _engineResult = InternalUnsafeMethods.GetImagePath()(ObjectPtr, _args);
             return StringMarshal.IntPtrToUtf8String(_engineResult);
        }

        /// <description>
        /// Get the type info object for the ImageAsset class.
        /// </description>
        /// <returns>The type info object for ImageAsset</returns>
        public static EngineTypeInfo StaticGetType() {
             InternalUnsafeMethods.StaticGetType__Args _args = new InternalUnsafeMethods.StaticGetType__Args() {
             };
             IntPtr _engineResult = InternalUnsafeMethods.StaticGetType()(_args);
             return new EngineTypeInfo(_engineResult);
        }


        /// <value>
        /// <description>
        /// Path to the image file.
        /// </description>
        /// </value>
        public string ImageFile {
            get => GenericMarshal.StringTo<string>(GetFieldValue("imageFile"));
            set => SetFieldValue("imageFile", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Should the image use mips? (Currently unused).
        /// </description>
        /// </value>
        public bool UseMips {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("UseMips"));
            set => SetFieldValue("UseMips", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Is the image in an HDR format? (Currently unused)
        /// </description>
        /// </value>
        public bool IsHDRImage {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("isHDRImage"));
            set => SetFieldValue("isHDRImage", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// What the main use-case for the image is for.
        /// </description>
        /// </value>
        public ImageAssetType ImageType {
            get => GenericMarshal.StringTo<ImageAssetType>(GetFieldValue("imageType"));
            set => SetFieldValue("imageType", GenericMarshal.ToString(value));
        }
    }
}