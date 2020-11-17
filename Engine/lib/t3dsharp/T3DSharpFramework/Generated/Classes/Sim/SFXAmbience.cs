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
    /// <summary>A datablock that describes an ambient sound space.</summary>
    /// <description>
    /// Each ambience datablock captures the properties of a unique ambient sound space.  A sound space is comprised of:
    /// - an ambient audio track that is played when the listener is inside the space,
    /// - a reverb environment that is active inside the space, and
    /// - a number of SFXStates that are activated when entering the space and deactivated when exiting it.
    /// 
    /// Each of these properties is optional.
    /// 
    /// An important characteristic of ambient audio spaces is that their unique nature is not determined by their location in space but rather by their SFXAmbience datablock.  This means that the same SFXAmbience datablock assigned to multiple locations in a level represents the same unique audio space to the sound system.
    /// 
    /// This is an important distinction for the ambient sound mixer which will activate a given ambient audio space only once at any one time regardless of how many intersecting audio spaces with the same SFXAmbience datablock assigned the listener may currently be in.
    /// 
    /// All SFXAmbience instances are automatically added to the global
    /// </description>
    /// <code>
    /// singleton SFXAmbience( Underwater )
    /// {
    ///    environment = AudioEnvUnderwater;
    ///    soundTrack = ScubaSoundList;
    ///    states[ 0 ] = AudioLocationUnderwater;
    /// };
    /// </code>
    /// <see cref="SFXEnvironment" />
    /// <see cref="SFXTrack" />
    /// <see cref="SFXState" />
    /// <see cref="LevelInfo::soundAmbience" />
    /// <see cref="Zone::soundAmbience" />
    public unsafe class SFXAmbience : SimDataBlock {
        public SFXAmbience(bool pRegister = false) 
            : base(pRegister) {
        }
        
        public SFXAmbience(string pName, bool pRegister) 
            : this(false) {
            Name = pName;
            if (pRegister) {
                RegisterObject();
            }
        }
        
        public SFXAmbience(string pName) 
            : this(pName, false) {
        }
        
        public SFXAmbience(string pName, string pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(Engine.Sim.FindObject<SimObject>(pParent));
        }
        
        public SFXAmbience(string pName, SimObject pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(pParent);
        }
        
        public SFXAmbience(SimObject pObj) 
            : base(pObj) {
        }
        
        public SFXAmbience(IntPtr pObj) 
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
                                "fnSFXAmbience_staticGetType"), typeof(_StaticGetType));
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
                                "fnSFXAmbience_create"), typeof(_Create));
                }
                
                return _CreateFunc;
            }
        }
        #endregion

        /// <description>
        /// Get the type info object for the SFXAmbience class.
        /// </description>
        /// <returns>The type info object for SFXAmbience</returns>
        public static EngineTypeInfo StaticGetType() {
             InternalUnsafeMethods.StaticGetType__Args _args = new InternalUnsafeMethods.StaticGetType__Args() {
             };
             IntPtr _engineResult = InternalUnsafeMethods.StaticGetType()(_args);
             return new EngineTypeInfo(_engineResult);
        }


        /// <value>
        /// <description>
        /// Reverb environment active in the ambience zone.
        /// </description>
        /// </value>
        public SFXEnvironment Environment {
            get => GenericMarshal.StringTo<SFXEnvironment>(GetFieldValue("environment"));
            set => SetFieldValue("environment", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Sound track to play in the ambience zone.
        /// </description>
        /// </value>
        public SFXTrack SoundTrack {
            get => GenericMarshal.StringTo<SFXTrack>(GetFieldValue("soundTrack"));
            set => SetFieldValue("soundTrack", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// The rolloff factor to apply to distance-based volume attenuation in this space.
        /// Defaults to 1.0.
        /// </description>
        /// <remarks> This applies to the logarithmic distance model only.
        /// 
        /// </remarks>
        /// </value>
        public float RolloffFactor {
            get => GenericMarshal.StringTo<float>(GetFieldValue("rolloffFactor"));
            set => SetFieldValue("rolloffFactor", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// The factor to apply to the doppler affect in this space.
        /// Defaults to 0.5.
        /// </description>
        /// </value>
        public float DopplerFactor {
            get => GenericMarshal.StringTo<float>(GetFieldValue("dopplerFactor"));
            set => SetFieldValue("dopplerFactor", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// States to activate when the ambient zone is entered.
        /// When the ambient sound state is entered, all states associated with the state will be activated (given that they are not disabled) and deactivated when the space is exited again.
        /// </description>
        /// </value>
        public DynamicFieldVector<SFXState> States {
            get => new DynamicFieldVector<SFXState>(
                    this, 
                    "states", 
                    4, 
                    val => GenericMarshal.StringTo<SFXState>(val),
                    obj => GenericMarshal.ToString(obj)
                );
        }
    }
}