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
    /// <summary>Stores common properties for a ProximityMine.</summary>
    /// <description>
    /// 
    /// </description>
    /// <see cref="ProximityMine" />
    public unsafe class ProximityMineData : ItemData {
        public ProximityMineData(bool pRegister = false) 
            : base(pRegister) {
        }
        
        public ProximityMineData(string pName, bool pRegister) 
            : this(false) {
            Name = pName;
            if (pRegister) {
                RegisterObject();
            }
        }
        
        public ProximityMineData(string pName) 
            : this(pName, false) {
        }
        
        public ProximityMineData(string pName, string pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(Engine.Sim.FindObject<SimObject>(pParent));
        }
        
        public ProximityMineData(string pName, SimObject pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(pParent);
        }
        
        public ProximityMineData(SimObject pObj) 
            : base(pObj) {
        }
        
        public ProximityMineData(IntPtr pObj) 
            : base(pObj) {
        }
        
		protected override void CreateObjectPtr()
		{
			ObjectPtr = InternalUnsafeMethods.Create()(new InternalUnsafeMethods.Create__Args());
		}

        #region UnsafeNativeMethods
        new internal struct InternalUnsafeMethods {
            [StructLayout(LayoutKind.Sequential)]
            internal struct OnExplode__Args
            {
                internal IntPtr obj;
                internal IntPtr pos;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _OnExplode(IntPtr _this, OnExplode__Args args);
            private static _OnExplode _OnExplodeFunc;
            internal static _OnExplode OnExplode() {
                if (_OnExplodeFunc == null) {
                    _OnExplodeFunc =
                        (_OnExplode)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "cbProximityMineData_onExplode"), typeof(_OnExplode));
                }
                
                return _OnExplodeFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct OnTriggered__Args
            {
                internal IntPtr obj;
                internal IntPtr target;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _OnTriggered(IntPtr _this, OnTriggered__Args args);
            private static _OnTriggered _OnTriggeredFunc;
            internal static _OnTriggered OnTriggered() {
                if (_OnTriggeredFunc == null) {
                    _OnTriggeredFunc =
                        (_OnTriggered)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "cbProximityMineData_onTriggered"), typeof(_OnTriggered));
                }
                
                return _OnTriggeredFunc;
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
                                "fnProximityMineData_staticGetType"), typeof(_StaticGetType));
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
                                "fnProximityMineData_create"), typeof(_Create));
                }
                
                return _CreateFunc;
            }
        }
        #endregion

        /// <description>
        /// Callback invoked when a ProximityMine is about to explode.
        /// </description>
        /// <param name="obj">The ProximityMine object</param>
        /// <param name="pos">The position of the mine explosion</param>
        /// <remarks> This callback is only invoked on the server.
        /// </remarks>
        /// <see cref="ProximityMine" />
        public virtual void OnExplode(ProximityMine obj, Point3F pos) {
pos.Alloc();             InternalUnsafeMethods.OnExplode__Args _args = new InternalUnsafeMethods.OnExplode__Args() {
                obj = obj.ObjectPtr,
                pos = pos.internalStructPtr,
             };
             InternalUnsafeMethods.OnExplode()(ObjectPtr, _args);
pos.Free();        }

        /// <description>
        /// Callback invoked when an object triggers the ProximityMine.
        /// </description>
        /// <param name="obj">The ProximityMine object</param>
        /// <param name="target">The object that triggered the mine</param>
        /// <remarks> This callback is only invoked on the server.
        /// </remarks>
        /// <see cref="ProximityMine" />
        public virtual void OnTriggered(ProximityMine obj, SceneObject target) {
             InternalUnsafeMethods.OnTriggered__Args _args = new InternalUnsafeMethods.OnTriggered__Args() {
                obj = obj.ObjectPtr,
                target = target.ObjectPtr,
             };
             InternalUnsafeMethods.OnTriggered()(ObjectPtr, _args);
        }

        /// <description>
        /// Get the type info object for the ProximityMineData class.
        /// </description>
        /// <returns>The type info object for ProximityMineData</returns>
        public static EngineTypeInfo StaticGetType() {
             InternalUnsafeMethods.StaticGetType__Args _args = new InternalUnsafeMethods.StaticGetType__Args() {
             };
             IntPtr _engineResult = InternalUnsafeMethods.StaticGetType()(_args);
             return new EngineTypeInfo(_engineResult);
        }


        /// <value>
        /// <description>
        /// Delay (in seconds) from when the mine is placed to when it becomes active.
        /// </description>
        /// </value>
        public float ArmingDelay {
            get => GenericMarshal.StringTo<float>(GetFieldValue("armingDelay"));
            set => SetFieldValue("armingDelay", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Sound to play when the mine is armed (starts at the same time as the <i>armed</i> sequence if defined).
        /// </description>
        /// </value>
        public SFXTrack ArmingSound {
            get => GenericMarshal.StringTo<SFXTrack>(GetFieldValue("armingSound"));
            set => SetFieldValue("armingSound", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <summary>Delay (in seconds) from arming until the mine automatically triggers and explodes, even if no object has entered the trigger area.</summary>
        /// <description>
        /// Set to 0 to disable.
        /// </description>
        /// </value>
        public float AutoTriggerDelay {
            get => GenericMarshal.StringTo<float>(GetFieldValue("autoTriggerDelay"));
            set => SetFieldValue("autoTriggerDelay", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <summary>Controls whether the mine can be triggered by the object that owns it.</summary>
        /// <description>
        /// For example, a player could deploy mines that are only dangerous to other players and not himself.
        /// </description>
        /// </value>
        public bool TriggerOnOwner {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("triggerOnOwner"));
            set => SetFieldValue("triggerOnOwner", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Distance at which an activated mine will detect other objects and explode.
        /// </description>
        /// </value>
        public float TriggerRadius {
            get => GenericMarshal.StringTo<float>(GetFieldValue("triggerRadius"));
            set => SetFieldValue("triggerRadius", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Speed above which moving objects within the trigger radius will trigger the mine
        /// </description>
        /// </value>
        public float TriggerSpeed {
            get => GenericMarshal.StringTo<float>(GetFieldValue("triggerSpeed"));
            set => SetFieldValue("triggerSpeed", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Delay (in seconds) from when the mine is triggered until it explodes.
        /// </description>
        /// </value>
        public float TriggerDelay {
            get => GenericMarshal.StringTo<float>(GetFieldValue("triggerDelay"));
            set => SetFieldValue("triggerDelay", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Sound to play when the mine is triggered (starts at the same time as the <i>triggered</i> sequence if defined).
        /// </description>
        /// </value>
        public SFXTrack TriggerSound {
            get => GenericMarshal.StringTo<SFXTrack>(GetFieldValue("triggerSound"));
            set => SetFieldValue("triggerSound", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <summary>Offset from the mine's origin where the explosion emanates from.Sometimes a thrown mine may be slightly sunk into the ground.  This can be just enough to cause the explosion to occur under the ground, especially on flat ground, which can end up blocking the explosion.  This offset along the mine's 'up' normal allows you to raise the explosion origin to a better height.</summary>
        /// </value>
        public float ExplosionOffset {
            get => GenericMarshal.StringTo<float>(GetFieldValue("explosionOffset"));
            set => SetFieldValue("explosionOffset", GenericMarshal.ToString(value));
        }
    }
}