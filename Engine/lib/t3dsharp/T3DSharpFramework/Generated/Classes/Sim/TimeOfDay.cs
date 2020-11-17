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
    /// <summary>Environmental object that triggers a day/night cycle in level.</summary>
    /// <description>
    /// 
    /// </description>
    /// <remarks> TimeOfDay only works in Advanced Lighting with a Sub object or ScatterSky
    /// 
    /// </remarks>
    /// <code>
    /// new TimeOfDay(tod)
    /// {
    ///    axisTilt = "23.44";
    ///    dayLength = "120";
    ///    startTime = "0.15";
    ///    time = "0.15";
    ///    play = "0";
    ///    azimuthOverride = "572.958";
    ///    dayScale = "1";
    ///    nightScale = "1.5";
    ///    position = "598.399 550.652 196.297";
    ///    rotation = "1 0 0 0";
    ///    scale = "1 1 1";
    ///    canSave = "1";
    ///    canSaveDynamicFields = "1";
    /// };
    /// </code>
    public unsafe class TimeOfDay : SceneObject {
        public TimeOfDay(bool pRegister = false) 
            : base(pRegister) {
        }
        
        public TimeOfDay(string pName, bool pRegister) 
            : this(false) {
            Name = pName;
            if (pRegister) {
                RegisterObject();
            }
        }
        
        public TimeOfDay(string pName) 
            : this(pName, false) {
        }
        
        public TimeOfDay(string pName, string pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(Engine.Sim.FindObject<SimObject>(pParent));
        }
        
        public TimeOfDay(string pName, SimObject pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(pParent);
        }
        
        public TimeOfDay(SimObject pObj) 
            : base(pObj) {
        }
        
        public TimeOfDay(IntPtr pObj) 
            : base(pObj) {
        }
        
		protected override void CreateObjectPtr()
		{
			ObjectPtr = InternalUnsafeMethods.Create()(new InternalUnsafeMethods.Create__Args());
		}

        #region UnsafeNativeMethods
        new internal struct InternalUnsafeMethods {
            [StructLayout(LayoutKind.Sequential)]
            internal struct Animate__Args
            {
                internal float elevation;
                internal float degreesPerSecond;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _Animate(IntPtr _this, Animate__Args args);
            private static _Animate _AnimateFunc;
            internal static _Animate Animate() {
                if (_AnimateFunc == null) {
                    _AnimateFunc =
                        (_Animate)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnTimeOfDay_animate"), typeof(_Animate));
                }
                
                return _AnimateFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct SetDayLength__Args
            {
                internal float seconds;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _SetDayLength(IntPtr _this, SetDayLength__Args args);
            private static _SetDayLength _SetDayLengthFunc;
            internal static _SetDayLength SetDayLength() {
                if (_SetDayLengthFunc == null) {
                    _SetDayLengthFunc =
                        (_SetDayLength)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnTimeOfDay_setDayLength"), typeof(_SetDayLength));
                }
                
                return _SetDayLengthFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct SetPlay__Args
            {
                [MarshalAs(UnmanagedType.I1)]
                internal bool enabled;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _SetPlay(IntPtr _this, SetPlay__Args args);
            private static _SetPlay _SetPlayFunc;
            internal static _SetPlay SetPlay() {
                if (_SetPlayFunc == null) {
                    _SetPlayFunc =
                        (_SetPlay)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnTimeOfDay_setPlay"), typeof(_SetPlay));
                }
                
                return _SetPlayFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct SetTimeOfDay__Args
            {
                internal float time;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _SetTimeOfDay(IntPtr _this, SetTimeOfDay__Args args);
            private static _SetTimeOfDay _SetTimeOfDayFunc;
            internal static _SetTimeOfDay SetTimeOfDay() {
                if (_SetTimeOfDayFunc == null) {
                    _SetTimeOfDayFunc =
                        (_SetTimeOfDay)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnTimeOfDay_setTimeOfDay"), typeof(_SetTimeOfDay));
                }
                
                return _SetTimeOfDayFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct AddTimeOfDayEvent__Args
            {
                internal float elevation;
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string identifier;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _AddTimeOfDayEvent(IntPtr _this, AddTimeOfDayEvent__Args args);
            private static _AddTimeOfDayEvent _AddTimeOfDayEventFunc;
            internal static _AddTimeOfDayEvent AddTimeOfDayEvent() {
                if (_AddTimeOfDayEventFunc == null) {
                    _AddTimeOfDayEventFunc =
                        (_AddTimeOfDayEvent)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnTimeOfDay_addTimeOfDayEvent"), typeof(_AddTimeOfDayEvent));
                }
                
                return _AddTimeOfDayEventFunc;
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
                                "fnTimeOfDay_staticGetType"), typeof(_StaticGetType));
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
                                "fnTimeOfDay_create"), typeof(_Create));
                }
                
                return _CreateFunc;
            }
        }
        #endregion

        /// 
        public void Animate(float elevation, float degreesPerSecond) {
             InternalUnsafeMethods.Animate__Args _args = new InternalUnsafeMethods.Animate__Args() {
                elevation = elevation,
                degreesPerSecond = degreesPerSecond,
             };
             InternalUnsafeMethods.Animate()(ObjectPtr, _args);
        }

        /// 
        public void SetDayLength(float seconds) {
             InternalUnsafeMethods.SetDayLength__Args _args = new InternalUnsafeMethods.SetDayLength__Args() {
                seconds = seconds,
             };
             InternalUnsafeMethods.SetDayLength()(ObjectPtr, _args);
        }

        /// 
        public void SetPlay(bool enabled) {
             InternalUnsafeMethods.SetPlay__Args _args = new InternalUnsafeMethods.SetPlay__Args() {
                enabled = enabled,
             };
             InternalUnsafeMethods.SetPlay()(ObjectPtr, _args);
        }

        /// 
        public void SetTimeOfDay(float time) {
             InternalUnsafeMethods.SetTimeOfDay__Args _args = new InternalUnsafeMethods.SetTimeOfDay__Args() {
                time = time,
             };
             InternalUnsafeMethods.SetTimeOfDay()(ObjectPtr, _args);
        }

        /// 
        public void AddTimeOfDayEvent(float elevation, string identifier) {
             InternalUnsafeMethods.AddTimeOfDayEvent__Args _args = new InternalUnsafeMethods.AddTimeOfDayEvent__Args() {
                elevation = elevation,
                identifier = identifier,
             };
             InternalUnsafeMethods.AddTimeOfDayEvent()(ObjectPtr, _args);
        }

        /// <description>
        /// Get the type info object for the TimeOfDay class.
        /// </description>
        /// <returns>The type info object for TimeOfDay</returns>
        public static EngineTypeInfo StaticGetType() {
             InternalUnsafeMethods.StaticGetType__Args _args = new InternalUnsafeMethods.StaticGetType__Args() {
             };
             IntPtr _engineResult = InternalUnsafeMethods.StaticGetType()(_args);
             return new EngineTypeInfo(_engineResult);
        }


        /// <value>
        /// <description>
        /// The angle in degrees between global equator and tropic.
        /// </description>
        /// </value>
        public float AxisTilt {
            get => GenericMarshal.StringTo<float>(GetFieldValue("axisTilt"));
            set => SetFieldValue("axisTilt", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// The length of a virtual day in real world seconds.
        /// </description>
        /// </value>
        public float DayLength {
            get => GenericMarshal.StringTo<float>(GetFieldValue("dayLength"));
            set => SetFieldValue("dayLength", GenericMarshal.ToString(value));
        }


        /// <value>
        /// 
        /// </value>
        public float StartTime {
            get => GenericMarshal.StringTo<float>(GetFieldValue("startTime"));
            set => SetFieldValue("startTime", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Current time of day.
        /// </description>
        /// </value>
        public float Time {
            get => GenericMarshal.StringTo<float>(GetFieldValue("Time"));
            set => SetFieldValue("Time", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// True when the TimeOfDay object is operating.
        /// </description>
        /// </value>
        public bool Play {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("play"));
            set => SetFieldValue("play", GenericMarshal.ToString(value));
        }


        /// <value>
        /// 
        /// </value>
        public float AzimuthOverride {
            get => GenericMarshal.StringTo<float>(GetFieldValue("azimuthOverride"));
            set => SetFieldValue("azimuthOverride", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Scalar applied to time that elapses while the sun is up.
        /// </description>
        /// </value>
        public float DayScale {
            get => GenericMarshal.StringTo<float>(GetFieldValue("dayScale"));
            set => SetFieldValue("dayScale", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Scalar applied to time that elapses while the sun is down.
        /// </description>
        /// </value>
        public float NightScale {
            get => GenericMarshal.StringTo<float>(GetFieldValue("nightScale"));
            set => SetFieldValue("nightScale", GenericMarshal.ToString(value));
        }
    }
}