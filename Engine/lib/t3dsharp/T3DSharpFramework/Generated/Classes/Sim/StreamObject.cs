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
    /// <summary>Base class for working with streams.</summary>
    /// <description>
    /// You do not instantiate a StreamObject directly.  Instead, it is used as part of a FileStreamObject and ZipObject to support working with uncompressed and compressed files respectively.
    /// </description>
    /// <code>
    /// // You cannot actually declare a StreamObject
    /// // Instead, use the derived class "FileStreamObject"
    /// %fsObject = FileStreamObject();
    /// </code>
    /// <see cref="FileStreamObject for the derived class usable in script." />
    /// <see cref="ZipObject where StreamObject is used to read and write to files within a zip archive." />
    public unsafe class StreamObject : SimObject {
        public StreamObject(bool pRegister = false) 
            : base(pRegister) {
        }
        
        public StreamObject(string pName, bool pRegister) 
            : this(false) {
            Name = pName;
            if (pRegister) {
                RegisterObject();
            }
        }
        
        public StreamObject(string pName) 
            : this(pName, false) {
        }
        
        public StreamObject(string pName, string pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(Engine.Sim.FindObject<SimObject>(pParent));
        }
        
        public StreamObject(string pName, SimObject pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(pParent);
        }
        
        public StreamObject(SimObject pObj) 
            : base(pObj) {
        }
        
        public StreamObject(IntPtr pObj) 
            : base(pObj) {
        }
        
		protected override void CreateObjectPtr()
		{
			ObjectPtr = InternalUnsafeMethods.Create()(new InternalUnsafeMethods.Create__Args());
		}

        #region UnsafeNativeMethods
        new internal struct InternalUnsafeMethods {
            [StructLayout(LayoutKind.Sequential)]
            internal struct CopyFrom__Args
            {
                internal IntPtr other;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            [return: MarshalAs(UnmanagedType.I1)]
            internal delegate bool _CopyFrom(IntPtr _this, CopyFrom__Args args);
            private static _CopyFrom _CopyFromFunc;
            internal static _CopyFrom CopyFrom() {
                if (_CopyFromFunc == null) {
                    _CopyFromFunc =
                        (_CopyFrom)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnStreamObject_copyFrom"), typeof(_CopyFrom));
                }
                
                return _CopyFromFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct WriteString__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string _string;
                internal int maxLength;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _WriteString(IntPtr _this, WriteString__Args args);
            private static _WriteString _WriteStringFunc;
            internal static _WriteString WriteString() {
                if (_WriteStringFunc == null) {
                    _WriteStringFunc =
                        (_WriteString)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnStreamObject_writeString"), typeof(_WriteString));
                }
                
                return _WriteStringFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct WriteLongString__Args
            {
                internal int maxLength;
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string _string;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _WriteLongString(IntPtr _this, WriteLongString__Args args);
            private static _WriteLongString _WriteLongStringFunc;
            internal static _WriteLongString WriteLongString() {
                if (_WriteLongStringFunc == null) {
                    _WriteLongStringFunc =
                        (_WriteLongString)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnStreamObject_writeLongString"), typeof(_WriteLongString));
                }
                
                return _WriteLongStringFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct ReadLongString__Args
            {
                internal int maxLength;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            
            internal delegate IntPtr _ReadLongString(IntPtr _this, ReadLongString__Args args);
            private static _ReadLongString _ReadLongStringFunc;
            internal static _ReadLongString ReadLongString() {
                if (_ReadLongStringFunc == null) {
                    _ReadLongStringFunc =
                        (_ReadLongString)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnStreamObject_readLongString"), typeof(_ReadLongString));
                }
                
                return _ReadLongStringFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct ReadString__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            
            internal delegate IntPtr _ReadString(IntPtr _this, ReadString__Args args);
            private static _ReadString _ReadStringFunc;
            internal static _ReadString ReadString() {
                if (_ReadStringFunc == null) {
                    _ReadStringFunc =
                        (_ReadString)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnStreamObject_readString"), typeof(_ReadString));
                }
                
                return _ReadStringFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct ReadSTString__Args
            {
                [MarshalAs(UnmanagedType.I1)]
                internal bool caseSensitive;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            
            internal delegate IntPtr _ReadSTString(IntPtr _this, ReadSTString__Args args);
            private static _ReadSTString _ReadSTStringFunc;
            internal static _ReadSTString ReadSTString() {
                if (_ReadSTStringFunc == null) {
                    _ReadSTStringFunc =
                        (_ReadSTString)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnStreamObject_readSTString"), typeof(_ReadSTString));
                }
                
                return _ReadSTStringFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct WriteLine__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string line;
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
                                "fnStreamObject_writeLine"), typeof(_WriteLine));
                }
                
                return _WriteLineFunc;
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
                                "fnStreamObject_readLine"), typeof(_ReadLine));
                }
                
                return _ReadLineFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct GetStreamSize__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate int _GetStreamSize(IntPtr _this, GetStreamSize__Args args);
            private static _GetStreamSize _GetStreamSizeFunc;
            internal static _GetStreamSize GetStreamSize() {
                if (_GetStreamSizeFunc == null) {
                    _GetStreamSizeFunc =
                        (_GetStreamSize)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnStreamObject_getStreamSize"), typeof(_GetStreamSize));
                }
                
                return _GetStreamSizeFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct SetPosition__Args
            {
                internal int newPosition;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            [return: MarshalAs(UnmanagedType.I1)]
            internal delegate bool _SetPosition(IntPtr _this, SetPosition__Args args);
            private static _SetPosition _SetPositionFunc;
            internal static _SetPosition SetPosition() {
                if (_SetPositionFunc == null) {
                    _SetPositionFunc =
                        (_SetPosition)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnStreamObject_setPosition"), typeof(_SetPosition));
                }
                
                return _SetPositionFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct GetPosition__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate int _GetPosition(IntPtr _this, GetPosition__Args args);
            private static _GetPosition _GetPositionFunc;
            internal static _GetPosition GetPosition() {
                if (_GetPositionFunc == null) {
                    _GetPositionFunc =
                        (_GetPosition)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnStreamObject_getPosition"), typeof(_GetPosition));
                }
                
                return _GetPositionFunc;
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
                                "fnStreamObject_isEOF"), typeof(_IsEOF));
                }
                
                return _IsEOFFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct IsEOS__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            [return: MarshalAs(UnmanagedType.I1)]
            internal delegate bool _IsEOS(IntPtr _this, IsEOS__Args args);
            private static _IsEOS _IsEOSFunc;
            internal static _IsEOS IsEOS() {
                if (_IsEOSFunc == null) {
                    _IsEOSFunc =
                        (_IsEOS)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnStreamObject_isEOS"), typeof(_IsEOS));
                }
                
                return _IsEOSFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct GetStatus__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            
            internal delegate IntPtr _GetStatus(IntPtr _this, GetStatus__Args args);
            private static _GetStatus _GetStatusFunc;
            internal static _GetStatus GetStatus() {
                if (_GetStatusFunc == null) {
                    _GetStatusFunc =
                        (_GetStatus)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnStreamObject_getStatus"), typeof(_GetStatus));
                }
                
                return _GetStatusFunc;
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
                                "fnStreamObject_staticGetType"), typeof(_StaticGetType));
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
                                "fnStreamObject_create"), typeof(_Create));
                }
                
                return _CreateFunc;
            }
        }
        #endregion

        /// <summary>Copy from another StreamObject into this StreamObject</summary>
        /// <description>
        /// 
        /// </description>
        /// <param name="other">The StreamObject to copy from.</param>
        /// <returns>True if the copy was successful.</returns>
        public bool CopyFrom(SimObject other) {
             InternalUnsafeMethods.CopyFrom__Args _args = new InternalUnsafeMethods.CopyFrom__Args() {
                other = other.ObjectPtr,
             };
             bool _engineResult = InternalUnsafeMethods.CopyFrom()(ObjectPtr, _args);
             return _engineResult;
        }

        /// <summary>Write out a string with a default maximum length of 256 characters.</summary>
        /// <description>
        /// 
        /// </description>
        /// <param name="string">The string to write out to the stream</param>
        /// <param name="maxLength">The maximum string length to write out with a default of 256 characters.  This value should not be larger than 256 as it is written to the stream as a single byte.</param>
        /// <see cref="readString()" />
        /// <remarks> When working with these particular string reading and writing methods, the stream begins with the length of the string followed by the string itself, and does not include a NULL terminator.</remarks>
        public void WriteString(string _string, int maxLength = 256) {
             InternalUnsafeMethods.WriteString__Args _args = new InternalUnsafeMethods.WriteString__Args() {
                _string = _string,
                maxLength = maxLength,
             };
             InternalUnsafeMethods.WriteString()(ObjectPtr, _args);
        }

        /// <summary>Write out a string up to the maximum number of characters.</summary>
        /// <description>
        /// 
        /// </description>
        /// <param name="maxLength">The maximum number of characters that will be written.</param>
        /// <param name="string">The string to write out to the stream.</param>
        /// <see cref="readLongString()" />
        /// <remarks> When working with these particular string reading and writing methods, the stream begins with the length of the string followed by the string itself, and does not include a NULL terminator.</remarks>
        public void WriteLongString(int maxLength, string _string) {
             InternalUnsafeMethods.WriteLongString__Args _args = new InternalUnsafeMethods.WriteLongString__Args() {
                maxLength = maxLength,
                _string = _string,
             };
             InternalUnsafeMethods.WriteLongString()(ObjectPtr, _args);
        }

        /// <summary>Read in a string up to the given maximum number of characters.</summary>
        /// <description>
        /// 
        /// </description>
        /// <param name="maxLength">The maximum number of characters to read in.</param>
        /// <returns>The string that was read from the stream.</returns>
        /// <see cref="writeLongString()" />
        /// <remarks> When working with these particular string reading and writing methods, the stream begins with the length of the string followed by the string itself, and does not include a NULL terminator.</remarks>
        public string ReadLongString(int maxLength) {
             InternalUnsafeMethods.ReadLongString__Args _args = new InternalUnsafeMethods.ReadLongString__Args() {
                maxLength = maxLength,
             };
             IntPtr _engineResult = InternalUnsafeMethods.ReadLongString()(ObjectPtr, _args);
             return StringMarshal.IntPtrToUtf8String(_engineResult);
        }

        /// <summary>Read a string up to a maximum of 256 characters</summary>
        /// <returns>The string that was read from the stream.</returns>
        /// <see cref="writeString()" />
        /// <remarks> When working with these particular string reading and writing methods, the stream begins with the length of the string followed by the string itself, and does not include a NULL terminator.</remarks>
        public string ReadString() {
             InternalUnsafeMethods.ReadString__Args _args = new InternalUnsafeMethods.ReadString__Args() {
             };
             IntPtr _engineResult = InternalUnsafeMethods.ReadString()(ObjectPtr, _args);
             return StringMarshal.IntPtrToUtf8String(_engineResult);
        }

        /// <summary>Read in a string and place it on the string table.</summary>
        /// <description>
        /// 
        /// </description>
        /// <param name="caseSensitive">If false then case will not be taken into account when attempting to match the read in string with what is already in the string table.</param>
        /// <returns>The string that was read from the stream.</returns>
        /// <see cref="writeString()" />
        /// <remarks> When working with these particular string reading and writing methods, the stream begins with the length of the string followed by the string itself, and does not include a NULL terminator.</remarks>
        public string ReadSTString(bool caseSensitive = false) {
             InternalUnsafeMethods.ReadSTString__Args _args = new InternalUnsafeMethods.ReadSTString__Args() {
                caseSensitive = caseSensitive,
             };
             IntPtr _engineResult = InternalUnsafeMethods.ReadSTString()(ObjectPtr, _args);
             return StringMarshal.IntPtrToUtf8String(_engineResult);
        }

        /// <summary>Write a line to the stream, if it was opened for writing.</summary>
        /// <description>
        /// There is no limit as to what kind of data you can write. Any format and data is allowable, not just text. Be careful of what you write, as whitespace, current values, and literals will be preserved.
        /// </description>
        /// <param name="line">The data we are writing out to file.</param>
        /// <code>
        /// // Create a file stream
        /// %fsObject = new FileStreamObject();
        /// 
        /// // Open the file for writing
        /// // If it does not exist, it is created. If it does exist, the file is cleared
        /// %fsObject.open("./test.txt", "write");
        /// 
        /// // Write a line to the file
        /// %fsObject.writeLine("Hello World");
        /// 
        /// // Write another line to the file
        /// %fsObject.writeLine("Documentation Rocks!");
        /// 
        /// // Always remember to close a file stream when finished
        /// %fsObject.close();
        /// </code>
        /// <see cref="readLine()" />
        public void WriteLine(string line) {
             InternalUnsafeMethods.WriteLine__Args _args = new InternalUnsafeMethods.WriteLine__Args() {
                line = line,
             };
             InternalUnsafeMethods.WriteLine()(ObjectPtr, _args);
        }

        /// <summary>Read a line from the stream.</summary>
        /// <description>
        /// Emphasis on *line*, as in you cannot parse individual characters or chunks of data. There is no limitation as to what kind of data you can read.
        /// </description>
        /// <code>
        /// // Create a file stream object for reading
        /// // This file contains the following two lines:
        /// // HelloWorld
        /// // HelloWorld
        /// %fsObject = new FileStreamObject();
        /// 
        /// %fsObject.open("./test.txt", "read");
        /// 
        /// // Read in the first line
        /// %line = %fsObject.readLine();
        /// 
        /// // Print the line we just read
        /// echo(%line);
        /// 
        /// // Always remember to close a file stream when finished
        /// %fsObject.close();
        /// </code>
        /// <returns>String containing the line of data that was just read</returns>
        /// <see cref="writeLine()" />
        public string ReadLine() {
             InternalUnsafeMethods.ReadLine__Args _args = new InternalUnsafeMethods.ReadLine__Args() {
             };
             IntPtr _engineResult = InternalUnsafeMethods.ReadLine()(ObjectPtr, _args);
             return StringMarshal.IntPtrToUtf8String(_engineResult);
        }

        /// <summary>Gets the size of the stream</summary>
        /// <description>
        /// The size is dependent on the type of stream being used. If it is a file stream, returned value will be the size of the file. If it is a memory stream, it will be the size of the allocated buffer.
        /// </description>
        /// <code>
        /// // Create a file stream object for reading
        /// %fsObject = new FileStreamObject();
        /// 
        /// // Open a file for reading
        /// // This file contains the following two lines:
        /// // HelloWorld
        /// // HelloWorld
        /// %fsObject.open("./test.txt", "read");
        /// 
        /// // Found out how large the file stream is
        /// // Then print it to the console
        /// // Should be 22
        /// %streamSize = %fsObject.getStreamSize();
        /// echo(%streamSize);
        /// 
        /// // Always remember to close a file stream when finished
        /// %fsObject.close();
        /// </code>
        /// <returns>Size of stream, in bytes</returns>
        public int GetStreamSize() {
             InternalUnsafeMethods.GetStreamSize__Args _args = new InternalUnsafeMethods.GetStreamSize__Args() {
             };
             int _engineResult = InternalUnsafeMethods.GetStreamSize()(ObjectPtr, _args);
             return _engineResult;
        }

        /// <summary>Gets the position in the stream</summary>
        /// <description>
        /// The easiest way to visualize this is to think of a cursor in a text file. If you have moved the cursor by five characters, the current position is 5. If you move ahead 10 more characters, the position is now 15. For StreamObject, when you read in the line the position is increased by the number of characters parsed, the null terminator, and a newline. Using setPosition allows you to skip to specific points of the file.
        /// </description>
        /// <code>
        /// // Create a file stream object for reading
        /// %fsObject = new FileStreamObject();
        /// 
        /// // Open a file for reading
        /// // This file contains the following two lines:
        /// // 11111111111
        /// // Hello World
        /// %fsObject.open("./test.txt", "read");
        /// 
        /// // Skip ahead by 12, which will bypass the first line entirely
        /// %fsObject.setPosition(12);
        /// 
        /// // Read in the next line
        /// %line = %fsObject.readLine();
        /// 
        /// // Print the line just read in, should be "Hello World"
        /// echo(%line);
        /// 
        /// // Always remember to close a file stream when finished
        /// %fsObject.close();
        /// </code>
        /// <returns>Number of bytes which stream has parsed so far, null terminators and newlines are included</returns>
        /// <see cref="getPosition()" />
        public bool SetPosition(int newPosition) {
             InternalUnsafeMethods.SetPosition__Args _args = new InternalUnsafeMethods.SetPosition__Args() {
                newPosition = newPosition,
             };
             bool _engineResult = InternalUnsafeMethods.SetPosition()(ObjectPtr, _args);
             return _engineResult;
        }

        /// <summary>Gets the position in the stream</summary>
        /// <description>
        /// The easiest way to visualize this is to think of a cursor in a text file. If you have moved the cursor by five characters, the current position is 5. If you move ahead 10 more characters, the position is now 15. For StreamObject, when you read in the line the position is increased by the number of characters parsed, the null terminator, and a newline.
        /// </description>
        /// <code>
        /// // Create a file stream object for reading
        /// %fsObject = new FileStreamObject();
        /// 
        /// // Open a file for reading
        /// // This file contains two lines of text repeated:
        /// // Hello World
        /// // Hello World
        /// %fsObject.open("./test.txt", "read");
        /// 
        /// // Read in the first line
        /// %line = %fsObject.readLine();
        /// 
        /// // Get the position of the stream
        /// %position = %fsObject.getPosition();
        /// 
        /// // Print the current position
        /// // Should be 13, 10 for the words, 1 for the space, 1 for the null terminator, and 1 for the newline
        /// echo(%position);
        /// 
        /// // Always remember to close a file stream when finished
        /// %fsObject.close();
        /// </code>
        /// <returns>Number of bytes which stream has parsed so far, null terminators and newlines are included</returns>
        /// <see cref="setPosition()" />
        public int GetPosition() {
             InternalUnsafeMethods.GetPosition__Args _args = new InternalUnsafeMethods.GetPosition__Args() {
             };
             int _engineResult = InternalUnsafeMethods.GetPosition()(ObjectPtr, _args);
             return _engineResult;
        }

        /// <summary>Tests if the stream has reached the end of the file</summary>
        /// <description>
        /// This is an alternative name for isEOS. Both functions are interchangeable. This simply exists for those familiar with some C++ file I/O standards.
        /// </description>
        /// <code>
        /// // Create a file stream object for reading
        /// %fsObject = new FileStreamObject();
        /// 
        /// // Open a file for reading
        /// %fsObject.open("./test.txt", "read");
        /// 
        /// // Keep reading until we reach the end of the file
        /// while( !%fsObject.isEOF() )
        /// {
        ///    %line = %fsObject.readLine();
        ///    echo(%line);
        /// }
        /// // Made it to the end
        /// echo("Finished reading file");
        /// 
        /// // Always remember to close a file stream when finished
        /// %fsObject.close();
        /// </code>
        /// <returns>True if the parser has reached the end of the file, false otherwise</returns>
        /// <see cref="isEOS()" />
        public bool IsEOF() {
             InternalUnsafeMethods.IsEOF__Args _args = new InternalUnsafeMethods.IsEOF__Args() {
             };
             bool _engineResult = InternalUnsafeMethods.IsEOF()(ObjectPtr, _args);
             return _engineResult;
        }

        /// <summary>Tests if the stream has reached the end of the file</summary>
        /// <description>
        /// This is an alternative name for isEOF. Both functions are interchangeable. This simply exists for those familiar with some C++ file I/O standards.
        /// </description>
        /// <code>
        /// // Create a file stream object for reading
        /// %fsObject = new FileStreamObject();
        /// 
        /// // Open a file for reading
        /// %fsObject.open("./test.txt", "read");
        /// 
        /// // Keep reading until we reach the end of the file
        /// while( !%fsObject.isEOS() )
        /// {
        ///    %line = %fsObject.readLine();
        ///    echo(%line);
        /// }
        /// // Made it to the end
        /// echo("Finished reading file");
        /// 
        /// // Always remember to close a file stream when finished
        /// %fsObject.close();
        /// </code>
        /// <returns>True if the parser has reached the end of the file, false otherwise</returns>
        /// <see cref="isEOF()" />
        public bool IsEOS() {
             InternalUnsafeMethods.IsEOS__Args _args = new InternalUnsafeMethods.IsEOS__Args() {
             };
             bool _engineResult = InternalUnsafeMethods.IsEOS()(ObjectPtr, _args);
             return _engineResult;
        }

        /// <summary>Gets a printable string form of the stream's status</summary>
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
        /// // Get the status and print it
        /// %status = %fsObject.getStatus();
        /// echo(%status);
        /// 
        /// // Always remember to close a file stream when finished
        /// %fsObject.close();
        /// </code>
        /// <returns>String containing status constant, one of the following:
        /// 
        /// 	OK - Stream is active and no file errors
        /// 
        /// 	IOError - Something went wrong during read or writing the stream
        /// 
        /// 	EOS - End of Stream reached (mostly for reads)
        /// 
        /// 	IllegalCall - An unsupported operation used.  Always w/ accompanied by AssertWarn
        /// 
        ///   Closed - Tried to operate on a closed stream (or detached filter)
        /// 
        /// 	UnknownError - Catch all for an error of some kind
        /// 
        /// 	Invalid - Entire stream is invalid</returns>
        public string GetStatus() {
             InternalUnsafeMethods.GetStatus__Args _args = new InternalUnsafeMethods.GetStatus__Args() {
             };
             IntPtr _engineResult = InternalUnsafeMethods.GetStatus()(ObjectPtr, _args);
             return StringMarshal.IntPtrToUtf8String(_engineResult);
        }

        /// <description>
        /// Get the type info object for the StreamObject class.
        /// </description>
        /// <returns>The type info object for StreamObject</returns>
        public static EngineTypeInfo StaticGetType() {
             InternalUnsafeMethods.StaticGetType__Args _args = new InternalUnsafeMethods.StaticGetType__Args() {
             };
             IntPtr _engineResult = InternalUnsafeMethods.StaticGetType()(_args);
             return new EngineTypeInfo(_engineResult);
        }
    }
}