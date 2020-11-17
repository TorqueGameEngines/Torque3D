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
    /// <summary>An invisible shape that causes objects hidden from view behind it to not be rendered.</summary>
    /// <description>
    /// OcclusionVolume is a class for scene optimization.  It's main use is for outdoor spaces where zones and portals do not help in optimizing scene culling as they almost only make sense for modeling visibility in indoor scenarios (and for connecting indoor spaces to outdoor spaces).
    /// 
    /// During rendering, every object that is fully behind an occluder 
    /// 
    /// Be aware that occluders add overhead to scene culling.  Only if this overhead is outweighed by the time saved by not rendering hidden objects, is the occluder actually effective.  Because of this, chose only those spots for placing occluders where a significant number of objects will be culled from points that the player will actually be at during the game.
    /// 
    /// Like zones and portals, OcclusionVolumes may have a default box shape or a more complex
    /// </description>
    /// <see cref="Scene::maxOccludersPerZone" />
    /// <see cref="Scene::occluderMinWidthPercentage" />
    /// <see cref="Scene::occluderMinHeightPercentage" />
    public unsafe class OcclusionVolume : SceneObject {
        public OcclusionVolume(bool pRegister = false) 
            : base(pRegister) {
        }
        
        public OcclusionVolume(string pName, bool pRegister) 
            : this(false) {
            Name = pName;
            if (pRegister) {
                RegisterObject();
            }
        }
        
        public OcclusionVolume(string pName) 
            : this(pName, false) {
        }
        
        public OcclusionVolume(string pName, string pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(Engine.Sim.FindObject<SimObject>(pParent));
        }
        
        public OcclusionVolume(string pName, SimObject pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(pParent);
        }
        
        public OcclusionVolume(SimObject pObj) 
            : base(pObj) {
        }
        
        public OcclusionVolume(IntPtr pObj) 
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
                                "fnOcclusionVolume_staticGetType"), typeof(_StaticGetType));
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
                                "fnOcclusionVolume_create"), typeof(_Create));
                }
                
                return _CreateFunc;
            }
        }
        #endregion

        /// <description>
        /// Get the type info object for the OcclusionVolume class.
        /// </description>
        /// <returns>The type info object for OcclusionVolume</returns>
        public static EngineTypeInfo StaticGetType() {
             InternalUnsafeMethods.StaticGetType__Args _args = new InternalUnsafeMethods.StaticGetType__Args() {
             };
             IntPtr _engineResult = InternalUnsafeMethods.StaticGetType()(_args);
             return new EngineTypeInfo(_engineResult);
        }


        /// <value>
        /// <description>
        /// For internal use only.
        /// </description>
        /// </value>
        public string Plane {
            get => GenericMarshal.StringTo<string>(GetFieldValue("plane"));
            set => SetFieldValue("plane", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// For internal use only.
        /// </description>
        /// </value>
        public string Point {
            get => GenericMarshal.StringTo<string>(GetFieldValue("point"));
            set => SetFieldValue("point", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// For internal use only.
        /// </description>
        /// </value>
        public string Edge {
            get => GenericMarshal.StringTo<string>(GetFieldValue("edge"));
            set => SetFieldValue("edge", GenericMarshal.ToString(value));
        }
    }
}