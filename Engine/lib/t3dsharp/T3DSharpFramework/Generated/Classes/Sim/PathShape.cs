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
    public unsafe class PathShape : StaticShape {
        public PathShape(bool pRegister = false) 
            : base(pRegister) {
        }
        
        public PathShape(string pName, bool pRegister) 
            : this(false) {
            Name = pName;
            if (pRegister) {
                RegisterObject();
            }
        }
        
        public PathShape(string pName) 
            : this(pName, false) {
        }
        
        public PathShape(string pName, string pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(Engine.Sim.FindObject<SimObject>(pParent));
        }
        
        public PathShape(string pName, SimObject pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(pParent);
        }
        
        public PathShape(SimObject pObj) 
            : base(pObj) {
        }
        
        public PathShape(IntPtr pObj) 
            : base(pObj) {
        }
        
		protected override void CreateObjectPtr()
		{
			ObjectPtr = InternalUnsafeMethods.Create()(new InternalUnsafeMethods.Create__Args());
		}

        #region UnsafeNativeMethods
        new internal struct InternalUnsafeMethods {
            [StructLayout(LayoutKind.Sequential)]
            internal struct GetState__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate int _GetState(IntPtr _this, GetState__Args args);
            private static _GetState _GetStateFunc;
            internal static _GetState GetState() {
                if (_GetStateFunc == null) {
                    _GetStateFunc =
                        (_GetState)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnPathShape_getState"), typeof(_GetState));
                }
                
                return _GetStateFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct PopFront__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _PopFront(IntPtr _this, PopFront__Args args);
            private static _PopFront _PopFrontFunc;
            internal static _PopFront PopFront() {
                if (_PopFrontFunc == null) {
                    _PopFrontFunc =
                        (_PopFront)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnPathShape_popFront"), typeof(_PopFront));
                }
                
                return _PopFrontFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct PushFront__Args
            {
                internal IntPtr transform;
                internal float speed;
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string type;
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string path;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _PushFront(IntPtr _this, PushFront__Args args);
            private static _PushFront _PushFrontFunc;
            internal static _PushFront PushFront() {
                if (_PushFrontFunc == null) {
                    _PushFrontFunc =
                        (_PushFront)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnPathShape_pushFront"), typeof(_PushFront));
                }
                
                return _PushFrontFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct PushBack__Args
            {
                internal IntPtr transform;
                internal float speed;
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string type;
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string path;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _PushBack(IntPtr _this, PushBack__Args args);
            private static _PushBack _PushBackFunc;
            internal static _PushBack PushBack() {
                if (_PushBackFunc == null) {
                    _PushBackFunc =
                        (_PushBack)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnPathShape_pushBack"), typeof(_PushBack));
                }
                
                return _PushBackFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct Reset__Args
            {
                internal float speed;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _Reset(IntPtr _this, Reset__Args args);
            private static _Reset _ResetFunc;
            internal static _Reset Reset() {
                if (_ResetFunc == null) {
                    _ResetFunc =
                        (_Reset)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnPathShape_reset"), typeof(_Reset));
                }
                
                return _ResetFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct SetState__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string newState;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _SetState(IntPtr _this, SetState__Args args);
            private static _SetState _SetStateFunc;
            internal static _SetState SetState() {
                if (_SetStateFunc == null) {
                    _SetStateFunc =
                        (_SetState)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnPathShape_setState"), typeof(_SetState));
                }
                
                return _SetStateFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct SetTarget__Args
            {
                internal float position;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _SetTarget(IntPtr _this, SetTarget__Args args);
            private static _SetTarget _SetTargetFunc;
            internal static _SetTarget SetTarget() {
                if (_SetTargetFunc == null) {
                    _SetTargetFunc =
                        (_SetTarget)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnPathShape_setTarget"), typeof(_SetTarget));
                }
                
                return _SetTargetFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct SetPosition__Args
            {
                internal float position;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _SetPosition(IntPtr _this, SetPosition__Args args);
            private static _SetPosition _SetPositionFunc;
            internal static _SetPosition SetPosition() {
                if (_SetPositionFunc == null) {
                    _SetPositionFunc =
                        (_SetPosition)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnPathShape_setPosition"), typeof(_SetPosition));
                }
                
                return _SetPositionFunc;
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
                                "fnPathShape_staticGetType"), typeof(_StaticGetType));
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
                                "fnPathShape_create"), typeof(_Create));
                }
                
                return _CreateFunc;
            }
        }
        #endregion

        /// <description>
        /// PathShape.getState()
        /// </description>
        public int GetState() {
             InternalUnsafeMethods.GetState__Args _args = new InternalUnsafeMethods.GetState__Args() {
             };
             int _engineResult = InternalUnsafeMethods.GetState()(ObjectPtr, _args);
             return _engineResult;
        }

        /// <description>
        /// Removes the knot at the front of the camera's path.
        /// </description>
        /// <code>
        /// // Remove the first knot in the camera's path.
        /// %pathCamera.popFront();
        /// </code>
        public void PopFront() {
             InternalUnsafeMethods.PopFront__Args _args = new InternalUnsafeMethods.PopFront__Args() {
             };
             InternalUnsafeMethods.PopFront()(ObjectPtr, _args);
        }

        /// <summary>Adds a new knot to the front of a path camera's path.</summary>
        /// <description>
        /// 
        /// </description>
        /// <param name="transform">Transform for the new knot. In the form of "x y z ax ay az aa" such as returned by SceneObject::getTransform()</param>
        /// <param name="speed">Speed setting for this knot.</param>
        /// <param name="type">Knot type (Normal, Position Only, Kink).</param>
        /// <param name="path">%Path type (Linear, Spline).</param>
        /// <code>
        /// // Transform vector for new knot. (Pos_X,Pos_Y,Pos_Z,Rot_X,Rot_Y,Rot_Z,Angle)
        /// %transform = "15.0 5.0 5.0 1.4 1.0 0.2 1.0"
        /// 
        /// // Speed setting for knot.
        /// %speed = "1.0";
        /// 
        /// // Knot type. (Normal, Position Only, Kink)
        /// %type = "Normal";
        /// 
        /// // Path Type. (Linear, Spline)
        /// %path = "Linear";
        /// 
        /// // Inform the path camera to add a new knot to the front of its path
        /// %pathCamera.pushFront(%transform, %speed, %type, %path);
        /// </code>
        public void PushFront(TransformF transform, float speed = 1f, string type = "Normal", string path = "Linear") {
transform.Alloc();             InternalUnsafeMethods.PushFront__Args _args = new InternalUnsafeMethods.PushFront__Args() {
                transform = transform.internalStructPtr,
                speed = speed,
                type = type,
                path = path,
             };
             InternalUnsafeMethods.PushFront()(ObjectPtr, _args);
transform.Free();        }

        /// <summary>Adds a new knot to the back of a path camera's path.</summary>
        /// <description>
        /// 
        /// </description>
        /// <param name="transform">Transform for the new knot.  In the form of "x y z ax ay az aa" such as returned by SceneObject::getTransform()</param>
        /// <param name="speed">Speed setting for this knot.</param>
        /// <param name="type">Knot type (Normal, Position Only, Kink).</param>
        /// <param name="path">%Path type (Linear, Spline).</param>
        /// <code>
        /// // Transform vector for new knot. (Pos_X Pos_Y Pos_Z Rot_X Rot_Y Rot_Z Angle)
        /// %transform = "15.0 5.0 5.0 1.4 1.0 0.2 1.0"
        /// 
        /// // Speed setting for knot.
        /// %speed = "1.0"
        /// 
        /// // Knot type. (Normal, Position Only, Kink)
        /// %type = "Normal";
        /// 
        /// // Path Type. (Linear, Spline)
        /// %path = "Linear";
        /// 
        /// // Inform the path camera to add a new knot to the back of its path
        /// %pathCamera.pushBack(%transform,%speed,%type,%path);
        /// </code>
        public void PushBack(TransformF transform = null, float speed = 1f, string type = "Normal", string path = "Linear") {
transform = transform ?? new TransformF("0 0 0 0 0 0 0 false");
transform.Alloc();             InternalUnsafeMethods.PushBack__Args _args = new InternalUnsafeMethods.PushBack__Args() {
                transform = transform.internalStructPtr,
                speed = speed,
                type = type,
                path = path,
             };
             InternalUnsafeMethods.PushBack()(ObjectPtr, _args);
transform.Free();        }

        /// <summary>Clear the camera's path and set the camera's current transform as the start of the new path.</summary>
        /// <description>
        /// What specifically occurs is a new knot is created from the camera's current transform.  Then the current path is cleared and the new knot is pushed onto the path.  Any previous target is cleared and the camera's movement state is set to Forward.  The camera is now ready for a new path to be defined.
        /// </description>
        /// <param name="speed">Speed for the camera to move along its path after being reset.</param>
        /// <code>
        /// //Determine the new movement speed of this camera. If not set, the speed will default to 1.0.
        /// %speed = "0.50";
        /// 
        /// // Inform the path camera to start a new path at// the camera's current position, and set the new // path's speed value.
        /// %pathCamera.reset(%speed);
        /// </code>
        public void Reset(float speed = 1f) {
             InternalUnsafeMethods.Reset__Args _args = new InternalUnsafeMethods.Reset__Args() {
                speed = speed,
             };
             InternalUnsafeMethods.Reset()(ObjectPtr, _args);
        }

        /// <description>
        /// Set the movement state for this path camera.
        /// </description>
        /// <param name="newState">New movement state type for this camera. Forward, Backward or Stop.</param>
        /// <code>
        /// // Set the state type (forward, backward, stop).
        /// // In this example, the camera will travel from the first node
        /// // to the last node (or target if given with setTarget())
        /// %state = "forward";
        /// 
        /// // Inform the pathCamera to change its movement state to the defined value.
        /// %pathCamera.setState(%state);
        /// </code>
        public void SetState(string newState = "forward") {
             InternalUnsafeMethods.SetState__Args _args = new InternalUnsafeMethods.SetState__Args() {
                newState = newState,
             };
             InternalUnsafeMethods.SetState()(ObjectPtr, _args);
        }

        /// <summary>Set the movement target for this camera along its path.</summary>
        /// <description>
        /// The camera will attempt to move along the path to the given target in the direction provided by setState() (the default is forwards).  Once the camera moves past this target it will come to a stop, and the target state will be cleared.
        /// </description>
        /// <param name="position">Target position, between 0.0 (path start) and 1.0 (path end), for the camera to move to along its path.</param>
        /// <code>
        /// // Set the position target, between 0.0 (path start) and 1.0 (path end), for this camera to move to.
        /// %position = "0.50";
        /// 
        /// // Inform the pathCamera of the new target position it will move to.
        /// %pathCamera.setTarget(%position);
        /// </code>
        public void SetTarget(float position = 1f) {
             InternalUnsafeMethods.SetTarget__Args _args = new InternalUnsafeMethods.SetTarget__Args() {
                position = position,
             };
             InternalUnsafeMethods.SetTarget()(ObjectPtr, _args);
        }

        /// <description>
        /// Set the current position of the camera along the path.
        /// </description>
        /// <param name="position">Position along the path, from 0.0 (path start) - 1.0 (path end), to place the camera.</param>
        /// <code>
        /// // Set the camera on a position along its path from 0.0 - 1.0.
        /// %position = "0.35";
        /// 
        /// // Force the pathCamera to its new position along the path.
        /// %pathCamera.setPosition(%position);
        /// </code>
        public void SetPosition(float position = 0f) {
             InternalUnsafeMethods.SetPosition__Args _args = new InternalUnsafeMethods.SetPosition__Args() {
                position = position,
             };
             InternalUnsafeMethods.SetPosition()(ObjectPtr, _args);
        }

        /// <description>
        /// Get the type info object for the PathShape class.
        /// </description>
        /// <returns>The type info object for PathShape</returns>
        public static EngineTypeInfo StaticGetType() {
             InternalUnsafeMethods.StaticGetType__Args _args = new InternalUnsafeMethods.StaticGetType__Args() {
             };
             IntPtr _engineResult = InternalUnsafeMethods.StaticGetType()(_args);
             return new EngineTypeInfo(_engineResult);
        }


        /// <value>
        /// <summary>Name of a Path to follow.</summary>
        /// </value>
        public Path Path {
            get => GenericMarshal.StringTo<Path>(GetFieldValue("Path"));
            set => SetFieldValue("Path", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// controlers
        /// </description>
        /// </value>
        public DynamicFieldVector<string> Controler {
            get => new DynamicFieldVector<string>(
                    this, 
                    "Controler", 
                    4, 
                    val => GenericMarshal.StringTo<string>(val),
                    obj => GenericMarshal.ToString(obj)
                );
        }
    }
}