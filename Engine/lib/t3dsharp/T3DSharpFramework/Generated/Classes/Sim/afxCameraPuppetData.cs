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
    /// <summary>A datablock that specifies a Camera Puppet effect.</summary>
    /// <description>
    /// A Camera Puppet effect is used to control the position and orientation of the camera using the AFX constraint system. Camera Puppet effects are useful for creating small cut-scenes and can add a lot of visual drama to a spell or effectron effect.
    /// 
    /// Effective use of Camera Puppet effects require a fairly advanced understanding of how Torque cameras work in a server-client context. Care must be taken to prevent client cameras from drifting too far out of sync from the server camera. Otherwise, obvious discontinuities in the motion will result when the Camera Puppet ends and control is restored to the server camera. Scoping problems can also result if a client camera is moved to a location that is inconsistent with the scene scoping done by the server camera.
    /// 
    /// Often it is useful to manage camera controlling in an isolated effectron rather than directly incorporated into a magic-spell. This way the camera controlling effectron can target the specific client associated with the spellcaster. The spellcasting player observes the spell in a dramatic cut-scene-like fashion while other players continue to observe from their own viewing locations.
    /// </description>
    public unsafe class afxCameraPuppetData : GameBaseData {
        public afxCameraPuppetData(bool pRegister = false) 
            : base(pRegister) {
        }
        
        public afxCameraPuppetData(string pName, bool pRegister) 
            : this(false) {
            Name = pName;
            if (pRegister) {
                RegisterObject();
            }
        }
        
        public afxCameraPuppetData(string pName) 
            : this(pName, false) {
        }
        
        public afxCameraPuppetData(string pName, string pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(Engine.Sim.FindObject<SimObject>(pParent));
        }
        
        public afxCameraPuppetData(string pName, SimObject pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(pParent);
        }
        
        public afxCameraPuppetData(SimObject pObj) 
            : base(pObj) {
        }
        
        public afxCameraPuppetData(IntPtr pObj) 
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
                                "fnafxCameraPuppetData_staticGetType"), typeof(_StaticGetType));
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
                                "fnafxCameraPuppetData_create"), typeof(_Create));
                }
                
                return _CreateFunc;
            }
        }
        #endregion

        /// <description>
        /// Get the type info object for the afxCameraPuppetData class.
        /// </description>
        /// <returns>The type info object for afxCameraPuppetData</returns>
        public static EngineTypeInfo StaticGetType() {
             InternalUnsafeMethods.StaticGetType__Args _args = new InternalUnsafeMethods.StaticGetType__Args() {
             };
             IntPtr _engineResult = InternalUnsafeMethods.StaticGetType()(_args);
             return new EngineTypeInfo(_engineResult);
        }


        /// <value>
        /// <description>
        /// This field is like the effect-wrapper fields for specifying constraint sources, but here it specifies a target for the camera-puppet effect.
        /// </description>
        /// </value>
        public string CameraSpec {
            get => GenericMarshal.StringTo<string>(GetFieldValue("cameraSpec"));
            set => SetFieldValue("cameraSpec", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Specifies the networking model used for the camerapuppet effect. The effect can puppet just the server camera, just the client camera, or both.
        /// Possible values: $AFX::SERVER_ONLY, $AFX::CLIENT_ONLY, or $AFX::SERVER_AND_CLIENT.
        /// </description>
        /// </value>
        public sbyte Networking {
            get => GenericMarshal.StringTo<sbyte>(GetFieldValue("networking"));
            set => SetFieldValue("networking", GenericMarshal.ToString(value));
        }
    }
}