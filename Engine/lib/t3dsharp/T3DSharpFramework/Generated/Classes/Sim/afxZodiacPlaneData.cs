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
    /// <summary>A datablock that specifies a Zodiac Plane effect.</summary>
    /// <description>
    /// afxZodiacData describes a zodiac-like effect called a zodiac plane. It reproduces most of the behavior of normal zodiacs but unlike zodiac decals, it is represented as a flat plane of geometry that can be more flexibly positioned and oriented.
    /// </description>
    public unsafe class afxZodiacPlaneData : GameBaseData {
        public afxZodiacPlaneData(bool pRegister = false) 
            : base(pRegister) {
        }
        
        public afxZodiacPlaneData(string pName, bool pRegister) 
            : this(false) {
            Name = pName;
            if (pRegister) {
                RegisterObject();
            }
        }
        
        public afxZodiacPlaneData(string pName) 
            : this(pName, false) {
        }
        
        public afxZodiacPlaneData(string pName, string pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(Engine.Sim.FindObject<SimObject>(pParent));
        }
        
        public afxZodiacPlaneData(string pName, SimObject pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(pParent);
        }
        
        public afxZodiacPlaneData(SimObject pObj) 
            : base(pObj) {
        }
        
        public afxZodiacPlaneData(IntPtr pObj) 
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
                                "fnafxZodiacPlaneData_staticGetType"), typeof(_StaticGetType));
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
                                "fnafxZodiacPlaneData_create"), typeof(_Create));
                }
                
                return _CreateFunc;
            }
        }
        #endregion

        /// <description>
        /// Get the type info object for the afxZodiacPlaneData class.
        /// </description>
        /// <returns>The type info object for afxZodiacPlaneData</returns>
        public static EngineTypeInfo StaticGetType() {
             InternalUnsafeMethods.StaticGetType__Args _args = new InternalUnsafeMethods.StaticGetType__Args() {
             };
             IntPtr _engineResult = InternalUnsafeMethods.StaticGetType()(_args);
             return new EngineTypeInfo(_engineResult);
        }


        /// <value>
        /// <description>
        /// An image to use as the zodiac's texture.
        /// </description>
        /// </value>
        public string Texture {
            get => GenericMarshal.StringTo<string>(GetFieldValue("texture"));
            set => SetFieldValue("texture", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// The zodiac's radius in scene units.
        /// </description>
        /// </value>
        public float Radius {
            get => GenericMarshal.StringTo<float>(GetFieldValue("radius"));
            set => SetFieldValue("radius", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// The starting angle in degrees of the zodiac's rotation.
        /// </description>
        /// </value>
        public float StartAngle {
            get => GenericMarshal.StringTo<float>(GetFieldValue("startAngle"));
            set => SetFieldValue("startAngle", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// The rate of rotation in degrees-per-second. Zodiacs with a positive rotationRate rotate clockwise, while those with negative values turn counter-clockwise.
        /// </description>
        /// </value>
        public float RotationRate {
            get => GenericMarshal.StringTo<float>(GetFieldValue("rotationRate"));
            set => SetFieldValue("rotationRate", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// A duration of time in seconds over which the zodiac grows from a zero size to its full size as specified by the radius.
        /// </description>
        /// </value>
        public float GrowInTime {
            get => GenericMarshal.StringTo<float>(GetFieldValue("growInTime"));
            set => SetFieldValue("growInTime", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// A duration of time in seconds over which the zodiac shrinks from full size to invisible.
        /// </description>
        /// </value>
        public float ShrinkOutTime {
            get => GenericMarshal.StringTo<float>(GetFieldValue("shrinkOutTime"));
            set => SetFieldValue("shrinkOutTime", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// A rate in meters-per-second at which the zodiac grows in size. A negative value will shrink the zodiac.
        /// </description>
        /// </value>
        public float GrowthRate {
            get => GenericMarshal.StringTo<float>(GetFieldValue("growthRate"));
            set => SetFieldValue("growthRate", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// A color value for the zodiac.
        /// </description>
        /// </value>
        public LinearColorF Color {
            get => GenericMarshal.StringTo<LinearColorF>(GetFieldValue("color"));
            set => SetFieldValue("color", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// A blending style for the zodiac. Possible values: normal, additive, or subtractive.
        /// </description>
        /// </value>
        public afxZodiacPlane_BlendType Blend {
            get => GenericMarshal.StringTo<afxZodiacPlane_BlendType>(GetFieldValue("blend"));
            set => SetFieldValue("blend", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Specifies if the zodiac's rotation should be defined by its constrained transformation.
        /// </description>
        /// </value>
        public bool TrackOrientConstraint {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("trackOrientConstraint"));
            set => SetFieldValue("trackOrientConstraint", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Controls whether the zodiac-plane's polygons are rendered when viewed from either side. If set to false, the zodiac-plane will only be seen when viewed from the direction it is facing (according to faceDir).
        /// </description>
        /// </value>
        public bool DoubleSided {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("doubleSided"));
            set => SetFieldValue("doubleSided", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Specifies which direction the zodiac-plane's polygons face. Possible values: up, down, front, back, right, or left.
        /// </description>
        /// </value>
        public afxZodiacPlane_FacingType FaceDir {
            get => GenericMarshal.StringTo<afxZodiacPlane_FacingType>(GetFieldValue("faceDir"));
            set => SetFieldValue("faceDir", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Normal zodiacs have only one degree of freedom, a rotation around the z-axis. Depending on the setting for trackOrientConstraint, this means that the effect's orientation is either ignored or is limited to influencing the zodiac's angle of rotation. By default, zodiac-plane reproduces this limited behavior in order to match normal zodiacs. When useFullTransform is set to true, the zodiac can be arbitrarily oriented.
        /// </description>
        /// </value>
        public bool UseFullTransform {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("useFullTransform"));
            set => SetFieldValue("useFullTransform", GenericMarshal.ToString(value));
        }
    }
}