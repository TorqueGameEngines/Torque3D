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
    /// <summary>A spellbook datablock.</summary>
    /// <description>
    /// 
    /// </description>
    public unsafe class afxSpellBookData : GameBaseData {
        public afxSpellBookData(bool pRegister = false) 
            : base(pRegister) {
        }
        
        public afxSpellBookData(string pName, bool pRegister) 
            : this(false) {
            Name = pName;
            if (pRegister) {
                RegisterObject();
            }
        }
        
        public afxSpellBookData(string pName) 
            : this(pName, false) {
        }
        
        public afxSpellBookData(string pName, string pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(Engine.Sim.FindObject<SimObject>(pParent));
        }
        
        public afxSpellBookData(string pName, SimObject pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(pParent);
        }
        
        public afxSpellBookData(SimObject pObj) 
            : base(pObj) {
        }
        
        public afxSpellBookData(IntPtr pObj) 
            : base(pObj) {
        }
        
		protected override void CreateObjectPtr()
		{
			ObjectPtr = InternalUnsafeMethods.Create()(new InternalUnsafeMethods.Create__Args());
		}

        #region UnsafeNativeMethods
        new internal struct InternalUnsafeMethods {
            [StructLayout(LayoutKind.Sequential)]
            internal struct GetCapacity__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate int _GetCapacity(IntPtr _this, GetCapacity__Args args);
            private static _GetCapacity _GetCapacityFunc;
            internal static _GetCapacity GetCapacity() {
                if (_GetCapacityFunc == null) {
                    _GetCapacityFunc =
                        (_GetCapacity)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnafxSpellBookData_getCapacity"), typeof(_GetCapacity));
                }
                
                return _GetCapacityFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct GetPageSlotIndex__Args
            {
                internal IntPtr bookSlot;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate int _GetPageSlotIndex(IntPtr _this, GetPageSlotIndex__Args args);
            private static _GetPageSlotIndex _GetPageSlotIndexFunc;
            internal static _GetPageSlotIndex GetPageSlotIndex() {
                if (_GetPageSlotIndexFunc == null) {
                    _GetPageSlotIndexFunc =
                        (_GetPageSlotIndex)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnafxSpellBookData_getPageSlotIndex"), typeof(_GetPageSlotIndex));
                }
                
                return _GetPageSlotIndexFunc;
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
                                "fnafxSpellBookData_staticGetType"), typeof(_StaticGetType));
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
                                "fnafxSpellBookData_create"), typeof(_Create));
                }
                
                return _CreateFunc;
            }
        }
        #endregion

        /// <description>
        /// Get the capacity (total number of spell slots) in a spellbook.
        /// </description>
        public int GetCapacity() {
             InternalUnsafeMethods.GetCapacity__Args _args = new InternalUnsafeMethods.GetCapacity__Args() {
             };
             int _engineResult = InternalUnsafeMethods.GetCapacity()(ObjectPtr, _args);
             return _engineResult;
        }

        /// <description>
        /// ...
        /// </description>
        public int GetPageSlotIndex(Point2I bookSlot) {
bookSlot.Alloc();             InternalUnsafeMethods.GetPageSlotIndex__Args _args = new InternalUnsafeMethods.GetPageSlotIndex__Args() {
                bookSlot = bookSlot.internalStructPtr,
             };
             int _engineResult = InternalUnsafeMethods.GetPageSlotIndex()(ObjectPtr, _args);
bookSlot.Free();             return _engineResult;
        }

        /// <description>
        /// Get the type info object for the afxSpellBookData class.
        /// </description>
        /// <returns>The type info object for afxSpellBookData</returns>
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
        public sbyte SpellsPerPage {
            get => GenericMarshal.StringTo<sbyte>(GetFieldValue("spellsPerPage"));
            set => SetFieldValue("spellsPerPage", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// ...
        /// </description>
        /// </value>
        public sbyte PagesPerBook {
            get => GenericMarshal.StringTo<sbyte>(GetFieldValue("pagesPerBook"));
            set => SetFieldValue("pagesPerBook", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// ...
        /// </description>
        /// </value>
        public DynamicFieldVector<GameBaseData> Spells {
            get => new DynamicFieldVector<GameBaseData>(
                    this, 
                    "spells", 
                    144, 
                    val => GenericMarshal.StringTo<GameBaseData>(val),
                    obj => GenericMarshal.ToString(obj)
                );
        }


        /// <value>
        /// <description>
        /// ...
        /// </description>
        /// </value>
        public DynamicFieldVector<GameBaseData> RpgSpells {
            get => new DynamicFieldVector<GameBaseData>(
                    this, 
                    "rpgSpells", 
                    144, 
                    val => GenericMarshal.StringTo<GameBaseData>(val),
                    obj => GenericMarshal.ToString(obj)
                );
        }
    }
}