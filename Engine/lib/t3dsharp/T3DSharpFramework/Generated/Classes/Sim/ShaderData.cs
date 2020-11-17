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
    /// <summary>Special type of data block that stores information about a handwritten shader.</summary>
    /// <description>
    /// To use hand written shaders, a ShaderData datablock must be used. This datablock refers only to the vertex and pixel shader filenames and a hardware target level. Shaders are API specific, so DirectX and OpenGL shaders must be explicitly identified.
    /// </description>
    /// <code>
    /// // Used for the procedural clould system
    /// singleton ShaderData( CloudLayerShader )
    /// {
    /// 	DXVertexShaderFile   = $Core::CommonShaderPath@ "/cloudLayerV.hlsl";
    /// 	DXPixelShaderFile    = $Core::CommonShaderPath 
    /// </code>
    public unsafe class ShaderData : SimObject {
        public ShaderData(bool pRegister = false) 
            : base(pRegister) {
        }
        
        public ShaderData(string pName, bool pRegister) 
            : this(false) {
            Name = pName;
            if (pRegister) {
                RegisterObject();
            }
        }
        
        public ShaderData(string pName) 
            : this(pName, false) {
        }
        
        public ShaderData(string pName, string pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(Engine.Sim.FindObject<SimObject>(pParent));
        }
        
        public ShaderData(string pName, SimObject pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(pParent);
        }
        
        public ShaderData(SimObject pObj) 
            : base(pObj) {
        }
        
        public ShaderData(IntPtr pObj) 
            : base(pObj) {
        }
        
		protected override void CreateObjectPtr()
		{
			ObjectPtr = InternalUnsafeMethods.Create()(new InternalUnsafeMethods.Create__Args());
		}

        #region UnsafeNativeMethods
        new internal struct InternalUnsafeMethods {
            [StructLayout(LayoutKind.Sequential)]
            internal struct Reload__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _Reload(IntPtr _this, Reload__Args args);
            private static _Reload _ReloadFunc;
            internal static _Reload Reload() {
                if (_ReloadFunc == null) {
                    _ReloadFunc =
                        (_Reload)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnShaderData_reload"), typeof(_Reload));
                }
                
                return _ReloadFunc;
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
                                "fnShaderData_staticGetType"), typeof(_StaticGetType));
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
                                "fnShaderData_create"), typeof(_Create));
                }
                
                return _CreateFunc;
            }
        }
        #endregion

        /// <summary>Rebuilds all the vertex and pixel shader instances created from this ShaderData.</summary>
        /// <description>
        /// 
        /// </description>
        /// <code>
        /// // Rebuild the shader instances from ShaderData CloudLayerShader
        /// CloudLayerShader.reload();
        /// </code>
        public void Reload() {
             InternalUnsafeMethods.Reload__Args _args = new InternalUnsafeMethods.Reload__Args() {
             };
             InternalUnsafeMethods.Reload()(ObjectPtr, _args);
        }

        /// <description>
        /// Get the type info object for the ShaderData class.
        /// </description>
        /// <returns>The type info object for ShaderData</returns>
        public static EngineTypeInfo StaticGetType() {
             InternalUnsafeMethods.StaticGetType__Args _args = new InternalUnsafeMethods.StaticGetType__Args() {
             };
             IntPtr _engineResult = InternalUnsafeMethods.StaticGetType()(_args);
             return new EngineTypeInfo(_engineResult);
        }


        /// <value>
        /// <summary>%Path to the DirectX vertex shader file to use for this ShaderData.</summary>
        /// <description>
        /// It must contain only one program and no pixel shader, just the vertex shader.It can be either an HLSL or assembly level shader. HLSL's must have a filename extension of .hlsl, otherwise its assumed to be an assembly file.
        /// </description>
        /// </value>
        public string DXVertexShaderFile {
            get => GenericMarshal.StringTo<string>(GetFieldValue("DXVertexShaderFile"));
            set => SetFieldValue("DXVertexShaderFile", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <summary>%Path to the DirectX pixel shader file to use for this ShaderData.</summary>
        /// <description>
        /// It must contain only one program and no vertex shader, just the pixel shader. It can be either an HLSL or assembly level shader. HLSL's must have a filename extension of .hlsl, otherwise its assumed to be an assembly file.
        /// </description>
        /// </value>
        public string DXPixelShaderFile {
            get => GenericMarshal.StringTo<string>(GetFieldValue("DXPixelShaderFile"));
            set => SetFieldValue("DXPixelShaderFile", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <summary>%Path to an OpenGL vertex shader file to use for this ShaderData.</summary>
        /// <description>
        /// It must contain only one program and no pixel shader, just the vertex shader.
        /// </description>
        /// </value>
        public string OGLVertexShaderFile {
            get => GenericMarshal.StringTo<string>(GetFieldValue("OGLVertexShaderFile"));
            set => SetFieldValue("OGLVertexShaderFile", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <summary>%Path to an OpenGL pixel shader file to use for this ShaderData.</summary>
        /// <description>
        /// It must contain only one program and no vertex shader, just the pixel shader.
        /// </description>
        /// </value>
        public string OGLPixelShaderFile {
            get => GenericMarshal.StringTo<string>(GetFieldValue("OGLPixelShaderFile"));
            set => SetFieldValue("OGLPixelShaderFile", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <summary>If true, the maximum pixel shader version offered by the graphics card will be used.</summary>
        /// <description>
        /// Otherwise, the script-defined pixel shader version will be used.
        /// </description>
        /// </value>
        public bool UseDevicePixVersion {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("useDevicePixVersion"));
            set => SetFieldValue("useDevicePixVersion", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <summary>Indicates target level the shader should be compiled.</summary>
        /// <description>
        /// Valid numbers at the time of this writing are 1.1, 1.4, 2.0, and 3.0. The shader will not run properly if the hardware does not support the level of shader compiled.
        /// </description>
        /// </value>
        public float PixVersion {
            get => GenericMarshal.StringTo<float>(GetFieldValue("pixVersion"));
            set => SetFieldValue("pixVersion", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <summary>String of case-sensitive defines passed to the shader compiler.</summary>
        /// <description>
        /// The string should be delimited by a semicolon, tab, or newline character.
        /// </description>
        /// <code>
        /// singleton ShaderData( FlashShader )
        /// {
        /// DXVertexShaderFile 	= $shaderGen::cachePath@ "/postFx/flashV.hlsl";
        /// DXPixelShaderFile 	= $shaderGen::cachePath 
        /// </code>
        /// </value>
        public string Defines {
            get => GenericMarshal.StringTo<string>(GetFieldValue("defines"));
            set => SetFieldValue("defines", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <summary>Indicates names of samplers present in shader. Order is important.</summary>
        /// <description>
        /// Order of sampler names are used to assert correct sampler register/locationOther objects (GFXStateBlockData, PostEffect...) use index number to link samplers.
        /// </description>
        /// </value>
        public DynamicFieldVector<string> SamplerNames {
            get => new DynamicFieldVector<string>(
                    this, 
                    "samplerNames", 
                    8, 
                    val => GenericMarshal.StringTo<string>(val),
                    obj => GenericMarshal.ToString(obj)
                );
        }


        /// <value>
        /// 
        /// </value>
        public DynamicFieldVector<bool> RtParams {
            get => new DynamicFieldVector<bool>(
                    this, 
                    "rtParams", 
                    8, 
                    val => GenericMarshal.StringTo<bool>(val),
                    obj => GenericMarshal.ToString(obj)
                );
        }
    }
}