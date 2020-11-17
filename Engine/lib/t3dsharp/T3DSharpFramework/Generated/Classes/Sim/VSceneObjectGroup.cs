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
    public unsafe class VSceneObjectGroup : VGroup {
        public VSceneObjectGroup(bool pRegister = false) 
            : base(pRegister) {
        }
        
        public VSceneObjectGroup(string pName, bool pRegister) 
            : this(false) {
            Name = pName;
            if (pRegister) {
                RegisterObject();
            }
        }
        
        public VSceneObjectGroup(string pName) 
            : this(pName, false) {
        }
        
        public VSceneObjectGroup(string pName, string pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(Engine.Sim.FindObject<SimObject>(pParent));
        }
        
        public VSceneObjectGroup(string pName, SimObject pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(pParent);
        }
        
        public VSceneObjectGroup(SimObject pObj) 
            : base(pObj) {
        }
        
        public VSceneObjectGroup(IntPtr pObj) 
            : base(pObj) {
        }
        
		protected override void CreateObjectPtr()
		{
			ObjectPtr = InternalUnsafeMethods.Create()(new InternalUnsafeMethods.Create__Args());
		}

        #region UnsafeNativeMethods
        new internal struct InternalUnsafeMethods {
            [StructLayout(LayoutKind.Sequential)]
            internal struct GetSceneObject__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate int _GetSceneObject(IntPtr _this, GetSceneObject__Args args);
            private static _GetSceneObject _GetSceneObjectFunc;
            internal static _GetSceneObject GetSceneObject() {
                if (_GetSceneObjectFunc == null) {
                    _GetSceneObjectFunc =
                        (_GetSceneObject)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnVSceneObjectGroup_getSceneObject"), typeof(_GetSceneObject));
                }
                
                return _GetSceneObjectFunc;
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
                                "fnVSceneObjectGroup_staticGetType"), typeof(_StaticGetType));
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
                                "fnVSceneObjectGroup_create"), typeof(_Create));
                }
                
                return _CreateFunc;
            }
        }
        #endregion

        /// <description>
        /// ( void ) - Get the object this group references.
        /// </description>
        /// <returns>Returns the SimObjectID for the object.</returns>
        public int GetSceneObject() {
             InternalUnsafeMethods.GetSceneObject__Args _args = new InternalUnsafeMethods.GetSceneObject__Args() {
             };
             int _engineResult = InternalUnsafeMethods.GetSceneObject()(ObjectPtr, _args);
             return _engineResult;
        }

        /// <description>
        /// Get the type info object for the VSceneObjectGroup class.
        /// </description>
        /// <returns>The type info object for VSceneObjectGroup</returns>
        public static EngineTypeInfo StaticGetType() {
             InternalUnsafeMethods.StaticGetType__Args _args = new InternalUnsafeMethods.StaticGetType__Args() {
             };
             IntPtr _engineResult = InternalUnsafeMethods.StaticGetType()(_args);
             return new EngineTypeInfo(_engineResult);
        }


        /// <value>
        /// <description>
        /// The name of the data field referencing the targeted object.
        /// </description>
        /// </value>
        public string Reference {
            get => GenericMarshal.StringTo<string>(GetFieldValue("Reference"));
            set => SetFieldValue("Reference", GenericMarshal.ToString(value));
        }
    }
}