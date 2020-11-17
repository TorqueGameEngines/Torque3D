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
    /// <summary>A text control that uses the Gui Markup Language ('ML') tags to dynamically change the text.</summary>
    /// <description>
    /// Example of dynamic changes include colors, styles, and/or hyperlinks. These changes can occur without having to use separate text controls with separate text profiles.
    /// </description>
    /// <code>
    /// new GuiMLTextCtrl(CenterPrintText)
    /// {
    ///     lineSpacing = "2";
    ///     allowColorChars = "0";
    ///     maxChars = "-1";
    ///     deniedSound = "DeniedSoundProfile";
    ///     text = "The Text for This Control.";
    ///     useURLMouseCursor = "true";
    ///     //Properties not specific to this control have been omitted from this example.
    /// };
    /// </code>
    /// <see cref="GuiControl" />
    public unsafe class GuiMLTextCtrl : GuiControl {
        public GuiMLTextCtrl(bool pRegister = false) 
            : base(pRegister) {
        }
        
        public GuiMLTextCtrl(string pName, bool pRegister) 
            : this(false) {
            Name = pName;
            if (pRegister) {
                RegisterObject();
            }
        }
        
        public GuiMLTextCtrl(string pName) 
            : this(pName, false) {
        }
        
        public GuiMLTextCtrl(string pName, string pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(Engine.Sim.FindObject<SimObject>(pParent));
        }
        
        public GuiMLTextCtrl(string pName, SimObject pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(pParent);
        }
        
        public GuiMLTextCtrl(SimObject pObj) 
            : base(pObj) {
        }
        
        public GuiMLTextCtrl(IntPtr pObj) 
            : base(pObj) {
        }
        
		protected override void CreateObjectPtr()
		{
			ObjectPtr = InternalUnsafeMethods.Create()(new InternalUnsafeMethods.Create__Args());
		}

        #region UnsafeNativeMethods
        new internal struct InternalUnsafeMethods {
            [StructLayout(LayoutKind.Sequential)]
            internal struct SetAlpha__Args
            {
                internal float alphaVal;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _SetAlpha(IntPtr _this, SetAlpha__Args args);
            private static _SetAlpha _SetAlphaFunc;
            internal static _SetAlpha SetAlpha() {
                if (_SetAlphaFunc == null) {
                    _SetAlphaFunc =
                        (_SetAlpha)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnGuiMLTextCtrl_setAlpha"), typeof(_SetAlpha));
                }
                
                return _SetAlphaFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct ForceReflow__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _ForceReflow(IntPtr _this, ForceReflow__Args args);
            private static _ForceReflow _ForceReflowFunc;
            internal static _ForceReflow ForceReflow() {
                if (_ForceReflowFunc == null) {
                    _ForceReflowFunc =
                        (_ForceReflow)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnGuiMLTextCtrl_forceReflow"), typeof(_ForceReflow));
                }
                
                return _ForceReflowFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct ScrollToBottom__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _ScrollToBottom(IntPtr _this, ScrollToBottom__Args args);
            private static _ScrollToBottom _ScrollToBottomFunc;
            internal static _ScrollToBottom ScrollToBottom() {
                if (_ScrollToBottomFunc == null) {
                    _ScrollToBottomFunc =
                        (_ScrollToBottom)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnGuiMLTextCtrl_scrollToBottom"), typeof(_ScrollToBottom));
                }
                
                return _ScrollToBottomFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct ScrollToTop__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _ScrollToTop(IntPtr _this, ScrollToTop__Args args);
            private static _ScrollToTop _ScrollToTopFunc;
            internal static _ScrollToTop ScrollToTop() {
                if (_ScrollToTopFunc == null) {
                    _ScrollToTopFunc =
                        (_ScrollToTop)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnGuiMLTextCtrl_scrollToTop"), typeof(_ScrollToTop));
                }
                
                return _ScrollToTopFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct ScrollToTag__Args
            {
                internal int tagID;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _ScrollToTag(IntPtr _this, ScrollToTag__Args args);
            private static _ScrollToTag _ScrollToTagFunc;
            internal static _ScrollToTag ScrollToTag() {
                if (_ScrollToTagFunc == null) {
                    _ScrollToTagFunc =
                        (_ScrollToTag)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnGuiMLTextCtrl_scrollToTag"), typeof(_ScrollToTag));
                }
                
                return _ScrollToTagFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct SetCursorPosition__Args
            {
                internal int newPos;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            [return: MarshalAs(UnmanagedType.I1)]
            internal delegate bool _SetCursorPosition(IntPtr _this, SetCursorPosition__Args args);
            private static _SetCursorPosition _SetCursorPositionFunc;
            internal static _SetCursorPosition SetCursorPosition() {
                if (_SetCursorPositionFunc == null) {
                    _SetCursorPositionFunc =
                        (_SetCursorPosition)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnGuiMLTextCtrl_setCursorPosition"), typeof(_SetCursorPosition));
                }
                
                return _SetCursorPositionFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct AddText__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string text;
                [MarshalAs(UnmanagedType.I1)]
                internal bool reformat;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _AddText(IntPtr _this, AddText__Args args);
            private static _AddText _AddTextFunc;
            internal static _AddText AddText() {
                if (_AddTextFunc == null) {
                    _AddTextFunc =
                        (_AddText)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnGuiMLTextCtrl_addText"), typeof(_AddText));
                }
                
                return _AddTextFunc;
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
                                "fnGuiMLTextCtrl_getText"), typeof(_GetText));
                }
                
                return _GetTextFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct SetText__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string text;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _SetText(IntPtr _this, SetText__Args args);
            private static _SetText _SetTextFunc;
            internal static _SetText SetText() {
                if (_SetTextFunc == null) {
                    _SetTextFunc =
                        (_SetText)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnGuiMLTextCtrl_setText"), typeof(_SetText));
                }
                
                return _SetTextFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct OnResize__Args
            {
                internal int width;
                internal int maxY;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _OnResize(IntPtr _this, OnResize__Args args);
            private static _OnResize _OnResizeFunc;
            internal static _OnResize OnResize() {
                if (_OnResizeFunc == null) {
                    _OnResizeFunc =
                        (_OnResize)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "cbGuiMLTextCtrl_onResize"), typeof(_OnResize));
                }
                
                return _OnResizeFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct OnURL__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string url;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _OnURL(IntPtr _this, OnURL__Args args);
            private static _OnURL _OnURLFunc;
            internal static _OnURL OnURL() {
                if (_OnURLFunc == null) {
                    _OnURLFunc =
                        (_OnURL)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "cbGuiMLTextCtrl_onURL"), typeof(_OnURL));
                }
                
                return _OnURLFunc;
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
                                "fnGuiMLTextCtrl_staticGetType"), typeof(_StaticGetType));
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
                                "fnGuiMLTextCtrl_create"), typeof(_Create));
                }
                
                return _CreateFunc;
            }
        }
        #endregion

        /// <summary>Sets the alpha value of the control.</summary>
        /// <description>
        /// 
        /// </description>
        /// <param name="alphaVal">n - 1.0 floating value for the alpha</param>
        /// <code>
        /// // Define the alphe value
        /// %alphaVal = "0.5";
        /// 
        /// // Inform the control to update its alpha value.
        /// %thisGuiMLTextCtrl.setAlpha(%alphaVal);
        /// </code>
        /// <see cref="GuiControl" />
        public void SetAlpha(float alphaVal) {
             InternalUnsafeMethods.SetAlpha__Args _args = new InternalUnsafeMethods.SetAlpha__Args() {
                alphaVal = alphaVal,
             };
             InternalUnsafeMethods.SetAlpha()(ObjectPtr, _args);
        }

        /// <summary>Forces the text control to reflow the text after new text is added, possibly resizing the control.</summary>
        /// <description>
        /// 
        /// </description>
        /// <code>
        /// // Define new text to add
        /// %newText = "BACON!";
        /// 
        /// // Add the new text to the control
        /// %thisGuiMLTextCtrl.addText(%newText);
        /// 
        /// // Inform the GuiMLTextCtrl object to force a reflow to ensure the added text fits properly.
        /// %thisGuiMLTextCtrl.forceReflow();
        /// </code>
        /// <see cref="GuiControl" />
        public void ForceReflow() {
             InternalUnsafeMethods.ForceReflow__Args _args = new InternalUnsafeMethods.ForceReflow__Args() {
             };
             InternalUnsafeMethods.ForceReflow()(ObjectPtr, _args);
        }

        /// <summary>Scroll to the bottom of the text.</summary>
        /// <description>
        /// 
        /// </description>
        /// <code>
        /// // Inform GuiMLTextCtrl object to scroll to its bottom
        /// %thisGuiMLTextCtrl.scrollToBottom();
        /// </code>
        /// <see cref="GuiControl" />
        public void ScrollToBottom() {
             InternalUnsafeMethods.ScrollToBottom__Args _args = new InternalUnsafeMethods.ScrollToBottom__Args() {
             };
             InternalUnsafeMethods.ScrollToBottom()(ObjectPtr, _args);
        }

        /// <summary>Scroll to the top of the text.</summary>
        /// <description>
        /// 
        /// </description>
        /// <code>
        /// // Inform GuiMLTextCtrl object to scroll to its top
        /// %thisGuiMLTextCtrl.scrollToTop();
        /// </code>
        /// <see cref="GuiControl" />
        public void ScrollToTop() {
             InternalUnsafeMethods.ScrollToTop__Args _args = new InternalUnsafeMethods.ScrollToTop__Args() {
             };
             InternalUnsafeMethods.ScrollToTop()(ObjectPtr, _args);
        }

        /// <summary>Scroll down to a specified tag.</summary>
        /// <description>
        /// Detailed description
        /// </description>
        /// <param name="tagID">TagID to scroll the control to</param>
        /// <code>
        /// // Define the TagID we want to scroll the control to
        /// %tagId = "4";
        /// 
        /// // Inform the GuiMLTextCtrl to scroll to the defined TagID
        /// %thisGuiMLTextCtrl.scrollToTag(%tagId);
        /// </code>
        /// <see cref="GuiControl" />
        public void ScrollToTag(int tagID) {
             InternalUnsafeMethods.ScrollToTag__Args _args = new InternalUnsafeMethods.ScrollToTag__Args() {
                tagID = tagID,
             };
             InternalUnsafeMethods.ScrollToTag()(ObjectPtr, _args);
        }

        /// <summary>Change the text cursor's position to a new defined offset within the text in the control.</summary>
        /// <description>
        /// 
        /// </description>
        /// <param name="newPos">Offset to place cursor.</param>
        /// <code>
        /// // Define cursor offset position
        /// %position = "23";
        /// 
        /// // Inform the GuiMLTextCtrl object to move the cursor to the new position.
        /// %thisGuiMLTextCtrl.setCursorPosition(%position);
        /// </code>
        /// <returns>Returns true if the cursor position moved, or false if the position was not changed.</returns>
        /// <see cref="GuiControl" />
        public bool SetCursorPosition(int newPos) {
             InternalUnsafeMethods.SetCursorPosition__Args _args = new InternalUnsafeMethods.SetCursorPosition__Args() {
                newPos = newPos,
             };
             bool _engineResult = InternalUnsafeMethods.SetCursorPosition()(ObjectPtr, _args);
             return _engineResult;
        }

        /// <summary>Appends the text in the control with additional text. Also .</summary>
        /// <description>
        /// 
        /// </description>
        /// <param name="text">New text to append to the existing text.</param>
        /// <param name="reformat">If true, the control will also be visually reset (defaults to true).</param>
        /// <code>
        /// // Define new text to add
        /// %text = "New Text to Add";
        /// 
        /// // Set reformat boolean
        /// %reformat = "true";
        /// 
        /// // Inform the control to add the new text
        /// %thisGuiMLTextCtrl.addText(%text,%reformat);
        /// </code>
        /// <see cref="GuiControl" />
        public void AddText(string text, bool reformat = true) {
             InternalUnsafeMethods.AddText__Args _args = new InternalUnsafeMethods.AddText__Args() {
                text = text,
                reformat = reformat,
             };
             InternalUnsafeMethods.AddText()(ObjectPtr, _args);
        }

        /// <summary>Returns the text from the control, including TorqueML characters.</summary>
        /// <description>
        /// 
        /// </description>
        /// <code>
        /// // Get the text displayed in the control
        /// %controlText = %thisGuiMLTextCtrl.getText();
        /// </code>
        /// <returns>Text string displayed in the control, including any TorqueML characters.</returns>
        /// <see cref="GuiControl" />
        public string GetText() {
             InternalUnsafeMethods.GetText__Args _args = new InternalUnsafeMethods.GetText__Args() {
             };
             IntPtr _engineResult = InternalUnsafeMethods.GetText()(ObjectPtr, _args);
             return StringMarshal.IntPtrToUtf8String(_engineResult);
        }

        /// <summary>Set the text contained in the control.</summary>
        /// <description>
        /// 
        /// </description>
        /// <param name="text">The text to display in the control.</param>
        /// <code>
        /// // Define the text to display
        /// %text = "Nifty Control Text";
        /// 
        /// // Set the text displayed within the control
        /// %thisGuiMLTextCtrl.setText(%text);
        /// </code>
        /// <see cref="GuiControl" />
        public void SetText(string text) {
             InternalUnsafeMethods.SetText__Args _args = new InternalUnsafeMethods.SetText__Args() {
                text = text,
             };
             InternalUnsafeMethods.SetText()(ObjectPtr, _args);
        }

        /// <summary>Called whenever the control size changes.</summary>
        /// <description>
        /// 
        /// </description>
        /// <param name="width">The new width value for the control</param>
        /// <param name="maxY">The current maximum allowed Y value for the control</param>
        /// <code>
        /// // Control size changed, causing the callback to occur.
        /// GuiMLTextCtrl::onResize(%this,%width,%maxY)
        ///   {
        ///      // Code to call when the control size changes
        ///   }
        /// </code>
        /// <see cref="GuiControl" />
        public virtual void OnResize(int width, int maxY) {
             InternalUnsafeMethods.OnResize__Args _args = new InternalUnsafeMethods.OnResize__Args() {
                width = width,
                maxY = maxY,
             };
             InternalUnsafeMethods.OnResize()(ObjectPtr, _args);
        }

        /// <summary>Called whenever a URL was clicked on within the control.</summary>
        /// <description>
        /// 
        /// </description>
        /// <param name="url">The URL address that was clicked on.</param>
        /// <code>
        /// // A URL address was clicked on in the control, causing the callback to occur.
        /// GuiMLTextCtrl::onUrl(%this,%url)
        ///   {
        ///      // Code to run whenever a URL was clicked on
        ///   }
        /// </code>
        /// <see cref="GuiControl" />
        public virtual void OnURL(string url) {
             InternalUnsafeMethods.OnURL__Args _args = new InternalUnsafeMethods.OnURL__Args() {
                url = url,
             };
             InternalUnsafeMethods.OnURL()(ObjectPtr, _args);
        }

        /// <description>
        /// Get the type info object for the GuiMLTextCtrl class.
        /// </description>
        /// <returns>The type info object for GuiMLTextCtrl</returns>
        public static EngineTypeInfo StaticGetType() {
             InternalUnsafeMethods.StaticGetType__Args _args = new InternalUnsafeMethods.StaticGetType__Args() {
             };
             IntPtr _engineResult = InternalUnsafeMethods.StaticGetType()(_args);
             return new EngineTypeInfo(_engineResult);
        }


        /// <value>
        /// <description>
        /// The number of blank pixels to place between each line.
        /// </description>
        /// </value>
        public int LineSpacing {
            get => GenericMarshal.StringTo<int>(GetFieldValue("lineSpacing"));
            set => SetFieldValue("lineSpacing", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// If true, the control will allow characters to have unique colors.
        /// </description>
        /// </value>
        public bool AllowColorChars {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("allowColorChars"));
            set => SetFieldValue("allowColorChars", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Maximum number of characters that the control will display.
        /// </description>
        /// </value>
        public int MaxChars {
            get => GenericMarshal.StringTo<int>(GetFieldValue("maxChars"));
            set => SetFieldValue("maxChars", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// If the text will not fit in the control, the deniedSound is played.
        /// </description>
        /// </value>
        public SFXTrack DeniedSound {
            get => GenericMarshal.StringTo<SFXTrack>(GetFieldValue("deniedSound"));
            set => SetFieldValue("deniedSound", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Text to display in this control.
        /// </description>
        /// </value>
        public string Text {
            get => GenericMarshal.StringTo<string>(GetFieldValue("text"));
            set => SetFieldValue("text", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// If true, the mouse cursor will turn into a hand cursor while over a link in the text.
        /// This is dependant on the markup language used by the GuiMLTextCtrl
        /// </description>
        /// </value>
        public bool UseURLMouseCursor {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("useURLMouseCursor"));
            set => SetFieldValue("useURLMouseCursor", GenericMarshal.ToString(value));
        }
    }
}