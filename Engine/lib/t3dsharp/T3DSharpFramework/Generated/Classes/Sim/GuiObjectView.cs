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
    /// <summary>GUI control which displays a 3D model.</summary>
    /// <description>
    /// Model displayed in the control can have other objects mounted onto it, and the light settings can be adjusted.
    /// </description>
    /// <code>
    /// new GuiObjectView(ObjectPreview)
    /// 	{
    /// 		shapeFile = "art/shapes/items/kit/healthkit.dts";
    /// 		mountedNode = "mount0";
    /// 		lightColor = "1 1 1 1";
    /// 		lightAmbient = "0.5 0.5 0.5 1";
    /// 		lightDirection = "0 0.707 -0.707";
    /// 		orbitDiststance = "2";
    /// 		minOrbitDiststance = "0.917688";
    /// 		maxOrbitDiststance = "5";
    /// 		cameraSpeed = "0.01";
    /// 		cameraZRot = "0";
    /// 		forceFOV = "0";
    /// 		reflectPriority = "0";
    /// 	};
    /// </code>
    /// <see cref="GuiControl" />
    public unsafe class GuiObjectView : GuiTSCtrl {
        public GuiObjectView(bool pRegister = false) 
            : base(pRegister) {
        }
        
        public GuiObjectView(string pName, bool pRegister) 
            : this(false) {
            Name = pName;
            if (pRegister) {
                RegisterObject();
            }
        }
        
        public GuiObjectView(string pName) 
            : this(pName, false) {
        }
        
        public GuiObjectView(string pName, string pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(Engine.Sim.FindObject<SimObject>(pParent));
        }
        
        public GuiObjectView(string pName, SimObject pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(pParent);
        }
        
        public GuiObjectView(SimObject pObj) 
            : base(pObj) {
        }
        
        public GuiObjectView(IntPtr pObj) 
            : base(pObj) {
        }
        
		protected override void CreateObjectPtr()
		{
			ObjectPtr = InternalUnsafeMethods.Create()(new InternalUnsafeMethods.Create__Args());
		}

        #region UnsafeNativeMethods
        new internal struct InternalUnsafeMethods {
            [StructLayout(LayoutKind.Sequential)]
            internal struct SetLightDirection__Args
            {
                internal IntPtr direction;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _SetLightDirection(IntPtr _this, SetLightDirection__Args args);
            private static _SetLightDirection _SetLightDirectionFunc;
            internal static _SetLightDirection SetLightDirection() {
                if (_SetLightDirectionFunc == null) {
                    _SetLightDirectionFunc =
                        (_SetLightDirection)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnGuiObjectView_setLightDirection"), typeof(_SetLightDirection));
                }
                
                return _SetLightDirectionFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct SetLightAmbient__Args
            {
                internal IntPtr color;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _SetLightAmbient(IntPtr _this, SetLightAmbient__Args args);
            private static _SetLightAmbient _SetLightAmbientFunc;
            internal static _SetLightAmbient SetLightAmbient() {
                if (_SetLightAmbientFunc == null) {
                    _SetLightAmbientFunc =
                        (_SetLightAmbient)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnGuiObjectView_setLightAmbient"), typeof(_SetLightAmbient));
                }
                
                return _SetLightAmbientFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct SetLightColor__Args
            {
                internal IntPtr color;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _SetLightColor(IntPtr _this, SetLightColor__Args args);
            private static _SetLightColor _SetLightColorFunc;
            internal static _SetLightColor SetLightColor() {
                if (_SetLightColorFunc == null) {
                    _SetLightColorFunc =
                        (_SetLightColor)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnGuiObjectView_setLightColor"), typeof(_SetLightColor));
                }
                
                return _SetLightColorFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct SetCameraSpeed__Args
            {
                internal float factor;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _SetCameraSpeed(IntPtr _this, SetCameraSpeed__Args args);
            private static _SetCameraSpeed _SetCameraSpeedFunc;
            internal static _SetCameraSpeed SetCameraSpeed() {
                if (_SetCameraSpeedFunc == null) {
                    _SetCameraSpeedFunc =
                        (_SetCameraSpeed)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnGuiObjectView_setCameraSpeed"), typeof(_SetCameraSpeed));
                }
                
                return _SetCameraSpeedFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct GetCameraSpeed__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate float _GetCameraSpeed(IntPtr _this, GetCameraSpeed__Args args);
            private static _GetCameraSpeed _GetCameraSpeedFunc;
            internal static _GetCameraSpeed GetCameraSpeed() {
                if (_GetCameraSpeedFunc == null) {
                    _GetCameraSpeedFunc =
                        (_GetCameraSpeed)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnGuiObjectView_getCameraSpeed"), typeof(_GetCameraSpeed));
                }
                
                return _GetCameraSpeedFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct SetOrbitDistance__Args
            {
                internal float distance;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _SetOrbitDistance(IntPtr _this, SetOrbitDistance__Args args);
            private static _SetOrbitDistance _SetOrbitDistanceFunc;
            internal static _SetOrbitDistance SetOrbitDistance() {
                if (_SetOrbitDistanceFunc == null) {
                    _SetOrbitDistanceFunc =
                        (_SetOrbitDistance)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnGuiObjectView_setOrbitDistance"), typeof(_SetOrbitDistance));
                }
                
                return _SetOrbitDistanceFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct GetOrbitDistance__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate float _GetOrbitDistance(IntPtr _this, GetOrbitDistance__Args args);
            private static _GetOrbitDistance _GetOrbitDistanceFunc;
            internal static _GetOrbitDistance GetOrbitDistance() {
                if (_GetOrbitDistanceFunc == null) {
                    _GetOrbitDistanceFunc =
                        (_GetOrbitDistance)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnGuiObjectView_getOrbitDistance"), typeof(_GetOrbitDistance));
                }
                
                return _GetOrbitDistanceFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct SetMount__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string shapeName;
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string mountNodeIndexOrName;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _SetMount(IntPtr _this, SetMount__Args args);
            private static _SetMount _SetMountFunc;
            internal static _SetMount SetMount() {
                if (_SetMountFunc == null) {
                    _SetMountFunc =
                        (_SetMount)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnGuiObjectView_setMount"), typeof(_SetMount));
                }
                
                return _SetMountFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct SetSeq__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string indexOrName;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _SetSeq(IntPtr _this, SetSeq__Args args);
            private static _SetSeq _SetSeqFunc;
            internal static _SetSeq SetSeq() {
                if (_SetSeqFunc == null) {
                    _SetSeqFunc =
                        (_SetSeq)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnGuiObjectView_setSeq"), typeof(_SetSeq));
                }
                
                return _SetSeqFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct SetMountSkin__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string skinName;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _SetMountSkin(IntPtr _this, SetMountSkin__Args args);
            private static _SetMountSkin _SetMountSkinFunc;
            internal static _SetMountSkin SetMountSkin() {
                if (_SetMountSkinFunc == null) {
                    _SetMountSkinFunc =
                        (_SetMountSkin)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnGuiObjectView_setMountSkin"), typeof(_SetMountSkin));
                }
                
                return _SetMountSkinFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct GetMountSkin__Args
            {
                internal int param1;
                internal int param2;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            
            internal delegate IntPtr _GetMountSkin(IntPtr _this, GetMountSkin__Args args);
            private static _GetMountSkin _GetMountSkinFunc;
            internal static _GetMountSkin GetMountSkin() {
                if (_GetMountSkinFunc == null) {
                    _GetMountSkinFunc =
                        (_GetMountSkin)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnGuiObjectView_getMountSkin"), typeof(_GetMountSkin));
                }
                
                return _GetMountSkinFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct SetSkin__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string skinName;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _SetSkin(IntPtr _this, SetSkin__Args args);
            private static _SetSkin _SetSkinFunc;
            internal static _SetSkin SetSkin() {
                if (_SetSkinFunc == null) {
                    _SetSkinFunc =
                        (_SetSkin)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnGuiObjectView_setSkin"), typeof(_SetSkin));
                }
                
                return _SetSkinFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct GetSkin__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            
            internal delegate IntPtr _GetSkin(IntPtr _this, GetSkin__Args args);
            private static _GetSkin _GetSkinFunc;
            internal static _GetSkin GetSkin() {
                if (_GetSkinFunc == null) {
                    _GetSkinFunc =
                        (_GetSkin)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnGuiObjectView_getSkin"), typeof(_GetSkin));
                }
                
                return _GetSkinFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct SetMountedModel__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string shapeName;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _SetMountedModel(IntPtr _this, SetMountedModel__Args args);
            private static _SetMountedModel _SetMountedModelFunc;
            internal static _SetMountedModel SetMountedModel() {
                if (_SetMountedModelFunc == null) {
                    _SetMountedModelFunc =
                        (_SetMountedModel)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnGuiObjectView_setMountedModel"), typeof(_SetMountedModel));
                }
                
                return _SetMountedModelFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct GetMountedModel__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            
            internal delegate IntPtr _GetMountedModel(IntPtr _this, GetMountedModel__Args args);
            private static _GetMountedModel _GetMountedModelFunc;
            internal static _GetMountedModel GetMountedModel() {
                if (_GetMountedModelFunc == null) {
                    _GetMountedModelFunc =
                        (_GetMountedModel)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnGuiObjectView_getMountedModel"), typeof(_GetMountedModel));
                }
                
                return _GetMountedModelFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct SetModel__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string shapeName;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _SetModel(IntPtr _this, SetModel__Args args);
            private static _SetModel _SetModelFunc;
            internal static _SetModel SetModel() {
                if (_SetModelFunc == null) {
                    _SetModelFunc =
                        (_SetModel)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnGuiObjectView_setModel"), typeof(_SetModel));
                }
                
                return _SetModelFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct GetModel__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            
            internal delegate IntPtr _GetModel(IntPtr _this, GetModel__Args args);
            private static _GetModel _GetModelFunc;
            internal static _GetModel GetModel() {
                if (_GetModelFunc == null) {
                    _GetModelFunc =
                        (_GetModel)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnGuiObjectView_getModel"), typeof(_GetModel));
                }
                
                return _GetModelFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct OnMouseLeave__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _OnMouseLeave(IntPtr _this, OnMouseLeave__Args args);
            private static _OnMouseLeave _OnMouseLeaveFunc;
            internal static _OnMouseLeave OnMouseLeave() {
                if (_OnMouseLeaveFunc == null) {
                    _OnMouseLeaveFunc =
                        (_OnMouseLeave)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "cbGuiObjectView_onMouseLeave"), typeof(_OnMouseLeave));
                }
                
                return _OnMouseLeaveFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct OnMouseEnter__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _OnMouseEnter(IntPtr _this, OnMouseEnter__Args args);
            private static _OnMouseEnter _OnMouseEnterFunc;
            internal static _OnMouseEnter OnMouseEnter() {
                if (_OnMouseEnterFunc == null) {
                    _OnMouseEnterFunc =
                        (_OnMouseEnter)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "cbGuiObjectView_onMouseEnter"), typeof(_OnMouseEnter));
                }
                
                return _OnMouseEnterFunc;
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
                                "fnGuiObjectView_staticGetType"), typeof(_StaticGetType));
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
                                "fnGuiObjectView_create"), typeof(_Create));
                }
                
                return _CreateFunc;
            }
        }
        #endregion

        /// <summary>Set the light direction from which to light the model.</summary>
        /// <description>
        /// 
        /// </description>
        /// <param name="direction">XYZ direction from which the light will shine on the model</param>
        /// <code>
        /// // Set the light direction
        /// %direction = "1.0 0.2 0.4"
        /// 
        /// // Inform the GuiObjectView object to change the light direction to the defined value
        /// %thisGuiObjectView.setLightDirection(%direction);
        /// </code>
        /// <see cref="GuiControl" />
        public void SetLightDirection(Point3F direction) {
direction.Alloc();             InternalUnsafeMethods.SetLightDirection__Args _args = new InternalUnsafeMethods.SetLightDirection__Args() {
                direction = direction.internalStructPtr,
             };
             InternalUnsafeMethods.SetLightDirection()(ObjectPtr, _args);
direction.Free();        }

        /// <summary>Set the light ambient color on the sun object used to render the model.</summary>
        /// <description>
        /// 
        /// </description>
        /// <param name="color">Ambient color of sunlight.</param>
        /// <code>
        /// // Define the sun ambient color value
        /// %color = "1.0 0.4 0.6";
        /// 
        /// // Inform the GuiObjectView object to set the sun ambient color to the requested value
        /// %thisGuiObjectView.setLightAmbient(%color);
        /// </code>
        /// <see cref="GuiControl" />
        public void SetLightAmbient(LinearColorF color) {
color.Alloc();             InternalUnsafeMethods.SetLightAmbient__Args _args = new InternalUnsafeMethods.SetLightAmbient__Args() {
                color = color.internalStructPtr,
             };
             InternalUnsafeMethods.SetLightAmbient()(ObjectPtr, _args);
color.Free();        }

        /// <summary>Set the light color on the sun object used to render the model.</summary>
        /// <description>
        /// 
        /// </description>
        /// <param name="color">Color of sunlight.</param>
        /// <code>
        /// // Set the color value for the sun
        /// %color = "1.0 0.4 0.5";
        /// 
        /// // Inform the GuiObjectView object to change the sun color to the defined value
        /// %thisGuiObjectView.setLightColor(%color);
        /// </code>
        /// <see cref="GuiControl" />
        public void SetLightColor(LinearColorF color) {
color.Alloc();             InternalUnsafeMethods.SetLightColor__Args _args = new InternalUnsafeMethods.SetLightColor__Args() {
                color = color.internalStructPtr,
             };
             InternalUnsafeMethods.SetLightColor()(ObjectPtr, _args);
color.Free();        }

        /// <summary>Sets the multiplier for the camera rotation and zoom speed.</summary>
        /// <description>
        /// 
        /// </description>
        /// <param name="factor">Multiplier for camera rotation and zoom speed.</param>
        /// <code>
        /// // Set the factor value
        /// %factor = "0.75";
        /// 
        /// // Inform the GuiObjectView object to set the camera speed.
        /// %thisGuiObjectView.setCameraSpeed(%factor);
        /// </code>
        /// <see cref="GuiControl" />
        public void SetCameraSpeed(float factor) {
             InternalUnsafeMethods.SetCameraSpeed__Args _args = new InternalUnsafeMethods.SetCameraSpeed__Args() {
                factor = factor,
             };
             InternalUnsafeMethods.SetCameraSpeed()(ObjectPtr, _args);
        }

        /// <summary>Return the current multiplier for camera zooming and rotation.</summary>
        /// <description>
        /// 
        /// </description>
        /// <code>
        /// // Request the current camera zooming and rotation multiplier value
        /// %multiplier = %thisGuiObjectView.getCameraSpeed();
        /// </code>
        /// <returns>Camera zooming / rotation multiplier value.</returns>
        /// <see cref="GuiControl" />
        public float GetCameraSpeed() {
             InternalUnsafeMethods.GetCameraSpeed__Args _args = new InternalUnsafeMethods.GetCameraSpeed__Args() {
             };
             float _engineResult = InternalUnsafeMethods.GetCameraSpeed()(ObjectPtr, _args);
             return _engineResult;
        }

        /// <summary>Sets the distance at which the camera orbits the object. Clamped to the acceptable range defined in the class by min and max orbit distances.</summary>
        /// <description>
        /// Detailed description
        /// </description>
        /// <param name="distance">The distance to set the orbit to (will be clamped).</param>
        /// <code>
        /// // Define the orbit distance value
        /// %orbitDistance = "1.5";
        /// 
        /// // Inform the GuiObjectView object to set the orbit distance to the defined value
        /// %thisGuiObjectView.setOrbitDistance(%orbitDistance);
        /// </code>
        /// <see cref="GuiControl" />
        public void SetOrbitDistance(float distance) {
             InternalUnsafeMethods.SetOrbitDistance__Args _args = new InternalUnsafeMethods.SetOrbitDistance__Args() {
                distance = distance,
             };
             InternalUnsafeMethods.SetOrbitDistance()(ObjectPtr, _args);
        }

        /// <summary>Return the current distance at which the camera orbits the object.</summary>
        /// <description>
        /// 
        /// </description>
        /// <code>
        /// // Request the current orbit distance
        /// %orbitDistance = %thisGuiObjectView.getOrbitDistance();
        /// </code>
        /// <returns>The distance at which the camera orbits the object.</returns>
        /// <see cref="GuiControl" />
        public float GetOrbitDistance() {
             InternalUnsafeMethods.GetOrbitDistance__Args _args = new InternalUnsafeMethods.GetOrbitDistance__Args() {
             };
             float _engineResult = InternalUnsafeMethods.GetOrbitDistance()(ObjectPtr, _args);
             return _engineResult;
        }

        /// <summary>Mounts the given model to the specified mount point of the primary model displayed in this control.</summary>
        /// <description>
        /// Detailed description
        /// </description>
        /// <param name="shapeName">Name of the model to mount.</param>
        /// <param name="mountNodeIndexOrName">Index or name of the mount point to be mounted to. If index, corresponds to "mountN" in your shape where N is the number passed here.</param>
        /// <code>
        /// // Set the shapeName to mount
        /// %shapeName = "GideonGlasses.dts"
        /// 
        /// // Set the mount node of the primary model in the control to mount the new shape at
        /// %mountNodeIndexOrName = "3";
        /// //OR:
        /// %mountNodeIndexOrName = "Face";
        /// 
        /// // Inform the GuiObjectView object to mount the shape at the specified node.
        /// %thisGuiObjectView.setMount(%shapeName,%mountNodeIndexOrName);
        /// </code>
        /// <see cref="GuiControl" />
        public void SetMount(string shapeName, string mountNodeIndexOrName) {
             InternalUnsafeMethods.SetMount__Args _args = new InternalUnsafeMethods.SetMount__Args() {
                shapeName = shapeName,
                mountNodeIndexOrName = mountNodeIndexOrName,
             };
             InternalUnsafeMethods.SetMount()(ObjectPtr, _args);
        }

        /// <summary>Sets the animation to play for the viewed object.</summary>
        /// <description>
        /// 
        /// </description>
        /// <param name="indexOrName">The index or name of the animation to play.</param>
        /// <code>
        /// // Set the animation index value, or animation sequence name.
        /// %indexVal = "3";
        /// //OR:
        /// %indexVal = "idle";
        /// 
        /// // Inform the GuiObjectView object to set the animation sequence of the object in the control.
        /// %thisGuiObjectVew.setSeq(%indexVal);
        /// </code>
        /// <see cref="GuiControl" />
        public void SetSeq(string indexOrName) {
             InternalUnsafeMethods.SetSeq__Args _args = new InternalUnsafeMethods.SetSeq__Args() {
                indexOrName = indexOrName,
             };
             InternalUnsafeMethods.SetSeq()(ObjectPtr, _args);
        }

        /// <summary>Sets the skin to use on the mounted model.</summary>
        /// <description>
        /// 
        /// </description>
        /// <param name="skinName">Name of the skin to set on the model mounted to the main model in the control</param>
        /// <code>
        /// // Define the name of the skin
        /// %skinName = "BronzeGlasses";
        /// 
        /// // Inform the GuiObjectView Control of the skin to use on the mounted model
        /// %thisGuiObjectViewCtrl.setMountSkin(%skinName);
        /// </code>
        /// <see cref="GuiControl" />
        public void SetMountSkin(string skinName) {
             InternalUnsafeMethods.SetMountSkin__Args _args = new InternalUnsafeMethods.SetMountSkin__Args() {
                skinName = skinName,
             };
             InternalUnsafeMethods.SetMountSkin()(ObjectPtr, _args);
        }

        /// <summary>Return the name of skin used on the mounted model.</summary>
        /// <description>
        /// 
        /// </description>
        /// <code>
        /// // Request the skin name from the model mounted on to the main model in the control
        /// %mountModelSkin = %thisGuiObjectView.getMountSkin();
        /// </code>
        /// <returns>Name of the skin used on the mounted model.</returns>
        /// <see cref="GuiControl" />
        public string GetMountSkin(int param1, int param2) {
             InternalUnsafeMethods.GetMountSkin__Args _args = new InternalUnsafeMethods.GetMountSkin__Args() {
                param1 = param1,
                param2 = param2,
             };
             IntPtr _engineResult = InternalUnsafeMethods.GetMountSkin()(ObjectPtr, _args);
             return StringMarshal.IntPtrToUtf8String(_engineResult);
        }

        /// <summary>Sets the skin to use on the model being displayed.</summary>
        /// <description>
        /// 
        /// </description>
        /// <param name="skinName">Name of the skin to use.</param>
        /// <code>
        /// // Define the skin we want to apply to the main model in the control
        /// %skinName = "disco_gideon";
        /// 
        /// // Inform the GuiObjectView control to update the skin the to defined skin
        /// %thisGuiObjectView.setSkin(%skinName);
        /// </code>
        /// <see cref="GuiControl" />
        public void SetSkin(string skinName) {
             InternalUnsafeMethods.SetSkin__Args _args = new InternalUnsafeMethods.SetSkin__Args() {
                skinName = skinName,
             };
             InternalUnsafeMethods.SetSkin()(ObjectPtr, _args);
        }

        /// <summary>Return the name of skin used on the primary model.</summary>
        /// <description>
        /// 
        /// </description>
        /// <code>
        /// // Request the name of the skin used on the primary model in the control
        /// %skinName = %thisGuiObjectView.getSkin();
        /// </code>
        /// <returns>Name of the skin used on the primary model.</returns>
        /// <see cref="GuiControl" />
        public string GetSkin() {
             InternalUnsafeMethods.GetSkin__Args _args = new InternalUnsafeMethods.GetSkin__Args() {
             };
             IntPtr _engineResult = InternalUnsafeMethods.GetSkin()(ObjectPtr, _args);
             return StringMarshal.IntPtrToUtf8String(_engineResult);
        }

        /// <summary>Sets the model to be mounted on the primary model.</summary>
        /// <description>
        /// 
        /// </description>
        /// <param name="shapeName">Name of the model to mount.</param>
        /// <code>
        /// // Define the model name to mount
        /// %modelToMount = "GideonGlasses.dts";
        /// 
        /// // Inform the GuiObjectView object to mount the defined model to the existing model in the control
        /// %thisGuiObjectView.setMountedModel(%modelToMount);
        /// </code>
        /// <see cref="GuiControl" />
        public void SetMountedModel(string shapeName) {
             InternalUnsafeMethods.SetMountedModel__Args _args = new InternalUnsafeMethods.SetMountedModel__Args() {
                shapeName = shapeName,
             };
             InternalUnsafeMethods.SetMountedModel()(ObjectPtr, _args);
        }

        /// <summary>Return the name of the mounted model.</summary>
        /// <description>
        /// 
        /// </description>
        /// <code>
        /// // Request the name of the mounted model from the GuiObjectView object
        /// %mountedModelName = %thisGuiObjectView.getMountedModel();
        /// </code>
        /// <returns>Name of the mounted model.</returns>
        /// <see cref="GuiControl" />
        public string GetMountedModel() {
             InternalUnsafeMethods.GetMountedModel__Args _args = new InternalUnsafeMethods.GetMountedModel__Args() {
             };
             IntPtr _engineResult = InternalUnsafeMethods.GetMountedModel()(ObjectPtr, _args);
             return StringMarshal.IntPtrToUtf8String(_engineResult);
        }

        /// <summary>Sets the model to be displayed in this control.</summary>
        /// <description>
        /// 
        /// </description>
        /// <param name="shapeName">Name of the model to display.</param>
        /// <code>
        /// // Define the model we want to display
        /// %shapeName = "gideon.dts";
        /// 
        /// // Tell the GuiObjectView object to display the defined model
        /// %thisGuiObjectView.setModel(%shapeName);
        /// </code>
        /// <see cref="GuiControl" />
        public void SetModel(string shapeName) {
             InternalUnsafeMethods.SetModel__Args _args = new InternalUnsafeMethods.SetModel__Args() {
                shapeName = shapeName,
             };
             InternalUnsafeMethods.SetModel()(ObjectPtr, _args);
        }

        /// <summary>Return the model displayed in this view.</summary>
        /// <description>
        /// 
        /// </description>
        /// <code>
        /// // Request the displayed model name from the GuiObjectView object.
        /// %modelName = %thisGuiObjectView.getModel();
        /// </code>
        /// <returns>Name of the displayed model.</returns>
        /// <see cref="GuiControl" />
        public string GetModel() {
             InternalUnsafeMethods.GetModel__Args _args = new InternalUnsafeMethods.GetModel__Args() {
             };
             IntPtr _engineResult = InternalUnsafeMethods.GetModel()(ObjectPtr, _args);
             return StringMarshal.IntPtrToUtf8String(_engineResult);
        }

        /// <summary>Called whenever the mouse leaves the control.</summary>
        /// <description>
        /// 
        /// </description>
        /// <code>
        /// // The mouse has left the control, causing the callback to occur
        /// GuiObjectView::onMouseLeave(%this)
        /// 	{
        /// 		// Code to run when the mouse leaves this control
        /// 	}
        /// </code>
        /// <see cref="GuiControl" />
        public virtual void OnMouseLeave() {
             InternalUnsafeMethods.OnMouseLeave__Args _args = new InternalUnsafeMethods.OnMouseLeave__Args() {
             };
             InternalUnsafeMethods.OnMouseLeave()(ObjectPtr, _args);
        }

        /// <summary>Called whenever the mouse enters the control.</summary>
        /// <description>
        /// 
        /// </description>
        /// <code>
        /// // The mouse has entered the control, causing the callback to occur
        /// GuiObjectView::onMouseEnter(%this)
        /// 	{
        /// 		// Code to run when the mouse enters this control
        /// 	}
        /// </code>
        /// <see cref="GuiControl" />
        public virtual void OnMouseEnter() {
             InternalUnsafeMethods.OnMouseEnter__Args _args = new InternalUnsafeMethods.OnMouseEnter__Args() {
             };
             InternalUnsafeMethods.OnMouseEnter()(ObjectPtr, _args);
        }

        /// <description>
        /// Get the type info object for the GuiObjectView class.
        /// </description>
        /// <returns>The type info object for GuiObjectView</returns>
        public static EngineTypeInfo StaticGetType() {
             InternalUnsafeMethods.StaticGetType__Args _args = new InternalUnsafeMethods.StaticGetType__Args() {
             };
             IntPtr _engineResult = InternalUnsafeMethods.StaticGetType()(_args);
             return new EngineTypeInfo(_engineResult);
        }


        /// <value>
        /// <description>
        /// The object model shape file to show in the view.
        /// </description>
        /// </value>
        public string ShapeFile {
            get => GenericMarshal.StringTo<string>(GetFieldValue("shapeFile"));
            set => SetFieldValue("shapeFile", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// The skin to use on the object model.
        /// </description>
        /// </value>
        public string Skin {
            get => GenericMarshal.StringTo<string>(GetFieldValue("skin"));
            set => SetFieldValue("skin", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// The animation sequence to play on the model.
        /// </description>
        /// </value>
        public string AnimSequence {
            get => GenericMarshal.StringTo<string>(GetFieldValue("animSequence"));
            set => SetFieldValue("animSequence", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Optional shape file to mount on the primary model (e.g. weapon).
        /// </description>
        /// </value>
        public string MountedShapeFile {
            get => GenericMarshal.StringTo<string>(GetFieldValue("mountedShapeFile"));
            set => SetFieldValue("mountedShapeFile", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Skin name used on mounted shape file.
        /// </description>
        /// </value>
        public string MountedSkin {
            get => GenericMarshal.StringTo<string>(GetFieldValue("mountedSkin"));
            set => SetFieldValue("mountedSkin", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Name of node on primary model to which to mount the secondary shape.
        /// </description>
        /// </value>
        public string MountedNode {
            get => GenericMarshal.StringTo<string>(GetFieldValue("mountedNode"));
            set => SetFieldValue("mountedNode", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Diffuse color of the sunlight used to render the model.
        /// </description>
        /// </value>
        public LinearColorF LightColor {
            get => GenericMarshal.StringTo<LinearColorF>(GetFieldValue("lightColor"));
            set => SetFieldValue("lightColor", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Ambient color of the sunlight used to render the model.
        /// </description>
        /// </value>
        public LinearColorF LightAmbient {
            get => GenericMarshal.StringTo<LinearColorF>(GetFieldValue("lightAmbient"));
            set => SetFieldValue("lightAmbient", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Direction from which the model is illuminated.
        /// </description>
        /// </value>
        public Point3F LightDirection {
            get => GenericMarshal.StringTo<Point3F>(GetFieldValue("lightDirection"));
            set => SetFieldValue("lightDirection", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Distance from which to render the model.
        /// </description>
        /// </value>
        public float OrbitDiststance {
            get => GenericMarshal.StringTo<float>(GetFieldValue("orbitDiststance"));
            set => SetFieldValue("orbitDiststance", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Maxiumum distance to which the camera can be zoomed out.
        /// </description>
        /// </value>
        public float MinOrbitDiststance {
            get => GenericMarshal.StringTo<float>(GetFieldValue("minOrbitDiststance"));
            set => SetFieldValue("minOrbitDiststance", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Minimum distance below which the camera will not zoom in further.
        /// </description>
        /// </value>
        public float MaxOrbitDiststance {
            get => GenericMarshal.StringTo<float>(GetFieldValue("maxOrbitDiststance"));
            set => SetFieldValue("maxOrbitDiststance", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Multiplier for mouse camera operations.
        /// </description>
        /// </value>
        public float CameraSpeed {
            get => GenericMarshal.StringTo<float>(GetFieldValue("cameraSpeed"));
            set => SetFieldValue("cameraSpeed", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Set the camera rotation.
        /// </description>
        /// </value>
        public Point3F CameraRotation {
            get => GenericMarshal.StringTo<Point3F>(GetFieldValue("cameraRotation"));
            set => SetFieldValue("cameraRotation", GenericMarshal.ToString(value));
        }
    }
}