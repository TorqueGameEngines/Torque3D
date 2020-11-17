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
    /// <summary>A layer of clouds which change shape over time and are affected by scene lighting.</summary>
    /// <description>
    /// %CloudLayer always renders overhead, following the camera. It is intended as part of the background of your level, rendering in front of Sky/Sun type objects and behind everything else.
    /// 
    /// The illusion of clouds forming and changing over time is controlled by the normal/opacity texture and the three sets of texture animation parameters. The texture is sampled three times.  The first sample defines overall cloud density, where clouds are likely to form and their general size and shape. The second two samples control how it changes over time; they are combined and used as modifiers to the first sample.
    /// 
    /// %CloudLayer is affected by scene lighting and is designed to be used in scenes with dynamic lighting or time of day changes.
    /// </description>
    public unsafe class CloudLayer : SceneObject {
        public CloudLayer(bool pRegister = false) 
            : base(pRegister) {
        }
        
        public CloudLayer(string pName, bool pRegister) 
            : this(false) {
            Name = pName;
            if (pRegister) {
                RegisterObject();
            }
        }
        
        public CloudLayer(string pName) 
            : this(pName, false) {
        }
        
        public CloudLayer(string pName, string pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(Engine.Sim.FindObject<SimObject>(pParent));
        }
        
        public CloudLayer(string pName, SimObject pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(pParent);
        }
        
        public CloudLayer(SimObject pObj) 
            : base(pObj) {
        }
        
        public CloudLayer(IntPtr pObj) 
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
                                "fnCloudLayer_staticGetType"), typeof(_StaticGetType));
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
                                "fnCloudLayer_create"), typeof(_Create));
                }
                
                return _CreateFunc;
            }
        }
        #endregion

        /// <description>
        /// Get the type info object for the CloudLayer class.
        /// </description>
        /// <returns>The type info object for CloudLayer</returns>
        public static EngineTypeInfo StaticGetType() {
             InternalUnsafeMethods.StaticGetType__Args _args = new InternalUnsafeMethods.StaticGetType__Args() {
             };
             IntPtr _engineResult = InternalUnsafeMethods.StaticGetType()(_args);
             return new EngineTypeInfo(_engineResult);
        }


        /// <value>
        /// <description>
        /// An RGBA texture which should contain normals and opacity (density).
        /// </description>
        /// </value>
        public string Texture {
            get => GenericMarshal.StringTo<string>(GetFieldValue("texture"));
            set => SetFieldValue("texture", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Controls the texture repeat of this slot.
        /// </description>
        /// </value>
        public DynamicFieldVector<float> TexScale {
            get => new DynamicFieldVector<float>(
                    this, 
                    "texScale", 
                    3, 
                    val => GenericMarshal.StringTo<float>(val),
                    obj => GenericMarshal.ToString(obj)
                );
        }


        /// <value>
        /// <description>
        /// Controls the direction this slot scrolls.
        /// </description>
        /// </value>
        public DynamicFieldVector<Point2F> TexDirection {
            get => new DynamicFieldVector<Point2F>(
                    this, 
                    "texDirection", 
                    3, 
                    val => GenericMarshal.StringTo<Point2F>(val),
                    obj => GenericMarshal.ToString(obj)
                );
        }


        /// <value>
        /// <description>
        /// Controls the speed this slot scrolls.
        /// </description>
        /// </value>
        public DynamicFieldVector<float> TexSpeed {
            get => new DynamicFieldVector<float>(
                    this, 
                    "texSpeed", 
                    3, 
                    val => GenericMarshal.StringTo<float>(val),
                    obj => GenericMarshal.ToString(obj)
                );
        }


        /// <value>
        /// <description>
        /// Base cloud color before lighting.
        /// </description>
        /// </value>
        public LinearColorF BaseColor {
            get => GenericMarshal.StringTo<LinearColorF>(GetFieldValue("baseColor"));
            set => SetFieldValue("baseColor", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Brightness scale so CloudLayer can be overblown if desired.
        /// </description>
        /// </value>
        public float Exposure {
            get => GenericMarshal.StringTo<float>(GetFieldValue("exposure"));
            set => SetFieldValue("exposure", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Fraction of sky covered by clouds 0-1.
        /// </description>
        /// </value>
        public float Coverage {
            get => GenericMarshal.StringTo<float>(GetFieldValue("coverage"));
            set => SetFieldValue("coverage", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Overall scalar to texture scroll speed.
        /// </description>
        /// </value>
        public float WindSpeed {
            get => GenericMarshal.StringTo<float>(GetFieldValue("windSpeed"));
            set => SetFieldValue("windSpeed", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Abstract number which controls the curvature and height of the dome mesh.
        /// </description>
        /// </value>
        public float Height {
            get => GenericMarshal.StringTo<float>(GetFieldValue("height"));
            set => SetFieldValue("height", GenericMarshal.ToString(value));
        }
    }
}