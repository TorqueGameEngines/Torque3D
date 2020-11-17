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
    /// <summary>The base Terrain Editor tool</summary>
    /// <description>
    /// Editor use only.
    /// </description>
    public unsafe class TerrainEditor : EditTSCtrl {
        public TerrainEditor(bool pRegister = false) 
            : base(pRegister) {
        }
        
        public TerrainEditor(string pName, bool pRegister) 
            : this(false) {
            Name = pName;
            if (pRegister) {
                RegisterObject();
            }
        }
        
        public TerrainEditor(string pName) 
            : this(pName, false) {
        }
        
        public TerrainEditor(string pName, string pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(Engine.Sim.FindObject<SimObject>(pParent));
        }
        
        public TerrainEditor(string pName, SimObject pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(pParent);
        }
        
        public TerrainEditor(SimObject pObj) 
            : base(pObj) {
        }
        
        public TerrainEditor(IntPtr pObj) 
            : base(pObj) {
        }
        
		protected override void CreateObjectPtr()
		{
			ObjectPtr = InternalUnsafeMethods.Create()(new InternalUnsafeMethods.Create__Args());
		}

        #region UnsafeNativeMethods
        new internal struct InternalUnsafeMethods {
            [StructLayout(LayoutKind.Sequential)]
            internal struct AutoMaterialLayer__Args
            {
                internal float minHeight;
                internal float maxHeight;
                internal float minSlope;
                internal float maxSlope;
                internal float coverage;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _AutoMaterialLayer(IntPtr _this, AutoMaterialLayer__Args args);
            private static _AutoMaterialLayer _AutoMaterialLayerFunc;
            internal static _AutoMaterialLayer AutoMaterialLayer() {
                if (_AutoMaterialLayerFunc == null) {
                    _AutoMaterialLayerFunc =
                        (_AutoMaterialLayer)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnTerrainEditor_autoMaterialLayer"), typeof(_AutoMaterialLayer));
                }
                
                return _AutoMaterialLayerFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct SetSlopeLimitMaxAngle__Args
            {
                internal float angle;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate float _SetSlopeLimitMaxAngle(IntPtr _this, SetSlopeLimitMaxAngle__Args args);
            private static _SetSlopeLimitMaxAngle _SetSlopeLimitMaxAngleFunc;
            internal static _SetSlopeLimitMaxAngle SetSlopeLimitMaxAngle() {
                if (_SetSlopeLimitMaxAngleFunc == null) {
                    _SetSlopeLimitMaxAngleFunc =
                        (_SetSlopeLimitMaxAngle)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnTerrainEditor_setSlopeLimitMaxAngle"), typeof(_SetSlopeLimitMaxAngle));
                }
                
                return _SetSlopeLimitMaxAngleFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct GetSlopeLimitMaxAngle__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate float _GetSlopeLimitMaxAngle(IntPtr _this, GetSlopeLimitMaxAngle__Args args);
            private static _GetSlopeLimitMaxAngle _GetSlopeLimitMaxAngleFunc;
            internal static _GetSlopeLimitMaxAngle GetSlopeLimitMaxAngle() {
                if (_GetSlopeLimitMaxAngleFunc == null) {
                    _GetSlopeLimitMaxAngleFunc =
                        (_GetSlopeLimitMaxAngle)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnTerrainEditor_getSlopeLimitMaxAngle"), typeof(_GetSlopeLimitMaxAngle));
                }
                
                return _GetSlopeLimitMaxAngleFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct SetSlopeLimitMinAngle__Args
            {
                internal float angle;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate float _SetSlopeLimitMinAngle(IntPtr _this, SetSlopeLimitMinAngle__Args args);
            private static _SetSlopeLimitMinAngle _SetSlopeLimitMinAngleFunc;
            internal static _SetSlopeLimitMinAngle SetSlopeLimitMinAngle() {
                if (_SetSlopeLimitMinAngleFunc == null) {
                    _SetSlopeLimitMinAngleFunc =
                        (_SetSlopeLimitMinAngle)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnTerrainEditor_setSlopeLimitMinAngle"), typeof(_SetSlopeLimitMinAngle));
                }
                
                return _SetSlopeLimitMinAngleFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct GetSlopeLimitMinAngle__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate float _GetSlopeLimitMinAngle(IntPtr _this, GetSlopeLimitMinAngle__Args args);
            private static _GetSlopeLimitMinAngle _GetSlopeLimitMinAngleFunc;
            internal static _GetSlopeLimitMinAngle GetSlopeLimitMinAngle() {
                if (_GetSlopeLimitMinAngleFunc == null) {
                    _GetSlopeLimitMinAngleFunc =
                        (_GetSlopeLimitMinAngle)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnTerrainEditor_getSlopeLimitMinAngle"), typeof(_GetSlopeLimitMinAngle));
                }
                
                return _GetSlopeLimitMinAngleFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct GetTerrainUnderWorldPoint__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string ptOrX;
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string Y;
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string Z;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate int _GetTerrainUnderWorldPoint(IntPtr _this, GetTerrainUnderWorldPoint__Args args);
            private static _GetTerrainUnderWorldPoint _GetTerrainUnderWorldPointFunc;
            internal static _GetTerrainUnderWorldPoint GetTerrainUnderWorldPoint() {
                if (_GetTerrainUnderWorldPointFunc == null) {
                    _GetTerrainUnderWorldPointFunc =
                        (_GetTerrainUnderWorldPoint)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnTerrainEditor_getTerrainUnderWorldPoint"), typeof(_GetTerrainUnderWorldPoint));
                }
                
                return _GetTerrainUnderWorldPointFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct ReorderMaterial__Args
            {
                internal int index;
                internal int orderPos;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _ReorderMaterial(IntPtr _this, ReorderMaterial__Args args);
            private static _ReorderMaterial _ReorderMaterialFunc;
            internal static _ReorderMaterial ReorderMaterial() {
                if (_ReorderMaterialFunc == null) {
                    _ReorderMaterialFunc =
                        (_ReorderMaterial)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnTerrainEditor_reorderMaterial"), typeof(_ReorderMaterial));
                }
                
                return _ReorderMaterialFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct GetMaterialIndex__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string name;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate int _GetMaterialIndex(IntPtr _this, GetMaterialIndex__Args args);
            private static _GetMaterialIndex _GetMaterialIndexFunc;
            internal static _GetMaterialIndex GetMaterialIndex() {
                if (_GetMaterialIndexFunc == null) {
                    _GetMaterialIndexFunc =
                        (_GetMaterialIndex)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnTerrainEditor_getMaterialIndex"), typeof(_GetMaterialIndex));
                }
                
                return _GetMaterialIndexFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct GetMaterialName__Args
            {
                internal int index;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            
            internal delegate IntPtr _GetMaterialName(IntPtr _this, GetMaterialName__Args args);
            private static _GetMaterialName _GetMaterialNameFunc;
            internal static _GetMaterialName GetMaterialName() {
                if (_GetMaterialNameFunc == null) {
                    _GetMaterialNameFunc =
                        (_GetMaterialName)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnTerrainEditor_getMaterialName"), typeof(_GetMaterialName));
                }
                
                return _GetMaterialNameFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct GetMaterials__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            
            internal delegate IntPtr _GetMaterials(IntPtr _this, GetMaterials__Args args);
            private static _GetMaterials _GetMaterialsFunc;
            internal static _GetMaterials GetMaterials() {
                if (_GetMaterialsFunc == null) {
                    _GetMaterialsFunc =
                        (_GetMaterials)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnTerrainEditor_getMaterials"), typeof(_GetMaterials));
                }
                
                return _GetMaterialsFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct GetMaterialCount__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate int _GetMaterialCount(IntPtr _this, GetMaterialCount__Args args);
            private static _GetMaterialCount _GetMaterialCountFunc;
            internal static _GetMaterialCount GetMaterialCount() {
                if (_GetMaterialCountFunc == null) {
                    _GetMaterialCountFunc =
                        (_GetMaterialCount)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnTerrainEditor_getMaterialCount"), typeof(_GetMaterialCount));
                }
                
                return _GetMaterialCountFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct RemoveMaterial__Args
            {
                internal int index;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _RemoveMaterial(IntPtr _this, RemoveMaterial__Args args);
            private static _RemoveMaterial _RemoveMaterialFunc;
            internal static _RemoveMaterial RemoveMaterial() {
                if (_RemoveMaterialFunc == null) {
                    _RemoveMaterialFunc =
                        (_RemoveMaterial)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnTerrainEditor_removeMaterial"), typeof(_RemoveMaterial));
                }
                
                return _RemoveMaterialFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct AddMaterial__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string matName;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate int _AddMaterial(IntPtr _this, AddMaterial__Args args);
            private static _AddMaterial _AddMaterialFunc;
            internal static _AddMaterial AddMaterial() {
                if (_AddMaterialFunc == null) {
                    _AddMaterialFunc =
                        (_AddMaterial)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnTerrainEditor_addMaterial"), typeof(_AddMaterial));
                }
                
                return _AddMaterialFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct UpdateMaterial__Args
            {
                internal uint index;
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string matName;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            [return: MarshalAs(UnmanagedType.I1)]
            internal delegate bool _UpdateMaterial(IntPtr _this, UpdateMaterial__Args args);
            private static _UpdateMaterial _UpdateMaterialFunc;
            internal static _UpdateMaterial UpdateMaterial() {
                if (_UpdateMaterialFunc == null) {
                    _UpdateMaterialFunc =
                        (_UpdateMaterial)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnTerrainEditor_updateMaterial"), typeof(_UpdateMaterial));
                }
                
                return _UpdateMaterialFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct SetTerraformOverlay__Args
            {
                [MarshalAs(UnmanagedType.I1)]
                internal bool overlayEnable;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _SetTerraformOverlay(IntPtr _this, SetTerraformOverlay__Args args);
            private static _SetTerraformOverlay _SetTerraformOverlayFunc;
            internal static _SetTerraformOverlay SetTerraformOverlay() {
                if (_SetTerraformOverlayFunc == null) {
                    _SetTerraformOverlayFunc =
                        (_SetTerraformOverlay)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnTerrainEditor_setTerraformOverlay"), typeof(_SetTerraformOverlay));
                }
                
                return _SetTerraformOverlayFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct MirrorTerrain__Args
            {
                internal int mirrorIndex;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _MirrorTerrain(IntPtr _this, MirrorTerrain__Args args);
            private static _MirrorTerrain _MirrorTerrainFunc;
            internal static _MirrorTerrain MirrorTerrain() {
                if (_MirrorTerrainFunc == null) {
                    _MirrorTerrainFunc =
                        (_MirrorTerrain)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnTerrainEditor_mirrorTerrain"), typeof(_MirrorTerrain));
                }
                
                return _MirrorTerrainFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct MarkEmptySquares__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _MarkEmptySquares(IntPtr _this, MarkEmptySquares__Args args);
            private static _MarkEmptySquares _MarkEmptySquaresFunc;
            internal static _MarkEmptySquares MarkEmptySquares() {
                if (_MarkEmptySquaresFunc == null) {
                    _MarkEmptySquaresFunc =
                        (_MarkEmptySquares)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnTerrainEditor_markEmptySquares"), typeof(_MarkEmptySquares));
                }
                
                return _MarkEmptySquaresFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct GetNumTextures__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate int _GetNumTextures(IntPtr _this, GetNumTextures__Args args);
            private static _GetNumTextures _GetNumTexturesFunc;
            internal static _GetNumTextures GetNumTextures() {
                if (_GetNumTexturesFunc == null) {
                    _GetNumTexturesFunc =
                        (_GetNumTextures)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnTerrainEditor_getNumTextures"), typeof(_GetNumTextures));
                }
                
                return _GetNumTexturesFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct GetActiveTerrain__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate int _GetActiveTerrain(IntPtr _this, GetActiveTerrain__Args args);
            private static _GetActiveTerrain _GetActiveTerrainFunc;
            internal static _GetActiveTerrain GetActiveTerrain() {
                if (_GetActiveTerrainFunc == null) {
                    _GetActiveTerrainFunc =
                        (_GetActiveTerrain)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnTerrainEditor_getActiveTerrain"), typeof(_GetActiveTerrain));
                }
                
                return _GetActiveTerrainFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct ProcessAction__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string action;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _ProcessAction(IntPtr _this, ProcessAction__Args args);
            private static _ProcessAction _ProcessActionFunc;
            internal static _ProcessAction ProcessAction() {
                if (_ProcessActionFunc == null) {
                    _ProcessActionFunc =
                        (_ProcessAction)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnTerrainEditor_processAction"), typeof(_ProcessAction));
                }
                
                return _ProcessActionFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct ClearSelection__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _ClearSelection(IntPtr _this, ClearSelection__Args args);
            private static _ClearSelection _ClearSelectionFunc;
            internal static _ClearSelection ClearSelection() {
                if (_ClearSelectionFunc == null) {
                    _ClearSelectionFunc =
                        (_ClearSelection)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnTerrainEditor_clearSelection"), typeof(_ClearSelection));
                }
                
                return _ClearSelectionFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct ResetSelWeights__Args
            {
                [MarshalAs(UnmanagedType.I1)]
                internal bool clear;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _ResetSelWeights(IntPtr _this, ResetSelWeights__Args args);
            private static _ResetSelWeights _ResetSelWeightsFunc;
            internal static _ResetSelWeights ResetSelWeights() {
                if (_ResetSelWeightsFunc == null) {
                    _ResetSelWeightsFunc =
                        (_ResetSelWeights)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnTerrainEditor_resetSelWeights"), typeof(_ResetSelWeights));
                }
                
                return _ResetSelWeightsFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct GetCurrentAction__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            
            internal delegate IntPtr _GetCurrentAction(IntPtr _this, GetCurrentAction__Args args);
            private static _GetCurrentAction _GetCurrentActionFunc;
            internal static _GetCurrentAction GetCurrentAction() {
                if (_GetCurrentActionFunc == null) {
                    _GetCurrentActionFunc =
                        (_GetCurrentAction)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnTerrainEditor_getCurrentAction"), typeof(_GetCurrentAction));
                }
                
                return _GetCurrentActionFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct GetNumActions__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate int _GetNumActions(IntPtr _this, GetNumActions__Args args);
            private static _GetNumActions _GetNumActionsFunc;
            internal static _GetNumActions GetNumActions() {
                if (_GetNumActionsFunc == null) {
                    _GetNumActionsFunc =
                        (_GetNumActions)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnTerrainEditor_getNumActions"), typeof(_GetNumActions));
                }
                
                return _GetNumActionsFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct GetActionName__Args
            {
                internal uint index;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            
            internal delegate IntPtr _GetActionName(IntPtr _this, GetActionName__Args args);
            private static _GetActionName _GetActionNameFunc;
            internal static _GetActionName GetActionName() {
                if (_GetActionNameFunc == null) {
                    _GetActionNameFunc =
                        (_GetActionName)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnTerrainEditor_getActionName"), typeof(_GetActionName));
                }
                
                return _GetActionNameFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct SetAction__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string action_name;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _SetAction(IntPtr _this, SetAction__Args args);
            private static _SetAction _SetActionFunc;
            internal static _SetAction SetAction() {
                if (_SetActionFunc == null) {
                    _SetActionFunc =
                        (_SetAction)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnTerrainEditor_setAction"), typeof(_SetAction));
                }
                
                return _SetActionFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct SetBrushPos__Args
            {
                internal IntPtr pos;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _SetBrushPos(IntPtr _this, SetBrushPos__Args args);
            private static _SetBrushPos _SetBrushPosFunc;
            internal static _SetBrushPos SetBrushPos() {
                if (_SetBrushPosFunc == null) {
                    _SetBrushPosFunc =
                        (_SetBrushPos)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnTerrainEditor_setBrushPos"), typeof(_SetBrushPos));
                }
                
                return _SetBrushPosFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct GetBrushPos__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            
            internal delegate IntPtr _GetBrushPos(IntPtr _this, GetBrushPos__Args args);
            private static _GetBrushPos _GetBrushPosFunc;
            internal static _GetBrushPos GetBrushPos() {
                if (_GetBrushPosFunc == null) {
                    _GetBrushPosFunc =
                        (_GetBrushPos)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnTerrainEditor_getBrushPos"), typeof(_GetBrushPos));
                }
                
                return _GetBrushPosFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct GetBrushSoftness__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate float _GetBrushSoftness(IntPtr _this, GetBrushSoftness__Args args);
            private static _GetBrushSoftness _GetBrushSoftnessFunc;
            internal static _GetBrushSoftness GetBrushSoftness() {
                if (_GetBrushSoftnessFunc == null) {
                    _GetBrushSoftnessFunc =
                        (_GetBrushSoftness)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnTerrainEditor_getBrushSoftness"), typeof(_GetBrushSoftness));
                }
                
                return _GetBrushSoftnessFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct SetBrushSoftness__Args
            {
                internal float softness;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _SetBrushSoftness(IntPtr _this, SetBrushSoftness__Args args);
            private static _SetBrushSoftness _SetBrushSoftnessFunc;
            internal static _SetBrushSoftness SetBrushSoftness() {
                if (_SetBrushSoftnessFunc == null) {
                    _SetBrushSoftnessFunc =
                        (_SetBrushSoftness)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnTerrainEditor_setBrushSoftness"), typeof(_SetBrushSoftness));
                }
                
                return _SetBrushSoftnessFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct GetBrushPressure__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate float _GetBrushPressure(IntPtr _this, GetBrushPressure__Args args);
            private static _GetBrushPressure _GetBrushPressureFunc;
            internal static _GetBrushPressure GetBrushPressure() {
                if (_GetBrushPressureFunc == null) {
                    _GetBrushPressureFunc =
                        (_GetBrushPressure)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnTerrainEditor_getBrushPressure"), typeof(_GetBrushPressure));
                }
                
                return _GetBrushPressureFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct SetBrushPressure__Args
            {
                internal float pressure;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _SetBrushPressure(IntPtr _this, SetBrushPressure__Args args);
            private static _SetBrushPressure _SetBrushPressureFunc;
            internal static _SetBrushPressure SetBrushPressure() {
                if (_SetBrushPressureFunc == null) {
                    _SetBrushPressureFunc =
                        (_SetBrushPressure)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnTerrainEditor_setBrushPressure"), typeof(_SetBrushPressure));
                }
                
                return _SetBrushPressureFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct GetBrushSize__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            
            internal delegate IntPtr _GetBrushSize(IntPtr _this, GetBrushSize__Args args);
            private static _GetBrushSize _GetBrushSizeFunc;
            internal static _GetBrushSize GetBrushSize() {
                if (_GetBrushSizeFunc == null) {
                    _GetBrushSizeFunc =
                        (_GetBrushSize)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnTerrainEditor_getBrushSize"), typeof(_GetBrushSize));
                }
                
                return _GetBrushSizeFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct SetBrushSize__Args
            {
                internal int w;
                internal int h;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _SetBrushSize(IntPtr _this, SetBrushSize__Args args);
            private static _SetBrushSize _SetBrushSizeFunc;
            internal static _SetBrushSize SetBrushSize() {
                if (_SetBrushSizeFunc == null) {
                    _SetBrushSizeFunc =
                        (_SetBrushSize)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnTerrainEditor_setBrushSize"), typeof(_SetBrushSize));
                }
                
                return _SetBrushSizeFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct GetBrushType__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            
            internal delegate IntPtr _GetBrushType(IntPtr _this, GetBrushType__Args args);
            private static _GetBrushType _GetBrushTypeFunc;
            internal static _GetBrushType GetBrushType() {
                if (_GetBrushTypeFunc == null) {
                    _GetBrushTypeFunc =
                        (_GetBrushType)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnTerrainEditor_getBrushType"), typeof(_GetBrushType));
                }
                
                return _GetBrushTypeFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct SetBrushType__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string type;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _SetBrushType(IntPtr _this, SetBrushType__Args args);
            private static _SetBrushType _SetBrushTypeFunc;
            internal static _SetBrushType SetBrushType() {
                if (_SetBrushTypeFunc == null) {
                    _SetBrushTypeFunc =
                        (_SetBrushType)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnTerrainEditor_setBrushType"), typeof(_SetBrushType));
                }
                
                return _SetBrushTypeFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct GetTerrainBlocksMaterialList__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            
            internal delegate IntPtr _GetTerrainBlocksMaterialList(IntPtr _this, GetTerrainBlocksMaterialList__Args args);
            private static _GetTerrainBlocksMaterialList _GetTerrainBlocksMaterialListFunc;
            internal static _GetTerrainBlocksMaterialList GetTerrainBlocksMaterialList() {
                if (_GetTerrainBlocksMaterialListFunc == null) {
                    _GetTerrainBlocksMaterialListFunc =
                        (_GetTerrainBlocksMaterialList)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnTerrainEditor_getTerrainBlocksMaterialList"), typeof(_GetTerrainBlocksMaterialList));
                }
                
                return _GetTerrainBlocksMaterialListFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct GetTerrainBlock__Args
            {
                internal int index;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate int _GetTerrainBlock(IntPtr _this, GetTerrainBlock__Args args);
            private static _GetTerrainBlock _GetTerrainBlockFunc;
            internal static _GetTerrainBlock GetTerrainBlock() {
                if (_GetTerrainBlockFunc == null) {
                    _GetTerrainBlockFunc =
                        (_GetTerrainBlock)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnTerrainEditor_getTerrainBlock"), typeof(_GetTerrainBlock));
                }
                
                return _GetTerrainBlockFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct GetTerrainBlockCount__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate int _GetTerrainBlockCount(IntPtr _this, GetTerrainBlockCount__Args args);
            private static _GetTerrainBlockCount _GetTerrainBlockCountFunc;
            internal static _GetTerrainBlockCount GetTerrainBlockCount() {
                if (_GetTerrainBlockCountFunc == null) {
                    _GetTerrainBlockCountFunc =
                        (_GetTerrainBlockCount)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnTerrainEditor_getTerrainBlockCount"), typeof(_GetTerrainBlockCount));
                }
                
                return _GetTerrainBlockCountFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct AttachTerrain__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string terrain;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _AttachTerrain(IntPtr _this, AttachTerrain__Args args);
            private static _AttachTerrain _AttachTerrainFunc;
            internal static _AttachTerrain AttachTerrain() {
                if (_AttachTerrainFunc == null) {
                    _AttachTerrainFunc =
                        (_AttachTerrain)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnTerrainEditor_attachTerrain"), typeof(_AttachTerrain));
                }
                
                return _AttachTerrainFunc;
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
                                "fnTerrainEditor_staticGetType"), typeof(_StaticGetType));
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
                                "fnTerrainEditor_create"), typeof(_Create));
                }
                
                return _CreateFunc;
            }
        }
        #endregion

        /// <description>
        /// Rule based terrain painting.
        /// </description>
        /// <param name="minHeight">Minimum terrain height.</param>
        /// <param name="maxHeight">Maximum terrain height.</param>
        /// <param name="minSlope">Minimum terrain slope.</param>
        /// <param name="maxSlope">Maximum terrain slope.</param>
        /// <param name="coverage">Terrain coverage amount.</param>
        public void AutoMaterialLayer(float minHeight, float maxHeight, float minSlope, float maxSlope, float coverage) {
             InternalUnsafeMethods.AutoMaterialLayer__Args _args = new InternalUnsafeMethods.AutoMaterialLayer__Args() {
                minHeight = minHeight,
                maxHeight = maxHeight,
                minSlope = minSlope,
                maxSlope = maxSlope,
                coverage = coverage,
             };
             InternalUnsafeMethods.AutoMaterialLayer()(ObjectPtr, _args);
        }

        /// 
        public float SetSlopeLimitMaxAngle(float angle) {
             InternalUnsafeMethods.SetSlopeLimitMaxAngle__Args _args = new InternalUnsafeMethods.SetSlopeLimitMaxAngle__Args() {
                angle = angle,
             };
             float _engineResult = InternalUnsafeMethods.SetSlopeLimitMaxAngle()(ObjectPtr, _args);
             return _engineResult;
        }

        /// 
        public float GetSlopeLimitMaxAngle() {
             InternalUnsafeMethods.GetSlopeLimitMaxAngle__Args _args = new InternalUnsafeMethods.GetSlopeLimitMaxAngle__Args() {
             };
             float _engineResult = InternalUnsafeMethods.GetSlopeLimitMaxAngle()(ObjectPtr, _args);
             return _engineResult;
        }

        /// 
        public float SetSlopeLimitMinAngle(float angle) {
             InternalUnsafeMethods.SetSlopeLimitMinAngle__Args _args = new InternalUnsafeMethods.SetSlopeLimitMinAngle__Args() {
                angle = angle,
             };
             float _engineResult = InternalUnsafeMethods.SetSlopeLimitMinAngle()(ObjectPtr, _args);
             return _engineResult;
        }

        /// 
        public float GetSlopeLimitMinAngle() {
             InternalUnsafeMethods.GetSlopeLimitMinAngle__Args _args = new InternalUnsafeMethods.GetSlopeLimitMinAngle__Args() {
             };
             float _engineResult = InternalUnsafeMethods.GetSlopeLimitMinAngle()(ObjectPtr, _args);
             return _engineResult;
        }

        /// <description>
        /// (x/y/z) Gets the terrain block that is located under the given world point.
        /// </description>
        /// <param name="x/y/z">The world coordinates (floating point values) you wish to query at. These can be formatted as either a string ("x y z") or separately as (x, y, z)</param>
        /// <returns>Returns the ID of the requested terrain block (0 if not found).</returns>
        public int GetTerrainUnderWorldPoint(string ptOrX = "", string Y = "", string Z = "") {
             InternalUnsafeMethods.GetTerrainUnderWorldPoint__Args _args = new InternalUnsafeMethods.GetTerrainUnderWorldPoint__Args() {
                ptOrX = ptOrX,
                Y = Y,
                Z = Z,
             };
             int _engineResult = InternalUnsafeMethods.GetTerrainUnderWorldPoint()(ObjectPtr, _args);
             return _engineResult;
        }

        /// <description>
        /// ( int index, int order ) - Reorder material at the given index to the new position, changing the order in which it is rendered / blended.
        /// </description>
        public void ReorderMaterial(int index, int orderPos) {
             InternalUnsafeMethods.ReorderMaterial__Args _args = new InternalUnsafeMethods.ReorderMaterial__Args() {
                index = index,
                orderPos = orderPos,
             };
             InternalUnsafeMethods.ReorderMaterial()(ObjectPtr, _args);
        }

        /// <description>
        /// ( string name ) - Returns the index of the material with the given name or -1.
        /// </description>
        public int GetMaterialIndex(string name) {
             InternalUnsafeMethods.GetMaterialIndex__Args _args = new InternalUnsafeMethods.GetMaterialIndex__Args() {
                name = name,
             };
             int _engineResult = InternalUnsafeMethods.GetMaterialIndex()(ObjectPtr, _args);
             return _engineResult;
        }

        /// <description>
        /// ( int index ) - Returns the name of the material at the given index.
        /// </description>
        public string GetMaterialName(int index) {
             InternalUnsafeMethods.GetMaterialName__Args _args = new InternalUnsafeMethods.GetMaterialName__Args() {
                index = index,
             };
             IntPtr _engineResult = InternalUnsafeMethods.GetMaterialName()(ObjectPtr, _args);
             return StringMarshal.IntPtrToUtf8String(_engineResult);
        }

        /// <description>
        /// () gets the list of current terrain materials.
        /// </description>
        public string GetMaterials() {
             InternalUnsafeMethods.GetMaterials__Args _args = new InternalUnsafeMethods.GetMaterials__Args() {
             };
             IntPtr _engineResult = InternalUnsafeMethods.GetMaterials()(ObjectPtr, _args);
             return StringMarshal.IntPtrToUtf8String(_engineResult);
        }

        /// <description>
        /// Returns the current material count.
        /// </description>
        public int GetMaterialCount() {
             InternalUnsafeMethods.GetMaterialCount__Args _args = new InternalUnsafeMethods.GetMaterialCount__Args() {
             };
             int _engineResult = InternalUnsafeMethods.GetMaterialCount()(ObjectPtr, _args);
             return _engineResult;
        }

        /// <description>
        /// ( int index ) - Remove the material at the given index.
        /// </description>
        public void RemoveMaterial(int index) {
             InternalUnsafeMethods.RemoveMaterial__Args _args = new InternalUnsafeMethods.RemoveMaterial__Args() {
                index = index,
             };
             InternalUnsafeMethods.RemoveMaterial()(ObjectPtr, _args);
        }

        /// <description>
        /// ( string matName )
        /// Adds a new material.
        /// </description>
        public int AddMaterial(string matName) {
             InternalUnsafeMethods.AddMaterial__Args _args = new InternalUnsafeMethods.AddMaterial__Args() {
                matName = matName,
             };
             int _engineResult = InternalUnsafeMethods.AddMaterial()(ObjectPtr, _args);
             return _engineResult;
        }

        /// <description>
        /// ( int index, string matName )
        /// Changes the material name at the index.
        /// </description>
        public bool UpdateMaterial(uint index, string matName) {
             InternalUnsafeMethods.UpdateMaterial__Args _args = new InternalUnsafeMethods.UpdateMaterial__Args() {
                index = index,
                matName = matName,
             };
             bool _engineResult = InternalUnsafeMethods.UpdateMaterial()(ObjectPtr, _args);
             return _engineResult;
        }

        /// <description>
        /// (bool overlayEnable) - sets the terraformer current heightmap to draw as an overlay over the current terrain.
        /// </description>
        public void SetTerraformOverlay(bool overlayEnable) {
             InternalUnsafeMethods.SetTerraformOverlay__Args _args = new InternalUnsafeMethods.SetTerraformOverlay__Args() {
                overlayEnable = overlayEnable,
             };
             InternalUnsafeMethods.SetTerraformOverlay()(ObjectPtr, _args);
        }

        /// 
        public void MirrorTerrain(int mirrorIndex) {
             InternalUnsafeMethods.MirrorTerrain__Args _args = new InternalUnsafeMethods.MirrorTerrain__Args() {
                mirrorIndex = mirrorIndex,
             };
             InternalUnsafeMethods.MirrorTerrain()(ObjectPtr, _args);
        }

        /// 
        public void MarkEmptySquares() {
             InternalUnsafeMethods.MarkEmptySquares__Args _args = new InternalUnsafeMethods.MarkEmptySquares__Args() {
             };
             InternalUnsafeMethods.MarkEmptySquares()(ObjectPtr, _args);
        }

        /// 
        public int GetNumTextures() {
             InternalUnsafeMethods.GetNumTextures__Args _args = new InternalUnsafeMethods.GetNumTextures__Args() {
             };
             int _engineResult = InternalUnsafeMethods.GetNumTextures()(ObjectPtr, _args);
             return _engineResult;
        }

        /// 
        public int GetActiveTerrain() {
             InternalUnsafeMethods.GetActiveTerrain__Args _args = new InternalUnsafeMethods.GetActiveTerrain__Args() {
             };
             int _engineResult = InternalUnsafeMethods.GetActiveTerrain()(ObjectPtr, _args);
             return _engineResult;
        }

        /// <description>
        /// (string action=NULL)
        /// </description>
        public void ProcessAction(string action = "") {
             InternalUnsafeMethods.ProcessAction__Args _args = new InternalUnsafeMethods.ProcessAction__Args() {
                action = action,
             };
             InternalUnsafeMethods.ProcessAction()(ObjectPtr, _args);
        }

        /// 
        public void ClearSelection() {
             InternalUnsafeMethods.ClearSelection__Args _args = new InternalUnsafeMethods.ClearSelection__Args() {
             };
             InternalUnsafeMethods.ClearSelection()(ObjectPtr, _args);
        }

        /// <description>
        /// (bool clear)
        /// </description>
        public void ResetSelWeights(bool clear) {
             InternalUnsafeMethods.ResetSelWeights__Args _args = new InternalUnsafeMethods.ResetSelWeights__Args() {
                clear = clear,
             };
             InternalUnsafeMethods.ResetSelWeights()(ObjectPtr, _args);
        }

        /// 
        public string GetCurrentAction() {
             InternalUnsafeMethods.GetCurrentAction__Args _args = new InternalUnsafeMethods.GetCurrentAction__Args() {
             };
             IntPtr _engineResult = InternalUnsafeMethods.GetCurrentAction()(ObjectPtr, _args);
             return StringMarshal.IntPtrToUtf8String(_engineResult);
        }

        /// 
        public int GetNumActions() {
             InternalUnsafeMethods.GetNumActions__Args _args = new InternalUnsafeMethods.GetNumActions__Args() {
             };
             int _engineResult = InternalUnsafeMethods.GetNumActions()(ObjectPtr, _args);
             return _engineResult;
        }

        /// <description>
        /// (int num)
        /// </description>
        public string GetActionName(uint index) {
             InternalUnsafeMethods.GetActionName__Args _args = new InternalUnsafeMethods.GetActionName__Args() {
                index = index,
             };
             IntPtr _engineResult = InternalUnsafeMethods.GetActionName()(ObjectPtr, _args);
             return StringMarshal.IntPtrToUtf8String(_engineResult);
        }

        /// <description>
        /// (string action_name)
        /// </description>
        public void SetAction(string action_name) {
             InternalUnsafeMethods.SetAction__Args _args = new InternalUnsafeMethods.SetAction__Args() {
                action_name = action_name,
             };
             InternalUnsafeMethods.SetAction()(ObjectPtr, _args);
        }

        /// <description>
        /// Location
        /// </description>
        public void SetBrushPos(Point2I pos) {
pos.Alloc();             InternalUnsafeMethods.SetBrushPos__Args _args = new InternalUnsafeMethods.SetBrushPos__Args() {
                pos = pos.internalStructPtr,
             };
             InternalUnsafeMethods.SetBrushPos()(ObjectPtr, _args);
pos.Free();        }

        /// <description>
        /// Returns a Point2I.
        /// </description>
        public string GetBrushPos() {
             InternalUnsafeMethods.GetBrushPos__Args _args = new InternalUnsafeMethods.GetBrushPos__Args() {
             };
             IntPtr _engineResult = InternalUnsafeMethods.GetBrushPos()(ObjectPtr, _args);
             return StringMarshal.IntPtrToUtf8String(_engineResult);
        }

        /// <description>
        /// ()
        /// </description>
        public float GetBrushSoftness() {
             InternalUnsafeMethods.GetBrushSoftness__Args _args = new InternalUnsafeMethods.GetBrushSoftness__Args() {
             };
             float _engineResult = InternalUnsafeMethods.GetBrushSoftness()(ObjectPtr, _args);
             return _engineResult;
        }

        /// <description>
        /// (float softness)
        /// </description>
        public void SetBrushSoftness(float softness) {
             InternalUnsafeMethods.SetBrushSoftness__Args _args = new InternalUnsafeMethods.SetBrushSoftness__Args() {
                softness = softness,
             };
             InternalUnsafeMethods.SetBrushSoftness()(ObjectPtr, _args);
        }

        /// <description>
        /// ()
        /// </description>
        public float GetBrushPressure() {
             InternalUnsafeMethods.GetBrushPressure__Args _args = new InternalUnsafeMethods.GetBrushPressure__Args() {
             };
             float _engineResult = InternalUnsafeMethods.GetBrushPressure()(ObjectPtr, _args);
             return _engineResult;
        }

        /// <description>
        /// (float pressure)
        /// </description>
        public void SetBrushPressure(float pressure) {
             InternalUnsafeMethods.SetBrushPressure__Args _args = new InternalUnsafeMethods.SetBrushPressure__Args() {
                pressure = pressure,
             };
             InternalUnsafeMethods.SetBrushPressure()(ObjectPtr, _args);
        }

        /// <description>
        /// ()
        /// </description>
        public string GetBrushSize() {
             InternalUnsafeMethods.GetBrushSize__Args _args = new InternalUnsafeMethods.GetBrushSize__Args() {
             };
             IntPtr _engineResult = InternalUnsafeMethods.GetBrushSize()(ObjectPtr, _args);
             return StringMarshal.IntPtrToUtf8String(_engineResult);
        }

        /// <description>
        /// (int w [, int h])
        /// </description>
        public void SetBrushSize(int w, int h = 0) {
             InternalUnsafeMethods.SetBrushSize__Args _args = new InternalUnsafeMethods.SetBrushSize__Args() {
                w = w,
                h = h,
             };
             InternalUnsafeMethods.SetBrushSize()(ObjectPtr, _args);
        }

        /// <description>
        /// ()
        /// </description>
        public string GetBrushType() {
             InternalUnsafeMethods.GetBrushType__Args _args = new InternalUnsafeMethods.GetBrushType__Args() {
             };
             IntPtr _engineResult = InternalUnsafeMethods.GetBrushType()(ObjectPtr, _args);
             return StringMarshal.IntPtrToUtf8String(_engineResult);
        }

        /// <description>
        /// (string type)One of box, ellipse, selection.
        /// </description>
        public void SetBrushType(string type) {
             InternalUnsafeMethods.SetBrushType__Args _args = new InternalUnsafeMethods.SetBrushType__Args() {
                type = type,
             };
             InternalUnsafeMethods.SetBrushType()(ObjectPtr, _args);
        }

        /// <description>
        /// () gets the list of current terrain materials for all terrain blocks.
        /// </description>
        public string GetTerrainBlocksMaterialList() {
             InternalUnsafeMethods.GetTerrainBlocksMaterialList__Args _args = new InternalUnsafeMethods.GetTerrainBlocksMaterialList__Args() {
             };
             IntPtr _engineResult = InternalUnsafeMethods.GetTerrainBlocksMaterialList()(ObjectPtr, _args);
             return StringMarshal.IntPtrToUtf8String(_engineResult);
        }

        /// <description>
        /// (S32 index)
        /// </description>
        public int GetTerrainBlock(int index) {
             InternalUnsafeMethods.GetTerrainBlock__Args _args = new InternalUnsafeMethods.GetTerrainBlock__Args() {
                index = index,
             };
             int _engineResult = InternalUnsafeMethods.GetTerrainBlock()(ObjectPtr, _args);
             return _engineResult;
        }

        /// <description>
        /// ()
        /// </description>
        public int GetTerrainBlockCount() {
             InternalUnsafeMethods.GetTerrainBlockCount__Args _args = new InternalUnsafeMethods.GetTerrainBlockCount__Args() {
             };
             int _engineResult = InternalUnsafeMethods.GetTerrainBlockCount()(ObjectPtr, _args);
             return _engineResult;
        }

        /// <description>
        /// (TerrainBlock terrain)
        /// </description>
        public void AttachTerrain(string terrain = "") {
             InternalUnsafeMethods.AttachTerrain__Args _args = new InternalUnsafeMethods.AttachTerrain__Args() {
                terrain = terrain,
             };
             InternalUnsafeMethods.AttachTerrain()(ObjectPtr, _args);
        }

        /// <description>
        /// Get the type info object for the TerrainEditor class.
        /// </description>
        /// <returns>The type info object for TerrainEditor</returns>
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
        /// 
        /// </value>
        public bool IsMissionDirty {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("isMissionDirty"));
            set => SetFieldValue("isMissionDirty", GenericMarshal.ToString(value));
        }


        /// <value>
        /// 
        /// </value>
        public bool RenderBorder {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("renderBorder"));
            set => SetFieldValue("renderBorder", GenericMarshal.ToString(value));
        }


        /// <value>
        /// 
        /// </value>
        public float BorderHeight {
            get => GenericMarshal.StringTo<float>(GetFieldValue("borderHeight"));
            set => SetFieldValue("borderHeight", GenericMarshal.ToString(value));
        }


        /// <value>
        /// 
        /// </value>
        public ColorI BorderFillColor {
            get => GenericMarshal.StringTo<ColorI>(GetFieldValue("borderFillColor"));
            set => SetFieldValue("borderFillColor", GenericMarshal.ToString(value));
        }


        /// <value>
        /// 
        /// </value>
        public ColorI BorderFrameColor {
            get => GenericMarshal.StringTo<ColorI>(GetFieldValue("borderFrameColor"));
            set => SetFieldValue("borderFrameColor", GenericMarshal.ToString(value));
        }


        /// <value>
        /// 
        /// </value>
        public bool BorderLineMode {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("borderLineMode"));
            set => SetFieldValue("borderLineMode", GenericMarshal.ToString(value));
        }


        /// <value>
        /// 
        /// </value>
        public bool SelectionHidden {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("selectionHidden"));
            set => SetFieldValue("selectionHidden", GenericMarshal.ToString(value));
        }


        /// <value>
        /// 
        /// </value>
        public bool RenderVertexSelection {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("renderVertexSelection"));
            set => SetFieldValue("renderVertexSelection", GenericMarshal.ToString(value));
        }


        /// <value>
        /// 
        /// </value>
        public bool RenderSolidBrush {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("renderSolidBrush"));
            set => SetFieldValue("renderSolidBrush", GenericMarshal.ToString(value));
        }


        /// <value>
        /// 
        /// </value>
        public bool ProcessUsesBrush {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("processUsesBrush"));
            set => SetFieldValue("processUsesBrush", GenericMarshal.ToString(value));
        }


        /// <value>
        /// 
        /// </value>
        public Point2I MaxBrushSize {
            get => GenericMarshal.StringTo<Point2I>(GetFieldValue("maxBrushSize"));
            set => SetFieldValue("maxBrushSize", GenericMarshal.ToString(value));
        }


        /// <value>
        /// 
        /// </value>
        public float AdjustHeightVal {
            get => GenericMarshal.StringTo<float>(GetFieldValue("adjustHeightVal"));
            set => SetFieldValue("adjustHeightVal", GenericMarshal.ToString(value));
        }


        /// <value>
        /// 
        /// </value>
        public float SetHeightVal {
            get => GenericMarshal.StringTo<float>(GetFieldValue("setHeightVal"));
            set => SetFieldValue("setHeightVal", GenericMarshal.ToString(value));
        }


        /// <value>
        /// 
        /// </value>
        public float ScaleVal {
            get => GenericMarshal.StringTo<float>(GetFieldValue("scaleVal"));
            set => SetFieldValue("scaleVal", GenericMarshal.ToString(value));
        }


        /// <value>
        /// 
        /// </value>
        public float SmoothFactor {
            get => GenericMarshal.StringTo<float>(GetFieldValue("smoothFactor"));
            set => SetFieldValue("smoothFactor", GenericMarshal.ToString(value));
        }


        /// <value>
        /// 
        /// </value>
        public float NoiseFactor {
            get => GenericMarshal.StringTo<float>(GetFieldValue("noiseFactor"));
            set => SetFieldValue("noiseFactor", GenericMarshal.ToString(value));
        }


        /// <value>
        /// 
        /// </value>
        public int MaterialGroup {
            get => GenericMarshal.StringTo<int>(GetFieldValue("materialGroup"));
            set => SetFieldValue("materialGroup", GenericMarshal.ToString(value));
        }


        /// <value>
        /// 
        /// </value>
        public float SoftSelectRadius {
            get => GenericMarshal.StringTo<float>(GetFieldValue("softSelectRadius"));
            set => SetFieldValue("softSelectRadius", GenericMarshal.ToString(value));
        }


        /// <value>
        /// 
        /// </value>
        public string SoftSelectFilter {
            get => GenericMarshal.StringTo<string>(GetFieldValue("softSelectFilter"));
            set => SetFieldValue("softSelectFilter", GenericMarshal.ToString(value));
        }


        /// <value>
        /// 
        /// </value>
        public string SoftSelectDefaultFilter {
            get => GenericMarshal.StringTo<string>(GetFieldValue("softSelectDefaultFilter"));
            set => SetFieldValue("softSelectDefaultFilter", GenericMarshal.ToString(value));
        }


        /// <value>
        /// 
        /// </value>
        public float AdjustHeightMouseScale {
            get => GenericMarshal.StringTo<float>(GetFieldValue("adjustHeightMouseScale"));
            set => SetFieldValue("adjustHeightMouseScale", GenericMarshal.ToString(value));
        }


        /// <value>
        /// 
        /// </value>
        public int PaintIndex {
            get => GenericMarshal.StringTo<int>(GetFieldValue("paintIndex"));
            set => SetFieldValue("paintIndex", GenericMarshal.ToString(value));
        }
    }
}