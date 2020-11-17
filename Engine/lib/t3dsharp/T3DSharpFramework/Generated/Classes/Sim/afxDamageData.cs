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
    /// <summary>A datablock that specifies a Damage effect.</summary>
    /// <description>
    /// A Damage effect is useful for assigning damage with unusual timing that must be synchronized with other effects. They can be used to deal direct damage, radius damage, and damage over time. Negative damage amounts can be used for healing effects.
    /// </description>
    public unsafe class afxDamageData : GameBaseData {
        public afxDamageData(bool pRegister = false) 
            : base(pRegister) {
        }
        
        public afxDamageData(string pName, bool pRegister) 
            : this(false) {
            Name = pName;
            if (pRegister) {
                RegisterObject();
            }
        }
        
        public afxDamageData(string pName) 
            : this(pName, false) {
        }
        
        public afxDamageData(string pName, string pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(Engine.Sim.FindObject<SimObject>(pParent));
        }
        
        public afxDamageData(string pName, SimObject pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(pParent);
        }
        
        public afxDamageData(SimObject pObj) 
            : base(pObj) {
        }
        
        public afxDamageData(IntPtr pObj) 
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
                                "fnafxDamageData_staticGetType"), typeof(_StaticGetType));
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
                                "fnafxDamageData_create"), typeof(_Create));
                }
                
                return _CreateFunc;
            }
        }
        #endregion

        /// <description>
        /// Get the type info object for the afxDamageData class.
        /// </description>
        /// <returns>The type info object for afxDamageData</returns>
        public static EngineTypeInfo StaticGetType() {
             InternalUnsafeMethods.StaticGetType__Args _args = new InternalUnsafeMethods.StaticGetType__Args() {
             };
             IntPtr _engineResult = InternalUnsafeMethods.StaticGetType()(_args);
             return new EngineTypeInfo(_engineResult);
        }


        /// <value>
        /// <description>
        /// An arbitrary string which is passed as an argument to a spell's onDamage() script method. It can be used to identify which damage effect the damage came from in cases where more than one damage effect is used in a single spell.
        /// </description>
        /// </value>
        public string Label {
            get => GenericMarshal.StringTo<string>(GetFieldValue("Label"));
            set => SetFieldValue("Label", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// An arbitrary string which is passed as an argument to a spell's onDamage() script method. It is used to classify a type of damage such as 'melee', 'magical', or 'fire'.
        /// </description>
        /// </value>
        public string Flavor {
            get => GenericMarshal.StringTo<string>(GetFieldValue("flavor"));
            set => SetFieldValue("flavor", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// An amount of direct damage to inflict on a target.
        /// </description>
        /// </value>
        public float DirectDamage {
            get => GenericMarshal.StringTo<float>(GetFieldValue("directDamage"));
            set => SetFieldValue("directDamage", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// The number of times to inflict the damage specified by directDamage. Values greater than 1 inflict damage over time, with the amount of directDamage repeatedly dealt at evenly spaced intervals over the lifetime of the effect.
        /// </description>
        /// </value>
        public sbyte DirectDamageRepeats {
            get => GenericMarshal.StringTo<sbyte>(GetFieldValue("directDamageRepeats"));
            set => SetFieldValue("directDamageRepeats", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// An amount of area damage to inflict on a target. Objects within half the radius receive full damage which then diminishes out to the full distance of areaDamageRadius.
        /// </description>
        /// </value>
        public float AreaDamage {
            get => GenericMarshal.StringTo<float>(GetFieldValue("areaDamage"));
            set => SetFieldValue("areaDamage", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Radius centered at the effect position in which damage will be applied.
        /// </description>
        /// </value>
        public float AreaDamageRadius {
            get => GenericMarshal.StringTo<float>(GetFieldValue("areaDamageRadius"));
            set => SetFieldValue("areaDamageRadius", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Specifies an amount of force to apply to damaged objects. Objects within half the radius receive full impulse which then diminishes out to the full distance of areaDamageRadius.
        /// </description>
        /// </value>
        public float AreaDamageImpulse {
            get => GenericMarshal.StringTo<float>(GetFieldValue("areaDamageImpulse"));
            set => SetFieldValue("areaDamageImpulse", GenericMarshal.ToString(value));
        }
    }
}