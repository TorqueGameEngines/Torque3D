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
    public unsafe class guiAnimBitmapCtrl : GuiBitmapCtrl {
        public guiAnimBitmapCtrl(bool pRegister = false) 
            : base(pRegister) {
        }
        
        public guiAnimBitmapCtrl(string pName, bool pRegister) 
            : this(false) {
            Name = pName;
            if (pRegister) {
                RegisterObject();
            }
        }
        
        public guiAnimBitmapCtrl(string pName) 
            : this(pName, false) {
        }
        
        public guiAnimBitmapCtrl(string pName, string pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(Engine.Sim.FindObject<SimObject>(pParent));
        }
        
        public guiAnimBitmapCtrl(string pName, SimObject pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(pParent);
        }
        
        public guiAnimBitmapCtrl(SimObject pObj) 
            : base(pObj) {
        }
        
        public guiAnimBitmapCtrl(IntPtr pObj) 
            : base(pObj) {
        }
        
		protected override void CreateObjectPtr()
		{
			ObjectPtr = InternalUnsafeMethods.Create()(new InternalUnsafeMethods.Create__Args());
		}

        #region UnsafeNativeMethods
        new internal struct InternalUnsafeMethods {
            [StructLayout(LayoutKind.Sequential)]
            internal struct OnFrame__Args
            {
                internal int frameIndex;
                internal int frame;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _OnFrame(IntPtr _this, OnFrame__Args args);
            private static _OnFrame _OnFrameFunc;
            internal static _OnFrame OnFrame() {
                if (_OnFrameFunc == null) {
                    _OnFrameFunc =
                        (_OnFrame)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "cbguiAnimBitmapCtrl_onFrame"), typeof(_OnFrame));
                }
                
                return _OnFrameFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct OnCompleted__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _OnCompleted(IntPtr _this, OnCompleted__Args args);
            private static _OnCompleted _OnCompletedFunc;
            internal static _OnCompleted OnCompleted() {
                if (_OnCompletedFunc == null) {
                    _OnCompletedFunc =
                        (_OnCompleted)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "cbguiAnimBitmapCtrl_onCompleted"), typeof(_OnCompleted));
                }
                
                return _OnCompletedFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct OnLoop__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _OnLoop(IntPtr _this, OnLoop__Args args);
            private static _OnLoop _OnLoopFunc;
            internal static _OnLoop OnLoop() {
                if (_OnLoopFunc == null) {
                    _OnLoopFunc =
                        (_OnLoop)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "cbguiAnimBitmapCtrl_onLoop"), typeof(_OnLoop));
                }
                
                return _OnLoopFunc;
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
                                "fnguiAnimBitmapCtrl_staticGetType"), typeof(_StaticGetType));
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
                                "fnguiAnimBitmapCtrl_create"), typeof(_Create));
                }
                
                return _CreateFunc;
            }
        }
        #endregion

        /// <description>
        /// triggered when a frame increments
        /// </description>
        public virtual void OnFrame(int frameIndex, int frame) {
             InternalUnsafeMethods.OnFrame__Args _args = new InternalUnsafeMethods.OnFrame__Args() {
                frameIndex = frameIndex,
                frame = frame,
             };
             InternalUnsafeMethods.OnFrame()(ObjectPtr, _args);
        }

        /// <description>
        /// triggered when an animation completes
        /// </description>
        public virtual void OnCompleted() {
             InternalUnsafeMethods.OnCompleted__Args _args = new InternalUnsafeMethods.OnCompleted__Args() {
             };
             InternalUnsafeMethods.OnCompleted()(ObjectPtr, _args);
        }

        /// <description>
        /// triggered when a loop completes
        /// </description>
        public virtual void OnLoop() {
             InternalUnsafeMethods.OnLoop__Args _args = new InternalUnsafeMethods.OnLoop__Args() {
             };
             InternalUnsafeMethods.OnLoop()(ObjectPtr, _args);
        }

        /// <description>
        /// Get the type info object for the guiAnimBitmapCtrl class.
        /// </description>
        /// <returns>The type info object for guiAnimBitmapCtrl</returns>
        public static EngineTypeInfo StaticGetType() {
             InternalUnsafeMethods.StaticGetType__Args _args = new InternalUnsafeMethods.StaticGetType__Args() {
             };
             IntPtr _engineResult = InternalUnsafeMethods.StaticGetType()(_args);
             return new EngineTypeInfo(_engineResult);
        }


        /// <value>
        /// <summary>The number of frames, in rows and columns stored in textureName (when animateTexture is true).</summary>
        /// <description>
        /// A maximum of 256 frames can be stored in a single texture when using mAnimTexTiling. Value should be "NumColumns NumRows", for example "4 4".
        /// </description>
        /// </value>
        public Point2I AnimTexTiling {
            get => GenericMarshal.StringTo<Point2I>(GetFieldValue("animTexTiling"));
            set => SetFieldValue("animTexTiling", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <summary>A list of frames and/or frame ranges to use for particle animation if animateTexture is true.</summary>
        /// <description>
        /// Each frame token must be separated by whitespace. A frame token must be a positive integer frame number or a range of frame numbers separated with a '-'. The range separator, '-', cannot have any whitspace around it.
        /// 
        /// Ranges can be specified to move through the frames in reverse as well as forward (eg. 19-14). Frame numbers exceeding the number of tiles will wrap.
        /// </description>
        /// <code>
        /// mAnimTexFrames = "0-16 20 19 18 17 31-21";
        /// </code>
        /// </value>
        public string AnimTexFrames {
            get => GenericMarshal.StringTo<string>(GetFieldValue("animTexFrames"));
            set => SetFieldValue("animTexFrames", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// loop?
        /// </description>
        /// </value>
        public bool Loop {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("Loop"));
            set => SetFieldValue("Loop", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// play?
        /// </description>
        /// </value>
        public bool Play {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("play"));
            set => SetFieldValue("play", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// play reversed?
        /// </description>
        /// </value>
        public bool Reverse {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("reverse"));
            set => SetFieldValue("reverse", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Frame Rate
        /// </description>
        /// </value>
        public int Fps {
            get => GenericMarshal.StringTo<int>(GetFieldValue("fps"));
            set => SetFieldValue("fps", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Index of currently Displaying Frame
        /// </description>
        /// </value>
        public int CurFrame {
            get => GenericMarshal.StringTo<int>(GetFieldValue("curFrame"));
            set => SetFieldValue("curFrame", GenericMarshal.ToString(value));
        }
    }
}