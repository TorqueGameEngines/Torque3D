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
    /// <summary>A gui control that is used to display an image.</summary>
    /// <description>
    /// The image is stretched to the constraints of the control by default. However, the control can also
    /// tile the image as well.
    /// 
    /// The image itself is stored inside the GuiBitmapCtrl::bitmap field. The boolean value that decides
    /// whether the image is stretched or tiled is stored inside the GuiBitmapCtrl::wrap field.
    /// </description>
    /// <code>
    /// // Create a tiling GuiBitmapCtrl that displays "myImage.png"
    /// %bitmapCtrl = new GuiBitmapCtrl()
    /// {
    ///    bitmap = "myImage.png";
    ///    wrap = "true";
    /// };
    /// </code>
    public unsafe class GuiBitmapCtrl : GuiControl {
        public GuiBitmapCtrl(bool pRegister = false) 
            : base(pRegister) {
        }
        
        public GuiBitmapCtrl(string pName, bool pRegister) 
            : this(false) {
            Name = pName;
            if (pRegister) {
                RegisterObject();
            }
        }
        
        public GuiBitmapCtrl(string pName) 
            : this(pName, false) {
        }
        
        public GuiBitmapCtrl(string pName, string pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(Engine.Sim.FindObject<SimObject>(pParent));
        }
        
        public GuiBitmapCtrl(string pName, SimObject pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(pParent);
        }
        
        public GuiBitmapCtrl(SimObject pObj) 
            : base(pObj) {
        }
        
        public GuiBitmapCtrl(IntPtr pObj) 
            : base(pObj) {
        }
        
		protected override void CreateObjectPtr()
		{
			ObjectPtr = InternalUnsafeMethods.Create()(new InternalUnsafeMethods.Create__Args());
		}

        #region UnsafeNativeMethods
        new internal struct InternalUnsafeMethods {
            [StructLayout(LayoutKind.Sequential)]
            internal struct SetNamedTexture__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string namedtexture;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            [return: MarshalAs(UnmanagedType.I1)]
            internal delegate bool _SetNamedTexture(IntPtr _this, SetNamedTexture__Args args);
            private static _SetNamedTexture _SetNamedTextureFunc;
            internal static _SetNamedTexture SetNamedTexture() {
                if (_SetNamedTextureFunc == null) {
                    _SetNamedTextureFunc =
                        (_SetNamedTexture)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnGuiBitmapCtrl_setNamedTexture"), typeof(_SetNamedTexture));
                }
                
                return _SetNamedTextureFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct SetBitmap__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string fileRoot;
                [MarshalAs(UnmanagedType.I1)]
                internal bool resize;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _SetBitmap(IntPtr _this, SetBitmap__Args args);
            private static _SetBitmap _SetBitmapFunc;
            internal static _SetBitmap SetBitmap() {
                if (_SetBitmapFunc == null) {
                    _SetBitmapFunc =
                        (_SetBitmap)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnGuiBitmapCtrl_setBitmap"), typeof(_SetBitmap));
                }
                
                return _SetBitmapFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct SetValue__Args
            {
                internal int x;
                internal int y;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _SetValue(IntPtr _this, SetValue__Args args);
            private static _SetValue _SetValueFunc;
            internal static _SetValue SetValue() {
                if (_SetValueFunc == null) {
                    _SetValueFunc =
                        (_SetValue)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnGuiBitmapCtrl_setValue"), typeof(_SetValue));
                }
                
                return _SetValueFunc;
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
                                "fnGuiBitmapCtrl_staticGetType"), typeof(_StaticGetType));
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
                                "fnGuiBitmapCtrl_create"), typeof(_Create));
                }
                
                return _CreateFunc;
            }
        }
        #endregion

        /// <summary>Set a texture as the image.</summary>
        /// <description>
        /// 
        /// </description>
        /// <param name="namedtexture">The name of the texture (NamedTexTarget).</param>
        /// <returns>true if the texture exists.</returns>
        public bool SetNamedTexture(string namedtexture) {
             InternalUnsafeMethods.SetNamedTexture__Args _args = new InternalUnsafeMethods.SetNamedTexture__Args() {
                namedtexture = namedtexture,
             };
             bool _engineResult = InternalUnsafeMethods.SetNamedTexture()(ObjectPtr, _args);
             return _engineResult;
        }

        /// <description>
        /// ( String filename | String filename, bool resize ) Assign an image to the control.
        /// </description>
        public void SetBitmap(string fileRoot, bool resize = false) {
             InternalUnsafeMethods.SetBitmap__Args _args = new InternalUnsafeMethods.SetBitmap__Args() {
                fileRoot = fileRoot,
                resize = resize,
             };
             InternalUnsafeMethods.SetBitmap()(ObjectPtr, _args);
        }

        /// <description>
        /// Set the offset of the bitmap within the control.
        /// </description>
        /// <param name="x">The x-axis offset of the image.</param>
        /// <param name="y">The y-axis offset of the image.</param>
        public void SetValue(int x, int y) {
             InternalUnsafeMethods.SetValue__Args _args = new InternalUnsafeMethods.SetValue__Args() {
                x = x,
                y = y,
             };
             InternalUnsafeMethods.SetValue()(ObjectPtr, _args);
        }

        /// <description>
        /// Get the type info object for the GuiBitmapCtrl class.
        /// </description>
        /// <returns>The type info object for GuiBitmapCtrl</returns>
        public static EngineTypeInfo StaticGetType() {
             InternalUnsafeMethods.StaticGetType__Args _args = new InternalUnsafeMethods.StaticGetType__Args() {
             };
             IntPtr _engineResult = InternalUnsafeMethods.StaticGetType()(_args);
             return new EngineTypeInfo(_engineResult);
        }


        /// <value>
        /// <description>
        /// The bitmap file to display in the control.
        /// </description>
        /// </value>
        public string Bitmap {
            get => GenericMarshal.StringTo<string>(GetFieldValue("bitmap"));
            set => SetFieldValue("bitmap", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// color mul
        /// </description>
        /// </value>
        public ColorI Color {
            get => GenericMarshal.StringTo<ColorI>(GetFieldValue("color"));
            set => SetFieldValue("color", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// If true, the bitmap is tiled inside the control rather than stretched to fit.
        /// </description>
        /// </value>
        public bool Wrap {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("wrap"));
            set => SetFieldValue("wrap", GenericMarshal.ToString(value));
        }
    }
}