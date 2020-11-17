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
    /// <summary>Simulated client driven by AI commands.</summary>
    /// <description>
    /// This object is derived from the AIConnection class. It introduces its own Player object to solidify the purpose of this class: Simulated client connecting as a player
    /// 
    /// To get more specific, if you want a strong alternative to AIPlayer (and wish to make use of the AIConnection structure), consider AIClient. AIClient inherits from AIConnection, contains quite a bit of functionality you will find in AIPlayer, and has its own Player object.
    /// </description>
    /// <remarks> This is a legacy class, which you are discouraged from using as it will most likely be deprecated in a future version. For now it has been left in for backwards compatibility with TGE and the old RTS Kit. Use AIPlayer instead.
    /// 
    /// </remarks>
    /// <see cref="AIPlayer, AIConnection" />
    public unsafe class AIClient : AIConnection {
        public AIClient(bool pRegister = false) 
            : base(pRegister) {
        }
        
        public AIClient(string pName, bool pRegister) 
            : this(false) {
            Name = pName;
            if (pRegister) {
                RegisterObject();
            }
        }
        
        public AIClient(string pName) 
            : this(pName, false) {
        }
        
        public AIClient(string pName, string pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(Engine.Sim.FindObject<SimObject>(pParent));
        }
        
        public AIClient(string pName, SimObject pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(pParent);
        }
        
        public AIClient(SimObject pObj) 
            : base(pObj) {
        }
        
        public AIClient(IntPtr pObj) 
            : base(pObj) {
        }
        
		protected override void CreateObjectPtr()
		{
			ObjectPtr = InternalUnsafeMethods.Create()(new InternalUnsafeMethods.Create__Args());
		}

        #region UnsafeNativeMethods
        new internal struct InternalUnsafeMethods {
            [StructLayout(LayoutKind.Sequential)]
            internal struct MoveForward__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _MoveForward(IntPtr _this, MoveForward__Args args);
            private static _MoveForward _MoveForwardFunc;
            internal static _MoveForward MoveForward() {
                if (_MoveForwardFunc == null) {
                    _MoveForwardFunc =
                        (_MoveForward)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnAIClient_moveForward"), typeof(_MoveForward));
                }
                
                return _MoveForwardFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct GetLocation__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate Point3F.InternalStruct _GetLocation(IntPtr _this, GetLocation__Args args);
            private static _GetLocation _GetLocationFunc;
            internal static _GetLocation GetLocation() {
                if (_GetLocationFunc == null) {
                    _GetLocationFunc =
                        (_GetLocation)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnAIClient_getLocation"), typeof(_GetLocation));
                }
                
                return _GetLocationFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct Move__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _Move(IntPtr _this, Move__Args args);
            private static _Move _MoveFunc;
            internal static _Move Move() {
                if (_MoveFunc == null) {
                    _MoveFunc =
                        (_Move)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnAIClient_move"), typeof(_Move));
                }
                
                return _MoveFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct MissionCycleCleanup__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _MissionCycleCleanup(IntPtr _this, MissionCycleCleanup__Args args);
            private static _MissionCycleCleanup _MissionCycleCleanupFunc;
            internal static _MissionCycleCleanup MissionCycleCleanup() {
                if (_MissionCycleCleanupFunc == null) {
                    _MissionCycleCleanupFunc =
                        (_MissionCycleCleanup)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnAIClient_missionCycleCleanup"), typeof(_MissionCycleCleanup));
                }
                
                return _MissionCycleCleanupFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct GetTargetObject__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate int _GetTargetObject(IntPtr _this, GetTargetObject__Args args);
            private static _GetTargetObject _GetTargetObjectFunc;
            internal static _GetTargetObject GetTargetObject() {
                if (_GetTargetObjectFunc == null) {
                    _GetTargetObjectFunc =
                        (_GetTargetObject)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnAIClient_getTargetObject"), typeof(_GetTargetObject));
                }
                
                return _GetTargetObjectFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct SetTargetObject__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string objName;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _SetTargetObject(IntPtr _this, SetTargetObject__Args args);
            private static _SetTargetObject _SetTargetObjectFunc;
            internal static _SetTargetObject SetTargetObject() {
                if (_SetTargetObjectFunc == null) {
                    _SetTargetObjectFunc =
                        (_SetTargetObject)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnAIClient_setTargetObject"), typeof(_SetTargetObject));
                }
                
                return _SetTargetObjectFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct GetMoveDestination__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate Point3F.InternalStruct _GetMoveDestination(IntPtr _this, GetMoveDestination__Args args);
            private static _GetMoveDestination _GetMoveDestinationFunc;
            internal static _GetMoveDestination GetMoveDestination() {
                if (_GetMoveDestinationFunc == null) {
                    _GetMoveDestinationFunc =
                        (_GetMoveDestination)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnAIClient_getMoveDestination"), typeof(_GetMoveDestination));
                }
                
                return _GetMoveDestinationFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct GetAimLocation__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate Point3F.InternalStruct _GetAimLocation(IntPtr _this, GetAimLocation__Args args);
            private static _GetAimLocation _GetAimLocationFunc;
            internal static _GetAimLocation GetAimLocation() {
                if (_GetAimLocationFunc == null) {
                    _GetAimLocationFunc =
                        (_GetAimLocation)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnAIClient_getAimLocation"), typeof(_GetAimLocation));
                }
                
                return _GetAimLocationFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct SetMoveDestination__Args
            {
                internal IntPtr v;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _SetMoveDestination(IntPtr _this, SetMoveDestination__Args args);
            private static _SetMoveDestination _SetMoveDestinationFunc;
            internal static _SetMoveDestination SetMoveDestination() {
                if (_SetMoveDestinationFunc == null) {
                    _SetMoveDestinationFunc =
                        (_SetMoveDestination)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnAIClient_setMoveDestination"), typeof(_SetMoveDestination));
                }
                
                return _SetMoveDestinationFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct SetAimLocation__Args
            {
                internal IntPtr v;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _SetAimLocation(IntPtr _this, SetAimLocation__Args args);
            private static _SetAimLocation _SetAimLocationFunc;
            internal static _SetAimLocation SetAimLocation() {
                if (_SetAimLocationFunc == null) {
                    _SetAimLocationFunc =
                        (_SetAimLocation)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnAIClient_setAimLocation"), typeof(_SetAimLocation));
                }
                
                return _SetAimLocationFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct Stop__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _Stop(IntPtr _this, Stop__Args args);
            private static _Stop _StopFunc;
            internal static _Stop Stop() {
                if (_StopFunc == null) {
                    _StopFunc =
                        (_Stop)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnAIClient_stop"), typeof(_Stop));
                }
                
                return _StopFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct SetMoveSpeed__Args
            {
                internal float speed;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _SetMoveSpeed(IntPtr _this, SetMoveSpeed__Args args);
            private static _SetMoveSpeed _SetMoveSpeedFunc;
            internal static _SetMoveSpeed SetMoveSpeed() {
                if (_SetMoveSpeedFunc == null) {
                    _SetMoveSpeedFunc =
                        (_SetMoveSpeed)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnAIClient_setMoveSpeed"), typeof(_SetMoveSpeed));
                }
                
                return _SetMoveSpeedFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct OnConnect__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string idString;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _OnConnect(IntPtr _this, OnConnect__Args args);
            private static _OnConnect _OnConnectFunc;
            internal static _OnConnect OnConnect() {
                if (_OnConnectFunc == null) {
                    _OnConnectFunc =
                        (_OnConnect)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "cbAIClient_onConnect"), typeof(_OnConnect));
                }
                
                return _OnConnectFunc;
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
                                "fnAIClient_staticGetType"), typeof(_StaticGetType));
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
                                "fnAIClient_create"), typeof(_Create));
                }
                
                return _CreateFunc;
            }
        }
        #endregion

        /// <description>
        /// ai.moveForward();
        /// </description>
        public void MoveForward() {
             InternalUnsafeMethods.MoveForward__Args _args = new InternalUnsafeMethods.MoveForward__Args() {
             };
             InternalUnsafeMethods.MoveForward()(ObjectPtr, _args);
        }

        /// <description>
        /// ai.getLocation();
        /// </description>
        public Point3F GetLocation() {
             InternalUnsafeMethods.GetLocation__Args _args = new InternalUnsafeMethods.GetLocation__Args() {
             };
             Point3F.InternalStruct _engineResult = InternalUnsafeMethods.GetLocation()(ObjectPtr, _args);
             return new Point3F(_engineResult);
        }

        /// <description>
        /// ai.move();
        /// </description>
        public void Move() {
             InternalUnsafeMethods.Move__Args _args = new InternalUnsafeMethods.Move__Args() {
             };
             InternalUnsafeMethods.Move()(ObjectPtr, _args);
        }

        /// <description>
        /// ai.missionCycleCleanup();
        /// </description>
        public void MissionCycleCleanup() {
             InternalUnsafeMethods.MissionCycleCleanup__Args _args = new InternalUnsafeMethods.MissionCycleCleanup__Args() {
             };
             InternalUnsafeMethods.MissionCycleCleanup()(ObjectPtr, _args);
        }

        /// <description>
        /// ai.getTargetObject();
        /// </description>
        public int GetTargetObject() {
             InternalUnsafeMethods.GetTargetObject__Args _args = new InternalUnsafeMethods.GetTargetObject__Args() {
             };
             int _engineResult = InternalUnsafeMethods.GetTargetObject()(ObjectPtr, _args);
             return _engineResult;
        }

        /// <description>
        /// ai.setTargetObject( obj );
        /// </description>
        public void SetTargetObject(string objName) {
             InternalUnsafeMethods.SetTargetObject__Args _args = new InternalUnsafeMethods.SetTargetObject__Args() {
                objName = objName,
             };
             InternalUnsafeMethods.SetTargetObject()(ObjectPtr, _args);
        }

        /// <description>
        /// ai.getMoveDestination();
        /// </description>
        public Point3F GetMoveDestination() {
             InternalUnsafeMethods.GetMoveDestination__Args _args = new InternalUnsafeMethods.GetMoveDestination__Args() {
             };
             Point3F.InternalStruct _engineResult = InternalUnsafeMethods.GetMoveDestination()(ObjectPtr, _args);
             return new Point3F(_engineResult);
        }

        /// <description>
        /// ai.getAimLocation();
        /// </description>
        public Point3F GetAimLocation() {
             InternalUnsafeMethods.GetAimLocation__Args _args = new InternalUnsafeMethods.GetAimLocation__Args() {
             };
             Point3F.InternalStruct _engineResult = InternalUnsafeMethods.GetAimLocation()(ObjectPtr, _args);
             return new Point3F(_engineResult);
        }

        /// <description>
        /// ai.setMoveDestination( x y z );
        /// </description>
        public void SetMoveDestination(Point3F v) {
v.Alloc();             InternalUnsafeMethods.SetMoveDestination__Args _args = new InternalUnsafeMethods.SetMoveDestination__Args() {
                v = v.internalStructPtr,
             };
             InternalUnsafeMethods.SetMoveDestination()(ObjectPtr, _args);
v.Free();        }

        /// <description>
        /// ai.setAimLocation( x y z );
        /// </description>
        public void SetAimLocation(Point3F v) {
v.Alloc();             InternalUnsafeMethods.SetAimLocation__Args _args = new InternalUnsafeMethods.SetAimLocation__Args() {
                v = v.internalStructPtr,
             };
             InternalUnsafeMethods.SetAimLocation()(ObjectPtr, _args);
v.Free();        }

        /// <description>
        /// ai.stop();
        /// </description>
        public void Stop() {
             InternalUnsafeMethods.Stop__Args _args = new InternalUnsafeMethods.Stop__Args() {
             };
             InternalUnsafeMethods.Stop()(ObjectPtr, _args);
        }

        /// <description>
        /// ai.setMoveSpeed( float );
        /// </description>
        public void SetMoveSpeed(float speed) {
             InternalUnsafeMethods.SetMoveSpeed__Args _args = new InternalUnsafeMethods.SetMoveSpeed__Args() {
                speed = speed,
             };
             InternalUnsafeMethods.SetMoveSpeed()(ObjectPtr, _args);
        }

        /// 
        public virtual void OnConnect(string idString) {
             InternalUnsafeMethods.OnConnect__Args _args = new InternalUnsafeMethods.OnConnect__Args() {
                idString = idString,
             };
             InternalUnsafeMethods.OnConnect()(ObjectPtr, _args);
        }

        /// <description>
        /// Get the type info object for the AIClient class.
        /// </description>
        /// <returns>The type info object for AIClient</returns>
        public static EngineTypeInfo StaticGetType() {
             InternalUnsafeMethods.StaticGetType__Args _args = new InternalUnsafeMethods.StaticGetType__Args() {
             };
             IntPtr _engineResult = InternalUnsafeMethods.StaticGetType()(_args);
             return new EngineTypeInfo(_engineResult);
        }
    }
}