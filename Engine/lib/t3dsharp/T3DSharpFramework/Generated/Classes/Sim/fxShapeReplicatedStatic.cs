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
    /// <summary>The object definition for shapes that will be replicated across an area using an fxShapeReplicator.</summary>
    /// <description>
    /// 
    /// </description>
    public unsafe class fxShapeReplicatedStatic : SceneObject {
        public fxShapeReplicatedStatic(bool pRegister = false) 
            : base(pRegister) {
        }
        
        public fxShapeReplicatedStatic(string pName, bool pRegister) 
            : this(false) {
            Name = pName;
            if (pRegister) {
                RegisterObject();
            }
        }
        
        public fxShapeReplicatedStatic(string pName) 
            : this(pName, false) {
        }
        
        public fxShapeReplicatedStatic(string pName, string pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(Engine.Sim.FindObject<SimObject>(pParent));
        }
        
        public fxShapeReplicatedStatic(string pName, SimObject pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(pParent);
        }
        
        public fxShapeReplicatedStatic(SimObject pObj) 
            : base(pObj) {
        }
        
        public fxShapeReplicatedStatic(IntPtr pObj) 
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
                                "fnfxShapeReplicatedStatic_staticGetType"), typeof(_StaticGetType));
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
                                "fnfxShapeReplicatedStatic_create"), typeof(_Create));
                }
                
                return _CreateFunc;
            }
        }
        #endregion

        /// <description>
        /// Get the type info object for the fxShapeReplicatedStatic class.
        /// </description>
        /// <returns>The type info object for fxShapeReplicatedStatic</returns>
        public static EngineTypeInfo StaticGetType() {
             InternalUnsafeMethods.StaticGetType__Args _args = new InternalUnsafeMethods.StaticGetType__Args() {
             };
             IntPtr _engineResult = InternalUnsafeMethods.StaticGetType()(_args);
             return new EngineTypeInfo(_engineResult);
        }


        /// <value>
        /// <description>
        /// Percent Animation Offset.
        /// </description>
        /// </value>
        public float AnimOffset {
            get => GenericMarshal.StringTo<float>(GetFieldValue("AnimOffset"));
            set => SetFieldValue("AnimOffset", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Percent Animation Speed.
        /// </description>
        /// </value>
        public float AnimSpeed {
            get => GenericMarshal.StringTo<float>(GetFieldValue("AnimSpeed"));
            set => SetFieldValue("AnimSpeed", GenericMarshal.ToString(value));
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
        /// %Path and filename of the model file (.DTS, .DAE) to use for this TSStatic. Legacy field. Any loose files assigned here will attempt to be auto-imported in as an asset.
        /// </description>
        /// </value>
        public string ShapeName {
            get => GenericMarshal.StringTo<string>(GetFieldValue("shapeName"));
            set => SetFieldValue("shapeName", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <summary>The skin applied to the shape.</summary>
        /// <description>
        /// 'Skinning' the shape effectively renames the material targets, allowing different materials to be used on different instances of the same model.
        /// 
        /// Any material targets that start with the old skin name have that part of the name replaced with the new skin name. The initial old skin name is "base". For example, if a new skin of "blue" was applied to a model that had material targets <i>base_body</i> and <i>face</i>, the new targets would be <i>blue_body</i> and <i>face</i>. Note that <i>face</i> was not renamed since it did not start with the old skin name of "base".
        /// 
        /// To support models that do not use the default "base" naming convention, you can also specify the part of the name to replace in the skin field itself. For example, if a model had a material target called <i>shapemat</i>, we could apply a new skin "shape=blue", and the material target would be renamed to <i>bluemat</i> (note "shape" has been replaced with "blue").
        /// 
        /// Multiple skin updates can also be applied at the same time by separating them with a semicolon. For example: "base=blue;face=happy_face".
        /// 
        /// Material targets are only renamed if an existing Material maps to that name, or if there is a diffuse texture in the model folder with the same name as the new target.
        /// </description>
        /// </value>
        public string Skin {
            get => GenericMarshal.StringTo<string>(GetFieldValue("skin"));
            set => SetFieldValue("skin", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Enables automatic playing of the animation sequence named "ambient" (if it exists) when the TSStatic is loaded.
        /// </description>
        /// </value>
        public bool PlayAmbient {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("playAmbient"));
            set => SetFieldValue("playAmbient", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Enables detailed culling of meshes within the TSStatic. Should only be used with large complex shapes like buildings which contain many submeshes.
        /// </description>
        /// </value>
        public bool MeshCulling {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("meshCulling"));
            set => SetFieldValue("meshCulling", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Enables translucent sorting of the TSStatic by its origin instead of the bounds.
        /// </description>
        /// </value>
        public bool OriginSort {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("originSort"));
            set => SetFieldValue("originSort", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// References a ReflectorDesc datablock that defines performance and quality properties for dynamic reflections.
        /// </description>
        /// </value>
        public string CubeReflectorDesc {
            get => GenericMarshal.StringTo<string>(GetFieldValue("cubeReflectorDesc"));
            set => SetFieldValue("cubeReflectorDesc", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// The type of mesh data to use for collision queries.
        /// </description>
        /// </value>
        public TSMeshType CollisionType {
            get => GenericMarshal.StringTo<TSMeshType>(GetFieldValue("collisionType"));
            set => SetFieldValue("collisionType", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// The type of mesh data used to clip decal polygons against.
        /// </description>
        /// </value>
        public TSMeshType DecalType {
            get => GenericMarshal.StringTo<TSMeshType>(GetFieldValue("decalType"));
            set => SetFieldValue("decalType", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <summary>Allow a Player to walk up sloping polygons in the TSStatic (based on the collisionType).</summary>
        /// <description>
        /// When set to false, the slightest bump will stop the player from walking on top of the object.
        /// </description>
        /// </value>
        public bool AllowPlayerStep {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("allowPlayerStep"));
            set => SetFieldValue("allowPlayerStep", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Turn on/off Alpha Fade
        /// </description>
        /// </value>
        public bool AlphaFadeEnable {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("alphaFadeEnable"));
            set => SetFieldValue("alphaFadeEnable", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Distance of start Alpha Fade
        /// </description>
        /// </value>
        public float AlphaFadeStart {
            get => GenericMarshal.StringTo<float>(GetFieldValue("alphaFadeStart"));
            set => SetFieldValue("alphaFadeStart", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Distance of end Alpha Fade
        /// </description>
        /// </value>
        public float AlphaFadeEnd {
            get => GenericMarshal.StringTo<float>(GetFieldValue("alphaFadeEnd"));
            set => SetFieldValue("alphaFadeEnd", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Invert Alpha Fade's Start & End Distance
        /// </description>
        /// </value>
        public bool AlphaFadeInverse {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("alphaFadeInverse"));
            set => SetFieldValue("alphaFadeInverse", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Debug rendering mode shows the normals for each point in the TSStatic's mesh.
        /// </description>
        /// </value>
        public float RenderNormals {
            get => GenericMarshal.StringTo<float>(GetFieldValue("renderNormals"));
            set => SetFieldValue("renderNormals", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Forces rendering to a particular detail level.
        /// </description>
        /// </value>
        public int ForceDetail {
            get => GenericMarshal.StringTo<int>(GetFieldValue("forceDetail"));
            set => SetFieldValue("forceDetail", GenericMarshal.ToString(value));
        }


        /// <value>
        /// 
        /// </value>
        public bool IgnoreZodiacs {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("ignoreZodiacs"));
            set => SetFieldValue("ignoreZodiacs", GenericMarshal.ToString(value));
        }


        /// <value>
        /// 
        /// </value>
        public bool UseGradientRange {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("useGradientRange"));
            set => SetFieldValue("useGradientRange", GenericMarshal.ToString(value));
        }


        /// <value>
        /// 
        /// </value>
        public Point2F GradientRange {
            get => GenericMarshal.StringTo<Point2F>(GetFieldValue("gradientRange"));
            set => SetFieldValue("gradientRange", GenericMarshal.ToString(value));
        }


        /// <value>
        /// 
        /// </value>
        public bool InvertGradientRange {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("invertGradientRange"));
            set => SetFieldValue("invertGradientRange", GenericMarshal.ToString(value));
        }
    }
}