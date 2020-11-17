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
    /// <summary>A datablock that describes an Effect Wrapper.</summary>
    /// <description>
    /// Conceptually an effect wrapper encloses a building-block effect and acts as a handle for adding the effect to a choreographer. Effect wrapper fields primarily deal with effect timing, constraints, and conditional effect execution.
    /// </description>
    /// <see cref="afxEffectBaseData" />
    /// <see cref="afxEffectGroupData" />
    public unsafe class afxEffectWrapperData : afxEffectBaseData {
        public afxEffectWrapperData(bool pRegister = false) 
            : base(pRegister) {
        }
        
        public afxEffectWrapperData(string pName, bool pRegister) 
            : this(false) {
            Name = pName;
            if (pRegister) {
                RegisterObject();
            }
        }
        
        public afxEffectWrapperData(string pName) 
            : this(pName, false) {
        }
        
        public afxEffectWrapperData(string pName, string pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(Engine.Sim.FindObject<SimObject>(pParent));
        }
        
        public afxEffectWrapperData(string pName, SimObject pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(pParent);
        }
        
        public afxEffectWrapperData(SimObject pObj) 
            : base(pObj) {
        }
        
        public afxEffectWrapperData(IntPtr pObj) 
            : base(pObj) {
        }
        
		protected override void CreateObjectPtr()
		{
			ObjectPtr = InternalUnsafeMethods.Create()(new InternalUnsafeMethods.Create__Args());
		}

        #region UnsafeNativeMethods
        new internal struct InternalUnsafeMethods {
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
                                "fnafxEffectWrapperData_staticGetType"), typeof(_StaticGetType));
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
                                "fnafxEffectWrapperData_create"), typeof(_Create));
                }
                
                return _CreateFunc;
            }
        }
        #endregion

        /// <description>
        /// Get the type info object for the afxEffectWrapperData class.
        /// </description>
        /// <returns>The type info object for afxEffectWrapperData</returns>
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
        public SimDataBlock Effect {
            get => GenericMarshal.StringTo<SimDataBlock>(GetFieldValue("effect"));
            set => SetFieldValue("effect", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// ...
        /// </description>
        /// </value>
        public string EffectName {
            get => GenericMarshal.StringTo<string>(GetFieldValue("effectName"));
            set => SetFieldValue("effectName", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// ...
        /// </description>
        /// </value>
        public string Constraint {
            get => GenericMarshal.StringTo<string>(GetFieldValue("constraint"));
            set => SetFieldValue("constraint", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// ...
        /// </description>
        /// </value>
        public string PosConstraint {
            get => GenericMarshal.StringTo<string>(GetFieldValue("posConstraint"));
            set => SetFieldValue("posConstraint", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// ...
        /// </description>
        /// </value>
        public string PosConstraint2 {
            get => GenericMarshal.StringTo<string>(GetFieldValue("posConstraint2"));
            set => SetFieldValue("posConstraint2", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// ...
        /// </description>
        /// </value>
        public string OrientConstraint {
            get => GenericMarshal.StringTo<string>(GetFieldValue("orientConstraint"));
            set => SetFieldValue("orientConstraint", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// ...
        /// </description>
        /// </value>
        public string LifeConstraint {
            get => GenericMarshal.StringTo<string>(GetFieldValue("lifeConstraint"));
            set => SetFieldValue("lifeConstraint", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// ...
        /// </description>
        /// </value>
        public bool IsConstraintSrc {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("isConstraintSrc"));
            set => SetFieldValue("isConstraintSrc", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// ...
        /// </description>
        /// </value>
        public bool GhostIsConstraintSrc {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("ghostIsConstraintSrc"));
            set => SetFieldValue("ghostIsConstraintSrc", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// ...
        /// </description>
        /// </value>
        public float Delay {
            get => GenericMarshal.StringTo<float>(GetFieldValue("delay"));
            set => SetFieldValue("delay", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// ...
        /// </description>
        /// </value>
        public float Lifetime {
            get => GenericMarshal.StringTo<float>(GetFieldValue("lifetime"));
            set => SetFieldValue("lifetime", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// ...
        /// </description>
        /// </value>
        public float FadeInTime {
            get => GenericMarshal.StringTo<float>(GetFieldValue("fadeInTime"));
            set => SetFieldValue("fadeInTime", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// ...
        /// </description>
        /// </value>
        public float ResidueLifetime {
            get => GenericMarshal.StringTo<float>(GetFieldValue("residueLifetime"));
            set => SetFieldValue("residueLifetime", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// ...
        /// </description>
        /// </value>
        public Point2F FadeInEase {
            get => GenericMarshal.StringTo<Point2F>(GetFieldValue("fadeInEase"));
            set => SetFieldValue("fadeInEase", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// ...
        /// </description>
        /// </value>
        public Point2F FadeOutEase {
            get => GenericMarshal.StringTo<Point2F>(GetFieldValue("fadeOutEase"));
            set => SetFieldValue("fadeOutEase", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// ...
        /// </description>
        /// </value>
        public float LifetimeBias {
            get => GenericMarshal.StringTo<float>(GetFieldValue("lifetimeBias"));
            set => SetFieldValue("lifetimeBias", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// ...
        /// </description>
        /// </value>
        public float FadeOutTime {
            get => GenericMarshal.StringTo<float>(GetFieldValue("fadeOutTime"));
            set => SetFieldValue("fadeOutTime", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// ...
        /// </description>
        /// </value>
        public float RateFactor {
            get => GenericMarshal.StringTo<float>(GetFieldValue("rateFactor"));
            set => SetFieldValue("rateFactor", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// ...
        /// </description>
        /// </value>
        public float ScaleFactor {
            get => GenericMarshal.StringTo<float>(GetFieldValue("scaleFactor"));
            set => SetFieldValue("scaleFactor", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// ...
        /// </description>
        /// </value>
        public bool IsLooping {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("isLooping"));
            set => SetFieldValue("isLooping", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// ...
        /// </description>
        /// </value>
        public int LoopCount {
            get => GenericMarshal.StringTo<int>(GetFieldValue("LoopCount"));
            set => SetFieldValue("LoopCount", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// ...
        /// </description>
        /// </value>
        public float LoopGapTime {
            get => GenericMarshal.StringTo<float>(GetFieldValue("loopGapTime"));
            set => SetFieldValue("loopGapTime", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// ...
        /// </description>
        /// </value>
        public bool IgnoreTimeFactor {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("ignoreTimeFactor"));
            set => SetFieldValue("ignoreTimeFactor", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// ...
        /// </description>
        /// </value>
        public bool PropagateTimeFactor {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("propagateTimeFactor"));
            set => SetFieldValue("propagateTimeFactor", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// ...
        /// </description>
        /// </value>
        public bool EffectEnabled {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("effectEnabled"));
            set => SetFieldValue("effectEnabled", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// ...
        /// </description>
        /// </value>
        public ByteRange RankingRange {
            get => GenericMarshal.StringTo<ByteRange>(GetFieldValue("rankingRange"));
            set => SetFieldValue("rankingRange", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// ...
        /// </description>
        /// </value>
        public ByteRange LevelOfDetailRange {
            get => GenericMarshal.StringTo<ByteRange>(GetFieldValue("levelOfDetailRange"));
            set => SetFieldValue("levelOfDetailRange", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// ...
        /// </description>
        /// </value>
        public int LifeConditions {
            get => GenericMarshal.StringTo<int>(GetFieldValue("lifeConditions"));
            set => SetFieldValue("lifeConditions", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// ...
        /// </description>
        /// </value>
        public DynamicFieldVector<int> ExecConditions {
            get => new DynamicFieldVector<int>(
                    this, 
                    "execConditions", 
                    4, 
                    val => GenericMarshal.StringTo<int>(val),
                    obj => GenericMarshal.ToString(obj)
                );
        }


        /// <value>
        /// <description>
        /// ...
        /// </description>
        /// </value>
        public DynamicFieldVector<int> ExecOffConditions {
            get => new DynamicFieldVector<int>(
                    this, 
                    "execOffConditions", 
                    4, 
                    val => GenericMarshal.StringTo<int>(val),
                    obj => GenericMarshal.ToString(obj)
                );
        }


        /// <value>
        /// <description>
        /// ...
        /// </description>
        /// </value>
        public DynamicFieldVector<afxXM_BaseData> XfmModifiers {
            get => new DynamicFieldVector<afxXM_BaseData>(
                    this, 
                    "xfmModifiers", 
                    32, 
                    val => GenericMarshal.StringTo<afxXM_BaseData>(val),
                    obj => GenericMarshal.ToString(obj)
                );
        }


        /// <value>
        /// <description>
        /// ...
        /// </description>
        /// </value>
        public Box3F ForcedBBox {
            get => GenericMarshal.StringTo<Box3F>(GetFieldValue("forcedBBox"));
            set => SetFieldValue("forcedBBox", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// ...
        /// </description>
        /// </value>
        public bool UpdateForcedBBox {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("updateForcedBBox"));
            set => SetFieldValue("updateForcedBBox", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// ...
        /// </description>
        /// </value>
        public sbyte SortPriority {
            get => GenericMarshal.StringTo<sbyte>(GetFieldValue("sortPriority"));
            set => SetFieldValue("sortPriority", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// ...
        /// </description>
        /// </value>
        public Point3F Direction {
            get => GenericMarshal.StringTo<Point3F>(GetFieldValue("direction"));
            set => SetFieldValue("direction", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// ...
        /// </description>
        /// </value>
        public float Speed {
            get => GenericMarshal.StringTo<float>(GetFieldValue("speed"));
            set => SetFieldValue("speed", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// ...
        /// </description>
        /// </value>
        public float Mass {
            get => GenericMarshal.StringTo<float>(GetFieldValue("mass"));
            set => SetFieldValue("mass", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// ...
        /// </description>
        /// </value>
        public bool BorrowAltitudes {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("borrowAltitudes"));
            set => SetFieldValue("borrowAltitudes", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// ...
        /// </description>
        /// </value>
        public string VisibilityKeys {
            get => GenericMarshal.StringTo<string>(GetFieldValue("visibilityKeys"));
            set => SetFieldValue("visibilityKeys", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// ...
        /// </description>
        /// </value>
        public int GroupIndex {
            get => GenericMarshal.StringTo<int>(GetFieldValue("groupIndex"));
            set => SetFieldValue("groupIndex", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// ...
        /// </description>
        /// </value>
        public int InheritGroupTiming {
            get => GenericMarshal.StringTo<int>(GetFieldValue("inheritGroupTiming"));
            set => SetFieldValue("inheritGroupTiming", GenericMarshal.ToString(value));
        }
    }
}