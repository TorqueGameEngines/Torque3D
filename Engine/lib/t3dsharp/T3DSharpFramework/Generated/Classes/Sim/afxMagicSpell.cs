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
    /// <summary>A magic spell effects choreographer.</summary>
    /// <description>
    /// 
    /// </description>
    public unsafe class afxMagicSpell : afxChoreographer {
        public afxMagicSpell(bool pRegister = false) 
            : base(pRegister) {
        }
        
        public afxMagicSpell(string pName, bool pRegister) 
            : this(false) {
            Name = pName;
            if (pRegister) {
                RegisterObject();
            }
        }
        
        public afxMagicSpell(string pName) 
            : this(pName, false) {
        }
        
        public afxMagicSpell(string pName, string pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(Engine.Sim.FindObject<SimObject>(pParent));
        }
        
        public afxMagicSpell(string pName, SimObject pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(pParent);
        }
        
        public afxMagicSpell(SimObject pObj) 
            : base(pObj) {
        }
        
        public afxMagicSpell(IntPtr pObj) 
            : base(pObj) {
        }
        
		protected override void CreateObjectPtr()
		{
			ObjectPtr = InternalUnsafeMethods.Create()(new InternalUnsafeMethods.Create__Args());
		}

        #region UnsafeNativeMethods
        new internal struct InternalUnsafeMethods {
            [StructLayout(LayoutKind.Sequential)]
            internal struct Activate__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _Activate(IntPtr _this, Activate__Args args);
            private static _Activate _ActivateFunc;
            internal static _Activate Activate() {
                if (_ActivateFunc == null) {
                    _ActivateFunc =
                        (_Activate)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnafxMagicSpell_activate"), typeof(_Activate));
                }
                
                return _ActivateFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct Interrupt__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _Interrupt(IntPtr _this, Interrupt__Args args);
            private static _Interrupt _InterruptFunc;
            internal static _Interrupt Interrupt() {
                if (_InterruptFunc == null) {
                    _InterruptFunc =
                        (_Interrupt)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnafxMagicSpell_interrupt"), typeof(_Interrupt));
                }
                
                return _InterruptFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct InterruptStage__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _InterruptStage(IntPtr _this, InterruptStage__Args args);
            private static _InterruptStage _InterruptStageFunc;
            internal static _InterruptStage InterruptStage() {
                if (_InterruptStageFunc == null) {
                    _InterruptStageFunc =
                        (_InterruptStage)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnafxMagicSpell_interruptStage"), typeof(_InterruptStage));
                }
                
                return _InterruptStageFunc;
            }


            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _SetTimeFactor(IntPtr _this, ref StringVector.InternalStruct args);
            private static _SetTimeFactor _SetTimeFactorFunc;
            internal static _SetTimeFactor SetTimeFactor() {
                if (_SetTimeFactorFunc == null) {
                    _SetTimeFactorFunc =
                        (_SetTimeFactor)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnafxMagicSpell_setTimeFactor"), typeof(_SetTimeFactor));
                }
                
                return _SetTimeFactorFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct GetImpactedObject__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate int _GetImpactedObject(IntPtr _this, GetImpactedObject__Args args);
            private static _GetImpactedObject _GetImpactedObjectFunc;
            internal static _GetImpactedObject GetImpactedObject() {
                if (_GetImpactedObjectFunc == null) {
                    _GetImpactedObjectFunc =
                        (_GetImpactedObject)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnafxMagicSpell_getImpactedObject"), typeof(_GetImpactedObject));
                }
                
                return _GetImpactedObjectFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct GetMissile__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate int _GetMissile(IntPtr _this, GetMissile__Args args);
            private static _GetMissile _GetMissileFunc;
            internal static _GetMissile GetMissile() {
                if (_GetMissileFunc == null) {
                    _GetMissileFunc =
                        (_GetMissile)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnafxMagicSpell_getMissile"), typeof(_GetMissile));
                }
                
                return _GetMissileFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct GetTarget__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate int _GetTarget(IntPtr _this, GetTarget__Args args);
            private static _GetTarget _GetTargetFunc;
            internal static _GetTarget GetTarget() {
                if (_GetTargetFunc == null) {
                    _GetTargetFunc =
                        (_GetTarget)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnafxMagicSpell_getTarget"), typeof(_GetTarget));
                }
                
                return _GetTargetFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct GetCaster__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate int _GetCaster(IntPtr _this, GetCaster__Args args);
            private static _GetCaster _GetCasterFunc;
            internal static _GetCaster GetCaster() {
                if (_GetCasterFunc == null) {
                    _GetCasterFunc =
                        (_GetCaster)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnafxMagicSpell_getCaster"), typeof(_GetCaster));
                }
                
                return _GetCasterFunc;
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
                                "fnafxMagicSpell_staticGetType"), typeof(_StaticGetType));
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
                                "fnafxMagicSpell_create"), typeof(_Create));
                }
                
                return _CreateFunc;
            }
        }
        #endregion

        /// <description>
        /// Activates a magic spell that was started with postponeActivation=true.
        /// </description>
        public void Activate() {
             InternalUnsafeMethods.Activate__Args _args = new InternalUnsafeMethods.Activate__Args() {
             };
             InternalUnsafeMethods.Activate()(ObjectPtr, _args);
        }

        /// <description>
        /// Interrupts and deletes a running magic spell.
        /// </description>
        public void Interrupt() {
             InternalUnsafeMethods.Interrupt__Args _args = new InternalUnsafeMethods.Interrupt__Args() {
             };
             InternalUnsafeMethods.Interrupt()(ObjectPtr, _args);
        }

        /// <description>
        /// Interrupts the current stage of a magic spell causing it to move onto the next one.
        /// </description>
        public void InterruptStage() {
             InternalUnsafeMethods.InterruptStage__Args _args = new InternalUnsafeMethods.InterruptStage__Args() {
             };
             InternalUnsafeMethods.InterruptStage()(ObjectPtr, _args);
        }

        /// <description>
        /// (F32 factor) or (string phase, F32 factor)Sets the time-factor for the spell, either overall or for a specific phrase.
        /// </description>
        public void SetTimeFactor(params string[] args) { 
            List<string> _argList = new List<string>() {"", ""};
            _argList.AddRange(args);

            StringVector nativeVecArgs = new StringVector {
                ElementCount = (uint)_argList.Count,
                Array = _argList.ToArray(),
                ArraySize = (uint)_argList.Count
            };
            nativeVecArgs.Alloc();
            InternalUnsafeMethods.SetTimeFactor()(ObjectPtr, ref nativeVecArgs.internalStruct);
            nativeVecArgs.Free();

        }

        /// <description>
        /// Returns ID of impacted-object for the spell.
        /// </description>
        public int GetImpactedObject() {
             InternalUnsafeMethods.GetImpactedObject__Args _args = new InternalUnsafeMethods.GetImpactedObject__Args() {
             };
             int _engineResult = InternalUnsafeMethods.GetImpactedObject()(ObjectPtr, _args);
             return _engineResult;
        }

        /// <description>
        /// Returns ID of the spell's magic-missile object.
        /// </description>
        public int GetMissile() {
             InternalUnsafeMethods.GetMissile__Args _args = new InternalUnsafeMethods.GetMissile__Args() {
             };
             int _engineResult = InternalUnsafeMethods.GetMissile()(ObjectPtr, _args);
             return _engineResult;
        }

        /// <description>
        /// Returns ID of the spell's target object.
        /// </description>
        public int GetTarget() {
             InternalUnsafeMethods.GetTarget__Args _args = new InternalUnsafeMethods.GetTarget__Args() {
             };
             int _engineResult = InternalUnsafeMethods.GetTarget()(ObjectPtr, _args);
             return _engineResult;
        }

        /// <description>
        /// Returns ID of the spell's caster object.
        /// </description>
        public int GetCaster() {
             InternalUnsafeMethods.GetCaster__Args _args = new InternalUnsafeMethods.GetCaster__Args() {
             };
             int _engineResult = InternalUnsafeMethods.GetCaster()(ObjectPtr, _args);
             return _engineResult;
        }

        /// <description>
        /// Get the type info object for the afxMagicSpell class.
        /// </description>
        /// <returns>The type info object for afxMagicSpell</returns>
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
        public SimObject Caster {
            get => GenericMarshal.StringTo<SimObject>(GetFieldValue("caster"));
            set => SetFieldValue("caster", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// ...
        /// </description>
        /// </value>
        public SimObject Target {
            get => GenericMarshal.StringTo<SimObject>(GetFieldValue("Target"));
            set => SetFieldValue("Target", GenericMarshal.ToString(value));
        }
    }
}