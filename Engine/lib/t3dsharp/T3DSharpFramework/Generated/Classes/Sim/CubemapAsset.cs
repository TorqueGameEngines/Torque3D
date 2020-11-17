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
    public unsafe class CubemapAsset : AssetBase {
        public CubemapAsset(bool pRegister = false) 
            : base(pRegister) {
        }
        
        public CubemapAsset(string pName, bool pRegister) 
            : this(false) {
            Name = pName;
            if (pRegister) {
                RegisterObject();
            }
        }
        
        public CubemapAsset(string pName) 
            : this(pName, false) {
        }
        
        public CubemapAsset(string pName, string pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(Engine.Sim.FindObject<SimObject>(pParent));
        }
        
        public CubemapAsset(string pName, SimObject pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(pParent);
        }
        
        public CubemapAsset(SimObject pObj) 
            : base(pObj) {
        }
        
        public CubemapAsset(IntPtr pObj) 
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
                                "fnCubemapAsset_staticGetType"), typeof(_StaticGetType));
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
                                "fnCubemapAsset_create"), typeof(_Create));
                }
                
                return _CreateFunc;
            }
        }
        #endregion

        /// <description>
        /// Get the type info object for the CubemapAsset class.
        /// </description>
        /// <returns>The type info object for CubemapAsset</returns>
        public static EngineTypeInfo StaticGetType() {
             InternalUnsafeMethods.StaticGetType__Args _args = new InternalUnsafeMethods.StaticGetType__Args() {
             };
             IntPtr _engineResult = InternalUnsafeMethods.StaticGetType()(_args);
             return new EngineTypeInfo(_engineResult);
        }


        /// <value>
        /// <description>
        /// Unique Name of the component. Defines the namespace of the scripts for the component.
        /// </description>
        /// </value>
        public string ComponentName {
            get => GenericMarshal.StringTo<string>(GetFieldValue("componentName"));
            set => SetFieldValue("componentName", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Class of object this component uses.
        /// </description>
        /// </value>
        public string ComponentClass {
            get => GenericMarshal.StringTo<string>(GetFieldValue("componentClass"));
            set => SetFieldValue("componentClass", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// The human-readble name for the component.
        /// </description>
        /// </value>
        public string FriendlyName {
            get => GenericMarshal.StringTo<string>(GetFieldValue("friendlyName"));
            set => SetFieldValue("friendlyName", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// The category of the component for organizing in the editor.
        /// </description>
        /// </value>
        public string ComponentType {
            get => GenericMarshal.StringTo<string>(GetFieldValue("componentType"));
            set => SetFieldValue("componentType", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Simple description of the component.
        /// </description>
        /// </value>
        public string Description {
            get => GenericMarshal.StringTo<string>(GetFieldValue("description"));
            set => SetFieldValue("description", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// A script file with additional scripted functionality for this component.
        /// </description>
        /// </value>
        public string ScriptFile {
            get => GenericMarshal.StringTo<string>(GetFieldValue("scriptFile"));
            set => SetFieldValue("scriptFile", GenericMarshal.ToString(value));
        }
    }
}