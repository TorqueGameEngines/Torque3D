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
    /// <summary>A datablock that specifies a Camera Shake effect.</summary>
    /// <description>
    /// Camera Shake internally utilizes the standard Torque CameraShake class to implement a shaken camera effect.
    /// </description>
    public unsafe class afxCameraShakeData : GameBaseData {
        public afxCameraShakeData(bool pRegister = false) 
            : base(pRegister) {
        }
        
        public afxCameraShakeData(string pName, bool pRegister) 
            : this(false) {
            Name = pName;
            if (pRegister) {
                RegisterObject();
            }
        }
        
        public afxCameraShakeData(string pName) 
            : this(pName, false) {
        }
        
        public afxCameraShakeData(string pName, string pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(Engine.Sim.FindObject<SimObject>(pParent));
        }
        
        public afxCameraShakeData(string pName, SimObject pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(pParent);
        }
        
        public afxCameraShakeData(SimObject pObj) 
            : base(pObj) {
        }
        
        public afxCameraShakeData(IntPtr pObj) 
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
                                "fnafxCameraShakeData_staticGetType"), typeof(_StaticGetType));
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
                                "fnafxCameraShakeData_create"), typeof(_Create));
                }
                
                return _CreateFunc;
            }
        }
        #endregion

        /// <description>
        /// Get the type info object for the afxCameraShakeData class.
        /// </description>
        /// <returns>The type info object for afxCameraShakeData</returns>
        public static EngineTypeInfo StaticGetType() {
             InternalUnsafeMethods.StaticGetType__Args _args = new InternalUnsafeMethods.StaticGetType__Args() {
             };
             IntPtr _engineResult = InternalUnsafeMethods.StaticGetType()(_args);
             return new EngineTypeInfo(_engineResult);
        }


        /// <value>
        /// <description>
        /// The camera shake frequencies for all three axes: X, Y, Z.
        /// </description>
        /// </value>
        public Point3F Frequency {
            get => GenericMarshal.StringTo<Point3F>(GetFieldValue("Frequency"));
            set => SetFieldValue("Frequency", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// The camera shake amplitudes for all three axes: X, Y, Z.
        /// </description>
        /// </value>
        public Point3F Amplitude {
            get => GenericMarshal.StringTo<Point3F>(GetFieldValue("Amplitude"));
            set => SetFieldValue("Amplitude", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Radius about the effect position in which shaking will be applied.
        /// </description>
        /// </value>
        public float Radius {
            get => GenericMarshal.StringTo<float>(GetFieldValue("radius"));
            set => SetFieldValue("radius", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Magnitude by which shaking decreases over distance to radius.
        /// </description>
        /// </value>
        public float Falloff {
            get => GenericMarshal.StringTo<float>(GetFieldValue("Falloff"));
            set => SetFieldValue("Falloff", GenericMarshal.ToString(value));
        }
    }
}