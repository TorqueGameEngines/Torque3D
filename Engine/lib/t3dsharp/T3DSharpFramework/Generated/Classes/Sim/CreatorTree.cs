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
    /// <summary>Creator tree from old editor.  Not used in current editor.</summary>
    /// <description>
    /// 
    /// </description>
    public unsafe class CreatorTree : GuiArrayCtrl {
        public CreatorTree(bool pRegister = false) 
            : base(pRegister) {
        }
        
        public CreatorTree(string pName, bool pRegister) 
            : this(false) {
            Name = pName;
            if (pRegister) {
                RegisterObject();
            }
        }
        
        public CreatorTree(string pName) 
            : this(pName, false) {
        }
        
        public CreatorTree(string pName, string pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(Engine.Sim.FindObject<SimObject>(pParent));
        }
        
        public CreatorTree(string pName, SimObject pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(pParent);
        }
        
        public CreatorTree(SimObject pObj) 
            : base(pObj) {
        }
        
        public CreatorTree(IntPtr pObj) 
            : base(pObj) {
        }
        
		protected override void CreateObjectPtr()
		{
			ObjectPtr = InternalUnsafeMethods.Create()(new InternalUnsafeMethods.Create__Args());
		}

        #region UnsafeNativeMethods
        new internal struct InternalUnsafeMethods {
            [StructLayout(LayoutKind.Sequential)]
            internal struct GetParent__Args
            {
                internal int nodeValue;
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
                                "fnCreatorTree_getParent"), typeof(_GetParent));
                }
                
                return _GetParentFunc;
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
                                "fnCreatorTree_clear"), typeof(_Clear));
                }
                
                return _ClearFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct GetValue__Args
            {
                internal int nodeValue;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            
            internal delegate IntPtr _GetValue(IntPtr _this, GetValue__Args args);
            private static _GetValue _GetValueFunc;
            internal static _GetValue GetValue() {
                if (_GetValueFunc == null) {
                    _GetValueFunc =
                        (_GetValue)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnCreatorTree_getValue"), typeof(_GetValue));
                }
                
                return _GetValueFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct GetName__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string item;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            
            internal delegate IntPtr _GetName(IntPtr _this, GetName__Args args);
            private static _GetName _GetNameFunc;
            internal static _GetName GetName() {
                if (_GetNameFunc == null) {
                    _GetNameFunc =
                        (_GetName)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnCreatorTree_getName"), typeof(_GetName));
                }
                
                return _GetNameFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct IsGroup__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string group;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            [return: MarshalAs(UnmanagedType.I1)]
            internal delegate bool _IsGroup(IntPtr _this, IsGroup__Args args);
            private static _IsGroup _IsGroupFunc;
            internal static _IsGroup IsGroup() {
                if (_IsGroupFunc == null) {
                    _IsGroupFunc =
                        (_IsGroup)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnCreatorTree_isGroup"), typeof(_IsGroup));
                }
                
                return _IsGroupFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct GetSelected__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate int _GetSelected(IntPtr _this, GetSelected__Args args);
            private static _GetSelected _GetSelectedFunc;
            internal static _GetSelected GetSelected() {
                if (_GetSelectedFunc == null) {
                    _GetSelectedFunc =
                        (_GetSelected)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnCreatorTree_getSelected"), typeof(_GetSelected));
                }
                
                return _GetSelectedFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct FileNameMatch__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string world;
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string type;
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string filename;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            [return: MarshalAs(UnmanagedType.I1)]
            internal delegate bool _FileNameMatch(IntPtr _this, FileNameMatch__Args args);
            private static _FileNameMatch _FileNameMatchFunc;
            internal static _FileNameMatch FileNameMatch() {
                if (_FileNameMatchFunc == null) {
                    _FileNameMatchFunc =
                        (_FileNameMatch)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnCreatorTree_fileNameMatch"), typeof(_FileNameMatch));
                }
                
                return _FileNameMatchFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct AddItem__Args
            {
                internal int group;
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string name;
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string value;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate int _AddItem(IntPtr _this, AddItem__Args args);
            private static _AddItem _AddItemFunc;
            internal static _AddItem AddItem() {
                if (_AddItemFunc == null) {
                    _AddItemFunc =
                        (_AddItem)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnCreatorTree_addItem"), typeof(_AddItem));
                }
                
                return _AddItemFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct AddGroup__Args
            {
                internal int group;
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string name;
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string value;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate int _AddGroup(IntPtr _this, AddGroup__Args args);
            private static _AddGroup _AddGroupFunc;
            internal static _AddGroup AddGroup() {
                if (_AddGroupFunc == null) {
                    _AddGroupFunc =
                        (_AddGroup)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnCreatorTree_addGroup"), typeof(_AddGroup));
                }
                
                return _AddGroupFunc;
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
                                "fnCreatorTree_staticGetType"), typeof(_StaticGetType));
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
                                "fnCreatorTree_create"), typeof(_Create));
                }
                
                return _CreateFunc;
            }
        }
        #endregion

        /// <description>
        /// (Node n)
        /// </description>
        public int GetParent(int nodeValue) {
             InternalUnsafeMethods.GetParent__Args _args = new InternalUnsafeMethods.GetParent__Args() {
                nodeValue = nodeValue,
             };
             int _engineResult = InternalUnsafeMethods.GetParent()(ObjectPtr, _args);
             return _engineResult;
        }

        /// <description>
        /// Clear the tree.
        /// </description>
        public void Clear() {
             InternalUnsafeMethods.Clear__Args _args = new InternalUnsafeMethods.Clear__Args() {
             };
             InternalUnsafeMethods.Clear()(ObjectPtr, _args);
        }

        /// <description>
        /// (Node n)
        /// </description>
        public string GetValue(int nodeValue) {
             InternalUnsafeMethods.GetValue__Args _args = new InternalUnsafeMethods.GetValue__Args() {
                nodeValue = nodeValue,
             };
             IntPtr _engineResult = InternalUnsafeMethods.GetValue()(ObjectPtr, _args);
             return StringMarshal.IntPtrToUtf8String(_engineResult);
        }

        /// <description>
        /// (Node item)
        /// </description>
        public string GetName(string item) {
             InternalUnsafeMethods.GetName__Args _args = new InternalUnsafeMethods.GetName__Args() {
                item = item,
             };
             IntPtr _engineResult = InternalUnsafeMethods.GetName()(ObjectPtr, _args);
             return StringMarshal.IntPtrToUtf8String(_engineResult);
        }

        /// <description>
        /// (Group g)
        /// </description>
        public bool IsGroup(string group) {
             InternalUnsafeMethods.IsGroup__Args _args = new InternalUnsafeMethods.IsGroup__Args() {
                group = group,
             };
             bool _engineResult = InternalUnsafeMethods.IsGroup()(ObjectPtr, _args);
             return _engineResult;
        }

        /// <description>
        /// Return a handle to the currently selected item.
        /// </description>
        public int GetSelected() {
             InternalUnsafeMethods.GetSelected__Args _args = new InternalUnsafeMethods.GetSelected__Args() {
             };
             int _engineResult = InternalUnsafeMethods.GetSelected()(ObjectPtr, _args);
             return _engineResult;
        }

        /// <description>
        /// (string world, string type, string filename)
        /// </description>
        public bool FileNameMatch(string world, string type, string filename) {
             InternalUnsafeMethods.FileNameMatch__Args _args = new InternalUnsafeMethods.FileNameMatch__Args() {
                world = world,
                type = type,
                filename = filename,
             };
             bool _engineResult = InternalUnsafeMethods.FileNameMatch()(ObjectPtr, _args);
             return _engineResult;
        }

        /// <description>
        /// (Node group, string name, string value)
        /// </description>
        public int AddItem(int group, string name, string value) {
             InternalUnsafeMethods.AddItem__Args _args = new InternalUnsafeMethods.AddItem__Args() {
                group = group,
                name = name,
                value = value,
             };
             int _engineResult = InternalUnsafeMethods.AddItem()(ObjectPtr, _args);
             return _engineResult;
        }

        /// <description>
        /// (string group, string name, string value)
        /// </description>
        public int AddGroup(int group, string name, string value) {
             InternalUnsafeMethods.AddGroup__Args _args = new InternalUnsafeMethods.AddGroup__Args() {
                group = group,
                name = name,
                value = value,
             };
             int _engineResult = InternalUnsafeMethods.AddGroup()(ObjectPtr, _args);
             return _engineResult;
        }

        /// <description>
        /// Get the type info object for the CreatorTree class.
        /// </description>
        /// <returns>The type info object for CreatorTree</returns>
        public static EngineTypeInfo StaticGetType() {
             InternalUnsafeMethods.StaticGetType__Args _args = new InternalUnsafeMethods.StaticGetType__Args() {
             };
             IntPtr _engineResult = InternalUnsafeMethods.StaticGetType()(_args);
             return new EngineTypeInfo(_engineResult);
        }
    }
}