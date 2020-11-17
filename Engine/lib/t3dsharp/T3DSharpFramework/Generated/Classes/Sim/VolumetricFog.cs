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
    /// <summary>Volumetric Fog Object class. Main class defining the Volumetric</summary>
    /// <description>
    /// Fog objects in the scene. Used in conjunction with the VolumetricFogRTManager
    /// class which is responsible for the required rendertargets.
    /// 
    /// Methods (exposed to script):
    ///  setFogColorF(color) Changes the overall fog color (color.rgba range 0.0 - 1.0).
    /// ; setFogColor(color) Changes the overall fog color color.rgba range 0 - 255).
    /// ; setFogDensity(density) Changes the overall fog density.
    ///  setFogModulation(strength, speed1, speed2) changes the strength
    ///  and the speeds of the 2 animation layers.
    /// 
    /// Callbacks:
    /// onEnterFog triggered whenever the controlobject (Player or Camera) enters the Fog.
    ///  (current Fog object and the controlobject are exposed to script.
    /// onLeaveFog triggered whenever the controlobject (Player or Camera) left the Fog.
    ///  (current Fog object and the controlobject are exposed to script.
    /// </description>
    /// <code>
    /// new VolumetricFog()
    ///  {
    ///  shapeName = "art/environment/FogRCube.dts";
    ///  fogColor = "200 200 200 128";
    ///  fogDensity = "0.2";
    ///  ignoreWater = "0";
    ///  MinSize = "250";
    ///  FadeSize = "750";
    ///  texture = "art/environment/FogMod_heavy.dds";
    ///  tiles = "1.5";
    ///  modStrength = "0.2";
    ///  PrimSpeed = "-0.01 0.04";
    ///  SecSpeed = "0.02 -0.02";
    ///  position = "748.644 656.371 65.3506"; 
    ///  rotation = "0 0 1 20.354";
    ///  scale = "40 30 6";
    ///  };
    /// </code>
    public unsafe class VolumetricFog : SceneObject {
        public VolumetricFog(bool pRegister = false) 
            : base(pRegister) {
        }
        
        public VolumetricFog(string pName, bool pRegister) 
            : this(false) {
            Name = pName;
            if (pRegister) {
                RegisterObject();
            }
        }
        
        public VolumetricFog(string pName) 
            : this(pName, false) {
        }
        
        public VolumetricFog(string pName, string pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(Engine.Sim.FindObject<SimObject>(pParent));
        }
        
        public VolumetricFog(string pName, SimObject pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(pParent);
        }
        
        public VolumetricFog(SimObject pObj) 
            : base(pObj) {
        }
        
        public VolumetricFog(IntPtr pObj) 
            : base(pObj) {
        }
        
		protected override void CreateObjectPtr()
		{
			ObjectPtr = InternalUnsafeMethods.Create()(new InternalUnsafeMethods.Create__Args());
		}

        #region UnsafeNativeMethods
        new internal struct InternalUnsafeMethods {
            [StructLayout(LayoutKind.Sequential)]
            internal struct IsInsideFog__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            [return: MarshalAs(UnmanagedType.I1)]
            internal delegate bool _IsInsideFog(IntPtr _this, IsInsideFog__Args args);
            private static _IsInsideFog _IsInsideFogFunc;
            internal static _IsInsideFog IsInsideFog() {
                if (_IsInsideFogFunc == null) {
                    _IsInsideFogFunc =
                        (_IsInsideFog)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnVolumetricFog_isInsideFog"), typeof(_IsInsideFog));
                }
                
                return _IsInsideFogFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct SetFogLightray__Args
            {
                [MarshalAs(UnmanagedType.I1)]
                internal bool on_off;
                internal float strength;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _SetFogLightray(IntPtr _this, SetFogLightray__Args args);
            private static _SetFogLightray _SetFogLightrayFunc;
            internal static _SetFogLightray SetFogLightray() {
                if (_SetFogLightrayFunc == null) {
                    _SetFogLightrayFunc =
                        (_SetFogLightray)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnVolumetricFog_SetFogLightray"), typeof(_SetFogLightray));
                }
                
                return _SetFogLightrayFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct SetFogGlow__Args
            {
                [MarshalAs(UnmanagedType.I1)]
                internal bool on_off;
                internal float strength;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _SetFogGlow(IntPtr _this, SetFogGlow__Args args);
            private static _SetFogGlow _SetFogGlowFunc;
            internal static _SetFogGlow SetFogGlow() {
                if (_SetFogGlowFunc == null) {
                    _SetFogGlowFunc =
                        (_SetFogGlow)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnVolumetricFog_SetFogGlow"), typeof(_SetFogGlow));
                }
                
                return _SetFogGlowFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct SetFogModulation__Args
            {
                internal float new_strenght;
                internal IntPtr new_speed1;
                internal IntPtr new_speed2;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _SetFogModulation(IntPtr _this, SetFogModulation__Args args);
            private static _SetFogModulation _SetFogModulationFunc;
            internal static _SetFogModulation SetFogModulation() {
                if (_SetFogModulationFunc == null) {
                    _SetFogModulationFunc =
                        (_SetFogModulation)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnVolumetricFog_SetFogModulation"), typeof(_SetFogModulation));
                }
                
                return _SetFogModulationFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct SetFogDensity__Args
            {
                internal float new_density;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _SetFogDensity(IntPtr _this, SetFogDensity__Args args);
            private static _SetFogDensity _SetFogDensityFunc;
            internal static _SetFogDensity SetFogDensity() {
                if (_SetFogDensityFunc == null) {
                    _SetFogDensityFunc =
                        (_SetFogDensity)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnVolumetricFog_SetFogDensity"), typeof(_SetFogDensity));
                }
                
                return _SetFogDensityFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct SetFogColor__Args
            {
                internal IntPtr new_color;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _SetFogColor(IntPtr _this, SetFogColor__Args args);
            private static _SetFogColor _SetFogColorFunc;
            internal static _SetFogColor SetFogColor() {
                if (_SetFogColorFunc == null) {
                    _SetFogColorFunc =
                        (_SetFogColor)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnVolumetricFog_SetFogColor"), typeof(_SetFogColor));
                }
                
                return _SetFogColorFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct SetFogColorF__Args
            {
                internal IntPtr new_color;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _SetFogColorF(IntPtr _this, SetFogColorF__Args args);
            private static _SetFogColorF _SetFogColorFFunc;
            internal static _SetFogColorF SetFogColorF() {
                if (_SetFogColorFFunc == null) {
                    _SetFogColorFFunc =
                        (_SetFogColorF)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnVolumetricFog_SetFogColorF"), typeof(_SetFogColorF));
                }
                
                return _SetFogColorFFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct OnLeaveFog__Args
            {
                internal uint obj;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _OnLeaveFog(IntPtr _this, OnLeaveFog__Args args);
            private static _OnLeaveFog _OnLeaveFogFunc;
            internal static _OnLeaveFog OnLeaveFog() {
                if (_OnLeaveFogFunc == null) {
                    _OnLeaveFogFunc =
                        (_OnLeaveFog)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "cbVolumetricFog_onLeaveFog"), typeof(_OnLeaveFog));
                }
                
                return _OnLeaveFogFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct OnEnterFog__Args
            {
                internal uint obj;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _OnEnterFog(IntPtr _this, OnEnterFog__Args args);
            private static _OnEnterFog _OnEnterFogFunc;
            internal static _OnEnterFog OnEnterFog() {
                if (_OnEnterFogFunc == null) {
                    _OnEnterFogFunc =
                        (_OnEnterFog)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "cbVolumetricFog_onEnterFog"), typeof(_OnEnterFog));
                }
                
                return _OnEnterFogFunc;
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
                                "fnVolumetricFog_staticGetType"), typeof(_StaticGetType));
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
                                "fnVolumetricFog_create"), typeof(_Create));
                }
                
                return _CreateFunc;
            }
        }
        #endregion

        /// <summary>returns true if control object is inside the fog</summary>
        /// <description>
        /// .
        /// </description>
        public bool IsInsideFog() {
             InternalUnsafeMethods.IsInsideFog__Args _args = new InternalUnsafeMethods.IsInsideFog__Args() {
             };
             bool _engineResult = InternalUnsafeMethods.IsInsideFog()(ObjectPtr, _args);
             return _engineResult;
        }

        /// <summary>Changes the lightrays postfx when inside the fog</summary>
        /// <description>
        /// .
        /// </description>
        /// <param name="on_off">set to true to modification of the lightray postfx.</param>
        /// <param name="strength">lightray strength.</param>
        public void SetFogLightray(bool on_off, float strength) {
             InternalUnsafeMethods.SetFogLightray__Args _args = new InternalUnsafeMethods.SetFogLightray__Args() {
                on_off = on_off,
                strength = strength,
             };
             InternalUnsafeMethods.SetFogLightray()(ObjectPtr, _args);
        }

        /// <summary>Changes the glow postfx when inside the fog</summary>
        /// <description>
        /// .
        /// </description>
        /// <param name="on_off">set to true to enable glow.</param>
        /// <param name="strength">glow strength.</param>
        public void SetFogGlow(bool on_off, float strength) {
             InternalUnsafeMethods.SetFogGlow__Args _args = new InternalUnsafeMethods.SetFogGlow__Args() {
                on_off = on_off,
                strength = strength,
             };
             InternalUnsafeMethods.SetFogGlow()(ObjectPtr, _args);
        }

        /// <summary>Changes the modulation of the fog</summary>
        /// <description>
        /// .
        /// </description>
        /// <param name="new_strenght">the new strength of the modulation.</param>
        /// <param name="new_speed1">the new speed (x y) of the modulation layer 1.</param>
        /// <param name="new_speed2">the new speed (x y) of the modulation layer 2.</param>
        public void SetFogModulation(float new_strenght, Point2F new_speed1, Point2F new_speed2) {
new_speed1.Alloc();new_speed2.Alloc();             InternalUnsafeMethods.SetFogModulation__Args _args = new InternalUnsafeMethods.SetFogModulation__Args() {
                new_strenght = new_strenght,
                new_speed1 = new_speed1.internalStructPtr,
                new_speed2 = new_speed2.internalStructPtr,
             };
             InternalUnsafeMethods.SetFogModulation()(ObjectPtr, _args);
new_speed1.Free();new_speed2.Free();        }

        /// <summary>Changes the density of the fog</summary>
        /// <description>
        /// .
        /// </description>
        /// <param name="new_density">the new fog density.</param>
        public void SetFogDensity(float new_density) {
             InternalUnsafeMethods.SetFogDensity__Args _args = new InternalUnsafeMethods.SetFogDensity__Args() {
                new_density = new_density,
             };
             InternalUnsafeMethods.SetFogDensity()(ObjectPtr, _args);
        }

        /// <summary>Changes the color of the fog</summary>
        /// <description>
        /// .
        /// </description>
        /// <param name="new_color">the new fog color (rgb 0-255, a is ignored.</param>
        public void SetFogColor(ColorI new_color) {
new_color.Alloc();             InternalUnsafeMethods.SetFogColor__Args _args = new InternalUnsafeMethods.SetFogColor__Args() {
                new_color = new_color.internalStructPtr,
             };
             InternalUnsafeMethods.SetFogColor()(ObjectPtr, _args);
new_color.Free();        }

        /// <summary>Changes the color of the fog</summary>
        /// <description>
        /// .
        /// </description>
        /// <param name="new_color">the new fog color (rgb 0.0 - 1.0, a is ignored.</param>
        public void SetFogColorF(LinearColorF new_color) {
new_color.Alloc();             InternalUnsafeMethods.SetFogColorF__Args _args = new InternalUnsafeMethods.SetFogColorF__Args() {
                new_color = new_color.internalStructPtr,
             };
             InternalUnsafeMethods.SetFogColorF()(ObjectPtr, _args);
new_color.Free();        }

        /// <summary>Called when an object left the volume of the Fog instance.</summary>
        /// <description>
        /// 
        /// </description>
        /// <param name="obj">the controlobject leaving the fog.</param>
        public virtual void OnLeaveFog(uint obj) {
             InternalUnsafeMethods.OnLeaveFog__Args _args = new InternalUnsafeMethods.OnLeaveFog__Args() {
                obj = obj,
             };
             InternalUnsafeMethods.OnLeaveFog()(ObjectPtr, _args);
        }

        /// <summary>Called when an object enters the volume of the Fog instance.</summary>
        /// <description>
        /// 
        /// </description>
        /// <param name="obj">the controlobject entering the fog.</param>
        public virtual void OnEnterFog(uint obj) {
             InternalUnsafeMethods.OnEnterFog__Args _args = new InternalUnsafeMethods.OnEnterFog__Args() {
                obj = obj,
             };
             InternalUnsafeMethods.OnEnterFog()(ObjectPtr, _args);
        }

        /// <description>
        /// Get the type info object for the VolumetricFog class.
        /// </description>
        /// <returns>The type info object for VolumetricFog</returns>
        public static EngineTypeInfo StaticGetType() {
             InternalUnsafeMethods.StaticGetType__Args _args = new InternalUnsafeMethods.StaticGetType__Args() {
             };
             IntPtr _engineResult = InternalUnsafeMethods.StaticGetType()(_args);
             return new EngineTypeInfo(_engineResult);
        }


        /// <value>
        /// <description>
        /// The source shape asset.
        /// </description>
        /// </value>
        public string ShapeAsset {
            get => GenericMarshal.StringTo<string>(GetFieldValue("ShapeAsset"));
            set => SetFieldValue("ShapeAsset", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Path and filename of the model file (.DTS, .DAE) to use for this Volume.
        /// </description>
        /// </value>
        public string ShapeName {
            get => GenericMarshal.StringTo<string>(GetFieldValue("shapeName"));
            set => SetFieldValue("shapeName", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Fog color RGBA (Alpha is ignored)
        /// </description>
        /// </value>
        public ColorI FogColor {
            get => GenericMarshal.StringTo<ColorI>(GetFieldValue("fogColor"));
            set => SetFieldValue("fogColor", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Overal fog density value (0 disables the fog).
        /// </description>
        /// </value>
        public float FogDensity {
            get => GenericMarshal.StringTo<float>(GetFieldValue("fogDensity"));
            set => SetFieldValue("fogDensity", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Set to true if volumetric fog should continue while submerged.
        /// </description>
        /// </value>
        public bool IgnoreWater {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("ignoreWater"));
            set => SetFieldValue("ignoreWater", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Min size (in pixels) for fog to be rendered.
        /// </description>
        /// </value>
        public float MinSize {
            get => GenericMarshal.StringTo<float>(GetFieldValue("MinSize"));
            set => SetFieldValue("MinSize", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Object size in pixels at which the FX-fading kicks in (0 disables fading).
        /// </description>
        /// </value>
        public float FadeSize {
            get => GenericMarshal.StringTo<float>(GetFieldValue("fadeSize"));
            set => SetFieldValue("fadeSize", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// A texture which contains Fogdensity modulator in the red channel and color with 1-green channel. No texture disables modulation.
        /// </description>
        /// </value>
        public string Texture {
            get => GenericMarshal.StringTo<string>(GetFieldValue("texture"));
            set => SetFieldValue("texture", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// How many times the texture is mapped to the object.
        /// </description>
        /// </value>
        public float Tiles {
            get => GenericMarshal.StringTo<float>(GetFieldValue("tiles"));
            set => SetFieldValue("tiles", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Overall strength of the density modulation (0 disables modulation).
        /// </description>
        /// </value>
        public float ModStrength {
            get => GenericMarshal.StringTo<float>(GetFieldValue("modStrength"));
            set => SetFieldValue("modStrength", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Overall primary speed of the density modulation (x-speed(u) y-speed(v))
        /// </description>
        /// </value>
        public Point2F PrimSpeed {
            get => GenericMarshal.StringTo<Point2F>(GetFieldValue("PrimSpeed"));
            set => SetFieldValue("PrimSpeed", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Overall secundary speed of the density modulation (x-speed(u) y-speed(v))
        /// </description>
        /// </value>
        public Point2F SecSpeed {
            get => GenericMarshal.StringTo<Point2F>(GetFieldValue("SecSpeed"));
            set => SetFieldValue("SecSpeed", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Set to true if volumetric fog should be reflected.
        /// </description>
        /// </value>
        public bool Reflectable {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("Reflectable"));
            set => SetFieldValue("Reflectable", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Strength of the reflections (0 disables the fog).
        /// </description>
        /// </value>
        public float ReflectStrength {
            get => GenericMarshal.StringTo<float>(GetFieldValue("ReflectStrength"));
            set => SetFieldValue("ReflectStrength", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Set to true if volumetric fog should use glow PostFX.
        /// </description>
        /// </value>
        public bool UseGlow {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("useGlow"));
            set => SetFieldValue("useGlow", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Overall strength of the glow PostFX.
        /// </description>
        /// </value>
        public float GlowStrength {
            get => GenericMarshal.StringTo<float>(GetFieldValue("glowStrength"));
            set => SetFieldValue("glowStrength", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Set to true if volumetric fog should modify the brightness of the Lightrays.
        /// </description>
        /// </value>
        public bool ModLightRay {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("modLightRay"));
            set => SetFieldValue("modLightRay", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Modifier for LightRay PostFX when inside Fog.
        /// </description>
        /// </value>
        public float LightRayMod {
            get => GenericMarshal.StringTo<float>(GetFieldValue("lightRayMod"));
            set => SetFieldValue("lightRayMod", GenericMarshal.ToString(value));
        }
    }
}