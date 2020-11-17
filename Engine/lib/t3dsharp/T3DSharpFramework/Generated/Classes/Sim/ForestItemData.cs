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
    /// <summary>Base class for defining a type of ForestItem. It does not implement loading or rendering of the shapeFile.</summary>
    /// <description>
    /// 
    /// </description>
    public unsafe class ForestItemData : SimDataBlock {
        public ForestItemData(bool pRegister = false) 
            : base(pRegister) {
        }
        
        public ForestItemData(string pName, bool pRegister) 
            : this(false) {
            Name = pName;
            if (pRegister) {
                RegisterObject();
            }
        }
        
        public ForestItemData(string pName) 
            : this(pName, false) {
        }
        
        public ForestItemData(string pName, string pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(Engine.Sim.FindObject<SimObject>(pParent));
        }
        
        public ForestItemData(string pName, SimObject pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(pParent);
        }
        
        public ForestItemData(SimObject pObj) 
            : base(pObj) {
        }
        
        public ForestItemData(IntPtr pObj) 
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
                                "fnForestItemData_staticGetType"), typeof(_StaticGetType));
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
                                "fnForestItemData_create"), typeof(_Create));
                }
                
                return _CreateFunc;
            }
        }
        #endregion

        /// <description>
        /// Get the type info object for the ForestItemData class.
        /// </description>
        /// <returns>The type info object for ForestItemData</returns>
        public static EngineTypeInfo StaticGetType() {
             InternalUnsafeMethods.StaticGetType__Args _args = new InternalUnsafeMethods.StaticGetType__Args() {
             };
             IntPtr _engineResult = InternalUnsafeMethods.StaticGetType()(_args);
             return new EngineTypeInfo(_engineResult);
        }


        /// <value>
        /// <description>
        /// Shape file for this item type
        /// </description>
        /// </value>
        public string ShapeFile {
            get => GenericMarshal.StringTo<string>(GetFieldValue("shapeFile"));
            set => SetFieldValue("shapeFile", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Can other objects or spacial queries hit items of this type.
        /// </description>
        /// </value>
        public bool Collidable {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("collidable"));
            set => SetFieldValue("collidable", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Radius used during placement to ensure items are not crowded.
        /// </description>
        /// </value>
        public float Radius {
            get => GenericMarshal.StringTo<float>(GetFieldValue("radius"));
            set => SetFieldValue("radius", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Mass used in calculating spring forces on the trunk. Generally how springy a plant is.
        /// </description>
        /// </value>
        public float Mass {
            get => GenericMarshal.StringTo<float>(GetFieldValue("mass"));
            set => SetFieldValue("mass", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Rigidity used in calculating spring forces on the trunk. How much the plant resists the wind force
        /// </description>
        /// </value>
        public float Rigidity {
            get => GenericMarshal.StringTo<float>(GetFieldValue("rigidity"));
            set => SetFieldValue("rigidity", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Coefficient used in calculating spring forces on the trunk. How much the plant resists bending.
        /// </description>
        /// </value>
        public float TightnessCoefficient {
            get => GenericMarshal.StringTo<float>(GetFieldValue("tightnessCoefficient"));
            set => SetFieldValue("tightnessCoefficient", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Coefficient used in calculating spring forces on the trunk. Causes oscillation and forces to decay faster over time.
        /// </description>
        /// </value>
        public float DampingCoefficient {
            get => GenericMarshal.StringTo<float>(GetFieldValue("dampingCoefficient"));
            set => SetFieldValue("dampingCoefficient", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Overall scale to the effect of wind.
        /// </description>
        /// </value>
        public float WindScale {
            get => GenericMarshal.StringTo<float>(GetFieldValue("windScale"));
            set => SetFieldValue("windScale", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Overall bend amount of the tree trunk by wind and impacts.
        /// </description>
        /// </value>
        public float TrunkBendScale {
            get => GenericMarshal.StringTo<float>(GetFieldValue("trunkBendScale"));
            set => SetFieldValue("trunkBendScale", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Amplitude of the effect on larger branches.
        /// </description>
        /// </value>
        public float BranchAmp {
            get => GenericMarshal.StringTo<float>(GetFieldValue("branchAmp"));
            set => SetFieldValue("branchAmp", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Amplitude of the winds effect on leafs/fronds.
        /// </description>
        /// </value>
        public float DetailAmp {
            get => GenericMarshal.StringTo<float>(GetFieldValue("detailAmp"));
            set => SetFieldValue("detailAmp", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Frequency (speed) of the effect on leafs/fronds.
        /// </description>
        /// </value>
        public float DetailFreq {
            get => GenericMarshal.StringTo<float>(GetFieldValue("detailFreq"));
            set => SetFieldValue("detailFreq", GenericMarshal.ToString(value));
        }
    }
}