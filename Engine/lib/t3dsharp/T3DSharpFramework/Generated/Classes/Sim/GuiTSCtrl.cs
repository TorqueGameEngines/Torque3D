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
    /// <summary>Abstract base class for controls that render 3D scenes.</summary>
    /// <description>
    /// GuiTSCtrl is the base class for controls that render 3D camera views in Torque.  The class itself does not implement a concrete scene rendering.  Use GuiObjectView to display invidiual shapes in the Gui and GameTSCtrl to render full scenes.
    /// </description>
    /// <see cref="GameTSCtrl" />
    /// <see cref="GuiObjectView" />
    public unsafe class GuiTSCtrl : GuiContainer {
        public GuiTSCtrl(bool pRegister = false) 
            : base(pRegister) {
        }
        
        public GuiTSCtrl(string pName, bool pRegister) 
            : this(false) {
            Name = pName;
            if (pRegister) {
                RegisterObject();
            }
        }
        
        public GuiTSCtrl(string pName) 
            : this(pName, false) {
        }
        
        public GuiTSCtrl(string pName, string pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(Engine.Sim.FindObject<SimObject>(pParent));
        }
        
        public GuiTSCtrl(string pName, SimObject pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(pParent);
        }
        
        public GuiTSCtrl(SimObject pObj) 
            : base(pObj) {
        }
        
        public GuiTSCtrl(IntPtr pObj) 
            : base(pObj) {
        }
        
		protected override void CreateObjectPtr()
		{
			ObjectPtr = InternalUnsafeMethods.Create()(new InternalUnsafeMethods.Create__Args());
		}

        #region UnsafeNativeMethods
        new internal struct InternalUnsafeMethods {
            [StructLayout(LayoutKind.Sequential)]
            internal struct SetStereoGui__Args
            {
                internal IntPtr canvas;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _SetStereoGui(IntPtr _this, SetStereoGui__Args args);
            private static _SetStereoGui _SetStereoGuiFunc;
            internal static _SetStereoGui SetStereoGui() {
                if (_SetStereoGuiFunc == null) {
                    _SetStereoGuiFunc =
                        (_SetStereoGui)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnGuiTSCtrl_setStereoGui"), typeof(_SetStereoGui));
                }
                
                return _SetStereoGuiFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct CalculateViewDistance__Args
            {
                internal float radius;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate float _CalculateViewDistance(IntPtr _this, CalculateViewDistance__Args args);
            private static _CalculateViewDistance _CalculateViewDistanceFunc;
            internal static _CalculateViewDistance CalculateViewDistance() {
                if (_CalculateViewDistanceFunc == null) {
                    _CalculateViewDistanceFunc =
                        (_CalculateViewDistance)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnGuiTSCtrl_calculateViewDistance"), typeof(_CalculateViewDistance));
                }
                
                return _CalculateViewDistanceFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct GetWorldToScreenScale__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate Point2F.InternalStruct _GetWorldToScreenScale(IntPtr _this, GetWorldToScreenScale__Args args);
            private static _GetWorldToScreenScale _GetWorldToScreenScaleFunc;
            internal static _GetWorldToScreenScale GetWorldToScreenScale() {
                if (_GetWorldToScreenScaleFunc == null) {
                    _GetWorldToScreenScaleFunc =
                        (_GetWorldToScreenScale)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnGuiTSCtrl_getWorldToScreenScale"), typeof(_GetWorldToScreenScale));
                }
                
                return _GetWorldToScreenScaleFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct Project__Args
            {
                internal IntPtr worldPosition;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate Point3F.InternalStruct _Project(IntPtr _this, Project__Args args);
            private static _Project _ProjectFunc;
            internal static _Project Project() {
                if (_ProjectFunc == null) {
                    _ProjectFunc =
                        (_Project)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnGuiTSCtrl_project"), typeof(_Project));
                }
                
                return _ProjectFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct Unproject__Args
            {
                internal IntPtr screenPosition;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate Point3F.InternalStruct _Unproject(IntPtr _this, Unproject__Args args);
            private static _Unproject _UnprojectFunc;
            internal static _Unproject Unproject() {
                if (_UnprojectFunc == null) {
                    _UnprojectFunc =
                        (_Unproject)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnGuiTSCtrl_unproject"), typeof(_Unproject));
                }
                
                return _UnprojectFunc;
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
                                "fnGuiTSCtrl_staticGetType"), typeof(_StaticGetType));
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
                                "fnGuiTSCtrl_create"), typeof(_Create));
                }
                
                return _CreateFunc;
            }
        }
        #endregion

        /// <description>
        /// Sets the current stereo texture to an offscreen canvas
        /// </description>
        /// <param name="canvas">The desired canvas.</param>
        public void SetStereoGui(GuiOffscreenCanvas canvas) {
             InternalUnsafeMethods.SetStereoGui__Args _args = new InternalUnsafeMethods.SetStereoGui__Args() {
                canvas = canvas.ObjectPtr,
             };
             InternalUnsafeMethods.SetStereoGui()(ObjectPtr, _args);
        }

        /// <description>
        /// Given the camera's current FOV, get the distance from the camera's viewpoint at which the given radius will fit in the render area.
        /// </description>
        /// <param name="radius">Radius in world-space units which should fit in the view.</param>
        /// <returns>The distance from the viewpoint at which the given radius would be fully visible.</returns>
        public float CalculateViewDistance(float radius) {
             InternalUnsafeMethods.CalculateViewDistance__Args _args = new InternalUnsafeMethods.CalculateViewDistance__Args() {
                radius = radius,
             };
             float _engineResult = InternalUnsafeMethods.CalculateViewDistance()(ObjectPtr, _args);
             return _engineResult;
        }

        /// <description>
        /// Get the ratio between world-space units and pixels.
        /// </description>
        /// <returns>The amount of world-space units covered by the extent of a single pixel.</returns>
        public Point2F GetWorldToScreenScale() {
             InternalUnsafeMethods.GetWorldToScreenScale__Args _args = new InternalUnsafeMethods.GetWorldToScreenScale__Args() {
             };
             Point2F.InternalStruct _engineResult = InternalUnsafeMethods.GetWorldToScreenScale()(ObjectPtr, _args);
             return new Point2F(_engineResult);
        }

        /// <description>
        /// Transform world-space coordinates to screen-space (x, y, depth) coordinates.
        /// </description>
        /// <param name="worldPosition">The world-space position to transform to screen-space.</param>
        /// <returns>The</returns>
        public Point3F Project(Point3F worldPosition) {
worldPosition.Alloc();             InternalUnsafeMethods.Project__Args _args = new InternalUnsafeMethods.Project__Args() {
                worldPosition = worldPosition.internalStructPtr,
             };
             Point3F.InternalStruct _engineResult = InternalUnsafeMethods.Project()(ObjectPtr, _args);
worldPosition.Free();             return new Point3F(_engineResult);
        }

        /// <description>
        /// Transform 3D screen-space coordinates (x, y, depth) to world space.
        /// This method can be, for example, used to find the world-space position relating to the current mouse cursor position.
        /// </description>
        /// <param name="screenPosition">The x/y position on the screen plus the depth from the screen-plane outwards.</param>
        /// <returns>The world-space position corresponding to the given screen-space coordinates.</returns>
        public Point3F Unproject(Point3F screenPosition) {
screenPosition.Alloc();             InternalUnsafeMethods.Unproject__Args _args = new InternalUnsafeMethods.Unproject__Args() {
                screenPosition = screenPosition.internalStructPtr,
             };
             Point3F.InternalStruct _engineResult = InternalUnsafeMethods.Unproject()(ObjectPtr, _args);
screenPosition.Free();             return new Point3F(_engineResult);
        }

        /// <description>
        /// Get the type info object for the GuiTSCtrl class.
        /// </description>
        /// <returns>The type info object for GuiTSCtrl</returns>
        public static EngineTypeInfo StaticGetType() {
             InternalUnsafeMethods.StaticGetType__Args _args = new InternalUnsafeMethods.StaticGetType__Args() {
             };
             IntPtr _engineResult = InternalUnsafeMethods.StaticGetType()(_args);
             return new EngineTypeInfo(_engineResult);
        }


        /// <value>
        /// <description>
        /// Z rotation angle of camera.
        /// </description>
        /// </value>
        public float CameraZRot {
            get => GenericMarshal.StringTo<float>(GetFieldValue("cameraZRot"));
            set => SetFieldValue("cameraZRot", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// The vertical field of view in degrees or zero to use the normal camera FOV.
        /// </description>
        /// </value>
        public float ForceFOV {
            get => GenericMarshal.StringTo<float>(GetFieldValue("forceFOV"));
            set => SetFieldValue("forceFOV", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// The share of the per-frame reflection update work this control's rendering should run.
        /// The reflect update priorities of all visible GuiTSCtrls are added together and each control is assigned a share of the per-frame reflection update time according to its percentage of the total priority value.
        /// </description>
        /// </value>
        public float ReflectPriority {
            get => GenericMarshal.StringTo<float>(GetFieldValue("reflectPriority"));
            set => SetFieldValue("reflectPriority", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Indicates how this control should render its contents.
        /// </description>
        /// </value>
        public GuiTSRenderStyles RenderStyle {
            get => GenericMarshal.StringTo<GuiTSRenderStyles>(GetFieldValue("renderStyle"));
            set => SetFieldValue("renderStyle", GenericMarshal.ToString(value));
        }
    }
}