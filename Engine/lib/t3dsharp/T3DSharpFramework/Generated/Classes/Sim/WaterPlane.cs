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
    /// <summary>Represents a large body of water stretching to the horizon in all directions.</summary>
    /// <description>
    /// WaterPlane's position is defined only height, the z element of position, it is infinite in xy and depth. %WaterPlane is designed to represent the ocean on an island scene and viewed from ground level; other uses may not be appropriate and a WaterBlock may be used.
    /// </description>
    /// <see cref="WaterObject for inherited functionality.
    /// 
    /// Limitations:
    /// 
    /// Because %WaterPlane cannot be projected exactly to the far-clip distance, other objects nearing this distance can have noticible artifacts as they clip through first the %WaterPlane and then the far plane.
    /// 
    /// To avoid this large objects should be positioned such that they will not line up with the far-clip from vantage points the player is expected to be. In particular, your TerrainBlock should be completely contained by the far-clip distance.
    /// 
    /// Viewing %WaterPlane from a high altitude with a tight far-clip distance will accentuate this limitation. %WaterPlane is primarily designed to be viewed from ground level." />
    public unsafe class WaterPlane : WaterObject {
        public WaterPlane(bool pRegister = false) 
            : base(pRegister) {
        }
        
        public WaterPlane(string pName, bool pRegister) 
            : this(false) {
            Name = pName;
            if (pRegister) {
                RegisterObject();
            }
        }
        
        public WaterPlane(string pName) 
            : this(pName, false) {
        }
        
        public WaterPlane(string pName, string pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(Engine.Sim.FindObject<SimObject>(pParent));
        }
        
        public WaterPlane(string pName, SimObject pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(pParent);
        }
        
        public WaterPlane(SimObject pObj) 
            : base(pObj) {
        }
        
        public WaterPlane(IntPtr pObj) 
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
                                "fnWaterPlane_staticGetType"), typeof(_StaticGetType));
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
                                "fnWaterPlane_create"), typeof(_Create));
                }
                
                return _CreateFunc;
            }
        }
        #endregion

        /// <description>
        /// Get the type info object for the WaterPlane class.
        /// </description>
        /// <returns>The type info object for WaterPlane</returns>
        public static EngineTypeInfo StaticGetType() {
             InternalUnsafeMethods.StaticGetType__Args _args = new InternalUnsafeMethods.StaticGetType__Args() {
             };
             IntPtr _engineResult = InternalUnsafeMethods.StaticGetType()(_args);
             return new EngineTypeInfo(_engineResult);
        }


        /// <value>
        /// <description>
        /// Spacing between vertices in the WaterBlock mesh
        /// </description>
        /// </value>
        public int GridSize {
            get => GenericMarshal.StringTo<int>(GetFieldValue("gridSize"));
            set => SetFieldValue("gridSize", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Duplicate of gridElementSize for backwards compatility
        /// </description>
        /// </value>
        public float GridElementSize {
            get => GenericMarshal.StringTo<float>(GetFieldValue("gridElementSize"));
            set => SetFieldValue("gridElementSize", GenericMarshal.ToString(value));
        }
    }
}