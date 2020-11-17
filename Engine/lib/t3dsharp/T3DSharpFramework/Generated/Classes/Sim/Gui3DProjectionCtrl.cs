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
    public unsafe class Gui3DProjectionCtrl : GuiControl {
        public Gui3DProjectionCtrl(bool pRegister = false) 
            : base(pRegister) {
        }
        
        public Gui3DProjectionCtrl(string pName, bool pRegister) 
            : this(false) {
            Name = pName;
            if (pRegister) {
                RegisterObject();
            }
        }
        
        public Gui3DProjectionCtrl(string pName) 
            : this(pName, false) {
        }
        
        public Gui3DProjectionCtrl(string pName, string pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(Engine.Sim.FindObject<SimObject>(pParent));
        }
        
        public Gui3DProjectionCtrl(string pName, SimObject pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(pParent);
        }
        
        public Gui3DProjectionCtrl(SimObject pObj) 
            : base(pObj) {
        }
        
        public Gui3DProjectionCtrl(IntPtr pObj) 
            : base(pObj) {
        }
        
		protected override void CreateObjectPtr()
		{
			ObjectPtr = InternalUnsafeMethods.Create()(new InternalUnsafeMethods.Create__Args());
		}

        #region UnsafeNativeMethods
        new internal struct InternalUnsafeMethods {
            [StructLayout(LayoutKind.Sequential)]
            internal struct GetAttachedTo__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate int _GetAttachedTo(IntPtr _this, GetAttachedTo__Args args);
            private static _GetAttachedTo _GetAttachedToFunc;
            internal static _GetAttachedTo GetAttachedTo() {
                if (_GetAttachedToFunc == null) {
                    _GetAttachedToFunc =
                        (_GetAttachedTo)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnGui3DProjectionCtrl_getAttachedTo"), typeof(_GetAttachedTo));
                }
                
                return _GetAttachedToFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct SetAttachedTo__Args
            {
                internal IntPtr target;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _SetAttachedTo(IntPtr _this, SetAttachedTo__Args args);
            private static _SetAttachedTo _SetAttachedToFunc;
            internal static _SetAttachedTo SetAttachedTo() {
                if (_SetAttachedToFunc == null) {
                    _SetAttachedToFunc =
                        (_SetAttachedTo)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnGui3DProjectionCtrl_setAttachedTo"), typeof(_SetAttachedTo));
                }
                
                return _SetAttachedToFunc;
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
                                "fnGui3DProjectionCtrl_staticGetType"), typeof(_StaticGetType));
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
                                "fnGui3DProjectionCtrl_create"), typeof(_Create));
                }
                
                return _CreateFunc;
            }
        }
        #endregion

        /// <description>
        /// ()
        /// </description>
        public int GetAttachedTo() {
             InternalUnsafeMethods.GetAttachedTo__Args _args = new InternalUnsafeMethods.GetAttachedTo__Args() {
             };
             int _engineResult = InternalUnsafeMethods.GetAttachedTo()(ObjectPtr, _args);
             return _engineResult;
        }

        /// <description>
        /// (object)
        /// </description>
        public void SetAttachedTo(SceneObject target = null) {
             InternalUnsafeMethods.SetAttachedTo__Args _args = new InternalUnsafeMethods.SetAttachedTo__Args() {
                target = target.ObjectPtr,
             };
             InternalUnsafeMethods.SetAttachedTo()(ObjectPtr, _args);
        }

        /// <description>
        /// Get the type info object for the Gui3DProjectionCtrl class.
        /// </description>
        /// <returns>The type info object for Gui3DProjectionCtrl</returns>
        public static EngineTypeInfo StaticGetType() {
             InternalUnsafeMethods.StaticGetType__Args _args = new InternalUnsafeMethods.StaticGetType__Args() {
             };
             IntPtr _engineResult = InternalUnsafeMethods.StaticGetType()(_args);
             return new EngineTypeInfo(_engineResult);
        }


        /// <value>
        /// 
        /// </value>
        public Point3F PointWorld {
            get => GenericMarshal.StringTo<Point3F>(GetFieldValue("pointWorld"));
            set => SetFieldValue("pointWorld", GenericMarshal.ToString(value));
        }


        /// <value>
        /// 
        /// </value>
        public Point3F OffsetObject {
            get => GenericMarshal.StringTo<Point3F>(GetFieldValue("offsetObject"));
            set => SetFieldValue("offsetObject", GenericMarshal.ToString(value));
        }


        /// <value>
        /// 
        /// </value>
        public Point3F OffsetWorld {
            get => GenericMarshal.StringTo<Point3F>(GetFieldValue("offsetWorld"));
            set => SetFieldValue("offsetWorld", GenericMarshal.ToString(value));
        }


        /// <value>
        /// 
        /// </value>
        public Point2I OffsetScreen {
            get => GenericMarshal.StringTo<Point2I>(GetFieldValue("offsetScreen"));
            set => SetFieldValue("offsetScreen", GenericMarshal.ToString(value));
        }


        /// <value>
        /// 
        /// </value>
        public int HAlign {
            get => GenericMarshal.StringTo<int>(GetFieldValue("hAlign"));
            set => SetFieldValue("hAlign", GenericMarshal.ToString(value));
        }


        /// <value>
        /// 
        /// </value>
        public int VAlign {
            get => GenericMarshal.StringTo<int>(GetFieldValue("vAlign"));
            set => SetFieldValue("vAlign", GenericMarshal.ToString(value));
        }


        /// <value>
        /// 
        /// </value>
        public Point2I UseEyePoint {
            get => GenericMarshal.StringTo<Point2I>(GetFieldValue("useEyePoint"));
            set => SetFieldValue("useEyePoint", GenericMarshal.ToString(value));
        }


        /// <value>
        /// 
        /// </value>
        public bool AutoDelete {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("autoDelete"));
            set => SetFieldValue("autoDelete", GenericMarshal.ToString(value));
        }
    }
}