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
    /// <summary>Description of a reverb environment.</summary>
    /// <description>
    /// A reverb environment specifies how the audio mixer should render advanced environmental audio effects.  
    /// 
    /// To use reverb environments in your level, set up one or more ambient audio spaces, assign reverb environments appropriately, and then attach the SFXAmbiences to your LevelInfo (taking effect globally) or Zone objects (taking effect locally).
    /// 
    /// To define your own custom reverb environments, it is usually easiest to adapt one of the pre-existing reverb definitions:
    /// </description>
    /// <see href="http://www.atc.creative.com/algorithms/eax20.pdf" />
    /// <see href="http://connect.creativelabs.com/developer/Gaming/Forms/AllItems.aspx" />
    /// <see cref="SFXAmbience::environment" />
    public unsafe class SFXEnvironment : SimDataBlock {
        public SFXEnvironment(bool pRegister = false) 
            : base(pRegister) {
        }
        
        public SFXEnvironment(string pName, bool pRegister) 
            : this(false) {
            Name = pName;
            if (pRegister) {
                RegisterObject();
            }
        }
        
        public SFXEnvironment(string pName) 
            : this(pName, false) {
        }
        
        public SFXEnvironment(string pName, string pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(Engine.Sim.FindObject<SimObject>(pParent));
        }
        
        public SFXEnvironment(string pName, SimObject pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(pParent);
        }
        
        public SFXEnvironment(SimObject pObj) 
            : base(pObj) {
        }
        
        public SFXEnvironment(IntPtr pObj) 
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
                                "fnSFXEnvironment_staticGetType"), typeof(_StaticGetType));
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
                                "fnSFXEnvironment_create"), typeof(_Create));
                }
                
                return _CreateFunc;
            }
        }
        #endregion

        /// <description>
        /// Get the type info object for the SFXEnvironment class.
        /// </description>
        /// <returns>The type info object for SFXEnvironment</returns>
        public static EngineTypeInfo StaticGetType() {
             InternalUnsafeMethods.StaticGetType__Args _args = new InternalUnsafeMethods.StaticGetType__Args() {
             };
             IntPtr _engineResult = InternalUnsafeMethods.StaticGetType()(_args);
             return new EngineTypeInfo(_engineResult);
        }


        /// <value>
        /// <description>
        /// Density of reverb environment.
        /// </description>
        /// </value>
        public float ReverbDensity {
            get => GenericMarshal.StringTo<float>(GetFieldValue("reverbDensity"));
            set => SetFieldValue("reverbDensity", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Environment diffusion.
        /// </description>
        /// </value>
        public float ReverbDiffusion {
            get => GenericMarshal.StringTo<float>(GetFieldValue("reverbDiffusion"));
            set => SetFieldValue("reverbDiffusion", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Reverb Gain Level.
        /// </description>
        /// </value>
        public float ReverbGain {
            get => GenericMarshal.StringTo<float>(GetFieldValue("reverbGain"));
            set => SetFieldValue("reverbGain", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Reverb Gain to high frequencies
        /// </description>
        /// </value>
        public float ReverbGainHF {
            get => GenericMarshal.StringTo<float>(GetFieldValue("reverbGainHF"));
            set => SetFieldValue("reverbGainHF", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Reverb Gain to high frequencies
        /// </description>
        /// </value>
        public float ReverbGainLF {
            get => GenericMarshal.StringTo<float>(GetFieldValue("reverbGainLF"));
            set => SetFieldValue("reverbGainLF", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Decay time for the reverb.
        /// </description>
        /// </value>
        public float ReverbDecayTime {
            get => GenericMarshal.StringTo<float>(GetFieldValue("reverbDecayTime"));
            set => SetFieldValue("reverbDecayTime", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// High frequency decay time ratio.
        /// </description>
        /// </value>
        public float ReverbDecayHFRatio {
            get => GenericMarshal.StringTo<float>(GetFieldValue("reverbDecayHFRatio"));
            set => SetFieldValue("reverbDecayHFRatio", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// High frequency decay time ratio.
        /// </description>
        /// </value>
        public float ReverbDecayLFRatio {
            get => GenericMarshal.StringTo<float>(GetFieldValue("reverbDecayLFRatio"));
            set => SetFieldValue("reverbDecayLFRatio", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Reflection Gain.
        /// </description>
        /// </value>
        public float ReflectionsGain {
            get => GenericMarshal.StringTo<float>(GetFieldValue("reflectionsGain"));
            set => SetFieldValue("reflectionsGain", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// How long to delay reflections.
        /// </description>
        /// </value>
        public float ReflectionDelay {
            get => GenericMarshal.StringTo<float>(GetFieldValue("reflectionDelay"));
            set => SetFieldValue("reflectionDelay", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Reflection reverberation panning vector.
        /// </description>
        /// </value>
        public DynamicFieldVector<float> ReflectionsPan {
            get => new DynamicFieldVector<float>(
                    this, 
                    "reflectionsPan", 
                    3, 
                    val => GenericMarshal.StringTo<float>(val),
                    obj => GenericMarshal.ToString(obj)
                );
        }


        /// <value>
        /// <description>
        /// Late reverb gain amount.
        /// </description>
        /// </value>
        public float LateReverbGain {
            get => GenericMarshal.StringTo<float>(GetFieldValue("lateReverbGain"));
            set => SetFieldValue("lateReverbGain", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Late reverb delay time.
        /// </description>
        /// </value>
        public float LateReverbDelay {
            get => GenericMarshal.StringTo<float>(GetFieldValue("lateReverbDelay"));
            set => SetFieldValue("lateReverbDelay", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Late reverberation panning vector.
        /// </description>
        /// </value>
        public DynamicFieldVector<float> LateReverbPan {
            get => new DynamicFieldVector<float>(
                    this, 
                    "lateReverbPan", 
                    3, 
                    val => GenericMarshal.StringTo<float>(val),
                    obj => GenericMarshal.ToString(obj)
                );
        }


        /// <value>
        /// <description>
        /// Reverb echo time.
        /// </description>
        /// </value>
        public float ReverbEchoTime {
            get => GenericMarshal.StringTo<float>(GetFieldValue("reverbEchoTime"));
            set => SetFieldValue("reverbEchoTime", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Reverb echo depth.
        /// </description>
        /// </value>
        public float ReverbEchoDepth {
            get => GenericMarshal.StringTo<float>(GetFieldValue("reverbEchoDepth"));
            set => SetFieldValue("reverbEchoDepth", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Reverb Modulation time.
        /// </description>
        /// </value>
        public float ReverbModTime {
            get => GenericMarshal.StringTo<float>(GetFieldValue("reverbModTime"));
            set => SetFieldValue("reverbModTime", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Reverb Modulation time.
        /// </description>
        /// </value>
        public float ReverbModDepth {
            get => GenericMarshal.StringTo<float>(GetFieldValue("reverbModDepth"));
            set => SetFieldValue("reverbModDepth", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// High Frequency air absorbtion
        /// </description>
        /// </value>
        public float AirAbsorbtionGainHF {
            get => GenericMarshal.StringTo<float>(GetFieldValue("airAbsorbtionGainHF"));
            set => SetFieldValue("airAbsorbtionGainHF", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Reverb High Frequency Reference.
        /// </description>
        /// </value>
        public float ReverbHFRef {
            get => GenericMarshal.StringTo<float>(GetFieldValue("reverbHFRef"));
            set => SetFieldValue("reverbHFRef", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Reverb Low Frequency Reference.
        /// </description>
        /// </value>
        public float ReverbLFRef {
            get => GenericMarshal.StringTo<float>(GetFieldValue("reverbLFRef"));
            set => SetFieldValue("reverbLFRef", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Rolloff factor for reverb.
        /// </description>
        /// </value>
        public float RoomRolloffFactor {
            get => GenericMarshal.StringTo<float>(GetFieldValue("roomRolloffFactor"));
            set => SetFieldValue("roomRolloffFactor", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// High Frequency decay limit.
        /// </description>
        /// </value>
        public int DecayHFLimit {
            get => GenericMarshal.StringTo<int>(GetFieldValue("decayHFLimit"));
            set => SetFieldValue("decayHFLimit", GenericMarshal.ToString(value));
        }
    }
}