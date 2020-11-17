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
    /// <summary>A wrapper around StreamObject for parsing text and data from files.</summary>
    /// <description>
    /// FileStreamObject inherits from StreamObject and provides some unique methods for working with strings.  If you're looking for general file handling, you may want to use FileObject.
    /// </description>
    /// <code>
    /// // Create a file stream object for reading
    /// %fsObject = new FileStreamObject();
    /// 
    /// // Open a file for reading
    /// %fsObject.open("./test.txt", "read");
    /// 
    /// // Get the status and print it
    /// %status = %fsObject.getStatus();
    /// echo(%status);
    /// 
    /// // Always remember to close a file stream when finished
    /// %fsObject.close();
    /// </code>
    /// <see cref="StreamObject for the list of inherited functions variables" />
    /// <see cref="FileObject for general file handling." />
    public unsafe class FileStreamObject : StreamObject {
        public FileStreamObject(bool pRegister = false) 
            : base(pRegister) {
        }
        
        public FileStreamObject(string pName, bool pRegister) 
            : this(false) {
            Name = pName;
            if (pRegister) {
                RegisterObject();
            }
        }
        
        public FileStreamObject(string pName) 
            : this(pName, false) {
        }
        
        public FileStreamObject(string pName, string pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(Engine.Sim.FindObject<SimObject>(pParent));
        }
        
        public FileStreamObject(string pName, SimObject pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(pParent);
        }
        
        public FileStreamObject(SimObject pObj) 
            : base(pObj) {
        }
        
        public FileStreamObject(IntPtr pObj) 
            : base(pObj) {
        }
        
		protected override void CreateObjectPtr()
		{
			ObjectPtr = InternalUnsafeMethods.Create()(new InternalUnsafeMethods.Create__Args());
		}

        #region UnsafeNativeMethods
        new internal struct InternalUnsafeMethods {
            [StructLayout(LayoutKind.Sequential)]
            internal struct Close__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _Close(IntPtr _this, Close__Args args);
            private static _Close _CloseFunc;
            internal static _Close Close() {
                if (_CloseFunc == null) {
                    _CloseFunc =
                        (_Close)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnFileStreamObject_close"), typeof(_Close));
                }
                
                return _CloseFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct Open__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string filename;
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string openMode;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            [return: MarshalAs(UnmanagedType.I1)]
            internal delegate bool _Open(IntPtr _this, Open__Args args);
            private static _Open _OpenFunc;
            internal static _Open Open() {
                if (_OpenFunc == null) {
                    _OpenFunc =
                        (_Open)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnFileStreamObject_open"), typeof(_Open));
                }
                
                return _OpenFunc;
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
                                "fnFileStreamObject_staticGetType"), typeof(_StaticGetType));
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
                                "fnFileStreamObject_create"), typeof(_Create));
                }
                
                return _CreateFunc;
            }
        }
        #endregion

        /// <summary>Close the file. You can no longer read or write to it unless you open it again.</summary>
        /// <description>
        /// 
        /// </description>
        /// <code>
        /// // Create a file stream object for reading
        /// %fsObject = new FileStreamObject();
        /// 
        /// // Open a file for reading
        /// %fsObject.open("./test.txt", "read");
        /// 
        /// // Always remember to close a file stream when finished
        /// %fsObject.close();
        /// </code>
        /// <see cref="open()" />
        public void Close() {
             InternalUnsafeMethods.Close__Args _args = new InternalUnsafeMethods.Close__Args() {
             };
             InternalUnsafeMethods.Close()(ObjectPtr, _args);
        }

        /// <summary>Open a file for reading, writing, reading and writing, or appending</summary>
        /// <description>
        /// Using "Read" for the open mode allows you to parse the contents of file, but not making modifications. "Write" will create a new file if it does not exist, or erase the contents of an existing file when opened. Write also allows you to modify the contents of the file.
        /// 
        /// "ReadWrite" will provide the ability to parse data (read it in) and manipulate data (write it out) interchangeably. Keep in mind the stream can move during each operation. Finally, "WriteAppend" will open a file if it exists, but will not clear the contents. You can write new data starting  at the end of the files existing contents.
        /// </description>
        /// <param name="filename">Name of file to open</param>
        /// <param name="openMode">One of "Read", "Write", "ReadWrite" or "WriteAppend"</param>
        /// <code>
        /// // Create a file stream object for reading
        /// %fsObject = new FileStreamObject();
        /// 
        /// // Open a file for reading
        /// %fsObject.open("./test.txt", "read");
        /// 
        /// // Get the status and print it
        /// %status = %fsObject.getStatus();
        /// echo(%status);
        /// 
        /// // Always remember to close a file stream when finished
        /// %fsObject.close();
        /// </code>
        /// <returns>True if the file was successfully opened, false if something went wrong</returns>
        /// <see cref="close()" />
        public bool Open(string filename, string openMode) {
             InternalUnsafeMethods.Open__Args _args = new InternalUnsafeMethods.Open__Args() {
                filename = filename,
                openMode = openMode,
             };
             bool _engineResult = InternalUnsafeMethods.Open()(ObjectPtr, _args);
             return _engineResult;
        }

        /// <description>
        /// Get the type info object for the FileStreamObject class.
        /// </description>
        /// <returns>The type info object for FileStreamObject</returns>
        public static EngineTypeInfo StaticGetType() {
             InternalUnsafeMethods.StaticGetType__Args _args = new InternalUnsafeMethods.StaticGetType__Args() {
             };
             IntPtr _engineResult = InternalUnsafeMethods.StaticGetType()(_args);
             return new EngineTypeInfo(_engineResult);
        }
    }
}