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
    /// <summary>Represents a type of ForestItem and parameters for how it is placed when painting with a ForestBrush that contains it.</summary>
    /// <description>
    /// 
    /// </description>
    public unsafe class ForestBrushElement : SimObject {
        public ForestBrushElement(bool pRegister = false) 
            : base(pRegister) {
        }
        
        public ForestBrushElement(string pName, bool pRegister) 
            : this(false) {
            Name = pName;
            if (pRegister) {
                RegisterObject();
            }
        }
        
        public ForestBrushElement(string pName) 
            : this(pName, false) {
        }
        
        public ForestBrushElement(string pName, string pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(Engine.Sim.FindObject<SimObject>(pParent));
        }
        
        public ForestBrushElement(string pName, SimObject pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(pParent);
        }
        
        public ForestBrushElement(SimObject pObj) 
            : base(pObj) {
        }
        
        public ForestBrushElement(IntPtr pObj) 
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
                                "fnForestBrushElement_staticGetType"), typeof(_StaticGetType));
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
                                "fnForestBrushElement_create"), typeof(_Create));
                }
                
                return _CreateFunc;
            }
        }
        #endregion

        /// <description>
        /// Get the type info object for the ForestBrushElement class.
        /// </description>
        /// <returns>The type info object for ForestBrushElement</returns>
        public static EngineTypeInfo StaticGetType() {
             InternalUnsafeMethods.StaticGetType__Args _args = new InternalUnsafeMethods.StaticGetType__Args() {
             };
             IntPtr _engineResult = InternalUnsafeMethods.StaticGetType()(_args);
             return new EngineTypeInfo(_engineResult);
        }


        /// <value>
        /// <description>
        /// The type of ForestItem this element holds placement parameters for.
        /// </description>
        /// </value>
        public ForestItemData ForestItemData {
            get => GenericMarshal.StringTo<ForestItemData>(GetFieldValue("ForestItemData"));
            set => SetFieldValue("ForestItemData", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// The probability that this element will be created during an editor brush stroke is the sum of all element probabilities in the brush divided by the probability of this element.
        /// </description>
        /// </value>
        public float Probability {
            get => GenericMarshal.StringTo<float>(GetFieldValue("probability"));
            set => SetFieldValue("probability", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// The max rotation in degrees that items will be placed.
        /// </description>
        /// </value>
        public float RotationRange {
            get => GenericMarshal.StringTo<float>(GetFieldValue("rotationRange"));
            set => SetFieldValue("rotationRange", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// The minimum random size for each item.
        /// </description>
        /// </value>
        public float ScaleMin {
            get => GenericMarshal.StringTo<float>(GetFieldValue("scaleMin"));
            set => SetFieldValue("scaleMin", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// The maximum random size of each item.
        /// </description>
        /// </value>
        public float ScaleMax {
            get => GenericMarshal.StringTo<float>(GetFieldValue("scaleMax"));
            set => SetFieldValue("scaleMax", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// An exponent used to bias between the minimum and maximum random sizes.
        /// </description>
        /// </value>
        public float ScaleExponent {
            get => GenericMarshal.StringTo<float>(GetFieldValue("scaleExponent"));
            set => SetFieldValue("scaleExponent", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Min variation in the sink radius.
        /// </description>
        /// </value>
        public float SinkMin {
            get => GenericMarshal.StringTo<float>(GetFieldValue("sinkMin"));
            set => SetFieldValue("sinkMin", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Max variation in the sink radius.
        /// </description>
        /// </value>
        public float SinkMax {
            get => GenericMarshal.StringTo<float>(GetFieldValue("sinkMax"));
            set => SetFieldValue("sinkMax", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// This is the radius used to calculate how much to sink the trunk at its base and is used to sink the tree into the ground when its on a slope.
        /// </description>
        /// </value>
        public float SinkRadius {
            get => GenericMarshal.StringTo<float>(GetFieldValue("sinkRadius"));
            set => SetFieldValue("sinkRadius", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// The min surface slope in degrees this item will be placed on.
        /// </description>
        /// </value>
        public float SlopeMin {
            get => GenericMarshal.StringTo<float>(GetFieldValue("slopeMin"));
            set => SetFieldValue("slopeMin", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// The max surface slope in degrees this item will be placed on.
        /// </description>
        /// </value>
        public float SlopeMax {
            get => GenericMarshal.StringTo<float>(GetFieldValue("slopeMax"));
            set => SetFieldValue("slopeMax", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// The min world space elevation this item will be placed.
        /// </description>
        /// </value>
        public float ElevationMin {
            get => GenericMarshal.StringTo<float>(GetFieldValue("elevationMin"));
            set => SetFieldValue("elevationMin", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// The max world space elevation this item will be placed.
        /// </description>
        /// </value>
        public float ElevationMax {
            get => GenericMarshal.StringTo<float>(GetFieldValue("elevationMax"));
            set => SetFieldValue("elevationMax", GenericMarshal.ToString(value));
        }
    }
}