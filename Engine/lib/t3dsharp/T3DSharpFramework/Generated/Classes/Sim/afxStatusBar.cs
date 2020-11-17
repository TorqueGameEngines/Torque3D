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
    /// <summary>A GUI status bar for tracking and displaying health and energy of ShapeBase objects.</summary>
    /// <description>
    /// 
    /// </description>
    public unsafe class afxStatusBar : GuiControl {
        public afxStatusBar(bool pRegister = false) 
            : base(pRegister) {
        }
        
        public afxStatusBar(string pName, bool pRegister) 
            : this(false) {
            Name = pName;
            if (pRegister) {
                RegisterObject();
            }
        }
        
        public afxStatusBar(string pName) 
            : this(pName, false) {
        }
        
        public afxStatusBar(string pName, string pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(Engine.Sim.FindObject<SimObject>(pParent));
        }
        
        public afxStatusBar(string pName, SimObject pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(pParent);
        }
        
        public afxStatusBar(SimObject pObj) 
            : base(pObj) {
        }
        
        public afxStatusBar(IntPtr pObj) 
            : base(pObj) {
        }
        
		protected override void CreateObjectPtr()
		{
			ObjectPtr = InternalUnsafeMethods.Create()(new InternalUnsafeMethods.Create__Args());
		}

        #region UnsafeNativeMethods
        new internal struct InternalUnsafeMethods {
            [StructLayout(LayoutKind.Sequential)]
            internal struct ClearShape__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _ClearShape(IntPtr _this, ClearShape__Args args);
            private static _ClearShape _ClearShapeFunc;
            internal static _ClearShape ClearShape() {
                if (_ClearShapeFunc == null) {
                    _ClearShapeFunc =
                        (_ClearShape)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnafxStatusBar_clearShape"), typeof(_ClearShape));
                }
                
                return _ClearShapeFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct SetShape__Args
            {
                internal IntPtr shape;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _SetShape(IntPtr _this, SetShape__Args args);
            private static _SetShape _SetShapeFunc;
            internal static _SetShape SetShape() {
                if (_SetShapeFunc == null) {
                    _SetShapeFunc =
                        (_SetShape)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnafxStatusBar_setShape"), typeof(_SetShape));
                }
                
                return _SetShapeFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct SetProgress__Args
            {
                internal float percentDone;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _SetProgress(IntPtr _this, SetProgress__Args args);
            private static _SetProgress _SetProgressFunc;
            internal static _SetProgress SetProgress() {
                if (_SetProgressFunc == null) {
                    _SetProgressFunc =
                        (_SetProgress)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnafxStatusBar_setProgress"), typeof(_SetProgress));
                }
                
                return _SetProgressFunc;
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
                                "fnafxStatusBar_staticGetType"), typeof(_StaticGetType));
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
                                "fnafxStatusBar_create"), typeof(_Create));
                }
                
                return _CreateFunc;
            }
        }
        #endregion

        /// <description>
        /// Clear out any ShapeBase-derived object associated with the status-bar.
        /// </description>
        public void ClearShape() {
             InternalUnsafeMethods.ClearShape__Args _args = new InternalUnsafeMethods.ClearShape__Args() {
             };
             InternalUnsafeMethods.ClearShape()(ObjectPtr, _args);
        }

        /// <description>
        /// Associate a ShapeBase-derived object with the status-bar.
        /// </description>
        public void SetShape(ShapeBase shape) {
             InternalUnsafeMethods.SetShape__Args _args = new InternalUnsafeMethods.SetShape__Args() {
                shape = shape.ObjectPtr,
             };
             InternalUnsafeMethods.SetShape()(ObjectPtr, _args);
        }

        /// <description>
        /// Set the progress percentage on the status-bar.
        /// </description>
        public void SetProgress(float percentDone) {
             InternalUnsafeMethods.SetProgress__Args _args = new InternalUnsafeMethods.SetProgress__Args() {
                percentDone = percentDone,
             };
             InternalUnsafeMethods.SetProgress()(ObjectPtr, _args);
        }

        /// <description>
        /// Get the type info object for the afxStatusBar class.
        /// </description>
        /// <returns>The type info object for afxStatusBar</returns>
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
        public LinearColorF FillColor {
            get => GenericMarshal.StringTo<LinearColorF>(GetFieldValue("fillColor"));
            set => SetFieldValue("fillColor", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// ...
        /// </description>
        /// </value>
        public bool DisplayEnergy {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("displayEnergy"));
            set => SetFieldValue("displayEnergy", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// ...
        /// </description>
        /// </value>
        public bool MonitorPlayer {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("monitorPlayer"));
            set => SetFieldValue("monitorPlayer", GenericMarshal.ToString(value));
        }
    }
}