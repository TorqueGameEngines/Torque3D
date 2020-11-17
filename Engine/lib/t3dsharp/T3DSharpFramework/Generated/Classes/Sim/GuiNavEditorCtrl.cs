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
    /// <summary>GUI tool that makes up the Navigation Editor</summary>
    /// <description>
    /// Editor use only.
    /// </description>
    public unsafe class GuiNavEditorCtrl : EditTSCtrl {
        public GuiNavEditorCtrl(bool pRegister = false) 
            : base(pRegister) {
        }
        
        public GuiNavEditorCtrl(string pName, bool pRegister) 
            : this(false) {
            Name = pName;
            if (pRegister) {
                RegisterObject();
            }
        }
        
        public GuiNavEditorCtrl(string pName) 
            : this(pName, false) {
        }
        
        public GuiNavEditorCtrl(string pName, string pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(Engine.Sim.FindObject<SimObject>(pParent));
        }
        
        public GuiNavEditorCtrl(string pName, SimObject pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(pParent);
        }
        
        public GuiNavEditorCtrl(SimObject pObj) 
            : base(pObj) {
        }
        
        public GuiNavEditorCtrl(IntPtr pObj) 
            : base(pObj) {
        }
        
		protected override void CreateObjectPtr()
		{
			ObjectPtr = InternalUnsafeMethods.Create()(new InternalUnsafeMethods.Create__Args());
		}

        #region UnsafeNativeMethods
        new internal struct InternalUnsafeMethods {
            [StructLayout(LayoutKind.Sequential)]
            internal struct SetMode__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string mode;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _SetMode(IntPtr _this, SetMode__Args args);
            private static _SetMode _SetModeFunc;
            internal static _SetMode SetMode() {
                if (_SetModeFunc == null) {
                    _SetModeFunc =
                        (_SetMode)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnGuiNavEditorCtrl_setMode"), typeof(_SetMode));
                }
                
                return _SetModeFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct GetMode__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            
            internal delegate IntPtr _GetMode(IntPtr _this, GetMode__Args args);
            private static _GetMode _GetModeFunc;
            internal static _GetMode GetMode() {
                if (_GetModeFunc == null) {
                    _GetModeFunc =
                        (_GetMode)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnGuiNavEditorCtrl_getMode"), typeof(_GetMode));
                }
                
                return _GetModeFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct SpawnPlayer__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _SpawnPlayer(IntPtr _this, SpawnPlayer__Args args);
            private static _SpawnPlayer _SpawnPlayerFunc;
            internal static _SpawnPlayer SpawnPlayer() {
                if (_SpawnPlayerFunc == null) {
                    _SpawnPlayerFunc =
                        (_SpawnPlayer)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnGuiNavEditorCtrl_spawnPlayer"), typeof(_SpawnPlayer));
                }
                
                return _SpawnPlayerFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct BuildTile__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _BuildTile(IntPtr _this, BuildTile__Args args);
            private static _BuildTile _BuildTileFunc;
            internal static _BuildTile BuildTile() {
                if (_BuildTileFunc == null) {
                    _BuildTileFunc =
                        (_BuildTile)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnGuiNavEditorCtrl_buildTile"), typeof(_BuildTile));
                }
                
                return _BuildTileFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct SetLinkFlags__Args
            {
                internal uint flags;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _SetLinkFlags(IntPtr _this, SetLinkFlags__Args args);
            private static _SetLinkFlags _SetLinkFlagsFunc;
            internal static _SetLinkFlags SetLinkFlags() {
                if (_SetLinkFlagsFunc == null) {
                    _SetLinkFlagsFunc =
                        (_SetLinkFlags)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnGuiNavEditorCtrl_setLinkFlags"), typeof(_SetLinkFlags));
                }
                
                return _SetLinkFlagsFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct DeleteLink__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _DeleteLink(IntPtr _this, DeleteLink__Args args);
            private static _DeleteLink _DeleteLinkFunc;
            internal static _DeleteLink DeleteLink() {
                if (_DeleteLinkFunc == null) {
                    _DeleteLinkFunc =
                        (_DeleteLink)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnGuiNavEditorCtrl_deleteLink"), typeof(_DeleteLink));
                }
                
                return _DeleteLinkFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct Deselect__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _Deselect(IntPtr _this, Deselect__Args args);
            private static _Deselect _DeselectFunc;
            internal static _Deselect Deselect() {
                if (_DeselectFunc == null) {
                    _DeselectFunc =
                        (_Deselect)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnGuiNavEditorCtrl_deselect"), typeof(_Deselect));
                }
                
                return _DeselectFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct GetPlayer__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate int _GetPlayer(IntPtr _this, GetPlayer__Args args);
            private static _GetPlayer _GetPlayerFunc;
            internal static _GetPlayer GetPlayer() {
                if (_GetPlayerFunc == null) {
                    _GetPlayerFunc =
                        (_GetPlayer)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnGuiNavEditorCtrl_getPlayer"), typeof(_GetPlayer));
                }
                
                return _GetPlayerFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct GetMesh__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate int _GetMesh(IntPtr _this, GetMesh__Args args);
            private static _GetMesh _GetMeshFunc;
            internal static _GetMesh GetMesh() {
                if (_GetMeshFunc == null) {
                    _GetMeshFunc =
                        (_GetMesh)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnGuiNavEditorCtrl_getMesh"), typeof(_GetMesh));
                }
                
                return _GetMeshFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct SelectMesh__Args
            {
                internal int id;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _SelectMesh(IntPtr _this, SelectMesh__Args args);
            private static _SelectMesh _SelectMeshFunc;
            internal static _SelectMesh SelectMesh() {
                if (_SelectMeshFunc == null) {
                    _SelectMeshFunc =
                        (_SelectMesh)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnGuiNavEditorCtrl_selectMesh"), typeof(_SelectMesh));
                }
                
                return _SelectMeshFunc;
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
                                "fnGuiNavEditorCtrl_staticGetType"), typeof(_StaticGetType));
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
                                "fnGuiNavEditorCtrl_create"), typeof(_Create));
                }
                
                return _CreateFunc;
            }
        }
        #endregion

        /// <description>
        /// setMode(String mode)
        /// </description>
        public void SetMode(string mode) {
             InternalUnsafeMethods.SetMode__Args _args = new InternalUnsafeMethods.SetMode__Args() {
                mode = mode,
             };
             InternalUnsafeMethods.SetMode()(ObjectPtr, _args);
        }

        /// 
        public string GetMode() {
             InternalUnsafeMethods.GetMode__Args _args = new InternalUnsafeMethods.GetMode__Args() {
             };
             IntPtr _engineResult = InternalUnsafeMethods.GetMode()(ObjectPtr, _args);
             return StringMarshal.IntPtrToUtf8String(_engineResult);
        }

        /// <summary>Spawn an AIPlayer at the centre of the screen.</summary>
        public void SpawnPlayer() {
             InternalUnsafeMethods.SpawnPlayer__Args _args = new InternalUnsafeMethods.SpawnPlayer__Args() {
             };
             InternalUnsafeMethods.SpawnPlayer()(ObjectPtr, _args);
        }

        /// <summary>Build the currently selected tile.</summary>
        public void BuildTile() {
             InternalUnsafeMethods.BuildTile__Args _args = new InternalUnsafeMethods.BuildTile__Args() {
             };
             InternalUnsafeMethods.BuildTile()(ObjectPtr, _args);
        }

        /// 
        public void SetLinkFlags(uint flags) {
             InternalUnsafeMethods.SetLinkFlags__Args _args = new InternalUnsafeMethods.SetLinkFlags__Args() {
                flags = flags,
             };
             InternalUnsafeMethods.SetLinkFlags()(ObjectPtr, _args);
        }

        /// <summary>Delete the currently selected link.</summary>
        public void DeleteLink() {
             InternalUnsafeMethods.DeleteLink__Args _args = new InternalUnsafeMethods.DeleteLink__Args() {
             };
             InternalUnsafeMethods.DeleteLink()(ObjectPtr, _args);
        }

        /// <summary>Deselect whatever is currently selected in the editor.</summary>
        public void Deselect() {
             InternalUnsafeMethods.Deselect__Args _args = new InternalUnsafeMethods.Deselect__Args() {
             };
             InternalUnsafeMethods.Deselect()(ObjectPtr, _args);
        }

        /// <summary>Select a NavMesh object.</summary>
        public int GetPlayer() {
             InternalUnsafeMethods.GetPlayer__Args _args = new InternalUnsafeMethods.GetPlayer__Args() {
             };
             int _engineResult = InternalUnsafeMethods.GetPlayer()(ObjectPtr, _args);
             return _engineResult;
        }

        /// <summary>Select a NavMesh object.</summary>
        public int GetMesh() {
             InternalUnsafeMethods.GetMesh__Args _args = new InternalUnsafeMethods.GetMesh__Args() {
             };
             int _engineResult = InternalUnsafeMethods.GetMesh()(ObjectPtr, _args);
             return _engineResult;
        }

        /// <summary>Select a NavMesh object.</summary>
        public void SelectMesh(int id) {
             InternalUnsafeMethods.SelectMesh__Args _args = new InternalUnsafeMethods.SelectMesh__Args() {
                id = id,
             };
             InternalUnsafeMethods.SelectMesh()(ObjectPtr, _args);
        }

        /// <description>
        /// Get the type info object for the GuiNavEditorCtrl class.
        /// </description>
        /// <returns>The type info object for GuiNavEditorCtrl</returns>
        public static EngineTypeInfo StaticGetType() {
             InternalUnsafeMethods.StaticGetType__Args _args = new InternalUnsafeMethods.StaticGetType__Args() {
             };
             IntPtr _engineResult = InternalUnsafeMethods.StaticGetType()(_args);
             return new EngineTypeInfo(_engineResult);
        }


        /// <value>
        /// 
        /// </value>
        public bool IsDirty {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("isDirty"));
            set => SetFieldValue("isDirty", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Class of object to spawn in test mode.
        /// </description>
        /// </value>
        public string SpawnClass {
            get => GenericMarshal.StringTo<string>(GetFieldValue("spawnClass"));
            set => SetFieldValue("spawnClass", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Datablock to give new objects in test mode.
        /// </description>
        /// </value>
        public string SpawnDatablock {
            get => GenericMarshal.StringTo<string>(GetFieldValue("spawnDatablock"));
            set => SetFieldValue("spawnDatablock", GenericMarshal.ToString(value));
        }
    }
}