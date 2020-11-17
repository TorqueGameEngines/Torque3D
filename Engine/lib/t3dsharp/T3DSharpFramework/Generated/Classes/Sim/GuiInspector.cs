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
    /// <summary>A control that allows to edit the properties of one or more SimObjects.</summary>
    /// <description>
    /// Editor use only.
    /// </description>
    public unsafe class GuiInspector : GuiStackControl {
        public GuiInspector(bool pRegister = false) 
            : base(pRegister) {
        }
        
        public GuiInspector(string pName, bool pRegister) 
            : this(false) {
            Name = pName;
            if (pRegister) {
                RegisterObject();
            }
        }
        
        public GuiInspector(string pName) 
            : this(pName, false) {
        }
        
        public GuiInspector(string pName, string pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(Engine.Sim.FindObject<SimObject>(pParent));
        }
        
        public GuiInspector(string pName, SimObject pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(pParent);
        }
        
        public GuiInspector(SimObject pObj) 
            : base(pObj) {
        }
        
        public GuiInspector(IntPtr pObj) 
            : base(pObj) {
        }
        
		protected override void CreateObjectPtr()
		{
			ObjectPtr = InternalUnsafeMethods.Create()(new InternalUnsafeMethods.Create__Args());
		}

        #region UnsafeNativeMethods
        new internal struct InternalUnsafeMethods {
            [StructLayout(LayoutKind.Sequential)]
            internal struct FindByObject__Args
            {
                internal IntPtr obj;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate int _FindByObject(IntPtr _this, FindByObject__Args args);
            private static _FindByObject _FindByObjectFunc;
            internal static _FindByObject FindByObject() {
                if (_FindByObjectFunc == null) {
                    _FindByObjectFunc =
                        (_FindByObject)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnGuiInspector_findByObject"), typeof(_FindByObject));
                }
                
                return _FindByObjectFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct SetObjectField__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string fieldname;
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string data;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _SetObjectField(IntPtr _this, SetObjectField__Args args);
            private static _SetObjectField _SetObjectFieldFunc;
            internal static _SetObjectField SetObjectField() {
                if (_SetObjectFieldFunc == null) {
                    _SetObjectFieldFunc =
                        (_SetObjectField)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnGuiInspector_setObjectField"), typeof(_SetObjectField));
                }
                
                return _SetObjectFieldFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct Apply__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _Apply(IntPtr _this, Apply__Args args);
            private static _Apply _ApplyFunc;
            internal static _Apply Apply() {
                if (_ApplyFunc == null) {
                    _ApplyFunc =
                        (_Apply)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnGuiInspector_apply"), typeof(_Apply));
                }
                
                return _ApplyFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct SetName__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string newObjectName;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _SetName(IntPtr _this, SetName__Args args);
            private static _SetName _SetNameFunc;
            internal static _SetName SetName() {
                if (_SetNameFunc == null) {
                    _SetNameFunc =
                        (_SetName)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnGuiInspector_setName"), typeof(_SetName));
                }
                
                return _SetNameFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct GetNumInspectObjects__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate int _GetNumInspectObjects(IntPtr _this, GetNumInspectObjects__Args args);
            private static _GetNumInspectObjects _GetNumInspectObjectsFunc;
            internal static _GetNumInspectObjects GetNumInspectObjects() {
                if (_GetNumInspectObjectsFunc == null) {
                    _GetNumInspectObjectsFunc =
                        (_GetNumInspectObjects)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnGuiInspector_getNumInspectObjects"), typeof(_GetNumInspectObjects));
                }
                
                return _GetNumInspectObjectsFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct GetInspectObject__Args
            {
                internal int index;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            
            internal delegate IntPtr _GetInspectObject(IntPtr _this, GetInspectObject__Args args);
            private static _GetInspectObject _GetInspectObjectFunc;
            internal static _GetInspectObject GetInspectObject() {
                if (_GetInspectObjectFunc == null) {
                    _GetInspectObjectFunc =
                        (_GetInspectObject)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnGuiInspector_getInspectObject"), typeof(_GetInspectObject));
                }
                
                return _GetInspectObjectFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct Refresh__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _Refresh(IntPtr _this, Refresh__Args args);
            private static _Refresh _RefreshFunc;
            internal static _Refresh Refresh() {
                if (_RefreshFunc == null) {
                    _RefreshFunc =
                        (_Refresh)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnGuiInspector_refresh"), typeof(_Refresh));
                }
                
                return _RefreshFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct RemoveInspect__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string simObject;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _RemoveInspect(IntPtr _this, RemoveInspect__Args args);
            private static _RemoveInspect _RemoveInspectFunc;
            internal static _RemoveInspect RemoveInspect() {
                if (_RemoveInspectFunc == null) {
                    _RemoveInspectFunc =
                        (_RemoveInspect)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnGuiInspector_removeInspect"), typeof(_RemoveInspect));
                }
                
                return _RemoveInspectFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct AddInspect__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string simObject;
                [MarshalAs(UnmanagedType.I1)]
                internal bool autoSync;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _AddInspect(IntPtr _this, AddInspect__Args args);
            private static _AddInspect _AddInspectFunc;
            internal static _AddInspect AddInspect() {
                if (_AddInspectFunc == null) {
                    _AddInspectFunc =
                        (_AddInspect)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnGuiInspector_addInspect"), typeof(_AddInspect));
                }
                
                return _AddInspectFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct Inspect__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string simObject;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _Inspect(IntPtr _this, Inspect__Args args);
            private static _Inspect _InspectFunc;
            internal static _Inspect Inspect() {
                if (_InspectFunc == null) {
                    _InspectFunc =
                        (_Inspect)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnGuiInspector_inspect"), typeof(_Inspect));
                }
                
                return _InspectFunc;
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
                                "fnGuiInspector_staticGetType"), typeof(_StaticGetType));
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
                                "fnGuiInspector_create"), typeof(_Create));
                }
                
                return _CreateFunc;
            }
        }
        #endregion

        /// <description>
        /// Returns the id of an awake inspector that is inspecting the passed object if one exists
        /// </description>
        /// <param name="object">Object to find away inspector for.</param>
        /// <returns>id of an awake inspector that is inspecting the passed object if one exists, else NULL or 0.</returns>
        public int FindByObject(SimObject obj) {
             InternalUnsafeMethods.FindByObject__Args _args = new InternalUnsafeMethods.FindByObject__Args() {
                obj = obj.ObjectPtr,
             };
             int _engineResult = InternalUnsafeMethods.FindByObject()(ObjectPtr, _args);
             return _engineResult;
        }

        /// <description>
        /// Set a named fields value on the inspected object if it exists. This triggers all the usual callbacks that would occur if the field had been changed through the gui..
        /// </description>
        /// <param name="fieldname">Field name on object we are inspecting we want to change.</param>
        /// <param name="data">New Value for the given field.</param>
        public void SetObjectField(string fieldname, string data) {
             InternalUnsafeMethods.SetObjectField__Args _args = new InternalUnsafeMethods.SetObjectField__Args() {
                fieldname = fieldname,
                data = data,
             };
             InternalUnsafeMethods.SetObjectField()(ObjectPtr, _args);
        }

        /// <description>
        /// Force application of inspected object's attributes.
        /// </description>
        public void Apply() {
             InternalUnsafeMethods.Apply__Args _args = new InternalUnsafeMethods.Apply__Args() {
             };
             InternalUnsafeMethods.Apply()(ObjectPtr, _args);
        }

        /// <description>
        /// Rename the object being inspected (first object in inspect list).
        /// </description>
        /// <param name="newObjectName">new name for object being inspected.</param>
        public void SetName(string newObjectName) {
             InternalUnsafeMethods.SetName__Args _args = new InternalUnsafeMethods.SetName__Args() {
                newObjectName = newObjectName,
             };
             InternalUnsafeMethods.SetName()(ObjectPtr, _args);
        }

        /// <description>
        /// Return the number of objects currently being inspected.
        /// </description>
        /// <returns>number of objects currently being inspected.</returns>
        public int GetNumInspectObjects() {
             InternalUnsafeMethods.GetNumInspectObjects__Args _args = new InternalUnsafeMethods.GetNumInspectObjects__Args() {
             };
             int _engineResult = InternalUnsafeMethods.GetNumInspectObjects()(ObjectPtr, _args);
             return _engineResult;
        }

        /// <description>
        /// Returns currently inspected object.
        /// </description>
        /// <param name="index">Index of object in inspection list you want to get.</param>
        /// <returns>object being inspected.</returns>
        public string GetInspectObject(int index = 0) {
             InternalUnsafeMethods.GetInspectObject__Args _args = new InternalUnsafeMethods.GetInspectObject__Args() {
                index = index,
             };
             IntPtr _engineResult = InternalUnsafeMethods.GetInspectObject()(ObjectPtr, _args);
             return StringMarshal.IntPtrToUtf8String(_engineResult);
        }

        /// <description>
        /// Re-inspect the currently selected object.
        /// </description>
        public void Refresh() {
             InternalUnsafeMethods.Refresh__Args _args = new InternalUnsafeMethods.Refresh__Args() {
             };
             InternalUnsafeMethods.Refresh()(ObjectPtr, _args);
        }

        /// <description>
        /// Remove the object from the list of objects being inspected.
        /// </description>
        /// <param name="simObject">Object to remove from the inspection.</param>
        public void RemoveInspect(string simObject) {
             InternalUnsafeMethods.RemoveInspect__Args _args = new InternalUnsafeMethods.RemoveInspect__Args() {
                simObject = simObject,
             };
             InternalUnsafeMethods.RemoveInspect()(ObjectPtr, _args);
        }

        /// <description>
        /// Add the object to the list of objects being inspected.
        /// </description>
        /// <param name="simObject">Object to add to the inspection.</param>
        /// <param name="autoSync">Auto sync the values when they change.</param>
        public void AddInspect(string simObject, bool autoSync = true) {
             InternalUnsafeMethods.AddInspect__Args _args = new InternalUnsafeMethods.AddInspect__Args() {
                simObject = simObject,
                autoSync = autoSync,
             };
             InternalUnsafeMethods.AddInspect()(ObjectPtr, _args);
        }

        /// <description>
        /// Inspect the given object.
        /// </description>
        /// <param name="simObject">Object to inspect.</param>
        public void Inspect(string simObject = "") {
             InternalUnsafeMethods.Inspect__Args _args = new InternalUnsafeMethods.Inspect__Args() {
                simObject = simObject,
             };
             InternalUnsafeMethods.Inspect()(ObjectPtr, _args);
        }

        /// <description>
        /// Get the type info object for the GuiInspector class.
        /// </description>
        /// <returns>The type info object for GuiInspector</returns>
        public static EngineTypeInfo StaticGetType() {
             InternalUnsafeMethods.StaticGetType__Args _args = new InternalUnsafeMethods.StaticGetType__Args() {
             };
             IntPtr _engineResult = InternalUnsafeMethods.StaticGetType()(_args);
             return new EngineTypeInfo(_engineResult);
        }


        /// <value>
        /// 
        /// </value>
        public int DividerMargin {
            get => GenericMarshal.StringTo<int>(GetFieldValue("dividerMargin"));
            set => SetFieldValue("dividerMargin", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Specify groups that should be shown or not. Specifying 'shown' implicitly does 'not show' all other groups. Example string: +name -otherName
        /// </description>
        /// </value>
        public string GroupFilters {
            get => GenericMarshal.StringTo<string>(GetFieldValue("groupFilters"));
            set => SetFieldValue("groupFilters", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// If false the custom fields Name, Id, and Source Class will not be shown.
        /// </description>
        /// </value>
        public bool ShowCustomFields {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("showCustomFields"));
            set => SetFieldValue("showCustomFields", GenericMarshal.ToString(value));
        }
    }
}