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
    /// <summary>Defines properties for a ShapeBase object.</summary>
    /// <description>
    /// 
    /// </description>
    /// <see cref="ShapeBase" />
    public unsafe class ShapeBaseData : GameBaseData {
        public ShapeBaseData(bool pRegister = false) 
            : base(pRegister) {
        }
        
        public ShapeBaseData(string pName, bool pRegister) 
            : this(false) {
            Name = pName;
            if (pRegister) {
                RegisterObject();
            }
        }
        
        public ShapeBaseData(string pName) 
            : this(pName, false) {
        }
        
        public ShapeBaseData(string pName, string pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(Engine.Sim.FindObject<SimObject>(pParent));
        }
        
        public ShapeBaseData(string pName, SimObject pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(pParent);
        }
        
        public ShapeBaseData(SimObject pObj) 
            : base(pObj) {
        }
        
        public ShapeBaseData(IntPtr pObj) 
            : base(pObj) {
        }
        
		protected override void CreateObjectPtr()
		{
			ObjectPtr = InternalUnsafeMethods.Create()(new InternalUnsafeMethods.Create__Args());
		}

        #region UnsafeNativeMethods
        new internal struct InternalUnsafeMethods {
            [StructLayout(LayoutKind.Sequential)]
            internal struct GetDeployTransform__Args
            {
                internal IntPtr pos;
                internal IntPtr normal;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate TransformF.InternalStruct _GetDeployTransform(IntPtr _this, GetDeployTransform__Args args);
            private static _GetDeployTransform _GetDeployTransformFunc;
            internal static _GetDeployTransform GetDeployTransform() {
                if (_GetDeployTransformFunc == null) {
                    _GetDeployTransformFunc =
                        (_GetDeployTransform)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnShapeBaseData_getDeployTransform"), typeof(_GetDeployTransform));
                }
                
                return _GetDeployTransformFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct CheckDeployPos__Args
            {
                internal IntPtr txfm;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            [return: MarshalAs(UnmanagedType.I1)]
            internal delegate bool _CheckDeployPos(IntPtr _this, CheckDeployPos__Args args);
            private static _CheckDeployPos _CheckDeployPosFunc;
            internal static _CheckDeployPos CheckDeployPos() {
                if (_CheckDeployPosFunc == null) {
                    _CheckDeployPosFunc =
                        (_CheckDeployPos)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnShapeBaseData_checkDeployPos"), typeof(_CheckDeployPos));
                }
                
                return _CheckDeployPosFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct OnForceUncloak__Args
            {
                internal IntPtr obj;
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string reason;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _OnForceUncloak(IntPtr _this, OnForceUncloak__Args args);
            private static _OnForceUncloak _OnForceUncloakFunc;
            internal static _OnForceUncloak OnForceUncloak() {
                if (_OnForceUncloakFunc == null) {
                    _OnForceUncloakFunc =
                        (_OnForceUncloak)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "cbShapeBaseData_onForceUncloak"), typeof(_OnForceUncloak));
                }
                
                return _OnForceUncloakFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct OnEndSequence__Args
            {
                internal IntPtr obj;
                internal int slot;
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string name;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _OnEndSequence(IntPtr _this, OnEndSequence__Args args);
            private static _OnEndSequence _OnEndSequenceFunc;
            internal static _OnEndSequence OnEndSequence() {
                if (_OnEndSequenceFunc == null) {
                    _OnEndSequenceFunc =
                        (_OnEndSequence)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "cbShapeBaseData_onEndSequence"), typeof(_OnEndSequence));
                }
                
                return _OnEndSequenceFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct OnTrigger__Args
            {
                internal IntPtr obj;
                internal int index;
                [MarshalAs(UnmanagedType.I1)]
                internal bool state;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _OnTrigger(IntPtr _this, OnTrigger__Args args);
            private static _OnTrigger _OnTriggerFunc;
            internal static _OnTrigger OnTrigger() {
                if (_OnTriggerFunc == null) {
                    _OnTriggerFunc =
                        (_OnTrigger)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "cbShapeBaseData_onTrigger"), typeof(_OnTrigger));
                }
                
                return _OnTriggerFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct OnDamage__Args
            {
                internal IntPtr obj;
                internal float delta;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _OnDamage(IntPtr _this, OnDamage__Args args);
            private static _OnDamage _OnDamageFunc;
            internal static _OnDamage OnDamage() {
                if (_OnDamageFunc == null) {
                    _OnDamageFunc =
                        (_OnDamage)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "cbShapeBaseData_onDamage"), typeof(_OnDamage));
                }
                
                return _OnDamageFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct OnCollision__Args
            {
                internal IntPtr obj;
                internal IntPtr collObj;
                internal IntPtr vec;
                internal float len;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _OnCollision(IntPtr _this, OnCollision__Args args);
            private static _OnCollision _OnCollisionFunc;
            internal static _OnCollision OnCollision() {
                if (_OnCollisionFunc == null) {
                    _OnCollisionFunc =
                        (_OnCollision)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "cbShapeBaseData_onCollision"), typeof(_OnCollision));
                }
                
                return _OnCollisionFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct OnImpact__Args
            {
                internal IntPtr obj;
                internal IntPtr collObj;
                internal IntPtr vec;
                internal float len;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _OnImpact(IntPtr _this, OnImpact__Args args);
            private static _OnImpact _OnImpactFunc;
            internal static _OnImpact OnImpact() {
                if (_OnImpactFunc == null) {
                    _OnImpactFunc =
                        (_OnImpact)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "cbShapeBaseData_onImpact"), typeof(_OnImpact));
                }
                
                return _OnImpactFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct OnDestroyed__Args
            {
                internal IntPtr obj;
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string lastState;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _OnDestroyed(IntPtr _this, OnDestroyed__Args args);
            private static _OnDestroyed _OnDestroyedFunc;
            internal static _OnDestroyed OnDestroyed() {
                if (_OnDestroyedFunc == null) {
                    _OnDestroyedFunc =
                        (_OnDestroyed)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "cbShapeBaseData_onDestroyed"), typeof(_OnDestroyed));
                }
                
                return _OnDestroyedFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct OnDisabled__Args
            {
                internal IntPtr obj;
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string lastState;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _OnDisabled(IntPtr _this, OnDisabled__Args args);
            private static _OnDisabled _OnDisabledFunc;
            internal static _OnDisabled OnDisabled() {
                if (_OnDisabledFunc == null) {
                    _OnDisabledFunc =
                        (_OnDisabled)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "cbShapeBaseData_onDisabled"), typeof(_OnDisabled));
                }
                
                return _OnDisabledFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct OnEnabled__Args
            {
                internal IntPtr obj;
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string lastState;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _OnEnabled(IntPtr _this, OnEnabled__Args args);
            private static _OnEnabled _OnEnabledFunc;
            internal static _OnEnabled OnEnabled() {
                if (_OnEnabledFunc == null) {
                    _OnEnabledFunc =
                        (_OnEnabled)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "cbShapeBaseData_onEnabled"), typeof(_OnEnabled));
                }
                
                return _OnEnabledFunc;
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
                                "fnShapeBaseData_staticGetType"), typeof(_StaticGetType));
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
                                "fnShapeBaseData_create"), typeof(_Create));
                }
                
                return _CreateFunc;
            }
        }
        #endregion

        /// <summary>Helper method to get a transform from a position and vector (suitable for use with setTransform).</summary>
        /// <description>
        /// 
        /// </description>
        /// <param name="pos">Desired transform position</param>
        /// <param name="normal">Vector of desired direction</param>
        /// <returns>The deploy transform</returns>
        public TransformF GetDeployTransform(Point3F pos, Point3F normal) {
pos.Alloc();normal.Alloc();             InternalUnsafeMethods.GetDeployTransform__Args _args = new InternalUnsafeMethods.GetDeployTransform__Args() {
                pos = pos.internalStructPtr,
                normal = normal.internalStructPtr,
             };
             TransformF.InternalStruct _engineResult = InternalUnsafeMethods.GetDeployTransform()(ObjectPtr, _args);
pos.Free();normal.Free();             return new TransformF(_engineResult);
        }

        /// <summary>Check if there is the space at the given transform is free to spawn into.</summary>
        /// <description>
        /// The shape's bounding box volume is used to check for collisions at the given world transform.  Only interior and static objects are checked for collision.
        /// </description>
        /// <param name="txfm">Deploy transform to check</param>
        /// <returns>True if the space is free, false if there is already something in the way.</returns>
        /// <remarks> This is a server side only check, and is not actually limited to spawning.
        /// </remarks>
        public bool CheckDeployPos(TransformF txfm) {
txfm.Alloc();             InternalUnsafeMethods.CheckDeployPos__Args _args = new InternalUnsafeMethods.CheckDeployPos__Args() {
                txfm = txfm.internalStructPtr,
             };
             bool _engineResult = InternalUnsafeMethods.CheckDeployPos()(ObjectPtr, _args);
txfm.Free();             return _engineResult;
        }

        /// <summary>Called when the object is forced to uncloak.</summary>
        /// <description>
        /// 
        /// </description>
        /// <param name="obj">The ShapeBase object</param>
        /// <param name="reason">String describing why the object was uncloaked</param>
        public virtual void OnForceUncloak(ShapeBase obj, string reason) {
             InternalUnsafeMethods.OnForceUncloak__Args _args = new InternalUnsafeMethods.OnForceUncloak__Args() {
                obj = obj.ObjectPtr,
                reason = reason,
             };
             InternalUnsafeMethods.OnForceUncloak()(ObjectPtr, _args);
        }

        /// <summary>Called when a thread playing a non-cyclic sequence reaches the end of the sequence.</summary>
        /// <description>
        /// 
        /// </description>
        /// <param name="obj">The ShapeBase object</param>
        /// <param name="slot">Thread slot that finished playing</param>
        /// <param name="name">Thread name that finished playing</param>
        public virtual void OnEndSequence(ShapeBase obj, int slot, string name) {
             InternalUnsafeMethods.OnEndSequence__Args _args = new InternalUnsafeMethods.OnEndSequence__Args() {
                obj = obj.ObjectPtr,
                slot = slot,
                name = name,
             };
             InternalUnsafeMethods.OnEndSequence()(ObjectPtr, _args);
        }

        /// <summary>Called when a move trigger input changes state.</summary>
        /// <description>
        /// 
        /// </description>
        /// <param name="obj">The ShapeBase object</param>
        /// <param name="index">Index of the trigger that changed</param>
        /// <param name="state">New state of the trigger</param>
        public virtual void OnTrigger(ShapeBase obj, int index, bool state) {
             InternalUnsafeMethods.OnTrigger__Args _args = new InternalUnsafeMethods.OnTrigger__Args() {
                obj = obj.ObjectPtr,
                index = index,
                state = state,
             };
             InternalUnsafeMethods.OnTrigger()(ObjectPtr, _args);
        }

        /// <summary>Called when the object is damaged.</summary>
        /// <description>
        /// 
        /// </description>
        /// <param name="obj">The ShapeBase object</param>
        /// <param name="obj">The ShapeBase object</param>
        /// <param name="delta">The amount of damage received.</param>
        public virtual void OnDamage(ShapeBase obj, float delta) {
             InternalUnsafeMethods.OnDamage__Args _args = new InternalUnsafeMethods.OnDamage__Args() {
                obj = obj.ObjectPtr,
                delta = delta,
             };
             InternalUnsafeMethods.OnDamage()(ObjectPtr, _args);
        }

        /// <summary>Called when we collide with another object.</summary>
        /// <description>
        /// 
        /// </description>
        /// <param name="obj">The ShapeBase object</param>
        /// <param name="collObj">The object we collided with</param>
        /// <param name="vec">Collision impact vector</param>
        /// <param name="len">Length of the impact vector</param>
        public virtual void OnCollision(ShapeBase obj, SceneObject collObj, Point3F vec, float len) {
vec.Alloc();             InternalUnsafeMethods.OnCollision__Args _args = new InternalUnsafeMethods.OnCollision__Args() {
                obj = obj.ObjectPtr,
                collObj = collObj.ObjectPtr,
                vec = vec.internalStructPtr,
                len = len,
             };
             InternalUnsafeMethods.OnCollision()(ObjectPtr, _args);
vec.Free();        }

        /// <summary>Called when we collide with another object beyond some impact speed.</summary>
        /// <description>
        /// The Player class makes use of this callback when a collision speed is more than PlayerData::minImpactSpeed.
        /// </description>
        /// <param name="obj">The ShapeBase object</param>
        /// <param name="collObj">The object we collided with</param>
        /// <param name="vec">Collision impact vector</param>
        /// <param name="len">Length of the impact vector</param>
        public virtual void OnImpact(ShapeBase obj, SceneObject collObj, Point3F vec, float len) {
vec.Alloc();             InternalUnsafeMethods.OnImpact__Args _args = new InternalUnsafeMethods.OnImpact__Args() {
                obj = obj.ObjectPtr,
                collObj = collObj.ObjectPtr,
                vec = vec.internalStructPtr,
                len = len,
             };
             InternalUnsafeMethods.OnImpact()(ObjectPtr, _args);
vec.Free();        }

        /// <summary>Called when the object damage state changes to Destroyed.</summary>
        /// <description>
        /// 
        /// </description>
        /// <param name="obj">The ShapeBase object</param>
        /// <param name="lastState">The previous damage state</param>
        public virtual void OnDestroyed(ShapeBase obj, string lastState) {
             InternalUnsafeMethods.OnDestroyed__Args _args = new InternalUnsafeMethods.OnDestroyed__Args() {
                obj = obj.ObjectPtr,
                lastState = lastState,
             };
             InternalUnsafeMethods.OnDestroyed()(ObjectPtr, _args);
        }

        /// <summary>Called when the object damage state changes to Disabled.</summary>
        /// <description>
        /// 
        /// </description>
        /// <param name="obj">The ShapeBase object</param>
        /// <param name="lastState">The previous damage state</param>
        public virtual void OnDisabled(ShapeBase obj, string lastState) {
             InternalUnsafeMethods.OnDisabled__Args _args = new InternalUnsafeMethods.OnDisabled__Args() {
                obj = obj.ObjectPtr,
                lastState = lastState,
             };
             InternalUnsafeMethods.OnDisabled()(ObjectPtr, _args);
        }

        /// <summary>Called when the object damage state changes to Enabled.</summary>
        /// <description>
        /// 
        /// </description>
        /// <param name="obj">The ShapeBase object</param>
        /// <param name="lastState">The previous damage state</param>
        public virtual void OnEnabled(ShapeBase obj, string lastState) {
             InternalUnsafeMethods.OnEnabled__Args _args = new InternalUnsafeMethods.OnEnabled__Args() {
                obj = obj.ObjectPtr,
                lastState = lastState,
             };
             InternalUnsafeMethods.OnEnabled()(ObjectPtr, _args);
        }

        /// <description>
        /// Get the type info object for the ShapeBaseData class.
        /// </description>
        /// <returns>The type info object for ShapeBaseData</returns>
        public static EngineTypeInfo StaticGetType() {
             InternalUnsafeMethods.StaticGetType__Args _args = new InternalUnsafeMethods.StaticGetType__Args() {
             };
             IntPtr _engineResult = InternalUnsafeMethods.StaticGetType()(_args);
             return new EngineTypeInfo(_engineResult);
        }


        /// <value>
        /// <description>
        /// Enable shadows for this shape (currently unused, shadows are always enabled).
        /// </description>
        /// </value>
        public bool ShadowEnable {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("shadowEnable"));
            set => SetFieldValue("shadowEnable", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Size of the projected shadow texture (must be power of 2).
        /// </description>
        /// </value>
        public int ShadowSize {
            get => GenericMarshal.StringTo<int>(GetFieldValue("shadowSize"));
            set => SetFieldValue("shadowSize", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Maximum distance at which shadow is visible (currently unused).
        /// </description>
        /// </value>
        public float ShadowMaxVisibleDistance {
            get => GenericMarshal.StringTo<float>(GetFieldValue("shadowMaxVisibleDistance"));
            set => SetFieldValue("shadowMaxVisibleDistance", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Maximum height above ground to project shadow. If the object is higher than this no shadow will be rendered.
        /// </description>
        /// </value>
        public float ShadowProjectionDistance {
            get => GenericMarshal.StringTo<float>(GetFieldValue("shadowProjectionDistance"));
            set => SetFieldValue("shadowProjectionDistance", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Scalar applied to the radius of spot shadows (initial radius is based on the shape bounds but can be adjusted with this field).
        /// </description>
        /// </value>
        public float ShadowSphereAdjust {
            get => GenericMarshal.StringTo<float>(GetFieldValue("shadowSphereAdjust"));
            set => SetFieldValue("shadowSphereAdjust", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// The DTS or DAE model to use for this object.
        /// </description>
        /// </value>
        public string ShapeFile {
            get => GenericMarshal.StringTo<string>(GetFieldValue("shapeFile"));
            set => SetFieldValue("shapeFile", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// %Explosion to generate when this shape is blown up.
        /// </description>
        /// </value>
        public ExplosionData Explosion {
            get => GenericMarshal.StringTo<ExplosionData>(GetFieldValue("Explosion"));
            set => SetFieldValue("Explosion", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// %Explosion to generate when this shape is blown up underwater.
        /// </description>
        /// </value>
        public ExplosionData UnderwaterExplosion {
            get => GenericMarshal.StringTo<ExplosionData>(GetFieldValue("underwaterExplosion"));
            set => SetFieldValue("underwaterExplosion", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// %Debris to generate when this shape is blown up.
        /// </description>
        /// </value>
        public DebrisData Debris {
            get => GenericMarshal.StringTo<DebrisData>(GetFieldValue("Debris"));
            set => SetFieldValue("Debris", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Whether to render the shape when it is in the "Destroyed" damage state.
        /// </description>
        /// </value>
        public bool RenderWhenDestroyed {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("renderWhenDestroyed"));
            set => SetFieldValue("renderWhenDestroyed", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// The DTS or DAE model to use for auto-generated breakups.
        /// </description>
        /// <remarks> may not be functional.</remarks>
        /// </value>
        public string DebrisShapeName {
            get => GenericMarshal.StringTo<string>(GetFieldValue("debrisShapeName"));
            set => SetFieldValue("debrisShapeName", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Shape mass.
        /// Used in simulation of moving objects.
        /// </description>
        /// </value>
        public float Mass {
            get => GenericMarshal.StringTo<float>(GetFieldValue("mass"));
            set => SetFieldValue("mass", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Drag factor.
        /// Reduces velocity of moving objects.
        /// </description>
        /// </value>
        public float Drag {
            get => GenericMarshal.StringTo<float>(GetFieldValue("drag"));
            set => SetFieldValue("drag", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Shape density.
        /// Used when computing buoyancy when in water.
        /// </description>
        /// </value>
        public float Density {
            get => GenericMarshal.StringTo<float>(GetFieldValue("density"));
            set => SetFieldValue("density", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Maximum energy level for this object.
        /// </description>
        /// </value>
        public float MaxEnergy {
            get => GenericMarshal.StringTo<float>(GetFieldValue("maxEnergy"));
            set => SetFieldValue("maxEnergy", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Maximum damage level for this object.
        /// </description>
        /// </value>
        public float MaxDamage {
            get => GenericMarshal.StringTo<float>(GetFieldValue("maxDamage"));
            set => SetFieldValue("maxDamage", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Damage level above which the object is disabled.
        /// Currently unused.
        /// </description>
        /// </value>
        public float DisabledLevel {
            get => GenericMarshal.StringTo<float>(GetFieldValue("disabledLevel"));
            set => SetFieldValue("disabledLevel", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Damage level above which the object is destroyed.
        /// When the damage level increases above this value, the object damage state is set to "Destroyed".
        /// </description>
        /// </value>
        public float DestroyedLevel {
            get => GenericMarshal.StringTo<float>(GetFieldValue("destroyedLevel"));
            set => SetFieldValue("destroyedLevel", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Rate at which damage is repaired in damage units/tick.
        /// This value is subtracted from the damage level until it reaches 0.
        /// </description>
        /// </value>
        public float RepairRate {
            get => GenericMarshal.StringTo<float>(GetFieldValue("repairRate"));
            set => SetFieldValue("repairRate", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Flag controlling whether to manage our own energy level, or to use the energy level of the object we are mounted to.
        /// </description>
        /// </value>
        public bool InheritEnergyFromMount {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("inheritEnergyFromMount"));
            set => SetFieldValue("inheritEnergyFromMount", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Invincible flag; when invincible, the object cannot be damaged or repaired.
        /// </description>
        /// </value>
        public bool IsInvincible {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("isInvincible"));
            set => SetFieldValue("isInvincible", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// The maximum distance from the camera to the object.
        /// Used when computing a custom camera transform for this object.
        /// </description>
        /// <see cref="observeThroughObject" />
        /// </value>
        public float CameraMaxDist {
            get => GenericMarshal.StringTo<float>(GetFieldValue("cameraMaxDist"));
            set => SetFieldValue("cameraMaxDist", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// The minimum distance from the camera to the object.
        /// Used when computing a custom camera transform for this object.
        /// </description>
        /// <see cref="observeThroughObject" />
        /// </value>
        public float CameraMinDist {
            get => GenericMarshal.StringTo<float>(GetFieldValue("cameraMinDist"));
            set => SetFieldValue("cameraMinDist", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// The default camera vertical FOV in degrees.
        /// </description>
        /// </value>
        public float CameraDefaultFov {
            get => GenericMarshal.StringTo<float>(GetFieldValue("cameraDefaultFov"));
            set => SetFieldValue("cameraDefaultFov", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// The minimum camera vertical FOV allowed in degrees.
        /// </description>
        /// </value>
        public float CameraMinFov {
            get => GenericMarshal.StringTo<float>(GetFieldValue("cameraMinFov"));
            set => SetFieldValue("cameraMinFov", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// The maximum camera vertical FOV allowed in degrees.
        /// </description>
        /// </value>
        public float CameraMaxFov {
            get => GenericMarshal.StringTo<float>(GetFieldValue("cameraMaxFov"));
            set => SetFieldValue("cameraMaxFov", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// If the derrived class supports it, allow the camera to bank.
        /// </description>
        /// </value>
        public bool CameraCanBank {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("cameraCanBank"));
            set => SetFieldValue("cameraCanBank", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Do mounted images bank along with the camera?
        /// </description>
        /// </value>
        public bool MountedImagesBank {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("mountedImagesBank"));
            set => SetFieldValue("mountedImagesBank", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Flag controlling whether the view from this object is first person only.
        /// </description>
        /// </value>
        public bool FirstPersonOnly {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("firstPersonOnly"));
            set => SetFieldValue("firstPersonOnly", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Flag controlling whether the client uses this object's eye point to view from.
        /// </description>
        /// </value>
        public bool UseEyePoint {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("useEyePoint"));
            set => SetFieldValue("useEyePoint", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Observe this object through its camera transform and default fov.
        /// If true, when this object is the camera it can provide a custom camera transform and FOV (instead of the default eye transform).
        /// </description>
        /// </value>
        public bool ObserveThroughObject {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("observeThroughObject"));
            set => SetFieldValue("observeThroughObject", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// If true, verify that the CRC of the client's shape model matches the server's CRC for the shape model when loaded by the client.
        /// </description>
        /// </value>
        public bool ComputeCRC {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("computeCRC"));
            set => SetFieldValue("computeCRC", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// References a ReflectorDesc datablock that defines performance and quality properties for dynamic reflections.
        /// </description>
        /// </value>
        public string CubeReflectorDesc {
            get => GenericMarshal.StringTo<string>(GetFieldValue("cubeReflectorDesc"));
            set => SetFieldValue("cubeReflectorDesc", GenericMarshal.ToString(value));
        }


        /// <value>
        /// 
        /// </value>
        public string RemapTextureTags {
            get => GenericMarshal.StringTo<string>(GetFieldValue("remapTextureTags"));
            set => SetFieldValue("remapTextureTags", GenericMarshal.ToString(value));
        }


        /// <value>
        /// 
        /// </value>
        public bool SilentBBoxValidation {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("silentBBoxValidation"));
            set => SetFieldValue("silentBBoxValidation", GenericMarshal.ToString(value));
        }
    }
}