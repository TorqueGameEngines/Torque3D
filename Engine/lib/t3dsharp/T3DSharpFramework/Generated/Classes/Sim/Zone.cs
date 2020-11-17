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
    /// <summary>An object that represents an interior space.</summary>
    /// <description>
    /// A zone is an invisible volume that encloses an interior space.  All objects that have their world space axis-aligned bounding boxes (AABBs) intersect the zone's volume are assigned to the zone.  This assignment happens automatically as objects are placed and transformed.  Also, assignment is not exclusive meaning that an object can be assigned to many zones at the same time if it intersects all of them.
    /// 
    /// In itself, the volume of a zone is fully sealed off from the outside.  This means that while viewing the scene from inside the volume, only objects assigned to the zone are rendered while when viewing the scene from outside the volume, objects <em>exclusively</em> only assigned the zone are not rendered.
    /// 
    /// Usually, you will want to connect zones to each other by means of portals.  A portal overlapping with a zone
    /// </description>
    /// <code>
    /// // Example declaration of a Zone.  This creates a box-shaped zone.
    /// new Zone( TestZone )
    /// {
    ///    position = "3.61793 -1.01945 14.7442";
    ///    rotation = "1 0 0 0";
    ///    scale = "10 10 10";
    /// };
    /// </code>
    /// <see cref="Portal" />
    public unsafe class Zone : SceneObject {
        public Zone(bool pRegister = false) 
            : base(pRegister) {
        }
        
        public Zone(string pName, bool pRegister) 
            : this(false) {
            Name = pName;
            if (pRegister) {
                RegisterObject();
            }
        }
        
        public Zone(string pName) 
            : this(pName, false) {
        }
        
        public Zone(string pName, string pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(Engine.Sim.FindObject<SimObject>(pParent));
        }
        
        public Zone(string pName, SimObject pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(pParent);
        }
        
        public Zone(SimObject pObj) 
            : base(pObj) {
        }
        
        public Zone(IntPtr pObj) 
            : base(pObj) {
        }
        
		protected override void CreateObjectPtr()
		{
			ObjectPtr = InternalUnsafeMethods.Create()(new InternalUnsafeMethods.Create__Args());
		}

        #region UnsafeNativeMethods
        new internal struct InternalUnsafeMethods {
            [StructLayout(LayoutKind.Sequential)]
            internal struct SelectWithin__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _SelectWithin(IntPtr _this, SelectWithin__Args args);
            private static _SelectWithin _SelectWithinFunc;
            internal static _SelectWithin SelectWithin() {
                if (_SelectWithinFunc == null) {
                    _SelectWithinFunc =
                        (_SelectWithin)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnZone_selectWithin"), typeof(_SelectWithin));
                }
                
                return _SelectWithinFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct DumpZoneState__Args
            {
                [MarshalAs(UnmanagedType.I1)]
                internal bool updateFirst;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _DumpZoneState(IntPtr _this, DumpZoneState__Args args);
            private static _DumpZoneState _DumpZoneStateFunc;
            internal static _DumpZoneState DumpZoneState() {
                if (_DumpZoneStateFunc == null) {
                    _DumpZoneStateFunc =
                        (_DumpZoneState)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnZone_dumpZoneState"), typeof(_DumpZoneState));
                }
                
                return _DumpZoneStateFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct GetZoneId__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate int _GetZoneId(IntPtr _this, GetZoneId__Args args);
            private static _GetZoneId _GetZoneIdFunc;
            internal static _GetZoneId GetZoneId() {
                if (_GetZoneIdFunc == null) {
                    _GetZoneIdFunc =
                        (_GetZoneId)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnZone_getZoneId"), typeof(_GetZoneId));
                }
                
                return _GetZoneIdFunc;
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
                                "fnZone_staticGetType"), typeof(_StaticGetType));
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
                                "fnZone_create"), typeof(_Create));
                }
                
                return _CreateFunc;
            }
        }
        #endregion

        /// <description>
        /// select a list of all objects assigned to the zone
        /// </description>
        public void SelectWithin() {
             InternalUnsafeMethods.SelectWithin__Args _args = new InternalUnsafeMethods.SelectWithin__Args() {
             };
             InternalUnsafeMethods.SelectWithin()(ObjectPtr, _args);
        }

        /// <description>
        /// Dump a list of all objects assigned to the zone to the console as well as a list of all connected zone spaces.
        /// </description>
        /// <param name="updateFirst">Whether to update the contents of the zone before dumping.  Since zoning states of objects are updated on demand, the zone contents can be outdated.</param>
        public void DumpZoneState(bool updateFirst = true) {
             InternalUnsafeMethods.DumpZoneState__Args _args = new InternalUnsafeMethods.DumpZoneState__Args() {
                updateFirst = updateFirst,
             };
             InternalUnsafeMethods.DumpZoneState()(ObjectPtr, _args);
        }

        /// <description>
        /// Get the unique numeric ID of the zone in its scene.
        /// </description>
        /// <returns>The ID of the zone.</returns>
        public int GetZoneId() {
             InternalUnsafeMethods.GetZoneId__Args _args = new InternalUnsafeMethods.GetZoneId__Args() {
             };
             int _engineResult = InternalUnsafeMethods.GetZoneId()(ObjectPtr, _args);
             return _engineResult;
        }

        /// <description>
        /// Get the type info object for the Zone class.
        /// </description>
        /// <returns>The type info object for Zone</returns>
        public static EngineTypeInfo StaticGetType() {
             InternalUnsafeMethods.StaticGetType__Args _args = new InternalUnsafeMethods.StaticGetType__Args() {
             };
             IntPtr _engineResult = InternalUnsafeMethods.StaticGetType()(_args);
             return new EngineTypeInfo(_engineResult);
        }


        /// <value>
        /// <description>
        /// Select all in this zone
        /// </description>
        /// </value>
        public bool SelectAll {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("selectAll"));
            set => SetFieldValue("selectAll", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Ambient sound environment for the space.
        /// </description>
        /// </value>
        public SFXAmbience SoundAmbience {
            get => GenericMarshal.StringTo<SFXAmbience>(GetFieldValue("soundAmbience"));
            set => SetFieldValue("soundAmbience", GenericMarshal.ToString(value));
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


        /// <value>
        /// <description>
        /// Whether to use #ambientLightColor for ambient lighting in this zone or the global ambient color.
        /// </description>
        /// </value>
        public bool UseAmbientLightColor {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("useAmbientLightColor"));
            set => SetFieldValue("useAmbientLightColor", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Color of ambient lighting in this zone.
        /// 
        /// Only used if #useAmbientLightColor is true.
        /// </description>
        /// </value>
        public LinearColorF AmbientLightColor {
            get => GenericMarshal.StringTo<LinearColorF>(GetFieldValue("ambientLightColor"));
            set => SetFieldValue("ambientLightColor", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// ID of group the zone is part of.
        /// </description>
        /// </value>
        public int ZoneGroup {
            get => GenericMarshal.StringTo<int>(GetFieldValue("zoneGroup"));
            set => SetFieldValue("zoneGroup", GenericMarshal.ToString(value));
        }
    }
}