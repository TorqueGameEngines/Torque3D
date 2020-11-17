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
    /// <summary>A control that allows to select a value from a drop-down list.</summary>
    /// <description>
    /// For a nearly identical GUI with additional features, use GuiPopUpMenuCtrlEx.
    /// </description>
    /// <code>
    /// new GuiPopUpMenuCtrl()
    /// {
    ///   maxPopupHeight = "200";
    ///   sbUsesNAColor = "0";
    ///   reverseTextList = "0";
    ///   bitmapBounds = "16 16";
    ///   maxLength = "1024";
    ///   position = "56 31";
    ///   extent = "64 64";
    ///   minExtent = "8 2";
    ///   profile = "GuiPopUpMenuProfile";
    ///   tooltipProfile = "GuiToolTipProfile";
    /// };
    /// </code>
    /// <remarks> This is definitely going to be deprecated soon.
    /// 
    /// </remarks>
    /// <see cref="GuiPopUpMenuCtrlEx for more features and better explanations." />
    public unsafe class GuiPopUpMenuCtrl : GuiTextCtrl {
        public GuiPopUpMenuCtrl(bool pRegister = false) 
            : base(pRegister) {
        }
        
        public GuiPopUpMenuCtrl(string pName, bool pRegister) 
            : this(false) {
            Name = pName;
            if (pRegister) {
                RegisterObject();
            }
        }
        
        public GuiPopUpMenuCtrl(string pName) 
            : this(pName, false) {
        }
        
        public GuiPopUpMenuCtrl(string pName, string pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(Engine.Sim.FindObject<SimObject>(pParent));
        }
        
        public GuiPopUpMenuCtrl(string pName, SimObject pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(pParent);
        }
        
        public GuiPopUpMenuCtrl(SimObject pObj) 
            : base(pObj) {
        }
        
        public GuiPopUpMenuCtrl(IntPtr pObj) 
            : base(pObj) {
        }
        
		protected override void CreateObjectPtr()
		{
			ObjectPtr = InternalUnsafeMethods.Create()(new InternalUnsafeMethods.Create__Args());
		}

        #region UnsafeNativeMethods
        new internal struct InternalUnsafeMethods {
            [StructLayout(LayoutKind.Sequential)]
            internal struct ClearEntry__Args
            {
                internal int entry;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _ClearEntry(IntPtr _this, ClearEntry__Args args);
            private static _ClearEntry _ClearEntryFunc;
            internal static _ClearEntry ClearEntry() {
                if (_ClearEntryFunc == null) {
                    _ClearEntryFunc =
                        (_ClearEntry)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnGuiPopUpMenuCtrl_clearEntry"), typeof(_ClearEntry));
                }
                
                return _ClearEntryFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct ReplaceText__Args
            {
                [MarshalAs(UnmanagedType.I1)]
                internal bool doReplaceText;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _ReplaceText(IntPtr _this, ReplaceText__Args args);
            private static _ReplaceText _ReplaceTextFunc;
            internal static _ReplaceText ReplaceText() {
                if (_ReplaceTextFunc == null) {
                    _ReplaceTextFunc =
                        (_ReplaceText)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnGuiPopUpMenuCtrl_replaceText"), typeof(_ReplaceText));
                }
                
                return _ReplaceTextFunc;
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
                                "fnGuiPopUpMenuCtrl_size"), typeof(_Size));
                }
                
                return _SizeFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct FindText__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string text;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate int _FindText(IntPtr _this, FindText__Args args);
            private static _FindText _FindTextFunc;
            internal static _FindText FindText() {
                if (_FindTextFunc == null) {
                    _FindTextFunc =
                        (_FindText)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnGuiPopUpMenuCtrl_findText"), typeof(_FindText));
                }
                
                return _FindTextFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct SetEnumContent__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string className;
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string enumName;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _SetEnumContent(IntPtr _this, SetEnumContent__Args args);
            private static _SetEnumContent _SetEnumContentFunc;
            internal static _SetEnumContent SetEnumContent() {
                if (_SetEnumContentFunc == null) {
                    _SetEnumContentFunc =
                        (_SetEnumContent)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnGuiPopUpMenuCtrl_setEnumContent"), typeof(_SetEnumContent));
                }
                
                return _SetEnumContentFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct ChangeTextById__Args
            {
                internal int id;
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string text;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _ChangeTextById(IntPtr _this, ChangeTextById__Args args);
            private static _ChangeTextById _ChangeTextByIdFunc;
            internal static _ChangeTextById ChangeTextById() {
                if (_ChangeTextByIdFunc == null) {
                    _ChangeTextByIdFunc =
                        (_ChangeTextById)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnGuiPopUpMenuCtrl_changeTextById"), typeof(_ChangeTextById));
                }
                
                return _ChangeTextByIdFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct GetTextById__Args
            {
                internal int id;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            
            internal delegate IntPtr _GetTextById(IntPtr _this, GetTextById__Args args);
            private static _GetTextById _GetTextByIdFunc;
            internal static _GetTextById GetTextById() {
                if (_GetTextByIdFunc == null) {
                    _GetTextByIdFunc =
                        (_GetTextById)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnGuiPopUpMenuCtrl_getTextById"), typeof(_GetTextById));
                }
                
                return _GetTextByIdFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct SetNoneSelected__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _SetNoneSelected(IntPtr _this, SetNoneSelected__Args args);
            private static _SetNoneSelected _SetNoneSelectedFunc;
            internal static _SetNoneSelected SetNoneSelected() {
                if (_SetNoneSelectedFunc == null) {
                    _SetNoneSelectedFunc =
                        (_SetNoneSelected)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnGuiPopUpMenuCtrl_setNoneSelected"), typeof(_SetNoneSelected));
                }
                
                return _SetNoneSelectedFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct SetFirstSelected__Args
            {
                [MarshalAs(UnmanagedType.I1)]
                internal bool scriptCallback;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _SetFirstSelected(IntPtr _this, SetFirstSelected__Args args);
            private static _SetFirstSelected _SetFirstSelectedFunc;
            internal static _SetFirstSelected SetFirstSelected() {
                if (_SetFirstSelectedFunc == null) {
                    _SetFirstSelectedFunc =
                        (_SetFirstSelected)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnGuiPopUpMenuCtrl_setFirstSelected"), typeof(_SetFirstSelected));
                }
                
                return _SetFirstSelectedFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct SetSelected__Args
            {
                internal int id;
                [MarshalAs(UnmanagedType.I1)]
                internal bool scriptCallback;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _SetSelected(IntPtr _this, SetSelected__Args args);
            private static _SetSelected _SetSelectedFunc;
            internal static _SetSelected SetSelected() {
                if (_SetSelectedFunc == null) {
                    _SetSelectedFunc =
                        (_SetSelected)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnGuiPopUpMenuCtrl_setSelected"), typeof(_SetSelected));
                }
                
                return _SetSelectedFunc;
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
                                "fnGuiPopUpMenuCtrl_getSelected"), typeof(_GetSelected));
                }
                
                return _GetSelectedFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct ForceClose__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _ForceClose(IntPtr _this, ForceClose__Args args);
            private static _ForceClose _ForceCloseFunc;
            internal static _ForceClose ForceClose() {
                if (_ForceCloseFunc == null) {
                    _ForceCloseFunc =
                        (_ForceClose)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnGuiPopUpMenuCtrl_forceClose"), typeof(_ForceClose));
                }
                
                return _ForceCloseFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct ForceOnAction__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _ForceOnAction(IntPtr _this, ForceOnAction__Args args);
            private static _ForceOnAction _ForceOnActionFunc;
            internal static _ForceOnAction ForceOnAction() {
                if (_ForceOnActionFunc == null) {
                    _ForceOnActionFunc =
                        (_ForceOnAction)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnGuiPopUpMenuCtrl_forceOnAction"), typeof(_ForceOnAction));
                }
                
                return _ForceOnActionFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct SortID__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _SortID(IntPtr _this, SortID__Args args);
            private static _SortID _SortIDFunc;
            internal static _SortID SortID() {
                if (_SortIDFunc == null) {
                    _SortIDFunc =
                        (_SortID)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnGuiPopUpMenuCtrl_sortID"), typeof(_SortID));
                }
                
                return _SortIDFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct Sort__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _Sort(IntPtr _this, Sort__Args args);
            private static _Sort _SortFunc;
            internal static _Sort Sort() {
                if (_SortFunc == null) {
                    _SortFunc =
                        (_Sort)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnGuiPopUpMenuCtrl_sort"), typeof(_Sort));
                }
                
                return _SortFunc;
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
                                "fnGuiPopUpMenuCtrl_clear"), typeof(_Clear));
                }
                
                return _ClearFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct GetText__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            
            internal delegate IntPtr _GetText(IntPtr _this, GetText__Args args);
            private static _GetText _GetTextFunc;
            internal static _GetText GetText() {
                if (_GetTextFunc == null) {
                    _GetTextFunc =
                        (_GetText)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnGuiPopUpMenuCtrl_getText"), typeof(_GetText));
                }
                
                return _GetTextFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct AddScheme__Args
            {
                internal uint id;
                internal IntPtr fontColor;
                internal IntPtr fontColorHL;
                internal IntPtr fontColorSEL;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _AddScheme(IntPtr _this, AddScheme__Args args);
            private static _AddScheme _AddSchemeFunc;
            internal static _AddScheme AddScheme() {
                if (_AddSchemeFunc == null) {
                    _AddSchemeFunc =
                        (_AddScheme)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnGuiPopUpMenuCtrl_addScheme"), typeof(_AddScheme));
                }
                
                return _AddSchemeFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct Add__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string name;
                internal int idNum;
                internal uint scheme;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _Add(IntPtr _this, Add__Args args);
            private static _Add _AddFunc;
            internal static _Add Add() {
                if (_AddFunc == null) {
                    _AddFunc =
                        (_Add)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnGuiPopUpMenuCtrl_add"), typeof(_Add));
                }
                
                return _AddFunc;
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
                                "fnGuiPopUpMenuCtrl_staticGetType"), typeof(_StaticGetType));
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
                                "fnGuiPopUpMenuCtrl_create"), typeof(_Create));
                }
                
                return _CreateFunc;
            }
        }
        #endregion

        /// <description>
        /// (S32 entry)
        /// </description>
        public void ClearEntry(int entry) {
             InternalUnsafeMethods.ClearEntry__Args _args = new InternalUnsafeMethods.ClearEntry__Args() {
                entry = entry,
             };
             InternalUnsafeMethods.ClearEntry()(ObjectPtr, _args);
        }

        /// <description>
        /// (bool doReplaceText)
        /// </description>
        public void ReplaceText(bool doReplaceText) {
             InternalUnsafeMethods.ReplaceText__Args _args = new InternalUnsafeMethods.ReplaceText__Args() {
                doReplaceText = doReplaceText,
             };
             InternalUnsafeMethods.ReplaceText()(ObjectPtr, _args);
        }

        /// <description>
        /// Get the size of the menu - the number of entries in it.
        /// </description>
        public int Size() {
             InternalUnsafeMethods.Size__Args _args = new InternalUnsafeMethods.Size__Args() {
             };
             int _engineResult = InternalUnsafeMethods.Size()(ObjectPtr, _args);
             return _engineResult;
        }

        /// <description>
        /// (string text)Returns the position of the first entry containing the specified text or -1 if not found.
        /// </description>
        public int FindText(string text) {
             InternalUnsafeMethods.FindText__Args _args = new InternalUnsafeMethods.FindText__Args() {
                text = text,
             };
             int _engineResult = InternalUnsafeMethods.FindText()(ObjectPtr, _args);
             return _engineResult;
        }

        /// <description>
        /// (string class, string enum)This fills the popup with a classrep's field enumeration type info.
        /// 
        /// More of a helper function than anything.   If console access to the field list is added, at least for the enumerated types, then this should go away..
        /// </description>
        public void SetEnumContent(string className, string enumName) {
             InternalUnsafeMethods.SetEnumContent__Args _args = new InternalUnsafeMethods.SetEnumContent__Args() {
                className = className,
                enumName = enumName,
             };
             InternalUnsafeMethods.SetEnumContent()(ObjectPtr, _args);
        }

        /// <description>
        /// ( int id, string text )
        /// </description>
        public void ChangeTextById(int id, string text) {
             InternalUnsafeMethods.ChangeTextById__Args _args = new InternalUnsafeMethods.ChangeTextById__Args() {
                id = id,
                text = text,
             };
             InternalUnsafeMethods.ChangeTextById()(ObjectPtr, _args);
        }

        /// <description>
        /// (int id)
        /// </description>
        public string GetTextById(int id) {
             InternalUnsafeMethods.GetTextById__Args _args = new InternalUnsafeMethods.GetTextById__Args() {
                id = id,
             };
             IntPtr _engineResult = InternalUnsafeMethods.GetTextById()(ObjectPtr, _args);
             return StringMarshal.IntPtrToUtf8String(_engineResult);
        }

        /// 
        public void SetNoneSelected() {
             InternalUnsafeMethods.SetNoneSelected__Args _args = new InternalUnsafeMethods.SetNoneSelected__Args() {
             };
             InternalUnsafeMethods.SetNoneSelected()(ObjectPtr, _args);
        }

        /// <description>
        /// ([scriptCallback=true])
        /// </description>
        public void SetFirstSelected(bool scriptCallback = true) {
             InternalUnsafeMethods.SetFirstSelected__Args _args = new InternalUnsafeMethods.SetFirstSelected__Args() {
                scriptCallback = scriptCallback,
             };
             InternalUnsafeMethods.SetFirstSelected()(ObjectPtr, _args);
        }

        /// <description>
        /// (int id, [scriptCallback=true])
        /// </description>
        public void SetSelected(int id, bool scriptCallback = true) {
             InternalUnsafeMethods.SetSelected__Args _args = new InternalUnsafeMethods.SetSelected__Args() {
                id = id,
                scriptCallback = scriptCallback,
             };
             InternalUnsafeMethods.SetSelected()(ObjectPtr, _args);
        }

        /// <description>
        /// Gets the selected index
        /// </description>
        public int GetSelected() {
             InternalUnsafeMethods.GetSelected__Args _args = new InternalUnsafeMethods.GetSelected__Args() {
             };
             int _engineResult = InternalUnsafeMethods.GetSelected()(ObjectPtr, _args);
             return _engineResult;
        }

        /// 
        public void ForceClose() {
             InternalUnsafeMethods.ForceClose__Args _args = new InternalUnsafeMethods.ForceClose__Args() {
             };
             InternalUnsafeMethods.ForceClose()(ObjectPtr, _args);
        }

        /// 
        public void ForceOnAction() {
             InternalUnsafeMethods.ForceOnAction__Args _args = new InternalUnsafeMethods.ForceOnAction__Args() {
             };
             InternalUnsafeMethods.ForceOnAction()(ObjectPtr, _args);
        }

        /// <description>
        /// Sort the list by ID.
        /// </description>
        public void SortID() {
             InternalUnsafeMethods.SortID__Args _args = new InternalUnsafeMethods.SortID__Args() {
             };
             InternalUnsafeMethods.SortID()(ObjectPtr, _args);
        }

        /// <description>
        /// Sort the list alphabetically.
        /// </description>
        public void Sort() {
             InternalUnsafeMethods.Sort__Args _args = new InternalUnsafeMethods.Sort__Args() {
             };
             InternalUnsafeMethods.Sort()(ObjectPtr, _args);
        }

        /// <description>
        /// Clear the popup list.
        /// </description>
        public void Clear() {
             InternalUnsafeMethods.Clear__Args _args = new InternalUnsafeMethods.Clear__Args() {
             };
             InternalUnsafeMethods.Clear()(ObjectPtr, _args);
        }

        /// 
        public string GetText() {
             InternalUnsafeMethods.GetText__Args _args = new InternalUnsafeMethods.GetText__Args() {
             };
             IntPtr _engineResult = InternalUnsafeMethods.GetText()(ObjectPtr, _args);
             return StringMarshal.IntPtrToUtf8String(_engineResult);
        }

        /// <description>
        /// (int id, ColorI fontColor, ColorI fontColorHL, ColorI fontColorSEL)
        /// </description>
        public void AddScheme(uint id, ColorI fontColor, ColorI fontColorHL, ColorI fontColorSEL) {
fontColor.Alloc();fontColorHL.Alloc();fontColorSEL.Alloc();             InternalUnsafeMethods.AddScheme__Args _args = new InternalUnsafeMethods.AddScheme__Args() {
                id = id,
                fontColor = fontColor.internalStructPtr,
                fontColorHL = fontColorHL.internalStructPtr,
                fontColorSEL = fontColorSEL.internalStructPtr,
             };
             InternalUnsafeMethods.AddScheme()(ObjectPtr, _args);
fontColor.Free();fontColorHL.Free();fontColorSEL.Free();        }

        /// <description>
        /// (string name, int idNum, int scheme=0)
        /// </description>
        public void Add(string name = "", int idNum = -1, uint scheme = 0) {
             InternalUnsafeMethods.Add__Args _args = new InternalUnsafeMethods.Add__Args() {
                name = name,
                idNum = idNum,
                scheme = scheme,
             };
             InternalUnsafeMethods.Add()(ObjectPtr, _args);
        }

        /// <description>
        /// Get the type info object for the GuiPopUpMenuCtrl class.
        /// </description>
        /// <returns>The type info object for GuiPopUpMenuCtrl</returns>
        public static EngineTypeInfo StaticGetType() {
             InternalUnsafeMethods.StaticGetType__Args _args = new InternalUnsafeMethods.StaticGetType__Args() {
             };
             IntPtr _engineResult = InternalUnsafeMethods.StaticGetType()(_args);
             return new EngineTypeInfo(_engineResult);
        }


        /// <value>
        /// 
        /// </value>
        public int MaxPopupHeight {
            get => GenericMarshal.StringTo<int>(GetFieldValue("maxPopupHeight"));
            set => SetFieldValue("maxPopupHeight", GenericMarshal.ToString(value));
        }


        /// <value>
        /// 
        /// </value>
        public bool SbUsesNAColor {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("sbUsesNAColor"));
            set => SetFieldValue("sbUsesNAColor", GenericMarshal.ToString(value));
        }


        /// <value>
        /// 
        /// </value>
        public bool ReverseTextList {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("reverseTextList"));
            set => SetFieldValue("reverseTextList", GenericMarshal.ToString(value));
        }


        /// <value>
        /// 
        /// </value>
        public string Bitmap {
            get => GenericMarshal.StringTo<string>(GetFieldValue("bitmap"));
            set => SetFieldValue("bitmap", GenericMarshal.ToString(value));
        }


        /// <value>
        /// 
        /// </value>
        public Point2I BitmapBounds {
            get => GenericMarshal.StringTo<Point2I>(GetFieldValue("bitmapBounds"));
            set => SetFieldValue("bitmapBounds", GenericMarshal.ToString(value));
        }
    }
}