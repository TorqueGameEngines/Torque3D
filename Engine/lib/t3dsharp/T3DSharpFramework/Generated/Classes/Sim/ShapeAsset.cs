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
    public unsafe class ShapeAsset : AssetBase {
        public ShapeAsset(bool pRegister = false) 
            : base(pRegister) {
        }
        
        public ShapeAsset(string pName, bool pRegister) 
            : this(false) {
            Name = pName;
            if (pRegister) {
                RegisterObject();
            }
        }
        
        public ShapeAsset(string pName) 
            : this(pName, false) {
        }
        
        public ShapeAsset(string pName, string pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(Engine.Sim.FindObject<SimObject>(pParent));
        }
        
        public ShapeAsset(string pName, SimObject pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(pParent);
        }
        
        public ShapeAsset(SimObject pObj) 
            : base(pObj) {
        }
        
        public ShapeAsset(IntPtr pObj) 
            : base(pObj) {
        }
        
		protected override void CreateObjectPtr()
		{
			ObjectPtr = InternalUnsafeMethods.Create()(new InternalUnsafeMethods.Create__Args());
		}

        #region UnsafeNativeMethods
        new internal struct InternalUnsafeMethods {
            [StructLayout(LayoutKind.Sequential)]
            internal struct GetShapeFile__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            
            internal delegate IntPtr _GetShapeFile(IntPtr _this, GetShapeFile__Args args);
            private static _GetShapeFile _GetShapeFileFunc;
            internal static _GetShapeFile GetShapeFile() {
                if (_GetShapeFileFunc == null) {
                    _GetShapeFileFunc =
                        (_GetShapeFile)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnShapeAsset_getShapeFile"), typeof(_GetShapeFile));
                }
                
                return _GetShapeFileFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct GetAnimation__Args
            {
                internal int index;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate IntPtr _GetAnimation(IntPtr _this, GetAnimation__Args args);
            private static _GetAnimation _GetAnimationFunc;
            internal static _GetAnimation GetAnimation() {
                if (_GetAnimationFunc == null) {
                    _GetAnimationFunc =
                        (_GetAnimation)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnShapeAsset_getAnimation"), typeof(_GetAnimation));
                }
                
                return _GetAnimationFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct GetAnimationCount__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate int _GetAnimationCount(IntPtr _this, GetAnimationCount__Args args);
            private static _GetAnimationCount _GetAnimationCountFunc;
            internal static _GetAnimationCount GetAnimationCount() {
                if (_GetAnimationCountFunc == null) {
                    _GetAnimationCountFunc =
                        (_GetAnimationCount)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnShapeAsset_getAnimationCount"), typeof(_GetAnimationCount));
                }
                
                return _GetAnimationCountFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct GetMaterialCount__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate int _GetMaterialCount(IntPtr _this, GetMaterialCount__Args args);
            private static _GetMaterialCount _GetMaterialCountFunc;
            internal static _GetMaterialCount GetMaterialCount() {
                if (_GetMaterialCountFunc == null) {
                    _GetMaterialCountFunc =
                        (_GetMaterialCount)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnShapeAsset_getMaterialCount"), typeof(_GetMaterialCount));
                }
                
                return _GetMaterialCountFunc;
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
                                "fnShapeAsset_staticGetType"), typeof(_StaticGetType));
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
                                "fnShapeAsset_create"), typeof(_Create));
                }
                
                return _CreateFunc;
            }
        }
        #endregion

        /// <description>
        /// Creates a new script asset using the targetFilePath.
        /// </description>
        /// <returns>The bool result of calling exec</returns>
        public string GetShapeFile() {
             InternalUnsafeMethods.GetShapeFile__Args _args = new InternalUnsafeMethods.GetShapeFile__Args() {
             };
             IntPtr _engineResult = InternalUnsafeMethods.GetShapeFile()(ObjectPtr, _args);
             return StringMarshal.IntPtrToUtf8String(_engineResult);
        }

        /// <description>
        /// Gets a particular shape animation asset for this shape.
        /// </description>
        /// <param name="animation">asset index.</param>
        /// <returns>Shape Animation Asset.</returns>
        public ShapeAnimationAsset GetAnimation(int index = 0) {
             InternalUnsafeMethods.GetAnimation__Args _args = new InternalUnsafeMethods.GetAnimation__Args() {
                index = index,
             };
             IntPtr _engineResult = InternalUnsafeMethods.GetAnimation()(ObjectPtr, _args);
             return new ShapeAnimationAsset(_engineResult);
        }

        /// <description>
        /// Gets the number of animations for this shape asset.
        /// </description>
        /// <returns>Animation count.</returns>
        public int GetAnimationCount() {
             InternalUnsafeMethods.GetAnimationCount__Args _args = new InternalUnsafeMethods.GetAnimationCount__Args() {
             };
             int _engineResult = InternalUnsafeMethods.GetAnimationCount()(ObjectPtr, _args);
             return _engineResult;
        }

        /// <description>
        /// Gets the number of materials for this shape asset.
        /// </description>
        /// <returns>Material count.</returns>
        public int GetMaterialCount() {
             InternalUnsafeMethods.GetMaterialCount__Args _args = new InternalUnsafeMethods.GetMaterialCount__Args() {
             };
             int _engineResult = InternalUnsafeMethods.GetMaterialCount()(ObjectPtr, _args);
             return _engineResult;
        }

        /// <description>
        /// Get the type info object for the ShapeAsset class.
        /// </description>
        /// <returns>The type info object for ShapeAsset</returns>
        public static EngineTypeInfo StaticGetType() {
             InternalUnsafeMethods.StaticGetType__Args _args = new InternalUnsafeMethods.StaticGetType__Args() {
             };
             IntPtr _engineResult = InternalUnsafeMethods.StaticGetType()(_args);
             return new EngineTypeInfo(_engineResult);
        }


        /// <value>
        /// <description>
        /// Path to the shape file we want to render
        /// </description>
        /// </value>
        public string FileName {
            get => GenericMarshal.StringTo<string>(GetFieldValue("fileName"));
            set => SetFieldValue("fileName", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Path to the shape file we want to render
        /// </description>
        /// </value>
        public string ConstuctorFileName {
            get => GenericMarshal.StringTo<string>(GetFieldValue("constuctorFileName"));
            set => SetFieldValue("constuctorFileName", GenericMarshal.ToString(value));
        }
    }
}