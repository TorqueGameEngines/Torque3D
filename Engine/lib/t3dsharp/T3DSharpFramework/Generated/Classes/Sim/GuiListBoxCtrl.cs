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
    /// <summary>A list of text items.</summary>
    /// <description>
    /// A list of text items where each individual entry can have its own text value, text color and associated SimObject.
    /// </description>
    /// <code>
    /// new GuiListBoxCtrl(GuiMusicPlayerMusicList)
    /// {
    ///    allowMultipleSelections = "true";
    ///    fitParentWidth = "true";
    ///    mirrorSet = "AnotherGuiListBoxCtrl";
    ///    makeNameCallback = "";
    ///    colorBullet = "1";
    ///    //Properties not specific to this control have been omitted from this example.
    /// };
    /// </code>
    /// <see cref="GuiControl" />
    public unsafe class GuiListBoxCtrl : GuiControl {
        public GuiListBoxCtrl(bool pRegister = false) 
            : base(pRegister) {
        }
        
        public GuiListBoxCtrl(string pName, bool pRegister) 
            : this(false) {
            Name = pName;
            if (pRegister) {
                RegisterObject();
            }
        }
        
        public GuiListBoxCtrl(string pName) 
            : this(pName, false) {
        }
        
        public GuiListBoxCtrl(string pName, string pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(Engine.Sim.FindObject<SimObject>(pParent));
        }
        
        public GuiListBoxCtrl(string pName, SimObject pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(pParent);
        }
        
        public GuiListBoxCtrl(SimObject pObj) 
            : base(pObj) {
        }
        
        public GuiListBoxCtrl(IntPtr pObj) 
            : base(pObj) {
        }
        
		protected override void CreateObjectPtr()
		{
			ObjectPtr = InternalUnsafeMethods.Create()(new InternalUnsafeMethods.Create__Args());
		}

        #region UnsafeNativeMethods
        new internal struct InternalUnsafeMethods {
            [StructLayout(LayoutKind.Sequential)]
            internal struct RemoveFilteredItem__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string itemName;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _RemoveFilteredItem(IntPtr _this, RemoveFilteredItem__Args args);
            private static _RemoveFilteredItem _RemoveFilteredItemFunc;
            internal static _RemoveFilteredItem RemoveFilteredItem() {
                if (_RemoveFilteredItemFunc == null) {
                    _RemoveFilteredItemFunc =
                        (_RemoveFilteredItem)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnGuiListBoxCtrl_removeFilteredItem"), typeof(_RemoveFilteredItem));
                }
                
                return _RemoveFilteredItemFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct AddFilteredItem__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string newItem;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _AddFilteredItem(IntPtr _this, AddFilteredItem__Args args);
            private static _AddFilteredItem _AddFilteredItemFunc;
            internal static _AddFilteredItem AddFilteredItem() {
                if (_AddFilteredItemFunc == null) {
                    _AddFilteredItemFunc =
                        (_AddFilteredItem)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnGuiListBoxCtrl_addFilteredItem"), typeof(_AddFilteredItem));
                }
                
                return _AddFilteredItemFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct DoMirror__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _DoMirror(IntPtr _this, DoMirror__Args args);
            private static _DoMirror _DoMirrorFunc;
            internal static _DoMirror DoMirror() {
                if (_DoMirrorFunc == null) {
                    _DoMirrorFunc =
                        (_DoMirror)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnGuiListBoxCtrl_doMirror"), typeof(_DoMirror));
                }
                
                return _DoMirrorFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct GetLastClickItem__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate int _GetLastClickItem(IntPtr _this, GetLastClickItem__Args args);
            private static _GetLastClickItem _GetLastClickItemFunc;
            internal static _GetLastClickItem GetLastClickItem() {
                if (_GetLastClickItemFunc == null) {
                    _GetLastClickItemFunc =
                        (_GetLastClickItem)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnGuiListBoxCtrl_getLastClickItem"), typeof(_GetLastClickItem));
                }
                
                return _GetLastClickItemFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct SetItemTooltip__Args
            {
                internal int index;
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string text;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _SetItemTooltip(IntPtr _this, SetItemTooltip__Args args);
            private static _SetItemTooltip _SetItemTooltipFunc;
            internal static _SetItemTooltip SetItemTooltip() {
                if (_SetItemTooltipFunc == null) {
                    _SetItemTooltipFunc =
                        (_SetItemTooltip)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnGuiListBoxCtrl_setItemTooltip"), typeof(_SetItemTooltip));
                }
                
                return _SetItemTooltipFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct SetItemText__Args
            {
                internal int index;
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string newtext;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _SetItemText(IntPtr _this, SetItemText__Args args);
            private static _SetItemText _SetItemTextFunc;
            internal static _SetItemText SetItemText() {
                if (_SetItemTextFunc == null) {
                    _SetItemTextFunc =
                        (_SetItemText)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnGuiListBoxCtrl_setItemText"), typeof(_SetItemText));
                }
                
                return _SetItemTextFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct GetItemObject__Args
            {
                internal int index;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            
            internal delegate IntPtr _GetItemObject(IntPtr _this, GetItemObject__Args args);
            private static _GetItemObject _GetItemObjectFunc;
            internal static _GetItemObject GetItemObject() {
                if (_GetItemObjectFunc == null) {
                    _GetItemObjectFunc =
                        (_GetItemObject)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnGuiListBoxCtrl_getItemObject"), typeof(_GetItemObject));
                }
                
                return _GetItemObjectFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct GetItemText__Args
            {
                internal int index;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            
            internal delegate IntPtr _GetItemText(IntPtr _this, GetItemText__Args args);
            private static _GetItemText _GetItemTextFunc;
            internal static _GetItemText GetItemText() {
                if (_GetItemTextFunc == null) {
                    _GetItemTextFunc =
                        (_GetItemText)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnGuiListBoxCtrl_getItemText"), typeof(_GetItemText));
                }
                
                return _GetItemTextFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct DeleteItem__Args
            {
                internal int itemIndex;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _DeleteItem(IntPtr _this, DeleteItem__Args args);
            private static _DeleteItem _DeleteItemFunc;
            internal static _DeleteItem DeleteItem() {
                if (_DeleteItemFunc == null) {
                    _DeleteItemFunc =
                        (_DeleteItem)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnGuiListBoxCtrl_deleteItem"), typeof(_DeleteItem));
                }
                
                return _DeleteItemFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct InsertItem__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string text;
                internal int index;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _InsertItem(IntPtr _this, InsertItem__Args args);
            private static _InsertItem _InsertItemFunc;
            internal static _InsertItem InsertItem() {
                if (_InsertItemFunc == null) {
                    _InsertItemFunc =
                        (_InsertItem)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnGuiListBoxCtrl_insertItem"), typeof(_InsertItem));
                }
                
                return _InsertItemFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct ClearItemColor__Args
            {
                internal int index;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _ClearItemColor(IntPtr _this, ClearItemColor__Args args);
            private static _ClearItemColor _ClearItemColorFunc;
            internal static _ClearItemColor ClearItemColor() {
                if (_ClearItemColorFunc == null) {
                    _ClearItemColorFunc =
                        (_ClearItemColor)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnGuiListBoxCtrl_clearItemColor"), typeof(_ClearItemColor));
                }
                
                return _ClearItemColorFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct SetItemColor__Args
            {
                internal int index;
                internal IntPtr color;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _SetItemColor(IntPtr _this, SetItemColor__Args args);
            private static _SetItemColor _SetItemColorFunc;
            internal static _SetItemColor SetItemColor() {
                if (_SetItemColorFunc == null) {
                    _SetItemColorFunc =
                        (_SetItemColor)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnGuiListBoxCtrl_setItemColor"), typeof(_SetItemColor));
                }
                
                return _SetItemColorFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct AddItem__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string newItem;
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string color;
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
                                "fnGuiListBoxCtrl_addItem"), typeof(_AddItem));
                }
                
                return _AddItemFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct SetCurSelRange__Args
            {
                internal int indexStart;
                internal int indexStop;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _SetCurSelRange(IntPtr _this, SetCurSelRange__Args args);
            private static _SetCurSelRange _SetCurSelRangeFunc;
            internal static _SetCurSelRange SetCurSelRange() {
                if (_SetCurSelRangeFunc == null) {
                    _SetCurSelRangeFunc =
                        (_SetCurSelRange)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnGuiListBoxCtrl_setCurSelRange"), typeof(_SetCurSelRange));
                }
                
                return _SetCurSelRangeFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct SetCurSel__Args
            {
                internal int indexId;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _SetCurSel(IntPtr _this, SetCurSel__Args args);
            private static _SetCurSel _SetCurSelFunc;
            internal static _SetCurSel SetCurSel() {
                if (_SetCurSelFunc == null) {
                    _SetCurSelFunc =
                        (_SetCurSel)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnGuiListBoxCtrl_setCurSel"), typeof(_SetCurSel));
                }
                
                return _SetCurSelFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct FindItemText__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string findText;
                [MarshalAs(UnmanagedType.I1)]
                internal bool bCaseSensitive;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate int _FindItemText(IntPtr _this, FindItemText__Args args);
            private static _FindItemText _FindItemTextFunc;
            internal static _FindItemText FindItemText() {
                if (_FindItemTextFunc == null) {
                    _FindItemTextFunc =
                        (_FindItemText)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnGuiListBoxCtrl_findItemText"), typeof(_FindItemText));
                }
                
                return _FindItemTextFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct GetSelectedItems__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            
            internal delegate IntPtr _GetSelectedItems(IntPtr _this, GetSelectedItems__Args args);
            private static _GetSelectedItems _GetSelectedItemsFunc;
            internal static _GetSelectedItems GetSelectedItems() {
                if (_GetSelectedItemsFunc == null) {
                    _GetSelectedItemsFunc =
                        (_GetSelectedItems)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnGuiListBoxCtrl_getSelectedItems"), typeof(_GetSelectedItems));
                }
                
                return _GetSelectedItemsFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct GetSelectedItem__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate int _GetSelectedItem(IntPtr _this, GetSelectedItem__Args args);
            private static _GetSelectedItem _GetSelectedItemFunc;
            internal static _GetSelectedItem GetSelectedItem() {
                if (_GetSelectedItemFunc == null) {
                    _GetSelectedItemFunc =
                        (_GetSelectedItem)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnGuiListBoxCtrl_getSelectedItem"), typeof(_GetSelectedItem));
                }
                
                return _GetSelectedItemFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct GetSelCount__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate int _GetSelCount(IntPtr _this, GetSelCount__Args args);
            private static _GetSelCount _GetSelCountFunc;
            internal static _GetSelCount GetSelCount() {
                if (_GetSelCountFunc == null) {
                    _GetSelCountFunc =
                        (_GetSelCount)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnGuiListBoxCtrl_getSelCount"), typeof(_GetSelCount));
                }
                
                return _GetSelCountFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct GetItemCount__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate int _GetItemCount(IntPtr _this, GetItemCount__Args args);
            private static _GetItemCount _GetItemCountFunc;
            internal static _GetItemCount GetItemCount() {
                if (_GetItemCountFunc == null) {
                    _GetItemCountFunc =
                        (_GetItemCount)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnGuiListBoxCtrl_getItemCount"), typeof(_GetItemCount));
                }
                
                return _GetItemCountFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct SetSelected__Args
            {
                internal int index;
                [MarshalAs(UnmanagedType.I1)]
                internal bool setSelected;
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
                                "fnGuiListBoxCtrl_setSelected"), typeof(_SetSelected));
                }
                
                return _SetSelectedFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct ClearSelection__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _ClearSelection(IntPtr _this, ClearSelection__Args args);
            private static _ClearSelection _ClearSelectionFunc;
            internal static _ClearSelection ClearSelection() {
                if (_ClearSelectionFunc == null) {
                    _ClearSelectionFunc =
                        (_ClearSelection)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnGuiListBoxCtrl_clearSelection"), typeof(_ClearSelection));
                }
                
                return _ClearSelectionFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct ClearItems__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _ClearItems(IntPtr _this, ClearItems__Args args);
            private static _ClearItems _ClearItemsFunc;
            internal static _ClearItems ClearItems() {
                if (_ClearItemsFunc == null) {
                    _ClearItemsFunc =
                        (_ClearItems)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnGuiListBoxCtrl_clearItems"), typeof(_ClearItems));
                }
                
                return _ClearItemsFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct SetMultipleSelection__Args
            {
                [MarshalAs(UnmanagedType.I1)]
                internal bool allowMultSelections;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _SetMultipleSelection(IntPtr _this, SetMultipleSelection__Args args);
            private static _SetMultipleSelection _SetMultipleSelectionFunc;
            internal static _SetMultipleSelection SetMultipleSelection() {
                if (_SetMultipleSelectionFunc == null) {
                    _SetMultipleSelectionFunc =
                        (_SetMultipleSelection)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnGuiListBoxCtrl_setMultipleSelection"), typeof(_SetMultipleSelection));
                }
                
                return _SetMultipleSelectionFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct IsObjectMirrored__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string indexIdString;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            [return: MarshalAs(UnmanagedType.I1)]
            internal delegate bool _IsObjectMirrored(IntPtr _this, IsObjectMirrored__Args args);
            private static _IsObjectMirrored _IsObjectMirroredFunc;
            internal static _IsObjectMirrored IsObjectMirrored() {
                if (_IsObjectMirroredFunc == null) {
                    _IsObjectMirroredFunc =
                        (_IsObjectMirrored)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "cbGuiListBoxCtrl_isObjectMirrored"), typeof(_IsObjectMirrored));
                }
                
                return _IsObjectMirroredFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct OnDeleteKey__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _OnDeleteKey(IntPtr _this, OnDeleteKey__Args args);
            private static _OnDeleteKey _OnDeleteKeyFunc;
            internal static _OnDeleteKey OnDeleteKey() {
                if (_OnDeleteKeyFunc == null) {
                    _OnDeleteKeyFunc =
                        (_OnDeleteKey)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "cbGuiListBoxCtrl_onDeleteKey"), typeof(_OnDeleteKey));
                }
                
                return _OnDeleteKeyFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct OnMouseUp__Args
            {
                internal int itemHit;
                internal int mouseClickCount;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _OnMouseUp(IntPtr _this, OnMouseUp__Args args);
            private static _OnMouseUp _OnMouseUpFunc;
            internal static _OnMouseUp OnMouseUp() {
                if (_OnMouseUpFunc == null) {
                    _OnMouseUpFunc =
                        (_OnMouseUp)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "cbGuiListBoxCtrl_onMouseUp"), typeof(_OnMouseUp));
                }
                
                return _OnMouseUpFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct OnDoubleClick__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _OnDoubleClick(IntPtr _this, OnDoubleClick__Args args);
            private static _OnDoubleClick _OnDoubleClickFunc;
            internal static _OnDoubleClick OnDoubleClick() {
                if (_OnDoubleClickFunc == null) {
                    _OnDoubleClickFunc =
                        (_OnDoubleClick)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "cbGuiListBoxCtrl_onDoubleClick"), typeof(_OnDoubleClick));
                }
                
                return _OnDoubleClickFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct OnSelect__Args
            {
                internal int index;
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string itemText;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _OnSelect(IntPtr _this, OnSelect__Args args);
            private static _OnSelect _OnSelectFunc;
            internal static _OnSelect OnSelect() {
                if (_OnSelectFunc == null) {
                    _OnSelectFunc =
                        (_OnSelect)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "cbGuiListBoxCtrl_onSelect"), typeof(_OnSelect));
                }
                
                return _OnSelectFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct OnUnSelect__Args
            {
                internal int index;
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string itemText;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _OnUnSelect(IntPtr _this, OnUnSelect__Args args);
            private static _OnUnSelect _OnUnSelectFunc;
            internal static _OnUnSelect OnUnSelect() {
                if (_OnUnSelectFunc == null) {
                    _OnUnSelectFunc =
                        (_OnUnSelect)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "cbGuiListBoxCtrl_onUnSelect"), typeof(_OnUnSelect));
                }
                
                return _OnUnSelectFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct OnClearSelection__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _OnClearSelection(IntPtr _this, OnClearSelection__Args args);
            private static _OnClearSelection _OnClearSelectionFunc;
            internal static _OnClearSelection OnClearSelection() {
                if (_OnClearSelectionFunc == null) {
                    _OnClearSelectionFunc =
                        (_OnClearSelection)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "cbGuiListBoxCtrl_onClearSelection"), typeof(_OnClearSelection));
                }
                
                return _OnClearSelectionFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct OnMouseDragged__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _OnMouseDragged(IntPtr _this, OnMouseDragged__Args args);
            private static _OnMouseDragged _OnMouseDraggedFunc;
            internal static _OnMouseDragged OnMouseDragged() {
                if (_OnMouseDraggedFunc == null) {
                    _OnMouseDraggedFunc =
                        (_OnMouseDragged)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "cbGuiListBoxCtrl_onMouseDragged"), typeof(_OnMouseDragged));
                }
                
                return _OnMouseDraggedFunc;
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
                                "fnGuiListBoxCtrl_staticGetType"), typeof(_StaticGetType));
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
                                "fnGuiListBoxCtrl_create"), typeof(_Create));
                }
                
                return _CreateFunc;
            }
        }
        #endregion

        /// <summary>Removes an item of the entered name from the filtered items list.</summary>
        /// <description>
        /// 
        /// </description>
        /// <param name="itemName">Name of the item to remove from the filtered list.</param>
        /// <code>
        /// // Define the itemName that you wish to remove.
        /// %itemName = "This Item Name";
        /// 
        /// // Remove the itemName from the GuiListBoxCtrl
        /// %thisGuiListBoxCtrl.removeFilteredItem(%itemName);
        /// </code>
        /// <see cref="GuiControl" />
        public void RemoveFilteredItem(string itemName) {
             InternalUnsafeMethods.RemoveFilteredItem__Args _args = new InternalUnsafeMethods.RemoveFilteredItem__Args() {
                itemName = itemName,
             };
             InternalUnsafeMethods.RemoveFilteredItem()(ObjectPtr, _args);
        }

        /// <summary>Checks if there is an item with the exact text of what is passed in, and if so</summary>
        /// <description>
        /// the item is removed from the list and adds that item's data to the filtered list.
        /// </description>
        /// <param name="itemName">Name of the item that we wish to add to the filtered item list of the GuiListBoxCtrl.</param>
        /// <code>
        /// // Define the itemName that we wish to add to the filtered item list.
        /// %itemName = "This Item Name";
        /// 
        /// // Add the item name to the filtered item list.
        /// %thisGuiListBoxCtrl.addFilteredItem(%filteredItemName);
        /// </code>
        /// <see cref="GuiControl" />
        public void AddFilteredItem(string newItem) {
             InternalUnsafeMethods.AddFilteredItem__Args _args = new InternalUnsafeMethods.AddFilteredItem__Args() {
                newItem = newItem,
             };
             InternalUnsafeMethods.AddFilteredItem()(ObjectPtr, _args);
        }

        /// <summary>Informs the GuiListBoxCtrl object to mirror the contents of the GuiListBoxCtrl stored in the mirrorSet field.</summary>
        /// <description>
        /// 
        /// </description>
        /// <code>
        /// \ Inform the object to mirror the object located at %thisGuiListBox.mirrorSet
        /// %thisGuiListBox.doMirror();
        /// </code>
        /// <see cref="GuiCore" />
        public void DoMirror() {
             InternalUnsafeMethods.DoMirror__Args _args = new InternalUnsafeMethods.DoMirror__Args() {
             };
             InternalUnsafeMethods.DoMirror()(ObjectPtr, _args);
        }

        /// <summary>Request the item index for the item that was last clicked.</summary>
        /// <description>
        /// 
        /// </description>
        /// <code>
        /// // Request the item index for the last clicked item in the list
        /// %lastClickedIndex = %thisGuiListBoxCtrl.getLastClickItem();
        /// </code>
        /// <returns>Index id for the last clicked item in the list.</returns>
        /// <see cref="GuiControl" />
        public int GetLastClickItem() {
             InternalUnsafeMethods.GetLastClickItem__Args _args = new InternalUnsafeMethods.GetLastClickItem__Args() {
             };
             int _engineResult = InternalUnsafeMethods.GetLastClickItem()(ObjectPtr, _args);
             return _engineResult;
        }

        /// <summary>Set the tooltip text to display for the given list item.</summary>
        /// <description>
        /// 
        /// </description>
        /// <param name="index">Index id to change the tooltip text</param>
        /// <param name="text">Text for the tooltip.</param>
        /// <code>
        /// // Define the index id
        /// %index = "12";
        /// 
        /// // Define the tooltip text
        /// %tooltip = "Gideon's goggles can see through space and time."
        /// 
        /// // Inform the GuiListBoxCtrl object to set the tooltop for the item at the defined index id
        /// %thisGuiListBoxCtrl.setItemToolTip(%index,%tooltip);
        /// </code>
        /// <see cref="GuiControl" />
        public void SetItemTooltip(int index, string text) {
             InternalUnsafeMethods.SetItemTooltip__Args _args = new InternalUnsafeMethods.SetItemTooltip__Args() {
                index = index,
                text = text,
             };
             InternalUnsafeMethods.SetItemTooltip()(ObjectPtr, _args);
        }

        /// <summary>Sets the items text at the specified index.</summary>
        /// <description>
        /// 
        /// </description>
        /// <param name="index">Index id to set the item text at.</param>
        /// <param name="newtext">Text to change the list item at index id to.</param>
        /// <code>
        /// // Define the index id/n%index = "12";
        /// 
        /// // Define the text to set the list item to
        /// %newtext = "Gideon's Fancy Goggles";
        /// 
        /// // Inform the GuiListBoxCtrl object to change the text at the requested index
        /// %thisGuiListBoxCtrl.setItemText(%index,%newText);
        /// </code>
        /// <see cref="GuiControl" />
        public void SetItemText(int index, string newtext) {
             InternalUnsafeMethods.SetItemText__Args _args = new InternalUnsafeMethods.SetItemText__Args() {
                index = index,
                newtext = newtext,
             };
             InternalUnsafeMethods.SetItemText()(ObjectPtr, _args);
        }

        /// <summary>Returns the object associated with an item. This only makes sense if you are mirroring a simset.</summary>
        /// <description>
        /// 
        /// </description>
        /// <param name="index">Index id to request the associated item from.</param>
        /// <code>
        /// // Define the index id
        /// %index = "12";
        /// 
        /// // Request the item from the GuiListBoxCtrl object
        /// %object = %thisGuiListBoxCtrl.getItemObject(%index);
        /// </code>
        /// <returns>The object associated with the item in the list.</returns>
        /// <see cref="References" />
        public string GetItemObject(int index) {
             InternalUnsafeMethods.GetItemObject__Args _args = new InternalUnsafeMethods.GetItemObject__Args() {
                index = index,
             };
             IntPtr _engineResult = InternalUnsafeMethods.GetItemObject()(ObjectPtr, _args);
             return StringMarshal.IntPtrToUtf8String(_engineResult);
        }

        /// <summary>Returns the text of the item at the specified index.</summary>
        /// <description>
        /// 
        /// </description>
        /// <param name="index">Index id to return the item text from.</param>
        /// <code>
        /// // Define the index id entry to request the text from
        /// %index = "12";
        /// 
        /// // Request the item id text from the GuiListBoxCtrl object.
        /// %text = %thisGuiListBoxCtrl.getItemText(%index);
        /// </code>
        /// <returns>The text of the requested index id.</returns>
        /// <see cref="GuiControl" />
        public string GetItemText(int index) {
             InternalUnsafeMethods.GetItemText__Args _args = new InternalUnsafeMethods.GetItemText__Args() {
                index = index,
             };
             IntPtr _engineResult = InternalUnsafeMethods.GetItemText()(ObjectPtr, _args);
             return StringMarshal.IntPtrToUtf8String(_engineResult);
        }

        /// <summary>Removes the list entry at the requested index id from the control and clears the memory associated with it.</summary>
        /// <description>
        /// 
        /// </description>
        /// <param name="itemIndex">Index id location to remove the item from.</param>
        /// <code>
        /// // Define the index id we want to remove from the list
        /// %itemIndex = "8";
        /// 
        /// // Inform the GuiListBoxCtrl object to remove the item at the defined index id.
        /// %thisGuiListBoxCtrl.deleteItem(%itemIndex);
        /// </code>
        /// <see cref="References" />
        public void DeleteItem(int itemIndex) {
             InternalUnsafeMethods.DeleteItem__Args _args = new InternalUnsafeMethods.DeleteItem__Args() {
                itemIndex = itemIndex,
             };
             InternalUnsafeMethods.DeleteItem()(ObjectPtr, _args);
        }

        /// <summary>Inserts an item into the list at the specified index and returns the index assigned or -1 on error.</summary>
        /// <description>
        /// 
        /// </description>
        /// <param name="text">Text item to add.</param>
        /// <param name="index">Index id to insert the list item text at.</param>
        /// <code>
        /// // Define the text to insert
        /// %text = "Secret Agent Gideon";
        /// 
        /// // Define the index entry to insert the text at
        /// %index = "14";
        /// 
        /// // In form the GuiListBoxCtrl object to insert the text at the defined index.
        /// %assignedId = %thisGuiListBoxCtrl.insertItem(%text,%index);
        /// </code>
        /// <returns>If successful will return the index id assigned. If unsuccessful, will return -1.</returns>
        /// <see cref="GuiControl" />
        public void InsertItem(string text, int index) {
             InternalUnsafeMethods.InsertItem__Args _args = new InternalUnsafeMethods.InsertItem__Args() {
                text = text,
                index = index,
             };
             InternalUnsafeMethods.InsertItem()(ObjectPtr, _args);
        }

        /// <summary>Removes any custom coloring from an item at the defined index id in the list.</summary>
        /// <description>
        /// 
        /// </description>
        /// <param name="index">Index id for the item to clear any custom color from.</param>
        /// <code>
        /// // Define the index id
        /// %index = "4";
        /// 
        /// // Request the GuiListBoxCtrl object to remove any custom coloring from the defined index entry
        /// %thisGuiListBoxCtrl.clearItemColor(%index);
        /// </code>
        /// <see cref="GuiControl" />
        public void ClearItemColor(int index) {
             InternalUnsafeMethods.ClearItemColor__Args _args = new InternalUnsafeMethods.ClearItemColor__Args() {
                index = index,
             };
             InternalUnsafeMethods.ClearItemColor()(ObjectPtr, _args);
        }

        /// <summary>Sets the color of a single list entry at the specified index id.</summary>
        /// <description>
        /// 
        /// </description>
        /// <param name="index">Index id to modify the color of in the list.</param>
        /// <param name="color">Color value to set the list entry to.</param>
        /// <code>
        /// // Define the index id value
        /// %index = "5";
        /// 
        /// // Define the color value
        /// %color = "1.0 0.0 0.0";
        /// 
        /// // Inform the GuiListBoxCtrl object to change the color of the requested index
        /// %thisGuiListBoxCtrl.setItemColor(%index,%color);
        /// </code>
        /// <see cref="GuiControl" />
        public void SetItemColor(int index, LinearColorF color) {
color.Alloc();             InternalUnsafeMethods.SetItemColor__Args _args = new InternalUnsafeMethods.SetItemColor__Args() {
                index = index,
                color = color.internalStructPtr,
             };
             InternalUnsafeMethods.SetItemColor()(ObjectPtr, _args);
color.Free();        }

        /// <summary>Adds an item to the end of the list with an optional color.</summary>
        /// <description>
        /// 
        /// </description>
        /// <param name="newItem">New item to add to the list.</param>
        /// <param name="color">Optional color parameter to add to the new item.</param>
        /// <code>
        /// // Define the item to add to the list.
        /// %newItem = "Gideon's Blue Coat";
        /// 
        /// // Define the optional color for the new list item.
        /// %color = "0.0 0.0 1.0";
        /// 
        /// // Inform the GuiListBoxCtrl object to add the item to the end of the list with the defined color.
        /// %thisGuiListBoxCtrl.addItem(%newItem,%color);
        /// </code>
        /// <returns>If not void, return value and description</returns>
        /// <see cref="GuiControl" />
        public int AddItem(string newItem, string color = "") {
             InternalUnsafeMethods.AddItem__Args _args = new InternalUnsafeMethods.AddItem__Args() {
                newItem = newItem,
                color = color,
             };
             int _engineResult = InternalUnsafeMethods.AddItem()(ObjectPtr, _args);
             return _engineResult;
        }

        /// <summary>Sets the current selection range from index start to stop. If no stop is specified it sets from start index to the end of the list</summary>
        /// <description>
        /// 
        /// </description>
        /// <param name="indexStart">Index Id to start selection.</param>
        /// <param name="indexStop">Index Id to end selection.</param>
        /// <code>
        /// // Set start id
        /// %indexStart = "3";
        /// 
        /// // Set end id
        /// %indexEnd = "6";
        /// 
        /// // Request the GuiListBoxCtrl object to select the defined range.
        /// %thisGuiListBoxCtrl.setCurSelRange(%indexStart,%indexEnd);
        /// </code>
        /// <see cref="GuiControl" />
        public void SetCurSelRange(int indexStart, int indexStop = 999999) {
             InternalUnsafeMethods.SetCurSelRange__Args _args = new InternalUnsafeMethods.SetCurSelRange__Args() {
                indexStart = indexStart,
                indexStop = indexStop,
             };
             InternalUnsafeMethods.SetCurSelRange()(ObjectPtr, _args);
        }

        /// <summary>Sets the currently selected item at the specified index.</summary>
        /// <description>
        /// 
        /// </description>
        /// <param name="indexId">Index Id to set selected.</param>
        /// <code>
        /// // Define the index id that we wish to select.
        /// %selectId = "4";
        /// 
        /// // Inform the GuiListBoxCtrl object to set the requested index as selected.
        /// %thisGuiListBoxCtrl.setCurSel(%selectId);
        /// </code>
        /// <see cref="GuiControl" />
        public void SetCurSel(int indexId) {
             InternalUnsafeMethods.SetCurSel__Args _args = new InternalUnsafeMethods.SetCurSel__Args() {
                indexId = indexId,
             };
             InternalUnsafeMethods.SetCurSel()(ObjectPtr, _args);
        }

        /// <summary>Returns index of item with matching text or -1 if none found.</summary>
        /// <description>
        /// 
        /// </description>
        /// <param name="findText">Text in the list to find.</param>
        /// <param name="isCaseSensitive">If true, the search will be case sensitive.</param>
        /// <code>
        /// // Define the text we wish to find in the list.
        /// %findText = "Hickory Smoked Gideon"/n/n// Define if this is a case sensitive search or not.
        /// %isCaseSensitive = "false";
        /// 
        /// // Ask the GuiListBoxCtrl object what item id in the list matches the requested text.
        /// %matchingId = %thisGuiListBoxCtrl.findItemText(%findText,%isCaseSensitive);
        /// </code>
        /// <returns>Index id of item with matching text or -1 if none found.</returns>
        /// <see cref="GuiControl" />
        public int FindItemText(string findText, bool bCaseSensitive = false) {
             InternalUnsafeMethods.FindItemText__Args _args = new InternalUnsafeMethods.FindItemText__Args() {
                findText = findText,
                bCaseSensitive = bCaseSensitive,
             };
             int _engineResult = InternalUnsafeMethods.FindItemText()(ObjectPtr, _args);
             return _engineResult;
        }

        /// <summary>Returns a space delimited list of the selected items indexes in the list.</summary>
        /// <description>
        /// 
        /// </description>
        /// <code>
        /// // Request a space delimited list of the items in the GuiListBoxCtrl object.
        /// %selectionList = %thisGuiListBoxCtrl.getSelectedItems();
        /// </code>
        /// <returns>Space delimited list of the selected items indexes in the list</returns>
        /// <see cref="GuiControl" />
        public string GetSelectedItems() {
             InternalUnsafeMethods.GetSelectedItems__Args _args = new InternalUnsafeMethods.GetSelectedItems__Args() {
             };
             IntPtr _engineResult = InternalUnsafeMethods.GetSelectedItems()(ObjectPtr, _args);
             return StringMarshal.IntPtrToUtf8String(_engineResult);
        }

        /// <summary>Returns the selected items index or -1 if none selected. If multiple selections exist it returns the first selected item.</summary>
        /// <description>
        /// 
        /// </description>
        /// <code>
        /// // Request the index id of the currently selected item
        /// %selectedItemId = %thisGuiListBoxCtrl.getSelectedItem();
        /// </code>
        /// <returns>The selected items index or -1 if none selected.</returns>
        /// <see cref="GuiControl" />
        public int GetSelectedItem() {
             InternalUnsafeMethods.GetSelectedItem__Args _args = new InternalUnsafeMethods.GetSelectedItem__Args() {
             };
             int _engineResult = InternalUnsafeMethods.GetSelectedItem()(ObjectPtr, _args);
             return _engineResult;
        }

        /// <summary>Returns the number of items currently selected.</summary>
        /// <description>
        /// 
        /// </description>
        /// <code>
        /// // Request the number of currently selected items
        /// %selectedItemCount = %thisGuiListBoxCtrl.getSelCount();
        /// </code>
        /// <returns>Number of currently selected items.</returns>
        /// <see cref="GuiControl" />
        public int GetSelCount() {
             InternalUnsafeMethods.GetSelCount__Args _args = new InternalUnsafeMethods.GetSelCount__Args() {
             };
             int _engineResult = InternalUnsafeMethods.GetSelCount()(ObjectPtr, _args);
             return _engineResult;
        }

        /// <summary>Returns the number of items in the list.</summary>
        /// <description>
        /// 
        /// </description>
        /// <code>
        /// // Request the number of items in the list of the GuiListBoxCtrl object.
        /// %listItemCount = %thisGuiListBoxCtrl.getItemCount();
        /// </code>
        /// <returns>The number of items in the list.</returns>
        /// <see cref="GuiControl" />
        public int GetItemCount() {
             InternalUnsafeMethods.GetItemCount__Args _args = new InternalUnsafeMethods.GetItemCount__Args() {
             };
             int _engineResult = InternalUnsafeMethods.GetItemCount()(ObjectPtr, _args);
             return _engineResult;
        }

        /// <summary>Sets the item at the index specified to selected or not.</summary>
        /// <description>
        /// Detailed description
        /// </description>
        /// <param name="index">Item index to set selected or unselected.</param>
        /// <param name="setSelected">Boolean selection state to set the requested item index.</param>
        /// <code>
        /// // Define the index
        /// %index = "5";
        /// 
        /// // Define the selection state
        /// %selected = "true"
        /// 
        /// // Inform the GuiListBoxCtrl object of the new selection state for the requested index entry.
        /// %thisGuiListBoxCtrl.setSelected(%index,%selected);
        /// </code>
        /// <see cref="GuiControl" />
        public void SetSelected(int index, bool setSelected = true) {
             InternalUnsafeMethods.SetSelected__Args _args = new InternalUnsafeMethods.SetSelected__Args() {
                index = index,
                setSelected = setSelected,
             };
             InternalUnsafeMethods.SetSelected()(ObjectPtr, _args);
        }

        /// <summary>Sets all currently selected items to unselected.</summary>
        /// <description>
        /// Detailed description
        /// </description>
        /// <code>
        /// // Inform the GuiListBoxCtrl object to set all of its items to unselected./n%thisGuiListBoxCtrl.clearSelection();
        /// </code>
        /// <see cref="GuiControl" />
        public void ClearSelection() {
             InternalUnsafeMethods.ClearSelection__Args _args = new InternalUnsafeMethods.ClearSelection__Args() {
             };
             InternalUnsafeMethods.ClearSelection()(ObjectPtr, _args);
        }

        /// <summary>Clears all the items in the listbox.</summary>
        /// <description>
        /// 
        /// </description>
        /// <code>
        /// // Inform the GuiListBoxCtrl object to clear all items from its list.
        /// %thisGuiListBoxCtrl.clearItems();
        /// </code>
        /// <see cref="GuiControl" />
        public void ClearItems() {
             InternalUnsafeMethods.ClearItems__Args _args = new InternalUnsafeMethods.ClearItems__Args() {
             };
             InternalUnsafeMethods.ClearItems()(ObjectPtr, _args);
        }

        /// <summary>Enable or disable multiple selections for this GuiListBoxCtrl object.</summary>
        /// <description>
        /// 
        /// </description>
        /// <param name="allowMultSelections">Boolean variable to set the use of multiple selections or not.</param>
        /// <code>
        /// // Define the multiple selection use state.
        /// %allowMultSelections = "true";
        /// 
        /// // Set the allow  multiple selection state on the GuiListBoxCtrl object.
        /// %thisGuiListBoxCtrl.setMultipleSelection(%allowMultSelections);
        /// </code>
        /// <see cref="GuiControl" />
        public void SetMultipleSelection(bool allowMultSelections) {
             InternalUnsafeMethods.SetMultipleSelection__Args _args = new InternalUnsafeMethods.SetMultipleSelection__Args() {
                allowMultSelections = allowMultSelections,
             };
             InternalUnsafeMethods.SetMultipleSelection()(ObjectPtr, _args);
        }

        /// <summary>Checks if a list item at a defined index id is mirrored, and returns the result.</summary>
        /// <description>
        /// 
        /// </description>
        /// <param name="indexIdString">Index id of the list to check.</param>
        /// <code>
        /// // Engine has requested of the script level to determine if a list entry is mirrored or not.
        /// GuiListBoxCtrl::isObjectMirrored(%this, %indexIdString)
        ///   {
        ///      // Perform code required to check and see if the list item at the index id is mirrored or not.
        ///      return %isMirrored;
        ///   }
        /// </code>
        /// <returns>A boolean value on if the list item is mirrored or not.</returns>
        /// <see cref="GuiControl" />
        public virtual bool IsObjectMirrored(string indexIdString) {
             InternalUnsafeMethods.IsObjectMirrored__Args _args = new InternalUnsafeMethods.IsObjectMirrored__Args() {
                indexIdString = indexIdString,
             };
             bool _engineResult = InternalUnsafeMethods.IsObjectMirrored()(ObjectPtr, _args);
             return _engineResult;
        }

        /// <summary>Called whenever the Delete key on the keyboard has been pressed while in this control.</summary>
        /// <description>
        /// 
        /// </description>
        /// <code>
        /// // The delete key on the keyboard has been pressed while this control is in focus, causing the callback to occur.
        /// GuiListBoxCtrl::onDeleteKey(%this)
        ///   {
        ///      // Code to call whenever the delete key is pressed
        ///   }
        /// </code>
        /// <see cref="GuiControl" />
        public virtual void OnDeleteKey() {
             InternalUnsafeMethods.OnDeleteKey__Args _args = new InternalUnsafeMethods.OnDeleteKey__Args() {
             };
             InternalUnsafeMethods.OnDeleteKey()(ObjectPtr, _args);
        }

        /// <summary>Called whenever the mouse has previously been clicked down (onMouseDown) and has now been raised on the control.</summary>
        /// <description>
        /// If an item in the list was hit during the click cycle, then the index id of the clicked object along with how many clicks occured are passed
        /// into the callback.
        /// 
        /// Detailed description
        /// </description>
        /// <param name="itemHit">Index id for the list item that was hit</param>
        /// <param name="mouseClickCount">How many mouse clicks occured on this list item</param>
        /// <code>
        /// // Mouse was previously clicked down, and now has been released, causing the callback to occur.
        /// GuiListBoxCtrl::onMouseUp(%this, %itemHit, %mouseClickCount)
        ///   {
        ///      // Code to call whenever the mouse has been clicked and released on the control
        ///   }
        /// </code>
        /// <see cref="GuiControl" />
        public virtual void OnMouseUp(int itemHit, int mouseClickCount) {
             InternalUnsafeMethods.OnMouseUp__Args _args = new InternalUnsafeMethods.OnMouseUp__Args() {
                itemHit = itemHit,
                mouseClickCount = mouseClickCount,
             };
             InternalUnsafeMethods.OnMouseUp()(ObjectPtr, _args);
        }

        /// <summary>Called whenever an item in the list has been double clicked.</summary>
        /// <description>
        /// 
        /// </description>
        /// <code>
        /// // An item in the list is double clicked, causing the callback to occur.
        /// GuiListBoxCtrl::onDoubleClick(%this)
        ///   {
        ///      // Code to run whenever an item in the control has been double clicked
        ///   }
        /// </code>
        /// <see cref="GuiControl" />
        public virtual void OnDoubleClick() {
             InternalUnsafeMethods.OnDoubleClick__Args _args = new InternalUnsafeMethods.OnDoubleClick__Args() {
             };
             InternalUnsafeMethods.OnDoubleClick()(ObjectPtr, _args);
        }

        /// <summary>Called whenever an item in the list is selected.</summary>
        /// <description>
        /// 
        /// </description>
        /// <param name="index">Index id for the item in the list that was selected.</param>
        /// <param name="itemText">Text for the list item at the index that was selected.</param>
        /// <code>
        /// // An item in the list is selected, causing the callback to occur
        /// GuiListBoxCtrl::onSelect(%this, %index, %itemText)
        ///   {
        ///      // Code to run whenever an item in the list is selected
        ///   }
        /// </code>
        /// <see cref="GuiControl" />
        public virtual void OnSelect(int index, string itemText) {
             InternalUnsafeMethods.OnSelect__Args _args = new InternalUnsafeMethods.OnSelect__Args() {
                index = index,
                itemText = itemText,
             };
             InternalUnsafeMethods.OnSelect()(ObjectPtr, _args);
        }

        /// <summary>Called whenever a selected item in the list has been unselected.</summary>
        /// <description>
        /// 
        /// </description>
        /// <param name="index">Index id of the item that was unselected</param>
        /// <param name="itemText">Text for the list entry at the index id that was unselected</param>
        /// <code>
        /// // A selected item is unselected, causing the callback to occur
        /// GuiListBoxCtrl::onUnSelect(%this, %indexId, %itemText)
        ///   {
        ///      // Code to run whenever a selected list item is unselected
        ///   }
        /// </code>
        /// <see cref="GuiControl" />
        public virtual void OnUnSelect(int index, string itemText) {
             InternalUnsafeMethods.OnUnSelect__Args _args = new InternalUnsafeMethods.OnUnSelect__Args() {
                index = index,
                itemText = itemText,
             };
             InternalUnsafeMethods.OnUnSelect()(ObjectPtr, _args);
        }

        /// <summary>Called whenever a selected item in the list is cleared.</summary>
        /// <description>
        /// 
        /// </description>
        /// <code>
        /// // A selected item is cleared, causing the callback to occur.
        /// GuiListBoxCtrl::onClearSelection(%this)
        ///   {
        ///      // Code to run whenever a selected item is cleared
        ///   }
        /// </code>
        /// <see cref="GuiControl" />
        public virtual void OnClearSelection() {
             InternalUnsafeMethods.OnClearSelection__Args _args = new InternalUnsafeMethods.OnClearSelection__Args() {
             };
             InternalUnsafeMethods.OnClearSelection()(ObjectPtr, _args);
        }

        /// <summary>Called whenever the mouse is dragged across the control.</summary>
        /// <description>
        /// 
        /// </description>
        /// <code>
        /// // Mouse is dragged across the control, causing the callback to occur.
        /// GuiListBoxCtrl::onMouseDragged(%this)
        ///   {
        ///      // Code to run whenever the mouse is dragged across the control
        ///   }
        /// </code>
        /// <see cref="GuiControl" />
        public virtual void OnMouseDragged() {
             InternalUnsafeMethods.OnMouseDragged__Args _args = new InternalUnsafeMethods.OnMouseDragged__Args() {
             };
             InternalUnsafeMethods.OnMouseDragged()(ObjectPtr, _args);
        }

        /// <description>
        /// Get the type info object for the GuiListBoxCtrl class.
        /// </description>
        /// <returns>The type info object for GuiListBoxCtrl</returns>
        public static EngineTypeInfo StaticGetType() {
             InternalUnsafeMethods.StaticGetType__Args _args = new InternalUnsafeMethods.StaticGetType__Args() {
             };
             IntPtr _engineResult = InternalUnsafeMethods.StaticGetType()(_args);
             return new EngineTypeInfo(_engineResult);
        }


        /// <value>
        /// <description>
        /// If true, will allow the selection of multiple items in the listbox.
        /// </description>
        /// </value>
        public bool AllowMultipleSelections {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("allowMultipleSelections"));
            set => SetFieldValue("allowMultipleSelections", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// If true, the width of the listbox will match the width of its parent control.
        /// </description>
        /// </value>
        public bool FitParentWidth {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("fitParentWidth"));
            set => SetFieldValue("fitParentWidth", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// If true, colored items will render a colored rectangular bullet next to the item text.
        /// </description>
        /// </value>
        public bool ColorBullet {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("colorBullet"));
            set => SetFieldValue("colorBullet", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// If populated with the name of another GuiListBoxCtrl, then this list box will mirror the contents of the mirrorSet listbox.
        /// </description>
        /// </value>
        public string MirrorSet {
            get => GenericMarshal.StringTo<string>(GetFieldValue("mirrorSet"));
            set => SetFieldValue("mirrorSet", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// A script snippet to control what is displayed in the list for a SimObject. Within this snippet, $ThisControl is bound to the guiListBoxCtrl and $ThisObject to the contained object in question.
        /// </description>
        /// </value>
        public string MakeNameCallback {
            get => GenericMarshal.StringTo<string>(GetFieldValue("makeNameCallback"));
            set => SetFieldValue("makeNameCallback", GenericMarshal.ToString(value));
        }
    }
}