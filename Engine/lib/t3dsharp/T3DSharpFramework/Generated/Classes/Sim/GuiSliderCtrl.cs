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
    /// <summary>A control that displays a value between its minimal and maximal bounds using a slider placed on a vertical or horizontal axis.</summary>
    /// <description>
    /// A slider displays a value and allows that value to be changed by dragging a thumb control along the axis of the slider.  In this way, the value is changed between its allowed minimum and maximum.
    /// 
    /// To hook up script code to the value changes of a slider, use the #command and #altCommand properties.  #command is executed once the thumb is released by the user whereas #altCommand is called any time the slider value changes. When changing the slider value from script, however, trigger of #altCommand is suppressed by default.
    /// 
    /// The orientation of a slider is automatically determined from the ratio of its width to its height.  If a slider is taller than it is wide, it will be rendered with a vertical orientation.  If it is wider than it is tall, it will be rendered with a horizontal orientation.
    /// 
    /// The rendering of a slider depends on the bitmap in the slider's profile.  This bitmap must be a bitmap array comprised of at least five bitmap rectangles.  The rectangles are used such that:
    /// 
    /// - Rectangle #1: Left edge of slider
    /// - Rectangle #2: Center piece of slider; this is stretched between the left and right edge
    /// - Rectangle #3: Right edge of slider
    /// - Rectangle #4: Thumb button in normal state
    /// - Rectangle #5: Thumb button in highlighted (mouse-over) state
    /// </description>
    /// <code>
    /// // Create a sound source and a slider that changes the volume of the source.
    /// 
    /// %source = sfxPlayOnce( "art/sound/testing", AudioLoop2D );
    /// 
    /// new GuiSlider()
    /// {
    ///    // Update the sound source volume when the slider is being dragged and released.
    ///    command = %source@ ".setVolume( $ThisControl.value );";
    /// 
    ///    // Limit the range to 0..1 since that is the allowable range for sound volumes.
    ///    range = "0 1";
    /// };
    /// 
    /// </code>
    /// <see cref="GuiTextEditSliderCtrl" />
    /// <see cref="GuiTextEditSliderBitmapCtrl" />
    public unsafe class GuiSliderCtrl : GuiControl {
        public GuiSliderCtrl(bool pRegister = false) 
            : base(pRegister) {
        }
        
        public GuiSliderCtrl(string pName, bool pRegister) 
            : this(false) {
            Name = pName;
            if (pRegister) {
                RegisterObject();
            }
        }
        
        public GuiSliderCtrl(string pName) 
            : this(pName, false) {
        }
        
        public GuiSliderCtrl(string pName, string pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(Engine.Sim.FindObject<SimObject>(pParent));
        }
        
        public GuiSliderCtrl(string pName, SimObject pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(pParent);
        }
        
        public GuiSliderCtrl(SimObject pObj) 
            : base(pObj) {
        }
        
        public GuiSliderCtrl(IntPtr pObj) 
            : base(pObj) {
        }
        
		protected override void CreateObjectPtr()
		{
			ObjectPtr = InternalUnsafeMethods.Create()(new InternalUnsafeMethods.Create__Args());
		}

        #region UnsafeNativeMethods
        new internal struct InternalUnsafeMethods {
            [StructLayout(LayoutKind.Sequential)]
            internal struct IsThumbBeingDragged__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            [return: MarshalAs(UnmanagedType.I1)]
            internal delegate bool _IsThumbBeingDragged(IntPtr _this, IsThumbBeingDragged__Args args);
            private static _IsThumbBeingDragged _IsThumbBeingDraggedFunc;
            internal static _IsThumbBeingDragged IsThumbBeingDragged() {
                if (_IsThumbBeingDraggedFunc == null) {
                    _IsThumbBeingDraggedFunc =
                        (_IsThumbBeingDragged)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnGuiSliderCtrl_isThumbBeingDragged"), typeof(_IsThumbBeingDragged));
                }
                
                return _IsThumbBeingDraggedFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct SetValue__Args
            {
                internal float pos;
                [MarshalAs(UnmanagedType.I1)]
                internal bool doCallback;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _SetValue(IntPtr _this, SetValue__Args args);
            private static _SetValue _SetValueFunc;
            internal static _SetValue SetValue() {
                if (_SetValueFunc == null) {
                    _SetValueFunc =
                        (_SetValue)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnGuiSliderCtrl_setValue"), typeof(_SetValue));
                }
                
                return _SetValueFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct GetValue__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate float _GetValue(IntPtr _this, GetValue__Args args);
            private static _GetValue _GetValueFunc;
            internal static _GetValue GetValue() {
                if (_GetValueFunc == null) {
                    _GetValueFunc =
                        (_GetValue)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnGuiSliderCtrl_getValue"), typeof(_GetValue));
                }
                
                return _GetValueFunc;
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
                                "cbGuiSliderCtrl_onMouseDragged"), typeof(_OnMouseDragged));
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
                                "fnGuiSliderCtrl_staticGetType"), typeof(_StaticGetType));
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
                                "fnGuiSliderCtrl_create"), typeof(_Create));
                }
                
                return _CreateFunc;
            }
        }
        #endregion

        /// <description>
        /// Returns true if the thumb is currently being dragged by the user.  This method is mainly useful for scrubbing type sliders where the slider position is sync'd to a changing value.  When the user is dragging the thumb, however, the sync'ing should pause and not get in the way of the user.
        /// </description>
        public bool IsThumbBeingDragged() {
             InternalUnsafeMethods.IsThumbBeingDragged__Args _args = new InternalUnsafeMethods.IsThumbBeingDragged__Args() {
             };
             bool _engineResult = InternalUnsafeMethods.IsThumbBeingDragged()(ObjectPtr, _args);
             return _engineResult;
        }

        /// <description>
        /// Set position of the thumb on the slider.
        /// </description>
        /// <param name="pos">New slider position (from range.x to range.y)</param>
        /// <param name="doCallback">If true, the altCommand callback will be invoked</param>
        public void SetValue(float pos, bool doCallback = false) {
             InternalUnsafeMethods.SetValue__Args _args = new InternalUnsafeMethods.SetValue__Args() {
                pos = pos,
                doCallback = doCallback,
             };
             InternalUnsafeMethods.SetValue()(ObjectPtr, _args);
        }

        /// <description>
        /// Get the current value of the slider based on the position of the thumb.
        /// </description>
        /// <returns>Slider position (from range.x to range.y).</returns>
        public float GetValue() {
             InternalUnsafeMethods.GetValue__Args _args = new InternalUnsafeMethods.GetValue__Args() {
             };
             float _engineResult = InternalUnsafeMethods.GetValue()(ObjectPtr, _args);
             return _engineResult;
        }

        /// <description>
        /// Called when the left mouse button is dragged across the slider.
        /// </description>
        public virtual void OnMouseDragged() {
             InternalUnsafeMethods.OnMouseDragged__Args _args = new InternalUnsafeMethods.OnMouseDragged__Args() {
             };
             InternalUnsafeMethods.OnMouseDragged()(ObjectPtr, _args);
        }

        /// <description>
        /// Get the type info object for the GuiSliderCtrl class.
        /// </description>
        /// <returns>The type info object for GuiSliderCtrl</returns>
        public static EngineTypeInfo StaticGetType() {
             InternalUnsafeMethods.StaticGetType__Args _args = new InternalUnsafeMethods.StaticGetType__Args() {
             };
             IntPtr _engineResult = InternalUnsafeMethods.StaticGetType()(_args);
             return new EngineTypeInfo(_engineResult);
        }


        /// <value>
        /// <description>
        /// Min and max values corresponding to left and right slider position.
        /// </description>
        /// </value>
        public Point2F Range {
            get => GenericMarshal.StringTo<Point2F>(GetFieldValue("range"));
            set => SetFieldValue("range", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Spacing between tick marks in pixels. 0=off.
        /// </description>
        /// </value>
        public int Ticks {
            get => GenericMarshal.StringTo<int>(GetFieldValue("ticks"));
            set => SetFieldValue("ticks", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Whether to snap the slider to tick marks.
        /// </description>
        /// </value>
        public bool Snap {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("snap"));
            set => SetFieldValue("snap", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// The value corresponding to the current slider position.
        /// </description>
        /// </value>
        public float Value {
            get => GenericMarshal.StringTo<float>(GetFieldValue("value"));
            set => SetFieldValue("value", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Whether to render the tick marks.
        /// </description>
        /// </value>
        public bool UseFillBar {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("useFillBar"));
            set => SetFieldValue("useFillBar", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Whether to render the tick marks.
        /// </description>
        /// </value>
        public ColorI FillBarColor {
            get => GenericMarshal.StringTo<ColorI>(GetFieldValue("fillBarColor"));
            set => SetFieldValue("fillBarColor", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Whether to render the tick marks.
        /// </description>
        /// </value>
        public bool RenderTicks {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("renderTicks"));
            set => SetFieldValue("renderTicks", GenericMarshal.ToString(value));
        }
    }
}