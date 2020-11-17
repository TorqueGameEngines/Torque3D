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
    /// <summary>A datablock describing an individual decal.</summary>
    /// <description>
    /// The textures defined by the decal Material can be divided into multiple rectangular sub-textures as shown below, with a different sub-texture selected by all decals using the same DecalData (via #frame) or each decal instance (via #randomize).
    /// </description>
    /// <code>
    /// datablock DecalData(BulletHoleDecal)
    /// {
    ///    material = "DECAL_BulletHole";
    ///    size = "5.0";
    ///    lifeSpan = "50000";
    ///    randomize = "1";
    ///    texRows = "2";
    ///    texCols = "2";
    ///    clippingAngle = "60";
    /// };
    /// </code>
    /// <see cref="Decals" />
    public unsafe class DecalData : SimDataBlock {
        public DecalData(bool pRegister = false) 
            : base(pRegister) {
        }
        
        public DecalData(string pName, bool pRegister) 
            : this(false) {
            Name = pName;
            if (pRegister) {
                RegisterObject();
            }
        }
        
        public DecalData(string pName) 
            : this(pName, false) {
        }
        
        public DecalData(string pName, string pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(Engine.Sim.FindObject<SimObject>(pParent));
        }
        
        public DecalData(string pName, SimObject pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(pParent);
        }
        
        public DecalData(SimObject pObj) 
            : base(pObj) {
        }
        
        public DecalData(IntPtr pObj) 
            : base(pObj) {
        }
        
		protected override void CreateObjectPtr()
		{
			ObjectPtr = InternalUnsafeMethods.Create()(new InternalUnsafeMethods.Create__Args());
		}

        #region UnsafeNativeMethods
        new internal struct InternalUnsafeMethods {
            [StructLayout(LayoutKind.Sequential)]
            internal struct PostApply__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _PostApply(IntPtr _this, PostApply__Args args);
            private static _PostApply _PostApplyFunc;
            internal static _PostApply PostApply() {
                if (_PostApplyFunc == null) {
                    _PostApplyFunc =
                        (_PostApply)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnDecalData_postApply"), typeof(_PostApply));
                }
                
                return _PostApplyFunc;
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
                                "fnDecalData_staticGetType"), typeof(_StaticGetType));
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
                                "fnDecalData_create"), typeof(_Create));
                }
                
                return _CreateFunc;
            }
        }
        #endregion

        /// <description>
        /// Recompute the imagemap sub-texture rectangles for this DecalData.
        /// </description>
        /// <code>
        /// // Inform the decal object to reload its imagemap and frame data.
        /// %decalData.texRows = 4;
        /// %decalData.postApply();
        /// </code>
        public void PostApply() {
             InternalUnsafeMethods.PostApply__Args _args = new InternalUnsafeMethods.PostApply__Args() {
             };
             InternalUnsafeMethods.PostApply()(ObjectPtr, _args);
        }

        /// <description>
        /// Get the type info object for the DecalData class.
        /// </description>
        /// <returns>The type info object for DecalData</returns>
        public static EngineTypeInfo StaticGetType() {
             InternalUnsafeMethods.StaticGetType__Args _args = new InternalUnsafeMethods.StaticGetType__Args() {
             };
             IntPtr _engineResult = InternalUnsafeMethods.StaticGetType()(_args);
             return new EngineTypeInfo(_engineResult);
        }


        /// <value>
        /// <description>
        /// Width and height of the decal in meters before scale is applied.
        /// </description>
        /// </value>
        public float Size {
            get => GenericMarshal.StringTo<float>(GetFieldValue("size"));
            set => SetFieldValue("size", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Material to use for this decal.
        /// </description>
        /// </value>
        public string Material {
            get => GenericMarshal.StringTo<string>(GetFieldValue("Material"));
            set => SetFieldValue("Material", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Time (in milliseconds) before this decal will be automatically deleted.
        /// </description>
        /// </value>
        public int LifeSpan {
            get => GenericMarshal.StringTo<int>(GetFieldValue("lifeSpan"));
            set => SetFieldValue("lifeSpan", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <summary>Time (in milliseconds) over which to fade out the decal before deleting it at the end of its lifetime.</summary>
        /// <description>
        /// 
        /// </description>
        /// <see cref="lifeSpan" />
        /// </value>
        public int FadeTime {
            get => GenericMarshal.StringTo<int>(GetFieldValue("fadeTime"));
            set => SetFieldValue("fadeTime", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <summary>LOD value - size in pixels at which decals of this type begin to fade out.</summary>
        /// <description>
        /// This should be a larger value than #fadeEndPixelSize. However, you may also set this to a negative value to disable lod-based fading.
        /// </description>
        /// </value>
        public float FadeStartPixelSize {
            get => GenericMarshal.StringTo<float>(GetFieldValue("fadeStartPixelSize"));
            set => SetFieldValue("fadeStartPixelSize", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <summary>LOD value - size in pixels at which decals of this type are fully faded out.</summary>
        /// <description>
        /// This should be a smaller value than #fadeStartPixelSize.
        /// </description>
        /// </value>
        public float FadeEndPixelSize {
            get => GenericMarshal.StringTo<float>(GetFieldValue("fadeEndPixelSize"));
            set => SetFieldValue("fadeEndPixelSize", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Default renderPriority for decals of this type (determines draw order when decals overlap).
        /// </description>
        /// </value>
        public sbyte RenderPriority {
            get => GenericMarshal.StringTo<sbyte>(GetFieldValue("renderPriority"));
            set => SetFieldValue("renderPriority", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// The angle in degrees used to clip geometry that faces away from the decal projection direction.
        /// </description>
        /// </value>
        public float ClippingAngle {
            get => GenericMarshal.StringTo<float>(GetFieldValue("clippingAngle"));
            set => SetFieldValue("clippingAngle", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Index of the texture rectangle within the imagemap to use for this decal.
        /// </description>
        /// </value>
        public int Frame {
            get => GenericMarshal.StringTo<int>(GetFieldValue("frame"));
            set => SetFieldValue("frame", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// If true, a random frame from the imagemap is selected for each instance of the decal.
        /// </description>
        /// </value>
        public bool Randomize {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("randomize"));
            set => SetFieldValue("randomize", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Number of individual frames in the imagemap (maximum 16).
        /// </description>
        /// </value>
        public int TextureCoordCount {
            get => GenericMarshal.StringTo<int>(GetFieldValue("textureCoordCount"));
            set => SetFieldValue("textureCoordCount", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <summary>Number of rows in the supplied imagemap.</summary>
        /// <description>
        /// Use #texRows and #texCols if the imagemap frames are arranged in a grid; use #textureCoords to manually specify UV coordinates for irregular sized frames.
        /// </description>
        /// </value>
        public int TexRows {
            get => GenericMarshal.StringTo<int>(GetFieldValue("texRows"));
            set => SetFieldValue("texRows", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <summary>Number of columns in the supplied imagemap.</summary>
        /// <description>
        /// Use #texRows and #texCols if the imagemap frames are arranged in a grid; use #textureCoords to manually specify UV coordinates for irregular sized frames.
        /// </description>
        /// </value>
        public int TexCols {
            get => GenericMarshal.StringTo<int>(GetFieldValue("texCols"));
            set => SetFieldValue("texCols", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <summary>An array of RectFs (topleft.x topleft.y extent.x extent.y) representing the UV coordinates for each frame in the imagemap.</summary>
        /// <description>
        /// 
        /// </description>
        /// <remarks> This field should only be set if the imagemap frames are irregular in size. Otherwise use the #texRows and #texCols fields and the UV coordinates will be calculated automatically.</remarks>
        /// </value>
        public DynamicFieldVector<RectF> TextureCoords {
            get => new DynamicFieldVector<RectF>(
                    this, 
                    "textureCoords", 
                    16, 
                    val => GenericMarshal.StringTo<RectF>(val),
                    obj => GenericMarshal.ToString(obj)
                );
        }
    }
}