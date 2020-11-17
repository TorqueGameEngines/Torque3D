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
    /// <summary>A script-level OOP object which allows binding of a class, superClass and arguments along with declaration of methods.</summary>
    /// <description>
    /// ScriptObjects are extrodinarily powerful objects that allow defining of any type of data required. They can optionally have
    /// a class and a superclass defined for added control of multiple ScriptObjects through a simple class definition.
    /// </description>
    /// <code>
    /// new ScriptObject(Game)
    /// {
    ///    class = "DeathMatchGame";
    ///    superClass = GameCore;
    ///    genre = "Action FPS"; // Note the new, non-Torque variable
    /// };
    /// </code>
    /// <see cref="SimObject" />
    public unsafe class ScriptObject : SimObject {
        public ScriptObject(bool pRegister = false) 
            : base(pRegister) {
        }
        
        public ScriptObject(string pName, bool pRegister) 
            : this(false) {
            Name = pName;
            if (pRegister) {
                RegisterObject();
            }
        }
        
        public ScriptObject(string pName) 
            : this(pName, false) {
        }
        
        public ScriptObject(string pName, string pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(Engine.Sim.FindObject<SimObject>(pParent));
        }
        
        public ScriptObject(string pName, SimObject pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(pParent);
        }
        
        public ScriptObject(SimObject pObj) 
            : base(pObj) {
        }
        
        public ScriptObject(IntPtr pObj) 
            : base(pObj) {
        }
        
		protected override void CreateObjectPtr()
		{
			ObjectPtr = InternalUnsafeMethods.Create()(new InternalUnsafeMethods.Create__Args());
		}

        #region UnsafeNativeMethods
        new internal struct InternalUnsafeMethods {
            [StructLayout(LayoutKind.Sequential)]
            internal struct OnRemove__Args
            {
                internal uint ID;
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
                                "cbScriptObject_onRemove"), typeof(_OnRemove));
                }
                
                return _OnRemoveFunc;
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
                                "cbScriptObject_onAdd"), typeof(_OnAdd));
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
                                "fnScriptObject_staticGetType"), typeof(_StaticGetType));
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
                                "fnScriptObject_create"), typeof(_Create));
                }
                
                return _CreateFunc;
            }
        }
        #endregion

        /// <description>
        /// Called when this ScriptObject is removed from the system.
        /// </description>
        /// <param name="ID">Unique object ID assigned when created (%this in script).</param>
        public virtual void OnRemove(uint ID) {
             InternalUnsafeMethods.OnRemove__Args _args = new InternalUnsafeMethods.OnRemove__Args() {
                ID = ID,
             };
             InternalUnsafeMethods.OnRemove()(ObjectPtr, _args);
        }

        /// <description>
        /// Called when this ScriptObject is added to the system.
        /// </description>
        /// <param name="ID">Unique object ID assigned when created (%this in script).</param>
        public virtual void OnAdd(uint ID) {
             InternalUnsafeMethods.OnAdd__Args _args = new InternalUnsafeMethods.OnAdd__Args() {
                ID = ID,
             };
             InternalUnsafeMethods.OnAdd()(ObjectPtr, _args);
        }

        /// <description>
        /// Get the type info object for the ScriptObject class.
        /// </description>
        /// <returns>The type info object for ScriptObject</returns>
        public static EngineTypeInfo StaticGetType() {
             InternalUnsafeMethods.StaticGetType__Args _args = new InternalUnsafeMethods.StaticGetType__Args() {
             };
             IntPtr _engineResult = InternalUnsafeMethods.StaticGetType()(_args);
             return new EngineTypeInfo(_engineResult);
        }
    }
}