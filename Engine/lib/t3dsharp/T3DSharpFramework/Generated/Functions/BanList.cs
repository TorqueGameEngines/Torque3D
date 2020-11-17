using System;
using System.Collections.Generic;
using System.Runtime.InteropServices;
using T3DSharpFramework.Generated.Classes.Global;
using T3DSharpFramework.Generated.Classes.Net;
using T3DSharpFramework.Generated.Classes.Sim;
using T3DSharpFramework.Generated.Classes.Sim.Net;
using T3DSharpFramework.Generated.Enums.Global;
using T3DSharpFramework.Generated.Structs.Global;
using T3DSharpFramework.Generated.Structs.Gui;
using T3DSharpFramework.Generated.Structs.Math;
using T3DSharpFramework.Interop;

namespace T3DSharpFramework.Generated.Functions {

    public static unsafe class BanList {

        #region UnsafeNativeMethods
        new internal struct InternalUnsafeMethods {
            [StructLayout(LayoutKind.Sequential)]
            internal struct Export__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string filename;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _Export(Export__Args args);
            private static _Export _ExportFunc;
            internal static _Export Export() {
                if (_ExportFunc == null) {
                    _ExportFunc =
                        (_Export)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnBanList_export"), typeof(_Export));
                }
                
                return _ExportFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct IsBanned__Args
            {
                internal int uniqueId;
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string transportAddress;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            [return: MarshalAs(UnmanagedType.I1)]
            internal delegate bool _IsBanned(IsBanned__Args args);
            private static _IsBanned _IsBannedFunc;
            internal static _IsBanned IsBanned() {
                if (_IsBannedFunc == null) {
                    _IsBannedFunc =
                        (_IsBanned)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnBanList_isBanned"), typeof(_IsBanned));
                }
                
                return _IsBannedFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct RemoveBan__Args
            {
                internal int uniqueId;
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string transportAddress;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _RemoveBan(RemoveBan__Args args);
            private static _RemoveBan _RemoveBanFunc;
            internal static _RemoveBan RemoveBan() {
                if (_RemoveBanFunc == null) {
                    _RemoveBanFunc =
                        (_RemoveBan)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnBanList_removeBan"), typeof(_RemoveBan));
                }
                
                return _RemoveBanFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct Add__Args
            {
                internal int uniqueId;
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string transportAddress;
                internal int banLength;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _Add(Add__Args args);
            private static _Add _AddFunc;
            internal static _Add Add() {
                if (_AddFunc == null) {
                    _AddFunc =
                        (_Add)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnBanList_add"), typeof(_Add));
                }
                
                return _AddFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct AddAbsolute__Args
            {
                internal int uniqueId;
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string transportAddress;
                internal int banTime;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _AddAbsolute(AddAbsolute__Args args);
            private static _AddAbsolute _AddAbsoluteFunc;
            internal static _AddAbsolute AddAbsolute() {
                if (_AddAbsoluteFunc == null) {
                    _AddAbsoluteFunc =
                        (_AddAbsolute)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnBanList_addAbsolute"), typeof(_AddAbsolute));
                }
                
                return _AddAbsoluteFunc;
            }
        }
        #endregion

        /// <description>
        /// Dump the banlist to a file.
        /// </description>
        /// <param name="filename">Path of the file to write the list to.</param>
        public static void Export(string filename) {
             InternalUnsafeMethods.Export__Args _args = new InternalUnsafeMethods.Export__Args() {
                filename = filename,
             };
             InternalUnsafeMethods.Export()(_args);
        }

        /// <description>
        /// Is someone banned?
        /// </description>
        /// <param name="uniqueId">Unique ID of the player.</param>
        /// <param name="transportAddress">Address from which the player connected.</param>
        /// <code>
        /// //-----------------------------------------------------------------------------
        /// // This script function is called before a client connection
        /// // is accepted.  Returning  will accept the connection,
        /// // anything else will be sent back as an error to the client.
        /// // All the connect args are passed also to onConnectRequest
        /// function GameConnection::onConnectRequest( %client, %netAddress, %name )
        /// {
        /// 	  // Find out who is trying to connect
        /// 	  echo("Connect request from: "@ %netAddress);
        /// 
        /// 	  // Are they allowed in?
        /// 	  if(BanList::isBanned(%client.guid, %netAddress))
        /// 		  return "CR_YOUAREBANNED";
        /// 
        /// 	  // Is there room for an unbanned player?
        /// 	  if($Server::PlayerCount >= $pref::Server::MaxPlayers)
        /// 		  return "CR_SERVERFULL";
        /// 	  return ;
        /// }
        /// 
        /// </code>
        public static bool IsBanned(int uniqueId, string transportAddress) {
             InternalUnsafeMethods.IsBanned__Args _args = new InternalUnsafeMethods.IsBanned__Args() {
                uniqueId = uniqueId,
                transportAddress = transportAddress,
             };
             bool _engineResult = InternalUnsafeMethods.IsBanned()(_args);
             return _engineResult;
        }

        /// <description>
        /// Unban someone.
        /// </description>
        /// <param name="uniqueId">Unique ID of the player.</param>
        /// <param name="transportAddress">Address from which the player connected.</param>
        /// <code>
        /// BanList::removeBan(%userID, %ipAddress);
        /// </code>
        public static void RemoveBan(int uniqueId, string transportAddress) {
             InternalUnsafeMethods.RemoveBan__Args _args = new InternalUnsafeMethods.RemoveBan__Args() {
                uniqueId = uniqueId,
                transportAddress = transportAddress,
             };
             InternalUnsafeMethods.RemoveBan()(_args);
        }

        /// <description>
        /// Ban a user for banLength seconds.
        /// </description>
        /// <param name="uniqueId">Unique ID of the player.</param>
        /// <param name="transportAddress">Address from which the player connected.</param>
        /// <param name="banLength">Time period over which to ban the player.</param>
        /// <code>
        /// // Kick someone off the server
        /// // %client - This is the connection to the person we are kicking
        /// function kick(%client)
        /// {
        /// 		// Let the server know what happened
        /// 		messageAll( 'MsgAdminForce', '\c2The Admin has kicked %1.', %client.playerName);
        /// 
        /// 		// If it is not an AI Player, execute the ban.
        /// 		if (!%client.isAIControlled())
        /// 			BanList::add(%client.guid, %client.getAddress(), $pref::Server::KickBanTime);
        /// 
        /// 		// Let the player know they messed up
        /// 		%client.delete("You have been kicked from this server");
        /// }
        /// </code>
        public static void Add(int uniqueId, string transportAddress, int banLength) {
             InternalUnsafeMethods.Add__Args _args = new InternalUnsafeMethods.Add__Args() {
                uniqueId = uniqueId,
                transportAddress = transportAddress,
                banLength = banLength,
             };
             InternalUnsafeMethods.Add()(_args);
        }

        /// <description>
        /// Ban a user until a given time.
        /// </description>
        /// <param name="uniqueId">Unique ID of the player.</param>
        /// <param name="transportAddress">Address from which the player connected.</param>
        /// <param name="banTime">Time at which they will be allowed back in.</param>
        /// <code>
        /// // Kick someone off the server
        /// // %client - This is the connection to the person we are kicking
        /// function kick(%client)
        /// {
        /// 		// Let the server know what happened
        /// 		messageAll( 'MsgAdminForce', '\c2The Admin has kicked %1.', %client.playerName);
        /// 
        /// 		// If it is not an AI Player, execute the ban.
        /// 		if (!%client.isAIControlled())
        /// 			BanList::addAbsolute(%client.guid, %client.getAddress(), $pref::Server::KickBanTime);
        /// 
        /// 		// Let the player know they messed up
        /// 		%client.delete("You have been kicked from this server");
        /// }
        /// </code>
        public static void AddAbsolute(int uniqueId, string transportAddress, int banTime) {
             InternalUnsafeMethods.AddAbsolute__Args _args = new InternalUnsafeMethods.AddAbsolute__Args() {
                uniqueId = uniqueId,
                transportAddress = transportAddress,
                banTime = banTime,
             };
             InternalUnsafeMethods.AddAbsolute()(_args);
        }

    }
}