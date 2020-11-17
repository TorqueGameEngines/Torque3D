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
    /// <summary>Specialized GUI used for editing the MissionArea in a level</summary>
    /// <description>
    /// Editor use only.
    /// </description>
    public unsafe class GuiMissionAreaEditorCtrl : EditTSCtrl {
        public GuiMissionAreaEditorCtrl(bool pRegister = false) 
            : base(pRegister) {
        }
        
        public GuiMissionAreaEditorCtrl(string pName, bool pRegister) 
            : this(false) {
            Name = pName;
            if (pRegister) {
                RegisterObject();
            }
        }
        
        public GuiMissionAreaEditorCtrl(string pName) 
            : this(pName, false) {
        }
        
        public GuiMissionAreaEditorCtrl(string pName, string pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(Engine.Sim.FindObject<SimObject>(pParent));
        }
        
        public GuiMissionAreaEditorCtrl(string pName, SimObject pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(pParent);
        }
        
        public GuiMissionAreaEditorCtrl(SimObject pObj) 
            : base(pObj) {
        }
        
        public GuiMissionAreaEditorCtrl(IntPtr pObj) 
            : base(pObj) {
        }
        
		protected override void CreateObjectPtr()
		{
			ObjectPtr = InternalUnsafeMethods.Create()(new InternalUnsafeMethods.Create__Args());
		}

        #region UnsafeNativeMethods
        new internal struct InternalUnsafeMethods {
            [StructLayout(LayoutKind.Sequential)]
            internal struct GetSelectedMissionArea__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            
            internal delegate IntPtr _GetSelectedMissionArea(IntPtr _this, GetSelectedMissionArea__Args args);
            private static _GetSelectedMissionArea _GetSelectedMissionAreaFunc;
            internal static _GetSelectedMissionArea GetSelectedMissionArea() {
                if (_GetSelectedMissionAreaFunc == null) {
                    _GetSelectedMissionAreaFunc =
                        (_GetSelectedMissionArea)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnGuiMissionAreaEditorCtrl_getSelectedMissionArea"), typeof(_GetSelectedMissionArea));
                }
                
                return _GetSelectedMissionAreaFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct SetSelectedMissionArea__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string missionAreaName;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _SetSelectedMissionArea(IntPtr _this, SetSelectedMissionArea__Args args);
            private static _SetSelectedMissionArea _SetSelectedMissionAreaFunc;
            internal static _SetSelectedMissionArea SetSelectedMissionArea() {
                if (_SetSelectedMissionAreaFunc == null) {
                    _SetSelectedMissionAreaFunc =
                        (_SetSelectedMissionArea)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnGuiMissionAreaEditorCtrl_setSelectedMissionArea"), typeof(_SetSelectedMissionArea));
                }
                
                return _SetSelectedMissionAreaFunc;
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
                                "fnGuiMissionAreaEditorCtrl_staticGetType"), typeof(_StaticGetType));
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
                                "fnGuiMissionAreaEditorCtrl_create"), typeof(_Create));
                }
                
                return _CreateFunc;
            }
        }
        #endregion

        /// 
        public string GetSelectedMissionArea() {
             InternalUnsafeMethods.GetSelectedMissionArea__Args _args = new InternalUnsafeMethods.GetSelectedMissionArea__Args() {
             };
             IntPtr _engineResult = InternalUnsafeMethods.GetSelectedMissionArea()(ObjectPtr, _args);
             return StringMarshal.IntPtrToUtf8String(_engineResult);
        }

        /// 
        public void SetSelectedMissionArea(string missionAreaName = "") {
             InternalUnsafeMethods.SetSelectedMissionArea__Args _args = new InternalUnsafeMethods.SetSelectedMissionArea__Args() {
                missionAreaName = missionAreaName,
             };
             InternalUnsafeMethods.SetSelectedMissionArea()(ObjectPtr, _args);
        }

        /// <description>
        /// Get the type info object for the GuiMissionAreaEditorCtrl class.
        /// </description>
        /// <returns>The type info object for GuiMissionAreaEditorCtrl</returns>
        public static EngineTypeInfo StaticGetType() {
             InternalUnsafeMethods.StaticGetType__Args _args = new InternalUnsafeMethods.StaticGetType__Args() {
             };
             IntPtr _engineResult = InternalUnsafeMethods.StaticGetType()(_args);
             return new EngineTypeInfo(_engineResult);
        }
    }
}