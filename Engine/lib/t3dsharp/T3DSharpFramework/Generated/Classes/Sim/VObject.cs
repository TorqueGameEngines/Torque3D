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
    public unsafe class VObject : SimObject {
        public VObject(bool pRegister = false) 
            : base(pRegister) {
        }
        
        public VObject(string pName, bool pRegister) 
            : this(false) {
            Name = pName;
            if (pRegister) {
                RegisterObject();
            }
        }
        
        public VObject(string pName) 
            : this(pName, false) {
        }
        
        public VObject(string pName, string pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(Engine.Sim.FindObject<SimObject>(pParent));
        }
        
        public VObject(string pName, SimObject pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(pParent);
        }
        
        public VObject(SimObject pObj) 
            : base(pObj) {
        }
        
        public VObject(IntPtr pObj) 
            : base(pObj) {
        }
        
		protected override void CreateObjectPtr()
		{
			ObjectPtr = InternalUnsafeMethods.Create()(new InternalUnsafeMethods.Create__Args());
		}

        #region UnsafeNativeMethods
        new internal struct InternalUnsafeMethods {
            [StructLayout(LayoutKind.Sequential)]
            internal struct SetLabelUnique__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string label;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _SetLabelUnique(IntPtr _this, SetLabelUnique__Args args);
            private static _SetLabelUnique _SetLabelUniqueFunc;
            internal static _SetLabelUnique SetLabelUnique() {
                if (_SetLabelUniqueFunc == null) {
                    _SetLabelUniqueFunc =
                        (_SetLabelUnique)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnVObject_setLabelUnique"), typeof(_SetLabelUnique));
                }
                
                return _SetLabelUniqueFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct RemoveObject__Args
            {
                internal IntPtr simObj;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _RemoveObject(IntPtr _this, RemoveObject__Args args);
            private static _RemoveObject _RemoveObjectFunc;
            internal static _RemoveObject RemoveObject() {
                if (_RemoveObjectFunc == null) {
                    _RemoveObjectFunc =
                        (_RemoveObject)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnVObject_removeObject"), typeof(_RemoveObject));
                }
                
                return _RemoveObjectFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct AddObject__Args
            {
                internal IntPtr simObj;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _AddObject(IntPtr _this, AddObject__Args args);
            private static _AddObject _AddObjectFunc;
            internal static _AddObject AddObject() {
                if (_AddObjectFunc == null) {
                    _AddObjectFunc =
                        (_AddObject)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnVObject_addObject"), typeof(_AddObject));
                }
                
                return _AddObjectFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct Clear__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _Clear(IntPtr _this, Clear__Args args);
            private static _Clear _ClearFunc;
            internal static _Clear Clear() {
                if (_ClearFunc == null) {
                    _ClearFunc =
                        (_Clear)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnVObject_clear"), typeof(_Clear));
                }
                
                return _ClearFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct GetObject__Args
            {
                internal int index;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate int _GetObject(IntPtr _this, GetObject__Args args);
            private static _GetObject _GetObjectFunc;
            internal static _GetObject GetObject() {
                if (_GetObjectFunc == null) {
                    _GetObjectFunc =
                        (_GetObject)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnVObject_getObject"), typeof(_GetObject));
                }
                
                return _GetObjectFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct GetCount__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate int _GetCount(IntPtr _this, GetCount__Args args);
            private static _GetCount _GetCountFunc;
            internal static _GetCount GetCount() {
                if (_GetCountFunc == null) {
                    _GetCountFunc =
                        (_GetCount)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnVObject_getCount"), typeof(_GetCount));
                }
                
                return _GetCountFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct GetIndex__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate int _GetIndex(IntPtr _this, GetIndex__Args args);
            private static _GetIndex _GetIndexFunc;
            internal static _GetIndex GetIndex() {
                if (_GetIndexFunc == null) {
                    _GetIndexFunc =
                        (_GetIndex)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnVObject_getIndex"), typeof(_GetIndex));
                }
                
                return _GetIndexFunc;
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
                                "fnVObject_getParent"), typeof(_GetParent));
                }
                
                return _GetParentFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct GetRoot__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate int _GetRoot(IntPtr _this, GetRoot__Args args);
            private static _GetRoot _GetRootFunc;
            internal static _GetRoot GetRoot() {
                if (_GetRootFunc == null) {
                    _GetRootFunc =
                        (_GetRoot)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnVObject_getRoot"), typeof(_GetRoot));
                }
                
                return _GetRootFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct ReadFile__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string fileName;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            [return: MarshalAs(UnmanagedType.I1)]
            internal delegate bool _ReadFile(IntPtr _this, ReadFile__Args args);
            private static _ReadFile _ReadFileFunc;
            internal static _ReadFile ReadFile() {
                if (_ReadFileFunc == null) {
                    _ReadFileFunc =
                        (_ReadFile)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnVObject_readFile"), typeof(_ReadFile));
                }
                
                return _ReadFileFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct WriteFile__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string fileName;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            [return: MarshalAs(UnmanagedType.I1)]
            internal delegate bool _WriteFile(IntPtr _this, WriteFile__Args args);
            private static _WriteFile _WriteFileFunc;
            internal static _WriteFile WriteFile() {
                if (_WriteFileFunc == null) {
                    _WriteFileFunc =
                        (_WriteFile)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnVObject_writeFile"), typeof(_WriteFile));
                }
                
                return _WriteFileFunc;
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
                                "fnVObject_staticGetType"), typeof(_StaticGetType));
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
                                "fnVObject_create"), typeof(_Create));
                }
                
                return _CreateFunc;
            }
        }
        #endregion

        /// <description>
        /// ( string pLabel ) - Force this label to be unique.
        /// </description>
        /// <param name="pLabel">The name you wish to reference this object by.</param>
        /// <returns>No return value.</returns>
        public void SetLabelUnique(string label = "") {
             InternalUnsafeMethods.SetLabelUnique__Args _args = new InternalUnsafeMethods.SetLabelUnique__Args() {
                label = label,
             };
             InternalUnsafeMethods.SetLabelUnique()(ObjectPtr, _args);
        }

        /// <description>
        /// ( SimObject pObject ) - Remove the target object from this node.
        /// </description>
        /// <param name="pObject">The SimObjectID of the object to be removed from this node.</param>
        /// <returns>No return value.</returns>
        public void RemoveObject(SimObject simObj = null) {
             InternalUnsafeMethods.RemoveObject__Args _args = new InternalUnsafeMethods.RemoveObject__Args() {
                simObj = simObj.ObjectPtr,
             };
             InternalUnsafeMethods.RemoveObject()(ObjectPtr, _args);
        }

        /// <description>
        /// ( SimObject pObject ) - Add a child object to this node.
        /// </description>
        /// <param name="pObject">The SimObjectID of the object to be added to this node.</param>
        /// <returns>No return value.</returns>
        public void AddObject(SimObject simObj = null) {
             InternalUnsafeMethods.AddObject__Args _args = new InternalUnsafeMethods.AddObject__Args() {
                simObj = simObj.ObjectPtr,
             };
             InternalUnsafeMethods.AddObject()(ObjectPtr, _args);
        }

        /// <description>
        /// ( void ) - Detaches and deletes all of the child objects.
        /// </description>
        /// <returns>No return value.</returns>
        public void Clear() {
             InternalUnsafeMethods.Clear__Args _args = new InternalUnsafeMethods.Clear__Args() {
             };
             InternalUnsafeMethods.Clear()(ObjectPtr, _args);
        }

        /// <description>
        /// ( int pIndex ) - Get the object corresponding to the given index.
        /// </description>
        /// <param name="pIndex">The index of the object you wish to retrieve.</param>
        /// <returns>Returns the SimObjectID for the object.</returns>
        public int GetObject(int index = 0) {
             InternalUnsafeMethods.GetObject__Args _args = new InternalUnsafeMethods.GetObject__Args() {
                index = index,
             };
             int _engineResult = InternalUnsafeMethods.GetObject()(ObjectPtr, _args);
             return _engineResult;
        }

        /// <description>
        /// ( void ) - Get the number of child objects.
        /// </description>
        /// <returns>Returns the number of child objects.</returns>
        public int GetCount() {
             InternalUnsafeMethods.GetCount__Args _args = new InternalUnsafeMethods.GetCount__Args() {
             };
             int _engineResult = InternalUnsafeMethods.GetCount()(ObjectPtr, _args);
             return _engineResult;
        }

        /// <description>
        /// ( void ) - Get the index of this object relative to its siblings.
        /// </description>
        /// <returns>Returns the index of this object.</returns>
        public int GetIndex() {
             InternalUnsafeMethods.GetIndex__Args _args = new InternalUnsafeMethods.GetIndex__Args() {
             };
             int _engineResult = InternalUnsafeMethods.GetIndex()(ObjectPtr, _args);
             return _engineResult;
        }

        /// <description>
        /// ( void ) - Get the parent object.
        /// </description>
        /// <returns>Returns the SimObjectId for the parent object.</returns>
        public int GetParent() {
             InternalUnsafeMethods.GetParent__Args _args = new InternalUnsafeMethods.GetParent__Args() {
             };
             int _engineResult = InternalUnsafeMethods.GetParent()(ObjectPtr, _args);
             return _engineResult;
        }

        /// <description>
        /// ( void ) - Get the root object.
        /// </description>
        /// <returns>Returns the SimObjectId for the root object.</returns>
        public int GetRoot() {
             InternalUnsafeMethods.GetRoot__Args _args = new InternalUnsafeMethods.GetRoot__Args() {
             };
             int _engineResult = InternalUnsafeMethods.GetRoot()(ObjectPtr, _args);
             return _engineResult;
        }

        /// <description>
        /// ( string pFileName ) - Clears the object and loads the new data from the given filename.
        /// </description>
        /// <param name="pFileName">The target file to read from.</param>
        /// <returns>Returns true if the read was successful.</returns>
        public bool ReadFile(string fileName = "") {
             InternalUnsafeMethods.ReadFile__Args _args = new InternalUnsafeMethods.ReadFile__Args() {
                fileName = fileName,
             };
             bool _engineResult = InternalUnsafeMethods.ReadFile()(ObjectPtr, _args);
             return _engineResult;
        }

        /// <description>
        /// ( string pFileName ) - Save to a given filename.
        /// </description>
        /// <param name="pFileName">The target file to write to.</param>
        /// <returns>Returns true if the write was successful.</returns>
        public bool WriteFile(string fileName = "") {
             InternalUnsafeMethods.WriteFile__Args _args = new InternalUnsafeMethods.WriteFile__Args() {
                fileName = fileName,
             };
             bool _engineResult = InternalUnsafeMethods.WriteFile()(ObjectPtr, _args);
             return _engineResult;
        }

        /// <description>
        /// Get the type info object for the VObject class.
        /// </description>
        /// <returns>The type info object for VObject</returns>
        public static EngineTypeInfo StaticGetType() {
             InternalUnsafeMethods.StaticGetType__Args _args = new InternalUnsafeMethods.StaticGetType__Args() {
             };
             IntPtr _engineResult = InternalUnsafeMethods.StaticGetType()(_args);
             return new EngineTypeInfo(_engineResult);
        }


        /// <value>
        /// <description>
        /// Enable or Disable the object from playback.
        /// </description>
        /// </value>
        public bool Enabled {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("Enabled"));
            set => SetFieldValue("Enabled", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// The label this object is referenced by.
        /// </description>
        /// </value>
        public string Label {
            get => GenericMarshal.StringTo<string>(GetFieldValue("Label"));
            set => SetFieldValue("Label", GenericMarshal.ToString(value));
        }
    }
}