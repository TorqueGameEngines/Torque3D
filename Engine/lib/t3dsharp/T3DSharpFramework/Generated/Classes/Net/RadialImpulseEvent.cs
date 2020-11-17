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

namespace T3DSharpFramework.Generated.Classes.Net {
    /// <summary>Creates a physics-based impulse effect from a defined central point and magnitude.</summary>
    /// <description>
    /// 
    /// </description>
    /// <see cref="RadialImpulseEvent::send" />
    public unsafe class RadialImpulseEvent : NetEvent {
        public RadialImpulseEvent(bool pRegister = false) 
            : base(pRegister) {
        }
        
        public RadialImpulseEvent(ConsoleObjectBase pObj) 
            : base(pObj) {
        }
        
        public RadialImpulseEvent(IntPtr pObj) 
            : base(pObj) {
        }

        #region UnsafeNativeMethods
        new internal struct InternalUnsafeMethods {
            [StructLayout(LayoutKind.Sequential)]
            internal struct Send__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string inPosition;
                internal float radius;
                internal float magnitude;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _Send(Send__Args args);
            private static _Send _SendFunc;
            internal static _Send Send() {
                if (_SendFunc == null) {
                    _SendFunc =
                        (_Send)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnRadialImpulseEvent_send"), typeof(_Send));
                }
                
                return _SendFunc;
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
                                "fnRadialImpulseEvent_staticGetType"), typeof(_StaticGetType));
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
                                "fnRadialImpulseEvent_create"), typeof(_Create));
                }
                
                return _CreateFunc;
            }
        }
        #endregion

        /// <summary>Applies a radial impulse to any SceneObjects within the area of effect.</summary>
        /// <description>
        /// This event is performed both server and client-side.
        /// </description>
        /// <param name="position">Center point for this radial impulse.</param>
        /// <param name="radius">Distance from the position for this radial impulse to affect.</param>
        /// <param name="magnitude">The force applied to objects within the radius from the position of this radial impulse effect.</param>
        /// <code>
        /// // Define the Position
        /// %position = "10.0 15.0 10.0";
        /// 
        /// // Define the Radius
        /// %radius = "25.0";
        /// 
        /// // Define the Magnitude
        /// %magnitude = "30.0"
        /// 
        /// // Create a globalRadialImpulse physics effect.
        /// RadialImpulseEvent::send(%position,%radius,%magnitude);
        /// </code>
        public static void Send(string inPosition = "1.0 1.0 1.0", float radius = 10f, float magnitude = 20f) {
             InternalUnsafeMethods.Send__Args _args = new InternalUnsafeMethods.Send__Args() {
                inPosition = inPosition,
                radius = radius,
                magnitude = magnitude,
             };
             InternalUnsafeMethods.Send()(_args);
        }

        /// <description>
        /// Get the type info object for the RadialImpulseEvent class.
        /// </description>
        /// <returns>The type info object for RadialImpulseEvent</returns>
        public static EngineTypeInfo StaticGetType() {
             InternalUnsafeMethods.StaticGetType__Args _args = new InternalUnsafeMethods.StaticGetType__Args() {
             };
             IntPtr _engineResult = InternalUnsafeMethods.StaticGetType()(_args);
             return new EngineTypeInfo(_engineResult);
        }
    }
}