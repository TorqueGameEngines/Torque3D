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

namespace T3DSharpFramework.Generated.Classes.Sim.Net {
    /// <summary>Provides the basis for implementing a multiplayer game protocol.</summary>
    /// <description>
    /// NetConnection combines a low-level notify protocol implemented in ConnectionProtocol with a SimGroup, and implements several distinct subsystems:
    /// 
    /// - <b>Event Manager</b>  This is responsible for transmitting NetEvents over the wire.  It deals with ensuring that the various types of NetEvents are delivered appropriately, and with notifying the event of its delivery status.
    /// 
    /// - <b>Move Manager</b>  This is responsible for transferring a Move to the server 32 times a second (on the client) and applying it to the control object (on the server).
    /// 
    /// - <b>Ghost Manager</b>  This is responsible for doing scoping calculations (on the server side) and transmitting most-recent ghost information to the client.
    /// 
    /// - <b>File Transfer</b>  It is often the case that clients will lack important files when connecting to a server which is running a mod or new map. This subsystem allows the server to transfer such files to the client.
    /// 
    /// - <b>Networked String Table</b>  String data can easily soak up network bandwidth, so for efficiency, we implement a networked string table. We can then notify the connection of strings we will reference often, such as player names, and transmit only a tag, instead of the whole string.
    /// 
    /// - <b>Demo Recording</b>  A demo in Torque is a log of the network traffic between client and server; when a NetConnection records a demo, it simply logs this data to a file. When it plays a demo back, it replays the logged data.
    /// 
    /// - <b>Connection Database</b>  This is used to keep track of all the NetConnections; it can be iterated over (for instance, to send an event to all active connections), or queried by address.
    /// 
    /// The NetConnection is a SimGroup. On the client side, it contains all the objects which have been ghosted to that client. On the server side, it is empty; it can be used (typically in script) to hold objects related to the connection. For instance, you might place an observation camera in the NetConnnection. In both cases, when the connection is destroyed, so are the contained objects.
    /// 
    /// The NetConnection also has the concept of local connections.  These are used when the client and server reside in the same process.  A local connection is typically required to use the standard Torque world building tools.  A local connection is also required when building a single player game.
    /// </description>
    /// <see cref="" />
    public unsafe class NetConnection : SimGroup {
        public NetConnection(bool pRegister = false) 
            : base(pRegister) {
        }
        
        public NetConnection(string pName, bool pRegister) 
            : this(false) {
            Name = pName;
            if (pRegister) {
                RegisterObject();
            }
        }
        
        public NetConnection(string pName) 
            : this(pName, false) {
        }
        
        public NetConnection(string pName, string pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(Engine.Sim.FindObject<SimObject>(pParent));
        }
        
        public NetConnection(string pName, SimObject pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(pParent);
        }
        
        public NetConnection(SimObject pObj) 
            : base(pObj) {
        }
        
        public NetConnection(IntPtr pObj) 
            : base(pObj) {
        }
        
		protected override void CreateObjectPtr()
		{
			ObjectPtr = InternalUnsafeMethods.Create()(new InternalUnsafeMethods.Create__Args());
		}

        #region UnsafeNativeMethods
        new internal struct InternalUnsafeMethods {
            [StructLayout(LayoutKind.Sequential)]
            internal struct ResolveGhost__Args
            {
                internal int ghostIndex;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate int _ResolveGhost(IntPtr _this, ResolveGhost__Args args);
            private static _ResolveGhost _ResolveGhostFunc;
            internal static _ResolveGhost ResolveGhost() {
                if (_ResolveGhostFunc == null) {
                    _ResolveGhostFunc =
                        (_ResolveGhost)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnNetConnection_ResolveGhost"), typeof(_ResolveGhost));
                }
                
                return _ResolveGhostFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct GetGhostIndex__Args
            {
                internal IntPtr obj;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate int _GetGhostIndex(IntPtr _this, GetGhostIndex__Args args);
            private static _GetGhostIndex _GetGhostIndexFunc;
            internal static _GetGhostIndex GetGhostIndex() {
                if (_GetGhostIndexFunc == null) {
                    _GetGhostIndexFunc =
                        (_GetGhostIndex)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnNetConnection_GetGhostIndex"), typeof(_GetGhostIndex));
                }
                
                return _GetGhostIndexFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct GetGhostsActive__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate int _GetGhostsActive(IntPtr _this, GetGhostsActive__Args args);
            private static _GetGhostsActive _GetGhostsActiveFunc;
            internal static _GetGhostsActive GetGhostsActive() {
                if (_GetGhostsActiveFunc == null) {
                    _GetGhostsActiveFunc =
                        (_GetGhostsActive)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnNetConnection_getGhostsActive"), typeof(_GetGhostsActive));
                }
                
                return _GetGhostsActiveFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct ConnectLocal__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            
            internal delegate IntPtr _ConnectLocal(IntPtr _this, ConnectLocal__Args args);
            private static _ConnectLocal _ConnectLocalFunc;
            internal static _ConnectLocal ConnectLocal() {
                if (_ConnectLocalFunc == null) {
                    _ConnectLocalFunc =
                        (_ConnectLocal)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnNetConnection_connectLocal"), typeof(_ConnectLocal));
                }
                
                return _ConnectLocalFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct Connect__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string remoteAddress;
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
                                "fnNetConnection_connect"), typeof(_Connect));
                }
                
                return _ConnectFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct GetGhostID__Args
            {
                internal int realID;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate int _GetGhostID(IntPtr _this, GetGhostID__Args args);
            private static _GetGhostID _GetGhostIDFunc;
            internal static _GetGhostID GetGhostID() {
                if (_GetGhostIDFunc == null) {
                    _GetGhostIDFunc =
                        (_GetGhostID)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnNetConnection_getGhostID"), typeof(_GetGhostID));
                }
                
                return _GetGhostIDFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct ResolveObjectFromGhostIndex__Args
            {
                internal int ghostID;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate int _ResolveObjectFromGhostIndex(IntPtr _this, ResolveObjectFromGhostIndex__Args args);
            private static _ResolveObjectFromGhostIndex _ResolveObjectFromGhostIndexFunc;
            internal static _ResolveObjectFromGhostIndex ResolveObjectFromGhostIndex() {
                if (_ResolveObjectFromGhostIndexFunc == null) {
                    _ResolveObjectFromGhostIndexFunc =
                        (_ResolveObjectFromGhostIndex)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnNetConnection_resolveObjectFromGhostIndex"), typeof(_ResolveObjectFromGhostIndex));
                }
                
                return _ResolveObjectFromGhostIndexFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct ResolveGhostID__Args
            {
                internal int ghostID;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate int _ResolveGhostID(IntPtr _this, ResolveGhostID__Args args);
            private static _ResolveGhostID _ResolveGhostIDFunc;
            internal static _ResolveGhostID ResolveGhostID() {
                if (_ResolveGhostIDFunc == null) {
                    _ResolveGhostIDFunc =
                        (_ResolveGhostID)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnNetConnection_resolveGhostID"), typeof(_ResolveGhostID));
                }
                
                return _ResolveGhostIDFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct CheckMaxRate__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _CheckMaxRate(IntPtr _this, CheckMaxRate__Args args);
            private static _CheckMaxRate _CheckMaxRateFunc;
            internal static _CheckMaxRate CheckMaxRate() {
                if (_CheckMaxRateFunc == null) {
                    _CheckMaxRateFunc =
                        (_CheckMaxRate)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnNetConnection_checkMaxRate"), typeof(_CheckMaxRate));
                }
                
                return _CheckMaxRateFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct GetPacketLoss__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate int _GetPacketLoss(IntPtr _this, GetPacketLoss__Args args);
            private static _GetPacketLoss _GetPacketLossFunc;
            internal static _GetPacketLoss GetPacketLoss() {
                if (_GetPacketLossFunc == null) {
                    _GetPacketLossFunc =
                        (_GetPacketLoss)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnNetConnection_getPacketLoss"), typeof(_GetPacketLoss));
                }
                
                return _GetPacketLossFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct GetPing__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate int _GetPing(IntPtr _this, GetPing__Args args);
            private static _GetPing _GetPingFunc;
            internal static _GetPing GetPing() {
                if (_GetPingFunc == null) {
                    _GetPingFunc =
                        (_GetPing)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnNetConnection_getPing"), typeof(_GetPing));
                }
                
                return _GetPingFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct SetSimulatedNetParams__Args
            {
                internal float packetLoss;
                internal int delay;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _SetSimulatedNetParams(IntPtr _this, SetSimulatedNetParams__Args args);
            private static _SetSimulatedNetParams _SetSimulatedNetParamsFunc;
            internal static _SetSimulatedNetParams SetSimulatedNetParams() {
                if (_SetSimulatedNetParamsFunc == null) {
                    _SetSimulatedNetParamsFunc =
                        (_SetSimulatedNetParams)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnNetConnection_setSimulatedNetParams"), typeof(_SetSimulatedNetParams));
                }
                
                return _SetSimulatedNetParamsFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct GetAddress__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            
            internal delegate IntPtr _GetAddress(IntPtr _this, GetAddress__Args args);
            private static _GetAddress _GetAddressFunc;
            internal static _GetAddress GetAddress() {
                if (_GetAddressFunc == null) {
                    _GetAddressFunc =
                        (_GetAddress)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnNetConnection_getAddress"), typeof(_GetAddress));
                }
                
                return _GetAddressFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct ClearPaths__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _ClearPaths(IntPtr _this, ClearPaths__Args args);
            private static _ClearPaths _ClearPathsFunc;
            internal static _ClearPaths ClearPaths() {
                if (_ClearPathsFunc == null) {
                    _ClearPathsFunc =
                        (_ClearPaths)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnNetConnection_clearPaths"), typeof(_ClearPaths));
                }
                
                return _ClearPathsFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct TransmitPaths__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _TransmitPaths(IntPtr _this, TransmitPaths__Args args);
            private static _TransmitPaths _TransmitPathsFunc;
            internal static _TransmitPaths TransmitPaths() {
                if (_TransmitPathsFunc == null) {
                    _TransmitPathsFunc =
                        (_TransmitPaths)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnNetConnection_transmitPaths"), typeof(_TransmitPaths));
                }
                
                return _TransmitPathsFunc;
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
                                "fnNetConnection_staticGetType"), typeof(_StaticGetType));
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
                                "fnNetConnection_create"), typeof(_Create));
                }
                
                return _CreateFunc;
            }
        }
        #endregion

        /// <description>
        /// Resolves a ghost-index into an object ID.
        /// </description>
        public int ResolveGhost(int ghostIndex) {
             InternalUnsafeMethods.ResolveGhost__Args _args = new InternalUnsafeMethods.ResolveGhost__Args() {
                ghostIndex = ghostIndex,
             };
             int _engineResult = InternalUnsafeMethods.ResolveGhost()(ObjectPtr, _args);
             return _engineResult;
        }

        /// <description>
        /// Returns the ghost-index for an object.
        /// </description>
        public int GetGhostIndex(NetObject obj) {
             InternalUnsafeMethods.GetGhostIndex__Args _args = new InternalUnsafeMethods.GetGhostIndex__Args() {
                obj = obj.ObjectPtr,
             };
             int _engineResult = InternalUnsafeMethods.GetGhostIndex()(ObjectPtr, _args);
             return _engineResult;
        }

        /// <summary>Provides the number of active ghosts on the connection.</summary>
        /// <description>
        /// 
        /// </description>
        /// <returns>The number of active ghosts.</returns>
        /// <see cref="" />
        public int GetGhostsActive() {
             InternalUnsafeMethods.GetGhostsActive__Args _args = new InternalUnsafeMethods.GetGhostsActive__Args() {
             };
             int _engineResult = InternalUnsafeMethods.GetGhostsActive()(ObjectPtr, _args);
             return _engineResult;
        }

        /// <summary>Connects with the server that is running within the same process as the client.</summary>
        /// <description>
        /// 
        /// </description>
        /// <returns>An error text message upon failure, or an empty string when successful.</returns>
        /// <see cref="See" />
        public string ConnectLocal() {
             InternalUnsafeMethods.ConnectLocal__Args _args = new InternalUnsafeMethods.ConnectLocal__Args() {
             };
             IntPtr _engineResult = InternalUnsafeMethods.ConnectLocal()(ObjectPtr, _args);
             return StringMarshal.IntPtrToUtf8String(_engineResult);
        }

        /// <summary>Connects to the remote address.</summary>
        /// <description>
        /// Attempts to connect with another NetConnection on the given address.  Typically once connected, a game's information is passed along from the server to the client, followed by the player entering the game world.  The actual procedure is dependent on the NetConnection subclass that is used.  i.e. GameConnection.
        /// </description>
        /// <param name="remoteAddress">The address to connect to in the form of IP:&lt;address&gt;:&lt;port&rt; although the <i>IP:</i> portion is optional.  The <i>address</i> portion may be in the form of w.x.y.z or as a host name, in which case a DNS lookup will be performed.  You may also substitue the word <i>broadcast</i> for the address to broadcast the connect request over the local subnet.</param>
        /// <see cref="NetConnection::connectLocal() to connect to a server running within the same process as the client." />
        public void Connect(string remoteAddress) {
             InternalUnsafeMethods.Connect__Args _args = new InternalUnsafeMethods.Connect__Args() {
                remoteAddress = remoteAddress,
             };
             InternalUnsafeMethods.Connect()(ObjectPtr, _args);
        }

        /// <summary>On server or client, convert a real id to the ghost id for this connection.</summary>
        /// <description>
        /// Torque's network ghosting system only exchanges ghost ID's between the server and client.  Use this method on the server or client to discover an object's ghost ID based on its real SimObject ID.
        /// </description>
        /// <param name="realID">The real SimObject ID of the object.</param>
        /// <returns>The ghost ID of the object for this connection, or -1 if it could not be resolved.</returns>
        /// <see cref="" />
        public int GetGhostID(int realID) {
             InternalUnsafeMethods.GetGhostID__Args _args = new InternalUnsafeMethods.GetGhostID__Args() {
                realID = realID,
             };
             int _engineResult = InternalUnsafeMethods.GetGhostID()(ObjectPtr, _args);
             return _engineResult;
        }

        /// <summary>On the server, convert a ghost ID from this connection to a real SimObject ID.</summary>
        /// <description>
        /// Torque's network ghosting system only exchanges ghost ID's between the server and client.  Use this method on the server to discover an object's local SimObject ID when you only have a ghost ID.
        /// </description>
        /// <param name="ghostID">The ghost ID of the object as sent by the server.</param>
        /// <returns>The SimObject ID of the object, or 0 if it could not be resolved.</returns>
        /// <code>
        /// %object = %client.resolveObjectFromGhostIndex( %ghostId );
        /// </code>
        /// <see cref="" />
        public int ResolveObjectFromGhostIndex(int ghostID) {
             InternalUnsafeMethods.ResolveObjectFromGhostIndex__Args _args = new InternalUnsafeMethods.ResolveObjectFromGhostIndex__Args() {
                ghostID = ghostID,
             };
             int _engineResult = InternalUnsafeMethods.ResolveObjectFromGhostIndex()(ObjectPtr, _args);
             return _engineResult;
        }

        /// <summary>On the client, convert a ghost ID from this connection to a real SimObject ID.</summary>
        /// <description>
        /// Torque's network ghosting system only exchanges ghost ID's between the server and client.  Use this method on the client to discover an object's local SimObject ID when you only have a ghost ID.
        /// </description>
        /// <param name="ghostID">The ghost ID of the object as sent by the server.</param>
        /// <returns>The SimObject ID of the object, or 0 if it could not be resolved.</returns>
        /// <code>
        /// %object = ServerConnection.resolveGhostID( %ghostId );
        /// </code>
        /// <see cref="" />
        public int ResolveGhostID(int ghostID) {
             InternalUnsafeMethods.ResolveGhostID__Args _args = new InternalUnsafeMethods.ResolveGhostID__Args() {
                ghostID = ghostID,
             };
             int _engineResult = InternalUnsafeMethods.ResolveGhostID()(ObjectPtr, _args);
             return _engineResult;
        }

        /// <summary>Ensures that all configured packet rates and sizes meet minimum requirements.</summary>
        /// <description>
        /// This method is normally only called when a NetConnection class is first constructed.  It need only be manually called if the global variables that set the packet rate or size have changed.
        /// </description>
        /// <remarks> If </remarks>
        public void CheckMaxRate() {
             InternalUnsafeMethods.CheckMaxRate__Args _args = new InternalUnsafeMethods.CheckMaxRate__Args() {
             };
             InternalUnsafeMethods.CheckMaxRate()(ObjectPtr, _args);
        }

        /// <summary>Returns the percentage of packets lost per tick.</summary>
        /// <description>
        /// 
        /// </description>
        /// <remarks> This method is not yet hooked up.
        /// </remarks>
        public int GetPacketLoss() {
             InternalUnsafeMethods.GetPacketLoss__Args _args = new InternalUnsafeMethods.GetPacketLoss__Args() {
             };
             int _engineResult = InternalUnsafeMethods.GetPacketLoss()(ObjectPtr, _args);
             return _engineResult;
        }

        /// <summary>Returns the average round trip time (in ms) for the connection.</summary>
        /// <description>
        /// The round trip time is recalculated every time a notify packet is received.  Notify packets are used to information the connection that the far end successfully received the sent packet.
        /// </description>
        public int GetPing() {
             InternalUnsafeMethods.GetPing__Args _args = new InternalUnsafeMethods.GetPing__Args() {
             };
             int _engineResult = InternalUnsafeMethods.GetPing()(ObjectPtr, _args);
             return _engineResult;
        }

        /// <summary>Simulate network issues on the connection for testing.</summary>
        /// <description>
        /// 
        /// </description>
        /// <param name="packetLoss">The fraction of packets that will be lost.  Ranges from 0.0 (no loss) to 1.0 (complete loss)</param>
        /// <param name="delay">Delays packets being transmitted by simulating a particular ping.  This is an absolute integer, measured in ms.</param>
        public void SetSimulatedNetParams(float packetLoss, int delay) {
             InternalUnsafeMethods.SetSimulatedNetParams__Args _args = new InternalUnsafeMethods.SetSimulatedNetParams__Args() {
                packetLoss = packetLoss,
                delay = delay,
             };
             InternalUnsafeMethods.SetSimulatedNetParams()(ObjectPtr, _args);
        }

        /// <summary>Returns the far end network address for the connection.</summary>
        /// <description>
        /// The address will be in one of the following forms:
        /// - <b>IP:Broadcast:&lt;port&gt;</b> for broadcast type addresses
        /// - <b>IP:&lt;address&gt;:&lt;port&gt;</b> for IP addresses
        /// - <b>local</b> when connected locally (server and client running in same process
        /// </description>
        public string GetAddress() {
             InternalUnsafeMethods.GetAddress__Args _args = new InternalUnsafeMethods.GetAddress__Args() {
             };
             IntPtr _engineResult = InternalUnsafeMethods.GetAddress()(ObjectPtr, _args);
             return StringMarshal.IntPtrToUtf8String(_engineResult);
        }

        /// <summary>On the server, resets the connection to indicate that motion spline paths have not been transmitted.</summary>
        /// <description>
        /// Typically when a mission has ended on the server, all connected clients are informed of this change and their connections are reset back to a starting state.  This method resets a connection on the server to indicate that motion spline paths have not been transmitted.
        /// </description>
        /// <code>
        /// // Inform the clients
        ///    for (%clientIndex = 0; %clientIndex < ClientGroup.getCount(); %clientIndex++)
        ///    {
        ///       // clear ghosts and paths from all clients
        ///       %cl = ClientGroup.getObject(%clientIndex);
        ///       %cl.endMission();
        ///       %cl.resetGhosting();
        ///       %cl.clearPaths();
        ///    }
        /// </code>
        /// <see cref="transmitPaths()" />
        /// <see cref="Path" />
        public void ClearPaths() {
             InternalUnsafeMethods.ClearPaths__Args _args = new InternalUnsafeMethods.ClearPaths__Args() {
             };
             InternalUnsafeMethods.ClearPaths()(ObjectPtr, _args);
        }

        /// <summary>Sent by the server during phase 2 of the mission download to update motion spline paths.</summary>
        /// <description>
        /// The server transmits all spline motion paths that are within the mission (Path) separate from other objects.  This is due to the potentially large number of nodes within each path, which may saturate a packet sent to the client.  By managing this step separately, Torque has finer control over how packets are organised vs. doing it during the ghosting stage.
        /// 
        /// Internally a PathManager is used to track all paths defined within a mission on the server, and each one is transmitted using a PathManagerEvent.  The client side collects these events and builds the given paths within its own PathManager.  This is typically done during the standard mission start phase 2 when following Torque's example mission startup sequence.
        /// 
        /// When a mission is ended, all paths need to be cleared from their respective path managers.
        /// </description>
        /// <code>
        /// function serverCmdMissionStartPhase2Ack(%client, %seq, %playerDB)
        /// {
        ///    // Make sure to ignore calls from a previous mission load
        ///    if (%seq != $missionSequence || !$MissionRunning)
        ///       return;
        ///    if (%client.currentPhase != 1.5)
        ///       return;
        ///    %client.currentPhase = 2;
        /// 
        ///    // Set the player datablock choice
        ///    %client.playerDB = %playerDB;
        /// 
        ///    // Update mission paths (SimPath), this needs to get there before the objects.
        ///    %client.transmitPaths();
        /// 
        ///    // Start ghosting objects to the client
        ///    %client.activateGhosting();
        /// }
        /// </code>
        /// <see cref="clearPaths()" />
        /// <see cref="Path" />
        public void TransmitPaths() {
             InternalUnsafeMethods.TransmitPaths__Args _args = new InternalUnsafeMethods.TransmitPaths__Args() {
             };
             InternalUnsafeMethods.TransmitPaths()(ObjectPtr, _args);
        }

        /// <description>
        /// Get the type info object for the NetConnection class.
        /// </description>
        /// <returns>The type info object for NetConnection</returns>
        public static EngineTypeInfo StaticGetType() {
             InternalUnsafeMethods.StaticGetType__Args _args = new InternalUnsafeMethods.StaticGetType__Args() {
             };
             IntPtr _engineResult = InternalUnsafeMethods.StaticGetType()(_args);
             return new EngineTypeInfo(_engineResult);
        }
    }
}