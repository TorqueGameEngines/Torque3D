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
    /// <summary>An object used to modify a DTS or COLLADA shape model after it has been loaded by Torque</summary>
    /// <description>
    /// 
    /// </description>
    public unsafe class TSShapeConstructor : SimObject {
        public TSShapeConstructor(bool pRegister = false) 
            : base(pRegister) {
        }
        
        public TSShapeConstructor(string pName, bool pRegister) 
            : this(false) {
            Name = pName;
            if (pRegister) {
                RegisterObject();
            }
        }
        
        public TSShapeConstructor(string pName) 
            : this(pName, false) {
        }
        
        public TSShapeConstructor(string pName, string pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(Engine.Sim.FindObject<SimObject>(pParent));
        }
        
        public TSShapeConstructor(string pName, SimObject pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(pParent);
        }
        
        public TSShapeConstructor(SimObject pObj) 
            : base(pObj) {
        }
        
        public TSShapeConstructor(IntPtr pObj) 
            : base(pObj) {
        }
        
		protected override void CreateObjectPtr()
		{
			ObjectPtr = InternalUnsafeMethods.Create()(new InternalUnsafeMethods.Create__Args());
		}

        #region UnsafeNativeMethods
        new internal struct InternalUnsafeMethods {
            [StructLayout(LayoutKind.Sequential)]
            internal struct RemoveTrigger__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string name;
                internal int keyframe;
                internal int state;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            [return: MarshalAs(UnmanagedType.I1)]
            internal delegate bool _RemoveTrigger(IntPtr _this, RemoveTrigger__Args args);
            private static _RemoveTrigger _RemoveTriggerFunc;
            internal static _RemoveTrigger RemoveTrigger() {
                if (_RemoveTriggerFunc == null) {
                    _RemoveTriggerFunc =
                        (_RemoveTrigger)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnTSShapeConstructor_removeTrigger"), typeof(_RemoveTrigger));
                }
                
                return _RemoveTriggerFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct AddTrigger__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string name;
                internal int keyframe;
                internal int state;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            [return: MarshalAs(UnmanagedType.I1)]
            internal delegate bool _AddTrigger(IntPtr _this, AddTrigger__Args args);
            private static _AddTrigger _AddTriggerFunc;
            internal static _AddTrigger AddTrigger() {
                if (_AddTriggerFunc == null) {
                    _AddTriggerFunc =
                        (_AddTrigger)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnTSShapeConstructor_addTrigger"), typeof(_AddTrigger));
                }
                
                return _AddTriggerFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct GetTrigger__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string name;
                internal int index;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            
            internal delegate IntPtr _GetTrigger(IntPtr _this, GetTrigger__Args args);
            private static _GetTrigger _GetTriggerFunc;
            internal static _GetTrigger GetTrigger() {
                if (_GetTriggerFunc == null) {
                    _GetTriggerFunc =
                        (_GetTrigger)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnTSShapeConstructor_getTrigger"), typeof(_GetTrigger));
                }
                
                return _GetTriggerFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct GetTriggerCount__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string name;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate int _GetTriggerCount(IntPtr _this, GetTriggerCount__Args args);
            private static _GetTriggerCount _GetTriggerCountFunc;
            internal static _GetTriggerCount GetTriggerCount() {
                if (_GetTriggerCountFunc == null) {
                    _GetTriggerCountFunc =
                        (_GetTriggerCount)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnTSShapeConstructor_getTriggerCount"), typeof(_GetTriggerCount));
                }
                
                return _GetTriggerCountFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct RemoveSequence__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string name;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            [return: MarshalAs(UnmanagedType.I1)]
            internal delegate bool _RemoveSequence(IntPtr _this, RemoveSequence__Args args);
            private static _RemoveSequence _RemoveSequenceFunc;
            internal static _RemoveSequence RemoveSequence() {
                if (_RemoveSequenceFunc == null) {
                    _RemoveSequenceFunc =
                        (_RemoveSequence)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnTSShapeConstructor_removeSequence"), typeof(_RemoveSequence));
                }
                
                return _RemoveSequenceFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct AddSequence__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string source;
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string name;
                internal int start;
                internal int end;
                [MarshalAs(UnmanagedType.I1)]
                internal bool padRot;
                [MarshalAs(UnmanagedType.I1)]
                internal bool padTrans;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            [return: MarshalAs(UnmanagedType.I1)]
            internal delegate bool _AddSequence(IntPtr _this, AddSequence__Args args);
            private static _AddSequence _AddSequenceFunc;
            internal static _AddSequence AddSequence() {
                if (_AddSequenceFunc == null) {
                    _AddSequenceFunc =
                        (_AddSequence)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnTSShapeConstructor_addSequence"), typeof(_AddSequence));
                }
                
                return _AddSequenceFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct RenameSequence__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string oldName;
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string newName;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            [return: MarshalAs(UnmanagedType.I1)]
            internal delegate bool _RenameSequence(IntPtr _this, RenameSequence__Args args);
            private static _RenameSequence _RenameSequenceFunc;
            internal static _RenameSequence RenameSequence() {
                if (_RenameSequenceFunc == null) {
                    _RenameSequenceFunc =
                        (_RenameSequence)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnTSShapeConstructor_renameSequence"), typeof(_RenameSequence));
                }
                
                return _RenameSequenceFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct SetSequenceBlend__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string name;
                [MarshalAs(UnmanagedType.I1)]
                internal bool blend;
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string blendSeq;
                internal int blendFrame;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            [return: MarshalAs(UnmanagedType.I1)]
            internal delegate bool _SetSequenceBlend(IntPtr _this, SetSequenceBlend__Args args);
            private static _SetSequenceBlend _SetSequenceBlendFunc;
            internal static _SetSequenceBlend SetSequenceBlend() {
                if (_SetSequenceBlendFunc == null) {
                    _SetSequenceBlendFunc =
                        (_SetSequenceBlend)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnTSShapeConstructor_setSequenceBlend"), typeof(_SetSequenceBlend));
                }
                
                return _SetSequenceBlendFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct GetSequenceBlend__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string name;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            
            internal delegate IntPtr _GetSequenceBlend(IntPtr _this, GetSequenceBlend__Args args);
            private static _GetSequenceBlend _GetSequenceBlendFunc;
            internal static _GetSequenceBlend GetSequenceBlend() {
                if (_GetSequenceBlendFunc == null) {
                    _GetSequenceBlendFunc =
                        (_GetSequenceBlend)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnTSShapeConstructor_getSequenceBlend"), typeof(_GetSequenceBlend));
                }
                
                return _GetSequenceBlendFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct SetSequenceCyclic__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string name;
                [MarshalAs(UnmanagedType.I1)]
                internal bool cyclic;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            [return: MarshalAs(UnmanagedType.I1)]
            internal delegate bool _SetSequenceCyclic(IntPtr _this, SetSequenceCyclic__Args args);
            private static _SetSequenceCyclic _SetSequenceCyclicFunc;
            internal static _SetSequenceCyclic SetSequenceCyclic() {
                if (_SetSequenceCyclicFunc == null) {
                    _SetSequenceCyclicFunc =
                        (_SetSequenceCyclic)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnTSShapeConstructor_setSequenceCyclic"), typeof(_SetSequenceCyclic));
                }
                
                return _SetSequenceCyclicFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct GetSequenceCyclic__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string name;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            [return: MarshalAs(UnmanagedType.I1)]
            internal delegate bool _GetSequenceCyclic(IntPtr _this, GetSequenceCyclic__Args args);
            private static _GetSequenceCyclic _GetSequenceCyclicFunc;
            internal static _GetSequenceCyclic GetSequenceCyclic() {
                if (_GetSequenceCyclicFunc == null) {
                    _GetSequenceCyclicFunc =
                        (_GetSequenceCyclic)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnTSShapeConstructor_getSequenceCyclic"), typeof(_GetSequenceCyclic));
                }
                
                return _GetSequenceCyclicFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct SetSequenceGroundSpeed__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string name;
                internal IntPtr transSpeed;
                internal IntPtr rotSpeed;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            [return: MarshalAs(UnmanagedType.I1)]
            internal delegate bool _SetSequenceGroundSpeed(IntPtr _this, SetSequenceGroundSpeed__Args args);
            private static _SetSequenceGroundSpeed _SetSequenceGroundSpeedFunc;
            internal static _SetSequenceGroundSpeed SetSequenceGroundSpeed() {
                if (_SetSequenceGroundSpeedFunc == null) {
                    _SetSequenceGroundSpeedFunc =
                        (_SetSequenceGroundSpeed)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnTSShapeConstructor_setSequenceGroundSpeed"), typeof(_SetSequenceGroundSpeed));
                }
                
                return _SetSequenceGroundSpeedFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct GetSequenceGroundSpeed__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string name;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            
            internal delegate IntPtr _GetSequenceGroundSpeed(IntPtr _this, GetSequenceGroundSpeed__Args args);
            private static _GetSequenceGroundSpeed _GetSequenceGroundSpeedFunc;
            internal static _GetSequenceGroundSpeed GetSequenceGroundSpeed() {
                if (_GetSequenceGroundSpeedFunc == null) {
                    _GetSequenceGroundSpeedFunc =
                        (_GetSequenceGroundSpeed)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnTSShapeConstructor_getSequenceGroundSpeed"), typeof(_GetSequenceGroundSpeed));
                }
                
                return _GetSequenceGroundSpeedFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct SetSequencePriority__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string name;
                internal float priority;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            [return: MarshalAs(UnmanagedType.I1)]
            internal delegate bool _SetSequencePriority(IntPtr _this, SetSequencePriority__Args args);
            private static _SetSequencePriority _SetSequencePriorityFunc;
            internal static _SetSequencePriority SetSequencePriority() {
                if (_SetSequencePriorityFunc == null) {
                    _SetSequencePriorityFunc =
                        (_SetSequencePriority)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnTSShapeConstructor_setSequencePriority"), typeof(_SetSequencePriority));
                }
                
                return _SetSequencePriorityFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct GetSequencePriority__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string name;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate float _GetSequencePriority(IntPtr _this, GetSequencePriority__Args args);
            private static _GetSequencePriority _GetSequencePriorityFunc;
            internal static _GetSequencePriority GetSequencePriority() {
                if (_GetSequencePriorityFunc == null) {
                    _GetSequencePriorityFunc =
                        (_GetSequencePriority)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnTSShapeConstructor_getSequencePriority"), typeof(_GetSequencePriority));
                }
                
                return _GetSequencePriorityFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct GetSequenceFrameCount__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string name;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate int _GetSequenceFrameCount(IntPtr _this, GetSequenceFrameCount__Args args);
            private static _GetSequenceFrameCount _GetSequenceFrameCountFunc;
            internal static _GetSequenceFrameCount GetSequenceFrameCount() {
                if (_GetSequenceFrameCountFunc == null) {
                    _GetSequenceFrameCountFunc =
                        (_GetSequenceFrameCount)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnTSShapeConstructor_getSequenceFrameCount"), typeof(_GetSequenceFrameCount));
                }
                
                return _GetSequenceFrameCountFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct GetSequenceSource__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string name;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            
            internal delegate IntPtr _GetSequenceSource(IntPtr _this, GetSequenceSource__Args args);
            private static _GetSequenceSource _GetSequenceSourceFunc;
            internal static _GetSequenceSource GetSequenceSource() {
                if (_GetSequenceSourceFunc == null) {
                    _GetSequenceSourceFunc =
                        (_GetSequenceSource)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnTSShapeConstructor_getSequenceSource"), typeof(_GetSequenceSource));
                }
                
                return _GetSequenceSourceFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct GetSequenceName__Args
            {
                internal int index;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            
            internal delegate IntPtr _GetSequenceName(IntPtr _this, GetSequenceName__Args args);
            private static _GetSequenceName _GetSequenceNameFunc;
            internal static _GetSequenceName GetSequenceName() {
                if (_GetSequenceNameFunc == null) {
                    _GetSequenceNameFunc =
                        (_GetSequenceName)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnTSShapeConstructor_getSequenceName"), typeof(_GetSequenceName));
                }
                
                return _GetSequenceNameFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct GetSequenceIndex__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string name;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate int _GetSequenceIndex(IntPtr _this, GetSequenceIndex__Args args);
            private static _GetSequenceIndex _GetSequenceIndexFunc;
            internal static _GetSequenceIndex GetSequenceIndex() {
                if (_GetSequenceIndexFunc == null) {
                    _GetSequenceIndexFunc =
                        (_GetSequenceIndex)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnTSShapeConstructor_getSequenceIndex"), typeof(_GetSequenceIndex));
                }
                
                return _GetSequenceIndexFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct GetSequenceCount__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate int _GetSequenceCount(IntPtr _this, GetSequenceCount__Args args);
            private static _GetSequenceCount _GetSequenceCountFunc;
            internal static _GetSequenceCount GetSequenceCount() {
                if (_GetSequenceCountFunc == null) {
                    _GetSequenceCountFunc =
                        (_GetSequenceCount)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnTSShapeConstructor_getSequenceCount"), typeof(_GetSequenceCount));
                }
                
                return _GetSequenceCountFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct RemoveImposter__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            [return: MarshalAs(UnmanagedType.I1)]
            internal delegate bool _RemoveImposter(IntPtr _this, RemoveImposter__Args args);
            private static _RemoveImposter _RemoveImposterFunc;
            internal static _RemoveImposter RemoveImposter() {
                if (_RemoveImposterFunc == null) {
                    _RemoveImposterFunc =
                        (_RemoveImposter)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnTSShapeConstructor_removeImposter"), typeof(_RemoveImposter));
                }
                
                return _RemoveImposterFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct AddImposter__Args
            {
                internal int size;
                internal int equatorSteps;
                internal int polarSteps;
                internal int dl;
                internal int dim;
                [MarshalAs(UnmanagedType.I1)]
                internal bool includePoles;
                internal float polarAngle;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate int _AddImposter(IntPtr _this, AddImposter__Args args);
            private static _AddImposter _AddImposterFunc;
            internal static _AddImposter AddImposter() {
                if (_AddImposterFunc == null) {
                    _AddImposterFunc =
                        (_AddImposter)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnTSShapeConstructor_addImposter"), typeof(_AddImposter));
                }
                
                return _AddImposterFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct GetImposterSettings__Args
            {
                internal int index;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            
            internal delegate IntPtr _GetImposterSettings(IntPtr _this, GetImposterSettings__Args args);
            private static _GetImposterSettings _GetImposterSettingsFunc;
            internal static _GetImposterSettings GetImposterSettings() {
                if (_GetImposterSettingsFunc == null) {
                    _GetImposterSettingsFunc =
                        (_GetImposterSettings)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnTSShapeConstructor_getImposterSettings"), typeof(_GetImposterSettings));
                }
                
                return _GetImposterSettingsFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct GetImposterDetailLevel__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate int _GetImposterDetailLevel(IntPtr _this, GetImposterDetailLevel__Args args);
            private static _GetImposterDetailLevel _GetImposterDetailLevelFunc;
            internal static _GetImposterDetailLevel GetImposterDetailLevel() {
                if (_GetImposterDetailLevelFunc == null) {
                    _GetImposterDetailLevelFunc =
                        (_GetImposterDetailLevel)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnTSShapeConstructor_getImposterDetailLevel"), typeof(_GetImposterDetailLevel));
                }
                
                return _GetImposterDetailLevelFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct SetDetailLevelSize__Args
            {
                internal int index;
                internal int newSize;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate int _SetDetailLevelSize(IntPtr _this, SetDetailLevelSize__Args args);
            private static _SetDetailLevelSize _SetDetailLevelSizeFunc;
            internal static _SetDetailLevelSize SetDetailLevelSize() {
                if (_SetDetailLevelSizeFunc == null) {
                    _SetDetailLevelSizeFunc =
                        (_SetDetailLevelSize)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnTSShapeConstructor_setDetailLevelSize"), typeof(_SetDetailLevelSize));
                }
                
                return _SetDetailLevelSizeFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct RemoveDetailLevel__Args
            {
                internal int index;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            [return: MarshalAs(UnmanagedType.I1)]
            internal delegate bool _RemoveDetailLevel(IntPtr _this, RemoveDetailLevel__Args args);
            private static _RemoveDetailLevel _RemoveDetailLevelFunc;
            internal static _RemoveDetailLevel RemoveDetailLevel() {
                if (_RemoveDetailLevelFunc == null) {
                    _RemoveDetailLevelFunc =
                        (_RemoveDetailLevel)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnTSShapeConstructor_removeDetailLevel"), typeof(_RemoveDetailLevel));
                }
                
                return _RemoveDetailLevelFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct RenameDetailLevel__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string oldName;
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string newName;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            [return: MarshalAs(UnmanagedType.I1)]
            internal delegate bool _RenameDetailLevel(IntPtr _this, RenameDetailLevel__Args args);
            private static _RenameDetailLevel _RenameDetailLevelFunc;
            internal static _RenameDetailLevel RenameDetailLevel() {
                if (_RenameDetailLevelFunc == null) {
                    _RenameDetailLevelFunc =
                        (_RenameDetailLevel)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnTSShapeConstructor_renameDetailLevel"), typeof(_RenameDetailLevel));
                }
                
                return _RenameDetailLevelFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct GetDetailLevelIndex__Args
            {
                internal int size;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate int _GetDetailLevelIndex(IntPtr _this, GetDetailLevelIndex__Args args);
            private static _GetDetailLevelIndex _GetDetailLevelIndexFunc;
            internal static _GetDetailLevelIndex GetDetailLevelIndex() {
                if (_GetDetailLevelIndexFunc == null) {
                    _GetDetailLevelIndexFunc =
                        (_GetDetailLevelIndex)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnTSShapeConstructor_getDetailLevelIndex"), typeof(_GetDetailLevelIndex));
                }
                
                return _GetDetailLevelIndexFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct GetDetailLevelSize__Args
            {
                internal int index;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate int _GetDetailLevelSize(IntPtr _this, GetDetailLevelSize__Args args);
            private static _GetDetailLevelSize _GetDetailLevelSizeFunc;
            internal static _GetDetailLevelSize GetDetailLevelSize() {
                if (_GetDetailLevelSizeFunc == null) {
                    _GetDetailLevelSizeFunc =
                        (_GetDetailLevelSize)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnTSShapeConstructor_getDetailLevelSize"), typeof(_GetDetailLevelSize));
                }
                
                return _GetDetailLevelSizeFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct GetDetailLevelName__Args
            {
                internal int index;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            
            internal delegate IntPtr _GetDetailLevelName(IntPtr _this, GetDetailLevelName__Args args);
            private static _GetDetailLevelName _GetDetailLevelNameFunc;
            internal static _GetDetailLevelName GetDetailLevelName() {
                if (_GetDetailLevelNameFunc == null) {
                    _GetDetailLevelNameFunc =
                        (_GetDetailLevelName)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnTSShapeConstructor_getDetailLevelName"), typeof(_GetDetailLevelName));
                }
                
                return _GetDetailLevelNameFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct GetDetailLevelCount__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate int _GetDetailLevelCount(IntPtr _this, GetDetailLevelCount__Args args);
            private static _GetDetailLevelCount _GetDetailLevelCountFunc;
            internal static _GetDetailLevelCount GetDetailLevelCount() {
                if (_GetDetailLevelCountFunc == null) {
                    _GetDetailLevelCountFunc =
                        (_GetDetailLevelCount)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnTSShapeConstructor_getDetailLevelCount"), typeof(_GetDetailLevelCount));
                }
                
                return _GetDetailLevelCountFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct SetBounds__Args
            {
                internal IntPtr bbox;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            [return: MarshalAs(UnmanagedType.I1)]
            internal delegate bool _SetBounds(IntPtr _this, SetBounds__Args args);
            private static _SetBounds _SetBoundsFunc;
            internal static _SetBounds SetBounds() {
                if (_SetBoundsFunc == null) {
                    _SetBoundsFunc =
                        (_SetBounds)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnTSShapeConstructor_setBounds"), typeof(_SetBounds));
                }
                
                return _SetBoundsFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct GetBounds__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate Box3F.InternalStruct _GetBounds(IntPtr _this, GetBounds__Args args);
            private static _GetBounds _GetBoundsFunc;
            internal static _GetBounds GetBounds() {
                if (_GetBoundsFunc == null) {
                    _GetBoundsFunc =
                        (_GetBounds)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnTSShapeConstructor_getBounds"), typeof(_GetBounds));
                }
                
                return _GetBoundsFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct RemoveMesh__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string name;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            [return: MarshalAs(UnmanagedType.I1)]
            internal delegate bool _RemoveMesh(IntPtr _this, RemoveMesh__Args args);
            private static _RemoveMesh _RemoveMeshFunc;
            internal static _RemoveMesh RemoveMesh() {
                if (_RemoveMeshFunc == null) {
                    _RemoveMeshFunc =
                        (_RemoveMesh)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnTSShapeConstructor_removeMesh"), typeof(_RemoveMesh));
                }
                
                return _RemoveMeshFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct AddMesh__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string meshName;
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string srcShape;
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string srcMesh;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            [return: MarshalAs(UnmanagedType.I1)]
            internal delegate bool _AddMesh(IntPtr _this, AddMesh__Args args);
            private static _AddMesh _AddMeshFunc;
            internal static _AddMesh AddMesh() {
                if (_AddMeshFunc == null) {
                    _AddMeshFunc =
                        (_AddMesh)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnTSShapeConstructor_addMesh"), typeof(_AddMesh));
                }
                
                return _AddMeshFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct SetMeshMaterial__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string meshName;
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string matName;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            [return: MarshalAs(UnmanagedType.I1)]
            internal delegate bool _SetMeshMaterial(IntPtr _this, SetMeshMaterial__Args args);
            private static _SetMeshMaterial _SetMeshMaterialFunc;
            internal static _SetMeshMaterial SetMeshMaterial() {
                if (_SetMeshMaterialFunc == null) {
                    _SetMeshMaterialFunc =
                        (_SetMeshMaterial)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnTSShapeConstructor_setMeshMaterial"), typeof(_SetMeshMaterial));
                }
                
                return _SetMeshMaterialFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct GetMeshMaterial__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string name;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            
            internal delegate IntPtr _GetMeshMaterial(IntPtr _this, GetMeshMaterial__Args args);
            private static _GetMeshMaterial _GetMeshMaterialFunc;
            internal static _GetMeshMaterial GetMeshMaterial() {
                if (_GetMeshMaterialFunc == null) {
                    _GetMeshMaterialFunc =
                        (_GetMeshMaterial)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnTSShapeConstructor_getMeshMaterial"), typeof(_GetMeshMaterial));
                }
                
                return _GetMeshMaterialFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct SetMeshType__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string name;
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string type;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            [return: MarshalAs(UnmanagedType.I1)]
            internal delegate bool _SetMeshType(IntPtr _this, SetMeshType__Args args);
            private static _SetMeshType _SetMeshTypeFunc;
            internal static _SetMeshType SetMeshType() {
                if (_SetMeshTypeFunc == null) {
                    _SetMeshTypeFunc =
                        (_SetMeshType)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnTSShapeConstructor_setMeshType"), typeof(_SetMeshType));
                }
                
                return _SetMeshTypeFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct GetMeshType__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string name;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            
            internal delegate IntPtr _GetMeshType(IntPtr _this, GetMeshType__Args args);
            private static _GetMeshType _GetMeshTypeFunc;
            internal static _GetMeshType GetMeshType() {
                if (_GetMeshTypeFunc == null) {
                    _GetMeshTypeFunc =
                        (_GetMeshType)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnTSShapeConstructor_getMeshType"), typeof(_GetMeshType));
                }
                
                return _GetMeshTypeFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct SetMeshSize__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string name;
                internal int size;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            [return: MarshalAs(UnmanagedType.I1)]
            internal delegate bool _SetMeshSize(IntPtr _this, SetMeshSize__Args args);
            private static _SetMeshSize _SetMeshSizeFunc;
            internal static _SetMeshSize SetMeshSize() {
                if (_SetMeshSizeFunc == null) {
                    _SetMeshSizeFunc =
                        (_SetMeshSize)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnTSShapeConstructor_setMeshSize"), typeof(_SetMeshSize));
                }
                
                return _SetMeshSizeFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct GetMeshSize__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string name;
                internal int index;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate int _GetMeshSize(IntPtr _this, GetMeshSize__Args args);
            private static _GetMeshSize _GetMeshSizeFunc;
            internal static _GetMeshSize GetMeshSize() {
                if (_GetMeshSizeFunc == null) {
                    _GetMeshSizeFunc =
                        (_GetMeshSize)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnTSShapeConstructor_getMeshSize"), typeof(_GetMeshSize));
                }
                
                return _GetMeshSizeFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct GetMeshName__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string name;
                internal int index;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            
            internal delegate IntPtr _GetMeshName(IntPtr _this, GetMeshName__Args args);
            private static _GetMeshName _GetMeshNameFunc;
            internal static _GetMeshName GetMeshName() {
                if (_GetMeshNameFunc == null) {
                    _GetMeshNameFunc =
                        (_GetMeshName)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnTSShapeConstructor_getMeshName"), typeof(_GetMeshName));
                }
                
                return _GetMeshNameFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct GetMeshCount__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string name;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate int _GetMeshCount(IntPtr _this, GetMeshCount__Args args);
            private static _GetMeshCount _GetMeshCountFunc;
            internal static _GetMeshCount GetMeshCount() {
                if (_GetMeshCountFunc == null) {
                    _GetMeshCountFunc =
                        (_GetMeshCount)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnTSShapeConstructor_getMeshCount"), typeof(_GetMeshCount));
                }
                
                return _GetMeshCountFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct RemoveObject__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string name;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            [return: MarshalAs(UnmanagedType.I1)]
            internal delegate bool _RemoveObject(IntPtr _this, RemoveObject__Args args);
            private static _RemoveObject _RemoveObjectFunc;
            internal static _RemoveObject RemoveObject() {
                if (_RemoveObjectFunc == null) {
                    _RemoveObjectFunc =
                        (_RemoveObject)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnTSShapeConstructor_removeObject"), typeof(_RemoveObject));
                }
                
                return _RemoveObjectFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct RenameObject__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string oldName;
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string newName;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            [return: MarshalAs(UnmanagedType.I1)]
            internal delegate bool _RenameObject(IntPtr _this, RenameObject__Args args);
            private static _RenameObject _RenameObjectFunc;
            internal static _RenameObject RenameObject() {
                if (_RenameObjectFunc == null) {
                    _RenameObjectFunc =
                        (_RenameObject)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnTSShapeConstructor_renameObject"), typeof(_RenameObject));
                }
                
                return _RenameObjectFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct SetObjectNode__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string objName;
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string nodeName;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            [return: MarshalAs(UnmanagedType.I1)]
            internal delegate bool _SetObjectNode(IntPtr _this, SetObjectNode__Args args);
            private static _SetObjectNode _SetObjectNodeFunc;
            internal static _SetObjectNode SetObjectNode() {
                if (_SetObjectNodeFunc == null) {
                    _SetObjectNodeFunc =
                        (_SetObjectNode)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnTSShapeConstructor_setObjectNode"), typeof(_SetObjectNode));
                }
                
                return _SetObjectNodeFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct GetObjectNode__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string name;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            
            internal delegate IntPtr _GetObjectNode(IntPtr _this, GetObjectNode__Args args);
            private static _GetObjectNode _GetObjectNodeFunc;
            internal static _GetObjectNode GetObjectNode() {
                if (_GetObjectNodeFunc == null) {
                    _GetObjectNodeFunc =
                        (_GetObjectNode)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnTSShapeConstructor_getObjectNode"), typeof(_GetObjectNode));
                }
                
                return _GetObjectNodeFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct GetObjectIndex__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string name;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate int _GetObjectIndex(IntPtr _this, GetObjectIndex__Args args);
            private static _GetObjectIndex _GetObjectIndexFunc;
            internal static _GetObjectIndex GetObjectIndex() {
                if (_GetObjectIndexFunc == null) {
                    _GetObjectIndexFunc =
                        (_GetObjectIndex)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnTSShapeConstructor_getObjectIndex"), typeof(_GetObjectIndex));
                }
                
                return _GetObjectIndexFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct GetObjectName__Args
            {
                internal int index;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            
            internal delegate IntPtr _GetObjectName(IntPtr _this, GetObjectName__Args args);
            private static _GetObjectName _GetObjectNameFunc;
            internal static _GetObjectName GetObjectName() {
                if (_GetObjectNameFunc == null) {
                    _GetObjectNameFunc =
                        (_GetObjectName)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnTSShapeConstructor_getObjectName"), typeof(_GetObjectName));
                }
                
                return _GetObjectNameFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct GetObjectCount__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate int _GetObjectCount(IntPtr _this, GetObjectCount__Args args);
            private static _GetObjectCount _GetObjectCountFunc;
            internal static _GetObjectCount GetObjectCount() {
                if (_GetObjectCountFunc == null) {
                    _GetObjectCountFunc =
                        (_GetObjectCount)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnTSShapeConstructor_getObjectCount"), typeof(_GetObjectCount));
                }
                
                return _GetObjectCountFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct GetTargetName__Args
            {
                internal int index;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            
            internal delegate IntPtr _GetTargetName(IntPtr _this, GetTargetName__Args args);
            private static _GetTargetName _GetTargetNameFunc;
            internal static _GetTargetName GetTargetName() {
                if (_GetTargetNameFunc == null) {
                    _GetTargetNameFunc =
                        (_GetTargetName)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnTSShapeConstructor_getTargetName"), typeof(_GetTargetName));
                }
                
                return _GetTargetNameFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct GetTargetCount__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate int _GetTargetCount(IntPtr _this, GetTargetCount__Args args);
            private static _GetTargetCount _GetTargetCountFunc;
            internal static _GetTargetCount GetTargetCount() {
                if (_GetTargetCountFunc == null) {
                    _GetTargetCountFunc =
                        (_GetTargetCount)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnTSShapeConstructor_getTargetCount"), typeof(_GetTargetCount));
                }
                
                return _GetTargetCountFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct RemoveNode__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string name;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            [return: MarshalAs(UnmanagedType.I1)]
            internal delegate bool _RemoveNode(IntPtr _this, RemoveNode__Args args);
            private static _RemoveNode _RemoveNodeFunc;
            internal static _RemoveNode RemoveNode() {
                if (_RemoveNodeFunc == null) {
                    _RemoveNodeFunc =
                        (_RemoveNode)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnTSShapeConstructor_removeNode"), typeof(_RemoveNode));
                }
                
                return _RemoveNodeFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct AddNode__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string name;
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string parentName;
                internal IntPtr txfm;
                [MarshalAs(UnmanagedType.I1)]
                internal bool isWorld;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            [return: MarshalAs(UnmanagedType.I1)]
            internal delegate bool _AddNode(IntPtr _this, AddNode__Args args);
            private static _AddNode _AddNodeFunc;
            internal static _AddNode AddNode() {
                if (_AddNodeFunc == null) {
                    _AddNodeFunc =
                        (_AddNode)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnTSShapeConstructor_addNode"), typeof(_AddNode));
                }
                
                return _AddNodeFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct RenameNode__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string oldName;
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string newName;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            [return: MarshalAs(UnmanagedType.I1)]
            internal delegate bool _RenameNode(IntPtr _this, RenameNode__Args args);
            private static _RenameNode _RenameNodeFunc;
            internal static _RenameNode RenameNode() {
                if (_RenameNodeFunc == null) {
                    _RenameNodeFunc =
                        (_RenameNode)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnTSShapeConstructor_renameNode"), typeof(_RenameNode));
                }
                
                return _RenameNodeFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct SetNodeTransform__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string name;
                internal IntPtr txfm;
                [MarshalAs(UnmanagedType.I1)]
                internal bool isWorld;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            [return: MarshalAs(UnmanagedType.I1)]
            internal delegate bool _SetNodeTransform(IntPtr _this, SetNodeTransform__Args args);
            private static _SetNodeTransform _SetNodeTransformFunc;
            internal static _SetNodeTransform SetNodeTransform() {
                if (_SetNodeTransformFunc == null) {
                    _SetNodeTransformFunc =
                        (_SetNodeTransform)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnTSShapeConstructor_setNodeTransform"), typeof(_SetNodeTransform));
                }
                
                return _SetNodeTransformFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct GetNodeTransform__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string name;
                [MarshalAs(UnmanagedType.I1)]
                internal bool isWorld;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate TransformF.InternalStruct _GetNodeTransform(IntPtr _this, GetNodeTransform__Args args);
            private static _GetNodeTransform _GetNodeTransformFunc;
            internal static _GetNodeTransform GetNodeTransform() {
                if (_GetNodeTransformFunc == null) {
                    _GetNodeTransformFunc =
                        (_GetNodeTransform)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnTSShapeConstructor_getNodeTransform"), typeof(_GetNodeTransform));
                }
                
                return _GetNodeTransformFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct GetNodeObjectName__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string name;
                internal int index;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            
            internal delegate IntPtr _GetNodeObjectName(IntPtr _this, GetNodeObjectName__Args args);
            private static _GetNodeObjectName _GetNodeObjectNameFunc;
            internal static _GetNodeObjectName GetNodeObjectName() {
                if (_GetNodeObjectNameFunc == null) {
                    _GetNodeObjectNameFunc =
                        (_GetNodeObjectName)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnTSShapeConstructor_getNodeObjectName"), typeof(_GetNodeObjectName));
                }
                
                return _GetNodeObjectNameFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct GetNodeObjectCount__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string name;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate int _GetNodeObjectCount(IntPtr _this, GetNodeObjectCount__Args args);
            private static _GetNodeObjectCount _GetNodeObjectCountFunc;
            internal static _GetNodeObjectCount GetNodeObjectCount() {
                if (_GetNodeObjectCountFunc == null) {
                    _GetNodeObjectCountFunc =
                        (_GetNodeObjectCount)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnTSShapeConstructor_getNodeObjectCount"), typeof(_GetNodeObjectCount));
                }
                
                return _GetNodeObjectCountFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct GetNodeChildName__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string name;
                internal int index;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            
            internal delegate IntPtr _GetNodeChildName(IntPtr _this, GetNodeChildName__Args args);
            private static _GetNodeChildName _GetNodeChildNameFunc;
            internal static _GetNodeChildName GetNodeChildName() {
                if (_GetNodeChildNameFunc == null) {
                    _GetNodeChildNameFunc =
                        (_GetNodeChildName)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnTSShapeConstructor_getNodeChildName"), typeof(_GetNodeChildName));
                }
                
                return _GetNodeChildNameFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct GetNodeChildCount__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string name;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate int _GetNodeChildCount(IntPtr _this, GetNodeChildCount__Args args);
            private static _GetNodeChildCount _GetNodeChildCountFunc;
            internal static _GetNodeChildCount GetNodeChildCount() {
                if (_GetNodeChildCountFunc == null) {
                    _GetNodeChildCountFunc =
                        (_GetNodeChildCount)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnTSShapeConstructor_getNodeChildCount"), typeof(_GetNodeChildCount));
                }
                
                return _GetNodeChildCountFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct SetNodeParent__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string name;
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string parentName;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            [return: MarshalAs(UnmanagedType.I1)]
            internal delegate bool _SetNodeParent(IntPtr _this, SetNodeParent__Args args);
            private static _SetNodeParent _SetNodeParentFunc;
            internal static _SetNodeParent SetNodeParent() {
                if (_SetNodeParentFunc == null) {
                    _SetNodeParentFunc =
                        (_SetNodeParent)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnTSShapeConstructor_setNodeParent"), typeof(_SetNodeParent));
                }
                
                return _SetNodeParentFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct GetNodeParentName__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string name;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            
            internal delegate IntPtr _GetNodeParentName(IntPtr _this, GetNodeParentName__Args args);
            private static _GetNodeParentName _GetNodeParentNameFunc;
            internal static _GetNodeParentName GetNodeParentName() {
                if (_GetNodeParentNameFunc == null) {
                    _GetNodeParentNameFunc =
                        (_GetNodeParentName)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnTSShapeConstructor_getNodeParentName"), typeof(_GetNodeParentName));
                }
                
                return _GetNodeParentNameFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct GetNodeName__Args
            {
                internal int index;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            
            internal delegate IntPtr _GetNodeName(IntPtr _this, GetNodeName__Args args);
            private static _GetNodeName _GetNodeNameFunc;
            internal static _GetNodeName GetNodeName() {
                if (_GetNodeNameFunc == null) {
                    _GetNodeNameFunc =
                        (_GetNodeName)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnTSShapeConstructor_getNodeName"), typeof(_GetNodeName));
                }
                
                return _GetNodeNameFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct GetNodeIndex__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string name;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate int _GetNodeIndex(IntPtr _this, GetNodeIndex__Args args);
            private static _GetNodeIndex _GetNodeIndexFunc;
            internal static _GetNodeIndex GetNodeIndex() {
                if (_GetNodeIndexFunc == null) {
                    _GetNodeIndexFunc =
                        (_GetNodeIndex)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnTSShapeConstructor_getNodeIndex"), typeof(_GetNodeIndex));
                }
                
                return _GetNodeIndexFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct GetNodeCount__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate int _GetNodeCount(IntPtr _this, GetNodeCount__Args args);
            private static _GetNodeCount _GetNodeCountFunc;
            internal static _GetNodeCount GetNodeCount() {
                if (_GetNodeCountFunc == null) {
                    _GetNodeCountFunc =
                        (_GetNodeCount)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnTSShapeConstructor_getNodeCount"), typeof(_GetNodeCount));
                }
                
                return _GetNodeCountFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct NotifyShapeChanged__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _NotifyShapeChanged(IntPtr _this, NotifyShapeChanged__Args args);
            private static _NotifyShapeChanged _NotifyShapeChangedFunc;
            internal static _NotifyShapeChanged NotifyShapeChanged() {
                if (_NotifyShapeChangedFunc == null) {
                    _NotifyShapeChangedFunc =
                        (_NotifyShapeChanged)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnTSShapeConstructor_notifyShapeChanged"), typeof(_NotifyShapeChanged));
                }
                
                return _NotifyShapeChangedFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct WriteChangeSet__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _WriteChangeSet(IntPtr _this, WriteChangeSet__Args args);
            private static _WriteChangeSet _WriteChangeSetFunc;
            internal static _WriteChangeSet WriteChangeSet() {
                if (_WriteChangeSetFunc == null) {
                    _WriteChangeSetFunc =
                        (_WriteChangeSet)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnTSShapeConstructor_writeChangeSet"), typeof(_WriteChangeSet));
                }
                
                return _WriteChangeSetFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct SaveShape__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string filename;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _SaveShape(IntPtr _this, SaveShape__Args args);
            private static _SaveShape _SaveShapeFunc;
            internal static _SaveShape SaveShape() {
                if (_SaveShapeFunc == null) {
                    _SaveShapeFunc =
                        (_SaveShape)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnTSShapeConstructor_saveShape"), typeof(_SaveShape));
                }
                
                return _SaveShapeFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct DumpShape__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string filename;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _DumpShape(IntPtr _this, DumpShape__Args args);
            private static _DumpShape _DumpShapeFunc;
            internal static _DumpShape DumpShape() {
                if (_DumpShapeFunc == null) {
                    _DumpShapeFunc =
                        (_DumpShape)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnTSShapeConstructor_dumpShape"), typeof(_DumpShape));
                }
                
                return _DumpShapeFunc;
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
                                "fnTSShapeConstructor_staticGetType"), typeof(_StaticGetType));
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
                                "fnTSShapeConstructor_create"), typeof(_Create));
                }
                
                return _CreateFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct OnUnload__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _OnUnload(IntPtr _this, OnUnload__Args args);
            private static _OnUnload _OnUnloadFunc;
            internal static _OnUnload OnUnload() {
                if (_OnUnloadFunc == null) {
                    _OnUnloadFunc =
                        (_OnUnload)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "cbTSShapeConstructor_onUnload"), typeof(_OnUnload));
                }
                
                return _OnUnloadFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct OnLoad__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _OnLoad(IntPtr _this, OnLoad__Args args);
            private static _OnLoad _OnLoadFunc;
            internal static _OnLoad OnLoad() {
                if (_OnLoadFunc == null) {
                    _OnLoadFunc =
                        (_OnLoad)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "cbTSShapeConstructor_onLoad"), typeof(_OnLoad));
                }
                
                return _OnLoadFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct AddCollisionDetail__Args
            {
                internal int size;
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string type;
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string target;
                internal int depth;
                internal float merge;
                internal float concavity;
                internal int maxVerts;
                internal float boxMaxError;
                internal float sphereMaxError;
                internal float capsuleMaxError;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            [return: MarshalAs(UnmanagedType.I1)]
            internal delegate bool _AddCollisionDetail(IntPtr _this, AddCollisionDetail__Args args);
            private static _AddCollisionDetail _AddCollisionDetailFunc;
            internal static _AddCollisionDetail AddCollisionDetail() {
                if (_AddCollisionDetailFunc == null) {
                    _AddCollisionDetailFunc =
                        (_AddCollisionDetail)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnTSShapeConstructor_addCollisionDetail"), typeof(_AddCollisionDetail));
                }
                
                return _AddCollisionDetailFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct AddPrimitive__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string meshName;
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string type;
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string _params;
                internal IntPtr txfm;
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string nodeName;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            [return: MarshalAs(UnmanagedType.I1)]
            internal delegate bool _AddPrimitive(IntPtr _this, AddPrimitive__Args args);
            private static _AddPrimitive _AddPrimitiveFunc;
            internal static _AddPrimitive AddPrimitive() {
                if (_AddPrimitiveFunc == null) {
                    _AddPrimitiveFunc =
                        (_AddPrimitive)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnTSShapeConstructor_addPrimitive"), typeof(_AddPrimitive));
                }
                
                return _AddPrimitiveFunc;
            }
        }
        #endregion

        /// <description>
        /// Remove a trigger from the sequence.
        /// </description>
        /// <param name="name">name of the sequence to modify</param>
        /// <param name="keyframe">keyframe of the trigger to remove</param>
        /// <param name="state">of the trigger to remove</param>
        /// <returns>true if successful, false otherwise</returns>
        /// <code>
        /// %this.removeTrigger( "walk", 3, 1 );
        /// </code>
        public bool RemoveTrigger(string name, int keyframe, int state) {
             InternalUnsafeMethods.RemoveTrigger__Args _args = new InternalUnsafeMethods.RemoveTrigger__Args() {
                name = name,
                keyframe = keyframe,
                state = state,
             };
             bool _engineResult = InternalUnsafeMethods.RemoveTrigger()(ObjectPtr, _args);
             return _engineResult;
        }

        /// <description>
        /// Add a new trigger to the sequence.
        /// </description>
        /// <param name="name">name of the sequence to modify</param>
        /// <param name="keyframe">keyframe of the new trigger</param>
        /// <param name="state">of the new trigger</param>
        /// <returns>true if successful, false otherwise</returns>
        /// <code>
        /// %this.addTrigger( "walk", 3, 1 );
        /// %this.addTrigger( "walk", 5, -1 );
        /// </code>
        public bool AddTrigger(string name, int keyframe, int state) {
             InternalUnsafeMethods.AddTrigger__Args _args = new InternalUnsafeMethods.AddTrigger__Args() {
                name = name,
                keyframe = keyframe,
                state = state,
             };
             bool _engineResult = InternalUnsafeMethods.AddTrigger()(ObjectPtr, _args);
             return _engineResult;
        }

        /// <description>
        /// Get information about the indexed trigger
        /// </description>
        /// <param name="name">name of the sequence to query</param>
        /// <param name="index">index of the trigger (valid range is 0 - getTriggerCount()-1)</param>
        /// <returns>string of the form "frame state"</returns>
        /// <code>
        /// // print all triggers in the sequence
        /// %count = %this.getTriggerCount( "back" );
        /// for ( %i = 0; %i < %count; %i++ )
        ///    echo( %i SPC %this.getTrigger( "back", %i ) );
        /// </code>
        public string GetTrigger(string name, int index) {
             InternalUnsafeMethods.GetTrigger__Args _args = new InternalUnsafeMethods.GetTrigger__Args() {
                name = name,
                index = index,
             };
             IntPtr _engineResult = InternalUnsafeMethods.GetTrigger()(ObjectPtr, _args);
             return StringMarshal.IntPtrToUtf8String(_engineResult);
        }

        /// <description>
        /// Get the number of triggers in the specified sequence.
        /// </description>
        /// <param name="name">name of the sequence to query</param>
        /// <returns>number of triggers in the sequence</returns>
        public int GetTriggerCount(string name) {
             InternalUnsafeMethods.GetTriggerCount__Args _args = new InternalUnsafeMethods.GetTriggerCount__Args() {
                name = name,
             };
             int _engineResult = InternalUnsafeMethods.GetTriggerCount()(ObjectPtr, _args);
             return _engineResult;
        }

        /// <description>
        /// Remove the sequence from the shape.
        /// </description>
        /// <param name="name">name of the sequence to remove</param>
        /// <returns>true if successful, false otherwise</returns>
        public bool RemoveSequence(string name) {
             InternalUnsafeMethods.RemoveSequence__Args _args = new InternalUnsafeMethods.RemoveSequence__Args() {
                name = name,
             };
             bool _engineResult = InternalUnsafeMethods.RemoveSequence()(ObjectPtr, _args);
             return _engineResult;
        }

        /// <description>
        /// Add a new sequence to the shape.
        /// </description>
        /// <param name="source">the name of an existing sequence, or the name of a DTS or DAE shape or DSQ sequence file. When the shape file contains more than one sequence, the desired sequence can be specified by appending the name to the end of the shape file. eg. "myShape.dts run" would select the "run" sequence from the "myShape.dts" file.</param>
        /// <param name="name">name of the new sequence</param>
        /// <param name="start">(optional) first frame to copy. Defaults to 0, the first frame in the sequence.</param>
        /// <param name="end">(optional) last frame to copy. Defaults to -1, the last frame in the sequence.</param>
        /// <param name="padRot">(optional) copy root-pose rotation keys for non-animated nodes. This is useful if the source sequence data has a different root-pose to the target shape, such as if one character was in the T pose, and the other had arms at the side. Normally only nodes that are actually rotated by the source sequence have keyframes added, but setting this flag will also add keyframes for nodes that are not animated, but have a different root-pose rotation to the target shape root pose.</param>
        /// <param name="padTrans">(optional) copy root-pose translation keys for non-animated nodes.  This is useful if the source sequence data has a different root-pose to the target shape, such as if one character was in the T pose, and the other had arms at the side. Normally only nodes that are actually moved by the source sequence have keyframes added, but setting this flag will also add keyframes for nodes that are not animated, but have a different root-pose position to the target shape root pose.</param>
        /// <returns>true if successful, false otherwise</returns>
        /// <code>
        /// %this.addSequence( "./testShape.dts ambient", "ambient" );
        /// %this.addSequence( "./myPlayer.dae run", "run" );
        /// %this.addSequence( "./player_look.dsq", "look", 0, -1 );     // start to end
        /// %this.addSequence( "walk", "walk_shortA", 0, 4 );            // start to frame 4
        /// %this.addSequence( "walk", "walk_shortB", 4, -1 );           // frame 4 to end
        /// </code>
        public bool AddSequence(string source, string name, int start = 0, int end = -1, bool padRot = true, bool padTrans = false) {
             InternalUnsafeMethods.AddSequence__Args _args = new InternalUnsafeMethods.AddSequence__Args() {
                source = source,
                name = name,
                start = start,
                end = end,
                padRot = padRot,
                padTrans = padTrans,
             };
             bool _engineResult = InternalUnsafeMethods.AddSequence()(ObjectPtr, _args);
             return _engineResult;
        }

        /// <description>
        /// Rename a sequence.
        /// </description>
        /// <remarks> Note that sequence names must be unique, so this command will fail if there is already a sequence with the desired name
        /// </remarks>
        /// <param name="oldName">current name of the sequence</param>
        /// <param name="newName">new name of the sequence</param>
        /// <returns>true if successful, false otherwise</returns>
        /// <code>
        /// %this.renameSequence( "walking", "walk" );
        /// </code>
        public bool RenameSequence(string oldName, string newName) {
             InternalUnsafeMethods.RenameSequence__Args _args = new InternalUnsafeMethods.RenameSequence__Args() {
                oldName = oldName,
                newName = newName,
             };
             bool _engineResult = InternalUnsafeMethods.RenameSequence()(ObjectPtr, _args);
             return _engineResult;
        }

        /// <description>
        /// Mark a sequence as a blend or non-blend.
        /// A blend sequence is one that will be added on top of any other playing sequences. This is done by storing the animated node transforms relative to a reference frame, rather than as absolute transforms.
        /// </description>
        /// <param name="name">name of the sequence to modify</param>
        /// <param name="blend">true to make the sequence a blend, false for a non-blend</param>
        /// <param name="blendSeq">the name of the sequence that contains the blend reference frame</param>
        /// <param name="blendFrame">the reference frame in the blendSeq sequence</param>
        /// <returns>true if successful, false otherwise</returns>
        /// <code>
        /// %this.setSequenceBlend( "look", true, "root", 0 );
        /// </code>
        public bool SetSequenceBlend(string name, bool blend, string blendSeq, int blendFrame) {
             InternalUnsafeMethods.SetSequenceBlend__Args _args = new InternalUnsafeMethods.SetSequenceBlend__Args() {
                name = name,
                blend = blend,
                blendSeq = blendSeq,
                blendFrame = blendFrame,
             };
             bool _engineResult = InternalUnsafeMethods.SetSequenceBlend()(ObjectPtr, _args);
             return _engineResult;
        }

        /// <description>
        /// Get information about blended sequences.
        /// </description>
        /// <param name="name">name of the sequence to query</param>
        /// <returns>TAB delimited string of the form: "isBlend blendSeq blendFrame", where:<dl><dt>blend_flag</dt><dd>a boolean flag indicating whether this sequence is a blend</dd><dt>blend_seq_name</dt><dd>the name of the sequence that contains the reference frame (empty for blend sequences embedded in DTS files)</dd><dt>blend_seq_frame</dt><dd>the blend reference frame (empty for blend sequences embedded in DTS files)</dd></dl></returns>
        /// <remarks> Note that only sequences set to be blends using the setSequenceBlend command will contain the blendSeq and blendFrame information.
        /// 
        /// </remarks>
        /// <code>
        /// %blendData = %this.getSequenceBlend( "look" );
        /// if ( getField( %blendData, 0 ) )
        ///    echo( "look is a blend, reference: "@ getField( %blendData, 1 ) );
        /// 
        /// </code>
        public string GetSequenceBlend(string name) {
             InternalUnsafeMethods.GetSequenceBlend__Args _args = new InternalUnsafeMethods.GetSequenceBlend__Args() {
                name = name,
             };
             IntPtr _engineResult = InternalUnsafeMethods.GetSequenceBlend()(ObjectPtr, _args);
             return StringMarshal.IntPtrToUtf8String(_engineResult);
        }

        /// <description>
        /// Mark a sequence as cyclic or non-cyclic.
        /// </description>
        /// <param name="name">name of the sequence to modify</param>
        /// <param name="cyclic">true to make the sequence cyclic, false for non-cyclic</param>
        /// <returns>true if successful, false otherwise</returns>
        /// <code>
        /// %this.setSequenceCyclic( "ambient", true );
        /// %this.setSequenceCyclic( "shoot", false );
        /// </code>
        public bool SetSequenceCyclic(string name, bool cyclic) {
             InternalUnsafeMethods.SetSequenceCyclic__Args _args = new InternalUnsafeMethods.SetSequenceCyclic__Args() {
                name = name,
                cyclic = cyclic,
             };
             bool _engineResult = InternalUnsafeMethods.SetSequenceCyclic()(ObjectPtr, _args);
             return _engineResult;
        }

        /// <description>
        /// Check if this sequence is cyclic (looping).
        /// </description>
        /// <param name="name">name of the sequence to query</param>
        /// <returns>true if this sequence is cyclic, false if not</returns>
        /// <code>
        /// if ( !%this.getSequenceCyclic( "ambient" ) )
        ///    error( "ambient sequence is not cyclic!" );
        /// </code>
        public bool GetSequenceCyclic(string name) {
             InternalUnsafeMethods.GetSequenceCyclic__Args _args = new InternalUnsafeMethods.GetSequenceCyclic__Args() {
                name = name,
             };
             bool _engineResult = InternalUnsafeMethods.GetSequenceCyclic()(ObjectPtr, _args);
             return _engineResult;
        }

        /// <description>
        /// Set the translation and rotation ground speed of the sequence.
        /// The ground speed of the sequence is set by generating ground transform keyframes. The ground translational and rotational speed is assumed to be constant for the duration of the sequence. Existing ground frames for the sequence (if any) will be replaced.
        /// </description>
        /// <param name="name">name of the sequence to modify</param>
        /// <param name="transSpeed">translational speed (trans.x trans.y trans.z) in Torque units per frame</param>
        /// <param name="rotSpeed">(optional) rotational speed (rot.x rot.y rot.z) in radians per frame. Default is "0 0 0"</param>
        /// <returns>true if successful, false otherwise</returns>
        /// <code>
        /// %this.setSequenceGroundSpeed( "run", "5 0 0" );
        /// %this.setSequenceGroundSpeed( "spin", "0 0 0", "4 0 0" );
        /// </code>
        public bool SetSequenceGroundSpeed(string name, Point3F transSpeed, Point3F rotSpeed = null) {
transSpeed.Alloc();rotSpeed = rotSpeed ?? new Point3F("0 0 0");
rotSpeed.Alloc();             InternalUnsafeMethods.SetSequenceGroundSpeed__Args _args = new InternalUnsafeMethods.SetSequenceGroundSpeed__Args() {
                name = name,
                transSpeed = transSpeed.internalStructPtr,
                rotSpeed = rotSpeed.internalStructPtr,
             };
             bool _engineResult = InternalUnsafeMethods.SetSequenceGroundSpeed()(ObjectPtr, _args);
transSpeed.Free();rotSpeed.Free();             return _engineResult;
        }

        /// <description>
        /// Get the ground speed of the sequence.
        /// </description>
        /// <remarks> Note that only the first 2 ground frames of the sequence are examined; the speed is assumed to be constant throughout the sequence.
        /// </remarks>
        /// <param name="name">name of the sequence to query</param>
        /// <returns>string of the form: "trans.x trans.y trans.z rot.x rot.y rot.z"</returns>
        /// <code>
        /// %speed = VectorLen( getWords( %this.getSequenceGroundSpeed( "run" ), 0, 2 ) );
        ///    echo( "Run moves at "@ %speed 
        /// </code>
        public string GetSequenceGroundSpeed(string name) {
             InternalUnsafeMethods.GetSequenceGroundSpeed__Args _args = new InternalUnsafeMethods.GetSequenceGroundSpeed__Args() {
                name = name,
             };
             IntPtr _engineResult = InternalUnsafeMethods.GetSequenceGroundSpeed()(ObjectPtr, _args);
             return StringMarshal.IntPtrToUtf8String(_engineResult);
        }

        /// <description>
        /// Set the sequence priority.
        /// </description>
        /// <param name="name">name of the sequence to modify</param>
        /// <param name="priority">new priority value</param>
        /// <returns>true if successful, false otherwise</returns>
        public bool SetSequencePriority(string name, float priority) {
             InternalUnsafeMethods.SetSequencePriority__Args _args = new InternalUnsafeMethods.SetSequencePriority__Args() {
                name = name,
                priority = priority,
             };
             bool _engineResult = InternalUnsafeMethods.SetSequencePriority()(ObjectPtr, _args);
             return _engineResult;
        }

        /// <description>
        /// Get the priority setting of the sequence.
        /// </description>
        /// <param name="name">name of the sequence to query</param>
        /// <returns>priority value of the sequence</returns>
        public float GetSequencePriority(string name) {
             InternalUnsafeMethods.GetSequencePriority__Args _args = new InternalUnsafeMethods.GetSequencePriority__Args() {
                name = name,
             };
             float _engineResult = InternalUnsafeMethods.GetSequencePriority()(ObjectPtr, _args);
             return _engineResult;
        }

        /// <description>
        /// Get the number of keyframes in the sequence.
        /// </description>
        /// <param name="name">name of the sequence to query</param>
        /// <returns>number of keyframes in the sequence</returns>
        /// <code>
        /// echo( "Run has "@ %this.getSequenceFrameCount( "run" ) 
        /// </code>
        public int GetSequenceFrameCount(string name) {
             InternalUnsafeMethods.GetSequenceFrameCount__Args _args = new InternalUnsafeMethods.GetSequenceFrameCount__Args() {
                name = name,
             };
             int _engineResult = InternalUnsafeMethods.GetSequenceFrameCount()(ObjectPtr, _args);
             return _engineResult;
        }

        /// <description>
        /// Get information about where the sequence data came from.
        /// For example, whether it was loaded from an external DSQ file.
        /// </description>
        /// <param name="name">name of the sequence to query</param>
        /// <returns>TAB delimited string of the form: "from reserved start end total", where:<dl><dt>from</dt><dd>the source of the animation data, such as the path to a DSQ file, or the name of an existing sequence in the shape. This field will be empty for sequences already embedded in the DTS or DAE file.</dd><dt>reserved</dt><dd>reserved value</dd><dt>start</dt><dd>the first frame in the source sequence used to create this sequence</dd><dt>end</dt><dd>the last frame in the source sequence used to create this sequence</dd><dt>total</dt><dd>the total number of frames in the source sequence</dd></dl></returns>
        /// <code>
        /// // print the source for the walk animation
        /// echo( "walk source:" SPC getField( %this.getSequenceSource( "walk" ), 0 ) );
        /// </code>
        public string GetSequenceSource(string name) {
             InternalUnsafeMethods.GetSequenceSource__Args _args = new InternalUnsafeMethods.GetSequenceSource__Args() {
                name = name,
             };
             IntPtr _engineResult = InternalUnsafeMethods.GetSequenceSource()(ObjectPtr, _args);
             return StringMarshal.IntPtrToUtf8String(_engineResult);
        }

        /// <description>
        /// Get the name of the indexed sequence.
        /// </description>
        /// <param name="index">index of the sequence to query (valid range is 0 - getSequenceCount()-1)</param>
        /// <returns>the name of the sequence</returns>
        /// <code>
        /// // print the name of all sequences in the shape
        /// %count = %this.getSequenceCount();
        /// for ( %i = 0; %i < %count; %i++ )
        ///    echo( %i SPC %this.getSequenceName( %i ) );
        /// </code>
        public string GetSequenceName(int index) {
             InternalUnsafeMethods.GetSequenceName__Args _args = new InternalUnsafeMethods.GetSequenceName__Args() {
                index = index,
             };
             IntPtr _engineResult = InternalUnsafeMethods.GetSequenceName()(ObjectPtr, _args);
             return StringMarshal.IntPtrToUtf8String(_engineResult);
        }

        /// <description>
        /// Find the index of the sequence with the given name.
        /// </description>
        /// <param name="name">name of the sequence to lookup</param>
        /// <returns>index of the sequence with matching name, or -1 if not found</returns>
        /// <code>
        /// // Check if a given sequence exists in the shape
        /// if ( %this.getSequenceIndex( "walk" ) == -1 )
        ///    echo( "Could not find 'walk' sequence" );
        /// </code>
        public int GetSequenceIndex(string name) {
             InternalUnsafeMethods.GetSequenceIndex__Args _args = new InternalUnsafeMethods.GetSequenceIndex__Args() {
                name = name,
             };
             int _engineResult = InternalUnsafeMethods.GetSequenceIndex()(ObjectPtr, _args);
             return _engineResult;
        }

        /// <description>
        /// Get the total number of sequences in the shape.
        /// </description>
        /// <returns>the number of sequences in the shape</returns>
        public int GetSequenceCount() {
             InternalUnsafeMethods.GetSequenceCount__Args _args = new InternalUnsafeMethods.GetSequenceCount__Args() {
             };
             int _engineResult = InternalUnsafeMethods.GetSequenceCount()(ObjectPtr, _args);
             return _engineResult;
        }

        /// <description>
        /// () Remove the imposter detail level (if any) from the shape.
        /// </description>
        /// <returns>true if successful, false otherwise</returns>
        public bool RemoveImposter() {
             InternalUnsafeMethods.RemoveImposter__Args _args = new InternalUnsafeMethods.RemoveImposter__Args() {
             };
             bool _engineResult = InternalUnsafeMethods.RemoveImposter()(ObjectPtr, _args);
             return _engineResult;
        }

        /// <description>
        /// Add (or edit) an imposter detail level to the shape.
        /// If the shape already contains an imposter detail level, this command will simply change the imposter settings
        /// </description>
        /// <param name="size">size of the imposter detail level</param>
        /// <param name="equatorSteps">defines the number of snapshots to take around the equator. Imagine the object being rotated around the vertical axis, then a snapshot taken at regularly spaced intervals.</param>
        /// <param name="polarSteps">defines the number of snapshots taken between the poles (top and bottom), at each equator step. eg. At each equator snapshot, snapshots are taken at regular intervals between the poles.</param>
        /// <param name="dl">the detail level to use when generating the snapshots. Note that this is an array index rather than a detail size. So if an object has detail sizes of: 200, 150, and 40, then setting<paramref name="" /> dl to 1 will generate the snapshots using detail size 150.
        /// </param>
        /// <param name="dim">defines the size of the imposter images in pixels. The larger the number, the more detailed the billboard will be.</param>
        /// <param name="includePoles">flag indicating whether to include the "pole" snapshots. ie. the views from the top and bottom of the object.</param>
        /// <param name="polar_angle">if pole snapshots are active (<paramref name="" /> includePoles is true), this parameter defines the camera angle (in degrees) within which to render the pole snapshot. eg. if polar_angle is set to 25 degrees, then the snapshot taken at the pole (looking directly down or up at the object) will be rendered when the camera is within 25 degrees of the pole.
        /// </param>
        /// <returns>true if successful, false otherwise</returns>
        /// <code>
        /// %this.addImposter( 2, 4, 0, 0, 64, false, 0 );
        /// %this.addImposter( 2, 4, 2, 0, 64, true, 10 );   // this command would edit the existing imposter detail level
        /// </code>
        public int AddImposter(int size, int equatorSteps, int polarSteps, int dl, int dim, bool includePoles, float polarAngle) {
             InternalUnsafeMethods.AddImposter__Args _args = new InternalUnsafeMethods.AddImposter__Args() {
                size = size,
                equatorSteps = equatorSteps,
                polarSteps = polarSteps,
                dl = dl,
                dim = dim,
                includePoles = includePoles,
                polarAngle = polarAngle,
             };
             int _engineResult = InternalUnsafeMethods.AddImposter()(ObjectPtr, _args);
             return _engineResult;
        }

        /// <description>
        /// Get the settings used to generate imposters for the indexed detail level.
        /// </description>
        /// <param name="index">index of the detail level to query (does not need to be an imposter detail level</param>
        /// <returns>string of the form: "valid eqSteps pSteps dl dim poles angle", where:<dl><dt>valid</dt><dd>1 if this detail level generates imposters, 0 otherwise</dd><dt>eqSteps</dt><dd>number of steps around the equator</dd><dt>pSteps</dt><dd>number of steps between the poles</dd><dt>dl</dt><dd>index of the detail level used to generate imposters</dd><dt>dim</dt><dd>size (in pixels) of each imposter image</dd><dt>poles</dt><dd>1 to include pole images, 0 otherwise</dd><dt>angle</dt><dd>angle at which to display pole images</dd></dl></returns>
        /// <code>
        /// // print the imposter detail level settings
        /// %index = %this.getImposterDetailLevel();
        /// if ( %index != -1 )
        ///    echo( "Imposter settings: "@ %this.getImposterSettings( %index ) );
        /// 
        /// </code>
        public string GetImposterSettings(int index) {
             InternalUnsafeMethods.GetImposterSettings__Args _args = new InternalUnsafeMethods.GetImposterSettings__Args() {
                index = index,
             };
             IntPtr _engineResult = InternalUnsafeMethods.GetImposterSettings()(ObjectPtr, _args);
             return StringMarshal.IntPtrToUtf8String(_engineResult);
        }

        /// <description>
        /// Get the index of the imposter (auto-billboard) detail level (if any).
        /// </description>
        /// <returns>imposter detail level index, or -1 if the shape does not use imposters.</returns>
        public int GetImposterDetailLevel() {
             InternalUnsafeMethods.GetImposterDetailLevel__Args _args = new InternalUnsafeMethods.GetImposterDetailLevel__Args() {
             };
             int _engineResult = InternalUnsafeMethods.GetImposterDetailLevel()(ObjectPtr, _args);
             return _engineResult;
        }

        /// <description>
        /// Change the size of a detail level.
        /// </description>
        /// <remarks> Note that detail levels are always sorted in decreasing size order, so this command may cause detail level indices to change.
        /// </remarks>
        /// <param name="index">index of the detail level to modify</param>
        /// <param name="newSize">new size for the detail level</param>
        /// <returns>new index for this detail level</returns>
        /// <code>
        /// %this.setDetailLevelSize( 2, 256 );
        /// </code>
        public int SetDetailLevelSize(int index, int newSize) {
             InternalUnsafeMethods.SetDetailLevelSize__Args _args = new InternalUnsafeMethods.SetDetailLevelSize__Args() {
                index = index,
                newSize = newSize,
             };
             int _engineResult = InternalUnsafeMethods.SetDetailLevelSize()(ObjectPtr, _args);
             return _engineResult;
        }

        /// <description>
        /// Remove the detail level (including all meshes in the detail level)
        /// </description>
        /// <param name="size">size of the detail level to remove</param>
        /// <returns>true if successful, false otherwise</returns>
        /// <code>
        /// %this.removeDetailLevel( 2 );
        /// </code>
        public bool RemoveDetailLevel(int index) {
             InternalUnsafeMethods.RemoveDetailLevel__Args _args = new InternalUnsafeMethods.RemoveDetailLevel__Args() {
                index = index,
             };
             bool _engineResult = InternalUnsafeMethods.RemoveDetailLevel()(ObjectPtr, _args);
             return _engineResult;
        }

        /// <description>
        /// Rename a detail level.
        /// </description>
        /// <remarks> Note that detail level names must be unique, so this command will fail if there is already a detail level with the desired name
        /// </remarks>
        /// <param name="oldName">current name of the detail level</param>
        /// <param name="newName">new name of the detail level</param>
        /// <returns>true if successful, false otherwise</returns>
        /// <code>
        /// %this.renameDetailLevel( "detail-1", "collision-1" );
        /// </code>
        public bool RenameDetailLevel(string oldName, string newName) {
             InternalUnsafeMethods.RenameDetailLevel__Args _args = new InternalUnsafeMethods.RenameDetailLevel__Args() {
                oldName = oldName,
                newName = newName,
             };
             bool _engineResult = InternalUnsafeMethods.RenameDetailLevel()(ObjectPtr, _args);
             return _engineResult;
        }

        /// <description>
        /// Get the index of the detail level with a given size.
        /// </description>
        /// <param name="size">size of the detail level to lookup</param>
        /// <returns>index of the detail level with the desired size, or -1 if no such detail exists</returns>
        /// <code>
        /// if ( %this.getDetailLevelSize( 32 ) == -1 )
        ///    echo( "Error: This shape does not have a detail level at size 32" );
        /// </code>
        public int GetDetailLevelIndex(int size) {
             InternalUnsafeMethods.GetDetailLevelIndex__Args _args = new InternalUnsafeMethods.GetDetailLevelIndex__Args() {
                size = size,
             };
             int _engineResult = InternalUnsafeMethods.GetDetailLevelIndex()(ObjectPtr, _args);
             return _engineResult;
        }

        /// <description>
        /// Get the size of the indexed detail level.
        /// </description>
        /// <param name="index">detail level index (valid range is 0 - getDetailLevelCount()-1)</param>
        /// <returns>the detail level size</returns>
        /// <code>
        /// // print the sizes of all detail levels in the shape
        /// %count = %this.getDetailLevelCount();
        /// for ( %i = 0; %i < %count; %i++ )
        ///    echo( "Detail"@ %i 
        /// </code>
        public int GetDetailLevelSize(int index) {
             InternalUnsafeMethods.GetDetailLevelSize__Args _args = new InternalUnsafeMethods.GetDetailLevelSize__Args() {
                index = index,
             };
             int _engineResult = InternalUnsafeMethods.GetDetailLevelSize()(ObjectPtr, _args);
             return _engineResult;
        }

        /// <description>
        /// Get the name of the indexed detail level.
        /// </description>
        /// <param name="index">detail level index (valid range is 0 - getDetailLevelCount()-1)</param>
        /// <returns>the detail level name</returns>
        /// <code>
        /// // print the names of all detail levels in the shape
        /// %count = %this.getDetailLevelCount();
        /// for ( %i = 0; %i < %count; %i++ )
        ///    echo( %i SPC %this.getDetailLevelName( %i ) );
        /// </code>
        public string GetDetailLevelName(int index) {
             InternalUnsafeMethods.GetDetailLevelName__Args _args = new InternalUnsafeMethods.GetDetailLevelName__Args() {
                index = index,
             };
             IntPtr _engineResult = InternalUnsafeMethods.GetDetailLevelName()(ObjectPtr, _args);
             return StringMarshal.IntPtrToUtf8String(_engineResult);
        }

        /// <description>
        /// Get the total number of detail levels in the shape.
        /// </description>
        /// <returns>the number of detail levels in the shape</returns>
        public int GetDetailLevelCount() {
             InternalUnsafeMethods.GetDetailLevelCount__Args _args = new InternalUnsafeMethods.GetDetailLevelCount__Args() {
             };
             int _engineResult = InternalUnsafeMethods.GetDetailLevelCount()(ObjectPtr, _args);
             return _engineResult;
        }

        /// <description>
        /// Set the shape bounds to the given bounding box.
        /// </description>
        /// <param name="Bounding">box "minX minY minZ maxX maxY maxZ"</param>
        /// <returns>true if successful, false otherwise</returns>
        public bool SetBounds(Box3F bbox) {
bbox.Alloc();             InternalUnsafeMethods.SetBounds__Args _args = new InternalUnsafeMethods.SetBounds__Args() {
                bbox = bbox.internalStructPtr,
             };
             bool _engineResult = InternalUnsafeMethods.SetBounds()(ObjectPtr, _args);
bbox.Free();             return _engineResult;
        }

        /// <description>
        /// Get the bounding box for the shape.
        /// </description>
        /// <returns>Bounding box "minX minY minZ maxX maxY maxZ"</returns>
        public Box3F GetBounds() {
             InternalUnsafeMethods.GetBounds__Args _args = new InternalUnsafeMethods.GetBounds__Args() {
             };
             Box3F.InternalStruct _engineResult = InternalUnsafeMethods.GetBounds()(ObjectPtr, _args);
             return new Box3F(_engineResult);
        }

        /// <description>
        /// Remove a mesh from the shape.
        /// If all geometry is removed from an object, the object is also removed.
        /// </description>
        /// <param name="name">full name (object name + detail size) of the mesh to remove</param>
        /// <returns>true if successful, false otherwise</returns>
        /// <code>
        /// %this.removeMesh( "SimpleShape128" );
        /// </code>
        public bool RemoveMesh(string name) {
             InternalUnsafeMethods.RemoveMesh__Args _args = new InternalUnsafeMethods.RemoveMesh__Args() {
                name = name,
             };
             bool _engineResult = InternalUnsafeMethods.RemoveMesh()(ObjectPtr, _args);
             return _engineResult;
        }

        /// <description>
        /// Add geometry from another DTS or DAE shape file into this shape.
        /// Any materials required by the source mesh are also copied into this shape.<br>
        /// </description>
        /// <param name="meshName">full name (object name + detail size) of the new mesh. If no detail size is present at the end of the name, a value of 2 is used.<br>An underscore before the number at the end of the name will be interpreted as a negative sign. eg. "MyMesh_4" will be interpreted as "MyMesh-4".</param>
        /// <param name="srcShape">name of a shape file (DTS or DAE) that contains the mesh</param>
        /// <param name="srcMesh">the full name (object name + detail size) of the mesh to copy from the DTS/DAE file into this shape</li></param>
        /// <returns>true if successful, false otherwise</returns>
        /// <code>
        /// %this.addMesh( "ColMesh-1", "./collision.dts", "ColMesh", "Col-1" );
        /// %this.addMesh( "SimpleShape10", "./testShape.dae", "MyMesh2",  );
        /// </code>
        public bool AddMesh(string meshName, string srcShape, string srcMesh) {
             InternalUnsafeMethods.AddMesh__Args _args = new InternalUnsafeMethods.AddMesh__Args() {
                meshName = meshName,
                srcShape = srcShape,
                srcMesh = srcMesh,
             };
             bool _engineResult = InternalUnsafeMethods.AddMesh()(ObjectPtr, _args);
             return _engineResult;
        }

        /// <description>
        /// Set the name of the material attached to the mesh.
        /// </description>
        /// <param name="meshName">full name (object name + detail size) of the mesh to modify</param>
        /// <param name="matName">name of the material to attach. This could be the base name of the diffuse texture (eg. "test_mat" for "test_mat.jpg"), or the name of a Material object already defined in script.</param>
        /// <returns>true if successful, false otherwise</returns>
        /// <code>
        /// // set the mesh material
        /// %this.setMeshMaterial( "SimpleShape128", "test_mat" );
        /// </code>
        public bool SetMeshMaterial(string meshName, string matName) {
             InternalUnsafeMethods.SetMeshMaterial__Args _args = new InternalUnsafeMethods.SetMeshMaterial__Args() {
                meshName = meshName,
                matName = matName,
             };
             bool _engineResult = InternalUnsafeMethods.SetMeshMaterial()(ObjectPtr, _args);
             return _engineResult;
        }

        /// <description>
        /// Get the name of the material attached to a mesh. Note that only the first material used by the mesh is returned.
        /// </description>
        /// <param name="name">full name (object name + detail size) of the mesh to query</param>
        /// <returns>name of the material attached to the mesh (suitable for use with the Material mapTo field)</returns>
        /// <code>
        /// echo( "Mesh material is "@ %this.sgetMeshMaterial( "SimpleShape128" ) );
        /// 
        /// </code>
        public string GetMeshMaterial(string name) {
             InternalUnsafeMethods.GetMeshMaterial__Args _args = new InternalUnsafeMethods.GetMeshMaterial__Args() {
                name = name,
             };
             IntPtr _engineResult = InternalUnsafeMethods.GetMeshMaterial()(ObjectPtr, _args);
             return StringMarshal.IntPtrToUtf8String(_engineResult);
        }

        /// <description>
        /// Set the display type for the mesh.
        /// </description>
        /// <param name="name">full name (object name + detail size) of the mesh to modify</param>
        /// <param name="type">the new type for the mesh: "normal", "billboard" or "billboardzaxis"</param>
        /// <returns>true if successful, false otherwise</returns>
        /// <code>
        /// // set the mesh to be a billboard
        /// %this.setMeshType( "SimpleShape64", "billboard" );
        /// </code>
        public bool SetMeshType(string name, string type) {
             InternalUnsafeMethods.SetMeshType__Args _args = new InternalUnsafeMethods.SetMeshType__Args() {
                name = name,
                type = type,
             };
             bool _engineResult = InternalUnsafeMethods.SetMeshType()(ObjectPtr, _args);
             return _engineResult;
        }

        /// <description>
        /// Get the display type of the mesh.
        /// </description>
        /// <param name="name">name of the mesh to query</param>
        /// <returns>the string returned is one of:<dl><dt>normal</dt><dd>a normal 3D mesh</dd><dt>billboard</dt><dd>a mesh that always faces the camera</dd><dt>billboardzaxis</dt><dd>a mesh that always faces the camera in the Z-axis</dd></dl></returns>
        /// <code>
        /// echo( "Mesh type is "@ %this.getMeshType( "SimpleShape128" ) );
        /// 
        /// </code>
        public string GetMeshType(string name) {
             InternalUnsafeMethods.GetMeshType__Args _args = new InternalUnsafeMethods.GetMeshType__Args() {
                name = name,
             };
             IntPtr _engineResult = InternalUnsafeMethods.GetMeshType()(ObjectPtr, _args);
             return StringMarshal.IntPtrToUtf8String(_engineResult);
        }

        /// <description>
        /// Change the detail level size of the named mesh.
        /// </description>
        /// <param name="name">full name (object name + current size ) of the mesh to modify</param>
        /// <param name="size">new detail level size</param>
        /// <returns>true if successful, false otherwise.</returns>
        /// <code>
        /// %this.setMeshSize( "SimpleShape128", 64 );
        /// </code>
        public bool SetMeshSize(string name, int size) {
             InternalUnsafeMethods.SetMeshSize__Args _args = new InternalUnsafeMethods.SetMeshSize__Args() {
                name = name,
                size = size,
             };
             bool _engineResult = InternalUnsafeMethods.SetMeshSize()(ObjectPtr, _args);
             return _engineResult;
        }

        /// <description>
        /// Get the detail level size of the indexed mesh for the specified object.
        /// </description>
        /// <param name="name">name of the object to query</param>
        /// <param name="index">index of the mesh (valid range is 0 - getMeshCount()-1)</param>
        /// <returns>the mesh detail level size.</returns>
        /// <code>
        /// // print sizes for all detail levels of this object
        /// %objName = "trunk";
        /// %count = %this.getMeshCount( %objName );
        /// for ( %i = 0; %i < %count; %i++ )
        ///    echo( %this.getMeshSize( %objName, %i ) );
        /// </code>
        public int GetMeshSize(string name, int index) {
             InternalUnsafeMethods.GetMeshSize__Args _args = new InternalUnsafeMethods.GetMeshSize__Args() {
                name = name,
                index = index,
             };
             int _engineResult = InternalUnsafeMethods.GetMeshSize()(ObjectPtr, _args);
             return _engineResult;
        }

        /// <description>
        /// Get the name of the indexed mesh (detail level) for the specified object.
        /// </description>
        /// <param name="name">name of the object to query</param>
        /// <param name="index">index of the mesh (valid range is 0 - getMeshCount()-1)</param>
        /// <returns>the mesh name.</returns>
        /// <code>
        /// // print the names of all meshes in the shape
        /// %objCount = %this.getObjectCount();
        /// for ( %i = 0; %i < %objCount; %i++ )
        /// {
        ///    %objName = %this.getObjectName( %i );
        ///    %meshCount = %this.getMeshCount( %objName );
        ///    for ( %j = 0; %j < %meshCount; %j++ )
        ///       echo( %this.getMeshName( %objName, %j ) );
        /// }
        /// </code>
        public string GetMeshName(string name, int index) {
             InternalUnsafeMethods.GetMeshName__Args _args = new InternalUnsafeMethods.GetMeshName__Args() {
                name = name,
                index = index,
             };
             IntPtr _engineResult = InternalUnsafeMethods.GetMeshName()(ObjectPtr, _args);
             return StringMarshal.IntPtrToUtf8String(_engineResult);
        }

        /// <description>
        /// Get the number of meshes (detail levels) for the specified object.
        /// </description>
        /// <param name="name">name of the object to query</param>
        /// <returns>the number of meshes for this object.</returns>
        /// <code>
        /// %count = %this.getMeshCount( "SimpleShape" );
        /// </code>
        public int GetMeshCount(string name) {
             InternalUnsafeMethods.GetMeshCount__Args _args = new InternalUnsafeMethods.GetMeshCount__Args() {
                name = name,
             };
             int _engineResult = InternalUnsafeMethods.GetMeshCount()(ObjectPtr, _args);
             return _engineResult;
        }

        /// <description>
        /// Remove an object (including all meshes for that object) from the shape.
        /// </description>
        /// <param name="name">name of the object to remove.</param>
        /// <returns>true if successful, false otherwise.</returns>
        /// <code>
        /// // clear all objects in the shape
        /// %count = %this.getObjectCount();
        /// for ( %i = %count-1; %i >= 0; %i-- )
        ///    %this.removeObject( %this.getObjectName(%i) );
        /// </code>
        public bool RemoveObject(string name) {
             InternalUnsafeMethods.RemoveObject__Args _args = new InternalUnsafeMethods.RemoveObject__Args() {
                name = name,
             };
             bool _engineResult = InternalUnsafeMethods.RemoveObject()(ObjectPtr, _args);
             return _engineResult;
        }

        /// <description>
        /// Rename an object.
        /// </description>
        /// <remarks> Note that object names must be unique, so this command will fail if there is already an object with the desired name
        /// </remarks>
        /// <param name="oldName">current name of the object</param>
        /// <param name="newName">new name of the object</param>
        /// <returns>true if successful, false otherwise</returns>
        /// <code>
        /// %this.renameObject( "MyBox", "Box" );
        /// </code>
        public bool RenameObject(string oldName, string newName) {
             InternalUnsafeMethods.RenameObject__Args _args = new InternalUnsafeMethods.RenameObject__Args() {
                oldName = oldName,
                newName = newName,
             };
             bool _engineResult = InternalUnsafeMethods.RenameObject()(ObjectPtr, _args);
             return _engineResult;
        }

        /// <description>
        /// Set the node an object is attached to.
        /// When the shape is rendered, the object geometry is rendered at the node's current transform.
        /// </description>
        /// <param name="objName">name of the object to modify</param>
        /// <param name="nodeName">name of the node to attach the object to</param>
        /// <returns>true if successful, false otherwise</returns>
        /// <code>
        /// %this.setObjectNode( "Hand", "Bip01 LeftHand" );
        /// </code>
        public bool SetObjectNode(string objName, string nodeName) {
             InternalUnsafeMethods.SetObjectNode__Args _args = new InternalUnsafeMethods.SetObjectNode__Args() {
                objName = objName,
                nodeName = nodeName,
             };
             bool _engineResult = InternalUnsafeMethods.SetObjectNode()(ObjectPtr, _args);
             return _engineResult;
        }

        /// <description>
        /// Get the name of the node this object is attached to.
        /// </description>
        /// <param name="name">name of the object to get.</param>
        /// <returns>the name of the attached node, or an empty string if this object is not attached to a node (usually the case for skinned meshes).</returns>
        /// <code>
        /// echo( "Hand is attached to "@ %this.getObjectNode( "Hand" ) );
        /// 
        /// </code>
        public string GetObjectNode(string name) {
             InternalUnsafeMethods.GetObjectNode__Args _args = new InternalUnsafeMethods.GetObjectNode__Args() {
                name = name,
             };
             IntPtr _engineResult = InternalUnsafeMethods.GetObjectNode()(ObjectPtr, _args);
             return StringMarshal.IntPtrToUtf8String(_engineResult);
        }

        /// <description>
        /// Get the index of the first object with the given name.
        /// </description>
        /// <param name="name">name of the object to get.</param>
        /// <returns>the index of the named object.</returns>
        /// <code>
        /// %index = %this.getObjectIndex( "Head" );
        /// </code>
        public int GetObjectIndex(string name) {
             InternalUnsafeMethods.GetObjectIndex__Args _args = new InternalUnsafeMethods.GetObjectIndex__Args() {
                name = name,
             };
             int _engineResult = InternalUnsafeMethods.GetObjectIndex()(ObjectPtr, _args);
             return _engineResult;
        }

        /// <description>
        /// Get the name of the indexed object.
        /// </description>
        /// <param name="index">index of the object to get (valid range is 0 - getObjectCount()-1).</param>
        /// <returns>the name of the indexed object.</returns>
        /// <code>
        /// // print the names of all objects in the shape
        /// %count = %this.getObjectCount();
        /// for ( %i = 0; %i < %count; %i++ )
        ///    echo( %i SPC %this.getObjectName( %i ) );
        /// </code>
        public string GetObjectName(int index) {
             InternalUnsafeMethods.GetObjectName__Args _args = new InternalUnsafeMethods.GetObjectName__Args() {
                index = index,
             };
             IntPtr _engineResult = InternalUnsafeMethods.GetObjectName()(ObjectPtr, _args);
             return StringMarshal.IntPtrToUtf8String(_engineResult);
        }

        /// <description>
        /// Get the total number of objects in the shape.
        /// </description>
        /// <returns>the number of objects in the shape.</returns>
        /// <code>
        /// %count = %this.getObjectCount();
        /// </code>
        public int GetObjectCount() {
             InternalUnsafeMethods.GetObjectCount__Args _args = new InternalUnsafeMethods.GetObjectCount__Args() {
             };
             int _engineResult = InternalUnsafeMethods.GetObjectCount()(ObjectPtr, _args);
             return _engineResult;
        }

        /// <description>
        /// Get the name of the indexed shape material.
        /// </description>
        /// <param name="index">index of the material to get (valid range is 0 - getTargetCount()-1).</param>
        /// <returns>the name of the indexed material.</returns>
        /// <code>
        /// %count = %this.getTargetCount();
        /// for ( %i = 0; %i < %count; %i++ )
        ///    echo( "Target "@ %i 
        /// </code>
        public string GetTargetName(int index) {
             InternalUnsafeMethods.GetTargetName__Args _args = new InternalUnsafeMethods.GetTargetName__Args() {
                index = index,
             };
             IntPtr _engineResult = InternalUnsafeMethods.GetTargetName()(ObjectPtr, _args);
             return StringMarshal.IntPtrToUtf8String(_engineResult);
        }

        /// <description>
        /// Get the number of materials in the shape.
        /// </description>
        /// <returns>the number of materials in the shape.</returns>
        /// <code>
        /// %count = %this.getTargetCount();
        /// </code>
        public int GetTargetCount() {
             InternalUnsafeMethods.GetTargetCount__Args _args = new InternalUnsafeMethods.GetTargetCount__Args() {
             };
             int _engineResult = InternalUnsafeMethods.GetTargetCount()(ObjectPtr, _args);
             return _engineResult;
        }

        /// <description>
        /// Remove a node from the shape.
        /// The named node is removed from the shape, including from any sequences that use the node. Child nodes and objects attached to the node are re-assigned to the node's parent.
        /// </description>
        /// <param name="name">name of the node to remove.</param>
        /// <returns>true if successful, false otherwise.</returns>
        /// <code>
        /// %this.removeNode( "Nose" );
        /// </code>
        public bool RemoveNode(string name) {
             InternalUnsafeMethods.RemoveNode__Args _args = new InternalUnsafeMethods.RemoveNode__Args() {
                name = name,
             };
             bool _engineResult = InternalUnsafeMethods.RemoveNode()(ObjectPtr, _args);
             return _engineResult;
        }

        /// <description>
        /// Add a new node.
        /// </description>
        /// <param name="name">name for the new node (must not already exist)</param>
        /// <param name="parentName">name of an existing node to be the parent of the new node. If empty (""), the new node will be at the root level of the node hierarchy.</param>
        /// <param name="txfm">(optional) transform string of the form: "pos.x pos.y pos.z rot.x rot.y rot.z rot.angle"</param>
        /// <param name="isworld">(optional) flag to set the local-to-parent or the global transform. If false, or not specified, the position and orientation are treated as relative to the node's parent.</param>
        /// <returns>true if successful, false otherwise</returns>
        /// <code>
        /// %this.addNode( "Nose", "Bip01 Head", "0 2 2 0 0 1 0" );
        /// %this.addNode( "myRoot", "", "0 0 4 0 0 1 1.57" );
        /// %this.addNode( "Nodes", "Bip01 Head", "0 2 0 0 0 1 0", true );
        /// </code>
        public bool AddNode(string name, string parentName, TransformF txfm = null, bool isWorld = false) {
txfm = txfm ?? new TransformF("0 0 0 0 0 0 0 false");
txfm.Alloc();             InternalUnsafeMethods.AddNode__Args _args = new InternalUnsafeMethods.AddNode__Args() {
                name = name,
                parentName = parentName,
                txfm = txfm.internalStructPtr,
                isWorld = isWorld,
             };
             bool _engineResult = InternalUnsafeMethods.AddNode()(ObjectPtr, _args);
txfm.Free();             return _engineResult;
        }

        /// <description>
        /// Rename a node.
        /// </description>
        /// <remarks> Note that node names must be unique, so this command will fail if there is already a node with the desired name
        /// </remarks>
        /// <param name="oldName">current name of the node</param>
        /// <param name="newName">new name of the node</param>
        /// <returns>true if successful, false otherwise</returns>
        /// <code>
        /// %this.renameNode( "Bip01 L Hand", "mount5" );
        /// </code>
        public bool RenameNode(string oldName, string newName) {
             InternalUnsafeMethods.RenameNode__Args _args = new InternalUnsafeMethods.RenameNode__Args() {
                oldName = oldName,
                newName = newName,
             };
             bool _engineResult = InternalUnsafeMethods.RenameNode()(ObjectPtr, _args);
             return _engineResult;
        }

        /// <description>
        /// Set the base transform of a node. That is, the transform of the node when in the root (not-animated) pose.
        /// </description>
        /// <param name="name">name of the node to modify</param>
        /// <param name="txfm">transform string of the form: "pos.x pos.y pos.z rot.x rot.y rot.z rot.angle"</param>
        /// <param name="isworld">(optional) flag to set the local-to-parent or the global transform. If false, or not specified, the position and orientation are treated as relative to the node's parent.</param>
        /// <returns>true if successful, false otherwise</returns>
        /// <code>
        /// %this.setNodeTransform( "mount0", "0 0 1 0 0 1 0" );
        /// %this.setNodeTransform( "mount0", "0 0 0 0 0 1 1.57" );
        /// %this.setNodeTransform( "mount0", "1 0 0 0 0 1 0", true );
        /// </code>
        public bool SetNodeTransform(string name, TransformF txfm, bool isWorld = false) {
txfm.Alloc();             InternalUnsafeMethods.SetNodeTransform__Args _args = new InternalUnsafeMethods.SetNodeTransform__Args() {
                name = name,
                txfm = txfm.internalStructPtr,
                isWorld = isWorld,
             };
             bool _engineResult = InternalUnsafeMethods.SetNodeTransform()(ObjectPtr, _args);
txfm.Free();             return _engineResult;
        }

        /// <description>
        /// Get the base (ie. not animated) transform of a node.
        /// </description>
        /// <param name="name">name of the node to query.</param>
        /// <param name="isWorld">true to get the global transform, false (or omitted) to get the local-to-parent transform.</param>
        /// <returns>the node transform in the form "pos.x pos.y pos.z rot.x rot.y rot.z rot.angle".</returns>
        /// <code>
        /// %ret = %this.getNodeTransform( "mount0" );
        /// %this.setNodeTransform( "mount4", %ret );
        /// </code>
        public TransformF GetNodeTransform(string name, bool isWorld = false) {
             InternalUnsafeMethods.GetNodeTransform__Args _args = new InternalUnsafeMethods.GetNodeTransform__Args() {
                name = name,
                isWorld = isWorld,
             };
             TransformF.InternalStruct _engineResult = InternalUnsafeMethods.GetNodeTransform()(ObjectPtr, _args);
             return new TransformF(_engineResult);
        }

        /// <description>
        /// Get the name of the indexed object.
        /// </description>
        /// <param name="name">name of the node to query.</param>
        /// <param name="index">index of the object (valid range is 0 - getNodeObjectCount()-1).</param>
        /// <returns>the name of the indexed object.</returns>
        /// <code>
        /// // print the names of all objects attached to the node
        /// %count = %this.getNodeObjectCount( "Bip01 Head" );
        /// for ( %i = 0; %i < %count; %i++ )
        ///    echo( %this.getNodeObjectName( "Bip01 Head", %i ) );
        /// </code>
        public string GetNodeObjectName(string name, int index) {
             InternalUnsafeMethods.GetNodeObjectName__Args _args = new InternalUnsafeMethods.GetNodeObjectName__Args() {
                name = name,
                index = index,
             };
             IntPtr _engineResult = InternalUnsafeMethods.GetNodeObjectName()(ObjectPtr, _args);
             return StringMarshal.IntPtrToUtf8String(_engineResult);
        }

        /// <description>
        /// Get the number of geometry objects attached to this node.
        /// </description>
        /// <param name="name">name of the node to query.</param>
        /// <returns>the number of attached objects.</returns>
        /// <code>
        /// %count = %this.getNodeObjectCount( "Bip01 Head" );
        /// </code>
        public int GetNodeObjectCount(string name) {
             InternalUnsafeMethods.GetNodeObjectCount__Args _args = new InternalUnsafeMethods.GetNodeObjectCount__Args() {
                name = name,
             };
             int _engineResult = InternalUnsafeMethods.GetNodeObjectCount()(ObjectPtr, _args);
             return _engineResult;
        }

        /// <description>
        /// Get the name of the indexed child node.
        /// </description>
        /// <param name="name">name of the parent node to query.</param>
        /// <param name="index">index of the child node (valid range is 0 - getNodeChildName()-1).</param>
        /// <returns>the name of the indexed child node.</returns>
        /// <code>
        /// function dumpNode( %shape, %name, %indent )
        /// {
        ///    echo( %indent@ %name );
        ///    %count = %shape.getNodeChildCount( %name );
        ///    for ( %i = 0; %i < %count; %i++ )
        ///       dumpNode( %shape, %shape.getNodeChildName( %name, %i ), %indent 
        /// </code>
        public string GetNodeChildName(string name, int index) {
             InternalUnsafeMethods.GetNodeChildName__Args _args = new InternalUnsafeMethods.GetNodeChildName__Args() {
                name = name,
                index = index,
             };
             IntPtr _engineResult = InternalUnsafeMethods.GetNodeChildName()(ObjectPtr, _args);
             return StringMarshal.IntPtrToUtf8String(_engineResult);
        }

        /// <description>
        /// Get the number of children of this node.
        /// </description>
        /// <param name="name">name of the node to query.</param>
        /// <returns>the number of child nodes.</returns>
        /// <code>
        /// %count = %this.getNodeChildCount( "Bip01 Pelvis" );
        /// </code>
        public int GetNodeChildCount(string name) {
             InternalUnsafeMethods.GetNodeChildCount__Args _args = new InternalUnsafeMethods.GetNodeChildCount__Args() {
                name = name,
             };
             int _engineResult = InternalUnsafeMethods.GetNodeChildCount()(ObjectPtr, _args);
             return _engineResult;
        }

        /// <description>
        /// Set the parent of a node.
        /// </description>
        /// <param name="name">name of the node to modify</param>
        /// <param name="parentName">name of the parent node to set (use "" to move the node to the root level)</param>
        /// <returns>true if successful, false if failed</returns>
        /// <code>
        /// %this.setNodeParent( "Bip01 Pelvis", "start01" );
        /// </code>
        public bool SetNodeParent(string name, string parentName) {
             InternalUnsafeMethods.SetNodeParent__Args _args = new InternalUnsafeMethods.SetNodeParent__Args() {
                name = name,
                parentName = parentName,
             };
             bool _engineResult = InternalUnsafeMethods.SetNodeParent()(ObjectPtr, _args);
             return _engineResult;
        }

        /// <description>
        /// Get the name of the node's parent. If the node has no parent (ie. it is at the root level), return an empty string.
        /// </description>
        /// <param name="name">name of the node to query.</param>
        /// <returns>the name of the node's parent, or "" if the node is at the root level</returns>
        /// <code>
        /// echo( "Bip01 Pelvis parent = "@ %this.getNodeParentName( "Bip01 Pelvis ") );
        /// 
        /// </code>
        public string GetNodeParentName(string name) {
             InternalUnsafeMethods.GetNodeParentName__Args _args = new InternalUnsafeMethods.GetNodeParentName__Args() {
                name = name,
             };
             IntPtr _engineResult = InternalUnsafeMethods.GetNodeParentName()(ObjectPtr, _args);
             return StringMarshal.IntPtrToUtf8String(_engineResult);
        }

        /// <description>
        /// Get the name of the indexed node.
        /// </description>
        /// <param name="index">index of the node to lookup (valid range is 0 - getNodeCount()-1).</param>
        /// <returns>the name of the indexed node, or "" if no such node exists.</returns>
        /// <code>
        /// // print the names of all the nodes in the shape
        /// %count = %this.getNodeCount();
        /// for (%i = 0; %i < %count; %i++)
        ///    echo(%i SPC %this.getNodeName(%i));
        /// </code>
        public string GetNodeName(int index) {
             InternalUnsafeMethods.GetNodeName__Args _args = new InternalUnsafeMethods.GetNodeName__Args() {
                index = index,
             };
             IntPtr _engineResult = InternalUnsafeMethods.GetNodeName()(ObjectPtr, _args);
             return StringMarshal.IntPtrToUtf8String(_engineResult);
        }

        /// <description>
        /// Get the index of the node.
        /// </description>
        /// <param name="name">name of the node to lookup.</param>
        /// <returns>the index of the named node, or -1 if no such node exists.</returns>
        /// <code>
        /// // get the index of Bip01 Pelvis node in the shape
        /// %index = %this.getNodeIndex( "Bip01 Pelvis" );
        /// </code>
        public int GetNodeIndex(string name) {
             InternalUnsafeMethods.GetNodeIndex__Args _args = new InternalUnsafeMethods.GetNodeIndex__Args() {
                name = name,
             };
             int _engineResult = InternalUnsafeMethods.GetNodeIndex()(ObjectPtr, _args);
             return _engineResult;
        }

        /// <description>
        /// Get the total number of nodes in the shape.
        /// </description>
        /// <returns>the number of nodes in the shape.</returns>
        /// <code>
        /// %count = %this.getNodeCount();
        /// </code>
        public int GetNodeCount() {
             InternalUnsafeMethods.GetNodeCount__Args _args = new InternalUnsafeMethods.GetNodeCount__Args() {
             };
             int _engineResult = InternalUnsafeMethods.GetNodeCount()(ObjectPtr, _args);
             return _engineResult;
        }

        /// <description>
        /// Notify game objects that this shape file has changed, allowing them to update internal data if needed.
        /// </description>
        public void NotifyShapeChanged() {
             InternalUnsafeMethods.NotifyShapeChanged__Args _args = new InternalUnsafeMethods.NotifyShapeChanged__Args() {
             };
             InternalUnsafeMethods.NotifyShapeChanged()(ObjectPtr, _args);
        }

        /// <description>
        /// Write the current change set to a TSShapeConstructor script file. The name of the script file is the same as the model, but with .cs extension. eg. myShape.cs for myShape.dts or myShape.dae.
        /// </description>
        public void WriteChangeSet() {
             InternalUnsafeMethods.WriteChangeSet__Args _args = new InternalUnsafeMethods.WriteChangeSet__Args() {
             };
             InternalUnsafeMethods.WriteChangeSet()(ObjectPtr, _args);
        }

        /// <description>
        /// Save the shape (with all current changes) to a new DTS file.
        /// </description>
        /// <param name="filename">Destination filename.</param>
        /// <code>
        /// %this.saveShape( "./myShape.dts" );
        /// </code>
        public void SaveShape(string filename) {
             InternalUnsafeMethods.SaveShape__Args _args = new InternalUnsafeMethods.SaveShape__Args() {
                filename = filename,
             };
             InternalUnsafeMethods.SaveShape()(ObjectPtr, _args);
        }

        /// <description>
        /// Dump the shape hierarchy to the console or to a file. Useful for reviewing the result of a series of construction commands.
        /// </description>
        /// <param name="filename">Destination filename. If not specified, dump to console.</param>
        /// <code>
        /// %this.dumpShape();               // dump to console
        /// %this.dumpShape( "./dump.txt" ); // dump to file
        /// </code>
        public void DumpShape(string filename = "") {
             InternalUnsafeMethods.DumpShape__Args _args = new InternalUnsafeMethods.DumpShape__Args() {
                filename = filename,
             };
             InternalUnsafeMethods.DumpShape()(ObjectPtr, _args);
        }

        /// <description>
        /// Get the type info object for the TSShapeConstructor class.
        /// </description>
        /// <returns>The type info object for TSShapeConstructor</returns>
        public static EngineTypeInfo StaticGetType() {
             InternalUnsafeMethods.StaticGetType__Args _args = new InternalUnsafeMethods.StaticGetType__Args() {
             };
             IntPtr _engineResult = InternalUnsafeMethods.StaticGetType()(_args);
             return new EngineTypeInfo(_engineResult);
        }

        /// <description>
        /// Called when the DTS or DAE resource is flushed from memory. Not normally required, but may be useful to perform cleanup.
        /// </description>
        public virtual void OnUnload() {
             InternalUnsafeMethods.OnUnload__Args _args = new InternalUnsafeMethods.OnUnload__Args() {
             };
             InternalUnsafeMethods.OnUnload()(ObjectPtr, _args);
        }

        /// <description>
        /// Called immediately after the DTS or DAE file has been loaded; before the shape data is available to any other object (StaticShape, Player etc). This is where you should put any post-load commands to modify the shape in-memory such as addNode, renameSequence etc.
        /// </description>
        public virtual void OnLoad() {
             InternalUnsafeMethods.OnLoad__Args _args = new InternalUnsafeMethods.OnLoad__Args() {
             };
             InternalUnsafeMethods.OnLoad()(ObjectPtr, _args);
        }

        /// <description>
        /// Autofit a mesh primitive or set of convex hulls to the shape geometry. Hulls may optionally be converted to boxes, spheres and/or capsules based on their volume.
        /// </description>
        /// <param name="size">size for this detail level</param>
        /// <param name="type">one of: box, sphere, capsule, 10-dop x, 10-dop y, 10-dop z, 18-dop, 26-dop, convex hulls. See the Shape Editor documentation for more details about these types.</param>
        /// <param name="target">geometry to fit collision mesh(es) to; either "bounds" (for the whole shape), or the name of an object in the shape</param>
        /// <param name="depth">maximum split recursion depth (hulls only)</param>
        /// <param name="merge">volume % threshold used to merge hulls together (hulls only)</param>
        /// <param name="concavity">volume % threshold used to detect concavity (hulls only)</param>
        /// <param name="maxVerts">maximum number of vertices per hull (hulls only)</param>
        /// <param name="boxMaxError">max % volume difference for a hull to be converted to a box (hulls only)</param>
        /// <param name="sphereMaxError">max % volume difference for a hull to be converted to a sphere (hulls only)</param>
        /// <param name="capsuleMaxError">max % volume difference for a hull to be converted to a capsule (hulls only)</param>
        /// <returns>true if successful, false otherwise</returns>
        /// <code>
        /// %this.addCollisionDetail( -1, "box", "bounds" );
        /// %this.addCollisionDetail( -1, "convex hulls", "bounds", 4, 30, 30, 32, 0, 0, 0 );
        /// %this.addCollisionDetail( -1, "convex hulls", "bounds", 4, 30, 30, 32, 50, 50, 50 );
        /// </code>
        public bool AddCollisionDetail(int size, string type, string target, int depth = 4, float merge = 30f, float concavity = 30f, int maxVerts = 32, float boxMaxError = 0f, float sphereMaxError = 0f, float capsuleMaxError = 0f) {
             InternalUnsafeMethods.AddCollisionDetail__Args _args = new InternalUnsafeMethods.AddCollisionDetail__Args() {
                size = size,
                type = type,
                target = target,
                depth = depth,
                merge = merge,
                concavity = concavity,
                maxVerts = maxVerts,
                boxMaxError = boxMaxError,
                sphereMaxError = sphereMaxError,
                capsuleMaxError = capsuleMaxError,
             };
             bool _engineResult = InternalUnsafeMethods.AddCollisionDetail()(ObjectPtr, _args);
             return _engineResult;
        }

        /// <description>
        /// Add a new mesh primitive to the shape.
        /// </description>
        /// <param name="meshName">full name (object name + detail size) of the new mesh. If no detail size is present at the end of the name, a value of 2 is used.<br>An underscore before the number at the end of the name will be interpreted as a negative sign. eg. "MyMesh_4" will be interpreted as "MyMesh-4".</param>
        /// <param name="type">one of: "box", "sphere", "capsule"</param>
        /// <param name="params">mesh primitive parameters:
        /// <ul><li>for box: "size_x size_y size_z"</li><li>for sphere: "radius"</li><li>for capsule: "height radius"</li></ul></ul></param>
        /// <param name="txfm">local transform offset from the node for this mesh</param>
        /// <param name="nodeName">name of the node to attach the new mesh to (will change the object's node if adding a new mesh to an existing object)</param>
        /// <returns>true if successful, false otherwise</returns>
        /// <code>
        /// %this.addMesh( "Box4", "box", "2 4 2", "0 2 0 0 0 1 0", "eye" );
        /// %this.addMesh( "Sphere256", "sphere", "2", "0 0 0 0 0 1 0", "root" );
        /// %this.addMesh( "MyCapsule-1", "capsule", "2 5", "0 0 2 0 0 1 0", "base01" );
        /// </code>
        public bool AddPrimitive(string meshName, string type, string _params, TransformF txfm, string nodeName) {
txfm.Alloc();             InternalUnsafeMethods.AddPrimitive__Args _args = new InternalUnsafeMethods.AddPrimitive__Args() {
                meshName = meshName,
                type = type,
                _params = _params,
                txfm = txfm.internalStructPtr,
                nodeName = nodeName,
             };
             bool _engineResult = InternalUnsafeMethods.AddPrimitive()(ObjectPtr, _args);
txfm.Free();             return _engineResult;
        }


        /// <value>
        /// <description>
        /// Specifies the path to the DTS or DAE file to be operated on by this object.
        /// Since the TSShapeConstructor script must be in the same folder as the DTS or DAE file, it is recommended to use a relative path so that the shape and script files can be copied to another location without having to modify the path.
        /// </description>
        /// </value>
        public string BaseShape {
            get => GenericMarshal.StringTo<string>(GetFieldValue("baseShape"));
            set => SetFieldValue("baseShape", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Override the <up_axis> element in the COLLADA (.dae) file. No effect for DTS files.
        /// Set to one of the following values:
        /// <dl><dt>X_AXIS</dt><dd>Positive X points up. Model will be rotated into Torque's coordinate system (Z up).</dd><dt>Y_AXIS</dt><dd>Positive Y points up. Model will be rotated into Torque's coordinate system (Z up).</dd><dt>Z_AXIS</dt><dd>Positive Z points up. No rotation will be applied to the model.</dd><dt>DEFAULT</dt><dd>The default value. Use the value in the .dae file (defaults to Z_AXIS if the <up_axis> element is not present).</dd></dl>
        /// </description>
        /// </value>
        public TSShapeConstructorUpAxis UpAxis {
            get => GenericMarshal.StringTo<TSShapeConstructorUpAxis>(GetFieldValue("upAxis"));
            set => SetFieldValue("upAxis", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Override the <unit> element in the COLLADA (.dae) file. No effect for DTS files.
        /// COLLADA (.dae) files usually contain a <unit> element that indicates the 'real world' units that the model is described in. It means you can work in sensible and meaningful units in your modeling app.<br>
        /// For example, if you were modeling a small object like a cup, it might make sense to work in inches (1 MAX unit = 1 inch), but if you were modeling a building, it might make more sense to work in feet (1 MAX unit = 1 foot). If you export both models to COLLADA, T3D will automatically scale them appropriately. 1 T3D unit = 1 meter, so the cup would be scaled down by 0.0254, and the building scaled down by 0.3048, given them both the correct scale relative to each other.<br>
        /// Omit the field or set to -1 to use the value in the .dae file (1.0 if the <unit> element is not present)
        /// </description>
        /// </value>
        public float Unit {
            get => GenericMarshal.StringTo<float>(GetFieldValue("unit"));
            set => SetFieldValue("unit", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Control how the COLLADA (.dae) importer interprets LOD in the model. No effect for DTS files.
        /// Set to one of the following values:
        /// <dl><dt>DetectDTS</dt><dd>The default value. Instructs the importer to search for a 'baseXXX->startXXX' node hierarchy at the root level. If found, the importer acts as if ''TrailingNumber'' was set. Otherwise, all geometry is imported at a single detail size.</dd><dt>SingleSize</dt><dd>All geometry is imported at a fixed detail size. Numbers at the end of geometry node's are ignored.</dd><dt>TrailingNumber</dt><dd>Numbers at the end of geometry node's name are interpreted as the detail size (similar to DTS exporting). Geometry instances with the same base name but different trailing number are grouped into the same object.</dd><dt>DEFAULT</dt><dd>The default value. Use the value in the .dae file (defaults to Z_AXIS if the <up_axis> element is not present).</dd></dl>
        /// </description>
        /// </value>
        public TSShapeConstructorLodType LODType {
            get => GenericMarshal.StringTo<TSShapeConstructorLodType>(GetFieldValue("LODType"));
            set => SetFieldValue("LODType", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Sets the detail size when lodType is set to SingleSize. No effect otherwise, and no effect for DTS files.
        /// </description>
        /// <see cref="lodType" />
        /// </value>
        public int SingleDetailSize {
            get => GenericMarshal.StringTo<int>(GetFieldValue("singleDetailSize"));
            set => SetFieldValue("singleDetailSize", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Prefix to apply to all material map names in the COLLADA (.dae) file. No effect for DTS files.
        /// This field is useful to avoid material name clashes for exporters that generate generic material names like "texture0" or "material1".
        /// </description>
        /// </value>
        public string MatNamePrefix {
            get => GenericMarshal.StringTo<string>(GetFieldValue("matNamePrefix"));
            set => SetFieldValue("matNamePrefix", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// TAB separated patterns of nodes to import even if in neverImport list. No effect for DTS files.
        /// Torque allows unwanted nodes in COLLADA (.dae) files to to be ignored during import. This field contains a TAB separated list of patterns to match node names. Any node that matches one of the patterns in the list will <b>always</b> be imported, even if it also matches the neverImport list
        /// </description>
        /// <see cref="neverImport" />
        /// <code>
        /// singleton TSShapeConstructor(MyShapeDae)
        /// {
        ///    baseShape = "./myShape.dae";
        ///    alwaysImport = "mount*" TAB "eye";
        ///    neverImport = "*-PIVOT";
        /// }
        /// </code>
        /// </value>
        public string AlwaysImport {
            get => GenericMarshal.StringTo<string>(GetFieldValue("alwaysImport"));
            set => SetFieldValue("alwaysImport", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// TAB separated patterns of nodes to ignore on loading. No effect for DTS files.
        /// Torque allows unwanted nodes in COLLADA (.dae) files to to be ignored during import. This field contains a TAB separated list of patterns to match node names. Any node that matches one of the patterns in the list will not be imported (unless it matches the alwaysImport list.
        /// </description>
        /// <see cref="alwaysImport" />
        /// </value>
        public string NeverImport {
            get => GenericMarshal.StringTo<string>(GetFieldValue("neverImport"));
            set => SetFieldValue("neverImport", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// TAB separated patterns of meshes to import even if in neverImportMesh list. No effect for DTS files.
        /// Torque allows unwanted meshes in COLLADA (.dae) files to to be ignored during import. This field contains a TAB separated list of patterns to match mesh names. Any mesh that matches one of the patterns in the list will <b>always</b> be imported, even if it also matches the neverImportMesh list
        /// </description>
        /// <see cref="neverImportMesh" />
        /// <code>
        /// singleton TSShapeConstructor(MyShapeDae)
        /// {
        ///    baseShape = "./myShape.dae";
        ///    alwaysImportMesh = "body*" TAB "armor" TAB "bounds";
        ///    neverImportMesh = "*-dummy";
        /// }
        /// </code>
        /// </value>
        public string AlwaysImportMesh {
            get => GenericMarshal.StringTo<string>(GetFieldValue("alwaysImportMesh"));
            set => SetFieldValue("alwaysImportMesh", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// TAB separated patterns of meshes to ignore on loading. No effect for DTS files.
        /// Torque allows unwanted meshes in COLLADA (.dae) files to to be ignored during import. This field contains a TAB separated list of patterns to match mesh names. Any mesh that matches one of the patterns in the list will not be imported (unless it matches the alwaysImportMesh list.
        /// </description>
        /// <see cref="alwaysImportMesh" />
        /// </value>
        public string NeverImportMesh {
            get => GenericMarshal.StringTo<string>(GetFieldValue("neverImportMesh"));
            set => SetFieldValue("neverImportMesh", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// TAB separated patterns of materials to ignore on loading. No effect for DTS files.
        /// Torque allows unwanted materials in COLLADA (.dae) files to to be ignored during import. This field contains a TAB separated list of patterns to match material names. Any material that matches one of the patterns in the list will not be imported
        /// </description>
        /// </value>
        public string NeverImportMat {
            get => GenericMarshal.StringTo<string>(GetFieldValue("neverImportMat"));
            set => SetFieldValue("neverImportMat", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Ignore <scale> elements inside COLLADA <node>s. No effect for DTS files.
        /// This field is a workaround for certain exporters that generate bad node scaling, and is not usually required.
        /// </description>
        /// </value>
        public bool IgnoreNodeScale {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("IgnoreNodeScale"));
            set => SetFieldValue("IgnoreNodeScale", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Translate COLLADA model on import so the origin is at the center. No effect for DTS files.
        /// </description>
        /// </value>
        public bool AdjustCenter {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("AdjustCenter"));
            set => SetFieldValue("AdjustCenter", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Translate COLLADA model on import so origin is at the (Z axis) bottom of the model. No effect for DTS files.
        /// This can be used along with adjustCenter to have the origin at the center of the bottom of the model.
        /// </description>
        /// <see cref="adjustCenter" />
        /// </value>
        public bool AdjustFloor {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("AdjustFloor"));
            set => SetFieldValue("AdjustFloor", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Forces update of the materials.cs file in the same folder as the COLLADA (.dae) file, even if Materials already exist. No effect for DTS files.
        /// Normally only Materials that are not already defined are written to materials.cs.
        /// </description>
        /// </value>
        public bool ForceUpdateMaterials {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("forceUpdateMaterials"));
            set => SetFieldValue("forceUpdateMaterials", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Convert to left handed coordinate system.
        /// </description>
        /// </value>
        public bool ConvertLeftHanded {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("convertLeftHanded"));
            set => SetFieldValue("convertLeftHanded", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Calculate tangents and bitangents, if possible.
        /// </description>
        /// </value>
        public bool CalcTangentSpace {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("calcTangentSpace"));
            set => SetFieldValue("calcTangentSpace", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Convert spherical, cylindrical, box and planar mapping to proper UVs.
        /// </description>
        /// </value>
        public bool GenUVCoords {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("genUVCoords"));
            set => SetFieldValue("genUVCoords", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Preprocess UV transformations (scaling, translation ...).
        /// </description>
        /// </value>
        public bool TransformUVCoords {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("transformUVCoords"));
            set => SetFieldValue("transformUVCoords", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// This step flips all UV coordinates along the y-axis and adjusts material settings and bitangents accordingly.
        /// Assimp uses TL(0,0):BR(1,1). T3D uses TL(0,1):BR(1,0). This will be needed for most textured models.
        /// </description>
        /// </value>
        public bool FlipUVCoords {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("flipUVCoords"));
            set => SetFieldValue("flipUVCoords", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Search for instanced meshes and remove them by references to one master.
        /// </description>
        /// </value>
        public bool FindInstances {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("findInstances"));
            set => SetFieldValue("findInstances", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Limit bone weights to 4 per vertex.
        /// </description>
        /// </value>
        public bool LimitBoneWeights {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("limitBoneWeights"));
            set => SetFieldValue("limitBoneWeights", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Identifies and joins identical vertex data sets within all imported meshes.
        /// </description>
        /// </value>
        public bool JoinIdenticalVerts {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("JoinIdenticalVerts"));
            set => SetFieldValue("JoinIdenticalVerts", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// This step adjusts the output face winding order to be clockwise. The default assimp face winding order is counter clockwise.
        /// </description>
        /// </value>
        public bool ReverseWindingOrder {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("reverseWindingOrder"));
            set => SetFieldValue("reverseWindingOrder", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Reverse the normal vector direction for all normals.
        /// </description>
        /// </value>
        public bool InvertNormals {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("invertNormals"));
            set => SetFieldValue("invertNormals", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Removes redundant materials.
        /// </description>
        /// </value>
        public bool RemoveRedundantMats {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("removeRedundantMats"));
            set => SetFieldValue("removeRedundantMats", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// How to import timing data as frames, seconds or milliseconds.
        /// </description>
        /// </value>
        public TSShapeConstructorAnimType AnimTiming {
            get => GenericMarshal.StringTo<TSShapeConstructorAnimType>(GetFieldValue("animTiming"));
            set => SetFieldValue("animTiming", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// FPS value to use if timing is set in frames and the animations does not have an fps set.
        /// </description>
        /// </value>
        public int AnimFPS {
            get => GenericMarshal.StringTo<int>(GetFieldValue("animFPS"));
            set => SetFieldValue("animFPS", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Legacy method of adding sequences to a DTS or DAE shape after loading.
        /// </description>
        /// <code>
        /// singleton TSShapeConstructor(MyShapeDae)
        /// {
        ///    baseShape = "./myShape.dae";
        ///    sequence = "../anims/root.dae root";
        ///    sequence = "../anims/walk.dae walk";
        ///    sequence = "../anims/jump.dsq jump";
        /// }
        /// </code>
        /// </value>
        public string Sequence {
            get => GenericMarshal.StringTo<string>(GetFieldValue("sequence"));
            set => SetFieldValue("sequence", GenericMarshal.ToString(value));
        }
    }
}