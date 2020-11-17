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
    public unsafe class LevelAsset : AssetBase {
        public LevelAsset(bool pRegister = false) 
            : base(pRegister) {
        }
        
        public LevelAsset(string pName, bool pRegister) 
            : this(false) {
            Name = pName;
            if (pRegister) {
                RegisterObject();
            }
        }
        
        public LevelAsset(string pName) 
            : this(pName, false) {
        }
        
        public LevelAsset(string pName, string pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(Engine.Sim.FindObject<SimObject>(pParent));
        }
        
        public LevelAsset(string pName, SimObject pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(pParent);
        }
        
        public LevelAsset(SimObject pObj) 
            : base(pObj) {
        }
        
        public LevelAsset(IntPtr pObj) 
            : base(pObj) {
        }
        
		protected override void CreateObjectPtr()
		{
			ObjectPtr = InternalUnsafeMethods.Create()(new InternalUnsafeMethods.Create__Args());
		}

        #region UnsafeNativeMethods
        new internal struct InternalUnsafeMethods {
            [StructLayout(LayoutKind.Sequential)]
            internal struct UnloadDependencies__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _UnloadDependencies(IntPtr _this, UnloadDependencies__Args args);
            private static _UnloadDependencies _UnloadDependenciesFunc;
            internal static _UnloadDependencies UnloadDependencies() {
                if (_UnloadDependenciesFunc == null) {
                    _UnloadDependenciesFunc =
                        (_UnloadDependencies)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnLevelAsset_unloadDependencies"), typeof(_UnloadDependencies));
                }
                
                return _UnloadDependenciesFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct LoadDependencies__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _LoadDependencies(IntPtr _this, LoadDependencies__Args args);
            private static _LoadDependencies _LoadDependenciesFunc;
            internal static _LoadDependencies LoadDependencies() {
                if (_LoadDependenciesFunc == null) {
                    _LoadDependenciesFunc =
                        (_LoadDependencies)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnLevelAsset_loadDependencies"), typeof(_LoadDependencies));
                }
                
                return _LoadDependenciesFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct GetDecalsPath__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            
            internal delegate IntPtr _GetDecalsPath(IntPtr _this, GetDecalsPath__Args args);
            private static _GetDecalsPath _GetDecalsPathFunc;
            internal static _GetDecalsPath GetDecalsPath() {
                if (_GetDecalsPathFunc == null) {
                    _GetDecalsPathFunc =
                        (_GetDecalsPath)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnLevelAsset_getDecalsPath"), typeof(_GetDecalsPath));
                }
                
                return _GetDecalsPathFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct GetPostFXPresetPath__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            
            internal delegate IntPtr _GetPostFXPresetPath(IntPtr _this, GetPostFXPresetPath__Args args);
            private static _GetPostFXPresetPath _GetPostFXPresetPathFunc;
            internal static _GetPostFXPresetPath GetPostFXPresetPath() {
                if (_GetPostFXPresetPathFunc == null) {
                    _GetPostFXPresetPathFunc =
                        (_GetPostFXPresetPath)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnLevelAsset_getPostFXPresetPath"), typeof(_GetPostFXPresetPath));
                }
                
                return _GetPostFXPresetPathFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct GetLevelPath__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            
            internal delegate IntPtr _GetLevelPath(IntPtr _this, GetLevelPath__Args args);
            private static _GetLevelPath _GetLevelPathFunc;
            internal static _GetLevelPath GetLevelPath() {
                if (_GetLevelPathFunc == null) {
                    _GetLevelPathFunc =
                        (_GetLevelPath)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnLevelAsset_getLevelPath"), typeof(_GetLevelPath));
                }
                
                return _GetLevelPathFunc;
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
                                "fnLevelAsset_staticGetType"), typeof(_StaticGetType));
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
                                "fnLevelAsset_create"), typeof(_Create));
                }
                
                return _CreateFunc;
            }
        }
        #endregion

        /// <description>
        /// Initiates the unloading of previously loaded asset dependencies for this level.
        /// </description>
        public void UnloadDependencies() {
             InternalUnsafeMethods.UnloadDependencies__Args _args = new InternalUnsafeMethods.UnloadDependencies__Args() {
             };
             InternalUnsafeMethods.UnloadDependencies()(ObjectPtr, _args);
        }

        /// <description>
        /// Initiates the loading of asset dependencies for this level.
        /// </description>
        public void LoadDependencies() {
             InternalUnsafeMethods.LoadDependencies__Args _args = new InternalUnsafeMethods.LoadDependencies__Args() {
             };
             InternalUnsafeMethods.LoadDependencies()(ObjectPtr, _args);
        }

        /// <description>
        /// Creates a new script asset using the targetFilePath.
        /// </description>
        /// <returns>The bool result of calling exec</returns>
        public string GetDecalsPath() {
             InternalUnsafeMethods.GetDecalsPath__Args _args = new InternalUnsafeMethods.GetDecalsPath__Args() {
             };
             IntPtr _engineResult = InternalUnsafeMethods.GetDecalsPath()(ObjectPtr, _args);
             return StringMarshal.IntPtrToUtf8String(_engineResult);
        }

        /// <description>
        /// Creates a new script asset using the targetFilePath.
        /// </description>
        /// <returns>The bool result of calling exec</returns>
        public string GetPostFXPresetPath() {
             InternalUnsafeMethods.GetPostFXPresetPath__Args _args = new InternalUnsafeMethods.GetPostFXPresetPath__Args() {
             };
             IntPtr _engineResult = InternalUnsafeMethods.GetPostFXPresetPath()(ObjectPtr, _args);
             return StringMarshal.IntPtrToUtf8String(_engineResult);
        }

        /// <description>
        /// Creates a new script asset using the targetFilePath.
        /// </description>
        /// <returns>The bool result of calling exec</returns>
        public string GetLevelPath() {
             InternalUnsafeMethods.GetLevelPath__Args _args = new InternalUnsafeMethods.GetLevelPath__Args() {
             };
             IntPtr _engineResult = InternalUnsafeMethods.GetLevelPath()(ObjectPtr, _args);
             return StringMarshal.IntPtrToUtf8String(_engineResult);
        }

        /// <description>
        /// Get the type info object for the LevelAsset class.
        /// </description>
        /// <returns>The type info object for LevelAsset</returns>
        public static EngineTypeInfo StaticGetType() {
             InternalUnsafeMethods.StaticGetType__Args _args = new InternalUnsafeMethods.StaticGetType__Args() {
             };
             IntPtr _engineResult = InternalUnsafeMethods.StaticGetType()(_args);
             return new EngineTypeInfo(_engineResult);
        }


        /// <value>
        /// <description>
        /// Path to the actual level file.
        /// </description>
        /// </value>
        public string LevelFile {
            get => GenericMarshal.StringTo<string>(GetFieldValue("LevelFile"));
            set => SetFieldValue("LevelFile", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Human-friendly name for the level.
        /// </description>
        /// </value>
        public string LevelName {
            get => GenericMarshal.StringTo<string>(GetFieldValue("LevelName"));
            set => SetFieldValue("LevelName", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Path to the image used for selection preview.
        /// </description>
        /// </value>
        public string PreviewImage {
            get => GenericMarshal.StringTo<string>(GetFieldValue("PreviewImage"));
            set => SetFieldValue("PreviewImage", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Path to the level's postFXPreset.
        /// </description>
        /// </value>
        public string PostFXPresetFile {
            get => GenericMarshal.StringTo<string>(GetFieldValue("PostFXPresetFile"));
            set => SetFieldValue("PostFXPresetFile", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Path to the decals cache file.
        /// </description>
        /// </value>
        public string DecalsFile {
            get => GenericMarshal.StringTo<string>(GetFieldValue("DecalsFile"));
            set => SetFieldValue("DecalsFile", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Path to the Forest cache file.
        /// </description>
        /// </value>
        public string ForestFile {
            get => GenericMarshal.StringTo<string>(GetFieldValue("ForestFile"));
            set => SetFieldValue("ForestFile", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Path to the navmesh file.
        /// </description>
        /// </value>
        public string NavmeshFile {
            get => GenericMarshal.StringTo<string>(GetFieldValue("NavmeshFile"));
            set => SetFieldValue("NavmeshFile", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Path to the level file with objects that were removed as part of the baking process. Loaded when the editor is loaded for ease of editing.
        /// </description>
        /// </value>
        public string EditorFile {
            get => GenericMarshal.StringTo<string>(GetFieldValue("EditorFile"));
            set => SetFieldValue("EditorFile", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Path to the level file with the objects generated as part of the baking process
        /// </description>
        /// </value>
        public string BakedSceneFile {
            get => GenericMarshal.StringTo<string>(GetFieldValue("BakedSceneFile"));
            set => SetFieldValue("BakedSceneFile", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Is this a sublevel to another Scene
        /// </description>
        /// </value>
        public bool IsSubScene {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("isSubScene"));
            set => SetFieldValue("isSubScene", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Name of the Game Mode to be used with this level
        /// </description>
        /// </value>
        public string GameModeName {
            get => GenericMarshal.StringTo<string>(GetFieldValue("gameModeName"));
            set => SetFieldValue("gameModeName", GenericMarshal.ToString(value));
        }
    }
}