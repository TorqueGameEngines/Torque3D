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
    /// <summary>A datablock that specifies a Phrase Effect, a grouping of other effects.</summary>
    /// <description>
    /// A Phrase Effect is a grouping or phrase of effects that do nothing until certain trigger events occur. It's like having a whole Effectron organized as an individual effect.
    /// 
    /// Phrase effects can respond to a number of different kinds of triggers:
    ///   -- Player triggers such as footsteps, jumps, landings, and idle triggers.
    ///   -- Arbitrary animation triggers on dts-based scene objects.
    ///   -- Arbitrary trigger bits assigned to active choreographer objects.
    /// </description>
    public unsafe class afxPhraseEffectData : GameBaseData {
        public afxPhraseEffectData(bool pRegister = false) 
            : base(pRegister) {
        }
        
        public afxPhraseEffectData(string pName, bool pRegister) 
            : this(false) {
            Name = pName;
            if (pRegister) {
                RegisterObject();
            }
        }
        
        public afxPhraseEffectData(string pName) 
            : this(pName, false) {
        }
        
        public afxPhraseEffectData(string pName, string pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(Engine.Sim.FindObject<SimObject>(pParent));
        }
        
        public afxPhraseEffectData(string pName, SimObject pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(pParent);
        }
        
        public afxPhraseEffectData(SimObject pObj) 
            : base(pObj) {
        }
        
        public afxPhraseEffectData(IntPtr pObj) 
            : base(pObj) {
        }
        
		protected override void CreateObjectPtr()
		{
			ObjectPtr = InternalUnsafeMethods.Create()(new InternalUnsafeMethods.Create__Args());
		}

        #region UnsafeNativeMethods
        new internal struct InternalUnsafeMethods {
            [StructLayout(LayoutKind.Sequential)]
            internal struct PushEffect__Args
            {
                internal IntPtr effectData;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _PushEffect(IntPtr _this, PushEffect__Args args);
            private static _PushEffect _PushEffectFunc;
            internal static _PushEffect PushEffect() {
                if (_PushEffectFunc == null) {
                    _PushEffectFunc =
                        (_PushEffect)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnafxPhraseEffectData_pushEffect"), typeof(_PushEffect));
                }
                
                return _PushEffectFunc;
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
                                "fnafxPhraseEffectData_staticGetType"), typeof(_StaticGetType));
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
                                "fnafxPhraseEffectData_create"), typeof(_Create));
                }
                
                return _CreateFunc;
            }
        }
        #endregion

        /// <description>
        /// Add a child effect to a phrase effect datablock. Argument can be an afxEffectWrappperData or an afxEffectGroupData.
        /// </description>
        public void PushEffect(afxEffectBaseData effectData) {
             InternalUnsafeMethods.PushEffect__Args _args = new InternalUnsafeMethods.PushEffect__Args() {
                effectData = effectData.ObjectPtr,
             };
             InternalUnsafeMethods.PushEffect()(ObjectPtr, _args);
        }

        /// <description>
        /// Get the type info object for the afxPhraseEffectData class.
        /// </description>
        /// <returns>The type info object for afxPhraseEffectData</returns>
        public static EngineTypeInfo StaticGetType() {
             InternalUnsafeMethods.StaticGetType__Args _args = new InternalUnsafeMethods.StaticGetType__Args() {
             };
             IntPtr _engineResult = InternalUnsafeMethods.StaticGetType()(_args);
             return new EngineTypeInfo(_engineResult);
        }


        /// <value>
        /// <description>
        /// Specifies a duration for the phrase-effect. If set to infinity, the phrase-effect needs to have a phraseType of continuous. Set infinite duration using $AFX::INFINITE_TIME.
        /// </description>
        /// </value>
        public float Duration {
            get => GenericMarshal.StringTo<float>(GetFieldValue("Duration"));
            set => SetFieldValue("Duration", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Specifies the number of times the phrase-effect should loop. If set to infinity, the phrase-effect needs to have a phraseType of continuous. Set infinite looping using $AFX::INFINITE_REPEATS.
        /// </description>
        /// </value>
        public int NumLoops {
            get => GenericMarshal.StringTo<int>(GetFieldValue("numLoops"));
            set => SetFieldValue("numLoops", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Sets which bits to consider in the current trigger-state which consists of 32 trigger-bits combined from (possibly overlapping) player trigger bits, constraint trigger bits, and choreographer trigger bits.
        /// </description>
        /// </value>
        public int TriggerMask {
            get => GenericMarshal.StringTo<int>(GetFieldValue("triggerMask"));
            set => SetFieldValue("triggerMask", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Selects what combination of bits in triggerMask lead to a trigger. When set to 'any', any bit in triggerMask matching the current trigger-state will cause a trigger. If set to 'all', every bit in triggerMask must match the trigger-state. Possible values: any or all.
        /// </description>
        /// </value>
        public afxPhraseEffect_MatchType MatchType {
            get => GenericMarshal.StringTo<afxPhraseEffect_MatchType>(GetFieldValue("matchType"));
            set => SetFieldValue("matchType", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Selects which bit-state(s) of bits in the triggerMask to consider when comparing to the current trigger-state. Possible values: on, off, or both.
        /// </description>
        /// </value>
        public afxPhraseEffect_StateType MatchState {
            get => GenericMarshal.StringTo<afxPhraseEffect_StateType>(GetFieldValue("matchState"));
            set => SetFieldValue("matchState", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Selects between triggered and continuous types of phrases. When set to 'triggered', the phrase-effect is triggered when the relevant trigger-bits change state. When set to 'continuous', the phrase-effect will stay active as long as the trigger-bits remain in a matching state. Possible values: triggered or continuous.
        /// </description>
        /// </value>
        public afxPhraseEffect_PhraseType PhraseType {
            get => GenericMarshal.StringTo<afxPhraseEffect_PhraseType>(GetFieldValue("phraseType"));
            set => SetFieldValue("phraseType", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// When true, trigger-bits on the choreographer will be ignored.
        /// </description>
        /// </value>
        public bool IgnoreChoreographerTriggers {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("ignoreChoreographerTriggers"));
            set => SetFieldValue("ignoreChoreographerTriggers", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// When true, animation triggers from dts-based constraint source objects will be ignored.
        /// </description>
        /// </value>
        public bool IgnoreConstraintTriggers {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("ignoreConstraintTriggers"));
            set => SetFieldValue("ignoreConstraintTriggers", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// When true, Player-specific triggers from Player-derived constraint source objects will be ignored.
        /// </description>
        /// </value>
        public bool IgnorePlayerTriggers {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("ignorePlayerTriggers"));
            set => SetFieldValue("ignorePlayerTriggers", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Like a field substitution statement without the leading '$$' token, this eval statement will be executed when a trigger occurs. Any '%%' and '##'  tokens will be substituted.
        /// </description>
        /// </value>
        public string OnTriggerCommand {
            get => GenericMarshal.StringTo<string>(GetFieldValue("onTriggerCommand"));
            set => SetFieldValue("onTriggerCommand", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// A field macro which adds an effect wrapper datablock to a list of effects associated with the phrase-effect's single phrase. Unlike other fields, addEffect follows an unusual syntax. Order is important since the effects will resolve in the order they are added to each list.
        /// </description>
        /// </value>
        public afxEffectBaseData AddEffect {
            get => GenericMarshal.StringTo<afxEffectBaseData>(GetFieldValue("addEffect"));
            set => SetFieldValue("addEffect", GenericMarshal.ToString(value));
        }
    }
}