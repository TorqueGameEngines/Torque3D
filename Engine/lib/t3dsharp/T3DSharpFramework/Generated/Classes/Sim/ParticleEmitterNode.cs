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
    /// <summary>A particle emitter object that can be positioned in the world and dynamically enabled or disabled.</summary>
    /// <description>
    /// 
    /// </description>
    /// <code>
    /// datablock ParticleEmitterNodeData( SimpleEmitterNodeData )
    /// {
    ///    timeMultiple = 1.0;
    /// };
    /// 
    /// %emitter = new ParticleEmitterNode()
    /// {
    ///    datablock = SimpleEmitterNodeData;
    ///    active = true;
    ///    emitter = FireEmitterData;
    ///    velocity = 3.5;
    /// };
    /// 
    /// // Dynamically change emitter datablock
    /// %emitter.setEmitterDataBlock( DustEmitterData );
    /// </code>
    /// <remarks> To change the emitter field dynamically (after the ParticleEmitterNode object has been created) you must use the setEmitterDataBlock() method or the change will not be replicated to other clients in the game.
    /// Similarly, use the setActive() method instead of changing the active field directly. When changing velocity, you need to toggle setActive() on and off to force the state change to be transmitted to other clients.
    /// 
    /// </remarks>
    /// <see cref="ParticleEmitterNodeData" />
    /// <see cref="ParticleEmitterData" />
    public unsafe class ParticleEmitterNode : GameBase {
        public ParticleEmitterNode(bool pRegister = false) 
            : base(pRegister) {
        }
        
        public ParticleEmitterNode(string pName, bool pRegister) 
            : this(false) {
            Name = pName;
            if (pRegister) {
                RegisterObject();
            }
        }
        
        public ParticleEmitterNode(string pName) 
            : this(pName, false) {
        }
        
        public ParticleEmitterNode(string pName, string pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(Engine.Sim.FindObject<SimObject>(pParent));
        }
        
        public ParticleEmitterNode(string pName, SimObject pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(pParent);
        }
        
        public ParticleEmitterNode(SimObject pObj) 
            : base(pObj) {
        }
        
        public ParticleEmitterNode(IntPtr pObj) 
            : base(pObj) {
        }
        
		protected override void CreateObjectPtr()
		{
			ObjectPtr = InternalUnsafeMethods.Create()(new InternalUnsafeMethods.Create__Args());
		}

        #region UnsafeNativeMethods
        new internal struct InternalUnsafeMethods {
            [StructLayout(LayoutKind.Sequential)]
            internal struct SetActive__Args
            {
                [MarshalAs(UnmanagedType.I1)]
                internal bool active;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _SetActive(IntPtr _this, SetActive__Args args);
            private static _SetActive _SetActiveFunc;
            internal static _SetActive SetActive() {
                if (_SetActiveFunc == null) {
                    _SetActiveFunc =
                        (_SetActive)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnParticleEmitterNode_setActive"), typeof(_SetActive));
                }
                
                return _SetActiveFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct SetEmitterDataBlock__Args
            {
                internal IntPtr emitterDatablock;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _SetEmitterDataBlock(IntPtr _this, SetEmitterDataBlock__Args args);
            private static _SetEmitterDataBlock _SetEmitterDataBlockFunc;
            internal static _SetEmitterDataBlock SetEmitterDataBlock() {
                if (_SetEmitterDataBlockFunc == null) {
                    _SetEmitterDataBlockFunc =
                        (_SetEmitterDataBlock)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnParticleEmitterNode_setEmitterDataBlock"), typeof(_SetEmitterDataBlock));
                }
                
                return _SetEmitterDataBlockFunc;
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
                                "fnParticleEmitterNode_staticGetType"), typeof(_StaticGetType));
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
                                "fnParticleEmitterNode_create"), typeof(_Create));
                }
                
                return _CreateFunc;
            }
        }
        #endregion

        /// <description>
        /// Turns the emitter on or off.
        /// </description>
        /// <param name="active">New emitter state</param>
        public void SetActive(bool active) {
             InternalUnsafeMethods.SetActive__Args _args = new InternalUnsafeMethods.SetActive__Args() {
                active = active,
             };
             InternalUnsafeMethods.SetActive()(ObjectPtr, _args);
        }

        /// <description>
        /// Assigns the datablock for this emitter node.
        /// </description>
        /// <param name="emitterDatablock">ParticleEmitterData datablock to assign</param>
        /// <code>
        /// // Assign a new emitter datablock
        /// %emitter.setEmitterDatablock( %emitterDatablock );
        /// </code>
        public void SetEmitterDataBlock(ParticleEmitterData emitterDatablock = null) {
             InternalUnsafeMethods.SetEmitterDataBlock__Args _args = new InternalUnsafeMethods.SetEmitterDataBlock__Args() {
                emitterDatablock = emitterDatablock.ObjectPtr,
             };
             InternalUnsafeMethods.SetEmitterDataBlock()(ObjectPtr, _args);
        }

        /// <description>
        /// Get the type info object for the ParticleEmitterNode class.
        /// </description>
        /// <returns>The type info object for ParticleEmitterNode</returns>
        public static EngineTypeInfo StaticGetType() {
             InternalUnsafeMethods.StaticGetType__Args _args = new InternalUnsafeMethods.StaticGetType__Args() {
             };
             IntPtr _engineResult = InternalUnsafeMethods.StaticGetType()(_args);
             return new EngineTypeInfo(_engineResult);
        }


        /// <value>
        /// <description>
        /// Controls whether particles are emitted from this node.
        /// </description>
        /// </value>
        public bool Active {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("active"));
            set => SetFieldValue("active", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Datablock to use when emitting particles.
        /// </description>
        /// </value>
        public ParticleEmitterData Emitter {
            get => GenericMarshal.StringTo<ParticleEmitterData>(GetFieldValue("emitter"));
            set => SetFieldValue("emitter", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Velocity to use when emitting particles (in the direction of the ParticleEmitterNode object's up (Z) axis).
        /// </description>
        /// </value>
        public float Velocity {
            get => GenericMarshal.StringTo<float>(GetFieldValue("velocity"));
            set => SetFieldValue("velocity", GenericMarshal.ToString(value));
        }
    }
}