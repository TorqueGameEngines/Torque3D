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
    /// <summary>Object responsible for simulating wind in a level.</summary>
    /// <description>
    /// When placed in the level, a ForestWindEmitter will cause tree branches to bend and sway, leaves to flutter, and create vertical bending on the tree's trunk.
    /// </description>
    /// <code>
    /// // The following is a full declaration of a wind emitter
    /// new ForestWindEmitter()
    /// {
    ///    position = "497.739 765.821 102.395";
    ///    windEnabled = "1";
    ///    radialEmitter = "1";
    ///    strength = "1";
    ///    radius = "3";
    ///    gustStrength = "0.5";
    ///    gustFrequency = "1";
    ///    gustYawAngle = "10";
    ///    gustYawFrequency = "4";
    ///    gustWobbleStrength = "2";
    ///    turbulenceStrength = "1";
    ///    turbulenceFrequency = "2";
    ///    hasMount = "0";
    ///    scale = "3 3 3";
    ///    canSave = "1";
    ///    canSaveDynamicFields = "1";
    ///    rotation = "1 0 0 0";
    /// };
    /// </code>
    public unsafe class ForestWindEmitter : SceneObject {
        public ForestWindEmitter(bool pRegister = false) 
            : base(pRegister) {
        }
        
        public ForestWindEmitter(string pName, bool pRegister) 
            : this(false) {
            Name = pName;
            if (pRegister) {
                RegisterObject();
            }
        }
        
        public ForestWindEmitter(string pName) 
            : this(pName, false) {
        }
        
        public ForestWindEmitter(string pName, string pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(Engine.Sim.FindObject<SimObject>(pParent));
        }
        
        public ForestWindEmitter(string pName, SimObject pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(pParent);
        }
        
        public ForestWindEmitter(SimObject pObj) 
            : base(pObj) {
        }
        
        public ForestWindEmitter(IntPtr pObj) 
            : base(pObj) {
        }
        
		protected override void CreateObjectPtr()
		{
			ObjectPtr = InternalUnsafeMethods.Create()(new InternalUnsafeMethods.Create__Args());
		}

        #region UnsafeNativeMethods
        new internal struct InternalUnsafeMethods {
            [StructLayout(LayoutKind.Sequential)]
            internal struct AttachToObject__Args
            {
                internal uint objectID;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _AttachToObject(IntPtr _this, AttachToObject__Args args);
            private static _AttachToObject _AttachToObjectFunc;
            internal static _AttachToObject AttachToObject() {
                if (_AttachToObjectFunc == null) {
                    _AttachToObjectFunc =
                        (_AttachToObject)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnForestWindEmitter_attachToObject"), typeof(_AttachToObject));
                }
                
                return _AttachToObjectFunc;
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
                                "fnForestWindEmitter_staticGetType"), typeof(_StaticGetType));
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
                                "fnForestWindEmitter_create"), typeof(_Create));
                }
                
                return _CreateFunc;
            }
        }
        #endregion

        /// <summary>Mounts the wind emitter to another scene object</summary>
        /// <description>
        /// 
        /// </description>
        /// <param name="objectID">Unique ID of the object wind emitter should attach to</param>
        /// <code>
        /// // Wind emitter previously created and named %windEmitter
        /// // Going to attach it to the player, making him a walking wind storm
        /// %windEmitter.attachToObject(%player);
        /// </code>
        public void AttachToObject(uint objectID) {
             InternalUnsafeMethods.AttachToObject__Args _args = new InternalUnsafeMethods.AttachToObject__Args() {
                objectID = objectID,
             };
             InternalUnsafeMethods.AttachToObject()(ObjectPtr, _args);
        }

        /// <description>
        /// Get the type info object for the ForestWindEmitter class.
        /// </description>
        /// <returns>The type info object for ForestWindEmitter</returns>
        public static EngineTypeInfo StaticGetType() {
             InternalUnsafeMethods.StaticGetType__Args _args = new InternalUnsafeMethods.StaticGetType__Args() {
             };
             IntPtr _engineResult = InternalUnsafeMethods.StaticGetType()(_args);
             return new EngineTypeInfo(_engineResult);
        }


        /// <value>
        /// <description>
        /// Determines if the emitter will be counted in wind calculations.
        /// </description>
        /// </value>
        public bool WindEnabled {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("windEnabled"));
            set => SetFieldValue("windEnabled", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Determines if the emitter is a global direction or local radial emitter.
        /// </description>
        /// </value>
        public bool RadialEmitter {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("radialEmitter"));
            set => SetFieldValue("radialEmitter", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// The strength of the wind force.
        /// </description>
        /// </value>
        public float Strength {
            get => GenericMarshal.StringTo<float>(GetFieldValue("strength"));
            set => SetFieldValue("strength", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// The radius of the emitter for local radial emitters.
        /// </description>
        /// </value>
        public float Radius {
            get => GenericMarshal.StringTo<float>(GetFieldValue("radius"));
            set => SetFieldValue("radius", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// The maximum strength of a gust.
        /// </description>
        /// </value>
        public float GustStrength {
            get => GenericMarshal.StringTo<float>(GetFieldValue("gustStrength"));
            set => SetFieldValue("gustStrength", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// The frequency of gusting in seconds.
        /// </description>
        /// </value>
        public float GustFrequency {
            get => GenericMarshal.StringTo<float>(GetFieldValue("gustFrequency"));
            set => SetFieldValue("gustFrequency", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// The amount of degrees the wind direction can drift (both positive and negative).
        /// </description>
        /// </value>
        public float GustYawAngle {
            get => GenericMarshal.StringTo<float>(GetFieldValue("gustYawAngle"));
            set => SetFieldValue("gustYawAngle", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// The frequency of wind yaw drift, in seconds.
        /// </description>
        /// </value>
        public float GustYawFrequency {
            get => GenericMarshal.StringTo<float>(GetFieldValue("gustYawFrequency"));
            set => SetFieldValue("gustYawFrequency", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// The amount of random wobble added to gust and turbulence vectors.
        /// </description>
        /// </value>
        public float GustWobbleStrength {
            get => GenericMarshal.StringTo<float>(GetFieldValue("gustWobbleStrength"));
            set => SetFieldValue("gustWobbleStrength", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// The strength of gust turbulence.
        /// </description>
        /// </value>
        public float TurbulenceStrength {
            get => GenericMarshal.StringTo<float>(GetFieldValue("turbulenceStrength"));
            set => SetFieldValue("turbulenceStrength", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// The frequency of gust turbulence, in seconds.
        /// </description>
        /// </value>
        public float TurbulenceFrequency {
            get => GenericMarshal.StringTo<float>(GetFieldValue("turbulenceFrequency"));
            set => SetFieldValue("turbulenceFrequency", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Determines if the emitter is mounted to another object.
        /// </description>
        /// </value>
        public bool HasMount {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("hasMount"));
            set => SetFieldValue("hasMount", GenericMarshal.ToString(value));
        }
    }
}