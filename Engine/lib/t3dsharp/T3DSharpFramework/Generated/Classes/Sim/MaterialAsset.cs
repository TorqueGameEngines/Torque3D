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
    public unsafe class MaterialAsset : AssetBase {
        public MaterialAsset(bool pRegister = false) 
            : base(pRegister) {
        }
        
        public MaterialAsset(string pName, bool pRegister) 
            : this(false) {
            Name = pName;
            if (pRegister) {
                RegisterObject();
            }
        }
        
        public MaterialAsset(string pName) 
            : this(pName, false) {
        }
        
        public MaterialAsset(string pName, string pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(Engine.Sim.FindObject<SimObject>(pParent));
        }
        
        public MaterialAsset(string pName, SimObject pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(pParent);
        }
        
        public MaterialAsset(SimObject pObj) 
            : base(pObj) {
        }
        
        public MaterialAsset(IntPtr pObj) 
            : base(pObj) {
        }
        
		protected override void CreateObjectPtr()
		{
			ObjectPtr = InternalUnsafeMethods.Create()(new InternalUnsafeMethods.Create__Args());
		}

        #region UnsafeNativeMethods
        new internal struct InternalUnsafeMethods {
            [StructLayout(LayoutKind.Sequential)]
            internal struct CompileShader__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _CompileShader(IntPtr _this, CompileShader__Args args);
            private static _CompileShader _CompileShaderFunc;
            internal static _CompileShader CompileShader() {
                if (_CompileShaderFunc == null) {
                    _CompileShaderFunc =
                        (_CompileShader)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnMaterialAsset_compileShader"), typeof(_CompileShader));
                }
                
                return _CompileShaderFunc;
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
                                "fnMaterialAsset_staticGetType"), typeof(_StaticGetType));
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
                                "fnMaterialAsset_create"), typeof(_Create));
                }
                
                return _CreateFunc;
            }
        }
        #endregion

        /// <description>
        /// Compiles the material's generated shader, if any. Not yet implemented
        /// </description>
        public void CompileShader() {
             InternalUnsafeMethods.CompileShader__Args _args = new InternalUnsafeMethods.CompileShader__Args() {
             };
             InternalUnsafeMethods.CompileShader()(ObjectPtr, _args);
        }

        /// <description>
        /// Get the type info object for the MaterialAsset class.
        /// </description>
        /// <returns>The type info object for MaterialAsset</returns>
        public static EngineTypeInfo StaticGetType() {
             InternalUnsafeMethods.StaticGetType__Args _args = new InternalUnsafeMethods.StaticGetType__Args() {
             };
             IntPtr _engineResult = InternalUnsafeMethods.StaticGetType()(_args);
             return new EngineTypeInfo(_engineResult);
        }


        /// <value>
        /// <description>
        /// Path to the file containing the material definition.
        /// </description>
        /// </value>
        public string ScriptFile {
            get => GenericMarshal.StringTo<string>(GetFieldValue("scriptFile"));
            set => SetFieldValue("scriptFile", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Name of the material definition this asset is for.
        /// </description>
        /// </value>
        public string MaterialDefinitionName {
            get => GenericMarshal.StringTo<string>(GetFieldValue("materialDefinitionName"));
            set => SetFieldValue("materialDefinitionName", GenericMarshal.ToString(value));
        }
    }
}