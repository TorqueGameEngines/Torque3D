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
    /// <summary>Store a list of chat messages.</summary>
    /// <description>
    /// This is responsible for managing messages which appear in the chat HUD, not the actual control rendered to the screen
    /// </description>
    /// <code>
    /// // Declare ChatHud, which is what will display the actual chat from a MessageVector
    /// new GuiMessageVectorCtrl(ChatHud) {
    ///    profile = "ChatHudMessageProfile";
    ///    horizSizing = "width";
    ///    vertSizing = "height";
    ///    position = "1 1";
    ///    extent = "252 16";
    ///    minExtent = "8 8";
    ///    visible = "1";
    ///    helpTag = "0";
    ///    lineSpacing = "0";
    ///    lineContinuedIndex = "10";
    ///    matchColor = "0 0 255 255";
    ///    maxColorIndex = "5";
    /// };
    /// 
    /// // All messages are stored in this HudMessageVector, the actual
    /// // MainChatHud only displays the contents of this vector.
    /// new MessageVector(HudMessageVector);
    /// 
    /// // Attach the MessageVector to the chat control
    /// chatHud.attach(HudMessageVector);
    /// </code>
    /// <see cref="GuiMessageVectorCtrl for more details on how this is used." />
    public unsafe class MessageVector : SimObject {
        public MessageVector(bool pRegister = false) 
            : base(pRegister) {
        }
        
        public MessageVector(string pName, bool pRegister) 
            : this(false) {
            Name = pName;
            if (pRegister) {
                RegisterObject();
            }
        }
        
        public MessageVector(string pName) 
            : this(pName, false) {
        }
        
        public MessageVector(string pName, string pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(Engine.Sim.FindObject<SimObject>(pParent));
        }
        
        public MessageVector(string pName, SimObject pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(pParent);
        }
        
        public MessageVector(SimObject pObj) 
            : base(pObj) {
        }
        
        public MessageVector(IntPtr pObj) 
            : base(pObj) {
        }
        
		protected override void CreateObjectPtr()
		{
			ObjectPtr = InternalUnsafeMethods.Create()(new InternalUnsafeMethods.Create__Args());
		}

        #region UnsafeNativeMethods
        new internal struct InternalUnsafeMethods {
            [StructLayout(LayoutKind.Sequential)]
            internal struct GetLineTag__Args
            {
                internal int pos;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate int _GetLineTag(IntPtr _this, GetLineTag__Args args);
            private static _GetLineTag _GetLineTagFunc;
            internal static _GetLineTag GetLineTag() {
                if (_GetLineTagFunc == null) {
                    _GetLineTagFunc =
                        (_GetLineTag)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnMessageVector_getLineTag"), typeof(_GetLineTag));
                }
                
                return _GetLineTagFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct GetLineText__Args
            {
                internal int pos;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            
            internal delegate IntPtr _GetLineText(IntPtr _this, GetLineText__Args args);
            private static _GetLineText _GetLineTextFunc;
            internal static _GetLineText GetLineText() {
                if (_GetLineTextFunc == null) {
                    _GetLineTextFunc =
                        (_GetLineText)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnMessageVector_getLineText"), typeof(_GetLineText));
                }
                
                return _GetLineTextFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct GetLineIndexByTag__Args
            {
                internal int tag;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate int _GetLineIndexByTag(IntPtr _this, GetLineIndexByTag__Args args);
            private static _GetLineIndexByTag _GetLineIndexByTagFunc;
            internal static _GetLineIndexByTag GetLineIndexByTag() {
                if (_GetLineIndexByTagFunc == null) {
                    _GetLineIndexByTagFunc =
                        (_GetLineIndexByTag)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnMessageVector_getLineIndexByTag"), typeof(_GetLineIndexByTag));
                }
                
                return _GetLineIndexByTagFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct GetLineTextByTag__Args
            {
                internal int tag;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            
            internal delegate IntPtr _GetLineTextByTag(IntPtr _this, GetLineTextByTag__Args args);
            private static _GetLineTextByTag _GetLineTextByTagFunc;
            internal static _GetLineTextByTag GetLineTextByTag() {
                if (_GetLineTextByTagFunc == null) {
                    _GetLineTextByTagFunc =
                        (_GetLineTextByTag)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnMessageVector_getLineTextByTag"), typeof(_GetLineTextByTag));
                }
                
                return _GetLineTextByTagFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct GetNumLines__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate int _GetNumLines(IntPtr _this, GetNumLines__Args args);
            private static _GetNumLines _GetNumLinesFunc;
            internal static _GetNumLines GetNumLines() {
                if (_GetNumLinesFunc == null) {
                    _GetNumLinesFunc =
                        (_GetNumLines)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnMessageVector_getNumLines"), typeof(_GetNumLines));
                }
                
                return _GetNumLinesFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct Dump__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string filename;
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string header;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _Dump(IntPtr _this, Dump__Args args);
            private static _Dump _DumpFunc;
            internal static _Dump Dump() {
                if (_DumpFunc == null) {
                    _DumpFunc =
                        (_Dump)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnMessageVector_dump"), typeof(_Dump));
                }
                
                return _DumpFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct DeleteLine__Args
            {
                internal int deletePos;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            [return: MarshalAs(UnmanagedType.I1)]
            internal delegate bool _DeleteLine(IntPtr _this, DeleteLine__Args args);
            private static _DeleteLine _DeleteLineFunc;
            internal static _DeleteLine DeleteLine() {
                if (_DeleteLineFunc == null) {
                    _DeleteLineFunc =
                        (_DeleteLine)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnMessageVector_deleteLine"), typeof(_DeleteLine));
                }
                
                return _DeleteLineFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct InsertLine__Args
            {
                internal int insertPos;
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string msg;
                internal int tag;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            [return: MarshalAs(UnmanagedType.I1)]
            internal delegate bool _InsertLine(IntPtr _this, InsertLine__Args args);
            private static _InsertLine _InsertLineFunc;
            internal static _InsertLine InsertLine() {
                if (_InsertLineFunc == null) {
                    _InsertLineFunc =
                        (_InsertLine)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnMessageVector_insertLine"), typeof(_InsertLine));
                }
                
                return _InsertLineFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct PopFrontLine__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            [return: MarshalAs(UnmanagedType.I1)]
            internal delegate bool _PopFrontLine(IntPtr _this, PopFrontLine__Args args);
            private static _PopFrontLine _PopFrontLineFunc;
            internal static _PopFrontLine PopFrontLine() {
                if (_PopFrontLineFunc == null) {
                    _PopFrontLineFunc =
                        (_PopFrontLine)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnMessageVector_popFrontLine"), typeof(_PopFrontLine));
                }
                
                return _PopFrontLineFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct PushFrontLine__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string msg;
                internal int tag;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _PushFrontLine(IntPtr _this, PushFrontLine__Args args);
            private static _PushFrontLine _PushFrontLineFunc;
            internal static _PushFrontLine PushFrontLine() {
                if (_PushFrontLineFunc == null) {
                    _PushFrontLineFunc =
                        (_PushFrontLine)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnMessageVector_pushFrontLine"), typeof(_PushFrontLine));
                }
                
                return _PushFrontLineFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct PopBackLine__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            [return: MarshalAs(UnmanagedType.I1)]
            internal delegate bool _PopBackLine(IntPtr _this, PopBackLine__Args args);
            private static _PopBackLine _PopBackLineFunc;
            internal static _PopBackLine PopBackLine() {
                if (_PopBackLineFunc == null) {
                    _PopBackLineFunc =
                        (_PopBackLine)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnMessageVector_popBackLine"), typeof(_PopBackLine));
                }
                
                return _PopBackLineFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct PushBackLine__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string msg;
                internal int tag;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _PushBackLine(IntPtr _this, PushBackLine__Args args);
            private static _PushBackLine _PushBackLineFunc;
            internal static _PushBackLine PushBackLine() {
                if (_PushBackLineFunc == null) {
                    _PushBackLineFunc =
                        (_PushBackLine)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnMessageVector_pushBackLine"), typeof(_PushBackLine));
                }
                
                return _PushBackLineFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct Clear__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _Clear(IntPtr _this, Clear__Args args);
            private static _Clear _ClearFunc;
            internal static _Clear Clear() {
                if (_ClearFunc == null) {
                    _ClearFunc =
                        (_Clear)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnMessageVector_clear"), typeof(_Clear));
                }
                
                return _ClearFunc;
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
                                "fnMessageVector_staticGetType"), typeof(_StaticGetType));
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
                                "fnMessageVector_create"), typeof(_Create));
                }
                
                return _CreateFunc;
            }
        }
        #endregion

        /// <description>
        /// Get the tag of a specified line.
        /// </description>
        /// <param name="pos">Position in vector to grab tag from</param>
        /// <code>
        /// // Remove all lines that do not have a tag value of 1.
        /// while( HudMessageVector.getNumLines())
        /// {
        ///    %tag = HudMessageVector.getLineTag(1);
        ///    if(%tag != 1)
        ///       %tag.delete();
        ///    HudMessageVector.popFrontLine();
        /// }
        /// </code>
        /// <returns>Tag value of a given line, if the position is greater than the number of lines return 0</returns>
        public int GetLineTag(int pos) {
             InternalUnsafeMethods.GetLineTag__Args _args = new InternalUnsafeMethods.GetLineTag__Args() {
                pos = pos,
             };
             int _engineResult = InternalUnsafeMethods.GetLineTag()(ObjectPtr, _args);
             return _engineResult;
        }

        /// <description>
        /// Get the text at a specified line.
        /// </description>
        /// <param name="pos">Position in vector to grab text from</param>
        /// <code>
        /// // Print a line of text at position 1.
        /// %text = HudMessageVector.getLineText(1);
        /// echo(%text);
        /// </code>
        /// <returns>Text at specified line, if the position is greater than the number of lines return ""</returns>
        public string GetLineText(int pos) {
             InternalUnsafeMethods.GetLineText__Args _args = new InternalUnsafeMethods.GetLineText__Args() {
                pos = pos,
             };
             IntPtr _engineResult = InternalUnsafeMethods.GetLineText()(ObjectPtr, _args);
             return StringMarshal.IntPtrToUtf8String(_engineResult);
        }

        /// <description>
        /// Scan through the vector, returning the line number of the first line that matches the specified tag; else returns -1 if no match was found.
        /// </description>
        /// <param name="tag">Numerical value assigned to a message when it was added or inserted</param>
        /// <code>
        /// // Locate a line of text tagged with the value "1", then delete it.
        /// %taggedLine = HudMessageVector.getLineIndexByTag(1);
        /// HudMessageVector.deleteLine(%taggedLine);
        /// </code>
        /// <returns>Line with matching tag, other wise -1</returns>
        public int GetLineIndexByTag(int tag) {
             InternalUnsafeMethods.GetLineIndexByTag__Args _args = new InternalUnsafeMethods.GetLineIndexByTag__Args() {
                tag = tag,
             };
             int _engineResult = InternalUnsafeMethods.GetLineIndexByTag()(ObjectPtr, _args);
             return _engineResult;
        }

        /// <description>
        /// Scan through the lines in the vector, returning the first line that has a matching tag.
        /// </description>
        /// <param name="tag">Numerical value assigned to a message when it was added or inserted</param>
        /// <code>
        /// // Locate text in the vector tagged with the value "1", then print it
        /// %taggedText = HudMessageVector.getLineTextByTag(1);
        /// echo(%taggedText);
        /// </code>
        /// <returns>Text from a line with matching tag, other wise ""</returns>
        public string GetLineTextByTag(int tag) {
             InternalUnsafeMethods.GetLineTextByTag__Args _args = new InternalUnsafeMethods.GetLineTextByTag__Args() {
                tag = tag,
             };
             IntPtr _engineResult = InternalUnsafeMethods.GetLineTextByTag()(ObjectPtr, _args);
             return StringMarshal.IntPtrToUtf8String(_engineResult);
        }

        /// <description>
        /// Get the number of lines in the vector.
        /// </description>
        /// <code>
        /// // Find out how many lines have been stored in HudMessageVector
        /// %chatLines = HudMessageVector.getNumLines();
        /// echo(%chatLines);
        /// </code>
        public int GetNumLines() {
             InternalUnsafeMethods.GetNumLines__Args _args = new InternalUnsafeMethods.GetNumLines__Args() {
             };
             int _engineResult = InternalUnsafeMethods.GetNumLines()(ObjectPtr, _args);
             return _engineResult;
        }

        /// <description>
        /// (string filename, string header=NULL)Dump the message vector to a file, optionally prefixing a header.
        /// </description>
        public void Dump(string filename, string header = "") {
             InternalUnsafeMethods.Dump__Args _args = new InternalUnsafeMethods.Dump__Args() {
                filename = filename,
                header = header,
             };
             InternalUnsafeMethods.Dump()(ObjectPtr, _args);
        }

        /// <description>
        /// Delete the line at the specified position.
        /// </description>
        /// <param name="deletePos">Position in the vector containing the line to be deleted</param>
        /// <code>
        /// // Delete the first line (index 0) in the vector...
        /// HudMessageVector.deleteLine(0);
        /// </code>
        /// <returns>False if deletePos is greater than the number of lines in the current vector</returns>
        public bool DeleteLine(int deletePos) {
             InternalUnsafeMethods.DeleteLine__Args _args = new InternalUnsafeMethods.DeleteLine__Args() {
                deletePos = deletePos,
             };
             bool _engineResult = InternalUnsafeMethods.DeleteLine()(ObjectPtr, _args);
             return _engineResult;
        }

        /// <description>
        /// Push a line onto the back of the list.
        /// </description>
        /// <param name="msg">Text that makes up the message</param>
        /// <param name="tag">Numerical value associated with this message, useful for searching.</param>
        /// <code>
        /// // Add the message...
        /// HudMessageVector.insertLine(1, "Hello World", 0);
        /// </code>
        /// <returns>False if insertPos is greater than the number of lines in the current vector</returns>
        public bool InsertLine(int insertPos, string msg, int tag) {
             InternalUnsafeMethods.InsertLine__Args _args = new InternalUnsafeMethods.InsertLine__Args() {
                insertPos = insertPos,
                msg = msg,
                tag = tag,
             };
             bool _engineResult = InternalUnsafeMethods.InsertLine()(ObjectPtr, _args);
             return _engineResult;
        }

        /// <description>
        /// Pop a line from the front of the vector, destroying the line.
        /// </description>
        /// <returns>False if there are no lines to pop (underflow), true otherwise</returns>
        public bool PopFrontLine() {
             InternalUnsafeMethods.PopFrontLine__Args _args = new InternalUnsafeMethods.PopFrontLine__Args() {
             };
             bool _engineResult = InternalUnsafeMethods.PopFrontLine()(ObjectPtr, _args);
             return _engineResult;
        }

        /// <description>
        /// Push a line onto the front of the vector.
        /// </description>
        /// <param name="msg">Text that makes up the message</param>
        /// <param name="tag">Numerical value associated with this message, useful for searching.</param>
        /// <code>
        /// // Add the message...
        /// HudMessageVector.pushFrontLine("Hello World", 0);
        /// </code>
        public void PushFrontLine(string msg, int tag) {
             InternalUnsafeMethods.PushFrontLine__Args _args = new InternalUnsafeMethods.PushFrontLine__Args() {
                msg = msg,
                tag = tag,
             };
             InternalUnsafeMethods.PushFrontLine()(ObjectPtr, _args);
        }

        /// <description>
        /// Pop a line from the back of the list; destroys the line.
        /// </description>
        /// <returns>False if there are no lines to pop (underflow), true otherwise</returns>
        public bool PopBackLine() {
             InternalUnsafeMethods.PopBackLine__Args _args = new InternalUnsafeMethods.PopBackLine__Args() {
             };
             bool _engineResult = InternalUnsafeMethods.PopBackLine()(ObjectPtr, _args);
             return _engineResult;
        }

        /// <description>
        /// Push a line onto the back of the list.
        /// </description>
        /// <param name="msg">Text that makes up the message</param>
        /// <param name="tag">Numerical value associated with this message, useful for searching.</param>
        /// <code>
        /// // Add the message...
        /// HudMessageVector.pushBackLine("Hello World", 0);
        /// </code>
        public void PushBackLine(string msg, int tag) {
             InternalUnsafeMethods.PushBackLine__Args _args = new InternalUnsafeMethods.PushBackLine__Args() {
                msg = msg,
                tag = tag,
             };
             InternalUnsafeMethods.PushBackLine()(ObjectPtr, _args);
        }

        /// <description>
        /// Clear all messages in the vector
        /// </description>
        public void Clear() {
             InternalUnsafeMethods.Clear__Args _args = new InternalUnsafeMethods.Clear__Args() {
             };
             InternalUnsafeMethods.Clear()(ObjectPtr, _args);
        }

        /// <description>
        /// Get the type info object for the MessageVector class.
        /// </description>
        /// <returns>The type info object for MessageVector</returns>
        public static EngineTypeInfo StaticGetType() {
             InternalUnsafeMethods.StaticGetType__Args _args = new InternalUnsafeMethods.StaticGetType__Args() {
             };
             IntPtr _engineResult = InternalUnsafeMethods.StaticGetType()(_args);
             return new EngineTypeInfo(_engineResult);
        }
    }
}