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
    public unsafe class ModuleManager : SimObject {
        public ModuleManager(bool pRegister = false) 
            : base(pRegister) {
        }
        
        public ModuleManager(string pName, bool pRegister) 
            : this(false) {
            Name = pName;
            if (pRegister) {
                RegisterObject();
            }
        }
        
        public ModuleManager(string pName) 
            : this(pName, false) {
        }
        
        public ModuleManager(string pName, string pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(Engine.Sim.FindObject<SimObject>(pParent));
        }
        
        public ModuleManager(string pName, SimObject pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(pParent);
        }
        
        public ModuleManager(SimObject pObj) 
            : base(pObj) {
        }
        
        public ModuleManager(IntPtr pObj) 
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
                                "fnModuleManager_staticGetType"), typeof(_StaticGetType));
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
                                "fnModuleManager_create"), typeof(_Create));
                }
                
                return _CreateFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct IgnoreLoadedGroups__Args
            {
                [MarshalAs(UnmanagedType.I1)]
                internal bool doIgnore;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _IgnoreLoadedGroups(IntPtr _this, IgnoreLoadedGroups__Args args);
            private static _IgnoreLoadedGroups _IgnoreLoadedGroupsFunc;
            internal static _IgnoreLoadedGroups IgnoreLoadedGroups() {
                if (_IgnoreLoadedGroupsFunc == null) {
                    _IgnoreLoadedGroupsFunc =
                        (_IgnoreLoadedGroups)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnModuleManager_ignoreLoadedGroups"), typeof(_IgnoreLoadedGroups));
                }
                
                return _IgnoreLoadedGroupsFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct RemoveListener__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string listenerObject;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _RemoveListener(IntPtr _this, RemoveListener__Args args);
            private static _RemoveListener _RemoveListenerFunc;
            internal static _RemoveListener RemoveListener() {
                if (_RemoveListenerFunc == null) {
                    _RemoveListenerFunc =
                        (_RemoveListener)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnModuleManager_removeListener"), typeof(_RemoveListener));
                }
                
                return _RemoveListenerFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct AddListener__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string listenerObject;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _AddListener(IntPtr _this, AddListener__Args args);
            private static _AddListener _AddListenerFunc;
            internal static _AddListener AddListener() {
                if (_AddListenerFunc == null) {
                    _AddListenerFunc =
                        (_AddListener)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnModuleManager_addListener"), typeof(_AddListener));
                }
                
                return _AddListenerFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct MergeModules__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string pMergeTargetPath;
                [MarshalAs(UnmanagedType.I1)]
                internal bool removeMergeDefinition;
                [MarshalAs(UnmanagedType.I1)]
                internal bool registerNewModules;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            [return: MarshalAs(UnmanagedType.I1)]
            internal delegate bool _MergeModules(IntPtr _this, MergeModules__Args args);
            private static _MergeModules _MergeModulesFunc;
            internal static _MergeModules MergeModules() {
                if (_MergeModulesFunc == null) {
                    _MergeModulesFunc =
                        (_MergeModules)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnModuleManager_mergeModules"), typeof(_MergeModules));
                }
                
                return _MergeModulesFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct CanMergeModules__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string mergeSourcePath;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            [return: MarshalAs(UnmanagedType.I1)]
            internal delegate bool _CanMergeModules(IntPtr _this, CanMergeModules__Args args);
            private static _CanMergeModules _CanMergeModulesFunc;
            internal static _CanMergeModules CanMergeModules() {
                if (_CanMergeModulesFunc == null) {
                    _CanMergeModulesFunc =
                        (_CanMergeModules)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnModuleManager_canMergeModules"), typeof(_CanMergeModules));
                }
                
                return _CanMergeModulesFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct IsModuleMergeAvailable__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            [return: MarshalAs(UnmanagedType.I1)]
            internal delegate bool _IsModuleMergeAvailable(IntPtr _this, IsModuleMergeAvailable__Args args);
            private static _IsModuleMergeAvailable _IsModuleMergeAvailableFunc;
            internal static _IsModuleMergeAvailable IsModuleMergeAvailable() {
                if (_IsModuleMergeAvailableFunc == null) {
                    _IsModuleMergeAvailableFunc =
                        (_IsModuleMergeAvailable)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnModuleManager_isModuleMergeAvailable"), typeof(_IsModuleMergeAvailable));
                }
                
                return _IsModuleMergeAvailableFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct SynchronizeDependencies__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string rootModuleDefinition;
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string pTargetDependencyFolder;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            [return: MarshalAs(UnmanagedType.I1)]
            internal delegate bool _SynchronizeDependencies(IntPtr _this, SynchronizeDependencies__Args args);
            private static _SynchronizeDependencies _SynchronizeDependenciesFunc;
            internal static _SynchronizeDependencies SynchronizeDependencies() {
                if (_SynchronizeDependenciesFunc == null) {
                    _SynchronizeDependenciesFunc =
                        (_SynchronizeDependencies)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnModuleManager_synchronizeDependencies"), typeof(_SynchronizeDependencies));
                }
                
                return _SynchronizeDependenciesFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct RenameModule__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string sourceModuleDefinition;
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string pNewModuleName;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            [return: MarshalAs(UnmanagedType.I1)]
            internal delegate bool _RenameModule(IntPtr _this, RenameModule__Args args);
            private static _RenameModule _RenameModuleFunc;
            internal static _RenameModule RenameModule() {
                if (_RenameModuleFunc == null) {
                    _RenameModuleFunc =
                        (_RenameModule)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnModuleManager_renameModule"), typeof(_RenameModule));
                }
                
                return _RenameModuleFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct CopyModule__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string sourceModuleDefinition;
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string pTargetModuleId;
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string pTargetPath;
                [MarshalAs(UnmanagedType.I1)]
                internal bool useVersionPathing;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            
            internal delegate IntPtr _CopyModule(IntPtr _this, CopyModule__Args args);
            private static _CopyModule _CopyModuleFunc;
            internal static _CopyModule CopyModule() {
                if (_CopyModuleFunc == null) {
                    _CopyModuleFunc =
                        (_CopyModule)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnModuleManager_copyModule"), typeof(_CopyModule));
                }
                
                return _CopyModuleFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct FindModuleTypes__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string pModuleType;
                [MarshalAs(UnmanagedType.I1)]
                internal bool loadedOnly;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            
            internal delegate IntPtr _FindModuleTypes(IntPtr _this, FindModuleTypes__Args args);
            private static _FindModuleTypes _FindModuleTypesFunc;
            internal static _FindModuleTypes FindModuleTypes() {
                if (_FindModuleTypesFunc == null) {
                    _FindModuleTypesFunc =
                        (_FindModuleTypes)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnModuleManager_findModuleTypes"), typeof(_FindModuleTypes));
                }
                
                return _FindModuleTypesFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct FindModules__Args
            {
                [MarshalAs(UnmanagedType.I1)]
                internal bool loadedOnly;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            
            internal delegate IntPtr _FindModules(IntPtr _this, FindModules__Args args);
            private static _FindModules _FindModulesFunc;
            internal static _FindModules FindModules() {
                if (_FindModulesFunc == null) {
                    _FindModulesFunc =
                        (_FindModules)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnModuleManager_findModules"), typeof(_FindModules));
                }
                
                return _FindModulesFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct FindModule__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string pModuleId;
                internal uint pVersionId;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            
            internal delegate IntPtr _FindModule(IntPtr _this, FindModule__Args args);
            private static _FindModule _FindModuleFunc;
            internal static _FindModule FindModule() {
                if (_FindModuleFunc == null) {
                    _FindModuleFunc =
                        (_FindModule)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnModuleManager_findModule"), typeof(_FindModule));
                }
                
                return _FindModuleFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct UnloadExplicit__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string pModuleId;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            [return: MarshalAs(UnmanagedType.I1)]
            internal delegate bool _UnloadExplicit(IntPtr _this, UnloadExplicit__Args args);
            private static _UnloadExplicit _UnloadExplicitFunc;
            internal static _UnloadExplicit UnloadExplicit() {
                if (_UnloadExplicitFunc == null) {
                    _UnloadExplicitFunc =
                        (_UnloadExplicit)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnModuleManager_unloadExplicit"), typeof(_UnloadExplicit));
                }
                
                return _UnloadExplicitFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct LoadExplicit__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string pModuleId;
                internal int pVersionId;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            [return: MarshalAs(UnmanagedType.I1)]
            internal delegate bool _LoadExplicit(IntPtr _this, LoadExplicit__Args args);
            private static _LoadExplicit _LoadExplicitFunc;
            internal static _LoadExplicit LoadExplicit() {
                if (_LoadExplicitFunc == null) {
                    _LoadExplicitFunc =
                        (_LoadExplicit)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnModuleManager_loadExplicit"), typeof(_LoadExplicit));
                }
                
                return _LoadExplicitFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct UnloadGroup__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string pModuleGroup;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            [return: MarshalAs(UnmanagedType.I1)]
            internal delegate bool _UnloadGroup(IntPtr _this, UnloadGroup__Args args);
            private static _UnloadGroup _UnloadGroupFunc;
            internal static _UnloadGroup UnloadGroup() {
                if (_UnloadGroupFunc == null) {
                    _UnloadGroupFunc =
                        (_UnloadGroup)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnModuleManager_unloadGroup"), typeof(_UnloadGroup));
                }
                
                return _UnloadGroupFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct LoadGroup__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string pModuleGroup;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            [return: MarshalAs(UnmanagedType.I1)]
            internal delegate bool _LoadGroup(IntPtr _this, LoadGroup__Args args);
            private static _LoadGroup _LoadGroupFunc;
            internal static _LoadGroup LoadGroup() {
                if (_LoadGroupFunc == null) {
                    _LoadGroupFunc =
                        (_LoadGroup)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnModuleManager_loadGroup"), typeof(_LoadGroup));
                }
                
                return _LoadGroupFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct UnregisterModule__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string pModuleId;
                [MarshalAs(UnmanagedType.I1)]
                internal bool versionId;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            [return: MarshalAs(UnmanagedType.I1)]
            internal delegate bool _UnregisterModule(IntPtr _this, UnregisterModule__Args args);
            private static _UnregisterModule _UnregisterModuleFunc;
            internal static _UnregisterModule UnregisterModule() {
                if (_UnregisterModuleFunc == null) {
                    _UnregisterModuleFunc =
                        (_UnregisterModule)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnModuleManager_unregisterModule"), typeof(_UnregisterModule));
                }
                
                return _UnregisterModuleFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct RegisterModule__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string pModulePath;
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string pModuleFile;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            [return: MarshalAs(UnmanagedType.I1)]
            internal delegate bool _RegisterModule(IntPtr _this, RegisterModule__Args args);
            private static _RegisterModule _RegisterModuleFunc;
            internal static _RegisterModule RegisterModule() {
                if (_RegisterModuleFunc == null) {
                    _RegisterModuleFunc =
                        (_RegisterModule)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnModuleManager_registerModule"), typeof(_RegisterModule));
                }
                
                return _RegisterModuleFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct ScanModules__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string pRootPath;
                [MarshalAs(UnmanagedType.I1)]
                internal bool rootOnly;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            [return: MarshalAs(UnmanagedType.I1)]
            internal delegate bool _ScanModules(IntPtr _this, ScanModules__Args args);
            private static _ScanModules _ScanModulesFunc;
            internal static _ScanModules ScanModules() {
                if (_ScanModulesFunc == null) {
                    _ScanModulesFunc =
                        (_ScanModules)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnModuleManager_scanModules"), typeof(_ScanModules));
                }
                
                return _ScanModulesFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct SetModuleExtension__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string moduleExtension;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            [return: MarshalAs(UnmanagedType.I1)]
            internal delegate bool _SetModuleExtension(IntPtr _this, SetModuleExtension__Args args);
            private static _SetModuleExtension _SetModuleExtensionFunc;
            internal static _SetModuleExtension SetModuleExtension() {
                if (_SetModuleExtensionFunc == null) {
                    _SetModuleExtensionFunc =
                        (_SetModuleExtension)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnModuleManager_setModuleExtension"), typeof(_SetModuleExtension));
                }
                
                return _SetModuleExtensionFunc;
            }
        }
        #endregion

        /// <description>
        /// Get the type info object for the ModuleManager class.
        /// </description>
        /// <returns>The type info object for ModuleManager</returns>
        public static EngineTypeInfo StaticGetType() {
             InternalUnsafeMethods.StaticGetType__Args _args = new InternalUnsafeMethods.StaticGetType__Args() {
             };
             IntPtr _engineResult = InternalUnsafeMethods.StaticGetType()(_args);
             return new EngineTypeInfo(_engineResult);
        }

        /// <description>
        /// Sets if the Module Manager should ingore laoded groups.
        /// </description>
        /// <param name="doIgnore">Whether we should or should not ignore loaded groups.</param>
        /// <returns>No return value.</returns>
        public void IgnoreLoadedGroups(bool doIgnore = false) {
             InternalUnsafeMethods.IgnoreLoadedGroups__Args _args = new InternalUnsafeMethods.IgnoreLoadedGroups__Args() {
                doIgnore = doIgnore,
             };
             InternalUnsafeMethods.IgnoreLoadedGroups()(ObjectPtr, _args);
        }

        /// <description>
        /// Unregisters the specified object as a listener for module notifications.
        /// </description>
        /// <param name="listenerObject">The object to stop receiving module notifications.</param>
        /// <returns>No return value.</returns>
        public void RemoveListener(string listenerObject = "") {
             InternalUnsafeMethods.RemoveListener__Args _args = new InternalUnsafeMethods.RemoveListener__Args() {
                listenerObject = listenerObject,
             };
             InternalUnsafeMethods.RemoveListener()(ObjectPtr, _args);
        }

        /// <description>
        /// Registers the specified object as a listener for module notifications.
        /// </description>
        /// <param name="listenerObject">The object to start receiving module notifications.</param>
        /// <returns>No return value.</returns>
        public void AddListener(string listenerObject = "") {
             InternalUnsafeMethods.AddListener__Args _args = new InternalUnsafeMethods.AddListener__Args() {
                listenerObject = listenerObject,
             };
             InternalUnsafeMethods.AddListener()(ObjectPtr, _args);
        }

        /// <description>
        /// Performs a module merge into the selected target path.
        /// </description>
        /// <param name="mergeTargetPath">The path where modules will be merged into.</param>
        /// <param name="removeMergeDefinition">Whether to remove any merge definition found or not if merge is successful.</param>
        /// <param name="registerNewModules">Whether new (not replaced or updated) modules should be registered or not.</param>
        /// <returns>Whether the module merge was successful or not.Failure here could result in a corrupt module state.Reinstall is recommended or at least advised to the user is recommended.</returns>
        public bool MergeModules(string pMergeTargetPath = "", bool removeMergeDefinition = false, bool registerNewModules = false) {
             InternalUnsafeMethods.MergeModules__Args _args = new InternalUnsafeMethods.MergeModules__Args() {
                pMergeTargetPath = pMergeTargetPath,
                removeMergeDefinition = removeMergeDefinition,
                registerNewModules = registerNewModules,
             };
             bool _engineResult = InternalUnsafeMethods.MergeModules()(ObjectPtr, _args);
             return _engineResult;
        }

        /// <description>
        /// Checks whether a module merge using the modules in the source path can current happen or not.
        /// </description>
        /// <param name="mergeSourcePath">The path where modules to be merged are located.</param>
        /// <returns>Whether a module merge using the modules in the source path can current happen or not.</returns>
        public bool CanMergeModules(string mergeSourcePath = "") {
             InternalUnsafeMethods.CanMergeModules__Args _args = new InternalUnsafeMethods.CanMergeModules__Args() {
                mergeSourcePath = mergeSourcePath,
             };
             bool _engineResult = InternalUnsafeMethods.CanMergeModules()(ObjectPtr, _args);
             return _engineResult;
        }

        /// <description>
        /// Checks whether a module merge definition file is available or not.
        /// </description>
        /// <returns>Whether a module merge definition file is available or not.</returns>
        public bool IsModuleMergeAvailable() {
             InternalUnsafeMethods.IsModuleMergeAvailable__Args _args = new InternalUnsafeMethods.IsModuleMergeAvailable__Args() {
             };
             bool _engineResult = InternalUnsafeMethods.IsModuleMergeAvailable()(ObjectPtr, _args);
             return _engineResult;
        }

        /// <description>
        /// Synchronize the module dependencies of a module definition to a target dependency folder.
        /// </description>
        /// <param name="rootModuleDefinition">The module definition used to determine dependencies.</param>
        /// <param name="targetDependencyPath">The target dependency folder to copy dependencies to.</param>
        /// <returns>Whether the module dependencies were synchronized correctly or not.</returns>
        public bool SynchronizeDependencies(string rootModuleDefinition = "", string pTargetDependencyFolder = "") {
             InternalUnsafeMethods.SynchronizeDependencies__Args _args = new InternalUnsafeMethods.SynchronizeDependencies__Args() {
                rootModuleDefinition = rootModuleDefinition,
                pTargetDependencyFolder = pTargetDependencyFolder,
             };
             bool _engineResult = InternalUnsafeMethods.SynchronizeDependencies()(ObjectPtr, _args);
             return _engineResult;
        }

        /// <description>
        /// Rename a module.
        /// </description>
        /// <param name="sourceModuleDefinition">The module definition to rename.</param>
        /// <param name="pNewModuleName">The new name the module should have.</param>
        /// <returns>Weither the rename was successful or not.</returns>
        public bool RenameModule(string sourceModuleDefinition = "", string pNewModuleName = "") {
             InternalUnsafeMethods.RenameModule__Args _args = new InternalUnsafeMethods.RenameModule__Args() {
                sourceModuleDefinition = sourceModuleDefinition,
                pNewModuleName = pNewModuleName,
             };
             bool _engineResult = InternalUnsafeMethods.RenameModule()(ObjectPtr, _args);
             return _engineResult;
        }

        /// <description>
        /// Copy the module to a new location with a new module Id.
        /// </description>
        /// <param name="sourceModuleDefinition">The module definition to copy.</param>
        /// <param name="targetModuleId">The module Id to rename the copied module to including all references to the source module Id.It is valid to specifiy the source module Id to produce an identical copy.</param>
        /// <param name="targetPath">The target path to copy the module to.Addition folders will be created depending on whether 'useVersionPathing' is used or not.</param>
        /// <param name="useVersionPathing">Whether to add a '/targetModuleId/versionId' folder to the target path or not.This allows copying multiple versions of the same module Id.</param>
        /// <returns>The new module definition file if copy was successful or NULL if not.</returns>
        public string CopyModule(string sourceModuleDefinition = "", string pTargetModuleId = "", string pTargetPath = "", bool useVersionPathing = false) {
             InternalUnsafeMethods.CopyModule__Args _args = new InternalUnsafeMethods.CopyModule__Args() {
                sourceModuleDefinition = sourceModuleDefinition,
                pTargetModuleId = pTargetModuleId,
                pTargetPath = pTargetPath,
                useVersionPathing = useVersionPathing,
             };
             IntPtr _engineResult = InternalUnsafeMethods.CopyModule()(ObjectPtr, _args);
             return StringMarshal.IntPtrToUtf8String(_engineResult);
        }

        /// <description>
        /// Find the modules registered with the specified module type.
        /// </description>
        /// <param name="moduleType">The module type to search for.</param>
        /// <param name="loadedOnly">Whether to return only modules that are loaded or not.</param>
        /// <returns>A list of space - separated module definition object Ids.</returns>
        public string FindModuleTypes(string pModuleType = "", bool loadedOnly = false) {
             InternalUnsafeMethods.FindModuleTypes__Args _args = new InternalUnsafeMethods.FindModuleTypes__Args() {
                pModuleType = pModuleType,
                loadedOnly = loadedOnly,
             };
             IntPtr _engineResult = InternalUnsafeMethods.FindModuleTypes()(ObjectPtr, _args);
             return StringMarshal.IntPtrToUtf8String(_engineResult);
        }

        /// <description>
        /// Find all the modules registered with the specified loaded state.
        /// </description>
        /// <param name="loadedOnly">Whether to return only modules that are loaded or not.</param>
        /// <returns>A list of space - separated module definition object Ids.</returns>
        public string FindModules(bool loadedOnly = false) {
             InternalUnsafeMethods.FindModules__Args _args = new InternalUnsafeMethods.FindModules__Args() {
                loadedOnly = loadedOnly,
             };
             IntPtr _engineResult = InternalUnsafeMethods.FindModules()(ObjectPtr, _args);
             return StringMarshal.IntPtrToUtf8String(_engineResult);
        }

        /// <description>
        /// Find the specific module Id optionally at the specified version Id.
        /// </description>
        /// <param name="moduleId">The module Id to find.</param>
        /// <param name="versionId">The version Id to find.</param>
        /// <returns>The module definition object or NULL if not found.</returns>
        public string FindModule(string pModuleId = "", uint pVersionId = 1) {
             InternalUnsafeMethods.FindModule__Args _args = new InternalUnsafeMethods.FindModule__Args() {
                pModuleId = pModuleId,
                pVersionId = pVersionId,
             };
             IntPtr _engineResult = InternalUnsafeMethods.FindModule()(ObjectPtr, _args);
             return StringMarshal.IntPtrToUtf8String(_engineResult);
        }

        /// <description>
        /// Unload the specified module explicitly.
        /// </description>
        /// <param name="moduleId">The module Id to unload.</param>
        /// <returns>Whether the module Id was unloaded or not.</returns>
        public bool UnloadExplicit(string pModuleId = "") {
             InternalUnsafeMethods.UnloadExplicit__Args _args = new InternalUnsafeMethods.UnloadExplicit__Args() {
                pModuleId = pModuleId,
             };
             bool _engineResult = InternalUnsafeMethods.UnloadExplicit()(ObjectPtr, _args);
             return _engineResult;
        }

        /// <description>
        /// Load the specified module explicitly.
        /// </description>
        /// <param name="moduleId">The module Id to load.</param>
        /// <param name="versionId">The version Id to load.Optional:  Will load the latest version.</param>
        /// <returns>Whether the module Id was loaded or not.</returns>
        public bool LoadExplicit(string pModuleId = "", int pVersionId = -1) {
             InternalUnsafeMethods.LoadExplicit__Args _args = new InternalUnsafeMethods.LoadExplicit__Args() {
                pModuleId = pModuleId,
                pVersionId = pVersionId,
             };
             bool _engineResult = InternalUnsafeMethods.LoadExplicit()(ObjectPtr, _args);
             return _engineResult;
        }

        /// <description>
        /// Unload the specified module group.
        /// </description>
        /// <param name="moduleGroup">The module group to unload.</param>
        /// <returns>Whether the module group was unloaded or not.</returns>
        public bool UnloadGroup(string pModuleGroup = "") {
             InternalUnsafeMethods.UnloadGroup__Args _args = new InternalUnsafeMethods.UnloadGroup__Args() {
                pModuleGroup = pModuleGroup,
             };
             bool _engineResult = InternalUnsafeMethods.UnloadGroup()(ObjectPtr, _args);
             return _engineResult;
        }

        /// <description>
        /// Load the specified module group.
        /// </description>
        /// <param name="moduleGroup">The module group to load.</param>
        /// <returns>Whether the module group was loaded or not.</returns>
        public bool LoadGroup(string pModuleGroup = "") {
             InternalUnsafeMethods.LoadGroup__Args _args = new InternalUnsafeMethods.LoadGroup__Args() {
                pModuleGroup = pModuleGroup,
             };
             bool _engineResult = InternalUnsafeMethods.LoadGroup()(ObjectPtr, _args);
             return _engineResult;
        }

        /// <description>
        /// Unregister the specified module.
        /// </description>
        /// <param name="moduleId">The module Id to unregister.</param>
        /// <param name="versionId">The version Id to unregister.</param>
        /// <returns>Whether the module was unregister or not.</returns>
        public bool UnregisterModule(string pModuleId = "", bool versionId = false) {
             InternalUnsafeMethods.UnregisterModule__Args _args = new InternalUnsafeMethods.UnregisterModule__Args() {
                pModuleId = pModuleId,
                versionId = versionId,
             };
             bool _engineResult = InternalUnsafeMethods.UnregisterModule()(ObjectPtr, _args);
             return _engineResult;
        }

        /// <description>
        /// Register the specified module.
        /// </description>
        /// <param name="moduleId">The module Id to register.</param>
        /// <param name="versionId">The version Id to register.</param>
        /// <returns>Whether the module was registered or not.</returns>
        public bool RegisterModule(string pModulePath = "", string pModuleFile = "") {
             InternalUnsafeMethods.RegisterModule__Args _args = new InternalUnsafeMethods.RegisterModule__Args() {
                pModulePath = pModulePath,
                pModuleFile = pModuleFile,
             };
             bool _engineResult = InternalUnsafeMethods.RegisterModule()(ObjectPtr, _args);
             return _engineResult;
        }

        /// <description>
        /// Scans for modules which are sub-directories of the specified path.
        /// </description>
        /// <param name="moduleRootPath">The root directory to scan for sub - directories containing modules.</param>
        /// <param name="rootOnly[Optional]">- Specifies whether to only scan the root path or not when searching for modules.</param>
        /// <returns>Whether the scan was successful or not.A successful scan can still find zero modules.</returns>
        public bool ScanModules(string pRootPath = "", bool rootOnly = false) {
             InternalUnsafeMethods.ScanModules__Args _args = new InternalUnsafeMethods.ScanModules__Args() {
                pRootPath = pRootPath,
                rootOnly = rootOnly,
             };
             bool _engineResult = InternalUnsafeMethods.ScanModules()(ObjectPtr, _args);
             return _engineResult;
        }

        /// <description>
        /// Set the module extension used to scan for modules.  The default is 'module'.
        /// </description>
        /// <param name="moduleExtension">The module extension used to scan for modules.Do not use a period character.</param>
        /// <returns>Whether setting the module extension was successful or not.</returns>
        public bool SetModuleExtension(string moduleExtension = "") {
             InternalUnsafeMethods.SetModuleExtension__Args _args = new InternalUnsafeMethods.SetModuleExtension__Args() {
                moduleExtension = moduleExtension,
             };
             bool _engineResult = InternalUnsafeMethods.SetModuleExtension()(ObjectPtr, _args);
             return _engineResult;
        }


        /// <value>
        /// <description>
        /// Whether the module manager enforces any dependencies on module definitions it discovers or not.
        /// </description>
        /// </value>
        public bool EnforceDependencies {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("EnforceDependencies"));
            set => SetFieldValue("EnforceDependencies", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Whether the module manager echos extra information to the console or not.
        /// </description>
        /// </value>
        public bool EchoInfo {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("EchoInfo"));
            set => SetFieldValue("EchoInfo", GenericMarshal.ToString(value));
        }
    }
}