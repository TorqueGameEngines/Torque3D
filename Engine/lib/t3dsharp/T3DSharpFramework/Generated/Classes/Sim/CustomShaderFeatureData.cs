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
    /// <summary>A Shader Feature with custom definitions.</summary>
    /// <description>
    /// This class allows for the creation and implementation of a ShaderGen ShaderFeature Implemented either engine side or script, and facilitates passing along of per-instance ShaderData.
    /// </description>
    public unsafe class CustomShaderFeatureData : SimObject {
        public CustomShaderFeatureData(bool pRegister = false) 
            : base(pRegister) {
        }
        
        public CustomShaderFeatureData(string pName, bool pRegister) 
            : this(false) {
            Name = pName;
            if (pRegister) {
                RegisterObject();
            }
        }
        
        public CustomShaderFeatureData(string pName) 
            : this(pName, false) {
        }
        
        public CustomShaderFeatureData(string pName, string pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(Engine.Sim.FindObject<SimObject>(pParent));
        }
        
        public CustomShaderFeatureData(string pName, SimObject pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(pParent);
        }
        
        public CustomShaderFeatureData(SimObject pObj) 
            : base(pObj) {
        }
        
        public CustomShaderFeatureData(IntPtr pObj) 
            : base(pObj) {
        }
        
		protected override void CreateObjectPtr()
		{
			ObjectPtr = InternalUnsafeMethods.Create()(new InternalUnsafeMethods.Create__Args());
		}

        #region UnsafeNativeMethods
        new internal struct InternalUnsafeMethods {
            [StructLayout(LayoutKind.Sequential)]
            internal struct HasFeature__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string name;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            [return: MarshalAs(UnmanagedType.I1)]
            internal delegate bool _HasFeature(IntPtr _this, HasFeature__Args args);
            private static _HasFeature _HasFeatureFunc;
            internal static _HasFeature HasFeature() {
                if (_HasFeatureFunc == null) {
                    _HasFeatureFunc =
                        (_HasFeature)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnCustomShaderFeatureData_hasFeature"), typeof(_HasFeature));
                }
                
                return _HasFeatureFunc;
            }


            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _WriteLine(IntPtr _this, ref StringVector.InternalStruct args);
            private static _WriteLine _WriteLineFunc;
            internal static _WriteLine WriteLine() {
                if (_WriteLineFunc == null) {
                    _WriteLineFunc =
                        (_WriteLine)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnCustomShaderFeatureData_writeLine"), typeof(_WriteLine));
                }
                
                return _WriteLineFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct AddVertTexCoord__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string name;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _AddVertTexCoord(IntPtr _this, AddVertTexCoord__Args args);
            private static _AddVertTexCoord _AddVertTexCoordFunc;
            internal static _AddVertTexCoord AddVertTexCoord() {
                if (_AddVertTexCoordFunc == null) {
                    _AddVertTexCoordFunc =
                        (_AddVertTexCoord)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnCustomShaderFeatureData_addVertTexCoord"), typeof(_AddVertTexCoord));
                }
                
                return _AddVertTexCoordFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct AddConnector__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string name;
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string type;
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string elementName;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _AddConnector(IntPtr _this, AddConnector__Args args);
            private static _AddConnector _AddConnectorFunc;
            internal static _AddConnector AddConnector() {
                if (_AddConnectorFunc == null) {
                    _AddConnectorFunc =
                        (_AddConnector)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnCustomShaderFeatureData_addConnector"), typeof(_AddConnector));
                }
                
                return _AddConnectorFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct AddTexture__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string name;
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string type;
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string samplerState;
                internal uint arraySize;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _AddTexture(IntPtr _this, AddTexture__Args args);
            private static _AddTexture _AddTextureFunc;
            internal static _AddTexture AddTexture() {
                if (_AddTextureFunc == null) {
                    _AddTextureFunc =
                        (_AddTexture)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnCustomShaderFeatureData_addTexture"), typeof(_AddTexture));
                }
                
                return _AddTextureFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct AddSampler__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string name;
                internal uint arraySize;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _AddSampler(IntPtr _this, AddSampler__Args args);
            private static _AddSampler _AddSamplerFunc;
            internal static _AddSampler AddSampler() {
                if (_AddSamplerFunc == null) {
                    _AddSamplerFunc =
                        (_AddSampler)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnCustomShaderFeatureData_addSampler"), typeof(_AddSampler));
                }
                
                return _AddSamplerFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct AddUniform__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string name;
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string type;
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string defaultValue;
                internal uint arraySize;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _AddUniform(IntPtr _this, AddUniform__Args args);
            private static _AddUniform _AddUniformFunc;
            internal static _AddUniform AddUniform() {
                if (_AddUniformFunc == null) {
                    _AddUniformFunc =
                        (_AddUniform)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnCustomShaderFeatureData_addUniform"), typeof(_AddUniform));
                }
                
                return _AddUniformFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct AddVariable__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string name;
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string type;
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string defaultValue;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _AddVariable(IntPtr _this, AddVariable__Args args);
            private static _AddVariable _AddVariableFunc;
            internal static _AddVariable AddVariable() {
                if (_AddVariableFunc == null) {
                    _AddVariableFunc =
                        (_AddVariable)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnCustomShaderFeatureData_addVariable"), typeof(_AddVariable));
                }
                
                return _AddVariableFunc;
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
                                "fnCustomShaderFeatureData_staticGetType"), typeof(_StaticGetType));
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
                                "fnCustomShaderFeatureData_create"), typeof(_Create));
                }
                
                return _CreateFunc;
            }
        }
        #endregion

        /// 
        public bool HasFeature(string name = "") {
             InternalUnsafeMethods.HasFeature__Args _args = new InternalUnsafeMethods.HasFeature__Args() {
                name = name,
             };
             bool _engineResult = InternalUnsafeMethods.HasFeature()(ObjectPtr, _args);
             return _engineResult;
        }

        /// <description>
        /// ( string format, string args... ) Dynamically call a method on an object.
        /// </description>
        /// <param name="method">Name of method to call.</param>
        /// <param name="args">Zero or more arguments for the method.</param>
        /// <returns>The result of the method call.</returns>
        public void WriteLine(params string[] args) { 
            List<string> _argList = new List<string>() {"", ""};
            _argList.AddRange(args);

            StringVector nativeVecArgs = new StringVector {
                ElementCount = (uint)_argList.Count,
                Array = _argList.ToArray(),
                ArraySize = (uint)_argList.Count
            };
            nativeVecArgs.Alloc();
            InternalUnsafeMethods.WriteLine()(ObjectPtr, ref nativeVecArgs.internalStruct);
            nativeVecArgs.Free();

        }

        /// 
        public void AddVertTexCoord(string name = "") {
             InternalUnsafeMethods.AddVertTexCoord__Args _args = new InternalUnsafeMethods.AddVertTexCoord__Args() {
                name = name,
             };
             InternalUnsafeMethods.AddVertTexCoord()(ObjectPtr, _args);
        }

        /// 
        public void AddConnector(string name = "", string type = "", string elementName = "") {
             InternalUnsafeMethods.AddConnector__Args _args = new InternalUnsafeMethods.AddConnector__Args() {
                name = name,
                type = type,
                elementName = elementName,
             };
             InternalUnsafeMethods.AddConnector()(ObjectPtr, _args);
        }

        /// 
        public void AddTexture(string name, string type = "", string samplerState = "", uint arraySize = 0) {
             InternalUnsafeMethods.AddTexture__Args _args = new InternalUnsafeMethods.AddTexture__Args() {
                name = name,
                type = type,
                samplerState = samplerState,
                arraySize = arraySize,
             };
             InternalUnsafeMethods.AddTexture()(ObjectPtr, _args);
        }

        /// 
        public void AddSampler(string name = "", uint arraySize = 0) {
             InternalUnsafeMethods.AddSampler__Args _args = new InternalUnsafeMethods.AddSampler__Args() {
                name = name,
                arraySize = arraySize,
             };
             InternalUnsafeMethods.AddSampler()(ObjectPtr, _args);
        }

        /// 
        public void AddUniform(string name = "", string type = "", string defaultValue = "", uint arraySize = 0) {
             InternalUnsafeMethods.AddUniform__Args _args = new InternalUnsafeMethods.AddUniform__Args() {
                name = name,
                type = type,
                defaultValue = defaultValue,
                arraySize = arraySize,
             };
             InternalUnsafeMethods.AddUniform()(ObjectPtr, _args);
        }

        /// 
        public void AddVariable(string name = "", string type = "", string defaultValue = "") {
             InternalUnsafeMethods.AddVariable__Args _args = new InternalUnsafeMethods.AddVariable__Args() {
                name = name,
                type = type,
                defaultValue = defaultValue,
             };
             InternalUnsafeMethods.AddVariable()(ObjectPtr, _args);
        }

        /// <description>
        /// Get the type info object for the CustomShaderFeatureData class.
        /// </description>
        /// <returns>The type info object for CustomShaderFeatureData</returns>
        public static EngineTypeInfo StaticGetType() {
             InternalUnsafeMethods.StaticGetType__Args _args = new InternalUnsafeMethods.StaticGetType__Args() {
             };
             IntPtr _engineResult = InternalUnsafeMethods.StaticGetType()(_args);
             return new EngineTypeInfo(_engineResult);
        }
    }
}