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
    /// <summary>A datablock that specifies a Mooring effect.</summary>
    /// <description>
    /// A Mooring is an invisible effect object which can be positioned and oriented within a scene like other objects. Its main purpose is to serve as a common mount point for other effects within the same choreographer. Typically one uses AFX animation features to create movement for a Mooring and then other effects are bound to it using effect-to-effect constraints (#effect).
    /// </description>
    public unsafe class afxMooringData : GameBaseData {
        public afxMooringData(bool pRegister = false) 
            : base(pRegister) {
        }
        
        public afxMooringData(string pName, bool pRegister) 
            : this(false) {
            Name = pName;
            if (pRegister) {
                RegisterObject();
            }
        }
        
        public afxMooringData(string pName) 
            : this(pName, false) {
        }
        
        public afxMooringData(string pName, string pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(Engine.Sim.FindObject<SimObject>(pParent));
        }
        
        public afxMooringData(string pName, SimObject pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(pParent);
        }
        
        public afxMooringData(SimObject pObj) 
            : base(pObj) {
        }
        
        public afxMooringData(IntPtr pObj) 
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
                                "fnafxMooringData_staticGetType"), typeof(_StaticGetType));
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
                                "fnafxMooringData_create"), typeof(_Create));
                }
                
                return _CreateFunc;
            }
        }
        #endregion

        /// <description>
        /// Get the type info object for the afxMooringData class.
        /// </description>
        /// <returns>The type info object for afxMooringData</returns>
        public static EngineTypeInfo StaticGetType() {
             InternalUnsafeMethods.StaticGetType__Args _args = new InternalUnsafeMethods.StaticGetType__Args() {
             };
             IntPtr _engineResult = InternalUnsafeMethods.StaticGetType()(_args);
             return new EngineTypeInfo(_engineResult);
        }


        /// <value>
        /// <description>
        /// Specifies whether to display an axis to help visualize the position and orientation of the mooring.
        /// </description>
        /// </value>
        public bool DisplayAxisMarker {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("displayAxisMarker"));
            set => SetFieldValue("displayAxisMarker", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// This field is only meaningful for networking settings of SCOPE_ALWAYS and GHOSTABLE. In these cases, client moorings are ghosting a mooring on the server, and trackPosOnly determines if the client moorings need to be updated with the server mooring's complete transform or just its position. If only the position needs to be tracked, setting trackPosOnly to true will reduce the network traffic.
        /// </description>
        /// </value>
        public bool TrackPosOnly {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("trackPosOnly"));
            set => SetFieldValue("trackPosOnly", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Specifies the networking model used for the mooring and should be one of: $AFX::SCOPE_ALWAYS, $AFX::GHOSTABLE, $AFX::SERVER_ONLY, or $AFX::CLIENT_ONLY
        /// </description>
        /// </value>
        public sbyte Networking {
            get => GenericMarshal.StringTo<sbyte>(GetFieldValue("networking"));
            set => SetFieldValue("networking", GenericMarshal.ToString(value));
        }
    }
}