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
    /// <summary>A datablock that specifies an Animation Clip effect.</summary>
    /// <description>
    /// An Animation Clip forces a target ShapeBase-derived object, such as Player or AIPlayer, to perform a particular animation sequence. Animation Clip does not supply any new animation data, but simply selects, by name, a sequence that is already defined in the target. Animation Clip can also target afxModel effects within the same choreographer.
    /// 
    /// The target of an Animation Clip is the constraint source object specified by the posConstraint field of the enclosing effect wrapper. The target must be a ShapeBase-derived object, or an afxModel and it must contain an animation sequence with the same name as the clipName field.
    /// 
    /// Animation Clip controls the rate of animation playback and can even play a sequence in reverse. When an Animation Clip selects a blended animation sequence, it is mixed with the current animation instead of replacing it. Animation Clips can be used to activate multiple, overlapping blend sequences.
    /// 
    /// Normally when an Animation Clip is applied to a user-controlled Player, any interactive user actions will override the animation selected by the clip, but Animation Clips can be configured to temporarily block out some user actions for the duration of the clip.
    /// </description>
    public unsafe class afxAnimClipData : GameBaseData {
        public afxAnimClipData(bool pRegister = false) 
            : base(pRegister) {
        }
        
        public afxAnimClipData(string pName, bool pRegister) 
            : this(false) {
            Name = pName;
            if (pRegister) {
                RegisterObject();
            }
        }
        
        public afxAnimClipData(string pName) 
            : this(pName, false) {
        }
        
        public afxAnimClipData(string pName, string pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(Engine.Sim.FindObject<SimObject>(pParent));
        }
        
        public afxAnimClipData(string pName, SimObject pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(pParent);
        }
        
        public afxAnimClipData(SimObject pObj) 
            : base(pObj) {
        }
        
        public afxAnimClipData(IntPtr pObj) 
            : base(pObj) {
        }
        
		protected override void CreateObjectPtr()
		{
			ObjectPtr = InternalUnsafeMethods.Create()(new InternalUnsafeMethods.Create__Args());
		}

        #region UnsafeNativeMethods
        new internal struct InternalUnsafeMethods {
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
                                "fnafxAnimClipData_staticGetType"), typeof(_StaticGetType));
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
                                "fnafxAnimClipData_create"), typeof(_Create));
                }
                
                return _CreateFunc;
            }
        }
        #endregion

        /// <description>
        /// Get the type info object for the afxAnimClipData class.
        /// </description>
        /// <returns>The type info object for afxAnimClipData</returns>
        public static EngineTypeInfo StaticGetType() {
             InternalUnsafeMethods.StaticGetType__Args _args = new InternalUnsafeMethods.StaticGetType__Args() {
             };
             IntPtr _engineResult = InternalUnsafeMethods.StaticGetType()(_args);
             return new EngineTypeInfo(_engineResult);
        }


        /// <value>
        /// <description>
        /// The name of an animation sequence to be played by a ShapeBase-derived object to which this effect is constrained. Also works on afxModel effects.
        /// default: ""
        /// </description>
        /// </value>
        public string ClipName {
            get => GenericMarshal.StringTo<string>(GetFieldValue("clipName"));
            set => SetFieldValue("clipName", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// The desired playback speed for the sequence. A value of 1.0 indicates forward playback at a normal rate. Negative values cause the sequence to play backwards.
        /// default: 1.0
        /// </description>
        /// </value>
        public float Rate {
            get => GenericMarshal.StringTo<float>(GetFieldValue("rate"));
            set => SetFieldValue("rate", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Sets a starting offset for the selected animation clip. It directly specifies an animation thread position in the 0.0 to 1.0 range as a fraction of the clip's duration.
        /// default: 1.0
        /// </description>
        /// </value>
        public float PosOffset {
            get => GenericMarshal.StringTo<float>(GetFieldValue("posOffset"));
            set => SetFieldValue("posOffset", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// The duration in which the active animation overlaps and blends into the sequence selected by the animation clip.
        /// default: 0.12
        /// </description>
        /// </value>
        public float TransitionTime {
            get => GenericMarshal.StringTo<float>(GetFieldValue("transitionTime"));
            set => SetFieldValue("transitionTime", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Specifies if the animation clip should not be applied to corpses or anything else with a disabled damage state.
        /// default: false
        /// </description>
        /// </value>
        public bool IgnoreCorpse {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("ignoreCorpse"));
            set => SetFieldValue("ignoreCorpse", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Specifies if the animation clip should not be applied to living objects or anything else with an enabled damage state.
        /// default: false
        /// </description>
        /// </value>
        public bool IgnoreLiving {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("ignoreLiving"));
            set => SetFieldValue("ignoreLiving", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Indicates if the animation clip is a death animation. If the target object dies during the effect, this will prevent the object from playing another standard death animation after this clip finishes.
        /// default: false
        /// </description>
        /// </value>
        public bool TreatAsDeathAnim {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("treatAsDeathAnim"));
            set => SetFieldValue("treatAsDeathAnim", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Indicates if user control of a Player should be temporarily blocked during the clip. (See afxAnimLockData.)
        /// default: false
        /// </description>
        /// </value>
        public bool LockAnimation {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("lockAnimation"));
            set => SetFieldValue("lockAnimation", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// If true, the clip will not be played on targets that are the control object and the camera is in first person mode.
        /// default: false
        /// </description>
        /// </value>
        public bool IgnoreFirstPerson {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("ignoreFirstPerson"));
            set => SetFieldValue("ignoreFirstPerson", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// If true, the clip will not be played on targets that are the control object and the camera is in third person mode.
        /// default: false
        /// </description>
        /// </value>
        public bool IgnoreThirdPerson {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("ignoreThirdPerson"));
            set => SetFieldValue("ignoreThirdPerson", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// A synonym for ignoreLiving.
        /// </description>
        /// </value>
        public bool IgnoreDisabled {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("ignoreDisabled"));
            set => SetFieldValue("ignoreDisabled", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// A synonym for ignoreCorpse.
        /// </description>
        /// </value>
        public bool IgnoreEnabled {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("ignoreEnabled"));
            set => SetFieldValue("ignoreEnabled", GenericMarshal.ToString(value));
        }
    }
}