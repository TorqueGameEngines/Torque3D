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
    /// <summary>Base class used by choreographers.</summary>
    /// <description>
    /// 
    /// </description>
    public unsafe class afxChoreographer : GameBase {
        public afxChoreographer(bool pRegister = false) 
            : base(pRegister) {
        }
        
        public afxChoreographer(string pName, bool pRegister) 
            : this(false) {
            Name = pName;
            if (pRegister) {
                RegisterObject();
            }
        }
        
        public afxChoreographer(string pName) 
            : this(pName, false) {
        }
        
        public afxChoreographer(string pName, string pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(Engine.Sim.FindObject<SimObject>(pParent));
        }
        
        public afxChoreographer(string pName, SimObject pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(pParent);
        }
        
        public afxChoreographer(SimObject pObj) 
            : base(pObj) {
        }
        
        public afxChoreographer(IntPtr pObj) 
            : base(pObj) {
        }
        
		protected override void CreateObjectPtr()
		{
			ObjectPtr = InternalUnsafeMethods.Create()(new InternalUnsafeMethods.Create__Args());
		}

        #region UnsafeNativeMethods
        new internal struct InternalUnsafeMethods {
            [StructLayout(LayoutKind.Sequential)]
            internal struct RemapConstraint__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string source;
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string name;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _RemapConstraint(IntPtr _this, RemapConstraint__Args args);
            private static _RemapConstraint _RemapConstraintFunc;
            internal static _RemapConstraint RemapConstraint() {
                if (_RemapConstraintFunc == null) {
                    _RemapConstraintFunc =
                        (_RemapConstraint)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnafxChoreographer_remapConstraint"), typeof(_RemapConstraint));
                }
                
                return _RemapConstraintFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct TestTriggerBit__Args
            {
                internal uint bit_num;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            [return: MarshalAs(UnmanagedType.I1)]
            internal delegate bool _TestTriggerBit(IntPtr _this, TestTriggerBit__Args args);
            private static _TestTriggerBit _TestTriggerBitFunc;
            internal static _TestTriggerBit TestTriggerBit() {
                if (_TestTriggerBitFunc == null) {
                    _TestTriggerBitFunc =
                        (_TestTriggerBit)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnafxChoreographer_testTriggerBit"), typeof(_TestTriggerBit));
                }
                
                return _TestTriggerBitFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct ClearTriggerBit__Args
            {
                internal uint bit_num;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _ClearTriggerBit(IntPtr _this, ClearTriggerBit__Args args);
            private static _ClearTriggerBit _ClearTriggerBitFunc;
            internal static _ClearTriggerBit ClearTriggerBit() {
                if (_ClearTriggerBitFunc == null) {
                    _ClearTriggerBitFunc =
                        (_ClearTriggerBit)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnafxChoreographer_clearTriggerBit"), typeof(_ClearTriggerBit));
                }
                
                return _ClearTriggerBitFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct SetTriggerBit__Args
            {
                internal uint bit_num;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _SetTriggerBit(IntPtr _this, SetTriggerBit__Args args);
            private static _SetTriggerBit _SetTriggerBitFunc;
            internal static _SetTriggerBit SetTriggerBit() {
                if (_SetTriggerBitFunc == null) {
                    _SetTriggerBitFunc =
                        (_SetTriggerBit)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnafxChoreographer_setTriggerBit"), typeof(_SetTriggerBit));
                }
                
                return _SetTriggerBitFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct AddExplicitClient__Args
            {
                internal IntPtr client;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _AddExplicitClient(IntPtr _this, AddExplicitClient__Args args);
            private static _AddExplicitClient _AddExplicitClientFunc;
            internal static _AddExplicitClient AddExplicitClient() {
                if (_AddExplicitClientFunc == null) {
                    _AddExplicitClientFunc =
                        (_AddExplicitClient)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnafxChoreographer_addExplicitClient"), typeof(_AddExplicitClient));
                }
                
                return _AddExplicitClientFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct AddConstraint__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string source;
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string name;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _AddConstraint(IntPtr _this, AddConstraint__Args args);
            private static _AddConstraint _AddConstraintFunc;
            internal static _AddConstraint AddConstraint() {
                if (_AddConstraintFunc == null) {
                    _AddConstraintFunc =
                        (_AddConstraint)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnafxChoreographer_addConstraint"), typeof(_AddConstraint));
                }
                
                return _AddConstraintFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct SetExecConditions__Args
            {
                internal uint mask;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _SetExecConditions(IntPtr _this, SetExecConditions__Args args);
            private static _SetExecConditions _SetExecConditionsFunc;
            internal static _SetExecConditions SetExecConditions() {
                if (_SetExecConditionsFunc == null) {
                    _SetExecConditionsFunc =
                        (_SetExecConditions)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnafxChoreographer_setExecConditions"), typeof(_SetExecConditions));
                }
                
                return _SetExecConditionsFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct SetLevelOfDetail__Args
            {
                internal uint lod;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _SetLevelOfDetail(IntPtr _this, SetLevelOfDetail__Args args);
            private static _SetLevelOfDetail _SetLevelOfDetailFunc;
            internal static _SetLevelOfDetail SetLevelOfDetail() {
                if (_SetLevelOfDetailFunc == null) {
                    _SetLevelOfDetailFunc =
                        (_SetLevelOfDetail)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnafxChoreographer_setLevelOfDetail"), typeof(_SetLevelOfDetail));
                }
                
                return _SetLevelOfDetailFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct SetRanking__Args
            {
                internal uint ranking;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _SetRanking(IntPtr _this, SetRanking__Args args);
            private static _SetRanking _SetRankingFunc;
            internal static _SetRanking SetRanking() {
                if (_SetRankingFunc == null) {
                    _SetRankingFunc =
                        (_SetRanking)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnafxChoreographer_setRanking"), typeof(_SetRanking));
                }
                
                return _SetRankingFunc;
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
                                "fnafxChoreographer_staticGetType"), typeof(_StaticGetType));
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
                                "fnafxChoreographer_create"), typeof(_Create));
                }
                
                return _CreateFunc;
            }
        }
        #endregion

        /// <description>
        /// Remap a dynamic constraint to use a new source. The source can be a SceneObject, a 3-valued position, or a 7-valued transform. but must match type of existing source.
        /// </description>
        public void RemapConstraint(string source, string name) {
             InternalUnsafeMethods.RemapConstraint__Args _args = new InternalUnsafeMethods.RemapConstraint__Args() {
                source = source,
                name = name,
             };
             InternalUnsafeMethods.RemapConstraint()(ObjectPtr, _args);
        }

        /// <description>
        /// Test state of a trigger-mask bit.
        /// </description>
        public bool TestTriggerBit(uint bit_num) {
             InternalUnsafeMethods.TestTriggerBit__Args _args = new InternalUnsafeMethods.TestTriggerBit__Args() {
                bit_num = bit_num,
             };
             bool _engineResult = InternalUnsafeMethods.TestTriggerBit()(ObjectPtr, _args);
             return _engineResult;
        }

        /// <description>
        /// Unset a bit of the trigger-mask.
        /// </description>
        public void ClearTriggerBit(uint bit_num) {
             InternalUnsafeMethods.ClearTriggerBit__Args _args = new InternalUnsafeMethods.ClearTriggerBit__Args() {
                bit_num = bit_num,
             };
             InternalUnsafeMethods.ClearTriggerBit()(ObjectPtr, _args);
        }

        /// <description>
        /// Set a bit of the trigger-mask.
        /// </description>
        public void SetTriggerBit(uint bit_num) {
             InternalUnsafeMethods.SetTriggerBit__Args _args = new InternalUnsafeMethods.SetTriggerBit__Args() {
                bit_num = bit_num,
             };
             InternalUnsafeMethods.SetTriggerBit()(ObjectPtr, _args);
        }

        /// <description>
        /// Add an explicit client.
        /// </description>
        public void AddExplicitClient(NetConnection client) {
             InternalUnsafeMethods.AddExplicitClient__Args _args = new InternalUnsafeMethods.AddExplicitClient__Args() {
                client = client.ObjectPtr,
             };
             InternalUnsafeMethods.AddExplicitClient()(ObjectPtr, _args);
        }

        /// <description>
        /// Add a dynamic constraint consistiing of a source and name. The source can be a SceneObject, a 3-valued position, or a 7-valued transform.
        /// </description>
        public void AddConstraint(string source, string name) {
             InternalUnsafeMethods.AddConstraint__Args _args = new InternalUnsafeMethods.AddConstraint__Args() {
                source = source,
                name = name,
             };
             InternalUnsafeMethods.AddConstraint()(ObjectPtr, _args);
        }

        /// <description>
        /// Set a bitmask to specifiy the state of exec-conditions.
        /// </description>
        public void SetExecConditions(uint mask) {
             InternalUnsafeMethods.SetExecConditions__Args _args = new InternalUnsafeMethods.SetExecConditions__Args() {
                mask = mask,
             };
             InternalUnsafeMethods.SetExecConditions()(ObjectPtr, _args);
        }

        /// <description>
        /// Set a level-of-detail value (0-255) for the choreographer.
        /// </description>
        public void SetLevelOfDetail(uint lod) {
             InternalUnsafeMethods.SetLevelOfDetail__Args _args = new InternalUnsafeMethods.SetLevelOfDetail__Args() {
                lod = lod,
             };
             InternalUnsafeMethods.SetLevelOfDetail()(ObjectPtr, _args);
        }

        /// <description>
        /// Set a ranking value (0-255) for the choreographer.
        /// </description>
        public void SetRanking(uint ranking) {
             InternalUnsafeMethods.SetRanking__Args _args = new InternalUnsafeMethods.SetRanking__Args() {
                ranking = ranking,
             };
             InternalUnsafeMethods.SetRanking()(ObjectPtr, _args);
        }

        /// <description>
        /// Get the type info object for the afxChoreographer class.
        /// </description>
        /// <returns>The type info object for afxChoreographer</returns>
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
        public SimObject Extra {
            get => GenericMarshal.StringTo<SimObject>(GetFieldValue("extra"));
            set => SetFieldValue("extra", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// ...
        /// </description>
        /// </value>
        public bool PostponeActivation {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("postponeActivation"));
            set => SetFieldValue("postponeActivation", GenericMarshal.ToString(value));
        }
    }
}