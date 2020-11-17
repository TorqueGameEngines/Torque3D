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
    /// <summary>Represents geometry to be mounted to a ShapeBase object.</summary>
    /// <description>
    /// 
    /// </description>
    public unsafe class ShapeBaseImageData : GameBaseData {
        public ShapeBaseImageData(bool pRegister = false) 
            : base(pRegister) {
        }
        
        public ShapeBaseImageData(string pName, bool pRegister) 
            : this(false) {
            Name = pName;
            if (pRegister) {
                RegisterObject();
            }
        }
        
        public ShapeBaseImageData(string pName) 
            : this(pName, false) {
        }
        
        public ShapeBaseImageData(string pName, string pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(Engine.Sim.FindObject<SimObject>(pParent));
        }
        
        public ShapeBaseImageData(string pName, SimObject pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(pParent);
        }
        
        public ShapeBaseImageData(SimObject pObj) 
            : base(pObj) {
        }
        
        public ShapeBaseImageData(IntPtr pObj) 
            : base(pObj) {
        }
        
		protected override void CreateObjectPtr()
		{
			ObjectPtr = InternalUnsafeMethods.Create()(new InternalUnsafeMethods.Create__Args());
		}

        #region UnsafeNativeMethods
        new internal struct InternalUnsafeMethods {
            [StructLayout(LayoutKind.Sequential)]
            internal struct OnUnmount__Args
            {
                internal IntPtr obj;
                internal int slot;
                internal float dt;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _OnUnmount(IntPtr _this, OnUnmount__Args args);
            private static _OnUnmount _OnUnmountFunc;
            internal static _OnUnmount OnUnmount() {
                if (_OnUnmountFunc == null) {
                    _OnUnmountFunc =
                        (_OnUnmount)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "cbShapeBaseImageData_onUnmount"), typeof(_OnUnmount));
                }
                
                return _OnUnmountFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct OnMount__Args
            {
                internal IntPtr obj;
                internal int slot;
                internal float dt;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _OnMount(IntPtr _this, OnMount__Args args);
            private static _OnMount _OnMountFunc;
            internal static _OnMount OnMount() {
                if (_OnMountFunc == null) {
                    _OnMountFunc =
                        (_OnMount)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "cbShapeBaseImageData_onMount"), typeof(_OnMount));
                }
                
                return _OnMountFunc;
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
                                "fnShapeBaseImageData_staticGetType"), typeof(_StaticGetType));
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
                                "fnShapeBaseImageData_create"), typeof(_Create));
                }
                
                return _CreateFunc;
            }
        }
        #endregion

        /// <summary>Called when the Image is unmounted from the object.</summary>
        /// <description>
        /// 
        /// </description>
        /// <param name="obj">object that this Image has been unmounted from</param>
        /// <param name="slot">Image mount slot on the object</param>
        /// <param name="dt">time remaining in this Image update</param>
        public virtual void OnUnmount(SceneObject obj, int slot, float dt) {
             InternalUnsafeMethods.OnUnmount__Args _args = new InternalUnsafeMethods.OnUnmount__Args() {
                obj = obj.ObjectPtr,
                slot = slot,
                dt = dt,
             };
             InternalUnsafeMethods.OnUnmount()(ObjectPtr, _args);
        }

        /// <summary>Called when the Image is first mounted to the object.</summary>
        /// <description>
        /// 
        /// </description>
        /// <param name="obj">object that this Image has been mounted to</param>
        /// <param name="slot">Image mount slot on the object</param>
        /// <param name="dt">time remaining in this Image update</param>
        public virtual void OnMount(SceneObject obj, int slot, float dt) {
             InternalUnsafeMethods.OnMount__Args _args = new InternalUnsafeMethods.OnMount__Args() {
                obj = obj.ObjectPtr,
                slot = slot,
                dt = dt,
             };
             InternalUnsafeMethods.OnMount()(ObjectPtr, _args);
        }

        /// <description>
        /// Get the type info object for the ShapeBaseImageData class.
        /// </description>
        /// <returns>The type info object for ShapeBaseImageData</returns>
        public static EngineTypeInfo StaticGetType() {
             InternalUnsafeMethods.StaticGetType__Args _args = new InternalUnsafeMethods.StaticGetType__Args() {
             };
             IntPtr _engineResult = InternalUnsafeMethods.StaticGetType()(_args);
             return new EngineTypeInfo(_engineResult);
        }


        /// <value>
        /// <summary>Whether to enable environment mapping on this Image.</summary>
        /// <description>
        /// 
        /// </description>
        /// </value>
        public bool Emap {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("emap"));
            set => SetFieldValue("emap", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <summary>The DTS or DAE model to use for this Image.</summary>
        /// <description>
        /// 
        /// </description>
        /// </value>
        public string ShapeFile {
            get => GenericMarshal.StringTo<string>(GetFieldValue("shapeFile"));
            set => SetFieldValue("shapeFile", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <summary>The DTS or DAE model to use for this Image when in first person.</summary>
        /// <description>
        /// This is an optional parameter that also requires either eyeOffset or useEyeNode to be set.  If none of these conditions is met then shapeFile will be used for all cases.
        /// 
        /// Typically you set a first person image for a weapon that includes the player's arms attached to it for animating while firing, reloading, etc.  This is typical of many FPS games.
        /// </description>
        /// <see cref="eyeOffset" />
        /// <see cref="useEyeNode" />
        /// </value>
        public string ShapeFileFP {
            get => GenericMarshal.StringTo<string>(GetFieldValue("shapeFileFP"));
            set => SetFieldValue("shapeFileFP", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <summary>Passed along to the mounting shape to modify animation sequences played in third person. [optional]</summary>
        /// <description>
        /// 
        /// </description>
        /// </value>
        public string ImageAnimPrefix {
            get => GenericMarshal.StringTo<string>(GetFieldValue("imageAnimPrefix"));
            set => SetFieldValue("imageAnimPrefix", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <summary>Passed along to the mounting shape to modify animation sequences played in first person. [optional]</summary>
        /// <description>
        /// 
        /// </description>
        /// </value>
        public string ImageAnimPrefixFP {
            get => GenericMarshal.StringTo<string>(GetFieldValue("imageAnimPrefixFP"));
            set => SetFieldValue("imageAnimPrefixFP", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <summary>Indicates that all shapes should be animated in sync.</summary>
        /// <description>
        /// When multiple shapes are defined for this image datablock, each of them are automatically animated in step with each other.  This allows for easy switching between between shapes when some other condition changes, such as going from first person to third person, and keeping their look consistent.  If you know that you'll never switch between shapes on the fly, such as players only being allowed in a first person view, then you could set this to false to save some calculations.
        /// 
        /// There are other circumstances internal to the engine that determine that only the current shape should be animated rather than all defined shapes.  In those cases, this property is ignored.
        /// </description>
        /// <remarks> This property is only important if you have more than one shape defined, such as shapeFileFP.
        /// 
        /// </remarks>
        /// <see cref="shapeFileFP" />
        /// </value>
        public bool AnimateAllShapes {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("animateAllShapes"));
            set => SetFieldValue("animateAllShapes", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <summary>Indicates that the image should be animated on the server.</summary>
        /// <description>
        /// In most cases you'll want this set if you're using useEyeNode.  You may also want to set this if the muzzlePoint is animated while it shoots.  You can set this to false even if these previous cases are true if the image's shape is set up in the correct position and orientation in the 'root' pose and none of the nodes are animated at key times, such as the muzzlePoint essentially remaining at the same position at the start of the fire state (it could animate just fine after the projectile is away as the muzzle vector is only calculated at the start of the state).
        /// 
        /// You'll also want to set this to true if you're animating the camera using the image's 'eye' node -- unless the movement is very subtle and doesn't need to be reflected on the server.
        /// </description>
        /// <remarks> Setting this to true causes up to four animation threads to be advanced on the server for each instance in use, although for most images only one or two are actually defined.
        /// 
        /// </remarks>
        /// <see cref="useEyeNode" />
        /// </value>
        public bool AnimateOnServer {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("animateOnServer"));
            set => SetFieldValue("animateOnServer", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <summary>The amount of time to transition between the previous sequence and new sequence when the script prefix has changed.</summary>
        /// <description>
        /// When setImageScriptAnimPrefix() is used on a ShapeBase that has this image mounted, the image will attempt to switch to the new animation sequence based on the given script prefix.  This is the amount of time it takes to transition from the previously playing animation sequence tothe new script prefix-based animation sequence.
        /// </description>
        /// <see cref="ShapeBase::setImageScriptAnimPrefix()" />
        /// </value>
        public float ScriptAnimTransitionTime {
            get => GenericMarshal.StringTo<float>(GetFieldValue("scriptAnimTransitionTime"));
            set => SetFieldValue("scriptAnimTransitionTime", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <summary>The projectile fired by this Image</summary>
        /// <description>
        /// 
        /// </description>
        /// </value>
        public ProjectileData Projectile {
            get => GenericMarshal.StringTo<ProjectileData>(GetFieldValue("Projectile"));
            set => SetFieldValue("Projectile", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <summary>Whether this Image can be cloaked.</summary>
        /// <description>
        /// Currently unused.
        /// </description>
        /// </value>
        public bool Cloakable {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("cloakable"));
            set => SetFieldValue("cloakable", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <summary>Mount node # to mount this Image to.</summary>
        /// <description>
        /// This should correspond to a mount# node on the ShapeBase derived object we are mounting to.
        /// </description>
        /// </value>
        public int MountPoint {
            get => GenericMarshal.StringTo<int>(GetFieldValue("mountPoint"));
            set => SetFieldValue("mountPoint", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <summary>"X Y Z" translation offset from this Image's <i>mountPoint</i> node to attach to.</summary>
        /// <description>
        /// Defaults to "0 0 0". ie. attach this Image's <i>mountPoint</i> node to the ShapeBase model's mount# node without any offset.
        /// </description>
        /// <see cref="rotation" />
        /// </value>
        public Point3F Offset {
            get => GenericMarshal.StringTo<Point3F>(GetFieldValue("offset"));
            set => SetFieldValue("offset", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <summary>"X Y Z ANGLE" rotation offset from this Image's <i>mountPoint</i> node to attach to.</summary>
        /// <description>
        /// Defaults to "0 0 0". ie. attach this Image's <i>mountPoint</i> node to the ShapeBase model's mount# node without any additional rotation.
        /// </description>
        /// <see cref="offset" />
        /// </value>
        public MatrixF Rotation {
            get => GenericMarshal.StringTo<MatrixF>(GetFieldValue("rotation"));
            set => SetFieldValue("rotation", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <summary>"X Y Z" translation offset from the ShapeBase model's eye node.</summary>
        /// <description>
        /// When in first person view, this is the offset from the eye node to place the gun.  This gives the gun a fixed point in space, typical of a lot of FPS games.
        /// </description>
        /// <see cref="eyeRotation" />
        /// </value>
        public Point3F EyeOffset {
            get => GenericMarshal.StringTo<Point3F>(GetFieldValue("eyeOffset"));
            set => SetFieldValue("eyeOffset", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <summary>"X Y Z ANGLE" rotation offset from the ShapeBase model's eye node.</summary>
        /// <description>
        /// When in first person view, this is the rotation from the eye node to place the gun.
        /// </description>
        /// <see cref="eyeOffset" />
        /// </value>
        public MatrixF EyeRotation {
            get => GenericMarshal.StringTo<MatrixF>(GetFieldValue("eyeRotation"));
            set => SetFieldValue("eyeRotation", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <summary>Mount image using image's eyeMount node and place the camera at the image's eye node (or at the eyeMount node if the eye node is missing).</summary>
        /// <description>
        /// When in first person view, if an 'eyeMount' node is present in the image's shape, this indicates that the image should mount eyeMount node to Player eye node for image placement.  The Player's camera should also mount to the image's eye node to inherit any animation (or the eyeMount node if the image doesn't have an eye node).
        /// </description>
        /// <remarks> Used instead of eyeOffset.
        /// 
        /// </remarks>
        /// <remarks> Read about the animateOnServer field as you may want to set it to true if you're using useEyeNode.
        /// 
        /// </remarks>
        /// <see cref="eyeOffset" />
        /// <see cref="animateOnServer" />
        /// </value>
        public bool UseEyeNode {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("useEyeNode"));
            set => SetFieldValue("useEyeNode", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <summary>Flag to adjust the aiming vector to the eye's LOS point when in 1st person view.</summary>
        /// <description>
        /// 
        /// </description>
        /// <see cref="ShapeBase::getMuzzleVector()" />
        /// </value>
        public bool CorrectMuzzleVector {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("correctMuzzleVector"));
            set => SetFieldValue("correctMuzzleVector", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <summary>Flag to adjust the aiming vector to the camera's LOS point when in 3rd person view.</summary>
        /// <description>
        /// 
        /// </description>
        /// <see cref="ShapeBase::getMuzzleVector()" />
        /// </value>
        public bool CorrectMuzzleVectorTP {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("correctMuzzleVectorTP"));
            set => SetFieldValue("correctMuzzleVectorTP", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <summary>Set to true to render the image in first person.</summary>
        /// </value>
        public bool FirstPerson {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("firstPerson"));
            set => SetFieldValue("firstPerson", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <summary>Mass of this Image.</summary>
        /// <description>
        /// This is added to the total mass of the ShapeBase object.
        /// </description>
        /// </value>
        public float Mass {
            get => GenericMarshal.StringTo<float>(GetFieldValue("mass"));
            set => SetFieldValue("mass", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <summary>Flag indicating whether this Image uses energy instead of ammo.  The energy level comes from the ShapeBase object we're mounted to.</summary>
        /// <description>
        /// 
        /// </description>
        /// <see cref="ShapeBase::setEnergyLevel()" />
        /// </value>
        public bool UsesEnergy {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("usesEnergy"));
            set => SetFieldValue("usesEnergy", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <summary>Minimum Image energy for it to be operable.</summary>
        /// <description>
        /// 
        /// </description>
        /// <see cref="usesEnergy" />
        /// </value>
        public float MinEnergy {
            get => GenericMarshal.StringTo<float>(GetFieldValue("minEnergy"));
            set => SetFieldValue("minEnergy", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <summary>Flag to control whether the Image's aim is automatically converged with the crosshair.</summary>
        /// <description>
        /// Currently unused.
        /// </description>
        /// </value>
        public bool AccuFire {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("accuFire"));
            set => SetFieldValue("accuFire", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <summary>The type of light this Image emits.</summary>
        /// <description>
        /// 
        /// </description>
        /// <see cref="ShapeBaseImageLightType" />
        /// </value>
        public ShapeBaseImageLightType LightType {
            get => GenericMarshal.StringTo<ShapeBaseImageLightType>(GetFieldValue("lightType"));
            set => SetFieldValue("lightType", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <summary>The color of light this Image emits.</summary>
        /// <description>
        /// 
        /// </description>
        /// <see cref="lightType" />
        /// </value>
        public LinearColorF LightColor {
            get => GenericMarshal.StringTo<LinearColorF>(GetFieldValue("lightColor"));
            set => SetFieldValue("lightColor", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <summary>Duration in SimTime of Pulsing and WeaponFire type lights.</summary>
        /// <description>
        /// 
        /// </description>
        /// <see cref="lightType" />
        /// </value>
        public int LightDuration {
            get => GenericMarshal.StringTo<int>(GetFieldValue("lightDuration"));
            set => SetFieldValue("lightDuration", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <summary>Radius of the light this Image emits.</summary>
        /// <description>
        /// 
        /// </description>
        /// <see cref="lightType" />
        /// </value>
        public float LightRadius {
            get => GenericMarshal.StringTo<float>(GetFieldValue("lightRadius"));
            set => SetFieldValue("lightRadius", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <summary>Brightness of the light this Image emits.</summary>
        /// <description>
        /// Only valid for WeaponFireLight.
        /// </description>
        /// <see cref="lightType" />
        /// </value>
        public float LightBrightness {
            get => GenericMarshal.StringTo<float>(GetFieldValue("lightBrightness"));
            set => SetFieldValue("lightBrightness", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <summary>Flag indicating whether the camera should shake when this Image fires.</summary>
        /// <description>
        /// 
        /// </description>
        /// </value>
        public bool ShakeCamera {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("ShakeCamera"));
            set => SetFieldValue("ShakeCamera", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <summary>Frequency of the camera shaking effect.</summary>
        /// <description>
        /// 
        /// </description>
        /// <see cref="shakeCamera" />
        /// </value>
        public Point3F CamShakeFreq {
            get => GenericMarshal.StringTo<Point3F>(GetFieldValue("camShakeFreq"));
            set => SetFieldValue("camShakeFreq", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <summary>Amplitude of the camera shaking effect.</summary>
        /// <description>
        /// 
        /// </description>
        /// <see cref="shakeCamera" />
        /// </value>
        public Point3F CamShakeAmp {
            get => GenericMarshal.StringTo<Point3F>(GetFieldValue("camShakeAmp"));
            set => SetFieldValue("camShakeAmp", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Duration (in seconds) to shake the camera.
        /// </description>
        /// </value>
        public float CamShakeDuration {
            get => GenericMarshal.StringTo<float>(GetFieldValue("camShakeDuration"));
            set => SetFieldValue("camShakeDuration", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Radial distance that a camera's position must be within relative to the center of the explosion to be shaken.
        /// </description>
        /// </value>
        public float CamShakeRadius {
            get => GenericMarshal.StringTo<float>(GetFieldValue("camShakeRadius"));
            set => SetFieldValue("camShakeRadius", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Falloff value for the camera shake.
        /// </description>
        /// </value>
        public float CamShakeFalloff {
            get => GenericMarshal.StringTo<float>(GetFieldValue("camShakeFalloff"));
            set => SetFieldValue("camShakeFalloff", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <summary>DebrisData datablock to use for ejected casings.</summary>
        /// <description>
        /// 
        /// </description>
        /// <see cref="stateEjectShell" />
        /// </value>
        public DebrisData Casing {
            get => GenericMarshal.StringTo<DebrisData>(GetFieldValue("casing"));
            set => SetFieldValue("casing", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <summary>Vector direction to eject shell casings.</summary>
        /// <description>
        /// 
        /// </description>
        /// <see cref="casing" />
        /// </value>
        public Point3F ShellExitDir {
            get => GenericMarshal.StringTo<Point3F>(GetFieldValue("shellExitDir"));
            set => SetFieldValue("shellExitDir", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <summary>Variance (in degrees) from the shellExitDir vector to eject casings.</summary>
        /// <description>
        /// 
        /// </description>
        /// <see cref="shellExitDir" />
        /// </value>
        public float ShellExitVariance {
            get => GenericMarshal.StringTo<float>(GetFieldValue("shellExitVariance"));
            set => SetFieldValue("shellExitVariance", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <summary>Speed at which to eject casings.</summary>
        /// <description>
        /// 
        /// </description>
        /// <see cref="casing" />
        /// </value>
        public float ShellVelocity {
            get => GenericMarshal.StringTo<float>(GetFieldValue("shellVelocity"));
            set => SetFieldValue("shellVelocity", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Name of this state.
        /// </description>
        /// </value>
        public DynamicFieldVector<string> StateName {
            get => new DynamicFieldVector<string>(
                    this, 
                    "stateName", 
                    31, 
                    val => GenericMarshal.StringTo<string>(val),
                    obj => GenericMarshal.ToString(obj)
                );
        }


        /// <value>
        /// <description>
        /// Name of the state to transition to when the loaded state of the Image changes to 'Loaded'.
        /// </description>
        /// </value>
        public DynamicFieldVector<string> StateTransitionOnLoaded {
            get => new DynamicFieldVector<string>(
                    this, 
                    "stateTransitionOnLoaded", 
                    31, 
                    val => GenericMarshal.StringTo<string>(val),
                    obj => GenericMarshal.ToString(obj)
                );
        }


        /// <value>
        /// <description>
        /// Name of the state to transition to when the loaded state of the Image changes to 'Empty'.
        /// </description>
        /// </value>
        public DynamicFieldVector<string> StateTransitionOnNotLoaded {
            get => new DynamicFieldVector<string>(
                    this, 
                    "stateTransitionOnNotLoaded", 
                    31, 
                    val => GenericMarshal.StringTo<string>(val),
                    obj => GenericMarshal.ToString(obj)
                );
        }


        /// <value>
        /// <description>
        /// Name of the state to transition to when the ammo state of the Image changes to true.
        /// </description>
        /// </value>
        public DynamicFieldVector<string> StateTransitionOnAmmo {
            get => new DynamicFieldVector<string>(
                    this, 
                    "stateTransitionOnAmmo", 
                    31, 
                    val => GenericMarshal.StringTo<string>(val),
                    obj => GenericMarshal.ToString(obj)
                );
        }


        /// <value>
        /// <description>
        /// Name of the state to transition to when the ammo state of the Image changes to false.
        /// </description>
        /// </value>
        public DynamicFieldVector<string> StateTransitionOnNoAmmo {
            get => new DynamicFieldVector<string>(
                    this, 
                    "stateTransitionOnNoAmmo", 
                    31, 
                    val => GenericMarshal.StringTo<string>(val),
                    obj => GenericMarshal.ToString(obj)
                );
        }


        /// <value>
        /// <description>
        /// Name of the state to transition to when the Image gains a target.
        /// </description>
        /// </value>
        public DynamicFieldVector<string> StateTransitionOnTarget {
            get => new DynamicFieldVector<string>(
                    this, 
                    "stateTransitionOnTarget", 
                    31, 
                    val => GenericMarshal.StringTo<string>(val),
                    obj => GenericMarshal.ToString(obj)
                );
        }


        /// <value>
        /// <description>
        /// Name of the state to transition to when the Image loses a target.
        /// </description>
        /// </value>
        public DynamicFieldVector<string> StateTransitionOnNoTarget {
            get => new DynamicFieldVector<string>(
                    this, 
                    "stateTransitionOnNoTarget", 
                    31, 
                    val => GenericMarshal.StringTo<string>(val),
                    obj => GenericMarshal.ToString(obj)
                );
        }


        /// <value>
        /// <description>
        /// Name of the state to transition to when the Image enters the water.
        /// </description>
        /// </value>
        public DynamicFieldVector<string> StateTransitionOnWet {
            get => new DynamicFieldVector<string>(
                    this, 
                    "stateTransitionOnWet", 
                    31, 
                    val => GenericMarshal.StringTo<string>(val),
                    obj => GenericMarshal.ToString(obj)
                );
        }


        /// <value>
        /// <description>
        /// Name of the state to transition to when the Image exits the water.
        /// </description>
        /// </value>
        public DynamicFieldVector<string> StateTransitionOnNotWet {
            get => new DynamicFieldVector<string>(
                    this, 
                    "stateTransitionOnNotWet", 
                    31, 
                    val => GenericMarshal.StringTo<string>(val),
                    obj => GenericMarshal.ToString(obj)
                );
        }


        /// <value>
        /// <description>
        /// Name of the state to transition to when the Player moves.
        /// </description>
        /// </value>
        public DynamicFieldVector<string> StateTransitionOnMotion {
            get => new DynamicFieldVector<string>(
                    this, 
                    "stateTransitionOnMotion", 
                    31, 
                    val => GenericMarshal.StringTo<string>(val),
                    obj => GenericMarshal.ToString(obj)
                );
        }


        /// <value>
        /// <description>
        /// Name of the state to transition to when the Player stops moving.
        /// </description>
        /// </value>
        public DynamicFieldVector<string> StateTransitionOnNoMotion {
            get => new DynamicFieldVector<string>(
                    this, 
                    "stateTransitionOnNoMotion", 
                    31, 
                    val => GenericMarshal.StringTo<string>(val),
                    obj => GenericMarshal.ToString(obj)
                );
        }


        /// <value>
        /// <description>
        /// Name of the state to transition to when the trigger state of the Image changes to true (fire button down).
        /// </description>
        /// </value>
        public DynamicFieldVector<string> StateTransitionOnTriggerUp {
            get => new DynamicFieldVector<string>(
                    this, 
                    "stateTransitionOnTriggerUp", 
                    31, 
                    val => GenericMarshal.StringTo<string>(val),
                    obj => GenericMarshal.ToString(obj)
                );
        }


        /// <value>
        /// <description>
        /// Name of the state to transition to when the trigger state of the Image changes to false (fire button released).
        /// </description>
        /// </value>
        public DynamicFieldVector<string> StateTransitionOnTriggerDown {
            get => new DynamicFieldVector<string>(
                    this, 
                    "stateTransitionOnTriggerDown", 
                    31, 
                    val => GenericMarshal.StringTo<string>(val),
                    obj => GenericMarshal.ToString(obj)
                );
        }


        /// <value>
        /// <description>
        /// Name of the state to transition to when the alt trigger state of the Image changes to true (alt fire button down).
        /// </description>
        /// </value>
        public DynamicFieldVector<string> StateTransitionOnAltTriggerUp {
            get => new DynamicFieldVector<string>(
                    this, 
                    "stateTransitionOnAltTriggerUp", 
                    31, 
                    val => GenericMarshal.StringTo<string>(val),
                    obj => GenericMarshal.ToString(obj)
                );
        }


        /// <value>
        /// <description>
        /// Name of the state to transition to when the alt trigger state of the Image changes to false (alt fire button up).
        /// </description>
        /// </value>
        public DynamicFieldVector<string> StateTransitionOnAltTriggerDown {
            get => new DynamicFieldVector<string>(
                    this, 
                    "stateTransitionOnAltTriggerDown", 
                    31, 
                    val => GenericMarshal.StringTo<string>(val),
                    obj => GenericMarshal.ToString(obj)
                );
        }


        /// <value>
        /// <description>
        /// Name of the state to transition to when we have been in this state for stateTimeoutValue seconds.
        /// </description>
        /// </value>
        public DynamicFieldVector<string> StateTransitionOnTimeout {
            get => new DynamicFieldVector<string>(
                    this, 
                    "stateTransitionOnTimeout", 
                    31, 
                    val => GenericMarshal.StringTo<string>(val),
                    obj => GenericMarshal.ToString(obj)
                );
        }


        /// <value>
        /// <description>
        /// Name of the state to transition to when the generic trigger 0 state changes to true.
        /// </description>
        /// </value>
        public DynamicFieldVector<string> StateTransitionGeneric0In {
            get => new DynamicFieldVector<string>(
                    this, 
                    "stateTransitionGeneric0In", 
                    31, 
                    val => GenericMarshal.StringTo<string>(val),
                    obj => GenericMarshal.ToString(obj)
                );
        }


        /// <value>
        /// <description>
        /// Name of the state to transition to when the generic trigger 0 state changes to false.
        /// </description>
        /// </value>
        public DynamicFieldVector<string> StateTransitionGeneric0Out {
            get => new DynamicFieldVector<string>(
                    this, 
                    "stateTransitionGeneric0Out", 
                    31, 
                    val => GenericMarshal.StringTo<string>(val),
                    obj => GenericMarshal.ToString(obj)
                );
        }


        /// <value>
        /// <description>
        /// Name of the state to transition to when the generic trigger 1 state changes to true.
        /// </description>
        /// </value>
        public DynamicFieldVector<string> StateTransitionGeneric1In {
            get => new DynamicFieldVector<string>(
                    this, 
                    "stateTransitionGeneric1In", 
                    31, 
                    val => GenericMarshal.StringTo<string>(val),
                    obj => GenericMarshal.ToString(obj)
                );
        }


        /// <value>
        /// <description>
        /// Name of the state to transition to when the generic trigger 1 state changes to false.
        /// </description>
        /// </value>
        public DynamicFieldVector<string> StateTransitionGeneric1Out {
            get => new DynamicFieldVector<string>(
                    this, 
                    "stateTransitionGeneric1Out", 
                    31, 
                    val => GenericMarshal.StringTo<string>(val),
                    obj => GenericMarshal.ToString(obj)
                );
        }


        /// <value>
        /// <description>
        /// Name of the state to transition to when the generic trigger 2 state changes to true.
        /// </description>
        /// </value>
        public DynamicFieldVector<string> StateTransitionGeneric2In {
            get => new DynamicFieldVector<string>(
                    this, 
                    "stateTransitionGeneric2In", 
                    31, 
                    val => GenericMarshal.StringTo<string>(val),
                    obj => GenericMarshal.ToString(obj)
                );
        }


        /// <value>
        /// <description>
        /// Name of the state to transition to when the generic trigger 2 state changes to false.
        /// </description>
        /// </value>
        public DynamicFieldVector<string> StateTransitionGeneric2Out {
            get => new DynamicFieldVector<string>(
                    this, 
                    "stateTransitionGeneric2Out", 
                    31, 
                    val => GenericMarshal.StringTo<string>(val),
                    obj => GenericMarshal.ToString(obj)
                );
        }


        /// <value>
        /// <description>
        /// Name of the state to transition to when the generic trigger 3 state changes to true.
        /// </description>
        /// </value>
        public DynamicFieldVector<string> StateTransitionGeneric3In {
            get => new DynamicFieldVector<string>(
                    this, 
                    "stateTransitionGeneric3In", 
                    31, 
                    val => GenericMarshal.StringTo<string>(val),
                    obj => GenericMarshal.ToString(obj)
                );
        }


        /// <value>
        /// <description>
        /// Name of the state to transition to when the generic trigger 3 state changes to false.
        /// </description>
        /// </value>
        public DynamicFieldVector<string> StateTransitionGeneric3Out {
            get => new DynamicFieldVector<string>(
                    this, 
                    "stateTransitionGeneric3Out", 
                    31, 
                    val => GenericMarshal.StringTo<string>(val),
                    obj => GenericMarshal.ToString(obj)
                );
        }


        /// <value>
        /// <description>
        /// Time in seconds to wait before transitioning to stateTransitionOnTimeout.
        /// </description>
        /// </value>
        public DynamicFieldVector<float> StateTimeoutValue {
            get => new DynamicFieldVector<float>(
                    this, 
                    "stateTimeoutValue", 
                    31, 
                    val => GenericMarshal.StringTo<float>(val),
                    obj => GenericMarshal.ToString(obj)
                );
        }


        /// <value>
        /// <description>
        /// If false, this state ignores stateTimeoutValue and transitions immediately if other transition conditions are met.
        /// </description>
        /// </value>
        public DynamicFieldVector<bool> StateWaitForTimeout {
            get => new DynamicFieldVector<bool>(
                    this, 
                    "stateWaitForTimeout", 
                    31, 
                    val => GenericMarshal.StringTo<bool>(val),
                    obj => GenericMarshal.ToString(obj)
                );
        }


        /// <value>
        /// <description>
        /// The first state with this set to true is the state entered by the client when it receives the 'fire' event.
        /// </description>
        /// </value>
        public DynamicFieldVector<bool> StateFire {
            get => new DynamicFieldVector<bool>(
                    this, 
                    "stateFire", 
                    31, 
                    val => GenericMarshal.StringTo<bool>(val),
                    obj => GenericMarshal.ToString(obj)
                );
        }


        /// <value>
        /// <description>
        /// The first state with this set to true is the state entered by the client when it receives the 'altFire' event.
        /// </description>
        /// </value>
        public DynamicFieldVector<bool> StateAlternateFire {
            get => new DynamicFieldVector<bool>(
                    this, 
                    "stateAlternateFire", 
                    31, 
                    val => GenericMarshal.StringTo<bool>(val),
                    obj => GenericMarshal.ToString(obj)
                );
        }


        /// <value>
        /// <description>
        /// The first state with this set to true is the state entered by the client when it receives the 'reload' event.
        /// </description>
        /// </value>
        public DynamicFieldVector<bool> StateReload {
            get => new DynamicFieldVector<bool>(
                    this, 
                    "stateReload", 
                    31, 
                    val => GenericMarshal.StringTo<bool>(val),
                    obj => GenericMarshal.ToString(obj)
                );
        }


        /// <value>
        /// <description>
        /// If true, a shell casing will be ejected in this state.
        /// </description>
        /// </value>
        public DynamicFieldVector<bool> StateEjectShell {
            get => new DynamicFieldVector<bool>(
                    this, 
                    "stateEjectShell", 
                    31, 
                    val => GenericMarshal.StringTo<bool>(val),
                    obj => GenericMarshal.ToString(obj)
                );
        }


        /// <value>
        /// <summary>Amount of energy to subtract from the Image in this state.</summary>
        /// <description>
        /// Energy is drained at stateEnergyDrain units/tick as long as we are in this state.
        /// </description>
        /// <see cref="usesEnergy" />
        /// </value>
        public DynamicFieldVector<float> StateEnergyDrain {
            get => new DynamicFieldVector<float>(
                    this, 
                    "stateEnergyDrain", 
                    31, 
                    val => GenericMarshal.StringTo<float>(val),
                    obj => GenericMarshal.ToString(obj)
                );
        }


        /// <value>
        /// <summary>If false, other Images will temporarily be blocked from mounting while the state machine is executing the tasks in this state.</summary>
        /// <description>
        /// For instance, if we have a rocket launcher, the player shouldn't be able to switch out <i>while</i> firing. So, you'd set stateAllowImageChange to false in firing states, and true the rest of the time.
        /// </description>
        /// </value>
        public DynamicFieldVector<bool> StateAllowImageChange {
            get => new DynamicFieldVector<bool>(
                    this, 
                    "stateAllowImageChange", 
                    31, 
                    val => GenericMarshal.StringTo<bool>(val),
                    obj => GenericMarshal.ToString(obj)
                );
        }


        /// <value>
        /// <summary>Direction of the animation to play in this state.</summary>
        /// <description>
        /// True is forward, false is backward.
        /// </description>
        /// </value>
        public DynamicFieldVector<bool> StateDirection {
            get => new DynamicFieldVector<bool>(
                    this, 
                    "stateDirection", 
                    31, 
                    val => GenericMarshal.StringTo<bool>(val),
                    obj => GenericMarshal.ToString(obj)
                );
        }


        /// <value>
        /// <summary>Set the loaded state of the Image.</summary>
        /// <description>
        /// <ul><li>IgnoreLoaded: Don't change Image loaded state.</li><li>Loaded: Set Image loaded state to true.</li><li>NotLoaded: Set Image loaded state to false.</li></ul>
        /// </description>
        /// <see cref="ShapeBaseImageLoadedState" />
        /// </value>
        public DynamicFieldVector<ShapeBaseImageLoadedState> StateLoadedFlag {
            get => new DynamicFieldVector<ShapeBaseImageLoadedState>(
                    this, 
                    "stateLoadedFlag", 
                    31, 
                    val => GenericMarshal.StringTo<ShapeBaseImageLoadedState>(val),
                    obj => GenericMarshal.ToString(obj)
                );
        }


        /// <value>
        /// <summary>Controls how fast the 'spin' animation sequence will be played in this state.</summary>
        /// <description>
        /// <ul><li>Ignore: No change to the spin sequence.</li><li>Stop: Stops the spin sequence at its current position.</li><li>SpinUp: Increase spin sequence timeScale from 0 (on state entry) to 1 (after stateTimeoutValue seconds).</li><li>SpinDown: Decrease spin sequence timeScale from 1 (on state entry) to 0 (after stateTimeoutValue seconds).</li><li>FullSpeed: Resume the spin sequence playback at its current position with timeScale=1.</li></ul>
        /// </description>
        /// <see cref="ShapeBaseImageSpinState" />
        /// </value>
        public DynamicFieldVector<ShapeBaseImageSpinState> StateSpinThread {
            get => new DynamicFieldVector<ShapeBaseImageSpinState>(
                    this, 
                    "stateSpinThread", 
                    31, 
                    val => GenericMarshal.StringTo<ShapeBaseImageSpinState>(val),
                    obj => GenericMarshal.ToString(obj)
                );
        }


        /// <value>
        /// <summary>Type of recoil sequence to play on the ShapeBase object on entry to this state.</summary>
        /// <description>
        /// <ul><li>NoRecoil: Do not play a recoil sequence.</li><li>LightRecoil: Play the light_recoil sequence.</li><li>MediumRecoil: Play the medium_recoil sequence.</li><li>HeavyRecoil: Play the heavy_recoil sequence.</li></ul>
        /// </description>
        /// <see cref="ShapeBaseImageRecoilState" />
        /// </value>
        public DynamicFieldVector<ShapeBaseImageRecoilState> StateRecoil {
            get => new DynamicFieldVector<ShapeBaseImageRecoilState>(
                    this, 
                    "stateRecoil", 
                    31, 
                    val => GenericMarshal.StringTo<ShapeBaseImageRecoilState>(val),
                    obj => GenericMarshal.ToString(obj)
                );
        }


        /// <value>
        /// <description>
        /// Name of the sequence to play on entry to this state.
        /// </description>
        /// </value>
        public DynamicFieldVector<string> StateSequence {
            get => new DynamicFieldVector<string>(
                    this, 
                    "stateSequence", 
                    31, 
                    val => GenericMarshal.StringTo<string>(val),
                    obj => GenericMarshal.ToString(obj)
                );
        }


        /// <value>
        /// <summary>If true, the muzzle flash sequence will be played while in this state.</summary>
        /// <description>
        /// The name of the muzzle flash sequence is the same as stateSequence, with "_vis" at the end.
        /// </description>
        /// </value>
        public DynamicFieldVector<bool> StateSequenceRandomFlash {
            get => new DynamicFieldVector<bool>(
                    this, 
                    "stateSequenceRandomFlash", 
                    31, 
                    val => GenericMarshal.StringTo<bool>(val),
                    obj => GenericMarshal.ToString(obj)
                );
        }


        /// <value>
        /// <description>
        /// If true, the timeScale of the stateSequence animation will be adjusted such that the sequence plays for stateTimeoutValue seconds.
        /// </description>
        /// </value>
        public DynamicFieldVector<bool> StateScaleAnimation {
            get => new DynamicFieldVector<bool>(
                    this, 
                    "stateScaleAnimation", 
                    31, 
                    val => GenericMarshal.StringTo<bool>(val),
                    obj => GenericMarshal.ToString(obj)
                );
        }


        /// <value>
        /// <description>
        /// If true, the timeScale of the first person stateSequence animation will be adjusted such that the sequence plays for stateTimeoutValue seconds.
        /// </description>
        /// </value>
        public DynamicFieldVector<bool> StateScaleAnimationFP {
            get => new DynamicFieldVector<bool>(
                    this, 
                    "stateScaleAnimationFP", 
                    31, 
                    val => GenericMarshal.StringTo<bool>(val),
                    obj => GenericMarshal.ToString(obj)
                );
        }


        /// <value>
        /// <description>
        /// Do we transition to the state's sequence when we enter the state?
        /// </description>
        /// </value>
        public DynamicFieldVector<bool> StateSequenceTransitionIn {
            get => new DynamicFieldVector<bool>(
                    this, 
                    "stateSequenceTransitionIn", 
                    31, 
                    val => GenericMarshal.StringTo<bool>(val),
                    obj => GenericMarshal.ToString(obj)
                );
        }


        /// <value>
        /// <description>
        /// Do we transition to the new state's sequence when we leave the state?
        /// </description>
        /// </value>
        public DynamicFieldVector<bool> StateSequenceTransitionOut {
            get => new DynamicFieldVector<bool>(
                    this, 
                    "stateSequenceTransitionOut", 
                    31, 
                    val => GenericMarshal.StringTo<bool>(val),
                    obj => GenericMarshal.ToString(obj)
                );
        }


        /// <value>
        /// <description>
        /// Never allow a transition to this sequence.  Often used for a fire sequence.
        /// </description>
        /// </value>
        public DynamicFieldVector<bool> StateSequenceNeverTransition {
            get => new DynamicFieldVector<bool>(
                    this, 
                    "stateSequenceNeverTransition", 
                    31, 
                    val => GenericMarshal.StringTo<bool>(val),
                    obj => GenericMarshal.ToString(obj)
                );
        }


        /// <value>
        /// <description>
        /// The time to transition in or out of a sequence.
        /// </description>
        /// </value>
        public DynamicFieldVector<float> StateSequenceTransitionTime {
            get => new DynamicFieldVector<float>(
                    this, 
                    "stateSequenceTransitionTime", 
                    31, 
                    val => GenericMarshal.StringTo<float>(val),
                    obj => GenericMarshal.ToString(obj)
                );
        }


        /// <value>
        /// <description>
        /// Name of the sequence that is played on the mounting shape.
        /// </description>
        /// </value>
        public DynamicFieldVector<string> StateShapeSequence {
            get => new DynamicFieldVector<string>(
                    this, 
                    "stateShapeSequence", 
                    31, 
                    val => GenericMarshal.StringTo<string>(val),
                    obj => GenericMarshal.ToString(obj)
                );
        }


        /// <value>
        /// <description>
        /// Indicates if the sequence to be played on the mounting shape should be scaled to the length of the state.
        /// </description>
        /// </value>
        public DynamicFieldVector<bool> StateScaleShapeSequence {
            get => new DynamicFieldVector<bool>(
                    this, 
                    "stateScaleShapeSequence", 
                    31, 
                    val => GenericMarshal.StringTo<bool>(val),
                    obj => GenericMarshal.ToString(obj)
                );
        }


        /// <value>
        /// <description>
        /// Sound to play on entry to this state.
        /// </description>
        /// </value>
        public DynamicFieldVector<SFXTrack> StateSound {
            get => new DynamicFieldVector<SFXTrack>(
                    this, 
                    "stateSound", 
                    31, 
                    val => GenericMarshal.StringTo<SFXTrack>(val),
                    obj => GenericMarshal.ToString(obj)
                );
        }


        /// <value>
        /// <summary>Method to execute on entering this state.</summary>
        /// <description>
        /// Scoped to this image class name, then ShapeBaseImageData. The script callback function takes the same arguments as the onMount callback.
        /// </description>
        /// <see cref="onMount() for the same arguments as this callback." />
        /// </value>
        public DynamicFieldVector<string> StateScript {
            get => new DynamicFieldVector<string>(
                    this, 
                    "stateScript", 
                    31, 
                    val => GenericMarshal.StringTo<string>(val),
                    obj => GenericMarshal.ToString(obj)
                );
        }


        /// <value>
        /// <summary>Emitter to generate particles in this state (from muzzle point or specified node).</summary>
        /// <description>
        /// 
        /// </description>
        /// <see cref="stateEmitterNode" />
        /// </value>
        public DynamicFieldVector<ParticleEmitterData> StateEmitter {
            get => new DynamicFieldVector<ParticleEmitterData>(
                    this, 
                    "stateEmitter", 
                    31, 
                    val => GenericMarshal.StringTo<ParticleEmitterData>(val),
                    obj => GenericMarshal.ToString(obj)
                );
        }


        /// <value>
        /// <description>
        /// How long (in seconds) to emit particles on entry to this state.
        /// </description>
        /// </value>
        public DynamicFieldVector<float> StateEmitterTime {
            get => new DynamicFieldVector<float>(
                    this, 
                    "stateEmitterTime", 
                    31, 
                    val => GenericMarshal.StringTo<float>(val),
                    obj => GenericMarshal.ToString(obj)
                );
        }


        /// <value>
        /// <summary>Name of the node to emit particles from.</summary>
        /// <description>
        /// 
        /// </description>
        /// <see cref="stateEmitter" />
        /// </value>
        public DynamicFieldVector<string> StateEmitterNode {
            get => new DynamicFieldVector<string>(
                    this, 
                    "stateEmitterNode", 
                    31, 
                    val => GenericMarshal.StringTo<string>(val),
                    obj => GenericMarshal.ToString(obj)
                );
        }


        /// <value>
        /// <summary>If set to true, and both ready and loaded transitions are true, the ready transition will be taken instead of the loaded transition.</summary>
        /// <description>
        /// A state is 'ready' if pressing the fire trigger in that state would transition to the fire state.
        /// </description>
        /// </value>
        public DynamicFieldVector<bool> StateIgnoreLoadedForReady {
            get => new DynamicFieldVector<bool>(
                    this, 
                    "stateIgnoreLoadedForReady", 
                    31, 
                    val => GenericMarshal.StringTo<bool>(val),
                    obj => GenericMarshal.ToString(obj)
                );
        }


        /// <value>
        /// <description>
        /// If true, verify that the CRC of the client's Image matches the server's CRC for the Image when loaded by the client.
        /// </description>
        /// </value>
        public bool ComputeCRC {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("computeCRC"));
            set => SetFieldValue("computeCRC", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <summary>Maximum number of sounds this Image can play at a time.</summary>
        /// <description>
        /// Any value <= 0 indicates that it can play an infinite number of sounds.
        /// </description>
        /// </value>
        public int MaxConcurrentSounds {
            get => GenericMarshal.StringTo<int>(GetFieldValue("maxConcurrentSounds"));
            set => SetFieldValue("maxConcurrentSounds", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <summary>If true, allow multiple timeout transitions to occur within a single tick (useful if states have a very small timeout).</summary>
        /// <description>
        /// 
        /// </description>
        /// </value>
        public bool UseRemainderDT {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("useRemainderDT"));
            set => SetFieldValue("useRemainderDT", GenericMarshal.ToString(value));
        }
    }
}