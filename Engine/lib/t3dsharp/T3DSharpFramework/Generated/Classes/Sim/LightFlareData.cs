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
    /// <summary>Defines a light flare effect usable by scene lights.</summary>
    /// <description>
    /// %LightFlareData is a datablock which defines a type of flare effect. This may then be referenced by other classes which support the rendering of a flare: Sun, ScatterSky, LightBase.
    /// 
    /// A flare contains one or more elements defined in the element* named fields of %LightFlareData, with a maximum of ten elements. Each element is rendered as a 2D sprite in screenspace.
    /// </description>
    /// <code>
    /// // example from Full Template, core/art/datablocks/lights.cs
    /// datablock LightFlareData( LightFlareExample0 )
    /// {
    ///    overallScale = 2.0;
    ///    flareEnabled = true;
    ///    renderReflectPass = true;
    ///    flareTexture = "./../special/lensFlareSheet1";
    ///    occlusionRadius = 0.25;
    ///    
    ///    elementRect[0] = "0 512 512 512";
    ///    elementDist[0] = 0.0;
    ///    elementScale[0] = 0.5;
    ///    elementTint[0] = "1.0 1.0 1.0";
    ///    elementRotate[0] = false;
    ///    elementUseLightColor[0] = false;
    ///    
    ///    elementRect[1] = "512 0 512 512";
    ///    elementDist[1] = 0.0;
    ///    elementScale[1] = 2.0;
    ///    elementTint[1] = "0.5 0.5 0.5";
    ///    elementRotate[1] = false;
    ///    elementUseLightColor[1] = false;
    /// };
    /// </code>
    public unsafe class LightFlareData : SimDataBlock {
        public LightFlareData(bool pRegister = false) 
            : base(pRegister) {
        }
        
        public LightFlareData(string pName, bool pRegister) 
            : this(false) {
            Name = pName;
            if (pRegister) {
                RegisterObject();
            }
        }
        
        public LightFlareData(string pName) 
            : this(pName, false) {
        }
        
        public LightFlareData(string pName, string pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(Engine.Sim.FindObject<SimObject>(pParent));
        }
        
        public LightFlareData(string pName, SimObject pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(pParent);
        }
        
        public LightFlareData(SimObject pObj) 
            : base(pObj) {
        }
        
        public LightFlareData(IntPtr pObj) 
            : base(pObj) {
        }
        
		protected override void CreateObjectPtr()
		{
			ObjectPtr = InternalUnsafeMethods.Create()(new InternalUnsafeMethods.Create__Args());
		}

        #region UnsafeNativeMethods
        new internal struct InternalUnsafeMethods {
            [StructLayout(LayoutKind.Sequential)]
            internal struct Apply__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _Apply(IntPtr _this, Apply__Args args);
            private static _Apply _ApplyFunc;
            internal static _Apply Apply() {
                if (_ApplyFunc == null) {
                    _ApplyFunc =
                        (_Apply)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnLightFlareData_apply"), typeof(_Apply));
                }
                
                return _ApplyFunc;
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
                                "fnLightFlareData_staticGetType"), typeof(_StaticGetType));
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
                                "fnLightFlareData_create"), typeof(_Create));
                }
                
                return _CreateFunc;
            }
        }
        #endregion

        /// <description>
        /// Intended as a helper to developers and editor scripts.
        /// Force trigger an inspectPostApply
        /// </description>
        public void Apply() {
             InternalUnsafeMethods.Apply__Args _args = new InternalUnsafeMethods.Apply__Args() {
             };
             InternalUnsafeMethods.Apply()(ObjectPtr, _args);
        }

        /// <description>
        /// Get the type info object for the LightFlareData class.
        /// </description>
        /// <returns>The type info object for LightFlareData</returns>
        public static EngineTypeInfo StaticGetType() {
             InternalUnsafeMethods.StaticGetType__Args _args = new InternalUnsafeMethods.StaticGetType__Args() {
             };
             IntPtr _engineResult = InternalUnsafeMethods.StaticGetType()(_args);
             return new EngineTypeInfo(_engineResult);
        }


        /// <value>
        /// <description>
        /// Size scale applied to all elements of the flare.
        /// </description>
        /// </value>
        public float OverallScale {
            get => GenericMarshal.StringTo<float>(GetFieldValue("overallScale"));
            set => SetFieldValue("overallScale", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// If positive an occlusion query is used to test flare visibility, else it uses simple raycasts.
        /// </description>
        /// </value>
        public float OcclusionRadius {
            get => GenericMarshal.StringTo<float>(GetFieldValue("occlusionRadius"));
            set => SetFieldValue("occlusionRadius", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// If false the flare does not render in reflections, else only non-zero distance elements are rendered.
        /// </description>
        /// </value>
        public bool RenderReflectPass {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("renderReflectPass"));
            set => SetFieldValue("renderReflectPass", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Allows the user to disable this flare globally for any lights referencing it.
        /// </description>
        /// </value>
        public bool FlareEnabled {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("flareEnabled"));
            set => SetFieldValue("flareEnabled", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// The texture / sprite sheet for this flare.
        /// </description>
        /// </value>
        public string FlareTexture {
            get => GenericMarshal.StringTo<string>(GetFieldValue("flareTexture"));
            set => SetFieldValue("flareTexture", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// A rectangle specified in pixels of the flareTexture image.
        /// </description>
        /// </value>
        public DynamicFieldVector<RectF> ElementRect {
            get => new DynamicFieldVector<RectF>(
                    this, 
                    "elementRect", 
                    20, 
                    val => GenericMarshal.StringTo<RectF>(val),
                    obj => GenericMarshal.ToString(obj)
                );
        }


        /// <value>
        /// <description>
        /// Where this element appears along the flare beam.
        /// </description>
        /// </value>
        public DynamicFieldVector<float> ElementDist {
            get => new DynamicFieldVector<float>(
                    this, 
                    "elementDist", 
                    20, 
                    val => GenericMarshal.StringTo<float>(val),
                    obj => GenericMarshal.ToString(obj)
                );
        }


        /// <value>
        /// <description>
        /// Size scale applied to this element.
        /// </description>
        /// </value>
        public DynamicFieldVector<float> ElementScale {
            get => new DynamicFieldVector<float>(
                    this, 
                    "elementScale", 
                    20, 
                    val => GenericMarshal.StringTo<float>(val),
                    obj => GenericMarshal.ToString(obj)
                );
        }


        /// <value>
        /// <description>
        /// Used to modulate this element's color if elementUseLightColor is false.
        /// </description>
        /// <see cref="elementUseLightColor" />
        /// </value>
        public DynamicFieldVector<LinearColorF> ElementTint {
            get => new DynamicFieldVector<LinearColorF>(
                    this, 
                    "elementTint", 
                    20, 
                    val => GenericMarshal.StringTo<LinearColorF>(val),
                    obj => GenericMarshal.ToString(obj)
                );
        }


        /// <value>
        /// <description>
        /// Defines if this element orients to point along the flare beam or if it is always upright.
        /// </description>
        /// </value>
        public DynamicFieldVector<bool> ElementRotate {
            get => new DynamicFieldVector<bool>(
                    this, 
                    "elementRotate", 
                    20, 
                    val => GenericMarshal.StringTo<bool>(val),
                    obj => GenericMarshal.ToString(obj)
                );
        }


        /// <value>
        /// <description>
        /// If true this element's color is modulated by the light color. If false, elementTint will be used.
        /// </description>
        /// <see cref="elementTint" />
        /// </value>
        public DynamicFieldVector<bool> ElementUseLightColor {
            get => new DynamicFieldVector<bool>(
                    this, 
                    "elementUseLightColor", 
                    20, 
                    val => GenericMarshal.StringTo<bool>(val),
                    obj => GenericMarshal.ToString(obj)
                );
        }
    }
}