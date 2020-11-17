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
    /// <summary>Scriptable, demo-able datablock.  Used by GameBase objects.</summary>
    /// <description>
    /// 
    /// </description>
    /// <see cref="GameBase" />
    public unsafe class GameBaseData : SimDataBlock {
        public GameBaseData(bool pRegister = false) 
            : base(pRegister) {
        }
        
        public GameBaseData(string pName, bool pRegister) 
            : this(false) {
            Name = pName;
            if (pRegister) {
                RegisterObject();
            }
        }
        
        public GameBaseData(string pName) 
            : this(pName, false) {
        }
        
        public GameBaseData(string pName, string pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(Engine.Sim.FindObject<SimObject>(pParent));
        }
        
        public GameBaseData(string pName, SimObject pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(pParent);
        }
        
        public GameBaseData(SimObject pObj) 
            : base(pObj) {
        }
        
        public GameBaseData(IntPtr pObj) 
            : base(pObj) {
        }
        
		protected override void CreateObjectPtr()
		{
			ObjectPtr = InternalUnsafeMethods.Create()(new InternalUnsafeMethods.Create__Args());
		}

        #region UnsafeNativeMethods
        new internal struct InternalUnsafeMethods {
            [StructLayout(LayoutKind.Sequential)]
            internal struct OnUnmount__Args
            {
                internal IntPtr obj;
                internal IntPtr mountObj;
                internal int node;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _OnUnmount(IntPtr _this, OnUnmount__Args args);
            private static _OnUnmount _OnUnmountFunc;
            internal static _OnUnmount OnUnmount() {
                if (_OnUnmountFunc == null) {
                    _OnUnmountFunc =
                        (_OnUnmount)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "cbGameBaseData_onUnmount"), typeof(_OnUnmount));
                }
                
                return _OnUnmountFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct OnMount__Args
            {
                internal IntPtr obj;
                internal IntPtr mountObj;
                internal int node;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _OnMount(IntPtr _this, OnMount__Args args);
            private static _OnMount _OnMountFunc;
            internal static _OnMount OnMount() {
                if (_OnMountFunc == null) {
                    _OnMountFunc =
                        (_OnMount)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "cbGameBaseData_onMount"), typeof(_OnMount));
                }
                
                return _OnMountFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct OnRemove__Args
            {
                internal IntPtr obj;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _OnRemove(IntPtr _this, OnRemove__Args args);
            private static _OnRemove _OnRemoveFunc;
            internal static _OnRemove OnRemove() {
                if (_OnRemoveFunc == null) {
                    _OnRemoveFunc =
                        (_OnRemove)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "cbGameBaseData_onRemove"), typeof(_OnRemove));
                }
                
                return _OnRemoveFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct OnNewDataBlock__Args
            {
                internal IntPtr obj;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _OnNewDataBlock(IntPtr _this, OnNewDataBlock__Args args);
            private static _OnNewDataBlock _OnNewDataBlockFunc;
            internal static _OnNewDataBlock OnNewDataBlock() {
                if (_OnNewDataBlockFunc == null) {
                    _OnNewDataBlockFunc =
                        (_OnNewDataBlock)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "cbGameBaseData_onNewDataBlock"), typeof(_OnNewDataBlock));
                }
                
                return _OnNewDataBlockFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct OnAdd__Args
            {
                internal IntPtr obj;
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
                                "cbGameBaseData_onAdd"), typeof(_OnAdd));
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
                                "fnGameBaseData_staticGetType"), typeof(_StaticGetType));
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
                                "fnGameBaseData_create"), typeof(_Create));
                }
                
                return _CreateFunc;
            }
        }
        #endregion

        /// <summary>Called when the object is unmounted from another object in the scene.</summary>
        /// <description>
        /// 
        /// </description>
        /// <param name="obj">the GameBase object being unmounted</param>
        /// <param name="mountObj">the object we are unmounted from</param>
        /// <param name="node">the mountObj node we are unmounted from</param>
        /// <see cref="onAdd for an example" />
        public virtual void OnUnmount(SceneObject obj, SceneObject mountObj, int node) {
             InternalUnsafeMethods.OnUnmount__Args _args = new InternalUnsafeMethods.OnUnmount__Args() {
                obj = obj.ObjectPtr,
                mountObj = mountObj.ObjectPtr,
                node = node,
             };
             InternalUnsafeMethods.OnUnmount()(ObjectPtr, _args);
        }

        /// <summary>Called when the object is mounted to another object in the scene.</summary>
        /// <description>
        /// 
        /// </description>
        /// <param name="obj">the GameBase object being mounted</param>
        /// <param name="mountObj">the object we are mounted to</param>
        /// <param name="node">the mountObj node we are mounted to</param>
        /// <see cref="onAdd for an example" />
        public virtual void OnMount(SceneObject obj, SceneObject mountObj, int node) {
             InternalUnsafeMethods.OnMount__Args _args = new InternalUnsafeMethods.OnMount__Args() {
                obj = obj.ObjectPtr,
                mountObj = mountObj.ObjectPtr,
                node = node,
             };
             InternalUnsafeMethods.OnMount()(ObjectPtr, _args);
        }

        /// <summary>Called when the object is removed from the scene.</summary>
        /// <description>
        /// 
        /// </description>
        /// <param name="obj">the GameBase object</param>
        /// <see cref="onAdd for an example" />
        public virtual void OnRemove(GameBase obj) {
             InternalUnsafeMethods.OnRemove__Args _args = new InternalUnsafeMethods.OnRemove__Args() {
                obj = obj.ObjectPtr,
             };
             InternalUnsafeMethods.OnRemove()(ObjectPtr, _args);
        }

        /// <summary>Called when the object has a new datablock assigned.</summary>
        /// <description>
        /// 
        /// </description>
        /// <param name="obj">the GameBase object</param>
        /// <see cref="onAdd for an example" />
        public virtual void OnNewDataBlock(GameBase obj) {
             InternalUnsafeMethods.OnNewDataBlock__Args _args = new InternalUnsafeMethods.OnNewDataBlock__Args() {
                obj = obj.ObjectPtr,
             };
             InternalUnsafeMethods.OnNewDataBlock()(ObjectPtr, _args);
        }

        /// <summary>Called when the object is added to the scene.</summary>
        /// <description>
        /// 
        /// </description>
        /// <param name="obj">the GameBase object</param>
        /// <code>
        /// datablock GameBaseData(MyObjectData)
        /// {
        ///    category = "Misc";
        /// };
        /// 
        /// function MyObjectData::onAdd( %this, %obj )
        /// {
        ///    echo( "Added "@ %obj.getName() 
        /// </code>
        public virtual void OnAdd(GameBase obj) {
             InternalUnsafeMethods.OnAdd__Args _args = new InternalUnsafeMethods.OnAdd__Args() {
                obj = obj.ObjectPtr,
             };
             InternalUnsafeMethods.OnAdd()(ObjectPtr, _args);
        }

        /// <description>
        /// Get the type info object for the GameBaseData class.
        /// </description>
        /// <returns>The type info object for GameBaseData</returns>
        public static EngineTypeInfo StaticGetType() {
             InternalUnsafeMethods.StaticGetType__Args _args = new InternalUnsafeMethods.StaticGetType__Args() {
             };
             IntPtr _engineResult = InternalUnsafeMethods.StaticGetType()(_args);
             return new EngineTypeInfo(_engineResult);
        }


        /// <value>
        /// <description>
        /// The group that this datablock will show up in under the "Scripted" tab in the World Editor Library.
        /// </description>
        /// </value>
        public string Category {
            get => GenericMarshal.StringTo<string>(GetFieldValue("category"));
            set => SetFieldValue("category", GenericMarshal.ToString(value));
        }
    }
}