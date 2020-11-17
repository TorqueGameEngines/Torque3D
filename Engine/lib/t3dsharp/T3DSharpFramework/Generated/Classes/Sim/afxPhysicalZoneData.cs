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
    /// <summary>A datablock that specifies a PhysicalZone effect.</summary>
    /// <description>
    /// A Physical Zone is a Torque effect that applies physical forces to Players and other movable objects that enter a specific region of influence. AFX has enhanced Physical Zones by allowing orientation of vector forces and adding radial forces. AFX has also optimized Physical Zone networking so that they can be constrained to moving objects for a variety of effects including repelling and flying.
    /// </description>
    public unsafe class afxPhysicalZoneData : GameBaseData {
        public afxPhysicalZoneData(bool pRegister = false) 
            : base(pRegister) {
        }
        
        public afxPhysicalZoneData(string pName, bool pRegister) 
            : this(false) {
            Name = pName;
            if (pRegister) {
                RegisterObject();
            }
        }
        
        public afxPhysicalZoneData(string pName) 
            : this(pName, false) {
        }
        
        public afxPhysicalZoneData(string pName, string pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(Engine.Sim.FindObject<SimObject>(pParent));
        }
        
        public afxPhysicalZoneData(string pName, SimObject pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(pParent);
        }
        
        public afxPhysicalZoneData(SimObject pObj) 
            : base(pObj) {
        }
        
        public afxPhysicalZoneData(IntPtr pObj) 
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
                                "fnafxPhysicalZoneData_staticGetType"), typeof(_StaticGetType));
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
                                "fnafxPhysicalZoneData_create"), typeof(_Create));
                }
                
                return _CreateFunc;
            }
        }
        #endregion

        /// <description>
        /// Get the type info object for the afxPhysicalZoneData class.
        /// </description>
        /// <returns>The type info object for afxPhysicalZoneData</returns>
        public static EngineTypeInfo StaticGetType() {
             InternalUnsafeMethods.StaticGetType__Args _args = new InternalUnsafeMethods.StaticGetType__Args() {
             };
             IntPtr _engineResult = InternalUnsafeMethods.StaticGetType()(_args);
             return new EngineTypeInfo(_engineResult);
        }


        /// <value>
        /// <description>
        /// A multiplier that biases the velocity of an object every tick it is within the zone.
        /// </description>
        /// </value>
        public float VelocityMod {
            get => GenericMarshal.StringTo<float>(GetFieldValue("velocityMod"));
            set => SetFieldValue("velocityMod", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// A multiplier that biases the influence of gravity on objects within the zone.
        /// </description>
        /// </value>
        public float GravityMod {
            get => GenericMarshal.StringTo<float>(GetFieldValue("gravityMod"));
            set => SetFieldValue("gravityMod", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// A three-valued vector representing a directional force applied to objects withing the zone.
        /// </description>
        /// </value>
        public Point3F AppliedForce {
            get => GenericMarshal.StringTo<Point3F>(GetFieldValue("appliedForce"));
            set => SetFieldValue("appliedForce", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Floating point values describing the outer bounds of the PhysicalZone's region of influence.
        /// </description>
        /// </value>
        public string Polyhedron {
            get => GenericMarshal.StringTo<string>(GetFieldValue("polyhedron"));
            set => SetFieldValue("polyhedron", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// This enumerated attribute defines the type of force used in the PhysicalZone. Possible values: vector, sphere, or cylinder.
        /// </description>
        /// </value>
        public PhysicalZone_ForceType ForceType {
            get => GenericMarshal.StringTo<PhysicalZone_ForceType>(GetFieldValue("forceType"));
            set => SetFieldValue("forceType", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Determines if the force can be oriented by the PhysicalZone's transform matrix.
        /// </description>
        /// </value>
        public bool OrientForce {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("orientForce"));
            set => SetFieldValue("orientForce", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// When true, an object used as the primary position constraint of a physical-zone effect will not be influenced by the forces of the zone.
        /// </description>
        /// </value>
        public bool ExcludeConstraintObject {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("excludeConstraintObject"));
            set => SetFieldValue("excludeConstraintObject", GenericMarshal.ToString(value));
        }
    }
}