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
    /// 
    public unsafe class Player : ShapeBase {
        public Player(bool pRegister = false) 
            : base(pRegister) {
        }
        
        public Player(string pName, bool pRegister) 
            : this(false) {
            Name = pName;
            if (pRegister) {
                RegisterObject();
            }
        }
        
        public Player(string pName) 
            : this(pName, false) {
        }
        
        public Player(string pName, string pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(Engine.Sim.FindObject<SimObject>(pParent));
        }
        
        public Player(string pName, SimObject pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(pParent);
        }
        
        public Player(SimObject pObj) 
            : base(pObj) {
        }
        
        public Player(IntPtr pObj) 
            : base(pObj) {
        }
        
		protected override void CreateObjectPtr()
		{
			ObjectPtr = InternalUnsafeMethods.Create()(new InternalUnsafeMethods.Create__Args());
		}

        #region UnsafeNativeMethods
        new internal struct InternalUnsafeMethods {
            [StructLayout(LayoutKind.Sequential)]
            internal struct SetMovementSpeedBias__Args
            {
                internal float bias;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _SetMovementSpeedBias(IntPtr _this, SetMovementSpeedBias__Args args);
            private static _SetMovementSpeedBias _SetMovementSpeedBiasFunc;
            internal static _SetMovementSpeedBias SetMovementSpeedBias() {
                if (_SetMovementSpeedBiasFunc == null) {
                    _SetMovementSpeedBiasFunc =
                        (_SetMovementSpeedBias)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnPlayer_setMovementSpeedBias"), typeof(_SetMovementSpeedBias));
                }
                
                return _SetMovementSpeedBiasFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct CopyHeadRotation__Args
            {
                internal IntPtr other_player;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _CopyHeadRotation(IntPtr _this, CopyHeadRotation__Args args);
            private static _CopyHeadRotation _CopyHeadRotationFunc;
            internal static _CopyHeadRotation CopyHeadRotation() {
                if (_CopyHeadRotationFunc == null) {
                    _CopyHeadRotationFunc =
                        (_CopyHeadRotation)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnPlayer_copyHeadRotation"), typeof(_CopyHeadRotation));
                }
                
                return _CopyHeadRotationFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct SetLookAnimationOverride__Args
            {
                [MarshalAs(UnmanagedType.I1)]
                internal bool flag;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _SetLookAnimationOverride(IntPtr _this, SetLookAnimationOverride__Args args);
            private static _SetLookAnimationOverride _SetLookAnimationOverrideFunc;
            internal static _SetLookAnimationOverride SetLookAnimationOverride() {
                if (_SetLookAnimationOverrideFunc == null) {
                    _SetLookAnimationOverrideFunc =
                        (_SetLookAnimationOverride)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnPlayer_setLookAnimationOverride"), typeof(_SetLookAnimationOverride));
                }
                
                return _SetLookAnimationOverrideFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct IsAnimationLocked__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            [return: MarshalAs(UnmanagedType.I1)]
            internal delegate bool _IsAnimationLocked(IntPtr _this, IsAnimationLocked__Args args);
            private static _IsAnimationLocked _IsAnimationLockedFunc;
            internal static _IsAnimationLocked IsAnimationLocked() {
                if (_IsAnimationLockedFunc == null) {
                    _IsAnimationLockedFunc =
                        (_IsAnimationLocked)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnPlayer_isAnimationLocked"), typeof(_IsAnimationLocked));
                }
                
                return _IsAnimationLockedFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct GetNumDeathAnimations__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate int _GetNumDeathAnimations(IntPtr _this, GetNumDeathAnimations__Args args);
            private static _GetNumDeathAnimations _GetNumDeathAnimationsFunc;
            internal static _GetNumDeathAnimations GetNumDeathAnimations() {
                if (_GetNumDeathAnimationsFunc == null) {
                    _GetNumDeathAnimationsFunc =
                        (_GetNumDeathAnimations)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnPlayer_getNumDeathAnimations"), typeof(_GetNumDeathAnimations));
                }
                
                return _GetNumDeathAnimationsFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct CheckDismountPoint__Args
            {
                internal IntPtr oldPos;
                internal IntPtr pos;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            [return: MarshalAs(UnmanagedType.I1)]
            internal delegate bool _CheckDismountPoint(IntPtr _this, CheckDismountPoint__Args args);
            private static _CheckDismountPoint _CheckDismountPointFunc;
            internal static _CheckDismountPoint CheckDismountPoint() {
                if (_CheckDismountPointFunc == null) {
                    _CheckDismountPointFunc =
                        (_CheckDismountPoint)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnPlayer_checkDismountPoint"), typeof(_CheckDismountPoint));
                }
                
                return _CheckDismountPointFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct ClearControlObject__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _ClearControlObject(IntPtr _this, ClearControlObject__Args args);
            private static _ClearControlObject _ClearControlObjectFunc;
            internal static _ClearControlObject ClearControlObject() {
                if (_ClearControlObjectFunc == null) {
                    _ClearControlObjectFunc =
                        (_ClearControlObject)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnPlayer_clearControlObject"), typeof(_ClearControlObject));
                }
                
                return _ClearControlObjectFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct GetControlObject__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate int _GetControlObject(IntPtr _this, GetControlObject__Args args);
            private static _GetControlObject _GetControlObjectFunc;
            internal static _GetControlObject GetControlObject() {
                if (_GetControlObjectFunc == null) {
                    _GetControlObjectFunc =
                        (_GetControlObject)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnPlayer_getControlObject"), typeof(_GetControlObject));
                }
                
                return _GetControlObjectFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct SetControlObject__Args
            {
                internal IntPtr obj;
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
                                "fnPlayer_setControlObject"), typeof(_SetControlObject));
                }
                
                return _SetControlObjectFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct SetActionThread__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string name;
                [MarshalAs(UnmanagedType.I1)]
                internal bool hold;
                [MarshalAs(UnmanagedType.I1)]
                internal bool fsp;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            [return: MarshalAs(UnmanagedType.I1)]
            internal delegate bool _SetActionThread(IntPtr _this, SetActionThread__Args args);
            private static _SetActionThread _SetActionThreadFunc;
            internal static _SetActionThread SetActionThread() {
                if (_SetActionThreadFunc == null) {
                    _SetActionThreadFunc =
                        (_SetActionThread)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnPlayer_setActionThread"), typeof(_SetActionThread));
                }
                
                return _SetActionThreadFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct SetArmThread__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string name;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            [return: MarshalAs(UnmanagedType.I1)]
            internal delegate bool _SetArmThread(IntPtr _this, SetArmThread__Args args);
            private static _SetArmThread _SetArmThreadFunc;
            internal static _SetArmThread SetArmThread() {
                if (_SetArmThreadFunc == null) {
                    _SetArmThreadFunc =
                        (_SetArmThread)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnPlayer_setArmThread"), typeof(_SetArmThread));
                }
                
                return _SetArmThreadFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct GetDamageLocation__Args
            {
                internal IntPtr pos;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            
            internal delegate IntPtr _GetDamageLocation(IntPtr _this, GetDamageLocation__Args args);
            private static _GetDamageLocation _GetDamageLocationFunc;
            internal static _GetDamageLocation GetDamageLocation() {
                if (_GetDamageLocationFunc == null) {
                    _GetDamageLocationFunc =
                        (_GetDamageLocation)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnPlayer_getDamageLocation"), typeof(_GetDamageLocation));
                }
                
                return _GetDamageLocationFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct GetState__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            
            internal delegate IntPtr _GetState(IntPtr _this, GetState__Args args);
            private static _GetState _GetStateFunc;
            internal static _GetState GetState() {
                if (_GetStateFunc == null) {
                    _GetStateFunc =
                        (_GetState)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnPlayer_getState"), typeof(_GetState));
                }
                
                return _GetStateFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct AllowSwimming__Args
            {
                [MarshalAs(UnmanagedType.I1)]
                internal bool state;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _AllowSwimming(IntPtr _this, AllowSwimming__Args args);
            private static _AllowSwimming _AllowSwimmingFunc;
            internal static _AllowSwimming AllowSwimming() {
                if (_AllowSwimmingFunc == null) {
                    _AllowSwimmingFunc =
                        (_AllowSwimming)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnPlayer_allowSwimming"), typeof(_AllowSwimming));
                }
                
                return _AllowSwimmingFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct AllowProne__Args
            {
                [MarshalAs(UnmanagedType.I1)]
                internal bool state;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _AllowProne(IntPtr _this, AllowProne__Args args);
            private static _AllowProne _AllowProneFunc;
            internal static _AllowProne AllowProne() {
                if (_AllowProneFunc == null) {
                    _AllowProneFunc =
                        (_AllowProne)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnPlayer_allowProne"), typeof(_AllowProne));
                }
                
                return _AllowProneFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct AllowCrouching__Args
            {
                [MarshalAs(UnmanagedType.I1)]
                internal bool state;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _AllowCrouching(IntPtr _this, AllowCrouching__Args args);
            private static _AllowCrouching _AllowCrouchingFunc;
            internal static _AllowCrouching AllowCrouching() {
                if (_AllowCrouchingFunc == null) {
                    _AllowCrouchingFunc =
                        (_AllowCrouching)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnPlayer_allowCrouching"), typeof(_AllowCrouching));
                }
                
                return _AllowCrouchingFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct AllowSprinting__Args
            {
                [MarshalAs(UnmanagedType.I1)]
                internal bool state;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _AllowSprinting(IntPtr _this, AllowSprinting__Args args);
            private static _AllowSprinting _AllowSprintingFunc;
            internal static _AllowSprinting AllowSprinting() {
                if (_AllowSprintingFunc == null) {
                    _AllowSprintingFunc =
                        (_AllowSprinting)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnPlayer_allowSprinting"), typeof(_AllowSprinting));
                }
                
                return _AllowSprintingFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct AllowJetJumping__Args
            {
                [MarshalAs(UnmanagedType.I1)]
                internal bool state;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _AllowJetJumping(IntPtr _this, AllowJetJumping__Args args);
            private static _AllowJetJumping _AllowJetJumpingFunc;
            internal static _AllowJetJumping AllowJetJumping() {
                if (_AllowJetJumpingFunc == null) {
                    _AllowJetJumpingFunc =
                        (_AllowJetJumping)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnPlayer_allowJetJumping"), typeof(_AllowJetJumping));
                }
                
                return _AllowJetJumpingFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct AllowJumping__Args
            {
                [MarshalAs(UnmanagedType.I1)]
                internal bool state;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _AllowJumping(IntPtr _this, AllowJumping__Args args);
            private static _AllowJumping _AllowJumpingFunc;
            internal static _AllowJumping AllowJumping() {
                if (_AllowJumpingFunc == null) {
                    _AllowJumpingFunc =
                        (_AllowJumping)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnPlayer_allowJumping"), typeof(_AllowJumping));
                }
                
                return _AllowJumpingFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct AllowAllPoses__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _AllowAllPoses(IntPtr _this, AllowAllPoses__Args args);
            private static _AllowAllPoses _AllowAllPosesFunc;
            internal static _AllowAllPoses AllowAllPoses() {
                if (_AllowAllPosesFunc == null) {
                    _AllowAllPosesFunc =
                        (_AllowAllPoses)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnPlayer_allowAllPoses"), typeof(_AllowAllPoses));
                }
                
                return _AllowAllPosesFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct GetPose__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            
            internal delegate IntPtr _GetPose(IntPtr _this, GetPose__Args args);
            private static _GetPose _GetPoseFunc;
            internal static _GetPose GetPose() {
                if (_GetPoseFunc == null) {
                    _GetPoseFunc =
                        (_GetPose)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnPlayer_getPose"), typeof(_GetPose));
                }
                
                return _GetPoseFunc;
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
                                "fnPlayer_staticGetType"), typeof(_StaticGetType));
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
                                "fnPlayer_create"), typeof(_Create));
                }
                
                return _CreateFunc;
            }
        }
        #endregion

        /// <description>
        /// setMovementSpeedBias(F32 bias)
        /// </description>
        public void SetMovementSpeedBias(float bias) {
             InternalUnsafeMethods.SetMovementSpeedBias__Args _args = new InternalUnsafeMethods.SetMovementSpeedBias__Args() {
                bias = bias,
             };
             InternalUnsafeMethods.SetMovementSpeedBias()(ObjectPtr, _args);
        }

        /// 
        public void CopyHeadRotation(Player other_player) {
             InternalUnsafeMethods.CopyHeadRotation__Args _args = new InternalUnsafeMethods.CopyHeadRotation__Args() {
                other_player = other_player.ObjectPtr,
             };
             InternalUnsafeMethods.CopyHeadRotation()(ObjectPtr, _args);
        }

        /// 
        public void SetLookAnimationOverride(bool flag) {
             InternalUnsafeMethods.SetLookAnimationOverride__Args _args = new InternalUnsafeMethods.SetLookAnimationOverride__Args() {
                flag = flag,
             };
             InternalUnsafeMethods.SetLookAnimationOverride()(ObjectPtr, _args);
        }

        /// 
        public bool IsAnimationLocked() {
             InternalUnsafeMethods.IsAnimationLocked__Args _args = new InternalUnsafeMethods.IsAnimationLocked__Args() {
             };
             bool _engineResult = InternalUnsafeMethods.IsAnimationLocked()(ObjectPtr, _args);
             return _engineResult;
        }

        /// <summary>Get the number of death animations available to this player.</summary>
        /// <description>
        /// Death animations are assumed to be named death1-N using consecutive indices.
        /// </description>
        public int GetNumDeathAnimations() {
             InternalUnsafeMethods.GetNumDeathAnimations__Args _args = new InternalUnsafeMethods.GetNumDeathAnimations__Args() {
             };
             int _engineResult = InternalUnsafeMethods.GetNumDeathAnimations()(ObjectPtr, _args);
             return _engineResult;
        }

        /// <summary>Check if it is safe to dismount at this position.</summary>
        /// <description>
        /// Internally this method casts a ray from oldPos to pos to determine if it hits the terrain, an interior object, a water object, another player, a static shape, a vehicle (exluding the one currently mounted), or physical zone.  If this ray is in the clear, then the player's bounding box is also checked for a collision at the pos position.  If this displaced bounding box is also in the clear, then checkDismountPoint() returns true.
        /// </description>
        /// <param name="oldPos">The player's current position</param>
        /// <param name="pos">The dismount position to check</param>
        /// <returns>True if the dismount position is clear, false if not</returns>
        /// <remarks> The player must be already mounted for this method to not assert.
        /// </remarks>
        public bool CheckDismountPoint(Point3F oldPos, Point3F pos) {
oldPos.Alloc();pos.Alloc();             InternalUnsafeMethods.CheckDismountPoint__Args _args = new InternalUnsafeMethods.CheckDismountPoint__Args() {
                oldPos = oldPos.internalStructPtr,
                pos = pos.internalStructPtr,
             };
             bool _engineResult = InternalUnsafeMethods.CheckDismountPoint()(ObjectPtr, _args);
oldPos.Free();pos.Free();             return _engineResult;
        }

        /// <summary>Clears the player's current control object.</summary>
        /// <description>
        /// Returns control to the player. This internally calls Player::setControlObject(0).
        /// </description>
        /// <code>
        /// %player.clearControlObject();
        /// echo(%player.getControlObject()); //<-- Returns 0, player assumes control
        /// %player.setControlObject(%vehicle);
        /// echo(%player.getControlObject()); //<-- Returns %vehicle, player controls the vehicle now.
        /// </code>
        /// <remarks> If the player does not have a control object, the player will receive all moves from its GameConnection.  If you're looking to remove control from the player itself (i.e. stop sending moves to the player) use GameConnection::setControlObject() to transfer control to another object, such as a camera.
        /// </remarks>
        /// <see cref="setControlObject()" />
        /// <see cref="getControlObject()" />
        /// <see cref="GameConnection::setControlObject()" />
        public void ClearControlObject() {
             InternalUnsafeMethods.ClearControlObject__Args _args = new InternalUnsafeMethods.ClearControlObject__Args() {
             };
             InternalUnsafeMethods.ClearControlObject()(ObjectPtr, _args);
        }

        /// <summary>Get the current object we are controlling.</summary>
        /// <description>
        /// 
        /// </description>
        /// <returns>ID of the ShapeBase object we control, or 0 if not controlling an object.</returns>
        /// <see cref="setControlObject()" />
        /// <see cref="clearControlObject()" />
        public int GetControlObject() {
             InternalUnsafeMethods.GetControlObject__Args _args = new InternalUnsafeMethods.GetControlObject__Args() {
             };
             int _engineResult = InternalUnsafeMethods.GetControlObject()(ObjectPtr, _args);
             return _engineResult;
        }

        /// <summary>Set the object to be controlled by this player</summary>
        /// <description>
        /// It is possible to have the moves sent to the Player object from the GameConnection to be passed along to another object.  This happens, for example when a player is mounted to a vehicle.  The move commands pass through the Player and on to the vehicle (while the player remains stationary within the vehicle).  With setControlObject() you can have the Player pass along its moves to any object.  One possible use is for a player to move a remote controlled vehicle.  In this case the player does not mount the vehicle directly, but still wants to be able to control it.
        /// </description>
        /// <param name="obj">Object to control with this player</param>
        /// <returns>True if the object is valid, false if not</returns>
        /// <see cref="getControlObject()" />
        /// <see cref="clearControlObject()" />
        /// <see cref="GameConnection::setControlObject()" />
        public bool SetControlObject(ShapeBase obj) {
             InternalUnsafeMethods.SetControlObject__Args _args = new InternalUnsafeMethods.SetControlObject__Args() {
                obj = obj.ObjectPtr,
             };
             bool _engineResult = InternalUnsafeMethods.SetControlObject()(ObjectPtr, _args);
             return _engineResult;
        }

        /// <summary>Set the main action sequence to play for this player.</summary>
        /// <description>
        /// 
        /// </description>
        /// <param name="name">Name of the action sequence to set</param>
        /// <param name="hold">Set to false to get a callback on the datablock when the sequence ends (PlayerData::animationDone()).  When set to true no callback is made.</param>
        /// <param name="fsp">True if first person and none of the spine nodes in the shape should animate.  False will allow the shape's spine nodes to animate.</param>
        /// <returns>True if succesful, false if failed</returns>
        /// <remarks> The spine nodes for the Player's shape are named as follows:
        /// 
        /// <ul><li>Bip01 Pelvis</li><li>Bip01 Spine</li><li>Bip01 Spine1</li><li>Bip01 Spine2</li><li>Bip01 Neck</li><li>Bip01 Head</li></ul>
        /// 
        /// You cannot use setActionThread() to have the Player play one of the motion determined action animation sequences.  These sequences are chosen based on how the Player moves and the Player's current pose.  The names of these sequences are:
        /// 
        /// <ul><li>root</li><li>run</li><li>side</li><li>side_right</li><li>crouch_root</li><li>crouch_forward</li><li>crouch_backward</li><li>crouch_side</li><li>crouch_right</li><li>prone_root</li><li>prone_forward</li><li>prone_backward</li><li>swim_root</li><li>swim_forward</li><li>swim_backward</li><li>swim_left</li><li>swim_right</li><li>fall</li><li>jump</li><li>standjump</li><li>land</li><li>jet</li></ul>
        /// 
        /// If the player moves in any direction then the animation sequence set using this method will be cancelled and the chosen mation-based sequence will take over.  This makes great for times when the Player cannot move, such as when mounted, or when it doesn't matter if the action sequence changes, such as waving and saluting.
        /// </remarks>
        /// <code>
        /// // Place the player in a sitting position after being mounted
        /// %player.setActionThread( "sitting", true, true );
        /// </code>
        public bool SetActionThread(string name, bool hold = false, bool fsp = true) {
             InternalUnsafeMethods.SetActionThread__Args _args = new InternalUnsafeMethods.SetActionThread__Args() {
                name = name,
                hold = hold,
                fsp = fsp,
             };
             bool _engineResult = InternalUnsafeMethods.SetActionThread()(ObjectPtr, _args);
             return _engineResult;
        }

        /// <summary>Set the sequence that controls the player's arms (dynamically adjusted to match look direction).</summary>
        /// <description>
        /// 
        /// </description>
        /// <param name="name">Name of the sequence to play on the player's arms.</param>
        /// <returns>true if successful, false if failed.</returns>
        /// <remarks> By default the 'look' sequence is used, if available.
        /// </remarks>
        public bool SetArmThread(string name) {
             InternalUnsafeMethods.SetArmThread__Args _args = new InternalUnsafeMethods.SetArmThread__Args() {
                name = name,
             };
             bool _engineResult = InternalUnsafeMethods.SetArmThread()(ObjectPtr, _args);
             return _engineResult;
        }

        /// <summary>Get the named damage location and modifier for a given world position.</summary>
        /// <description>
        /// the Player object can simulate different hit locations based on a pre-defined set of PlayerData defined percentages.  These hit percentages divide up the Player's bounding box into different regions.  The diagram below demonstrates how the various PlayerData properties split up the bounding volume:
        /// 
        /// <img src="images/player_damageloc.png">
        /// 
        /// While you may pass in any world position and getDamageLocation() will provide a best-fit location, you should be aware that this can produce some interesting results.  For example, any position that is above PlayerData::boxHeadPercentage will be considered a 'head' hit, even if the world position is high in the sky.  Therefore it may be wise to keep the passed in point to somewhere on the surface of, or within, the Player's bounding volume.
        /// </description>
        /// <remarks> This method will not return an accurate location when the player is prone or swimming.
        /// 
        /// </remarks>
        /// <param name="pos">A world position for which to retrieve a body region on this player.</param>
        /// <returns>a string containing two words (space separated strings), where the first is a location and the second is a modifier.
        /// 
        /// Posible locations:<ul><li>head</li><li>torso</li><li>legs</li></ul>
        /// Head modifiers:<ul><li>left_back</li><li>middle_back</li><li>right_back</li><li>left_middle</li><li>middle_middle</li><li>right_middle</li><li>left_front</li><li>middle_front</li><li>right_front</li></ul>
        /// Legs/Torso modifiers:<ul><li>front_left</li><li>front_right</li><li>back_left</li><li>back_right</li></ul></returns>
        /// <see cref="PlayerData::boxHeadPercentage" />
        /// <see cref="PlayerData::boxHeadFrontPercentage" />
        /// <see cref="PlayerData::boxHeadBackPercentage" />
        /// <see cref="PlayerData::boxHeadLeftPercentage" />
        /// <see cref="PlayerData::boxHeadRightPercentage" />
        /// <see cref="PlayerData::boxTorsoPercentage" />
        public string GetDamageLocation(Point3F pos) {
pos.Alloc();             InternalUnsafeMethods.GetDamageLocation__Args _args = new InternalUnsafeMethods.GetDamageLocation__Args() {
                pos = pos.internalStructPtr,
             };
             IntPtr _engineResult = InternalUnsafeMethods.GetDamageLocation()(ObjectPtr, _args);
pos.Free();             return StringMarshal.IntPtrToUtf8String(_engineResult);
        }

        /// <summary>Get the name of the player's current state.</summary>
        /// <description>
        /// The state is one of the following:
        /// 
        /// <ul><li>Dead - The Player is dead.</li><li>Mounted - The Player is mounted to an object such as a vehicle.</li><li>Move - The Player is free to move.  The usual state.</li><li>Recover - The Player is recovering from a fall.  See PlayerData::recoverDelay.</li></ul>
        /// </description>
        /// <returns>The current state; one of: "Dead", "Mounted", "Move", "Recover"</returns>
        public string GetState() {
             InternalUnsafeMethods.GetState__Args _args = new InternalUnsafeMethods.GetState__Args() {
             };
             IntPtr _engineResult = InternalUnsafeMethods.GetState()(ObjectPtr, _args);
             return StringMarshal.IntPtrToUtf8String(_engineResult);
        }

        /// <summary>Set if the Player is allowed to swim.</summary>
        /// <description>
        /// The default is to allow swimming unless there are other environmental concerns that prevent it.  This method is mainly used to explicitly disallow swimming at any time.
        /// </description>
        /// <param name="state">Set to true to allow swimming, false to disable it.</param>
        /// <see cref="allowAllPoses()" />
        public void AllowSwimming(bool state) {
             InternalUnsafeMethods.AllowSwimming__Args _args = new InternalUnsafeMethods.AllowSwimming__Args() {
                state = state,
             };
             InternalUnsafeMethods.AllowSwimming()(ObjectPtr, _args);
        }

        /// <summary>Set if the Player is allowed to go prone.</summary>
        /// <description>
        /// The default is to allow being prone unless there are other environmental concerns that prevent it.  This method is mainly used to explicitly disallow going prone at any time.
        /// </description>
        /// <param name="state">Set to true to allow being prone, false to disable it.</param>
        /// <see cref="allowAllPoses()" />
        public void AllowProne(bool state) {
             InternalUnsafeMethods.AllowProne__Args _args = new InternalUnsafeMethods.AllowProne__Args() {
                state = state,
             };
             InternalUnsafeMethods.AllowProne()(ObjectPtr, _args);
        }

        /// <summary>Set if the Player is allowed to crouch.</summary>
        /// <description>
        /// The default is to allow crouching unless there are other environmental concerns that prevent it.  This method is mainly used to explicitly disallow crouching at any time.
        /// </description>
        /// <param name="state">Set to true to allow crouching, false to disable it.</param>
        /// <see cref="allowAllPoses()" />
        public void AllowCrouching(bool state) {
             InternalUnsafeMethods.AllowCrouching__Args _args = new InternalUnsafeMethods.AllowCrouching__Args() {
                state = state,
             };
             InternalUnsafeMethods.AllowCrouching()(ObjectPtr, _args);
        }

        /// <summary>Set if the Player is allowed to sprint.</summary>
        /// <description>
        /// The default is to allow sprinting unless there are other environmental concerns that prevent it.  This method is mainly used to explicitly disallow sprinting at any time.
        /// </description>
        /// <param name="state">Set to true to allow sprinting, false to disable it.</param>
        /// <see cref="allowAllPoses()" />
        public void AllowSprinting(bool state) {
             InternalUnsafeMethods.AllowSprinting__Args _args = new InternalUnsafeMethods.AllowSprinting__Args() {
                state = state,
             };
             InternalUnsafeMethods.AllowSprinting()(ObjectPtr, _args);
        }

        /// <summary>Set if the Player is allowed to jet jump.</summary>
        /// <description>
        /// The default is to allow jet jumping unless there are other environmental concerns that prevent it.  This method is mainly used to explicitly disallow jet jumping at any time.
        /// </description>
        /// <param name="state">Set to true to allow jet jumping, false to disable it.</param>
        /// <see cref="allowAllPoses()" />
        public void AllowJetJumping(bool state) {
             InternalUnsafeMethods.AllowJetJumping__Args _args = new InternalUnsafeMethods.AllowJetJumping__Args() {
                state = state,
             };
             InternalUnsafeMethods.AllowJetJumping()(ObjectPtr, _args);
        }

        /// <summary>Set if the Player is allowed to jump.</summary>
        /// <description>
        /// The default is to allow jumping unless there are other environmental concerns that prevent it.  This method is mainly used to explicitly disallow jumping at any time.
        /// </description>
        /// <param name="state">Set to true to allow jumping, false to disable it.</param>
        /// <see cref="allowAllPoses()" />
        public void AllowJumping(bool state) {
             InternalUnsafeMethods.AllowJumping__Args _args = new InternalUnsafeMethods.AllowJumping__Args() {
                state = state,
             };
             InternalUnsafeMethods.AllowJumping()(ObjectPtr, _args);
        }

        /// <summary>Allow all poses a chance to occur.</summary>
        /// <description>
        /// This method resets any poses that have manually been blocked from occuring.  This includes the regular pose states such as sprinting, crouch, being prone and swimming.  It also includes being able to jump and jet jump.  While this is allowing these poses to occur it doesn't mean that they all can due to other conditions.  We're just not manually blocking them from being allowed.
        /// </description>
        /// <see cref="allowJumping()" />
        /// <see cref="allowJetJumping()" />
        /// <see cref="allowSprinting()" />
        /// <see cref="allowCrouching()" />
        /// <see cref="allowProne()" />
        /// <see cref="allowSwimming()" />
        public void AllowAllPoses() {
             InternalUnsafeMethods.AllowAllPoses__Args _args = new InternalUnsafeMethods.AllowAllPoses__Args() {
             };
             InternalUnsafeMethods.AllowAllPoses()(ObjectPtr, _args);
        }

        /// <summary>Get the name of the player's current pose.</summary>
        /// <description>
        /// The pose is one of the following:
        /// 
        /// <ul><li>Stand - Standard movement pose.</li><li>Sprint - Sprinting pose.</li><li>Crouch - Crouch pose.</li><li>Prone - Prone pose.</li><li>Swim - Swimming pose.</li></ul>
        /// </description>
        /// <returns>The current pose; one of: "Stand", "Sprint", "Crouch", "Prone", "Swim"</returns>
        public string GetPose() {
             InternalUnsafeMethods.GetPose__Args _args = new InternalUnsafeMethods.GetPose__Args() {
             };
             IntPtr _engineResult = InternalUnsafeMethods.GetPose()(ObjectPtr, _args);
             return StringMarshal.IntPtrToUtf8String(_engineResult);
        }

        /// <description>
        /// Get the type info object for the Player class.
        /// </description>
        /// <returns>The type info object for Player</returns>
        public static EngineTypeInfo StaticGetType() {
             InternalUnsafeMethods.StaticGetType__Args _args = new InternalUnsafeMethods.StaticGetType__Args() {
             };
             IntPtr _engineResult = InternalUnsafeMethods.StaticGetType()(_args);
             return new EngineTypeInfo(_engineResult);
        }
    }
}