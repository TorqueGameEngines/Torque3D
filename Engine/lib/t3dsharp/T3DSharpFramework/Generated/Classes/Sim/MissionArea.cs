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
    /// <summary>Level object which defines the boundaries of the level.</summary>
    /// <description>
    /// This is a simple box with starting points, width, depth, and height. It does not have any default functionality. Instead, when objects hit the boundaries certain script callbacks will be made allowing you to control the reaction.
    /// </description>
    /// <code>
    /// new MissionArea(GlobalMissionArea)
    /// {
    /// 	  Area = "-152 -352 1008 864";
    /// 	  flightCeiling = "300";
    /// 	  flightCeilingRange = "20";
    /// 	  canSaveDynamicFields = "1";
    /// 		 enabled = "1";
    /// 		 TypeBool locked = "false";
    /// };
    /// </code>
    public unsafe class MissionArea : NetObject {
        public MissionArea(bool pRegister = false) 
            : base(pRegister) {
        }
        
        public MissionArea(string pName, bool pRegister) 
            : this(false) {
            Name = pName;
            if (pRegister) {
                RegisterObject();
            }
        }
        
        public MissionArea(string pName) 
            : this(pName, false) {
        }
        
        public MissionArea(string pName, string pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(Engine.Sim.FindObject<SimObject>(pParent));
        }
        
        public MissionArea(string pName, SimObject pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(pParent);
        }
        
        public MissionArea(SimObject pObj) 
            : base(pObj) {
        }
        
        public MissionArea(IntPtr pObj) 
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
                                "fnMissionArea_postApply"), typeof(_PostApply));
                }
                
                return _PostApplyFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct SetArea__Args
            {
                internal int x;
                internal int y;
                internal int width;
                internal int height;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _SetArea(IntPtr _this, SetArea__Args args);
            private static _SetArea _SetAreaFunc;
            internal static _SetArea SetArea() {
                if (_SetAreaFunc == null) {
                    _SetAreaFunc =
                        (_SetArea)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnMissionArea_setArea"), typeof(_SetArea));
                }
                
                return _SetAreaFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct GetArea__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            
            internal delegate IntPtr _GetArea(IntPtr _this, GetArea__Args args);
            private static _GetArea _GetAreaFunc;
            internal static _GetArea GetArea() {
                if (_GetAreaFunc == null) {
                    _GetAreaFunc =
                        (_GetArea)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnMissionArea_getArea"), typeof(_GetArea));
                }
                
                return _GetAreaFunc;
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
                                "fnMissionArea_staticGetType"), typeof(_StaticGetType));
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
                                "fnMissionArea_create"), typeof(_Create));
                }
                
                return _CreateFunc;
            }
        }
        #endregion

        /// <description>
        /// Intended as a helper to developers and editor scripts.
        /// Force trigger an inspectPostApply. This will transmit material and other fields ( not including nodes ) to client objects.
        /// </description>
        public void PostApply() {
             InternalUnsafeMethods.PostApply__Args _args = new InternalUnsafeMethods.PostApply__Args() {
             };
             InternalUnsafeMethods.PostApply()(ObjectPtr, _args);
        }

        /// <summary>- Defines the size of the MissionArea</summary>
        /// <description>
        /// param x Starting X coordinate position for MissionArea
        /// param y Starting Y coordinate position for MissionArea
        /// param width New width of the MissionArea
        /// param height New height of the MissionArea
        /// </description>
        /// <remarks> Only the server object may be set.
        /// </remarks>
        public void SetArea(int x, int y, int width, int height) {
             InternalUnsafeMethods.SetArea__Args _args = new InternalUnsafeMethods.SetArea__Args() {
                x = x,
                y = y,
                width = width,
                height = height,
             };
             InternalUnsafeMethods.SetArea()(ObjectPtr, _args);
        }

        /// <description>
        /// Returns 4 fields: starting x, starting y, extents x, extents y.
        /// </description>
        public string GetArea() {
             InternalUnsafeMethods.GetArea__Args _args = new InternalUnsafeMethods.GetArea__Args() {
             };
             IntPtr _engineResult = InternalUnsafeMethods.GetArea()(ObjectPtr, _args);
             return StringMarshal.IntPtrToUtf8String(_engineResult);
        }

        /// <description>
        /// Get the type info object for the MissionArea class.
        /// </description>
        /// <returns>The type info object for MissionArea</returns>
        public static EngineTypeInfo StaticGetType() {
             InternalUnsafeMethods.StaticGetType__Args _args = new InternalUnsafeMethods.StaticGetType__Args() {
             };
             IntPtr _engineResult = InternalUnsafeMethods.StaticGetType()(_args);
             return new EngineTypeInfo(_engineResult);
        }


        /// <value>
        /// <description>
        /// Four corners (X1, X2, Y1, Y2) that makes up the level's boundaries
        /// </description>
        /// </value>
        public RectI Area {
            get => GenericMarshal.StringTo<RectI>(GetFieldValue("area"));
            set => SetFieldValue("area", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Represents the top of the mission area, used by FlyingVehicle.
        /// </description>
        /// </value>
        public float FlightCeiling {
            get => GenericMarshal.StringTo<float>(GetFieldValue("flightCeiling"));
            set => SetFieldValue("flightCeiling", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Distance from ceiling before FlyingVehicle thrust is cut off.
        /// </description>
        /// </value>
        public float FlightCeilingRange {
            get => GenericMarshal.StringTo<float>(GetFieldValue("flightCeilingRange"));
            set => SetFieldValue("flightCeilingRange", GenericMarshal.ToString(value));
        }
    }
}