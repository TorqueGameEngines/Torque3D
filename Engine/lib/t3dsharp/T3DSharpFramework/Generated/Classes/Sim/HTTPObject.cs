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
    /// <summary>Allows communications between the game and a server using HTTP.</summary>
    /// <description>
    /// HTTPObject is derrived from TCPObject and makes use of the same callbacks for dealing with connections and received data.  However, the way in which you use HTTPObject to connect with a server is different than TCPObject.  Rather than opening a connection, sending data, waiting to receive data, and then closing the connection, you issue a get() or post() and handle the response.  The connection is automatically created and destroyed for you.
    /// </description>
    /// <code>
    /// // In this example we'll retrieve the weather in Las Vegas using
    /// // Google's API.  The response is in XML which could be processed
    /// // and used by the game using SimXMLDocument, but we'll just output
    /// // the results to the console in this example.
    /// 
    /// // Define callbacks for our specific HTTPObject using our instance's
    /// // name (WeatherFeed) as the namespace.
    /// 
    /// // Handle an issue with resolving the server's name
    /// function WeatherFeed::onDNSFailed(%this)
    /// {
    ///    // Store this state
    ///    %this.lastState = "DNSFailed";
    /// 
    ///    // Handle DNS failure
    /// }
    /// 
    /// function WeatherFeed::onConnectFailed(%this)
    /// {
    ///    // Store this state
    ///    %this.lastState = "ConnectFailed";
    /// 
    ///    // Handle connection failure
    /// }
    /// 
    /// function WeatherFeed::onDNSResolved(%this)
    /// {
    ///    // Store this state
    ///    %this.lastState = "DNSResolved";
    /// 
    /// }
    /// 
    /// function WeatherFeed::onConnected(%this)
    /// {
    ///    // Store this state
    ///    %this.lastState = "Connected";
    /// 
    ///    // Clear our buffer
    ///    %this.buffer = "";
    /// }
    /// 
    /// function WeatherFeed::onDisconnect(%this)
    /// {
    ///    // Store this state
    ///    %this.lastState = "Disconnected";
    /// 
    ///    // Output the buffer to the console
    ///    echo("Google Weather Results:");
    ///    echo(%this.buffer);
    /// }
    /// 
    /// // Handle a line from the server
    /// function WeatherFeed::onLine(%this, %line)
    /// {
    ///    // Store this line in out buffer
    ///    %this.buffer = %this.buffer@ %line;
    /// }
    /// 
    /// // Create the HTTPObject
    /// %feed = new HTTPObject(WeatherFeed);
    /// 
    /// // Define a dynamic field to store the last connection state
    /// %feed.lastState = "None";
    /// 
    /// // Send the GET command
    /// %feed.get("www.google.com:80", "/ig/api", "weather=Las-Vegas,US");
    /// 
    /// </code>
    /// <see cref="TCPObject" />
    public unsafe class HTTPObject : TCPObject {
        public HTTPObject(bool pRegister = false) 
            : base(pRegister) {
        }
        
        public HTTPObject(string pName, bool pRegister) 
            : this(false) {
            Name = pName;
            if (pRegister) {
                RegisterObject();
            }
        }
        
        public HTTPObject(string pName) 
            : this(pName, false) {
        }
        
        public HTTPObject(string pName, string pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(Engine.Sim.FindObject<SimObject>(pParent));
        }
        
        public HTTPObject(string pName, SimObject pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(pParent);
        }
        
        public HTTPObject(SimObject pObj) 
            : base(pObj) {
        }
        
        public HTTPObject(IntPtr pObj) 
            : base(pObj) {
        }
        
		protected override void CreateObjectPtr()
		{
			ObjectPtr = InternalUnsafeMethods.Create()(new InternalUnsafeMethods.Create__Args());
		}

        #region UnsafeNativeMethods
        new internal struct InternalUnsafeMethods {
            [StructLayout(LayoutKind.Sequential)]
            internal struct Post__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string Address;
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string requirstURI;
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string query;
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string post;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _Post(IntPtr _this, Post__Args args);
            private static _Post _PostFunc;
            internal static _Post Post() {
                if (_PostFunc == null) {
                    _PostFunc =
                        (_Post)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnHTTPObject_post"), typeof(_Post));
                }
                
                return _PostFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct Get__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string Address;
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string requirstURI;
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string query;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _Get(IntPtr _this, Get__Args args);
            private static _Get _GetFunc;
            internal static _Get Get() {
                if (_GetFunc == null) {
                    _GetFunc =
                        (_Get)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnHTTPObject_get"), typeof(_Get));
                }
                
                return _GetFunc;
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
                                "fnHTTPObject_staticGetType"), typeof(_StaticGetType));
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
                                "fnHTTPObject_create"), typeof(_Create));
                }
                
                return _CreateFunc;
            }
        }
        #endregion

        /// <summary>Send POST command to a server to send or retrieve data.</summary>
        /// <description>
        /// 
        /// </description>
        /// <param name="Address">HTTP web address to send this get call to. Be sure to include the port at the end (IE: "www.garagegames.com:80").</param>
        /// <param name="requirstURI">Specific location on the server to access (IE: "index.php".)</param>
        /// <param name="query">Actual data to transmit to the server. Can be anything required providing it sticks with limitations of the HTTP protocol.</param>
        /// <param name="post">Submission data to be processed.</param>
        /// <code>
        /// // Create an HTTP object for communications
        /// %httpObj = new HTTPObject();
        /// 
        /// // Specify a URL to transmit to
        /// %url = "www.garagegames.com:80";
        /// 
        /// // Specify a URI to communicate with
        /// %URI = "/index.php";
        /// 
        /// // Specify a query to send.
        /// %query = "";
        /// 
        /// // Specify the submission data.
        /// %post = "";
        /// 
        /// // Send the POST command to the server
        /// %httpObj.POST(%url,%URI,%query,%post);
        /// </code>
        public void Post(string Address, string requirstURI, string query, string post) {
             InternalUnsafeMethods.Post__Args _args = new InternalUnsafeMethods.Post__Args() {
                Address = Address,
                requirstURI = requirstURI,
                query = query,
                post = post,
             };
             InternalUnsafeMethods.Post()(ObjectPtr, _args);
        }

        /// <summary>Send a GET command to a server to send or retrieve data.</summary>
        /// <description>
        /// 
        /// </description>
        /// <param name="Address">HTTP web address to send this get call to. Be sure to include the port at the end (IE: "www.garagegames.com:80").</param>
        /// <param name="requirstURI">Specific location on the server to access (IE: "index.php".)</param>
        /// <param name="query">Optional. Actual data to transmit to the server. Can be anything required providing it sticks with limitations of the HTTP protocol. If you were building the URL manually, this is the text that follows the question mark.  For example: http://www.google.com/ig/api?<b>weather=Las-Vegas,US</b></param>
        /// <code>
        /// // Create an HTTP object for communications
        /// %httpObj = new HTTPObject();
        /// 
        /// // Specify a URL to transmit to
        /// %url = "www.garagegames.com:80";
        /// 
        /// // Specify a URI to communicate with
        /// %URI = "/index.php";
        /// 
        /// // Specify a query to send.
        /// %query = "";
        /// 
        /// // Send the GET command to the server
        /// %httpObj.get(%url,%URI,%query);
        /// </code>
        public void Get(string Address, string requirstURI, string query = "") {
             InternalUnsafeMethods.Get__Args _args = new InternalUnsafeMethods.Get__Args() {
                Address = Address,
                requirstURI = requirstURI,
                query = query,
             };
             InternalUnsafeMethods.Get()(ObjectPtr, _args);
        }

        /// <description>
        /// Get the type info object for the HTTPObject class.
        /// </description>
        /// <returns>The type info object for HTTPObject</returns>
        public static EngineTypeInfo StaticGetType() {
             InternalUnsafeMethods.StaticGetType__Args _args = new InternalUnsafeMethods.StaticGetType__Args() {
             };
             IntPtr _engineResult = InternalUnsafeMethods.StaticGetType()(_args);
             return new EngineTypeInfo(_engineResult);
        }
    }
}