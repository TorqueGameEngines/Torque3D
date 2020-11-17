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
    public unsafe class VPath : SceneObject {
        public VPath(bool pRegister = false) 
            : base(pRegister) {
        }
        
        public VPath(string pName, bool pRegister) 
            : this(false) {
            Name = pName;
            if (pRegister) {
                RegisterObject();
            }
        }
        
        public VPath(string pName) 
            : this(pName, false) {
        }
        
        public VPath(string pName, string pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(Engine.Sim.FindObject<SimObject>(pParent));
        }
        
        public VPath(string pName, SimObject pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(pParent);
        }
        
        public VPath(SimObject pObj) 
            : base(pObj) {
        }
        
        public VPath(IntPtr pObj) 
            : base(pObj) {
        }
        
		protected override void CreateObjectPtr()
		{
			ObjectPtr = InternalUnsafeMethods.Create()(new InternalUnsafeMethods.Create__Args());
		}

        #region UnsafeNativeMethods
        new internal struct InternalUnsafeMethods {
            [StructLayout(LayoutKind.Sequential)]
            internal struct SetPathObjectEndNode__Args
            {
                internal IntPtr sceneObject;
                internal int nodeIndex;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _SetPathObjectEndNode(IntPtr _this, SetPathObjectEndNode__Args args);
            private static _SetPathObjectEndNode _SetPathObjectEndNodeFunc;
            internal static _SetPathObjectEndNode SetPathObjectEndNode() {
                if (_SetPathObjectEndNodeFunc == null) {
                    _SetPathObjectEndNodeFunc =
                        (_SetPathObjectEndNode)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnVPath_setPathObjectEndNode"), typeof(_SetPathObjectEndNode));
                }
                
                return _SetPathObjectEndNodeFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct GetPathObjectEndNode__Args
            {
                internal IntPtr sceneObject;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate int _GetPathObjectEndNode(IntPtr _this, GetPathObjectEndNode__Args args);
            private static _GetPathObjectEndNode _GetPathObjectEndNodeFunc;
            internal static _GetPathObjectEndNode GetPathObjectEndNode() {
                if (_GetPathObjectEndNodeFunc == null) {
                    _GetPathObjectEndNodeFunc =
                        (_GetPathObjectEndNode)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnVPath_getPathObjectEndNode"), typeof(_GetPathObjectEndNode));
                }
                
                return _GetPathObjectEndNodeFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct SetPathObjectNode__Args
            {
                internal IntPtr sceneObject;
                internal int nodeIndex;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _SetPathObjectNode(IntPtr _this, SetPathObjectNode__Args args);
            private static _SetPathObjectNode _SetPathObjectNodeFunc;
            internal static _SetPathObjectNode SetPathObjectNode() {
                if (_SetPathObjectNodeFunc == null) {
                    _SetPathObjectNodeFunc =
                        (_SetPathObjectNode)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnVPath_setPathObjectNode"), typeof(_SetPathObjectNode));
                }
                
                return _SetPathObjectNodeFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct GetPathObjectNode__Args
            {
                internal IntPtr sceneObject;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate int _GetPathObjectNode(IntPtr _this, GetPathObjectNode__Args args);
            private static _GetPathObjectNode _GetPathObjectNodeFunc;
            internal static _GetPathObjectNode GetPathObjectNode() {
                if (_GetPathObjectNodeFunc == null) {
                    _GetPathObjectNodeFunc =
                        (_GetPathObjectNode)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnVPath_getPathObjectNode"), typeof(_GetPathObjectNode));
                }
                
                return _GetPathObjectNodeFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct SetPathObjectForward__Args
            {
                internal IntPtr sceneObject;
                [MarshalAs(UnmanagedType.I1)]
                internal bool forward;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _SetPathObjectForward(IntPtr _this, SetPathObjectForward__Args args);
            private static _SetPathObjectForward _SetPathObjectForwardFunc;
            internal static _SetPathObjectForward SetPathObjectForward() {
                if (_SetPathObjectForwardFunc == null) {
                    _SetPathObjectForwardFunc =
                        (_SetPathObjectForward)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnVPath_setPathObjectForward"), typeof(_SetPathObjectForward));
                }
                
                return _SetPathObjectForwardFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct IsPathObjectForward__Args
            {
                internal IntPtr sceneObject;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            [return: MarshalAs(UnmanagedType.I1)]
            internal delegate bool _IsPathObjectForward(IntPtr _this, IsPathObjectForward__Args args);
            private static _IsPathObjectForward _IsPathObjectForwardFunc;
            internal static _IsPathObjectForward IsPathObjectForward() {
                if (_IsPathObjectForwardFunc == null) {
                    _IsPathObjectForwardFunc =
                        (_IsPathObjectForward)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnVPath_isPathObjectForward"), typeof(_IsPathObjectForward));
                }
                
                return _IsPathObjectForwardFunc;
            }


            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _SetPathObjectOrientationMode(IntPtr _this, ref StringVector.InternalStruct args);
            private static _SetPathObjectOrientationMode _SetPathObjectOrientationModeFunc;
            internal static _SetPathObjectOrientationMode SetPathObjectOrientationMode() {
                if (_SetPathObjectOrientationModeFunc == null) {
                    _SetPathObjectOrientationModeFunc =
                        (_SetPathObjectOrientationMode)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnVPath_setPathObjectOrientationMode"), typeof(_SetPathObjectOrientationMode));
                }
                
                return _SetPathObjectOrientationModeFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct GetPathObjectOrientationMode__Args
            {
                internal IntPtr sceneObject;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            
            internal delegate IntPtr _GetPathObjectOrientationMode(IntPtr _this, GetPathObjectOrientationMode__Args args);
            private static _GetPathObjectOrientationMode _GetPathObjectOrientationModeFunc;
            internal static _GetPathObjectOrientationMode GetPathObjectOrientationMode() {
                if (_GetPathObjectOrientationModeFunc == null) {
                    _GetPathObjectOrientationModeFunc =
                        (_GetPathObjectOrientationMode)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnVPath_getPathObjectOrientationMode"), typeof(_GetPathObjectOrientationMode));
                }
                
                return _GetPathObjectOrientationModeFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct SetPathObjectSpeed__Args
            {
                internal IntPtr sceneObject;
                internal float speed;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _SetPathObjectSpeed(IntPtr _this, SetPathObjectSpeed__Args args);
            private static _SetPathObjectSpeed _SetPathObjectSpeedFunc;
            internal static _SetPathObjectSpeed SetPathObjectSpeed() {
                if (_SetPathObjectSpeedFunc == null) {
                    _SetPathObjectSpeedFunc =
                        (_SetPathObjectSpeed)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnVPath_setPathObjectSpeed"), typeof(_SetPathObjectSpeed));
                }
                
                return _SetPathObjectSpeedFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct GetPathObjectSpeed__Args
            {
                internal IntPtr sceneObject;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate float _GetPathObjectSpeed(IntPtr _this, GetPathObjectSpeed__Args args);
            private static _GetPathObjectSpeed _GetPathObjectSpeedFunc;
            internal static _GetPathObjectSpeed GetPathObjectSpeed() {
                if (_GetPathObjectSpeedFunc == null) {
                    _GetPathObjectSpeedFunc =
                        (_GetPathObjectSpeed)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnVPath_getPathObjectSpeed"), typeof(_GetPathObjectSpeed));
                }
                
                return _GetPathObjectSpeedFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct SetPathObjectOffset__Args
            {
                internal IntPtr sceneObject;
                internal IntPtr offset;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _SetPathObjectOffset(IntPtr _this, SetPathObjectOffset__Args args);
            private static _SetPathObjectOffset _SetPathObjectOffsetFunc;
            internal static _SetPathObjectOffset SetPathObjectOffset() {
                if (_SetPathObjectOffsetFunc == null) {
                    _SetPathObjectOffsetFunc =
                        (_SetPathObjectOffset)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnVPath_setPathObjectOffset"), typeof(_SetPathObjectOffset));
                }
                
                return _SetPathObjectOffsetFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct GetPathObjectOffset__Args
            {
                internal IntPtr sceneObject;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            
            internal delegate IntPtr _GetPathObjectOffset(IntPtr _this, GetPathObjectOffset__Args args);
            private static _GetPathObjectOffset _GetPathObjectOffsetFunc;
            internal static _GetPathObjectOffset GetPathObjectOffset() {
                if (_GetPathObjectOffsetFunc == null) {
                    _GetPathObjectOffsetFunc =
                        (_GetPathObjectOffset)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnVPath_getPathObjectOffset"), typeof(_GetPathObjectOffset));
                }
                
                return _GetPathObjectOffsetFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct SetPathObjectInterp__Args
            {
                internal IntPtr sceneObject;
                internal float timeInterp;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _SetPathObjectInterp(IntPtr _this, SetPathObjectInterp__Args args);
            private static _SetPathObjectInterp _SetPathObjectInterpFunc;
            internal static _SetPathObjectInterp SetPathObjectInterp() {
                if (_SetPathObjectInterpFunc == null) {
                    _SetPathObjectInterpFunc =
                        (_SetPathObjectInterp)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnVPath_setPathObjectInterp"), typeof(_SetPathObjectInterp));
                }
                
                return _SetPathObjectInterpFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct GetPathObjectInterp__Args
            {
                internal IntPtr sceneObject;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate float _GetPathObjectInterp(IntPtr _this, GetPathObjectInterp__Args args);
            private static _GetPathObjectInterp _GetPathObjectInterpFunc;
            internal static _GetPathObjectInterp GetPathObjectInterp() {
                if (_GetPathObjectInterpFunc == null) {
                    _GetPathObjectInterpFunc =
                        (_GetPathObjectInterp)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnVPath_getPathObjectInterp"), typeof(_GetPathObjectInterp));
                }
                
                return _GetPathObjectInterpFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct SetPathObjectActive__Args
            {
                internal IntPtr sceneObject;
                [MarshalAs(UnmanagedType.I1)]
                internal bool isActive;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _SetPathObjectActive(IntPtr _this, SetPathObjectActive__Args args);
            private static _SetPathObjectActive _SetPathObjectActiveFunc;
            internal static _SetPathObjectActive SetPathObjectActive() {
                if (_SetPathObjectActiveFunc == null) {
                    _SetPathObjectActiveFunc =
                        (_SetPathObjectActive)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnVPath_setPathObjectActive"), typeof(_SetPathObjectActive));
                }
                
                return _SetPathObjectActiveFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct IsPathObjectActive__Args
            {
                internal IntPtr sceneObject;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            [return: MarshalAs(UnmanagedType.I1)]
            internal delegate bool _IsPathObjectActive(IntPtr _this, IsPathObjectActive__Args args);
            private static _IsPathObjectActive _IsPathObjectActiveFunc;
            internal static _IsPathObjectActive IsPathObjectActive() {
                if (_IsPathObjectActiveFunc == null) {
                    _IsPathObjectActiveFunc =
                        (_IsPathObjectActive)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnVPath_isPathObjectActive"), typeof(_IsPathObjectActive));
                }
                
                return _IsPathObjectActiveFunc;
            }


            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _SetNodeOrientationMode(IntPtr _this, ref StringVector.InternalStruct args);
            private static _SetNodeOrientationMode _SetNodeOrientationModeFunc;
            internal static _SetNodeOrientationMode SetNodeOrientationMode() {
                if (_SetNodeOrientationModeFunc == null) {
                    _SetNodeOrientationModeFunc =
                        (_SetNodeOrientationMode)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnVPath_setNodeOrientationMode"), typeof(_SetNodeOrientationMode));
                }
                
                return _SetNodeOrientationModeFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct GetNodeOrientationMode__Args
            {
                internal int nodeIndex;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            
            internal delegate IntPtr _GetNodeOrientationMode(IntPtr _this, GetNodeOrientationMode__Args args);
            private static _GetNodeOrientationMode _GetNodeOrientationModeFunc;
            internal static _GetNodeOrientationMode GetNodeOrientationMode() {
                if (_GetNodeOrientationModeFunc == null) {
                    _GetNodeOrientationModeFunc =
                        (_GetNodeOrientationMode)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnVPath_getNodeOrientationMode"), typeof(_GetNodeOrientationMode));
                }
                
                return _GetNodeOrientationModeFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct SetNodeWeight__Args
            {
                internal int nodeIndex;
                internal float nodeWeight;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _SetNodeWeight(IntPtr _this, SetNodeWeight__Args args);
            private static _SetNodeWeight _SetNodeWeightFunc;
            internal static _SetNodeWeight SetNodeWeight() {
                if (_SetNodeWeightFunc == null) {
                    _SetNodeWeightFunc =
                        (_SetNodeWeight)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnVPath_setNodeWeight"), typeof(_SetNodeWeight));
                }
                
                return _SetNodeWeightFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct SetNodeRotation__Args
            {
                internal int nodeIndex;
                internal IntPtr aa;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _SetNodeRotation(IntPtr _this, SetNodeRotation__Args args);
            private static _SetNodeRotation _SetNodeRotationFunc;
            internal static _SetNodeRotation SetNodeRotation() {
                if (_SetNodeRotationFunc == null) {
                    _SetNodeRotationFunc =
                        (_SetNodeRotation)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnVPath_setNodeRotation"), typeof(_SetNodeRotation));
                }
                
                return _SetNodeRotationFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct SetNodePosition__Args
            {
                internal int nodeIndex;
                internal IntPtr position;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _SetNodePosition(IntPtr _this, SetNodePosition__Args args);
            private static _SetNodePosition _SetNodePositionFunc;
            internal static _SetNodePosition SetNodePosition() {
                if (_SetNodePositionFunc == null) {
                    _SetNodePositionFunc =
                        (_SetNodePosition)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnVPath_setNodePosition"), typeof(_SetNodePosition));
                }
                
                return _SetNodePositionFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct SetNodeTransform__Args
            {
                internal int nodeIndex;
                internal IntPtr transform;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _SetNodeTransform(IntPtr _this, SetNodeTransform__Args args);
            private static _SetNodeTransform _SetNodeTransformFunc;
            internal static _SetNodeTransform SetNodeTransform() {
                if (_SetNodeTransformFunc == null) {
                    _SetNodeTransformFunc =
                        (_SetNodeTransform)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnVPath_setNodeTransform"), typeof(_SetNodeTransform));
                }
                
                return _SetNodeTransformFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct GetNodeLength__Args
            {
                internal int nodeIndex;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate float _GetNodeLength(IntPtr _this, GetNodeLength__Args args);
            private static _GetNodeLength _GetNodeLengthFunc;
            internal static _GetNodeLength GetNodeLength() {
                if (_GetNodeLengthFunc == null) {
                    _GetNodeLengthFunc =
                        (_GetNodeLength)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnVPath_getNodeLength"), typeof(_GetNodeLength));
                }
                
                return _GetNodeLengthFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct GetNodeWeight__Args
            {
                internal int nodeIndex;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate float _GetNodeWeight(IntPtr _this, GetNodeWeight__Args args);
            private static _GetNodeWeight _GetNodeWeightFunc;
            internal static _GetNodeWeight GetNodeWeight() {
                if (_GetNodeWeightFunc == null) {
                    _GetNodeWeightFunc =
                        (_GetNodeWeight)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnVPath_getNodeWeight"), typeof(_GetNodeWeight));
                }
                
                return _GetNodeWeightFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct GetNodeWorldRotation__Args
            {
                internal int nodeIndex;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate AngAxisF.InternalStruct _GetNodeWorldRotation(IntPtr _this, GetNodeWorldRotation__Args args);
            private static _GetNodeWorldRotation _GetNodeWorldRotationFunc;
            internal static _GetNodeWorldRotation GetNodeWorldRotation() {
                if (_GetNodeWorldRotationFunc == null) {
                    _GetNodeWorldRotationFunc =
                        (_GetNodeWorldRotation)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnVPath_getNodeWorldRotation"), typeof(_GetNodeWorldRotation));
                }
                
                return _GetNodeWorldRotationFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct GetNodeWorldPosition__Args
            {
                internal int nodeIndex;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate Point3F.InternalStruct _GetNodeWorldPosition(IntPtr _this, GetNodeWorldPosition__Args args);
            private static _GetNodeWorldPosition _GetNodeWorldPositionFunc;
            internal static _GetNodeWorldPosition GetNodeWorldPosition() {
                if (_GetNodeWorldPositionFunc == null) {
                    _GetNodeWorldPositionFunc =
                        (_GetNodeWorldPosition)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnVPath_getNodeWorldPosition"), typeof(_GetNodeWorldPosition));
                }
                
                return _GetNodeWorldPositionFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct GetNodeWorldTransform__Args
            {
                internal int nodeIndex;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate TransformF.InternalStruct _GetNodeWorldTransform(IntPtr _this, GetNodeWorldTransform__Args args);
            private static _GetNodeWorldTransform _GetNodeWorldTransformFunc;
            internal static _GetNodeWorldTransform GetNodeWorldTransform() {
                if (_GetNodeWorldTransformFunc == null) {
                    _GetNodeWorldTransformFunc =
                        (_GetNodeWorldTransform)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnVPath_getNodeWorldTransform"), typeof(_GetNodeWorldTransform));
                }
                
                return _GetNodeWorldTransformFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct GetNodeLocalRotation__Args
            {
                internal int nodeIndex;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate AngAxisF.InternalStruct _GetNodeLocalRotation(IntPtr _this, GetNodeLocalRotation__Args args);
            private static _GetNodeLocalRotation _GetNodeLocalRotationFunc;
            internal static _GetNodeLocalRotation GetNodeLocalRotation() {
                if (_GetNodeLocalRotationFunc == null) {
                    _GetNodeLocalRotationFunc =
                        (_GetNodeLocalRotation)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnVPath_getNodeLocalRotation"), typeof(_GetNodeLocalRotation));
                }
                
                return _GetNodeLocalRotationFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct GetNodeLocalPosition__Args
            {
                internal int nodeIndex;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate Point3F.InternalStruct _GetNodeLocalPosition(IntPtr _this, GetNodeLocalPosition__Args args);
            private static _GetNodeLocalPosition _GetNodeLocalPositionFunc;
            internal static _GetNodeLocalPosition GetNodeLocalPosition() {
                if (_GetNodeLocalPositionFunc == null) {
                    _GetNodeLocalPositionFunc =
                        (_GetNodeLocalPosition)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnVPath_getNodeLocalPosition"), typeof(_GetNodeLocalPosition));
                }
                
                return _GetNodeLocalPositionFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct GetNodeLocalTransform__Args
            {
                internal int nodeIndex;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            
            internal delegate IntPtr _GetNodeLocalTransform(IntPtr _this, GetNodeLocalTransform__Args args);
            private static _GetNodeLocalTransform _GetNodeLocalTransformFunc;
            internal static _GetNodeLocalTransform GetNodeLocalTransform() {
                if (_GetNodeLocalTransformFunc == null) {
                    _GetNodeLocalTransformFunc =
                        (_GetNodeLocalTransform)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnVPath_getNodeLocalTransform"), typeof(_GetNodeLocalTransform));
                }
                
                return _GetNodeLocalTransformFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct GetNodeCount__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate int _GetNodeCount(IntPtr _this, GetNodeCount__Args args);
            private static _GetNodeCount _GetNodeCountFunc;
            internal static _GetNodeCount GetNodeCount() {
                if (_GetNodeCountFunc == null) {
                    _GetNodeCountFunc =
                        (_GetNodeCount)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnVPath_getNodeCount"), typeof(_GetNodeCount));
                }
                
                return _GetNodeCountFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct GetPathPosition__Args
            {
                internal int srcNodeIndex;
                internal int dstNodeIndex;
                internal float timeInterp;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            
            internal delegate IntPtr _GetPathPosition(IntPtr _this, GetPathPosition__Args args);
            private static _GetPathPosition _GetPathPositionFunc;
            internal static _GetPathPosition GetPathPosition() {
                if (_GetPathPositionFunc == null) {
                    _GetPathPositionFunc =
                        (_GetPathPosition)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnVPath_getPathPosition"), typeof(_GetPathPosition));
                }
                
                return _GetPathPositionFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct GetPathTransform__Args
            {
                internal int srcNodeIndex;
                internal int dstNodeIndex;
                internal float timeInterp;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            
            internal delegate IntPtr _GetPathTransform(IntPtr _this, GetPathTransform__Args args);
            private static _GetPathTransform _GetPathTransformFunc;
            internal static _GetPathTransform GetPathTransform() {
                if (_GetPathTransformFunc == null) {
                    _GetPathTransformFunc =
                        (_GetPathTransform)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnVPath_getPathTransform"), typeof(_GetPathTransform));
                }
                
                return _GetPathTransformFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct DetachObject__Args
            {
                internal IntPtr sceneObject;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _DetachObject(IntPtr _this, DetachObject__Args args);
            private static _DetachObject _DetachObjectFunc;
            internal static _DetachObject DetachObject() {
                if (_DetachObjectFunc == null) {
                    _DetachObjectFunc =
                        (_DetachObject)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnVPath_detachObject"), typeof(_DetachObject));
                }
                
                return _DetachObjectFunc;
            }


            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _AttachObject(IntPtr _this, ref StringVector.InternalStruct args);
            private static _AttachObject _AttachObjectFunc;
            internal static _AttachObject AttachObject() {
                if (_AttachObjectFunc == null) {
                    _AttachObjectFunc =
                        (_AttachObject)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnVPath_attachObject"), typeof(_AttachObject));
                }
                
                return _AttachObjectFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct IsObjectAttached__Args
            {
                internal IntPtr sceneObject;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            [return: MarshalAs(UnmanagedType.I1)]
            internal delegate bool _IsObjectAttached(IntPtr _this, IsObjectAttached__Args args);
            private static _IsObjectAttached _IsObjectAttachedFunc;
            internal static _IsObjectAttached IsObjectAttached() {
                if (_IsObjectAttachedFunc == null) {
                    _IsObjectAttachedFunc =
                        (_IsObjectAttached)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnVPath_isObjectAttached"), typeof(_IsObjectAttached));
                }
                
                return _IsObjectAttachedFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct DeleteNode__Args
            {
                internal int nodeIndex;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _DeleteNode(IntPtr _this, DeleteNode__Args args);
            private static _DeleteNode _DeleteNodeFunc;
            internal static _DeleteNode DeleteNode() {
                if (_DeleteNodeFunc == null) {
                    _DeleteNodeFunc =
                        (_DeleteNode)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnVPath_deleteNode"), typeof(_DeleteNode));
                }
                
                return _DeleteNodeFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct AddNode__Args
            {
                internal IntPtr transform;
                internal float weight;
                internal int location;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _AddNode(IntPtr _this, AddNode__Args args);
            private static _AddNode _AddNodeFunc;
            internal static _AddNode AddNode() {
                if (_AddNodeFunc == null) {
                    _AddNodeFunc =
                        (_AddNode)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnVPath_addNode"), typeof(_AddNode));
                }
                
                return _AddNodeFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct SetPathType__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string pathType;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _SetPathType(IntPtr _this, SetPathType__Args args);
            private static _SetPathType _SetPathTypeFunc;
            internal static _SetPathType SetPathType() {
                if (_SetPathTypeFunc == null) {
                    _SetPathTypeFunc =
                        (_SetPathType)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnVPath_setPathType"), typeof(_SetPathType));
                }
                
                return _SetPathTypeFunc;
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
                                "fnVPath_staticGetType"), typeof(_StaticGetType));
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
                                "fnVPath_create"), typeof(_Create));
                }
                
                return _CreateFunc;
            }
        }
        #endregion

        /// <description>
        /// ( SimObject pObject, bool pNodeIndex ) - Set end node of the path object. If a value of "-1" is applied, the object will path indefinitely.
        /// </description>
        /// <param name="pObject">The SimObjectID of the object being altered.</param>
        /// <param name="pNodeIndex">The index of the node that the object will cease pathing upon reaching.</param>
        /// <returns>No return value.</returns>
        public void SetPathObjectEndNode(SceneObject sceneObject = null, int nodeIndex = 0) {
             InternalUnsafeMethods.SetPathObjectEndNode__Args _args = new InternalUnsafeMethods.SetPathObjectEndNode__Args() {
                sceneObject = sceneObject.ObjectPtr,
                nodeIndex = nodeIndex,
             };
             InternalUnsafeMethods.SetPathObjectEndNode()(ObjectPtr, _args);
        }

        /// <description>
        /// ( SimObject pObject ) - Get the index of the node this object is meant to stop upon reaching.
        /// </description>
        /// <param name="pObject">The SimObjectID of the object being observed.</param>
        /// <returns>Returns the node index.</returns>
        public int GetPathObjectEndNode(SceneObject sceneObject = null) {
             InternalUnsafeMethods.GetPathObjectEndNode__Args _args = new InternalUnsafeMethods.GetPathObjectEndNode__Args() {
                sceneObject = sceneObject.ObjectPtr,
             };
             int _engineResult = InternalUnsafeMethods.GetPathObjectEndNode()(ObjectPtr, _args);
             return _engineResult;
        }

        /// <description>
        /// ( SimObject pObject, bool pNodeIndex ) - Move the object to the node's position. You may also want to observe the "setPathObjectInterp" method.
        /// </description>
        /// <param name="pObject">The SimObjectID of the object being altered.</param>
        /// <param name="pNodeIndex">The index of the node that the object will reposition to.</param>
        /// <returns>No return value.</returns>
        public void SetPathObjectNode(SceneObject sceneObject = null, int nodeIndex = 0) {
             InternalUnsafeMethods.SetPathObjectNode__Args _args = new InternalUnsafeMethods.SetPathObjectNode__Args() {
                sceneObject = sceneObject.ObjectPtr,
                nodeIndex = nodeIndex,
             };
             InternalUnsafeMethods.SetPathObjectNode()(ObjectPtr, _args);
        }

        /// <description>
        /// ( SimObject pObject ) - Gets the last node of the object.
        /// </description>
        /// <param name="pObject">The SimObjectID of the object being observed.</param>
        /// <returns>Returns the node index.</returns>
        public int GetPathObjectNode(SceneObject sceneObject = null) {
             InternalUnsafeMethods.GetPathObjectNode__Args _args = new InternalUnsafeMethods.GetPathObjectNode__Args() {
                sceneObject = sceneObject.ObjectPtr,
             };
             int _engineResult = InternalUnsafeMethods.GetPathObjectNode()(ObjectPtr, _args);
             return _engineResult;
        }

        /// <description>
        /// ( SimObject pObject, bool pForward ) - Set the travel direction of the object.
        /// </description>
        /// <param name="pObject">The SimObjectID of the object being altered.</param>
        /// <param name="pForward">The direction of the object.</param>
        /// <returns>No return value.</returns>
        public void SetPathObjectForward(SceneObject sceneObject = null, bool forward = true) {
             InternalUnsafeMethods.SetPathObjectForward__Args _args = new InternalUnsafeMethods.SetPathObjectForward__Args() {
                sceneObject = sceneObject.ObjectPtr,
                forward = forward,
             };
             InternalUnsafeMethods.SetPathObjectForward()(ObjectPtr, _args);
        }

        /// <description>
        /// ( SimObject pObject ) - Get if this object is traveling forwards along the path.
        /// </description>
        /// <param name="pObject">The SimObjectID of the object being observed.</param>
        /// <returns>Returns true if the object is traveling forwards.</returns>
        public bool IsPathObjectForward(SceneObject sceneObject = null) {
             InternalUnsafeMethods.IsPathObjectForward__Args _args = new InternalUnsafeMethods.IsPathObjectForward__Args() {
                sceneObject = sceneObject.ObjectPtr,
             };
             bool _engineResult = InternalUnsafeMethods.IsPathObjectForward()(ObjectPtr, _args);
             return _engineResult;
        }

        /// <description>
        /// ( SimObject pObject, string pOrientationType, [SimObject pObject / vector pPoint] ) - Set the orientation mode of the object. This property affects the rotation of the object. If you wish to ignore the object's rotation altogether, set the mode to "FREE".
        /// </description>
        /// <param name="pObject">The SimObjectID of the object being altered.</param>
        /// <param name="pOrientationType">The new orientation type of the object.</param>
        /// <param name="pObject">If the orientation type is set to OBJECT, this parameter must be the SimObjectID of a scene object.</param>
        /// <param name="pPoint">If the orientation type is set to POINT, this parameter must be a vector.</param>
        /// <returns>No return value.</returns>
        public void SetPathObjectOrientationMode(params string[] args) { 
            List<string> _argList = new List<string>() {"", ""};
            _argList.AddRange(args);

            StringVector nativeVecArgs = new StringVector {
                ElementCount = (uint)_argList.Count,
                Array = _argList.ToArray(),
                ArraySize = (uint)_argList.Count
            };
            nativeVecArgs.Alloc();
            InternalUnsafeMethods.SetPathObjectOrientationMode()(ObjectPtr, ref nativeVecArgs.internalStruct);
            nativeVecArgs.Free();

        }

        /// <description>
        /// ( SimObject pObject ) - Gets the current orientation mode of the object.
        /// </description>
        /// <param name="pObject">The SimObjectID of the object being observed.</param>
        /// <returns>Returns a string indicating the orientation mode and its properties.</returns>
        public string GetPathObjectOrientationMode(SceneObject sceneObject = null) {
             InternalUnsafeMethods.GetPathObjectOrientationMode__Args _args = new InternalUnsafeMethods.GetPathObjectOrientationMode__Args() {
                sceneObject = sceneObject.ObjectPtr,
             };
             IntPtr _engineResult = InternalUnsafeMethods.GetPathObjectOrientationMode()(ObjectPtr, _args);
             return StringMarshal.IntPtrToUtf8String(_engineResult);
        }

        /// <description>
        /// ( SimObject pObject, float pSpeed ) - Set the speed of the object.
        /// </description>
        /// <param name="pObject">The SimObjectID of the object being altered.</param>
        /// <param name="pSpeed">The new speed of the object.</param>
        /// <returns>No return value.</returns>
        public void SetPathObjectSpeed(SceneObject sceneObject = null, float speed = 1f) {
             InternalUnsafeMethods.SetPathObjectSpeed__Args _args = new InternalUnsafeMethods.SetPathObjectSpeed__Args() {
                sceneObject = sceneObject.ObjectPtr,
                speed = speed,
             };
             InternalUnsafeMethods.SetPathObjectSpeed()(ObjectPtr, _args);
        }

        /// <description>
        /// ( SimObject pObject ) - Get the speed this object is traveling along the path at.
        /// </description>
        /// <param name="pObject">The SimObjectID of the object being observed.</param>
        /// <returns>Returns the speed of the object.</returns>
        public float GetPathObjectSpeed(SceneObject sceneObject = null) {
             InternalUnsafeMethods.GetPathObjectSpeed__Args _args = new InternalUnsafeMethods.GetPathObjectSpeed__Args() {
                sceneObject = sceneObject.ObjectPtr,
             };
             float _engineResult = InternalUnsafeMethods.GetPathObjectSpeed()(ObjectPtr, _args);
             return _engineResult;
        }

        /// <description>
        /// ( SimObject pObject, vector pOffset ) - Set the position offset of the object. As the object is moving along the path, its position is offset by this value. Setting the "Relative" parameter while attaching an object will automatically apply an offset value.
        /// </description>
        /// <param name="pObject">The SimObjectID of the object being altered.</param>
        /// <param name="pOffset">The new position offset of the object.</param>
        /// <returns>No return value.</returns>
        public void SetPathObjectOffset(SceneObject sceneObject = null, Point3F offset = null) {
offset = offset ?? new Point3F("0 0 0");
offset.Alloc();             InternalUnsafeMethods.SetPathObjectOffset__Args _args = new InternalUnsafeMethods.SetPathObjectOffset__Args() {
                sceneObject = sceneObject.ObjectPtr,
                offset = offset.internalStructPtr,
             };
             InternalUnsafeMethods.SetPathObjectOffset()(ObjectPtr, _args);
offset.Free();        }

        /// <description>
        /// ( SimObject pObject ) - Get the position offset assigned to this object.
        /// </description>
        /// <param name="pObject">The SimObjectID of the object being observed.</param>
        /// <returns>Returns the position offset.</returns>
        public string GetPathObjectOffset(SceneObject sceneObject = null) {
             InternalUnsafeMethods.GetPathObjectOffset__Args _args = new InternalUnsafeMethods.GetPathObjectOffset__Args() {
                sceneObject = sceneObject.ObjectPtr,
             };
             IntPtr _engineResult = InternalUnsafeMethods.GetPathObjectOffset()(ObjectPtr, _args);
             return StringMarshal.IntPtrToUtf8String(_engineResult);
        }

        /// <description>
        /// ( SimObject pObject, float pTimeInterp ) - Set the interp position of the object between its current nodes.
        /// </description>
        /// <param name="pObject">The SimObjectID of the object being altered.</param>
        /// <param name="pTimeInterp">The new interp position of the object.</param>
        /// <returns>No return value.</returns>
        public void SetPathObjectInterp(SceneObject sceneObject = null, float timeInterp = 1f) {
             InternalUnsafeMethods.SetPathObjectInterp__Args _args = new InternalUnsafeMethods.SetPathObjectInterp__Args() {
                sceneObject = sceneObject.ObjectPtr,
                timeInterp = timeInterp,
             };
             InternalUnsafeMethods.SetPathObjectInterp()(ObjectPtr, _args);
        }

        /// <description>
        /// ( SimObject pObject ) - Get the current interp position of the path object.
        /// </description>
        /// <param name="pObject">The SimObjectID of the object being observed.</param>
        /// <returns>Returns the current interp position.</returns>
        public float GetPathObjectInterp(SceneObject sceneObject = null) {
             InternalUnsafeMethods.GetPathObjectInterp__Args _args = new InternalUnsafeMethods.GetPathObjectInterp__Args() {
                sceneObject = sceneObject.ObjectPtr,
             };
             float _engineResult = InternalUnsafeMethods.GetPathObjectInterp()(ObjectPtr, _args);
             return _engineResult;
        }

        /// <description>
        /// ( SimObject pObject, bool pActive ) - Enable or disable the object from traveling around this path. Inactive objects are still attached to the path, but are not updated.
        /// </description>
        /// <param name="pObject">The SimObjectID of the object being altered.</param>
        /// <param name="pActive">The new status of the object.</param>
        /// <returns>No return value.</returns>
        public void SetPathObjectActive(SceneObject sceneObject = null, bool isActive = true) {
             InternalUnsafeMethods.SetPathObjectActive__Args _args = new InternalUnsafeMethods.SetPathObjectActive__Args() {
                sceneObject = sceneObject.ObjectPtr,
                isActive = isActive,
             };
             InternalUnsafeMethods.SetPathObjectActive()(ObjectPtr, _args);
        }

        /// <description>
        /// ( SimObject pObject ) - Is the object actively traveling around this path?
        /// </description>
        /// <param name="pObject">The SimObjectID of the object being observed.</param>
        /// <returns>Returns true of the object is active.</returns>
        public bool IsPathObjectActive(SceneObject sceneObject = null) {
             InternalUnsafeMethods.IsPathObjectActive__Args _args = new InternalUnsafeMethods.IsPathObjectActive__Args() {
                sceneObject = sceneObject.ObjectPtr,
             };
             bool _engineResult = InternalUnsafeMethods.IsPathObjectActive()(ObjectPtr, _args);
             return _engineResult;
        }

        /// <description>
        /// ( int pNodeIndex, string pOrientationType, [vector pPoint] ) - Set the orientation mode of the node.
        /// </description>
        /// <param name="pNodeIndex">The index of the node.</param>
        /// <param name="pOrientationType">The new orientation type of the object.</param>
        /// <param name="pPoint">If the orientation type is set to POINT, this parameter must be a vector.</param>
        /// <returns>No return value.</returns>
        public void SetNodeOrientationMode(params string[] args) { 
            List<string> _argList = new List<string>() {"", ""};
            _argList.AddRange(args);

            StringVector nativeVecArgs = new StringVector {
                ElementCount = (uint)_argList.Count,
                Array = _argList.ToArray(),
                ArraySize = (uint)_argList.Count
            };
            nativeVecArgs.Alloc();
            InternalUnsafeMethods.SetNodeOrientationMode()(ObjectPtr, ref nativeVecArgs.internalStruct);
            nativeVecArgs.Free();

        }

        /// <description>
        /// ( int pNodeIndex ) - Gets the current orientation mode of the node.
        /// </description>
        /// <param name="pNodeIndex">The index of the node.</param>
        /// <returns>Returns a string indicating the orientation mode and its properties.</returns>
        public string GetNodeOrientationMode(int nodeIndex = 0) {
             InternalUnsafeMethods.GetNodeOrientationMode__Args _args = new InternalUnsafeMethods.GetNodeOrientationMode__Args() {
                nodeIndex = nodeIndex,
             };
             IntPtr _engineResult = InternalUnsafeMethods.GetNodeOrientationMode()(ObjectPtr, _args);
             return StringMarshal.IntPtrToUtf8String(_engineResult);
        }

        /// <description>
        /// ( int pNodeIndex, float pWeight ) - Set the weight of the given node.
        /// </description>
        /// <param name="pNodeIndex">The index of the node.</param>
        /// <param name="pWeight">The new weight to be applied to the node.</param>
        /// <returns>No return value.</returns>
        public void SetNodeWeight(int nodeIndex = 0, float nodeWeight = 1f) {
             InternalUnsafeMethods.SetNodeWeight__Args _args = new InternalUnsafeMethods.SetNodeWeight__Args() {
                nodeIndex = nodeIndex,
                nodeWeight = nodeWeight,
             };
             InternalUnsafeMethods.SetNodeWeight()(ObjectPtr, _args);
        }

        /// <description>
        /// ( int pNodeIndex, angAxis pRotation ) - Set the rotation of the given node.
        /// </description>
        /// <param name="pNodeIndex">The index of the node.</param>
        /// <param name="pRotation">The new rotation to be applied to the node.</param>
        /// <returns>No return value.</returns>
        public void SetNodeRotation(int nodeIndex = 0, AngAxisF aa = null) {
aa = aa ?? new AngAxisF("0 0 0 0");
aa.Alloc();             InternalUnsafeMethods.SetNodeRotation__Args _args = new InternalUnsafeMethods.SetNodeRotation__Args() {
                nodeIndex = nodeIndex,
                aa = aa.internalStructPtr,
             };
             InternalUnsafeMethods.SetNodeRotation()(ObjectPtr, _args);
aa.Free();        }

        /// <description>
        /// ( int pNodeIndex, vector pPosition ) - Set the position of the given node.
        /// </description>
        /// <param name="pNodeIndex">The index of the node.</param>
        /// <param name="pPosition">The new position to be applied to the node.</param>
        /// <returns>No return value.</returns>
        public void SetNodePosition(int nodeIndex = 0, Point3F position = null) {
position = position ?? new Point3F("0 0 0");
position.Alloc();             InternalUnsafeMethods.SetNodePosition__Args _args = new InternalUnsafeMethods.SetNodePosition__Args() {
                nodeIndex = nodeIndex,
                position = position.internalStructPtr,
             };
             InternalUnsafeMethods.SetNodePosition()(ObjectPtr, _args);
position.Free();        }

        /// <description>
        /// ( int pNodeIndex, matrix pTransform ) - Set the transform of the given node.
        /// </description>
        /// <param name="pNodeIndex">The index of the node.</param>
        /// <param name="pTransform">The new transform to be applied to the node.</param>
        /// <returns>No return value.</returns>
        public void SetNodeTransform(int nodeIndex = 0, TransformF transform = null) {
transform = transform ?? new TransformF("0 0 0 0 0 0 0 false");
transform.Alloc();             InternalUnsafeMethods.SetNodeTransform__Args _args = new InternalUnsafeMethods.SetNodeTransform__Args() {
                nodeIndex = nodeIndex,
                transform = transform.internalStructPtr,
             };
             InternalUnsafeMethods.SetNodeTransform()(ObjectPtr, _args);
transform.Free();        }

        /// <description>
        /// ( int pNodeIndex ) - Get the length of the given node.
        /// </description>
        /// <param name="pNodeIndex">The index of the node.</param>
        /// <returns>Returns the length of the given node.</returns>
        public float GetNodeLength(int nodeIndex = 0) {
             InternalUnsafeMethods.GetNodeLength__Args _args = new InternalUnsafeMethods.GetNodeLength__Args() {
                nodeIndex = nodeIndex,
             };
             float _engineResult = InternalUnsafeMethods.GetNodeLength()(ObjectPtr, _args);
             return _engineResult;
        }

        /// <description>
        /// ( int pNodeIndex ) - Get the weight of the given node.
        /// </description>
        /// <param name="pNodeIndex">The index of the node.</param>
        /// <returns>Returns the weight of the given node.</returns>
        public float GetNodeWeight(int nodeIndex = 0) {
             InternalUnsafeMethods.GetNodeWeight__Args _args = new InternalUnsafeMethods.GetNodeWeight__Args() {
                nodeIndex = nodeIndex,
             };
             float _engineResult = InternalUnsafeMethods.GetNodeWeight()(ObjectPtr, _args);
             return _engineResult;
        }

        /// <description>
        /// ( int pNodeIndex ) - Get the World Rotation of the given node.
        /// </description>
        /// <param name="pNodeIndex">The index of the node.</param>
        /// <returns>Returns the World Rotation of the given node.</returns>
        public AngAxisF GetNodeWorldRotation(int nodeIndex = 0) {
             InternalUnsafeMethods.GetNodeWorldRotation__Args _args = new InternalUnsafeMethods.GetNodeWorldRotation__Args() {
                nodeIndex = nodeIndex,
             };
             AngAxisF.InternalStruct _engineResult = InternalUnsafeMethods.GetNodeWorldRotation()(ObjectPtr, _args);
             return new AngAxisF(_engineResult);
        }

        /// <description>
        /// ( int pNodeIndex ) - Get the position of the given node.
        /// </description>
        /// <param name="pNodeIndex">The index of the node.</param>
        /// <returns>Returns the World Position of the given node.</returns>
        public Point3F GetNodeWorldPosition(int nodeIndex = 0) {
             InternalUnsafeMethods.GetNodeWorldPosition__Args _args = new InternalUnsafeMethods.GetNodeWorldPosition__Args() {
                nodeIndex = nodeIndex,
             };
             Point3F.InternalStruct _engineResult = InternalUnsafeMethods.GetNodeWorldPosition()(ObjectPtr, _args);
             return new Point3F(_engineResult);
        }

        /// <description>
        /// ( int pNodeIndex ) - Get the World Transform (position and rotation) of the given node.
        /// </description>
        /// <param name="pNodeIndex">The index of the node.</param>
        /// <returns>Returns the transform of the given node.</returns>
        public TransformF GetNodeWorldTransform(int nodeIndex = 0) {
             InternalUnsafeMethods.GetNodeWorldTransform__Args _args = new InternalUnsafeMethods.GetNodeWorldTransform__Args() {
                nodeIndex = nodeIndex,
             };
             TransformF.InternalStruct _engineResult = InternalUnsafeMethods.GetNodeWorldTransform()(ObjectPtr, _args);
             return new TransformF(_engineResult);
        }

        /// <description>
        /// ( int pNodeIndex ) - Get the Local Rotation of the given node.
        /// </description>
        /// <param name="pNodeIndex">The index of the node.</param>
        /// <returns>Returns the Local Rotation of the given node.</returns>
        public AngAxisF GetNodeLocalRotation(int nodeIndex = 0) {
             InternalUnsafeMethods.GetNodeLocalRotation__Args _args = new InternalUnsafeMethods.GetNodeLocalRotation__Args() {
                nodeIndex = nodeIndex,
             };
             AngAxisF.InternalStruct _engineResult = InternalUnsafeMethods.GetNodeLocalRotation()(ObjectPtr, _args);
             return new AngAxisF(_engineResult);
        }

        /// <description>
        /// ( int pNodeIndex ) - Get the position of the given node.
        /// </description>
        /// <param name="pNodeIndex">The index of the node.</param>
        /// <returns>Returns the Local Position of the given node.</returns>
        public Point3F GetNodeLocalPosition(int nodeIndex = 0) {
             InternalUnsafeMethods.GetNodeLocalPosition__Args _args = new InternalUnsafeMethods.GetNodeLocalPosition__Args() {
                nodeIndex = nodeIndex,
             };
             Point3F.InternalStruct _engineResult = InternalUnsafeMethods.GetNodeLocalPosition()(ObjectPtr, _args);
             return new Point3F(_engineResult);
        }

        /// <description>
        /// ( int pNodeIndex ) - Get the local transform (local position and rotation) of the given node.
        /// </description>
        /// <param name="pNodeIndex">The index of the node.</param>
        /// <returns>Returns the transform of the given node.</returns>
        public string GetNodeLocalTransform(int nodeIndex = 0) {
             InternalUnsafeMethods.GetNodeLocalTransform__Args _args = new InternalUnsafeMethods.GetNodeLocalTransform__Args() {
                nodeIndex = nodeIndex,
             };
             IntPtr _engineResult = InternalUnsafeMethods.GetNodeLocalTransform()(ObjectPtr, _args);
             return StringMarshal.IntPtrToUtf8String(_engineResult);
        }

        /// <description>
        /// () - Get the number of nodes in this path.
        /// </description>
        /// <returns>Returns the number of nodes.</returns>
        public int GetNodeCount() {
             InternalUnsafeMethods.GetNodeCount__Args _args = new InternalUnsafeMethods.GetNodeCount__Args() {
             };
             int _engineResult = InternalUnsafeMethods.GetNodeCount()(ObjectPtr, _args);
             return _engineResult;
        }

        /// <description>
        /// ( int pSrcNodeIndex, int pDstNodeIndex, int pTimeInterp ) - Get the world position of the path at the interp point between two nodes.
        /// </description>
        /// <param name="pSrcNodeIndex">The first node.</param>
        /// <param name="pDstNodeIndex">The second node.</param>
        /// <param name="pTimeInterp">The time to interp between the two nodes. Value is between 0.0 and 1.0.</param>
        /// <returns>Returns the world position of the interp time between the two given nodes.</returns>
        public string GetPathPosition(int srcNodeIndex = 0, int dstNodeIndex = 0, float timeInterp = 1f) {
             InternalUnsafeMethods.GetPathPosition__Args _args = new InternalUnsafeMethods.GetPathPosition__Args() {
                srcNodeIndex = srcNodeIndex,
                dstNodeIndex = dstNodeIndex,
                timeInterp = timeInterp,
             };
             IntPtr _engineResult = InternalUnsafeMethods.GetPathPosition()(ObjectPtr, _args);
             return StringMarshal.IntPtrToUtf8String(_engineResult);
        }

        /// <description>
        /// ( int pSrcNodeIndex, int pDstNodeIndex, float pTimeInterp ) - Get the transform of the path at the interp point between two nodes.
        /// </description>
        /// <param name="pSrcNodeIndex">The first node.</param>
        /// <param name="pDstNodeIndex">The second node.</param>
        /// <param name="pTimeInterp">The time to interp between the two nodes. Value is between 0.0 and 1.0.</param>
        /// <returns>Returns the transform of the interp time between the two given nodes.</returns>
        public string GetPathTransform(int srcNodeIndex = 0, int dstNodeIndex = 0, float timeInterp = 1f) {
             InternalUnsafeMethods.GetPathTransform__Args _args = new InternalUnsafeMethods.GetPathTransform__Args() {
                srcNodeIndex = srcNodeIndex,
                dstNodeIndex = dstNodeIndex,
                timeInterp = timeInterp,
             };
             IntPtr _engineResult = InternalUnsafeMethods.GetPathTransform()(ObjectPtr, _args);
             return StringMarshal.IntPtrToUtf8String(_engineResult);
        }

        /// <description>
        /// ( SimObject pObject ) - Detach the object from this path in place.
        /// </description>
        /// <param name="pObject">The SimObjectID of the object to be detached.</param>
        /// <returns>No return value.</returns>
        public void DetachObject(SceneObject sceneObject = null) {
             InternalUnsafeMethods.DetachObject__Args _args = new InternalUnsafeMethods.DetachObject__Args() {
                sceneObject = sceneObject.ObjectPtr,
             };
             InternalUnsafeMethods.DetachObject()(ObjectPtr, _args);
        }

        /// <description>
        /// ( SimObject pObject, bool pForward, float pSpeed, bool pRelative, int pStartNode, [int pEndNode] ) - Attach an object to this path with the given properties. If the object is already attached to a path, then a warning will be displayed and the object will *not* be attached to this path.
        /// </description>
        /// <param name="pObject">The SimObjectID of the object to be attached.</param>
        /// <param name="pForward">Should the object be moving forward?</param>
        /// <param name="pSpeed">The speed that the object will travel around the path.</param>
        /// <param name="pRelative">Offset the object based on the difference between the start node and its current position.</param>
        /// <param name="pStartNode">The index of the node this object starts pathing from.</param>
        /// <param name="pEndNode">The index of the node this object will stop pathing at.</param>
        /// <returns>No return value.</returns>
        public void AttachObject(params string[] args) { 
            List<string> _argList = new List<string>() {"", ""};
            _argList.AddRange(args);

            StringVector nativeVecArgs = new StringVector {
                ElementCount = (uint)_argList.Count,
                Array = _argList.ToArray(),
                ArraySize = (uint)_argList.Count
            };
            nativeVecArgs.Alloc();
            InternalUnsafeMethods.AttachObject()(ObjectPtr, ref nativeVecArgs.internalStruct);
            nativeVecArgs.Free();

        }

        /// <description>
        /// ( SimObject pObject ) - Is the object attached to this path?
        /// </description>
        /// <param name="pObject">The SimObjectID of the object you wish to check.</param>
        /// <returns>Returns true if the object is attached to this path.</returns>
        public bool IsObjectAttached(SceneObject sceneObject = null) {
             InternalUnsafeMethods.IsObjectAttached__Args _args = new InternalUnsafeMethods.IsObjectAttached__Args() {
                sceneObject = sceneObject.ObjectPtr,
             };
             bool _engineResult = InternalUnsafeMethods.IsObjectAttached()(ObjectPtr, _args);
             return _engineResult;
        }

        /// <description>
        /// ( int pNodeIndex ) - Delete the node with the given index. If you delete a node that an attached object is moving to, or from then the object's movement will adjust so that it has a valid path.
        /// </description>
        /// <param name="pNodeIndex">The index of the node to be deleted.</param>
        /// <returns>No return value.</returns>
        public void DeleteNode(int nodeIndex = 0) {
             InternalUnsafeMethods.DeleteNode__Args _args = new InternalUnsafeMethods.DeleteNode__Args() {
                nodeIndex = nodeIndex,
             };
             InternalUnsafeMethods.DeleteNode()(ObjectPtr, _args);
        }

        /// <description>
        /// ( transform pTransform, float pWeight, [int pLocation] ) - Add a node with the given properties. Nodes represent physical points that attached objects move towards or between, but the PathType determines "how" they move between them.
        /// </description>
        /// <param name="pTransform">The position and rotation of the new node.</param>
        /// <param name="pWeight">The weight of the new node.</param>
        /// <param name="pLocation">The index of the new node.</param>
        /// <returns>No return value.</returns>
        public void AddNode(TransformF transform = null, float weight = 1f, int location = -1) {
transform = transform ?? new TransformF("0 0 0 0 0 0 0 false");
transform.Alloc();             InternalUnsafeMethods.AddNode__Args _args = new InternalUnsafeMethods.AddNode__Args() {
                transform = transform.internalStructPtr,
                weight = weight,
                location = location,
             };
             InternalUnsafeMethods.AddNode()(ObjectPtr, _args);
transform.Free();        }

        /// <description>
        /// ( string pPathType ) - The path type dictates how attached objects move between nodes. There are currently two supported path types, "BEZIER" and "LINEAR".
        /// </description>
        /// <returns>No return value.</returns>
        public void SetPathType(string pathType = "LINEAR") {
             InternalUnsafeMethods.SetPathType__Args _args = new InternalUnsafeMethods.SetPathType__Args() {
                pathType = pathType,
             };
             InternalUnsafeMethods.SetPathType()(ObjectPtr, _args);
        }

        /// <description>
        /// Get the type info object for the VPath class.
        /// </description>
        /// <returns>The type info object for VPath</returns>
        public static EngineTypeInfo StaticGetType() {
             InternalUnsafeMethods.StaticGetType__Args _args = new InternalUnsafeMethods.StaticGetType__Args() {
             };
             IntPtr _engineResult = InternalUnsafeMethods.StaticGetType()(_args);
             return new EngineTypeInfo(_engineResult);
        }


        /// <value>
        /// <description>
        /// The type of path this is.
        /// </description>
        /// </value>
        public VPathType PathType {
            get => GenericMarshal.StringTo<VPathType>(GetFieldValue("PathType"));
            set => SetFieldValue("PathType", GenericMarshal.ToString(value));
        }
    }
}