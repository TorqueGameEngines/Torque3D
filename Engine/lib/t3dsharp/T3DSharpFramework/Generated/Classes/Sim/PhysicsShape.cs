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
    /// <summary>Represents a destructible physical object simulated through the plugin system.</summary>
    /// <description>
    /// 
    /// </description>
    /// <see cref="PhysicsShapeData." />
    public unsafe class PhysicsShape : GameBase {
        public PhysicsShape(bool pRegister = false) 
            : base(pRegister) {
        }
        
        public PhysicsShape(string pName, bool pRegister) 
            : this(false) {
            Name = pName;
            if (pRegister) {
                RegisterObject();
            }
        }
        
        public PhysicsShape(string pName) 
            : this(pName, false) {
        }
        
        public PhysicsShape(string pName, string pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(Engine.Sim.FindObject<SimObject>(pParent));
        }
        
        public PhysicsShape(string pName, SimObject pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(pParent);
        }
        
        public PhysicsShape(SimObject pObj) 
            : base(pObj) {
        }
        
        public PhysicsShape(IntPtr pObj) 
            : base(pObj) {
        }
        
		protected override void CreateObjectPtr()
		{
			ObjectPtr = InternalUnsafeMethods.Create()(new InternalUnsafeMethods.Create__Args());
		}

        #region UnsafeNativeMethods
        new internal struct InternalUnsafeMethods {
            [StructLayout(LayoutKind.Sequential)]
            internal struct ApplyForce__Args
            {
                internal IntPtr force;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _ApplyForce(IntPtr _this, ApplyForce__Args args);
            private static _ApplyForce _ApplyForceFunc;
            internal static _ApplyForce ApplyForce() {
                if (_ApplyForceFunc == null) {
                    _ApplyForceFunc =
                        (_ApplyForce)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnPhysicsShape_applyForce"), typeof(_ApplyForce));
                }
                
                return _ApplyForceFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct ApplyTorque__Args
            {
                internal IntPtr torque;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _ApplyTorque(IntPtr _this, ApplyTorque__Args args);
            private static _ApplyTorque _ApplyTorqueFunc;
            internal static _ApplyTorque ApplyTorque() {
                if (_ApplyTorqueFunc == null) {
                    _ApplyTorqueFunc =
                        (_ApplyTorque)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnPhysicsShape_applyTorque"), typeof(_ApplyTorque));
                }
                
                return _ApplyTorqueFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct Restore__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _Restore(IntPtr _this, Restore__Args args);
            private static _Restore _RestoreFunc;
            internal static _Restore Restore() {
                if (_RestoreFunc == null) {
                    _RestoreFunc =
                        (_Restore)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnPhysicsShape_restore"), typeof(_Restore));
                }
                
                return _RestoreFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct Destroy__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _Destroy(IntPtr _this, Destroy__Args args);
            private static _Destroy _DestroyFunc;
            internal static _Destroy Destroy() {
                if (_DestroyFunc == null) {
                    _DestroyFunc =
                        (_Destroy)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnPhysicsShape_destroy"), typeof(_Destroy));
                }
                
                return _DestroyFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct IsDestroyed__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            [return: MarshalAs(UnmanagedType.I1)]
            internal delegate bool _IsDestroyed(IntPtr _this, IsDestroyed__Args args);
            private static _IsDestroyed _IsDestroyedFunc;
            internal static _IsDestroyed IsDestroyed() {
                if (_IsDestroyedFunc == null) {
                    _IsDestroyedFunc =
                        (_IsDestroyed)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnPhysicsShape_isDestroyed"), typeof(_IsDestroyed));
                }
                
                return _IsDestroyedFunc;
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
                                "fnPhysicsShape_staticGetType"), typeof(_StaticGetType));
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
                                "fnPhysicsShape_create"), typeof(_Create));
                }
                
                return _CreateFunc;
            }
        }
        #endregion

        /// <summary>Add a force to a dynamic physics shape.</summary>
        /// <description>
        /// 
        /// </description>
        /// <param name="force">to apply to the dynamic physics shape</param>
        /// <remarks> This value is ignored on physics shapes that are not dynamic. Wakes up the dynamic physics shape if it is sleeping.
        /// </remarks>
        public void ApplyForce(Point3F force) {
force.Alloc();             InternalUnsafeMethods.ApplyForce__Args _args = new InternalUnsafeMethods.ApplyForce__Args() {
                force = force.internalStructPtr,
             };
             InternalUnsafeMethods.ApplyForce()(ObjectPtr, _args);
force.Free();        }

        /// <summary>Add a torque to a dynamic physics shape.</summary>
        /// <description>
        /// 
        /// </description>
        /// <param name="torque">to apply to the dynamic physics shape</param>
        /// <remarks> This value is ignored on physics shapes that are not dynamic. Wakes up the dynamic physics shape if it is sleeping.
        /// </remarks>
        public void ApplyTorque(Point3F torque) {
torque.Alloc();             InternalUnsafeMethods.ApplyTorque__Args _args = new InternalUnsafeMethods.ApplyTorque__Args() {
                torque = torque.internalStructPtr,
             };
             InternalUnsafeMethods.ApplyTorque()(ObjectPtr, _args);
torque.Free();        }

        /// <summary>Restores the shape to its state before being destroyed.</summary>
        /// <description>
        /// Re-enables rendering and physical simulation on the object and adds it to the client's scene graph. Has no effect if the shape is not destroyed.
        /// </description>
        public void Restore() {
             InternalUnsafeMethods.Restore__Args _args = new InternalUnsafeMethods.Restore__Args() {
             };
             InternalUnsafeMethods.Restore()(ObjectPtr, _args);
        }

        /// <summary>Disables rendering and physical simulation.</summary>
        /// <description>
        /// Calling destroy() will also spawn any explosions, debris, and/or destroyedShape defined for it, as well as remove it from the scene graph.
        /// 
        /// Destroyed objects are only created on the server. Ghosting will later update the client.
        /// </description>
        /// <remarks> This does not actually delete the PhysicsShape.</remarks>
        public void Destroy() {
             InternalUnsafeMethods.Destroy__Args _args = new InternalUnsafeMethods.Destroy__Args() {
             };
             InternalUnsafeMethods.Destroy()(ObjectPtr, _args);
        }

        /// <summary>Returns if a PhysicsShape has been destroyed or not.</summary>
        /// <description>
        /// 
        /// </description>
        public bool IsDestroyed() {
             InternalUnsafeMethods.IsDestroyed__Args _args = new InternalUnsafeMethods.IsDestroyed__Args() {
             };
             bool _engineResult = InternalUnsafeMethods.IsDestroyed()(ObjectPtr, _args);
             return _engineResult;
        }

        /// <description>
        /// Get the type info object for the PhysicsShape class.
        /// </description>
        /// <returns>The type info object for PhysicsShape</returns>
        public static EngineTypeInfo StaticGetType() {
             InternalUnsafeMethods.StaticGetType__Args _args = new InternalUnsafeMethods.StaticGetType__Args() {
             };
             IntPtr _engineResult = InternalUnsafeMethods.StaticGetType()(_args);
             return new EngineTypeInfo(_engineResult);
        }


        /// <value>
        /// <summary>Enables or disables playing of an ambient animation upon loading the shape.</summary>
        /// <description>
        /// 
        /// </description>
        /// <remarks> The ambient animation must be named "ambient".</remarks>
        /// </value>
        public bool PlayAmbient {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("playAmbient"));
            set => SetFieldValue("playAmbient", GenericMarshal.ToString(value));
        }
    }
}