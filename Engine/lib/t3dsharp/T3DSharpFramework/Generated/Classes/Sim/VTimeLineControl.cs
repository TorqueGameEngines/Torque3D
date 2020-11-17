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
    /// 
    public unsafe class VTimeLineControl : GuiControl {
        public VTimeLineControl(bool pRegister = false) 
            : base(pRegister) {
        }
        
        public VTimeLineControl(string pName, bool pRegister) 
            : this(false) {
            Name = pName;
            if (pRegister) {
                RegisterObject();
            }
        }
        
        public VTimeLineControl(string pName) 
            : this(pName, false) {
        }
        
        public VTimeLineControl(string pName, string pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(Engine.Sim.FindObject<SimObject>(pParent));
        }
        
        public VTimeLineControl(string pName, SimObject pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(pParent);
        }
        
        public VTimeLineControl(SimObject pObj) 
            : base(pObj) {
        }
        
        public VTimeLineControl(IntPtr pObj) 
            : base(pObj) {
        }
        
		protected override void CreateObjectPtr()
		{
			ObjectPtr = InternalUnsafeMethods.Create()(new InternalUnsafeMethods.Create__Args());
		}

        #region UnsafeNativeMethods
        new internal struct InternalUnsafeMethods {
            [StructLayout(LayoutKind.Sequential)]
            internal struct UpdateDuration__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _UpdateDuration(IntPtr _this, UpdateDuration__Args args);
            private static _UpdateDuration _UpdateDurationFunc;
            internal static _UpdateDuration UpdateDuration() {
                if (_UpdateDurationFunc == null) {
                    _UpdateDurationFunc =
                        (_UpdateDuration)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnVTimeLineControl_updateDuration"), typeof(_UpdateDuration));
                }
                
                return _UpdateDurationFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct SetSelection__Args
            {
                [MarshalAs(UnmanagedType.I1)]
                internal bool active;
                internal int time;
                internal int duration;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _SetSelection(IntPtr _this, SetSelection__Args args);
            private static _SetSelection _SetSelectionFunc;
            internal static _SetSelection SetSelection() {
                if (_SetSelectionFunc == null) {
                    _SetSelectionFunc =
                        (_SetSelection)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnVTimeLineControl_setSelection"), typeof(_SetSelection));
                }
                
                return _SetSelectionFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct GetSelection__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            
            internal delegate IntPtr _GetSelection(IntPtr _this, GetSelection__Args args);
            private static _GetSelection _GetSelectionFunc;
            internal static _GetSelection GetSelection() {
                if (_GetSelectionFunc == null) {
                    _GetSelectionFunc =
                        (_GetSelection)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnVTimeLineControl_getSelection"), typeof(_GetSelection));
                }
                
                return _GetSelectionFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct ToTime__Args
            {
                internal int point;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate int _ToTime(IntPtr _this, ToTime__Args args);
            private static _ToTime _ToTimeFunc;
            internal static _ToTime ToTime() {
                if (_ToTimeFunc == null) {
                    _ToTimeFunc =
                        (_ToTime)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnVTimeLineControl_toTime"), typeof(_ToTime));
                }
                
                return _ToTimeFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct ToPoint__Args
            {
                internal int time;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate int _ToPoint(IntPtr _this, ToPoint__Args args);
            private static _ToPoint _ToPointFunc;
            internal static _ToPoint ToPoint() {
                if (_ToPointFunc == null) {
                    _ToPointFunc =
                        (_ToPoint)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnVTimeLineControl_toPoint"), typeof(_ToPoint));
                }
                
                return _ToPointFunc;
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
                                "fnVTimeLineControl_staticGetType"), typeof(_StaticGetType));
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
                                "fnVTimeLineControl_create"), typeof(_Create));
                }
                
                return _CreateFunc;
            }
        }
        #endregion

        /// <description>
        /// ( )
        /// </description>
        public void UpdateDuration() {
             InternalUnsafeMethods.UpdateDuration__Args _args = new InternalUnsafeMethods.UpdateDuration__Args() {
             };
             InternalUnsafeMethods.UpdateDuration()(ObjectPtr, _args);
        }

        /// <description>
        /// ( pActive, [pTime, pDuration] )
        /// </description>
        public void SetSelection(bool active = true, int time = -1, int duration = 1) {
             InternalUnsafeMethods.SetSelection__Args _args = new InternalUnsafeMethods.SetSelection__Args() {
                active = active,
                time = time,
                duration = duration,
             };
             InternalUnsafeMethods.SetSelection()(ObjectPtr, _args);
        }

        /// <description>
        /// ( )
        /// </description>
        public string GetSelection() {
             InternalUnsafeMethods.GetSelection__Args _args = new InternalUnsafeMethods.GetSelection__Args() {
             };
             IntPtr _engineResult = InternalUnsafeMethods.GetSelection()(ObjectPtr, _args);
             return StringMarshal.IntPtrToUtf8String(_engineResult);
        }

        /// <description>
        /// ( pPoint )
        /// </description>
        public int ToTime(int point = 0) {
             InternalUnsafeMethods.ToTime__Args _args = new InternalUnsafeMethods.ToTime__Args() {
                point = point,
             };
             int _engineResult = InternalUnsafeMethods.ToTime()(ObjectPtr, _args);
             return _engineResult;
        }

        /// <description>
        /// ( pTime )
        /// </description>
        public int ToPoint(int time = 0) {
             InternalUnsafeMethods.ToPoint__Args _args = new InternalUnsafeMethods.ToPoint__Args() {
                time = time,
             };
             int _engineResult = InternalUnsafeMethods.ToPoint()(ObjectPtr, _args);
             return _engineResult;
        }

        /// <description>
        /// Get the type info object for the VTimeLineControl class.
        /// </description>
        /// <returns>The type info object for VTimeLineControl</returns>
        public static EngineTypeInfo StaticGetType() {
             InternalUnsafeMethods.StaticGetType__Args _args = new InternalUnsafeMethods.StaticGetType__Args() {
             };
             IntPtr _engineResult = InternalUnsafeMethods.StaticGetType()(_args);
             return new EngineTypeInfo(_engineResult);
        }


        /// <value>
        /// 
        /// </value>
        public bool IsController {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("IsController"));
            set => SetFieldValue("IsController", GenericMarshal.ToString(value));
        }


        /// <value>
        /// 
        /// </value>
        public VController Controller {
            get => GenericMarshal.StringTo<VController>(GetFieldValue("Controller"));
            set => SetFieldValue("Controller", GenericMarshal.ToString(value));
        }


        /// <value>
        /// 
        /// </value>
        public int DurationOffset {
            get => GenericMarshal.StringTo<int>(GetFieldValue("DurationOffset"));
            set => SetFieldValue("DurationOffset", GenericMarshal.ToString(value));
        }
    }
}