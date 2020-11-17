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
    /// <summary>An xmod datablock.</summary>
    /// <description>
    /// 
    /// </description>
    public unsafe class afxXM_WaveBaseData : afxXM_WeightedBaseData {
        public afxXM_WaveBaseData(bool pRegister = false) 
            : base(pRegister) {
        }
        
        public afxXM_WaveBaseData(string pName, bool pRegister) 
            : this(false) {
            Name = pName;
            if (pRegister) {
                RegisterObject();
            }
        }
        
        public afxXM_WaveBaseData(string pName) 
            : this(pName, false) {
        }
        
        public afxXM_WaveBaseData(string pName, string pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(Engine.Sim.FindObject<SimObject>(pParent));
        }
        
        public afxXM_WaveBaseData(string pName, SimObject pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(pParent);
        }
        
        public afxXM_WaveBaseData(SimObject pObj) 
            : base(pObj) {
        }
        
        public afxXM_WaveBaseData(IntPtr pObj) 
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
                                "fnafxXM_WaveBaseData_staticGetType"), typeof(_StaticGetType));
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
                                "fnafxXM_WaveBaseData_create"), typeof(_Create));
                }
                
                return _CreateFunc;
            }
        }
        #endregion

        /// <description>
        /// Get the type info object for the afxXM_WaveBaseData class.
        /// </description>
        /// <returns>The type info object for afxXM_WaveBaseData</returns>
        public static EngineTypeInfo StaticGetType() {
             InternalUnsafeMethods.StaticGetType__Args _args = new InternalUnsafeMethods.StaticGetType__Args() {
             };
             IntPtr _engineResult = InternalUnsafeMethods.StaticGetType()(_args);
             return new EngineTypeInfo(_engineResult);
        }


        /// <value>
        /// <description>
        /// ...
        /// </description>
        /// </value>
        public afxXM_WaveFormType Waveform {
            get => GenericMarshal.StringTo<afxXM_WaveFormType>(GetFieldValue("waveform"));
            set => SetFieldValue("waveform", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// ...
        /// </description>
        /// </value>
        public afxXM_WaveParamType Parameter {
            get => GenericMarshal.StringTo<afxXM_WaveParamType>(GetFieldValue("parameter"));
            set => SetFieldValue("parameter", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// ...
        /// </description>
        /// </value>
        public afxXM_WaveOpType Op {
            get => GenericMarshal.StringTo<afxXM_WaveOpType>(GetFieldValue("op"));
            set => SetFieldValue("op", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// waves per second
        /// </description>
        /// </value>
        public float Speed {
            get => GenericMarshal.StringTo<float>(GetFieldValue("speed"));
            set => SetFieldValue("speed", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// ...
        /// </description>
        /// </value>
        public float SpeedVariance {
            get => GenericMarshal.StringTo<float>(GetFieldValue("speedVariance"));
            set => SetFieldValue("speedVariance", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// ...
        /// </description>
        /// </value>
        public float Acceleration {
            get => GenericMarshal.StringTo<float>(GetFieldValue("acceleration"));
            set => SetFieldValue("acceleration", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// ...
        /// </description>
        /// </value>
        public float PhaseShift {
            get => GenericMarshal.StringTo<float>(GetFieldValue("phaseShift"));
            set => SetFieldValue("phaseShift", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// ...
        /// </description>
        /// </value>
        public float DutyCycle {
            get => GenericMarshal.StringTo<float>(GetFieldValue("dutyCycle"));
            set => SetFieldValue("dutyCycle", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// ...
        /// </description>
        /// </value>
        public float DutyShift {
            get => GenericMarshal.StringTo<float>(GetFieldValue("dutyShift"));
            set => SetFieldValue("dutyShift", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// ...
        /// </description>
        /// </value>
        public float OffDutyT {
            get => GenericMarshal.StringTo<float>(GetFieldValue("offDutyT"));
            set => SetFieldValue("offDutyT", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// ...
        /// </description>
        /// </value>
        public ByteRange WavesPerPulse {
            get => GenericMarshal.StringTo<ByteRange>(GetFieldValue("wavesPerPulse"));
            set => SetFieldValue("wavesPerPulse", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// ...
        /// </description>
        /// </value>
        public ByteRange WavesPerRest {
            get => GenericMarshal.StringTo<ByteRange>(GetFieldValue("wavesPerRest"));
            set => SetFieldValue("wavesPerRest", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// ...
        /// </description>
        /// </value>
        public float RestDuration {
            get => GenericMarshal.StringTo<float>(GetFieldValue("restDuration"));
            set => SetFieldValue("restDuration", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// ...
        /// </description>
        /// </value>
        public float RestDurationVariance {
            get => GenericMarshal.StringTo<float>(GetFieldValue("restDurationVariance"));
            set => SetFieldValue("restDurationVariance", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// ...
        /// </description>
        /// </value>
        public Point3F Axis {
            get => GenericMarshal.StringTo<Point3F>(GetFieldValue("axis"));
            set => SetFieldValue("axis", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// ...
        /// </description>
        /// </value>
        public bool AxisIsLocal {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("axisIsLocal"));
            set => SetFieldValue("axisIsLocal", GenericMarshal.ToString(value));
        }
    }
}