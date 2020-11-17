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
    /// <summary>Superclass for all ghostable networked objects.</summary>
    /// <description>
    /// 
    /// </description>
    public unsafe class NetObject : SimGroup {
        public NetObject(bool pRegister = false) 
            : base(pRegister) {
        }
        
        public NetObject(string pName, bool pRegister) 
            : this(false) {
            Name = pName;
            if (pRegister) {
                RegisterObject();
            }
        }
        
        public NetObject(string pName) 
            : this(pName, false) {
        }
        
        public NetObject(string pName, string pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(Engine.Sim.FindObject<SimObject>(pParent));
        }
        
        public NetObject(string pName, SimObject pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(pParent);
        }
        
        public NetObject(SimObject pObj) 
            : base(pObj) {
        }
        
        public NetObject(IntPtr pObj) 
            : base(pObj) {
        }
        
		protected override void CreateObjectPtr()
		{
			ObjectPtr = InternalUnsafeMethods.Create()(new InternalUnsafeMethods.Create__Args());
		}

        #region UnsafeNativeMethods
        new internal struct InternalUnsafeMethods {
            [StructLayout(LayoutKind.Sequential)]
            internal struct ClearScopeAlways__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _ClearScopeAlways(IntPtr _this, ClearScopeAlways__Args args);
            private static _ClearScopeAlways _ClearScopeAlwaysFunc;
            internal static _ClearScopeAlways ClearScopeAlways() {
                if (_ClearScopeAlwaysFunc == null) {
                    _ClearScopeAlwaysFunc =
                        (_ClearScopeAlways)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnNetObject_clearScopeAlways"), typeof(_ClearScopeAlways));
                }
                
                return _ClearScopeAlwaysFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct IsServerObject__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            [return: MarshalAs(UnmanagedType.I1)]
            internal delegate bool _IsServerObject(IntPtr _this, IsServerObject__Args args);
            private static _IsServerObject _IsServerObjectFunc;
            internal static _IsServerObject IsServerObject() {
                if (_IsServerObjectFunc == null) {
                    _IsServerObjectFunc =
                        (_IsServerObject)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnNetObject_isServerObject"), typeof(_IsServerObject));
                }
                
                return _IsServerObjectFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct IsClientObject__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            [return: MarshalAs(UnmanagedType.I1)]
            internal delegate bool _IsClientObject(IntPtr _this, IsClientObject__Args args);
            private static _IsClientObject _IsClientObjectFunc;
            internal static _IsClientObject IsClientObject() {
                if (_IsClientObjectFunc == null) {
                    _IsClientObjectFunc =
                        (_IsClientObject)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnNetObject_isClientObject"), typeof(_IsClientObject));
                }
                
                return _IsClientObjectFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct GetServerObject__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate int _GetServerObject(IntPtr _this, GetServerObject__Args args);
            private static _GetServerObject _GetServerObjectFunc;
            internal static _GetServerObject GetServerObject() {
                if (_GetServerObjectFunc == null) {
                    _GetServerObjectFunc =
                        (_GetServerObject)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnNetObject_getServerObject"), typeof(_GetServerObject));
                }
                
                return _GetServerObjectFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct GetClientObject__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate int _GetClientObject(IntPtr _this, GetClientObject__Args args);
            private static _GetClientObject _GetClientObjectFunc;
            internal static _GetClientObject GetClientObject() {
                if (_GetClientObjectFunc == null) {
                    _GetClientObjectFunc =
                        (_GetClientObject)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnNetObject_getClientObject"), typeof(_GetClientObject));
                }
                
                return _GetClientObjectFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct GetGhostID__Args
            {
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
                                "fnNetObject_getGhostID"), typeof(_GetGhostID));
                }
                
                return _GetGhostIDFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct SetScopeAlways__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _SetScopeAlways(IntPtr _this, SetScopeAlways__Args args);
            private static _SetScopeAlways _SetScopeAlwaysFunc;
            internal static _SetScopeAlways SetScopeAlways() {
                if (_SetScopeAlwaysFunc == null) {
                    _SetScopeAlwaysFunc =
                        (_SetScopeAlways)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnNetObject_setScopeAlways"), typeof(_SetScopeAlways));
                }
                
                return _SetScopeAlwaysFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct ClearScopeToClient__Args
            {
                internal IntPtr client;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _ClearScopeToClient(IntPtr _this, ClearScopeToClient__Args args);
            private static _ClearScopeToClient _ClearScopeToClientFunc;
            internal static _ClearScopeToClient ClearScopeToClient() {
                if (_ClearScopeToClientFunc == null) {
                    _ClearScopeToClientFunc =
                        (_ClearScopeToClient)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnNetObject_clearScopeToClient"), typeof(_ClearScopeToClient));
                }
                
                return _ClearScopeToClientFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct ScopeToClient__Args
            {
                internal IntPtr client;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _ScopeToClient(IntPtr _this, ScopeToClient__Args args);
            private static _ScopeToClient _ScopeToClientFunc;
            internal static _ScopeToClient ScopeToClient() {
                if (_ScopeToClientFunc == null) {
                    _ScopeToClientFunc =
                        (_ScopeToClient)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnNetObject_scopeToClient"), typeof(_ScopeToClient));
                }
                
                return _ScopeToClientFunc;
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
                                "fnNetObject_staticGetType"), typeof(_StaticGetType));
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
                                "fnNetObject_create"), typeof(_Create));
                }
                
                return _CreateFunc;
            }
        }
        #endregion

        /// <summary>Clears the scope always flag on this object.</summary>
        /// <description>
        /// 
        /// </description>
        public void ClearScopeAlways() {
             InternalUnsafeMethods.ClearScopeAlways__Args _args = new InternalUnsafeMethods.ClearScopeAlways__Args() {
             };
             InternalUnsafeMethods.ClearScopeAlways()(ObjectPtr, _args);
        }

        /// <summary>Checks if an object resides on the server.</summary>
        /// <description>
        /// 
        /// </description>
        /// <returns>True if the object resides on the server, false otherwise.</returns>
        public bool IsServerObject() {
             InternalUnsafeMethods.IsServerObject__Args _args = new InternalUnsafeMethods.IsServerObject__Args() {
             };
             bool _engineResult = InternalUnsafeMethods.IsServerObject()(ObjectPtr, _args);
             return _engineResult;
        }

        /// <summary>Called to check if an object resides on the clientside.</summary>
        /// <description>
        /// 
        /// </description>
        /// <returns>True if the object resides on the client, false otherwise.</returns>
        public bool IsClientObject() {
             InternalUnsafeMethods.IsClientObject__Args _args = new InternalUnsafeMethods.IsClientObject__Args() {
             };
             bool _engineResult = InternalUnsafeMethods.IsClientObject()(ObjectPtr, _args);
             return _engineResult;
        }

        /// <summary>Returns a pointer to the client object when on a local connection.</summary>
        /// <description>
        /// Short-Circuit-Netorking: this is only valid for a local-client / singleplayer situation.
        /// </description>
        /// <returns>The SimObject ID of the server object.</returns>
        /// <code>
        /// // Psuedo-code, some values left out for this example
        /// %node = new ParticleEmitterNode(){};
        /// %serverObject = %node.getServerObject();
        /// if(isObject(%serverObject)
        /// 	%serverObject.setTransform("0 0 0");
        /// </code>
        /// <see cref="" />
        public int GetServerObject() {
             InternalUnsafeMethods.GetServerObject__Args _args = new InternalUnsafeMethods.GetServerObject__Args() {
             };
             int _engineResult = InternalUnsafeMethods.GetServerObject()(ObjectPtr, _args);
             return _engineResult;
        }

        /// <summary>Returns a pointer to the client object when on a local connection.</summary>
        /// <description>
        /// Short-Circuit-Networking: this is only valid for a local-client / singleplayer situation.
        /// </description>
        /// <returns>the SimObject ID of the client object.</returns>
        /// <code>
        /// // Psuedo-code, some values left out for this example
        /// %node = new ParticleEmitterNode(){};
        /// %clientObject = %node.getClientObject();
        /// if(isObject(%clientObject)
        /// 	%clientObject.setTransform("0 0 0");
        /// </code>
        /// <see cref="" />
        public int GetClientObject() {
             InternalUnsafeMethods.GetClientObject__Args _args = new InternalUnsafeMethods.GetClientObject__Args() {
             };
             int _engineResult = InternalUnsafeMethods.GetClientObject()(ObjectPtr, _args);
             return _engineResult;
        }

        /// <summary>Get the ghost index of this object from the server.</summary>
        /// <description>
        /// 
        /// </description>
        /// <returns>The ghost ID of this NetObject on the server</returns>
        /// <code>
        /// %ghostID = LocalClientConnection.getGhostId( %serverObject );
        /// </code>
        public int GetGhostID() {
             InternalUnsafeMethods.GetGhostID__Args _args = new InternalUnsafeMethods.GetGhostID__Args() {
             };
             int _engineResult = InternalUnsafeMethods.GetGhostID()(ObjectPtr, _args);
             return _engineResult;
        }

        /// <summary>Always scope this object on all connections.</summary>
        /// <description>
        /// The object is marked as ScopeAlways and is immediately ghosted to all active connections.  This function has no effect if the object is not marked as Ghostable.
        /// </description>
        public void SetScopeAlways() {
             InternalUnsafeMethods.SetScopeAlways__Args _args = new InternalUnsafeMethods.SetScopeAlways__Args() {
             };
             InternalUnsafeMethods.SetScopeAlways()(ObjectPtr, _args);
        }

        /// <summary>Undo the effects of a scopeToClient() call.</summary>
        /// <description>
        /// 
        /// </description>
        /// <param name="client">The connection to remove this object's scoping from</param>
        /// <see cref="scopeToClient()" />
        public void ClearScopeToClient(NetConnection client) {
             InternalUnsafeMethods.ClearScopeToClient__Args _args = new InternalUnsafeMethods.ClearScopeToClient__Args() {
                client = client.ObjectPtr,
             };
             InternalUnsafeMethods.ClearScopeToClient()(ObjectPtr, _args);
        }

        /// <summary>Cause the NetObject to be forced as scoped on the specified NetConnection.</summary>
        /// <description>
        /// 
        /// </description>
        /// <param name="client">The connection this object will always be scoped to</param>
        /// <code>
        /// // Called to create new cameras in TorqueScript
        /// // %this - The active GameConnection
        /// // %spawnPoint - The spawn point location where we creat the camera
        /// function GameConnection::spawnCamera(%this, %spawnPoint)
        /// {
        /// 	// If this connection's camera exists
        /// 	if(isObject(%this.camera))
        /// 	{
        /// 		// Add it to the mission group to be cleaned up later
        /// 		MissionCleanup.add( %this.camera );
        /// 
        /// 		// Force it to scope to the client side
        /// 		%this.camera.scopeToClient(%this);
        /// 	}
        /// }
        /// </code>
        /// <see cref="clearScopeToClient()" />
        public void ScopeToClient(NetConnection client) {
             InternalUnsafeMethods.ScopeToClient__Args _args = new InternalUnsafeMethods.ScopeToClient__Args() {
                client = client.ObjectPtr,
             };
             InternalUnsafeMethods.ScopeToClient()(ObjectPtr, _args);
        }

        /// <description>
        /// Get the type info object for the NetObject class.
        /// </description>
        /// <returns>The type info object for NetObject</returns>
        public static EngineTypeInfo StaticGetType() {
             InternalUnsafeMethods.StaticGetType__Args _args = new InternalUnsafeMethods.StaticGetType__Args() {
             };
             IntPtr _engineResult = InternalUnsafeMethods.StaticGetType()(_args);
             return new EngineTypeInfo(_engineResult);
        }
    }
}