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
    /// <summary>A customized variation of GameTSCtrl.</summary>
    /// <description>
    /// 
    /// </description>
    public unsafe class afxTSCtrl : GuiTSCtrl {
        public afxTSCtrl(bool pRegister = false) 
            : base(pRegister) {
        }
        
        public afxTSCtrl(string pName, bool pRegister) 
            : this(false) {
            Name = pName;
            if (pRegister) {
                RegisterObject();
            }
        }
        
        public afxTSCtrl(string pName) 
            : this(pName, false) {
        }
        
        public afxTSCtrl(string pName, string pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(Engine.Sim.FindObject<SimObject>(pParent));
        }
        
        public afxTSCtrl(string pName, SimObject pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(pParent);
        }
        
        public afxTSCtrl(SimObject pObj) 
            : base(pObj) {
        }
        
        public afxTSCtrl(IntPtr pObj) 
            : base(pObj) {
        }
        
		protected override void CreateObjectPtr()
		{
			ObjectPtr = InternalUnsafeMethods.Create()(new InternalUnsafeMethods.Create__Args());
		}

        #region UnsafeNativeMethods
        new internal struct InternalUnsafeMethods {
            [StructLayout(LayoutKind.Sequential)]
            internal struct GetMouse3DPos__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate Point3F.InternalStruct _GetMouse3DPos(IntPtr _this, GetMouse3DPos__Args args);
            private static _GetMouse3DPos _GetMouse3DPosFunc;
            internal static _GetMouse3DPos GetMouse3DPos() {
                if (_GetMouse3DPosFunc == null) {
                    _GetMouse3DPosFunc =
                        (_GetMouse3DPos)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnafxTSCtrl_getMouse3DPos"), typeof(_GetMouse3DPos));
                }
                
                return _GetMouse3DPosFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct GetMouse3DVec__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate Point3F.InternalStruct _GetMouse3DVec(IntPtr _this, GetMouse3DVec__Args args);
            private static _GetMouse3DVec _GetMouse3DVecFunc;
            internal static _GetMouse3DVec GetMouse3DVec() {
                if (_GetMouse3DVecFunc == null) {
                    _GetMouse3DVecFunc =
                        (_GetMouse3DVec)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnafxTSCtrl_getMouse3DVec"), typeof(_GetMouse3DVec));
                }
                
                return _GetMouse3DVecFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct GetTargetingMode__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate int _GetTargetingMode(IntPtr _this, GetTargetingMode__Args args);
            private static _GetTargetingMode _GetTargetingModeFunc;
            internal static _GetTargetingMode GetTargetingMode() {
                if (_GetTargetingModeFunc == null) {
                    _GetTargetingModeFunc =
                        (_GetTargetingMode)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnafxTSCtrl_getTargetingMode"), typeof(_GetTargetingMode));
                }
                
                return _GetTargetingModeFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct PopTargetingMode__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _PopTargetingMode(IntPtr _this, PopTargetingMode__Args args);
            private static _PopTargetingMode _PopTargetingModeFunc;
            internal static _PopTargetingMode PopTargetingMode() {
                if (_PopTargetingModeFunc == null) {
                    _PopTargetingModeFunc =
                        (_PopTargetingMode)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnafxTSCtrl_popTargetingMode"), typeof(_PopTargetingMode));
                }
                
                return _PopTargetingModeFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct PushTargetingMode__Args
            {
                internal uint mode;
                internal uint checkMethod;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _PushTargetingMode(IntPtr _this, PushTargetingMode__Args args);
            private static _PushTargetingMode _PushTargetingModeFunc;
            internal static _PushTargetingMode PushTargetingMode() {
                if (_PushTargetingModeFunc == null) {
                    _PushTargetingModeFunc =
                        (_PushTargetingMode)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnafxTSCtrl_pushTargetingMode"), typeof(_PushTargetingMode));
                }
                
                return _PushTargetingModeFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct SetSpellBook__Args
            {
                internal IntPtr spellbook;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _SetSpellBook(IntPtr _this, SetSpellBook__Args args);
            private static _SetSpellBook _SetSpellBookFunc;
            internal static _SetSpellBook SetSpellBook() {
                if (_SetSpellBookFunc == null) {
                    _SetSpellBookFunc =
                        (_SetSpellBook)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnafxTSCtrl_setSpellBook"), typeof(_SetSpellBook));
                }
                
                return _SetSpellBookFunc;
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
                                "fnafxTSCtrl_staticGetType"), typeof(_StaticGetType));
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
                                "fnafxTSCtrl_create"), typeof(_Create));
                }
                
                return _CreateFunc;
            }
        }
        #endregion

        /// <description>
        /// Get the 3D position of the mouse cursor.
        /// </description>
        public Point3F GetMouse3DPos() {
             InternalUnsafeMethods.GetMouse3DPos__Args _args = new InternalUnsafeMethods.GetMouse3DPos__Args() {
             };
             Point3F.InternalStruct _engineResult = InternalUnsafeMethods.GetMouse3DPos()(ObjectPtr, _args);
             return new Point3F(_engineResult);
        }

        /// <description>
        /// Get the 3D direction vector for the mouse cursor.
        /// </description>
        public Point3F GetMouse3DVec() {
             InternalUnsafeMethods.GetMouse3DVec__Args _args = new InternalUnsafeMethods.GetMouse3DVec__Args() {
             };
             Point3F.InternalStruct _engineResult = InternalUnsafeMethods.GetMouse3DVec()(ObjectPtr, _args);
             return new Point3F(_engineResult);
        }

        /// <description>
        /// Get the current targeting-mode.
        /// </description>
        public int GetTargetingMode() {
             InternalUnsafeMethods.GetTargetingMode__Args _args = new InternalUnsafeMethods.GetTargetingMode__Args() {
             };
             int _engineResult = InternalUnsafeMethods.GetTargetingMode()(ObjectPtr, _args);
             return _engineResult;
        }

        /// <description>
        /// Pop the targeting-mode off a statck of modes.
        /// </description>
        public void PopTargetingMode() {
             InternalUnsafeMethods.PopTargetingMode__Args _args = new InternalUnsafeMethods.PopTargetingMode__Args() {
             };
             InternalUnsafeMethods.PopTargetingMode()(ObjectPtr, _args);
        }

        /// <description>
        /// Push a new targeting-mode onto a statck of modes.
        /// </description>
        public void PushTargetingMode(uint mode = 0, uint checkMethod = 0) {
             InternalUnsafeMethods.PushTargetingMode__Args _args = new InternalUnsafeMethods.PushTargetingMode__Args() {
                mode = mode,
                checkMethod = checkMethod,
             };
             InternalUnsafeMethods.PushTargetingMode()(ObjectPtr, _args);
        }

        /// <description>
        /// Associate a spellbook with an afxTSCtrl.
        /// </description>
        public void SetSpellBook(afxSpellBook spellbook) {
             InternalUnsafeMethods.SetSpellBook__Args _args = new InternalUnsafeMethods.SetSpellBook__Args() {
                spellbook = spellbook.ObjectPtr,
             };
             InternalUnsafeMethods.SetSpellBook()(ObjectPtr, _args);
        }

        /// <description>
        /// Get the type info object for the afxTSCtrl class.
        /// </description>
        /// <returns>The type info object for afxTSCtrl</returns>
        public static EngineTypeInfo StaticGetType() {
             InternalUnsafeMethods.StaticGetType__Args _args = new InternalUnsafeMethods.StaticGetType__Args() {
             };
             IntPtr _engineResult = InternalUnsafeMethods.StaticGetType()(_args);
             return new EngineTypeInfo(_engineResult);
        }
    }
}