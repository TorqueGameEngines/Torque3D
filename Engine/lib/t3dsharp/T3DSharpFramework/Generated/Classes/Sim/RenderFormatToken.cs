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
    /// <summary>Used to change the render target format when rendering in AL.</summary>
    /// <description>
    /// RenderFormatToken is an implementation which changes the format of the back buffer and/or the depth buffer.
    /// 
    /// The RenderPassStateBin manager changes the rendering state associated with this token. In stock Torque 3D, a single example exists in the way of AL_FormatToken (found in renderManager.cs). In that script file, all the render managers are intialized, and a single RenderFormatToken is used. This implementation basically exists to ensure Advanced Lighting works with MSAA.
    /// 
    /// The actions for this token toggle the format of the back/depth buffers and it lets you specify a custom shader to "copy" the data so it can be reformatted or altered. This is done through the variables copyEffect and resolveEffect (which are post processes just like fog or glow)
    /// </description>
    /// <code>
    /// // This token, and the associated render managers, ensure that driver MSAA does not get used for Advanced Lighting renders.
    /// // The 'AL_FormatResolve' PostEffect copies the result to the backbuffer.
    /// new RenderFormatToken(AL_FormatToken)
    /// {
    ///    enabled = "false";
    /// 
    ///    format = "GFXFormatR8G8B8A8";
    ///    depthFormat = "GFXFormatD24S8";
    ///    aaLevel = 0; // -1 = match backbuffer
    /// 
    ///    // The contents of the back buffer before this format token is executed
    ///    // is provided in $inTex
    ///    copyEffect = "AL_FormatCopy";
    /// 
    ///    // The contents of the render target created by this format token is
    ///    // provided in $inTex
    ///    resolveEffect = "AL_FormatCopy";
    /// };
    /// </code>
    /// <see cref="RenderPassToken" />
    /// <see cref="RenderPassStateBin" />
    /// <see cref="game/core/scripts/client/renderManager.cs" />
    public unsafe class RenderFormatToken : RenderPassStateToken {
        public RenderFormatToken(bool pRegister = false) 
            : base(pRegister) {
        }
        
        public RenderFormatToken(string pName, bool pRegister) 
            : this(false) {
            Name = pName;
            if (pRegister) {
                RegisterObject();
            }
        }
        
        public RenderFormatToken(string pName) 
            : this(pName, false) {
        }
        
        public RenderFormatToken(string pName, string pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(Engine.Sim.FindObject<SimObject>(pParent));
        }
        
        public RenderFormatToken(string pName, SimObject pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(pParent);
        }
        
        public RenderFormatToken(SimObject pObj) 
            : base(pObj) {
        }
        
        public RenderFormatToken(IntPtr pObj) 
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
                                "fnRenderFormatToken_staticGetType"), typeof(_StaticGetType));
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
                                "fnRenderFormatToken_create"), typeof(_Create));
                }
                
                return _CreateFunc;
            }
        }
        #endregion

        /// <description>
        /// Get the type info object for the RenderFormatToken class.
        /// </description>
        /// <returns>The type info object for RenderFormatToken</returns>
        public static EngineTypeInfo StaticGetType() {
             InternalUnsafeMethods.StaticGetType__Args _args = new InternalUnsafeMethods.StaticGetType__Args() {
             };
             IntPtr _engineResult = InternalUnsafeMethods.StaticGetType()(_args);
             return new EngineTypeInfo(_engineResult);
        }


        /// <value>
        /// <description>
        /// Sets the color buffer format for this token.
        /// </description>
        /// </value>
        public GFXFormat Format {
            get => GenericMarshal.StringTo<GFXFormat>(GetFieldValue("Format"));
            set => SetFieldValue("Format", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Sets the depth/stencil buffer format for this token.
        /// </description>
        /// </value>
        public GFXFormat DepthFormat {
            get => GenericMarshal.StringTo<GFXFormat>(GetFieldValue("depthFormat"));
            set => SetFieldValue("depthFormat", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// This PostEffect will be run when the render target is changed to the format specified by this token. It is used to copy/format data into the token rendertarget
        /// </description>
        /// </value>
        public PostEffect CopyEffect {
            get => GenericMarshal.StringTo<PostEffect>(GetFieldValue("copyEffect"));
            set => SetFieldValue("copyEffect", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// This PostEffect will be run when the render target is changed back to the format active prior to this token. It is used to copy/format data from the token rendertarget to the backbuffer.
        /// </description>
        /// </value>
        public PostEffect ResolveEffect {
            get => GenericMarshal.StringTo<PostEffect>(GetFieldValue("resolveEffect"));
            set => SetFieldValue("resolveEffect", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Anti-ailiasing level for the this token. 0 disables, -1 uses adapter default.
        /// </description>
        /// </value>
        public int AaLevel {
            get => GenericMarshal.StringTo<int>(GetFieldValue("aaLevel"));
            set => SetFieldValue("aaLevel", GenericMarshal.ToString(value));
        }
    }
}