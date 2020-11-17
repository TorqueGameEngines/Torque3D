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
    /// <summary>A datablock for defining RPG aspects of a spell.</summary>
    /// <description>
    /// 
    /// </description>
    public unsafe class afxRPGMagicSpellData : GameBaseData {
        public afxRPGMagicSpellData(bool pRegister = false) 
            : base(pRegister) {
        }
        
        public afxRPGMagicSpellData(string pName, bool pRegister) 
            : this(false) {
            Name = pName;
            if (pRegister) {
                RegisterObject();
            }
        }
        
        public afxRPGMagicSpellData(string pName) 
            : this(pName, false) {
        }
        
        public afxRPGMagicSpellData(string pName, string pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(Engine.Sim.FindObject<SimObject>(pParent));
        }
        
        public afxRPGMagicSpellData(string pName, SimObject pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(pParent);
        }
        
        public afxRPGMagicSpellData(SimObject pObj) 
            : base(pObj) {
        }
        
        public afxRPGMagicSpellData(IntPtr pObj) 
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
                                "fnafxRPGMagicSpellData_staticGetType"), typeof(_StaticGetType));
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
                                "fnafxRPGMagicSpellData_create"), typeof(_Create));
                }
                
                return _CreateFunc;
            }
        }
        #endregion

        /// <description>
        /// Get the type info object for the afxRPGMagicSpellData class.
        /// </description>
        /// <returns>The type info object for afxRPGMagicSpellData</returns>
        public static EngineTypeInfo StaticGetType() {
             InternalUnsafeMethods.StaticGetType__Args _args = new InternalUnsafeMethods.StaticGetType__Args() {
             };
             IntPtr _engineResult = InternalUnsafeMethods.StaticGetType()(_args);
             return new EngineTypeInfo(_engineResult);
        }


        /// <value>
        /// <description>
        /// ...
        /// </description>
        /// </value>
        public string SpellName {
            get => GenericMarshal.StringTo<string>(GetFieldValue("spellName"));
            set => SetFieldValue("spellName", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// ...
        /// </description>
        /// </value>
        public string Desc {
            get => GenericMarshal.StringTo<string>(GetFieldValue("desc"));
            set => SetFieldValue("desc", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// ...
        /// </description>
        /// </value>
        public afxRPGMagicSpell_TargetType Target {
            get => GenericMarshal.StringTo<afxRPGMagicSpell_TargetType>(GetFieldValue("Target"));
            set => SetFieldValue("Target", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// ...
        /// </description>
        /// </value>
        public float Range {
            get => GenericMarshal.StringTo<float>(GetFieldValue("range"));
            set => SetFieldValue("range", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// ...
        /// </description>
        /// </value>
        public int ManaCost {
            get => GenericMarshal.StringTo<int>(GetFieldValue("manaCost"));
            set => SetFieldValue("manaCost", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// ...
        /// </description>
        /// </value>
        public DynamicFieldVector<sbyte> ReagentCost {
            get => new DynamicFieldVector<sbyte>(
                    this, 
                    "reagentCost", 
                    8, 
                    val => GenericMarshal.StringTo<sbyte>(val),
                    obj => GenericMarshal.ToString(obj)
                );
        }


        /// <value>
        /// <description>
        /// ...
        /// </description>
        /// </value>
        public DynamicFieldVector<string> ReagentName {
            get => new DynamicFieldVector<string>(
                    this, 
                    "reagentName", 
                    8, 
                    val => GenericMarshal.StringTo<string>(val),
                    obj => GenericMarshal.ToString(obj)
                );
        }


        /// <value>
        /// 
        /// </value>
        public float CastingDur {
            get => GenericMarshal.StringTo<float>(GetFieldValue("castingDur"));
            set => SetFieldValue("castingDur", GenericMarshal.ToString(value));
        }


        /// <value>
        /// 
        /// </value>
        public string IconBitmap {
            get => GenericMarshal.StringTo<string>(GetFieldValue("iconBitmap"));
            set => SetFieldValue("iconBitmap", GenericMarshal.ToString(value));
        }


        /// <value>
        /// 
        /// </value>
        public string SourcePack {
            get => GenericMarshal.StringTo<string>(GetFieldValue("sourcePack"));
            set => SetFieldValue("sourcePack", GenericMarshal.ToString(value));
        }


        /// <value>
        /// 
        /// </value>
        public bool IsPlaceholder {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("isPlaceholder"));
            set => SetFieldValue("isPlaceholder", GenericMarshal.ToString(value));
        }


        /// <value>
        /// 
        /// </value>
        public sbyte FreeTargetStyle {
            get => GenericMarshal.StringTo<sbyte>(GetFieldValue("freeTargetStyle"));
            set => SetFieldValue("freeTargetStyle", GenericMarshal.ToString(value));
        }


        /// <value>
        /// 
        /// </value>
        public bool TargetOptional {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("targetOptional"));
            set => SetFieldValue("targetOptional", GenericMarshal.ToString(value));
        }
    }
}