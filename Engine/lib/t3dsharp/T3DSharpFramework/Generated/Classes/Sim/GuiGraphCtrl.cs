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
    /// <summary>A control that plots one or more curves in a chart.</summary>
    /// <description>
    /// Up to 6 individual curves can be plotted in the graph.  Each plotted curve can have its own display style including its own charting style (#plotType) and color (#plotColor).
    /// 
    /// The data points on each curve can be added in one of two ways:
    /// 
    /// - Manually by calling addDatum().  This causes new data points to be added to the left end of the plotting curve.
    /// - Automatically by letting the graph plot the values of a variable over time.  This is achieved by calling addAutoPlot and specifying the variable and update frequency.
    /// </description>
    /// <code>
    /// // Create a graph that plots a red polyline graph of the FPS counter in a 1 second (1000 milliseconds) interval.
    /// new GuiGraphCtrl( FPSGraph )
    /// {
    ///    plotType[ 0 ] = "PolyLine";
    ///    plotColor[ 0 ] = "1 0 0";
    ///    plotVariable[ 0 ] = "fps::real";
    ///    plotInterval[ 0 ] = 1000;
    /// };
    /// </code>
    /// <remarks> Each curve has a maximum number of 200 data points it can have at any one time.  Adding more data points to a curve will cause older data points to be removed.
    /// 
    /// </remarks>
    public unsafe class GuiGraphCtrl : GuiControl {
        public GuiGraphCtrl(bool pRegister = false) 
            : base(pRegister) {
        }
        
        public GuiGraphCtrl(string pName, bool pRegister) 
            : this(false) {
            Name = pName;
            if (pRegister) {
                RegisterObject();
            }
        }
        
        public GuiGraphCtrl(string pName) 
            : this(pName, false) {
        }
        
        public GuiGraphCtrl(string pName, string pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(Engine.Sim.FindObject<SimObject>(pParent));
        }
        
        public GuiGraphCtrl(string pName, SimObject pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(pParent);
        }
        
        public GuiGraphCtrl(SimObject pObj) 
            : base(pObj) {
        }
        
        public GuiGraphCtrl(IntPtr pObj) 
            : base(pObj) {
        }
        
		protected override void CreateObjectPtr()
		{
			ObjectPtr = InternalUnsafeMethods.Create()(new InternalUnsafeMethods.Create__Args());
		}

        #region UnsafeNativeMethods
        new internal struct InternalUnsafeMethods {

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _MatchScale(IntPtr _this, ref StringVector.InternalStruct args);
            private static _MatchScale _MatchScaleFunc;
            internal static _MatchScale MatchScale() {
                if (_MatchScaleFunc == null) {
                    _MatchScaleFunc =
                        (_MatchScale)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnGuiGraphCtrl_matchScale"), typeof(_MatchScale));
                }
                
                return _MatchScaleFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct SetGraphType__Args
            {
                internal int plotId;
                internal int graphType;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _SetGraphType(IntPtr _this, SetGraphType__Args args);
            private static _SetGraphType _SetGraphTypeFunc;
            internal static _SetGraphType SetGraphType() {
                if (_SetGraphTypeFunc == null) {
                    _SetGraphTypeFunc =
                        (_SetGraphType)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnGuiGraphCtrl_setGraphType"), typeof(_SetGraphType));
                }
                
                return _SetGraphTypeFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct RemoveAutoPlot__Args
            {
                internal int plotId;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _RemoveAutoPlot(IntPtr _this, RemoveAutoPlot__Args args);
            private static _RemoveAutoPlot _RemoveAutoPlotFunc;
            internal static _RemoveAutoPlot RemoveAutoPlot() {
                if (_RemoveAutoPlotFunc == null) {
                    _RemoveAutoPlotFunc =
                        (_RemoveAutoPlot)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnGuiGraphCtrl_removeAutoPlot"), typeof(_RemoveAutoPlot));
                }
                
                return _RemoveAutoPlotFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct AddAutoPlot__Args
            {
                internal int plotId;
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string variable;
                internal int updateFrequency;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _AddAutoPlot(IntPtr _this, AddAutoPlot__Args args);
            private static _AddAutoPlot _AddAutoPlotFunc;
            internal static _AddAutoPlot AddAutoPlot() {
                if (_AddAutoPlotFunc == null) {
                    _AddAutoPlotFunc =
                        (_AddAutoPlot)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnGuiGraphCtrl_addAutoPlot"), typeof(_AddAutoPlot));
                }
                
                return _AddAutoPlotFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct GetDatum__Args
            {
                internal int plotId;
                internal int index;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate float _GetDatum(IntPtr _this, GetDatum__Args args);
            private static _GetDatum _GetDatumFunc;
            internal static _GetDatum GetDatum() {
                if (_GetDatumFunc == null) {
                    _GetDatumFunc =
                        (_GetDatum)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnGuiGraphCtrl_getDatum"), typeof(_GetDatum));
                }
                
                return _GetDatumFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct AddDatum__Args
            {
                internal int plotId;
                internal float value;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _AddDatum(IntPtr _this, AddDatum__Args args);
            private static _AddDatum _AddDatumFunc;
            internal static _AddDatum AddDatum() {
                if (_AddDatumFunc == null) {
                    _AddDatumFunc =
                        (_AddDatum)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnGuiGraphCtrl_addDatum"), typeof(_AddDatum));
                }
                
                return _AddDatumFunc;
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
                                "fnGuiGraphCtrl_staticGetType"), typeof(_StaticGetType));
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
                                "fnGuiGraphCtrl_create"), typeof(_Create));
                }
                
                return _CreateFunc;
            }
        }
        #endregion

        /// <description>
        /// ( int plotID1, int plotID2, ... ) Set the scale of all specified plots to the maximum scale among them.
        /// </description>
        /// <param name="plotID1">Index of plotting curve.</param>
        /// <param name="plotID2">Index of plotting curve.</param>
        public void MatchScale(params string[] args) { 
            List<string> _argList = new List<string>() {"", ""};
            _argList.AddRange(args);

            StringVector nativeVecArgs = new StringVector {
                ElementCount = (uint)_argList.Count,
                Array = _argList.ToArray(),
                ArraySize = (uint)_argList.Count
            };
            nativeVecArgs.Alloc();
            InternalUnsafeMethods.MatchScale()(ObjectPtr, ref nativeVecArgs.internalStruct);
            nativeVecArgs.Free();

        }

        /// <description>
        /// Change the charting type of the given plotting curve.
        /// </description>
        /// <param name="plotId">Index of the plotting curve.  Must be 0<=plotId<6.</param>
        /// <param name="graphType">Charting type to use for the curve.</param>
        /// <remarks> Instead of calling this method, you can directly assign to #plotType.</remarks>
        public void SetGraphType(int plotId, GuiGraphType graphType) {
             InternalUnsafeMethods.SetGraphType__Args _args = new InternalUnsafeMethods.SetGraphType__Args() {
                plotId = plotId,
                graphType = (int)graphType,
             };
             InternalUnsafeMethods.SetGraphType()(ObjectPtr, _args);
        }

        /// <description>
        /// Stop automatic variable plotting for the given curve.
        /// </description>
        /// <param name="plotId">Index of the plotting curve.  Must be 0<=plotId<6.</param>
        public void RemoveAutoPlot(int plotId) {
             InternalUnsafeMethods.RemoveAutoPlot__Args _args = new InternalUnsafeMethods.RemoveAutoPlot__Args() {
                plotId = plotId,
             };
             InternalUnsafeMethods.RemoveAutoPlot()(ObjectPtr, _args);
        }

        /// <description>
        /// Sets up the given plotting curve to automatically plot the value of the<paramref name="" /> variable with a frequency of 
        /// </description>
        /// <param name="plotId">Index of the plotting curve.  Must be 0<=plotId<6.</param>
        /// <param name="variable">Name of the global variable.</param>
        /// <param name="updateFrequency">Frequency with which to add new data points to the plotting curve (in milliseconds).</param>
        /// <code>
        /// // Plot FPS counter at 1 second intervals.
        /// %graph.addAutoPlot( 0, "fps::real", 1000 );
        /// </code>
        public void AddAutoPlot(int plotId, string variable, int updateFrequency) {
             InternalUnsafeMethods.AddAutoPlot__Args _args = new InternalUnsafeMethods.AddAutoPlot__Args() {
                plotId = plotId,
                variable = variable,
                updateFrequency = updateFrequency,
             };
             InternalUnsafeMethods.AddAutoPlot()(ObjectPtr, _args);
        }

        /// <description>
        /// Get a data point on the given plotting curve.
        /// </description>
        /// <param name="plotId">Index of the plotting curve from which to fetch the data point.  Must be 0<=plotId<6.</param>
        /// <param name="index">Index of the data point on the curve.</param>
        /// <returns>The value of the data point or -1 if<paramref name="" /> plotId or </returns>
        public float GetDatum(int plotId, int index) {
             InternalUnsafeMethods.GetDatum__Args _args = new InternalUnsafeMethods.GetDatum__Args() {
                plotId = plotId,
                index = index,
             };
             float _engineResult = InternalUnsafeMethods.GetDatum()(ObjectPtr, _args);
             return _engineResult;
        }

        /// <description>
        /// Add a data point to the plot's curve.
        /// </description>
        /// <param name="plotId">Index of the plotting curve to which to add the data point.  Must be 0<=plotId<6.</param>
        /// <param name="value">Value of the data point to add to the curve.</param>
        /// <remarks> Data values are added to the </remarks>
        /// <remarks> A maximum number of 200 data points can be added to any single plotting curve at any one time.  If this limit is exceeded, data points on the right end of the curve are culled.</remarks>
        public void AddDatum(int plotId, float value) {
             InternalUnsafeMethods.AddDatum__Args _args = new InternalUnsafeMethods.AddDatum__Args() {
                plotId = plotId,
                value = value,
             };
             InternalUnsafeMethods.AddDatum()(ObjectPtr, _args);
        }

        /// <description>
        /// Get the type info object for the GuiGraphCtrl class.
        /// </description>
        /// <returns>The type info object for GuiGraphCtrl</returns>
        public static EngineTypeInfo StaticGetType() {
             InternalUnsafeMethods.StaticGetType__Args _args = new InternalUnsafeMethods.StaticGetType__Args() {
             };
             IntPtr _engineResult = InternalUnsafeMethods.StaticGetType()(_args);
             return new EngineTypeInfo(_engineResult);
        }


        /// <value>
        /// <description>
        /// Ratio of where to place the center coordinate of the graph on the Y axis. 0.5=middle height of control.
        /// 
        /// This allows to account for graphs that have only positive or only negative data points, for example.
        /// </description>
        /// </value>
        public float CenterY {
            get => GenericMarshal.StringTo<float>(GetFieldValue("centerY"));
            set => SetFieldValue("centerY", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Color to use for the plotting curves in the graph.
        /// </description>
        /// </value>
        public DynamicFieldVector<LinearColorF> PlotColor {
            get => new DynamicFieldVector<LinearColorF>(
                    this, 
                    "plotColor", 
                    6, 
                    val => GenericMarshal.StringTo<LinearColorF>(val),
                    obj => GenericMarshal.ToString(obj)
                );
        }


        /// <value>
        /// <description>
        /// Charting type of the plotting curves.
        /// </description>
        /// </value>
        public DynamicFieldVector<GuiGraphType> PlotType {
            get => new DynamicFieldVector<GuiGraphType>(
                    this, 
                    "plotType", 
                    6, 
                    val => GenericMarshal.StringTo<GuiGraphType>(val),
                    obj => GenericMarshal.ToString(obj)
                );
        }


        /// <value>
        /// <description>
        /// Name of the variable to automatically plot on the curves.  If empty, auto-plotting is disabled for the respective curve.
        /// </description>
        /// </value>
        public DynamicFieldVector<string> PlotVariable {
            get => new DynamicFieldVector<string>(
                    this, 
                    "plotVariable", 
                    6, 
                    val => GenericMarshal.StringTo<string>(val),
                    obj => GenericMarshal.ToString(obj)
                );
        }


        /// <value>
        /// <description>
        /// Interval between auto-plots of #plotVariable for the respective curve (in milliseconds).
        /// </description>
        /// </value>
        public DynamicFieldVector<int> PlotInterval {
            get => new DynamicFieldVector<int>(
                    this, 
                    "plotInterval", 
                    6, 
                    val => GenericMarshal.StringTo<int>(val),
                    obj => GenericMarshal.ToString(obj)
                );
        }
    }
}