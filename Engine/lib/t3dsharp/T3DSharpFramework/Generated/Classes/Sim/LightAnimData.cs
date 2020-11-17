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
    /// <summary>A datablock which defines and performs light animation, such as rotation, brightness fade, and colorization.</summary>
    /// <description>
    /// 
    /// </description>
    /// <code>
    /// datablock LightAnimData( SubtlePulseLightAnim )
    /// {
    ///    brightnessA = 0.5;
    ///    brightnessZ = 1;
    ///    brightnessPeriod = 1;
    ///    brightnessKeys = "aza";
    ///    brightnessSmooth = true;
    /// };
    /// </code>
    /// <see cref="LightBase" />
    /// <see cref="LightDescription" />
    public unsafe class LightAnimData : SimDataBlock {
        public LightAnimData(bool pRegister = false) 
            : base(pRegister) {
        }
        
        public LightAnimData(string pName, bool pRegister) 
            : this(false) {
            Name = pName;
            if (pRegister) {
                RegisterObject();
            }
        }
        
        public LightAnimData(string pName) 
            : this(pName, false) {
        }
        
        public LightAnimData(string pName, string pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(Engine.Sim.FindObject<SimObject>(pParent));
        }
        
        public LightAnimData(string pName, SimObject pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(pParent);
        }
        
        public LightAnimData(SimObject pObj) 
            : base(pObj) {
        }
        
        public LightAnimData(IntPtr pObj) 
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
                                "fnLightAnimData_staticGetType"), typeof(_StaticGetType));
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
                                "fnLightAnimData_create"), typeof(_Create));
                }
                
                return _CreateFunc;
            }
        }
        #endregion

        /// <description>
        /// Get the type info object for the LightAnimData class.
        /// </description>
        /// <returns>The type info object for LightAnimData</returns>
        public static EngineTypeInfo StaticGetType() {
             InternalUnsafeMethods.StaticGetType__Args _args = new InternalUnsafeMethods.StaticGetType__Args() {
             };
             IntPtr _engineResult = InternalUnsafeMethods.StaticGetType()(_args);
             return new EngineTypeInfo(_engineResult);
        }


        /// <value>
        /// <description>
        /// The value of the A key in the keyframe sequence.
        /// </description>
        /// </value>
        public DynamicFieldVector<float> OffsetA {
            get => new DynamicFieldVector<float>(
                    this, 
                    "offsetA", 
                    3, 
                    val => GenericMarshal.StringTo<float>(val),
                    obj => GenericMarshal.ToString(obj)
                );
        }


        /// <value>
        /// <description>
        /// The value of the Z key in the keyframe sequence.
        /// </description>
        /// </value>
        public DynamicFieldVector<float> OffsetZ {
            get => new DynamicFieldVector<float>(
                    this, 
                    "OffsetZ", 
                    3, 
                    val => GenericMarshal.StringTo<float>(val),
                    obj => GenericMarshal.ToString(obj)
                );
        }


        /// <value>
        /// <description>
        /// The animation time for keyframe sequence.
        /// </description>
        /// </value>
        public DynamicFieldVector<float> OffsetPeriod {
            get => new DynamicFieldVector<float>(
                    this, 
                    "offsetPeriod", 
                    3, 
                    val => GenericMarshal.StringTo<float>(val),
                    obj => GenericMarshal.ToString(obj)
                );
        }


        /// <value>
        /// <description>
        /// The keyframe sequence encoded into a string where characters from A to Z define a position between the two animation values.
        /// </description>
        /// </value>
        public DynamicFieldVector<string> OffsetKeys {
            get => new DynamicFieldVector<string>(
                    this, 
                    "offsetKeys", 
                    3, 
                    val => GenericMarshal.StringTo<string>(val),
                    obj => GenericMarshal.ToString(obj)
                );
        }


        /// <value>
        /// <description>
        /// If true the transition between keyframes will be smooth.
        /// </description>
        /// </value>
        public DynamicFieldVector<bool> OffsetSmooth {
            get => new DynamicFieldVector<bool>(
                    this, 
                    "offsetSmooth", 
                    3, 
                    val => GenericMarshal.StringTo<bool>(val),
                    obj => GenericMarshal.ToString(obj)
                );
        }


        /// <value>
        /// <description>
        /// The value of the A key in the keyframe sequence.
        /// </description>
        /// </value>
        public DynamicFieldVector<float> RotA {
            get => new DynamicFieldVector<float>(
                    this, 
                    "rotA", 
                    3, 
                    val => GenericMarshal.StringTo<float>(val),
                    obj => GenericMarshal.ToString(obj)
                );
        }


        /// <value>
        /// <description>
        /// The value of the Z key in the keyframe sequence.
        /// </description>
        /// </value>
        public DynamicFieldVector<float> RotZ {
            get => new DynamicFieldVector<float>(
                    this, 
                    "rotZ", 
                    3, 
                    val => GenericMarshal.StringTo<float>(val),
                    obj => GenericMarshal.ToString(obj)
                );
        }


        /// <value>
        /// <description>
        /// The animation time for keyframe sequence.
        /// </description>
        /// </value>
        public DynamicFieldVector<float> RotPeriod {
            get => new DynamicFieldVector<float>(
                    this, 
                    "rotPeriod", 
                    3, 
                    val => GenericMarshal.StringTo<float>(val),
                    obj => GenericMarshal.ToString(obj)
                );
        }


        /// <value>
        /// <description>
        /// The keyframe sequence encoded into a string where characters from A to Z define a position between the two animation values.
        /// </description>
        /// </value>
        public DynamicFieldVector<string> RotKeys {
            get => new DynamicFieldVector<string>(
                    this, 
                    "rotKeys", 
                    3, 
                    val => GenericMarshal.StringTo<string>(val),
                    obj => GenericMarshal.ToString(obj)
                );
        }


        /// <value>
        /// <description>
        /// If true the transition between keyframes will be smooth.
        /// </description>
        /// </value>
        public DynamicFieldVector<bool> RotSmooth {
            get => new DynamicFieldVector<bool>(
                    this, 
                    "rotSmooth", 
                    3, 
                    val => GenericMarshal.StringTo<bool>(val),
                    obj => GenericMarshal.ToString(obj)
                );
        }


        /// <value>
        /// <description>
        /// The value of the A key in the keyframe sequence.
        /// </description>
        /// </value>
        public DynamicFieldVector<float> ColorA {
            get => new DynamicFieldVector<float>(
                    this, 
                    "colorA", 
                    3, 
                    val => GenericMarshal.StringTo<float>(val),
                    obj => GenericMarshal.ToString(obj)
                );
        }


        /// <value>
        /// <description>
        /// The value of the Z key in the keyframe sequence.
        /// </description>
        /// </value>
        public DynamicFieldVector<float> ColorZ {
            get => new DynamicFieldVector<float>(
                    this, 
                    "colorZ", 
                    3, 
                    val => GenericMarshal.StringTo<float>(val),
                    obj => GenericMarshal.ToString(obj)
                );
        }


        /// <value>
        /// <description>
        /// The animation time for keyframe sequence.
        /// </description>
        /// </value>
        public DynamicFieldVector<float> ColorPeriod {
            get => new DynamicFieldVector<float>(
                    this, 
                    "colorPeriod", 
                    3, 
                    val => GenericMarshal.StringTo<float>(val),
                    obj => GenericMarshal.ToString(obj)
                );
        }


        /// <value>
        /// <description>
        /// The keyframe sequence encoded into a string where characters from A to Z define a position between the two animation values.
        /// </description>
        /// </value>
        public DynamicFieldVector<string> ColorKeys {
            get => new DynamicFieldVector<string>(
                    this, 
                    "colorKeys", 
                    3, 
                    val => GenericMarshal.StringTo<string>(val),
                    obj => GenericMarshal.ToString(obj)
                );
        }


        /// <value>
        /// <description>
        /// If true the transition between keyframes will be smooth.
        /// </description>
        /// </value>
        public DynamicFieldVector<bool> ColorSmooth {
            get => new DynamicFieldVector<bool>(
                    this, 
                    "colorSmooth", 
                    3, 
                    val => GenericMarshal.StringTo<bool>(val),
                    obj => GenericMarshal.ToString(obj)
                );
        }


        /// <value>
        /// <description>
        /// The value of the A key in the keyframe sequence.
        /// </description>
        /// </value>
        public float BrightnessA {
            get => GenericMarshal.StringTo<float>(GetFieldValue("brightnessA"));
            set => SetFieldValue("brightnessA", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// The value of the Z key in the keyframe sequence.
        /// </description>
        /// </value>
        public float BrightnessZ {
            get => GenericMarshal.StringTo<float>(GetFieldValue("brightnessZ"));
            set => SetFieldValue("brightnessZ", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// The animation time for keyframe sequence.
        /// </description>
        /// </value>
        public float BrightnessPeriod {
            get => GenericMarshal.StringTo<float>(GetFieldValue("brightnessPeriod"));
            set => SetFieldValue("brightnessPeriod", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// The keyframe sequence encoded into a string where characters from A to Z define a position between the two animation values.
        /// </description>
        /// </value>
        public string BrightnessKeys {
            get => GenericMarshal.StringTo<string>(GetFieldValue("brightnessKeys"));
            set => SetFieldValue("brightnessKeys", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// If true the transition between keyframes will be smooth.
        /// </description>
        /// </value>
        public bool BrightnessSmooth {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("brightnessSmooth"));
            set => SetFieldValue("brightnessSmooth", GenericMarshal.ToString(value));
        }
    }
}