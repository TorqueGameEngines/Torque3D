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
    /// <summary>The game-specific subclass of NetConnection.</summary>
    /// <description>
    /// The GameConnection introduces the concept of the control object.  The control object is simply the object that the client is associated with that network connection controls.  By default the control object is an instance of the Player class, but can also be an instance of Camera (when editing the mission, for example), or any other ShapeBase derived class as appropriate for the game.
    /// 
    /// Torque uses a model in which the server is the authoritative master of the simulation.  To prevent clients from cheating, the server simulates all player moves and then tells the client where his player is in the world.  This model, while secure, can have problems.  If the network latency is high, this round-trip time can give the player a very noticeable sense of movement lag.  To correct this problem, the game uses a form of prediction - it simulates the movement of the control object on the client and on the server both.  This way the client doesn't need to wait for round-trip verification of his moves.  Only in the case of a force acting on the control object on the server that doesn't exist on the client does the client's position need to be forcefully changed.
    /// 
    /// To support this, all control objects (derivative of ShapeBase) must supply a writePacketData() and readPacketData() function that send enough data to accurately simulate the object on the client.  These functions are only called for the current control object, and only when the server can determine that the client's simulation is somehow out of sync with the server.  This occurs usually if the client is affected by a force not present on the server (like an interpolating object) or if the server object is affected by a server only force (such as the impulse from an explosion).
    /// 
    /// The Move structure is a 32 millisecond snapshot of player input, containing x, y, and z positional and rotational changes as well as trigger state changes. When time passes in the simulation moves are collected (depending on how much time passes), and applied to the current control object on the client. The same moves are then packed over to the server in GameConnection::writePacket(), for processing on the server's version of the control object.
    /// </description>
    /// <see cref="" />
    public unsafe class GameConnection : NetConnection {
        public GameConnection(bool pRegister = false) 
            : base(pRegister) {
        }
        
        public GameConnection(string pName, bool pRegister) 
            : this(false) {
            Name = pName;
            if (pRegister) {
                RegisterObject();
            }
        }
        
        public GameConnection(string pName) 
            : this(pName, false) {
        }
        
        public GameConnection(string pName, string pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(Engine.Sim.FindObject<SimObject>(pParent));
        }
        
        public GameConnection(string pName, SimObject pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(pParent);
        }
        
        public GameConnection(SimObject pObj) 
            : base(pObj) {
        }
        
        public GameConnection(IntPtr pObj) 
            : base(pObj) {
        }
        
		protected override void CreateObjectPtr()
		{
			ObjectPtr = InternalUnsafeMethods.Create()(new InternalUnsafeMethods.Create__Args());
		}

        #region UnsafeNativeMethods
        new internal struct InternalUnsafeMethods {
            [StructLayout(LayoutKind.Sequential)]
            internal struct LoadDatablockCache_Continue__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            [return: MarshalAs(UnmanagedType.I1)]
            internal delegate bool _LoadDatablockCache_Continue(IntPtr _this, LoadDatablockCache_Continue__Args args);
            private static _LoadDatablockCache_Continue _LoadDatablockCache_ContinueFunc;
            internal static _LoadDatablockCache_Continue LoadDatablockCache_Continue() {
                if (_LoadDatablockCache_ContinueFunc == null) {
                    _LoadDatablockCache_ContinueFunc =
                        (_LoadDatablockCache_Continue)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnGameConnection_loadDatablockCache_Continue"), typeof(_LoadDatablockCache_Continue));
                }
                
                return _LoadDatablockCache_ContinueFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct LoadDatablockCache_Begin__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            [return: MarshalAs(UnmanagedType.I1)]
            internal delegate bool _LoadDatablockCache_Begin(IntPtr _this, LoadDatablockCache_Begin__Args args);
            private static _LoadDatablockCache_Begin _LoadDatablockCache_BeginFunc;
            internal static _LoadDatablockCache_Begin LoadDatablockCache_Begin() {
                if (_LoadDatablockCache_BeginFunc == null) {
                    _LoadDatablockCache_BeginFunc =
                        (_LoadDatablockCache_Begin)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnGameConnection_loadDatablockCache_Begin"), typeof(_LoadDatablockCache_Begin));
                }
                
                return _LoadDatablockCache_BeginFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct LoadDatablockCache__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _LoadDatablockCache(IntPtr _this, LoadDatablockCache__Args args);
            private static _LoadDatablockCache _LoadDatablockCacheFunc;
            internal static _LoadDatablockCache LoadDatablockCache() {
                if (_LoadDatablockCacheFunc == null) {
                    _LoadDatablockCacheFunc =
                        (_LoadDatablockCache)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnGameConnection_loadDatablockCache"), typeof(_LoadDatablockCache));
                }
                
                return _LoadDatablockCacheFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct SaveDatablockCache__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _SaveDatablockCache(IntPtr _this, SaveDatablockCache__Args args);
            private static _SaveDatablockCache _SaveDatablockCacheFunc;
            internal static _SaveDatablockCache SaveDatablockCache() {
                if (_SaveDatablockCacheFunc == null) {
                    _SaveDatablockCacheFunc =
                        (_SaveDatablockCache)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnGameConnection_saveDatablockCache"), typeof(_SaveDatablockCache));
                }
                
                return _SaveDatablockCacheFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct SetSelectedObjFromPreSelected__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _SetSelectedObjFromPreSelected(IntPtr _this, SetSelectedObjFromPreSelected__Args args);
            private static _SetSelectedObjFromPreSelected _SetSelectedObjFromPreSelectedFunc;
            internal static _SetSelectedObjFromPreSelected SetSelectedObjFromPreSelected() {
                if (_SetSelectedObjFromPreSelectedFunc == null) {
                    _SetSelectedObjFromPreSelectedFunc =
                        (_SetSelectedObjFromPreSelected)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnGameConnection_setSelectedObjFromPreSelected"), typeof(_SetSelectedObjFromPreSelected));
                }
                
                return _SetSelectedObjFromPreSelectedFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct ClearPreSelectedObj__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _ClearPreSelectedObj(IntPtr _this, ClearPreSelectedObj__Args args);
            private static _ClearPreSelectedObj _ClearPreSelectedObjFunc;
            internal static _ClearPreSelectedObj ClearPreSelectedObj() {
                if (_ClearPreSelectedObjFunc == null) {
                    _ClearPreSelectedObjFunc =
                        (_ClearPreSelectedObj)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnGameConnection_clearPreSelectedObj"), typeof(_ClearPreSelectedObj));
                }
                
                return _ClearPreSelectedObjFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct SetPreSelectedObjFromRollover__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _SetPreSelectedObjFromRollover(IntPtr _this, SetPreSelectedObjFromRollover__Args args);
            private static _SetPreSelectedObjFromRollover _SetPreSelectedObjFromRolloverFunc;
            internal static _SetPreSelectedObjFromRollover SetPreSelectedObjFromRollover() {
                if (_SetPreSelectedObjFromRolloverFunc == null) {
                    _SetPreSelectedObjFromRolloverFunc =
                        (_SetPreSelectedObjFromRollover)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnGameConnection_setPreSelectedObjFromRollover"), typeof(_SetPreSelectedObjFromRollover));
                }
                
                return _SetPreSelectedObjFromRolloverFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct ClearSelectedObj__Args
            {
                [MarshalAs(UnmanagedType.I1)]
                internal bool propagate_to_client;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _ClearSelectedObj(IntPtr _this, ClearSelectedObj__Args args);
            private static _ClearSelectedObj _ClearSelectedObjFunc;
            internal static _ClearSelectedObj ClearSelectedObj() {
                if (_ClearSelectedObjFunc == null) {
                    _ClearSelectedObjFunc =
                        (_ClearSelectedObj)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnGameConnection_clearSelectedObj"), typeof(_ClearSelectedObj));
                }
                
                return _ClearSelectedObjFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct GetSelectedObj__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate IntPtr _GetSelectedObj(IntPtr _this, GetSelectedObj__Args args);
            private static _GetSelectedObj _GetSelectedObjFunc;
            internal static _GetSelectedObj GetSelectedObj() {
                if (_GetSelectedObjFunc == null) {
                    _GetSelectedObjFunc =
                        (_GetSelectedObj)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnGameConnection_getSelectedObj"), typeof(_GetSelectedObj));
                }
                
                return _GetSelectedObjFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct SetSelectedObj__Args
            {
                internal IntPtr obj;
                [MarshalAs(UnmanagedType.I1)]
                internal bool propagate_to_client;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            [return: MarshalAs(UnmanagedType.I1)]
            internal delegate bool _SetSelectedObj(IntPtr _this, SetSelectedObj__Args args);
            private static _SetSelectedObj _SetSelectedObjFunc;
            internal static _SetSelectedObj SetSelectedObj() {
                if (_SetSelectedObjFunc == null) {
                    _SetSelectedObjFunc =
                        (_SetSelectedObj)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnGameConnection_setSelectedObj"), typeof(_SetSelectedObj));
                }
                
                return _SetSelectedObjFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct GetVisibleGhostDistance__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate float _GetVisibleGhostDistance(IntPtr _this, GetVisibleGhostDistance__Args args);
            private static _GetVisibleGhostDistance _GetVisibleGhostDistanceFunc;
            internal static _GetVisibleGhostDistance GetVisibleGhostDistance() {
                if (_GetVisibleGhostDistanceFunc == null) {
                    _GetVisibleGhostDistanceFunc =
                        (_GetVisibleGhostDistance)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnGameConnection_getVisibleGhostDistance"), typeof(_GetVisibleGhostDistance));
                }
                
                return _GetVisibleGhostDistanceFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct SetVisibleGhostDistance__Args
            {
                internal float dist;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _SetVisibleGhostDistance(IntPtr _this, SetVisibleGhostDistance__Args args);
            private static _SetVisibleGhostDistance _SetVisibleGhostDistanceFunc;
            internal static _SetVisibleGhostDistance SetVisibleGhostDistance() {
                if (_SetVisibleGhostDistanceFunc == null) {
                    _SetVisibleGhostDistanceFunc =
                        (_SetVisibleGhostDistance)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnGameConnection_setVisibleGhostDistance"), typeof(_SetVisibleGhostDistance));
                }
                
                return _SetVisibleGhostDistanceFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct GetControlSchemeAbsoluteRotation__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            [return: MarshalAs(UnmanagedType.I1)]
            internal delegate bool _GetControlSchemeAbsoluteRotation(IntPtr _this, GetControlSchemeAbsoluteRotation__Args args);
            private static _GetControlSchemeAbsoluteRotation _GetControlSchemeAbsoluteRotationFunc;
            internal static _GetControlSchemeAbsoluteRotation GetControlSchemeAbsoluteRotation() {
                if (_GetControlSchemeAbsoluteRotationFunc == null) {
                    _GetControlSchemeAbsoluteRotationFunc =
                        (_GetControlSchemeAbsoluteRotation)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnGameConnection_getControlSchemeAbsoluteRotation"), typeof(_GetControlSchemeAbsoluteRotation));
                }
                
                return _GetControlSchemeAbsoluteRotationFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct SetControlSchemeParameters__Args
            {
                [MarshalAs(UnmanagedType.I1)]
                internal bool absoluteRotation;
                [MarshalAs(UnmanagedType.I1)]
                internal bool addYawToAbsRot;
                [MarshalAs(UnmanagedType.I1)]
                internal bool addPitchToAbsRot;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _SetControlSchemeParameters(IntPtr _this, SetControlSchemeParameters__Args args);
            private static _SetControlSchemeParameters _SetControlSchemeParametersFunc;
            internal static _SetControlSchemeParameters SetControlSchemeParameters() {
                if (_SetControlSchemeParametersFunc == null) {
                    _SetControlSchemeParametersFunc =
                        (_SetControlSchemeParameters)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnGameConnection_setControlSchemeParameters"), typeof(_SetControlSchemeParameters));
                }
                
                return _SetControlSchemeParametersFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct SetFirstPerson__Args
            {
                [MarshalAs(UnmanagedType.I1)]
                internal bool firstPerson;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _SetFirstPerson(IntPtr _this, SetFirstPerson__Args args);
            private static _SetFirstPerson _SetFirstPersonFunc;
            internal static _SetFirstPerson SetFirstPerson() {
                if (_SetFirstPersonFunc == null) {
                    _SetFirstPersonFunc =
                        (_SetFirstPerson)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnGameConnection_setFirstPerson"), typeof(_SetFirstPerson));
                }
                
                return _SetFirstPersonFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct IsFirstPerson__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            [return: MarshalAs(UnmanagedType.I1)]
            internal delegate bool _IsFirstPerson(IntPtr _this, IsFirstPerson__Args args);
            private static _IsFirstPerson _IsFirstPersonFunc;
            internal static _IsFirstPerson IsFirstPerson() {
                if (_IsFirstPersonFunc == null) {
                    _IsFirstPersonFunc =
                        (_IsFirstPerson)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnGameConnection_isFirstPerson"), typeof(_IsFirstPerson));
                }
                
                return _IsFirstPersonFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct ClearCameraObject__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _ClearCameraObject(IntPtr _this, ClearCameraObject__Args args);
            private static _ClearCameraObject _ClearCameraObjectFunc;
            internal static _ClearCameraObject ClearCameraObject() {
                if (_ClearCameraObjectFunc == null) {
                    _ClearCameraObjectFunc =
                        (_ClearCameraObject)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnGameConnection_clearCameraObject"), typeof(_ClearCameraObject));
                }
                
                return _ClearCameraObjectFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct GetCameraObject__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate IntPtr _GetCameraObject(IntPtr _this, GetCameraObject__Args args);
            private static _GetCameraObject _GetCameraObjectFunc;
            internal static _GetCameraObject GetCameraObject() {
                if (_GetCameraObjectFunc == null) {
                    _GetCameraObjectFunc =
                        (_GetCameraObject)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnGameConnection_getCameraObject"), typeof(_GetCameraObject));
                }
                
                return _GetCameraObjectFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct SetCameraObject__Args
            {
                internal IntPtr camera;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            [return: MarshalAs(UnmanagedType.I1)]
            internal delegate bool _SetCameraObject(IntPtr _this, SetCameraObject__Args args);
            private static _SetCameraObject _SetCameraObjectFunc;
            internal static _SetCameraObject SetCameraObject() {
                if (_SetCameraObjectFunc == null) {
                    _SetCameraObjectFunc =
                        (_SetCameraObject)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnGameConnection_setCameraObject"), typeof(_SetCameraObject));
                }
                
                return _SetCameraObjectFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct GetServerConnection__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate int _GetServerConnection(GetServerConnection__Args args);
            private static _GetServerConnection _GetServerConnectionFunc;
            internal static _GetServerConnection GetServerConnection() {
                if (_GetServerConnectionFunc == null) {
                    _GetServerConnectionFunc =
                        (_GetServerConnection)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnGameConnection_getServerConnection"), typeof(_GetServerConnection));
                }
                
                return _GetServerConnectionFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct ListClassIDs__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _ListClassIDs(IntPtr _this, ListClassIDs__Args args);
            private static _ListClassIDs _ListClassIDsFunc;
            internal static _ListClassIDs ListClassIDs() {
                if (_ListClassIDsFunc == null) {
                    _ListClassIDsFunc =
                        (_ListClassIDs)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnGameConnection_listClassIDs"), typeof(_ListClassIDs));
                }
                
                return _ListClassIDsFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct IsDemoRecording__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            [return: MarshalAs(UnmanagedType.I1)]
            internal delegate bool _IsDemoRecording(IntPtr _this, IsDemoRecording__Args args);
            private static _IsDemoRecording _IsDemoRecordingFunc;
            internal static _IsDemoRecording IsDemoRecording() {
                if (_IsDemoRecordingFunc == null) {
                    _IsDemoRecordingFunc =
                        (_IsDemoRecording)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnGameConnection_isDemoRecording"), typeof(_IsDemoRecording));
                }
                
                return _IsDemoRecordingFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct IsDemoPlaying__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            [return: MarshalAs(UnmanagedType.I1)]
            internal delegate bool _IsDemoPlaying(IntPtr _this, IsDemoPlaying__Args args);
            private static _IsDemoPlaying _IsDemoPlayingFunc;
            internal static _IsDemoPlaying IsDemoPlaying() {
                if (_IsDemoPlayingFunc == null) {
                    _IsDemoPlayingFunc =
                        (_IsDemoPlaying)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnGameConnection_isDemoPlaying"), typeof(_IsDemoPlaying));
                }
                
                return _IsDemoPlayingFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct PlayDemo__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string demoFileName;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            [return: MarshalAs(UnmanagedType.I1)]
            internal delegate bool _PlayDemo(IntPtr _this, PlayDemo__Args args);
            private static _PlayDemo _PlayDemoFunc;
            internal static _PlayDemo PlayDemo() {
                if (_PlayDemoFunc == null) {
                    _PlayDemoFunc =
                        (_PlayDemo)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnGameConnection_playDemo"), typeof(_PlayDemo));
                }
                
                return _PlayDemoFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct StopRecording__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _StopRecording(IntPtr _this, StopRecording__Args args);
            private static _StopRecording _StopRecordingFunc;
            internal static _StopRecording StopRecording() {
                if (_StopRecordingFunc == null) {
                    _StopRecordingFunc =
                        (_StopRecording)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnGameConnection_stopRecording"), typeof(_StopRecording));
                }
                
                return _StopRecordingFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct StartRecording__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string fileName;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _StartRecording(IntPtr _this, StartRecording__Args args);
            private static _StartRecording _StartRecordingFunc;
            internal static _StartRecording StartRecording() {
                if (_StartRecordingFunc == null) {
                    _StartRecordingFunc =
                        (_StartRecording)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnGameConnection_startRecording"), typeof(_StartRecording));
                }
                
                return _StartRecordingFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct Delete__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string reason;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _Delete(IntPtr _this, Delete__Args args);
            private static _Delete _DeleteFunc;
            internal static _Delete Delete() {
                if (_DeleteFunc == null) {
                    _DeleteFunc =
                        (_Delete)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnGameConnection_delete"), typeof(_Delete));
                }
                
                return _DeleteFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct SetMissionCRC__Args
            {
                internal int CRC;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _SetMissionCRC(IntPtr _this, SetMissionCRC__Args args);
            private static _SetMissionCRC _SetMissionCRCFunc;
            internal static _SetMissionCRC SetMissionCRC() {
                if (_SetMissionCRCFunc == null) {
                    _SetMissionCRCFunc =
                        (_SetMissionCRC)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnGameConnection_setMissionCRC"), typeof(_SetMissionCRC));
                }
                
                return _SetMissionCRCFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct SetBlackOut__Args
            {
                [MarshalAs(UnmanagedType.I1)]
                internal bool doFade;
                internal int timeMS;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _SetBlackOut(IntPtr _this, SetBlackOut__Args args);
            private static _SetBlackOut _SetBlackOutFunc;
            internal static _SetBlackOut SetBlackOut() {
                if (_SetBlackOutFunc == null) {
                    _SetBlackOutFunc =
                        (_SetBlackOut)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnGameConnection_setBlackOut"), typeof(_SetBlackOut));
                }
                
                return _SetBlackOutFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct GetWhiteOut__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate float _GetWhiteOut(IntPtr _this, GetWhiteOut__Args args);
            private static _GetWhiteOut _GetWhiteOutFunc;
            internal static _GetWhiteOut GetWhiteOut() {
                if (_GetWhiteOutFunc == null) {
                    _GetWhiteOutFunc =
                        (_GetWhiteOut)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnGameConnection_getWhiteOut"), typeof(_GetWhiteOut));
                }
                
                return _GetWhiteOutFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct GetDamageFlash__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate float _GetDamageFlash(IntPtr _this, GetDamageFlash__Args args);
            private static _GetDamageFlash _GetDamageFlashFunc;
            internal static _GetDamageFlash GetDamageFlash() {
                if (_GetDamageFlashFunc == null) {
                    _GetDamageFlashFunc =
                        (_GetDamageFlash)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnGameConnection_getDamageFlash"), typeof(_GetDamageFlash));
                }
                
                return _GetDamageFlashFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct GetControlCameraFov__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate float _GetControlCameraFov(IntPtr _this, GetControlCameraFov__Args args);
            private static _GetControlCameraFov _GetControlCameraFovFunc;
            internal static _GetControlCameraFov GetControlCameraFov() {
                if (_GetControlCameraFovFunc == null) {
                    _GetControlCameraFovFunc =
                        (_GetControlCameraFov)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnGameConnection_getControlCameraFov"), typeof(_GetControlCameraFov));
                }
                
                return _GetControlCameraFovFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct SetControlCameraFov__Args
            {
                internal float newFOV;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _SetControlCameraFov(IntPtr _this, SetControlCameraFov__Args args);
            private static _SetControlCameraFov _SetControlCameraFovFunc;
            internal static _SetControlCameraFov SetControlCameraFov() {
                if (_SetControlCameraFovFunc == null) {
                    _SetControlCameraFovFunc =
                        (_SetControlCameraFov)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnGameConnection_setControlCameraFov"), typeof(_SetControlCameraFov));
                }
                
                return _SetControlCameraFovFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct GetControlCameraDefaultFov__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate float _GetControlCameraDefaultFov(IntPtr _this, GetControlCameraDefaultFov__Args args);
            private static _GetControlCameraDefaultFov _GetControlCameraDefaultFovFunc;
            internal static _GetControlCameraDefaultFov GetControlCameraDefaultFov() {
                if (_GetControlCameraDefaultFovFunc == null) {
                    _GetControlCameraDefaultFovFunc =
                        (_GetControlCameraDefaultFov)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnGameConnection_getControlCameraDefaultFov"), typeof(_GetControlCameraDefaultFov));
                }
                
                return _GetControlCameraDefaultFovFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct ChaseCam__Args
            {
                internal int size;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            [return: MarshalAs(UnmanagedType.I1)]
            internal delegate bool _ChaseCam(IntPtr _this, ChaseCam__Args args);
            private static _ChaseCam _ChaseCamFunc;
            internal static _ChaseCam ChaseCam() {
                if (_ChaseCamFunc == null) {
                    _ChaseCamFunc =
                        (_ChaseCam)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnGameConnection_chaseCam"), typeof(_ChaseCam));
                }
                
                return _ChaseCamFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct Play3D__Args
            {
                internal IntPtr profile;
                internal IntPtr location;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            [return: MarshalAs(UnmanagedType.I1)]
            internal delegate bool _Play3D(IntPtr _this, Play3D__Args args);
            private static _Play3D _Play3DFunc;
            internal static _Play3D Play3D() {
                if (_Play3DFunc == null) {
                    _Play3DFunc =
                        (_Play3D)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnGameConnection_play3D"), typeof(_Play3D));
                }
                
                return _Play3DFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct Play2D__Args
            {
                internal IntPtr profile;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            [return: MarshalAs(UnmanagedType.I1)]
            internal delegate bool _Play2D(IntPtr _this, Play2D__Args args);
            private static _Play2D _Play2DFunc;
            internal static _Play2D Play2D() {
                if (_Play2DFunc == null) {
                    _Play2DFunc =
                        (_Play2D)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnGameConnection_play2D"), typeof(_Play2D));
                }
                
                return _Play2DFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct IsControlObjectRotDampedCamera__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            [return: MarshalAs(UnmanagedType.I1)]
            internal delegate bool _IsControlObjectRotDampedCamera(IntPtr _this, IsControlObjectRotDampedCamera__Args args);
            private static _IsControlObjectRotDampedCamera _IsControlObjectRotDampedCameraFunc;
            internal static _IsControlObjectRotDampedCamera IsControlObjectRotDampedCamera() {
                if (_IsControlObjectRotDampedCameraFunc == null) {
                    _IsControlObjectRotDampedCameraFunc =
                        (_IsControlObjectRotDampedCamera)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnGameConnection_isControlObjectRotDampedCamera"), typeof(_IsControlObjectRotDampedCamera));
                }
                
                return _IsControlObjectRotDampedCameraFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct IsAIControlled__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            [return: MarshalAs(UnmanagedType.I1)]
            internal delegate bool _IsAIControlled(IntPtr _this, IsAIControlled__Args args);
            private static _IsAIControlled _IsAIControlledFunc;
            internal static _IsAIControlled IsAIControlled() {
                if (_IsAIControlledFunc == null) {
                    _IsAIControlledFunc =
                        (_IsAIControlled)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnGameConnection_isAIControlled"), typeof(_IsAIControlled));
                }
                
                return _IsAIControlledFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct GetControlObject__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate IntPtr _GetControlObject(IntPtr _this, GetControlObject__Args args);
            private static _GetControlObject _GetControlObjectFunc;
            internal static _GetControlObject GetControlObject() {
                if (_GetControlObjectFunc == null) {
                    _GetControlObjectFunc =
                        (_GetControlObject)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnGameConnection_getControlObject"), typeof(_GetControlObject));
                }
                
                return _GetControlObjectFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct ClearDisplayDevice__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _ClearDisplayDevice(IntPtr _this, ClearDisplayDevice__Args args);
            private static _ClearDisplayDevice _ClearDisplayDeviceFunc;
            internal static _ClearDisplayDevice ClearDisplayDevice() {
                if (_ClearDisplayDeviceFunc == null) {
                    _ClearDisplayDeviceFunc =
                        (_ClearDisplayDevice)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnGameConnection_clearDisplayDevice"), typeof(_ClearDisplayDevice));
                }
                
                return _ClearDisplayDeviceFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct SetControlObject__Args
            {
                internal IntPtr ctrlObj;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            [return: MarshalAs(UnmanagedType.I1)]
            internal delegate bool _SetControlObject(IntPtr _this, SetControlObject__Args args);
            private static _SetControlObject _SetControlObjectFunc;
            internal static _SetControlObject SetControlObject() {
                if (_SetControlObjectFunc == null) {
                    _SetControlObjectFunc =
                        (_SetControlObject)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnGameConnection_setControlObject"), typeof(_SetControlObject));
                }
                
                return _SetControlObjectFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct ResetGhosting__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _ResetGhosting(IntPtr _this, ResetGhosting__Args args);
            private static _ResetGhosting _ResetGhostingFunc;
            internal static _ResetGhosting ResetGhosting() {
                if (_ResetGhostingFunc == null) {
                    _ResetGhostingFunc =
                        (_ResetGhosting)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnGameConnection_resetGhosting"), typeof(_ResetGhosting));
                }
                
                return _ResetGhostingFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct ActivateGhosting__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _ActivateGhosting(IntPtr _this, ActivateGhosting__Args args);
            private static _ActivateGhosting _ActivateGhostingFunc;
            internal static _ActivateGhosting ActivateGhosting() {
                if (_ActivateGhostingFunc == null) {
                    _ActivateGhostingFunc =
                        (_ActivateGhosting)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnGameConnection_activateGhosting"), typeof(_ActivateGhosting));
                }
                
                return _ActivateGhostingFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct TransmitDataBlocks__Args
            {
                internal int sequence;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _TransmitDataBlocks(IntPtr _this, TransmitDataBlocks__Args args);
            private static _TransmitDataBlocks _TransmitDataBlocksFunc;
            internal static _TransmitDataBlocks TransmitDataBlocks() {
                if (_TransmitDataBlocksFunc == null) {
                    _TransmitDataBlocksFunc =
                        (_TransmitDataBlocks)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnGameConnection_transmitDataBlocks"), typeof(_TransmitDataBlocks));
                }
                
                return _TransmitDataBlocksFunc;
            }


            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _SetConnectArgs(IntPtr _this, ref StringVector.InternalStruct args);
            private static _SetConnectArgs _SetConnectArgsFunc;
            internal static _SetConnectArgs SetConnectArgs() {
                if (_SetConnectArgsFunc == null) {
                    _SetConnectArgsFunc =
                        (_SetConnectArgs)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnGameConnection_setConnectArgs"), typeof(_SetConnectArgs));
                }
                
                return _SetConnectArgsFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct SetJoinPassword__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string password;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _SetJoinPassword(IntPtr _this, SetJoinPassword__Args args);
            private static _SetJoinPassword _SetJoinPasswordFunc;
            internal static _SetJoinPassword SetJoinPassword() {
                if (_SetJoinPasswordFunc == null) {
                    _SetJoinPasswordFunc =
                        (_SetJoinPassword)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnGameConnection_setJoinPassword"), typeof(_SetJoinPassword));
                }
                
                return _SetJoinPasswordFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct OnFlash__Args
            {
                [MarshalAs(UnmanagedType.I1)]
                internal bool state;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _OnFlash(IntPtr _this, OnFlash__Args args);
            private static _OnFlash _OnFlashFunc;
            internal static _OnFlash OnFlash() {
                if (_OnFlashFunc == null) {
                    _OnFlashFunc =
                        (_OnFlash)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "cbGameConnection_onFlash"), typeof(_OnFlash));
                }
                
                return _OnFlashFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct OnDataBlocksDone__Args
            {
                internal uint sequence;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _OnDataBlocksDone(IntPtr _this, OnDataBlocksDone__Args args);
            private static _OnDataBlocksDone _OnDataBlocksDoneFunc;
            internal static _OnDataBlocksDone OnDataBlocksDone() {
                if (_OnDataBlocksDoneFunc == null) {
                    _OnDataBlocksDoneFunc =
                        (_OnDataBlocksDone)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "cbGameConnection_onDataBlocksDone"), typeof(_OnDataBlocksDone));
                }
                
                return _OnDataBlocksDoneFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct SetLagIcon__Args
            {
                [MarshalAs(UnmanagedType.I1)]
                internal bool state;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _SetLagIcon(IntPtr _this, SetLagIcon__Args args);
            private static _SetLagIcon _SetLagIconFunc;
            internal static _SetLagIcon SetLagIcon() {
                if (_SetLagIconFunc == null) {
                    _SetLagIconFunc =
                        (_SetLagIcon)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "cbGameConnection_setLagIcon"), typeof(_SetLagIcon));
                }
                
                return _SetLagIconFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct OnControlObjectChange__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _OnControlObjectChange(IntPtr _this, OnControlObjectChange__Args args);
            private static _OnControlObjectChange _OnControlObjectChangeFunc;
            internal static _OnControlObjectChange OnControlObjectChange() {
                if (_OnControlObjectChangeFunc == null) {
                    _OnControlObjectChangeFunc =
                        (_OnControlObjectChange)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "cbGameConnection_onControlObjectChange"), typeof(_OnControlObjectChange));
                }
                
                return _OnControlObjectChangeFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct InitialControlSet__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _InitialControlSet(IntPtr _this, InitialControlSet__Args args);
            private static _InitialControlSet _InitialControlSetFunc;
            internal static _InitialControlSet InitialControlSet() {
                if (_InitialControlSetFunc == null) {
                    _InitialControlSetFunc =
                        (_InitialControlSet)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "cbGameConnection_initialControlSet"), typeof(_InitialControlSet));
                }
                
                return _InitialControlSetFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct OnDrop__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string disconnectReason;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _OnDrop(IntPtr _this, OnDrop__Args args);
            private static _OnDrop _OnDropFunc;
            internal static _OnDrop OnDrop() {
                if (_OnDropFunc == null) {
                    _OnDropFunc =
                        (_OnDrop)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "cbGameConnection_onDrop"), typeof(_OnDrop));
                }
                
                return _OnDropFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct OnConnectionError__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string errorString;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _OnConnectionError(IntPtr _this, OnConnectionError__Args args);
            private static _OnConnectionError _OnConnectionErrorFunc;
            internal static _OnConnectionError OnConnectionError() {
                if (_OnConnectionErrorFunc == null) {
                    _OnConnectionErrorFunc =
                        (_OnConnectionError)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "cbGameConnection_onConnectionError"), typeof(_OnConnectionError));
                }
                
                return _OnConnectionErrorFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct OnConnectRequestRejected__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string reason;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _OnConnectRequestRejected(IntPtr _this, OnConnectRequestRejected__Args args);
            private static _OnConnectRequestRejected _OnConnectRequestRejectedFunc;
            internal static _OnConnectRequestRejected OnConnectRequestRejected() {
                if (_OnConnectRequestRejectedFunc == null) {
                    _OnConnectRequestRejectedFunc =
                        (_OnConnectRequestRejected)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "cbGameConnection_onConnectRequestRejected"), typeof(_OnConnectRequestRejected));
                }
                
                return _OnConnectRequestRejectedFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct OnConnectionDropped__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string reason;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _OnConnectionDropped(IntPtr _this, OnConnectionDropped__Args args);
            private static _OnConnectionDropped _OnConnectionDroppedFunc;
            internal static _OnConnectionDropped OnConnectionDropped() {
                if (_OnConnectionDroppedFunc == null) {
                    _OnConnectionDroppedFunc =
                        (_OnConnectionDropped)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "cbGameConnection_onConnectionDropped"), typeof(_OnConnectionDropped));
                }
                
                return _OnConnectionDroppedFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct OnConnectRequestTimedOut__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _OnConnectRequestTimedOut(IntPtr _this, OnConnectRequestTimedOut__Args args);
            private static _OnConnectRequestTimedOut _OnConnectRequestTimedOutFunc;
            internal static _OnConnectRequestTimedOut OnConnectRequestTimedOut() {
                if (_OnConnectRequestTimedOutFunc == null) {
                    _OnConnectRequestTimedOutFunc =
                        (_OnConnectRequestTimedOut)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "cbGameConnection_onConnectRequestTimedOut"), typeof(_OnConnectRequestTimedOut));
                }
                
                return _OnConnectRequestTimedOutFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct OnConnectionAccepted__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _OnConnectionAccepted(IntPtr _this, OnConnectionAccepted__Args args);
            private static _OnConnectionAccepted _OnConnectionAcceptedFunc;
            internal static _OnConnectionAccepted OnConnectionAccepted() {
                if (_OnConnectionAcceptedFunc == null) {
                    _OnConnectionAcceptedFunc =
                        (_OnConnectionAccepted)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "cbGameConnection_onConnectionAccepted"), typeof(_OnConnectionAccepted));
                }
                
                return _OnConnectionAcceptedFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct OnConnectionTimedOut__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _OnConnectionTimedOut(IntPtr _this, OnConnectionTimedOut__Args args);
            private static _OnConnectionTimedOut _OnConnectionTimedOutFunc;
            internal static _OnConnectionTimedOut OnConnectionTimedOut() {
                if (_OnConnectionTimedOutFunc == null) {
                    _OnConnectionTimedOutFunc =
                        (_OnConnectionTimedOut)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "cbGameConnection_onConnectionTimedOut"), typeof(_OnConnectionTimedOut));
                }
                
                return _OnConnectionTimedOutFunc;
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
                                "fnGameConnection_staticGetType"), typeof(_StaticGetType));
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
                                "fnGameConnection_create"), typeof(_Create));
                }
                
                return _CreateFunc;
            }
        }
        #endregion

        /// 
        public bool LoadDatablockCache_Continue() {
             InternalUnsafeMethods.LoadDatablockCache_Continue__Args _args = new InternalUnsafeMethods.LoadDatablockCache_Continue__Args() {
             };
             bool _engineResult = InternalUnsafeMethods.LoadDatablockCache_Continue()(ObjectPtr, _args);
             return _engineResult;
        }

        /// 
        public bool LoadDatablockCache_Begin() {
             InternalUnsafeMethods.LoadDatablockCache_Begin__Args _args = new InternalUnsafeMethods.LoadDatablockCache_Begin__Args() {
             };
             bool _engineResult = InternalUnsafeMethods.LoadDatablockCache_Begin()(ObjectPtr, _args);
             return _engineResult;
        }

        /// 
        public void LoadDatablockCache() {
             InternalUnsafeMethods.LoadDatablockCache__Args _args = new InternalUnsafeMethods.LoadDatablockCache__Args() {
             };
             InternalUnsafeMethods.LoadDatablockCache()(ObjectPtr, _args);
        }

        /// 
        public void SaveDatablockCache() {
             InternalUnsafeMethods.SaveDatablockCache__Args _args = new InternalUnsafeMethods.SaveDatablockCache__Args() {
             };
             InternalUnsafeMethods.SaveDatablockCache()(ObjectPtr, _args);
        }

        /// 
        public void SetSelectedObjFromPreSelected() {
             InternalUnsafeMethods.SetSelectedObjFromPreSelected__Args _args = new InternalUnsafeMethods.SetSelectedObjFromPreSelected__Args() {
             };
             InternalUnsafeMethods.SetSelectedObjFromPreSelected()(ObjectPtr, _args);
        }

        /// 
        public void ClearPreSelectedObj() {
             InternalUnsafeMethods.ClearPreSelectedObj__Args _args = new InternalUnsafeMethods.ClearPreSelectedObj__Args() {
             };
             InternalUnsafeMethods.ClearPreSelectedObj()(ObjectPtr, _args);
        }

        /// 
        public void SetPreSelectedObjFromRollover() {
             InternalUnsafeMethods.SetPreSelectedObjFromRollover__Args _args = new InternalUnsafeMethods.SetPreSelectedObjFromRollover__Args() {
             };
             InternalUnsafeMethods.SetPreSelectedObjFromRollover()(ObjectPtr, _args);
        }

        /// 
        public void ClearSelectedObj(bool propagate_to_client = false) {
             InternalUnsafeMethods.ClearSelectedObj__Args _args = new InternalUnsafeMethods.ClearSelectedObj__Args() {
                propagate_to_client = propagate_to_client,
             };
             InternalUnsafeMethods.ClearSelectedObj()(ObjectPtr, _args);
        }

        /// 
        public SimObject GetSelectedObj() {
             InternalUnsafeMethods.GetSelectedObj__Args _args = new InternalUnsafeMethods.GetSelectedObj__Args() {
             };
             IntPtr _engineResult = InternalUnsafeMethods.GetSelectedObj()(ObjectPtr, _args);
             return new SimObject(_engineResult);
        }

        /// 
        public bool SetSelectedObj(SceneObject obj, bool propagate_to_client = false) {
             InternalUnsafeMethods.SetSelectedObj__Args _args = new InternalUnsafeMethods.SetSelectedObj__Args() {
                obj = obj.ObjectPtr,
                propagate_to_client = propagate_to_client,
             };
             bool _engineResult = InternalUnsafeMethods.SetSelectedObj()(ObjectPtr, _args);
             return _engineResult;
        }

        /// <summary>Gets the distance that objects around the connection will be ghosted.</summary>
        /// <description>
        /// 
        /// </description>
        /// <returns>S32 of distance.</returns>
        public float GetVisibleGhostDistance() {
             InternalUnsafeMethods.GetVisibleGhostDistance__Args _args = new InternalUnsafeMethods.GetVisibleGhostDistance__Args() {
             };
             float _engineResult = InternalUnsafeMethods.GetVisibleGhostDistance()(ObjectPtr, _args);
             return _engineResult;
        }

        /// <summary>Sets the distance that objects around it will be ghosted. If set to 0, it may be defined by the LevelInfo.</summary>
        /// <description>
        /// 
        /// </description>
        public void SetVisibleGhostDistance(float dist) {
             InternalUnsafeMethods.SetVisibleGhostDistance__Args _args = new InternalUnsafeMethods.SetVisibleGhostDistance__Args() {
                dist = dist,
             };
             InternalUnsafeMethods.SetVisibleGhostDistance()(ObjectPtr, _args);
        }

        /// <summary>Get the connection's control scheme absolute rotation property.</summary>
        /// <description>
        /// 
        /// </description>
        /// <returns>True if the connection's control object should use an absolute rotation control scheme.</returns>
        /// <see cref="GameConnection::setControlSchemeParameters()" />
        public bool GetControlSchemeAbsoluteRotation() {
             InternalUnsafeMethods.GetControlSchemeAbsoluteRotation__Args _args = new InternalUnsafeMethods.GetControlSchemeAbsoluteRotation__Args() {
             };
             bool _engineResult = InternalUnsafeMethods.GetControlSchemeAbsoluteRotation()(ObjectPtr, _args);
             return _engineResult;
        }

        /// <summary>Set the control scheme that may be used by a connection's control object.</summary>
        /// <description>
        /// 
        /// </description>
        /// <param name="absoluteRotation">Use absolute rotation values from client, likely through ExtendedMove.</param>
        /// <param name="addYawToAbsRot">Add relative yaw control to the absolute rotation calculation.  Only useful when absoluteRotation is true.</param>
        public void SetControlSchemeParameters(bool absoluteRotation, bool addYawToAbsRot, bool addPitchToAbsRot) {
             InternalUnsafeMethods.SetControlSchemeParameters__Args _args = new InternalUnsafeMethods.SetControlSchemeParameters__Args() {
                absoluteRotation = absoluteRotation,
                addYawToAbsRot = addYawToAbsRot,
                addPitchToAbsRot = addPitchToAbsRot,
             };
             InternalUnsafeMethods.SetControlSchemeParameters()(ObjectPtr, _args);
        }

        /// <summary>On the server, sets this connection into or out of first person mode.</summary>
        /// <description>
        /// 
        /// </description>
        /// <param name="firstPerson">Set to true to put the connection into first person mode.</param>
        public void SetFirstPerson(bool firstPerson) {
             InternalUnsafeMethods.SetFirstPerson__Args _args = new InternalUnsafeMethods.SetFirstPerson__Args() {
                firstPerson = firstPerson,
             };
             InternalUnsafeMethods.SetFirstPerson()(ObjectPtr, _args);
        }

        /// <summary>Returns true if this connection is in first person mode.</summary>
        /// <description>
        /// 
        /// </description>
        /// <remarks> Transition to first person occurs over time via mCameraPos, so this won't immediately return true after a set.
        /// 
        /// </remarks>
        public bool IsFirstPerson() {
             InternalUnsafeMethods.IsFirstPerson__Args _args = new InternalUnsafeMethods.IsFirstPerson__Args() {
             };
             bool _engineResult = InternalUnsafeMethods.IsFirstPerson()(ObjectPtr, _args);
             return _engineResult;
        }

        /// <summary>Clear the connection's camera object reference.</summary>
        /// <description>
        /// 
        /// </description>
        /// <see cref="GameConnection::setCameraObject() and GameConnection::getCameraObject()" />
        public void ClearCameraObject() {
             InternalUnsafeMethods.ClearCameraObject__Args _args = new InternalUnsafeMethods.ClearCameraObject__Args() {
             };
             InternalUnsafeMethods.ClearCameraObject()(ObjectPtr, _args);
        }

        /// <summary>Returns the connection's camera object used when not viewing through the control object.</summary>
        /// <description>
        /// 
        /// </description>
        /// <see cref="GameConnection::setCameraObject() and GameConnection::clearCameraObject()" />
        public SimObject GetCameraObject() {
             InternalUnsafeMethods.GetCameraObject__Args _args = new InternalUnsafeMethods.GetCameraObject__Args() {
             };
             IntPtr _engineResult = InternalUnsafeMethods.GetCameraObject()(ObjectPtr, _args);
             return new SimObject(_engineResult);
        }

        /// <summary>On the server, set the connection's camera object used when not viewing through the control object.</summary>
        /// <description>
        /// 
        /// </description>
        /// <see cref="GameConnection::getCameraObject() and GameConnection::clearCameraObject()" />
        public bool SetCameraObject(GameBase camera) {
             InternalUnsafeMethods.SetCameraObject__Args _args = new InternalUnsafeMethods.SetCameraObject__Args() {
                camera = camera.ObjectPtr,
             };
             bool _engineResult = InternalUnsafeMethods.SetCameraObject()(ObjectPtr, _args);
             return _engineResult;
        }

        /// <summary>On the client, this static mehtod will return the connection to the server, if any.</summary>
        /// <description>
        /// 
        /// </description>
        /// <returns>The SimObject ID of the server connection, or -1 if none is found.</returns>
        public static int GetServerConnection() {
             InternalUnsafeMethods.GetServerConnection__Args _args = new InternalUnsafeMethods.GetServerConnection__Args() {
             };
             int _engineResult = InternalUnsafeMethods.GetServerConnection()(_args);
             return _engineResult;
        }

        /// <summary>List all of the classes that this connection knows about, and what their IDs are. Useful for debugging network problems.</summary>
        /// <description>
        /// 
        /// </description>
        /// <remarks> The list is sent to the console.
        /// 
        /// </remarks>
        public void ListClassIDs() {
             InternalUnsafeMethods.ListClassIDs__Args _args = new InternalUnsafeMethods.ListClassIDs__Args() {
             };
             InternalUnsafeMethods.ListClassIDs()(ObjectPtr, _args);
        }

        /// <summary>Returns true if a demo file is now being recorded.</summary>
        /// <description>
        /// 
        /// </description>
        /// <see cref="GameConnection::startRecording(), GameConnection::stopRecording()" />
        public bool IsDemoRecording() {
             InternalUnsafeMethods.IsDemoRecording__Args _args = new InternalUnsafeMethods.IsDemoRecording__Args() {
             };
             bool _engineResult = InternalUnsafeMethods.IsDemoRecording()(ObjectPtr, _args);
             return _engineResult;
        }

        /// <summary>Returns true if a previously recorded demo file is now playing.</summary>
        /// <description>
        /// 
        /// </description>
        /// <see cref="GameConnection::playDemo()" />
        public bool IsDemoPlaying() {
             InternalUnsafeMethods.IsDemoPlaying__Args _args = new InternalUnsafeMethods.IsDemoPlaying__Args() {
             };
             bool _engineResult = InternalUnsafeMethods.IsDemoPlaying()(ObjectPtr, _args);
             return _engineResult;
        }

        /// <summary>On the client, play back a previously recorded game session.</summary>
        /// <description>
        /// It is often useful to play back a game session.  This could be for producing a demo of the game that will be shown at a later time, or for debugging a game.  By recording the entire network stream it is possible to later play game the game exactly as it unfolded during the actual play session.  This is because all user control and server results pass through the connection.
        /// </description>
        /// <returns>True if the playback was successful.  False if there was an issue, such as not being able to open the demo file for playback.</returns>
        /// <see cref="GameConnection::startRecording(), GameConnection::stopRecording()" />
        public bool PlayDemo(string demoFileName) {
             InternalUnsafeMethods.PlayDemo__Args _args = new InternalUnsafeMethods.PlayDemo__Args() {
                demoFileName = demoFileName,
             };
             bool _engineResult = InternalUnsafeMethods.PlayDemo()(ObjectPtr, _args);
             return _engineResult;
        }

        /// <summary>On the client, stops the recording of a connection's network traffic to a file.</summary>
        /// <description>
        /// 
        /// </description>
        /// <see cref="GameConnection::startRecording(), GameConnection::playDemo()" />
        public void StopRecording() {
             InternalUnsafeMethods.StopRecording__Args _args = new InternalUnsafeMethods.StopRecording__Args() {
             };
             InternalUnsafeMethods.StopRecording()(ObjectPtr, _args);
        }

        /// <summary>On the client, starts recording the network connection's traffic to a demo file.</summary>
        /// <description>
        /// It is often useful to play back a game session.  This could be for producing a demo of the game that will be shown at a later time, or for debugging a game.  By recording the entire network stream it is possible to later play game the game exactly as it unfolded during the actual play session.  This is because all user control and server results pass through the connection.
        /// </description>
        /// <param name="fileName">The file name to use for the demo recording.</param>
        /// <see cref="GameConnection::stopRecording(), GameConnection::playDemo()" />
        public void StartRecording(string fileName) {
             InternalUnsafeMethods.StartRecording__Args _args = new InternalUnsafeMethods.StartRecording__Args() {
                fileName = fileName,
             };
             InternalUnsafeMethods.StartRecording()(ObjectPtr, _args);
        }

        /// <summary>On the server, disconnect a client and pass along an optional reason why.</summary>
        /// <description>
        /// This method performs two operations: it disconnects a client connection from the server, and it deletes the connection object.  The optional reason is sent in the disconnect packet and is often displayed to the user so they know why they've been disconnected.
        /// </description>
        /// <param name="reason">[optional] The reason why the user has been disconnected from the server.</param>
        /// <code>
        /// function kick(%client)
        /// {
        ///    messageAll( 'MsgAdminForce', '\c2The Admin has kicked %1.', %client.playerName);
        /// 
        ///    if (!%client.isAIControlled())
        ///       BanList::add(%client.guid, %client.getAddress(), $Pref::Server::KickBanTime);
        ///    %client.delete("You have been kicked from this server");
        /// }
        /// </code>
        public void Delete(string reason = "") {
             InternalUnsafeMethods.Delete__Args _args = new InternalUnsafeMethods.Delete__Args() {
                reason = reason,
             };
             InternalUnsafeMethods.Delete()(ObjectPtr, _args);
        }

        /// <summary>On the server, transmits the mission file's CRC value to the client.</summary>
        /// <description>
        /// Typically, during the standard mission start phase 1, the mission file's CRC value on the server is send to the client.  This allows the client to determine if the mission has changed since the last time it downloaded this mission and act appropriately, such as rebuilt cached lightmaps.
        /// </description>
        /// <param name="CRC">The mission file's CRC value on the server.</param>
        /// <code>
        /// function serverCmdMissionStartPhase1Ack(%client, %seq)
        /// {
        ///    // Make sure to ignore calls from a previous mission load
        ///    if (%seq != $missionSequence || !$MissionRunning)
        ///       return;
        ///    if (%client.currentPhase != 0)
        ///       return;
        ///    %client.currentPhase = 1;
        /// 
        ///    // Start with the CRC
        ///    %client.setMissionCRC( $missionCRC );
        /// 
        ///    // Send over the datablocks...
        ///    // OnDataBlocksDone will get called when have confirmation
        ///    // that they've all been received.
        ///    %client.transmitDataBlocks($missionSequence);
        /// }
        /// </code>
        public void SetMissionCRC(int CRC) {
             InternalUnsafeMethods.SetMissionCRC__Args _args = new InternalUnsafeMethods.SetMissionCRC__Args() {
                CRC = CRC,
             };
             InternalUnsafeMethods.SetMissionCRC()(ObjectPtr, _args);
        }

        /// <summary>On the server, sets the client's 3D display to fade to black.</summary>
        /// <description>
        /// 
        /// </description>
        /// <param name="doFade">Set to true to fade to black, and false to fade from black.</param>
        /// <param name="timeMS">Time it takes to perform the fade as measured in ms.</param>
        /// <remarks> Not currently hooked up, and is not synchronized over the network.</remarks>
        public void SetBlackOut(bool doFade, int timeMS) {
             InternalUnsafeMethods.SetBlackOut__Args _args = new InternalUnsafeMethods.SetBlackOut__Args() {
                doFade = doFade,
                timeMS = timeMS,
             };
             InternalUnsafeMethods.SetBlackOut()(ObjectPtr, _args);
        }

        /// <summary>On the client, get the control object's white-out level.</summary>
        /// <description>
        /// 
        /// </description>
        /// <returns>white-out level</returns>
        public float GetWhiteOut() {
             InternalUnsafeMethods.GetWhiteOut__Args _args = new InternalUnsafeMethods.GetWhiteOut__Args() {
             };
             float _engineResult = InternalUnsafeMethods.GetWhiteOut()(ObjectPtr, _args);
             return _engineResult;
        }

        /// <summary>On the client, get the control object's damage flash level.</summary>
        /// <description>
        /// 
        /// </description>
        /// <returns>flash level</returns>
        public float GetDamageFlash() {
             InternalUnsafeMethods.GetDamageFlash__Args _args = new InternalUnsafeMethods.GetDamageFlash__Args() {
             };
             float _engineResult = InternalUnsafeMethods.GetDamageFlash()(ObjectPtr, _args);
             return _engineResult;
        }

        /// <summary>Returns the field of view as used by the control object's camera.</summary>
        /// <description>
        /// 
        /// </description>
        public float GetControlCameraFov() {
             InternalUnsafeMethods.GetControlCameraFov__Args _args = new InternalUnsafeMethods.GetControlCameraFov__Args() {
             };
             float _engineResult = InternalUnsafeMethods.GetControlCameraFov()(ObjectPtr, _args);
             return _engineResult;
        }

        /// <summary>On the server, sets the control object's camera's field of view.</summary>
        /// <description>
        /// 
        /// </description>
        /// <param name="newFOV">New field of view (in degrees) to force the control object's camera to use.  This value is clamped to be within the range of 1 to 179 degrees.</param>
        /// <remarks> When transmitted over the network to the client, the resolution is limited to one degree.  Any fraction is dropped.</remarks>
        public void SetControlCameraFov(float newFOV) {
             InternalUnsafeMethods.SetControlCameraFov__Args _args = new InternalUnsafeMethods.SetControlCameraFov__Args() {
                newFOV = newFOV,
             };
             InternalUnsafeMethods.SetControlCameraFov()(ObjectPtr, _args);
        }

        /// <summary>Returns the default field of view as used by the control object's camera.</summary>
        /// <description>
        /// 
        /// </description>
        public float GetControlCameraDefaultFov() {
             InternalUnsafeMethods.GetControlCameraDefaultFov__Args _args = new InternalUnsafeMethods.GetControlCameraDefaultFov__Args() {
             };
             float _engineResult = InternalUnsafeMethods.GetControlCameraDefaultFov()(ObjectPtr, _args);
             return _engineResult;
        }

        /// <summary>Sets the size of the chase camera's matrix queue.</summary>
        /// <description>
        /// 
        /// </description>
        /// <remarks> This sets the queue size across all GameConnections.
        /// 
        /// </remarks>
        /// <remarks> This is not currently hooked up.
        /// 
        /// </remarks>
        public bool ChaseCam(int size) {
             InternalUnsafeMethods.ChaseCam__Args _args = new InternalUnsafeMethods.ChaseCam__Args() {
                size = size,
             };
             bool _engineResult = InternalUnsafeMethods.ChaseCam()(ObjectPtr, _args);
             return _engineResult;
        }

        /// <summary>Used on the server to play a 3D sound that is not attached to any object.</summary>
        /// <description>
        /// 
        /// </description>
        /// <param name="profile">The SFXProfile that defines the sound to play.</param>
        /// <param name="location">The position and orientation of the 3D sound given in the form of "x y z ax ay az aa".</param>
        /// <code>
        /// function ServerPlay3D(%profile,%transform)
        /// {
        ///    // Play the given sound profile at the given position on every client
        ///    // The sound will be transmitted as an event, not attached to any object.
        ///    for(%idx = 0; %idx < ClientGroup.getCount(); %idx++)
        ///       ClientGroup.getObject(%idx).play3D(%profile,%transform);
        /// }
        /// </code>
        public bool Play3D(SFXProfile profile, TransformF location) {
location.Alloc();             InternalUnsafeMethods.Play3D__Args _args = new InternalUnsafeMethods.Play3D__Args() {
                profile = profile.ObjectPtr,
                location = location.internalStructPtr,
             };
             bool _engineResult = InternalUnsafeMethods.Play3D()(ObjectPtr, _args);
location.Free();             return _engineResult;
        }

        /// <summary>Used on the server to play a 2D sound that is not attached to any object.</summary>
        /// <description>
        /// 
        /// </description>
        /// <param name="profile">The SFXProfile that defines the sound to play.</param>
        /// <code>
        /// function ServerPlay2D(%profile)
        /// {
        ///    // Play the given sound profile on every client.
        ///    // The sounds will be transmitted as an event, not attached to any object.
        ///    for(%idx = 0; %idx < ClientGroup.getCount(); %idx++)
        ///       ClientGroup.getObject(%idx).play2D(%profile);
        /// }
        /// </code>
        public bool Play2D(SFXProfile profile) {
             InternalUnsafeMethods.Play2D__Args _args = new InternalUnsafeMethods.Play2D__Args() {
                profile = profile.ObjectPtr,
             };
             bool _engineResult = InternalUnsafeMethods.Play2D()(ObjectPtr, _args);
             return _engineResult;
        }

        /// <summary>Returns true if the object being controlled by the client is making use of a rotation damped camera.</summary>
        /// <description>
        /// 
        /// </description>
        /// <see cref="Camera" />
        public bool IsControlObjectRotDampedCamera() {
             InternalUnsafeMethods.IsControlObjectRotDampedCamera__Args _args = new InternalUnsafeMethods.IsControlObjectRotDampedCamera__Args() {
             };
             bool _engineResult = InternalUnsafeMethods.IsControlObjectRotDampedCamera()(ObjectPtr, _args);
             return _engineResult;
        }

        /// <summary>Returns true if this connection is AI controlled.</summary>
        /// <description>
        /// 
        /// </description>
        /// <see cref="AIConnection" />
        public bool IsAIControlled() {
             InternalUnsafeMethods.IsAIControlled__Args _args = new InternalUnsafeMethods.IsAIControlled__Args() {
             };
             bool _engineResult = InternalUnsafeMethods.IsAIControlled()(ObjectPtr, _args);
             return _engineResult;
        }

        /// <summary>On the server, returns the object that the client is controlling.By default the control object is an instance of the Player class, but can also be an instance of Camera (when editing the mission, for example), or any other ShapeBase derived class as appropriate for the game.</summary>
        /// <description>
        /// 
        /// </description>
        /// <see cref="GameConnection::setControlObject()" />
        public GameBase GetControlObject() {
             InternalUnsafeMethods.GetControlObject__Args _args = new InternalUnsafeMethods.GetControlObject__Args() {
             };
             IntPtr _engineResult = InternalUnsafeMethods.GetControlObject()(ObjectPtr, _args);
             return new GameBase(_engineResult);
        }

        /// <summary>Clear any display device.</summary>
        /// <description>
        /// A display device may define a number of properties that are used during rendering.
        /// </description>
        public void ClearDisplayDevice() {
             InternalUnsafeMethods.ClearDisplayDevice__Args _args = new InternalUnsafeMethods.ClearDisplayDevice__Args() {
             };
             InternalUnsafeMethods.ClearDisplayDevice()(ObjectPtr, _args);
        }

        /// <summary>On the server, sets the object that the client will control.</summary>
        /// <description>
        /// By default the control object is an instance of the Player class, but can also be an instance of Camera (when editing the mission, for example), or any other ShapeBase derived class as appropriate for the game.
        /// </description>
        /// <param name="ctrlObj">The GameBase object on the server to control.</param>
        public bool SetControlObject(GameBase ctrlObj) {
             InternalUnsafeMethods.SetControlObject__Args _args = new InternalUnsafeMethods.SetControlObject__Args() {
                ctrlObj = ctrlObj.ObjectPtr,
             };
             bool _engineResult = InternalUnsafeMethods.SetControlObject()(ObjectPtr, _args);
             return _engineResult;
        }

        /// <summary>On the server, resets the connection to indicate that ghosting has been disabled.</summary>
        /// <description>
        /// Typically when a mission has ended on the server, all connected clients are informed of this change and their connections are reset back to a starting state.  This method resets a connection on the server to indicate that ghosts are no longer being transmitted.  On the client end, all ghost information will be deleted.
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
        /// <see cref="" />
        public void ResetGhosting() {
             InternalUnsafeMethods.ResetGhosting__Args _args = new InternalUnsafeMethods.ResetGhosting__Args() {
             };
             InternalUnsafeMethods.ResetGhosting()(ObjectPtr, _args);
        }

        /// <summary>Called by the server during phase 2 of the mission download to start sending ghosts to the client.</summary>
        /// <description>
        /// Ghosts represent objects on the server that are in scope for the client.  These need to be synchronized with the client in order for the client to see and interact with them.  This is typically done during the standard mission start phase 2 when following Torque's example mission startup sequence.
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
        ///    // Update mod paths, this needs to get there before the objects.
        ///    %client.transmitPaths();
        /// 
        ///    // Start ghosting objects to the client
        ///    %client.activateGhosting();
        /// }
        /// </code>
        /// <see cref="" />
        public void ActivateGhosting() {
             InternalUnsafeMethods.ActivateGhosting__Args _args = new InternalUnsafeMethods.ActivateGhosting__Args() {
             };
             InternalUnsafeMethods.ActivateGhosting()(ObjectPtr, _args);
        }

        /// <summary>Sent by the server during phase 1 of the mission download to send the datablocks to the client.</summary>
        /// <description>
        /// SimDataBlocks, also known as just datablocks, need to be transmitted to the client prior to the client entering the game world.  These represent the static data that most objects in the world reference.  This is typically done during the standard mission start phase 1 when following Torque's example mission startup sequence.
        /// 
        /// When the datablocks have all been transmitted, onDataBlocksDone() is called to move the mission start process to the next phase.
        /// </description>
        /// <param name="sequence">The sequence is common between the server and client and ensures that the client is acting on the most recent mission start process.  If an errant network packet (one that was lost but has now been found) is received by the client with an incorrect sequence, it is just ignored.  This sequence number is updated on the server every time a mission is loaded.</param>
        /// <code>
        /// function serverCmdMissionStartPhase1Ack(%client, %seq)
        /// {
        ///    // Make sure to ignore calls from a previous mission load
        ///    if (%seq != $missionSequence || !$MissionRunning)
        ///       return;
        ///    if (%client.currentPhase != 0)
        ///       return;
        ///    %client.currentPhase = 1;
        /// 
        ///    // Start with the CRC
        ///    %client.setMissionCRC( $missionCRC );
        /// 
        ///    // Send over the datablocks...
        ///    // OnDataBlocksDone will get called when have confirmation
        ///    // that they've all been received.
        ///    %client.transmitDataBlocks($missionSequence);
        /// }
        /// </code>
        /// <see cref="GameConnection::onDataBlocksDone()" />
        public void TransmitDataBlocks(int sequence) {
             InternalUnsafeMethods.TransmitDataBlocks__Args _args = new InternalUnsafeMethods.TransmitDataBlocks__Args() {
                sequence = sequence,
             };
             InternalUnsafeMethods.TransmitDataBlocks()(ObjectPtr, _args);
        }

        /// <description>
        /// (const char* args)
        /// </description>
        /// <summary>On the client, pass along a variable set of parameters to the server.</summary>
        /// <description>
        /// Once the connection is established with the server, the server calls its onConnect() method with the client's passed in parameters as aruments.
        /// </description>
        /// <see cref="GameConnection::onConnect()" />
        public void SetConnectArgs(params string[] args) { 
            List<string> _argList = new List<string>() {"", ""};
            _argList.AddRange(args);

            StringVector nativeVecArgs = new StringVector {
                ElementCount = (uint)_argList.Count,
                Array = _argList.ToArray(),
                ArraySize = (uint)_argList.Count
            };
            nativeVecArgs.Alloc();
            InternalUnsafeMethods.SetConnectArgs()(ObjectPtr, ref nativeVecArgs.internalStruct);
            nativeVecArgs.Free();

        }

        /// <summary>On the client, set the password that will be passed to the server.</summary>
        /// <description>
        /// On the server, this password is compared with what is stored in $pref::Server::Password.  If $pref::Server::Password is empty then the client's sent password is ignored.  Otherwise, if the passed in client password and the server password do not match, the CHR_PASSWORD error string is sent back to the client and the connection is immediately terminated.
        /// 
        /// This password checking is performed quite early on in the connection request process so as to minimize the impact of multiple failed attempts -- also known as hacking.
        /// </description>
        public void SetJoinPassword(string password) {
             InternalUnsafeMethods.SetJoinPassword__Args _args = new InternalUnsafeMethods.SetJoinPassword__Args() {
                password = password,
             };
             InternalUnsafeMethods.SetJoinPassword()(ObjectPtr, _args);
        }

        /// <summary>Called on the client when the damage flash or white out states change.</summary>
        /// <description>
        /// When the server changes the damage flash or white out values, this callback is called either is on or both are off.  Typically this is used to enable the flash postFx.
        /// </description>
        /// <param name="state">Set to true if either the damage flash or white out conditions are active.</param>
        public virtual void OnFlash(bool state) {
             InternalUnsafeMethods.OnFlash__Args _args = new InternalUnsafeMethods.OnFlash__Args() {
                state = state,
             };
             InternalUnsafeMethods.OnFlash()(ObjectPtr, _args);
        }

        /// <summary>Called on the server when all datablocks has been sent to the client.</summary>
        /// <description>
        /// During phase 1 of the mission download, all datablocks are sent from the server to the client.  Once all datablocks have been sent, this callback is called and the mission download procedure may move on to the next phase.
        /// </description>
        /// <param name="sequence">The sequence is common between the server and client and ensures that the client is acting on the most recent mission start process.  If an errant network packet (one that was lost but has now been found) is received by the client with an incorrect sequence, it is just ignored.  This sequence number is updated on the server every time a mission is loaded.</param>
        /// <see cref="GameConnection::transmitDataBlocks()" />
        public virtual void OnDataBlocksDone(uint sequence) {
             InternalUnsafeMethods.OnDataBlocksDone__Args _args = new InternalUnsafeMethods.OnDataBlocksDone__Args() {
                sequence = sequence,
             };
             InternalUnsafeMethods.OnDataBlocksDone()(ObjectPtr, _args);
        }

        /// <summary>Called on the client to display the lag icon.</summary>
        /// <description>
        /// When the connection with the server is lagging, this callback is called to allow the game GUI to display some indicator to the player.
        /// </description>
        /// <param name="state">Set to true if the lag icon should be displayed.</param>
        public virtual void SetLagIcon(bool state) {
             InternalUnsafeMethods.SetLagIcon__Args _args = new InternalUnsafeMethods.SetLagIcon__Args() {
                state = state,
             };
             InternalUnsafeMethods.SetLagIcon()(ObjectPtr, _args);
        }

        /// <summary>Called on the client when the control object has been changed by the server.</summary>
        /// <description>
        /// 
        /// </description>
        public virtual void OnControlObjectChange() {
             InternalUnsafeMethods.OnControlObjectChange__Args _args = new InternalUnsafeMethods.OnControlObjectChange__Args() {
             };
             InternalUnsafeMethods.OnControlObjectChange()(ObjectPtr, _args);
        }

        /// <summary>Called on the client when the first control object has been set by the server and we are now ready to go.</summary>
        /// <description>
        /// A common action to perform when this callback is called is to switch the GUI canvas from the loading screen and over to the 3D game GUI.
        /// </description>
        public virtual void InitialControlSet() {
             InternalUnsafeMethods.InitialControlSet__Args _args = new InternalUnsafeMethods.InitialControlSet__Args() {
             };
             InternalUnsafeMethods.InitialControlSet()(ObjectPtr, _args);
        }

        /// <summary>Called on the server when the client's connection has been dropped.</summary>
        /// <description>
        /// 
        /// </description>
        /// <param name="disconnectReason">The reason why the connection was dropped.</param>
        public virtual void OnDrop(string disconnectReason) {
             InternalUnsafeMethods.OnDrop__Args _args = new InternalUnsafeMethods.OnDrop__Args() {
                disconnectReason = disconnectReason,
             };
             InternalUnsafeMethods.OnDrop()(ObjectPtr, _args);
        }

        /// <summary>Called on the client when there is an error with the connection to the server.</summary>
        /// <description>
        /// 
        /// </description>
        /// <param name="errorString">The connection error text.</param>
        public virtual void OnConnectionError(string errorString) {
             InternalUnsafeMethods.OnConnectionError__Args _args = new InternalUnsafeMethods.OnConnectionError__Args() {
                errorString = errorString,
             };
             InternalUnsafeMethods.OnConnectionError()(ObjectPtr, _args);
        }

        /// <summary>Called on the client when the connection to the server has been rejected.</summary>
        /// <description>
        /// 
        /// </description>
        /// <param name="reason">The reason why the connection request was rejected.</param>
        public virtual void OnConnectRequestRejected(string reason) {
             InternalUnsafeMethods.OnConnectRequestRejected__Args _args = new InternalUnsafeMethods.OnConnectRequestRejected__Args() {
                reason = reason,
             };
             InternalUnsafeMethods.OnConnectRequestRejected()(ObjectPtr, _args);
        }

        /// <summary>Called on the client when the connection to the server has been dropped.</summary>
        /// <description>
        /// 
        /// </description>
        /// <param name="reason">The reason why the connection was dropped.</param>
        public virtual void OnConnectionDropped(string reason) {
             InternalUnsafeMethods.OnConnectionDropped__Args _args = new InternalUnsafeMethods.OnConnectionDropped__Args() {
                reason = reason,
             };
             InternalUnsafeMethods.OnConnectionDropped()(ObjectPtr, _args);
        }

        /// <summary>Called when connection attempts have timed out.</summary>
        /// <description>
        /// 
        /// </description>
        public virtual void OnConnectRequestTimedOut() {
             InternalUnsafeMethods.OnConnectRequestTimedOut__Args _args = new InternalUnsafeMethods.OnConnectRequestTimedOut__Args() {
             };
             InternalUnsafeMethods.OnConnectRequestTimedOut()(ObjectPtr, _args);
        }

        /// <summary>Called on the client when the connection to the server has been established.</summary>
        /// <description>
        /// 
        /// </description>
        public virtual void OnConnectionAccepted() {
             InternalUnsafeMethods.OnConnectionAccepted__Args _args = new InternalUnsafeMethods.OnConnectionAccepted__Args() {
             };
             InternalUnsafeMethods.OnConnectionAccepted()(ObjectPtr, _args);
        }

        /// <summary>Called on the client when the connection to the server times out.</summary>
        /// <description>
        /// 
        /// </description>
        public virtual void OnConnectionTimedOut() {
             InternalUnsafeMethods.OnConnectionTimedOut__Args _args = new InternalUnsafeMethods.OnConnectionTimedOut__Args() {
             };
             InternalUnsafeMethods.OnConnectionTimedOut()(ObjectPtr, _args);
        }

        /// <description>
        /// Get the type info object for the GameConnection class.
        /// </description>
        /// <returns>The type info object for GameConnection</returns>
        public static EngineTypeInfo StaticGetType() {
             InternalUnsafeMethods.StaticGetType__Args _args = new InternalUnsafeMethods.StaticGetType__Args() {
             };
             IntPtr _engineResult = InternalUnsafeMethods.StaticGetType()(_args);
             return new EngineTypeInfo(_engineResult);
        }
    }
}