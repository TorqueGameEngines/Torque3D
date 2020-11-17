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
    /// <summary>Magic-missile class used internally by afxMagicSpell. Properties of individual missile types are defined using afxMagicMissileData.</summary>
    /// <description>
    /// 
    /// </description>
    public unsafe class afxMagicMissile : GameBase {
        public afxMagicMissile(bool pRegister = false) 
            : base(pRegister) {
        }
        
        public afxMagicMissile(string pName, bool pRegister) 
            : this(false) {
            Name = pName;
            if (pRegister) {
                RegisterObject();
            }
        }
        
        public afxMagicMissile(string pName) 
            : this(pName, false) {
        }
        
        public afxMagicMissile(string pName, string pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(Engine.Sim.FindObject<SimObject>(pParent));
        }
        
        public afxMagicMissile(string pName, SimObject pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(pParent);
        }
        
        public afxMagicMissile(SimObject pObj) 
            : base(pObj) {
        }
        
        public afxMagicMissile(IntPtr pObj) 
            : base(pObj) {
        }
        
		protected override void CreateObjectPtr()
		{
			ObjectPtr = InternalUnsafeMethods.Create()(new InternalUnsafeMethods.Create__Args());
		}

        #region UnsafeNativeMethods
        new internal struct InternalUnsafeMethods {
            [StructLayout(LayoutKind.Sequential)]
            internal struct SetStartingVelocity__Args
            {
                internal float velocity;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _SetStartingVelocity(IntPtr _this, SetStartingVelocity__Args args);
            private static _SetStartingVelocity _SetStartingVelocityFunc;
            internal static _SetStartingVelocity SetStartingVelocity() {
                if (_SetStartingVelocityFunc == null) {
                    _SetStartingVelocityFunc =
                        (_SetStartingVelocity)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnafxMagicMissile_setStartingVelocity"), typeof(_SetStartingVelocity));
                }
                
                return _SetStartingVelocityFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct SetStartingVelocityVector__Args
            {
                internal IntPtr velocityVec;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _SetStartingVelocityVector(IntPtr _this, SetStartingVelocityVector__Args args);
            private static _SetStartingVelocityVector _SetStartingVelocityVectorFunc;
            internal static _SetStartingVelocityVector SetStartingVelocityVector() {
                if (_SetStartingVelocityVectorFunc == null) {
                    _SetStartingVelocityVectorFunc =
                        (_SetStartingVelocityVector)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnafxMagicMissile_setStartingVelocityVector"), typeof(_SetStartingVelocityVector));
                }
                
                return _SetStartingVelocityVectorFunc;
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
                                "fnafxMagicMissile_staticGetType"), typeof(_StaticGetType));
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
                                "fnafxMagicMissile_create"), typeof(_Create));
                }
                
                return _CreateFunc;
            }
        }
        #endregion

        /// <description>
        /// Set the starting velocity for a magic-missile.
        /// </description>
        public void SetStartingVelocity(float velocity) {
             InternalUnsafeMethods.SetStartingVelocity__Args _args = new InternalUnsafeMethods.SetStartingVelocity__Args() {
                velocity = velocity,
             };
             InternalUnsafeMethods.SetStartingVelocity()(ObjectPtr, _args);
        }

        /// <description>
        /// Set the starting velocity-vector for a magic-missile.
        /// </description>
        public void SetStartingVelocityVector(Point3F velocityVec) {
velocityVec.Alloc();             InternalUnsafeMethods.SetStartingVelocityVector__Args _args = new InternalUnsafeMethods.SetStartingVelocityVector__Args() {
                velocityVec = velocityVec.internalStructPtr,
             };
             InternalUnsafeMethods.SetStartingVelocityVector()(ObjectPtr, _args);
velocityVec.Free();        }

        /// <description>
        /// Get the type info object for the afxMagicMissile class.
        /// </description>
        /// <returns>The type info object for afxMagicMissile</returns>
        public static EngineTypeInfo StaticGetType() {
             InternalUnsafeMethods.StaticGetType__Args _args = new InternalUnsafeMethods.StaticGetType__Args() {
             };
             IntPtr _engineResult = InternalUnsafeMethods.StaticGetType()(_args);
             return new EngineTypeInfo(_engineResult);
        }


        /// <value>
        /// <description>
        /// Initial starting position for this missile.
        /// </description>
        /// </value>
        public Point3F InitialPosition {
            get => GenericMarshal.StringTo<Point3F>(GetFieldValue("initialPosition"));
            set => SetFieldValue("initialPosition", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Initial starting velocity for this missile.
        /// </description>
        /// </value>
        public Point3F InitialVelocity {
            get => GenericMarshal.StringTo<Point3F>(GetFieldValue("initialVelocity"));
            set => SetFieldValue("initialVelocity", GenericMarshal.ToString(value));
        }
    }
}