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
    /// 
    public unsafe class VMotionTrack : VSceneObjectTrack {
        public VMotionTrack(bool pRegister = false) 
            : base(pRegister) {
        }
        
        public VMotionTrack(string pName, bool pRegister) 
            : this(false) {
            Name = pName;
            if (pRegister) {
                RegisterObject();
            }
        }
        
        public VMotionTrack(string pName) 
            : this(pName, false) {
        }
        
        public VMotionTrack(string pName, string pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(Engine.Sim.FindObject<SimObject>(pParent));
        }
        
        public VMotionTrack(string pName, SimObject pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(pParent);
        }
        
        public VMotionTrack(SimObject pObj) 
            : base(pObj) {
        }
        
        public VMotionTrack(IntPtr pObj) 
            : base(pObj) {
        }
        
		protected override void CreateObjectPtr()
		{
			ObjectPtr = InternalUnsafeMethods.Create()(new InternalUnsafeMethods.Create__Args());
		}

        #region UnsafeNativeMethods
        new internal struct InternalUnsafeMethods {
            [StructLayout(LayoutKind.Sequential)]
            internal struct GetPath__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate int _GetPath(IntPtr _this, GetPath__Args args);
            private static _GetPath _GetPathFunc;
            internal static _GetPath GetPath() {
                if (_GetPathFunc == null) {
                    _GetPathFunc =
                        (_GetPath)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnVMotionTrack_getPath"), typeof(_GetPath));
                }
                
                return _GetPathFunc;
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
                                "fnVMotionTrack_staticGetType"), typeof(_StaticGetType));
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
                                "fnVMotionTrack_create"), typeof(_Create));
                }
                
                return _CreateFunc;
            }
        }
        #endregion

        /// <description>
        /// ( void ) - Get the path object this track references.
        /// </description>
        /// <returns>Returns the SimObjectID for the object.</returns>
        public int GetPath() {
             InternalUnsafeMethods.GetPath__Args _args = new InternalUnsafeMethods.GetPath__Args() {
             };
             int _engineResult = InternalUnsafeMethods.GetPath()(ObjectPtr, _args);
             return _engineResult;
        }

        /// <description>
        /// Get the type info object for the VMotionTrack class.
        /// </description>
        /// <returns>The type info object for VMotionTrack</returns>
        public static EngineTypeInfo StaticGetType() {
             InternalUnsafeMethods.StaticGetType__Args _args = new InternalUnsafeMethods.StaticGetType__Args() {
             };
             IntPtr _engineResult = InternalUnsafeMethods.StaticGetType()(_args);
             return new EngineTypeInfo(_engineResult);
        }


        /// <value>
        /// <description>
        /// The name of the data field referencing the object to be attached to the path.
        /// </description>
        /// </value>
        public string Reference {
            get => GenericMarshal.StringTo<string>(GetFieldValue("Reference"));
            set => SetFieldValue("Reference", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// The orientation mode of the object attached to the path.
        /// </description>
        /// </value>
        public string OrientationMode {
            get => GenericMarshal.StringTo<string>(GetFieldValue("OrientationMode"));
            set => SetFieldValue("OrientationMode", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// The name of the data field holding the orientation data (used for Orientation Modes, ToObject & ToPoint).
        /// </description>
        /// </value>
        public string OrientationData {
            get => GenericMarshal.StringTo<string>(GetFieldValue("OrientationData"));
            set => SetFieldValue("OrientationData", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Attach the object with an offset based on its initial position.
        /// </description>
        /// </value>
        public bool Relative {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("Relative"));
            set => SetFieldValue("Relative", GenericMarshal.ToString(value));
        }
    }
}