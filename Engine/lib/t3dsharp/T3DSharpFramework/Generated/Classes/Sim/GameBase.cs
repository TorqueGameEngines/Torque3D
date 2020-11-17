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
    /// <summary>Base class for game objects which use datablocks, networking, are editable, and need to process ticks.</summary>
    /// <description>
    /// 
    /// </description>
    public unsafe class GameBase : SceneObject {
        public GameBase(bool pRegister = false) 
            : base(pRegister) {
        }
        
        public GameBase(string pName, bool pRegister) 
            : this(false) {
            Name = pName;
            if (pRegister) {
                RegisterObject();
            }
        }
        
        public GameBase(string pName) 
            : this(pName, false) {
        }
        
        public GameBase(string pName, string pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(Engine.Sim.FindObject<SimObject>(pParent));
        }
        
        public GameBase(string pName, SimObject pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(pParent);
        }
        
        public GameBase(SimObject pObj) 
            : base(pObj) {
        }
        
        public GameBase(IntPtr pObj) 
            : base(pObj) {
        }
        
		protected override void CreateObjectPtr()
		{
			ObjectPtr = InternalUnsafeMethods.Create()(new InternalUnsafeMethods.Create__Args());
		}

        #region UnsafeNativeMethods
        new internal struct InternalUnsafeMethods {
            [StructLayout(LayoutKind.Sequential)]
            internal struct DetachChild__Args
            {
                internal IntPtr _subObject;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            [return: MarshalAs(UnmanagedType.I1)]
            internal delegate bool _DetachChild(IntPtr _this, DetachChild__Args args);
            private static _DetachChild _DetachChildFunc;
            internal static _DetachChild DetachChild() {
                if (_DetachChildFunc == null) {
                    _DetachChildFunc =
                        (_DetachChild)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnGameBase_detachChild"), typeof(_DetachChild));
                }
                
                return _DetachChildFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct AttachChild__Args
            {
                internal IntPtr _subObject;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            [return: MarshalAs(UnmanagedType.I1)]
            internal delegate bool _AttachChild(IntPtr _this, AttachChild__Args args);
            private static _AttachChild _AttachChildFunc;
            internal static _AttachChild AttachChild() {
                if (_AttachChildFunc == null) {
                    _AttachChildFunc =
                        (_AttachChild)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnGameBase_attachChild"), typeof(_AttachChild));
                }
                
                return _AttachChildFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct ApplyRadialImpulse__Args
            {
                internal IntPtr origin;
                internal float radius;
                internal float magnitude;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _ApplyRadialImpulse(IntPtr _this, ApplyRadialImpulse__Args args);
            private static _ApplyRadialImpulse _ApplyRadialImpulseFunc;
            internal static _ApplyRadialImpulse ApplyRadialImpulse() {
                if (_ApplyRadialImpulseFunc == null) {
                    _ApplyRadialImpulseFunc =
                        (_ApplyRadialImpulse)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnGameBase_applyRadialImpulse"), typeof(_ApplyRadialImpulse));
                }
                
                return _ApplyRadialImpulseFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct ApplyImpulse__Args
            {
                internal IntPtr pos;
                internal IntPtr vel;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            [return: MarshalAs(UnmanagedType.I1)]
            internal delegate bool _ApplyImpulse(IntPtr _this, ApplyImpulse__Args args);
            private static _ApplyImpulse _ApplyImpulseFunc;
            internal static _ApplyImpulse ApplyImpulse() {
                if (_ApplyImpulseFunc == null) {
                    _ApplyImpulseFunc =
                        (_ApplyImpulse)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnGameBase_applyImpulse"), typeof(_ApplyImpulse));
                }
                
                return _ApplyImpulseFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct SetDataBlock__Args
            {
                internal IntPtr data;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            [return: MarshalAs(UnmanagedType.I1)]
            internal delegate bool _SetDataBlock(IntPtr _this, SetDataBlock__Args args);
            private static _SetDataBlock _SetDataBlockFunc;
            internal static _SetDataBlock SetDataBlock() {
                if (_SetDataBlockFunc == null) {
                    _SetDataBlockFunc =
                        (_SetDataBlock)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnGameBase_setDataBlock"), typeof(_SetDataBlock));
                }
                
                return _SetDataBlockFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct GetDataBlock__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate int _GetDataBlock(IntPtr _this, GetDataBlock__Args args);
            private static _GetDataBlock _GetDataBlockFunc;
            internal static _GetDataBlock GetDataBlock() {
                if (_GetDataBlockFunc == null) {
                    _GetDataBlockFunc =
                        (_GetDataBlock)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnGameBase_getDataBlock"), typeof(_GetDataBlock));
                }
                
                return _GetDataBlockFunc;
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
                                "fnGameBase_staticGetType"), typeof(_StaticGetType));
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
                                "fnGameBase_create"), typeof(_Create));
                }
                
                return _CreateFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct SetControl__Args
            {
                [MarshalAs(UnmanagedType.I1)]
                internal bool controlled;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _SetControl(IntPtr _this, SetControl__Args args);
            private static _SetControl _SetControlFunc;
            internal static _SetControl SetControl() {
                if (_SetControlFunc == null) {
                    _SetControlFunc =
                        (_SetControl)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "cbGameBase_setControl"), typeof(_SetControl));
                }
                
                return _SetControlFunc;
            }
        }
        #endregion

        /// <description>
        /// (SceneObject subObject)attach an object to this one, preserving its present transform.
        /// </description>
        public bool DetachChild(GameBase _subObject = null) {
             InternalUnsafeMethods.DetachChild__Args _args = new InternalUnsafeMethods.DetachChild__Args() {
                _subObject = _subObject.ObjectPtr,
             };
             bool _engineResult = InternalUnsafeMethods.DetachChild()(ObjectPtr, _args);
             return _engineResult;
        }

        /// <description>
        /// (SceneObject subObject)attach an object to this one, preserving its present transform.
        /// </description>
        public bool AttachChild(GameBase _subObject = null) {
             InternalUnsafeMethods.AttachChild__Args _args = new InternalUnsafeMethods.AttachChild__Args() {
                _subObject = _subObject.ObjectPtr,
             };
             bool _engineResult = InternalUnsafeMethods.AttachChild()(ObjectPtr, _args);
             return _engineResult;
        }

        /// <summary>Applies a radial impulse to the object using the given origin and force.</summary>
        /// <description>
        /// 
        /// </description>
        /// <param name="origin">World point of origin of the radial impulse.</param>
        /// <param name="radius">The radius of the impulse area.</param>
        /// <param name="magnitude">The strength of the impulse.</param>
        /// <remarks> Not all objects that derrive from GameBase have this defined.
        /// </remarks>
        public void ApplyRadialImpulse(Point3F origin, float radius, float magnitude) {
origin.Alloc();             InternalUnsafeMethods.ApplyRadialImpulse__Args _args = new InternalUnsafeMethods.ApplyRadialImpulse__Args() {
                origin = origin.internalStructPtr,
                radius = radius,
                magnitude = magnitude,
             };
             InternalUnsafeMethods.ApplyRadialImpulse()(ObjectPtr, _args);
origin.Free();        }

        /// <summary>Apply an impulse to this object as defined by a world position and velocity vector.</summary>
        /// <description>
        /// 
        /// </description>
        /// <param name="pos">impulse world position</param>
        /// <param name="vel">impulse velocity (impulse force F = m * v)</param>
        /// <returns>Always true</returns>
        /// <remarks> Not all objects that derrive from GameBase have this defined.
        /// </remarks>
        public bool ApplyImpulse(Point3F pos, Point3F vel) {
pos.Alloc();vel.Alloc();             InternalUnsafeMethods.ApplyImpulse__Args _args = new InternalUnsafeMethods.ApplyImpulse__Args() {
                pos = pos.internalStructPtr,
                vel = vel.internalStructPtr,
             };
             bool _engineResult = InternalUnsafeMethods.ApplyImpulse()(ObjectPtr, _args);
pos.Free();vel.Free();             return _engineResult;
        }

        /// <summary>Assign this GameBase to use the specified datablock.</summary>
        /// <description>
        /// 
        /// </description>
        /// <param name="data">new datablock to use</param>
        /// <returns>true if successful, false if failed.</returns>
        /// <see cref="getDataBlock()" />
        public bool SetDataBlock(GameBaseData data) {
             InternalUnsafeMethods.SetDataBlock__Args _args = new InternalUnsafeMethods.SetDataBlock__Args() {
                data = data.ObjectPtr,
             };
             bool _engineResult = InternalUnsafeMethods.SetDataBlock()(ObjectPtr, _args);
             return _engineResult;
        }

        /// <summary>Get the datablock used by this object.</summary>
        /// <description>
        /// 
        /// </description>
        /// <returns>the datablock this GameBase is using.</returns>
        /// <see cref="setDataBlock()" />
        public int GetDataBlock() {
             InternalUnsafeMethods.GetDataBlock__Args _args = new InternalUnsafeMethods.GetDataBlock__Args() {
             };
             int _engineResult = InternalUnsafeMethods.GetDataBlock()(ObjectPtr, _args);
             return _engineResult;
        }

        /// <description>
        /// Get the type info object for the GameBase class.
        /// </description>
        /// <returns>The type info object for GameBase</returns>
        public static EngineTypeInfo StaticGetType() {
             InternalUnsafeMethods.StaticGetType__Args _args = new InternalUnsafeMethods.StaticGetType__Args() {
             };
             IntPtr _engineResult = InternalUnsafeMethods.StaticGetType()(_args);
             return new EngineTypeInfo(_engineResult);
        }

        /// <summary>Called when the client controlling the object changes.</summary>
        /// <description>
        /// 
        /// </description>
        /// <param name="controlled">true if a client now controls this object, false if no client controls this object.</param>
        public virtual void SetControl(bool controlled) {
             InternalUnsafeMethods.SetControl__Args _args = new InternalUnsafeMethods.SetControl__Args() {
                controlled = controlled,
             };
             InternalUnsafeMethods.SetControl()(ObjectPtr, _args);
        }


        /// <value>
        /// <description>
        /// Script datablock used for game objects.
        /// </description>
        /// </value>
        public GameBaseData DataBlock {
            get => GenericMarshal.StringTo<GameBaseData>(GetFieldValue("dataBlock"));
            set => SetFieldValue("dataBlock", GenericMarshal.ToString(value));
        }
    }
}