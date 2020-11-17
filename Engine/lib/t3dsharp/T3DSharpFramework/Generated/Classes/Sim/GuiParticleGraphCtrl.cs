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
    /// <summary>Legacy remnant from old Torque particle editor</summary>
    /// <description>
    /// Editor use only.
    /// </description>
    public unsafe class GuiParticleGraphCtrl : GuiControl {
        public GuiParticleGraphCtrl(bool pRegister = false) 
            : base(pRegister) {
        }
        
        public GuiParticleGraphCtrl(string pName, bool pRegister) 
            : this(false) {
            Name = pName;
            if (pRegister) {
                RegisterObject();
            }
        }
        
        public GuiParticleGraphCtrl(string pName) 
            : this(pName, false) {
        }
        
        public GuiParticleGraphCtrl(string pName, string pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(Engine.Sim.FindObject<SimObject>(pParent));
        }
        
        public GuiParticleGraphCtrl(string pName, SimObject pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(pParent);
        }
        
        public GuiParticleGraphCtrl(SimObject pObj) 
            : base(pObj) {
        }
        
        public GuiParticleGraphCtrl(IntPtr pObj) 
            : base(pObj) {
        }
        
		protected override void CreateObjectPtr()
		{
			ObjectPtr = InternalUnsafeMethods.Create()(new InternalUnsafeMethods.Create__Args());
		}

        #region UnsafeNativeMethods
        new internal struct InternalUnsafeMethods {
            [StructLayout(LayoutKind.Sequential)]
            internal struct ResetSelectedPoint__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _ResetSelectedPoint(IntPtr _this, ResetSelectedPoint__Args args);
            private static _ResetSelectedPoint _ResetSelectedPointFunc;
            internal static _ResetSelectedPoint ResetSelectedPoint() {
                if (_ResetSelectedPointFunc == null) {
                    _ResetSelectedPointFunc =
                        (_ResetSelectedPoint)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnGuiParticleGraphCtrl_resetSelectedPoint"), typeof(_ResetSelectedPoint));
                }
                
                return _ResetSelectedPointFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct SetGraphName__Args
            {
                internal int plotID;
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string graphName;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _SetGraphName(IntPtr _this, SetGraphName__Args args);
            private static _SetGraphName _SetGraphNameFunc;
            internal static _SetGraphName SetGraphName() {
                if (_SetGraphNameFunc == null) {
                    _SetGraphNameFunc =
                        (_SetGraphName)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnGuiParticleGraphCtrl_setGraphName"), typeof(_SetGraphName));
                }
                
                return _SetGraphNameFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct SetRenderGraphTooltip__Args
            {
                [MarshalAs(UnmanagedType.I1)]
                internal bool autoRemove;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _SetRenderGraphTooltip(IntPtr _this, SetRenderGraphTooltip__Args args);
            private static _SetRenderGraphTooltip _SetRenderGraphTooltipFunc;
            internal static _SetRenderGraphTooltip SetRenderGraphTooltip() {
                if (_SetRenderGraphTooltipFunc == null) {
                    _SetRenderGraphTooltipFunc =
                        (_SetRenderGraphTooltip)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnGuiParticleGraphCtrl_setRenderGraphTooltip"), typeof(_SetRenderGraphTooltip));
                }
                
                return _SetRenderGraphTooltipFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct SetPointXMovementClamped__Args
            {
                [MarshalAs(UnmanagedType.I1)]
                internal bool autoRemove;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _SetPointXMovementClamped(IntPtr _this, SetPointXMovementClamped__Args args);
            private static _SetPointXMovementClamped _SetPointXMovementClampedFunc;
            internal static _SetPointXMovementClamped SetPointXMovementClamped() {
                if (_SetPointXMovementClampedFunc == null) {
                    _SetPointXMovementClampedFunc =
                        (_SetPointXMovementClamped)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnGuiParticleGraphCtrl_setPointXMovementClamped"), typeof(_SetPointXMovementClamped));
                }
                
                return _SetPointXMovementClampedFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct SetRenderAll__Args
            {
                [MarshalAs(UnmanagedType.I1)]
                internal bool autoRemove;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _SetRenderAll(IntPtr _this, SetRenderAll__Args args);
            private static _SetRenderAll _SetRenderAllFunc;
            internal static _SetRenderAll SetRenderAll() {
                if (_SetRenderAllFunc == null) {
                    _SetRenderAllFunc =
                        (_SetRenderAll)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnGuiParticleGraphCtrl_setRenderAll"), typeof(_SetRenderAll));
                }
                
                return _SetRenderAllFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct SetAutoRemove__Args
            {
                [MarshalAs(UnmanagedType.I1)]
                internal bool autoRemove;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _SetAutoRemove(IntPtr _this, SetAutoRemove__Args args);
            private static _SetAutoRemove _SetAutoRemoveFunc;
            internal static _SetAutoRemove SetAutoRemove() {
                if (_SetAutoRemoveFunc == null) {
                    _SetAutoRemoveFunc =
                        (_SetAutoRemove)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnGuiParticleGraphCtrl_setAutoRemove"), typeof(_SetAutoRemove));
                }
                
                return _SetAutoRemoveFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct SetAutoGraphMax__Args
            {
                [MarshalAs(UnmanagedType.I1)]
                internal bool autoMax;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _SetAutoGraphMax(IntPtr _this, SetAutoGraphMax__Args args);
            private static _SetAutoGraphMax _SetAutoGraphMaxFunc;
            internal static _SetAutoGraphMax SetAutoGraphMax() {
                if (_SetAutoGraphMaxFunc == null) {
                    _SetAutoGraphMaxFunc =
                        (_SetAutoGraphMax)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnGuiParticleGraphCtrl_setAutoGraphMax"), typeof(_SetAutoGraphMax));
                }
                
                return _SetAutoGraphMaxFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct SetGraphHidden__Args
            {
                internal int plotID;
                [MarshalAs(UnmanagedType.I1)]
                internal bool isHidden;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _SetGraphHidden(IntPtr _this, SetGraphHidden__Args args);
            private static _SetGraphHidden _SetGraphHiddenFunc;
            internal static _SetGraphHidden SetGraphHidden() {
                if (_SetGraphHiddenFunc == null) {
                    _SetGraphHiddenFunc =
                        (_SetGraphHidden)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnGuiParticleGraphCtrl_setGraphHidden"), typeof(_SetGraphHidden));
                }
                
                return _SetGraphHiddenFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct SetGraphMaxY__Args
            {
                internal int plotID;
                internal float maxX;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _SetGraphMaxY(IntPtr _this, SetGraphMaxY__Args args);
            private static _SetGraphMaxY _SetGraphMaxYFunc;
            internal static _SetGraphMaxY SetGraphMaxY() {
                if (_SetGraphMaxYFunc == null) {
                    _SetGraphMaxYFunc =
                        (_SetGraphMaxY)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnGuiParticleGraphCtrl_setGraphMaxY"), typeof(_SetGraphMaxY));
                }
                
                return _SetGraphMaxYFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct SetGraphMaxX__Args
            {
                internal int plotID;
                internal float maxX;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _SetGraphMaxX(IntPtr _this, SetGraphMaxX__Args args);
            private static _SetGraphMaxX _SetGraphMaxXFunc;
            internal static _SetGraphMaxX SetGraphMaxX() {
                if (_SetGraphMaxXFunc == null) {
                    _SetGraphMaxXFunc =
                        (_SetGraphMaxX)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnGuiParticleGraphCtrl_setGraphMaxX"), typeof(_SetGraphMaxX));
                }
                
                return _SetGraphMaxXFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct SetGraphMax__Args
            {
                internal int plotID;
                internal float maxX;
                internal float maxY;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _SetGraphMax(IntPtr _this, SetGraphMax__Args args);
            private static _SetGraphMax _SetGraphMaxFunc;
            internal static _SetGraphMax SetGraphMax() {
                if (_SetGraphMaxFunc == null) {
                    _SetGraphMaxFunc =
                        (_SetGraphMax)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnGuiParticleGraphCtrl_setGraphMax"), typeof(_SetGraphMax));
                }
                
                return _SetGraphMaxFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct SetGraphMinY__Args
            {
                internal int plotID;
                internal float minX;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _SetGraphMinY(IntPtr _this, SetGraphMinY__Args args);
            private static _SetGraphMinY _SetGraphMinYFunc;
            internal static _SetGraphMinY SetGraphMinY() {
                if (_SetGraphMinYFunc == null) {
                    _SetGraphMinYFunc =
                        (_SetGraphMinY)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnGuiParticleGraphCtrl_setGraphMinY"), typeof(_SetGraphMinY));
                }
                
                return _SetGraphMinYFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct SetGraphMinX__Args
            {
                internal int plotID;
                internal float minX;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _SetGraphMinX(IntPtr _this, SetGraphMinX__Args args);
            private static _SetGraphMinX _SetGraphMinXFunc;
            internal static _SetGraphMinX SetGraphMinX() {
                if (_SetGraphMinXFunc == null) {
                    _SetGraphMinXFunc =
                        (_SetGraphMinX)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnGuiParticleGraphCtrl_setGraphMinX"), typeof(_SetGraphMinX));
                }
                
                return _SetGraphMinXFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct SetGraphMin__Args
            {
                internal int plotID;
                internal float minX;
                internal float minY;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _SetGraphMin(IntPtr _this, SetGraphMin__Args args);
            private static _SetGraphMin _SetGraphMinFunc;
            internal static _SetGraphMin SetGraphMin() {
                if (_SetGraphMinFunc == null) {
                    _SetGraphMinFunc =
                        (_SetGraphMin)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnGuiParticleGraphCtrl_setGraphMin"), typeof(_SetGraphMin));
                }
                
                return _SetGraphMinFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct GetGraphName__Args
            {
                internal int plotID;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            
            internal delegate IntPtr _GetGraphName(IntPtr _this, GetGraphName__Args args);
            private static _GetGraphName _GetGraphNameFunc;
            internal static _GetGraphName GetGraphName() {
                if (_GetGraphNameFunc == null) {
                    _GetGraphNameFunc =
                        (_GetGraphName)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnGuiParticleGraphCtrl_getGraphName"), typeof(_GetGraphName));
                }
                
                return _GetGraphNameFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct GetGraphMax__Args
            {
                internal int plotID;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate Point2F.InternalStruct _GetGraphMax(IntPtr _this, GetGraphMax__Args args);
            private static _GetGraphMax _GetGraphMaxFunc;
            internal static _GetGraphMax GetGraphMax() {
                if (_GetGraphMaxFunc == null) {
                    _GetGraphMaxFunc =
                        (_GetGraphMax)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnGuiParticleGraphCtrl_getGraphMax"), typeof(_GetGraphMax));
                }
                
                return _GetGraphMaxFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct GetGraphMin__Args
            {
                internal int plotID;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate Point2F.InternalStruct _GetGraphMin(IntPtr _this, GetGraphMin__Args args);
            private static _GetGraphMin _GetGraphMinFunc;
            internal static _GetGraphMin GetGraphMin() {
                if (_GetGraphMinFunc == null) {
                    _GetGraphMinFunc =
                        (_GetGraphMin)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnGuiParticleGraphCtrl_getGraphMin"), typeof(_GetGraphMin));
                }
                
                return _GetGraphMinFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct GetGraphColor__Args
            {
                internal int plotID;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate LinearColorF.InternalStruct _GetGraphColor(IntPtr _this, GetGraphColor__Args args);
            private static _GetGraphColor _GetGraphColorFunc;
            internal static _GetGraphColor GetGraphColor() {
                if (_GetGraphColorFunc == null) {
                    _GetGraphColorFunc =
                        (_GetGraphColor)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnGuiParticleGraphCtrl_getGraphColor"), typeof(_GetGraphColor));
                }
                
                return _GetGraphColorFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct GetPlotIndex__Args
            {
                internal int plotID;
                internal float x;
                internal float y;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate int _GetPlotIndex(IntPtr _this, GetPlotIndex__Args args);
            private static _GetPlotIndex _GetPlotIndexFunc;
            internal static _GetPlotIndex GetPlotIndex() {
                if (_GetPlotIndexFunc == null) {
                    _GetPlotIndexFunc =
                        (_GetPlotIndex)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnGuiParticleGraphCtrl_getPlotIndex"), typeof(_GetPlotIndex));
                }
                
                return _GetPlotIndexFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct GetPlotPoint__Args
            {
                internal int plotID;
                internal int samples;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate Point2F.InternalStruct _GetPlotPoint(IntPtr _this, GetPlotPoint__Args args);
            private static _GetPlotPoint _GetPlotPointFunc;
            internal static _GetPlotPoint GetPlotPoint() {
                if (_GetPlotPointFunc == null) {
                    _GetPlotPointFunc =
                        (_GetPlotPoint)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnGuiParticleGraphCtrl_getPlotPoint"), typeof(_GetPlotPoint));
                }
                
                return _GetPlotPointFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct IsExistingPoint__Args
            {
                internal int plotID;
                internal int samples;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            [return: MarshalAs(UnmanagedType.I1)]
            internal delegate bool _IsExistingPoint(IntPtr _this, IsExistingPoint__Args args);
            private static _IsExistingPoint _IsExistingPointFunc;
            internal static _IsExistingPoint IsExistingPoint() {
                if (_IsExistingPointFunc == null) {
                    _IsExistingPointFunc =
                        (_IsExistingPoint)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnGuiParticleGraphCtrl_isExistingPoint"), typeof(_IsExistingPoint));
                }
                
                return _IsExistingPointFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct GetSelectedPoint__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate int _GetSelectedPoint(IntPtr _this, GetSelectedPoint__Args args);
            private static _GetSelectedPoint _GetSelectedPointFunc;
            internal static _GetSelectedPoint GetSelectedPoint() {
                if (_GetSelectedPointFunc == null) {
                    _GetSelectedPointFunc =
                        (_GetSelectedPoint)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnGuiParticleGraphCtrl_getSelectedPoint"), typeof(_GetSelectedPoint));
                }
                
                return _GetSelectedPointFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct GetSelectedPlot__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate int _GetSelectedPlot(IntPtr _this, GetSelectedPlot__Args args);
            private static _GetSelectedPlot _GetSelectedPlotFunc;
            internal static _GetSelectedPlot GetSelectedPlot() {
                if (_GetSelectedPlotFunc == null) {
                    _GetSelectedPlotFunc =
                        (_GetSelectedPlot)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnGuiParticleGraphCtrl_getSelectedPlot"), typeof(_GetSelectedPlot));
                }
                
                return _GetSelectedPlotFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct ChangePlotPoint__Args
            {
                internal int plotID;
                internal int i;
                internal float x;
                internal float y;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate int _ChangePlotPoint(IntPtr _this, ChangePlotPoint__Args args);
            private static _ChangePlotPoint _ChangePlotPointFunc;
            internal static _ChangePlotPoint ChangePlotPoint() {
                if (_ChangePlotPointFunc == null) {
                    _ChangePlotPointFunc =
                        (_ChangePlotPoint)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnGuiParticleGraphCtrl_changePlotPoint"), typeof(_ChangePlotPoint));
                }
                
                return _ChangePlotPointFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct InsertPlotPoint__Args
            {
                internal int plotID;
                internal int i;
                internal float x;
                internal float y;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _InsertPlotPoint(IntPtr _this, InsertPlotPoint__Args args);
            private static _InsertPlotPoint _InsertPlotPointFunc;
            internal static _InsertPlotPoint InsertPlotPoint() {
                if (_InsertPlotPointFunc == null) {
                    _InsertPlotPointFunc =
                        (_InsertPlotPoint)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnGuiParticleGraphCtrl_insertPlotPoint"), typeof(_InsertPlotPoint));
                }
                
                return _InsertPlotPointFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct AddPlotPoint__Args
            {
                internal int plotID;
                internal float x;
                internal float y;
                [MarshalAs(UnmanagedType.I1)]
                internal bool setAdded;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate int _AddPlotPoint(IntPtr _this, AddPlotPoint__Args args);
            private static _AddPlotPoint _AddPlotPointFunc;
            internal static _AddPlotPoint AddPlotPoint() {
                if (_AddPlotPointFunc == null) {
                    _AddPlotPointFunc =
                        (_AddPlotPoint)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnGuiParticleGraphCtrl_addPlotPoint"), typeof(_AddPlotPoint));
                }
                
                return _AddPlotPointFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct ClearAllGraphs__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _ClearAllGraphs(IntPtr _this, ClearAllGraphs__Args args);
            private static _ClearAllGraphs _ClearAllGraphsFunc;
            internal static _ClearAllGraphs ClearAllGraphs() {
                if (_ClearAllGraphsFunc == null) {
                    _ClearAllGraphsFunc =
                        (_ClearAllGraphs)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnGuiParticleGraphCtrl_clearAllGraphs"), typeof(_ClearAllGraphs));
                }
                
                return _ClearAllGraphsFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct ClearGraph__Args
            {
                internal int plotID;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _ClearGraph(IntPtr _this, ClearGraph__Args args);
            private static _ClearGraph _ClearGraphFunc;
            internal static _ClearGraph ClearGraph() {
                if (_ClearGraphFunc == null) {
                    _ClearGraphFunc =
                        (_ClearGraph)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnGuiParticleGraphCtrl_clearGraph"), typeof(_ClearGraph));
                }
                
                return _ClearGraphFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct SetSelectedPlot__Args
            {
                internal int plotID;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _SetSelectedPlot(IntPtr _this, SetSelectedPlot__Args args);
            private static _SetSelectedPlot _SetSelectedPlotFunc;
            internal static _SetSelectedPlot SetSelectedPlot() {
                if (_SetSelectedPlotFunc == null) {
                    _SetSelectedPlotFunc =
                        (_SetSelectedPlot)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnGuiParticleGraphCtrl_setSelectedPlot"), typeof(_SetSelectedPlot));
                }
                
                return _SetSelectedPlotFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct SetSelectedPoint__Args
            {
                internal int point;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _SetSelectedPoint(IntPtr _this, SetSelectedPoint__Args args);
            private static _SetSelectedPoint _SetSelectedPointFunc;
            internal static _SetSelectedPoint SetSelectedPoint() {
                if (_SetSelectedPointFunc == null) {
                    _SetSelectedPointFunc =
                        (_SetSelectedPoint)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnGuiParticleGraphCtrl_setSelectedPoint"), typeof(_SetSelectedPoint));
                }
                
                return _SetSelectedPointFunc;
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
                                "fnGuiParticleGraphCtrl_staticGetType"), typeof(_StaticGetType));
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
                                "fnGuiParticleGraphCtrl_create"), typeof(_Create));
                }
                
                return _CreateFunc;
            }
        }
        #endregion

        /// <description>
        /// ()This will reset the currently selected point to nothing.
        /// </description>
        /// <returns>No return value.</returns>
        public void ResetSelectedPoint() {
             InternalUnsafeMethods.ResetSelectedPoint__Args _args = new InternalUnsafeMethods.ResetSelectedPoint__Args() {
             };
             InternalUnsafeMethods.ResetSelectedPoint()(ObjectPtr, _args);
        }

        /// <description>
        /// (int plotID, string graphName) Set the name of the given plot.
        /// </description>
        /// <param name="plotID">The plot to modify.</param>
        /// <param name="graphName">The name to set on the plot.</param>
        /// <returns>No return value.</returns>
        public void SetGraphName(int plotID, string graphName) {
             InternalUnsafeMethods.SetGraphName__Args _args = new InternalUnsafeMethods.SetGraphName__Args() {
                plotID = plotID,
                graphName = graphName,
             };
             InternalUnsafeMethods.SetGraphName()(ObjectPtr, _args);
        }

        /// <description>
        /// (bool renderGraphTooltip)Set whether or not to render the graph tooltip.
        /// </description>
        /// <returns>No return value.</returns>
        public void SetRenderGraphTooltip(bool autoRemove) {
             InternalUnsafeMethods.SetRenderGraphTooltip__Args _args = new InternalUnsafeMethods.SetRenderGraphTooltip__Args() {
                autoRemove = autoRemove,
             };
             InternalUnsafeMethods.SetRenderGraphTooltip()(ObjectPtr, _args);
        }

        /// <description>
        /// (bool clamped)Set whether the x position of the selected graph point should be clamped
        /// </description>
        /// <returns>No return value.</returns>
        public void SetPointXMovementClamped(bool autoRemove) {
             InternalUnsafeMethods.SetPointXMovementClamped__Args _args = new InternalUnsafeMethods.SetPointXMovementClamped__Args() {
                autoRemove = autoRemove,
             };
             InternalUnsafeMethods.SetPointXMovementClamped()(ObjectPtr, _args);
        }

        /// <description>
        /// (bool renderAll)Set whether or not a position should be rendered on every point or just the last selected.
        /// </description>
        /// <returns>No return value.</returns>
        public void SetRenderAll(bool autoRemove) {
             InternalUnsafeMethods.SetRenderAll__Args _args = new InternalUnsafeMethods.SetRenderAll__Args() {
                autoRemove = autoRemove,
             };
             InternalUnsafeMethods.SetRenderAll()(ObjectPtr, _args);
        }

        /// <description>
        /// (bool autoRemove) Set whether or not a point should be deleted when you drag another one over it.
        /// </description>
        /// <returns>No return value.</returns>
        public void SetAutoRemove(bool autoRemove) {
             InternalUnsafeMethods.SetAutoRemove__Args _args = new InternalUnsafeMethods.SetAutoRemove__Args() {
                autoRemove = autoRemove,
             };
             InternalUnsafeMethods.SetAutoRemove()(ObjectPtr, _args);
        }

        /// <description>
        /// (bool autoMax) Set whether the max will automatically be set when adding points (ie if you add a value over the current max, the max is increased to that value).
        /// </description>
        /// <returns>No return value.</returns>
        public void SetAutoGraphMax(bool autoMax) {
             InternalUnsafeMethods.SetAutoGraphMax__Args _args = new InternalUnsafeMethods.SetAutoGraphMax__Args() {
                autoMax = autoMax,
             };
             InternalUnsafeMethods.SetAutoGraphMax()(ObjectPtr, _args);
        }

        /// <description>
        /// (int plotID, bool isHidden)Set whether the graph number passed is hidden or not.
        /// </description>
        /// <returns>No return value.</returns>
        public void SetGraphHidden(int plotID, bool isHidden) {
             InternalUnsafeMethods.SetGraphHidden__Args _args = new InternalUnsafeMethods.SetGraphHidden__Args() {
                plotID = plotID,
                isHidden = isHidden,
             };
             InternalUnsafeMethods.SetGraphHidden()(ObjectPtr, _args);
        }

        /// <description>
        /// (int plotID, float maxY)Set the max Y value of the graph of plotID.
        /// </description>
        /// <param name="plotID">The plot to modify.</param>
        /// <param name="maxY">The maximum y value.</param>
        /// <returns>No return Value.</returns>
        public void SetGraphMaxY(int plotID, float maxX) {
             InternalUnsafeMethods.SetGraphMaxY__Args _args = new InternalUnsafeMethods.SetGraphMaxY__Args() {
                plotID = plotID,
                maxX = maxX,
             };
             InternalUnsafeMethods.SetGraphMaxY()(ObjectPtr, _args);
        }

        /// <description>
        /// (int plotID, float maxX)Set the max X value of the graph of plotID.
        /// </description>
        /// <param name="plotID">The plot to modify.</param>
        /// <param name="maxX">The maximum x value.</param>
        /// <returns>No return Value.</returns>
        public void SetGraphMaxX(int plotID, float maxX) {
             InternalUnsafeMethods.SetGraphMaxX__Args _args = new InternalUnsafeMethods.SetGraphMaxX__Args() {
                plotID = plotID,
                maxX = maxX,
             };
             InternalUnsafeMethods.SetGraphMaxX()(ObjectPtr, _args);
        }

        /// <description>
        /// (int plotID, float maxX, float maxY) Set the max values of the graph of plotID.
        /// </description>
        /// <param name="plotID">The plot to modify</param>
        /// <param name="maxX,maxY">The maximum bound of the value range.</param>
        /// <returns>No return value.</returns>
        public void SetGraphMax(int plotID, float maxX, float maxY) {
             InternalUnsafeMethods.SetGraphMax__Args _args = new InternalUnsafeMethods.SetGraphMax__Args() {
                plotID = plotID,
                maxX = maxX,
                maxY = maxY,
             };
             InternalUnsafeMethods.SetGraphMax()(ObjectPtr, _args);
        }

        /// <description>
        /// (int plotID, float minY) Set the min Y value of the graph of plotID.
        /// </description>
        /// <param name="plotID">The plot to modify.</param>
        /// <param name="minY">The minimum y value.</param>
        /// <returns>No return Value.</returns>
        public void SetGraphMinY(int plotID, float minX) {
             InternalUnsafeMethods.SetGraphMinY__Args _args = new InternalUnsafeMethods.SetGraphMinY__Args() {
                plotID = plotID,
                minX = minX,
             };
             InternalUnsafeMethods.SetGraphMinY()(ObjectPtr, _args);
        }

        /// <description>
        /// (int plotID, float minX) Set the min X value of the graph of plotID.
        /// </description>
        /// <param name="plotID">The plot to modify.</param>
        /// <param name="minX">The minimum x value.</param>
        /// <returns>No return Value.</returns>
        public void SetGraphMinX(int plotID, float minX) {
             InternalUnsafeMethods.SetGraphMinX__Args _args = new InternalUnsafeMethods.SetGraphMinX__Args() {
                plotID = plotID,
                minX = minX,
             };
             InternalUnsafeMethods.SetGraphMinX()(ObjectPtr, _args);
        }

        /// <description>
        /// (int plotID, float minX, float minY) Set the min values of the graph of plotID.
        /// </description>
        /// <param name="plotID">The plot to modify</param>
        /// <param name="minX,minY">The minimum bound of the value range.</param>
        /// <returns>No return value.</returns>
        public void SetGraphMin(int plotID, float minX, float minY) {
             InternalUnsafeMethods.SetGraphMin__Args _args = new InternalUnsafeMethods.SetGraphMin__Args() {
                plotID = plotID,
                minX = minX,
                minY = minY,
             };
             InternalUnsafeMethods.SetGraphMin()(ObjectPtr, _args);
        }

        /// <description>
        /// (int plotID) Get the name of the graph passed.
        /// </description>
        /// <returns>Returns the name of the plot</returns>
        public string GetGraphName(int plotID) {
             InternalUnsafeMethods.GetGraphName__Args _args = new InternalUnsafeMethods.GetGraphName__Args() {
                plotID = plotID,
             };
             IntPtr _engineResult = InternalUnsafeMethods.GetGraphName()(ObjectPtr, _args);
             return StringMarshal.IntPtrToUtf8String(_engineResult);
        }

        /// <description>
        /// (int plotID) Get the maximum values of the graph ranges.
        /// </description>
        /// <returns>Returns the maximum of the range formatted as "x-max y-max"</returns>
        public Point2F GetGraphMax(int plotID) {
             InternalUnsafeMethods.GetGraphMax__Args _args = new InternalUnsafeMethods.GetGraphMax__Args() {
                plotID = plotID,
             };
             Point2F.InternalStruct _engineResult = InternalUnsafeMethods.GetGraphMax()(ObjectPtr, _args);
             return new Point2F(_engineResult);
        }

        /// <description>
        /// (int plotID) Get the minimum values of the graph ranges.
        /// </description>
        /// <returns>Returns the minimum of the range formatted as "x-min y-min"</returns>
        public Point2F GetGraphMin(int plotID) {
             InternalUnsafeMethods.GetGraphMin__Args _args = new InternalUnsafeMethods.GetGraphMin__Args() {
                plotID = plotID,
             };
             Point2F.InternalStruct _engineResult = InternalUnsafeMethods.GetGraphMin()(ObjectPtr, _args);
             return new Point2F(_engineResult);
        }

        /// <description>
        /// (int plotID)Get the color of the graph passed.
        /// </description>
        /// <returns>Returns the color of the graph as a string of RGB values formatted as "R G B"</returns>
        public LinearColorF GetGraphColor(int plotID) {
             InternalUnsafeMethods.GetGraphColor__Args _args = new InternalUnsafeMethods.GetGraphColor__Args() {
                plotID = plotID,
             };
             LinearColorF.InternalStruct _engineResult = InternalUnsafeMethods.GetGraphColor()(ObjectPtr, _args);
             return new LinearColorF(_engineResult);
        }

        /// <description>
        /// (int plotID, float x, float y)
        /// Gets the index of the point passed on the plotID passed (graph ID).
        /// </description>
        /// <param name="plotID">The plot you wish to check.</param>
        /// <param name="x,y">The coordinates of the point to get.</param>
        /// <returns>Returns the index of the point.</returns>
        public int GetPlotIndex(int plotID, float x, float y) {
             InternalUnsafeMethods.GetPlotIndex__Args _args = new InternalUnsafeMethods.GetPlotIndex__Args() {
                plotID = plotID,
                x = x,
                y = y,
             };
             int _engineResult = InternalUnsafeMethods.GetPlotIndex()(ObjectPtr, _args);
             return _engineResult;
        }

        /// <description>
        /// (int plotID, int samples)Get a data point from the plot specified, samples from the start of the graph.
        /// </description>
        /// <returns>The data point ID</returns>
        public Point2F GetPlotPoint(int plotID, int samples) {
             InternalUnsafeMethods.GetPlotPoint__Args _args = new InternalUnsafeMethods.GetPlotPoint__Args() {
                plotID = plotID,
                samples = samples,
             };
             Point2F.InternalStruct _engineResult = InternalUnsafeMethods.GetPlotPoint()(ObjectPtr, _args);
             return new Point2F(_engineResult);
        }

        /// <description>
        /// (int plotID, int samples)
        /// </description>
        /// <returns>Returns true or false whether or not the point in the plot passed is an existing point.</returns>
        public bool IsExistingPoint(int plotID, int samples) {
             InternalUnsafeMethods.IsExistingPoint__Args _args = new InternalUnsafeMethods.IsExistingPoint__Args() {
                plotID = plotID,
                samples = samples,
             };
             bool _engineResult = InternalUnsafeMethods.IsExistingPoint()(ObjectPtr, _args);
             return _engineResult;
        }

        /// <description>
        /// ()Gets the selected Point on the Plot (a.k.a. graph).
        /// </description>
        /// <returns>The last selected point ID</returns>
        public int GetSelectedPoint() {
             InternalUnsafeMethods.GetSelectedPoint__Args _args = new InternalUnsafeMethods.GetSelectedPoint__Args() {
             };
             int _engineResult = InternalUnsafeMethods.GetSelectedPoint()(ObjectPtr, _args);
             return _engineResult;
        }

        /// <description>
        /// () Gets the selected Plot (a.k.a. graph).
        /// </description>
        /// <returns>The plot's ID.</returns>
        public int GetSelectedPlot() {
             InternalUnsafeMethods.GetSelectedPlot__Args _args = new InternalUnsafeMethods.GetSelectedPlot__Args() {
             };
             int _engineResult = InternalUnsafeMethods.GetSelectedPlot()(ObjectPtr, _args);
             return _engineResult;
        }

        /// <description>
        /// (int plotID, int i, float x, float y)Change a data point to the given plot and plot position.
        /// </description>
        /// <param name="plotID">The plot you want to access</param>
        /// <param name="i">The data point.</param>
        /// <param name="x,y">The plot position.</param>
        /// <returns>No return value.</returns>
        public int ChangePlotPoint(int plotID, int i, float x, float y) {
             InternalUnsafeMethods.ChangePlotPoint__Args _args = new InternalUnsafeMethods.ChangePlotPoint__Args() {
                plotID = plotID,
                i = i,
                x = x,
                y = y,
             };
             int _engineResult = InternalUnsafeMethods.ChangePlotPoint()(ObjectPtr, _args);
             return _engineResult;
        }

        /// <description>
        /// (int plotID, int i, float x, float y)
        /// Insert a data point to the given plot and plot position.
        /// </description>
        /// <param name="plotID">The plot you want to access</param>
        /// <param name="i">The data point.</param>
        /// <param name="x,y">The plot position.</param>
        /// <returns>No return value.</returns>
        public void InsertPlotPoint(int plotID, int i, float x, float y) {
             InternalUnsafeMethods.InsertPlotPoint__Args _args = new InternalUnsafeMethods.InsertPlotPoint__Args() {
                plotID = plotID,
                i = i,
                x = x,
                y = y,
             };
             InternalUnsafeMethods.InsertPlotPoint()(ObjectPtr, _args);
        }

        /// <description>
        /// (int plotID, float x, float y, bool setAdded = true;)Add a data point to the given plot.
        /// </description>
        /// <returns></returns>
        public int AddPlotPoint(int plotID, float x, float y, bool setAdded = true) {
             InternalUnsafeMethods.AddPlotPoint__Args _args = new InternalUnsafeMethods.AddPlotPoint__Args() {
                plotID = plotID,
                x = x,
                y = y,
                setAdded = setAdded,
             };
             int _engineResult = InternalUnsafeMethods.AddPlotPoint()(ObjectPtr, _args);
             return _engineResult;
        }

        /// <description>
        /// ()Clear all of the graphs.
        /// </description>
        /// <returns>No return value</returns>
        public void ClearAllGraphs() {
             InternalUnsafeMethods.ClearAllGraphs__Args _args = new InternalUnsafeMethods.ClearAllGraphs__Args() {
             };
             InternalUnsafeMethods.ClearAllGraphs()(ObjectPtr, _args);
        }

        /// <description>
        /// (int plotID)Clear the graph of the given plot.
        /// </description>
        /// <returns>No return value</returns>
        public void ClearGraph(int plotID) {
             InternalUnsafeMethods.ClearGraph__Args _args = new InternalUnsafeMethods.ClearGraph__Args() {
                plotID = plotID,
             };
             InternalUnsafeMethods.ClearGraph()(ObjectPtr, _args);
        }

        /// <description>
        /// (int plotID)Set the selected plot (a.k.a. graph).
        /// </description>
        /// <returns>No return value</returns>
        public void SetSelectedPlot(int plotID) {
             InternalUnsafeMethods.SetSelectedPlot__Args _args = new InternalUnsafeMethods.SetSelectedPlot__Args() {
                plotID = plotID,
             };
             InternalUnsafeMethods.SetSelectedPlot()(ObjectPtr, _args);
        }

        /// <description>
        /// (int point)Set the selected point on the graph.
        /// </description>
        /// <returns>No return value</returns>
        public void SetSelectedPoint(int point) {
             InternalUnsafeMethods.SetSelectedPoint__Args _args = new InternalUnsafeMethods.SetSelectedPoint__Args() {
                point = point,
             };
             InternalUnsafeMethods.SetSelectedPoint()(ObjectPtr, _args);
        }

        /// <description>
        /// Get the type info object for the GuiParticleGraphCtrl class.
        /// </description>
        /// <returns>The type info object for GuiParticleGraphCtrl</returns>
        public static EngineTypeInfo StaticGetType() {
             InternalUnsafeMethods.StaticGetType__Args _args = new InternalUnsafeMethods.StaticGetType__Args() {
             };
             IntPtr _engineResult = InternalUnsafeMethods.StaticGetType()(_args);
             return new EngineTypeInfo(_engineResult);
        }
    }
}