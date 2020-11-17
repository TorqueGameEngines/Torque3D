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
    public unsafe class VShapeAnimationTrack : VSceneObjectTrack {
        public VShapeAnimationTrack(bool pRegister = false) 
            : base(pRegister) {
        }
        
        public VShapeAnimationTrack(string pName, bool pRegister) 
            : this(false) {
            Name = pName;
            if (pRegister) {
                RegisterObject();
            }
        }
        
        public VShapeAnimationTrack(string pName) 
            : this(pName, false) {
        }
        
        public VShapeAnimationTrack(string pName, string pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(Engine.Sim.FindObject<SimObject>(pParent));
        }
        
        public VShapeAnimationTrack(string pName, SimObject pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(pParent);
        }
        
        public VShapeAnimationTrack(SimObject pObj) 
            : base(pObj) {
        }
        
        public VShapeAnimationTrack(IntPtr pObj) 
            : base(pObj) {
        }
        
		protected override void CreateObjectPtr()
		{
			ObjectPtr = InternalUnsafeMethods.Create()(new InternalUnsafeMethods.Create__Args());
		}

        #region UnsafeNativeMethods
        new internal struct InternalUnsafeMethods {
            [StructLayout(LayoutKind.Sequential)]
            internal struct UpdateTrack__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _UpdateTrack(IntPtr _this, UpdateTrack__Args args);
            private static _UpdateTrack _UpdateTrackFunc;
            internal static _UpdateTrack UpdateTrack() {
                if (_UpdateTrackFunc == null) {
                    _UpdateTrackFunc =
                        (_UpdateTrack)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnVShapeAnimationTrack_updateTrack"), typeof(_UpdateTrack));
                }
                
                return _UpdateTrackFunc;
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
                                "fnVShapeAnimationTrack_staticGetType"), typeof(_StaticGetType));
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
                                "fnVShapeAnimationTrack_create"), typeof(_Create));
                }
                
                return _CreateFunc;
            }
        }
        #endregion

        /// <description>
        /// ( void ) - Update the Track.
        /// </description>
        /// <returns>No return value.</returns>
        public void UpdateTrack() {
             InternalUnsafeMethods.UpdateTrack__Args _args = new InternalUnsafeMethods.UpdateTrack__Args() {
             };
             InternalUnsafeMethods.UpdateTrack()(ObjectPtr, _args);
        }

        /// <description>
        /// Get the type info object for the VShapeAnimationTrack class.
        /// </description>
        /// <returns>The type info object for VShapeAnimationTrack</returns>
        public static EngineTypeInfo StaticGetType() {
             InternalUnsafeMethods.StaticGetType__Args _args = new InternalUnsafeMethods.StaticGetType__Args() {
             };
             IntPtr _engineResult = InternalUnsafeMethods.StaticGetType()(_args);
             return new EngineTypeInfo(_engineResult);
        }


        /// <value>
        /// <description>
        /// The index of the Animation Thread to play.
        /// </description>
        /// </value>
        public int ThreadIndex {
            get => GenericMarshal.StringTo<int>(GetFieldValue("ThreadIndex"));
            set => SetFieldValue("ThreadIndex", GenericMarshal.ToString(value));
        }
    }
}