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
    /// <summary>Allows communications between the game and a server using TCP/IP protocols.</summary>
    /// <description>
    /// To use TCPObject you set up a connection to a server, send data to the server, and handle each line of the server's response using a callback.  Once you are done communicating with the server, you disconnect.
    /// 
    /// TCPObject is intended to be used with text based protocols which means you'll need to delineate the server's response with an end-of-line character. i.e. the newline character
    /// </description>
    /// <code>
    /// // In this example we'll retrieve the new forum threads RSS
    /// // feed from garagegames.com.  As we're using TCPObject, the
    /// // raw text response will be received from the server, including
    /// // the HTTP header.
    /// 
    /// // Define callbacks for our specific TCPObject using our instance's
    /// // name (RSSFeed) as the namespace.
    /// 
    /// // Handle an issue with resolving the server's name
    /// function RSSFeed::onDNSFailed(%this)
    /// {
    ///    // Store this state
    ///    %this.lastState = "DNSFailed";
    /// 
    ///    // Handle DNS failure
    /// }
    /// 
    /// function RSSFeed::onConnectFailed(%this)
    /// {
    ///    // Store this state
    ///    %this.lastState = "ConnectFailed";
    /// 
    ///    // Handle connection failure
    /// }
    /// 
    /// function RSSFeed::onDNSResolved(%this)
    /// {
    ///    // Store this state
    ///    %this.lastState = "DNSResolved";
    /// 
    /// }
    /// 
    /// function RSSFeed::onConnected(%this)
    /// {
    ///    // Store this state
    ///    %this.lastState = "Connected";
    /// 
    /// }
    /// 
    /// function RSSFeed::onDisconnect(%this)
    /// {
    ///    // Store this state
    ///    %this.lastState = "Disconnected";
    /// 
    /// }
    /// 
    /// // Handle a line from the server
    /// function RSSFeed::onLine(%this, %line)
    /// {
    ///    // Print the line to the console
    ///    echo( %line );
    /// }
    /// 
    /// // Create the TCPObject
    /// %rss = new TCPObject(RSSFeed);
    /// 
    /// // Define a dynamic field to store the last connection state
    /// %rss.lastState = "None";
    /// 
    /// // Connect to the server
    /// %rss.connect("www.garagegames.com:80");
    /// 
    /// // Send the RSS feed request to the server.  Response will be
    /// // handled in onLine() callback above
    /// %rss.send("GET /feeds/rss/threads HTTP/1.1\r\nHost: www.garagegames.com\r\n\r\n");
    /// </code>
    /// <see cref="HTTPObject" />
    public unsafe class TCPObject : SimObject {
        public TCPObject(bool pRegister = false) 
            : base(pRegister) {
        }
        
        public TCPObject(string pName, bool pRegister) 
            : this(false) {
            Name = pName;
            if (pRegister) {
                RegisterObject();
            }
        }
        
        public TCPObject(string pName) 
            : this(pName, false) {
        }
        
        public TCPObject(string pName, string pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(Engine.Sim.FindObject<SimObject>(pParent));
        }
        
        public TCPObject(string pName, SimObject pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(pParent);
        }
        
        public TCPObject(SimObject pObj) 
            : base(pObj) {
        }
        
        public TCPObject(IntPtr pObj) 
            : base(pObj) {
        }
        
		protected override void CreateObjectPtr()
		{
			ObjectPtr = InternalUnsafeMethods.Create()(new InternalUnsafeMethods.Create__Args());
		}

        #region UnsafeNativeMethods
        new internal struct InternalUnsafeMethods {
            [StructLayout(LayoutKind.Sequential)]
            internal struct Disconnect__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _Disconnect(IntPtr _this, Disconnect__Args args);
            private static _Disconnect _DisconnectFunc;
            internal static _Disconnect Disconnect() {
                if (_DisconnectFunc == null) {
                    _DisconnectFunc =
                        (_Disconnect)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnTCPObject_disconnect"), typeof(_Disconnect));
                }
                
                return _DisconnectFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct Connect__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string address;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _Connect(IntPtr _this, Connect__Args args);
            private static _Connect _ConnectFunc;
            internal static _Connect Connect() {
                if (_ConnectFunc == null) {
                    _ConnectFunc =
                        (_Connect)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnTCPObject_connect"), typeof(_Connect));
                }
                
                return _ConnectFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct Listen__Args
            {
                internal uint port;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _Listen(IntPtr _this, Listen__Args args);
            private static _Listen _ListenFunc;
            internal static _Listen Listen() {
                if (_ListenFunc == null) {
                    _ListenFunc =
                        (_Listen)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnTCPObject_listen"), typeof(_Listen));
                }
                
                return _ListenFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct FinishLastLine__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _FinishLastLine(IntPtr _this, FinishLastLine__Args args);
            private static _FinishLastLine _FinishLastLineFunc;
            internal static _FinishLastLine FinishLastLine() {
                if (_FinishLastLineFunc == null) {
                    _FinishLastLineFunc =
                        (_FinishLastLine)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnTCPObject_finishLastLine"), typeof(_FinishLastLine));
                }
                
                return _FinishLastLineFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct SendFile__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string fileName;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            [return: MarshalAs(UnmanagedType.I1)]
            internal delegate bool _SendFile(IntPtr _this, SendFile__Args args);
            private static _SendFile _SendFileFunc;
            internal static _SendFile SendFile() {
                if (_SendFileFunc == null) {
                    _SendFileFunc =
                        (_SendFile)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnTCPObject_sendFile"), typeof(_SendFile));
                }
                
                return _SendFileFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct Send__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string data;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _Send(IntPtr _this, Send__Args args);
            private static _Send _SendFunc;
            internal static _Send Send() {
                if (_SendFunc == null) {
                    _SendFunc =
                        (_Send)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnTCPObject_send"), typeof(_Send));
                }
                
                return _SendFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct OnDisconnect__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _OnDisconnect(IntPtr _this, OnDisconnect__Args args);
            private static _OnDisconnect _OnDisconnectFunc;
            internal static _OnDisconnect OnDisconnect() {
                if (_OnDisconnectFunc == null) {
                    _OnDisconnectFunc =
                        (_OnDisconnect)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "cbTCPObject_onDisconnect"), typeof(_OnDisconnect));
                }
                
                return _OnDisconnectFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct OnConnectFailed__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _OnConnectFailed(IntPtr _this, OnConnectFailed__Args args);
            private static _OnConnectFailed _OnConnectFailedFunc;
            internal static _OnConnectFailed OnConnectFailed() {
                if (_OnConnectFailedFunc == null) {
                    _OnConnectFailedFunc =
                        (_OnConnectFailed)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "cbTCPObject_onConnectFailed"), typeof(_OnConnectFailed));
                }
                
                return _OnConnectFailedFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct OnConnected__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _OnConnected(IntPtr _this, OnConnected__Args args);
            private static _OnConnected _OnConnectedFunc;
            internal static _OnConnected OnConnected() {
                if (_OnConnectedFunc == null) {
                    _OnConnectedFunc =
                        (_OnConnected)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "cbTCPObject_onConnected"), typeof(_OnConnected));
                }
                
                return _OnConnectedFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct OnDNSFailed__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _OnDNSFailed(IntPtr _this, OnDNSFailed__Args args);
            private static _OnDNSFailed _OnDNSFailedFunc;
            internal static _OnDNSFailed OnDNSFailed() {
                if (_OnDNSFailedFunc == null) {
                    _OnDNSFailedFunc =
                        (_OnDNSFailed)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "cbTCPObject_onDNSFailed"), typeof(_OnDNSFailed));
                }
                
                return _OnDNSFailedFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct OnDNSResolved__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _OnDNSResolved(IntPtr _this, OnDNSResolved__Args args);
            private static _OnDNSResolved _OnDNSResolvedFunc;
            internal static _OnDNSResolved OnDNSResolved() {
                if (_OnDNSResolvedFunc == null) {
                    _OnDNSResolvedFunc =
                        (_OnDNSResolved)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "cbTCPObject_onDNSResolved"), typeof(_OnDNSResolved));
                }
                
                return _OnDNSResolvedFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct OnEndReceive__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _OnEndReceive(IntPtr _this, OnEndReceive__Args args);
            private static _OnEndReceive _OnEndReceiveFunc;
            internal static _OnEndReceive OnEndReceive() {
                if (_OnEndReceiveFunc == null) {
                    _OnEndReceiveFunc =
                        (_OnEndReceive)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "cbTCPObject_onEndReceive"), typeof(_OnEndReceive));
                }
                
                return _OnEndReceiveFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct OnPacket__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string data;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            [return: MarshalAs(UnmanagedType.I1)]
            internal delegate bool _OnPacket(IntPtr _this, OnPacket__Args args);
            private static _OnPacket _OnPacketFunc;
            internal static _OnPacket OnPacket() {
                if (_OnPacketFunc == null) {
                    _OnPacketFunc =
                        (_OnPacket)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "cbTCPObject_onPacket"), typeof(_OnPacket));
                }
                
                return _OnPacketFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct OnLine__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string line;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _OnLine(IntPtr _this, OnLine__Args args);
            private static _OnLine _OnLineFunc;
            internal static _OnLine OnLine() {
                if (_OnLineFunc == null) {
                    _OnLineFunc =
                        (_OnLine)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "cbTCPObject_onLine"), typeof(_OnLine));
                }
                
                return _OnLineFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct OnConnectionRequest__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string address;
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string ID;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _OnConnectionRequest(IntPtr _this, OnConnectionRequest__Args args);
            private static _OnConnectionRequest _OnConnectionRequestFunc;
            internal static _OnConnectionRequest OnConnectionRequest() {
                if (_OnConnectionRequestFunc == null) {
                    _OnConnectionRequestFunc =
                        (_OnConnectionRequest)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "cbTCPObject_onConnectionRequest"), typeof(_OnConnectionRequest));
                }
                
                return _OnConnectionRequestFunc;
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
                                "fnTCPObject_staticGetType"), typeof(_StaticGetType));
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
                                "fnTCPObject_create"), typeof(_Create));
                }
                
                return _CreateFunc;
            }
        }
        #endregion

        /// <summary>Disconnect from whatever this TCPObject is currently connected to, if anything.</summary>
        /// <description>
        /// 
        /// </description>
        /// <code>
        /// // Inform this TCPObject to disconnect from anything it is currently connected to.
        /// %thisTCPObj.disconnect();
        /// </code>
        public void Disconnect() {
             InternalUnsafeMethods.Disconnect__Args _args = new InternalUnsafeMethods.Disconnect__Args() {
             };
             InternalUnsafeMethods.Disconnect()(ObjectPtr, _args);
        }

        /// <summary>Connect to the given address.</summary>
        /// <description>
        /// 
        /// </description>
        /// <param name="address">Server address (including port) to connect to.</param>
        /// <code>
        /// // Set the address.
        /// %address = "www.garagegames.com:80";
        /// 
        /// // Inform this TCPObject to connect to the specified address.
        /// %thisTCPObj.connect(%address);
        /// </code>
        public void Connect(string address) {
             InternalUnsafeMethods.Connect__Args _args = new InternalUnsafeMethods.Connect__Args() {
                address = address,
             };
             InternalUnsafeMethods.Connect()(ObjectPtr, _args);
        }

        /// <summary>Start listening on the specified port for connections.</summary>
        /// <description>
        /// This method starts a listener which looks for incoming TCP connections to a port.  You must overload the onConnectionRequest callback to create a new TCPObject to read, write, or reject the new connection.
        /// </description>
        /// <param name="port">Port for this TCPObject to start listening for connections on.</param>
        /// <code>
        /// // Create a listener on port 8080.
        /// new TCPObject( TCPListener );
        /// TCPListener.listen( 8080 );
        /// 
        /// function TCPListener::onConnectionRequest( %this, %address, %id )
        /// {
        ///    // Create a new object to manage the connection.
        ///    new TCPObject( TCPClient, %id );
        /// }
        /// 
        /// function TCPClient::onLine( %this, %line )
        /// {
        ///    // Print the line of text from client.
        ///    echo( %line );
        /// }
        /// </code>
        public void Listen(uint port) {
             InternalUnsafeMethods.Listen__Args _args = new InternalUnsafeMethods.Listen__Args() {
                port = port,
             };
             InternalUnsafeMethods.Listen()(ObjectPtr, _args);
        }

        /// <summary>Eat the rest of the lines.</summary>
        /// <description>
        /// 
        /// </description>
        public void FinishLastLine() {
             InternalUnsafeMethods.FinishLastLine__Args _args = new InternalUnsafeMethods.FinishLastLine__Args() {
             };
             InternalUnsafeMethods.FinishLastLine()(ObjectPtr, _args);
        }

        /// <summary>Transmits the file in binary to the connected computer.</summary>
        /// <description>
        /// 
        /// </description>
        /// <param name="fileName">The filename of the file to transfer.</param>
        public bool SendFile(string fileName) {
             InternalUnsafeMethods.SendFile__Args _args = new InternalUnsafeMethods.SendFile__Args() {
                fileName = fileName,
             };
             bool _engineResult = InternalUnsafeMethods.SendFile()(ObjectPtr, _args);
             return _engineResult;
        }

        /// <summary>Transmits the data string to the connected computer.</summary>
        /// <description>
        /// This method is used to send text data to the connected computer regardless if we initiated the connection using connect(), or listening to a port using listen().
        /// </description>
        /// <param name="data">The data string to send.</param>
        /// <code>
        /// // Set the command data
        /// %data = "GET "@ $RSSFeed::serverURL 
        /// </code>
        public void Send(string data) {
             InternalUnsafeMethods.Send__Args _args = new InternalUnsafeMethods.Send__Args() {
                data = data,
             };
             InternalUnsafeMethods.Send()(ObjectPtr, _args);
        }

        /// <description>
        /// Called whenever the TCPObject disconnects from whatever it is currently connected to.
        /// </description>
        public virtual void OnDisconnect() {
             InternalUnsafeMethods.OnDisconnect__Args _args = new InternalUnsafeMethods.OnDisconnect__Args() {
             };
             InternalUnsafeMethods.OnDisconnect()(ObjectPtr, _args);
        }

        /// <description>
        /// Called whenever a connection has failed to be established with a server.
        /// </description>
        public virtual void OnConnectFailed() {
             InternalUnsafeMethods.OnConnectFailed__Args _args = new InternalUnsafeMethods.OnConnectFailed__Args() {
             };
             InternalUnsafeMethods.OnConnectFailed()(ObjectPtr, _args);
        }

        /// <description>
        /// Called whenever a connection is established with a server.
        /// </description>
        public virtual void OnConnected() {
             InternalUnsafeMethods.OnConnected__Args _args = new InternalUnsafeMethods.OnConnected__Args() {
             };
             InternalUnsafeMethods.OnConnected()(ObjectPtr, _args);
        }

        /// <description>
        /// Called whenever the DNS has failed to resolve.
        /// </description>
        public virtual void OnDNSFailed() {
             InternalUnsafeMethods.OnDNSFailed__Args _args = new InternalUnsafeMethods.OnDNSFailed__Args() {
             };
             InternalUnsafeMethods.OnDNSFailed()(ObjectPtr, _args);
        }

        /// <description>
        /// Called whenever the DNS has been resolved.
        /// </description>
        public virtual void OnDNSResolved() {
             InternalUnsafeMethods.OnDNSResolved__Args _args = new InternalUnsafeMethods.OnDNSResolved__Args() {
             };
             InternalUnsafeMethods.OnDNSResolved()(ObjectPtr, _args);
        }

        /// <summary>Called when we are done reading all lines.</summary>
        /// <description>
        /// 
        /// </description>
        public virtual void OnEndReceive() {
             InternalUnsafeMethods.OnEndReceive__Args _args = new InternalUnsafeMethods.OnEndReceive__Args() {
             };
             InternalUnsafeMethods.OnEndReceive()(ObjectPtr, _args);
        }

        /// <summary>Called when we get a packet with no newlines or nulls (probably websocket).</summary>
        /// <description>
        /// 
        /// </description>
        /// <param name="data">Data sent from the server.</param>
        /// <returns>true if script handled the packet.</returns>
        public virtual bool OnPacket(string data) {
             InternalUnsafeMethods.OnPacket__Args _args = new InternalUnsafeMethods.OnPacket__Args() {
                data = data,
             };
             bool _engineResult = InternalUnsafeMethods.OnPacket()(ObjectPtr, _args);
             return _engineResult;
        }

        /// <summary>Called whenever a line of data is sent to this TCPObject.</summary>
        /// <description>
        /// This callback is called when the received data contains a newline
        /// </description>
        /// <param name="line">Data sent from the server.</param>
        public virtual void OnLine(string line) {
             InternalUnsafeMethods.OnLine__Args _args = new InternalUnsafeMethods.OnLine__Args() {
                line = line,
             };
             InternalUnsafeMethods.OnLine()(ObjectPtr, _args);
        }

        /// <summary>Called whenever a connection request is made.</summary>
        /// <description>
        /// This callback is used when the TCPObject is listening to a port and a client is attempting to connect.
        /// </description>
        /// <param name="address">Server address connecting from.</param>
        /// <param name="ID">Connection ID</param>
        /// <see cref="listen()" />
        public virtual void OnConnectionRequest(string address, string ID) {
             InternalUnsafeMethods.OnConnectionRequest__Args _args = new InternalUnsafeMethods.OnConnectionRequest__Args() {
                address = address,
                ID = ID,
             };
             InternalUnsafeMethods.OnConnectionRequest()(ObjectPtr, _args);
        }

        /// <description>
        /// Get the type info object for the TCPObject class.
        /// </description>
        /// <returns>The type info object for TCPObject</returns>
        public static EngineTypeInfo StaticGetType() {
             InternalUnsafeMethods.StaticGetType__Args _args = new InternalUnsafeMethods.StaticGetType__Args() {
             };
             IntPtr _engineResult = InternalUnsafeMethods.StaticGetType()(_args);
             return new EngineTypeInfo(_engineResult);
        }
    }
}