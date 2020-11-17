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
    /// <summary>This class is responsible opening, reading, creating, and saving file contents.</summary>
    /// <description>
    /// FileObject acts as the interface with OS level files.  You create a new FileObject and pass into it a file's path and name.  The FileObject class supports three distinct operations for working with files:
    /// 
    /// <table border='1' cellpadding='1'><tr><th>Operation</th><th>%FileObject Method</th><th>Description</th></tr><tr><td>Read</td><td>openForRead()</td><td>Open the file for reading</td></tr><tr><td>Write</td><td>openForWrite()</td><td>Open the file for writing to and replace its contents (if any)</td></tr><tr><td>Append</td><td>openForAppend()</td><td>Open the file and start writing at its end</td></tr></table>
    /// 
    /// Before you may work with a file you need to use one of the three above methods on the FileObject.
    /// </description>
    /// <code>
    /// // Create a file object for writing
    /// %fileWrite = new FileObject();
    /// 
    /// // Open a file to write to, if it does not exist it will be created
    /// %result = %fileWrite.OpenForWrite("./test.txt");
    /// 
    /// if ( %result )
    /// {
    ///    // Write a line to the text files
    ///    %fileWrite.writeLine("READ. READ CODE. CODE");
    /// }
    /// 
    /// // Close the file when finished
    /// %fileWrite.close();
    /// 
    /// // Cleanup the file object
    /// %fileWrite.delete();
    /// 
    /// 
    /// // Create a file object for reading
    /// %fileRead = new FileObject();
    /// 
    /// // Open a text file, if it exists
    /// %result = %fileRead.OpenForRead("./test.txt");
    /// 
    /// if ( %result )
    /// {
    ///    // Read in the first line
    ///    %line = %fileRead.readline();
    /// 
    ///    // Print the line we just read
    ///    echo(%line);
    /// }
    /// 
    /// // Close the file when finished
    /// %fileRead.close();
    /// 
    /// // Cleanup the file object
    /// %fileRead.delete();
    /// </code>
    public unsafe class FileObject : SimObject {
        public FileObject(bool pRegister = false) 
            : base(pRegister) {
        }
        
        public FileObject(string pName, bool pRegister) 
            : this(false) {
            Name = pName;
            if (pRegister) {
                RegisterObject();
            }
        }
        
        public FileObject(string pName) 
            : this(pName, false) {
        }
        
        public FileObject(string pName, string pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(Engine.Sim.FindObject<SimObject>(pParent));
        }
        
        public FileObject(string pName, SimObject pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(pParent);
        }
        
        public FileObject(SimObject pObj) 
            : base(pObj) {
        }
        
        public FileObject(IntPtr pObj) 
            : base(pObj) {
        }
        
		protected override void CreateObjectPtr()
		{
			ObjectPtr = InternalUnsafeMethods.Create()(new InternalUnsafeMethods.Create__Args());
		}

        #region UnsafeNativeMethods
        new internal struct InternalUnsafeMethods {
            [StructLayout(LayoutKind.Sequential)]
            internal struct WriteObject__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string simName;
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string objName;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _WriteObject(IntPtr _this, WriteObject__Args args);
            private static _WriteObject _WriteObjectFunc;
            internal static _WriteObject WriteObject() {
                if (_WriteObjectFunc == null) {
                    _WriteObjectFunc =
                        (_WriteObject)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnFileObject_writeObject"), typeof(_WriteObject));
                }
                
                return _WriteObjectFunc;
            }

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
                                "fnFileObject_close"), typeof(_Close));
                }
                
                return _CloseFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct WriteLine__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string text;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _WriteLine(IntPtr _this, WriteLine__Args args);
            private static _WriteLine _WriteLineFunc;
            internal static _WriteLine WriteLine() {
                if (_WriteLineFunc == null) {
                    _WriteLineFunc =
                        (_WriteLine)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnFileObject_writeLine"), typeof(_WriteLine));
                }
                
                return _WriteLineFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct PeekLine__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            
            internal delegate IntPtr _PeekLine(IntPtr _this, PeekLine__Args args);
            private static _PeekLine _PeekLineFunc;
            internal static _PeekLine PeekLine() {
                if (_PeekLineFunc == null) {
                    _PeekLineFunc =
                        (_PeekLine)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnFileObject_peekLine"), typeof(_PeekLine));
                }
                
                return _PeekLineFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct ReadLine__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            
            internal delegate IntPtr _ReadLine(IntPtr _this, ReadLine__Args args);
            private static _ReadLine _ReadLineFunc;
            internal static _ReadLine ReadLine() {
                if (_ReadLineFunc == null) {
                    _ReadLineFunc =
                        (_ReadLine)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnFileObject_readLine"), typeof(_ReadLine));
                }
                
                return _ReadLineFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct IsEOF__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            [return: MarshalAs(UnmanagedType.I1)]
            internal delegate bool _IsEOF(IntPtr _this, IsEOF__Args args);
            private static _IsEOF _IsEOFFunc;
            internal static _IsEOF IsEOF() {
                if (_IsEOFFunc == null) {
                    _IsEOFFunc =
                        (_IsEOF)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnFileObject_isEOF"), typeof(_IsEOF));
                }
                
                return _IsEOFFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct OpenForAppend__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string filename;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            [return: MarshalAs(UnmanagedType.I1)]
            internal delegate bool _OpenForAppend(IntPtr _this, OpenForAppend__Args args);
            private static _OpenForAppend _OpenForAppendFunc;
            internal static _OpenForAppend OpenForAppend() {
                if (_OpenForAppendFunc == null) {
                    _OpenForAppendFunc =
                        (_OpenForAppend)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnFileObject_openForAppend"), typeof(_OpenForAppend));
                }
                
                return _OpenForAppendFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct OpenForWrite__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string filename;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            [return: MarshalAs(UnmanagedType.I1)]
            internal delegate bool _OpenForWrite(IntPtr _this, OpenForWrite__Args args);
            private static _OpenForWrite _OpenForWriteFunc;
            internal static _OpenForWrite OpenForWrite() {
                if (_OpenForWriteFunc == null) {
                    _OpenForWriteFunc =
                        (_OpenForWrite)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnFileObject_openForWrite"), typeof(_OpenForWrite));
                }
                
                return _OpenForWriteFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct OpenForRead__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string filename;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            [return: MarshalAs(UnmanagedType.I1)]
            internal delegate bool _OpenForRead(IntPtr _this, OpenForRead__Args args);
            private static _OpenForRead _OpenForReadFunc;
            internal static _OpenForRead OpenForRead() {
                if (_OpenForReadFunc == null) {
                    _OpenForReadFunc =
                        (_OpenForRead)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnFileObject_openForRead"), typeof(_OpenForRead));
                }
                
                return _OpenForReadFunc;
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
                                "fnFileObject_staticGetType"), typeof(_StaticGetType));
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
                                "fnFileObject_create"), typeof(_Create));
                }
                
                return _CreateFunc;
            }
        }
        #endregion

        /// <description>
        /// FileObject.writeObject(SimObject, object prepend)
        /// </description>
        public void WriteObject(string simName, string objName = "") {
             InternalUnsafeMethods.WriteObject__Args _args = new InternalUnsafeMethods.WriteObject__Args() {
                simName = simName,
                objName = objName,
             };
             InternalUnsafeMethods.WriteObject()(ObjectPtr, _args);
        }

        /// <summary>Close the file.</summary>
        /// <description>
        /// It is EXTREMELY important that you call this function when you are finished reading or writing to a file. Failing to do so is not only a bad programming practice, but could result in bad data or corrupt files. Remember: Open, Read/Write, Close, Delete...in that order!
        /// </description>
        /// <code>
        /// // Create a file object for reading
        /// %fileRead = new FileObject();
        /// 
        /// // Open a text file, if it exists
        /// %fileRead.OpenForRead("./test.txt");
        /// 
        /// // Peek the first line
        /// %line = %fileRead.peekLine();
        /// 
        /// // Print the line we just peeked
        /// echo(%line);
        /// // If we peek again...
        /// %line = %fileRead.peekLine();
        /// 
        /// // We will get the same output as the first time
        /// // since the stream did not move forward
        /// echo(%line);
        /// 
        /// // Close the file when finished
        /// %fileWrite.close();
        /// 
        /// // Cleanup the file object
        /// %fileWrite.delete();
        /// </code>
        public void Close() {
             InternalUnsafeMethods.Close__Args _args = new InternalUnsafeMethods.Close__Args() {
             };
             InternalUnsafeMethods.Close()(ObjectPtr, _args);
        }

        /// <summary>Write a line to the file, if it was opened for writing.</summary>
        /// <description>
        /// There is no limit as to what kind of text you can write. Any format and data is allowable, not just text. Be careful of what you write, as whitespace, current values, and literals will be preserved.
        /// </description>
        /// <param name="text">The data we are writing out to file.</param>
        /// <code>
        /// // Create a file object for writing
        /// %fileWrite = new FileObject();
        /// 
        /// // Open a file to write to, if it does not exist it will be created
        /// %fileWrite.OpenForWrite("./test.txt");
        /// 
        /// // Write a line to the text files
        /// %fileWrite.writeLine("READ. READ CODE. CODE");
        /// </code>
        /// <returns>True if file was successfully opened, false otherwise</returns>
        public void WriteLine(string text) {
             InternalUnsafeMethods.WriteLine__Args _args = new InternalUnsafeMethods.WriteLine__Args() {
                text = text,
             };
             InternalUnsafeMethods.WriteLine()(ObjectPtr, _args);
        }

        /// <summary>Read a line from the file without moving the stream position.</summary>
        /// <description>
        /// Emphasis on *line*, as in you cannot parse individual characters or chunks of data.  There is no limitation as to what kind of data you can read. Unlike readLine, the parser does not move forward after reading.
        /// </description>
        /// <param name="filename">Path, name, and extension of file to be read</param>
        /// <code>
        /// // Create a file object for reading
        /// %fileRead = new FileObject();
        /// 
        /// // Open a text file, if it exists
        /// %fileRead.OpenForRead("./test.txt");
        /// 
        /// // Peek the first line
        /// %line = %fileRead.peekLine();
        /// 
        /// // Print the line we just peeked
        /// echo(%line);
        /// // If we peek again...
        /// %line = %fileRead.peekLine();
        /// 
        /// // We will get the same output as the first time
        /// // since the stream did not move forward
        /// echo(%line);
        /// </code>
        /// <returns>String containing the line of data that was just peeked</returns>
        public string PeekLine() {
             InternalUnsafeMethods.PeekLine__Args _args = new InternalUnsafeMethods.PeekLine__Args() {
             };
             IntPtr _engineResult = InternalUnsafeMethods.PeekLine()(ObjectPtr, _args);
             return StringMarshal.IntPtrToUtf8String(_engineResult);
        }

        /// <summary>Read a line from file.</summary>
        /// <description>
        /// Emphasis on *line*, as in you cannot parse individual characters or chunks of data.  There is no limitation as to what kind of data you can read.
        /// </description>
        /// <code>
        /// // Create a file object for reading
        /// %fileRead = new FileObject();
        /// 
        /// // Open a text file, if it exists
        /// %fileRead.OpenForRead("./test.txt");
        /// 
        /// // Read in the first line
        /// %line = %fileRead.readline();
        /// 
        /// // Print the line we just read
        /// echo(%line);
        /// </code>
        /// <returns>String containing the line of data that was just read</returns>
        public string ReadLine() {
             InternalUnsafeMethods.ReadLine__Args _args = new InternalUnsafeMethods.ReadLine__Args() {
             };
             IntPtr _engineResult = InternalUnsafeMethods.ReadLine()(ObjectPtr, _args);
             return StringMarshal.IntPtrToUtf8String(_engineResult);
        }

        /// <summary>Determines if the parser for this FileObject has reached the end of the file</summary>
        /// <description>
        /// 
        /// </description>
        /// <code>
        /// // Create a file object for reading
        /// %fileRead = new FileObject();
        /// 
        /// // Open a text file, if it exists
        /// %fileRead.OpenForRead("./test.txt");
        /// 
        /// // Keep reading until we reach the end of the file
        /// while( !%fileRead.isEOF() )
        /// {
        ///    %line = %fileRead.readline();
        ///    echo(%line);
        /// }
        /// 
        /// // Made it to the end
        /// echo("Finished reading file");
        /// </code>
        /// <returns>True if the parser has reached the end of the file, false otherwise</returns>
        public bool IsEOF() {
             InternalUnsafeMethods.IsEOF__Args _args = new InternalUnsafeMethods.IsEOF__Args() {
             };
             bool _engineResult = InternalUnsafeMethods.IsEOF()(ObjectPtr, _args);
             return _engineResult;
        }

        /// <summary>Open a specified file for writing, adding data to the end of the file</summary>
        /// <description>
        /// There is no limit as to what kind of file you can write. Any format and data is allowable, not just text. Unlike openForWrite(), which will erase an existing file if it is opened, openForAppend() preserves data in an existing file and adds to it.
        /// </description>
        /// <param name="filename">Path, name, and extension of file to append to</param>
        /// <code>
        /// // Create a file object for writing
        /// %fileWrite = new FileObject();
        /// 
        /// // Open a file to write to, if it does not exist it will be created
        /// // If it does exist, whatever we write will be added to the end
        /// %result = %fileWrite.OpenForAppend("./test.txt");
        /// </code>
        /// <returns>True if file was successfully opened, false otherwise</returns>
        public bool OpenForAppend(string filename) {
             InternalUnsafeMethods.OpenForAppend__Args _args = new InternalUnsafeMethods.OpenForAppend__Args() {
                filename = filename,
             };
             bool _engineResult = InternalUnsafeMethods.OpenForAppend()(ObjectPtr, _args);
             return _engineResult;
        }

        /// <summary>Open a specified file for writing</summary>
        /// <description>
        /// There is no limit as to what kind of file you can write. Any format and data is allowable, not just text
        /// </description>
        /// <param name="filename">Path, name, and extension of file to write to</param>
        /// <code>
        /// // Create a file object for writing
        /// %fileWrite = new FileObject();
        /// 
        /// // Open a file to write to, if it does not exist it will be created
        /// %result = %fileWrite.OpenForWrite("./test.txt");
        /// </code>
        /// <returns>True if file was successfully opened, false otherwise</returns>
        public bool OpenForWrite(string filename) {
             InternalUnsafeMethods.OpenForWrite__Args _args = new InternalUnsafeMethods.OpenForWrite__Args() {
                filename = filename,
             };
             bool _engineResult = InternalUnsafeMethods.OpenForWrite()(ObjectPtr, _args);
             return _engineResult;
        }

        /// <summary>Open a specified file for reading</summary>
        /// <description>
        /// There is no limit as to what kind of file you can read. Any format and data contained within is accessible, not just text
        /// </description>
        /// <param name="filename">Path, name, and extension of file to be read</param>
        /// <code>
        /// // Create a file object for reading
        /// %fileRead = new FileObject();
        /// 
        /// // Open a text file, if it exists
        /// %result = %fileRead.OpenForRead("./test.txt");
        /// </code>
        /// <returns>True if file was successfully opened, false otherwise</returns>
        public bool OpenForRead(string filename) {
             InternalUnsafeMethods.OpenForRead__Args _args = new InternalUnsafeMethods.OpenForRead__Args() {
                filename = filename,
             };
             bool _engineResult = InternalUnsafeMethods.OpenForRead()(ObjectPtr, _args);
             return _engineResult;
        }

        /// <description>
        /// Get the type info object for the FileObject class.
        /// </description>
        /// <returns>The type info object for FileObject</returns>
        public static EngineTypeInfo StaticGetType() {
             InternalUnsafeMethods.StaticGetType__Args _args = new InternalUnsafeMethods.StaticGetType__Args() {
             };
             IntPtr _engineResult = InternalUnsafeMethods.StaticGetType()(_args);
             return new EngineTypeInfo(_engineResult);
        }
    }
}