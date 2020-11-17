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
    /// <summary>An object that provides a "window" into a zone, allowing a viewer to see what's rendered in the zone.</summary>
    /// <description>
    /// A portal is an object that connects zones such that the content of one zone becomes visible in the other when looking through the portal.
    /// 
    /// Each portal is a full zone which is divided into two sides by the portal plane that intersects it.  This intersection polygon is shown in red in the editor.  Either of the sides of a portal can be connected to one or more zones.
    /// 
    /// A connection from a specific portal side to a zone is made in either of two ways:
    /// 
    /// <ol>
    /// <li>By moving a Zone object to intersect with the portal at the respective side.  While usually it makes sense for this overlap to be small, the connection is established correctly as long as the center of the Zone object that should connect is on the correct side of the portal plane.</li>
    /// <li>By the respective side of the portal free of Zone objects that would connect to it.  In this case, given that the other side is connected to one or more Zones, the portal will automatically connect itself to the outdoor "zone" which implicitly is present in any level.</li>
    /// </ol>
    /// 
    /// From this, it follows that there are two types of portals:
    /// 
    /// <dl>
    /// <dt>Exterior Portals</dt><dd>An exterior portal is one that is connected to one or more Zone objects on one side and to the outdoor zone at the other side.  This kind of portal is most useful for covering transitions from outdoor spaces to indoor spaces.</dd><dt>Interior Portals</dt><dd>An interior portal is one that is connected to one or more Zone objects on both sides.  This kind of portal is most useful for covering transitions between indoor spaces./dd></dl>
    /// 
    /// Strictly speaking, there is a third type of portal called an "invalid portal".  This is a portal that is not connected to a Zone object on either side in which case the portal serves no use.
    /// 
    /// Portals in Torque are bidirectional meaning that they connect zones both ways and you can look through the portal's front side as well as through its back-side.
    /// 
    /// Like Zones, Portals can either be box-shaped or use custom convex polyhedral shapes.
    /// 
    /// Portals will usually be created in the editor but can, of course, also be created in script code as such:
    /// </description>
    /// <code>
    /// // Example declaration of a Portal.  This will create a box-shaped portal.
    /// new Portal( PortalToTestZone )
    /// {
    ///    position = "12.8467 -4.02246 14.8017";
    /// 	 rotation = "0 0 -1 97.5085";
    /// 	 scale = "1 0.25 1";
    /// 	 canSave = "1";
    /// 	 canSaveDynamicFields = "1";
    /// };
    /// </code>
    /// <remarks> Keep in mind that zones and portals are more or less strictly a scene optimization mechanism meant to improve render times.
    /// 
    /// </remarks>
    /// <see cref="Zone" />
    public unsafe class Portal : Zone {
        public Portal(bool pRegister = false) 
            : base(pRegister) {
        }
        
        public Portal(string pName, bool pRegister) 
            : this(false) {
            Name = pName;
            if (pRegister) {
                RegisterObject();
            }
        }
        
        public Portal(string pName) 
            : this(pName, false) {
        }
        
        public Portal(string pName, string pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(Engine.Sim.FindObject<SimObject>(pParent));
        }
        
        public Portal(string pName, SimObject pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(pParent);
        }
        
        public Portal(SimObject pObj) 
            : base(pObj) {
        }
        
        public Portal(IntPtr pObj) 
            : base(pObj) {
        }
        
		protected override void CreateObjectPtr()
		{
			ObjectPtr = InternalUnsafeMethods.Create()(new InternalUnsafeMethods.Create__Args());
		}

        #region UnsafeNativeMethods
        new internal struct InternalUnsafeMethods {
            [StructLayout(LayoutKind.Sequential)]
            internal struct IsExteriorPortal__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            [return: MarshalAs(UnmanagedType.I1)]
            internal delegate bool _IsExteriorPortal(IntPtr _this, IsExteriorPortal__Args args);
            private static _IsExteriorPortal _IsExteriorPortalFunc;
            internal static _IsExteriorPortal IsExteriorPortal() {
                if (_IsExteriorPortalFunc == null) {
                    _IsExteriorPortalFunc =
                        (_IsExteriorPortal)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnPortal_isExteriorPortal"), typeof(_IsExteriorPortal));
                }
                
                return _IsExteriorPortalFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct IsInteriorPortal__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            [return: MarshalAs(UnmanagedType.I1)]
            internal delegate bool _IsInteriorPortal(IntPtr _this, IsInteriorPortal__Args args);
            private static _IsInteriorPortal _IsInteriorPortalFunc;
            internal static _IsInteriorPortal IsInteriorPortal() {
                if (_IsInteriorPortalFunc == null) {
                    _IsInteriorPortalFunc =
                        (_IsInteriorPortal)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnPortal_isInteriorPortal"), typeof(_IsInteriorPortal));
                }
                
                return _IsInteriorPortalFunc;
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
                                "fnPortal_staticGetType"), typeof(_StaticGetType));
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
                                "fnPortal_create"), typeof(_Create));
                }
                
                return _CreateFunc;
            }
        }
        #endregion

        /// <description>
        /// Test whether the portal connects interior zones to the outdoor zone.
        /// </description>
        /// <returns>True if the portal is an exterior portal.</returns>
        public bool IsExteriorPortal() {
             InternalUnsafeMethods.IsExteriorPortal__Args _args = new InternalUnsafeMethods.IsExteriorPortal__Args() {
             };
             bool _engineResult = InternalUnsafeMethods.IsExteriorPortal()(ObjectPtr, _args);
             return _engineResult;
        }

        /// <description>
        /// Test whether the portal connects interior zones only.
        /// </description>
        /// <returns>True if the portal is an interior portal.</returns>
        public bool IsInteriorPortal() {
             InternalUnsafeMethods.IsInteriorPortal__Args _args = new InternalUnsafeMethods.IsInteriorPortal__Args() {
             };
             bool _engineResult = InternalUnsafeMethods.IsInteriorPortal()(ObjectPtr, _args);
             return _engineResult;
        }

        /// <description>
        /// Get the type info object for the Portal class.
        /// </description>
        /// <returns>The type info object for Portal</returns>
        public static EngineTypeInfo StaticGetType() {
             InternalUnsafeMethods.StaticGetType__Args _args = new InternalUnsafeMethods.StaticGetType__Args() {
             };
             IntPtr _engineResult = InternalUnsafeMethods.StaticGetType()(_args);
             return new EngineTypeInfo(_engineResult);
        }


        /// <value>
        /// <description>
        /// Whether one can view through the front-side of the portal.
        /// </description>
        /// </value>
        public bool FrontSidePassable {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("frontSidePassable"));
            set => SetFieldValue("frontSidePassable", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Whether one can view through the back-side of the portal.
        /// </description>
        /// </value>
        public bool BackSidePassable {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("backSidePassable"));
            set => SetFieldValue("backSidePassable", GenericMarshal.ToString(value));
        }
    }
}