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
    /// <summary>Helper object for gameplay physical forces.</summary>
    /// <description>
    /// %PhysicsForces can be created and "attached" to other
    /// </description>
    public unsafe class PhysicsForce : SceneObject {
        public PhysicsForce(bool pRegister = false) 
            : base(pRegister) {
        }
        
        public PhysicsForce(string pName, bool pRegister) 
            : this(false) {
            Name = pName;
            if (pRegister) {
                RegisterObject();
            }
        }
        
        public PhysicsForce(string pName) 
            : this(pName, false) {
        }
        
        public PhysicsForce(string pName, string pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(Engine.Sim.FindObject<SimObject>(pParent));
        }
        
        public PhysicsForce(string pName, SimObject pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(pParent);
        }
        
        public PhysicsForce(SimObject pObj) 
            : base(pObj) {
        }
        
        public PhysicsForce(IntPtr pObj) 
            : base(pObj) {
        }
        
		protected override void CreateObjectPtr()
		{
			ObjectPtr = InternalUnsafeMethods.Create()(new InternalUnsafeMethods.Create__Args());
		}

        #region UnsafeNativeMethods
        new internal struct InternalUnsafeMethods {
            [StructLayout(LayoutKind.Sequential)]
            internal struct IsAttached__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            [return: MarshalAs(UnmanagedType.I1)]
            internal delegate bool _IsAttached(IntPtr _this, IsAttached__Args args);
            private static _IsAttached _IsAttachedFunc;
            internal static _IsAttached IsAttached() {
                if (_IsAttachedFunc == null) {
                    _IsAttachedFunc =
                        (_IsAttached)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnPhysicsForce_isAttached"), typeof(_IsAttached));
                }
                
                return _IsAttachedFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct Detach__Args
            {
                internal IntPtr force;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _Detach(IntPtr _this, Detach__Args args);
            private static _Detach _DetachFunc;
            internal static _Detach Detach() {
                if (_DetachFunc == null) {
                    _DetachFunc =
                        (_Detach)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnPhysicsForce_detach"), typeof(_Detach));
                }
                
                return _DetachFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct Attach__Args
            {
                internal IntPtr start;
                internal IntPtr direction;
                internal float maxDist;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _Attach(IntPtr _this, Attach__Args args);
            private static _Attach _AttachFunc;
            internal static _Attach Attach() {
                if (_AttachFunc == null) {
                    _AttachFunc =
                        (_Attach)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnPhysicsForce_attach"), typeof(_Attach));
                }
                
                return _AttachFunc;
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
                                "fnPhysicsForce_staticGetType"), typeof(_StaticGetType));
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
                                "fnPhysicsForce_create"), typeof(_Create));
                }
                
                return _CreateFunc;
            }
        }
        #endregion

        /// <summary>Returns true if the %PhysicsForce is currently attached to an object.</summary>
        /// <description>
        /// 
        /// </description>
        /// <see cref="PhysicsForce::attach()" />
        public bool IsAttached() {
             InternalUnsafeMethods.IsAttached__Args _args = new InternalUnsafeMethods.IsAttached__Args() {
             };
             bool _engineResult = InternalUnsafeMethods.IsAttached()(ObjectPtr, _args);
             return _engineResult;
        }

        /// <summary>Disassociates the PhysicsForce from any attached PhysicsBody.</summary>
        /// <description>
        /// 
        /// </description>
        /// <param name="force">Optional force to apply to the attached PhysicsBody before detaching.</param>
        /// <remarks> Has no effect if the %PhysicsForce is not attached to anything.
        /// 
        /// </remarks>
        public void Detach(Point3F force = null) {
force = force ?? new Point3F("0 0 0");
force.Alloc();             InternalUnsafeMethods.Detach__Args _args = new InternalUnsafeMethods.Detach__Args() {
                force = force.internalStructPtr,
             };
             InternalUnsafeMethods.Detach()(ObjectPtr, _args);
force.Free();        }

        /// <summary>Attempts to associate the PhysicsForce with a PhysicsBody.</summary>
        /// <description>
        /// Performs a physics ray cast of the provided length and direction. The %PhysicsForce will attach itself to the first dynamic PhysicsBody the ray collides with. On every tick, the attached body will be attracted towards the position of the %PhysicsForce.
        /// 
        /// A %PhysicsForce can only be attached to one body at a time.
        /// </description>
        /// <remarks> To determine if an %attach was successful, check isAttached() immediately after calling this function.n
        /// </remarks>
        public void Attach(Point3F start, Point3F direction, float maxDist) {
start.Alloc();direction.Alloc();             InternalUnsafeMethods.Attach__Args _args = new InternalUnsafeMethods.Attach__Args() {
                start = start.internalStructPtr,
                direction = direction.internalStructPtr,
                maxDist = maxDist,
             };
             InternalUnsafeMethods.Attach()(ObjectPtr, _args);
start.Free();direction.Free();        }

        /// <description>
        /// Get the type info object for the PhysicsForce class.
        /// </description>
        /// <returns>The type info object for PhysicsForce</returns>
        public static EngineTypeInfo StaticGetType() {
             InternalUnsafeMethods.StaticGetType__Args _args = new InternalUnsafeMethods.StaticGetType__Args() {
             };
             IntPtr _engineResult = InternalUnsafeMethods.StaticGetType()(_args);
             return new EngineTypeInfo(_engineResult);
        }
    }
}