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
    public unsafe class VController : SimObject {
        public VController(bool pRegister = false) 
            : base(pRegister) {
        }
        
        public VController(string pName, bool pRegister) 
            : this(false) {
            Name = pName;
            if (pRegister) {
                RegisterObject();
            }
        }
        
        public VController(string pName) 
            : this(pName, false) {
        }
        
        public VController(string pName, string pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(Engine.Sim.FindObject<SimObject>(pParent));
        }
        
        public VController(string pName, SimObject pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(pParent);
        }
        
        public VController(SimObject pObj) 
            : base(pObj) {
        }
        
        public VController(IntPtr pObj) 
            : base(pObj) {
        }
        
		protected override void CreateObjectPtr()
		{
			ObjectPtr = InternalUnsafeMethods.Create()(new InternalUnsafeMethods.Create__Args());
		}

        #region UnsafeNativeMethods
        new internal struct InternalUnsafeMethods {
            [StructLayout(LayoutKind.Sequential)]
            internal struct RemoveDataField__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string fieldName;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _RemoveDataField(IntPtr _this, RemoveDataField__Args args);
            private static _RemoveDataField _RemoveDataFieldFunc;
            internal static _RemoveDataField RemoveDataField() {
                if (_RemoveDataFieldFunc == null) {
                    _RemoveDataFieldFunc =
                        (_RemoveDataField)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnVController_removeDataField"), typeof(_RemoveDataField));
                }
                
                return _RemoveDataFieldFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct AddDataField__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string fieldType;
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string fieldName;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _AddDataField(IntPtr _this, AddDataField__Args args);
            private static _AddDataField _AddDataFieldFunc;
            internal static _AddDataField AddDataField() {
                if (_AddDataFieldFunc == null) {
                    _AddDataFieldFunc =
                        (_AddDataField)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnVController_addDataField"), typeof(_AddDataField));
                }
                
                return _AddDataFieldFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct SortTracks__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _SortTracks(IntPtr _this, SortTracks__Args args);
            private static _SortTracks _SortTracksFunc;
            internal static _SortTracks SortTracks() {
                if (_SortTracksFunc == null) {
                    _SortTracksFunc =
                        (_SortTracks)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnVController_sortTracks"), typeof(_SortTracks));
                }
                
                return _SortTracksFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct SortGroups__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _SortGroups(IntPtr _this, SortGroups__Args args);
            private static _SortGroups _SortGroupsFunc;
            internal static _SortGroups SortGroups() {
                if (_SortGroupsFunc == null) {
                    _SortGroupsFunc =
                        (_SortGroups)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnVController_sortGroups"), typeof(_SortGroups));
                }
                
                return _SortGroupsFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct RemoveObject__Args
            {
                internal IntPtr simObj;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _RemoveObject(IntPtr _this, RemoveObject__Args args);
            private static _RemoveObject _RemoveObjectFunc;
            internal static _RemoveObject RemoveObject() {
                if (_RemoveObjectFunc == null) {
                    _RemoveObjectFunc =
                        (_RemoveObject)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnVController_removeObject"), typeof(_RemoveObject));
                }
                
                return _RemoveObjectFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct AddObject__Args
            {
                internal IntPtr simObj;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _AddObject(IntPtr _this, AddObject__Args args);
            private static _AddObject _AddObjectFunc;
            internal static _AddObject AddObject() {
                if (_AddObjectFunc == null) {
                    _AddObjectFunc =
                        (_AddObject)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnVController_addObject"), typeof(_AddObject));
                }
                
                return _AddObjectFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct GetObject__Args
            {
                internal int index;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate int _GetObject(IntPtr _this, GetObject__Args args);
            private static _GetObject _GetObjectFunc;
            internal static _GetObject GetObject() {
                if (_GetObjectFunc == null) {
                    _GetObjectFunc =
                        (_GetObject)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnVController_getObject"), typeof(_GetObject));
                }
                
                return _GetObjectFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct GetCount__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate int _GetCount(IntPtr _this, GetCount__Args args);
            private static _GetCount _GetCountFunc;
            internal static _GetCount GetCount() {
                if (_GetCountFunc == null) {
                    _GetCountFunc =
                        (_GetCount)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnVController_getCount"), typeof(_GetCount));
                }
                
                return _GetCountFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct ReadTemplate__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string fileName;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            [return: MarshalAs(UnmanagedType.I1)]
            internal delegate bool _ReadTemplate(IntPtr _this, ReadTemplate__Args args);
            private static _ReadTemplate _ReadTemplateFunc;
            internal static _ReadTemplate ReadTemplate() {
                if (_ReadTemplateFunc == null) {
                    _ReadTemplateFunc =
                        (_ReadTemplate)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnVController_readTemplate"), typeof(_ReadTemplate));
                }
                
                return _ReadTemplateFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct WriteFile__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string fileName;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            [return: MarshalAs(UnmanagedType.I1)]
            internal delegate bool _WriteFile(IntPtr _this, WriteFile__Args args);
            private static _WriteFile _WriteFileFunc;
            internal static _WriteFile WriteFile() {
                if (_WriteFileFunc == null) {
                    _WriteFileFunc =
                        (_WriteFile)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnVController_writeFile"), typeof(_WriteFile));
                }
                
                return _WriteFileFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct GetDataFieldType__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string fieldName;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            
            internal delegate IntPtr _GetDataFieldType(IntPtr _this, GetDataFieldType__Args args);
            private static _GetDataFieldType _GetDataFieldTypeFunc;
            internal static _GetDataFieldType GetDataFieldType() {
                if (_GetDataFieldTypeFunc == null) {
                    _GetDataFieldTypeFunc =
                        (_GetDataFieldType)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnVController_getDataFieldType"), typeof(_GetDataFieldType));
                }
                
                return _GetDataFieldTypeFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct GetDataFieldValue__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string fieldName;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            
            internal delegate IntPtr _GetDataFieldValue(IntPtr _this, GetDataFieldValue__Args args);
            private static _GetDataFieldValue _GetDataFieldValueFunc;
            internal static _GetDataFieldValue GetDataFieldValue() {
                if (_GetDataFieldValueFunc == null) {
                    _GetDataFieldValueFunc =
                        (_GetDataFieldValue)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnVController_getDataFieldValue"), typeof(_GetDataFieldValue));
                }
                
                return _GetDataFieldValueFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct GetDataFieldName__Args
            {
                internal int index;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            
            internal delegate IntPtr _GetDataFieldName(IntPtr _this, GetDataFieldName__Args args);
            private static _GetDataFieldName _GetDataFieldNameFunc;
            internal static _GetDataFieldName GetDataFieldName() {
                if (_GetDataFieldNameFunc == null) {
                    _GetDataFieldNameFunc =
                        (_GetDataFieldName)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnVController_getDataFieldName"), typeof(_GetDataFieldName));
                }
                
                return _GetDataFieldNameFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct GetDataFieldCount__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate int _GetDataFieldCount(IntPtr _this, GetDataFieldCount__Args args);
            private static _GetDataFieldCount _GetDataFieldCountFunc;
            internal static _GetDataFieldCount GetDataFieldCount() {
                if (_GetDataFieldCountFunc == null) {
                    _GetDataFieldCountFunc =
                        (_GetDataFieldCount)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnVController_getDataFieldCount"), typeof(_GetDataFieldCount));
                }
                
                return _GetDataFieldCountFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct IsDataField__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string fieldName;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            [return: MarshalAs(UnmanagedType.I1)]
            internal delegate bool _IsDataField(IntPtr _this, IsDataField__Args args);
            private static _IsDataField _IsDataFieldFunc;
            internal static _IsDataField IsDataField() {
                if (_IsDataFieldFunc == null) {
                    _IsDataFieldFunc =
                        (_IsDataField)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnVController_isDataField"), typeof(_IsDataField));
                }
                
                return _IsDataFieldFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct SetTimeScale__Args
            {
                internal float timeScale;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _SetTimeScale(IntPtr _this, SetTimeScale__Args args);
            private static _SetTimeScale _SetTimeScaleFunc;
            internal static _SetTimeScale SetTimeScale() {
                if (_SetTimeScaleFunc == null) {
                    _SetTimeScaleFunc =
                        (_SetTimeScale)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnVController_setTimeScale"), typeof(_SetTimeScale));
                }
                
                return _SetTimeScaleFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct GetTimeScale__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate float _GetTimeScale(IntPtr _this, GetTimeScale__Args args);
            private static _GetTimeScale _GetTimeScaleFunc;
            internal static _GetTimeScale GetTimeScale() {
                if (_GetTimeScaleFunc == null) {
                    _GetTimeScaleFunc =
                        (_GetTimeScale)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnVController_getTimeScale"), typeof(_GetTimeScale));
                }
                
                return _GetTimeScaleFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct Stop__Args
            {
                [MarshalAs(UnmanagedType.I1)]
                internal bool reset;
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
                                "fnVController_stop"), typeof(_Stop));
                }
                
                return _StopFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct IsStopped__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            [return: MarshalAs(UnmanagedType.I1)]
            internal delegate bool _IsStopped(IntPtr _this, IsStopped__Args args);
            private static _IsStopped _IsStoppedFunc;
            internal static _IsStopped IsStopped() {
                if (_IsStoppedFunc == null) {
                    _IsStoppedFunc =
                        (_IsStopped)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnVController_isStopped"), typeof(_IsStopped));
                }
                
                return _IsStoppedFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct Pause__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _Pause(IntPtr _this, Pause__Args args);
            private static _Pause _PauseFunc;
            internal static _Pause Pause() {
                if (_PauseFunc == null) {
                    _PauseFunc =
                        (_Pause)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnVController_pause"), typeof(_Pause));
                }
                
                return _PauseFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct IsPaused__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            [return: MarshalAs(UnmanagedType.I1)]
            internal delegate bool _IsPaused(IntPtr _this, IsPaused__Args args);
            private static _IsPaused _IsPausedFunc;
            internal static _IsPaused IsPaused() {
                if (_IsPausedFunc == null) {
                    _IsPausedFunc =
                        (_IsPaused)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnVController_isPaused"), typeof(_IsPaused));
                }
                
                return _IsPausedFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct Step__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _Step(IntPtr _this, Step__Args args);
            private static _Step _StepFunc;
            internal static _Step Step() {
                if (_StepFunc == null) {
                    _StepFunc =
                        (_Step)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnVController_step"), typeof(_Step));
                }
                
                return _StepFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct Play__Args
            {
                internal int time;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _Play(IntPtr _this, Play__Args args);
            private static _Play _PlayFunc;
            internal static _Play Play() {
                if (_PlayFunc == null) {
                    _PlayFunc =
                        (_Play)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnVController_play"), typeof(_Play));
                }
                
                return _PlayFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct IsPlaying__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            [return: MarshalAs(UnmanagedType.I1)]
            internal delegate bool _IsPlaying(IntPtr _this, IsPlaying__Args args);
            private static _IsPlaying _IsPlayingFunc;
            internal static _IsPlaying IsPlaying() {
                if (_IsPlayingFunc == null) {
                    _IsPlayingFunc =
                        (_IsPlaying)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnVController_isPlaying"), typeof(_IsPlaying));
                }
                
                return _IsPlayingFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct Reset__Args
            {
                internal int time;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _Reset(IntPtr _this, Reset__Args args);
            private static _Reset _ResetFunc;
            internal static _Reset Reset() {
                if (_ResetFunc == null) {
                    _ResetFunc =
                        (_Reset)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnVController_reset"), typeof(_Reset));
                }
                
                return _ResetFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct Clear__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _Clear(IntPtr _this, Clear__Args args);
            private static _Clear _ClearFunc;
            internal static _Clear Clear() {
                if (_ClearFunc == null) {
                    _ClearFunc =
                        (_Clear)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnVController_clear"), typeof(_Clear));
                }
                
                return _ClearFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct ReadFile__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string fileName;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            [return: MarshalAs(UnmanagedType.I1)]
            internal delegate bool _ReadFile(IntPtr _this, ReadFile__Args args);
            private static _ReadFile _ReadFileFunc;
            internal static _ReadFile ReadFile() {
                if (_ReadFileFunc == null) {
                    _ReadFileFunc =
                        (_ReadFile)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnVController_readFile"), typeof(_ReadFile));
                }
                
                return _ReadFileFunc;
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
                                "fnVController_staticGetType"), typeof(_StaticGetType));
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
                                "fnVController_create"), typeof(_Create));
                }
                
                return _CreateFunc;
            }
        }
        #endregion

        /// <description>
        /// ( string pFieldName ) - Remove a data entry from the Data Table.
        /// </description>
        /// <param name="pFieldName">The name of the field to be removed from the Data Table.</param>
        /// <returns>No return value.</returns>
        public void RemoveDataField(string fieldName = "") {
             InternalUnsafeMethods.RemoveDataField__Args _args = new InternalUnsafeMethods.RemoveDataField__Args() {
                fieldName = fieldName,
             };
             InternalUnsafeMethods.RemoveDataField()(ObjectPtr, _args);
        }

        /// <description>
        /// ( string pFieldType, string pFieldName ) - Add a new data entry to the Data Table.
        /// </description>
        /// <param name="pFieldType">The method of evaluating the field's data.</param>
        /// <param name="pFieldName">The name of the field to be added to the Data Table.</param>
        /// <returns>No return value.</returns>
        public void AddDataField(string fieldType = "", string fieldName = "") {
             InternalUnsafeMethods.AddDataField__Args _args = new InternalUnsafeMethods.AddDataField__Args() {
                fieldType = fieldType,
                fieldName = fieldName,
             };
             InternalUnsafeMethods.AddDataField()(ObjectPtr, _args);
        }

        /// <description>
        /// ( void ) - Sort Tracks by their Labels.
        /// </description>
        /// <returns>No return value.</returns>
        public void SortTracks() {
             InternalUnsafeMethods.SortTracks__Args _args = new InternalUnsafeMethods.SortTracks__Args() {
             };
             InternalUnsafeMethods.SortTracks()(ObjectPtr, _args);
        }

        /// <description>
        /// ( void ) - Sort Groups by their Labels.
        /// </description>
        /// <returns>No return value.</returns>
        public void SortGroups() {
             InternalUnsafeMethods.SortGroups__Args _args = new InternalUnsafeMethods.SortGroups__Args() {
             };
             InternalUnsafeMethods.SortGroups()(ObjectPtr, _args);
        }

        /// <description>
        /// ( SimObject pObject ) - Remove the target object from this node.
        /// </description>
        /// <param name="pObject">The SimObjectID of the object to be removed from this node.</param>
        /// <returns>No return value.</returns>
        public void RemoveObject(SimObject simObj = null) {
             InternalUnsafeMethods.RemoveObject__Args _args = new InternalUnsafeMethods.RemoveObject__Args() {
                simObj = simObj.ObjectPtr,
             };
             InternalUnsafeMethods.RemoveObject()(ObjectPtr, _args);
        }

        /// <description>
        /// ( SimObject pObject ) - Add a child object to this node.
        /// </description>
        /// <param name="pObject">The SimObjectID of the object to be added to this node.</param>
        /// <returns>No return value.</returns>
        public void AddObject(SimObject simObj = null) {
             InternalUnsafeMethods.AddObject__Args _args = new InternalUnsafeMethods.AddObject__Args() {
                simObj = simObj.ObjectPtr,
             };
             InternalUnsafeMethods.AddObject()(ObjectPtr, _args);
        }

        /// <description>
        /// ( int pIndex ) - Get the object corresponding to the given index.
        /// </description>
        /// <param name="pIndex">The index of the object you wish to retrieve.</param>
        /// <returns>Returns the SimObjectID for the object.</returns>
        public int GetObject(int index = 0) {
             InternalUnsafeMethods.GetObject__Args _args = new InternalUnsafeMethods.GetObject__Args() {
                index = index,
             };
             int _engineResult = InternalUnsafeMethods.GetObject()(ObjectPtr, _args);
             return _engineResult;
        }

        /// <description>
        /// ( void ) - Get the number of child objects.
        /// </description>
        /// <returns>Returns the number of child objects.</returns>
        public int GetCount() {
             InternalUnsafeMethods.GetCount__Args _args = new InternalUnsafeMethods.GetCount__Args() {
             };
             int _engineResult = InternalUnsafeMethods.GetCount()(ObjectPtr, _args);
             return _engineResult;
        }

        /// <description>
        /// ( string pFileName ) - Load data from given filename.
        /// </description>
        /// <param name="pFileName">The target file to read from.</param>
        /// <returns>Returns true if the read was successful.</returns>
        public bool ReadTemplate(string fileName = "") {
             InternalUnsafeMethods.ReadTemplate__Args _args = new InternalUnsafeMethods.ReadTemplate__Args() {
                fileName = fileName,
             };
             bool _engineResult = InternalUnsafeMethods.ReadTemplate()(ObjectPtr, _args);
             return _engineResult;
        }

        /// <description>
        /// ( string pFileName ) - Save to a given filename.
        /// </description>
        /// <param name="pFileName">The target file to write to.</param>
        /// <returns>Returns true if the write was successful.</returns>
        public bool WriteFile(string fileName = "") {
             InternalUnsafeMethods.WriteFile__Args _args = new InternalUnsafeMethods.WriteFile__Args() {
                fileName = fileName,
             };
             bool _engineResult = InternalUnsafeMethods.WriteFile()(ObjectPtr, _args);
             return _engineResult;
        }

        /// <description>
        /// ( string pFieldName ) - Get the type of data for the given field.
        /// </description>
        /// <param name="pFieldName">The name of the field you wish to check.</param>
        /// <returns>Returns the data type.</returns>
        public string GetDataFieldType(string fieldName = "") {
             InternalUnsafeMethods.GetDataFieldType__Args _args = new InternalUnsafeMethods.GetDataFieldType__Args() {
                fieldName = fieldName,
             };
             IntPtr _engineResult = InternalUnsafeMethods.GetDataFieldType()(ObjectPtr, _args);
             return StringMarshal.IntPtrToUtf8String(_engineResult);
        }

        /// <description>
        /// ( string pFieldName ) - Get the evaluated data from the data field.
        /// </description>
        /// <param name="pFieldName">The name of the field you wish to evaluate.</param>
        /// <returns>Returns the evaluated data from the field.</returns>
        public string GetDataFieldValue(string fieldName = "") {
             InternalUnsafeMethods.GetDataFieldValue__Args _args = new InternalUnsafeMethods.GetDataFieldValue__Args() {
                fieldName = fieldName,
             };
             IntPtr _engineResult = InternalUnsafeMethods.GetDataFieldValue()(ObjectPtr, _args);
             return StringMarshal.IntPtrToUtf8String(_engineResult);
        }

        /// <description>
        /// ( int pIndex ) - Get the name of the field given by the passed index.
        /// </description>
        /// <param name="pIndex">The index of the data field you wish to check.</param>
        /// <returns>Returns the name of the field corresponding to the given index.</returns>
        public string GetDataFieldName(int index = 0) {
             InternalUnsafeMethods.GetDataFieldName__Args _args = new InternalUnsafeMethods.GetDataFieldName__Args() {
                index = index,
             };
             IntPtr _engineResult = InternalUnsafeMethods.GetDataFieldName()(ObjectPtr, _args);
             return StringMarshal.IntPtrToUtf8String(_engineResult);
        }

        /// <description>
        /// ( void ) - Get the number of data elements in the Data Table.
        /// </description>
        /// <returns>Returns the size of the Data Table.</returns>
        public int GetDataFieldCount() {
             InternalUnsafeMethods.GetDataFieldCount__Args _args = new InternalUnsafeMethods.GetDataFieldCount__Args() {
             };
             int _engineResult = InternalUnsafeMethods.GetDataFieldCount()(ObjectPtr, _args);
             return _engineResult;
        }

        /// <description>
        /// ( string pFieldName ) - Is the field a member of the Data Table?
        /// </description>
        /// <param name="pFieldName">The name of the dynamic field you wish to check.</param>
        /// <returns>Returns true if the field is a member of the Data Table.</returns>
        public bool IsDataField(string fieldName = "") {
             InternalUnsafeMethods.IsDataField__Args _args = new InternalUnsafeMethods.IsDataField__Args() {
                fieldName = fieldName,
             };
             bool _engineResult = InternalUnsafeMethods.IsDataField()(ObjectPtr, _args);
             return _engineResult;
        }

        /// <description>
        /// ( float pTimeScale ) - Set the playback speed. A value > 0.0 will enable the Controller to play forwards, while a value < 0.0 will play backwards. If |pTimeScale| > 1.0, then playback will be faster than normal, while |pTimeScale| < 1.0 will be slower.
        /// </description>
        /// <param name="pTimeScale">Playback speed.</param>
        /// <returns>No return value.</returns>
        public void SetTimeScale(float timeScale = 1f) {
             InternalUnsafeMethods.SetTimeScale__Args _args = new InternalUnsafeMethods.SetTimeScale__Args() {
                timeScale = timeScale,
             };
             InternalUnsafeMethods.SetTimeScale()(ObjectPtr, _args);
        }

        /// <description>
        /// ( void ) - Get the playback speed. A value > 0.0 will enable the Controller to play forwards, while a value < 0.0 will play backwards.
        /// </description>
        /// <returns>Playback Speed.</returns>
        public float GetTimeScale() {
             InternalUnsafeMethods.GetTimeScale__Args _args = new InternalUnsafeMethods.GetTimeScale__Args() {
             };
             float _engineResult = InternalUnsafeMethods.GetTimeScale()(ObjectPtr, _args);
             return _engineResult;
        }

        /// <description>
        /// ( [bool pReset] ) - Stop the sequence and optionally reset it.
        /// </description>
        /// <param name="pReset">Reset the Controller after stopping.</param>
        /// <returns>No return value.</returns>
        public void Stop(bool reset = true) {
             InternalUnsafeMethods.Stop__Args _args = new InternalUnsafeMethods.Stop__Args() {
                reset = reset,
             };
             InternalUnsafeMethods.Stop()(ObjectPtr, _args);
        }

        /// <description>
        /// ( void ) - Is the sequence currently stopped?
        /// </description>
        /// <returns>Returns true if the Controller is stopped.</returns>
        public bool IsStopped() {
             InternalUnsafeMethods.IsStopped__Args _args = new InternalUnsafeMethods.IsStopped__Args() {
             };
             bool _engineResult = InternalUnsafeMethods.IsStopped()(ObjectPtr, _args);
             return _engineResult;
        }

        /// <description>
        /// ( void ) - Pause the sequence. Playback can resume by calling VController::play().
        /// </description>
        /// <returns>No return value.</returns>
        public void Pause() {
             InternalUnsafeMethods.Pause__Args _args = new InternalUnsafeMethods.Pause__Args() {
             };
             InternalUnsafeMethods.Pause()(ObjectPtr, _args);
        }

        /// <description>
        /// ( void ) - Is the sequence currently paused?
        /// </description>
        /// <returns>Returns true if the Controller is paused.</returns>
        public bool IsPaused() {
             InternalUnsafeMethods.IsPaused__Args _args = new InternalUnsafeMethods.IsPaused__Args() {
             };
             bool _engineResult = InternalUnsafeMethods.IsPaused()(ObjectPtr, _args);
             return _engineResult;
        }

        /// <description>
        /// ( void ) - Step forward one frame.
        /// </description>
        /// <returns>No return value.</returns>
        public void Step() {
             InternalUnsafeMethods.Step__Args _args = new InternalUnsafeMethods.Step__Args() {
             };
             InternalUnsafeMethods.Step()(ObjectPtr, _args);
        }

        /// <description>
        /// ( [int pTime] ) - Play the sequence. If a value for pTime is specified, the Controller is reset and played from that time.
        /// </description>
        /// <param name="pTime">The time to start playing the sequence from.</param>
        /// <returns>No return value.</returns>
        public void Play(int time = -1) {
             InternalUnsafeMethods.Play__Args _args = new InternalUnsafeMethods.Play__Args() {
                time = time,
             };
             InternalUnsafeMethods.Play()(ObjectPtr, _args);
        }

        /// <description>
        /// ( void ) - Is the sequence currently playing?
        /// </description>
        /// <returns>Returns true if the Controller is playing.</returns>
        public bool IsPlaying() {
             InternalUnsafeMethods.IsPlaying__Args _args = new InternalUnsafeMethods.IsPlaying__Args() {
             };
             bool _engineResult = InternalUnsafeMethods.IsPlaying()(ObjectPtr, _args);
             return _engineResult;
        }

        /// <description>
        /// ( [int pTime] ) - Reset the Controller's and child object's state.
        /// </description>
        /// <param name="pTime">The target time to reset to.</param>
        /// <returns>No return value.</returns>
        public void Reset(int time = -1) {
             InternalUnsafeMethods.Reset__Args _args = new InternalUnsafeMethods.Reset__Args() {
                time = time,
             };
             InternalUnsafeMethods.Reset()(ObjectPtr, _args);
        }

        /// <description>
        /// ( void ) - Detaches and deletes all of the child objects.
        /// </description>
        /// <returns>No return value.</returns>
        public void Clear() {
             InternalUnsafeMethods.Clear__Args _args = new InternalUnsafeMethods.Clear__Args() {
             };
             InternalUnsafeMethods.Clear()(ObjectPtr, _args);
        }

        /// <description>
        /// ( string pFileName ) - Clears the object and loads the new data from the given filename.
        /// </description>
        /// <param name="pFileName">The target file to read from.</param>
        /// <returns>Returns true if the read was successful.</returns>
        public bool ReadFile(string fileName = "") {
             InternalUnsafeMethods.ReadFile__Args _args = new InternalUnsafeMethods.ReadFile__Args() {
                fileName = fileName,
             };
             bool _engineResult = InternalUnsafeMethods.ReadFile()(ObjectPtr, _args);
             return _engineResult;
        }

        /// <description>
        /// Get the type info object for the VController class.
        /// </description>
        /// <returns>The type info object for VController</returns>
        public static EngineTypeInfo StaticGetType() {
             InternalUnsafeMethods.StaticGetType__Args _args = new InternalUnsafeMethods.StaticGetType__Args() {
             };
             IntPtr _engineResult = InternalUnsafeMethods.StaticGetType()(_args);
             return new EngineTypeInfo(_engineResult);
        }


        /// <value>
        /// <description>
        /// Current position of the Controller (in milliseconds).
        /// </description>
        /// </value>
        public int Time {
            get => GenericMarshal.StringTo<int>(GetFieldValue("Time"));
            set => SetFieldValue("Time", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Total length of the sequence (in milliseconds).
        /// </description>
        /// </value>
        public int Duration {
            get => GenericMarshal.StringTo<int>(GetFieldValue("Duration"));
            set => SetFieldValue("Duration", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Speed of playback. A value > 0.0 will enable the Controller to play forwards, while a value < 0.0 will play backwards. If |TimeScale| > 1.0, then playback will be faster than normal, while |TimeScale| < 1.0 will be slower.
        /// </description>
        /// </value>
        public float TimeScale {
            get => GenericMarshal.StringTo<float>(GetFieldValue("TimeScale"));
            set => SetFieldValue("TimeScale", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Instead of stopping once playback is complete, the Controller will reset and resume play.
        /// </description>
        /// </value>
        public bool Loop {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("Loop"));
            set => SetFieldValue("Loop", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// When the sequence loops, reverse the direction of play.
        /// </description>
        /// </value>
        public bool LoopBackwards {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("LoopBackwards"));
            set => SetFieldValue("LoopBackwards", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// The number of times the sequence loops before stopping. -1 will cause the sequence to loop indefinitely.
        /// </description>
        /// </value>
        public int LoopCount {
            get => GenericMarshal.StringTo<int>(GetFieldValue("LoopCount"));
            set => SetFieldValue("LoopCount", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// When the sequence loops, delay playback by this value (in milliseconds).
        /// </description>
        /// </value>
        public int LoopDelay {
            get => GenericMarshal.StringTo<int>(GetFieldValue("LoopDelay"));
            set => SetFieldValue("LoopDelay", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// When the sequence is completed, reset the state of the Controller.
        /// </description>
        /// </value>
        public bool ResetOnCompletion {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("ResetOnCompletion"));
            set => SetFieldValue("ResetOnCompletion", GenericMarshal.ToString(value));
        }
    }
}