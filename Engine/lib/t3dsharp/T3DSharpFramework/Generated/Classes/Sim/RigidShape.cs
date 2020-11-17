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
    /// <summary>The RigidShape class implements rigid-body physics for DTS objects in the world.</summary>
    /// <description>
    /// "Rigid body physics" refers to a system whereby objects are assumed to have a finite size,
    /// equally distributed masses, and where deformations of the objects themselves are not accounted for.
    /// Uses the RigidShape class to control its physics.
    /// </description>
    /// <code>
    /// datablock RigidShapeData( BouncingBoulder )
    /// 	{
    /// 	   category = "RigidShape";
    /// 
    /// 	   shapeFile = "~/data/shapes/boulder/boulder.dts";
    /// 	   emap = true;
    /// 
    /// 	   // Rigid Body
    /// 	   mass = 500;
    /// 	   massCenter = "0 0 0";    // Center of mass for rigid body
    /// 	   massBox = "0 0 0";         // Size of box used for moment of inertia,
    /// 								  // if zero it defaults to object bounding box
    /// 	   drag = 0.2;                // Drag coefficient
    /// 	   bodyFriction = 0.2;
    /// 	   bodyRestitution = 0.1;
    /// 	   minImpactSpeed = 5;        // Impacts over this invoke the script callback
    /// 	   softImpactSpeed = 5;       // Play SoftImpact Sound
    /// 	   hardImpactSpeed = 15;      // Play HardImpact Sound
    /// 	   integration = 4;           // Physics integration: TickSec/Rate
    /// 	   collisionTol = 0.1;        // Collision distance tolerance
    /// 	   contactTol = 0.1;          // Contact velocity tolerance
    /// 
    /// 	   minRollSpeed = 10;
    /// 
    /// 	   maxDrag = 0.5;
    /// 	   minDrag = 0.01;
    /// 
    /// 	   dustHeight = 10;
    /// 
    /// 	   dragForce = 0.05;
    /// 	   vertFactor = 0.05;
    /// 	};
    /// 
    ///  new RigidShape()
    /// 	{
    /// 		dataBlock = "BouncingBoulder";
    /// 		parentGroup = EWCreatorWindow.objectGroup;
    /// 	};
    /// </code>
    /// <see cref="RigidShapeData" />
    /// <see cref="ShapeBase" />
    public unsafe class RigidShape : ShapeBase {
        public RigidShape(bool pRegister = false) 
            : base(pRegister) {
        }
        
        public RigidShape(string pName, bool pRegister) 
            : this(false) {
            Name = pName;
            if (pRegister) {
                RegisterObject();
            }
        }
        
        public RigidShape(string pName) 
            : this(pName, false) {
        }
        
        public RigidShape(string pName, string pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(Engine.Sim.FindObject<SimObject>(pParent));
        }
        
        public RigidShape(string pName, SimObject pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(pParent);
        }
        
        public RigidShape(SimObject pObj) 
            : base(pObj) {
        }
        
        public RigidShape(IntPtr pObj) 
            : base(pObj) {
        }
        
		protected override void CreateObjectPtr()
		{
			ObjectPtr = InternalUnsafeMethods.Create()(new InternalUnsafeMethods.Create__Args());
		}

        #region UnsafeNativeMethods
        new internal struct InternalUnsafeMethods {
            [StructLayout(LayoutKind.Sequential)]
            internal struct ForceClientTransform__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _ForceClientTransform(IntPtr _this, ForceClientTransform__Args args);
            private static _ForceClientTransform _ForceClientTransformFunc;
            internal static _ForceClientTransform ForceClientTransform() {
                if (_ForceClientTransformFunc == null) {
                    _ForceClientTransformFunc =
                        (_ForceClientTransform)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnRigidShape_forceClientTransform"), typeof(_ForceClientTransform));
                }
                
                return _ForceClientTransformFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct FreezeSim__Args
            {
                [MarshalAs(UnmanagedType.I1)]
                internal bool isFrozen;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _FreezeSim(IntPtr _this, FreezeSim__Args args);
            private static _FreezeSim _FreezeSimFunc;
            internal static _FreezeSim FreezeSim() {
                if (_FreezeSimFunc == null) {
                    _FreezeSimFunc =
                        (_FreezeSim)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnRigidShape_freezeSim"), typeof(_FreezeSim));
                }
                
                return _FreezeSimFunc;
            }

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
                                "fnRigidShape_reset"), typeof(_Reset));
                }
                
                return _ResetFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct OnLeaveLiquid__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string objId;
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string liquidType;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _OnLeaveLiquid(IntPtr _this, OnLeaveLiquid__Args args);
            private static _OnLeaveLiquid _OnLeaveLiquidFunc;
            internal static _OnLeaveLiquid OnLeaveLiquid() {
                if (_OnLeaveLiquidFunc == null) {
                    _OnLeaveLiquidFunc =
                        (_OnLeaveLiquid)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "cbRigidShape_onLeaveLiquid"), typeof(_OnLeaveLiquid));
                }
                
                return _OnLeaveLiquidFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct OnEnterLiquid__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string objId;
                internal float waterCoverage;
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string liquidType;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _OnEnterLiquid(IntPtr _this, OnEnterLiquid__Args args);
            private static _OnEnterLiquid _OnEnterLiquidFunc;
            internal static _OnEnterLiquid OnEnterLiquid() {
                if (_OnEnterLiquidFunc == null) {
                    _OnEnterLiquidFunc =
                        (_OnEnterLiquid)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "cbRigidShape_onEnterLiquid"), typeof(_OnEnterLiquid));
                }
                
                return _OnEnterLiquidFunc;
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
                                "fnRigidShape_staticGetType"), typeof(_StaticGetType));
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
                                "fnRigidShape_create"), typeof(_Create));
                }
                
                return _CreateFunc;
            }
        }
        #endregion

        /// <summary>Forces the client to jump to the RigidShape's transform rather then warp to it.</summary>
        /// <description>
        /// 
        /// </description>
        public void ForceClientTransform() {
             InternalUnsafeMethods.ForceClientTransform__Args _args = new InternalUnsafeMethods.ForceClientTransform__Args() {
             };
             InternalUnsafeMethods.ForceClientTransform()(ObjectPtr, _args);
        }

        /// <summary>Enables or disables the physics simulation on the RigidShape object.</summary>
        /// <description>
        /// 
        /// </description>
        /// <param name="isFrozen">Boolean frozen state to set the object.</param>
        /// <code>
        /// // Define the frozen state.
        /// %isFrozen = "true";
        /// 
        /// // Inform the object of the defined frozen state
        /// %thisRigidShape.freezeSim(%isFrozen);
        /// </code>
        /// <see cref="ShapeBaseData" />
        public void FreezeSim(bool isFrozen) {
             InternalUnsafeMethods.FreezeSim__Args _args = new InternalUnsafeMethods.FreezeSim__Args() {
                isFrozen = isFrozen,
             };
             InternalUnsafeMethods.FreezeSim()(ObjectPtr, _args);
        }

        /// <summary>Clears physic forces from the shape and sets it at rest.</summary>
        /// <description>
        /// 
        /// </description>
        /// <code>
        /// // Inform the RigidShape object to reset.
        /// %thisRigidShape.reset();
        /// </code>
        /// <see cref="ShapeBaseData" />
        public void Reset() {
             InternalUnsafeMethods.Reset__Args _args = new InternalUnsafeMethods.Reset__Args() {
             };
             InternalUnsafeMethods.Reset()(ObjectPtr, _args);
        }

        /// <summary>Called whenever the RigidShape object exits liquid.</summary>
        /// <description>
        /// 
        /// </description>
        /// <param name="objId">The ID of the RigidShape object.</param>
        /// <param name="liquidType">Type if liquid that was exited.</param>
        /// <code>
        /// // The RigidShape object exits in a body of liquid, causing the callback to occur.
        /// RigidShape::onLeaveLiquid(%this,%objId,%liquidType)
        /// 	{
        /// 		// Code to run whenever this callback occurs.
        /// 	}
        /// </code>
        /// <see cref="ShapeBase" />
        public virtual void OnLeaveLiquid(string objId, string liquidType) {
             InternalUnsafeMethods.OnLeaveLiquid__Args _args = new InternalUnsafeMethods.OnLeaveLiquid__Args() {
                objId = objId,
                liquidType = liquidType,
             };
             InternalUnsafeMethods.OnLeaveLiquid()(ObjectPtr, _args);
        }

        /// <summary>Called whenever this RigidShape object enters liquid.</summary>
        /// <description>
        /// 
        /// </description>
        /// <param name="objId">The ID of the rigidShape object.</param>
        /// <param name="waterCoverage">Amount of water coverage the RigidShape has.</param>
        /// <param name="liquidType">Type of liquid that was entered.</param>
        /// <code>
        /// // The RigidShape object falls in a body of liquid, causing the callback to occur.
        /// RigidShape::onEnterLiquid(%this,%objId,%waterCoverage,%liquidType)
        /// 	{
        /// 		// Code to run whenever this callback occurs.
        /// 	}
        /// </code>
        /// <see cref="ShapeBase" />
        public virtual void OnEnterLiquid(string objId, float waterCoverage, string liquidType) {
             InternalUnsafeMethods.OnEnterLiquid__Args _args = new InternalUnsafeMethods.OnEnterLiquid__Args() {
                objId = objId,
                waterCoverage = waterCoverage,
                liquidType = liquidType,
             };
             InternalUnsafeMethods.OnEnterLiquid()(ObjectPtr, _args);
        }

        /// <description>
        /// Get the type info object for the RigidShape class.
        /// </description>
        /// <returns>The type info object for RigidShape</returns>
        public static EngineTypeInfo StaticGetType() {
             InternalUnsafeMethods.StaticGetType__Args _args = new InternalUnsafeMethods.StaticGetType__Args() {
             };
             IntPtr _engineResult = InternalUnsafeMethods.StaticGetType()(_args);
             return new EngineTypeInfo(_engineResult);
        }
    }
}