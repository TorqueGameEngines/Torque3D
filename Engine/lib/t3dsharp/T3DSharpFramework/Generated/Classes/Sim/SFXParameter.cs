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
    /// <summary>A sound channel value that can be bound to multiple sound sources.</summary>
    /// <description>
    /// Parameters are special objects that isolate a specific property that sound sources can have and allows to bind this isolated instance to multiple sound sources such that when the value of the parameter changes, all sources bound to the parameter will have their respective property changed.
    /// 
    /// Parameters are identified and referenced by their #internalName.  This means that the SFXDescription::parameters and SFXTrack::parameters fields should contain the #internalNames of the SFXParameter objects which should be attached to the SFXSources when they are created.  No two SFXParameters should have the same #internalName.
    /// 
    /// All SFXParameter instances are automatically made children of the SFXParameterGroup.
    /// </description>
    /// <remarks> To simply control the volume and/or pitch levels of a group of sounds, it is easier and more efficient to use a sound source group rather than SFXParameters (see </remarks>
    /// <code>
    /// new SFXParameter( EngineRPMLevel )
    /// {
    ///    // Set the name by which this parameter is identified.
    ///    internalName = "EngineRPMLevel";
    /// 
    ///    // Let this parameter control the pitch of attached sources to simulate engine RPM ramping up and down.
    ///    channel = "Pitch";
    /// 
    ///    // Start out with unmodified pitch.
    ///    defaultValue = 1;
    /// 
    ///    // Add a texture description of what this parameter does.
    ///    description = "Engine RPM Level";
    /// };
    /// 
    /// // Create a description that automatically attaches the engine RPM parameter.
    /// singleton SFXDescription( EngineRPMSound : AudioLoop2D )
    /// {
    ///    parameters[ 0 ] = "EngineRPMLevel";
    /// };
    /// 
    /// // Create sound sources for the engine.
    /// sfxCreateSource( EngineRPMSound, "art/sound/engine/enginePrimary" );
    /// sfxCreateSource( EngineRPMSound, "art/sound/engine/engineSecondary" );
    /// 
    /// // Setting the parameter value will now affect the pitch level of both sound sources.
    /// EngineRPMLevel.value = 0.5;
    /// EngineRPMLevel.value = 1.5;
    /// </code>
    public unsafe class SFXParameter : SimObject {
        public SFXParameter(bool pRegister = false) 
            : base(pRegister) {
        }
        
        public SFXParameter(string pName, bool pRegister) 
            : this(false) {
            Name = pName;
            if (pRegister) {
                RegisterObject();
            }
        }
        
        public SFXParameter(string pName) 
            : this(pName, false) {
        }
        
        public SFXParameter(string pName, string pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(Engine.Sim.FindObject<SimObject>(pParent));
        }
        
        public SFXParameter(string pName, SimObject pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(pParent);
        }
        
        public SFXParameter(SimObject pObj) 
            : base(pObj) {
        }
        
        public SFXParameter(IntPtr pObj) 
            : base(pObj) {
        }
        
		protected override void CreateObjectPtr()
		{
			ObjectPtr = InternalUnsafeMethods.Create()(new InternalUnsafeMethods.Create__Args());
		}

        #region UnsafeNativeMethods
        new internal struct InternalUnsafeMethods {
            [StructLayout(LayoutKind.Sequential)]
            internal struct Reset__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _Reset(IntPtr _this, Reset__Args args);
            private static _Reset _ResetFunc;
            internal static _Reset Reset() {
                if (_ResetFunc == null) {
                    _ResetFunc =
                        (_Reset)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnSFXParameter_reset"), typeof(_Reset));
                }
                
                return _ResetFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct GetParameterName__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            
            internal delegate IntPtr _GetParameterName(IntPtr _this, GetParameterName__Args args);
            private static _GetParameterName _GetParameterNameFunc;
            internal static _GetParameterName GetParameterName() {
                if (_GetParameterNameFunc == null) {
                    _GetParameterNameFunc =
                        (_GetParameterName)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnSFXParameter_getParameterName"), typeof(_GetParameterName));
                }
                
                return _GetParameterNameFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct OnUpdate__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _OnUpdate(IntPtr _this, OnUpdate__Args args);
            private static _OnUpdate _OnUpdateFunc;
            internal static _OnUpdate OnUpdate() {
                if (_OnUpdateFunc == null) {
                    _OnUpdateFunc =
                        (_OnUpdate)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "cbSFXParameter_onUpdate"), typeof(_OnUpdate));
                }
                
                return _OnUpdateFunc;
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
                                "fnSFXParameter_staticGetType"), typeof(_StaticGetType));
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
                                "fnSFXParameter_create"), typeof(_Create));
                }
                
                return _CreateFunc;
            }
        }
        #endregion

        /// <description>
        /// Reset the parameter's value to its default.
        /// </description>
        /// <see cref="SFXParameter::defaultValue" />
        public void Reset() {
             InternalUnsafeMethods.Reset__Args _args = new InternalUnsafeMethods.Reset__Args() {
             };
             InternalUnsafeMethods.Reset()(ObjectPtr, _args);
        }

        /// <description>
        /// Get the name of the parameter.
        /// </description>
        /// <returns>The paramete name.</returns>
        public string GetParameterName() {
             InternalUnsafeMethods.GetParameterName__Args _args = new InternalUnsafeMethods.GetParameterName__Args() {
             };
             IntPtr _engineResult = InternalUnsafeMethods.GetParameterName()(ObjectPtr, _args);
             return StringMarshal.IntPtrToUtf8String(_engineResult);
        }

        /// <description>
        /// Called when the sound system triggers an update on the parameter.
        /// This occurs periodically during system operation.
        /// </description>
        public virtual void OnUpdate() {
             InternalUnsafeMethods.OnUpdate__Args _args = new InternalUnsafeMethods.OnUpdate__Args() {
             };
             InternalUnsafeMethods.OnUpdate()(ObjectPtr, _args);
        }

        /// <description>
        /// Get the type info object for the SFXParameter class.
        /// </description>
        /// <returns>The type info object for SFXParameter</returns>
        public static EngineTypeInfo StaticGetType() {
             InternalUnsafeMethods.StaticGetType__Args _args = new InternalUnsafeMethods.StaticGetType__Args() {
             };
             IntPtr _engineResult = InternalUnsafeMethods.StaticGetType()(_args);
             return new EngineTypeInfo(_engineResult);
        }


        /// <value>
        /// <description>
        /// Current value of the audio parameter.
        /// All attached sources are notified when this value changes.
        /// </description>
        /// </value>
        public float Value {
            get => GenericMarshal.StringTo<float>(GetFieldValue("value"));
            set => SetFieldValue("value", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Permitted range for #value.
        /// Minimum and maximum allowed value for the parameter.  Both inclusive.
        /// 
        /// For all but the User0-3 channels, this property is automatically set up by SFXParameter.
        /// </description>
        /// </value>
        public Point2F Range {
            get => GenericMarshal.StringTo<Point2F>(GetFieldValue("range"));
            set => SetFieldValue("range", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Channel that the parameter controls.
        /// This controls which property of the sources it is attached to the parameter controls.
        /// </description>
        /// </value>
        public SFXChannel Channel {
            get => GenericMarshal.StringTo<SFXChannel>(GetFieldValue("channel"));
            set => SetFieldValue("channel", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Value to which the parameter is initially set.
        /// When the parameter is first added to the system, #value will be set to #defaultValue.
        /// </description>
        /// </value>
        public float DefaultValue {
            get => GenericMarshal.StringTo<float>(GetFieldValue("defaultValue"));
            set => SetFieldValue("defaultValue", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Textual description of the parameter.
        /// Primarily for use in the Audio Parameters dialog of the editor to allow for easier identification of parameters.
        /// </description>
        /// </value>
        public string Description {
            get => GenericMarshal.StringTo<string>(GetFieldValue("description"));
            set => SetFieldValue("description", GenericMarshal.ToString(value));
        }
    }
}