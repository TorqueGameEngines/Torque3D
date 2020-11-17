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
    /// <description>
    /// A class designed to be used as a console consumer and log the data it receives to a file.
    /// </description>
    /// <see cref="dumpConsoleFunctions" />
    /// <see cref="dumpConsoleClasses" />
    public unsafe class ConsoleLogger : SimObject {
        public ConsoleLogger(bool pRegister = false) 
            : base(pRegister) {
        }
        
        public ConsoleLogger(string pName, bool pRegister) 
            : this(false) {
            Name = pName;
            if (pRegister) {
                RegisterObject();
            }
        }
        
        public ConsoleLogger(string pName) 
            : this(pName, false) {
        }
        
        public ConsoleLogger(string pName, string pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(Engine.Sim.FindObject<SimObject>(pParent));
        }
        
        public ConsoleLogger(string pName, SimObject pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(pParent);
        }
        
        public ConsoleLogger(SimObject pObj) 
            : base(pObj) {
        }
        
        public ConsoleLogger(IntPtr pObj) 
            : base(pObj) {
        }
        
		protected override void CreateObjectPtr()
		{
			ObjectPtr = InternalUnsafeMethods.Create()(new InternalUnsafeMethods.Create__Args());
		}

        #region UnsafeNativeMethods
        new internal struct InternalUnsafeMethods {
            [StructLayout(LayoutKind.Sequential)]
            internal struct Detach__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            [return: MarshalAs(UnmanagedType.I1)]
            internal delegate bool _Detach(IntPtr _this, Detach__Args args);
            private static _Detach _DetachFunc;
            internal static _Detach Detach() {
                if (_DetachFunc == null) {
                    _DetachFunc =
                        (_Detach)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnConsoleLogger_detach"), typeof(_Detach));
                }
                
                return _DetachFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct Attach__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            [return: MarshalAs(UnmanagedType.I1)]
            internal delegate bool _Attach(IntPtr _this, Attach__Args args);
            private static _Attach _AttachFunc;
            internal static _Attach Attach() {
                if (_AttachFunc == null) {
                    _AttachFunc =
                        (_Attach)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnConsoleLogger_attach"), typeof(_Attach));
                }
                
                return _AttachFunc;
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
                                "fnConsoleLogger_staticGetType"), typeof(_StaticGetType));
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
                                "fnConsoleLogger_create"), typeof(_Create));
                }
                
                return _CreateFunc;
            }
        }
        #endregion

        /// <description>
        /// () Detaches the logger from the console and stops writing to file
        /// </description>
        /// <code>
        /// // Create the logger
        /// // Will automatically start writing to testLogging.txt with normal priority
        /// new ConsoleLogger(logger, "testLogging.txt", false);
        /// 
        /// // Send something to the console, with the logger consumes and writes to file
        /// echo("This is logged to the file");
        /// 
        /// // Stop logging, but do not delete the logger
        /// logger.detach();
        /// 
        /// echo("This is not logged to the file");
        /// 
        /// // Attach the logger to the console again
        /// logger.attach();
        /// 
        /// // Logging has resumed
        /// echo("Logging has resumed");
        /// </code>
        public bool Detach() {
             InternalUnsafeMethods.Detach__Args _args = new InternalUnsafeMethods.Detach__Args() {
             };
             bool _engineResult = InternalUnsafeMethods.Detach()(ObjectPtr, _args);
             return _engineResult;
        }

        /// <description>
        /// () Attaches the logger to the console and begins writing to file
        /// </description>
        /// <code>
        /// // Create the logger
        /// // Will automatically start writing to testLogging.txt with normal priority
        /// new ConsoleLogger(logger, "testLogging.txt", false);
        /// 
        /// // Send something to the console, with the logger consumes and writes to file
        /// echo("This is logged to the file");
        /// 
        /// // Stop logging, but do not delete the logger
        /// logger.detach();
        /// 
        /// echo("This is not logged to the file");
        /// 
        /// // Attach the logger to the console again
        /// logger.attach();
        /// 
        /// // Logging has resumed
        /// echo("Logging has resumed");
        /// </code>
        public bool Attach() {
             InternalUnsafeMethods.Attach__Args _args = new InternalUnsafeMethods.Attach__Args() {
             };
             bool _engineResult = InternalUnsafeMethods.Attach()(ObjectPtr, _args);
             return _engineResult;
        }

        /// <description>
        /// Get the type info object for the ConsoleLogger class.
        /// </description>
        /// <returns>The type info object for ConsoleLogger</returns>
        public static EngineTypeInfo StaticGetType() {
             InternalUnsafeMethods.StaticGetType__Args _args = new InternalUnsafeMethods.StaticGetType__Args() {
             };
             IntPtr _engineResult = InternalUnsafeMethods.StaticGetType()(_args);
             return new EngineTypeInfo(_engineResult);
        }


        /// <value>
        /// <description>
        /// Determines the priority level and attention the logged entry gets when recorded
        /// </description>
        /// </value>
        public LogLevel Level {
            get => GenericMarshal.StringTo<LogLevel>(GetFieldValue("level"));
            set => SetFieldValue("level", GenericMarshal.ToString(value));
        }
    }
}