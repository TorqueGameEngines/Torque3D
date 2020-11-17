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
    /// <summary>Inspector support for variable groups in a GuiVariableInspector.</summary>
    /// <description>
    /// Editor use only.
    /// </description>
    public unsafe class GuiInspectorVariableGroup : GuiInspectorGroup {
        public GuiInspectorVariableGroup(bool pRegister = false) 
            : base(pRegister) {
        }
        
        public GuiInspectorVariableGroup(string pName, bool pRegister) 
            : this(false) {
            Name = pName;
            if (pRegister) {
                RegisterObject();
            }
        }
        
        public GuiInspectorVariableGroup(string pName) 
            : this(pName, false) {
        }
        
        public GuiInspectorVariableGroup(string pName, string pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(Engine.Sim.FindObject<SimObject>(pParent));
        }
        
        public GuiInspectorVariableGroup(string pName, SimObject pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(pParent);
        }
        
        public GuiInspectorVariableGroup(SimObject pObj) 
            : base(pObj) {
        }
        
        public GuiInspectorVariableGroup(IntPtr pObj) 
            : base(pObj) {
        }
        
		protected override void CreateObjectPtr()
		{
			ObjectPtr = InternalUnsafeMethods.Create()(new InternalUnsafeMethods.Create__Args());
		}

        #region UnsafeNativeMethods
        new internal struct InternalUnsafeMethods {
            [StructLayout(LayoutKind.Sequential)]
            internal struct AddInspectorField__Args
            {
                internal IntPtr field;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _AddInspectorField(IntPtr _this, AddInspectorField__Args args);
            private static _AddInspectorField _AddInspectorFieldFunc;
            internal static _AddInspectorField AddInspectorField() {
                if (_AddInspectorFieldFunc == null) {
                    _AddInspectorFieldFunc =
                        (_AddInspectorField)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnGuiInspectorVariableGroup_addInspectorField"), typeof(_AddInspectorField));
                }
                
                return _AddInspectorFieldFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct CreateInspectorField__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate IntPtr _CreateInspectorField(IntPtr _this, CreateInspectorField__Args args);
            private static _CreateInspectorField _CreateInspectorFieldFunc;
            internal static _CreateInspectorField CreateInspectorField() {
                if (_CreateInspectorFieldFunc == null) {
                    _CreateInspectorFieldFunc =
                        (_CreateInspectorField)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnGuiInspectorVariableGroup_createInspectorField"), typeof(_CreateInspectorField));
                }
                
                return _CreateInspectorFieldFunc;
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
                                "fnGuiInspectorVariableGroup_staticGetType"), typeof(_StaticGetType));
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
                                "fnGuiInspectorVariableGroup_create"), typeof(_Create));
                }
                
                return _CreateFunc;
            }
        }
        #endregion

        /// <description>
        /// addInspectorField( GuiInspectorFieldObject )
        /// </description>
        public void AddInspectorField(GuiInspectorField field = null) {
             InternalUnsafeMethods.AddInspectorField__Args _args = new InternalUnsafeMethods.AddInspectorField__Args() {
                field = field.ObjectPtr,
             };
             InternalUnsafeMethods.AddInspectorField()(ObjectPtr, _args);
        }

        /// <description>
        /// createInspectorField()
        /// </description>
        public GuiInspectorField CreateInspectorField() {
             InternalUnsafeMethods.CreateInspectorField__Args _args = new InternalUnsafeMethods.CreateInspectorField__Args() {
             };
             IntPtr _engineResult = InternalUnsafeMethods.CreateInspectorField()(ObjectPtr, _args);
             return new GuiInspectorField(_engineResult);
        }

        /// <description>
        /// Get the type info object for the GuiInspectorVariableGroup class.
        /// </description>
        /// <returns>The type info object for GuiInspectorVariableGroup</returns>
        public static EngineTypeInfo StaticGetType() {
             InternalUnsafeMethods.StaticGetType__Args _args = new InternalUnsafeMethods.StaticGetType__Args() {
             };
             IntPtr _engineResult = InternalUnsafeMethods.StaticGetType()(_args);
             return new EngineTypeInfo(_engineResult);
        }
    }
}