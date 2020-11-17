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
    public unsafe class NavPath : SceneObject {
        public NavPath(bool pRegister = false) 
            : base(pRegister) {
        }
        
        public NavPath(string pName, bool pRegister) 
            : this(false) {
            Name = pName;
            if (pRegister) {
                RegisterObject();
            }
        }
        
        public NavPath(string pName) 
            : this(pName, false) {
        }
        
        public NavPath(string pName, string pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(Engine.Sim.FindObject<SimObject>(pParent));
        }
        
        public NavPath(string pName, SimObject pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(pParent);
        }
        
        public NavPath(SimObject pObj) 
            : base(pObj) {
        }
        
        public NavPath(IntPtr pObj) 
            : base(pObj) {
        }
        
		protected override void CreateObjectPtr()
		{
			ObjectPtr = InternalUnsafeMethods.Create()(new InternalUnsafeMethods.Create__Args());
		}

        #region UnsafeNativeMethods
        new internal struct InternalUnsafeMethods {
            [StructLayout(LayoutKind.Sequential)]
            internal struct GetLength__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate float _GetLength(IntPtr _this, GetLength__Args args);
            private static _GetLength _GetLengthFunc;
            internal static _GetLength GetLength() {
                if (_GetLengthFunc == null) {
                    _GetLengthFunc =
                        (_GetLength)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnNavPath_getLength"), typeof(_GetLength));
                }
                
                return _GetLengthFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct GetFlags__Args
            {
                internal int idx;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate int _GetFlags(IntPtr _this, GetFlags__Args args);
            private static _GetFlags _GetFlagsFunc;
            internal static _GetFlags GetFlags() {
                if (_GetFlagsFunc == null) {
                    _GetFlagsFunc =
                        (_GetFlags)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnNavPath_getFlags"), typeof(_GetFlags));
                }
                
                return _GetFlagsFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct GetNode__Args
            {
                internal int idx;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate Point3F.InternalStruct _GetNode(IntPtr _this, GetNode__Args args);
            private static _GetNode _GetNodeFunc;
            internal static _GetNode GetNode() {
                if (_GetNodeFunc == null) {
                    _GetNodeFunc =
                        (_GetNode)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnNavPath_getNode"), typeof(_GetNode));
                }
                
                return _GetNodeFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct Size__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate int _Size(IntPtr _this, Size__Args args);
            private static _Size _SizeFunc;
            internal static _Size Size() {
                if (_SizeFunc == null) {
                    _SizeFunc =
                        (_Size)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnNavPath_size"), typeof(_Size));
                }
                
                return _SizeFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct OnNavMeshUpdateBox__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string data;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _OnNavMeshUpdateBox(IntPtr _this, OnNavMeshUpdateBox__Args args);
            private static _OnNavMeshUpdateBox _OnNavMeshUpdateBoxFunc;
            internal static _OnNavMeshUpdateBox OnNavMeshUpdateBox() {
                if (_OnNavMeshUpdateBoxFunc == null) {
                    _OnNavMeshUpdateBoxFunc =
                        (_OnNavMeshUpdateBox)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnNavPath_onNavMeshUpdateBox"), typeof(_OnNavMeshUpdateBox));
                }
                
                return _OnNavMeshUpdateBoxFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct OnNavMeshUpdate__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string data;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _OnNavMeshUpdate(IntPtr _this, OnNavMeshUpdate__Args args);
            private static _OnNavMeshUpdate _OnNavMeshUpdateFunc;
            internal static _OnNavMeshUpdate OnNavMeshUpdate() {
                if (_OnNavMeshUpdateFunc == null) {
                    _OnNavMeshUpdateFunc =
                        (_OnNavMeshUpdate)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnNavPath_onNavMeshUpdate"), typeof(_OnNavMeshUpdate));
                }
                
                return _OnNavMeshUpdateFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct Plan__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            [return: MarshalAs(UnmanagedType.I1)]
            internal delegate bool _Plan(IntPtr _this, Plan__Args args);
            private static _Plan _PlanFunc;
            internal static _Plan Plan() {
                if (_PlanFunc == null) {
                    _PlanFunc =
                        (_Plan)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnNavPath_plan"), typeof(_Plan));
                }
                
                return _PlanFunc;
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
                                "fnNavPath_staticGetType"), typeof(_StaticGetType));
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
                                "fnNavPath_create"), typeof(_Create));
                }
                
                return _CreateFunc;
            }
        }
        #endregion

        /// <summary>Get the length of this path.</summary>
        public float GetLength() {
             InternalUnsafeMethods.GetLength__Args _args = new InternalUnsafeMethods.GetLength__Args() {
             };
             float _engineResult = InternalUnsafeMethods.GetLength()(ObjectPtr, _args);
             return _engineResult;
        }

        /// <summary>Get a specified node along the path.</summary>
        public int GetFlags(int idx) {
             InternalUnsafeMethods.GetFlags__Args _args = new InternalUnsafeMethods.GetFlags__Args() {
                idx = idx,
             };
             int _engineResult = InternalUnsafeMethods.GetFlags()(ObjectPtr, _args);
             return _engineResult;
        }

        /// <summary>Get a specified node along the path.</summary>
        public Point3F GetNode(int idx) {
             InternalUnsafeMethods.GetNode__Args _args = new InternalUnsafeMethods.GetNode__Args() {
                idx = idx,
             };
             Point3F.InternalStruct _engineResult = InternalUnsafeMethods.GetNode()(ObjectPtr, _args);
             return new Point3F(_engineResult);
        }

        /// <summary>Return the number of nodes in this path.</summary>
        public int Size() {
             InternalUnsafeMethods.Size__Args _args = new InternalUnsafeMethods.Size__Args() {
             };
             int _engineResult = InternalUnsafeMethods.Size()(ObjectPtr, _args);
             return _engineResult;
        }

        /// <summary>Callback when a particular area in this path's NavMesh is rebuilt.</summary>
        public void OnNavMeshUpdateBox(string data) {
             InternalUnsafeMethods.OnNavMeshUpdateBox__Args _args = new InternalUnsafeMethods.OnNavMeshUpdateBox__Args() {
                data = data,
             };
             InternalUnsafeMethods.OnNavMeshUpdateBox()(ObjectPtr, _args);
        }

        /// <summary>Callback when this path's NavMesh is loaded or rebuilt.</summary>
        public void OnNavMeshUpdate(string data) {
             InternalUnsafeMethods.OnNavMeshUpdate__Args _args = new InternalUnsafeMethods.OnNavMeshUpdate__Args() {
                data = data,
             };
             InternalUnsafeMethods.OnNavMeshUpdate()(ObjectPtr, _args);
        }

        /// <summary>Find a path using the already-specified path properties.</summary>
        public bool Plan() {
             InternalUnsafeMethods.Plan__Args _args = new InternalUnsafeMethods.Plan__Args() {
             };
             bool _engineResult = InternalUnsafeMethods.Plan()(ObjectPtr, _args);
             return _engineResult;
        }

        /// <description>
        /// Get the type info object for the NavPath class.
        /// </description>
        /// <returns>The type info object for NavPath</returns>
        public static EngineTypeInfo StaticGetType() {
             InternalUnsafeMethods.StaticGetType__Args _args = new InternalUnsafeMethods.StaticGetType__Args() {
             };
             IntPtr _engineResult = InternalUnsafeMethods.StaticGetType()(_args);
             return new EngineTypeInfo(_engineResult);
        }


        /// <value>
        /// <description>
        /// World location this path starts at.
        /// </description>
        /// </value>
        public Point3F From {
            get => GenericMarshal.StringTo<Point3F>(GetFieldValue("from"));
            set => SetFieldValue("from", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// World location this path should end at.
        /// </description>
        /// </value>
        public Point3F To {
            get => GenericMarshal.StringTo<Point3F>(GetFieldValue("to"));
            set => SetFieldValue("to", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Name of the NavMesh object this path travels within.
        /// </description>
        /// </value>
        public string Mesh {
            get => GenericMarshal.StringTo<string>(GetFieldValue("mesh"));
            set => SetFieldValue("mesh", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Path containing waypoints for this NavPath to visit.
        /// </description>
        /// </value>
        public Path Waypoints {
            get => GenericMarshal.StringTo<Path>(GetFieldValue("waypoints"));
            set => SetFieldValue("waypoints", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Does this path loop?
        /// </description>
        /// </value>
        public bool IsLooping {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("isLooping"));
            set => SetFieldValue("isLooping", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Plan this path over multiple updates instead of all at once.
        /// </description>
        /// </value>
        public bool IsSliced {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("isSliced"));
            set => SetFieldValue("isSliced", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Maximum iterations of path planning this path does per tick.
        /// </description>
        /// </value>
        public int MaxIterations {
            get => GenericMarshal.StringTo<int>(GetFieldValue("maxIterations"));
            set => SetFieldValue("maxIterations", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// If set, this path will automatically replan when its navigation mesh changes.
        /// </description>
        /// </value>
        public bool AutoUpdate {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("autoUpdate"));
            set => SetFieldValue("autoUpdate", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Allow the path to use dry land.
        /// </description>
        /// </value>
        public bool AllowWalk {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("allowWalk"));
            set => SetFieldValue("allowWalk", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Allow the path to use jump links.
        /// </description>
        /// </value>
        public bool AllowJump {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("allowJump"));
            set => SetFieldValue("allowJump", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Allow the path to use drop links.
        /// </description>
        /// </value>
        public bool AllowDrop {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("allowDrop"));
            set => SetFieldValue("allowDrop", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Allow the path to move in water.
        /// </description>
        /// </value>
        public bool AllowSwim {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("allowSwim"));
            set => SetFieldValue("allowSwim", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Allow the path to jump ledges.
        /// </description>
        /// </value>
        public bool AllowLedge {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("allowLedge"));
            set => SetFieldValue("allowLedge", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Allow the path to use climb links.
        /// </description>
        /// </value>
        public bool AllowClimb {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("allowClimb"));
            set => SetFieldValue("allowClimb", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Allow the path to use teleporters.
        /// </description>
        /// </value>
        public bool AllowTeleport {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("allowTeleport"));
            set => SetFieldValue("allowTeleport", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Render this NavPath even when not selected.
        /// </description>
        /// </value>
        public bool AlwaysRender {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("alwaysRender"));
            set => SetFieldValue("alwaysRender", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Render this NavPath through other objects.
        /// </description>
        /// </value>
        public bool Xray {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("xray"));
            set => SetFieldValue("xray", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Render the closed list of this NavPath's search.
        /// </description>
        /// </value>
        public bool RenderSearch {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("renderSearch"));
            set => SetFieldValue("renderSearch", GenericMarshal.ToString(value));
        }
    }
}