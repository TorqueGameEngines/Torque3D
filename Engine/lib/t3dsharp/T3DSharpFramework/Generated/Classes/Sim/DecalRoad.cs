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
    /// <summary>A strip shaped decal defined by spine nodes which clips against Terrain objects.</summary>
    /// <description>
    /// DecalRoad is for representing a road or path ( or other inventive things ) across a TerrainBlock. It renders as a decal and is therefore only for features that do not need geometric depth.
    /// 
    /// The Material assigned to DecalRoad should tile vertically.
    /// </description>
    public unsafe class DecalRoad : SceneObject {
        public DecalRoad(bool pRegister = false) 
            : base(pRegister) {
        }
        
        public DecalRoad(string pName, bool pRegister) 
            : this(false) {
            Name = pName;
            if (pRegister) {
                RegisterObject();
            }
        }
        
        public DecalRoad(string pName) 
            : this(pName, false) {
        }
        
        public DecalRoad(string pName, string pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(Engine.Sim.FindObject<SimObject>(pParent));
        }
        
        public DecalRoad(string pName, SimObject pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(pParent);
        }
        
        public DecalRoad(SimObject pObj) 
            : base(pObj) {
        }
        
        public DecalRoad(IntPtr pObj) 
            : base(pObj) {
        }
        
		protected override void CreateObjectPtr()
		{
			ObjectPtr = InternalUnsafeMethods.Create()(new InternalUnsafeMethods.Create__Args());
		}

        #region UnsafeNativeMethods
        new internal struct InternalUnsafeMethods {
            [StructLayout(LayoutKind.Sequential)]
            internal struct PostApply__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _PostApply(IntPtr _this, PostApply__Args args);
            private static _PostApply _PostApplyFunc;
            internal static _PostApply PostApply() {
                if (_PostApplyFunc == null) {
                    _PostApplyFunc =
                        (_PostApply)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnDecalRoad_postApply"), typeof(_PostApply));
                }
                
                return _PostApplyFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct Regenerate__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _Regenerate(IntPtr _this, Regenerate__Args args);
            private static _Regenerate _RegenerateFunc;
            internal static _Regenerate Regenerate() {
                if (_RegenerateFunc == null) {
                    _RegenerateFunc =
                        (_Regenerate)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnDecalRoad_regenerate"), typeof(_Regenerate));
                }
                
                return _RegenerateFunc;
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
                                "fnDecalRoad_staticGetType"), typeof(_StaticGetType));
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
                                "fnDecalRoad_create"), typeof(_Create));
                }
                
                return _CreateFunc;
            }
        }
        #endregion

        /// <description>
        /// Intended as a helper to developers and editor scripts.
        /// Force trigger an inspectPostApply. This will transmit the material and other fields ( not including nodes ) to client objects.
        /// </description>
        public void PostApply() {
             InternalUnsafeMethods.PostApply__Args _args = new InternalUnsafeMethods.PostApply__Args() {
             };
             InternalUnsafeMethods.PostApply()(ObjectPtr, _args);
        }

        /// <description>
        /// Intended as a helper to developers and editor scripts.
        /// Force DecalRoad to update it's spline and reclip geometry.
        /// </description>
        public void Regenerate() {
             InternalUnsafeMethods.Regenerate__Args _args = new InternalUnsafeMethods.Regenerate__Args() {
             };
             InternalUnsafeMethods.Regenerate()(ObjectPtr, _args);
        }

        /// <description>
        /// Get the type info object for the DecalRoad class.
        /// </description>
        /// <returns>The type info object for DecalRoad</returns>
        public static EngineTypeInfo StaticGetType() {
             InternalUnsafeMethods.StaticGetType__Args _args = new InternalUnsafeMethods.StaticGetType__Args() {
             };
             IntPtr _engineResult = InternalUnsafeMethods.StaticGetType()(_args);
             return new EngineTypeInfo(_engineResult);
        }


        /// <value>
        /// <description>
        /// Material used for rendering.
        /// </description>
        /// </value>
        public string Material {
            get => GenericMarshal.StringTo<string>(GetFieldValue("Material"));
            set => SetFieldValue("Material", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// The length in meters of textures mapped to the DecalRoad
        /// </description>
        /// </value>
        public float TextureLength {
            get => GenericMarshal.StringTo<float>(GetFieldValue("textureLength"));
            set => SetFieldValue("textureLength", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Angle in degrees - DecalRoad will subdivided the spline if its curve is greater than this threshold.
        /// </description>
        /// </value>
        public float BreakAngle {
            get => GenericMarshal.StringTo<float>(GetFieldValue("breakAngle"));
            set => SetFieldValue("breakAngle", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// DecalRoad(s) are rendered in descending renderPriority order.
        /// </description>
        /// </value>
        public int RenderPriority {
            get => GenericMarshal.StringTo<int>(GetFieldValue("renderPriority"));
            set => SetFieldValue("renderPriority", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Do not modify, for internal use.
        /// </description>
        /// </value>
        public string Node {
            get => GenericMarshal.StringTo<string>(GetFieldValue("Node"));
            set => SetFieldValue("Node", GenericMarshal.ToString(value));
        }
    }
}