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
    /// <summary>A networkable object that exists in the 3D world.</summary>
    /// <description>
    /// The SceneObject class provides the foundation for 3D objects in the Engine.  It exposes the functionality for:
    /// 
    /// <ul><li>Position, rotation and scale within the world.</li><li>Working with a scene graph (in the Zone and Portal sections), allowing efficient and robust rendering of the game scene.</li><li>Various helper functions, including functions to get bounding information and momentum/velocity.</li><li>Mounting one SceneObject to another.</li><li>An interface for collision detection, as well as ray casting.</li><li>Lighting. SceneObjects can register lights both at lightmap generation time, and dynamic lights at runtime (for special effects, such as from flame or a projectile, or from an explosion).</li></ul>
    /// 
    /// You do not typically work with SceneObjects themselves.  The SceneObject provides a reference within the game world (the scene), but does not render to the client on its own.  The same is true of collision detection beyond that of the bounding box.  Instead you use one of the many classes that derrive from SceneObject, such as TSStatic.
    /// </description>
    public unsafe class SceneObject : NetObject {
        public SceneObject(bool pRegister = false) 
            : base(pRegister) {
        }
        
        public SceneObject(string pName, bool pRegister) 
            : this(false) {
            Name = pName;
            if (pRegister) {
                RegisterObject();
            }
        }
        
        public SceneObject(string pName) 
            : this(pName, false) {
        }
        
        public SceneObject(string pName, string pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(Engine.Sim.FindObject<SimObject>(pParent));
        }
        
        public SceneObject(string pName, SimObject pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(pParent);
        }
        
        public SceneObject(SimObject pObj) 
            : base(pObj) {
        }
        
        public SceneObject(IntPtr pObj) 
            : base(pObj) {
        }
        
		protected override void CreateObjectPtr()
		{
			ObjectPtr = InternalUnsafeMethods.Create()(new InternalUnsafeMethods.Create__Args());
		}

        #region UnsafeNativeMethods
        new internal struct InternalUnsafeMethods {
            [StructLayout(LayoutKind.Sequential)]
            internal struct GetSpeed__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate float _GetSpeed(IntPtr _this, GetSpeed__Args args);
            private static _GetSpeed _GetSpeedFunc;
            internal static _GetSpeed GetSpeed() {
                if (_GetSpeedFunc == null) {
                    _GetSpeedFunc =
                        (_GetSpeed)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnSceneObject_getSpeed"), typeof(_GetSpeed));
                }
                
                return _GetSpeedFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct DetachChild__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string _subObject;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            [return: MarshalAs(UnmanagedType.I1)]
            internal delegate bool _DetachChild(IntPtr _this, DetachChild__Args args);
            private static _DetachChild _DetachChildFunc;
            internal static _DetachChild DetachChild() {
                if (_DetachChildFunc == null) {
                    _DetachChildFunc =
                        (_DetachChild)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnSceneObject_detachChild"), typeof(_DetachChild));
                }
                
                return _DetachChildFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct AttachChild__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string _subObject;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            [return: MarshalAs(UnmanagedType.I1)]
            internal delegate bool _AttachChild(IntPtr _this, AttachChild__Args args);
            private static _AttachChild _AttachChildFunc;
            internal static _AttachChild AttachChild() {
                if (_AttachChildFunc == null) {
                    _AttachChildFunc =
                        (_AttachChild)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnSceneObject_attachChild"), typeof(_AttachChild));
                }
                
                return _AttachChildFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct GetParent__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate int _GetParent(IntPtr _this, GetParent__Args args);
            private static _GetParent _GetParentFunc;
            internal static _GetParent GetParent() {
                if (_GetParentFunc == null) {
                    _GetParentFunc =
                        (_GetParent)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnSceneObject_getParent"), typeof(_GetParent));
                }
                
                return _GetParentFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct AttachToParent__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string _sceneObject;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            [return: MarshalAs(UnmanagedType.I1)]
            internal delegate bool _AttachToParent(IntPtr _this, AttachToParent__Args args);
            private static _AttachToParent _AttachToParentFunc;
            internal static _AttachToParent AttachToParent() {
                if (_AttachToParentFunc == null) {
                    _AttachToParentFunc =
                        (_AttachToParent)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnSceneObject_attachToParent"), typeof(_AttachToParent));
                }
                
                return _AttachToParentFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct AttachChildAt__Args
            {
                internal IntPtr _subObject;
                internal IntPtr _offset;
                internal int _node;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            [return: MarshalAs(UnmanagedType.I1)]
            internal delegate bool _AttachChildAt(IntPtr _this, AttachChildAt__Args args);
            private static _AttachChildAt _AttachChildAtFunc;
            internal static _AttachChildAt AttachChildAt() {
                if (_AttachChildAtFunc == null) {
                    _AttachChildAtFunc =
                        (_AttachChildAt)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnSceneObject_attachChildAt"), typeof(_AttachChildAt));
                }
                
                return _AttachChildAtFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct GetChild__Args
            {
                internal int _index;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate int _GetChild(IntPtr _this, GetChild__Args args);
            private static _GetChild _GetChildFunc;
            internal static _GetChild GetChild() {
                if (_GetChildFunc == null) {
                    _GetChildFunc =
                        (_GetChild)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnSceneObject_getChild"), typeof(_GetChild));
                }
                
                return _GetChildFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct GetNumProgeny__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate int _GetNumProgeny(IntPtr _this, GetNumProgeny__Args args);
            private static _GetNumProgeny _GetNumProgenyFunc;
            internal static _GetNumProgeny GetNumProgeny() {
                if (_GetNumProgenyFunc == null) {
                    _GetNumProgenyFunc =
                        (_GetNumProgeny)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnSceneObject_getNumProgeny"), typeof(_GetNumProgeny));
                }
                
                return _GetNumProgenyFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct GetNumChildren__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate int _GetNumChildren(IntPtr _this, GetNumChildren__Args args);
            private static _GetNumChildren _GetNumChildrenFunc;
            internal static _GetNumChildren GetNumChildren() {
                if (_GetNumChildrenFunc == null) {
                    _GetNumChildrenFunc =
                        (_GetNumChildren)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnSceneObject_getNumChildren"), typeof(_GetNumChildren));
                }
                
                return _GetNumChildrenFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct SetForwardVector__Args
            {
                internal IntPtr newForward;
                internal IntPtr upVector;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _SetForwardVector(IntPtr _this, SetForwardVector__Args args);
            private static _SetForwardVector _SetForwardVectorFunc;
            internal static _SetForwardVector SetForwardVector() {
                if (_SetForwardVectorFunc == null) {
                    _SetForwardVectorFunc =
                        (_SetForwardVector)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnSceneObject_setForwardVector"), typeof(_SetForwardVector));
                }
                
                return _SetForwardVectorFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct IsGlobalBounds__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            [return: MarshalAs(UnmanagedType.I1)]
            internal delegate bool _IsGlobalBounds(IntPtr _this, IsGlobalBounds__Args args);
            private static _IsGlobalBounds _IsGlobalBoundsFunc;
            internal static _IsGlobalBounds IsGlobalBounds() {
                if (_IsGlobalBoundsFunc == null) {
                    _IsGlobalBoundsFunc =
                        (_IsGlobalBounds)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnSceneObject_isGlobalBounds"), typeof(_IsGlobalBounds));
                }
                
                return _IsGlobalBoundsFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct GetObjectBox__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate Box3F.InternalStruct _GetObjectBox(IntPtr _this, GetObjectBox__Args args);
            private static _GetObjectBox _GetObjectBoxFunc;
            internal static _GetObjectBox GetObjectBox() {
                if (_GetObjectBoxFunc == null) {
                    _GetObjectBoxFunc =
                        (_GetObjectBox)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnSceneObject_getObjectBox"), typeof(_GetObjectBox));
                }
                
                return _GetObjectBoxFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct GetWorldBoxCenter__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate Point3F.InternalStruct _GetWorldBoxCenter(IntPtr _this, GetWorldBoxCenter__Args args);
            private static _GetWorldBoxCenter _GetWorldBoxCenterFunc;
            internal static _GetWorldBoxCenter GetWorldBoxCenter() {
                if (_GetWorldBoxCenterFunc == null) {
                    _GetWorldBoxCenterFunc =
                        (_GetWorldBoxCenter)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnSceneObject_getWorldBoxCenter"), typeof(_GetWorldBoxCenter));
                }
                
                return _GetWorldBoxCenterFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct GetWorldBox__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate Box3F.InternalStruct _GetWorldBox(IntPtr _this, GetWorldBox__Args args);
            private static _GetWorldBox _GetWorldBoxFunc;
            internal static _GetWorldBox GetWorldBox() {
                if (_GetWorldBoxFunc == null) {
                    _GetWorldBoxFunc =
                        (_GetWorldBox)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnSceneObject_getWorldBox"), typeof(_GetWorldBox));
                }
                
                return _GetWorldBoxFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct SetScale__Args
            {
                internal IntPtr scale;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _SetScale(IntPtr _this, SetScale__Args args);
            private static _SetScale _SetScaleFunc;
            internal static _SetScale SetScale() {
                if (_SetScaleFunc == null) {
                    _SetScaleFunc =
                        (_SetScale)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnSceneObject_setScale"), typeof(_SetScale));
                }
                
                return _SetScaleFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct GetScale__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate Point3F.InternalStruct _GetScale(IntPtr _this, GetScale__Args args);
            private static _GetScale _GetScaleFunc;
            internal static _GetScale GetScale() {
                if (_GetScaleFunc == null) {
                    _GetScaleFunc =
                        (_GetScale)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnSceneObject_getScale"), typeof(_GetScale));
                }
                
                return _GetScaleFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct SetTransform__Args
            {
                internal IntPtr txfm;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _SetTransform(IntPtr _this, SetTransform__Args args);
            private static _SetTransform _SetTransformFunc;
            internal static _SetTransform SetTransform() {
                if (_SetTransformFunc == null) {
                    _SetTransformFunc =
                        (_SetTransform)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnSceneObject_setTransform"), typeof(_SetTransform));
                }
                
                return _SetTransformFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct GetUpVector__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate Point3F.InternalStruct _GetUpVector(IntPtr _this, GetUpVector__Args args);
            private static _GetUpVector _GetUpVectorFunc;
            internal static _GetUpVector GetUpVector() {
                if (_GetUpVectorFunc == null) {
                    _GetUpVectorFunc =
                        (_GetUpVector)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnSceneObject_getUpVector"), typeof(_GetUpVector));
                }
                
                return _GetUpVectorFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct GetRightVector__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate Point3F.InternalStruct _GetRightVector(IntPtr _this, GetRightVector__Args args);
            private static _GetRightVector _GetRightVectorFunc;
            internal static _GetRightVector GetRightVector() {
                if (_GetRightVectorFunc == null) {
                    _GetRightVectorFunc =
                        (_GetRightVector)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnSceneObject_getRightVector"), typeof(_GetRightVector));
                }
                
                return _GetRightVectorFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct GetForwardVector__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate Point3F.InternalStruct _GetForwardVector(IntPtr _this, GetForwardVector__Args args);
            private static _GetForwardVector _GetForwardVectorFunc;
            internal static _GetForwardVector GetForwardVector() {
                if (_GetForwardVectorFunc == null) {
                    _GetForwardVectorFunc =
                        (_GetForwardVector)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnSceneObject_getForwardVector"), typeof(_GetForwardVector));
                }
                
                return _GetForwardVectorFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct GetEulerRotation__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate Point3F.InternalStruct _GetEulerRotation(IntPtr _this, GetEulerRotation__Args args);
            private static _GetEulerRotation _GetEulerRotationFunc;
            internal static _GetEulerRotation GetEulerRotation() {
                if (_GetEulerRotationFunc == null) {
                    _GetEulerRotationFunc =
                        (_GetEulerRotation)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnSceneObject_getEulerRotation"), typeof(_GetEulerRotation));
                }
                
                return _GetEulerRotationFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct SetPosition__Args
            {
                internal IntPtr pos;
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
                                "fnSceneObject_setPosition"), typeof(_SetPosition));
                }
                
                return _SetPositionFunc;
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
                                "fnSceneObject_getPosition"), typeof(_GetPosition));
                }
                
                return _GetPositionFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct GetInverseTransform__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate TransformF.InternalStruct _GetInverseTransform(IntPtr _this, GetInverseTransform__Args args);
            private static _GetInverseTransform _GetInverseTransformFunc;
            internal static _GetInverseTransform GetInverseTransform() {
                if (_GetInverseTransformFunc == null) {
                    _GetInverseTransformFunc =
                        (_GetInverseTransform)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnSceneObject_getInverseTransform"), typeof(_GetInverseTransform));
                }
                
                return _GetInverseTransformFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct GetTransform__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate TransformF.InternalStruct _GetTransform(IntPtr _this, GetTransform__Args args);
            private static _GetTransform _GetTransformFunc;
            internal static _GetTransform GetTransform() {
                if (_GetTransformFunc == null) {
                    _GetTransformFunc =
                        (_GetTransform)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnSceneObject_getTransform"), typeof(_GetTransform));
                }
                
                return _GetTransformFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct GetMountNodeObject__Args
            {
                internal int node;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate int _GetMountNodeObject(IntPtr _this, GetMountNodeObject__Args args);
            private static _GetMountNodeObject _GetMountNodeObjectFunc;
            internal static _GetMountNodeObject GetMountNodeObject() {
                if (_GetMountNodeObjectFunc == null) {
                    _GetMountNodeObjectFunc =
                        (_GetMountNodeObject)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnSceneObject_getMountNodeObject"), typeof(_GetMountNodeObject));
                }
                
                return _GetMountNodeObjectFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct GetMountedObjectNode__Args
            {
                internal int slot;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate int _GetMountedObjectNode(IntPtr _this, GetMountedObjectNode__Args args);
            private static _GetMountedObjectNode _GetMountedObjectNodeFunc;
            internal static _GetMountedObjectNode GetMountedObjectNode() {
                if (_GetMountedObjectNodeFunc == null) {
                    _GetMountedObjectNodeFunc =
                        (_GetMountedObjectNode)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnSceneObject_getMountedObjectNode"), typeof(_GetMountedObjectNode));
                }
                
                return _GetMountedObjectNodeFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct GetMountedObject__Args
            {
                internal int slot;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate int _GetMountedObject(IntPtr _this, GetMountedObject__Args args);
            private static _GetMountedObject _GetMountedObjectFunc;
            internal static _GetMountedObject GetMountedObject() {
                if (_GetMountedObjectFunc == null) {
                    _GetMountedObjectFunc =
                        (_GetMountedObject)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnSceneObject_getMountedObject"), typeof(_GetMountedObject));
                }
                
                return _GetMountedObjectFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct GetMountedObjectCount__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate int _GetMountedObjectCount(IntPtr _this, GetMountedObjectCount__Args args);
            private static _GetMountedObjectCount _GetMountedObjectCountFunc;
            internal static _GetMountedObjectCount GetMountedObjectCount() {
                if (_GetMountedObjectCountFunc == null) {
                    _GetMountedObjectCountFunc =
                        (_GetMountedObjectCount)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnSceneObject_getMountedObjectCount"), typeof(_GetMountedObjectCount));
                }
                
                return _GetMountedObjectCountFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct GetObjectMount__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate int _GetObjectMount(IntPtr _this, GetObjectMount__Args args);
            private static _GetObjectMount _GetObjectMountFunc;
            internal static _GetObjectMount GetObjectMount() {
                if (_GetObjectMountFunc == null) {
                    _GetObjectMountFunc =
                        (_GetObjectMount)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnSceneObject_getObjectMount"), typeof(_GetObjectMount));
                }
                
                return _GetObjectMountFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct IsMounted__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            [return: MarshalAs(UnmanagedType.I1)]
            internal delegate bool _IsMounted(IntPtr _this, IsMounted__Args args);
            private static _IsMounted _IsMountedFunc;
            internal static _IsMounted IsMounted() {
                if (_IsMountedFunc == null) {
                    _IsMountedFunc =
                        (_IsMounted)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnSceneObject_isMounted"), typeof(_IsMounted));
                }
                
                return _IsMountedFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct Unmount__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _Unmount(IntPtr _this, Unmount__Args args);
            private static _Unmount _UnmountFunc;
            internal static _Unmount Unmount() {
                if (_UnmountFunc == null) {
                    _UnmountFunc =
                        (_Unmount)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnSceneObject_unmount"), typeof(_Unmount));
                }
                
                return _UnmountFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct UnmountObject__Args
            {
                internal IntPtr target;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            [return: MarshalAs(UnmanagedType.I1)]
            internal delegate bool _UnmountObject(IntPtr _this, UnmountObject__Args args);
            private static _UnmountObject _UnmountObjectFunc;
            internal static _UnmountObject UnmountObject() {
                if (_UnmountObjectFunc == null) {
                    _UnmountObjectFunc =
                        (_UnmountObject)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnSceneObject_unmountObject"), typeof(_UnmountObject));
                }
                
                return _UnmountObjectFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct MountObject__Args
            {
                internal IntPtr objB;
                internal int slot;
                internal IntPtr txfm;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            [return: MarshalAs(UnmanagedType.I1)]
            internal delegate bool _MountObject(IntPtr _this, MountObject__Args args);
            private static _MountObject _MountObjectFunc;
            internal static _MountObject MountObject() {
                if (_MountObjectFunc == null) {
                    _MountObjectFunc =
                        (_MountObject)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnSceneObject_mountObject"), typeof(_MountObject));
                }
                
                return _MountObjectFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct GetType__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate int _GetType(IntPtr _this, GetType__Args args);
            private static _GetType _GetTypeFunc;
            internal static _GetType GetType() {
                if (_GetTypeFunc == null) {
                    _GetTypeFunc =
                        (_GetType)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnSceneObject_getType"), typeof(_GetType));
                }
                
                return _GetTypeFunc;
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
                                "fnSceneObject_staticGetType"), typeof(_StaticGetType));
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
                                "fnSceneObject_create"), typeof(_Create));
                }
                
                return _CreateFunc;
            }
        }
        #endregion

        /// <description>
        /// Returns the velocity of a scene-object.
        /// </description>
        public float GetSpeed() {
             InternalUnsafeMethods.GetSpeed__Args _args = new InternalUnsafeMethods.GetSpeed__Args() {
             };
             float _engineResult = InternalUnsafeMethods.GetSpeed()(ObjectPtr, _args);
             return _engineResult;
        }

        /// <description>
        /// SceneObject subObject
        /// </description>
        public bool DetachChild(string _subObject) {
             InternalUnsafeMethods.DetachChild__Args _args = new InternalUnsafeMethods.DetachChild__Args() {
                _subObject = _subObject,
             };
             bool _engineResult = InternalUnsafeMethods.DetachChild()(ObjectPtr, _args);
             return _engineResult;
        }

        /// <description>
        /// (SceneObject subObject)attach an object to this one, preserving its present transform.
        /// </description>
        public bool AttachChild(string _subObject) {
             InternalUnsafeMethods.AttachChild__Args _args = new InternalUnsafeMethods.AttachChild__Args() {
                _subObject = _subObject,
             };
             bool _engineResult = InternalUnsafeMethods.AttachChild()(ObjectPtr, _args);
             return _engineResult;
        }

        /// <description>
        /// returns ID of parent SceneObject
        /// </description>
        public int GetParent() {
             InternalUnsafeMethods.GetParent__Args _args = new InternalUnsafeMethods.GetParent__Args() {
             };
             int _engineResult = InternalUnsafeMethods.GetParent()(ObjectPtr, _args);
             return _engineResult;
        }

        /// <description>
        /// attachToParent(SceneObject)specify a null or non-null parent
        /// </description>
        public bool AttachToParent(string _sceneObject) {
             InternalUnsafeMethods.AttachToParent__Args _args = new InternalUnsafeMethods.AttachToParent__Args() {
                _sceneObject = _sceneObject,
             };
             bool _engineResult = InternalUnsafeMethods.AttachToParent()(ObjectPtr, _args);
             return _engineResult;
        }

        /// <description>
        /// (SceneObject subObject, MatrixF offset, S32 offset)Mount object to this one with the specified offset expressed in our coordinate space.
        /// </description>
        public bool AttachChildAt(SceneObject _subObject = null, MatrixF _offset = null, int _node = 0) {
_offset = _offset ?? new MatrixF("1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1");
_offset.Alloc();             InternalUnsafeMethods.AttachChildAt__Args _args = new InternalUnsafeMethods.AttachChildAt__Args() {
                _subObject = _subObject.ObjectPtr,
                _offset = _offset.internalStructPtr,
                _node = _node,
             };
             bool _engineResult = InternalUnsafeMethods.AttachChildAt()(ObjectPtr, _args);
_offset.Free();             return _engineResult;
        }

        /// <description>
        /// getChild(S32 index) -- returns child SceneObject at given index
        /// </description>
        public int GetChild(int _index = 0) {
             InternalUnsafeMethods.GetChild__Args _args = new InternalUnsafeMethods.GetChild__Args() {
                _index = _index,
             };
             int _engineResult = InternalUnsafeMethods.GetChild()(ObjectPtr, _args);
             return _engineResult;
        }

        /// <description>
        /// returns number of recursively-nested child objects
        /// </description>
        public int GetNumProgeny() {
             InternalUnsafeMethods.GetNumProgeny__Args _args = new InternalUnsafeMethods.GetNumProgeny__Args() {
             };
             int _engineResult = InternalUnsafeMethods.GetNumProgeny()(ObjectPtr, _args);
             return _engineResult;
        }

        /// <description>
        /// returns number of direct child objects
        /// </description>
        public int GetNumChildren() {
             InternalUnsafeMethods.GetNumChildren__Args _args = new InternalUnsafeMethods.GetNumChildren__Args() {
             };
             int _engineResult = InternalUnsafeMethods.GetNumChildren()(ObjectPtr, _args);
             return _engineResult;
        }

        /// <description>
        /// Sets the forward vector of a scene object, making it face Y+ along the new vector.
        /// </description>
        /// <param name="The">new forward vector to set.</param>
        /// <param name="(Optional)">The up vector to use to help orient the rotation.</param>
        public void SetForwardVector(Point3F newForward = null, Point3F upVector = null) {
newForward = newForward ?? new Point3F("0 0 0");
newForward.Alloc();upVector = upVector ?? new Point3F("0 0 0");
upVector.Alloc();             InternalUnsafeMethods.SetForwardVector__Args _args = new InternalUnsafeMethods.SetForwardVector__Args() {
                newForward = newForward.internalStructPtr,
                upVector = upVector.internalStructPtr,
             };
             InternalUnsafeMethods.SetForwardVector()(ObjectPtr, _args);
newForward.Free();upVector.Free();        }

        /// <description>
        /// Check if this object has a global bounds set.
        /// If global bounds are set to be true, then the object is assumed to have an infinitely large bounding box for collision and rendering purposes.
        /// </description>
        /// <returns>true if the object has a global bounds.</returns>
        public bool IsGlobalBounds() {
             InternalUnsafeMethods.IsGlobalBounds__Args _args = new InternalUnsafeMethods.IsGlobalBounds__Args() {
             };
             bool _engineResult = InternalUnsafeMethods.IsGlobalBounds()(ObjectPtr, _args);
             return _engineResult;
        }

        /// <description>
        /// Get the object's bounding box (relative to the object's origin).
        /// </description>
        /// <returns>six fields, two Point3Fs, containing the min and max points of the objectbox.</returns>
        public Box3F GetObjectBox() {
             InternalUnsafeMethods.GetObjectBox__Args _args = new InternalUnsafeMethods.GetObjectBox__Args() {
             };
             Box3F.InternalStruct _engineResult = InternalUnsafeMethods.GetObjectBox()(ObjectPtr, _args);
             return new Box3F(_engineResult);
        }

        /// <description>
        /// Get the center of the object's world bounding box.
        /// </description>
        /// <returns>the center of the world bounding box for this object.</returns>
        public Point3F GetWorldBoxCenter() {
             InternalUnsafeMethods.GetWorldBoxCenter__Args _args = new InternalUnsafeMethods.GetWorldBoxCenter__Args() {
             };
             Point3F.InternalStruct _engineResult = InternalUnsafeMethods.GetWorldBoxCenter()(ObjectPtr, _args);
             return new Point3F(_engineResult);
        }

        /// <description>
        /// Get the object's world bounding box.
        /// </description>
        /// <returns>six fields, two Point3Fs, containing the min and max points of the worldbox.</returns>
        public Box3F GetWorldBox() {
             InternalUnsafeMethods.GetWorldBox__Args _args = new InternalUnsafeMethods.GetWorldBox__Args() {
             };
             Box3F.InternalStruct _engineResult = InternalUnsafeMethods.GetWorldBox()(ObjectPtr, _args);
             return new Box3F(_engineResult);
        }

        /// <description>
        /// Set the object's scale.
        /// </description>
        /// <param name="scale">object scale to set</param>
        public void SetScale(Point3F scale) {
scale.Alloc();             InternalUnsafeMethods.SetScale__Args _args = new InternalUnsafeMethods.SetScale__Args() {
                scale = scale.internalStructPtr,
             };
             InternalUnsafeMethods.SetScale()(ObjectPtr, _args);
scale.Free();        }

        /// <description>
        /// Get the object's scale.
        /// </description>
        /// <returns>object scale as a Point3F</returns>
        public Point3F GetScale() {
             InternalUnsafeMethods.GetScale__Args _args = new InternalUnsafeMethods.GetScale__Args() {
             };
             Point3F.InternalStruct _engineResult = InternalUnsafeMethods.GetScale()(ObjectPtr, _args);
             return new Point3F(_engineResult);
        }

        /// <description>
        /// Set the object's transform (orientation and position).
        /// </description>
        /// <param name="txfm">object transform to set</param>
        public void SetTransform(TransformF txfm) {
txfm.Alloc();             InternalUnsafeMethods.SetTransform__Args _args = new InternalUnsafeMethods.SetTransform__Args() {
                txfm = txfm.internalStructPtr,
             };
             InternalUnsafeMethods.SetTransform()(ObjectPtr, _args);
txfm.Free();        }

        /// <description>
        /// Get the up vector of the object.
        /// </description>
        /// <returns>a vector indicating the up direction of this object.</returns>
        /// <remarks> This is the object's z axis.</remarks>
        public Point3F GetUpVector() {
             InternalUnsafeMethods.GetUpVector__Args _args = new InternalUnsafeMethods.GetUpVector__Args() {
             };
             Point3F.InternalStruct _engineResult = InternalUnsafeMethods.GetUpVector()(ObjectPtr, _args);
             return new Point3F(_engineResult);
        }

        /// <description>
        /// Get the right vector of the object.
        /// </description>
        /// <returns>a vector indicating the right direction of this object.</returns>
        /// <remarks> This is the object's x axis.</remarks>
        public Point3F GetRightVector() {
             InternalUnsafeMethods.GetRightVector__Args _args = new InternalUnsafeMethods.GetRightVector__Args() {
             };
             Point3F.InternalStruct _engineResult = InternalUnsafeMethods.GetRightVector()(ObjectPtr, _args);
             return new Point3F(_engineResult);
        }

        /// <description>
        /// Get the direction this object is facing.
        /// </description>
        /// <returns>a vector indicating the direction this object is facing.</returns>
        /// <remarks> This is the object's y axis.</remarks>
        public Point3F GetForwardVector() {
             InternalUnsafeMethods.GetForwardVector__Args _args = new InternalUnsafeMethods.GetForwardVector__Args() {
             };
             Point3F.InternalStruct _engineResult = InternalUnsafeMethods.GetForwardVector()(ObjectPtr, _args);
             return new Point3F(_engineResult);
        }

        /// <description>
        /// Get Euler rotation of this object.
        /// </description>
        /// <returns>the orientation of the object in the form of rotations around the X, Y and Z axes in degrees.</returns>
        public Point3F GetEulerRotation() {
             InternalUnsafeMethods.GetEulerRotation__Args _args = new InternalUnsafeMethods.GetEulerRotation__Args() {
             };
             Point3F.InternalStruct _engineResult = InternalUnsafeMethods.GetEulerRotation()(ObjectPtr, _args);
             return new Point3F(_engineResult);
        }

        /// <description>
        /// Set the object's world position.
        /// </description>
        /// <param name="pos">the new world position of the object</param>
        public void SetPosition(Point3F pos) {
pos.Alloc();             InternalUnsafeMethods.SetPosition__Args _args = new InternalUnsafeMethods.SetPosition__Args() {
                pos = pos.internalStructPtr,
             };
             InternalUnsafeMethods.SetPosition()(ObjectPtr, _args);
pos.Free();        }

        /// <description>
        /// Get the object's world position.
        /// </description>
        /// <returns>the current world position of the object</returns>
        public Point3F GetPosition() {
             InternalUnsafeMethods.GetPosition__Args _args = new InternalUnsafeMethods.GetPosition__Args() {
             };
             Point3F.InternalStruct _engineResult = InternalUnsafeMethods.GetPosition()(ObjectPtr, _args);
             return new Point3F(_engineResult);
        }

        /// <description>
        /// Get the object's inverse transform.
        /// </description>
        /// <returns>the inverse transform of the object</returns>
        public TransformF GetInverseTransform() {
             InternalUnsafeMethods.GetInverseTransform__Args _args = new InternalUnsafeMethods.GetInverseTransform__Args() {
             };
             TransformF.InternalStruct _engineResult = InternalUnsafeMethods.GetInverseTransform()(ObjectPtr, _args);
             return new TransformF(_engineResult);
        }

        /// <description>
        /// Get the object's transform.
        /// </description>
        /// <returns>the current transform of the object</returns>
        public TransformF GetTransform() {
             InternalUnsafeMethods.GetTransform__Args _args = new InternalUnsafeMethods.GetTransform__Args() {
             };
             TransformF.InternalStruct _engineResult = InternalUnsafeMethods.GetTransform()(ObjectPtr, _args);
             return new TransformF(_engineResult);
        }

        /// <summary>Get the object mounted at our given node index.</summary>
        /// <description>
        /// 
        /// </description>
        /// <param name="node">mount node index to query</param>
        /// <returns>ID of the first object mounted at the node, or 0 if none found.</returns>
        public int GetMountNodeObject(int node) {
             InternalUnsafeMethods.GetMountNodeObject__Args _args = new InternalUnsafeMethods.GetMountNodeObject__Args() {
                node = node,
             };
             int _engineResult = InternalUnsafeMethods.GetMountNodeObject()(ObjectPtr, _args);
             return _engineResult;
        }

        /// <summary>Get the mount node index of the object mounted at our given slot.</summary>
        /// <description>
        /// 
        /// </description>
        /// <param name="slot">mount slot index to query</param>
        /// <returns>index of the mount node used by the object mounted in this slot.</returns>
        public int GetMountedObjectNode(int slot) {
             InternalUnsafeMethods.GetMountedObjectNode__Args _args = new InternalUnsafeMethods.GetMountedObjectNode__Args() {
                slot = slot,
             };
             int _engineResult = InternalUnsafeMethods.GetMountedObjectNode()(ObjectPtr, _args);
             return _engineResult;
        }

        /// <description>
        /// Get the object mounted at a particular slot.
        /// </description>
        /// <param name="slot">mount slot index to query</param>
        /// <returns>ID of the object mounted in the slot, or 0 if no object.</returns>
        public int GetMountedObject(int slot) {
             InternalUnsafeMethods.GetMountedObject__Args _args = new InternalUnsafeMethods.GetMountedObject__Args() {
                slot = slot,
             };
             int _engineResult = InternalUnsafeMethods.GetMountedObject()(ObjectPtr, _args);
             return _engineResult;
        }

        /// <description>
        /// Get the number of objects mounted to us.
        /// </description>
        /// <returns>the number of mounted objects.</returns>
        public int GetMountedObjectCount() {
             InternalUnsafeMethods.GetMountedObjectCount__Args _args = new InternalUnsafeMethods.GetMountedObjectCount__Args() {
             };
             int _engineResult = InternalUnsafeMethods.GetMountedObjectCount()(ObjectPtr, _args);
             return _engineResult;
        }

        /// <summary>Get the object we are mounted to.</summary>
        /// <description>
        /// 
        /// </description>
        /// <returns>the SimObjectID of the object we're mounted to, or 0 if not mounted.</returns>
        public int GetObjectMount() {
             InternalUnsafeMethods.GetObjectMount__Args _args = new InternalUnsafeMethods.GetObjectMount__Args() {
             };
             int _engineResult = InternalUnsafeMethods.GetObjectMount()(ObjectPtr, _args);
             return _engineResult;
        }

        /// <summary>Check if we are mounted to another object.</summary>
        /// <description>
        /// 
        /// </description>
        /// <returns>true if mounted to another object, false if not mounted.</returns>
        public bool IsMounted() {
             InternalUnsafeMethods.IsMounted__Args _args = new InternalUnsafeMethods.IsMounted__Args() {
             };
             bool _engineResult = InternalUnsafeMethods.IsMounted()(ObjectPtr, _args);
             return _engineResult;
        }

        /// <description>
        /// Unmount us from the currently mounted object if any.
        /// </description>
        public void Unmount() {
             InternalUnsafeMethods.Unmount__Args _args = new InternalUnsafeMethods.Unmount__Args() {
             };
             InternalUnsafeMethods.Unmount()(ObjectPtr, _args);
        }

        /// <summary>Unmount an object from ourselves.</summary>
        /// <description>
        /// 
        /// </description>
        /// <param name="target">object to unmount</param>
        /// <returns>true if successful, false if failed</returns>
        public bool UnmountObject(SceneObject target) {
             InternalUnsafeMethods.UnmountObject__Args _args = new InternalUnsafeMethods.UnmountObject__Args() {
                target = target.ObjectPtr,
             };
             bool _engineResult = InternalUnsafeMethods.UnmountObject()(ObjectPtr, _args);
             return _engineResult;
        }

        /// <summary>Mount objB to this object at the desired slot with optional transform.</summary>
        /// <description>
        /// 
        /// </description>
        /// <param name="objB">Object to mount onto us</param>
        /// <param name="slot">Mount slot ID</param>
        /// <param name="txfm">(optional) mount offset transform</param>
        /// <returns>true if successful, false if failed (objB is not valid)</returns>
        public bool MountObject(SceneObject objB, int slot, TransformF txfm = null) {
txfm = txfm ?? new TransformF("0 0 0 0 0 0 0 false");
txfm.Alloc();             InternalUnsafeMethods.MountObject__Args _args = new InternalUnsafeMethods.MountObject__Args() {
                objB = objB.ObjectPtr,
                slot = slot,
                txfm = txfm.internalStructPtr,
             };
             bool _engineResult = InternalUnsafeMethods.MountObject()(ObjectPtr, _args);
txfm.Free();             return _engineResult;
        }

        /// <description>
        /// Return the type mask for this object.
        /// </description>
        /// <returns>The numeric type mask for the object.</returns>
        public int GetType() {
             InternalUnsafeMethods.GetType__Args _args = new InternalUnsafeMethods.GetType__Args() {
             };
             int _engineResult = InternalUnsafeMethods.GetType()(ObjectPtr, _args);
             return _engineResult;
        }

        /// <description>
        /// Get the type info object for the SceneObject class.
        /// </description>
        /// <returns>The type info object for SceneObject</returns>
        public static EngineTypeInfo StaticGetType() {
             InternalUnsafeMethods.StaticGetType__Args _args = new InternalUnsafeMethods.StaticGetType__Args() {
             };
             IntPtr _engineResult = InternalUnsafeMethods.StaticGetType()(_args);
             return new EngineTypeInfo(_engineResult);
        }


        /// <value>
        /// <description>
        /// The asset Id used for the game object this entity is based on.
        /// </description>
        /// </value>
        public GameObjectAsset GameObject {
            get => GenericMarshal.StringTo<GameObjectAsset>(GetFieldValue("GameObject"));
            set => SetFieldValue("GameObject", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// If this entity is a GameObject, it flags if this instance delinates from the template.
        /// </description>
        /// </value>
        public bool DirtyGameObject {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("dirtyGameObject"));
            set => SetFieldValue("dirtyGameObject", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Object world position.
        /// </description>
        /// </value>
        public Point3F Position {
            get => GenericMarshal.StringTo<Point3F>(GetFieldValue("position"));
            set => SetFieldValue("position", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Object world orientation.
        /// </description>
        /// </value>
        public MatrixF Rotation {
            get => GenericMarshal.StringTo<MatrixF>(GetFieldValue("rotation"));
            set => SetFieldValue("rotation", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Object world scale.
        /// </description>
        /// </value>
        public Point3F Scale {
            get => GenericMarshal.StringTo<Point3F>(GetFieldValue("scale"));
            set => SetFieldValue("scale", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Controls client-side rendering of the object.
        /// </description>
        /// <see cref="isRenderable()" />
        /// </value>
        public bool IsRenderEnabled {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("isRenderEnabled"));
            set => SetFieldValue("isRenderEnabled", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Determines if the object may be selected from wihin the Tools.
        /// </description>
        /// <see cref="isSelectable()" />
        /// </value>
        public bool IsSelectionEnabled {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("isSelectionEnabled"));
            set => SetFieldValue("isSelectionEnabled", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <summary>PersistentID of object we are mounted to.</summary>
        /// <description>
        /// Unlike the SimObjectID that is determined at run time, the PersistentID of an object is saved with the level/mission and may be used to form a link between objects.
        /// </description>
        /// </value>
        public SimPersistID MountPID {
            get => GenericMarshal.StringTo<SimPersistID>(GetFieldValue("mountPID"));
            set => SetFieldValue("mountPID", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Node we are mounted to.
        /// </description>
        /// </value>
        public int MountNode {
            get => GenericMarshal.StringTo<int>(GetFieldValue("mountNode"));
            set => SetFieldValue("mountNode", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Position we are mounted at ( object space of our mount object ).
        /// </description>
        /// </value>
        public Point3F MountPos {
            get => GenericMarshal.StringTo<Point3F>(GetFieldValue("mountPos"));
            set => SetFieldValue("mountPos", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Rotation we are mounted at ( object space of our mount object ).
        /// </description>
        /// </value>
        public MatrixF MountRot {
            get => GenericMarshal.StringTo<MatrixF>(GetFieldValue("mountRot"));
            set => SetFieldValue("mountRot", GenericMarshal.ToString(value));
        }
    }
}