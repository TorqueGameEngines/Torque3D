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
    /// <summary>A spline along which various objects can move along. The spline object acts like a container for Marker objects, which make</summary>
    /// <description>
    /// up the joints, or knots, along the path. Paths can be assigned a speed, can be looping or non-looping. Each of a path's markers can be
    /// one of three primary movement types: "normal", "Position Only", or "Kink".
    /// </description>
    /// <code>
    /// new path()
    /// 	{
    ///      isLooping = "1";
    /// 
    ///      new Marker()
    /// 		{
    /// 			seqNum = "0";
    /// 			type = "Normal";
    /// 			msToNext = "1000";
    /// 			smoothingType = "Spline";
    /// 			position = "-0.054708 -35.0612 234.802";
    /// 			rotation = "1 0 0 0";
    ///       };
    /// 
    /// 	};
    /// </code>
    /// <see cref="Marker" />
    /// <see cref="NetConnection::transmitPaths()" />
    /// <see cref="NetConnection::clearPaths()" />
    /// <see cref="Path" />
    public unsafe class Path : GameBase {
        public Path(bool pRegister = false) 
            : base(pRegister) {
        }
        
        public Path(string pName, bool pRegister) 
            : this(false) {
            Name = pName;
            if (pRegister) {
                RegisterObject();
            }
        }
        
        public Path(string pName) 
            : this(pName, false) {
        }
        
        public Path(string pName, string pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(Engine.Sim.FindObject<SimObject>(pParent));
        }
        
        public Path(string pName, SimObject pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(pParent);
        }
        
        public Path(SimObject pObj) 
            : base(pObj) {
        }
        
        public Path(IntPtr pObj) 
            : base(pObj) {
        }
        
		protected override void CreateObjectPtr()
		{
			ObjectPtr = InternalUnsafeMethods.Create()(new InternalUnsafeMethods.Create__Args());
		}

        #region UnsafeNativeMethods
        new internal struct InternalUnsafeMethods {
            [StructLayout(LayoutKind.Sequential)]
            internal struct GetPathId__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate int _GetPathId(IntPtr _this, GetPathId__Args args);
            private static _GetPathId _GetPathIdFunc;
            internal static _GetPathId GetPathId() {
                if (_GetPathIdFunc == null) {
                    _GetPathIdFunc =
                        (_GetPathId)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnPath_getPathId"), typeof(_GetPathId));
                }
                
                return _GetPathIdFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct OnAdd__Args
            {
                internal uint ID;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _OnAdd(IntPtr _this, OnAdd__Args args);
            private static _OnAdd _OnAddFunc;
            internal static _OnAdd OnAdd() {
                if (_OnAddFunc == null) {
                    _OnAddFunc =
                        (_OnAdd)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "cbPath_onAdd"), typeof(_OnAdd));
                }
                
                return _OnAddFunc;
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
                                "fnPath_staticGetType"), typeof(_StaticGetType));
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
                                "fnPath_create"), typeof(_Create));
                }
                
                return _CreateFunc;
            }
        }
        #endregion

        /// <summary>Returns the PathID (not the object ID) of this path.</summary>
        /// <description>
        /// 
        /// </description>
        /// <returns>PathID (not the object ID) of this path.</returns>
        /// <code>
        /// // Acquire the PathID of this path object.
        /// %pathID = %thisPath.getPathId();
        /// </code>
        public int GetPathId() {
             InternalUnsafeMethods.GetPathId__Args _args = new InternalUnsafeMethods.GetPathId__Args() {
             };
             int _engineResult = InternalUnsafeMethods.GetPathId()(ObjectPtr, _args);
             return _engineResult;
        }

        /// <description>
        /// Called when this ScriptGroup is added to the system.
        /// </description>
        /// <param name="ID">Unique object ID assigned when created (%this in script).</param>
        public virtual void OnAdd(uint ID) {
             InternalUnsafeMethods.OnAdd__Args _args = new InternalUnsafeMethods.OnAdd__Args() {
                ID = ID,
             };
             InternalUnsafeMethods.OnAdd()(ObjectPtr, _args);
        }

        /// <description>
        /// Get the type info object for the Path class.
        /// </description>
        /// <returns>The type info object for Path</returns>
        public static EngineTypeInfo StaticGetType() {
             InternalUnsafeMethods.StaticGetType__Args _args = new InternalUnsafeMethods.StaticGetType__Args() {
             };
             IntPtr _engineResult = InternalUnsafeMethods.StaticGetType()(_args);
             return new EngineTypeInfo(_engineResult);
        }


        /// <value>
        /// <description>
        /// If this is true, the loop is closed, otherwise it is open.
        /// </description>
        /// </value>
        public bool IsLooping {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("isLooping"));
            set => SetFieldValue("isLooping", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Speed.
        /// </description>
        /// </value>
        public float Speed {
            get => GenericMarshal.StringTo<float>(GetFieldValue("speed"));
            set => SetFieldValue("speed", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <summary>Spawned PathShape.</summary>
        /// <description>
        /// 
        /// </description>
        /// </value>
        public PathShapeData MPathShape {
            get => GenericMarshal.StringTo<PathShapeData>(GetFieldValue("mPathShape"));
            set => SetFieldValue("mPathShape", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Spawn Count.
        /// </description>
        /// </value>
        public int SpawnCount {
            get => GenericMarshal.StringTo<int>(GetFieldValue("spawnCount"));
            set => SetFieldValue("spawnCount", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Spawn Delay (min).
        /// </description>
        /// </value>
        public int MinDelay {
            get => GenericMarshal.StringTo<int>(GetFieldValue("minDelay"));
            set => SetFieldValue("minDelay", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Spawn Delay (max).
        /// </description>
        /// </value>
        public int MaxDelay {
            get => GenericMarshal.StringTo<int>(GetFieldValue("maxDelay"));
            set => SetFieldValue("maxDelay", GenericMarshal.ToString(value));
        }
    }
}