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
    /// <summary>Represents a position, direction and field of view to render a scene from.</summary>
    /// <description>
    /// A camera is typically manipulated by a GameConnection.  When set as the connection's control object, the camera handles all movement actions ($mvForwardAction, $mvPitch, etc.) just like a Player.
    /// </description>
    /// <code>
    /// // Set an already created camera as the GameConnection's control object
    /// %connection.setControlObject(%camera);
    /// </code>
    /// <code>
    /// // Create a camera in the level and set its position to a given spawn point.
    /// // Note: The camera starts in the standard fly mode.
    /// %cam = new Camera() {
    ///    datablock = "Observer";
    /// };
    /// MissionCleanup.add( %cam );
    /// %cam.setTransform( %spawnPoint.getTransform() );
    /// </code>
    /// <code>
    /// // Create a camera at the given spawn point for the specified
    /// // GameConnection i.e. the client.  Uses the standard
    /// // Sim::spawnObject() function to create the camera using the
    /// // defined default settings.
    /// // Note: The camera starts in the standard fly mode.
    /// function GameConnection::spawnCamera(%this, %spawnPoint)
    /// {
    ///    // Set the control object to the default camera
    ///    if (!isObject(%this.camera))
    ///    {
    ///       if (isDefined("$Game::DefaultCameraClass"))
    ///          %this.camera = spawnObject($Game::DefaultCameraClass, $Game::DefaultCameraDataBlock);
    ///    }
    /// 
    ///    // If we have a camera then set up some properties
    ///    if (isObject(%this.camera))
    ///    {
    ///       // Make sure we're cleaned up when the mission ends
    ///       MissionCleanup.add( %this.camera );
    /// 
    ///       // Make sure the camera is always in scope for the connection
    ///       %this.camera.scopeToClient(%this);
    /// 
    ///       // Send all user input from the connection to the camera
    ///       %this.setControlObject(%this.camera);
    /// 
    ///       if (isDefined("%spawnPoint"))
    ///       {
    ///          // Attempt to treat %spawnPoint as an object, such as a
    ///          // SpawnSphere class.
    ///          if (getWordCount(%spawnPoint) == 1 && isObject(%spawnPoint))
    ///          {
    ///             %this.camera.setTransform(%spawnPoint.getTransform());
    ///          }
    ///          else
    ///          {
    ///             // Treat %spawnPoint as an AngleAxis transform
    ///             %this.camera.setTransform(%spawnPoint);
    ///          }
    ///       }
    ///    }
    /// }
    /// </code>
    /// <see cref="CameraData" />
    /// <see cref="CameraMotionMode" />
    /// <see cref="Camera::movementSpeed" />
    public unsafe class Camera : ShapeBase {
        public Camera(bool pRegister = false) 
            : base(pRegister) {
        }
        
        public Camera(string pName, bool pRegister) 
            : this(false) {
            Name = pName;
            if (pRegister) {
                RegisterObject();
            }
        }
        
        public Camera(string pName) 
            : this(pName, false) {
        }
        
        public Camera(string pName, string pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(Engine.Sim.FindObject<SimObject>(pParent));
        }
        
        public Camera(string pName, SimObject pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(pParent);
        }
        
        public Camera(SimObject pObj) 
            : base(pObj) {
        }
        
        public Camera(IntPtr pObj) 
            : base(pObj) {
        }
        
		protected override void CreateObjectPtr()
		{
			ObjectPtr = InternalUnsafeMethods.Create()(new InternalUnsafeMethods.Create__Args());
		}

        #region UnsafeNativeMethods
        new internal struct InternalUnsafeMethods {
            [StructLayout(LayoutKind.Sequential)]
            internal struct LookAt__Args
            {
                internal IntPtr point;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _LookAt(IntPtr _this, LookAt__Args args);
            private static _LookAt _LookAtFunc;
            internal static _LookAt LookAt() {
                if (_LookAtFunc == null) {
                    _LookAtFunc =
                        (_LookAt)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnCamera_lookAt"), typeof(_LookAt));
                }
                
                return _LookAtFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct AutoFitRadius__Args
            {
                internal float radius;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _AutoFitRadius(IntPtr _this, AutoFitRadius__Args args);
            private static _AutoFitRadius _AutoFitRadiusFunc;
            internal static _AutoFitRadius AutoFitRadius() {
                if (_AutoFitRadiusFunc == null) {
                    _AutoFitRadiusFunc =
                        (_AutoFitRadius)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnCamera_autoFitRadius"), typeof(_AutoFitRadius));
                }
                
                return _AutoFitRadiusFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct SetEditOrbitPoint__Args
            {
                internal IntPtr point;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _SetEditOrbitPoint(IntPtr _this, SetEditOrbitPoint__Args args);
            private static _SetEditOrbitPoint _SetEditOrbitPointFunc;
            internal static _SetEditOrbitPoint SetEditOrbitPoint() {
                if (_SetEditOrbitPointFunc == null) {
                    _SetEditOrbitPointFunc =
                        (_SetEditOrbitPoint)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnCamera_setEditOrbitPoint"), typeof(_SetEditOrbitPoint));
                }
                
                return _SetEditOrbitPointFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct SetValidEditOrbitPoint__Args
            {
                [MarshalAs(UnmanagedType.I1)]
                internal bool validPoint;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _SetValidEditOrbitPoint(IntPtr _this, SetValidEditOrbitPoint__Args args);
            private static _SetValidEditOrbitPoint _SetValidEditOrbitPointFunc;
            internal static _SetValidEditOrbitPoint SetValidEditOrbitPoint() {
                if (_SetValidEditOrbitPointFunc == null) {
                    _SetValidEditOrbitPointFunc =
                        (_SetValidEditOrbitPoint)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnCamera_setValidEditOrbitPoint"), typeof(_SetValidEditOrbitPoint));
                }
                
                return _SetValidEditOrbitPointFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct IsEditOrbitMode__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            [return: MarshalAs(UnmanagedType.I1)]
            internal delegate bool _IsEditOrbitMode(IntPtr _this, IsEditOrbitMode__Args args);
            private static _IsEditOrbitMode _IsEditOrbitModeFunc;
            internal static _IsEditOrbitMode IsEditOrbitMode() {
                if (_IsEditOrbitModeFunc == null) {
                    _IsEditOrbitModeFunc =
                        (_IsEditOrbitMode)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnCamera_isEditOrbitMode"), typeof(_IsEditOrbitMode));
                }
                
                return _IsEditOrbitModeFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct SetBrakeMultiplier__Args
            {
                internal float multiplier;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _SetBrakeMultiplier(IntPtr _this, SetBrakeMultiplier__Args args);
            private static _SetBrakeMultiplier _SetBrakeMultiplierFunc;
            internal static _SetBrakeMultiplier SetBrakeMultiplier() {
                if (_SetBrakeMultiplierFunc == null) {
                    _SetBrakeMultiplierFunc =
                        (_SetBrakeMultiplier)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnCamera_setBrakeMultiplier"), typeof(_SetBrakeMultiplier));
                }
                
                return _SetBrakeMultiplierFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct SetSpeedMultiplier__Args
            {
                internal float multiplier;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _SetSpeedMultiplier(IntPtr _this, SetSpeedMultiplier__Args args);
            private static _SetSpeedMultiplier _SetSpeedMultiplierFunc;
            internal static _SetSpeedMultiplier SetSpeedMultiplier() {
                if (_SetSpeedMultiplierFunc == null) {
                    _SetSpeedMultiplierFunc =
                        (_SetSpeedMultiplier)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnCamera_setSpeedMultiplier"), typeof(_SetSpeedMultiplier));
                }
                
                return _SetSpeedMultiplierFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct SetFlyForce__Args
            {
                internal float force;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _SetFlyForce(IntPtr _this, SetFlyForce__Args args);
            private static _SetFlyForce _SetFlyForceFunc;
            internal static _SetFlyForce SetFlyForce() {
                if (_SetFlyForceFunc == null) {
                    _SetFlyForceFunc =
                        (_SetFlyForce)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnCamera_setFlyForce"), typeof(_SetFlyForce));
                }
                
                return _SetFlyForceFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct SetDrag__Args
            {
                internal float drag;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _SetDrag(IntPtr _this, SetDrag__Args args);
            private static _SetDrag _SetDragFunc;
            internal static _SetDrag SetDrag() {
                if (_SetDragFunc == null) {
                    _SetDragFunc =
                        (_SetDrag)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnCamera_setDrag"), typeof(_SetDrag));
                }
                
                return _SetDragFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct SetVelocity__Args
            {
                internal IntPtr velocity;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _SetVelocity(IntPtr _this, SetVelocity__Args args);
            private static _SetVelocity _SetVelocityFunc;
            internal static _SetVelocity SetVelocity() {
                if (_SetVelocityFunc == null) {
                    _SetVelocityFunc =
                        (_SetVelocity)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnCamera_setVelocity"), typeof(_SetVelocity));
                }
                
                return _SetVelocityFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct GetVelocity__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate Point3F.InternalStruct _GetVelocity(IntPtr _this, GetVelocity__Args args);
            private static _GetVelocity _GetVelocityFunc;
            internal static _GetVelocity GetVelocity() {
                if (_GetVelocityFunc == null) {
                    _GetVelocityFunc =
                        (_GetVelocity)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnCamera_getVelocity"), typeof(_GetVelocity));
                }
                
                return _GetVelocityFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct SetMass__Args
            {
                internal float mass;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _SetMass(IntPtr _this, SetMass__Args args);
            private static _SetMass _SetMassFunc;
            internal static _SetMass SetMass() {
                if (_SetMassFunc == null) {
                    _SetMassFunc =
                        (_SetMass)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnCamera_setMass"), typeof(_SetMass));
                }
                
                return _SetMassFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct SetAngularDrag__Args
            {
                internal float drag;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _SetAngularDrag(IntPtr _this, SetAngularDrag__Args args);
            private static _SetAngularDrag _SetAngularDragFunc;
            internal static _SetAngularDrag SetAngularDrag() {
                if (_SetAngularDragFunc == null) {
                    _SetAngularDragFunc =
                        (_SetAngularDrag)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnCamera_setAngularDrag"), typeof(_SetAngularDrag));
                }
                
                return _SetAngularDragFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct SetAngularForce__Args
            {
                internal float force;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _SetAngularForce(IntPtr _this, SetAngularForce__Args args);
            private static _SetAngularForce _SetAngularForceFunc;
            internal static _SetAngularForce SetAngularForce() {
                if (_SetAngularForceFunc == null) {
                    _SetAngularForceFunc =
                        (_SetAngularForce)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnCamera_setAngularForce"), typeof(_SetAngularForce));
                }
                
                return _SetAngularForceFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct SetAngularVelocity__Args
            {
                internal IntPtr velocity;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _SetAngularVelocity(IntPtr _this, SetAngularVelocity__Args args);
            private static _SetAngularVelocity _SetAngularVelocityFunc;
            internal static _SetAngularVelocity SetAngularVelocity() {
                if (_SetAngularVelocityFunc == null) {
                    _SetAngularVelocityFunc =
                        (_SetAngularVelocity)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnCamera_setAngularVelocity"), typeof(_SetAngularVelocity));
                }
                
                return _SetAngularVelocityFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct GetAngularVelocity__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate Point3F.InternalStruct _GetAngularVelocity(IntPtr _this, GetAngularVelocity__Args args);
            private static _GetAngularVelocity _GetAngularVelocityFunc;
            internal static _GetAngularVelocity GetAngularVelocity() {
                if (_GetAngularVelocityFunc == null) {
                    _GetAngularVelocityFunc =
                        (_GetAngularVelocity)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnCamera_getAngularVelocity"), typeof(_GetAngularVelocity));
                }
                
                return _GetAngularVelocityFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct IsRotationDamped__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            [return: MarshalAs(UnmanagedType.I1)]
            internal delegate bool _IsRotationDamped(IntPtr _this, IsRotationDamped__Args args);
            private static _IsRotationDamped _IsRotationDampedFunc;
            internal static _IsRotationDamped IsRotationDamped() {
                if (_IsRotationDampedFunc == null) {
                    _IsRotationDampedFunc =
                        (_IsRotationDamped)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnCamera_isRotationDamped"), typeof(_IsRotationDamped));
                }
                
                return _IsRotationDampedFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct SetNewtonFlyMode__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _SetNewtonFlyMode(IntPtr _this, SetNewtonFlyMode__Args args);
            private static _SetNewtonFlyMode _SetNewtonFlyModeFunc;
            internal static _SetNewtonFlyMode SetNewtonFlyMode() {
                if (_SetNewtonFlyModeFunc == null) {
                    _SetNewtonFlyModeFunc =
                        (_SetNewtonFlyMode)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnCamera_setNewtonFlyMode"), typeof(_SetNewtonFlyMode));
                }
                
                return _SetNewtonFlyModeFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct SetFlyMode__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _SetFlyMode(IntPtr _this, SetFlyMode__Args args);
            private static _SetFlyMode _SetFlyModeFunc;
            internal static _SetFlyMode SetFlyMode() {
                if (_SetFlyModeFunc == null) {
                    _SetFlyModeFunc =
                        (_SetFlyMode)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnCamera_setFlyMode"), typeof(_SetFlyMode));
                }
                
                return _SetFlyModeFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct SetEditOrbitMode__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _SetEditOrbitMode(IntPtr _this, SetEditOrbitMode__Args args);
            private static _SetEditOrbitMode _SetEditOrbitModeFunc;
            internal static _SetEditOrbitMode SetEditOrbitMode() {
                if (_SetEditOrbitModeFunc == null) {
                    _SetEditOrbitModeFunc =
                        (_SetEditOrbitMode)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnCamera_setEditOrbitMode"), typeof(_SetEditOrbitMode));
                }
                
                return _SetEditOrbitModeFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct SetTrackObject__Args
            {
                internal IntPtr trackObject;
                internal IntPtr offset;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            [return: MarshalAs(UnmanagedType.I1)]
            internal delegate bool _SetTrackObject(IntPtr _this, SetTrackObject__Args args);
            private static _SetTrackObject _SetTrackObjectFunc;
            internal static _SetTrackObject SetTrackObject() {
                if (_SetTrackObjectFunc == null) {
                    _SetTrackObjectFunc =
                        (_SetTrackObject)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnCamera_setTrackObject"), typeof(_SetTrackObject));
                }
                
                return _SetTrackObjectFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct SetOrbitPoint__Args
            {
                internal IntPtr orbitPoint;
                internal float minDistance;
                internal float maxDistance;
                internal float initDistance;
                internal IntPtr offset;
                [MarshalAs(UnmanagedType.I1)]
                internal bool locked;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _SetOrbitPoint(IntPtr _this, SetOrbitPoint__Args args);
            private static _SetOrbitPoint _SetOrbitPointFunc;
            internal static _SetOrbitPoint SetOrbitPoint() {
                if (_SetOrbitPointFunc == null) {
                    _SetOrbitPointFunc =
                        (_SetOrbitPoint)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnCamera_setOrbitPoint"), typeof(_SetOrbitPoint));
                }
                
                return _SetOrbitPointFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct SetOrbitObject__Args
            {
                internal IntPtr orbitObject;
                internal IntPtr rotation;
                internal float minDistance;
                internal float maxDistance;
                internal float initDistance;
                [MarshalAs(UnmanagedType.I1)]
                internal bool ownClientObject;
                internal IntPtr offset;
                [MarshalAs(UnmanagedType.I1)]
                internal bool locked;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            [return: MarshalAs(UnmanagedType.I1)]
            internal delegate bool _SetOrbitObject(IntPtr _this, SetOrbitObject__Args args);
            private static _SetOrbitObject _SetOrbitObjectFunc;
            internal static _SetOrbitObject SetOrbitObject() {
                if (_SetOrbitObjectFunc == null) {
                    _SetOrbitObjectFunc =
                        (_SetOrbitObject)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnCamera_setOrbitObject"), typeof(_SetOrbitObject));
                }
                
                return _SetOrbitObjectFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct SetOrbitMode__Args
            {
                internal IntPtr orbitObject;
                internal IntPtr orbitPoint;
                internal float minDistance;
                internal float maxDistance;
                internal float initDistance;
                [MarshalAs(UnmanagedType.I1)]
                internal bool ownClientObj;
                internal IntPtr offset;
                [MarshalAs(UnmanagedType.I1)]
                internal bool locked;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _SetOrbitMode(IntPtr _this, SetOrbitMode__Args args);
            private static _SetOrbitMode _SetOrbitModeFunc;
            internal static _SetOrbitMode SetOrbitMode() {
                if (_SetOrbitModeFunc == null) {
                    _SetOrbitModeFunc =
                        (_SetOrbitMode)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnCamera_setOrbitMode"), typeof(_SetOrbitMode));
                }
                
                return _SetOrbitModeFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct SetOffset__Args
            {
                internal IntPtr offset;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _SetOffset(IntPtr _this, SetOffset__Args args);
            private static _SetOffset _SetOffsetFunc;
            internal static _SetOffset SetOffset() {
                if (_SetOffsetFunc == null) {
                    _SetOffsetFunc =
                        (_SetOffset)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnCamera_setOffset"), typeof(_SetOffset));
                }
                
                return _SetOffsetFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct GetOffset__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate Point3F.InternalStruct _GetOffset(IntPtr _this, GetOffset__Args args);
            private static _GetOffset _GetOffsetFunc;
            internal static _GetOffset GetOffset() {
                if (_GetOffsetFunc == null) {
                    _GetOffsetFunc =
                        (_GetOffset)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnCamera_getOffset"), typeof(_GetOffset));
                }
                
                return _GetOffsetFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct SetRotation__Args
            {
                internal IntPtr rot;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _SetRotation(IntPtr _this, SetRotation__Args args);
            private static _SetRotation _SetRotationFunc;
            internal static _SetRotation SetRotation() {
                if (_SetRotationFunc == null) {
                    _SetRotationFunc =
                        (_SetRotation)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnCamera_setRotation"), typeof(_SetRotation));
                }
                
                return _SetRotationFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct GetRotation__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate Point3F.InternalStruct _GetRotation(IntPtr _this, GetRotation__Args args);
            private static _GetRotation _GetRotationFunc;
            internal static _GetRotation GetRotation() {
                if (_GetRotationFunc == null) {
                    _GetRotationFunc =
                        (_GetRotation)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnCamera_getRotation"), typeof(_GetRotation));
                }
                
                return _GetRotationFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct GetPosition__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate Point3F.InternalStruct _GetPosition(IntPtr _this, GetPosition__Args args);
            private static _GetPosition _GetPositionFunc;
            internal static _GetPosition GetPosition() {
                if (_GetPositionFunc == null) {
                    _GetPositionFunc =
                        (_GetPosition)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnCamera_getPosition"), typeof(_GetPosition));
                }
                
                return _GetPositionFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct GetMode__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate int _GetMode(IntPtr _this, GetMode__Args args);
            private static _GetMode _GetModeFunc;
            internal static _GetMode GetMode() {
                if (_GetModeFunc == null) {
                    _GetModeFunc =
                        (_GetMode)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnCamera_getMode"), typeof(_GetMode));
                }
                
                return _GetModeFunc;
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
                                "fnCamera_staticGetType"), typeof(_StaticGetType));
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
                                "fnCamera_create"), typeof(_Create));
                }
                
                return _CreateFunc;
            }
        }
        #endregion

        /// <description>
        /// Point the camera at the specified position.  Does not work in Orbit or Track modes.
        /// </description>
        /// <param name="point">The position to point the camera at.</param>
        public void LookAt(Point3F point) {
point.Alloc();             InternalUnsafeMethods.LookAt__Args _args = new InternalUnsafeMethods.LookAt__Args() {
                point = point.internalStructPtr,
             };
             InternalUnsafeMethods.LookAt()(ObjectPtr, _args);
point.Free();        }

        /// <description>
        /// Move the camera to fully view the given radius.
        /// </description>
        /// <remarks> For this operation to take affect a valid edit orbit point must first be specified.  See Camera::setEditOrbitPoint().
        /// </remarks>
        /// <param name="radius">The radius to view.</param>
        public void AutoFitRadius(float radius) {
             InternalUnsafeMethods.AutoFitRadius__Args _args = new InternalUnsafeMethods.AutoFitRadius__Args() {
                radius = radius,
             };
             InternalUnsafeMethods.AutoFitRadius()(ObjectPtr, _args);
        }

        /// <description>
        /// Set the editor camera's orbit point.
        /// </description>
        /// <param name="point">The point the camera will orbit in the form of "x y z".</param>
        public void SetEditOrbitPoint(Point3F point) {
point.Alloc();             InternalUnsafeMethods.SetEditOrbitPoint__Args _args = new InternalUnsafeMethods.SetEditOrbitPoint__Args() {
                point = point.internalStructPtr,
             };
             InternalUnsafeMethods.SetEditOrbitPoint()(ObjectPtr, _args);
point.Free();        }

        /// <description>
        /// Set if there is a valid editor camera orbit point.
        /// When validPoint is set to false the Camera operates as if it is in Fly mode rather than an Orbit mode.
        /// </description>
        /// <param name="validPoint">Indicates the validity of the orbit point.</param>
        /// <remarks> Only used when Camera is in Edit Orbit Mode.</remarks>
        public void SetValidEditOrbitPoint(bool validPoint) {
             InternalUnsafeMethods.SetValidEditOrbitPoint__Args _args = new InternalUnsafeMethods.SetValidEditOrbitPoint__Args() {
                validPoint = validPoint,
             };
             InternalUnsafeMethods.SetValidEditOrbitPoint()(ObjectPtr, _args);
        }

        /// <description>
        /// Is the camera in edit orbit mode?
        /// </description>
        /// <returns>true if the camera is in edit orbit mode.</returns>
        public bool IsEditOrbitMode() {
             InternalUnsafeMethods.IsEditOrbitMode__Args _args = new InternalUnsafeMethods.IsEditOrbitMode__Args() {
             };
             bool _engineResult = InternalUnsafeMethods.IsEditOrbitMode()(ObjectPtr, _args);
             return _engineResult;
        }

        /// <description>
        /// Set the Newton mode camera brake multiplier when trigger[1] is active.
        /// </description>
        /// <param name="multiplier">The brake multiplier to apply.</param>
        /// <remarks> Only used when Camera is in Newton mode.</remarks>
        public void SetBrakeMultiplier(float multiplier) {
             InternalUnsafeMethods.SetBrakeMultiplier__Args _args = new InternalUnsafeMethods.SetBrakeMultiplier__Args() {
                multiplier = multiplier,
             };
             InternalUnsafeMethods.SetBrakeMultiplier()(ObjectPtr, _args);
        }

        /// <description>
        /// Set the Newton mode camera speed multiplier when trigger[0] is active.
        /// </description>
        /// <param name="multiplier">The speed multiplier to apply.</param>
        /// <remarks> Only used when Camera is in Newton mode.</remarks>
        public void SetSpeedMultiplier(float multiplier) {
             InternalUnsafeMethods.SetSpeedMultiplier__Args _args = new InternalUnsafeMethods.SetSpeedMultiplier__Args() {
                multiplier = multiplier,
             };
             InternalUnsafeMethods.SetSpeedMultiplier()(ObjectPtr, _args);
        }

        /// <description>
        /// Set the force applied to a Newton mode camera while moving.
        /// </description>
        /// <param name="force">The force applied to the camera while attempting to move.</param>
        /// <remarks> Only used when Camera is in Newton mode.</remarks>
        public void SetFlyForce(float force) {
             InternalUnsafeMethods.SetFlyForce__Args _args = new InternalUnsafeMethods.SetFlyForce__Args() {
                force = force,
             };
             InternalUnsafeMethods.SetFlyForce()(ObjectPtr, _args);
        }

        /// <description>
        /// Set the drag for a Newton mode camera.
        /// </description>
        /// <param name="drag">The drag applied to the camera while moving.</param>
        /// <remarks> Only used when Camera is in Newton mode.</remarks>
        public void SetDrag(float drag) {
             InternalUnsafeMethods.SetDrag__Args _args = new InternalUnsafeMethods.SetDrag__Args() {
                drag = drag,
             };
             InternalUnsafeMethods.SetDrag()(ObjectPtr, _args);
        }

        /// <description>
        /// Set the velocity for the camera.
        /// </description>
        /// <param name="velocity">The camera's velocity in the form of "x y z".</param>
        /// <remarks> Only affects the Camera when in Newton mode.</remarks>
        public void SetVelocity(Point3F velocity) {
velocity.Alloc();             InternalUnsafeMethods.SetVelocity__Args _args = new InternalUnsafeMethods.SetVelocity__Args() {
                velocity = velocity.internalStructPtr,
             };
             InternalUnsafeMethods.SetVelocity()(ObjectPtr, _args);
velocity.Free();        }

        /// <description>
        /// Get the velocity for the camera.
        /// </description>
        /// <returns>The camera's velocity in the form of "x y z".</returns>
        /// <remarks> Only useful when the Camera is in Newton mode.</remarks>
        public Point3F GetVelocity() {
             InternalUnsafeMethods.GetVelocity__Args _args = new InternalUnsafeMethods.GetVelocity__Args() {
             };
             Point3F.InternalStruct _engineResult = InternalUnsafeMethods.GetVelocity()(ObjectPtr, _args);
             return new Point3F(_engineResult);
        }

        /// <description>
        /// Set the mass for a Newton mode camera.
        /// </description>
        /// <param name="mass">The mass used during ease-in and ease-out calculations.</param>
        /// <remarks> Only used when Camera is in Newton mode.</remarks>
        public void SetMass(float mass) {
             InternalUnsafeMethods.SetMass__Args _args = new InternalUnsafeMethods.SetMass__Args() {
                mass = mass,
             };
             InternalUnsafeMethods.SetMass()(ObjectPtr, _args);
        }

        /// <description>
        /// Set the angular drag for a Newton mode camera.
        /// </description>
        /// <param name="drag">The angular drag applied while the camera is rotating.</param>
        /// <remarks> Only takes affect when Camera::newtonRotation is set to true.</remarks>
        public void SetAngularDrag(float drag) {
             InternalUnsafeMethods.SetAngularDrag__Args _args = new InternalUnsafeMethods.SetAngularDrag__Args() {
                drag = drag,
             };
             InternalUnsafeMethods.SetAngularDrag()(ObjectPtr, _args);
        }

        /// <description>
        /// Set the angular force for a Newton mode camera.
        /// </description>
        /// <param name="force">The angular force applied when attempting to rotate the camera.</param>
        /// <remarks> Only takes affect when Camera::newtonRotation is set to true.</remarks>
        public void SetAngularForce(float force) {
             InternalUnsafeMethods.SetAngularForce__Args _args = new InternalUnsafeMethods.SetAngularForce__Args() {
                force = force,
             };
             InternalUnsafeMethods.SetAngularForce()(ObjectPtr, _args);
        }

        /// <description>
        /// Set the angular velocity for a Newton mode camera.
        /// </description>
        /// <param name="velocity">The angular velocity infor form of "x y z".</param>
        /// <remarks> Only takes affect when Camera::newtonRotation is set to true.</remarks>
        public void SetAngularVelocity(Point3F velocity) {
velocity.Alloc();             InternalUnsafeMethods.SetAngularVelocity__Args _args = new InternalUnsafeMethods.SetAngularVelocity__Args() {
                velocity = velocity.internalStructPtr,
             };
             InternalUnsafeMethods.SetAngularVelocity()(ObjectPtr, _args);
velocity.Free();        }

        /// <description>
        /// Get the angular velocity for a Newton mode camera.
        /// </description>
        /// <returns>The angular velocity in the form of "x y z".</returns>
        /// <remarks> Only returns useful results when Camera::newtonRotation is set to true.</remarks>
        public Point3F GetAngularVelocity() {
             InternalUnsafeMethods.GetAngularVelocity__Args _args = new InternalUnsafeMethods.GetAngularVelocity__Args() {
             };
             Point3F.InternalStruct _engineResult = InternalUnsafeMethods.GetAngularVelocity()(ObjectPtr, _args);
             return new Point3F(_engineResult);
        }

        /// <description>
        /// Is this a Newton Fly mode camera with damped rotation?
        /// </description>
        /// <returns>true if the camera uses a damped rotation.  i.e. Camera::newtonRotation is set to true.</returns>
        public bool IsRotationDamped() {
             InternalUnsafeMethods.IsRotationDamped__Args _args = new InternalUnsafeMethods.IsRotationDamped__Args() {
             };
             bool _engineResult = InternalUnsafeMethods.IsRotationDamped()(ObjectPtr, _args);
             return _engineResult;
        }

        /// <description>
        /// Set the camera to fly freely, but with ease-in and ease-out.
        /// 
        /// This method allows for the same 6 degrees of freedom as Camera::setFlyMode() but activates the ease-in and ease-out on the camera's movement.  To also activate Newton mode for the camera's rotation, set Camera::newtonRotation to true.
        /// </description>
        public void SetNewtonFlyMode() {
             InternalUnsafeMethods.SetNewtonFlyMode__Args _args = new InternalUnsafeMethods.SetNewtonFlyMode__Args() {
             };
             InternalUnsafeMethods.SetNewtonFlyMode()(ObjectPtr, _args);
        }

        /// <description>
        /// Set the camera to fly freely.
        /// 
        /// Allows the camera to have 6 degrees of freedom.  Provides for instantaneous motion and rotation unless one of the Newton fields has been set to true.  See Camera::newtonMode and Camera::newtonRotation.
        /// </description>
        public void SetFlyMode() {
             InternalUnsafeMethods.SetFlyMode__Args _args = new InternalUnsafeMethods.SetFlyMode__Args() {
             };
             InternalUnsafeMethods.SetFlyMode()(ObjectPtr, _args);
        }

        /// <description>
        /// Set the editor camera to orbit around a point set with Camera::setEditOrbitPoint().
        /// </description>
        /// <remarks> This method is generally used only within the World Editor and other tools.  To orbit about an object or point within a game, see Camera::setOrbitMode() and its helper methods.
        /// </remarks>
        public void SetEditOrbitMode() {
             InternalUnsafeMethods.SetEditOrbitMode__Args _args = new InternalUnsafeMethods.SetEditOrbitMode__Args() {
             };
             InternalUnsafeMethods.SetEditOrbitMode()(ObjectPtr, _args);
        }

        /// <description>
        /// Set the camera to track a given object.
        /// </description>
        /// <param name="trackObject">The object to track.</param>
        /// <param name="offset">[optional] An offset added to the camera's position.  Default is no offset.</param>
        /// <returns>false if the given object could not be found.</returns>
        public bool SetTrackObject(GameBase trackObject, Point3F offset = null) {
offset = offset ?? new Point3F("0 0 0");
offset.Alloc();             InternalUnsafeMethods.SetTrackObject__Args _args = new InternalUnsafeMethods.SetTrackObject__Args() {
                trackObject = trackObject.ObjectPtr,
                offset = offset.internalStructPtr,
             };
             bool _engineResult = InternalUnsafeMethods.SetTrackObject()(ObjectPtr, _args);
offset.Free();             return _engineResult;
        }

        /// <description>
        /// Set the camera to orbit around a given point.
        /// </description>
        /// <param name="orbitPoint">The point to orbit around.  In the form of "x y z ax ay az aa" such as returned by SceneObject::getTransform().</param>
        /// <param name="minDistance">The minimum distance allowed to the orbit object or point.</param>
        /// <param name="maxDistance">The maximum distance allowed from the orbit object or point.</param>
        /// <param name="initDistance">The initial distance from the orbit object or point.</param>
        /// <param name="offset">[optional] An offset added to the camera's position.  Default is no offset.</param>
        /// <param name="locked">[optional] Indicates the camera does not receive input from the player.  Default is false.</param>
        /// <see cref="Camera::setOrbitMode()" />
        public void SetOrbitPoint(TransformF orbitPoint, float minDistance, float maxDistance, float initDistance, Point3F offset = null, bool locked = false) {
orbitPoint.Alloc();offset = offset ?? new Point3F("0 0 0");
offset.Alloc();             InternalUnsafeMethods.SetOrbitPoint__Args _args = new InternalUnsafeMethods.SetOrbitPoint__Args() {
                orbitPoint = orbitPoint.internalStructPtr,
                minDistance = minDistance,
                maxDistance = maxDistance,
                initDistance = initDistance,
                offset = offset.internalStructPtr,
                locked = locked,
             };
             InternalUnsafeMethods.SetOrbitPoint()(ObjectPtr, _args);
orbitPoint.Free();offset.Free();        }

        /// <description>
        /// Set the camera to orbit around a given object.
        /// </description>
        /// <param name="orbitObject">The object to orbit around.</param>
        /// <param name="rotation">The initial camera rotation about the object in radians in the form of "x y z".</param>
        /// <param name="minDistance">The minimum distance allowed to the orbit object or point.</param>
        /// <param name="maxDistance">The maximum distance allowed from the orbit object or point.</param>
        /// <param name="initDistance">The initial distance from the orbit object or point.</param>
        /// <param name="ownClientObject">[optional] Are we orbiting an object that is owned by us?  Default is false.</param>
        /// <param name="offset">[optional] An offset added to the camera's position.  Default is no offset.</param>
        /// <param name="locked">[optional] Indicates the camera does not receive input from the player.  Default is false.</param>
        /// <returns>false if the given object could not be found.</returns>
        /// <see cref="Camera::setOrbitMode()" />
        public bool SetOrbitObject(GameBase orbitObject, Point3F rotation, float minDistance, float maxDistance, float initDistance, bool ownClientObject = false, Point3F offset = null, bool locked = false) {
rotation.Alloc();offset = offset ?? new Point3F("0 0 0");
offset.Alloc();             InternalUnsafeMethods.SetOrbitObject__Args _args = new InternalUnsafeMethods.SetOrbitObject__Args() {
                orbitObject = orbitObject.ObjectPtr,
                rotation = rotation.internalStructPtr,
                minDistance = minDistance,
                maxDistance = maxDistance,
                initDistance = initDistance,
                ownClientObject = ownClientObject,
                offset = offset.internalStructPtr,
                locked = locked,
             };
             bool _engineResult = InternalUnsafeMethods.SetOrbitObject()(ObjectPtr, _args);
rotation.Free();offset.Free();             return _engineResult;
        }

        /// <description>
        /// Set the camera to orbit around the given object, or if none is given, around the given point.
        /// </description>
        /// <param name="orbitObject">The object to orbit around.  If no object is given (0 or blank string is passed in) use the orbitPoint instead</param>
        /// <param name="orbitPoint">The point to orbit around when no object is given.  In the form of "x y z ax ay az aa" such as returned by SceneObject::getTransform().</param>
        /// <param name="minDistance">The minimum distance allowed to the orbit object or point.</param>
        /// <param name="maxDistance">The maximum distance allowed from the orbit object or point.</param>
        /// <param name="initDistance">The initial distance from the orbit object or point.</param>
        /// <param name="ownClientObj">[optional] Are we orbiting an object that is owned by us?  Default is false.</param>
        /// <param name="offset">[optional] An offset added to the camera's position.  Default is no offset.</param>
        /// <param name="locked">[optional] Indicates the camera does not receive input from the player.  Default is false.</param>
        /// <see cref="Camera::setOrbitObject()" />
        /// <see cref="Camera::setOrbitPoint()" />
        public void SetOrbitMode(GameBase orbitObject, TransformF orbitPoint, float minDistance, float maxDistance, float initDistance, bool ownClientObj = false, Point3F offset = null, bool locked = false) {
orbitPoint.Alloc();offset = offset ?? new Point3F("0 0 0");
offset.Alloc();             InternalUnsafeMethods.SetOrbitMode__Args _args = new InternalUnsafeMethods.SetOrbitMode__Args() {
                orbitObject = orbitObject.ObjectPtr,
                orbitPoint = orbitPoint.internalStructPtr,
                minDistance = minDistance,
                maxDistance = maxDistance,
                initDistance = initDistance,
                ownClientObj = ownClientObj,
                offset = offset.internalStructPtr,
                locked = locked,
             };
             InternalUnsafeMethods.SetOrbitMode()(ObjectPtr, _args);
orbitPoint.Free();offset.Free();        }

        /// <description>
        /// Set the camera's offset.
        /// 
        /// The offset is added to the camera's position when set to CameraMode::OrbitObject.
        /// </description>
        /// <param name="offset">The distance to offset the camera by in the form of "x y z".</param>
        public void SetOffset(Point3F offset) {
offset.Alloc();             InternalUnsafeMethods.SetOffset__Args _args = new InternalUnsafeMethods.SetOffset__Args() {
                offset = offset.internalStructPtr,
             };
             InternalUnsafeMethods.SetOffset()(ObjectPtr, _args);
offset.Free();        }

        /// <description>
        /// Get the camera's offset from its orbit or tracking point.
        /// 
        /// The offset is added to the camera's position when set to CameraMode::OrbitObject.
        /// </description>
        /// <returns>The offset in the form of "x y z".</returns>
        public Point3F GetOffset() {
             InternalUnsafeMethods.GetOffset__Args _args = new InternalUnsafeMethods.GetOffset__Args() {
             };
             Point3F.InternalStruct _engineResult = InternalUnsafeMethods.GetOffset()(ObjectPtr, _args);
             return new Point3F(_engineResult);
        }

        /// <description>
        /// Set the camera's Euler rotation in radians.
        /// </description>
        /// <param name="rot">The rotation in radians in the form of "x y z".</param>
        /// <remarks> Rotation around the Y axis is ignored</remarks>
        public void SetRotation(Point3F rot) {
rot.Alloc();             InternalUnsafeMethods.SetRotation__Args _args = new InternalUnsafeMethods.SetRotation__Args() {
                rot = rot.internalStructPtr,
             };
             InternalUnsafeMethods.SetRotation()(ObjectPtr, _args);
rot.Free();        }

        /// <description>
        /// Get the camera's Euler rotation in radians.
        /// </description>
        /// <returns>The rotation in radians in the form of "x y z".</returns>
        public Point3F GetRotation() {
             InternalUnsafeMethods.GetRotation__Args _args = new InternalUnsafeMethods.GetRotation__Args() {
             };
             Point3F.InternalStruct _engineResult = InternalUnsafeMethods.GetRotation()(ObjectPtr, _args);
             return new Point3F(_engineResult);
        }

        /// <description>
        /// Get the camera's position in the world.
        /// </description>
        /// <returns>The position in the form of "x y z".</returns>
        public Point3F GetPosition() {
             InternalUnsafeMethods.GetPosition__Args _args = new InternalUnsafeMethods.GetPosition__Args() {
             };
             Point3F.InternalStruct _engineResult = InternalUnsafeMethods.GetPosition()(ObjectPtr, _args);
             return new Point3F(_engineResult);
        }

        /// <description>
        /// Returns the current camera control mode.
        /// </description>
        /// <see cref="CameraMotionMode" />
        public CameraMotionMode GetMode() {
             InternalUnsafeMethods.GetMode__Args _args = new InternalUnsafeMethods.GetMode__Args() {
             };
             int _engineResult = InternalUnsafeMethods.GetMode()(ObjectPtr, _args);
             return (CameraMotionMode)_engineResult;
        }

        /// <description>
        /// Get the type info object for the Camera class.
        /// </description>
        /// <returns>The type info object for Camera</returns>
        public static EngineTypeInfo StaticGetType() {
             InternalUnsafeMethods.StaticGetType__Args _args = new InternalUnsafeMethods.StaticGetType__Args() {
             };
             IntPtr _engineResult = InternalUnsafeMethods.StaticGetType()(_args);
             return new EngineTypeInfo(_engineResult);
        }


        /// <value>
        /// <description>
        /// The current camera control mode.
        /// </description>
        /// </value>
        public CameraMotionMode ControlMode {
            get => GenericMarshal.StringTo<CameraMotionMode>(GetFieldValue("controlMode"));
            set => SetFieldValue("controlMode", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Apply smoothing (acceleration and damping) to camera movements.
        /// </description>
        /// </value>
        public bool NewtonMode {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("newtonMode"));
            set => SetFieldValue("newtonMode", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Apply smoothing (acceleration and damping) to camera rotations.
        /// </description>
        /// </value>
        public bool NewtonRotation {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("newtonRotation"));
            set => SetFieldValue("newtonRotation", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// The camera's mass (Newton mode only).  Default value is 10.
        /// </description>
        /// </value>
        public float Mass {
            get => GenericMarshal.StringTo<float>(GetFieldValue("mass"));
            set => SetFieldValue("mass", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Drag on camera when moving (Newton mode only).  Default value is 2.
        /// </description>
        /// </value>
        public float Drag {
            get => GenericMarshal.StringTo<float>(GetFieldValue("drag"));
            set => SetFieldValue("drag", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Force applied on camera when asked to move (Newton mode only).  Default value is 500.
        /// </description>
        /// </value>
        public float Force {
            get => GenericMarshal.StringTo<float>(GetFieldValue("force"));
            set => SetFieldValue("force", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Drag on camera when rotating (Newton mode only).  Default value is 2.
        /// </description>
        /// </value>
        public float AngularDrag {
            get => GenericMarshal.StringTo<float>(GetFieldValue("angularDrag"));
            set => SetFieldValue("angularDrag", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Force applied on camera when asked to rotate (Newton mode only).  Default value is 100.
        /// </description>
        /// </value>
        public float AngularForce {
            get => GenericMarshal.StringTo<float>(GetFieldValue("angularForce"));
            set => SetFieldValue("angularForce", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Speed multiplier when triggering the accelerator (Newton mode only).  Default value is 2.
        /// </description>
        /// </value>
        public float SpeedMultiplier {
            get => GenericMarshal.StringTo<float>(GetFieldValue("speedMultiplier"));
            set => SetFieldValue("speedMultiplier", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Speed multiplier when triggering the brake (Newton mode only).  Default value is 2.
        /// </description>
        /// </value>
        public float BrakeMultiplier {
            get => GenericMarshal.StringTo<float>(GetFieldValue("brakeMultiplier"));
            set => SetFieldValue("brakeMultiplier", GenericMarshal.ToString(value));
        }
    }
}