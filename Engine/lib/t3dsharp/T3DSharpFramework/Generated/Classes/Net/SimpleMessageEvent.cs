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
    /// <summary>A very simple example of a network event.</summary>
    /// <description>
    /// This object exists purely for instructional purposes. It is primarily geared toward developers that wish to understand the inner-working of Torque 3D's networking system. This is not intended for actual game development.
    /// </description>
    /// <see cref="NetEvent for the inner workings of network events" />
    public unsafe class SimpleMessageEvent : NetEvent {
        public SimpleMessageEvent(bool pRegister = false) 
            : base(pRegister) {
        }
        
        public SimpleMessageEvent(ConsoleObjectBase pObj) 
            : base(pObj) {
        }
        
        public SimpleMessageEvent(IntPtr pObj) 
            : base(pObj) {
        }

        #region UnsafeNativeMethods
        new internal struct InternalUnsafeMethods {
            [StructLayout(LayoutKind.Sequential)]
            internal struct Msg__Args
            {
                internal IntPtr con;
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string message;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _Msg(Msg__Args args);
            private static _Msg _MsgFunc;
            internal static _Msg Msg() {
                if (_MsgFunc == null) {
                    _MsgFunc =
                        (_Msg)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnSimpleMessageEvent_msg"), typeof(_Msg));
                }
                
                return _MsgFunc;
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
                                "fnSimpleMessageEvent_staticGetType"), typeof(_StaticGetType));
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
                                "fnSimpleMessageEvent_create"), typeof(_Create));
                }
                
                return _CreateFunc;
            }
        }
        #endregion

        /// <summary>Send a SimpleMessageEvent message to the specified connection.</summary>
        /// <description>
        /// The far end that receives the message will print the message out to the console.
        /// </description>
        /// <param name="con">The unique ID of the connection to transmit to</param>
        /// <param name="message">The string containing the message to transmit</param>
        /// <code>
        /// // Send a message to the other end of the given NetConnection
        /// SimpleMessageEvent::msg( %conn, "A message from me!");
        /// 
        /// // The far end will see the following in the console
        /// // (Note: The number may be something other than 1796 as it is the SimObjectID
        /// // of the received event)
        /// // 
        /// // RMSG 1796  A message from me!
        /// </code>
        public static void Msg(NetConnection con, string message) {
             InternalUnsafeMethods.Msg__Args _args = new InternalUnsafeMethods.Msg__Args() {
                con = con.ObjectPtr,
                message = message,
             };
             InternalUnsafeMethods.Msg()(_args);
        }

        /// <description>
        /// Get the type info object for the SimpleMessageEvent class.
        /// </description>
        /// <returns>The type info object for SimpleMessageEvent</returns>
        public static EngineTypeInfo StaticGetType() {
             InternalUnsafeMethods.StaticGetType__Args _args = new InternalUnsafeMethods.StaticGetType__Args() {
             };
             IntPtr _engineResult = InternalUnsafeMethods.StaticGetType()(_args);
             return new EngineTypeInfo(_engineResult);
        }
    }
}