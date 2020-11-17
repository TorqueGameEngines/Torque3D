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
    /// <summary>A simple proximity mine.</summary>
    /// <description>
    /// Proximity mines can be deployed using the world editor or thrown by an in-game object. Once armed, any Player or Vehicle object that moves within the mine's trigger area will cause it to explode.
    /// 
    /// Internally, the ProximityMine object transitions through the following states:
    /// <ol>
    ///   <li><b>Thrown</b>: Mine has been thrown, but has not yet attached to a surface</li>
    ///   <li><b>Deployed</b>: Mine has attached to a surface but is not yet armed. Start playing the #armingSound and <i>armed</i> sequence.</li>
    ///   <li><b>Armed</b>: Mine is armed and will trigger if a Vehicle or Player object moves within the trigger area.</li>
    ///   <li><b>Triggered</b>: Mine has been triggered and will explode soon. Invoke the onTriggered callback, and start playing the #triggerSound and <i>triggered</i> sequence.</li>
    ///   <li><b>Exploded</b>: Mine has exploded and will be deleted on the server shortly. Invoke the onExplode callback on the server and generate the explosion effects on the client.</li>
    /// </ol>
    /// </description>
    /// <remarks> Proximity mines with the #static field set to true will start in the <b>Armed</b> state. Use this for mines placed with the World Editor.
    /// 
    /// The shape used for the mine may optionally define the following sequences:
    /// <dl>
    ///   <dt>armed</dt><dd>Sequence to play when the mine is deployed, but before it becomes active and triggerable (#armingDelay should be set appropriately).</dd>
    ///   <dt>triggered</dt><dd>Sequence to play when the mine is triggered, just before it explodes (#triggerDelay should be set appropriately).<dd>
    /// </dl>
    /// 
    /// </remarks>
    /// <code>
    /// datablock ProximityMineData( SimpleMine )
    /// {
    ///    // ShapeBaseData fields
    ///    category = "Weapon";
    ///    shapeFile = "art/shapes/weapons/misc/proximityMine.dts";
    /// 
    ///    // ItemData fields
    ///    sticky = true;
    /// 
    ///    // ProximityMineData fields
    ///    armingDelay = 0.5;
    ///    armingSound = MineArmedSound;
    /// 
    ///    autoTriggerDelay = 0;
    ///    triggerOnOwner = true;
    ///    triggerRadius = 5.0;
    ///    triggerSpeed = 1.0;
    ///    triggerDelay = 0.5;
    ///    triggerSound = MineTriggeredSound;
    ///    explosion = RocketLauncherExplosion;
    /// 
    ///    // dynamic fields
    ///    pickUpName = "Proximity Mines";
    ///    maxInventory = 20;
    /// 
    ///    damageType = "MineDamage"; // type of damage applied to objects in radius
    ///    radiusDamage = 30;           // amount of damage to apply to objects in radius
    ///    damageRadius = 8;            // search radius to damage objects when exploding
    ///    areaImpulse = 2000;          // magnitude of impulse to apply to objects in radius
    /// };
    /// 
    /// function ProximityMineData::onTriggered( %this, %obj, %target )
    /// {
    ///    echo( %this.name SPC "triggered by "@ %target.getClassName() );
    /// }
    /// 
    /// function ProximityMineData::onExplode( %this, %obj, %position )
    /// {
    ///    // Damage objects within the mine's damage radius
    ///    if ( %this.damageRadius > 0 )
    ///       radiusDamage( %obj.sourceObject, %position, %this.damageRadius, %this.radiusDamage, %this.damageType, %this.areaImpulse );
    /// }
    /// 
    /// function ProximityMineData::damage( %this, %obj, %position, %source, %amount, %damageType )
    /// {
    ///    // Explode if any damage is applied to the mine
    ///    %obj.schedule(50 + getRandom(50), explode);
    /// }
    /// 
    /// %obj = new ProximityMine()
    /// {
    ///    dataBlock = SimpleMine;
    /// };
    /// 
    /// </code>
    /// <see cref="ProximityMineData" />
    public unsafe class ProximityMine : Item {
        public ProximityMine(bool pRegister = false) 
            : base(pRegister) {
        }
        
        public ProximityMine(string pName, bool pRegister) 
            : this(false) {
            Name = pName;
            if (pRegister) {
                RegisterObject();
            }
        }
        
        public ProximityMine(string pName) 
            : this(pName, false) {
        }
        
        public ProximityMine(string pName, string pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(Engine.Sim.FindObject<SimObject>(pParent));
        }
        
        public ProximityMine(string pName, SimObject pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(pParent);
        }
        
        public ProximityMine(SimObject pObj) 
            : base(pObj) {
        }
        
        public ProximityMine(IntPtr pObj) 
            : base(pObj) {
        }
        
		protected override void CreateObjectPtr()
		{
			ObjectPtr = InternalUnsafeMethods.Create()(new InternalUnsafeMethods.Create__Args());
		}

        #region UnsafeNativeMethods
        new internal struct InternalUnsafeMethods {
            [StructLayout(LayoutKind.Sequential)]
            internal struct Explode__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _Explode(IntPtr _this, Explode__Args args);
            private static _Explode _ExplodeFunc;
            internal static _Explode Explode() {
                if (_ExplodeFunc == null) {
                    _ExplodeFunc =
                        (_Explode)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnProximityMine_explode"), typeof(_Explode));
                }
                
                return _ExplodeFunc;
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
                                "fnProximityMine_staticGetType"), typeof(_StaticGetType));
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
                                "fnProximityMine_create"), typeof(_Create));
                }
                
                return _CreateFunc;
            }
        }
        #endregion

        /// <summary>Manually cause the mine to explode.</summary>
        /// <description>
        /// 
        /// </description>
        public void Explode() {
             InternalUnsafeMethods.Explode__Args _args = new InternalUnsafeMethods.Explode__Args() {
             };
             InternalUnsafeMethods.Explode()(ObjectPtr, _args);
        }

        /// <description>
        /// Get the type info object for the ProximityMine class.
        /// </description>
        /// <returns>The type info object for ProximityMine</returns>
        public static EngineTypeInfo StaticGetType() {
             InternalUnsafeMethods.StaticGetType__Args _args = new InternalUnsafeMethods.StaticGetType__Args() {
             };
             IntPtr _engineResult = InternalUnsafeMethods.StaticGetType()(_args);
             return new EngineTypeInfo(_engineResult);
        }
    }
}