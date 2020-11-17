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
    /// <summary>Inspector Field undo action instance</summary>
    /// <description>
    /// Not intended for game development, for editors or internal use only.
    /// </description>
    public unsafe class InspectorFieldUndoAction : UndoAction {
        public InspectorFieldUndoAction(bool pRegister = false) 
            : base(pRegister) {
        }
        
        public InspectorFieldUndoAction(string pName, bool pRegister) 
            : this(false) {
            Name = pName;
            if (pRegister) {
                RegisterObject();
            }
        }
        
        public InspectorFieldUndoAction(string pName) 
            : this(pName, false) {
        }
        
        public InspectorFieldUndoAction(string pName, string pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(Engine.Sim.FindObject<SimObject>(pParent));
        }
        
        public InspectorFieldUndoAction(string pName, SimObject pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(pParent);
        }
        
        public InspectorFieldUndoAction(SimObject pObj) 
            : base(pObj) {
        }
        
        public InspectorFieldUndoAction(IntPtr pObj) 
            : base(pObj) {
        }
        
		protected override void CreateObjectPtr()
		{
			ObjectPtr = InternalUnsafeMethods.Create()(new InternalUnsafeMethods.Create__Args());
		}

        #region UnsafeNativeMethods
        new internal struct InternalUnsafeMethods {
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
                                "fnInspectorFieldUndoAction_staticGetType"), typeof(_StaticGetType));
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
                                "fnInspectorFieldUndoAction_create"), typeof(_Create));
                }
                
                return _CreateFunc;
            }
        }
        #endregion

        /// <description>
        /// Get the type info object for the InspectorFieldUndoAction class.
        /// </description>
        /// <returns>The type info object for InspectorFieldUndoAction</returns>
        public static EngineTypeInfo StaticGetType() {
             InternalUnsafeMethods.StaticGetType__Args _args = new InternalUnsafeMethods.StaticGetType__Args() {
             };
             IntPtr _engineResult = InternalUnsafeMethods.StaticGetType()(_args);
             return new EngineTypeInfo(_engineResult);
        }


        /// <value>
        /// 
        /// </value>
        public GuiInspector InspectorGui {
            get => GenericMarshal.StringTo<GuiInspector>(GetFieldValue("inspectorGui"));
            set => SetFieldValue("inspectorGui", GenericMarshal.ToString(value));
        }


        /// <value>
        /// 
        /// </value>
        public int ObjectId {
            get => GenericMarshal.StringTo<int>(GetFieldValue("objectId"));
            set => SetFieldValue("objectId", GenericMarshal.ToString(value));
        }


        /// <value>
        /// 
        /// </value>
        public string FieldName {
            get => GenericMarshal.StringTo<string>(GetFieldValue("fieldName"));
            set => SetFieldValue("fieldName", GenericMarshal.ToString(value));
        }


        /// <value>
        /// 
        /// </value>
        public string FieldValue {
            get => GenericMarshal.StringTo<string>(GetFieldValue("fieldValue"));
            set => SetFieldValue("fieldValue", GenericMarshal.ToString(value));
        }


        /// <value>
        /// 
        /// </value>
        public string ArrayIndex {
            get => GenericMarshal.StringTo<string>(GetFieldValue("arrayIndex"));
            set => SetFieldValue("arrayIndex", GenericMarshal.ToString(value));
        }
    }
}