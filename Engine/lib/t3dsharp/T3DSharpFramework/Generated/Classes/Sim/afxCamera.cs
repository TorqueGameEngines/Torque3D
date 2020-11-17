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
    /// <summary>A 3rd person camera object.</summary>
    /// <description>
    /// 
    /// </description>
    public unsafe class afxCamera : ShapeBase {
        public afxCamera(bool pRegister = false) 
            : base(pRegister) {
        }
        
        public afxCamera(string pName, bool pRegister) 
            : this(false) {
            Name = pName;
            if (pRegister) {
                RegisterObject();
            }
        }
        
        public afxCamera(string pName) 
            : this(pName, false) {
        }
        
        public afxCamera(string pName, string pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(Engine.Sim.FindObject<SimObject>(pParent));
        }
        
        public afxCamera(string pName, SimObject pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(pParent);
        }
        
        public afxCamera(SimObject pObj) 
            : base(pObj) {
        }
        
        public afxCamera(IntPtr pObj) 
            : base(pObj) {
        }
        
		protected override void CreateObjectPtr()
		{
			ObjectPtr = InternalUnsafeMethods.Create()(new InternalUnsafeMethods.Create__Args());
		}

        #region UnsafeNativeMethods
        new internal struct InternalUnsafeMethods {
            [StructLayout(LayoutKind.Sequential)]
            internal struct GetMode__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            
            internal delegate IntPtr _GetMode(IntPtr _this, GetMode__Args args);
            private static _GetMode _GetModeFunc;
            internal static _GetMode GetMode() {
                if (_GetModeFunc == null) {
                    _GetModeFunc =
                        (_GetMode)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnafxCamera_getMode"), typeof(_GetMode));
                }
                
                return _GetModeFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct SetThirdPersonSnap__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _SetThirdPersonSnap(IntPtr _this, SetThirdPersonSnap__Args args);
            private static _SetThirdPersonSnap _SetThirdPersonSnapFunc;
            internal static _SetThirdPersonSnap SetThirdPersonSnap() {
                if (_SetThirdPersonSnapFunc == null) {
                    _SetThirdPersonSnapFunc =
                        (_SetThirdPersonSnap)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnafxCamera_setThirdPersonSnap"), typeof(_SetThirdPersonSnap));
                }
                
                return _SetThirdPersonSnapFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct SetThirdPersonMode__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _SetThirdPersonMode(IntPtr _this, SetThirdPersonMode__Args args);
            private static _SetThirdPersonMode _SetThirdPersonModeFunc;
            internal static _SetThirdPersonMode SetThirdPersonMode() {
                if (_SetThirdPersonModeFunc == null) {
                    _SetThirdPersonModeFunc =
                        (_SetThirdPersonMode)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnafxCamera_setThirdPersonMode"), typeof(_SetThirdPersonMode));
                }
                
                return _SetThirdPersonModeFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct GetThirdPersonCOIOffset__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate Point3F.InternalStruct _GetThirdPersonCOIOffset(IntPtr _this, GetThirdPersonCOIOffset__Args args);
            private static _GetThirdPersonCOIOffset _GetThirdPersonCOIOffsetFunc;
            internal static _GetThirdPersonCOIOffset GetThirdPersonCOIOffset() {
                if (_GetThirdPersonCOIOffsetFunc == null) {
                    _GetThirdPersonCOIOffsetFunc =
                        (_GetThirdPersonCOIOffset)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnafxCamera_getThirdPersonCOIOffset"), typeof(_GetThirdPersonCOIOffset));
                }
                
                return _GetThirdPersonCOIOffsetFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct GetThirdPersonOffset__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate Point3F.InternalStruct _GetThirdPersonOffset(IntPtr _this, GetThirdPersonOffset__Args args);
            private static _GetThirdPersonOffset _GetThirdPersonOffsetFunc;
            internal static _GetThirdPersonOffset GetThirdPersonOffset() {
                if (_GetThirdPersonOffsetFunc == null) {
                    _GetThirdPersonOffsetFunc =
                        (_GetThirdPersonOffset)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnafxCamera_getThirdPersonOffset"), typeof(_GetThirdPersonOffset));
                }
                
                return _GetThirdPersonOffsetFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct SetThirdPersonOffset__Args
            {
                internal IntPtr offset;
                internal IntPtr coi_offset;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _SetThirdPersonOffset(IntPtr _this, SetThirdPersonOffset__Args args);
            private static _SetThirdPersonOffset _SetThirdPersonOffsetFunc;
            internal static _SetThirdPersonOffset SetThirdPersonOffset() {
                if (_SetThirdPersonOffsetFunc == null) {
                    _SetThirdPersonOffsetFunc =
                        (_SetThirdPersonOffset)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnafxCamera_setThirdPersonOffset"), typeof(_SetThirdPersonOffset));
                }
                
                return _SetThirdPersonOffsetFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct GetThirdPersonAngle__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate float _GetThirdPersonAngle(IntPtr _this, GetThirdPersonAngle__Args args);
            private static _GetThirdPersonAngle _GetThirdPersonAngleFunc;
            internal static _GetThirdPersonAngle GetThirdPersonAngle() {
                if (_GetThirdPersonAngleFunc == null) {
                    _GetThirdPersonAngleFunc =
                        (_GetThirdPersonAngle)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnafxCamera_getThirdPersonAngle"), typeof(_GetThirdPersonAngle));
                }
                
                return _GetThirdPersonAngleFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct SetThirdPersonAngle__Args
            {
                internal float distance;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            [return: MarshalAs(UnmanagedType.I1)]
            internal delegate bool _SetThirdPersonAngle(IntPtr _this, SetThirdPersonAngle__Args args);
            private static _SetThirdPersonAngle _SetThirdPersonAngleFunc;
            internal static _SetThirdPersonAngle SetThirdPersonAngle() {
                if (_SetThirdPersonAngleFunc == null) {
                    _SetThirdPersonAngleFunc =
                        (_SetThirdPersonAngle)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnafxCamera_setThirdPersonAngle"), typeof(_SetThirdPersonAngle));
                }
                
                return _SetThirdPersonAngleFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct GetThirdPersonDistance__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate float _GetThirdPersonDistance(IntPtr _this, GetThirdPersonDistance__Args args);
            private static _GetThirdPersonDistance _GetThirdPersonDistanceFunc;
            internal static _GetThirdPersonDistance GetThirdPersonDistance() {
                if (_GetThirdPersonDistanceFunc == null) {
                    _GetThirdPersonDistanceFunc =
                        (_GetThirdPersonDistance)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnafxCamera_getThirdPersonDistance"), typeof(_GetThirdPersonDistance));
                }
                
                return _GetThirdPersonDistanceFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct SetThirdPersonDistance__Args
            {
                internal float distance;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            [return: MarshalAs(UnmanagedType.I1)]
            internal delegate bool _SetThirdPersonDistance(IntPtr _this, SetThirdPersonDistance__Args args);
            private static _SetThirdPersonDistance _SetThirdPersonDistanceFunc;
            internal static _SetThirdPersonDistance SetThirdPersonDistance() {
                if (_SetThirdPersonDistanceFunc == null) {
                    _SetThirdPersonDistanceFunc =
                        (_SetThirdPersonDistance)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnafxCamera_setThirdPersonDistance"), typeof(_SetThirdPersonDistance));
                }
                
                return _SetThirdPersonDistanceFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct SetCameraSubject__Args
            {
                internal IntPtr subject;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            [return: MarshalAs(UnmanagedType.I1)]
            internal delegate bool _SetCameraSubject(IntPtr _this, SetCameraSubject__Args args);
            private static _SetCameraSubject _SetCameraSubjectFunc;
            internal static _SetCameraSubject SetCameraSubject() {
                if (_SetCameraSubjectFunc == null) {
                    _SetCameraSubjectFunc =
                        (_SetCameraSubject)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnafxCamera_setCameraSubject"), typeof(_SetCameraSubject));
                }
                
                return _SetCameraSubjectFunc;
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
                                "fnafxCamera_getPosition"), typeof(_GetPosition));
                }
                
                return _GetPositionFunc;
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
                                "fnafxCamera_setFlyMode"), typeof(_SetFlyMode));
                }
                
                return _SetFlyModeFunc;
            }


            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _SetOrbitMode(IntPtr _this, ref StringVector.InternalStruct args);
            private static _SetOrbitMode _SetOrbitModeFunc;
            internal static _SetOrbitMode SetOrbitMode() {
                if (_SetOrbitModeFunc == null) {
                    _SetOrbitModeFunc =
                        (_SetOrbitMode)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnafxCamera_setOrbitMode"), typeof(_SetOrbitMode));
                }
                
                return _SetOrbitModeFunc;
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
                                "fnafxCamera_staticGetType"), typeof(_StaticGetType));
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
                                "fnafxCamera_create"), typeof(_Create));
                }
                
                return _CreateFunc;
            }
        }
        #endregion

        /// 
        public string GetMode() {
             InternalUnsafeMethods.GetMode__Args _args = new InternalUnsafeMethods.GetMode__Args() {
             };
             IntPtr _engineResult = InternalUnsafeMethods.GetMode()(ObjectPtr, _args);
             return StringMarshal.IntPtrToUtf8String(_engineResult);
        }

        /// 
        public void SetThirdPersonSnap() {
             InternalUnsafeMethods.SetThirdPersonSnap__Args _args = new InternalUnsafeMethods.SetThirdPersonSnap__Args() {
             };
             InternalUnsafeMethods.SetThirdPersonSnap()(ObjectPtr, _args);
        }

        /// 
        public void SetThirdPersonMode() {
             InternalUnsafeMethods.SetThirdPersonMode__Args _args = new InternalUnsafeMethods.SetThirdPersonMode__Args() {
             };
             InternalUnsafeMethods.SetThirdPersonMode()(ObjectPtr, _args);
        }

        /// 
        public Point3F GetThirdPersonCOIOffset() {
             InternalUnsafeMethods.GetThirdPersonCOIOffset__Args _args = new InternalUnsafeMethods.GetThirdPersonCOIOffset__Args() {
             };
             Point3F.InternalStruct _engineResult = InternalUnsafeMethods.GetThirdPersonCOIOffset()(ObjectPtr, _args);
             return new Point3F(_engineResult);
        }

        /// 
        public Point3F GetThirdPersonOffset() {
             InternalUnsafeMethods.GetThirdPersonOffset__Args _args = new InternalUnsafeMethods.GetThirdPersonOffset__Args() {
             };
             Point3F.InternalStruct _engineResult = InternalUnsafeMethods.GetThirdPersonOffset()(ObjectPtr, _args);
             return new Point3F(_engineResult);
        }

        /// 
        public void SetThirdPersonOffset(Point3F offset, Point3F coi_offset = null) {
offset.Alloc();coi_offset = coi_offset ?? new Point3F("3.40282e+38 3.40282e+38 3.40282e+38");
coi_offset.Alloc();             InternalUnsafeMethods.SetThirdPersonOffset__Args _args = new InternalUnsafeMethods.SetThirdPersonOffset__Args() {
                offset = offset.internalStructPtr,
                coi_offset = coi_offset.internalStructPtr,
             };
             InternalUnsafeMethods.SetThirdPersonOffset()(ObjectPtr, _args);
offset.Free();coi_offset.Free();        }

        /// 
        public float GetThirdPersonAngle() {
             InternalUnsafeMethods.GetThirdPersonAngle__Args _args = new InternalUnsafeMethods.GetThirdPersonAngle__Args() {
             };
             float _engineResult = InternalUnsafeMethods.GetThirdPersonAngle()(ObjectPtr, _args);
             return _engineResult;
        }

        /// 
        public bool SetThirdPersonAngle(float distance) {
             InternalUnsafeMethods.SetThirdPersonAngle__Args _args = new InternalUnsafeMethods.SetThirdPersonAngle__Args() {
                distance = distance,
             };
             bool _engineResult = InternalUnsafeMethods.SetThirdPersonAngle()(ObjectPtr, _args);
             return _engineResult;
        }

        /// 
        public float GetThirdPersonDistance() {
             InternalUnsafeMethods.GetThirdPersonDistance__Args _args = new InternalUnsafeMethods.GetThirdPersonDistance__Args() {
             };
             float _engineResult = InternalUnsafeMethods.GetThirdPersonDistance()(ObjectPtr, _args);
             return _engineResult;
        }

        /// 
        public bool SetThirdPersonDistance(float distance) {
             InternalUnsafeMethods.SetThirdPersonDistance__Args _args = new InternalUnsafeMethods.SetThirdPersonDistance__Args() {
                distance = distance,
             };
             bool _engineResult = InternalUnsafeMethods.SetThirdPersonDistance()(ObjectPtr, _args);
             return _engineResult;
        }

        /// 
        public bool SetCameraSubject(SceneObject subject) {
             InternalUnsafeMethods.SetCameraSubject__Args _args = new InternalUnsafeMethods.SetCameraSubject__Args() {
                subject = subject.ObjectPtr,
             };
             bool _engineResult = InternalUnsafeMethods.SetCameraSubject()(ObjectPtr, _args);
             return _engineResult;
        }

        /// <summary>Get the position of the camera.</summary>
        /// <description>
        /// 
        /// </description>
        /// <returns>The position of the camera.</returns>
        public Point3F GetPosition() {
             InternalUnsafeMethods.GetPosition__Args _args = new InternalUnsafeMethods.GetPosition__Args() {
             };
             Point3F.InternalStruct _engineResult = InternalUnsafeMethods.GetPosition()(ObjectPtr, _args);
             return new Point3F(_engineResult);
        }

        /// <summary>Set the camera to be able to fly freely.</summary>
        public void SetFlyMode() {
             InternalUnsafeMethods.SetFlyMode__Args _args = new InternalUnsafeMethods.SetFlyMode__Args() {
             };
             InternalUnsafeMethods.SetFlyMode()(ObjectPtr, _args);
        }

        /// <description>
        /// (GameBase orbitObject, TransformF mat, float minDistance, float maxDistance, float curDistance, bool ownClientObject)Set the camera to orbit around some given object.
        /// </description>
        /// <param name="orbitObject">Object we want to orbit.</param>
        /// <param name="mat">A set of fields: posX posY posZ aaX aaY aaZ aaTheta</param>
        /// <param name="minDistance">Minimum distance to keep from object.</param>
        /// <param name="maxDistance">Maximum distance to keep from object.</param>
        /// <param name="curDistance">Distance to set initially from object.</param>
        /// <param name="ownClientObj">Are we observing an object owned by us?</param>
        public void SetOrbitMode(params string[] args) { 
            List<string> _argList = new List<string>() {"", ""};
            _argList.AddRange(args);

            StringVector nativeVecArgs = new StringVector {
                ElementCount = (uint)_argList.Count,
                Array = _argList.ToArray(),
                ArraySize = (uint)_argList.Count
            };
            nativeVecArgs.Alloc();
            InternalUnsafeMethods.SetOrbitMode()(ObjectPtr, ref nativeVecArgs.internalStruct);
            nativeVecArgs.Free();

        }

        /// <description>
        /// Get the type info object for the afxCamera class.
        /// </description>
        /// <returns>The type info object for afxCamera</returns>
        public static EngineTypeInfo StaticGetType() {
             InternalUnsafeMethods.StaticGetType__Args _args = new InternalUnsafeMethods.StaticGetType__Args() {
             };
             IntPtr _engineResult = InternalUnsafeMethods.StaticGetType()(_args);
             return new EngineTypeInfo(_engineResult);
        }
    }
}