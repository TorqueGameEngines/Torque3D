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
    /// <summary>Special type of marker, distinguished by a name and team ID number</summary>
    /// <description>
    /// The original Torque engines were built from a multi-player game called Tribes. The Tribes series featured various team based game modes, such as capture the flag. The WayPoint class survived the conversion from game (Tribes) to game engine (Torque).
    /// 
    /// Essentially, this is a MissionMarker with the addition of two variables: markerName and team. Whenever a WayPoint is created, it is added to a unique global list called WayPointSet. You can iterate through this set, seeking out specific markers determined by their markerName and team ID. This avoids the overhead of constantly calling commandToClient and commandToServer to determine a WayPoint object's name, unique ID, etc.
    /// </description>
    /// <remarks> The <i>markerName<i> field was previously called <i>name</i>, but was changed because this conflicted with the SimObject name field. Existing scripts that relied on the WayPoint <i>name</i> field will need to be updated.
    /// 
    /// </remarks>
    /// <code>
    /// new WayPoint()
    /// {
    ///    team = "1";
    ///    dataBlock = "WayPointMarker";
    ///    position = "-0.0224786 1.53471 2.93219";
    ///    rotation = "1 0 0 0";
    ///    scale = "1 1 1";
    ///    canSave = "1";
    ///    canSaveDynamicFields = "1";
    /// };
    /// </code>
    /// <see cref="MissionMarker" />
    /// <see cref="MissionMarkerData" />
    public unsafe class WayPoint : MissionMarker {
        public WayPoint(bool pRegister = false) 
            : base(pRegister) {
        }
        
        public WayPoint(string pName, bool pRegister) 
            : this(false) {
            Name = pName;
            if (pRegister) {
                RegisterObject();
            }
        }
        
        public WayPoint(string pName) 
            : this(pName, false) {
        }
        
        public WayPoint(string pName, string pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(Engine.Sim.FindObject<SimObject>(pParent));
        }
        
        public WayPoint(string pName, SimObject pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(pParent);
        }
        
        public WayPoint(SimObject pObj) 
            : base(pObj) {
        }
        
        public WayPoint(IntPtr pObj) 
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
                                "fnWayPoint_staticGetType"), typeof(_StaticGetType));
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
                                "fnWayPoint_create"), typeof(_Create));
                }
                
                return _CreateFunc;
            }
        }
        #endregion

        /// <description>
        /// Get the type info object for the WayPoint class.
        /// </description>
        /// <returns>The type info object for WayPoint</returns>
        public static EngineTypeInfo StaticGetType() {
             InternalUnsafeMethods.StaticGetType__Args _args = new InternalUnsafeMethods.StaticGetType__Args() {
             };
             IntPtr _engineResult = InternalUnsafeMethods.StaticGetType()(_args);
             return new EngineTypeInfo(_engineResult);
        }


        /// <value>
        /// <description>
        /// Unique name representing this waypoint
        /// </description>
        /// </value>
        public string MarkerName {
            get => GenericMarshal.StringTo<string>(GetFieldValue("markerName"));
            set => SetFieldValue("markerName", GenericMarshal.ToString(value));
        }
    }
}