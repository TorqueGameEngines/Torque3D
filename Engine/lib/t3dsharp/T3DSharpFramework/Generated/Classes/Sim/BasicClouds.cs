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
    /// <summary>Renders up to three layers of scrolling cloud-cover textures overhead.</summary>
    /// <description>
    /// %BasicClouds always renders overhead, following the camera. It is intended as part of the background of your level, rendering in front of Sky/Sun type objects and behind everything else.
    /// 
    /// The parameters controlling the rendering of each texture are refered to and grouped as 'layers'. They are rendered in sequential order, so, layer 1 obscures layer 0, and so on.
    /// 
    /// BasicClouds is not affected by scene lighting and is therefore not appropriate for scenes in which lighting radically changes, such as day/night.
    /// </description>
    public unsafe class BasicClouds : SceneObject {
        public BasicClouds(bool pRegister = false) 
            : base(pRegister) {
        }
        
        public BasicClouds(string pName, bool pRegister) 
            : this(false) {
            Name = pName;
            if (pRegister) {
                RegisterObject();
            }
        }
        
        public BasicClouds(string pName) 
            : this(pName, false) {
        }
        
        public BasicClouds(string pName, string pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(Engine.Sim.FindObject<SimObject>(pParent));
        }
        
        public BasicClouds(string pName, SimObject pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(pParent);
        }
        
        public BasicClouds(SimObject pObj) 
            : base(pObj) {
        }
        
        public BasicClouds(IntPtr pObj) 
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
                                "fnBasicClouds_staticGetType"), typeof(_StaticGetType));
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
                                "fnBasicClouds_create"), typeof(_Create));
                }
                
                return _CreateFunc;
            }
        }
        #endregion

        /// <description>
        /// Get the type info object for the BasicClouds class.
        /// </description>
        /// <returns>The type info object for BasicClouds</returns>
        public static EngineTypeInfo StaticGetType() {
             InternalUnsafeMethods.StaticGetType__Args _args = new InternalUnsafeMethods.StaticGetType__Args() {
             };
             IntPtr _engineResult = InternalUnsafeMethods.StaticGetType()(_args);
             return new EngineTypeInfo(_engineResult);
        }


        /// <value>
        /// <description>
        /// Enable or disable rendering of this layer.
        /// </description>
        /// </value>
        public DynamicFieldVector<bool> LayerEnabled {
            get => new DynamicFieldVector<bool>(
                    this, 
                    "layerEnabled", 
                    3, 
                    val => GenericMarshal.StringTo<bool>(val),
                    obj => GenericMarshal.ToString(obj)
                );
        }


        /// <value>
        /// <description>
        /// Texture for this layer.
        /// </description>
        /// </value>
        public DynamicFieldVector<string> Texture {
            get => new DynamicFieldVector<string>(
                    this, 
                    "texture", 
                    3, 
                    val => GenericMarshal.StringTo<string>(val),
                    obj => GenericMarshal.ToString(obj)
                );
        }


        /// <value>
        /// <description>
        /// Texture repeat for this layer.
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
        /// Texture scroll direction for this layer, relative to the world axis.
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
        /// Texture scroll speed for this layer.
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
        /// UV offset for this layer.
        /// </description>
        /// </value>
        public DynamicFieldVector<Point2F> TexOffset {
            get => new DynamicFieldVector<Point2F>(
                    this, 
                    "texOffset", 
                    3, 
                    val => GenericMarshal.StringTo<Point2F>(val),
                    obj => GenericMarshal.ToString(obj)
                );
        }


        /// <value>
        /// <description>
        /// Abstract number which controls the curvature and height of the dome mesh
        /// </description>
        /// </value>
        public DynamicFieldVector<float> Height {
            get => new DynamicFieldVector<float>(
                    this, 
                    "height", 
                    3, 
                    val => GenericMarshal.StringTo<float>(val),
                    obj => GenericMarshal.ToString(obj)
                );
        }
    }
}