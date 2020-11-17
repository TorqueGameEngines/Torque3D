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
    /// <summary>A spellbook object.</summary>
    /// <description>
    /// 
    /// </description>
    public unsafe class afxSpellBook : GameBase {
        public afxSpellBook(bool pRegister = false) 
            : base(pRegister) {
        }
        
        public afxSpellBook(string pName, bool pRegister) 
            : this(false) {
            Name = pName;
            if (pRegister) {
                RegisterObject();
            }
        }
        
        public afxSpellBook(string pName) 
            : this(pName, false) {
        }
        
        public afxSpellBook(string pName, string pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(Engine.Sim.FindObject<SimObject>(pParent));
        }
        
        public afxSpellBook(string pName, SimObject pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(pParent);
        }
        
        public afxSpellBook(SimObject pObj) 
            : base(pObj) {
        }
        
        public afxSpellBook(IntPtr pObj) 
            : base(pObj) {
        }
        
		protected override void CreateObjectPtr()
		{
			ObjectPtr = InternalUnsafeMethods.Create()(new InternalUnsafeMethods.Create__Args());
		}

        #region UnsafeNativeMethods
        new internal struct InternalUnsafeMethods {
            [StructLayout(LayoutKind.Sequential)]
            internal struct StartAllSpellCooldown__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _StartAllSpellCooldown(IntPtr _this, StartAllSpellCooldown__Args args);
            private static _StartAllSpellCooldown _StartAllSpellCooldownFunc;
            internal static _StartAllSpellCooldown StartAllSpellCooldown() {
                if (_StartAllSpellCooldownFunc == null) {
                    _StartAllSpellCooldownFunc =
                        (_StartAllSpellCooldown)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnafxSpellBook_startAllSpellCooldown"), typeof(_StartAllSpellCooldown));
                }
                
                return _StartAllSpellCooldownFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct GetSpellRPGData__Args
            {
                internal IntPtr bookSlot;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate int _GetSpellRPGData(IntPtr _this, GetSpellRPGData__Args args);
            private static _GetSpellRPGData _GetSpellRPGDataFunc;
            internal static _GetSpellRPGData GetSpellRPGData() {
                if (_GetSpellRPGDataFunc == null) {
                    _GetSpellRPGDataFunc =
                        (_GetSpellRPGData)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnafxSpellBook_getSpellRPGData"), typeof(_GetSpellRPGData));
                }
                
                return _GetSpellRPGDataFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct GetSpellData__Args
            {
                internal IntPtr bookSlot;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate int _GetSpellData(IntPtr _this, GetSpellData__Args args);
            private static _GetSpellData _GetSpellDataFunc;
            internal static _GetSpellData GetSpellData() {
                if (_GetSpellDataFunc == null) {
                    _GetSpellDataFunc =
                        (_GetSpellData)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnafxSpellBook_getSpellData"), typeof(_GetSpellData));
                }
                
                return _GetSpellDataFunc;
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
                                "fnafxSpellBook_getPageSlotIndex"), typeof(_GetPageSlotIndex));
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
                                "fnafxSpellBook_staticGetType"), typeof(_StaticGetType));
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
                                "fnafxSpellBook_create"), typeof(_Create));
                }
                
                return _CreateFunc;
            }
        }
        #endregion

        /// <description>
        /// ...
        /// </description>
        public void StartAllSpellCooldown() {
             InternalUnsafeMethods.StartAllSpellCooldown__Args _args = new InternalUnsafeMethods.StartAllSpellCooldown__Args() {
             };
             InternalUnsafeMethods.StartAllSpellCooldown()(ObjectPtr, _args);
        }

        /// <description>
        /// Get spell RPG datablock for spell stored at spellbook index, (page, slot).
        /// </description>
        public int GetSpellRPGData(Point2I bookSlot) {
bookSlot.Alloc();             InternalUnsafeMethods.GetSpellRPGData__Args _args = new InternalUnsafeMethods.GetSpellRPGData__Args() {
                bookSlot = bookSlot.internalStructPtr,
             };
             int _engineResult = InternalUnsafeMethods.GetSpellRPGData()(ObjectPtr, _args);
bookSlot.Free();             return _engineResult;
        }

        /// <description>
        /// Get spell datablock for spell stored at spellbook index, (page, slot).
        /// </description>
        public int GetSpellData(Point2I bookSlot) {
bookSlot.Alloc();             InternalUnsafeMethods.GetSpellData__Args _args = new InternalUnsafeMethods.GetSpellData__Args() {
                bookSlot = bookSlot.internalStructPtr,
             };
             int _engineResult = InternalUnsafeMethods.GetSpellData()(ObjectPtr, _args);
bookSlot.Free();             return _engineResult;
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
        /// Get the type info object for the afxSpellBook class.
        /// </description>
        /// <returns>The type info object for afxSpellBook</returns>
        public static EngineTypeInfo StaticGetType() {
             InternalUnsafeMethods.StaticGetType__Args _args = new InternalUnsafeMethods.StaticGetType__Args() {
             };
             IntPtr _engineResult = InternalUnsafeMethods.StaticGetType()(_args);
             return new EngineTypeInfo(_engineResult);
        }
    }
}