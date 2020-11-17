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
    /// <summary>A container control that can be used to implement drag&drop behavior.</summary>
    /// <description>
    /// GuiDragAndDropControl is a special control that can be used to allow drag&drop behavior to be implemented where GuiControls may be dragged across the canvas and the dropped on other GuiControls.
    /// 
    /// To start a drag operation, construct a GuiDragAndDropControl and add the control that should be drag&dropped as a child to it.  Note that this must be a single child control.  To drag multiple controls, wrap them in a new GuiControl object as a temporary container.
    /// 
    /// Then, to initiate the drag, add the GuiDragAndDropControl to the canvas and call startDragging().  You can optionally supply an offset to better position the GuiDragAndDropControl on the mouse cursor.
    /// 
    /// As the GuiDragAndDropControl is then moved across the canvas, it will call the onControlDragEnter(), onControlDragExit(), onControlDragged(), and finally onControlDropped() callbacks on the visible topmost controls that it moves across.  onControlDropped() is called when the mouse button is released and the drag operation thus finished.
    /// </description>
    /// <code>
    /// // The following example implements drag&drop behavior for GuiSwatchButtonCtrl so that
    /// // one color swatch may be dragged over the other to quickly copy its color.
    /// //
    /// // This code is taken from the stock scripts.
    /// 
    /// //---------------------------------------------------------------------------------------------
    /// 
    /// // With this method, we start the operation when the mouse is click-dragged away from a color swatch.
    /// function GuiSwatchButtonCtrl::onMouseDragged( %this )
    /// {
    ///    // First we construct a new temporary swatch button that becomes the payload for our
    ///    // drag operation and give it the properties of the swatch button we want to copy.
    /// 
    ///    %payload = new GuiSwatchButtonCtrl();
    ///    %payload.assignFieldsFrom( %this );
    ///    %payload.position = "0 0";
    ///    %payload.dragSourceControl = %this; // Remember where the drag originated from so that we don't copy a color swatch onto itself.
    /// 
    ///    // Calculate the offset of the GuiDragAndDropControl from the mouse cursor.  Here we center
    ///    // it on the cursor.
    /// 
    ///    %xOffset = getWord( %payload.extent, 0 ) / 2;
    ///    %yOffset = getWord( %payload.extent, 1 ) / 2;
    /// 
    ///    // Compute the initial position of the GuiDragAndDrop control on the cavas based on the current
    ///    // mouse cursor position.
    /// 
    ///    %cursorpos = Canvas.getCursorPos();
    ///    %xPos = getWord( %cursorpos, 0 ) - %xOffset;
    ///    %yPos = getWord( %cursorpos, 1 ) - %yOffset;
    /// 
    ///    // Create the drag control.
    /// 
    ///    %ctrl = new GuiDragAndDropControl()
    ///    {
    ///       canSaveDynamicFields    = "0";
    ///       Profile                 = "GuiSolidDefaultProfile";
    ///       HorizSizing             = "right";
    ///       VertSizing              = "bottom";
    ///       Position                = %xPos SPC %yPos;
    ///       extent                  = %payload.extent;
    ///       MinExtent               = "4 4";
    ///       canSave                 = "1";
    ///       Visible                 = "1";
    ///       hovertime               = "1000";
    /// 
    ///       // Let the GuiDragAndDropControl delete itself on mouse-up.  When the drag is aborted,
    ///       // this not only deletes the drag control but also our payload.
    ///       deleteOnMouseUp         = true;
    /// 
    ///       // To differentiate drags, use the namespace hierarchy to classify them.
    ///       // This will allow a color swatch drag to tell itself apart from a file drag, for example.
    ///       class                   = "GuiDragAndDropControlType_ColorSwatch";
    ///    };
    /// 
    ///    // Add the temporary color swatch to the drag control as the payload.
    ///    %ctrl.add( %payload );
    /// 
    ///    // Start drag by adding the drag control to the canvas and then calling startDragging().
    /// 
    ///    Canvas.getContent().add( %ctrl );
    ///    %ctrl.startDragging( %xOffset, %yOffset );
    /// }
    /// 
    /// //---------------------------------------------------------------------------------------------
    /// 
    /// // This method receives the drop when the mouse button is released over a color swatch control
    /// // during a drag operation.
    /// function GuiSwatchButtonCtrl::onControlDropped( %this, %payload, %position )
    /// {
    ///    // Make sure this is a color swatch drag operation.
    ///    if( !%payload.parentGroup.isInNamespaceHierarchy( "GuiDragAndDropControlType_ColorSwatch" ) )
    ///       return;
    /// 
    ///    // If dropped on same button whence we came from,
    ///    // do nothing.
    /// 
    ///    if( %payload.dragSourceControl == %this )
    ///       return;
    /// 
    ///    // If a swatch button control is dropped onto this control,
    ///    // copy it's color.
    /// 
    ///    if( %payload.isMemberOfClass( "GuiSwatchButtonCtrl" ) )
    ///    {
    ///       // If the swatch button is part of a color-type inspector field,
    ///       // remember the inspector field so we can later set the color
    ///       // through it.
    /// 
    ///       if( %this.parentGroup.isMemberOfClass( "GuiInspectorTypeColorI" ) )
    ///          %this.parentGroup.apply( ColorFloatToInt( %payload.color ) );
    ///       else if( %this.parentGroup.isMemberOfClass( "GuiInspectorTypeColorF" ) )
    ///          %this.parentGroup.apply( %payload.color );
    ///       else
    ///          %this.setColor( %payload.color );
    ///    }
    /// }
    /// </code>
    /// <see cref="GuiControl::onControlDragEnter" />
    /// <see cref="GuiControl::onControlDragExit" />
    /// <see cref="GuiControl::onControlDragged" />
    /// <see cref="GuiControl::onControlDropped" />
    public unsafe class GuiDragAndDropControl : GuiControl {
        public GuiDragAndDropControl(bool pRegister = false) 
            : base(pRegister) {
        }
        
        public GuiDragAndDropControl(string pName, bool pRegister) 
            : this(false) {
            Name = pName;
            if (pRegister) {
                RegisterObject();
            }
        }
        
        public GuiDragAndDropControl(string pName) 
            : this(pName, false) {
        }
        
        public GuiDragAndDropControl(string pName, string pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(Engine.Sim.FindObject<SimObject>(pParent));
        }
        
        public GuiDragAndDropControl(string pName, SimObject pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(pParent);
        }
        
        public GuiDragAndDropControl(SimObject pObj) 
            : base(pObj) {
        }
        
        public GuiDragAndDropControl(IntPtr pObj) 
            : base(pObj) {
        }
        
		protected override void CreateObjectPtr()
		{
			ObjectPtr = InternalUnsafeMethods.Create()(new InternalUnsafeMethods.Create__Args());
		}

        #region UnsafeNativeMethods
        new internal struct InternalUnsafeMethods {
            [StructLayout(LayoutKind.Sequential)]
            internal struct StartDragging__Args
            {
                internal int x;
                internal int y;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _StartDragging(IntPtr _this, StartDragging__Args args);
            private static _StartDragging _StartDraggingFunc;
            internal static _StartDragging StartDragging() {
                if (_StartDraggingFunc == null) {
                    _StartDraggingFunc =
                        (_StartDragging)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnGuiDragAndDropControl_startDragging"), typeof(_StartDragging));
                }
                
                return _StartDraggingFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct OnControlDragCancelled__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _OnControlDragCancelled(IntPtr _this, OnControlDragCancelled__Args args);
            private static _OnControlDragCancelled _OnControlDragCancelledFunc;
            internal static _OnControlDragCancelled OnControlDragCancelled() {
                if (_OnControlDragCancelledFunc == null) {
                    _OnControlDragCancelledFunc =
                        (_OnControlDragCancelled)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "cbGuiDragAndDropControl_onControlDragCancelled"), typeof(_OnControlDragCancelled));
                }
                
                return _OnControlDragCancelledFunc;
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
                                "fnGuiDragAndDropControl_staticGetType"), typeof(_StaticGetType));
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
                                "fnGuiDragAndDropControl_create"), typeof(_Create));
                }
                
                return _CreateFunc;
            }
        }
        #endregion

        /// <description>
        /// Start the drag operation.
        /// </description>
        /// <param name="x">X coordinate for the mouse pointer offset which the drag control should position itself.</param>
        /// <param name="y">Y coordinate for the mouse pointer offset which the drag control should position itself.</param>
        public void StartDragging(int x = 0, int y = 0) {
             InternalUnsafeMethods.StartDragging__Args _args = new InternalUnsafeMethods.StartDragging__Args() {
                x = x,
                y = y,
             };
             InternalUnsafeMethods.StartDragging()(ObjectPtr, _args);
        }

        /// <description>
        /// Called when the we cancel out of the drag and drop action.
        /// </description>
        /// <see cref="GuiDragAndDropControl::onControlDragCancelled" />
        public virtual void OnControlDragCancelled() {
             InternalUnsafeMethods.OnControlDragCancelled__Args _args = new InternalUnsafeMethods.OnControlDragCancelled__Args() {
             };
             InternalUnsafeMethods.OnControlDragCancelled()(ObjectPtr, _args);
        }

        /// <description>
        /// Get the type info object for the GuiDragAndDropControl class.
        /// </description>
        /// <returns>The type info object for GuiDragAndDropControl</returns>
        public static EngineTypeInfo StaticGetType() {
             InternalUnsafeMethods.StaticGetType__Args _args = new InternalUnsafeMethods.StaticGetType__Args() {
             };
             IntPtr _engineResult = InternalUnsafeMethods.StaticGetType()(_args);
             return new EngineTypeInfo(_engineResult);
        }


        /// <value>
        /// <description>
        /// If true, the control deletes itself when the left mouse button is released.
        /// 
        /// If at this point, the drag&drop control still contains its payload, it will be deleted along with the control.
        /// </description>
        /// </value>
        public bool DeleteOnMouseUp {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("deleteOnMouseUp"));
            set => SetFieldValue("deleteOnMouseUp", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// If true, the control can be tested against ANY control active on the canvas instead of just the direct parent.
        /// </description>
        /// </value>
        public bool UseWholeCanvas {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("useWholeCanvas"));
            set => SetFieldValue("useWholeCanvas", GenericMarshal.ToString(value));
        }
    }
}