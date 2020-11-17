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
    /// <summary>A datablock that specifies an Area Damage effect.</summary>
    /// <description>
    /// An Area Damage effect is useful for assigning area damage with unusual timing that must be synchronized with other effects. Negative damage amounts can be used for healing effects.
    /// 
    /// The primary difference between afxAreaDamageData and afxDamageData, which is also capable of inflicting area damage, is that afxAreaDamageData effects calculate the area damage in C++ code rather than calling out to the script function radiusDamage(). In cases where area damage needs to be inflicted repeatedly or in areas crowded with many targets, afxAreaDamageData is likely to get better performance.
    /// </description>
    public unsafe class afxAreaDamageData : GameBaseData {
        public afxAreaDamageData(bool pRegister = false) 
            : base(pRegister) {
        }
        
        public afxAreaDamageData(string pName, bool pRegister) 
            : this(false) {
            Name = pName;
            if (pRegister) {
                RegisterObject();
            }
        }
        
        public afxAreaDamageData(string pName) 
            : this(pName, false) {
        }
        
        public afxAreaDamageData(string pName, string pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(Engine.Sim.FindObject<SimObject>(pParent));
        }
        
        public afxAreaDamageData(string pName, SimObject pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(pParent);
        }
        
        public afxAreaDamageData(SimObject pObj) 
            : base(pObj) {
        }
        
        public afxAreaDamageData(IntPtr pObj) 
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
                                "fnafxAreaDamageData_staticGetType"), typeof(_StaticGetType));
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
                                "fnafxAreaDamageData_create"), typeof(_Create));
                }
                
                return _CreateFunc;
            }
        }
        #endregion

        /// <description>
        /// Get the type info object for the afxAreaDamageData class.
        /// </description>
        /// <returns>The type info object for afxAreaDamageData</returns>
        public static EngineTypeInfo StaticGetType() {
             InternalUnsafeMethods.StaticGetType__Args _args = new InternalUnsafeMethods.StaticGetType__Args() {
             };
             IntPtr _engineResult = InternalUnsafeMethods.StaticGetType()(_args);
             return new EngineTypeInfo(_engineResult);
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
        /// An amount of area damage to inflict on a target. Objects within half the radius receive full damage which then diminishes out to the full distance of the specified radius.
        /// </description>
        /// </value>
        public float Damage {
            get => GenericMarshal.StringTo<float>(GetFieldValue("damage"));
            set => SetFieldValue("damage", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Radius centered at the effect position in which damage will be applied.
        /// </description>
        /// </value>
        public float Radius {
            get => GenericMarshal.StringTo<float>(GetFieldValue("radius"));
            set => SetFieldValue("radius", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Specifies an amount of force to apply to damaged objects. Objects within half the radius receive full impulse which then diminishes out to the full distance of the specified radius.
        /// </description>
        /// </value>
        public float Impulse {
            get => GenericMarshal.StringTo<float>(GetFieldValue("impulse"));
            set => SetFieldValue("impulse", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// When true, the onInflictedAreaDamage() method of the damaged object will be called to notify it of the damage. This is useful for starting some effects or action that responds to the damage.
        /// </description>
        /// </value>
        public bool NotifyDamageSource {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("notifyDamageSource"));
            set => SetFieldValue("notifyDamageSource", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// When true, the object specified as the effect's primary position constraint will not receive any damage.
        /// </description>
        /// </value>
        public bool ExcludeConstraintObject {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("excludeConstraintObject"));
            set => SetFieldValue("excludeConstraintObject", GenericMarshal.ToString(value));
        }
    }
}