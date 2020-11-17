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
    public unsafe class ModuleDefinition : SimSet {
        public ModuleDefinition(bool pRegister = false) 
            : base(pRegister) {
        }
        
        public ModuleDefinition(string pName, bool pRegister) 
            : this(false) {
            Name = pName;
            if (pRegister) {
                RegisterObject();
            }
        }
        
        public ModuleDefinition(string pName) 
            : this(pName, false) {
        }
        
        public ModuleDefinition(string pName, string pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(Engine.Sim.FindObject<SimObject>(pParent));
        }
        
        public ModuleDefinition(string pName, SimObject pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(pParent);
        }
        
        public ModuleDefinition(SimObject pObj) 
            : base(pObj) {
        }
        
        public ModuleDefinition(IntPtr pObj) 
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
                                "fnModuleDefinition_staticGetType"), typeof(_StaticGetType));
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
                                "fnModuleDefinition_create"), typeof(_Create));
                }
                
                return _CreateFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct RemoveDependency__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string pModuleId;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            [return: MarshalAs(UnmanagedType.I1)]
            internal delegate bool _RemoveDependency(IntPtr _this, RemoveDependency__Args args);
            private static _RemoveDependency _RemoveDependencyFunc;
            internal static _RemoveDependency RemoveDependency() {
                if (_RemoveDependencyFunc == null) {
                    _RemoveDependencyFunc =
                        (_RemoveDependency)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnModuleDefinition_removeDependency"), typeof(_RemoveDependency));
                }
                
                return _RemoveDependencyFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct AddDependency__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string pModuleId;
                internal uint versionId;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            [return: MarshalAs(UnmanagedType.I1)]
            internal delegate bool _AddDependency(IntPtr _this, AddDependency__Args args);
            private static _AddDependency _AddDependencyFunc;
            internal static _AddDependency AddDependency() {
                if (_AddDependencyFunc == null) {
                    _AddDependencyFunc =
                        (_AddDependency)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnModuleDefinition_addDependency"), typeof(_AddDependency));
                }
                
                return _AddDependencyFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct GetDependency__Args
            {
                internal uint dependencyIndex;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            
            internal delegate IntPtr _GetDependency(IntPtr _this, GetDependency__Args args);
            private static _GetDependency _GetDependencyFunc;
            internal static _GetDependency GetDependency() {
                if (_GetDependencyFunc == null) {
                    _GetDependencyFunc =
                        (_GetDependency)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnModuleDefinition_getDependency"), typeof(_GetDependency));
                }
                
                return _GetDependencyFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct GetDependencyCount__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate int _GetDependencyCount(IntPtr _this, GetDependencyCount__Args args);
            private static _GetDependencyCount _GetDependencyCountFunc;
            internal static _GetDependencyCount GetDependencyCount() {
                if (_GetDependencyCountFunc == null) {
                    _GetDependencyCountFunc =
                        (_GetDependencyCount)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnModuleDefinition_getDependencyCount"), typeof(_GetDependencyCount));
                }
                
                return _GetDependencyCountFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct GetModuleManager__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate int _GetModuleManager(IntPtr _this, GetModuleManager__Args args);
            private static _GetModuleManager _GetModuleManagerFunc;
            internal static _GetModuleManager GetModuleManager() {
                if (_GetModuleManagerFunc == null) {
                    _GetModuleManagerFunc =
                        (_GetModuleManager)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnModuleDefinition_getModuleManager"), typeof(_GetModuleManager));
                }
                
                return _GetModuleManagerFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct Save__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            [return: MarshalAs(UnmanagedType.I1)]
            internal delegate bool _Save(IntPtr _this, Save__Args args);
            private static _Save _SaveFunc;
            internal static _Save Save() {
                if (_SaveFunc == null) {
                    _SaveFunc =
                        (_Save)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnModuleDefinition_save"), typeof(_Save));
                }
                
                return _SaveFunc;
            }
        }
        #endregion

        /// <description>
        /// Get the type info object for the ModuleDefinition class.
        /// </description>
        /// <returns>The type info object for ModuleDefinition</returns>
        public static EngineTypeInfo StaticGetType() {
             InternalUnsafeMethods.StaticGetType__Args _args = new InternalUnsafeMethods.StaticGetType__Args() {
             };
             IntPtr _engineResult = InternalUnsafeMethods.StaticGetType()(_args);
             return new EngineTypeInfo(_engineResult);
        }

        /// <description>
        /// Removes the specified moduleId as a dependency.
        /// </description>
        /// <param name="moduleId">The module Id to remove as a dependency.</param>
        /// <returns>(bool success) Whether the module dependency was removed or not.</returns>
        public bool RemoveDependency(string pModuleId = "") {
             InternalUnsafeMethods.RemoveDependency__Args _args = new InternalUnsafeMethods.RemoveDependency__Args() {
                pModuleId = pModuleId,
             };
             bool _engineResult = InternalUnsafeMethods.RemoveDependency()(ObjectPtr, _args);
             return _engineResult;
        }

        /// <description>
        /// Adds the specified moduleId and vesionId as a dependency.
        /// </description>
        /// <param name="moduleId">The module Id to add as a dependency.</param>
        /// <param name="versionId">The version Id to add as a dependency.  Using zero indicates any version.</param>
        /// <returns>(bool success) Whether the module dependency was added or not.</returns>
        public bool AddDependency(string pModuleId = "", uint versionId = 0) {
             InternalUnsafeMethods.AddDependency__Args _args = new InternalUnsafeMethods.AddDependency__Args() {
                pModuleId = pModuleId,
                versionId = versionId,
             };
             bool _engineResult = InternalUnsafeMethods.AddDependency()(ObjectPtr, _args);
             return _engineResult;
        }

        /// <description>
        /// Gets the module dependency at the specified index.
        /// </description>
        /// <param name="dependencyIndex">The module dependency index.</param>
        /// <returns>(module - dependency) The module dependency at the specified index.</returns>
        public string GetDependency(uint dependencyIndex = 0) {
             InternalUnsafeMethods.GetDependency__Args _args = new InternalUnsafeMethods.GetDependency__Args() {
                dependencyIndex = dependencyIndex,
             };
             IntPtr _engineResult = InternalUnsafeMethods.GetDependency()(ObjectPtr, _args);
             return StringMarshal.IntPtrToUtf8String(_engineResult);
        }

        /// <description>
        /// Gets the number of module dependencies this module definition has.
        /// </description>
        /// <returns>(int count) The number of module dependencies this module definition has.</returns>
        public int GetDependencyCount() {
             InternalUnsafeMethods.GetDependencyCount__Args _args = new InternalUnsafeMethods.GetDependencyCount__Args() {
             };
             int _engineResult = InternalUnsafeMethods.GetDependencyCount()(ObjectPtr, _args);
             return _engineResult;
        }

        /// <description>
        /// Gets the module manager which this module definition is registered with (if any).
        /// </description>
        /// <returns>(moduleManager) The module manager which this module definition is registered with (zero if not registered).</returns>
        public int GetModuleManager() {
             InternalUnsafeMethods.GetModuleManager__Args _args = new InternalUnsafeMethods.GetModuleManager__Args() {
             };
             int _engineResult = InternalUnsafeMethods.GetModuleManager()(ObjectPtr, _args);
             return _engineResult;
        }

        /// <description>
        /// Saves the module definition to the file it was loaded from (if any).
        /// </description>
        /// <returns>(bool success) Whether the module definition was saved or not.</returns>
        public bool Save() {
             InternalUnsafeMethods.Save__Args _args = new InternalUnsafeMethods.Save__Args() {
             };
             bool _engineResult = InternalUnsafeMethods.Save()(ObjectPtr, _args);
             return _engineResult;
        }


        /// <value>
        /// <description>
        /// A unique string Id for the module.  It can contain any characters except a comma or semi-colon (the asset scope character).
        /// </description>
        /// </value>
        public string ModuleId {
            get => GenericMarshal.StringTo<string>(GetFieldValue("ModuleId"));
            set => SetFieldValue("ModuleId", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// The version Id.  Breaking changes to a module should use a higher version Id.
        /// </description>
        /// </value>
        public int VersionId {
            get => GenericMarshal.StringTo<int>(GetFieldValue("VersionId"));
            set => SetFieldValue("VersionId", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// The build Id.  Non-breaking changes to a module should use a higher build Id.  Optional: If not specified then the build Id will be zero.
        /// </description>
        /// </value>
        public int BuildId {
            get => GenericMarshal.StringTo<int>(GetFieldValue("BuildId"));
            set => SetFieldValue("BuildId", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Whether the module is enabled or not.  When disabled, it is effectively ignored.  Optional: If not specified then the module is enabled.
        /// </description>
        /// </value>
        public bool Enabled {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("Enabled"));
            set => SetFieldValue("Enabled", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Whether the module should be synchronized or not.  Optional: If not specified then the module is not synchronized.
        /// </description>
        /// </value>
        public bool Synchronized {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("Synchronized"));
            set => SetFieldValue("Synchronized", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Whether the module is deprecated or not.  Optional: If not specified then the module is not deprecated.
        /// </description>
        /// </value>
        public bool Deprecated {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("Deprecated"));
            set => SetFieldValue("Deprecated", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Whether the merging of a module prior to a restart is critical or not.  Optional: If not specified then the module is not merge critical.
        /// </description>
        /// </value>
        public bool CriticalMerge {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("CriticalMerge"));
            set => SetFieldValue("CriticalMerge", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Controls if when this module is loaded and the create function is executed, it will replace existing objects that share names or not.
        /// </description>
        /// </value>
        public bool OverrideExistingObjects {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("OverrideExistingObjects"));
            set => SetFieldValue("OverrideExistingObjects", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// The description typically used for debugging purposes but can be used for anything.
        /// </description>
        /// </value>
        public string Description {
            get => GenericMarshal.StringTo<string>(GetFieldValue("description"));
            set => SetFieldValue("description", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// The author of the module.
        /// </description>
        /// </value>
        public string Author {
            get => GenericMarshal.StringTo<string>(GetFieldValue("Author"));
            set => SetFieldValue("Author", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// The module group used typically when loading modules as a group.
        /// </description>
        /// </value>
        public string Group {
            get => GenericMarshal.StringTo<string>(GetFieldValue("Group"));
            set => SetFieldValue("Group", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// The module type typically used to distinguish modules during module enumeration.  Optional: If not specified then the type is empty although this can still be used as a pseudo 'global' type for instance.
        /// </description>
        /// </value>
        public string Type {
            get => GenericMarshal.StringTo<string>(GetFieldValue("type"));
            set => SetFieldValue("type", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// A comma-separated list of module Ids/VersionIds (<ModuleId>=<VersionId>,<ModuleId>=<VersionId>,etc) which this module depends upon. Optional: If not specified then no dependencies are assumed.
        /// </description>
        /// </value>
        public string Dependencies {
            get => GenericMarshal.StringTo<string>(GetFieldValue("Dependencies"));
            set => SetFieldValue("Dependencies", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// The name of the script file to compile when loading the module.  Optional.
        /// </description>
        /// </value>
        public string ScriptFile {
            get => GenericMarshal.StringTo<string>(GetFieldValue("scriptFile"));
            set => SetFieldValue("scriptFile", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// The name of the function used to create the module.  Optional: If not specified then no create function is called.
        /// </description>
        /// </value>
        public string CreateFunction {
            get => GenericMarshal.StringTo<string>(GetFieldValue("CreateFunction"));
            set => SetFieldValue("CreateFunction", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// The name of the function used to destroy the module.  Optional: If not specified then no destroy function is called.
        /// </description>
        /// </value>
        public string DestroyFunction {
            get => GenericMarshal.StringTo<string>(GetFieldValue("DestroyFunction"));
            set => SetFieldValue("DestroyFunction", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// The name of tags asset manifest file if this module contains asset tags.  Optional: If not specified then no asset tags will be found for this module.  Currently, only a single asset tag manifest should exist.
        /// </description>
        /// </value>
        public string AssetTagsManifest {
            get => GenericMarshal.StringTo<string>(GetFieldValue("AssetTagsManifest"));
            set => SetFieldValue("AssetTagsManifest", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// The scope set used to control the lifetime scope of objects that the module uses.  Objects added to this set are destroyed automatically when the module is unloaded.
        /// </description>
        /// </value>
        public int ScopeSet {
            get => GenericMarshal.StringTo<int>(GetFieldValue("ScopeSet"));
            set => SetFieldValue("ScopeSet", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// The path of the module.  This is read-only and is available only after the module has been registered by a module manager.
        /// </description>
        /// </value>
        public string ModulePath {
            get => GenericMarshal.StringTo<string>(GetFieldValue("ModulePath"));
            set => SetFieldValue("ModulePath", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// The file of the module.  This is read-only and is available only after the module has been registered by a module manager.
        /// </description>
        /// </value>
        public string ModuleFile {
            get => GenericMarshal.StringTo<string>(GetFieldValue("ModuleFile"));
            set => SetFieldValue("ModuleFile", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// The file-path of the module definition.  This is read-only and is available only after the module has been registered by a module manager.
        /// </description>
        /// </value>
        public string ModuleFilePath {
            get => GenericMarshal.StringTo<string>(GetFieldValue("ModuleFilePath"));
            set => SetFieldValue("ModuleFilePath", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// The file-path of the script-file referenced in the module definition.  This is read-only and is available only after the module has been registered by a module manager.
        /// </description>
        /// </value>
        public string ModuleScriptFilePath {
            get => GenericMarshal.StringTo<string>(GetFieldValue("ModuleScriptFilePath"));
            set => SetFieldValue("ModuleScriptFilePath", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// A unique signature of the module definition based upon its Id, version and build.  This is read-only and is available only after the module has been registered by a module manager.
        /// </description>
        /// </value>
        public string Signature {
            get => GenericMarshal.StringTo<string>(GetFieldValue("Signature"));
            set => SetFieldValue("Signature", GenericMarshal.ToString(value));
        }
    }
}