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
    /// <summary>A water volume defined by a 3D spline.</summary>
    /// <description>
    /// User may control width and depth per node and overall spline shape in three dimensions.
    /// 
    /// %River supports dynamic planar reflections (fullReflect) like all WaterObject classes, but keep in mind it is not necessarily a planar surface. For best visual quality a %River should be less reflective the more it twists and bends. This caution only applies to %Rivers with fullReflect on.
    /// </description>
    /// <see cref="WaterObject for inherited functionality." />
    public unsafe class River : WaterObject {
        public River(bool pRegister = false) 
            : base(pRegister) {
        }
        
        public River(string pName, bool pRegister) 
            : this(false) {
            Name = pName;
            if (pRegister) {
                RegisterObject();
            }
        }
        
        public River(string pName) 
            : this(pName, false) {
        }
        
        public River(string pName, string pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(Engine.Sim.FindObject<SimObject>(pParent));
        }
        
        public River(string pName, SimObject pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(pParent);
        }
        
        public River(SimObject pObj) 
            : base(pObj) {
        }
        
        public River(IntPtr pObj) 
            : base(pObj) {
        }
        
		protected override void CreateObjectPtr()
		{
			ObjectPtr = InternalUnsafeMethods.Create()(new InternalUnsafeMethods.Create__Args());
		}

        #region UnsafeNativeMethods
        new internal struct InternalUnsafeMethods {
            [StructLayout(LayoutKind.Sequential)]
            internal struct SetMaxDivisionSize__Args
            {
                internal float meters;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _SetMaxDivisionSize(IntPtr _this, SetMaxDivisionSize__Args args);
            private static _SetMaxDivisionSize _SetMaxDivisionSizeFunc;
            internal static _SetMaxDivisionSize SetMaxDivisionSize() {
                if (_SetMaxDivisionSizeFunc == null) {
                    _SetMaxDivisionSizeFunc =
                        (_SetMaxDivisionSize)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnRiver_setMaxDivisionSize"), typeof(_SetMaxDivisionSize));
                }
                
                return _SetMaxDivisionSizeFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct SetNodeDepth__Args
            {
                internal int idx;
                internal float meters;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _SetNodeDepth(IntPtr _this, SetNodeDepth__Args args);
            private static _SetNodeDepth _SetNodeDepthFunc;
            internal static _SetNodeDepth SetNodeDepth() {
                if (_SetNodeDepthFunc == null) {
                    _SetNodeDepthFunc =
                        (_SetNodeDepth)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnRiver_setNodeDepth"), typeof(_SetNodeDepth));
                }
                
                return _SetNodeDepthFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct SetBatchSize__Args
            {
                internal float meters;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _SetBatchSize(IntPtr _this, SetBatchSize__Args args);
            private static _SetBatchSize _SetBatchSizeFunc;
            internal static _SetBatchSize SetBatchSize() {
                if (_SetBatchSizeFunc == null) {
                    _SetBatchSizeFunc =
                        (_SetBatchSize)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnRiver_setBatchSize"), typeof(_SetBatchSize));
                }
                
                return _SetBatchSizeFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct SetMetersPerSegment__Args
            {
                internal float meters;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _SetMetersPerSegment(IntPtr _this, SetMetersPerSegment__Args args);
            private static _SetMetersPerSegment _SetMetersPerSegmentFunc;
            internal static _SetMetersPerSegment SetMetersPerSegment() {
                if (_SetMetersPerSegmentFunc == null) {
                    _SetMetersPerSegmentFunc =
                        (_SetMetersPerSegment)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnRiver_setMetersPerSegment"), typeof(_SetMetersPerSegment));
                }
                
                return _SetMetersPerSegmentFunc;
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
                                "fnRiver_regenerate"), typeof(_Regenerate));
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
                                "fnRiver_staticGetType"), typeof(_StaticGetType));
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
                                "fnRiver_create"), typeof(_Create));
                }
                
                return _CreateFunc;
            }
        }
        #endregion

        /// <description>
        /// Intended as a helper to developers and editor scripts.
        /// </description>
        /// <see cref="SubdivideLength field." />
        public void SetMaxDivisionSize(float meters) {
             InternalUnsafeMethods.SetMaxDivisionSize__Args _args = new InternalUnsafeMethods.SetMaxDivisionSize__Args() {
                meters = meters,
             };
             InternalUnsafeMethods.SetMaxDivisionSize()(ObjectPtr, _args);
        }

        /// <description>
        /// Intended as a helper to developers and editor scripts.
        /// Sets the depth in meters of a particular node.
        /// </description>
        public void SetNodeDepth(int idx, float meters) {
             InternalUnsafeMethods.SetNodeDepth__Args _args = new InternalUnsafeMethods.SetNodeDepth__Args() {
                idx = idx,
                meters = meters,
             };
             InternalUnsafeMethods.SetNodeDepth()(ObjectPtr, _args);
        }

        /// <description>
        /// Intended as a helper to developers and editor scripts.
        /// BatchSize is not currently used.
        /// </description>
        public void SetBatchSize(float meters) {
             InternalUnsafeMethods.SetBatchSize__Args _args = new InternalUnsafeMethods.SetBatchSize__Args() {
                meters = meters,
             };
             InternalUnsafeMethods.SetBatchSize()(ObjectPtr, _args);
        }

        /// <description>
        /// Intended as a helper to developers and editor scripts.
        /// </description>
        /// <see cref="SegmentLength field." />
        public void SetMetersPerSegment(float meters) {
             InternalUnsafeMethods.SetMetersPerSegment__Args _args = new InternalUnsafeMethods.SetMetersPerSegment__Args() {
                meters = meters,
             };
             InternalUnsafeMethods.SetMetersPerSegment()(ObjectPtr, _args);
        }

        /// <description>
        /// Intended as a helper to developers and editor scripts.
        /// Force River to recreate its geometry.
        /// </description>
        public void Regenerate() {
             InternalUnsafeMethods.Regenerate__Args _args = new InternalUnsafeMethods.Regenerate__Args() {
             };
             InternalUnsafeMethods.Regenerate()(ObjectPtr, _args);
        }

        /// <description>
        /// Get the type info object for the River class.
        /// </description>
        /// <returns>The type info object for River</returns>
        public static EngineTypeInfo StaticGetType() {
             InternalUnsafeMethods.StaticGetType__Args _args = new InternalUnsafeMethods.StaticGetType__Args() {
             };
             IntPtr _engineResult = InternalUnsafeMethods.StaticGetType()(_args);
             return new EngineTypeInfo(_engineResult);
        }


        /// <value>
        /// <description>
        /// Divide the River lengthwise into segments of this length in meters. These geometric volumes are used for spacial queries like determining containment.
        /// </description>
        /// </value>
        public float SegmentLength {
            get => GenericMarshal.StringTo<float>(GetFieldValue("SegmentLength"));
            set => SetFieldValue("SegmentLength", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// For purposes of generating the renderable geometry River segments are further subdivided such that no quad is of greater width or length than this distance in meters.
        /// </description>
        /// </value>
        public float SubdivideLength {
            get => GenericMarshal.StringTo<float>(GetFieldValue("SubdivideLength"));
            set => SetFieldValue("SubdivideLength", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Magnitude of the force vector applied to dynamic objects within the River.
        /// </description>
        /// </value>
        public float FlowMagnitude {
            get => GenericMarshal.StringTo<float>(GetFieldValue("FlowMagnitude"));
            set => SetFieldValue("FlowMagnitude", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Segments of the river at this distance in meters or greater will render as a single unsubdivided without undulation effects.
        /// </description>
        /// </value>
        public float LowLODDistance {
            get => GenericMarshal.StringTo<float>(GetFieldValue("LowLODDistance"));
            set => SetFieldValue("LowLODDistance", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// For internal use, do not modify.
        /// </description>
        /// </value>
        public string Node {
            get => GenericMarshal.StringTo<string>(GetFieldValue("Node"));
            set => SetFieldValue("Node", GenericMarshal.ToString(value));
        }
    }
}