using System;
using System.Collections.Generic;
using System.Runtime.InteropServices;
using T3DSharpFramework.Generated.Classes.Global;
using T3DSharpFramework.Generated.Classes.Net;
using T3DSharpFramework.Generated.Classes.Sim;
using T3DSharpFramework.Generated.Classes.Sim.Net;
using T3DSharpFramework.Generated.Enums.Global;
using T3DSharpFramework.Generated.Structs.Global;
using T3DSharpFramework.Generated.Structs.Gui;
using T3DSharpFramework.Generated.Structs.Math;
using T3DSharpFramework.Interop;

namespace T3DSharpFramework.Generated.Functions {

    public static unsafe class Global {

        #region UnsafeNativeMethods
        new internal struct InternalUnsafeMethods {
            [StructLayout(LayoutKind.Sequential)]
            internal struct CycleResources__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _CycleResources(CycleResources__Args args);
            private static _CycleResources _CycleResourcesFunc;
            internal static _CycleResources CycleResources() {
                if (_CycleResourcesFunc == null) {
                    _CycleResourcesFunc =
                        (_CycleResources)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fncycleResources"), typeof(_CycleResources));
                }
                
                return _CycleResourcesFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct IsKoreanBuild__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            [return: MarshalAs(UnmanagedType.I1)]
            internal delegate bool _IsKoreanBuild(IsKoreanBuild__Args args);
            private static _IsKoreanBuild _IsKoreanBuildFunc;
            internal static _IsKoreanBuild IsKoreanBuild() {
                if (_IsKoreanBuildFunc == null) {
                    _IsKoreanBuildFunc =
                        (_IsKoreanBuild)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnisKoreanBuild"), typeof(_IsKoreanBuild));
                }
                
                return _IsKoreanBuildFunc;
            }


            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _MathInit(ref StringVector.InternalStruct args);
            private static _MathInit _MathInitFunc;
            internal static _MathInit MathInit() {
                if (_MathInitFunc == null) {
                    _MathInitFunc =
                        (_MathInit)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnmathInit"), typeof(_MathInit));
                }
                
                return _MathInitFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct ShellExecute__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string executable;
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string args;
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string directory;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            [return: MarshalAs(UnmanagedType.I1)]
            internal delegate bool _ShellExecute(ShellExecute__Args args);
            private static _ShellExecute _ShellExecuteFunc;
            internal static _ShellExecute ShellExecute() {
                if (_ShellExecuteFunc == null) {
                    _ShellExecuteFunc =
                        (_ShellExecute)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnshellExecute"), typeof(_ShellExecute));
                }
                
                return _ShellExecuteFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct Rumble__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string device;
                internal float xRumble;
                internal float yRumble;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _Rumble(Rumble__Args args);
            private static _Rumble _RumbleFunc;
            internal static _Rumble Rumble() {
                if (_RumbleFunc == null) {
                    _RumbleFunc =
                        (_Rumble)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnrumble"), typeof(_Rumble));
                }
                
                return _RumbleFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct EchoInputState__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _EchoInputState(EchoInputState__Args args);
            private static _EchoInputState _EchoInputStateFunc;
            internal static _EchoInputState EchoInputState() {
                if (_EchoInputStateFunc == null) {
                    _EchoInputStateFunc =
                        (_EchoInputState)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnechoInputState"), typeof(_EchoInputState));
                }
                
                return _EchoInputStateFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct GetXInputState__Args
            {
                internal int controllerID;
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string properties;
                [MarshalAs(UnmanagedType.I1)]
                internal bool current;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate int _GetXInputState(GetXInputState__Args args);
            private static _GetXInputState _GetXInputStateFunc;
            internal static _GetXInputState GetXInputState() {
                if (_GetXInputStateFunc == null) {
                    _GetXInputStateFunc =
                        (_GetXInputState)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fngetXInputState"), typeof(_GetXInputState));
                }
                
                return _GetXInputStateFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct IsXInputConnected__Args
            {
                internal int controllerID;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            [return: MarshalAs(UnmanagedType.I1)]
            internal delegate bool _IsXInputConnected(IsXInputConnected__Args args);
            private static _IsXInputConnected _IsXInputConnectedFunc;
            internal static _IsXInputConnected IsXInputConnected() {
                if (_IsXInputConnectedFunc == null) {
                    _IsXInputConnectedFunc =
                        (_IsXInputConnected)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnisXInputConnected"), typeof(_IsXInputConnected));
                }
                
                return _IsXInputConnectedFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct ResetXInput__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _ResetXInput(ResetXInput__Args args);
            private static _ResetXInput _ResetXInputFunc;
            internal static _ResetXInput ResetXInput() {
                if (_ResetXInputFunc == null) {
                    _ResetXInputFunc =
                        (_ResetXInput)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnresetXInput"), typeof(_ResetXInput));
                }
                
                return _ResetXInputFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct DisableXInput__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _DisableXInput(DisableXInput__Args args);
            private static _DisableXInput _DisableXInputFunc;
            internal static _DisableXInput DisableXInput() {
                if (_DisableXInputFunc == null) {
                    _DisableXInputFunc =
                        (_DisableXInput)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fndisableXInput"), typeof(_DisableXInput));
                }
                
                return _DisableXInputFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct EnableXInput__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            [return: MarshalAs(UnmanagedType.I1)]
            internal delegate bool _EnableXInput(EnableXInput__Args args);
            private static _EnableXInput _EnableXInputFunc;
            internal static _EnableXInput EnableXInput() {
                if (_EnableXInputFunc == null) {
                    _EnableXInputFunc =
                        (_EnableXInput)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnenableXInput"), typeof(_EnableXInput));
                }
                
                return _EnableXInputFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct IsJoystickEnabled__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            [return: MarshalAs(UnmanagedType.I1)]
            internal delegate bool _IsJoystickEnabled(IsJoystickEnabled__Args args);
            private static _IsJoystickEnabled _IsJoystickEnabledFunc;
            internal static _IsJoystickEnabled IsJoystickEnabled() {
                if (_IsJoystickEnabledFunc == null) {
                    _IsJoystickEnabledFunc =
                        (_IsJoystickEnabled)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnisJoystickEnabled"), typeof(_IsJoystickEnabled));
                }
                
                return _IsJoystickEnabledFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct DisableJoystick__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _DisableJoystick(DisableJoystick__Args args);
            private static _DisableJoystick _DisableJoystickFunc;
            internal static _DisableJoystick DisableJoystick() {
                if (_DisableJoystickFunc == null) {
                    _DisableJoystickFunc =
                        (_DisableJoystick)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fndisableJoystick"), typeof(_DisableJoystick));
                }
                
                return _DisableJoystickFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct EnableJoystick__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            [return: MarshalAs(UnmanagedType.I1)]
            internal delegate bool _EnableJoystick(EnableJoystick__Args args);
            private static _EnableJoystick _EnableJoystickFunc;
            internal static _EnableJoystick EnableJoystick() {
                if (_EnableJoystickFunc == null) {
                    _EnableJoystickFunc =
                        (_EnableJoystick)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnenableJoystick"), typeof(_EnableJoystick));
                }
                
                return _EnableJoystickFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct EnableWinConsole__Args
            {
                [MarshalAs(UnmanagedType.I1)]
                internal bool flag;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _EnableWinConsole(EnableWinConsole__Args args);
            private static _EnableWinConsole _EnableWinConsoleFunc;
            internal static _EnableWinConsole EnableWinConsole() {
                if (_EnableWinConsoleFunc == null) {
                    _EnableWinConsoleFunc =
                        (_EnableWinConsole)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnenableWinConsole"), typeof(_EnableWinConsole));
                }
                
                return _EnableWinConsoleFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct InitDisplayDeviceInfo__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _InitDisplayDeviceInfo(InitDisplayDeviceInfo__Args args);
            private static _InitDisplayDeviceInfo _InitDisplayDeviceInfoFunc;
            internal static _InitDisplayDeviceInfo InitDisplayDeviceInfo() {
                if (_InitDisplayDeviceInfoFunc == null) {
                    _InitDisplayDeviceInfoFunc =
                        (_InitDisplayDeviceInfo)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fninitDisplayDeviceInfo"), typeof(_InitDisplayDeviceInfo));
                }
                
                return _InitDisplayDeviceInfoFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct GetServerPathSet__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate int _GetServerPathSet(GetServerPathSet__Args args);
            private static _GetServerPathSet _GetServerPathSetFunc;
            internal static _GetServerPathSet GetServerPathSet() {
                if (_GetServerPathSetFunc == null) {
                    _GetServerPathSetFunc =
                        (_GetServerPathSet)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fngetServerPathSet"), typeof(_GetServerPathSet));
                }
                
                return _GetServerPathSetFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct ShakeCamera__Args
            {
                internal float duration;
                internal float falloff;
                internal IntPtr amplitude;
                internal IntPtr frequency;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _ShakeCamera(ShakeCamera__Args args);
            private static _ShakeCamera _ShakeCameraFunc;
            internal static _ShakeCamera ShakeCamera() {
                if (_ShakeCameraFunc == null) {
                    _ShakeCameraFunc =
                        (_ShakeCamera)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnShakeCamera"), typeof(_ShakeCamera));
                }
                
                return _ShakeCameraFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct NavMeshUpdateOne__Args
            {
                internal int meshid;
                internal int objid;
                [MarshalAs(UnmanagedType.I1)]
                internal bool remove;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _NavMeshUpdateOne(NavMeshUpdateOne__Args args);
            private static _NavMeshUpdateOne _NavMeshUpdateOneFunc;
            internal static _NavMeshUpdateOne NavMeshUpdateOne() {
                if (_NavMeshUpdateOneFunc == null) {
                    _NavMeshUpdateOneFunc =
                        (_NavMeshUpdateOne)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnNavMeshUpdateOne"), typeof(_NavMeshUpdateOne));
                }
                
                return _NavMeshUpdateOneFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct NavMeshIgnore__Args
            {
                internal int objid;
                [MarshalAs(UnmanagedType.I1)]
                internal bool _ignore;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _NavMeshIgnore(NavMeshIgnore__Args args);
            private static _NavMeshIgnore _NavMeshIgnoreFunc;
            internal static _NavMeshIgnore NavMeshIgnore() {
                if (_NavMeshIgnoreFunc == null) {
                    _NavMeshIgnoreFunc =
                        (_NavMeshIgnore)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnNavMeshIgnore"), typeof(_NavMeshIgnore));
                }
                
                return _NavMeshIgnoreFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct NavMeshUpdateAroundObject__Args
            {
                internal int objid;
                [MarshalAs(UnmanagedType.I1)]
                internal bool remove;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _NavMeshUpdateAroundObject(NavMeshUpdateAroundObject__Args args);
            private static _NavMeshUpdateAroundObject _NavMeshUpdateAroundObjectFunc;
            internal static _NavMeshUpdateAroundObject NavMeshUpdateAroundObject() {
                if (_NavMeshUpdateAroundObjectFunc == null) {
                    _NavMeshUpdateAroundObjectFunc =
                        (_NavMeshUpdateAroundObject)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnNavMeshUpdateAroundObject"), typeof(_NavMeshUpdateAroundObject));
                }
                
                return _NavMeshUpdateAroundObjectFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct NavMeshUpdateAll__Args
            {
                internal int objid;
                [MarshalAs(UnmanagedType.I1)]
                internal bool remove;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _NavMeshUpdateAll(NavMeshUpdateAll__Args args);
            private static _NavMeshUpdateAll _NavMeshUpdateAllFunc;
            internal static _NavMeshUpdateAll NavMeshUpdateAll() {
                if (_NavMeshUpdateAllFunc == null) {
                    _NavMeshUpdateAllFunc =
                        (_NavMeshUpdateAll)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnNavMeshUpdateAll"), typeof(_NavMeshUpdateAll));
                }
                
                return _NavMeshUpdateAllFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct GetNavMeshEventManager__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate int _GetNavMeshEventManager(GetNavMeshEventManager__Args args);
            private static _GetNavMeshEventManager _GetNavMeshEventManagerFunc;
            internal static _GetNavMeshEventManager GetNavMeshEventManager() {
                if (_GetNavMeshEventManagerFunc == null) {
                    _GetNavMeshEventManagerFunc =
                        (_GetNavMeshEventManager)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fngetNavMeshEventManager"), typeof(_GetNavMeshEventManager));
                }
                
                return _GetNavMeshEventManagerFunc;
            }


            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            
            internal delegate IntPtr _ErrorThru(ref StringVector.InternalStruct args);
            private static _ErrorThru _ErrorThruFunc;
            internal static _ErrorThru ErrorThru() {
                if (_ErrorThruFunc == null) {
                    _ErrorThruFunc =
                        (_ErrorThru)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnerrorThru"), typeof(_ErrorThru));
                }
                
                return _ErrorThruFunc;
            }


            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            
            internal delegate IntPtr _WarnThru(ref StringVector.InternalStruct args);
            private static _WarnThru _WarnThruFunc;
            internal static _WarnThru WarnThru() {
                if (_WarnThruFunc == null) {
                    _WarnThruFunc =
                        (_WarnThru)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnwarnThru"), typeof(_WarnThru));
                }
                
                return _WarnThruFunc;
            }


            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            
            internal delegate IntPtr _EchoThru(ref StringVector.InternalStruct args);
            private static _EchoThru _EchoThruFunc;
            internal static _EchoThru EchoThru() {
                if (_EchoThruFunc == null) {
                    _EchoThruFunc =
                        (_EchoThru)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnechoThru"), typeof(_EchoThru));
                }
                
                return _EchoThruFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct GetMaxF__Args
            {
                internal float a;
                internal float b;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate float _GetMaxF(GetMaxF__Args args);
            private static _GetMaxF _GetMaxFFunc;
            internal static _GetMaxF GetMaxF() {
                if (_GetMaxFFunc == null) {
                    _GetMaxFFunc =
                        (_GetMaxF)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fngetMaxF"), typeof(_GetMaxF));
                }
                
                return _GetMaxFFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct GetMinF__Args
            {
                internal float a;
                internal float b;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate float _GetMinF(GetMinF__Args args);
            private static _GetMinF _GetMinFFunc;
            internal static _GetMinF GetMinF() {
                if (_GetMinFFunc == null) {
                    _GetMinFFunc =
                        (_GetMinF)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fngetMinF"), typeof(_GetMinF));
                }
                
                return _GetMinFFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct ColorScale__Args
            {
                internal IntPtr color;
                internal float scalar;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            
            internal delegate IntPtr _ColorScale(ColorScale__Args args);
            private static _ColorScale _ColorScaleFunc;
            internal static _ColorScale ColorScale() {
                if (_ColorScaleFunc == null) {
                    _ColorScaleFunc =
                        (_ColorScale)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnColorScale"), typeof(_ColorScale));
                }
                
                return _ColorScaleFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct GetColorFromHSV__Args
            {
                internal float hue;
                internal float sat;
                internal float val;
                internal float alpha;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            
            internal delegate IntPtr _GetColorFromHSV(GetColorFromHSV__Args args);
            private static _GetColorFromHSV _GetColorFromHSVFunc;
            internal static _GetColorFromHSV GetColorFromHSV() {
                if (_GetColorFromHSVFunc == null) {
                    _GetColorFromHSVFunc =
                        (_GetColorFromHSV)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fngetColorFromHSV"), typeof(_GetColorFromHSV));
                }
                
                return _GetColorFromHSVFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct WasSyntaxError__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            [return: MarshalAs(UnmanagedType.I1)]
            internal delegate bool _WasSyntaxError(WasSyntaxError__Args args);
            private static _WasSyntaxError _WasSyntaxErrorFunc;
            internal static _WasSyntaxError WasSyntaxError() {
                if (_WasSyntaxErrorFunc == null) {
                    _WasSyntaxErrorFunc =
                        (_WasSyntaxError)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnwasSyntaxError"), typeof(_WasSyntaxError));
                }
                
                return _WasSyntaxErrorFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct TouchDataBlocks__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _TouchDataBlocks(TouchDataBlocks__Args args);
            private static _TouchDataBlocks _TouchDataBlocksFunc;
            internal static _TouchDataBlocks TouchDataBlocks() {
                if (_TouchDataBlocksFunc == null) {
                    _TouchDataBlocksFunc =
                        (_TouchDataBlocks)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fntouchDataBlocks"), typeof(_TouchDataBlocks));
                }
                
                return _TouchDataBlocksFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct MarkDataBlocks__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _MarkDataBlocks(MarkDataBlocks__Args args);
            private static _MarkDataBlocks _MarkDataBlocksFunc;
            internal static _MarkDataBlocks MarkDataBlocks() {
                if (_MarkDataBlocksFunc == null) {
                    _MarkDataBlocksFunc =
                        (_MarkDataBlocks)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnmarkDataBlocks"), typeof(_MarkDataBlocks));
                }
                
                return _MarkDataBlocksFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct GetFreeTargetPosition__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate Point3F.InternalStruct _GetFreeTargetPosition(GetFreeTargetPosition__Args args);
            private static _GetFreeTargetPosition _GetFreeTargetPositionFunc;
            internal static _GetFreeTargetPosition GetFreeTargetPosition() {
                if (_GetFreeTargetPositionFunc == null) {
                    _GetFreeTargetPositionFunc =
                        (_GetFreeTargetPosition)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fngetFreeTargetPosition"), typeof(_GetFreeTargetPosition));
                }
                
                return _GetFreeTargetPositionFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct MoveTransformRel__Args
            {
                internal IntPtr xfrm;
                internal IntPtr pos;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate MatrixF.InternalStruct _MoveTransformRel(MoveTransformRel__Args args);
            private static _MoveTransformRel _MoveTransformRelFunc;
            internal static _MoveTransformRel MoveTransformRel() {
                if (_MoveTransformRelFunc == null) {
                    _MoveTransformRelFunc =
                        (_MoveTransformRel)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnmoveTransformRel"), typeof(_MoveTransformRel));
                }
                
                return _MoveTransformRelFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct MoveTransformAbs__Args
            {
                internal IntPtr xfrm;
                internal IntPtr pos;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate MatrixF.InternalStruct _MoveTransformAbs(MoveTransformAbs__Args args);
            private static _MoveTransformAbs _MoveTransformAbsFunc;
            internal static _MoveTransformAbs MoveTransformAbs() {
                if (_MoveTransformAbsFunc == null) {
                    _MoveTransformAbsFunc =
                        (_MoveTransformAbs)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnmoveTransformAbs"), typeof(_MoveTransformAbs));
                }
                
                return _MoveTransformAbsFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct MatrixInverseMulVector__Args
            {
                internal IntPtr xfrm;
                internal IntPtr vector;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate Point3F.InternalStruct _MatrixInverseMulVector(MatrixInverseMulVector__Args args);
            private static _MatrixInverseMulVector _MatrixInverseMulVectorFunc;
            internal static _MatrixInverseMulVector MatrixInverseMulVector() {
                if (_MatrixInverseMulVectorFunc == null) {
                    _MatrixInverseMulVectorFunc =
                        (_MatrixInverseMulVector)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnMatrixInverseMulVector"), typeof(_MatrixInverseMulVector));
                }
                
                return _MatrixInverseMulVectorFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct GetRandomDir__Args
            {
                internal IntPtr axis;
                internal float thetaMin;
                internal float thetaMax;
                internal float phiMin;
                internal float phiMax;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate Point3F.InternalStruct _GetRandomDir(GetRandomDir__Args args);
            private static _GetRandomDir _GetRandomDirFunc;
            internal static _GetRandomDir GetRandomDir() {
                if (_GetRandomDirFunc == null) {
                    _GetRandomDirFunc =
                        (_GetRandomDir)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fngetRandomDir"), typeof(_GetRandomDir));
                }
                
                return _GetRandomDirFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct GetRandomF__Args
            {
                internal float a;
                internal float b;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate float _GetRandomF(GetRandomF__Args args);
            private static _GetRandomF _GetRandomFFunc;
            internal static _GetRandomF GetRandomF() {
                if (_GetRandomFFunc == null) {
                    _GetRandomFFunc =
                        (_GetRandomF)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fngetRandomF"), typeof(_GetRandomF));
                }
                
                return _GetRandomFFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct RolloverRayCast__Args
            {
                internal IntPtr start;
                internal IntPtr end;
                internal uint mask;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate int _RolloverRayCast(RolloverRayCast__Args args);
            private static _RolloverRayCast _RolloverRayCastFunc;
            internal static _RolloverRayCast RolloverRayCast() {
                if (_RolloverRayCastFunc == null) {
                    _RolloverRayCastFunc =
                        (_RolloverRayCast)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnrolloverRayCast"), typeof(_RolloverRayCast));
                }
                
                return _RolloverRayCastFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct AfxGetEngine__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            
            internal delegate IntPtr _AfxGetEngine(AfxGetEngine__Args args);
            private static _AfxGetEngine _AfxGetEngineFunc;
            internal static _AfxGetEngine AfxGetEngine() {
                if (_AfxGetEngineFunc == null) {
                    _AfxGetEngineFunc =
                        (_AfxGetEngine)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnafxGetEngine"), typeof(_AfxGetEngine));
                }
                
                return _AfxGetEngineFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct AfxGetVersion__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            
            internal delegate IntPtr _AfxGetVersion(AfxGetVersion__Args args);
            private static _AfxGetVersion _AfxGetVersionFunc;
            internal static _AfxGetVersion AfxGetVersion() {
                if (_AfxGetVersionFunc == null) {
                    _AfxGetVersionFunc =
                        (_AfxGetVersion)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnafxGetVersion"), typeof(_AfxGetVersion));
                }
                
                return _AfxGetVersionFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct AfxEndMissionNotify__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _AfxEndMissionNotify(AfxEndMissionNotify__Args args);
            private static _AfxEndMissionNotify _AfxEndMissionNotifyFunc;
            internal static _AfxEndMissionNotify AfxEndMissionNotify() {
                if (_AfxEndMissionNotifyFunc == null) {
                    _AfxEndMissionNotifyFunc =
                        (_AfxEndMissionNotify)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnafxEndMissionNotify"), typeof(_AfxEndMissionNotify));
                }
                
                return _AfxEndMissionNotifyFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct StartSelectron__Args
            {
                internal IntPtr selectedObj;
                internal uint subcode;
                internal IntPtr extra;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate int _StartSelectron(StartSelectron__Args args);
            private static _StartSelectron _StartSelectronFunc;
            internal static _StartSelectron StartSelectron() {
                if (_StartSelectronFunc == null) {
                    _StartSelectronFunc =
                        (_StartSelectron)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnstartSelectron"), typeof(_StartSelectron));
                }
                
                return _StartSelectronFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct CastSpell__Args
            {
                internal IntPtr datablock;
                internal IntPtr caster;
                internal IntPtr target;
                internal IntPtr extra;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate int _CastSpell(CastSpell__Args args);
            private static _CastSpell _CastSpellFunc;
            internal static _CastSpell CastSpell() {
                if (_CastSpellFunc == null) {
                    _CastSpellFunc =
                        (_CastSpell)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fncastSpell"), typeof(_CastSpell));
                }
                
                return _CastSpellFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct DisplayScreenMessage__Args
            {
                internal IntPtr client;
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string message;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _DisplayScreenMessage(DisplayScreenMessage__Args args);
            private static _DisplayScreenMessage _DisplayScreenMessageFunc;
            internal static _DisplayScreenMessage DisplayScreenMessage() {
                if (_DisplayScreenMessageFunc == null) {
                    _DisplayScreenMessageFunc =
                        (_DisplayScreenMessage)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "cbDisplayScreenMessage"), typeof(_DisplayScreenMessage));
                }
                
                return _DisplayScreenMessageFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct OnCastingEnd__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _OnCastingEnd(OnCastingEnd__Args args);
            private static _OnCastingEnd _OnCastingEndFunc;
            internal static _OnCastingEnd OnCastingEnd() {
                if (_OnCastingEndFunc == null) {
                    _OnCastingEndFunc =
                        (_OnCastingEnd)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "cbonCastingEnd"), typeof(_OnCastingEnd));
                }
                
                return _OnCastingEndFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct OnCastingProgressUpdate__Args
            {
                internal float frac;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _OnCastingProgressUpdate(OnCastingProgressUpdate__Args args);
            private static _OnCastingProgressUpdate _OnCastingProgressUpdateFunc;
            internal static _OnCastingProgressUpdate OnCastingProgressUpdate() {
                if (_OnCastingProgressUpdateFunc == null) {
                    _OnCastingProgressUpdateFunc =
                        (_OnCastingProgressUpdate)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "cbonCastingProgressUpdate"), typeof(_OnCastingProgressUpdate));
                }
                
                return _OnCastingProgressUpdateFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct OnCastingStart__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _OnCastingStart(OnCastingStart__Args args);
            private static _OnCastingStart _OnCastingStartFunc;
            internal static _OnCastingStart OnCastingStart() {
                if (_OnCastingStartFunc == null) {
                    _OnCastingStartFunc =
                        (_OnCastingStart)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "cbonCastingStart"), typeof(_OnCastingStart));
                }
                
                return _OnCastingStartFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct StartEffectron__Args
            {
                internal IntPtr datablock;
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string constraintSource;
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string constraintName;
                internal IntPtr extra;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate int _StartEffectron(StartEffectron__Args args);
            private static _StartEffectron _StartEffectronFunc;
            internal static _StartEffectron StartEffectron() {
                if (_StartEffectronFunc == null) {
                    _StartEffectronFunc =
                        (_StartEffectron)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnstartEffectron"), typeof(_StartEffectron));
                }
                
                return _StartEffectronFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct OnSDLDeviceDisconnected__Args
            {
                internal int sdlIndex;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _OnSDLDeviceDisconnected(OnSDLDeviceDisconnected__Args args);
            private static _OnSDLDeviceDisconnected _OnSDLDeviceDisconnectedFunc;
            internal static _OnSDLDeviceDisconnected OnSDLDeviceDisconnected() {
                if (_OnSDLDeviceDisconnectedFunc == null) {
                    _OnSDLDeviceDisconnectedFunc =
                        (_OnSDLDeviceDisconnected)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "cbonSDLDeviceDisconnected"), typeof(_OnSDLDeviceDisconnected));
                }
                
                return _OnSDLDeviceDisconnectedFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct OnSDLDeviceConnected__Args
            {
                internal int sdlIndex;
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string deviceName;
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string deviceType;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _OnSDLDeviceConnected(OnSDLDeviceConnected__Args args);
            private static _OnSDLDeviceConnected _OnSDLDeviceConnectedFunc;
            internal static _OnSDLDeviceConnected OnSDLDeviceConnected() {
                if (_OnSDLDeviceConnectedFunc == null) {
                    _OnSDLDeviceConnectedFunc =
                        (_OnSDLDeviceConnected)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "cbonSDLDeviceConnected"), typeof(_OnSDLDeviceConnected));
                }
                
                return _OnSDLDeviceConnectedFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct SetShadowVizLight__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string name;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            
            internal delegate IntPtr _SetShadowVizLight(SetShadowVizLight__Args args);
            private static _SetShadowVizLight _SetShadowVizLightFunc;
            internal static _SetShadowVizLight SetShadowVizLight() {
                if (_SetShadowVizLightFunc == null) {
                    _SetShadowVizLightFunc =
                        (_SetShadowVizLight)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnsetShadowVizLight"), typeof(_SetShadowVizLight));
                }
                
                return _SetShadowVizLightFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct IsSupportedFormat__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string extension;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            [return: MarshalAs(UnmanagedType.I1)]
            internal delegate bool _IsSupportedFormat(IsSupportedFormat__Args args);
            private static _IsSupportedFormat _IsSupportedFormatFunc;
            internal static _IsSupportedFormat IsSupportedFormat() {
                if (_IsSupportedFormatFunc == null) {
                    _IsSupportedFormatFunc =
                        (_IsSupportedFormat)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnisSupportedFormat"), typeof(_IsSupportedFormat));
                }
                
                return _IsSupportedFormatFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct GetFormatFilters__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            
            internal delegate IntPtr _GetFormatFilters(GetFormatFilters__Args args);
            private static _GetFormatFilters _GetFormatFiltersFunc;
            internal static _GetFormatFilters GetFormatFilters() {
                if (_GetFormatFiltersFunc == null) {
                    _GetFormatFiltersFunc =
                        (_GetFormatFilters)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fngetFormatFilters"), typeof(_GetFormatFilters));
                }
                
                return _GetFormatFiltersFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct GetFormatExtensions__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            
            internal delegate IntPtr _GetFormatExtensions(GetFormatExtensions__Args args);
            private static _GetFormatExtensions _GetFormatExtensionsFunc;
            internal static _GetFormatExtensions GetFormatExtensions() {
                if (_GetFormatExtensionsFunc == null) {
                    _GetFormatExtensionsFunc =
                        (_GetFormatExtensions)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fngetFormatExtensions"), typeof(_GetFormatExtensions));
                }
                
                return _GetFormatExtensionsFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct GetShapeInfo__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string shapePath;
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string ctrl;
                [MarshalAs(UnmanagedType.I1)]
                internal bool loadCachedDts;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            [return: MarshalAs(UnmanagedType.I1)]
            internal delegate bool _GetShapeInfo(GetShapeInfo__Args args);
            private static _GetShapeInfo _GetShapeInfoFunc;
            internal static _GetShapeInfo GetShapeInfo() {
                if (_GetShapeInfoFunc == null) {
                    _GetShapeInfoFunc =
                        (_GetShapeInfo)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnGetShapeInfo"), typeof(_GetShapeInfo));
                }
                
                return _GetShapeInfoFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct LoadColladaLights__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string filename;
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string parentGroup;
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string baseObject;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            [return: MarshalAs(UnmanagedType.I1)]
            internal delegate bool _LoadColladaLights(LoadColladaLights__Args args);
            private static _LoadColladaLights _LoadColladaLightsFunc;
            internal static _LoadColladaLights LoadColladaLights() {
                if (_LoadColladaLightsFunc == null) {
                    _LoadColladaLightsFunc =
                        (_LoadColladaLights)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnloadColladaLights"), typeof(_LoadColladaLights));
                }
                
                return _LoadColladaLightsFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct EnumColladaForImport__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string shapePath;
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string ctrl;
                [MarshalAs(UnmanagedType.I1)]
                internal bool loadCachedDts;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            [return: MarshalAs(UnmanagedType.I1)]
            internal delegate bool _EnumColladaForImport(EnumColladaForImport__Args args);
            private static _EnumColladaForImport _EnumColladaForImportFunc;
            internal static _EnumColladaForImport EnumColladaForImport() {
                if (_EnumColladaForImportFunc == null) {
                    _EnumColladaForImportFunc =
                        (_EnumColladaForImport)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnenumColladaForImport"), typeof(_EnumColladaForImport));
                }
                
                return _EnumColladaForImportFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct GenerateTamlSchema__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            [return: MarshalAs(UnmanagedType.I1)]
            internal delegate bool _GenerateTamlSchema(GenerateTamlSchema__Args args);
            private static _GenerateTamlSchema _GenerateTamlSchemaFunc;
            internal static _GenerateTamlSchema GenerateTamlSchema() {
                if (_GenerateTamlSchemaFunc == null) {
                    _GenerateTamlSchemaFunc =
                        (_GenerateTamlSchema)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnGenerateTamlSchema"), typeof(_GenerateTamlSchema));
                }
                
                return _GenerateTamlSchemaFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct TamlRead__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string filename;
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string format;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            
            internal delegate IntPtr _TamlRead(TamlRead__Args args);
            private static _TamlRead _TamlReadFunc;
            internal static _TamlRead TamlRead() {
                if (_TamlReadFunc == null) {
                    _TamlReadFunc =
                        (_TamlRead)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnTamlRead"), typeof(_TamlRead));
                }
                
                return _TamlReadFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct TamlWrite__Args
            {
                internal IntPtr simObject;
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string filename;
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string format;
                [MarshalAs(UnmanagedType.I1)]
                internal bool compressed;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            [return: MarshalAs(UnmanagedType.I1)]
            internal delegate bool _TamlWrite(TamlWrite__Args args);
            private static _TamlWrite _TamlWriteFunc;
            internal static _TamlWrite TamlWrite() {
                if (_TamlWriteFunc == null) {
                    _TamlWriteFunc =
                        (_TamlWrite)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnTamlWrite"), typeof(_TamlWrite));
                }
                
                return _TamlWriteFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct DumpProcessList__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _DumpProcessList(DumpProcessList__Args args);
            private static _DumpProcessList _DumpProcessListFunc;
            internal static _DumpProcessList DumpProcessList() {
                if (_DumpProcessListFunc == null) {
                    _DumpProcessListFunc =
                        (_DumpProcessList)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fndumpProcessList"), typeof(_DumpProcessList));
                }
                
                return _DumpProcessListFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct SetDatablockCacheCRC__Args
            {
                internal uint crc;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _SetDatablockCacheCRC(SetDatablockCacheCRC__Args args);
            private static _SetDatablockCacheCRC _SetDatablockCacheCRCFunc;
            internal static _SetDatablockCacheCRC SetDatablockCacheCRC() {
                if (_SetDatablockCacheCRCFunc == null) {
                    _SetDatablockCacheCRCFunc =
                        (_SetDatablockCacheCRC)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnsetDatablockCacheCRC"), typeof(_SetDatablockCacheCRC));
                }
                
                return _SetDatablockCacheCRCFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct ExtractDatablockCacheCRC__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string fileName;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate int _ExtractDatablockCacheCRC(ExtractDatablockCacheCRC__Args args);
            private static _ExtractDatablockCacheCRC _ExtractDatablockCacheCRCFunc;
            internal static _ExtractDatablockCacheCRC ExtractDatablockCacheCRC() {
                if (_ExtractDatablockCacheCRCFunc == null) {
                    _ExtractDatablockCacheCRCFunc =
                        (_ExtractDatablockCacheCRC)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnextractDatablockCacheCRC"), typeof(_ExtractDatablockCacheCRC));
                }
                
                return _ExtractDatablockCacheCRCFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct GetDatablockCacheCRC__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate int _GetDatablockCacheCRC(GetDatablockCacheCRC__Args args);
            private static _GetDatablockCacheCRC _GetDatablockCacheCRCFunc;
            internal static _GetDatablockCacheCRC GetDatablockCacheCRC() {
                if (_GetDatablockCacheCRCFunc == null) {
                    _GetDatablockCacheCRCFunc =
                        (_GetDatablockCacheCRC)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fngetDatablockCacheCRC"), typeof(_GetDatablockCacheCRC));
                }
                
                return _GetDatablockCacheCRCFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct IsDatablockCacheSaved__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            [return: MarshalAs(UnmanagedType.I1)]
            internal delegate bool _IsDatablockCacheSaved(IsDatablockCacheSaved__Args args);
            private static _IsDatablockCacheSaved _IsDatablockCacheSavedFunc;
            internal static _IsDatablockCacheSaved IsDatablockCacheSaved() {
                if (_IsDatablockCacheSavedFunc == null) {
                    _IsDatablockCacheSavedFunc =
                        (_IsDatablockCacheSaved)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnisDatablockCacheSaved"), typeof(_IsDatablockCacheSaved));
                }
                
                return _IsDatablockCacheSavedFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct ResetDatablockCache__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _ResetDatablockCache(ResetDatablockCache__Args args);
            private static _ResetDatablockCache _ResetDatablockCacheFunc;
            internal static _ResetDatablockCache ResetDatablockCache() {
                if (_ResetDatablockCacheFunc == null) {
                    _ResetDatablockCacheFunc =
                        (_ResetDatablockCache)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnresetDatablockCache"), typeof(_ResetDatablockCache));
                }
                
                return _ResetDatablockCacheFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct OnDataBlockObjectReceived__Args
            {
                internal uint index;
                internal uint total;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _OnDataBlockObjectReceived(OnDataBlockObjectReceived__Args args);
            private static _OnDataBlockObjectReceived _OnDataBlockObjectReceivedFunc;
            internal static _OnDataBlockObjectReceived OnDataBlockObjectReceived() {
                if (_OnDataBlockObjectReceivedFunc == null) {
                    _OnDataBlockObjectReceivedFunc =
                        (_OnDataBlockObjectReceived)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "cbonDataBlockObjectReceived"), typeof(_OnDataBlockObjectReceived));
                }
                
                return _OnDataBlockObjectReceivedFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct DecalManagerEditDecal__Args
            {
                internal int decalID;
                internal IntPtr pos;
                internal IntPtr normal;
                internal float rotAroundNormal;
                internal float decalScale;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            [return: MarshalAs(UnmanagedType.I1)]
            internal delegate bool _DecalManagerEditDecal(DecalManagerEditDecal__Args args);
            private static _DecalManagerEditDecal _DecalManagerEditDecalFunc;
            internal static _DecalManagerEditDecal DecalManagerEditDecal() {
                if (_DecalManagerEditDecalFunc == null) {
                    _DecalManagerEditDecalFunc =
                        (_DecalManagerEditDecal)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fndecalManagerEditDecal"), typeof(_DecalManagerEditDecal));
                }
                
                return _DecalManagerEditDecalFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct DecalManagerRemoveDecal__Args
            {
                internal int decalID;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            [return: MarshalAs(UnmanagedType.I1)]
            internal delegate bool _DecalManagerRemoveDecal(DecalManagerRemoveDecal__Args args);
            private static _DecalManagerRemoveDecal _DecalManagerRemoveDecalFunc;
            internal static _DecalManagerRemoveDecal DecalManagerRemoveDecal() {
                if (_DecalManagerRemoveDecalFunc == null) {
                    _DecalManagerRemoveDecalFunc =
                        (_DecalManagerRemoveDecal)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fndecalManagerRemoveDecal"), typeof(_DecalManagerRemoveDecal));
                }
                
                return _DecalManagerRemoveDecalFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct DecalManagerAddDecal__Args
            {
                internal IntPtr position;
                internal IntPtr normal;
                internal float rot;
                internal float scale;
                internal IntPtr decalData;
                [MarshalAs(UnmanagedType.I1)]
                internal bool isImmortal;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate int _DecalManagerAddDecal(DecalManagerAddDecal__Args args);
            private static _DecalManagerAddDecal _DecalManagerAddDecalFunc;
            internal static _DecalManagerAddDecal DecalManagerAddDecal() {
                if (_DecalManagerAddDecalFunc == null) {
                    _DecalManagerAddDecalFunc =
                        (_DecalManagerAddDecal)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fndecalManagerAddDecal"), typeof(_DecalManagerAddDecal));
                }
                
                return _DecalManagerAddDecalFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct DecalManagerClear__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _DecalManagerClear(DecalManagerClear__Args args);
            private static _DecalManagerClear _DecalManagerClearFunc;
            internal static _DecalManagerClear DecalManagerClear() {
                if (_DecalManagerClearFunc == null) {
                    _DecalManagerClearFunc =
                        (_DecalManagerClear)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fndecalManagerClear"), typeof(_DecalManagerClear));
                }
                
                return _DecalManagerClearFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct DecalManagerDirty__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            [return: MarshalAs(UnmanagedType.I1)]
            internal delegate bool _DecalManagerDirty(DecalManagerDirty__Args args);
            private static _DecalManagerDirty _DecalManagerDirtyFunc;
            internal static _DecalManagerDirty DecalManagerDirty() {
                if (_DecalManagerDirtyFunc == null) {
                    _DecalManagerDirtyFunc =
                        (_DecalManagerDirty)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fndecalManagerDirty"), typeof(_DecalManagerDirty));
                }
                
                return _DecalManagerDirtyFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct DecalManagerLoad__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string fileName;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            [return: MarshalAs(UnmanagedType.I1)]
            internal delegate bool _DecalManagerLoad(DecalManagerLoad__Args args);
            private static _DecalManagerLoad _DecalManagerLoadFunc;
            internal static _DecalManagerLoad DecalManagerLoad() {
                if (_DecalManagerLoadFunc == null) {
                    _DecalManagerLoadFunc =
                        (_DecalManagerLoad)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fndecalManagerLoad"), typeof(_DecalManagerLoad));
                }
                
                return _DecalManagerLoadFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct DecalManagerSave__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string decalSaveFile;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _DecalManagerSave(DecalManagerSave__Args args);
            private static _DecalManagerSave _DecalManagerSaveFunc;
            internal static _DecalManagerSave DecalManagerSave() {
                if (_DecalManagerSaveFunc == null) {
                    _DecalManagerSaveFunc =
                        (_DecalManagerSave)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fndecalManagerSave"), typeof(_DecalManagerSave));
                }
                
                return _DecalManagerSaveFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct PhysicsDebugDraw__Args
            {
                [MarshalAs(UnmanagedType.I1)]
                internal bool enable;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _PhysicsDebugDraw(PhysicsDebugDraw__Args args);
            private static _PhysicsDebugDraw _PhysicsDebugDrawFunc;
            internal static _PhysicsDebugDraw PhysicsDebugDraw() {
                if (_PhysicsDebugDrawFunc == null) {
                    _PhysicsDebugDrawFunc =
                        (_PhysicsDebugDraw)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnphysicsDebugDraw"), typeof(_PhysicsDebugDraw));
                }
                
                return _PhysicsDebugDrawFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct PhysicsRestoreState__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _PhysicsRestoreState(PhysicsRestoreState__Args args);
            private static _PhysicsRestoreState _PhysicsRestoreStateFunc;
            internal static _PhysicsRestoreState PhysicsRestoreState() {
                if (_PhysicsRestoreStateFunc == null) {
                    _PhysicsRestoreStateFunc =
                        (_PhysicsRestoreState)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnphysicsRestoreState"), typeof(_PhysicsRestoreState));
                }
                
                return _PhysicsRestoreStateFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct PhysicsStoreState__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _PhysicsStoreState(PhysicsStoreState__Args args);
            private static _PhysicsStoreState _PhysicsStoreStateFunc;
            internal static _PhysicsStoreState PhysicsStoreState() {
                if (_PhysicsStoreStateFunc == null) {
                    _PhysicsStoreStateFunc =
                        (_PhysicsStoreState)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnphysicsStoreState"), typeof(_PhysicsStoreState));
                }
                
                return _PhysicsStoreStateFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct PhysicsGetTimeScale__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate float _PhysicsGetTimeScale(PhysicsGetTimeScale__Args args);
            private static _PhysicsGetTimeScale _PhysicsGetTimeScaleFunc;
            internal static _PhysicsGetTimeScale PhysicsGetTimeScale() {
                if (_PhysicsGetTimeScaleFunc == null) {
                    _PhysicsGetTimeScaleFunc =
                        (_PhysicsGetTimeScale)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnphysicsGetTimeScale"), typeof(_PhysicsGetTimeScale));
                }
                
                return _PhysicsGetTimeScaleFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct PhysicsSetTimeScale__Args
            {
                internal float scale;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _PhysicsSetTimeScale(PhysicsSetTimeScale__Args args);
            private static _PhysicsSetTimeScale _PhysicsSetTimeScaleFunc;
            internal static _PhysicsSetTimeScale PhysicsSetTimeScale() {
                if (_PhysicsSetTimeScaleFunc == null) {
                    _PhysicsSetTimeScaleFunc =
                        (_PhysicsSetTimeScale)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnphysicsSetTimeScale"), typeof(_PhysicsSetTimeScale));
                }
                
                return _PhysicsSetTimeScaleFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct PhysicsSimulationEnabled__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            [return: MarshalAs(UnmanagedType.I1)]
            internal delegate bool _PhysicsSimulationEnabled(PhysicsSimulationEnabled__Args args);
            private static _PhysicsSimulationEnabled _PhysicsSimulationEnabledFunc;
            internal static _PhysicsSimulationEnabled PhysicsSimulationEnabled() {
                if (_PhysicsSimulationEnabledFunc == null) {
                    _PhysicsSimulationEnabledFunc =
                        (_PhysicsSimulationEnabled)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnphysicsSimulationEnabled"), typeof(_PhysicsSimulationEnabled));
                }
                
                return _PhysicsSimulationEnabledFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct PhysicsStopSimulation__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string worldName;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _PhysicsStopSimulation(PhysicsStopSimulation__Args args);
            private static _PhysicsStopSimulation _PhysicsStopSimulationFunc;
            internal static _PhysicsStopSimulation PhysicsStopSimulation() {
                if (_PhysicsStopSimulationFunc == null) {
                    _PhysicsStopSimulationFunc =
                        (_PhysicsStopSimulation)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnphysicsStopSimulation"), typeof(_PhysicsStopSimulation));
                }
                
                return _PhysicsStopSimulationFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct PhysicsStartSimulation__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string worldName;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _PhysicsStartSimulation(PhysicsStartSimulation__Args args);
            private static _PhysicsStartSimulation _PhysicsStartSimulationFunc;
            internal static _PhysicsStartSimulation PhysicsStartSimulation() {
                if (_PhysicsStartSimulationFunc == null) {
                    _PhysicsStartSimulationFunc =
                        (_PhysicsStartSimulation)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnphysicsStartSimulation"), typeof(_PhysicsStartSimulation));
                }
                
                return _PhysicsStartSimulationFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct PhysicsDestroyWorld__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string worldName;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _PhysicsDestroyWorld(PhysicsDestroyWorld__Args args);
            private static _PhysicsDestroyWorld _PhysicsDestroyWorldFunc;
            internal static _PhysicsDestroyWorld PhysicsDestroyWorld() {
                if (_PhysicsDestroyWorldFunc == null) {
                    _PhysicsDestroyWorldFunc =
                        (_PhysicsDestroyWorld)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnphysicsDestroyWorld"), typeof(_PhysicsDestroyWorld));
                }
                
                return _PhysicsDestroyWorldFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct PhysicsInitWorld__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string worldName;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            [return: MarshalAs(UnmanagedType.I1)]
            internal delegate bool _PhysicsInitWorld(PhysicsInitWorld__Args args);
            private static _PhysicsInitWorld _PhysicsInitWorldFunc;
            internal static _PhysicsInitWorld PhysicsInitWorld() {
                if (_PhysicsInitWorldFunc == null) {
                    _PhysicsInitWorldFunc =
                        (_PhysicsInitWorld)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnphysicsInitWorld"), typeof(_PhysicsInitWorld));
                }
                
                return _PhysicsInitWorldFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct PhysicsDestroy__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _PhysicsDestroy(PhysicsDestroy__Args args);
            private static _PhysicsDestroy _PhysicsDestroyFunc;
            internal static _PhysicsDestroy PhysicsDestroy() {
                if (_PhysicsDestroyFunc == null) {
                    _PhysicsDestroyFunc =
                        (_PhysicsDestroy)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnphysicsDestroy"), typeof(_PhysicsDestroy));
                }
                
                return _PhysicsDestroyFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct PhysicsInit__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string library;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            [return: MarshalAs(UnmanagedType.I1)]
            internal delegate bool _PhysicsInit(PhysicsInit__Args args);
            private static _PhysicsInit _PhysicsInitFunc;
            internal static _PhysicsInit PhysicsInit() {
                if (_PhysicsInitFunc == null) {
                    _PhysicsInitFunc =
                        (_PhysicsInit)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnphysicsInit"), typeof(_PhysicsInit));
                }
                
                return _PhysicsInitFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct PhysicsPluginPresent__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            [return: MarshalAs(UnmanagedType.I1)]
            internal delegate bool _PhysicsPluginPresent(PhysicsPluginPresent__Args args);
            private static _PhysicsPluginPresent _PhysicsPluginPresentFunc;
            internal static _PhysicsPluginPresent PhysicsPluginPresent() {
                if (_PhysicsPluginPresentFunc == null) {
                    _PhysicsPluginPresentFunc =
                        (_PhysicsPluginPresent)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnphysicsPluginPresent"), typeof(_PhysicsPluginPresent));
                }
                
                return _PhysicsPluginPresentFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct StartClientReplication__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _StartClientReplication(StartClientReplication__Args args);
            private static _StartClientReplication _StartClientReplicationFunc;
            internal static _StartClientReplication StartClientReplication() {
                if (_StartClientReplicationFunc == null) {
                    _StartClientReplicationFunc =
                        (_StartClientReplication)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnStartClientReplication"), typeof(_StartClientReplication));
                }
                
                return _StartClientReplicationFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct StartFoliageReplication__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _StartFoliageReplication(StartFoliageReplication__Args args);
            private static _StartFoliageReplication _StartFoliageReplicationFunc;
            internal static _StartFoliageReplication StartFoliageReplication() {
                if (_StartFoliageReplicationFunc == null) {
                    _StartFoliageReplicationFunc =
                        (_StartFoliageReplication)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnStartFoliageReplication"), typeof(_StartFoliageReplication));
                }
                
                return _StartFoliageReplicationFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct CalcExplosionCoverage__Args
            {
                internal IntPtr pos;
                internal int id;
                internal uint covMask;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate float _CalcExplosionCoverage(CalcExplosionCoverage__Args args);
            private static _CalcExplosionCoverage _CalcExplosionCoverageFunc;
            internal static _CalcExplosionCoverage CalcExplosionCoverage() {
                if (_CalcExplosionCoverageFunc == null) {
                    _CalcExplosionCoverageFunc =
                        (_CalcExplosionCoverage)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fncalcExplosionCoverage"), typeof(_CalcExplosionCoverage));
                }
                
                return _CalcExplosionCoverageFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct GetMissionAreaServerObject__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate IntPtr _GetMissionAreaServerObject(GetMissionAreaServerObject__Args args);
            private static _GetMissionAreaServerObject _GetMissionAreaServerObjectFunc;
            internal static _GetMissionAreaServerObject GetMissionAreaServerObject() {
                if (_GetMissionAreaServerObjectFunc == null) {
                    _GetMissionAreaServerObjectFunc =
                        (_GetMissionAreaServerObject)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fngetMissionAreaServerObject"), typeof(_GetMissionAreaServerObject));
                }
                
                return _GetMissionAreaServerObjectFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct SnapToggle__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _SnapToggle(SnapToggle__Args args);
            private static _SnapToggle _SnapToggleFunc;
            internal static _SnapToggle SnapToggle() {
                if (_SnapToggleFunc == null) {
                    _SnapToggleFunc =
                        (_SnapToggle)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnsnapToggle"), typeof(_SnapToggle));
                }
                
                return _SnapToggleFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct SetFov__Args
            {
                internal float FOV;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _SetFov(SetFov__Args args);
            private static _SetFov _SetFovFunc;
            internal static _SetFov SetFov() {
                if (_SetFovFunc == null) {
                    _SetFovFunc =
                        (_SetFov)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnsetFov"), typeof(_SetFov));
                }
                
                return _SetFovFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct SetZoomSpeed__Args
            {
                internal int speed;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _SetZoomSpeed(SetZoomSpeed__Args args);
            private static _SetZoomSpeed _SetZoomSpeedFunc;
            internal static _SetZoomSpeed SetZoomSpeed() {
                if (_SetZoomSpeedFunc == null) {
                    _SetZoomSpeedFunc =
                        (_SetZoomSpeed)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnsetZoomSpeed"), typeof(_SetZoomSpeed));
                }
                
                return _SetZoomSpeedFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct SetDefaultFov__Args
            {
                internal float defaultFOV;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _SetDefaultFov(SetDefaultFov__Args args);
            private static _SetDefaultFov _SetDefaultFovFunc;
            internal static _SetDefaultFov SetDefaultFov() {
                if (_SetDefaultFovFunc == null) {
                    _SetDefaultFovFunc =
                        (_SetDefaultFov)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnsetDefaultFov"), typeof(_SetDefaultFov));
                }
                
                return _SetDefaultFovFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct ContainerFindNext__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            
            internal delegate IntPtr _ContainerFindNext(ContainerFindNext__Args args);
            private static _ContainerFindNext _ContainerFindNextFunc;
            internal static _ContainerFindNext ContainerFindNext() {
                if (_ContainerFindNextFunc == null) {
                    _ContainerFindNextFunc =
                        (_ContainerFindNext)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fncontainerFindNext"), typeof(_ContainerFindNext));
                }
                
                return _ContainerFindNextFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct ContainerFindFirst__Args
            {
                internal uint typeMask;
                internal IntPtr origin;
                internal IntPtr size;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            
            internal delegate IntPtr _ContainerFindFirst(ContainerFindFirst__Args args);
            private static _ContainerFindFirst _ContainerFindFirstFunc;
            internal static _ContainerFindFirst ContainerFindFirst() {
                if (_ContainerFindFirstFunc == null) {
                    _ContainerFindFirstFunc =
                        (_ContainerFindFirst)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fncontainerFindFirst"), typeof(_ContainerFindFirst));
                }
                
                return _ContainerFindFirstFunc;
            }


            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate int _AiConnect(ref StringVector.InternalStruct args);
            private static _AiConnect _AiConnectFunc;
            internal static _AiConnect AiConnect() {
                if (_AiConnectFunc == null) {
                    _AiConnectFunc =
                        (_AiConnect)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnaiConnect"), typeof(_AiConnect));
                }
                
                return _AiConnectFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct AiAddPlayer__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string name;
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string ns;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate int _AiAddPlayer(AiAddPlayer__Args args);
            private static _AiAddPlayer _AiAddPlayerFunc;
            internal static _AiAddPlayer AiAddPlayer() {
                if (_AiAddPlayerFunc == null) {
                    _AiAddPlayerFunc =
                        (_AiAddPlayer)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnaiAddPlayer"), typeof(_AiAddPlayer));
                }
                
                return _AiAddPlayerFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct GetRootScene__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate int _GetRootScene(GetRootScene__Args args);
            private static _GetRootScene _GetRootSceneFunc;
            internal static _GetRootScene GetRootScene() {
                if (_GetRootSceneFunc == null) {
                    _GetRootSceneFunc =
                        (_GetRootScene)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fngetRootScene"), typeof(_GetRootScene));
                }
                
                return _GetRootSceneFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct GetSceneCount__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate int _GetSceneCount(GetSceneCount__Args args);
            private static _GetSceneCount _GetSceneCountFunc;
            internal static _GetSceneCount GetSceneCount() {
                if (_GetSceneCountFunc == null) {
                    _GetSceneCountFunc =
                        (_GetSceneCount)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fngetSceneCount"), typeof(_GetSceneCount));
                }
                
                return _GetSceneCountFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct GetScene__Args
            {
                internal uint sceneId;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate IntPtr _GetScene(GetScene__Args args);
            private static _GetScene _GetSceneFunc;
            internal static _GetScene GetScene() {
                if (_GetSceneFunc == null) {
                    _GetSceneFunc =
                        (_GetScene)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fngetScene"), typeof(_GetScene));
                }
                
                return _GetSceneFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct DumpActivePostFX__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _DumpActivePostFX(DumpActivePostFX__Args args);
            private static _DumpActivePostFX _DumpActivePostFXFunc;
            internal static _DumpActivePostFX DumpActivePostFX() {
                if (_DumpActivePostFXFunc == null) {
                    _DumpActivePostFXFunc =
                        (_DumpActivePostFX)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fndumpActivePostFX"), typeof(_DumpActivePostFX));
                }
                
                return _DumpActivePostFXFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct DumpRandomNormalMap__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _DumpRandomNormalMap(DumpRandomNormalMap__Args args);
            private static _DumpRandomNormalMap _DumpRandomNormalMapFunc;
            internal static _DumpRandomNormalMap DumpRandomNormalMap() {
                if (_DumpRandomNormalMapFunc == null) {
                    _DumpRandomNormalMapFunc =
                        (_DumpRandomNormalMap)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fndumpRandomNormalMap"), typeof(_DumpRandomNormalMap));
                }
                
                return _DumpRandomNormalMapFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct TsUpdateImposterImages__Args
            {
                [MarshalAs(UnmanagedType.I1)]
                internal bool forceUpdate;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _TsUpdateImposterImages(TsUpdateImposterImages__Args args);
            private static _TsUpdateImposterImages _TsUpdateImposterImagesFunc;
            internal static _TsUpdateImposterImages TsUpdateImposterImages() {
                if (_TsUpdateImposterImagesFunc == null) {
                    _TsUpdateImposterImagesFunc =
                        (_TsUpdateImposterImages)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fntsUpdateImposterImages"), typeof(_TsUpdateImposterImages));
                }
                
                return _TsUpdateImposterImagesFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct SetFogVolumeQuality__Args
            {
                internal uint new_quality;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate int _SetFogVolumeQuality(SetFogVolumeQuality__Args args);
            private static _SetFogVolumeQuality _SetFogVolumeQualityFunc;
            internal static _SetFogVolumeQuality SetFogVolumeQuality() {
                if (_SetFogVolumeQualityFunc == null) {
                    _SetFogVolumeQualityFunc =
                        (_SetFogVolumeQuality)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnSetFogVolumeQuality"), typeof(_SetFogVolumeQuality));
                }
                
                return _SetFogVolumeQualityFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct GetTerrainHeightBelowPosition__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string ptOrX;
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string y;
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string z;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate float _GetTerrainHeightBelowPosition(GetTerrainHeightBelowPosition__Args args);
            private static _GetTerrainHeightBelowPosition _GetTerrainHeightBelowPositionFunc;
            internal static _GetTerrainHeightBelowPosition GetTerrainHeightBelowPosition() {
                if (_GetTerrainHeightBelowPositionFunc == null) {
                    _GetTerrainHeightBelowPositionFunc =
                        (_GetTerrainHeightBelowPosition)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fngetTerrainHeightBelowPosition"), typeof(_GetTerrainHeightBelowPosition));
                }
                
                return _GetTerrainHeightBelowPositionFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct GetTerrainHeight__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string ptOrX;
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string y;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate float _GetTerrainHeight(GetTerrainHeight__Args args);
            private static _GetTerrainHeight _GetTerrainHeightFunc;
            internal static _GetTerrainHeight GetTerrainHeight() {
                if (_GetTerrainHeightFunc == null) {
                    _GetTerrainHeightFunc =
                        (_GetTerrainHeight)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fngetTerrainHeight"), typeof(_GetTerrainHeight));
                }
                
                return _GetTerrainHeightFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct GetTerrainUnderWorldPoint__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string ptOrX;
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string y;
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string z;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate int _GetTerrainUnderWorldPoint(GetTerrainUnderWorldPoint__Args args);
            private static _GetTerrainUnderWorldPoint _GetTerrainUnderWorldPointFunc;
            internal static _GetTerrainUnderWorldPoint GetTerrainUnderWorldPoint() {
                if (_GetTerrainUnderWorldPointFunc == null) {
                    _GetTerrainUnderWorldPointFunc =
                        (_GetTerrainUnderWorldPoint)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fngetTerrainUnderWorldPoint"), typeof(_GetTerrainUnderWorldPoint));
                }
                
                return _GetTerrainUnderWorldPointFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct PathOnMissionLoadDone__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _PathOnMissionLoadDone(PathOnMissionLoadDone__Args args);
            private static _PathOnMissionLoadDone _PathOnMissionLoadDoneFunc;
            internal static _PathOnMissionLoadDone PathOnMissionLoadDone() {
                if (_PathOnMissionLoadDoneFunc == null) {
                    _PathOnMissionLoadDoneFunc =
                        (_PathOnMissionLoadDone)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnpathOnMissionLoadDone"), typeof(_PathOnMissionLoadDone));
                }
                
                return _PathOnMissionLoadDoneFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct SceneGetZoneOwner__Args
            {
                internal uint zoneId;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate IntPtr _SceneGetZoneOwner(SceneGetZoneOwner__Args args);
            private static _SceneGetZoneOwner _SceneGetZoneOwnerFunc;
            internal static _SceneGetZoneOwner SceneGetZoneOwner() {
                if (_SceneGetZoneOwnerFunc == null) {
                    _SceneGetZoneOwnerFunc =
                        (_SceneGetZoneOwner)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnsceneGetZoneOwner"), typeof(_SceneGetZoneOwner));
                }
                
                return _SceneGetZoneOwnerFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct SceneDumpZoneStates__Args
            {
                [MarshalAs(UnmanagedType.I1)]
                internal bool updateFirst;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _SceneDumpZoneStates(SceneDumpZoneStates__Args args);
            private static _SceneDumpZoneStates _SceneDumpZoneStatesFunc;
            internal static _SceneDumpZoneStates SceneDumpZoneStates() {
                if (_SceneDumpZoneStatesFunc == null) {
                    _SceneDumpZoneStatesFunc =
                        (_SceneDumpZoneStates)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnsceneDumpZoneStates"), typeof(_SceneDumpZoneStates));
                }
                
                return _SceneDumpZoneStatesFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct MaterialRayCast__Args
            {
                internal IntPtr start;
                internal IntPtr end;
                internal uint mask;
                internal IntPtr pExempt;
                [MarshalAs(UnmanagedType.I1)]
                internal bool useClientContainer;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            
            internal delegate IntPtr _MaterialRayCast(MaterialRayCast__Args args);
            private static _MaterialRayCast _MaterialRayCastFunc;
            internal static _MaterialRayCast MaterialRayCast() {
                if (_MaterialRayCastFunc == null) {
                    _MaterialRayCastFunc =
                        (_MaterialRayCast)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnmaterialRayCast"), typeof(_MaterialRayCast));
                }
                
                return _MaterialRayCastFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct ContainerRayCast__Args
            {
                internal IntPtr start;
                internal IntPtr end;
                internal uint mask;
                internal IntPtr pExempt;
                [MarshalAs(UnmanagedType.I1)]
                internal bool useClientContainer;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            
            internal delegate IntPtr _ContainerRayCast(ContainerRayCast__Args args);
            private static _ContainerRayCast _ContainerRayCastFunc;
            internal static _ContainerRayCast ContainerRayCast() {
                if (_ContainerRayCastFunc == null) {
                    _ContainerRayCastFunc =
                        (_ContainerRayCast)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fncontainerRayCast"), typeof(_ContainerRayCast));
                }
                
                return _ContainerRayCastFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct ContainerSearchCurrRadiusDist__Args
            {
                [MarshalAs(UnmanagedType.I1)]
                internal bool useClientContainer;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate float _ContainerSearchCurrRadiusDist(ContainerSearchCurrRadiusDist__Args args);
            private static _ContainerSearchCurrRadiusDist _ContainerSearchCurrRadiusDistFunc;
            internal static _ContainerSearchCurrRadiusDist ContainerSearchCurrRadiusDist() {
                if (_ContainerSearchCurrRadiusDistFunc == null) {
                    _ContainerSearchCurrRadiusDistFunc =
                        (_ContainerSearchCurrRadiusDist)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fncontainerSearchCurrRadiusDist"), typeof(_ContainerSearchCurrRadiusDist));
                }
                
                return _ContainerSearchCurrRadiusDistFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct ContainerSearchCurrDist__Args
            {
                [MarshalAs(UnmanagedType.I1)]
                internal bool useClientContainer;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate float _ContainerSearchCurrDist(ContainerSearchCurrDist__Args args);
            private static _ContainerSearchCurrDist _ContainerSearchCurrDistFunc;
            internal static _ContainerSearchCurrDist ContainerSearchCurrDist() {
                if (_ContainerSearchCurrDistFunc == null) {
                    _ContainerSearchCurrDistFunc =
                        (_ContainerSearchCurrDist)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fncontainerSearchCurrDist"), typeof(_ContainerSearchCurrDist));
                }
                
                return _ContainerSearchCurrDistFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct ContainerSearchNext__Args
            {
                [MarshalAs(UnmanagedType.I1)]
                internal bool useClientContainer;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate IntPtr _ContainerSearchNext(ContainerSearchNext__Args args);
            private static _ContainerSearchNext _ContainerSearchNextFunc;
            internal static _ContainerSearchNext ContainerSearchNext() {
                if (_ContainerSearchNextFunc == null) {
                    _ContainerSearchNextFunc =
                        (_ContainerSearchNext)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fncontainerSearchNext"), typeof(_ContainerSearchNext));
                }
                
                return _ContainerSearchNextFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct InitContainerTypeSearch__Args
            {
                internal uint mask;
                [MarshalAs(UnmanagedType.I1)]
                internal bool useClientContainer;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _InitContainerTypeSearch(InitContainerTypeSearch__Args args);
            private static _InitContainerTypeSearch _InitContainerTypeSearchFunc;
            internal static _InitContainerTypeSearch InitContainerTypeSearch() {
                if (_InitContainerTypeSearchFunc == null) {
                    _InitContainerTypeSearchFunc =
                        (_InitContainerTypeSearch)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fninitContainerTypeSearch"), typeof(_InitContainerTypeSearch));
                }
                
                return _InitContainerTypeSearchFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct InitContainerRadiusSearch__Args
            {
                internal IntPtr pos;
                internal float radius;
                internal uint mask;
                [MarshalAs(UnmanagedType.I1)]
                internal bool useClientContainer;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _InitContainerRadiusSearch(InitContainerRadiusSearch__Args args);
            private static _InitContainerRadiusSearch _InitContainerRadiusSearchFunc;
            internal static _InitContainerRadiusSearch InitContainerRadiusSearch() {
                if (_InitContainerRadiusSearchFunc == null) {
                    _InitContainerRadiusSearchFunc =
                        (_InitContainerRadiusSearch)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fninitContainerRadiusSearch"), typeof(_InitContainerRadiusSearch));
                }
                
                return _InitContainerRadiusSearchFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct ContainerBoxEmpty__Args
            {
                internal uint mask;
                internal IntPtr center;
                internal float xRadius;
                internal float yRadius;
                internal float zRadius;
                [MarshalAs(UnmanagedType.I1)]
                internal bool useClientContainer;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            [return: MarshalAs(UnmanagedType.I1)]
            internal delegate bool _ContainerBoxEmpty(ContainerBoxEmpty__Args args);
            private static _ContainerBoxEmpty _ContainerBoxEmptyFunc;
            internal static _ContainerBoxEmpty ContainerBoxEmpty() {
                if (_ContainerBoxEmptyFunc == null) {
                    _ContainerBoxEmptyFunc =
                        (_ContainerBoxEmpty)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fncontainerBoxEmpty"), typeof(_ContainerBoxEmpty));
                }
                
                return _ContainerBoxEmptyFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct SetReflectFormat__Args
            {
                internal int format;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _SetReflectFormat(SetReflectFormat__Args args);
            private static _SetReflectFormat _SetReflectFormatFunc;
            internal static _SetReflectFormat SetReflectFormat() {
                if (_SetReflectFormatFunc == null) {
                    _SetReflectFormatFunc =
                        (_SetReflectFormat)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnsetReflectFormat"), typeof(_SetReflectFormat));
                }
                
                return _SetReflectFormatFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct ClearClientPaths__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _ClearClientPaths(ClearClientPaths__Args args);
            private static _ClearClientPaths _ClearClientPathsFunc;
            internal static _ClearClientPaths ClearClientPaths() {
                if (_ClearClientPathsFunc == null) {
                    _ClearClientPathsFunc =
                        (_ClearClientPaths)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnclearClientPaths"), typeof(_ClearClientPaths));
                }
                
                return _ClearClientPathsFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct ClearServerPaths__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _ClearServerPaths(ClearServerPaths__Args args);
            private static _ClearServerPaths _ClearServerPathsFunc;
            internal static _ClearServerPaths ClearServerPaths() {
                if (_ClearServerPathsFunc == null) {
                    _ClearServerPathsFunc =
                        (_ClearServerPaths)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnclearServerPaths"), typeof(_ClearServerPaths));
                }
                
                return _ClearServerPathsFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct SetShadowManager__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string sShadowSystemName;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            [return: MarshalAs(UnmanagedType.I1)]
            internal delegate bool _SetShadowManager(SetShadowManager__Args args);
            private static _SetShadowManager _SetShadowManagerFunc;
            internal static _SetShadowManager SetShadowManager() {
                if (_SetShadowManagerFunc == null) {
                    _SetShadowManagerFunc =
                        (_SetShadowManager)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnsetShadowManager"), typeof(_SetShadowManager));
                }
                
                return _SetShadowManagerFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct ResetLightManager__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _ResetLightManager(ResetLightManager__Args args);
            private static _ResetLightManager _ResetLightManagerFunc;
            internal static _ResetLightManager ResetLightManager() {
                if (_ResetLightManagerFunc == null) {
                    _ResetLightManagerFunc =
                        (_ResetLightManager)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnresetLightManager"), typeof(_ResetLightManager));
                }
                
                return _ResetLightManagerFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct GetActiveLightManager__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            
            internal delegate IntPtr _GetActiveLightManager(GetActiveLightManager__Args args);
            private static _GetActiveLightManager _GetActiveLightManagerFunc;
            internal static _GetActiveLightManager GetActiveLightManager() {
                if (_GetActiveLightManagerFunc == null) {
                    _GetActiveLightManagerFunc =
                        (_GetActiveLightManager)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fngetActiveLightManager"), typeof(_GetActiveLightManager));
                }
                
                return _GetActiveLightManagerFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct GetLightManagerNames__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            
            internal delegate IntPtr _GetLightManagerNames(GetLightManagerNames__Args args);
            private static _GetLightManagerNames _GetLightManagerNamesFunc;
            internal static _GetLightManagerNames GetLightManagerNames() {
                if (_GetLightManagerNamesFunc == null) {
                    _GetLightManagerNamesFunc =
                        (_GetLightManagerNames)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fngetLightManagerNames"), typeof(_GetLightManagerNames));
                }
                
                return _GetLightManagerNamesFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct LightScene__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string completeCallbackFn;
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string mode;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            [return: MarshalAs(UnmanagedType.I1)]
            internal delegate bool _LightScene(LightScene__Args args);
            private static _LightScene _LightSceneFunc;
            internal static _LightScene LightScene() {
                if (_LightSceneFunc == null) {
                    _LightSceneFunc =
                        (_LightScene)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnlightScene"), typeof(_LightScene));
                }
                
                return _LightSceneFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct SetLightManager__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string name;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            [return: MarshalAs(UnmanagedType.I1)]
            internal delegate bool _SetLightManager(SetLightManager__Args args);
            private static _SetLightManager _SetLightManagerFunc;
            internal static _SetLightManager SetLightManager() {
                if (_SetLightManagerFunc == null) {
                    _SetLightManagerFunc =
                        (_SetLightManager)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnsetLightManager"), typeof(_SetLightManager));
                }
                
                return _SetLightManagerFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct OnLightManagerDeactivate__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string name;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _OnLightManagerDeactivate(OnLightManagerDeactivate__Args args);
            private static _OnLightManagerDeactivate _OnLightManagerDeactivateFunc;
            internal static _OnLightManagerDeactivate OnLightManagerDeactivate() {
                if (_OnLightManagerDeactivateFunc == null) {
                    _OnLightManagerDeactivateFunc =
                        (_OnLightManagerDeactivate)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "cbonLightManagerDeactivate"), typeof(_OnLightManagerDeactivate));
                }
                
                return _OnLightManagerDeactivateFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct OnLightManagerActivate__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string name;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _OnLightManagerActivate(OnLightManagerActivate__Args args);
            private static _OnLightManagerActivate _OnLightManagerActivateFunc;
            internal static _OnLightManagerActivate OnLightManagerActivate() {
                if (_OnLightManagerActivateFunc == null) {
                    _OnLightManagerActivateFunc =
                        (_OnLightManagerActivate)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "cbonLightManagerActivate"), typeof(_OnLightManagerActivate));
                }
                
                return _OnLightManagerActivateFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct GetMapEntry__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string texName;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            
            internal delegate IntPtr _GetMapEntry(GetMapEntry__Args args);
            private static _GetMapEntry _GetMapEntryFunc;
            internal static _GetMapEntry GetMapEntry() {
                if (_GetMapEntryFunc == null) {
                    _GetMapEntryFunc =
                        (_GetMapEntry)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fngetMapEntry"), typeof(_GetMapEntry));
                }
                
                return _GetMapEntryFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct GetMaterialInstances__Args
            {
                internal IntPtr target;
                internal IntPtr tree;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _GetMaterialInstances(GetMaterialInstances__Args args);
            private static _GetMaterialInstances _GetMaterialInstancesFunc;
            internal static _GetMaterialInstances GetMaterialInstances() {
                if (_GetMaterialInstancesFunc == null) {
                    _GetMaterialInstancesFunc =
                        (_GetMaterialInstances)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fngetMaterialInstances"), typeof(_GetMaterialInstances));
                }
                
                return _GetMaterialInstancesFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct DumpMaterialInstances__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _DumpMaterialInstances(DumpMaterialInstances__Args args);
            private static _DumpMaterialInstances _DumpMaterialInstancesFunc;
            internal static _DumpMaterialInstances DumpMaterialInstances() {
                if (_DumpMaterialInstancesFunc == null) {
                    _DumpMaterialInstancesFunc =
                        (_DumpMaterialInstances)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fndumpMaterialInstances"), typeof(_DumpMaterialInstances));
                }
                
                return _DumpMaterialInstancesFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct GetMaterialMapping__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string texName;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            
            internal delegate IntPtr _GetMaterialMapping(GetMaterialMapping__Args args);
            private static _GetMaterialMapping _GetMaterialMappingFunc;
            internal static _GetMaterialMapping GetMaterialMapping() {
                if (_GetMaterialMappingFunc == null) {
                    _GetMaterialMappingFunc =
                        (_GetMaterialMapping)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fngetMaterialMapping"), typeof(_GetMaterialMapping));
                }
                
                return _GetMaterialMappingFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct AddMaterialMapping__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string texName;
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string matName;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _AddMaterialMapping(AddMaterialMapping__Args args);
            private static _AddMaterialMapping _AddMaterialMappingFunc;
            internal static _AddMaterialMapping AddMaterialMapping() {
                if (_AddMaterialMappingFunc == null) {
                    _AddMaterialMappingFunc =
                        (_AddMaterialMapping)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnaddMaterialMapping"), typeof(_AddMaterialMapping));
                }
                
                return _AddMaterialMappingFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct ReInitMaterials__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _ReInitMaterials(ReInitMaterials__Args args);
            private static _ReInitMaterials _ReInitMaterialsFunc;
            internal static _ReInitMaterials ReInitMaterials() {
                if (_ReInitMaterialsFunc == null) {
                    _ReInitMaterialsFunc =
                        (_ReInitMaterials)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnreInitMaterials"), typeof(_ReInitMaterials));
                }
                
                return _ReInitMaterialsFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct ExcludeOtherInstance__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string appIdentifer;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            [return: MarshalAs(UnmanagedType.I1)]
            internal delegate bool _ExcludeOtherInstance(ExcludeOtherInstance__Args args);
            private static _ExcludeOtherInstance _ExcludeOtherInstanceFunc;
            internal static _ExcludeOtherInstance ExcludeOtherInstance() {
                if (_ExcludeOtherInstanceFunc == null) {
                    _ExcludeOtherInstanceFunc =
                        (_ExcludeOtherInstance)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnexcludeOtherInstance"), typeof(_ExcludeOtherInstance));
                }
                
                return _ExcludeOtherInstanceFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct StripMLControlChars__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string inString;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            
            internal delegate IntPtr _StripMLControlChars(StripMLControlChars__Args args);
            private static _StripMLControlChars _StripMLControlCharsFunc;
            internal static _StripMLControlChars StripMLControlChars() {
                if (_StripMLControlCharsFunc == null) {
                    _StripMLControlCharsFunc =
                        (_StripMLControlChars)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnStripMLControlChars"), typeof(_StripMLControlChars));
                }
                
                return _StripMLControlCharsFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct ScreenShot__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string file;
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string format;
                internal uint tileCount;
                internal float tileOverlap;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _ScreenShot(ScreenShot__Args args);
            private static _ScreenShot _ScreenShotFunc;
            internal static _ScreenShot ScreenShot() {
                if (_ScreenShotFunc == null) {
                    _ScreenShotFunc =
                        (_ScreenShot)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnscreenShot"), typeof(_ScreenShot));
                }
                
                return _ScreenShotFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct GetTextureProfileStats__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            
            internal delegate IntPtr _GetTextureProfileStats(GetTextureProfileStats__Args args);
            private static _GetTextureProfileStats _GetTextureProfileStatsFunc;
            internal static _GetTextureProfileStats GetTextureProfileStats() {
                if (_GetTextureProfileStatsFunc == null) {
                    _GetTextureProfileStatsFunc =
                        (_GetTextureProfileStats)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fngetTextureProfileStats"), typeof(_GetTextureProfileStats));
                }
                
                return _GetTextureProfileStatsFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct DumpTextureObjects__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _DumpTextureObjects(DumpTextureObjects__Args args);
            private static _DumpTextureObjects _DumpTextureObjectsFunc;
            internal static _DumpTextureObjects DumpTextureObjects() {
                if (_DumpTextureObjectsFunc == null) {
                    _DumpTextureObjectsFunc =
                        (_DumpTextureObjects)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fndumpTextureObjects"), typeof(_DumpTextureObjects));
                }
                
                return _DumpTextureObjectsFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct ReloadTextures__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _ReloadTextures(ReloadTextures__Args args);
            private static _ReloadTextures _ReloadTexturesFunc;
            internal static _ReloadTextures ReloadTextures() {
                if (_ReloadTexturesFunc == null) {
                    _ReloadTexturesFunc =
                        (_ReloadTextures)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnreloadTextures"), typeof(_ReloadTextures));
                }
                
                return _ReloadTexturesFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct CleanupTexturePool__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _CleanupTexturePool(CleanupTexturePool__Args args);
            private static _CleanupTexturePool _CleanupTexturePoolFunc;
            internal static _CleanupTexturePool CleanupTexturePool() {
                if (_CleanupTexturePoolFunc == null) {
                    _CleanupTexturePoolFunc =
                        (_CleanupTexturePool)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fncleanupTexturePool"), typeof(_CleanupTexturePool));
                }
                
                return _CleanupTexturePoolFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct FlushTextureCache__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _FlushTextureCache(FlushTextureCache__Args args);
            private static _FlushTextureCache _FlushTextureCacheFunc;
            internal static _FlushTextureCache FlushTextureCache() {
                if (_FlushTextureCacheFunc == null) {
                    _FlushTextureCacheFunc =
                        (_FlushTextureCache)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnflushTextureCache"), typeof(_FlushTextureCache));
                }
                
                return _FlushTextureCacheFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct SaveCompositeTexture__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string pathR;
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string pathG;
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string pathB;
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string pathA;
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string inputKeyString;
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string saveAs;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _SaveCompositeTexture(SaveCompositeTexture__Args args);
            private static _SaveCompositeTexture _SaveCompositeTextureFunc;
            internal static _SaveCompositeTexture SaveCompositeTexture() {
                if (_SaveCompositeTextureFunc == null) {
                    _SaveCompositeTextureFunc =
                        (_SaveCompositeTexture)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnsaveCompositeTexture"), typeof(_SaveCompositeTexture));
                }
                
                return _SaveCompositeTextureFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct RemoveGlobalShaderMacro__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string name;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _RemoveGlobalShaderMacro(RemoveGlobalShaderMacro__Args args);
            private static _RemoveGlobalShaderMacro _RemoveGlobalShaderMacroFunc;
            internal static _RemoveGlobalShaderMacro RemoveGlobalShaderMacro() {
                if (_RemoveGlobalShaderMacroFunc == null) {
                    _RemoveGlobalShaderMacroFunc =
                        (_RemoveGlobalShaderMacro)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnremoveGlobalShaderMacro"), typeof(_RemoveGlobalShaderMacro));
                }
                
                return _RemoveGlobalShaderMacroFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct AddGlobalShaderMacro__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string name;
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string value;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _AddGlobalShaderMacro(AddGlobalShaderMacro__Args args);
            private static _AddGlobalShaderMacro _AddGlobalShaderMacroFunc;
            internal static _AddGlobalShaderMacro AddGlobalShaderMacro() {
                if (_AddGlobalShaderMacroFunc == null) {
                    _AddGlobalShaderMacroFunc =
                        (_AddGlobalShaderMacro)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnaddGlobalShaderMacro"), typeof(_AddGlobalShaderMacro));
                }
                
                return _AddGlobalShaderMacroFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct GetDesktopResolution__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate Point3F.InternalStruct _GetDesktopResolution(GetDesktopResolution__Args args);
            private static _GetDesktopResolution _GetDesktopResolutionFunc;
            internal static _GetDesktopResolution GetDesktopResolution() {
                if (_GetDesktopResolutionFunc == null) {
                    _GetDesktopResolutionFunc =
                        (_GetDesktopResolution)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fngetDesktopResolution"), typeof(_GetDesktopResolution));
                }
                
                return _GetDesktopResolutionFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct ResetGFX__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _ResetGFX(ResetGFX__Args args);
            private static _ResetGFX _ResetGFXFunc;
            internal static _ResetGFX ResetGFX() {
                if (_ResetGFXFunc == null) {
                    _ResetGFXFunc =
                        (_ResetGFX)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnResetGFX"), typeof(_ResetGFX));
                }
                
                return _ResetGFXFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct GetBestHDRFormat__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate int _GetBestHDRFormat(GetBestHDRFormat__Args args);
            private static _GetBestHDRFormat _GetBestHDRFormatFunc;
            internal static _GetBestHDRFormat GetBestHDRFormat() {
                if (_GetBestHDRFormatFunc == null) {
                    _GetBestHDRFormatFunc =
                        (_GetBestHDRFormat)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fngetBestHDRFormat"), typeof(_GetBestHDRFormat));
                }
                
                return _GetBestHDRFormatFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct GetDisplayDeviceInformation__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            
            internal delegate IntPtr _GetDisplayDeviceInformation(GetDisplayDeviceInformation__Args args);
            private static _GetDisplayDeviceInformation _GetDisplayDeviceInformationFunc;
            internal static _GetDisplayDeviceInformation GetDisplayDeviceInformation() {
                if (_GetDisplayDeviceInformationFunc == null) {
                    _GetDisplayDeviceInformationFunc =
                        (_GetDisplayDeviceInformation)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fngetDisplayDeviceInformation"), typeof(_GetDisplayDeviceInformation));
                }
                
                return _GetDisplayDeviceInformationFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct SetPixelShaderVersion__Args
            {
                internal float version;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _SetPixelShaderVersion(SetPixelShaderVersion__Args args);
            private static _SetPixelShaderVersion _SetPixelShaderVersionFunc;
            internal static _SetPixelShaderVersion SetPixelShaderVersion() {
                if (_SetPixelShaderVersionFunc == null) {
                    _SetPixelShaderVersionFunc =
                        (_SetPixelShaderVersion)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnsetPixelShaderVersion"), typeof(_SetPixelShaderVersion));
                }
                
                return _SetPixelShaderVersionFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct GetPixelShaderVersion__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate float _GetPixelShaderVersion(GetPixelShaderVersion__Args args);
            private static _GetPixelShaderVersion _GetPixelShaderVersionFunc;
            internal static _GetPixelShaderVersion GetPixelShaderVersion() {
                if (_GetPixelShaderVersionFunc == null) {
                    _GetPixelShaderVersionFunc =
                        (_GetPixelShaderVersion)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fngetPixelShaderVersion"), typeof(_GetPixelShaderVersion));
                }
                
                return _GetPixelShaderVersionFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct DescribeGFXStateBlocks__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string filePath;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _DescribeGFXStateBlocks(DescribeGFXStateBlocks__Args args);
            private static _DescribeGFXStateBlocks _DescribeGFXStateBlocksFunc;
            internal static _DescribeGFXStateBlocks DescribeGFXStateBlocks() {
                if (_DescribeGFXStateBlocksFunc == null) {
                    _DescribeGFXStateBlocksFunc =
                        (_DescribeGFXStateBlocks)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fndescribeGFXStateBlocks"), typeof(_DescribeGFXStateBlocks));
                }
                
                return _DescribeGFXStateBlocksFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct DescribeGFXResources__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string resourceTypes;
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string filePath;
                [MarshalAs(UnmanagedType.I1)]
                internal bool unflaggedOnly;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _DescribeGFXResources(DescribeGFXResources__Args args);
            private static _DescribeGFXResources _DescribeGFXResourcesFunc;
            internal static _DescribeGFXResources DescribeGFXResources() {
                if (_DescribeGFXResourcesFunc == null) {
                    _DescribeGFXResourcesFunc =
                        (_DescribeGFXResources)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fndescribeGFXResources"), typeof(_DescribeGFXResources));
                }
                
                return _DescribeGFXResourcesFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct ClearGFXResourceFlags__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _ClearGFXResourceFlags(ClearGFXResourceFlags__Args args);
            private static _ClearGFXResourceFlags _ClearGFXResourceFlagsFunc;
            internal static _ClearGFXResourceFlags ClearGFXResourceFlags() {
                if (_ClearGFXResourceFlagsFunc == null) {
                    _ClearGFXResourceFlagsFunc =
                        (_ClearGFXResourceFlags)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnclearGFXResourceFlags"), typeof(_ClearGFXResourceFlags));
                }
                
                return _ClearGFXResourceFlagsFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct FlagCurrentGFXResources__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _FlagCurrentGFXResources(FlagCurrentGFXResources__Args args);
            private static _FlagCurrentGFXResources _FlagCurrentGFXResourcesFunc;
            internal static _FlagCurrentGFXResources FlagCurrentGFXResources() {
                if (_FlagCurrentGFXResourcesFunc == null) {
                    _FlagCurrentGFXResourcesFunc =
                        (_FlagCurrentGFXResources)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnflagCurrentGFXResources"), typeof(_FlagCurrentGFXResources));
                }
                
                return _FlagCurrentGFXResourcesFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct ListGFXResources__Args
            {
                [MarshalAs(UnmanagedType.I1)]
                internal bool unflaggedOnly;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _ListGFXResources(ListGFXResources__Args args);
            private static _ListGFXResources _ListGFXResourcesFunc;
            internal static _ListGFXResources ListGFXResources() {
                if (_ListGFXResourcesFunc == null) {
                    _ListGFXResourcesFunc =
                        (_ListGFXResources)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnlistGFXResources"), typeof(_ListGFXResources));
                }
                
                return _ListGFXResourcesFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct GetDisplayDeviceList__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            
            internal delegate IntPtr _GetDisplayDeviceList(GetDisplayDeviceList__Args args);
            private static _GetDisplayDeviceList _GetDisplayDeviceListFunc;
            internal static _GetDisplayDeviceList GetDisplayDeviceList() {
                if (_GetDisplayDeviceListFunc == null) {
                    _GetDisplayDeviceListFunc =
                        (_GetDisplayDeviceList)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fngetDisplayDeviceList"), typeof(_GetDisplayDeviceList));
                }
                
                return _GetDisplayDeviceListFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct DuplicateCachedFont__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string oldFontName;
                internal int oldFontSize;
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string newFontName;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _DuplicateCachedFont(DuplicateCachedFont__Args args);
            private static _DuplicateCachedFont _DuplicateCachedFontFunc;
            internal static _DuplicateCachedFont DuplicateCachedFont() {
                if (_DuplicateCachedFontFunc == null) {
                    _DuplicateCachedFontFunc =
                        (_DuplicateCachedFont)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnduplicateCachedFont"), typeof(_DuplicateCachedFont));
                }
                
                return _DuplicateCachedFontFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct ImportCachedFont__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string faceName;
                internal int fontSize;
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string fileName;
                internal int padding;
                internal int kerning;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _ImportCachedFont(ImportCachedFont__Args args);
            private static _ImportCachedFont _ImportCachedFontFunc;
            internal static _ImportCachedFont ImportCachedFont() {
                if (_ImportCachedFontFunc == null) {
                    _ImportCachedFontFunc =
                        (_ImportCachedFont)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnimportCachedFont"), typeof(_ImportCachedFont));
                }
                
                return _ImportCachedFontFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct ExportCachedFont__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string faceName;
                internal int fontSize;
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string fileName;
                internal int padding;
                internal int kerning;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _ExportCachedFont(ExportCachedFont__Args args);
            private static _ExportCachedFont _ExportCachedFontFunc;
            internal static _ExportCachedFont ExportCachedFont() {
                if (_ExportCachedFontFunc == null) {
                    _ExportCachedFontFunc =
                        (_ExportCachedFont)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnexportCachedFont"), typeof(_ExportCachedFont));
                }
                
                return _ExportCachedFontFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct PopulateAllFontCacheRange__Args
            {
                internal uint rangeStart;
                internal uint rangeEnd;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _PopulateAllFontCacheRange(PopulateAllFontCacheRange__Args args);
            private static _PopulateAllFontCacheRange _PopulateAllFontCacheRangeFunc;
            internal static _PopulateAllFontCacheRange PopulateAllFontCacheRange() {
                if (_PopulateAllFontCacheRangeFunc == null) {
                    _PopulateAllFontCacheRangeFunc =
                        (_PopulateAllFontCacheRange)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnpopulateAllFontCacheRange"), typeof(_PopulateAllFontCacheRange));
                }
                
                return _PopulateAllFontCacheRangeFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct PopulateAllFontCacheString__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string _string;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _PopulateAllFontCacheString(PopulateAllFontCacheString__Args args);
            private static _PopulateAllFontCacheString _PopulateAllFontCacheStringFunc;
            internal static _PopulateAllFontCacheString PopulateAllFontCacheString() {
                if (_PopulateAllFontCacheStringFunc == null) {
                    _PopulateAllFontCacheStringFunc =
                        (_PopulateAllFontCacheString)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnpopulateAllFontCacheString"), typeof(_PopulateAllFontCacheString));
                }
                
                return _PopulateAllFontCacheStringFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct WriteFontCache__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _WriteFontCache(WriteFontCache__Args args);
            private static _WriteFontCache _WriteFontCacheFunc;
            internal static _WriteFontCache WriteFontCache() {
                if (_WriteFontCacheFunc == null) {
                    _WriteFontCacheFunc =
                        (_WriteFontCache)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnwriteFontCache"), typeof(_WriteFontCache));
                }
                
                return _WriteFontCacheFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct DumpFontCacheStatus__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _DumpFontCacheStatus(DumpFontCacheStatus__Args args);
            private static _DumpFontCacheStatus _DumpFontCacheStatusFunc;
            internal static _DumpFontCacheStatus DumpFontCacheStatus() {
                if (_DumpFontCacheStatusFunc == null) {
                    _DumpFontCacheStatusFunc =
                        (_DumpFontCacheStatus)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fndumpFontCacheStatus"), typeof(_DumpFontCacheStatus));
                }
                
                return _DumpFontCacheStatusFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct PopulateFontCacheRange__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string faceName;
                internal int fontSize;
                internal uint rangeStart;
                internal uint rangeEnd;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _PopulateFontCacheRange(PopulateFontCacheRange__Args args);
            private static _PopulateFontCacheRange _PopulateFontCacheRangeFunc;
            internal static _PopulateFontCacheRange PopulateFontCacheRange() {
                if (_PopulateFontCacheRangeFunc == null) {
                    _PopulateFontCacheRangeFunc =
                        (_PopulateFontCacheRange)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnpopulateFontCacheRange"), typeof(_PopulateFontCacheRange));
                }
                
                return _PopulateFontCacheRangeFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct PopulateFontCacheString__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string faceName;
                internal int fontSize;
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string _string;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _PopulateFontCacheString(PopulateFontCacheString__Args args);
            private static _PopulateFontCacheString _PopulateFontCacheStringFunc;
            internal static _PopulateFontCacheString PopulateFontCacheString() {
                if (_PopulateFontCacheStringFunc == null) {
                    _PopulateFontCacheStringFunc =
                        (_PopulateFontCacheString)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnpopulateFontCacheString"), typeof(_PopulateFontCacheString));
                }
                
                return _PopulateFontCacheStringFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct PlayJournalToVideo__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string journalFile;
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string videoFile;
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string encoder;
                internal float framerate;
                internal IntPtr resolution;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _PlayJournalToVideo(PlayJournalToVideo__Args args);
            private static _PlayJournalToVideo _PlayJournalToVideoFunc;
            internal static _PlayJournalToVideo PlayJournalToVideo() {
                if (_PlayJournalToVideoFunc == null) {
                    _PlayJournalToVideoFunc =
                        (_PlayJournalToVideo)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnplayJournalToVideo"), typeof(_PlayJournalToVideo));
                }
                
                return _PlayJournalToVideoFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct StopVideoCapture__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _StopVideoCapture(StopVideoCapture__Args args);
            private static _StopVideoCapture _StopVideoCaptureFunc;
            internal static _StopVideoCapture StopVideoCapture() {
                if (_StopVideoCaptureFunc == null) {
                    _StopVideoCaptureFunc =
                        (_StopVideoCapture)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnstopVideoCapture"), typeof(_StopVideoCapture));
                }
                
                return _StopVideoCaptureFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct StartVideoCapture__Args
            {
                internal IntPtr canvas;
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string filename;
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string encoder;
                internal float framerate;
                internal IntPtr resolution;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _StartVideoCapture(StartVideoCapture__Args args);
            private static _StartVideoCapture _StartVideoCaptureFunc;
            internal static _StartVideoCapture StartVideoCapture() {
                if (_StartVideoCaptureFunc == null) {
                    _StartVideoCaptureFunc =
                        (_StartVideoCapture)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnstartVideoCapture"), typeof(_StartVideoCapture));
                }
                
                return _StartVideoCaptureFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct GetBitmapInfo__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string filename;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            
            internal delegate IntPtr _GetBitmapInfo(GetBitmapInfo__Args args);
            private static _GetBitmapInfo _GetBitmapInfoFunc;
            internal static _GetBitmapInfo GetBitmapInfo() {
                if (_GetBitmapInfoFunc == null) {
                    _GetBitmapInfoFunc =
                        (_GetBitmapInfo)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fngetBitmapInfo"), typeof(_GetBitmapInfo));
                }
                
                return _GetBitmapInfoFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct GetActiveDDSFiles__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate int _GetActiveDDSFiles(GetActiveDDSFiles__Args args);
            private static _GetActiveDDSFiles _GetActiveDDSFilesFunc;
            internal static _GetActiveDDSFiles GetActiveDDSFiles() {
                if (_GetActiveDDSFilesFunc == null) {
                    _GetActiveDDSFilesFunc =
                        (_GetActiveDDSFiles)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fngetActiveDDSFiles"), typeof(_GetActiveDDSFiles));
                }
                
                return _GetActiveDDSFilesFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct DispatchMessageObject__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string queueName;
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string message;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            [return: MarshalAs(UnmanagedType.I1)]
            internal delegate bool _DispatchMessageObject(DispatchMessageObject__Args args);
            private static _DispatchMessageObject _DispatchMessageObjectFunc;
            internal static _DispatchMessageObject DispatchMessageObject() {
                if (_DispatchMessageObjectFunc == null) {
                    _DispatchMessageObjectFunc =
                        (_DispatchMessageObject)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fndispatchMessageObject"), typeof(_DispatchMessageObject));
                }
                
                return _DispatchMessageObjectFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct DispatchMessage__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string queueName;
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string message;
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string data;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            [return: MarshalAs(UnmanagedType.I1)]
            internal delegate bool _DispatchMessage(DispatchMessage__Args args);
            private static _DispatchMessage _DispatchMessageFunc;
            internal static _DispatchMessage DispatchMessage() {
                if (_DispatchMessageFunc == null) {
                    _DispatchMessageFunc =
                        (_DispatchMessage)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fndispatchMessage"), typeof(_DispatchMessage));
                }
                
                return _DispatchMessageFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct UnregisterMessageListener__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string queueName;
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string listenerName;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _UnregisterMessageListener(UnregisterMessageListener__Args args);
            private static _UnregisterMessageListener _UnregisterMessageListenerFunc;
            internal static _UnregisterMessageListener UnregisterMessageListener() {
                if (_UnregisterMessageListenerFunc == null) {
                    _UnregisterMessageListenerFunc =
                        (_UnregisterMessageListener)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnunregisterMessageListener"), typeof(_UnregisterMessageListener));
                }
                
                return _UnregisterMessageListenerFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct RegisterMessageListener__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string queueName;
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string listenerName;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            [return: MarshalAs(UnmanagedType.I1)]
            internal delegate bool _RegisterMessageListener(RegisterMessageListener__Args args);
            private static _RegisterMessageListener _RegisterMessageListenerFunc;
            internal static _RegisterMessageListener RegisterMessageListener() {
                if (_RegisterMessageListenerFunc == null) {
                    _RegisterMessageListenerFunc =
                        (_RegisterMessageListener)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnregisterMessageListener"), typeof(_RegisterMessageListener));
                }
                
                return _RegisterMessageListenerFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct UnregisterMessageQueue__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string queueName;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _UnregisterMessageQueue(UnregisterMessageQueue__Args args);
            private static _UnregisterMessageQueue _UnregisterMessageQueueFunc;
            internal static _UnregisterMessageQueue UnregisterMessageQueue() {
                if (_UnregisterMessageQueueFunc == null) {
                    _UnregisterMessageQueueFunc =
                        (_UnregisterMessageQueue)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnunregisterMessageQueue"), typeof(_UnregisterMessageQueue));
                }
                
                return _UnregisterMessageQueueFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct RegisterMessageQueue__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string queueName;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _RegisterMessageQueue(RegisterMessageQueue__Args args);
            private static _RegisterMessageQueue _RegisterMessageQueueFunc;
            internal static _RegisterMessageQueue RegisterMessageQueue() {
                if (_RegisterMessageQueueFunc == null) {
                    _RegisterMessageQueueFunc =
                        (_RegisterMessageQueue)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnregisterMessageQueue"), typeof(_RegisterMessageQueue));
                }
                
                return _RegisterMessageQueueFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct IsQueueRegistered__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string queueName;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            [return: MarshalAs(UnmanagedType.I1)]
            internal delegate bool _IsQueueRegistered(IsQueueRegistered__Args args);
            private static _IsQueueRegistered _IsQueueRegisteredFunc;
            internal static _IsQueueRegistered IsQueueRegistered() {
                if (_IsQueueRegisteredFunc == null) {
                    _IsQueueRegisteredFunc =
                        (_IsQueueRegistered)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnisQueueRegistered"), typeof(_IsQueueRegistered));
                }
                
                return _IsQueueRegisteredFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct FindDataBlockByName__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string pName;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate IntPtr _FindDataBlockByName(FindDataBlockByName__Args args);
            private static _FindDataBlockByName _FindDataBlockByNameFunc;
            internal static _FindDataBlockByName FindDataBlockByName() {
                if (_FindDataBlockByNameFunc == null) {
                    _FindDataBlockByNameFunc =
                        (_FindDataBlockByName)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnFindDataBlockByName"), typeof(_FindDataBlockByName));
                }
                
                return _FindDataBlockByNameFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct FindObjectByName__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string pName;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate IntPtr _FindObjectByName(FindObjectByName__Args args);
            private static _FindObjectByName _FindObjectByNameFunc;
            internal static _FindObjectByName FindObjectByName() {
                if (_FindObjectByNameFunc == null) {
                    _FindObjectByNameFunc =
                        (_FindObjectByName)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnFindObjectByName"), typeof(_FindObjectByName));
                }
                
                return _FindObjectByNameFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct FindObjectById__Args
            {
                internal uint pId;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate IntPtr _FindObjectById(FindObjectById__Args args);
            private static _FindObjectById _FindObjectByIdFunc;
            internal static _FindObjectById FindObjectById() {
                if (_FindObjectByIdFunc == null) {
                    _FindObjectByIdFunc =
                        (_FindObjectById)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnFindObjectById"), typeof(_FindObjectById));
                }
                
                return _FindObjectByIdFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct SetConsoleBool__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string name;
                [MarshalAs(UnmanagedType.I1)]
                internal bool value;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _SetConsoleBool(SetConsoleBool__Args args);
            private static _SetConsoleBool _SetConsoleBoolFunc;
            internal static _SetConsoleBool SetConsoleBool() {
                if (_SetConsoleBoolFunc == null) {
                    _SetConsoleBoolFunc =
                        (_SetConsoleBool)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnSetConsoleBool"), typeof(_SetConsoleBool));
                }
                
                return _SetConsoleBoolFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct GetConsoleBool__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string name;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            [return: MarshalAs(UnmanagedType.I1)]
            internal delegate bool _GetConsoleBool(GetConsoleBool__Args args);
            private static _GetConsoleBool _GetConsoleBoolFunc;
            internal static _GetConsoleBool GetConsoleBool() {
                if (_GetConsoleBoolFunc == null) {
                    _GetConsoleBoolFunc =
                        (_GetConsoleBool)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnGetConsoleBool"), typeof(_GetConsoleBool));
                }
                
                return _GetConsoleBoolFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct SetConsoleFloat__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string name;
                internal float value;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _SetConsoleFloat(SetConsoleFloat__Args args);
            private static _SetConsoleFloat _SetConsoleFloatFunc;
            internal static _SetConsoleFloat SetConsoleFloat() {
                if (_SetConsoleFloatFunc == null) {
                    _SetConsoleFloatFunc =
                        (_SetConsoleFloat)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnSetConsoleFloat"), typeof(_SetConsoleFloat));
                }
                
                return _SetConsoleFloatFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct GetConsoleFloat__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string name;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate float _GetConsoleFloat(GetConsoleFloat__Args args);
            private static _GetConsoleFloat _GetConsoleFloatFunc;
            internal static _GetConsoleFloat GetConsoleFloat() {
                if (_GetConsoleFloatFunc == null) {
                    _GetConsoleFloatFunc =
                        (_GetConsoleFloat)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnGetConsoleFloat"), typeof(_GetConsoleFloat));
                }
                
                return _GetConsoleFloatFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct SetConsoleInt__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string name;
                internal int value;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _SetConsoleInt(SetConsoleInt__Args args);
            private static _SetConsoleInt _SetConsoleIntFunc;
            internal static _SetConsoleInt SetConsoleInt() {
                if (_SetConsoleIntFunc == null) {
                    _SetConsoleIntFunc =
                        (_SetConsoleInt)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnSetConsoleInt"), typeof(_SetConsoleInt));
                }
                
                return _SetConsoleIntFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct GetConsoleInt__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string name;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate int _GetConsoleInt(GetConsoleInt__Args args);
            private static _GetConsoleInt _GetConsoleIntFunc;
            internal static _GetConsoleInt GetConsoleInt() {
                if (_GetConsoleIntFunc == null) {
                    _GetConsoleIntFunc =
                        (_GetConsoleInt)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnGetConsoleInt"), typeof(_GetConsoleInt));
                }
                
                return _GetConsoleIntFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct SetConsoleString__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string name;
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string value;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _SetConsoleString(SetConsoleString__Args args);
            private static _SetConsoleString _SetConsoleStringFunc;
            internal static _SetConsoleString SetConsoleString() {
                if (_SetConsoleStringFunc == null) {
                    _SetConsoleStringFunc =
                        (_SetConsoleString)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnSetConsoleString"), typeof(_SetConsoleString));
                }
                
                return _SetConsoleStringFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct GetConsoleString__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string name;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            
            internal delegate IntPtr _GetConsoleString(GetConsoleString__Args args);
            private static _GetConsoleString _GetConsoleStringFunc;
            internal static _GetConsoleString GetConsoleString() {
                if (_GetConsoleStringFunc == null) {
                    _GetConsoleStringFunc =
                        (_GetConsoleString)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnGetConsoleString"), typeof(_GetConsoleString));
                }
                
                return _GetConsoleStringFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct MessageBox__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string title;
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string message;
                internal int buttons;
                internal int icons;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate int _MessageBox(MessageBox__Args args);
            private static _MessageBox _MessageBoxFunc;
            internal static _MessageBox MessageBox() {
                if (_MessageBoxFunc == null) {
                    _MessageBoxFunc =
                        (_MessageBox)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnmessageBox"), typeof(_MessageBox));
                }
                
                return _MessageBoxFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct ProfilerReset__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _ProfilerReset(ProfilerReset__Args args);
            private static _ProfilerReset _ProfilerResetFunc;
            internal static _ProfilerReset ProfilerReset() {
                if (_ProfilerResetFunc == null) {
                    _ProfilerResetFunc =
                        (_ProfilerReset)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnprofilerReset"), typeof(_ProfilerReset));
                }
                
                return _ProfilerResetFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct ProfilerDumpToFile__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string fileName;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _ProfilerDumpToFile(ProfilerDumpToFile__Args args);
            private static _ProfilerDumpToFile _ProfilerDumpToFileFunc;
            internal static _ProfilerDumpToFile ProfilerDumpToFile() {
                if (_ProfilerDumpToFileFunc == null) {
                    _ProfilerDumpToFileFunc =
                        (_ProfilerDumpToFile)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnprofilerDumpToFile"), typeof(_ProfilerDumpToFile));
                }
                
                return _ProfilerDumpToFileFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct ProfilerDump__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _ProfilerDump(ProfilerDump__Args args);
            private static _ProfilerDump _ProfilerDumpFunc;
            internal static _ProfilerDump ProfilerDump() {
                if (_ProfilerDumpFunc == null) {
                    _ProfilerDumpFunc =
                        (_ProfilerDump)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnprofilerDump"), typeof(_ProfilerDump));
                }
                
                return _ProfilerDumpFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct ProfilerEnable__Args
            {
                [MarshalAs(UnmanagedType.I1)]
                internal bool enable;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _ProfilerEnable(ProfilerEnable__Args args);
            private static _ProfilerEnable _ProfilerEnableFunc;
            internal static _ProfilerEnable ProfilerEnable() {
                if (_ProfilerEnableFunc == null) {
                    _ProfilerEnableFunc =
                        (_ProfilerEnable)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnprofilerEnable"), typeof(_ProfilerEnable));
                }
                
                return _ProfilerEnableFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct ProfilerMarkerEnable__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string markerName;
                [MarshalAs(UnmanagedType.I1)]
                internal bool enable;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _ProfilerMarkerEnable(ProfilerMarkerEnable__Args args);
            private static _ProfilerMarkerEnable _ProfilerMarkerEnableFunc;
            internal static _ProfilerMarkerEnable ProfilerMarkerEnable() {
                if (_ProfilerMarkerEnableFunc == null) {
                    _ProfilerMarkerEnableFunc =
                        (_ProfilerMarkerEnable)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnprofilerMarkerEnable"), typeof(_ProfilerMarkerEnable));
                }
                
                return _ProfilerMarkerEnableFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct StopPrecisionTimer__Args
            {
                internal int id;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate int _StopPrecisionTimer(StopPrecisionTimer__Args args);
            private static _StopPrecisionTimer _StopPrecisionTimerFunc;
            internal static _StopPrecisionTimer StopPrecisionTimer() {
                if (_StopPrecisionTimerFunc == null) {
                    _StopPrecisionTimerFunc =
                        (_StopPrecisionTimer)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnstopPrecisionTimer"), typeof(_StopPrecisionTimer));
                }
                
                return _StopPrecisionTimerFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct StartPrecisionTimer__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate int _StartPrecisionTimer(StartPrecisionTimer__Args args);
            private static _StartPrecisionTimer _StartPrecisionTimerFunc;
            internal static _StartPrecisionTimer StartPrecisionTimer() {
                if (_StartPrecisionTimerFunc == null) {
                    _StartPrecisionTimerFunc =
                        (_StartPrecisionTimer)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnstartPrecisionTimer"), typeof(_StartPrecisionTimer));
                }
                
                return _StartPrecisionTimerFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct RedbookGetLastError__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            
            internal delegate IntPtr _RedbookGetLastError(RedbookGetLastError__Args args);
            private static _RedbookGetLastError _RedbookGetLastErrorFunc;
            internal static _RedbookGetLastError RedbookGetLastError() {
                if (_RedbookGetLastErrorFunc == null) {
                    _RedbookGetLastErrorFunc =
                        (_RedbookGetLastError)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnredbookGetLastError"), typeof(_RedbookGetLastError));
                }
                
                return _RedbookGetLastErrorFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct RedbookGetDeviceName__Args
            {
                internal int index;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            
            internal delegate IntPtr _RedbookGetDeviceName(RedbookGetDeviceName__Args args);
            private static _RedbookGetDeviceName _RedbookGetDeviceNameFunc;
            internal static _RedbookGetDeviceName RedbookGetDeviceName() {
                if (_RedbookGetDeviceNameFunc == null) {
                    _RedbookGetDeviceNameFunc =
                        (_RedbookGetDeviceName)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnredbookGetDeviceName"), typeof(_RedbookGetDeviceName));
                }
                
                return _RedbookGetDeviceNameFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct RedbookGetDeviceCount__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate int _RedbookGetDeviceCount(RedbookGetDeviceCount__Args args);
            private static _RedbookGetDeviceCount _RedbookGetDeviceCountFunc;
            internal static _RedbookGetDeviceCount RedbookGetDeviceCount() {
                if (_RedbookGetDeviceCountFunc == null) {
                    _RedbookGetDeviceCountFunc =
                        (_RedbookGetDeviceCount)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnredbookGetDeviceCount"), typeof(_RedbookGetDeviceCount));
                }
                
                return _RedbookGetDeviceCountFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct RedbookSetVolume__Args
            {
                internal float volume;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            [return: MarshalAs(UnmanagedType.I1)]
            internal delegate bool _RedbookSetVolume(RedbookSetVolume__Args args);
            private static _RedbookSetVolume _RedbookSetVolumeFunc;
            internal static _RedbookSetVolume RedbookSetVolume() {
                if (_RedbookSetVolumeFunc == null) {
                    _RedbookSetVolumeFunc =
                        (_RedbookSetVolume)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnredbookSetVolume"), typeof(_RedbookSetVolume));
                }
                
                return _RedbookSetVolumeFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct RedbookGetVolume__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate float _RedbookGetVolume(RedbookGetVolume__Args args);
            private static _RedbookGetVolume _RedbookGetVolumeFunc;
            internal static _RedbookGetVolume RedbookGetVolume() {
                if (_RedbookGetVolumeFunc == null) {
                    _RedbookGetVolumeFunc =
                        (_RedbookGetVolume)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnredbookGetVolume"), typeof(_RedbookGetVolume));
                }
                
                return _RedbookGetVolumeFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct RedbookGetTrackCount__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate int _RedbookGetTrackCount(RedbookGetTrackCount__Args args);
            private static _RedbookGetTrackCount _RedbookGetTrackCountFunc;
            internal static _RedbookGetTrackCount RedbookGetTrackCount() {
                if (_RedbookGetTrackCountFunc == null) {
                    _RedbookGetTrackCountFunc =
                        (_RedbookGetTrackCount)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnredbookGetTrackCount"), typeof(_RedbookGetTrackCount));
                }
                
                return _RedbookGetTrackCountFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct RedbookStop__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            [return: MarshalAs(UnmanagedType.I1)]
            internal delegate bool _RedbookStop(RedbookStop__Args args);
            private static _RedbookStop _RedbookStopFunc;
            internal static _RedbookStop RedbookStop() {
                if (_RedbookStopFunc == null) {
                    _RedbookStopFunc =
                        (_RedbookStop)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnredbookStop"), typeof(_RedbookStop));
                }
                
                return _RedbookStopFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct RedbookPlay__Args
            {
                internal int track;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            [return: MarshalAs(UnmanagedType.I1)]
            internal delegate bool _RedbookPlay(RedbookPlay__Args args);
            private static _RedbookPlay _RedbookPlayFunc;
            internal static _RedbookPlay RedbookPlay() {
                if (_RedbookPlayFunc == null) {
                    _RedbookPlayFunc =
                        (_RedbookPlay)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnredbookPlay"), typeof(_RedbookPlay));
                }
                
                return _RedbookPlayFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct RedbookClose__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            [return: MarshalAs(UnmanagedType.I1)]
            internal delegate bool _RedbookClose(RedbookClose__Args args);
            private static _RedbookClose _RedbookCloseFunc;
            internal static _RedbookClose RedbookClose() {
                if (_RedbookCloseFunc == null) {
                    _RedbookCloseFunc =
                        (_RedbookClose)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnredbookClose"), typeof(_RedbookClose));
                }
                
                return _RedbookCloseFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct RedbookOpen__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string device;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            [return: MarshalAs(UnmanagedType.I1)]
            internal delegate bool _RedbookOpen(RedbookOpen__Args args);
            private static _RedbookOpen _RedbookOpenFunc;
            internal static _RedbookOpen RedbookOpen() {
                if (_RedbookOpenFunc == null) {
                    _RedbookOpenFunc =
                        (_RedbookOpen)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnredbookOpen"), typeof(_RedbookOpen));
                }
                
                return _RedbookOpenFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct DumpMemSnapshot__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string fileName;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _DumpMemSnapshot(DumpMemSnapshot__Args args);
            private static _DumpMemSnapshot _DumpMemSnapshotFunc;
            internal static _DumpMemSnapshot DumpMemSnapshot() {
                if (_DumpMemSnapshotFunc == null) {
                    _DumpMemSnapshotFunc =
                        (_DumpMemSnapshot)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fndumpMemSnapshot"), typeof(_DumpMemSnapshot));
                }
                
                return _DumpMemSnapshotFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct DumpAlloc__Args
            {
                internal int allocNum;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _DumpAlloc(DumpAlloc__Args args);
            private static _DumpAlloc _DumpAllocFunc;
            internal static _DumpAlloc DumpAlloc() {
                if (_DumpAllocFunc == null) {
                    _DumpAllocFunc =
                        (_DumpAlloc)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fndumpAlloc"), typeof(_DumpAlloc));
                }
                
                return _DumpAllocFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct DumpUnflaggedAllocs__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string fileName;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _DumpUnflaggedAllocs(DumpUnflaggedAllocs__Args args);
            private static _DumpUnflaggedAllocs _DumpUnflaggedAllocsFunc;
            internal static _DumpUnflaggedAllocs DumpUnflaggedAllocs() {
                if (_DumpUnflaggedAllocsFunc == null) {
                    _DumpUnflaggedAllocsFunc =
                        (_DumpUnflaggedAllocs)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fndumpUnflaggedAllocs"), typeof(_DumpUnflaggedAllocs));
                }
                
                return _DumpUnflaggedAllocsFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct FlagCurrentAllocs__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _FlagCurrentAllocs(FlagCurrentAllocs__Args args);
            private static _FlagCurrentAllocs _FlagCurrentAllocsFunc;
            internal static _FlagCurrentAllocs FlagCurrentAllocs() {
                if (_FlagCurrentAllocsFunc == null) {
                    _FlagCurrentAllocsFunc =
                        (_FlagCurrentAllocs)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnflagCurrentAllocs"), typeof(_FlagCurrentAllocs));
                }
                
                return _FlagCurrentAllocsFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct FreeMemoryDump__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _FreeMemoryDump(FreeMemoryDump__Args args);
            private static _FreeMemoryDump _FreeMemoryDumpFunc;
            internal static _FreeMemoryDump FreeMemoryDump() {
                if (_FreeMemoryDumpFunc == null) {
                    _FreeMemoryDumpFunc =
                        (_FreeMemoryDump)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnfreeMemoryDump"), typeof(_FreeMemoryDump));
                }
                
                return _FreeMemoryDumpFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct ValidateMemory__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _ValidateMemory(ValidateMemory__Args args);
            private static _ValidateMemory _ValidateMemoryFunc;
            internal static _ValidateMemory ValidateMemory() {
                if (_ValidateMemoryFunc == null) {
                    _ValidateMemoryFunc =
                        (_ValidateMemory)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnvalidateMemory"), typeof(_ValidateMemory));
                }
                
                return _ValidateMemoryFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct SetMainDotCsDir__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string path;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _SetMainDotCsDir(SetMainDotCsDir__Args args);
            private static _SetMainDotCsDir _SetMainDotCsDirFunc;
            internal static _SetMainDotCsDir SetMainDotCsDir() {
                if (_SetMainDotCsDirFunc == null) {
                    _SetMainDotCsDirFunc =
                        (_SetMainDotCsDir)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnsetMainDotCsDir"), typeof(_SetMainDotCsDir));
                }
                
                return _SetMainDotCsDirFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct GetUserHomeDirectory__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            
            internal delegate IntPtr _GetUserHomeDirectory(GetUserHomeDirectory__Args args);
            private static _GetUserHomeDirectory _GetUserHomeDirectoryFunc;
            internal static _GetUserHomeDirectory GetUserHomeDirectory() {
                if (_GetUserHomeDirectoryFunc == null) {
                    _GetUserHomeDirectoryFunc =
                        (_GetUserHomeDirectory)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fngetUserHomeDirectory"), typeof(_GetUserHomeDirectory));
                }
                
                return _GetUserHomeDirectoryFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct GetUserDataDirectory__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            
            internal delegate IntPtr _GetUserDataDirectory(GetUserDataDirectory__Args args);
            private static _GetUserDataDirectory _GetUserDataDirectoryFunc;
            internal static _GetUserDataDirectory GetUserDataDirectory() {
                if (_GetUserDataDirectoryFunc == null) {
                    _GetUserDataDirectoryFunc =
                        (_GetUserDataDirectory)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fngetUserDataDirectory"), typeof(_GetUserDataDirectory));
                }
                
                return _GetUserDataDirectoryFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct GetTemporaryFileName__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            
            internal delegate IntPtr _GetTemporaryFileName(GetTemporaryFileName__Args args);
            private static _GetTemporaryFileName _GetTemporaryFileNameFunc;
            internal static _GetTemporaryFileName GetTemporaryFileName() {
                if (_GetTemporaryFileNameFunc == null) {
                    _GetTemporaryFileNameFunc =
                        (_GetTemporaryFileName)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fngetTemporaryFileName"), typeof(_GetTemporaryFileName));
                }
                
                return _GetTemporaryFileNameFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct GetTemporaryDirectory__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            
            internal delegate IntPtr _GetTemporaryDirectory(GetTemporaryDirectory__Args args);
            private static _GetTemporaryDirectory _GetTemporaryDirectoryFunc;
            internal static _GetTemporaryDirectory GetTemporaryDirectory() {
                if (_GetTemporaryDirectoryFunc == null) {
                    _GetTemporaryDirectoryFunc =
                        (_GetTemporaryDirectory)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fngetTemporaryDirectory"), typeof(_GetTemporaryDirectory));
                }
                
                return _GetTemporaryDirectoryFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct Assert__Args
            {
                [MarshalAs(UnmanagedType.I1)]
                internal bool condition;
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string message;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _Assert(Assert__Args args);
            private static _Assert _AssertFunc;
            internal static _Assert Assert() {
                if (_AssertFunc == null) {
                    _AssertFunc =
                        (_Assert)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnAssert"), typeof(_Assert));
                }
                
                return _AssertFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct GetRandom__Args
            {
                internal int a;
                internal int b;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate float _GetRandom(GetRandom__Args args);
            private static _GetRandom _GetRandomFunc;
            internal static _GetRandom GetRandom() {
                if (_GetRandomFunc == null) {
                    _GetRandomFunc =
                        (_GetRandom)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fngetRandom"), typeof(_GetRandom));
                }
                
                return _GetRandomFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct GetRandomSeed__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate int _GetRandomSeed(GetRandomSeed__Args args);
            private static _GetRandomSeed _GetRandomSeedFunc;
            internal static _GetRandomSeed GetRandomSeed() {
                if (_GetRandomSeedFunc == null) {
                    _GetRandomSeedFunc =
                        (_GetRandomSeed)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fngetRandomSeed"), typeof(_GetRandomSeed));
                }
                
                return _GetRandomSeedFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct SetRandomSeed__Args
            {
                internal int seed;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _SetRandomSeed(SetRandomSeed__Args args);
            private static _SetRandomSeed _SetRandomSeedFunc;
            internal static _SetRandomSeed SetRandomSeed() {
                if (_SetRandomSeedFunc == null) {
                    _SetRandomSeedFunc =
                        (_SetRandomSeed)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnsetRandomSeed"), typeof(_SetRandomSeed));
                }
                
                return _SetRandomSeedFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct GetBoxCenter__Args
            {
                internal IntPtr box;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate Point3F.InternalStruct _GetBoxCenter(GetBoxCenter__Args args);
            private static _GetBoxCenter _GetBoxCenterFunc;
            internal static _GetBoxCenter GetBoxCenter() {
                if (_GetBoxCenterFunc == null) {
                    _GetBoxCenterFunc =
                        (_GetBoxCenter)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fngetBoxCenter"), typeof(_GetBoxCenter));
                }
                
                return _GetBoxCenterFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct MatrixMulPoint__Args
            {
                internal IntPtr transform;
                internal IntPtr point;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate Point3F.InternalStruct _MatrixMulPoint(MatrixMulPoint__Args args);
            private static _MatrixMulPoint _MatrixMulPointFunc;
            internal static _MatrixMulPoint MatrixMulPoint() {
                if (_MatrixMulPointFunc == null) {
                    _MatrixMulPointFunc =
                        (_MatrixMulPoint)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnMatrixMulPoint"), typeof(_MatrixMulPoint));
                }
                
                return _MatrixMulPointFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct MatrixMulVector__Args
            {
                internal IntPtr transform;
                internal IntPtr vector;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate Point3F.InternalStruct _MatrixMulVector(MatrixMulVector__Args args);
            private static _MatrixMulVector _MatrixMulVectorFunc;
            internal static _MatrixMulVector MatrixMulVector() {
                if (_MatrixMulVectorFunc == null) {
                    _MatrixMulVectorFunc =
                        (_MatrixMulVector)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnMatrixMulVector"), typeof(_MatrixMulVector));
                }
                
                return _MatrixMulVectorFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct MatrixMultiply__Args
            {
                internal IntPtr left;
                internal IntPtr right;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate TransformF.InternalStruct _MatrixMultiply(MatrixMultiply__Args args);
            private static _MatrixMultiply _MatrixMultiplyFunc;
            internal static _MatrixMultiply MatrixMultiply() {
                if (_MatrixMultiplyFunc == null) {
                    _MatrixMultiplyFunc =
                        (_MatrixMultiply)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnMatrixMultiply"), typeof(_MatrixMultiply));
                }
                
                return _MatrixMultiplyFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct MatrixCreateFromEuler__Args
            {
                internal IntPtr angles;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate TransformF.InternalStruct _MatrixCreateFromEuler(MatrixCreateFromEuler__Args args);
            private static _MatrixCreateFromEuler _MatrixCreateFromEulerFunc;
            internal static _MatrixCreateFromEuler MatrixCreateFromEuler() {
                if (_MatrixCreateFromEulerFunc == null) {
                    _MatrixCreateFromEulerFunc =
                        (_MatrixCreateFromEuler)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnMatrixCreateFromEuler"), typeof(_MatrixCreateFromEuler));
                }
                
                return _MatrixCreateFromEulerFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct MatrixCreate__Args
            {
                internal IntPtr position;
                internal IntPtr orientation;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate TransformF.InternalStruct _MatrixCreate(MatrixCreate__Args args);
            private static _MatrixCreate _MatrixCreateFunc;
            internal static _MatrixCreate MatrixCreate() {
                if (_MatrixCreateFunc == null) {
                    _MatrixCreateFunc =
                        (_MatrixCreate)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnMatrixCreate"), typeof(_MatrixCreate));
                }
                
                return _MatrixCreateFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct VectorReflect__Args
            {
                internal IntPtr vec;
                internal IntPtr normal;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate Point3F.InternalStruct _VectorReflect(VectorReflect__Args args);
            private static _VectorReflect _VectorReflectFunc;
            internal static _VectorReflect VectorReflect() {
                if (_VectorReflectFunc == null) {
                    _VectorReflectFunc =
                        (_VectorReflect)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnVectorReflect"), typeof(_VectorReflect));
                }
                
                return _VectorReflectFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct VectorLerp__Args
            {
                internal IntPtr a;
                internal IntPtr b;
                internal float t;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate Point3F.InternalStruct _VectorLerp(VectorLerp__Args args);
            private static _VectorLerp _VectorLerpFunc;
            internal static _VectorLerp VectorLerp() {
                if (_VectorLerpFunc == null) {
                    _VectorLerpFunc =
                        (_VectorLerp)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnVectorLerp"), typeof(_VectorLerp));
                }
                
                return _VectorLerpFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct VectorRot__Args
            {
                internal IntPtr v;
                internal float angle;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            
            internal delegate IntPtr _VectorRot(VectorRot__Args args);
            private static _VectorRot _VectorRotFunc;
            internal static _VectorRot VectorRot() {
                if (_VectorRotFunc == null) {
                    _VectorRotFunc =
                        (_VectorRot)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnVectorRot"), typeof(_VectorRot));
                }
                
                return _VectorRotFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct VectorOrthoBasis__Args
            {
                internal IntPtr aa;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate MatrixF.InternalStruct _VectorOrthoBasis(VectorOrthoBasis__Args args);
            private static _VectorOrthoBasis _VectorOrthoBasisFunc;
            internal static _VectorOrthoBasis VectorOrthoBasis() {
                if (_VectorOrthoBasisFunc == null) {
                    _VectorOrthoBasisFunc =
                        (_VectorOrthoBasis)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnVectorOrthoBasis"), typeof(_VectorOrthoBasis));
                }
                
                return _VectorOrthoBasisFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct VectorLen__Args
            {
                internal IntPtr v;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate float _VectorLen(VectorLen__Args args);
            private static _VectorLen _VectorLenFunc;
            internal static _VectorLen VectorLen() {
                if (_VectorLenFunc == null) {
                    _VectorLenFunc =
                        (_VectorLen)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnVectorLen"), typeof(_VectorLen));
                }
                
                return _VectorLenFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct VectorMidPoint__Args
            {
                internal IntPtr a;
                internal IntPtr b;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate Point3F.InternalStruct _VectorMidPoint(VectorMidPoint__Args args);
            private static _VectorMidPoint _VectorMidPointFunc;
            internal static _VectorMidPoint VectorMidPoint() {
                if (_VectorMidPointFunc == null) {
                    _VectorMidPointFunc =
                        (_VectorMidPoint)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnVectorMidPoint"), typeof(_VectorMidPoint));
                }
                
                return _VectorMidPointFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct VectorDist__Args
            {
                internal IntPtr a;
                internal IntPtr b;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate float _VectorDist(VectorDist__Args args);
            private static _VectorDist _VectorDistFunc;
            internal static _VectorDist VectorDist() {
                if (_VectorDistFunc == null) {
                    _VectorDistFunc =
                        (_VectorDist)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnVectorDist"), typeof(_VectorDist));
                }
                
                return _VectorDistFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct VectorCross__Args
            {
                internal IntPtr a;
                internal IntPtr b;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate Point3F.InternalStruct _VectorCross(VectorCross__Args args);
            private static _VectorCross _VectorCrossFunc;
            internal static _VectorCross VectorCross() {
                if (_VectorCrossFunc == null) {
                    _VectorCrossFunc =
                        (_VectorCross)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnVectorCross"), typeof(_VectorCross));
                }
                
                return _VectorCrossFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct VectorDot__Args
            {
                internal IntPtr a;
                internal IntPtr b;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate float _VectorDot(VectorDot__Args args);
            private static _VectorDot _VectorDotFunc;
            internal static _VectorDot VectorDot() {
                if (_VectorDotFunc == null) {
                    _VectorDotFunc =
                        (_VectorDot)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnVectorDot"), typeof(_VectorDot));
                }
                
                return _VectorDotFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct VectorNormalize__Args
            {
                internal IntPtr v;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate Point3F.InternalStruct _VectorNormalize(VectorNormalize__Args args);
            private static _VectorNormalize _VectorNormalizeFunc;
            internal static _VectorNormalize VectorNormalize() {
                if (_VectorNormalizeFunc == null) {
                    _VectorNormalizeFunc =
                        (_VectorNormalize)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnVectorNormalize"), typeof(_VectorNormalize));
                }
                
                return _VectorNormalizeFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct VectorDiv__Args
            {
                internal IntPtr a;
                internal IntPtr b;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate Point3F.InternalStruct _VectorDiv(VectorDiv__Args args);
            private static _VectorDiv _VectorDivFunc;
            internal static _VectorDiv VectorDiv() {
                if (_VectorDivFunc == null) {
                    _VectorDivFunc =
                        (_VectorDiv)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnVectorDiv"), typeof(_VectorDiv));
                }
                
                return _VectorDivFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct VectorMul__Args
            {
                internal IntPtr a;
                internal IntPtr b;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate Point3F.InternalStruct _VectorMul(VectorMul__Args args);
            private static _VectorMul _VectorMulFunc;
            internal static _VectorMul VectorMul() {
                if (_VectorMulFunc == null) {
                    _VectorMulFunc =
                        (_VectorMul)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnVectorMul"), typeof(_VectorMul));
                }
                
                return _VectorMulFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct VectorScale__Args
            {
                internal IntPtr a;
                internal float scalar;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate Point3F.InternalStruct _VectorScale(VectorScale__Args args);
            private static _VectorScale _VectorScaleFunc;
            internal static _VectorScale VectorScale() {
                if (_VectorScaleFunc == null) {
                    _VectorScaleFunc =
                        (_VectorScale)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnVectorScale"), typeof(_VectorScale));
                }
                
                return _VectorScaleFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct VectorSub__Args
            {
                internal IntPtr a;
                internal IntPtr b;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate Point3F.InternalStruct _VectorSub(VectorSub__Args args);
            private static _VectorSub _VectorSubFunc;
            internal static _VectorSub VectorSub() {
                if (_VectorSubFunc == null) {
                    _VectorSubFunc =
                        (_VectorSub)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnVectorSub"), typeof(_VectorSub));
                }
                
                return _VectorSubFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct VectorAdd__Args
            {
                internal IntPtr a;
                internal IntPtr b;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate Point3F.InternalStruct _VectorAdd(VectorAdd__Args args);
            private static _VectorAdd _VectorAddFunc;
            internal static _VectorAdd VectorAdd() {
                if (_VectorAddFunc == null) {
                    _VectorAddFunc =
                        (_VectorAdd)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnVectorAdd"), typeof(_VectorAdd));
                }
                
                return _VectorAddFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct GetRotationDirection__Args
            {
                internal IntPtr rot;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate Point3F.InternalStruct _GetRotationDirection(GetRotationDirection__Args args);
            private static _GetRotationDirection _GetRotationDirectionFunc;
            internal static _GetRotationDirection GetRotationDirection() {
                if (_GetRotationDirectionFunc == null) {
                    _GetRotationDirectionFunc =
                        (_GetRotationDirection)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fngetRotationDirection"), typeof(_GetRotationDirection));
                }
                
                return _GetRotationDirectionFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct GetRotationUpVector__Args
            {
                internal IntPtr rot;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate Point3F.InternalStruct _GetRotationUpVector(GetRotationUpVector__Args args);
            private static _GetRotationUpVector _GetRotationUpVectorFunc;
            internal static _GetRotationUpVector GetRotationUpVector() {
                if (_GetRotationUpVectorFunc == null) {
                    _GetRotationUpVectorFunc =
                        (_GetRotationUpVector)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fngetRotationUpVector"), typeof(_GetRotationUpVector));
                }
                
                return _GetRotationUpVectorFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct GetRotationRightVector__Args
            {
                internal IntPtr rot;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate Point3F.InternalStruct _GetRotationRightVector(GetRotationRightVector__Args args);
            private static _GetRotationRightVector _GetRotationRightVectorFunc;
            internal static _GetRotationRightVector GetRotationRightVector() {
                if (_GetRotationRightVectorFunc == null) {
                    _GetRotationRightVectorFunc =
                        (_GetRotationRightVector)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fngetRotationRightVector"), typeof(_GetRotationRightVector));
                }
                
                return _GetRotationRightVectorFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct GetRotationForwardVector__Args
            {
                internal IntPtr rot;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate Point3F.InternalStruct _GetRotationForwardVector(GetRotationForwardVector__Args args);
            private static _GetRotationForwardVector _GetRotationForwardVectorFunc;
            internal static _GetRotationForwardVector GetRotationForwardVector() {
                if (_GetRotationForwardVectorFunc == null) {
                    _GetRotationForwardVectorFunc =
                        (_GetRotationForwardVector)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fngetRotationForwardVector"), typeof(_GetRotationForwardVector));
                }
                
                return _GetRotationForwardVectorFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct SetRotationUpVector__Args
            {
                internal IntPtr rot;
                internal IntPtr upVec;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate RotationF.InternalStruct _SetRotationUpVector(SetRotationUpVector__Args args);
            private static _SetRotationUpVector _SetRotationUpVectorFunc;
            internal static _SetRotationUpVector SetRotationUpVector() {
                if (_SetRotationUpVectorFunc == null) {
                    _SetRotationUpVectorFunc =
                        (_SetRotationUpVector)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnsetRotationUpVector"), typeof(_SetRotationUpVector));
                }
                
                return _SetRotationUpVectorFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct SetRotationRightVector__Args
            {
                internal IntPtr rot;
                internal IntPtr rightVec;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate RotationF.InternalStruct _SetRotationRightVector(SetRotationRightVector__Args args);
            private static _SetRotationRightVector _SetRotationRightVectorFunc;
            internal static _SetRotationRightVector SetRotationRightVector() {
                if (_SetRotationRightVectorFunc == null) {
                    _SetRotationRightVectorFunc =
                        (_SetRotationRightVector)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnsetRotationRightVector"), typeof(_SetRotationRightVector));
                }
                
                return _SetRotationRightVectorFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct RotationLookAt__Args
            {
                internal IntPtr origin;
                internal IntPtr target;
                internal IntPtr up;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate RotationF.InternalStruct _RotationLookAt(RotationLookAt__Args args);
            private static _RotationLookAt _RotationLookAtFunc;
            internal static _RotationLookAt RotationLookAt() {
                if (_RotationLookAtFunc == null) {
                    _RotationLookAtFunc =
                        (_RotationLookAt)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnRotationLookAt"), typeof(_RotationLookAt));
                }
                
                return _RotationLookAtFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct InterpolateRotation__Args
            {
                internal IntPtr a;
                internal IntPtr b;
                internal float factor;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate RotationF.InternalStruct _InterpolateRotation(InterpolateRotation__Args args);
            private static _InterpolateRotation _InterpolateRotationFunc;
            internal static _InterpolateRotation InterpolateRotation() {
                if (_InterpolateRotationFunc == null) {
                    _InterpolateRotationFunc =
                        (_InterpolateRotation)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnInterpolateRotation"), typeof(_InterpolateRotation));
                }
                
                return _InterpolateRotationFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct SubtractRotation__Args
            {
                internal IntPtr a;
                internal IntPtr b;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate RotationF.InternalStruct _SubtractRotation(SubtractRotation__Args args);
            private static _SubtractRotation _SubtractRotationFunc;
            internal static _SubtractRotation SubtractRotation() {
                if (_SubtractRotationFunc == null) {
                    _SubtractRotationFunc =
                        (_SubtractRotation)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnSubtractRotation"), typeof(_SubtractRotation));
                }
                
                return _SubtractRotationFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct AddRotation__Args
            {
                internal IntPtr a;
                internal IntPtr b;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate RotationF.InternalStruct _AddRotation(AddRotation__Args args);
            private static _AddRotation _AddRotationFunc;
            internal static _AddRotation AddRotation() {
                if (_AddRotationFunc == null) {
                    _AddRotationFunc =
                        (_AddRotation)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnAddRotation"), typeof(_AddRotation));
                }
                
                return _AddRotationFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct MGetSignedAngleBetweenVectors__Args
            {
                internal IntPtr vecA;
                internal IntPtr vecB;
                internal IntPtr norm;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate float _MGetSignedAngleBetweenVectors(MGetSignedAngleBetweenVectors__Args args);
            private static _MGetSignedAngleBetweenVectors _MGetSignedAngleBetweenVectorsFunc;
            internal static _MGetSignedAngleBetweenVectors MGetSignedAngleBetweenVectors() {
                if (_MGetSignedAngleBetweenVectorsFunc == null) {
                    _MGetSignedAngleBetweenVectorsFunc =
                        (_MGetSignedAngleBetweenVectors)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnmGetSignedAngleBetweenVectors"), typeof(_MGetSignedAngleBetweenVectors));
                }
                
                return _MGetSignedAngleBetweenVectorsFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct MGetAngleBetweenVectors__Args
            {
                internal IntPtr vecA;
                internal IntPtr vecB;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate float _MGetAngleBetweenVectors(MGetAngleBetweenVectors__Args args);
            private static _MGetAngleBetweenVectors _MGetAngleBetweenVectorsFunc;
            internal static _MGetAngleBetweenVectors MGetAngleBetweenVectors() {
                if (_MGetAngleBetweenVectorsFunc == null) {
                    _MGetAngleBetweenVectorsFunc =
                        (_MGetAngleBetweenVectors)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnmGetAngleBetweenVectors"), typeof(_MGetAngleBetweenVectors));
                }
                
                return _MGetAngleBetweenVectorsFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct MRandomPointInSphere__Args
            {
                internal float radius;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate Point3F.InternalStruct _MRandomPointInSphere(MRandomPointInSphere__Args args);
            private static _MRandomPointInSphere _MRandomPointInSphereFunc;
            internal static _MRandomPointInSphere MRandomPointInSphere() {
                if (_MRandomPointInSphereFunc == null) {
                    _MRandomPointInSphereFunc =
                        (_MRandomPointInSphere)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnmRandomPointInSphere"), typeof(_MRandomPointInSphere));
                }
                
                return _MRandomPointInSphereFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct MRandomDir__Args
            {
                internal IntPtr axis;
                internal float angleMin;
                internal float angleMax;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate Point3F.InternalStruct _MRandomDir(MRandomDir__Args args);
            private static _MRandomDir _MRandomDirFunc;
            internal static _MRandomDir MRandomDir() {
                if (_MRandomDirFunc == null) {
                    _MRandomDirFunc =
                        (_MRandomDir)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnmRandomDir"), typeof(_MRandomDir));
                }
                
                return _MRandomDirFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct MIsPow2__Args
            {
                internal int v;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            [return: MarshalAs(UnmanagedType.I1)]
            internal delegate bool _MIsPow2(MIsPow2__Args args);
            private static _MIsPow2 _MIsPow2Func;
            internal static _MIsPow2 MIsPow2() {
                if (_MIsPow2Func == null) {
                    _MIsPow2Func =
                        (_MIsPow2)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnmIsPow2"), typeof(_MIsPow2));
                }
                
                return _MIsPow2Func;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct M2Pi__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate float _M2Pi(M2Pi__Args args);
            private static _M2Pi _M2PiFunc;
            internal static _M2Pi M2Pi() {
                if (_M2PiFunc == null) {
                    _M2PiFunc =
                        (_M2Pi)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnm2Pi"), typeof(_M2Pi));
                }
                
                return _M2PiFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct MPi__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate float _MPi(MPi__Args args);
            private static _MPi _MPiFunc;
            internal static _MPi MPi() {
                if (_MPiFunc == null) {
                    _MPiFunc =
                        (_MPi)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnmPi"), typeof(_MPi));
                }
                
                return _MPiFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct MLerp__Args
            {
                internal float v1;
                internal float v2;
                internal float time;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate float _MLerp(MLerp__Args args);
            private static _MLerp _MLerpFunc;
            internal static _MLerp MLerp() {
                if (_MLerpFunc == null) {
                    _MLerpFunc =
                        (_MLerp)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnmLerp"), typeof(_MLerp));
                }
                
                return _MLerpFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct GetMin__Args
            {
                internal float v1;
                internal float v2;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate float _GetMin(GetMin__Args args);
            private static _GetMin _GetMinFunc;
            internal static _GetMin GetMin() {
                if (_GetMinFunc == null) {
                    _GetMinFunc =
                        (_GetMin)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fngetMin"), typeof(_GetMin));
                }
                
                return _GetMinFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct GetMax__Args
            {
                internal float v1;
                internal float v2;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate float _GetMax(GetMax__Args args);
            private static _GetMax _GetMaxFunc;
            internal static _GetMax GetMax() {
                if (_GetMaxFunc == null) {
                    _GetMaxFunc =
                        (_GetMax)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fngetMax"), typeof(_GetMax));
                }
                
                return _GetMaxFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct MWrap__Args
            {
                internal int v;
                internal int min;
                internal int max;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate int _MWrap(MWrap__Args args);
            private static _MWrap _MWrapFunc;
            internal static _MWrap MWrap() {
                if (_MWrapFunc == null) {
                    _MWrapFunc =
                        (_MWrap)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnmWrap"), typeof(_MWrap));
                }
                
                return _MWrapFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct MWrapF__Args
            {
                internal float v;
                internal float min;
                internal float max;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate float _MWrapF(MWrapF__Args args);
            private static _MWrapF _MWrapFFunc;
            internal static _MWrapF MWrapF() {
                if (_MWrapFFunc == null) {
                    _MWrapFFunc =
                        (_MWrapF)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnmWrapF"), typeof(_MWrapF));
                }
                
                return _MWrapFFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct MSaturate__Args
            {
                internal float v;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate float _MSaturate(MSaturate__Args args);
            private static _MSaturate _MSaturateFunc;
            internal static _MSaturate MSaturate() {
                if (_MSaturateFunc == null) {
                    _MSaturateFunc =
                        (_MSaturate)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnmSaturate"), typeof(_MSaturate));
                }
                
                return _MSaturateFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct MClamp__Args
            {
                internal float v;
                internal float min;
                internal float max;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate float _MClamp(MClamp__Args args);
            private static _MClamp _MClampFunc;
            internal static _MClamp MClamp() {
                if (_MClampFunc == null) {
                    _MClampFunc =
                        (_MClamp)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnmClamp"), typeof(_MClamp));
                }
                
                return _MClampFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct MDegToRad__Args
            {
                internal float degrees;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate float _MDegToRad(MDegToRad__Args args);
            private static _MDegToRad _MDegToRadFunc;
            internal static _MDegToRad MDegToRad() {
                if (_MDegToRadFunc == null) {
                    _MDegToRadFunc =
                        (_MDegToRad)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnmDegToRad"), typeof(_MDegToRad));
                }
                
                return _MDegToRadFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct MRadToDeg__Args
            {
                internal float radians;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate float _MRadToDeg(MRadToDeg__Args args);
            private static _MRadToDeg _MRadToDegFunc;
            internal static _MRadToDeg MRadToDeg() {
                if (_MRadToDegFunc == null) {
                    _MRadToDegFunc =
                        (_MRadToDeg)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnmRadToDeg"), typeof(_MRadToDeg));
                }
                
                return _MRadToDegFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct MAtan__Args
            {
                internal float rise;
                internal float run;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate float _MAtan(MAtan__Args args);
            private static _MAtan _MAtanFunc;
            internal static _MAtan MAtan() {
                if (_MAtanFunc == null) {
                    _MAtanFunc =
                        (_MAtan)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnmAtan"), typeof(_MAtan));
                }
                
                return _MAtanFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct MAcos__Args
            {
                internal float v;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate float _MAcos(MAcos__Args args);
            private static _MAcos _MAcosFunc;
            internal static _MAcos MAcos() {
                if (_MAcosFunc == null) {
                    _MAcosFunc =
                        (_MAcos)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnmAcos"), typeof(_MAcos));
                }
                
                return _MAcosFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct MAsin__Args
            {
                internal float v;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate float _MAsin(MAsin__Args args);
            private static _MAsin _MAsinFunc;
            internal static _MAsin MAsin() {
                if (_MAsinFunc == null) {
                    _MAsinFunc =
                        (_MAsin)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnmAsin"), typeof(_MAsin));
                }
                
                return _MAsinFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct MTan__Args
            {
                internal float v;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate float _MTan(MTan__Args args);
            private static _MTan _MTanFunc;
            internal static _MTan MTan() {
                if (_MTanFunc == null) {
                    _MTanFunc =
                        (_MTan)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnmTan"), typeof(_MTan));
                }
                
                return _MTanFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct MCos__Args
            {
                internal float v;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate float _MCos(MCos__Args args);
            private static _MCos _MCosFunc;
            internal static _MCos MCos() {
                if (_MCosFunc == null) {
                    _MCosFunc =
                        (_MCos)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnmCos"), typeof(_MCos));
                }
                
                return _MCosFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct MSin__Args
            {
                internal float v;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate float _MSin(MSin__Args args);
            private static _MSin _MSinFunc;
            internal static _MSin MSin() {
                if (_MSinFunc == null) {
                    _MSinFunc =
                        (_MSin)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnmSin"), typeof(_MSin));
                }
                
                return _MSinFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct MLog__Args
            {
                internal float v;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate float _MLog(MLog__Args args);
            private static _MLog _MLogFunc;
            internal static _MLog MLog() {
                if (_MLogFunc == null) {
                    _MLogFunc =
                        (_MLog)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnmLog"), typeof(_MLog));
                }
                
                return _MLogFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct MPow__Args
            {
                internal float v;
                internal float p;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate float _MPow(MPow__Args args);
            private static _MPow _MPowFunc;
            internal static _MPow MPow() {
                if (_MPowFunc == null) {
                    _MPowFunc =
                        (_MPow)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnmPow"), typeof(_MPow));
                }
                
                return _MPowFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct MSqrt__Args
            {
                internal float v;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate float _MSqrt(MSqrt__Args args);
            private static _MSqrt _MSqrtFunc;
            internal static _MSqrt MSqrt() {
                if (_MSqrtFunc == null) {
                    _MSqrtFunc =
                        (_MSqrt)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnmSqrt"), typeof(_MSqrt));
                }
                
                return _MSqrtFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct MFMod__Args
            {
                internal float v;
                internal float d;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate float _MFMod(MFMod__Args args);
            private static _MFMod _MFModFunc;
            internal static _MFMod MFMod() {
                if (_MFModFunc == null) {
                    _MFModFunc =
                        (_MFMod)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnmFMod"), typeof(_MFMod));
                }
                
                return _MFModFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct MAbs__Args
            {
                internal float v;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate float _MAbs(MAbs__Args args);
            private static _MAbs _MAbsFunc;
            internal static _MAbs MAbs() {
                if (_MAbsFunc == null) {
                    _MAbsFunc =
                        (_MAbs)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnmAbs"), typeof(_MAbs));
                }
                
                return _MAbsFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct MFloatLength__Args
            {
                internal float v;
                internal uint precision;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            
            internal delegate IntPtr _MFloatLength(MFloatLength__Args args);
            private static _MFloatLength _MFloatLengthFunc;
            internal static _MFloatLength MFloatLength() {
                if (_MFloatLengthFunc == null) {
                    _MFloatLengthFunc =
                        (_MFloatLength)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnmFloatLength"), typeof(_MFloatLength));
                }
                
                return _MFloatLengthFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct MCeil__Args
            {
                internal float v;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate int _MCeil(MCeil__Args args);
            private static _MCeil _MCeilFunc;
            internal static _MCeil MCeil() {
                if (_MCeilFunc == null) {
                    _MCeilFunc =
                        (_MCeil)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnmCeil"), typeof(_MCeil));
                }
                
                return _MCeilFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct MRoundColour__Args
            {
                internal float v;
                internal int n;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate float _MRoundColour(MRoundColour__Args args);
            private static _MRoundColour _MRoundColourFunc;
            internal static _MRoundColour MRoundColour() {
                if (_MRoundColourFunc == null) {
                    _MRoundColourFunc =
                        (_MRoundColour)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnmRoundColour"), typeof(_MRoundColour));
                }
                
                return _MRoundColourFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct MRoundDelta__Args
            {
                internal float v;
                internal int d;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate int _MRoundDelta(MRoundDelta__Args args);
            private static _MRoundDelta _MRoundDeltaFunc;
            internal static _MRoundDelta MRoundDelta() {
                if (_MRoundDeltaFunc == null) {
                    _MRoundDeltaFunc =
                        (_MRoundDelta)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnmRoundDelta"), typeof(_MRoundDelta));
                }
                
                return _MRoundDeltaFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct MRound__Args
            {
                internal float v;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate int _MRound(MRound__Args args);
            private static _MRound _MRoundFunc;
            internal static _MRound MRound() {
                if (_MRoundFunc == null) {
                    _MRoundFunc =
                        (_MRound)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnmRound"), typeof(_MRound));
                }
                
                return _MRoundFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct MFloor__Args
            {
                internal float v;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate int _MFloor(MFloor__Args args);
            private static _MFloor _MFloorFunc;
            internal static _MFloor MFloor() {
                if (_MFloorFunc == null) {
                    _MFloorFunc =
                        (_MFloor)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnmFloor"), typeof(_MFloor));
                }
                
                return _MFloorFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct MSolveQuartic__Args
            {
                internal float a;
                internal float b;
                internal float c;
                internal float d;
                internal float e;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            
            internal delegate IntPtr _MSolveQuartic(MSolveQuartic__Args args);
            private static _MSolveQuartic _MSolveQuarticFunc;
            internal static _MSolveQuartic MSolveQuartic() {
                if (_MSolveQuarticFunc == null) {
                    _MSolveQuarticFunc =
                        (_MSolveQuartic)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnmSolveQuartic"), typeof(_MSolveQuartic));
                }
                
                return _MSolveQuarticFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct MSolveCubic__Args
            {
                internal float a;
                internal float b;
                internal float c;
                internal float d;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            
            internal delegate IntPtr _MSolveCubic(MSolveCubic__Args args);
            private static _MSolveCubic _MSolveCubicFunc;
            internal static _MSolveCubic MSolveCubic() {
                if (_MSolveCubicFunc == null) {
                    _MSolveCubicFunc =
                        (_MSolveCubic)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnmSolveCubic"), typeof(_MSolveCubic));
                }
                
                return _MSolveCubicFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct MSolveQuadratic__Args
            {
                internal float a;
                internal float b;
                internal float c;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            
            internal delegate IntPtr _MSolveQuadratic(MSolveQuadratic__Args args);
            private static _MSolveQuadratic _MSolveQuadraticFunc;
            internal static _MSolveQuadratic MSolveQuadratic() {
                if (_MSolveQuadraticFunc == null) {
                    _MSolveQuadraticFunc =
                        (_MSolveQuadratic)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnmSolveQuadratic"), typeof(_MSolveQuadratic));
                }
                
                return _MSolveQuadraticFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct EnableSamples__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string pattern;
                [MarshalAs(UnmanagedType.I1)]
                internal bool state;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _EnableSamples(EnableSamples__Args args);
            private static _EnableSamples _EnableSamplesFunc;
            internal static _EnableSamples EnableSamples() {
                if (_EnableSamplesFunc == null) {
                    _EnableSamplesFunc =
                        (_EnableSamples)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnenableSamples"), typeof(_EnableSamples));
                }
                
                return _EnableSamplesFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct StopSampling__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _StopSampling(StopSampling__Args args);
            private static _StopSampling _StopSamplingFunc;
            internal static _StopSampling StopSampling() {
                if (_StopSamplingFunc == null) {
                    _StopSamplingFunc =
                        (_StopSampling)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnstopSampling"), typeof(_StopSampling));
                }
                
                return _StopSamplingFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct BeginSampling__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string location;
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string backend;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _BeginSampling(BeginSampling__Args args);
            private static _BeginSampling _BeginSamplingFunc;
            internal static _BeginSampling BeginSampling() {
                if (_BeginSamplingFunc == null) {
                    _BeginSamplingFunc =
                        (_BeginSampling)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnbeginSampling"), typeof(_BeginSampling));
                }
                
                return _BeginSamplingFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct ResetFPSTracker__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _ResetFPSTracker(ResetFPSTracker__Args args);
            private static _ResetFPSTracker _ResetFPSTrackerFunc;
            internal static _ResetFPSTracker ResetFPSTracker() {
                if (_ResetFPSTrackerFunc == null) {
                    _ResetFPSTrackerFunc =
                        (_ResetFPSTracker)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnresetFPSTracker"), typeof(_ResetFPSTracker));
                }
                
                return _ResetFPSTrackerFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct DumpNetStringTable__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _DumpNetStringTable(DumpNetStringTable__Args args);
            private static _DumpNetStringTable _DumpNetStringTableFunc;
            internal static _DumpNetStringTable DumpNetStringTable() {
                if (_DumpNetStringTableFunc == null) {
                    _DumpNetStringTableFunc =
                        (_DumpNetStringTable)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fndumpNetStringTable"), typeof(_DumpNetStringTable));
                }
                
                return _DumpNetStringTableFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct AllowConnections__Args
            {
                [MarshalAs(UnmanagedType.I1)]
                internal bool allow;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _AllowConnections(AllowConnections__Args args);
            private static _AllowConnections _AllowConnectionsFunc;
            internal static _AllowConnections AllowConnections() {
                if (_AllowConnectionsFunc == null) {
                    _AllowConnectionsFunc =
                        (_AllowConnections)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnallowConnections"), typeof(_AllowConnections));
                }
                
                return _AllowConnectionsFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct GetCurrentActionMap__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate IntPtr _GetCurrentActionMap(GetCurrentActionMap__Args args);
            private static _GetCurrentActionMap _GetCurrentActionMapFunc;
            internal static _GetCurrentActionMap GetCurrentActionMap() {
                if (_GetCurrentActionMapFunc == null) {
                    _GetCurrentActionMapFunc =
                        (_GetCurrentActionMap)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fngetCurrentActionMap"), typeof(_GetCurrentActionMap));
                }
                
                return _GetCurrentActionMapFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct CompileLanguage__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string inputFile;
                [MarshalAs(UnmanagedType.I1)]
                internal bool createMap;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _CompileLanguage(CompileLanguage__Args args);
            private static _CompileLanguage _CompileLanguageFunc;
            internal static _CompileLanguage CompileLanguage() {
                if (_CompileLanguageFunc == null) {
                    _CompileLanguageFunc =
                        (_CompileLanguage)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnCompileLanguage"), typeof(_CompileLanguage));
                }
                
                return _CompileLanguageFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct SetCoreLangTable__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string lgTable;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _SetCoreLangTable(SetCoreLangTable__Args args);
            private static _SetCoreLangTable _SetCoreLangTableFunc;
            internal static _SetCoreLangTable SetCoreLangTable() {
                if (_SetCoreLangTableFunc == null) {
                    _SetCoreLangTableFunc =
                        (_SetCoreLangTable)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnsetCoreLangTable"), typeof(_SetCoreLangTable));
                }
                
                return _SetCoreLangTableFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct GetCoreLangTable__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate int _GetCoreLangTable(GetCoreLangTable__Args args);
            private static _GetCoreLangTable _GetCoreLangTableFunc;
            internal static _GetCoreLangTable GetCoreLangTable() {
                if (_GetCoreLangTableFunc == null) {
                    _GetCoreLangTableFunc =
                        (_GetCoreLangTable)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fngetCoreLangTable"), typeof(_GetCoreLangTable));
                }
                
                return _GetCoreLangTableFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct DumpStringMemStats__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _DumpStringMemStats(DumpStringMemStats__Args args);
            private static _DumpStringMemStats _DumpStringMemStatsFunc;
            internal static _DumpStringMemStats DumpStringMemStats() {
                if (_DumpStringMemStatsFunc == null) {
                    _DumpStringMemStatsFunc =
                        (_DumpStringMemStats)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fndumpStringMemStats"), typeof(_DumpStringMemStats));
                }
                
                return _DumpStringMemStatsFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct SbmDumpStrings__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _SbmDumpStrings(SbmDumpStrings__Args args);
            private static _SbmDumpStrings _SbmDumpStringsFunc;
            internal static _SbmDumpStrings SbmDumpStrings() {
                if (_SbmDumpStringsFunc == null) {
                    _SbmDumpStringsFunc =
                        (_SbmDumpStrings)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnsbmDumpStrings"), typeof(_SbmDumpStrings));
                }
                
                return _SbmDumpStringsFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct SbmDumpStats__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _SbmDumpStats(SbmDumpStats__Args args);
            private static _SbmDumpStats _SbmDumpStatsFunc;
            internal static _SbmDumpStats SbmDumpStats() {
                if (_SbmDumpStatsFunc == null) {
                    _SbmDumpStatsFunc =
                        (_SbmDumpStats)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnsbmDumpStats"), typeof(_SbmDumpStats));
                }
                
                return _SbmDumpStatsFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct ReloadResource__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string path;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _ReloadResource(ReloadResource__Args args);
            private static _ReloadResource _ReloadResourceFunc;
            internal static _ReloadResource ReloadResource() {
                if (_ReloadResourceFunc == null) {
                    _ReloadResourceFunc =
                        (_ReloadResource)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnreloadResource"), typeof(_ReloadResource));
                }
                
                return _ReloadResourceFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct ResourceDump__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _ResourceDump(ResourceDump__Args args);
            private static _ResourceDump _ResourceDumpFunc;
            internal static _ResourceDump ResourceDump() {
                if (_ResourceDumpFunc == null) {
                    _ResourceDumpFunc =
                        (_ResourceDump)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnresourceDump"), typeof(_ResourceDump));
                }
                
                return _ResourceDumpFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct GetMaxFrameAllocation__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate int _GetMaxFrameAllocation(GetMaxFrameAllocation__Args args);
            private static _GetMaxFrameAllocation _GetMaxFrameAllocationFunc;
            internal static _GetMaxFrameAllocation GetMaxFrameAllocation() {
                if (_GetMaxFrameAllocationFunc == null) {
                    _GetMaxFrameAllocationFunc =
                        (_GetMaxFrameAllocation)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fngetMaxFrameAllocation"), typeof(_GetMaxFrameAllocation));
                }
                
                return _GetMaxFrameAllocationFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct DNetSetLogging__Args
            {
                [MarshalAs(UnmanagedType.I1)]
                internal bool enabled;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _DNetSetLogging(DNetSetLogging__Args args);
            private static _DNetSetLogging _DNetSetLoggingFunc;
            internal static _DNetSetLogging DNetSetLogging() {
                if (_DNetSetLoggingFunc == null) {
                    _DNetSetLoggingFunc =
                        (_DNetSetLogging)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnDNetSetLogging"), typeof(_DNetSetLogging));
                }
                
                return _DNetSetLoggingFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct GetStockColorI__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string stockColorName;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate ColorI.InternalStruct _GetStockColorI(GetStockColorI__Args args);
            private static _GetStockColorI _GetStockColorIFunc;
            internal static _GetStockColorI GetStockColorI() {
                if (_GetStockColorIFunc == null) {
                    _GetStockColorIFunc =
                        (_GetStockColorI)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fngetStockColorI"), typeof(_GetStockColorI));
                }
                
                return _GetStockColorIFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct GetStockColorF__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string stockColorName;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate LinearColorF.InternalStruct _GetStockColorF(GetStockColorF__Args args);
            private static _GetStockColorF _GetStockColorFFunc;
            internal static _GetStockColorF GetStockColorF() {
                if (_GetStockColorFFunc == null) {
                    _GetStockColorFFunc =
                        (_GetStockColorF)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fngetStockColorF"), typeof(_GetStockColorF));
                }
                
                return _GetStockColorFFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct IsStockColor__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string stockColorName;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            [return: MarshalAs(UnmanagedType.I1)]
            internal delegate bool _IsStockColor(IsStockColor__Args args);
            private static _IsStockColor _IsStockColorFunc;
            internal static _IsStockColor IsStockColor() {
                if (_IsStockColorFunc == null) {
                    _IsStockColorFunc =
                        (_IsStockColor)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnisStockColor"), typeof(_IsStockColor));
                }
                
                return _IsStockColorFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct GetStockColorName__Args
            {
                internal int stockColorIndex;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            
            internal delegate IntPtr _GetStockColorName(GetStockColorName__Args args);
            private static _GetStockColorName _GetStockColorNameFunc;
            internal static _GetStockColorName GetStockColorName() {
                if (_GetStockColorNameFunc == null) {
                    _GetStockColorNameFunc =
                        (_GetStockColorName)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fngetStockColorName"), typeof(_GetStockColorName));
                }
                
                return _GetStockColorNameFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct GetStockColorCount__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate int _GetStockColorCount(GetStockColorCount__Args args);
            private static _GetStockColorCount _GetStockColorCountFunc;
            internal static _GetStockColorCount GetStockColorCount() {
                if (_GetStockColorCountFunc == null) {
                    _GetStockColorCountFunc =
                        (_GetStockColorCount)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fngetStockColorCount"), typeof(_GetStockColorCount));
                }
                
                return _GetStockColorCountFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct DbgDisconnect__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _DbgDisconnect(DbgDisconnect__Args args);
            private static _DbgDisconnect _DbgDisconnectFunc;
            internal static _DbgDisconnect DbgDisconnect() {
                if (_DbgDisconnectFunc == null) {
                    _DbgDisconnectFunc =
                        (_DbgDisconnect)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fndbgDisconnect"), typeof(_DbgDisconnect));
                }
                
                return _DbgDisconnectFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct DbgIsConnected__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            [return: MarshalAs(UnmanagedType.I1)]
            internal delegate bool _DbgIsConnected(DbgIsConnected__Args args);
            private static _DbgIsConnected _DbgIsConnectedFunc;
            internal static _DbgIsConnected DbgIsConnected() {
                if (_DbgIsConnectedFunc == null) {
                    _DbgIsConnectedFunc =
                        (_DbgIsConnected)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fndbgIsConnected"), typeof(_DbgIsConnected));
                }
                
                return _DbgIsConnectedFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct DbgSetParameters__Args
            {
                internal int port;
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string password;
                [MarshalAs(UnmanagedType.I1)]
                internal bool waitForClient;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _DbgSetParameters(DbgSetParameters__Args args);
            private static _DbgSetParameters _DbgSetParametersFunc;
            internal static _DbgSetParameters DbgSetParameters() {
                if (_DbgSetParametersFunc == null) {
                    _DbgSetParametersFunc =
                        (_DbgSetParameters)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fndbgSetParameters"), typeof(_DbgSetParameters));
                }
                
                return _DbgSetParametersFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct TelnetSetParameters__Args
            {
                internal int port;
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string consolePass;
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string listenPass;
                [MarshalAs(UnmanagedType.I1)]
                internal bool remoteEcho;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _TelnetSetParameters(TelnetSetParameters__Args args);
            private static _TelnetSetParameters _TelnetSetParametersFunc;
            internal static _TelnetSetParameters TelnetSetParameters() {
                if (_TelnetSetParametersFunc == null) {
                    _TelnetSetParametersFunc =
                        (_TelnetSetParameters)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fntelnetSetParameters"), typeof(_TelnetSetParameters));
                }
                
                return _TelnetSetParametersFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct LoadObject__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string filename;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate IntPtr _LoadObject(LoadObject__Args args);
            private static _LoadObject _LoadObjectFunc;
            internal static _LoadObject LoadObject() {
                if (_LoadObjectFunc == null) {
                    _LoadObjectFunc =
                        (_LoadObject)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnloadObject"), typeof(_LoadObject));
                }
                
                return _LoadObjectFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct SaveObject__Args
            {
                internal IntPtr _object;
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string filename;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            [return: MarshalAs(UnmanagedType.I1)]
            internal delegate bool _SaveObject(SaveObject__Args args);
            private static _SaveObject _SaveObjectFunc;
            internal static _SaveObject SaveObject() {
                if (_SaveObjectFunc == null) {
                    _SaveObjectFunc =
                        (_SaveObject)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnsaveObject"), typeof(_SaveObject));
                }
                
                return _SaveObjectFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct DebugEnumInstances__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string className;
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string functionName;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _DebugEnumInstances(DebugEnumInstances__Args args);
            private static _DebugEnumInstances _DebugEnumInstancesFunc;
            internal static _DebugEnumInstances DebugEnumInstances() {
                if (_DebugEnumInstancesFunc == null) {
                    _DebugEnumInstancesFunc =
                        (_DebugEnumInstances)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fndebugEnumInstances"), typeof(_DebugEnumInstances));
                }
                
                return _DebugEnumInstancesFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct DeleteDataBlocks__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _DeleteDataBlocks(DeleteDataBlocks__Args args);
            private static _DeleteDataBlocks _DeleteDataBlocksFunc;
            internal static _DeleteDataBlocks DeleteDataBlocks() {
                if (_DeleteDataBlocksFunc == null) {
                    _DeleteDataBlocksFunc =
                        (_DeleteDataBlocks)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fndeleteDataBlocks"), typeof(_DeleteDataBlocks));
                }
                
                return _DeleteDataBlocksFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct PreloadClientDataBlocks__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _PreloadClientDataBlocks(PreloadClientDataBlocks__Args args);
            private static _PreloadClientDataBlocks _PreloadClientDataBlocksFunc;
            internal static _PreloadClientDataBlocks PreloadClientDataBlocks() {
                if (_PreloadClientDataBlocksFunc == null) {
                    _PreloadClientDataBlocksFunc =
                        (_PreloadClientDataBlocks)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnpreloadClientDataBlocks"), typeof(_PreloadClientDataBlocks));
                }
                
                return _PreloadClientDataBlocksFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct IsValidObjectName__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string name;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            [return: MarshalAs(UnmanagedType.I1)]
            internal delegate bool _IsValidObjectName(IsValidObjectName__Args args);
            private static _IsValidObjectName _IsValidObjectNameFunc;
            internal static _IsValidObjectName IsValidObjectName() {
                if (_IsValidObjectNameFunc == null) {
                    _IsValidObjectNameFunc =
                        (_IsValidObjectName)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnisValidObjectName"), typeof(_IsValidObjectName));
                }
                
                return _IsValidObjectNameFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct GetUniqueInternalName__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string baseName;
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string setString;
                [MarshalAs(UnmanagedType.I1)]
                internal bool searchChildren;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            
            internal delegate IntPtr _GetUniqueInternalName(GetUniqueInternalName__Args args);
            private static _GetUniqueInternalName _GetUniqueInternalNameFunc;
            internal static _GetUniqueInternalName GetUniqueInternalName() {
                if (_GetUniqueInternalNameFunc == null) {
                    _GetUniqueInternalNameFunc =
                        (_GetUniqueInternalName)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fngetUniqueInternalName"), typeof(_GetUniqueInternalName));
                }
                
                return _GetUniqueInternalNameFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct GetUniqueName__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string baseName;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            
            internal delegate IntPtr _GetUniqueName(GetUniqueName__Args args);
            private static _GetUniqueName _GetUniqueNameFunc;
            internal static _GetUniqueName GetUniqueName() {
                if (_GetUniqueNameFunc == null) {
                    _GetUniqueNameFunc =
                        (_GetUniqueName)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fngetUniqueName"), typeof(_GetUniqueName));
                }
                
                return _GetUniqueNameFunc;
            }


            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate int _Schedule(ref StringVector.InternalStruct args);
            private static _Schedule _ScheduleFunc;
            internal static _Schedule Schedule() {
                if (_ScheduleFunc == null) {
                    _ScheduleFunc =
                        (_Schedule)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnschedule"), typeof(_Schedule));
                }
                
                return _ScheduleFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct GetTimeSinceStart__Args
            {
                internal int scheduleId;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate int _GetTimeSinceStart(GetTimeSinceStart__Args args);
            private static _GetTimeSinceStart _GetTimeSinceStartFunc;
            internal static _GetTimeSinceStart GetTimeSinceStart() {
                if (_GetTimeSinceStartFunc == null) {
                    _GetTimeSinceStartFunc =
                        (_GetTimeSinceStart)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fngetTimeSinceStart"), typeof(_GetTimeSinceStart));
                }
                
                return _GetTimeSinceStartFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct GetScheduleDuration__Args
            {
                internal int scheduleId;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate int _GetScheduleDuration(GetScheduleDuration__Args args);
            private static _GetScheduleDuration _GetScheduleDurationFunc;
            internal static _GetScheduleDuration GetScheduleDuration() {
                if (_GetScheduleDurationFunc == null) {
                    _GetScheduleDurationFunc =
                        (_GetScheduleDuration)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fngetScheduleDuration"), typeof(_GetScheduleDuration));
                }
                
                return _GetScheduleDurationFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct GetEventTimeLeft__Args
            {
                internal int scheduleId;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate int _GetEventTimeLeft(GetEventTimeLeft__Args args);
            private static _GetEventTimeLeft _GetEventTimeLeftFunc;
            internal static _GetEventTimeLeft GetEventTimeLeft() {
                if (_GetEventTimeLeftFunc == null) {
                    _GetEventTimeLeftFunc =
                        (_GetEventTimeLeft)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fngetEventTimeLeft"), typeof(_GetEventTimeLeft));
                }
                
                return _GetEventTimeLeftFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct IsEventPending__Args
            {
                internal int scheduleId;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            [return: MarshalAs(UnmanagedType.I1)]
            internal delegate bool _IsEventPending(IsEventPending__Args args);
            private static _IsEventPending _IsEventPendingFunc;
            internal static _IsEventPending IsEventPending() {
                if (_IsEventPendingFunc == null) {
                    _IsEventPendingFunc =
                        (_IsEventPending)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnisEventPending"), typeof(_IsEventPending));
                }
                
                return _IsEventPendingFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct CancelAll__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string objectId;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _CancelAll(CancelAll__Args args);
            private static _CancelAll _CancelAllFunc;
            internal static _CancelAll CancelAll() {
                if (_CancelAllFunc == null) {
                    _CancelAllFunc =
                        (_CancelAll)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fncancelAll"), typeof(_CancelAll));
                }
                
                return _CancelAllFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct Cancel__Args
            {
                internal int eventId;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _Cancel(Cancel__Args args);
            private static _Cancel _CancelFunc;
            internal static _Cancel Cancel() {
                if (_CancelFunc == null) {
                    _CancelFunc =
                        (_Cancel)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fncancel"), typeof(_Cancel));
                }
                
                return _CancelFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct SpawnObject__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string spawnClass;
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string spawnDataBlock;
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string spawnName;
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string spawnProperties;
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string spawnScript;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate int _SpawnObject(SpawnObject__Args args);
            private static _SpawnObject _SpawnObjectFunc;
            internal static _SpawnObject SpawnObject() {
                if (_SpawnObjectFunc == null) {
                    _SpawnObjectFunc =
                        (_SpawnObject)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnspawnObject"), typeof(_SpawnObject));
                }
                
                return _SpawnObjectFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct IsObject__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string objectName;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            [return: MarshalAs(UnmanagedType.I1)]
            internal delegate bool _IsObject(IsObject__Args args);
            private static _IsObject _IsObjectFunc;
            internal static _IsObject IsObject() {
                if (_IsObjectFunc == null) {
                    _IsObjectFunc =
                        (_IsObject)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnisObject"), typeof(_IsObject));
                }
                
                return _IsObjectFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct NameToID__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string objectName;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate int _NameToID(NameToID__Args args);
            private static _NameToID _NameToIDFunc;
            internal static _NameToID NameToID() {
                if (_NameToIDFunc == null) {
                    _NameToIDFunc =
                        (_NameToID)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnnameToID"), typeof(_NameToID));
                }
                
                return _NameToIDFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct ExpandOldFilename__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string filename;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            
            internal delegate IntPtr _ExpandOldFilename(ExpandOldFilename__Args args);
            private static _ExpandOldFilename _ExpandOldFilenameFunc;
            internal static _ExpandOldFilename ExpandOldFilename() {
                if (_ExpandOldFilenameFunc == null) {
                    _ExpandOldFilenameFunc =
                        (_ExpandOldFilename)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnexpandOldFilename"), typeof(_ExpandOldFilename));
                }
                
                return _ExpandOldFilenameFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct ExpandFilename__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string filename;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            
            internal delegate IntPtr _ExpandFilename(ExpandFilename__Args args);
            private static _ExpandFilename _ExpandFilenameFunc;
            internal static _ExpandFilename ExpandFilename() {
                if (_ExpandFilenameFunc == null) {
                    _ExpandFilenameFunc =
                        (_ExpandFilename)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnexpandFilename"), typeof(_ExpandFilename));
                }
                
                return _ExpandFilenameFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct CreatePath__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string path;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            [return: MarshalAs(UnmanagedType.I1)]
            internal delegate bool _CreatePath(CreatePath__Args args);
            private static _CreatePath _CreatePathFunc;
            internal static _CreatePath CreatePath() {
                if (_CreatePathFunc == null) {
                    _CreatePathFunc =
                        (_CreatePath)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fncreatePath"), typeof(_CreatePath));
                }
                
                return _CreatePathFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct SetCurrentDirectory__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string path;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            [return: MarshalAs(UnmanagedType.I1)]
            internal delegate bool _SetCurrentDirectory(SetCurrentDirectory__Args args);
            private static _SetCurrentDirectory _SetCurrentDirectoryFunc;
            internal static _SetCurrentDirectory SetCurrentDirectory() {
                if (_SetCurrentDirectoryFunc == null) {
                    _SetCurrentDirectoryFunc =
                        (_SetCurrentDirectory)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnsetCurrentDirectory"), typeof(_SetCurrentDirectory));
                }
                
                return _SetCurrentDirectoryFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct GetCurrentDirectory__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            
            internal delegate IntPtr _GetCurrentDirectory(GetCurrentDirectory__Args args);
            private static _GetCurrentDirectory _GetCurrentDirectoryFunc;
            internal static _GetCurrentDirectory GetCurrentDirectory() {
                if (_GetCurrentDirectoryFunc == null) {
                    _GetCurrentDirectoryFunc =
                        (_GetCurrentDirectory)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fngetCurrentDirectory"), typeof(_GetCurrentDirectory));
                }
                
                return _GetCurrentDirectoryFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct PathCopy__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string fromFile;
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string toFile;
                [MarshalAs(UnmanagedType.I1)]
                internal bool noOverwrite;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            [return: MarshalAs(UnmanagedType.I1)]
            internal delegate bool _PathCopy(PathCopy__Args args);
            private static _PathCopy _PathCopyFunc;
            internal static _PathCopy PathCopy() {
                if (_PathCopyFunc == null) {
                    _PathCopyFunc =
                        (_PathCopy)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnpathCopy"), typeof(_PathCopy));
                }
                
                return _PathCopyFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct OpenFile__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string file;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _OpenFile(OpenFile__Args args);
            private static _OpenFile _OpenFileFunc;
            internal static _OpenFile OpenFile() {
                if (_OpenFileFunc == null) {
                    _OpenFileFunc =
                        (_OpenFile)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnopenFile"), typeof(_OpenFile));
                }
                
                return _OpenFileFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct OpenFolder__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string path;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _OpenFolder(OpenFolder__Args args);
            private static _OpenFolder _OpenFolderFunc;
            internal static _OpenFolder OpenFolder() {
                if (_OpenFolderFunc == null) {
                    _OpenFolderFunc =
                        (_OpenFolder)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnopenFolder"), typeof(_OpenFolder));
                }
                
                return _OpenFolderFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct GetMainDotCsDir__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            
            internal delegate IntPtr _GetMainDotCsDir(GetMainDotCsDir__Args args);
            private static _GetMainDotCsDir _GetMainDotCsDirFunc;
            internal static _GetMainDotCsDir GetMainDotCsDir() {
                if (_GetMainDotCsDirFunc == null) {
                    _GetMainDotCsDirFunc =
                        (_GetMainDotCsDir)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fngetMainDotCsDir"), typeof(_GetMainDotCsDir));
                }
                
                return _GetMainDotCsDirFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct GetExecutableName__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            
            internal delegate IntPtr _GetExecutableName(GetExecutableName__Args args);
            private static _GetExecutableName _GetExecutableNameFunc;
            internal static _GetExecutableName GetExecutableName() {
                if (_GetExecutableNameFunc == null) {
                    _GetExecutableNameFunc =
                        (_GetExecutableName)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fngetExecutableName"), typeof(_GetExecutableName));
                }
                
                return _GetExecutableNameFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct PathConcat__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string path;
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string file;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            
            internal delegate IntPtr _PathConcat(PathConcat__Args args);
            private static _PathConcat _PathConcatFunc;
            internal static _PathConcat PathConcat() {
                if (_PathConcatFunc == null) {
                    _PathConcatFunc =
                        (_PathConcat)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnpathConcat"), typeof(_PathConcat));
                }
                
                return _PathConcatFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct MakeRelativePath__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string path;
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string to;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            
            internal delegate IntPtr _MakeRelativePath(MakeRelativePath__Args args);
            private static _MakeRelativePath _MakeRelativePathFunc;
            internal static _MakeRelativePath MakeRelativePath() {
                if (_MakeRelativePathFunc == null) {
                    _MakeRelativePathFunc =
                        (_MakeRelativePath)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnmakeRelativePath"), typeof(_MakeRelativePath));
                }
                
                return _MakeRelativePathFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct MakeFullPath__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string path;
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string cwd;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            
            internal delegate IntPtr _MakeFullPath(MakeFullPath__Args args);
            private static _MakeFullPath _MakeFullPathFunc;
            internal static _MakeFullPath MakeFullPath() {
                if (_MakeFullPathFunc == null) {
                    _MakeFullPathFunc =
                        (_MakeFullPath)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnmakeFullPath"), typeof(_MakeFullPath));
                }
                
                return _MakeFullPathFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct GetWorkingDirectory__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            
            internal delegate IntPtr _GetWorkingDirectory(GetWorkingDirectory__Args args);
            private static _GetWorkingDirectory _GetWorkingDirectoryFunc;
            internal static _GetWorkingDirectory GetWorkingDirectory() {
                if (_GetWorkingDirectoryFunc == null) {
                    _GetWorkingDirectoryFunc =
                        (_GetWorkingDirectory)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fngetWorkingDirectory"), typeof(_GetWorkingDirectory));
                }
                
                return _GetWorkingDirectoryFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct FilePath__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string fileName;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            
            internal delegate IntPtr _FilePath(FilePath__Args args);
            private static _FilePath _FilePathFunc;
            internal static _FilePath FilePath() {
                if (_FilePathFunc == null) {
                    _FilePathFunc =
                        (_FilePath)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnfilePath"), typeof(_FilePath));
                }
                
                return _FilePathFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct FileName__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string fileName;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            
            internal delegate IntPtr _FileName(FileName__Args args);
            private static _FileName _FileNameFunc;
            internal static _FileName FileName() {
                if (_FileNameFunc == null) {
                    _FileNameFunc =
                        (_FileName)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnfileName"), typeof(_FileName));
                }
                
                return _FileNameFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct FileBase__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string fileName;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            
            internal delegate IntPtr _FileBase(FileBase__Args args);
            private static _FileBase _FileBaseFunc;
            internal static _FileBase FileBase() {
                if (_FileBaseFunc == null) {
                    _FileBaseFunc =
                        (_FileBase)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnfileBase"), typeof(_FileBase));
                }
                
                return _FileBaseFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct FileExt__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string fileName;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            
            internal delegate IntPtr _FileExt(FileExt__Args args);
            private static _FileExt _FileExtFunc;
            internal static _FileExt FileExt() {
                if (_FileExtFunc == null) {
                    _FileExtFunc =
                        (_FileExt)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnfileExt"), typeof(_FileExt));
                }
                
                return _FileExtFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct FileDelete__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string path;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            [return: MarshalAs(UnmanagedType.I1)]
            internal delegate bool _FileDelete(FileDelete__Args args);
            private static _FileDelete _FileDeleteFunc;
            internal static _FileDelete FileDelete() {
                if (_FileDeleteFunc == null) {
                    _FileDeleteFunc =
                        (_FileDelete)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnfileDelete"), typeof(_FileDelete));
                }
                
                return _FileDeleteFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct FileCreatedTime__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string fileName;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            
            internal delegate IntPtr _FileCreatedTime(FileCreatedTime__Args args);
            private static _FileCreatedTime _FileCreatedTimeFunc;
            internal static _FileCreatedTime FileCreatedTime() {
                if (_FileCreatedTimeFunc == null) {
                    _FileCreatedTimeFunc =
                        (_FileCreatedTime)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnfileCreatedTime"), typeof(_FileCreatedTime));
                }
                
                return _FileCreatedTimeFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct FileModifiedTime__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string fileName;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            
            internal delegate IntPtr _FileModifiedTime(FileModifiedTime__Args args);
            private static _FileModifiedTime _FileModifiedTimeFunc;
            internal static _FileModifiedTime FileModifiedTime() {
                if (_FileModifiedTimeFunc == null) {
                    _FileModifiedTimeFunc =
                        (_FileModifiedTime)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnfileModifiedTime"), typeof(_FileModifiedTime));
                }
                
                return _FileModifiedTimeFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct FileSize__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string fileName;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate int _FileSize(FileSize__Args args);
            private static _FileSize _FileSizeFunc;
            internal static _FileSize FileSize() {
                if (_FileSizeFunc == null) {
                    _FileSizeFunc =
                        (_FileSize)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnfileSize"), typeof(_FileSize));
                }
                
                return _FileSizeFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct GetDirectoryList__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string path;
                internal int depth;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            
            internal delegate IntPtr _GetDirectoryList(GetDirectoryList__Args args);
            private static _GetDirectoryList _GetDirectoryListFunc;
            internal static _GetDirectoryList GetDirectoryList() {
                if (_GetDirectoryListFunc == null) {
                    _GetDirectoryListFunc =
                        (_GetDirectoryList)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fngetDirectoryList"), typeof(_GetDirectoryList));
                }
                
                return _GetDirectoryListFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct StopFileChangeNotifications__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _StopFileChangeNotifications(StopFileChangeNotifications__Args args);
            private static _StopFileChangeNotifications _StopFileChangeNotificationsFunc;
            internal static _StopFileChangeNotifications StopFileChangeNotifications() {
                if (_StopFileChangeNotificationsFunc == null) {
                    _StopFileChangeNotificationsFunc =
                        (_StopFileChangeNotifications)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnstopFileChangeNotifications"), typeof(_StopFileChangeNotifications));
                }
                
                return _StopFileChangeNotificationsFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct StartFileChangeNotifications__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _StartFileChangeNotifications(StartFileChangeNotifications__Args args);
            private static _StartFileChangeNotifications _StartFileChangeNotificationsFunc;
            internal static _StartFileChangeNotifications StartFileChangeNotifications() {
                if (_StartFileChangeNotificationsFunc == null) {
                    _StartFileChangeNotificationsFunc =
                        (_StartFileChangeNotifications)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnstartFileChangeNotifications"), typeof(_StartFileChangeNotifications));
                }
                
                return _StartFileChangeNotificationsFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct IsWriteableFileName__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string fileName;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            [return: MarshalAs(UnmanagedType.I1)]
            internal delegate bool _IsWriteableFileName(IsWriteableFileName__Args args);
            private static _IsWriteableFileName _IsWriteableFileNameFunc;
            internal static _IsWriteableFileName IsWriteableFileName() {
                if (_IsWriteableFileNameFunc == null) {
                    _IsWriteableFileNameFunc =
                        (_IsWriteableFileName)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnisWriteableFileName"), typeof(_IsWriteableFileName));
                }
                
                return _IsWriteableFileNameFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct IsDirectory__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string directory;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            [return: MarshalAs(UnmanagedType.I1)]
            internal delegate bool _IsDirectory(IsDirectory__Args args);
            private static _IsDirectory _IsDirectoryFunc;
            internal static _IsDirectory IsDirectory() {
                if (_IsDirectoryFunc == null) {
                    _IsDirectoryFunc =
                        (_IsDirectory)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnIsDirectory"), typeof(_IsDirectory));
                }
                
                return _IsDirectoryFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct IsFile__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string fileName;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            [return: MarshalAs(UnmanagedType.I1)]
            internal delegate bool _IsFile(IsFile__Args args);
            private static _IsFile _IsFileFunc;
            internal static _IsFile IsFile() {
                if (_IsFileFunc == null) {
                    _IsFileFunc =
                        (_IsFile)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnisFile"), typeof(_IsFile));
                }
                
                return _IsFileFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct GetFileCRC__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string fileName;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate int _GetFileCRC(GetFileCRC__Args args);
            private static _GetFileCRC _GetFileCRCFunc;
            internal static _GetFileCRC GetFileCRC() {
                if (_GetFileCRCFunc == null) {
                    _GetFileCRCFunc =
                        (_GetFileCRC)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fngetFileCRC"), typeof(_GetFileCRC));
                }
                
                return _GetFileCRCFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct GetFileCountMultiExpr__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string pattern;
                [MarshalAs(UnmanagedType.I1)]
                internal bool recurse;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate int _GetFileCountMultiExpr(GetFileCountMultiExpr__Args args);
            private static _GetFileCountMultiExpr _GetFileCountMultiExprFunc;
            internal static _GetFileCountMultiExpr GetFileCountMultiExpr() {
                if (_GetFileCountMultiExprFunc == null) {
                    _GetFileCountMultiExprFunc =
                        (_GetFileCountMultiExpr)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fngetFileCountMultiExpr"), typeof(_GetFileCountMultiExpr));
                }
                
                return _GetFileCountMultiExprFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct FindNextFileMultiExpr__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string pattern;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            
            internal delegate IntPtr _FindNextFileMultiExpr(FindNextFileMultiExpr__Args args);
            private static _FindNextFileMultiExpr _FindNextFileMultiExprFunc;
            internal static _FindNextFileMultiExpr FindNextFileMultiExpr() {
                if (_FindNextFileMultiExprFunc == null) {
                    _FindNextFileMultiExprFunc =
                        (_FindNextFileMultiExpr)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnfindNextFileMultiExpr"), typeof(_FindNextFileMultiExpr));
                }
                
                return _FindNextFileMultiExprFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct FindFirstFileMultiExpr__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string pattern;
                [MarshalAs(UnmanagedType.I1)]
                internal bool recurse;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            
            internal delegate IntPtr _FindFirstFileMultiExpr(FindFirstFileMultiExpr__Args args);
            private static _FindFirstFileMultiExpr _FindFirstFileMultiExprFunc;
            internal static _FindFirstFileMultiExpr FindFirstFileMultiExpr() {
                if (_FindFirstFileMultiExprFunc == null) {
                    _FindFirstFileMultiExprFunc =
                        (_FindFirstFileMultiExpr)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnfindFirstFileMultiExpr"), typeof(_FindFirstFileMultiExpr));
                }
                
                return _FindFirstFileMultiExprFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct GetFileCount__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string pattern;
                [MarshalAs(UnmanagedType.I1)]
                internal bool recurse;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate int _GetFileCount(GetFileCount__Args args);
            private static _GetFileCount _GetFileCountFunc;
            internal static _GetFileCount GetFileCount() {
                if (_GetFileCountFunc == null) {
                    _GetFileCountFunc =
                        (_GetFileCount)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fngetFileCount"), typeof(_GetFileCount));
                }
                
                return _GetFileCountFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct FindNextFile__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string pattern;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            
            internal delegate IntPtr _FindNextFile(FindNextFile__Args args);
            private static _FindNextFile _FindNextFileFunc;
            internal static _FindNextFile FindNextFile() {
                if (_FindNextFileFunc == null) {
                    _FindNextFileFunc =
                        (_FindNextFile)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnfindNextFile"), typeof(_FindNextFile));
                }
                
                return _FindNextFileFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct FindFirstFile__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string pattern;
                [MarshalAs(UnmanagedType.I1)]
                internal bool recurse;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            
            internal delegate IntPtr _FindFirstFile(FindFirstFile__Args args);
            private static _FindFirstFile _FindFirstFileFunc;
            internal static _FindFirstFile FindFirstFile() {
                if (_FindFirstFileFunc == null) {
                    _FindFirstFileFunc =
                        (_FindFirstFile)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnfindFirstFile"), typeof(_FindFirstFile));
                }
                
                return _FindFirstFileFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct ExportEngineAPIToXML__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate IntPtr _ExportEngineAPIToXML(ExportEngineAPIToXML__Args args);
            private static _ExportEngineAPIToXML _ExportEngineAPIToXMLFunc;
            internal static _ExportEngineAPIToXML ExportEngineAPIToXML() {
                if (_ExportEngineAPIToXMLFunc == null) {
                    _ExportEngineAPIToXMLFunc =
                        (_ExportEngineAPIToXML)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnexportEngineAPIToXML"), typeof(_ExportEngineAPIToXML));
                }
                
                return _ExportEngineAPIToXMLFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct DebugDumpAllObjects__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _DebugDumpAllObjects(DebugDumpAllObjects__Args args);
            private static _DebugDumpAllObjects _DebugDumpAllObjectsFunc;
            internal static _DebugDumpAllObjects DebugDumpAllObjects() {
                if (_DebugDumpAllObjectsFunc == null) {
                    _DebugDumpAllObjectsFunc =
                        (_DebugDumpAllObjects)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fndebugDumpAllObjects"), typeof(_DebugDumpAllObjects));
                }
                
                return _DebugDumpAllObjectsFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct DumpEngineDocs__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string outputFile;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            [return: MarshalAs(UnmanagedType.I1)]
            internal delegate bool _DumpEngineDocs(DumpEngineDocs__Args args);
            private static _DumpEngineDocs _DumpEngineDocsFunc;
            internal static _DumpEngineDocs DumpEngineDocs() {
                if (_DumpEngineDocsFunc == null) {
                    _DumpEngineDocsFunc =
                        (_DumpEngineDocs)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fndumpEngineDocs"), typeof(_DumpEngineDocs));
                }
                
                return _DumpEngineDocsFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct LinkNamespaces__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string childNSName;
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string parentNSName;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            [return: MarshalAs(UnmanagedType.I1)]
            internal delegate bool _LinkNamespaces(LinkNamespaces__Args args);
            private static _LinkNamespaces _LinkNamespacesFunc;
            internal static _LinkNamespaces LinkNamespaces() {
                if (_LinkNamespacesFunc == null) {
                    _LinkNamespacesFunc =
                        (_LinkNamespaces)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnlinkNamespaces"), typeof(_LinkNamespaces));
                }
                
                return _LinkNamespacesFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct sizeOf__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string objectOrClass;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate int _sizeOf(sizeOf__Args args);
            private static _sizeOf _sizeOfFunc;
            internal static _sizeOf sizeOf() {
                if (_sizeOfFunc == null) {
                    _sizeOfFunc =
                        (_sizeOf)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnsizeof"), typeof(_sizeOf));
                }
                
                return _sizeOfFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct DumpNetStats__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _DumpNetStats(DumpNetStats__Args args);
            private static _DumpNetStats _DumpNetStatsFunc;
            internal static _DumpNetStats DumpNetStats() {
                if (_DumpNetStatsFunc == null) {
                    _DumpNetStatsFunc =
                        (_DumpNetStats)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fndumpNetStats"), typeof(_DumpNetStats));
                }
                
                return _DumpNetStatsFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct EnumerateConsoleClassesByCategory__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string category;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            
            internal delegate IntPtr _EnumerateConsoleClassesByCategory(EnumerateConsoleClassesByCategory__Args args);
            private static _EnumerateConsoleClassesByCategory _EnumerateConsoleClassesByCategoryFunc;
            internal static _EnumerateConsoleClassesByCategory EnumerateConsoleClassesByCategory() {
                if (_EnumerateConsoleClassesByCategoryFunc == null) {
                    _EnumerateConsoleClassesByCategoryFunc =
                        (_EnumerateConsoleClassesByCategory)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnenumerateConsoleClassesByCategory"), typeof(_EnumerateConsoleClassesByCategory));
                }
                
                return _EnumerateConsoleClassesByCategoryFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct EnumerateConsoleClasses__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string className;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            
            internal delegate IntPtr _EnumerateConsoleClasses(EnumerateConsoleClasses__Args args);
            private static _EnumerateConsoleClasses _EnumerateConsoleClassesFunc;
            internal static _EnumerateConsoleClasses EnumerateConsoleClasses() {
                if (_EnumerateConsoleClassesFunc == null) {
                    _EnumerateConsoleClassesFunc =
                        (_EnumerateConsoleClasses)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnenumerateConsoleClasses"), typeof(_EnumerateConsoleClasses));
                }
                
                return _EnumerateConsoleClassesFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct GetCategoryOfClass__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string className;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            
            internal delegate IntPtr _GetCategoryOfClass(GetCategoryOfClass__Args args);
            private static _GetCategoryOfClass _GetCategoryOfClassFunc;
            internal static _GetCategoryOfClass GetCategoryOfClass() {
                if (_GetCategoryOfClassFunc == null) {
                    _GetCategoryOfClassFunc =
                        (_GetCategoryOfClass)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fngetCategoryOfClass"), typeof(_GetCategoryOfClass));
                }
                
                return _GetCategoryOfClassFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct GetDescriptionOfClass__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string className;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            
            internal delegate IntPtr _GetDescriptionOfClass(GetDescriptionOfClass__Args args);
            private static _GetDescriptionOfClass _GetDescriptionOfClassFunc;
            internal static _GetDescriptionOfClass GetDescriptionOfClass() {
                if (_GetDescriptionOfClassFunc == null) {
                    _GetDescriptionOfClassFunc =
                        (_GetDescriptionOfClass)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fngetDescriptionOfClass"), typeof(_GetDescriptionOfClass));
                }
                
                return _GetDescriptionOfClassFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct IsMemberOfClass__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string className;
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string superClassName;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            [return: MarshalAs(UnmanagedType.I1)]
            internal delegate bool _IsMemberOfClass(IsMemberOfClass__Args args);
            private static _IsMemberOfClass _IsMemberOfClassFunc;
            internal static _IsMemberOfClass IsMemberOfClass() {
                if (_IsMemberOfClassFunc == null) {
                    _IsMemberOfClassFunc =
                        (_IsMemberOfClass)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnisMemberOfClass"), typeof(_IsMemberOfClass));
                }
                
                return _IsMemberOfClassFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct IsClass__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string identifier;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            [return: MarshalAs(UnmanagedType.I1)]
            internal delegate bool _IsClass(IsClass__Args args);
            private static _IsClass _IsClassFunc;
            internal static _IsClass IsClass() {
                if (_IsClassFunc == null) {
                    _IsClassFunc =
                        (_IsClass)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnisClass"), typeof(_IsClass));
                }
                
                return _IsClassFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct GetPackageList__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            
            internal delegate IntPtr _GetPackageList(GetPackageList__Args args);
            private static _GetPackageList _GetPackageListFunc;
            internal static _GetPackageList GetPackageList() {
                if (_GetPackageListFunc == null) {
                    _GetPackageListFunc =
                        (_GetPackageList)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fngetPackageList"), typeof(_GetPackageList));
                }
                
                return _GetPackageListFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct DeactivatePackage__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string packageName;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _DeactivatePackage(DeactivatePackage__Args args);
            private static _DeactivatePackage _DeactivatePackageFunc;
            internal static _DeactivatePackage DeactivatePackage() {
                if (_DeactivatePackageFunc == null) {
                    _DeactivatePackageFunc =
                        (_DeactivatePackage)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fndeactivatePackage"), typeof(_DeactivatePackage));
                }
                
                return _DeactivatePackageFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct ActivatePackage__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string packageName;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _ActivatePackage(ActivatePackage__Args args);
            private static _ActivatePackage _ActivatePackageFunc;
            internal static _ActivatePackage ActivatePackage() {
                if (_ActivatePackageFunc == null) {
                    _ActivatePackageFunc =
                        (_ActivatePackage)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnactivatePackage"), typeof(_ActivatePackage));
                }
                
                return _ActivatePackageFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct IsPackage__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string identifier;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            [return: MarshalAs(UnmanagedType.I1)]
            internal delegate bool _IsPackage(IsPackage__Args args);
            private static _IsPackage _IsPackageFunc;
            internal static _IsPackage IsPackage() {
                if (_IsPackageFunc == null) {
                    _IsPackageFunc =
                        (_IsPackage)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnisPackage"), typeof(_IsPackage));
                }
                
                return _IsPackageFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct Backtrace__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _Backtrace(Backtrace__Args args);
            private static _Backtrace _BacktraceFunc;
            internal static _Backtrace Backtrace() {
                if (_BacktraceFunc == null) {
                    _BacktraceFunc =
                        (_Backtrace)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnbacktrace"), typeof(_Backtrace));
                }
                
                return _BacktraceFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct GetMaxDynamicVerts__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate int _GetMaxDynamicVerts(GetMaxDynamicVerts__Args args);
            private static _GetMaxDynamicVerts _GetMaxDynamicVertsFunc;
            internal static _GetMaxDynamicVerts GetMaxDynamicVerts() {
                if (_GetMaxDynamicVertsFunc == null) {
                    _GetMaxDynamicVertsFunc =
                        (_GetMaxDynamicVerts)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fngetMaxDynamicVerts"), typeof(_GetMaxDynamicVerts));
                }
                
                return _GetMaxDynamicVertsFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct IsToolBuild__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            [return: MarshalAs(UnmanagedType.I1)]
            internal delegate bool _IsToolBuild(IsToolBuild__Args args);
            private static _IsToolBuild _IsToolBuildFunc;
            internal static _IsToolBuild IsToolBuild() {
                if (_IsToolBuildFunc == null) {
                    _IsToolBuildFunc =
                        (_IsToolBuild)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnisToolBuild"), typeof(_IsToolBuild));
                }
                
                return _IsToolBuildFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct IsDebugBuild__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            [return: MarshalAs(UnmanagedType.I1)]
            internal delegate bool _IsDebugBuild(IsDebugBuild__Args args);
            private static _IsDebugBuild _IsDebugBuildFunc;
            internal static _IsDebugBuild IsDebugBuild() {
                if (_IsDebugBuildFunc == null) {
                    _IsDebugBuildFunc =
                        (_IsDebugBuild)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnisDebugBuild"), typeof(_IsDebugBuild));
                }
                
                return _IsDebugBuildFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct IsShippingBuild__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            [return: MarshalAs(UnmanagedType.I1)]
            internal delegate bool _IsShippingBuild(IsShippingBuild__Args args);
            private static _IsShippingBuild _IsShippingBuildFunc;
            internal static _IsShippingBuild IsShippingBuild() {
                if (_IsShippingBuildFunc == null) {
                    _IsShippingBuildFunc =
                        (_IsShippingBuild)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnisShippingBuild"), typeof(_IsShippingBuild));
                }
                
                return _IsShippingBuildFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct Debug__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _Debug(Debug__Args args);
            private static _Debug _DebugFunc;
            internal static _Debug Debug() {
                if (_DebugFunc == null) {
                    _DebugFunc =
                        (_Debug)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fndebug"), typeof(_Debug));
                }
                
                return _DebugFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct Trace__Args
            {
                [MarshalAs(UnmanagedType.I1)]
                internal bool enable;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _Trace(Trace__Args args);
            private static _Trace _TraceFunc;
            internal static _Trace Trace() {
                if (_TraceFunc == null) {
                    _TraceFunc =
                        (_Trace)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fntrace"), typeof(_Trace));
                }
                
                return _TraceFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct DeleteVariables__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string pattern;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _DeleteVariables(DeleteVariables__Args args);
            private static _DeleteVariables _DeleteVariablesFunc;
            internal static _DeleteVariables DeleteVariables() {
                if (_DeleteVariablesFunc == null) {
                    _DeleteVariablesFunc =
                        (_DeleteVariables)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fndeleteVariables"), typeof(_DeleteVariables));
                }
                
                return _DeleteVariablesFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct Export__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string pattern;
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string filename;
                [MarshalAs(UnmanagedType.I1)]
                internal bool append;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _Export(Export__Args args);
            private static _Export _ExportFunc;
            internal static _Export Export() {
                if (_ExportFunc == null) {
                    _ExportFunc =
                        (_Export)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnexport"), typeof(_Export));
                }
                
                return _ExportFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct ExecPrefs__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string relativeFileName;
                [MarshalAs(UnmanagedType.I1)]
                internal bool noCalls;
                [MarshalAs(UnmanagedType.I1)]
                internal bool journalScript;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            [return: MarshalAs(UnmanagedType.I1)]
            internal delegate bool _ExecPrefs(ExecPrefs__Args args);
            private static _ExecPrefs _ExecPrefsFunc;
            internal static _ExecPrefs ExecPrefs() {
                if (_ExecPrefsFunc == null) {
                    _ExecPrefsFunc =
                        (_ExecPrefs)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnexecPrefs"), typeof(_ExecPrefs));
                }
                
                return _ExecPrefsFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct GetPrefsPath__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string relativeFileName;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            
            internal delegate IntPtr _GetPrefsPath(GetPrefsPath__Args args);
            private static _GetPrefsPath _GetPrefsPathFunc;
            internal static _GetPrefsPath GetPrefsPath() {
                if (_GetPrefsPathFunc == null) {
                    _GetPrefsPathFunc =
                        (_GetPrefsPath)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fngetPrefsPath"), typeof(_GetPrefsPath));
                }
                
                return _GetPrefsPathFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct PopInstantGroup__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _PopInstantGroup(PopInstantGroup__Args args);
            private static _PopInstantGroup _PopInstantGroupFunc;
            internal static _PopInstantGroup PopInstantGroup() {
                if (_PopInstantGroupFunc == null) {
                    _PopInstantGroupFunc =
                        (_PopInstantGroup)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnpopInstantGroup"), typeof(_PopInstantGroup));
                }
                
                return _PopInstantGroupFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct PushInstantGroup__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string group;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _PushInstantGroup(PushInstantGroup__Args args);
            private static _PushInstantGroup _PushInstantGroupFunc;
            internal static _PushInstantGroup PushInstantGroup() {
                if (_PushInstantGroupFunc == null) {
                    _PushInstantGroupFunc =
                        (_PushInstantGroup)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnpushInstantGroup"), typeof(_PushInstantGroup));
                }
                
                return _PushInstantGroupFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct GetModNameFromPath__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string path;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            
            internal delegate IntPtr _GetModNameFromPath(GetModNameFromPath__Args args);
            private static _GetModNameFromPath _GetModNameFromPathFunc;
            internal static _GetModNameFromPath GetModNameFromPath() {
                if (_GetModNameFromPathFunc == null) {
                    _GetModNameFromPathFunc =
                        (_GetModNameFromPath)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fngetModNameFromPath"), typeof(_GetModNameFromPath));
                }
                
                return _GetModNameFromPathFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct IsCurrentScriptToolScript__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            [return: MarshalAs(UnmanagedType.I1)]
            internal delegate bool _IsCurrentScriptToolScript(IsCurrentScriptToolScript__Args args);
            private static _IsCurrentScriptToolScript _IsCurrentScriptToolScriptFunc;
            internal static _IsCurrentScriptToolScript IsCurrentScriptToolScript() {
                if (_IsCurrentScriptToolScriptFunc == null) {
                    _IsCurrentScriptToolScriptFunc =
                        (_IsCurrentScriptToolScript)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnisCurrentScriptToolScript"), typeof(_IsCurrentScriptToolScript));
                }
                
                return _IsCurrentScriptToolScriptFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct IsDefined__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string varName;
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string varValue;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            [return: MarshalAs(UnmanagedType.I1)]
            internal delegate bool _IsDefined(IsDefined__Args args);
            private static _IsDefined _IsDefinedFunc;
            internal static _IsDefined IsDefined() {
                if (_IsDefinedFunc == null) {
                    _IsDefinedFunc =
                        (_IsDefined)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnisDefined"), typeof(_IsDefined));
                }
                
                return _IsDefinedFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct GetMethodPackage__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string nameSpace;
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string method;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            
            internal delegate IntPtr _GetMethodPackage(GetMethodPackage__Args args);
            private static _GetMethodPackage _GetMethodPackageFunc;
            internal static _GetMethodPackage GetMethodPackage() {
                if (_GetMethodPackageFunc == null) {
                    _GetMethodPackageFunc =
                        (_GetMethodPackage)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fngetMethodPackage"), typeof(_GetMethodPackage));
                }
                
                return _GetMethodPackageFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct IsMethod__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string nameSpace;
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string method;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            [return: MarshalAs(UnmanagedType.I1)]
            internal delegate bool _IsMethod(IsMethod__Args args);
            private static _IsMethod _IsMethodFunc;
            internal static _IsMethod IsMethod() {
                if (_IsMethodFunc == null) {
                    _IsMethodFunc =
                        (_IsMethod)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnisMethod"), typeof(_IsMethod));
                }
                
                return _IsMethodFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct GetFunctionPackage__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string funcName;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            
            internal delegate IntPtr _GetFunctionPackage(GetFunctionPackage__Args args);
            private static _GetFunctionPackage _GetFunctionPackageFunc;
            internal static _GetFunctionPackage GetFunctionPackage() {
                if (_GetFunctionPackageFunc == null) {
                    _GetFunctionPackageFunc =
                        (_GetFunctionPackage)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fngetFunctionPackage"), typeof(_GetFunctionPackage));
                }
                
                return _GetFunctionPackageFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct IsFunction__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string funcName;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            [return: MarshalAs(UnmanagedType.I1)]
            internal delegate bool _IsFunction(IsFunction__Args args);
            private static _IsFunction _IsFunctionFunc;
            internal static _IsFunction IsFunction() {
                if (_IsFunctionFunc == null) {
                    _IsFunctionFunc =
                        (_IsFunction)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnisFunction"), typeof(_IsFunction));
                }
                
                return _IsFunctionFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct SetVariable__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string varName;
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string value;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _SetVariable(SetVariable__Args args);
            private static _SetVariable _SetVariableFunc;
            internal static _SetVariable SetVariable() {
                if (_SetVariableFunc == null) {
                    _SetVariableFunc =
                        (_SetVariable)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnsetVariable"), typeof(_SetVariable));
                }
                
                return _SetVariableFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct GetVariable__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string varName;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            
            internal delegate IntPtr _GetVariable(GetVariable__Args args);
            private static _GetVariable _GetVariableFunc;
            internal static _GetVariable GetVariable() {
                if (_GetVariableFunc == null) {
                    _GetVariableFunc =
                        (_GetVariable)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fngetVariable"), typeof(_GetVariable));
                }
                
                return _GetVariableFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct Eval__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string consoleString;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            
            internal delegate IntPtr _Eval(Eval__Args args);
            private static _Eval _EvalFunc;
            internal static _Eval Eval() {
                if (_EvalFunc == null) {
                    _EvalFunc =
                        (_Eval)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fneval"), typeof(_Eval));
                }
                
                return _EvalFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct Exec__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string fileName;
                [MarshalAs(UnmanagedType.I1)]
                internal bool noCalls;
                [MarshalAs(UnmanagedType.I1)]
                internal bool journalScript;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            [return: MarshalAs(UnmanagedType.I1)]
            internal delegate bool _Exec(Exec__Args args);
            private static _Exec _ExecFunc;
            internal static _Exec Exec() {
                if (_ExecFunc == null) {
                    _ExecFunc =
                        (_Exec)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnexec"), typeof(_Exec));
                }
                
                return _ExecFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct Compile__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string fileName;
                [MarshalAs(UnmanagedType.I1)]
                internal bool overrideNoDSO;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            [return: MarshalAs(UnmanagedType.I1)]
            internal delegate bool _Compile(Compile__Args args);
            private static _Compile _CompileFunc;
            internal static _Compile Compile() {
                if (_CompileFunc == null) {
                    _CompileFunc =
                        (_Compile)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fncompile"), typeof(_Compile));
                }
                
                return _CompileFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct GetDSOPath__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string scriptFileName;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            
            internal delegate IntPtr _GetDSOPath(GetDSOPath__Args args);
            private static _GetDSOPath _GetDSOPathFunc;
            internal static _GetDSOPath GetDSOPath() {
                if (_GetDSOPathFunc == null) {
                    _GetDSOPathFunc =
                        (_GetDSOPath)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fngetDSOPath"), typeof(_GetDSOPath));
                }
                
                return _GetDSOPathFunc;
            }


            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            
            internal delegate IntPtr _Call(ref StringVector.InternalStruct args);
            private static _Call _CallFunc;
            internal static _Call Call() {
                if (_CallFunc == null) {
                    _CallFunc =
                        (_Call)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fncall"), typeof(_Call));
                }
                
                return _CallFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct GenerateUUID__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate UUID.InternalStruct _GenerateUUID(GenerateUUID__Args args);
            private static _GenerateUUID _GenerateUUIDFunc;
            internal static _GenerateUUID GenerateUUID() {
                if (_GenerateUUIDFunc == null) {
                    _GenerateUUIDFunc =
                        (_GenerateUUID)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fngenerateUUID"), typeof(_GenerateUUID));
                }
                
                return _GenerateUUIDFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct CountBits__Args
            {
                internal int v;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate int _CountBits(CountBits__Args args);
            private static _CountBits _CountBitsFunc;
            internal static _CountBits CountBits() {
                if (_CountBitsFunc == null) {
                    _CountBitsFunc =
                        (_CountBits)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fncountBits"), typeof(_CountBits));
                }
                
                return _CountBitsFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct GetWebDeployment__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            [return: MarshalAs(UnmanagedType.I1)]
            internal delegate bool _GetWebDeployment(GetWebDeployment__Args args);
            private static _GetWebDeployment _GetWebDeploymentFunc;
            internal static _GetWebDeployment GetWebDeployment() {
                if (_GetWebDeploymentFunc == null) {
                    _GetWebDeploymentFunc =
                        (_GetWebDeployment)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fngetWebDeployment"), typeof(_GetWebDeployment));
                }
                
                return _GetWebDeploymentFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct CloseSplashWindow__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _CloseSplashWindow(CloseSplashWindow__Args args);
            private static _CloseSplashWindow _CloseSplashWindowFunc;
            internal static _CloseSplashWindow CloseSplashWindow() {
                if (_CloseSplashWindowFunc == null) {
                    _CloseSplashWindowFunc =
                        (_CloseSplashWindow)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fncloseSplashWindow"), typeof(_CloseSplashWindow));
                }
                
                return _CloseSplashWindowFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct DisplaySplashWindow__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string path;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            [return: MarshalAs(UnmanagedType.I1)]
            internal delegate bool _DisplaySplashWindow(DisplaySplashWindow__Args args);
            private static _DisplaySplashWindow _DisplaySplashWindowFunc;
            internal static _DisplaySplashWindow DisplaySplashWindow() {
                if (_DisplaySplashWindowFunc == null) {
                    _DisplaySplashWindowFunc =
                        (_DisplaySplashWindow)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fndisplaySplashWindow"), typeof(_DisplaySplashWindow));
                }
                
                return _DisplaySplashWindowFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct GotoWebPage__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string address;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _GotoWebPage(GotoWebPage__Args args);
            private static _GotoWebPage _GotoWebPageFunc;
            internal static _GotoWebPage GotoWebPage() {
                if (_GotoWebPageFunc == null) {
                    _GotoWebPageFunc =
                        (_GotoWebPage)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fngotoWebPage"), typeof(_GotoWebPage));
                }
                
                return _GotoWebPageFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct QuitWithStatus__Args
            {
                internal int status;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _QuitWithStatus(QuitWithStatus__Args args);
            private static _QuitWithStatus _QuitWithStatusFunc;
            internal static _QuitWithStatus QuitWithStatus() {
                if (_QuitWithStatusFunc == null) {
                    _QuitWithStatusFunc =
                        (_QuitWithStatus)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnquitWithStatus"), typeof(_QuitWithStatus));
                }
                
                return _QuitWithStatusFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct QuitWithErrorMessage__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string message;
                internal int status;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _QuitWithErrorMessage(QuitWithErrorMessage__Args args);
            private static _QuitWithErrorMessage _QuitWithErrorMessageFunc;
            internal static _QuitWithErrorMessage QuitWithErrorMessage() {
                if (_QuitWithErrorMessageFunc == null) {
                    _QuitWithErrorMessageFunc =
                        (_QuitWithErrorMessage)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnquitWithErrorMessage"), typeof(_QuitWithErrorMessage));
                }
                
                return _QuitWithErrorMessageFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct RealQuit__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _RealQuit(RealQuit__Args args);
            private static _RealQuit _RealQuitFunc;
            internal static _RealQuit RealQuit() {
                if (_RealQuitFunc == null) {
                    _RealQuitFunc =
                        (_RealQuit)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnrealQuit"), typeof(_RealQuit));
                }
                
                return _RealQuitFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct Quit__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _Quit(Quit__Args args);
            private static _Quit _QuitFunc;
            internal static _Quit Quit() {
                if (_QuitFunc == null) {
                    _QuitFunc =
                        (_Quit)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnquit"), typeof(_Quit));
                }
                
                return _QuitFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct SetLogMode__Args
            {
                internal int mode;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _SetLogMode(SetLogMode__Args args);
            private static _SetLogMode _SetLogModeFunc;
            internal static _SetLogMode SetLogMode() {
                if (_SetLogModeFunc == null) {
                    _SetLogModeFunc =
                        (_SetLogMode)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnsetLogMode"), typeof(_SetLogMode));
                }
                
                return _SetLogModeFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct CollapseEscape__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string text;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            
            internal delegate IntPtr _CollapseEscape(CollapseEscape__Args args);
            private static _CollapseEscape _CollapseEscapeFunc;
            internal static _CollapseEscape CollapseEscape() {
                if (_CollapseEscapeFunc == null) {
                    _CollapseEscapeFunc =
                        (_CollapseEscape)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fncollapseEscape"), typeof(_CollapseEscape));
                }
                
                return _CollapseEscapeFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct ExpandEscape__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string text;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            
            internal delegate IntPtr _ExpandEscape(ExpandEscape__Args args);
            private static _ExpandEscape _ExpandEscapeFunc;
            internal static _ExpandEscape ExpandEscape() {
                if (_ExpandEscapeFunc == null) {
                    _ExpandEscapeFunc =
                        (_ExpandEscape)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnexpandEscape"), typeof(_ExpandEscape));
                }
                
                return _ExpandEscapeFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct Debugv__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string variableName;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _Debugv(Debugv__Args args);
            private static _Debugv _DebugvFunc;
            internal static _Debugv Debugv() {
                if (_DebugvFunc == null) {
                    _DebugvFunc =
                        (_Debugv)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fndebugv"), typeof(_Debugv));
                }
                
                return _DebugvFunc;
            }


            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _Error(ref StringVector.InternalStruct args);
            private static _Error _ErrorFunc;
            internal static _Error Error() {
                if (_ErrorFunc == null) {
                    _ErrorFunc =
                        (_Error)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnerror"), typeof(_Error));
                }
                
                return _ErrorFunc;
            }


            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _Warn(ref StringVector.InternalStruct args);
            private static _Warn _WarnFunc;
            internal static _Warn Warn() {
                if (_WarnFunc == null) {
                    _WarnFunc =
                        (_Warn)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnwarn"), typeof(_Warn));
                }
                
                return _WarnFunc;
            }


            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _Echo(ref StringVector.InternalStruct args);
            private static _Echo _EchoFunc;
            internal static _Echo Echo() {
                if (_EchoFunc == null) {
                    _EchoFunc =
                        (_Echo)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnecho"), typeof(_Echo));
                }
                
                return _EchoFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct GetTag__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string textTagString;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            
            internal delegate IntPtr _GetTag(GetTag__Args args);
            private static _GetTag _GetTagFunc;
            internal static _GetTag GetTag() {
                if (_GetTagFunc == null) {
                    _GetTagFunc =
                        (_GetTag)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fngetTag"), typeof(_GetTag));
                }
                
                return _GetTagFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct Detag__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string str;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            
            internal delegate IntPtr _Detag(Detag__Args args);
            private static _Detag _DetagFunc;
            internal static _Detag Detag() {
                if (_DetagFunc == null) {
                    _DetagFunc =
                        (_Detag)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fndetag"), typeof(_Detag));
                }
                
                return _DetagFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct GetTokenCount__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string text;
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string delimiters;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate int _GetTokenCount(GetTokenCount__Args args);
            private static _GetTokenCount _GetTokenCountFunc;
            internal static _GetTokenCount GetTokenCount() {
                if (_GetTokenCountFunc == null) {
                    _GetTokenCountFunc =
                        (_GetTokenCount)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fngetTokenCount"), typeof(_GetTokenCount));
                }
                
                return _GetTokenCountFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct RemoveToken__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string text;
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string delimiters;
                internal int index;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            
            internal delegate IntPtr _RemoveToken(RemoveToken__Args args);
            private static _RemoveToken _RemoveTokenFunc;
            internal static _RemoveToken RemoveToken() {
                if (_RemoveTokenFunc == null) {
                    _RemoveTokenFunc =
                        (_RemoveToken)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnremoveToken"), typeof(_RemoveToken));
                }
                
                return _RemoveTokenFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct SetToken__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string text;
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string delimiters;
                internal int index;
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string replacement;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            
            internal delegate IntPtr _SetToken(SetToken__Args args);
            private static _SetToken _SetTokenFunc;
            internal static _SetToken SetToken() {
                if (_SetTokenFunc == null) {
                    _SetTokenFunc =
                        (_SetToken)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnsetToken"), typeof(_SetToken));
                }
                
                return _SetTokenFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct GetTokens__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string text;
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string delimiters;
                internal int startIndex;
                internal int endIndex;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            
            internal delegate IntPtr _GetTokens(GetTokens__Args args);
            private static _GetTokens _GetTokensFunc;
            internal static _GetTokens GetTokens() {
                if (_GetTokensFunc == null) {
                    _GetTokensFunc =
                        (_GetTokens)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fngetTokens"), typeof(_GetTokens));
                }
                
                return _GetTokensFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct GetToken__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string text;
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string delimiters;
                internal int index;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            
            internal delegate IntPtr _GetToken(GetToken__Args args);
            private static _GetToken _GetTokenFunc;
            internal static _GetToken GetToken() {
                if (_GetTokenFunc == null) {
                    _GetTokenFunc =
                        (_GetToken)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fngetToken"), typeof(_GetToken));
                }
                
                return _GetTokenFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct NextToken__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string str1;
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string token;
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string delim;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            
            internal delegate IntPtr _NextToken(NextToken__Args args);
            private static _NextToken _NextTokenFunc;
            internal static _NextToken NextToken() {
                if (_NextTokenFunc == null) {
                    _NextTokenFunc =
                        (_NextToken)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnnextToken"), typeof(_NextToken));
                }
                
                return _NextTokenFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct RestWords__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string text;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            
            internal delegate IntPtr _RestWords(RestWords__Args args);
            private static _RestWords _RestWordsFunc;
            internal static _RestWords RestWords() {
                if (_RestWordsFunc == null) {
                    _RestWordsFunc =
                        (_RestWords)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnrestWords"), typeof(_RestWords));
                }
                
                return _RestWordsFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct FirstWord__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string text;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            
            internal delegate IntPtr _FirstWord(FirstWord__Args args);
            private static _FirstWord _FirstWordFunc;
            internal static _FirstWord FirstWord() {
                if (_FirstWordFunc == null) {
                    _FirstWordFunc =
                        (_FirstWord)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnfirstWord"), typeof(_FirstWord));
                }
                
                return _FirstWordFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct GetRecordCount__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string text;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate int _GetRecordCount(GetRecordCount__Args args);
            private static _GetRecordCount _GetRecordCountFunc;
            internal static _GetRecordCount GetRecordCount() {
                if (_GetRecordCountFunc == null) {
                    _GetRecordCountFunc =
                        (_GetRecordCount)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fngetRecordCount"), typeof(_GetRecordCount));
                }
                
                return _GetRecordCountFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct RemoveRecord__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string text;
                internal int index;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            
            internal delegate IntPtr _RemoveRecord(RemoveRecord__Args args);
            private static _RemoveRecord _RemoveRecordFunc;
            internal static _RemoveRecord RemoveRecord() {
                if (_RemoveRecordFunc == null) {
                    _RemoveRecordFunc =
                        (_RemoveRecord)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnremoveRecord"), typeof(_RemoveRecord));
                }
                
                return _RemoveRecordFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct SetRecord__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string text;
                internal int index;
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string replacement;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            
            internal delegate IntPtr _SetRecord(SetRecord__Args args);
            private static _SetRecord _SetRecordFunc;
            internal static _SetRecord SetRecord() {
                if (_SetRecordFunc == null) {
                    _SetRecordFunc =
                        (_SetRecord)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnsetRecord"), typeof(_SetRecord));
                }
                
                return _SetRecordFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct GetRecords__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string text;
                internal int startIndex;
                internal int endIndex;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            
            internal delegate IntPtr _GetRecords(GetRecords__Args args);
            private static _GetRecords _GetRecordsFunc;
            internal static _GetRecords GetRecords() {
                if (_GetRecordsFunc == null) {
                    _GetRecordsFunc =
                        (_GetRecords)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fngetRecords"), typeof(_GetRecords));
                }
                
                return _GetRecordsFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct GetRecord__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string text;
                internal int index;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            
            internal delegate IntPtr _GetRecord(GetRecord__Args args);
            private static _GetRecord _GetRecordFunc;
            internal static _GetRecord GetRecord() {
                if (_GetRecordFunc == null) {
                    _GetRecordFunc =
                        (_GetRecord)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fngetRecord"), typeof(_GetRecord));
                }
                
                return _GetRecordFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct GetFieldCount__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string text;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate int _GetFieldCount(GetFieldCount__Args args);
            private static _GetFieldCount _GetFieldCountFunc;
            internal static _GetFieldCount GetFieldCount() {
                if (_GetFieldCountFunc == null) {
                    _GetFieldCountFunc =
                        (_GetFieldCount)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fngetFieldCount"), typeof(_GetFieldCount));
                }
                
                return _GetFieldCountFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct RemoveField__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string text;
                internal int index;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            
            internal delegate IntPtr _RemoveField(RemoveField__Args args);
            private static _RemoveField _RemoveFieldFunc;
            internal static _RemoveField RemoveField() {
                if (_RemoveFieldFunc == null) {
                    _RemoveFieldFunc =
                        (_RemoveField)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnremoveField"), typeof(_RemoveField));
                }
                
                return _RemoveFieldFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct SetField__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string text;
                internal int index;
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string replacement;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            
            internal delegate IntPtr _SetField(SetField__Args args);
            private static _SetField _SetFieldFunc;
            internal static _SetField SetField() {
                if (_SetFieldFunc == null) {
                    _SetFieldFunc =
                        (_SetField)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnsetField"), typeof(_SetField));
                }
                
                return _SetFieldFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct GetFields__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string text;
                internal int startIndex;
                internal int endIndex;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            
            internal delegate IntPtr _GetFields(GetFields__Args args);
            private static _GetFields _GetFieldsFunc;
            internal static _GetFields GetFields() {
                if (_GetFieldsFunc == null) {
                    _GetFieldsFunc =
                        (_GetFields)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fngetFields"), typeof(_GetFields));
                }
                
                return _GetFieldsFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct GetField__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string text;
                internal int index;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            
            internal delegate IntPtr _GetField(GetField__Args args);
            private static _GetField _GetFieldFunc;
            internal static _GetField GetField() {
                if (_GetFieldFunc == null) {
                    _GetFieldFunc =
                        (_GetField)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fngetField"), typeof(_GetField));
                }
                
                return _GetFieldFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct WeekdayNumToStr__Args
            {
                internal int num;
                [MarshalAs(UnmanagedType.I1)]
                internal bool abbreviate;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            
            internal delegate IntPtr _WeekdayNumToStr(WeekdayNumToStr__Args args);
            private static _WeekdayNumToStr _WeekdayNumToStrFunc;
            internal static _WeekdayNumToStr WeekdayNumToStr() {
                if (_WeekdayNumToStrFunc == null) {
                    _WeekdayNumToStrFunc =
                        (_WeekdayNumToStr)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnweekdayNumToStr"), typeof(_WeekdayNumToStr));
                }
                
                return _WeekdayNumToStrFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct MonthNumToStr__Args
            {
                internal int num;
                [MarshalAs(UnmanagedType.I1)]
                internal bool abbreviate;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            
            internal delegate IntPtr _MonthNumToStr(MonthNumToStr__Args args);
            private static _MonthNumToStr _MonthNumToStrFunc;
            internal static _MonthNumToStr MonthNumToStr() {
                if (_MonthNumToStrFunc == null) {
                    _MonthNumToStrFunc =
                        (_MonthNumToStr)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnmonthNumToStr"), typeof(_MonthNumToStr));
                }
                
                return _MonthNumToStrFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct GetWordCount__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string text;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate int _GetWordCount(GetWordCount__Args args);
            private static _GetWordCount _GetWordCountFunc;
            internal static _GetWordCount GetWordCount() {
                if (_GetWordCountFunc == null) {
                    _GetWordCountFunc =
                        (_GetWordCount)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fngetWordCount"), typeof(_GetWordCount));
                }
                
                return _GetWordCountFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct RemoveWord__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string text;
                internal int index;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            
            internal delegate IntPtr _RemoveWord(RemoveWord__Args args);
            private static _RemoveWord _RemoveWordFunc;
            internal static _RemoveWord RemoveWord() {
                if (_RemoveWordFunc == null) {
                    _RemoveWordFunc =
                        (_RemoveWord)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnremoveWord"), typeof(_RemoveWord));
                }
                
                return _RemoveWordFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct SetWord__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string text;
                internal int index;
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string replacement;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            
            internal delegate IntPtr _SetWord(SetWord__Args args);
            private static _SetWord _SetWordFunc;
            internal static _SetWord SetWord() {
                if (_SetWordFunc == null) {
                    _SetWordFunc =
                        (_SetWord)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnsetWord"), typeof(_SetWord));
                }
                
                return _SetWordFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct GetWords__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string text;
                internal int startIndex;
                internal int endIndex;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            
            internal delegate IntPtr _GetWords(GetWords__Args args);
            private static _GetWords _GetWordsFunc;
            internal static _GetWords GetWords() {
                if (_GetWordsFunc == null) {
                    _GetWordsFunc =
                        (_GetWords)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fngetWords"), typeof(_GetWords));
                }
                
                return _GetWordsFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct GetWord__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string text;
                internal int index;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            
            internal delegate IntPtr _GetWord(GetWord__Args args);
            private static _GetWord _GetWordFunc;
            internal static _GetWord GetWord() {
                if (_GetWordFunc == null) {
                    _GetWordFunc =
                        (_GetWord)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fngetWord"), typeof(_GetWord));
                }
                
                return _GetWordFunc;
            }


            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _AddCaseSensitiveStrings(ref StringVector.InternalStruct args);
            private static _AddCaseSensitiveStrings _AddCaseSensitiveStringsFunc;
            internal static _AddCaseSensitiveStrings AddCaseSensitiveStrings() {
                if (_AddCaseSensitiveStringsFunc == null) {
                    _AddCaseSensitiveStringsFunc =
                        (_AddCaseSensitiveStrings)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnaddCaseSensitiveStrings"), typeof(_AddCaseSensitiveStrings));
                }
                
                return _AddCaseSensitiveStringsFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct IsValidIP__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string str;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            [return: MarshalAs(UnmanagedType.I1)]
            internal delegate bool _IsValidIP(IsValidIP__Args args);
            private static _IsValidIP _IsValidIPFunc;
            internal static _IsValidIP IsValidIP() {
                if (_IsValidIPFunc == null) {
                    _IsValidIPFunc =
                        (_IsValidIP)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnisValidIP"), typeof(_IsValidIP));
                }
                
                return _IsValidIPFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct IsValidPort__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string str;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            [return: MarshalAs(UnmanagedType.I1)]
            internal delegate bool _IsValidPort(IsValidPort__Args args);
            private static _IsValidPort _IsValidPortFunc;
            internal static _IsValidPort IsValidPort() {
                if (_IsValidPortFunc == null) {
                    _IsValidPortFunc =
                        (_IsValidPort)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnisValidPort"), typeof(_IsValidPort));
                }
                
                return _IsValidPortFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct IsFloat__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string str;
                [MarshalAs(UnmanagedType.I1)]
                internal bool sciOk;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            [return: MarshalAs(UnmanagedType.I1)]
            internal delegate bool _IsFloat(IsFloat__Args args);
            private static _IsFloat _IsFloatFunc;
            internal static _IsFloat IsFloat() {
                if (_IsFloatFunc == null) {
                    _IsFloatFunc =
                        (_IsFloat)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnisFloat"), typeof(_IsFloat));
                }
                
                return _IsFloatFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct IsInt__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string str;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            [return: MarshalAs(UnmanagedType.I1)]
            internal delegate bool _IsInt(IsInt__Args args);
            private static _IsInt _IsIntFunc;
            internal static _IsInt IsInt() {
                if (_IsIntFunc == null) {
                    _IsIntFunc =
                        (_IsInt)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnisInt"), typeof(_IsInt));
                }
                
                return _IsIntFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct StrToggleCaseToWords__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string str;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            
            internal delegate IntPtr _StrToggleCaseToWords(StrToggleCaseToWords__Args args);
            private static _StrToggleCaseToWords _StrToggleCaseToWordsFunc;
            internal static _StrToggleCaseToWords StrToggleCaseToWords() {
                if (_StrToggleCaseToWordsFunc == null) {
                    _StrToggleCaseToWordsFunc =
                        (_StrToggleCaseToWords)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnstrToggleCaseToWords"), typeof(_StrToggleCaseToWords));
                }
                
                return _StrToggleCaseToWordsFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct ColorHSBToRGB__Args
            {
                internal IntPtr hsb;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate ColorI.InternalStruct _ColorHSBToRGB(ColorHSBToRGB__Args args);
            private static _ColorHSBToRGB _ColorHSBToRGBFunc;
            internal static _ColorHSBToRGB ColorHSBToRGB() {
                if (_ColorHSBToRGBFunc == null) {
                    _ColorHSBToRGBFunc =
                        (_ColorHSBToRGB)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnColorHSBToRGB"), typeof(_ColorHSBToRGB));
                }
                
                return _ColorHSBToRGBFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct ColorHEXToRGB__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string hex;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate ColorI.InternalStruct _ColorHEXToRGB(ColorHEXToRGB__Args args);
            private static _ColorHEXToRGB _ColorHEXToRGBFunc;
            internal static _ColorHEXToRGB ColorHEXToRGB() {
                if (_ColorHEXToRGBFunc == null) {
                    _ColorHEXToRGBFunc =
                        (_ColorHEXToRGB)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnColorHEXToRGB"), typeof(_ColorHEXToRGB));
                }
                
                return _ColorHEXToRGBFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct ColorRGBToHSB__Args
            {
                internal IntPtr color;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            
            internal delegate IntPtr _ColorRGBToHSB(ColorRGBToHSB__Args args);
            private static _ColorRGBToHSB _ColorRGBToHSBFunc;
            internal static _ColorRGBToHSB ColorRGBToHSB() {
                if (_ColorRGBToHSBFunc == null) {
                    _ColorRGBToHSBFunc =
                        (_ColorRGBToHSB)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnColorRGBToHSB"), typeof(_ColorRGBToHSB));
                }
                
                return _ColorRGBToHSBFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct ColorRGBToHEX__Args
            {
                internal IntPtr color;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            
            internal delegate IntPtr _ColorRGBToHEX(ColorRGBToHEX__Args args);
            private static _ColorRGBToHEX _ColorRGBToHEXFunc;
            internal static _ColorRGBToHEX ColorRGBToHEX() {
                if (_ColorRGBToHEXFunc == null) {
                    _ColorRGBToHEXFunc =
                        (_ColorRGBToHEX)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnColorRGBToHEX"), typeof(_ColorRGBToHEX));
                }
                
                return _ColorRGBToHEXFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct ColorIntToFloat__Args
            {
                internal IntPtr color;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate LinearColorF.InternalStruct _ColorIntToFloat(ColorIntToFloat__Args args);
            private static _ColorIntToFloat _ColorIntToFloatFunc;
            internal static _ColorIntToFloat ColorIntToFloat() {
                if (_ColorIntToFloatFunc == null) {
                    _ColorIntToFloatFunc =
                        (_ColorIntToFloat)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnColorIntToFloat"), typeof(_ColorIntToFloat));
                }
                
                return _ColorIntToFloatFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct ColorFloatToInt__Args
            {
                internal IntPtr color;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate ColorI.InternalStruct _ColorFloatToInt(ColorFloatToInt__Args args);
            private static _ColorFloatToInt _ColorFloatToIntFunc;
            internal static _ColorFloatToInt ColorFloatToInt() {
                if (_ColorFloatToIntFunc == null) {
                    _ColorFloatToIntFunc =
                        (_ColorFloatToInt)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnColorFloatToInt"), typeof(_ColorFloatToInt));
                }
                
                return _ColorFloatToIntFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct Strrchrpos__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string str;
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string chr;
                internal int start;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate int _Strrchrpos(Strrchrpos__Args args);
            private static _Strrchrpos _StrrchrposFunc;
            internal static _Strrchrpos Strrchrpos() {
                if (_StrrchrposFunc == null) {
                    _StrrchrposFunc =
                        (_Strrchrpos)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnstrrchrpos"), typeof(_Strrchrpos));
                }
                
                return _StrrchrposFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct Strchrpos__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string str;
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string chr;
                internal int start;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate int _Strchrpos(Strchrpos__Args args);
            private static _Strchrpos _StrchrposFunc;
            internal static _Strchrpos Strchrpos() {
                if (_StrchrposFunc == null) {
                    _StrchrposFunc =
                        (_Strchrpos)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnstrchrpos"), typeof(_Strchrpos));
                }
                
                return _StrchrposFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct EndsWith__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string str;
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string suffix;
                [MarshalAs(UnmanagedType.I1)]
                internal bool caseSensitive;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            [return: MarshalAs(UnmanagedType.I1)]
            internal delegate bool _EndsWith(EndsWith__Args args);
            private static _EndsWith _EndsWithFunc;
            internal static _EndsWith EndsWith() {
                if (_EndsWithFunc == null) {
                    _EndsWithFunc =
                        (_EndsWith)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnendsWith"), typeof(_EndsWith));
                }
                
                return _EndsWithFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct StartsWith__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string str;
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string prefix;
                [MarshalAs(UnmanagedType.I1)]
                internal bool caseSensitive;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            [return: MarshalAs(UnmanagedType.I1)]
            internal delegate bool _StartsWith(StartsWith__Args args);
            private static _StartsWith _StartsWithFunc;
            internal static _StartsWith StartsWith() {
                if (_StartsWithFunc == null) {
                    _StartsWithFunc =
                        (_StartsWith)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnstartsWith"), typeof(_StartsWith));
                }
                
                return _StartsWithFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct Isalnum__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string str;
                internal int index;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            [return: MarshalAs(UnmanagedType.I1)]
            internal delegate bool _Isalnum(Isalnum__Args args);
            private static _Isalnum _IsalnumFunc;
            internal static _Isalnum Isalnum() {
                if (_IsalnumFunc == null) {
                    _IsalnumFunc =
                        (_Isalnum)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnisalnum"), typeof(_Isalnum));
                }
                
                return _IsalnumFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct Isspace__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string str;
                internal int index;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            [return: MarshalAs(UnmanagedType.I1)]
            internal delegate bool _Isspace(Isspace__Args args);
            private static _Isspace _IsspaceFunc;
            internal static _Isspace Isspace() {
                if (_IsspaceFunc == null) {
                    _IsspaceFunc =
                        (_Isspace)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnisspace"), typeof(_Isspace));
                }
                
                return _IsspaceFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct GetFirstNumber__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string str;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            
            internal delegate IntPtr _GetFirstNumber(GetFirstNumber__Args args);
            private static _GetFirstNumber _GetFirstNumberFunc;
            internal static _GetFirstNumber GetFirstNumber() {
                if (_GetFirstNumberFunc == null) {
                    _GetFirstNumberFunc =
                        (_GetFirstNumber)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fngetFirstNumber"), typeof(_GetFirstNumber));
                }
                
                return _GetFirstNumberFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct StripTrailingNumber__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string str;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            
            internal delegate IntPtr _StripTrailingNumber(StripTrailingNumber__Args args);
            private static _StripTrailingNumber _StripTrailingNumberFunc;
            internal static _StripTrailingNumber StripTrailingNumber() {
                if (_StripTrailingNumberFunc == null) {
                    _StripTrailingNumberFunc =
                        (_StripTrailingNumber)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnstripTrailingNumber"), typeof(_StripTrailingNumber));
                }
                
                return _StripTrailingNumberFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct GetTrailingNumber__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string str;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate int _GetTrailingNumber(GetTrailingNumber__Args args);
            private static _GetTrailingNumber _GetTrailingNumberFunc;
            internal static _GetTrailingNumber GetTrailingNumber() {
                if (_GetTrailingNumberFunc == null) {
                    _GetTrailingNumberFunc =
                        (_GetTrailingNumber)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fngetTrailingNumber"), typeof(_GetTrailingNumber));
                }
                
                return _GetTrailingNumberFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct StrIsMatchMultipleExpr__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string patterns;
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string str;
                [MarshalAs(UnmanagedType.I1)]
                internal bool caseSensitive;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            [return: MarshalAs(UnmanagedType.I1)]
            internal delegate bool _StrIsMatchMultipleExpr(StrIsMatchMultipleExpr__Args args);
            private static _StrIsMatchMultipleExpr _StrIsMatchMultipleExprFunc;
            internal static _StrIsMatchMultipleExpr StrIsMatchMultipleExpr() {
                if (_StrIsMatchMultipleExprFunc == null) {
                    _StrIsMatchMultipleExprFunc =
                        (_StrIsMatchMultipleExpr)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnstrIsMatchMultipleExpr"), typeof(_StrIsMatchMultipleExpr));
                }
                
                return _StrIsMatchMultipleExprFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct StrIsMatchExpr__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string pattern;
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string str;
                [MarshalAs(UnmanagedType.I1)]
                internal bool caseSensitive;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            [return: MarshalAs(UnmanagedType.I1)]
            internal delegate bool _StrIsMatchExpr(StrIsMatchExpr__Args args);
            private static _StrIsMatchExpr _StrIsMatchExprFunc;
            internal static _StrIsMatchExpr StrIsMatchExpr() {
                if (_StrIsMatchExprFunc == null) {
                    _StrIsMatchExprFunc =
                        (_StrIsMatchExpr)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnstrIsMatchExpr"), typeof(_StrIsMatchExpr));
                }
                
                return _StrIsMatchExprFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct GetSubStr__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string str;
                internal int start;
                internal int numChars;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            
            internal delegate IntPtr _GetSubStr(GetSubStr__Args args);
            private static _GetSubStr _GetSubStrFunc;
            internal static _GetSubStr GetSubStr() {
                if (_GetSubStrFunc == null) {
                    _GetSubStrFunc =
                        (_GetSubStr)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fngetSubStr"), typeof(_GetSubStr));
                }
                
                return _GetSubStrFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct Strrepeat__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string str;
                internal int numTimes;
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string delimiter;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            
            internal delegate IntPtr _Strrepeat(Strrepeat__Args args);
            private static _Strrepeat _StrrepeatFunc;
            internal static _Strrepeat Strrepeat() {
                if (_StrrepeatFunc == null) {
                    _StrrepeatFunc =
                        (_Strrepeat)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnstrrepeat"), typeof(_Strrepeat));
                }
                
                return _StrrepeatFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct Strreplace__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string source;
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string from;
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string to;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            
            internal delegate IntPtr _Strreplace(Strreplace__Args args);
            private static _Strreplace _StrreplaceFunc;
            internal static _Strreplace Strreplace() {
                if (_StrreplaceFunc == null) {
                    _StrreplaceFunc =
                        (_Strreplace)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnstrreplace"), typeof(_Strreplace));
                }
                
                return _StrreplaceFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct Strrchr__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string str;
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string chr;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            
            internal delegate IntPtr _Strrchr(Strrchr__Args args);
            private static _Strrchr _StrrchrFunc;
            internal static _Strrchr Strrchr() {
                if (_StrrchrFunc == null) {
                    _StrrchrFunc =
                        (_Strrchr)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnstrrchr"), typeof(_Strrchr));
                }
                
                return _StrrchrFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct Strchr__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string str;
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string chr;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            
            internal delegate IntPtr _Strchr(Strchr__Args args);
            private static _Strchr _StrchrFunc;
            internal static _Strchr Strchr() {
                if (_StrchrFunc == null) {
                    _StrchrFunc =
                        (_Strchr)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnstrchr"), typeof(_Strchr));
                }
                
                return _StrchrFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct Strupr__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string str;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            
            internal delegate IntPtr _Strupr(Strupr__Args args);
            private static _Strupr _StruprFunc;
            internal static _Strupr Strupr() {
                if (_StruprFunc == null) {
                    _StruprFunc =
                        (_Strupr)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnstrupr"), typeof(_Strupr));
                }
                
                return _StruprFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct Strlwr__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string str;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            
            internal delegate IntPtr _Strlwr(Strlwr__Args args);
            private static _Strlwr _StrlwrFunc;
            internal static _Strlwr Strlwr() {
                if (_StrlwrFunc == null) {
                    _StrlwrFunc =
                        (_Strlwr)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnstrlwr"), typeof(_Strlwr));
                }
                
                return _StrlwrFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct StripChars__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string str;
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string chars;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            
            internal delegate IntPtr _StripChars(StripChars__Args args);
            private static _StripChars _StripCharsFunc;
            internal static _StripChars StripChars() {
                if (_StripCharsFunc == null) {
                    _StripCharsFunc =
                        (_StripChars)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnstripChars"), typeof(_StripChars));
                }
                
                return _StripCharsFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct Trim__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string str;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            
            internal delegate IntPtr _Trim(Trim__Args args);
            private static _Trim _TrimFunc;
            internal static _Trim Trim() {
                if (_TrimFunc == null) {
                    _TrimFunc =
                        (_Trim)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fntrim"), typeof(_Trim));
                }
                
                return _TrimFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct Rtrim__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string str;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            
            internal delegate IntPtr _Rtrim(Rtrim__Args args);
            private static _Rtrim _RtrimFunc;
            internal static _Rtrim Rtrim() {
                if (_RtrimFunc == null) {
                    _RtrimFunc =
                        (_Rtrim)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnrtrim"), typeof(_Rtrim));
                }
                
                return _RtrimFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct Ltrim__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string str;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            
            internal delegate IntPtr _Ltrim(Ltrim__Args args);
            private static _Ltrim _LtrimFunc;
            internal static _Ltrim Ltrim() {
                if (_LtrimFunc == null) {
                    _LtrimFunc =
                        (_Ltrim)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnltrim"), typeof(_Ltrim));
                }
                
                return _LtrimFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct Strposr__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string haystack;
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string needle;
                internal int offset;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate int _Strposr(Strposr__Args args);
            private static _Strposr _StrposrFunc;
            internal static _Strposr Strposr() {
                if (_StrposrFunc == null) {
                    _StrposrFunc =
                        (_Strposr)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnstrposr"), typeof(_Strposr));
                }
                
                return _StrposrFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct Strpos__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string haystack;
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string needle;
                internal int offset;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate int _Strpos(Strpos__Args args);
            private static _Strpos _StrposFunc;
            internal static _Strpos Strpos() {
                if (_StrposFunc == null) {
                    _StrposFunc =
                        (_Strpos)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnstrpos"), typeof(_Strpos));
                }
                
                return _StrposFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct Strstr__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string _string;
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string substring;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate int _Strstr(Strstr__Args args);
            private static _Strstr _StrstrFunc;
            internal static _Strstr Strstr() {
                if (_StrstrFunc == null) {
                    _StrstrFunc =
                        (_Strstr)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnstrstr"), typeof(_Strstr));
                }
                
                return _StrstrFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct Strlenskip__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string str;
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string first;
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string last;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate int _Strlenskip(Strlenskip__Args args);
            private static _Strlenskip _StrlenskipFunc;
            internal static _Strlenskip Strlenskip() {
                if (_StrlenskipFunc == null) {
                    _StrlenskipFunc =
                        (_Strlenskip)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnstrlenskip"), typeof(_Strlenskip));
                }
                
                return _StrlenskipFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct Strlen__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string str;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate int _Strlen(Strlen__Args args);
            private static _Strlen _StrlenFunc;
            internal static _Strlen Strlen() {
                if (_StrlenFunc == null) {
                    _StrlenFunc =
                        (_Strlen)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnstrlen"), typeof(_Strlen));
                }
                
                return _StrlenFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct Strinatcmp__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string str1;
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string str2;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate int _Strinatcmp(Strinatcmp__Args args);
            private static _Strinatcmp _StrinatcmpFunc;
            internal static _Strinatcmp Strinatcmp() {
                if (_StrinatcmpFunc == null) {
                    _StrinatcmpFunc =
                        (_Strinatcmp)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnstrinatcmp"), typeof(_Strinatcmp));
                }
                
                return _StrinatcmpFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct Strnatcmp__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string str1;
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string str2;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate int _Strnatcmp(Strnatcmp__Args args);
            private static _Strnatcmp _StrnatcmpFunc;
            internal static _Strnatcmp Strnatcmp() {
                if (_StrnatcmpFunc == null) {
                    _StrnatcmpFunc =
                        (_Strnatcmp)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnstrnatcmp"), typeof(_Strnatcmp));
                }
                
                return _StrnatcmpFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct Stricmp__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string str1;
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string str2;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate int _Stricmp(Stricmp__Args args);
            private static _Stricmp _StricmpFunc;
            internal static _Stricmp Stricmp() {
                if (_StricmpFunc == null) {
                    _StricmpFunc =
                        (_Stricmp)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnstricmp"), typeof(_Stricmp));
                }
                
                return _StricmpFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct Strcmp__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string str1;
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string str2;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate int _Strcmp(Strcmp__Args args);
            private static _Strcmp _StrcmpFunc;
            internal static _Strcmp Strcmp() {
                if (_StrcmpFunc == null) {
                    _StrcmpFunc =
                        (_Strcmp)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnstrcmp"), typeof(_Strcmp));
                }
                
                return _StrcmpFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct Strformat__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string format;
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string value;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            
            internal delegate IntPtr _Strformat(Strformat__Args args);
            private static _Strformat _StrformatFunc;
            internal static _Strformat Strformat() {
                if (_StrformatFunc == null) {
                    _StrformatFunc =
                        (_Strformat)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnstrformat"), typeof(_Strformat));
                }
                
                return _StrformatFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct Strasc__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string chr;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate int _Strasc(Strasc__Args args);
            private static _Strasc _StrascFunc;
            internal static _Strasc Strasc() {
                if (_StrascFunc == null) {
                    _StrascFunc =
                        (_Strasc)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnstrasc"), typeof(_Strasc));
                }
                
                return _StrascFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct DumpConsoleFunctions__Args
            {
                [MarshalAs(UnmanagedType.I1)]
                internal bool dumpScript;
                [MarshalAs(UnmanagedType.I1)]
                internal bool dumpEngine;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _DumpConsoleFunctions(DumpConsoleFunctions__Args args);
            private static _DumpConsoleFunctions _DumpConsoleFunctionsFunc;
            internal static _DumpConsoleFunctions DumpConsoleFunctions() {
                if (_DumpConsoleFunctionsFunc == null) {
                    _DumpConsoleFunctionsFunc =
                        (_DumpConsoleFunctions)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fndumpConsoleFunctions"), typeof(_DumpConsoleFunctions));
                }
                
                return _DumpConsoleFunctionsFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct DumpConsoleClasses__Args
            {
                [MarshalAs(UnmanagedType.I1)]
                internal bool dumpScript;
                [MarshalAs(UnmanagedType.I1)]
                internal bool dumpEngine;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _DumpConsoleClasses(DumpConsoleClasses__Args args);
            private static _DumpConsoleClasses _DumpConsoleClassesFunc;
            internal static _DumpConsoleClasses DumpConsoleClasses() {
                if (_DumpConsoleClassesFunc == null) {
                    _DumpConsoleClassesFunc =
                        (_DumpConsoleClasses)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fndumpConsoleClasses"), typeof(_DumpConsoleClasses));
                }
                
                return _DumpConsoleClassesFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct LogWarning__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string message;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _LogWarning(LogWarning__Args args);
            private static _LogWarning _LogWarningFunc;
            internal static _LogWarning LogWarning() {
                if (_LogWarningFunc == null) {
                    _LogWarningFunc =
                        (_LogWarning)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnlogWarning"), typeof(_LogWarning));
                }
                
                return _LogWarningFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct LogError__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string message;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _LogError(LogError__Args args);
            private static _LogError _LogErrorFunc;
            internal static _LogError LogError() {
                if (_LogErrorFunc == null) {
                    _LogErrorFunc =
                        (_LogError)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnlogError"), typeof(_LogError));
                }
                
                return _LogErrorFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct Log__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string message;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _Log(Log__Args args);
            private static _Log _LogFunc;
            internal static _Log Log() {
                if (_LogFunc == null) {
                    _LogFunc =
                        (_Log)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnlog"), typeof(_Log));
                }
                
                return _LogFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct SetClipboard__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string text;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            [return: MarshalAs(UnmanagedType.I1)]
            internal delegate bool _SetClipboard(SetClipboard__Args args);
            private static _SetClipboard _SetClipboardFunc;
            internal static _SetClipboard SetClipboard() {
                if (_SetClipboardFunc == null) {
                    _SetClipboardFunc =
                        (_SetClipboard)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnsetClipboard"), typeof(_SetClipboard));
                }
                
                return _SetClipboardFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct GetClipboard__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            
            internal delegate IntPtr _GetClipboard(GetClipboard__Args args);
            private static _GetClipboard _GetClipboardFunc;
            internal static _GetClipboard GetClipboard() {
                if (_GetClipboardFunc == null) {
                    _GetClipboardFunc =
                        (_GetClipboard)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fngetClipboard"), typeof(_GetClipboard));
                }
                
                return _GetClipboardFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct Cls__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _Cls(Cls__Args args);
            private static _Cls _ClsFunc;
            internal static _Cls Cls() {
                if (_ClsFunc == null) {
                    _ClsFunc =
                        (_Cls)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fncls"), typeof(_Cls));
                }
                
                return _ClsFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct SfxDumpSourcesToString__Args
            {
                [MarshalAs(UnmanagedType.I1)]
                internal bool includeGroups;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            
            internal delegate IntPtr _SfxDumpSourcesToString(SfxDumpSourcesToString__Args args);
            private static _SfxDumpSourcesToString _SfxDumpSourcesToStringFunc;
            internal static _SfxDumpSourcesToString SfxDumpSourcesToString() {
                if (_SfxDumpSourcesToStringFunc == null) {
                    _SfxDumpSourcesToStringFunc =
                        (_SfxDumpSourcesToString)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnsfxDumpSourcesToString"), typeof(_SfxDumpSourcesToString));
                }
                
                return _SfxDumpSourcesToStringFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct SfxDumpSources__Args
            {
                [MarshalAs(UnmanagedType.I1)]
                internal bool includeGroups;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _SfxDumpSources(SfxDumpSources__Args args);
            private static _SfxDumpSources _SfxDumpSourcesFunc;
            internal static _SfxDumpSources SfxDumpSources() {
                if (_SfxDumpSourcesFunc == null) {
                    _SfxDumpSourcesFunc =
                        (_SfxDumpSources)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnsfxDumpSources"), typeof(_SfxDumpSources));
                }
                
                return _SfxDumpSourcesFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct SfxSetRolloffFactor__Args
            {
                internal float value;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _SfxSetRolloffFactor(SfxSetRolloffFactor__Args args);
            private static _SfxSetRolloffFactor _SfxSetRolloffFactorFunc;
            internal static _SfxSetRolloffFactor SfxSetRolloffFactor() {
                if (_SfxSetRolloffFactorFunc == null) {
                    _SfxSetRolloffFactorFunc =
                        (_SfxSetRolloffFactor)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnsfxSetRolloffFactor"), typeof(_SfxSetRolloffFactor));
                }
                
                return _SfxSetRolloffFactorFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct SfxGetRolloffFactor__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate float _SfxGetRolloffFactor(SfxGetRolloffFactor__Args args);
            private static _SfxGetRolloffFactor _SfxGetRolloffFactorFunc;
            internal static _SfxGetRolloffFactor SfxGetRolloffFactor() {
                if (_SfxGetRolloffFactorFunc == null) {
                    _SfxGetRolloffFactorFunc =
                        (_SfxGetRolloffFactor)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnsfxGetRolloffFactor"), typeof(_SfxGetRolloffFactor));
                }
                
                return _SfxGetRolloffFactorFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct SfxSetDopplerFactor__Args
            {
                internal float value;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _SfxSetDopplerFactor(SfxSetDopplerFactor__Args args);
            private static _SfxSetDopplerFactor _SfxSetDopplerFactorFunc;
            internal static _SfxSetDopplerFactor SfxSetDopplerFactor() {
                if (_SfxSetDopplerFactorFunc == null) {
                    _SfxSetDopplerFactorFunc =
                        (_SfxSetDopplerFactor)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnsfxSetDopplerFactor"), typeof(_SfxSetDopplerFactor));
                }
                
                return _SfxSetDopplerFactorFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct SfxGetDopplerFactor__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate float _SfxGetDopplerFactor(SfxGetDopplerFactor__Args args);
            private static _SfxGetDopplerFactor _SfxGetDopplerFactorFunc;
            internal static _SfxGetDopplerFactor SfxGetDopplerFactor() {
                if (_SfxGetDopplerFactorFunc == null) {
                    _SfxGetDopplerFactorFunc =
                        (_SfxGetDopplerFactor)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnsfxGetDopplerFactor"), typeof(_SfxGetDopplerFactor));
                }
                
                return _SfxGetDopplerFactorFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct SfxSetDistanceModel__Args
            {
                internal int model;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _SfxSetDistanceModel(SfxSetDistanceModel__Args args);
            private static _SfxSetDistanceModel _SfxSetDistanceModelFunc;
            internal static _SfxSetDistanceModel SfxSetDistanceModel() {
                if (_SfxSetDistanceModelFunc == null) {
                    _SfxSetDistanceModelFunc =
                        (_SfxSetDistanceModel)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnsfxSetDistanceModel"), typeof(_SfxSetDistanceModel));
                }
                
                return _SfxSetDistanceModelFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct SfxGetDistanceModel__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate int _SfxGetDistanceModel(SfxGetDistanceModel__Args args);
            private static _SfxGetDistanceModel _SfxGetDistanceModelFunc;
            internal static _SfxGetDistanceModel SfxGetDistanceModel() {
                if (_SfxGetDistanceModelFunc == null) {
                    _SfxGetDistanceModelFunc =
                        (_SfxGetDistanceModel)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnsfxGetDistanceModel"), typeof(_SfxGetDistanceModel));
                }
                
                return _SfxGetDistanceModelFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct SfxDeleteWhenStopped__Args
            {
                internal IntPtr source;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _SfxDeleteWhenStopped(SfxDeleteWhenStopped__Args args);
            private static _SfxDeleteWhenStopped _SfxDeleteWhenStoppedFunc;
            internal static _SfxDeleteWhenStopped SfxDeleteWhenStopped() {
                if (_SfxDeleteWhenStoppedFunc == null) {
                    _SfxDeleteWhenStoppedFunc =
                        (_SfxDeleteWhenStopped)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnsfxDeleteWhenStopped"), typeof(_SfxDeleteWhenStopped));
                }
                
                return _SfxDeleteWhenStoppedFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct SfxStopAndDelete__Args
            {
                internal IntPtr source;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _SfxStopAndDelete(SfxStopAndDelete__Args args);
            private static _SfxStopAndDelete _SfxStopAndDeleteFunc;
            internal static _SfxStopAndDelete SfxStopAndDelete() {
                if (_SfxStopAndDeleteFunc == null) {
                    _SfxStopAndDeleteFunc =
                        (_SfxStopAndDelete)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnsfxStopAndDelete"), typeof(_SfxStopAndDelete));
                }
                
                return _SfxStopAndDeleteFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct SfxStop__Args
            {
                internal IntPtr source;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _SfxStop(SfxStop__Args args);
            private static _SfxStop _SfxStopFunc;
            internal static _SfxStop SfxStop() {
                if (_SfxStopFunc == null) {
                    _SfxStopFunc =
                        (_SfxStop)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnsfxStop"), typeof(_SfxStop));
                }
                
                return _SfxStopFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct SfxPlayOnce__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string sfxType;
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string arg0;
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string arg1;
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string arg2;
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string arg3;
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string arg4;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate int _SfxPlayOnce(SfxPlayOnce__Args args);
            private static _SfxPlayOnce _SfxPlayOnceFunc;
            internal static _SfxPlayOnce SfxPlayOnce() {
                if (_SfxPlayOnceFunc == null) {
                    _SfxPlayOnceFunc =
                        (_SfxPlayOnce)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnsfxPlayOnce"), typeof(_SfxPlayOnce));
                }
                
                return _SfxPlayOnceFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct SfxPlay__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string trackName;
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string pointOrX;
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string y;
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string z;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate int _SfxPlay(SfxPlay__Args args);
            private static _SfxPlay _SfxPlayFunc;
            internal static _SfxPlay SfxPlay() {
                if (_SfxPlayFunc == null) {
                    _SfxPlayFunc =
                        (_SfxPlay)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnsfxPlay"), typeof(_SfxPlay));
                }
                
                return _SfxPlayFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct SfxCreateSource__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string sfxType;
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string arg0;
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string arg1;
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string arg2;
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string arg3;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate int _SfxCreateSource(SfxCreateSource__Args args);
            private static _SfxCreateSource _SfxCreateSourceFunc;
            internal static _SfxCreateSource SfxCreateSource() {
                if (_SfxCreateSourceFunc == null) {
                    _SfxCreateSourceFunc =
                        (_SfxCreateSource)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnsfxCreateSource"), typeof(_SfxCreateSource));
                }
                
                return _SfxCreateSourceFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct SfxGetDeviceInfo__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            
            internal delegate IntPtr _SfxGetDeviceInfo(SfxGetDeviceInfo__Args args);
            private static _SfxGetDeviceInfo _SfxGetDeviceInfoFunc;
            internal static _SfxGetDeviceInfo SfxGetDeviceInfo() {
                if (_SfxGetDeviceInfoFunc == null) {
                    _SfxGetDeviceInfoFunc =
                        (_SfxGetDeviceInfo)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnsfxGetDeviceInfo"), typeof(_SfxGetDeviceInfo));
                }
                
                return _SfxGetDeviceInfoFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct SfxDeleteDevice__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _SfxDeleteDevice(SfxDeleteDevice__Args args);
            private static _SfxDeleteDevice _SfxDeleteDeviceFunc;
            internal static _SfxDeleteDevice SfxDeleteDevice() {
                if (_SfxDeleteDeviceFunc == null) {
                    _SfxDeleteDeviceFunc =
                        (_SfxDeleteDevice)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnsfxDeleteDevice"), typeof(_SfxDeleteDevice));
                }
                
                return _SfxDeleteDeviceFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct SfxCreateDevice__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string provider;
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string device;
                [MarshalAs(UnmanagedType.I1)]
                internal bool useHardware;
                internal int maxBuffers;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            [return: MarshalAs(UnmanagedType.I1)]
            internal delegate bool _SfxCreateDevice(SfxCreateDevice__Args args);
            private static _SfxCreateDevice _SfxCreateDeviceFunc;
            internal static _SfxCreateDevice SfxCreateDevice() {
                if (_SfxCreateDeviceFunc == null) {
                    _SfxCreateDeviceFunc =
                        (_SfxCreateDevice)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnsfxCreateDevice"), typeof(_SfxCreateDevice));
                }
                
                return _SfxCreateDeviceFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct SfxGetAvailableDevices__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            
            internal delegate IntPtr _SfxGetAvailableDevices(SfxGetAvailableDevices__Args args);
            private static _SfxGetAvailableDevices _SfxGetAvailableDevicesFunc;
            internal static _SfxGetAvailableDevices SfxGetAvailableDevices() {
                if (_SfxGetAvailableDevicesFunc == null) {
                    _SfxGetAvailableDevicesFunc =
                        (_SfxGetAvailableDevices)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnsfxGetAvailableDevices"), typeof(_SfxGetAvailableDevices));
                }
                
                return _SfxGetAvailableDevicesFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct SfxGetActiveStates__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            
            internal delegate IntPtr _SfxGetActiveStates(SfxGetActiveStates__Args args);
            private static _SfxGetActiveStates _SfxGetActiveStatesFunc;
            internal static _SfxGetActiveStates SfxGetActiveStates() {
                if (_SfxGetActiveStatesFunc == null) {
                    _SfxGetActiveStatesFunc =
                        (_SfxGetActiveStates)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnsfxGetActiveStates"), typeof(_SfxGetActiveStates));
                }
                
                return _SfxGetActiveStatesFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct GetBuildString__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            
            internal delegate IntPtr _GetBuildString(GetBuildString__Args args);
            private static _GetBuildString _GetBuildStringFunc;
            internal static _GetBuildString GetBuildString() {
                if (_GetBuildStringFunc == null) {
                    _GetBuildStringFunc =
                        (_GetBuildString)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fngetBuildString"), typeof(_GetBuildString));
                }
                
                return _GetBuildStringFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct GetCompileTimeString__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            
            internal delegate IntPtr _GetCompileTimeString(GetCompileTimeString__Args args);
            private static _GetCompileTimeString _GetCompileTimeStringFunc;
            internal static _GetCompileTimeString GetCompileTimeString() {
                if (_GetCompileTimeStringFunc == null) {
                    _GetCompileTimeStringFunc =
                        (_GetCompileTimeString)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fngetCompileTimeString"), typeof(_GetCompileTimeString));
                }
                
                return _GetCompileTimeStringFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct GetEngineName__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            
            internal delegate IntPtr _GetEngineName(GetEngineName__Args args);
            private static _GetEngineName _GetEngineNameFunc;
            internal static _GetEngineName GetEngineName() {
                if (_GetEngineNameFunc == null) {
                    _GetEngineNameFunc =
                        (_GetEngineName)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fngetEngineName"), typeof(_GetEngineName));
                }
                
                return _GetEngineNameFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct GetAppVersionString__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            
            internal delegate IntPtr _GetAppVersionString(GetAppVersionString__Args args);
            private static _GetAppVersionString _GetAppVersionStringFunc;
            internal static _GetAppVersionString GetAppVersionString() {
                if (_GetAppVersionStringFunc == null) {
                    _GetAppVersionStringFunc =
                        (_GetAppVersionString)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fngetAppVersionString"), typeof(_GetAppVersionString));
                }
                
                return _GetAppVersionStringFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct GetVersionString__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            
            internal delegate IntPtr _GetVersionString(GetVersionString__Args args);
            private static _GetVersionString _GetVersionStringFunc;
            internal static _GetVersionString GetVersionString() {
                if (_GetVersionStringFunc == null) {
                    _GetVersionStringFunc =
                        (_GetVersionString)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fngetVersionString"), typeof(_GetVersionString));
                }
                
                return _GetVersionStringFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct GetAppVersionNumber__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate int _GetAppVersionNumber(GetAppVersionNumber__Args args);
            private static _GetAppVersionNumber _GetAppVersionNumberFunc;
            internal static _GetAppVersionNumber GetAppVersionNumber() {
                if (_GetAppVersionNumberFunc == null) {
                    _GetAppVersionNumberFunc =
                        (_GetAppVersionNumber)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fngetAppVersionNumber"), typeof(_GetAppVersionNumber));
                }
                
                return _GetAppVersionNumberFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct GetVersionNumber__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate int _GetVersionNumber(GetVersionNumber__Args args);
            private static _GetVersionNumber _GetVersionNumberFunc;
            internal static _GetVersionNumber GetVersionNumber() {
                if (_GetVersionNumberFunc == null) {
                    _GetVersionNumberFunc =
                        (_GetVersionNumber)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fngetVersionNumber"), typeof(_GetVersionNumber));
                }
                
                return _GetVersionNumberFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct SetServerInfo__Args
            {
                internal uint index;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            [return: MarshalAs(UnmanagedType.I1)]
            internal delegate bool _SetServerInfo(SetServerInfo__Args args);
            private static _SetServerInfo _SetServerInfoFunc;
            internal static _SetServerInfo SetServerInfo() {
                if (_SetServerInfoFunc == null) {
                    _SetServerInfoFunc =
                        (_SetServerInfo)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnsetServerInfo"), typeof(_SetServerInfo));
                }
                
                return _SetServerInfoFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct GetServerCount__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate int _GetServerCount(GetServerCount__Args args);
            private static _GetServerCount _GetServerCountFunc;
            internal static _GetServerCount GetServerCount() {
                if (_GetServerCountFunc == null) {
                    _GetServerCountFunc =
                        (_GetServerCount)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fngetServerCount"), typeof(_GetServerCount));
                }
                
                return _GetServerCountFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct StopHeartbeat__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _StopHeartbeat(StopHeartbeat__Args args);
            private static _StopHeartbeat _StopHeartbeatFunc;
            internal static _StopHeartbeat StopHeartbeat() {
                if (_StopHeartbeatFunc == null) {
                    _StopHeartbeatFunc =
                        (_StopHeartbeat)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnstopHeartbeat"), typeof(_StopHeartbeat));
                }
                
                return _StopHeartbeatFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct StartHeartbeat__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _StartHeartbeat(StartHeartbeat__Args args);
            private static _StartHeartbeat _StartHeartbeatFunc;
            internal static _StartHeartbeat StartHeartbeat() {
                if (_StartHeartbeatFunc == null) {
                    _StartHeartbeatFunc =
                        (_StartHeartbeat)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnstartHeartbeat"), typeof(_StartHeartbeat));
                }
                
                return _StartHeartbeatFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct StopServerQuery__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _StopServerQuery(StopServerQuery__Args args);
            private static _StopServerQuery _StopServerQueryFunc;
            internal static _StopServerQuery StopServerQuery() {
                if (_StopServerQueryFunc == null) {
                    _StopServerQueryFunc =
                        (_StopServerQuery)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnstopServerQuery"), typeof(_StopServerQuery));
                }
                
                return _StopServerQueryFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct CancelServerQuery__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _CancelServerQuery(CancelServerQuery__Args args);
            private static _CancelServerQuery _CancelServerQueryFunc;
            internal static _CancelServerQuery CancelServerQuery() {
                if (_CancelServerQueryFunc == null) {
                    _CancelServerQueryFunc =
                        (_CancelServerQuery)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fncancelServerQuery"), typeof(_CancelServerQuery));
                }
                
                return _CancelServerQueryFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct QuerySingleServer__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string addrText;
                internal byte flags;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _QuerySingleServer(QuerySingleServer__Args args);
            private static _QuerySingleServer _QuerySingleServerFunc;
            internal static _QuerySingleServer QuerySingleServer() {
                if (_QuerySingleServerFunc == null) {
                    _QuerySingleServerFunc =
                        (_QuerySingleServer)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnquerySingleServer"), typeof(_QuerySingleServer));
                }
                
                return _QuerySingleServerFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct QueryMasterServer__Args
            {
                internal uint flags;
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string gameType;
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string missionType;
                internal uint minPlayers;
                internal uint maxPlayers;
                internal uint maxBots;
                internal uint regionMask;
                internal uint maxPing;
                internal uint minCPU;
                internal uint filterFlags;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _QueryMasterServer(QueryMasterServer__Args args);
            private static _QueryMasterServer _QueryMasterServerFunc;
            internal static _QueryMasterServer QueryMasterServer() {
                if (_QueryMasterServerFunc == null) {
                    _QueryMasterServerFunc =
                        (_QueryMasterServer)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnqueryMasterServer"), typeof(_QueryMasterServer));
                }
                
                return _QueryMasterServerFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct QueryLanServers__Args
            {
                internal uint lanPort;
                internal uint flags;
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string gameType;
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string missionType;
                internal uint minPlayers;
                internal uint maxPlayers;
                internal uint maxBots;
                internal uint regionMask;
                internal uint maxPing;
                internal uint minCPU;
                internal uint filterFlags;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _QueryLanServers(QueryLanServers__Args args);
            private static _QueryLanServers _QueryLanServersFunc;
            internal static _QueryLanServers QueryLanServers() {
                if (_QueryLanServersFunc == null) {
                    _QueryLanServersFunc =
                        (_QueryLanServers)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnqueryLanServers"), typeof(_QueryLanServers));
                }
                
                return _QueryLanServersFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct QueryAllServers__Args
            {
                internal uint lanPort;
                internal uint flags;
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string gameType;
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string missionType;
                internal uint minPlayers;
                internal uint maxPlayers;
                internal uint maxBots;
                internal uint regionMask;
                internal uint maxPing;
                internal uint minCPU;
                internal uint filterFlags;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _QueryAllServers(QueryAllServers__Args args);
            private static _QueryAllServers _QueryAllServersFunc;
            internal static _QueryAllServers QueryAllServers() {
                if (_QueryAllServersFunc == null) {
                    _QueryAllServersFunc =
                        (_QueryAllServers)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnqueryAllServers"), typeof(_QueryAllServers));
                }
                
                return _QueryAllServersFunc;
            }


            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            
            internal delegate IntPtr _BuildTaggedString(ref StringVector.InternalStruct args);
            private static _BuildTaggedString _BuildTaggedStringFunc;
            internal static _BuildTaggedString BuildTaggedString() {
                if (_BuildTaggedStringFunc == null) {
                    _BuildTaggedStringFunc =
                        (_BuildTaggedString)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnbuildTaggedString"), typeof(_BuildTaggedString));
                }
                
                return _BuildTaggedStringFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct GetTaggedString__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string tag;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            
            internal delegate IntPtr _GetTaggedString(GetTaggedString__Args args);
            private static _GetTaggedString _GetTaggedStringFunc;
            internal static _GetTaggedString GetTaggedString() {
                if (_GetTaggedStringFunc == null) {
                    _GetTaggedStringFunc =
                        (_GetTaggedString)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fngetTaggedString"), typeof(_GetTaggedString));
                }
                
                return _GetTaggedStringFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct AddTaggedString__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string str;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            
            internal delegate IntPtr _AddTaggedString(AddTaggedString__Args args);
            private static _AddTaggedString _AddTaggedStringFunc;
            internal static _AddTaggedString AddTaggedString() {
                if (_AddTaggedStringFunc == null) {
                    _AddTaggedStringFunc =
                        (_AddTaggedString)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnaddTaggedString"), typeof(_AddTaggedString));
                }
                
                return _AddTaggedStringFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct RemoveTaggedString__Args
            {
                internal int tag;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _RemoveTaggedString(RemoveTaggedString__Args args);
            private static _RemoveTaggedString _RemoveTaggedStringFunc;
            internal static _RemoveTaggedString RemoveTaggedString() {
                if (_RemoveTaggedStringFunc == null) {
                    _RemoveTaggedStringFunc =
                        (_RemoveTaggedString)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnremoveTaggedString"), typeof(_RemoveTaggedString));
                }
                
                return _RemoveTaggedStringFunc;
            }


            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _CommandToClient(ref StringVector.InternalStruct args);
            private static _CommandToClient _CommandToClientFunc;
            internal static _CommandToClient CommandToClient() {
                if (_CommandToClientFunc == null) {
                    _CommandToClientFunc =
                        (_CommandToClient)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fncommandToClient"), typeof(_CommandToClient));
                }
                
                return _CommandToClientFunc;
            }


            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _CommandToServer(ref StringVector.InternalStruct args);
            private static _CommandToServer _CommandToServerFunc;
            internal static _CommandToServer CommandToServer() {
                if (_CommandToServerFunc == null) {
                    _CommandToServerFunc =
                        (_CommandToServer)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fncommandToServer"), typeof(_CommandToServer));
                }
                
                return _CommandToServerFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct GetLocalTime__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            
            internal delegate IntPtr _GetLocalTime(GetLocalTime__Args args);
            private static _GetLocalTime _GetLocalTimeFunc;
            internal static _GetLocalTime GetLocalTime() {
                if (_GetLocalTimeFunc == null) {
                    _GetLocalTimeFunc =
                        (_GetLocalTime)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fngetLocalTime"), typeof(_GetLocalTime));
                }
                
                return _GetLocalTimeFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct GetRealTime__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate int _GetRealTime(GetRealTime__Args args);
            private static _GetRealTime _GetRealTimeFunc;
            internal static _GetRealTime GetRealTime() {
                if (_GetRealTimeFunc == null) {
                    _GetRealTimeFunc =
                        (_GetRealTime)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fngetRealTime"), typeof(_GetRealTime));
                }
                
                return _GetRealTimeFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct GetSimTime__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate int _GetSimTime(GetSimTime__Args args);
            private static _GetSimTime _GetSimTimeFunc;
            internal static _GetSimTime GetSimTime() {
                if (_GetSimTimeFunc == null) {
                    _GetSimTimeFunc =
                        (_GetSimTime)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fngetSimTime"), typeof(_GetSimTime));
                }
                
                return _GetSimTimeFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct PlayJournal__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string filename;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _PlayJournal(PlayJournal__Args args);
            private static _PlayJournal _PlayJournalFunc;
            internal static _PlayJournal PlayJournal() {
                if (_PlayJournalFunc == null) {
                    _PlayJournalFunc =
                        (_PlayJournal)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnplayJournal"), typeof(_PlayJournal));
                }
                
                return _PlayJournalFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct SaveJournal__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string filename;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _SaveJournal(SaveJournal__Args args);
            private static _SaveJournal _SaveJournalFunc;
            internal static _SaveJournal SaveJournal() {
                if (_SaveJournalFunc == null) {
                    _SaveJournalFunc =
                        (_SaveJournal)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnsaveJournal"), typeof(_SaveJournal));
                }
                
                return _SaveJournalFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct CloseNetPort__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _CloseNetPort(CloseNetPort__Args args);
            private static _CloseNetPort _CloseNetPortFunc;
            internal static _CloseNetPort CloseNetPort() {
                if (_CloseNetPortFunc == null) {
                    _CloseNetPortFunc =
                        (_CloseNetPort)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fncloseNetPort"), typeof(_CloseNetPort));
                }
                
                return _CloseNetPortFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct IsAddressTypeAvailable__Args
            {
                internal int addressType;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            [return: MarshalAs(UnmanagedType.I1)]
            internal delegate bool _IsAddressTypeAvailable(IsAddressTypeAvailable__Args args);
            private static _IsAddressTypeAvailable _IsAddressTypeAvailableFunc;
            internal static _IsAddressTypeAvailable IsAddressTypeAvailable() {
                if (_IsAddressTypeAvailableFunc == null) {
                    _IsAddressTypeAvailableFunc =
                        (_IsAddressTypeAvailable)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnisAddressTypeAvailable"), typeof(_IsAddressTypeAvailable));
                }
                
                return _IsAddressTypeAvailableFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct SetNetPort__Args
            {
                internal int port;
                [MarshalAs(UnmanagedType.I1)]
                internal bool bind;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            [return: MarshalAs(UnmanagedType.I1)]
            internal delegate bool _SetNetPort(SetNetPort__Args args);
            private static _SetNetPort _SetNetPortFunc;
            internal static _SetNetPort SetNetPort() {
                if (_SetNetPortFunc == null) {
                    _SetNetPortFunc =
                        (_SetNetPort)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnsetNetPort"), typeof(_SetNetPort));
                }
                
                return _SetNetPortFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct LockMouse__Args
            {
                [MarshalAs(UnmanagedType.I1)]
                internal bool isLocked;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _LockMouse(LockMouse__Args args);
            private static _LockMouse _LockMouseFunc;
            internal static _LockMouse LockMouse() {
                if (_LockMouseFunc == null) {
                    _LockMouseFunc =
                        (_LockMouse)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnlockMouse"), typeof(_LockMouse));
                }
                
                return _LockMouseFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct StrToPlayerName__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string ptr;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            
            internal delegate IntPtr _StrToPlayerName(StrToPlayerName__Args args);
            private static _StrToPlayerName _StrToPlayerNameFunc;
            internal static _StrToPlayerName StrToPlayerName() {
                if (_StrToPlayerNameFunc == null) {
                    _StrToPlayerNameFunc =
                        (_StrToPlayerName)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnstrToPlayerName"), typeof(_StrToPlayerName));
                }
                
                return _StrToPlayerNameFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct ActivateDirectInput__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _ActivateDirectInput(ActivateDirectInput__Args args);
            private static _ActivateDirectInput _ActivateDirectInputFunc;
            internal static _ActivateDirectInput ActivateDirectInput() {
                if (_ActivateDirectInputFunc == null) {
                    _ActivateDirectInputFunc =
                        (_ActivateDirectInput)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnactivateDirectInput"), typeof(_ActivateDirectInput));
                }
                
                return _ActivateDirectInputFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct DeactivateDirectInput__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _DeactivateDirectInput(DeactivateDirectInput__Args args);
            private static _DeactivateDirectInput _DeactivateDirectInputFunc;
            internal static _DeactivateDirectInput DeactivateDirectInput() {
                if (_DeactivateDirectInputFunc == null) {
                    _DeactivateDirectInputFunc =
                        (_DeactivateDirectInput)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fndeactivateDirectInput"), typeof(_DeactivateDirectInput));
                }
                
                return _DeactivateDirectInputFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct ContainsBadWords__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string text;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            [return: MarshalAs(UnmanagedType.I1)]
            internal delegate bool _ContainsBadWords(ContainsBadWords__Args args);
            private static _ContainsBadWords _ContainsBadWordsFunc;
            internal static _ContainsBadWords ContainsBadWords() {
                if (_ContainsBadWordsFunc == null) {
                    _ContainsBadWordsFunc =
                        (_ContainsBadWords)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fncontainsBadWords"), typeof(_ContainsBadWords));
                }
                
                return _ContainsBadWordsFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct FilterString__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string baseString;
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string replacementChars;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            
            internal delegate IntPtr _FilterString(FilterString__Args args);
            private static _FilterString _FilterStringFunc;
            internal static _FilterString FilterString() {
                if (_FilterStringFunc == null) {
                    _FilterStringFunc =
                        (_FilterString)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnfilterString"), typeof(_FilterString));
                }
                
                return _FilterStringFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct AddBadWord__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string badWord;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            [return: MarshalAs(UnmanagedType.I1)]
            internal delegate bool _AddBadWord(AddBadWord__Args args);
            private static _AddBadWord _AddBadWordFunc;
            internal static _AddBadWord AddBadWord() {
                if (_AddBadWordFunc == null) {
                    _AddBadWordFunc =
                        (_AddBadWord)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnaddBadWord"), typeof(_AddBadWord));
                }
                
                return _AddBadWordFunc;
            }
        }
        #endregion

        /// 
        public static void CycleResources() {
             InternalUnsafeMethods.CycleResources__Args _args = new InternalUnsafeMethods.CycleResources__Args() {
             };
             InternalUnsafeMethods.CycleResources()(_args);
        }

        /// <description>
        /// isKoreanBuild()
        /// </description>
        public static bool IsKoreanBuild() {
             InternalUnsafeMethods.IsKoreanBuild__Args _args = new InternalUnsafeMethods.IsKoreanBuild__Args() {
             };
             bool _engineResult = InternalUnsafeMethods.IsKoreanBuild()(_args);
             return _engineResult;
        }

        /// <description>
        /// ( ... )
        /// </description>
        /// <summary>Install the math library with specified extensions.</summary>
        /// <description>
        /// Possible parameters are:
        /// 
        ///     - 'DETECT' Autodetect math lib settings.
        /// 
        ///     - 'C' Enable the C math routines. C routines are always enabled.
        /// 
        ///     - 'FPU' Enable floating point unit routines.
        /// 
        ///     - 'MMX' Enable MMX math routines.
        /// 
        ///     - '3DNOW' Enable 3dNow! math routines.
        /// 
        ///     - 'SSE' Enable SSE math routines.
        /// </description>
        public static void MathInit(params string[] args) { 
            List<string> _argList = new List<string>() {""};
            _argList.AddRange(args);

            StringVector nativeVecArgs = new StringVector {
                ElementCount = (uint)_argList.Count,
                Array = _argList.ToArray(),
                ArraySize = (uint)_argList.Count
            };
            nativeVecArgs.Alloc();
            InternalUnsafeMethods.MathInit()(ref nativeVecArgs.internalStruct);
            nativeVecArgs.Free();

        }

        /// <description>
        /// (string executable, string args, string directory)
        /// </description>
        /// <summary>Launches an outside executable or batch file</summary>
        /// <description>
        /// 
        /// </description>
        /// <param name="executable">Name of the executable or batch file</param>
        /// <param name="args">Optional list of arguments, in string format, to pass to the executable</param>
        /// <param name="directory">Optional string containing path to output or shell</param>
        /// <returns>true if executed, false if not</returns>
        public static bool ShellExecute(string executable, string args = "", string directory = "") {
             InternalUnsafeMethods.ShellExecute__Args _args = new InternalUnsafeMethods.ShellExecute__Args() {
                executable = executable,
                args = args,
                directory = directory,
             };
             bool _engineResult = InternalUnsafeMethods.ShellExecute()(_args);
             return _engineResult;
        }

        /// <description>
        /// (string device, float xRumble, float yRumble)
        /// </description>
        /// <summary>Activates the vibration motors in the specified controller.</summary>
        /// <description>
        /// The controller will constantly at it's xRumble and yRumble intensities until changed or told to stop.Valid inputs for xRumble/yRumble are [0 - 1].
        /// </description>
        /// <param name="device">Name of the device to rumble.</param>
        /// <param name="xRumble">Intensity to apply to the left motor.</param>
        /// <param name="yRumble">Intensity to apply to the right motor.</param>
        /// <remarks> in an Xbox 360 controller, the left motor is low-frequency, while the right motor is high-frequency.</remarks>
        public static void Rumble(string device, float xRumble, float yRumble) {
             InternalUnsafeMethods.Rumble__Args _args = new InternalUnsafeMethods.Rumble__Args() {
                device = device,
                xRumble = xRumble,
                yRumble = yRumble,
             };
             InternalUnsafeMethods.Rumble()(_args);
        }

        /// <description>
        /// ()
        /// </description>
        /// <summary>Prints information to the console stating if DirectInput and a Joystick are enabled and active.</summary>
        /// <description>
        /// 
        /// </description>
        public static void EchoInputState() {
             InternalUnsafeMethods.EchoInputState__Args _args = new InternalUnsafeMethods.EchoInputState__Args() {
             };
             InternalUnsafeMethods.EchoInputState()(_args);
        }

        /// <description>
        /// ( int controllerID, string property, bool currentD )
        /// </description>
        /// <summary>Queries the current state of a connected Xbox 360 controller.</summary>
        /// <description>
        /// XInput Properties:
        /// 
        ///  - XI_THUMBLX, XI_THUMBLY - X and Y axes of the left thumbstick. 
        ///  - XI_THUMBRX, XI_THUMBRY - X and Y axes of the right thumbstick. 
        ///  - XI_LEFT_TRIGGER, XI_RIGHT_TRIGGER - Left and Right triggers. 
        ///  - SI_UPOV, SI_DPOV, SI_LPOV, SI_RPOV - Up, Down, Left, and Right on the directional pad.
        ///  - XI_START, XI_BACK - The Start and Back buttons.
        ///  - XI_LEFT_THUMB, XI_RIGHT_THUMB - Clicking in the left and right thumbstick.
        ///  - XI_LEFT_SHOULDER, XI_RIGHT_SHOULDER - Left and Right bumpers.
        ///  - XI_A, XI_B , XI_X, XI_Y - The A, B, X, and Y buttons.
        /// </description>
        /// <param name="controllerID">Zero-based index of the controller to return information about.</param>
        /// <param name="property">Name of input action being queried, such as "XI_THUMBLX".</param>
        /// <param name="current">True checks current device in action.</param>
        /// <returns>Button queried - 1 if the button is pressed, 0 if it's not.</returns>
        /// <returns>Thumbstick queried - Int representing displacement from rest position.</returns>
        /// <returns>%Trigger queried - Int from 0 to 255 representing how far the trigger is displaced.</returns>
        public static int GetXInputState(int controllerID, string properties, bool current = false) {
             InternalUnsafeMethods.GetXInputState__Args _args = new InternalUnsafeMethods.GetXInputState__Args() {
                controllerID = controllerID,
                properties = properties,
                current = current,
             };
             int _engineResult = InternalUnsafeMethods.GetXInputState()(_args);
             return _engineResult;
        }

        /// <description>
        /// ( int controllerID )
        /// </description>
        /// <summary>Checks to see if an Xbox 360 controller is connected</summary>
        /// <description>
        /// 
        /// </description>
        /// <param name="controllerID">Zero-based index of the controller to check.</param>
        /// <returns>1 if the controller is connected, 0 if it isn't, and 205 if XInput hasn't been initialized.</returns>
        public static bool IsXInputConnected(int controllerID) {
             InternalUnsafeMethods.IsXInputConnected__Args _args = new InternalUnsafeMethods.IsXInputConnected__Args() {
                controllerID = controllerID,
             };
             bool _engineResult = InternalUnsafeMethods.IsXInputConnected()(_args);
             return _engineResult;
        }

        /// <description>
        /// ()
        /// </description>
        /// <summary>Rebuilds the XInput section of the InputManager</summary>
        /// <description>
        /// Requests a full refresh of events for all controllers. Useful when called at the beginning of game code after actionMaps are set up to hook up all appropriate events.
        /// </description>
        public static void ResetXInput() {
             InternalUnsafeMethods.ResetXInput__Args _args = new InternalUnsafeMethods.ResetXInput__Args() {
             };
             InternalUnsafeMethods.ResetXInput()(_args);
        }

        /// <description>
        /// ()
        /// </description>
        /// <summary>Disables XInput for Xbox 360 controllers.</summary>
        /// <description>
        /// 
        /// </description>
        public static void DisableXInput() {
             InternalUnsafeMethods.DisableXInput__Args _args = new InternalUnsafeMethods.DisableXInput__Args() {
             };
             InternalUnsafeMethods.DisableXInput()(_args);
        }

        /// <description>
        /// ()
        /// </description>
        /// <summary>Enables XInput for Xbox 360 controllers.</summary>
        /// <description>
        /// 
        /// </description>
        /// <remarks> XInput is enabled by default. Disable to use an Xbox 360 Controller as a joystick device.
        /// 
        /// </remarks>
        public static bool EnableXInput() {
             InternalUnsafeMethods.EnableXInput__Args _args = new InternalUnsafeMethods.EnableXInput__Args() {
             };
             bool _engineResult = InternalUnsafeMethods.EnableXInput()(_args);
             return _engineResult;
        }

        /// <description>
        /// ()
        /// </description>
        /// <summary>Queries input manager to see if a joystick is enabled</summary>
        /// <description>
        /// 
        /// </description>
        /// <returns>1 if a joystick exists and is enabled, 0 if it's not.</returns>
        public static bool IsJoystickEnabled() {
             InternalUnsafeMethods.IsJoystickEnabled__Args _args = new InternalUnsafeMethods.IsJoystickEnabled__Args() {
             };
             bool _engineResult = InternalUnsafeMethods.IsJoystickEnabled()(_args);
             return _engineResult;
        }

        /// <description>
        /// ()
        /// </description>
        /// <summary>Disables use of the joystick.</summary>
        /// <description>
        /// 
        /// </description>
        /// <remarks> DirectInput must be enabled and active to use this function.
        /// 
        /// </remarks>
        public static void DisableJoystick() {
             InternalUnsafeMethods.DisableJoystick__Args _args = new InternalUnsafeMethods.DisableJoystick__Args() {
             };
             InternalUnsafeMethods.DisableJoystick()(_args);
        }

        /// <description>
        /// ()
        /// </description>
        /// <summary>Enables use of the joystick.</summary>
        /// <description>
        /// 
        /// </description>
        /// <remarks> DirectInput must be enabled and active to use this function.
        /// 
        /// </remarks>
        public static bool EnableJoystick() {
             InternalUnsafeMethods.EnableJoystick__Args _args = new InternalUnsafeMethods.EnableJoystick__Args() {
             };
             bool _engineResult = InternalUnsafeMethods.EnableJoystick()(_args);
             return _engineResult;
        }

        /// <description>
        /// enableWinConsole(bool);
        /// </description>
        public static void EnableWinConsole(bool flag) {
             InternalUnsafeMethods.EnableWinConsole__Args _args = new InternalUnsafeMethods.EnableWinConsole__Args() {
                flag = flag,
             };
             InternalUnsafeMethods.EnableWinConsole()(_args);
        }

        /// <description>
        /// ()
        /// </description>
        /// <summary>Initializes variables that track device and vendor information/IDs</summary>
        /// <description>
        /// 
        /// </description>
        public static void InitDisplayDeviceInfo() {
             InternalUnsafeMethods.InitDisplayDeviceInfo__Args _args = new InternalUnsafeMethods.InitDisplayDeviceInfo__Args() {
             };
             InternalUnsafeMethods.InitDisplayDeviceInfo()(_args);
        }

        /// <description>
        /// ( void )
        /// </description>
        public static int GetServerPathSet() {
             InternalUnsafeMethods.GetServerPathSet__Args _args = new InternalUnsafeMethods.GetServerPathSet__Args() {
             };
             int _engineResult = InternalUnsafeMethods.GetServerPathSet()(_args);
             return _engineResult;
        }

        /// <description>
        /// ( pDuration, pFalloff, pAmplitude, pFrequency )
        /// </description>
        public static void ShakeCamera(float duration = 0f, float falloff = 0f, Point3F amplitude = null, Point3F frequency = null) {
amplitude = amplitude ?? new Point3F("0 0 0");
amplitude.Alloc();frequency = frequency ?? new Point3F("0 0 0");
frequency.Alloc();             InternalUnsafeMethods.ShakeCamera__Args _args = new InternalUnsafeMethods.ShakeCamera__Args() {
                duration = duration,
                falloff = falloff,
                amplitude = amplitude.internalStructPtr,
                frequency = frequency.internalStructPtr,
             };
             InternalUnsafeMethods.ShakeCamera()(_args);
amplitude.Free();frequency.Free();        }

        /// <summary>Update all tiles in a given NavMesh that intersect the given object's world box.</summary>
        public static void NavMeshUpdateOne(int meshid = 0, int objid = 0, bool remove = false) {
             InternalUnsafeMethods.NavMeshUpdateOne__Args _args = new InternalUnsafeMethods.NavMeshUpdateOne__Args() {
                meshid = meshid,
                objid = objid,
                remove = remove,
             };
             InternalUnsafeMethods.NavMeshUpdateOne()(_args);
        }

        /// <summary>Flag this object as not generating a navmesh result.</summary>
        public static void NavMeshIgnore(int objid = 0, bool _ignore = true) {
             InternalUnsafeMethods.NavMeshIgnore__Args _args = new InternalUnsafeMethods.NavMeshIgnore__Args() {
                objid = objid,
                _ignore = _ignore,
             };
             InternalUnsafeMethods.NavMeshIgnore()(_args);
        }

        /// <summary>Update all NavMesh tiles that intersect the given object's world box.</summary>
        public static void NavMeshUpdateAroundObject(int objid = 0, bool remove = false) {
             InternalUnsafeMethods.NavMeshUpdateAroundObject__Args _args = new InternalUnsafeMethods.NavMeshUpdateAroundObject__Args() {
                objid = objid,
                remove = remove,
             };
             InternalUnsafeMethods.NavMeshUpdateAroundObject()(_args);
        }

        /// <summary>Update all NavMesh tiles that intersect the given object's world box.</summary>
        public static void NavMeshUpdateAll(int objid = 0, bool remove = false) {
             InternalUnsafeMethods.NavMeshUpdateAll__Args _args = new InternalUnsafeMethods.NavMeshUpdateAll__Args() {
                objid = objid,
                remove = remove,
             };
             InternalUnsafeMethods.NavMeshUpdateAll()(_args);
        }

        /// <summary>Get the EventManager object for all NavMesh updates.</summary>
        public static int GetNavMeshEventManager() {
             InternalUnsafeMethods.GetNavMeshEventManager__Args _args = new InternalUnsafeMethods.GetNavMeshEventManager__Args() {
             };
             int _engineResult = InternalUnsafeMethods.GetNavMeshEventManager()(_args);
             return _engineResult;
        }

        /// <description>
        /// (string passthru, string text...)Like error(), but first argument is returned.
        /// </description>
        public static string ErrorThru(params string[] args) { 
            List<string> _argList = new List<string>() {""};
            _argList.AddRange(args);

            StringVector nativeVecArgs = new StringVector {
                ElementCount = (uint)_argList.Count,
                Array = _argList.ToArray(),
                ArraySize = (uint)_argList.Count
            };
            nativeVecArgs.Alloc();
            IntPtr _engineResult = InternalUnsafeMethods.ErrorThru()(ref nativeVecArgs.internalStruct);
            nativeVecArgs.Free();

            return StringMarshal.IntPtrToUtf8String(_engineResult);
        }

        /// <description>
        /// (string passthru, string text...)Like warn(), but first argument is returned.
        /// </description>
        public static string WarnThru(params string[] args) { 
            List<string> _argList = new List<string>() {""};
            _argList.AddRange(args);

            StringVector nativeVecArgs = new StringVector {
                ElementCount = (uint)_argList.Count,
                Array = _argList.ToArray(),
                ArraySize = (uint)_argList.Count
            };
            nativeVecArgs.Alloc();
            IntPtr _engineResult = InternalUnsafeMethods.WarnThru()(ref nativeVecArgs.internalStruct);
            nativeVecArgs.Free();

            return StringMarshal.IntPtrToUtf8String(_engineResult);
        }

        /// <description>
        /// (string passthru, string text...)Like echo(), but first argument is returned.
        /// </description>
        public static string EchoThru(params string[] args) { 
            List<string> _argList = new List<string>() {""};
            _argList.AddRange(args);

            StringVector nativeVecArgs = new StringVector {
                ElementCount = (uint)_argList.Count,
                Array = _argList.ToArray(),
                ArraySize = (uint)_argList.Count
            };
            nativeVecArgs.Alloc();
            IntPtr _engineResult = InternalUnsafeMethods.EchoThru()(ref nativeVecArgs.internalStruct);
            nativeVecArgs.Free();

            return StringMarshal.IntPtrToUtf8String(_engineResult);
        }

        /// <description>
        /// Returns the greater of the two arguments.
        /// </description>
        public static float GetMaxF(float a, float b) {
             InternalUnsafeMethods.GetMaxF__Args _args = new InternalUnsafeMethods.GetMaxF__Args() {
                a = a,
                b = b,
             };
             float _engineResult = InternalUnsafeMethods.GetMaxF()(_args);
             return _engineResult;
        }

        /// <description>
        /// Returns the lesser of the two arguments.
        /// </description>
        public static float GetMinF(float a, float b) {
             InternalUnsafeMethods.GetMinF__Args _args = new InternalUnsafeMethods.GetMinF__Args() {
                a = a,
                b = b,
             };
             float _engineResult = InternalUnsafeMethods.GetMinF()(_args);
             return _engineResult;
        }

        /// <description>
        /// Returns color scaled by scalar (color*scalar).
        /// </description>
        /// <param name="color">The color to be scaled.</param>
        /// <param name="scalar">The amount to scale the color.</param>
        public static string ColorScale(LinearColorF color, float scalar) {
color.Alloc();             InternalUnsafeMethods.ColorScale__Args _args = new InternalUnsafeMethods.ColorScale__Args() {
                color = color.internalStructPtr,
                scalar = scalar,
             };
             IntPtr _engineResult = InternalUnsafeMethods.ColorScale()(_args);
color.Free();             return StringMarshal.IntPtrToUtf8String(_engineResult);
        }

        /// <description>
        /// Coverts an HSV formatted color into an RBG color.
        /// </description>
        /// <param name="hue">The hue of the color (0-360).</param>
        /// <param name="sat">The saturation of the color (0-1).</param>
        /// <param name="val">The value of the color (0-1).</param>
        /// <param name="alpha">The alpha of the color (0-1).</param>
        public static string GetColorFromHSV(float hue = 0f, float sat = 0f, float val = 1f, float alpha = 1f) {
             InternalUnsafeMethods.GetColorFromHSV__Args _args = new InternalUnsafeMethods.GetColorFromHSV__Args() {
                hue = hue,
                sat = sat,
                val = val,
                alpha = alpha,
             };
             IntPtr _engineResult = InternalUnsafeMethods.GetColorFromHSV()(_args);
             return StringMarshal.IntPtrToUtf8String(_engineResult);
        }

        /// <summary>Returns true if script compiler had a syntax error. Useful for detecting syntax errors after reloading a script.</summary>
        /// <description>
        /// 
        /// </description>
        public static bool WasSyntaxError() {
             InternalUnsafeMethods.WasSyntaxError__Args _args = new InternalUnsafeMethods.WasSyntaxError__Args() {
             };
             bool _engineResult = InternalUnsafeMethods.WasSyntaxError()(_args);
             return _engineResult;
        }

        /// <summary>Called after a series of datablocks are reloaded to trigger some important actions on the reloaded datablocks.</summary>
        /// <description>
        /// 
        /// </description>
        public static void TouchDataBlocks() {
             InternalUnsafeMethods.TouchDataBlocks__Args _args = new InternalUnsafeMethods.TouchDataBlocks__Args() {
             };
             InternalUnsafeMethods.TouchDataBlocks()(_args);
        }

        /// <summary>Called before a series of datablocks are reloaded to help distinguish reloaded datablocks from already loaded ones.</summary>
        /// <description>
        /// 
        /// </description>
        public static void MarkDataBlocks() {
             InternalUnsafeMethods.MarkDataBlocks__Args _args = new InternalUnsafeMethods.MarkDataBlocks__Args() {
             };
             InternalUnsafeMethods.MarkDataBlocks()(_args);
        }

        /// <summary>Returns the current location of the free target.</summary>
        /// <description>
        /// 
        /// </description>
        public static Point3F GetFreeTargetPosition() {
             InternalUnsafeMethods.GetFreeTargetPosition__Args _args = new InternalUnsafeMethods.GetFreeTargetPosition__Args() {
             };
             Point3F.InternalStruct _engineResult = InternalUnsafeMethods.GetFreeTargetPosition()(_args);
             return new Point3F(_engineResult);
        }

        /// <summary>Move the transform to the new relative position.</summary>
        /// <description>
        /// 
        /// </description>
        public static MatrixF MoveTransformRel(MatrixF xfrm, Point3F pos) {
xfrm.Alloc();pos.Alloc();             InternalUnsafeMethods.MoveTransformRel__Args _args = new InternalUnsafeMethods.MoveTransformRel__Args() {
                xfrm = xfrm.internalStructPtr,
                pos = pos.internalStructPtr,
             };
             MatrixF.InternalStruct _engineResult = InternalUnsafeMethods.MoveTransformRel()(_args);
xfrm.Free();pos.Free();             return new MatrixF(_engineResult);
        }

        /// <summary>Move the transform to the new absolute position.</summary>
        /// <description>
        /// 
        /// </description>
        public static MatrixF MoveTransformAbs(MatrixF xfrm, Point3F pos) {
xfrm.Alloc();pos.Alloc();             InternalUnsafeMethods.MoveTransformAbs__Args _args = new InternalUnsafeMethods.MoveTransformAbs__Args() {
                xfrm = xfrm.internalStructPtr,
                pos = pos.internalStructPtr,
             };
             MatrixF.InternalStruct _engineResult = InternalUnsafeMethods.MoveTransformAbs()(_args);
xfrm.Free();pos.Free();             return new MatrixF(_engineResult);
        }

        /// <summary>Multiply the vector by the affine inverse of the transform.</summary>
        /// <description>
        /// 
        /// </description>
        public static Point3F MatrixInverseMulVector(MatrixF xfrm, Point3F vector) {
xfrm.Alloc();vector.Alloc();             InternalUnsafeMethods.MatrixInverseMulVector__Args _args = new InternalUnsafeMethods.MatrixInverseMulVector__Args() {
                xfrm = xfrm.internalStructPtr,
                vector = vector.internalStructPtr,
             };
             Point3F.InternalStruct _engineResult = InternalUnsafeMethods.MatrixInverseMulVector()(_args);
xfrm.Free();vector.Free();             return new Point3F(_engineResult);
        }

        /// <description>
        /// Get a random direction vector.
        /// </description>
        public static Point3F GetRandomDir(Point3F axis = null, float thetaMin = 0f, float thetaMax = 180f, float phiMin = 0f, float phiMax = 360f) {
axis = axis ?? new Point3F("0 0 0");
axis.Alloc();             InternalUnsafeMethods.GetRandomDir__Args _args = new InternalUnsafeMethods.GetRandomDir__Args() {
                axis = axis.internalStructPtr,
                thetaMin = thetaMin,
                thetaMax = thetaMax,
                phiMin = phiMin,
                phiMax = phiMax,
             };
             Point3F.InternalStruct _engineResult = InternalUnsafeMethods.GetRandomDir()(_args);
axis.Free();             return new Point3F(_engineResult);
        }

        /// <description>
        /// Get a random float number between a and b.
        /// </description>
        public static float GetRandomF(float a = 3.40282e+38f, float b = 3.40282e+38f) {
             InternalUnsafeMethods.GetRandomF__Args _args = new InternalUnsafeMethods.GetRandomF__Args() {
                a = a,
                b = b,
             };
             float _engineResult = InternalUnsafeMethods.GetRandomF()(_args);
             return _engineResult;
        }

        /// <description>
        /// Performs a raycast from points start to end and returns the ID of nearest intersecting object with a type found in the specified mask. Returns -1 if no object is found.
        /// </description>
        public static int RolloverRayCast(Point3F start, Point3F end, uint mask) {
start.Alloc();end.Alloc();             InternalUnsafeMethods.RolloverRayCast__Args _args = new InternalUnsafeMethods.RolloverRayCast__Args() {
                start = start.internalStructPtr,
                end = end.internalStructPtr,
                mask = mask,
             };
             int _engineResult = InternalUnsafeMethods.RolloverRayCast()(_args);
start.Free();end.Free();             return _engineResult;
        }

        /// <description>
        /// ...
        /// </description>
        public static string AfxGetEngine() {
             InternalUnsafeMethods.AfxGetEngine__Args _args = new InternalUnsafeMethods.AfxGetEngine__Args() {
             };
             IntPtr _engineResult = InternalUnsafeMethods.AfxGetEngine()(_args);
             return StringMarshal.IntPtrToUtf8String(_engineResult);
        }

        /// <description>
        /// ...
        /// </description>
        public static string AfxGetVersion() {
             InternalUnsafeMethods.AfxGetVersion__Args _args = new InternalUnsafeMethods.AfxGetVersion__Args() {
             };
             IntPtr _engineResult = InternalUnsafeMethods.AfxGetVersion()(_args);
             return StringMarshal.IntPtrToUtf8String(_engineResult);
        }

        /// <description>
        /// ...
        /// </description>
        public static void AfxEndMissionNotify() {
             InternalUnsafeMethods.AfxEndMissionNotify__Args _args = new InternalUnsafeMethods.AfxEndMissionNotify__Args() {
             };
             InternalUnsafeMethods.AfxEndMissionNotify()(_args);
        }

        /// <description>
        /// Instantiates a selectron.
        /// </description>
        public static int StartSelectron(SceneObject selectedObj = null, uint subcode = 0, SimObject extra = null) {
             InternalUnsafeMethods.StartSelectron__Args _args = new InternalUnsafeMethods.StartSelectron__Args() {
                selectedObj = selectedObj.ObjectPtr,
                subcode = subcode,
                extra = extra.ObjectPtr,
             };
             int _engineResult = InternalUnsafeMethods.StartSelectron()(_args);
             return _engineResult;
        }

        /// <description>
        /// Instantiates the magic spell defined by datablock and cast by caster.
        /// </description>
        public static int CastSpell(afxMagicSpellData datablock = null, ShapeBase caster = null, SceneObject target = null, SimObject extra = null) {
             InternalUnsafeMethods.CastSpell__Args _args = new InternalUnsafeMethods.CastSpell__Args() {
                datablock = datablock.ObjectPtr,
                caster = caster.ObjectPtr,
                target = target.ObjectPtr,
                extra = extra.ObjectPtr,
             };
             int _engineResult = InternalUnsafeMethods.CastSpell()(_args);
             return _engineResult;
        }

        /// <description>
        /// Called to display a screen message.
        /// </description>
        public static void DisplayScreenMessage(GameConnection client, string message) {
             InternalUnsafeMethods.DisplayScreenMessage__Args _args = new InternalUnsafeMethods.DisplayScreenMessage__Args() {
                client = client.ObjectPtr,
                message = message,
             };
             InternalUnsafeMethods.DisplayScreenMessage()(_args);
        }

        /// <description>
        /// A callout called on clients by spells when the casting stage ends.
        /// </description>
        public static void OnCastingEnd() {
             InternalUnsafeMethods.OnCastingEnd__Args _args = new InternalUnsafeMethods.OnCastingEnd__Args() {
             };
             InternalUnsafeMethods.OnCastingEnd()(_args);
        }

        /// <description>
        /// A callout called periodically on clients by spells to indicate casting progress.
        /// </description>
        public static void OnCastingProgressUpdate(float frac) {
             InternalUnsafeMethods.OnCastingProgressUpdate__Args _args = new InternalUnsafeMethods.OnCastingProgressUpdate__Args() {
                frac = frac,
             };
             InternalUnsafeMethods.OnCastingProgressUpdate()(_args);
        }

        /// <description>
        /// A callout called on clients by spells when the casting stage begins.
        /// </description>
        public static void OnCastingStart() {
             InternalUnsafeMethods.OnCastingStart__Args _args = new InternalUnsafeMethods.OnCastingStart__Args() {
             };
             InternalUnsafeMethods.OnCastingStart()(_args);
        }

        /// <description>
        /// Instantiates the effectron defined by datablock.
        /// </description>
        public static int StartEffectron(afxEffectronData datablock = null, string constraintSource = "", string constraintName = "", SimObject extra = null) {
             InternalUnsafeMethods.StartEffectron__Args _args = new InternalUnsafeMethods.StartEffectron__Args() {
                datablock = datablock.ObjectPtr,
                constraintSource = constraintSource,
                constraintName = constraintName,
                extra = extra.ObjectPtr,
             };
             int _engineResult = InternalUnsafeMethods.StartEffectron()(_args);
             return _engineResult;
        }

        /// <description>
        /// Callback that occurs when an input device is disconnected from the system.
        /// </description>
        /// <param name="sdlIndex">The index of the device that was removed.</param>
        public static void OnSDLDeviceDisconnected(int sdlIndex) {
             InternalUnsafeMethods.OnSDLDeviceDisconnected__Args _args = new InternalUnsafeMethods.OnSDLDeviceDisconnected__Args() {
                sdlIndex = sdlIndex,
             };
             InternalUnsafeMethods.OnSDLDeviceDisconnected()(_args);
        }

        /// <description>
        /// Callback that occurs when an input device is connected to the system.
        /// </description>
        /// <param name="sdlIndex">The index that will be used by sdl to refer to the device.</param>
        /// <param name="deviceName">The name that the device reports. This will be the return value of SDL_JoystickNameForIndex or SDL_GameControllerNameForIndex depending on the device type.</param>
        /// <param name="deviceType">The type of device connected. See SDLInputManager::getDeviceType() for possible string values.</param>
        public static void OnSDLDeviceConnected(int sdlIndex, string deviceName, string deviceType) {
             InternalUnsafeMethods.OnSDLDeviceConnected__Args _args = new InternalUnsafeMethods.OnSDLDeviceConnected__Args() {
                sdlIndex = sdlIndex,
                deviceName = deviceName,
                deviceType = deviceType,
             };
             InternalUnsafeMethods.OnSDLDeviceConnected()(_args);
        }

        /// 
        public static string SetShadowVizLight(string name = "") {
             InternalUnsafeMethods.SetShadowVizLight__Args _args = new InternalUnsafeMethods.SetShadowVizLight__Args() {
                name = name,
             };
             IntPtr _engineResult = InternalUnsafeMethods.SetShadowVizLight()(_args);
             return StringMarshal.IntPtrToUtf8String(_engineResult);
        }

        /// 
        public static bool IsSupportedFormat(string extension) {
             InternalUnsafeMethods.IsSupportedFormat__Args _args = new InternalUnsafeMethods.IsSupportedFormat__Args() {
                extension = extension,
             };
             bool _engineResult = InternalUnsafeMethods.IsSupportedFormat()(_args);
             return _engineResult;
        }

        /// <description>
        /// Returns a list of supported shape formats in filter form.
        /// Example output: DSQ Files|*.dsq|COLLADA Files|*.dae|
        /// </description>
        public static string GetFormatFilters() {
             InternalUnsafeMethods.GetFormatFilters__Args _args = new InternalUnsafeMethods.GetFormatFilters__Args() {
             };
             IntPtr _engineResult = InternalUnsafeMethods.GetFormatFilters()(_args);
             return StringMarshal.IntPtrToUtf8String(_engineResult);
        }

        /// <description>
        /// Returns a list of supported shape format extensions separated by tabs.Example output: *.dsq TAB *.dae TAB
        /// </description>
        public static string GetFormatExtensions() {
             InternalUnsafeMethods.GetFormatExtensions__Args _args = new InternalUnsafeMethods.GetFormatExtensions__Args() {
             };
             IntPtr _engineResult = InternalUnsafeMethods.GetFormatExtensions()(_args);
             return StringMarshal.IntPtrToUtf8String(_engineResult);
        }

        /// <description>
        /// (string shapePath, GuiTreeViewCtrl ctrl) Collect scene information from a shape file and store it in a GuiTreeView control. This function is used by the assimp import gui to show a preview of the scene contents prior to import, and is probably not much use for anything else.
        /// </description>
        /// <param name="shapePath">shape filename</param>
        /// <param name="ctrl">GuiTreeView control to add elements to</param>
        /// <returns>true if successful, false otherwise</returns>
        public static bool GetShapeInfo(string shapePath = "", string ctrl = "", bool loadCachedDts = true) {
             InternalUnsafeMethods.GetShapeInfo__Args _args = new InternalUnsafeMethods.GetShapeInfo__Args() {
                shapePath = shapePath,
                ctrl = ctrl,
                loadCachedDts = loadCachedDts,
             };
             bool _engineResult = InternalUnsafeMethods.GetShapeInfo()(_args);
             return _engineResult;
        }

        /// <description>
        /// (string filename, SimGroup parentGroup=Scene, SimObject baseObject=-1)Load all light instances from a COLLADA (.dae) file and add to the scene.
        /// </description>
        /// <param name="filename">COLLADA filename to load lights from</param>
        /// <param name="parentGroup">(optional) name of an existing simgroup to add the new lights to (defaults to root Scene)</param>
        /// <param name="baseObject">(optional) name of an object to use as the origin (useful if you are loading the lights for a collada scene and have moved or rotated the geometry)</param>
        /// <returns>true if successful, false otherwise</returns>
        /// <code>
        /// // load the lights in room.dae
        /// loadColladaLights( "art/shapes/collada/room.dae" );
        /// 
        /// // load the lights in room.dae and add them to the RoomLights group
        /// loadColladaLights( "art/shapes/collada/room.dae", "RoomLights" );
        /// 
        /// // load the lights in room.dae and use the transform of the "Room"
        /// object as the origin
        /// loadColladaLights( "art/shapes/collada/room.dae", "", "Room" );
        /// </code>
        /// <remarks> Currently for editor use only
        /// </remarks>
        public static bool LoadColladaLights(string filename, string parentGroup = "", string baseObject = "") {
             InternalUnsafeMethods.LoadColladaLights__Args _args = new InternalUnsafeMethods.LoadColladaLights__Args() {
                filename = filename,
                parentGroup = parentGroup,
                baseObject = baseObject,
             };
             bool _engineResult = InternalUnsafeMethods.LoadColladaLights()(_args);
             return _engineResult;
        }

        /// <description>
        /// (string shapePath, GuiTreeViewCtrl ctrl) Collect scene information from a COLLADA file and store it in a GuiTreeView control. This function is used by the COLLADA import gui to show a preview of the scene contents prior to import, and is probably not much use for anything else.
        /// </description>
        /// <param name="shapePath">COLLADA filename</param>
        /// <param name="ctrl">GuiTreeView control to add elements to</param>
        /// <param name="loadCachedDts">dictates if it should try and load the cached dts file if it exists</param>
        /// <returns>true if successful, false otherwise</returns>
        public static bool EnumColladaForImport(string shapePath = "", string ctrl = "", bool loadCachedDts = true) {
             InternalUnsafeMethods.EnumColladaForImport__Args _args = new InternalUnsafeMethods.EnumColladaForImport__Args() {
                shapePath = shapePath,
                ctrl = ctrl,
                loadCachedDts = loadCachedDts,
             };
             bool _engineResult = InternalUnsafeMethods.EnumColladaForImport()(_args);
             return _engineResult;
        }

        /// <description>
        /// () - Generate a TAML schema file of all engine types.
        /// The schema file is specified using the console variable '$pref::T2D::TAMLSchema'.
        /// </description>
        /// <returns>Whether the schema file was writtent or not.</returns>
        public static bool GenerateTamlSchema() {
             InternalUnsafeMethods.GenerateTamlSchema__Args _args = new InternalUnsafeMethods.GenerateTamlSchema__Args() {
             };
             bool _engineResult = InternalUnsafeMethods.GenerateTamlSchema()(_args);
             return _engineResult;
        }

        /// <description>
        /// (filename, [format]) - Read an object from a file using Taml.
        /// </description>
        /// <param name="filename">The filename to read from.</param>
        /// <param name="format">The file format to use.  Optional: Defaults to 'xml'.  Can be set to 'binary'.</param>
        /// <returns>(Object) The object read from the file or an empty string if read failed.</returns>
        public static string TamlRead(string filename, string format = "xml") {
             InternalUnsafeMethods.TamlRead__Args _args = new InternalUnsafeMethods.TamlRead__Args() {
                filename = filename,
                format = format,
             };
             IntPtr _engineResult = InternalUnsafeMethods.TamlRead()(_args);
             return StringMarshal.IntPtrToUtf8String(_engineResult);
        }

        /// <description>
        /// (object, filename, [format], [compressed]) - Writes an object to a file using Taml.
        /// </description>
        /// <param name="object">The object to write.</param>
        /// <param name="filename">The filename to write to.</param>
        /// <param name="format">The file format to use.  Optional: Defaults to 'xml'.  Can be set to 'binary'.</param>
        /// <param name="compressed">Whether ZIP compression is used on binary formatting or not.  Optional: Defaults to 'true'.</param>
        /// <returns>Whether the write was successful or not.</returns>
        public static bool TamlWrite(SimObject simObject, string filename, string format = "xml", bool compressed = true) {
             InternalUnsafeMethods.TamlWrite__Args _args = new InternalUnsafeMethods.TamlWrite__Args() {
                simObject = simObject.ObjectPtr,
                filename = filename,
                format = format,
                compressed = compressed,
             };
             bool _engineResult = InternalUnsafeMethods.TamlWrite()(_args);
             return _engineResult;
        }

        /// <description>
        /// Dumps all ProcessObjects in ServerProcessList and ClientProcessList to the console.
        /// </description>
        public static void DumpProcessList() {
             InternalUnsafeMethods.DumpProcessList__Args _args = new InternalUnsafeMethods.DumpProcessList__Args() {
             };
             InternalUnsafeMethods.DumpProcessList()(_args);
        }

        /// 
        public static void SetDatablockCacheCRC(uint crc) {
             InternalUnsafeMethods.SetDatablockCacheCRC__Args _args = new InternalUnsafeMethods.SetDatablockCacheCRC__Args() {
                crc = crc,
             };
             InternalUnsafeMethods.SetDatablockCacheCRC()(_args);
        }

        /// 
        public static int ExtractDatablockCacheCRC(string fileName) {
             InternalUnsafeMethods.ExtractDatablockCacheCRC__Args _args = new InternalUnsafeMethods.ExtractDatablockCacheCRC__Args() {
                fileName = fileName,
             };
             int _engineResult = InternalUnsafeMethods.ExtractDatablockCacheCRC()(_args);
             return _engineResult;
        }

        /// 
        public static int GetDatablockCacheCRC() {
             InternalUnsafeMethods.GetDatablockCacheCRC__Args _args = new InternalUnsafeMethods.GetDatablockCacheCRC__Args() {
             };
             int _engineResult = InternalUnsafeMethods.GetDatablockCacheCRC()(_args);
             return _engineResult;
        }

        /// 
        public static bool IsDatablockCacheSaved() {
             InternalUnsafeMethods.IsDatablockCacheSaved__Args _args = new InternalUnsafeMethods.IsDatablockCacheSaved__Args() {
             };
             bool _engineResult = InternalUnsafeMethods.IsDatablockCacheSaved()(_args);
             return _engineResult;
        }

        /// 
        public static void ResetDatablockCache() {
             InternalUnsafeMethods.ResetDatablockCache__Args _args = new InternalUnsafeMethods.ResetDatablockCache__Args() {
             };
             InternalUnsafeMethods.ResetDatablockCache()(_args);
        }

        /// <summary>Called on the client each time a datablock has been received.</summary>
        /// <description>
        /// This callback is typically used to notify the player of how far along in the datablock download process they are.
        /// </description>
        /// <param name="index">The index of the datablock just received.</param>
        /// <param name="total">The total number of datablocks to be received.</param>
        /// <see cref="GameConnection, GameConnection::transmitDataBlocks(), GameConnection::onDataBlocksDone()" />
        public static void OnDataBlockObjectReceived(uint index, uint total) {
             InternalUnsafeMethods.OnDataBlockObjectReceived__Args _args = new InternalUnsafeMethods.OnDataBlockObjectReceived__Args() {
                index = index,
                total = total,
             };
             InternalUnsafeMethods.OnDataBlockObjectReceived()(_args);
        }

        /// <description>
        /// Edit specified decal of the decal manager.
        /// </description>
        /// <param name="decalID">ID of the decal to edit.</param>
        /// <param name="pos">World position for the decal.</param>
        /// <param name="normal">Decal normal vector (if the decal was a tire lying flat on a surface, this is the vector pointing in the direction of the axle).</param>
        /// <param name="rotAroundNormal">Angle (in radians) to rotate this decal around its normal vector.</param>
        /// <param name="decalScale">Scale factor applied to the decal.</param>
        /// <returns>Returns true if successful, false if decalID not found.</returns>
        public static bool DecalManagerEditDecal(int decalID, Point3F pos, Point3F normal, float rotAroundNormal, float decalScale) {
pos.Alloc();normal.Alloc();             InternalUnsafeMethods.DecalManagerEditDecal__Args _args = new InternalUnsafeMethods.DecalManagerEditDecal__Args() {
                decalID = decalID,
                pos = pos.internalStructPtr,
                normal = normal.internalStructPtr,
                rotAroundNormal = rotAroundNormal,
                decalScale = decalScale,
             };
             bool _engineResult = InternalUnsafeMethods.DecalManagerEditDecal()(_args);
pos.Free();normal.Free();             return _engineResult;
        }

        /// <description>
        /// Remove specified decal from the scene.
        /// </description>
        /// <param name="decalID">ID of the decal to remove.</param>
        /// <returns>Returns true if successful, false if decal ID not found.</returns>
        /// <code>
        /// // Specify a decal ID to be removed
        /// %decalID = 1;
        /// 
        /// // Tell the decal manager to remove the specified decal ID.
        /// decalManagerRemoveDecal( %decalId )
        /// </code>
        public static bool DecalManagerRemoveDecal(int decalID) {
             InternalUnsafeMethods.DecalManagerRemoveDecal__Args _args = new InternalUnsafeMethods.DecalManagerRemoveDecal__Args() {
                decalID = decalID,
             };
             bool _engineResult = InternalUnsafeMethods.DecalManagerRemoveDecal()(_args);
             return _engineResult;
        }

        /// <description>
        /// Adds a new decal to the decal manager.
        /// </description>
        /// <param name="position">World position for the decal.</param>
        /// <param name="normal">Decal normal vector (if the decal was a tire lying flat on a surface, this is the vector pointing in the direction of the axle).</param>
        /// <param name="rot">Angle (in radians) to rotate this decal around its normal vector.</param>
        /// <param name="scale">Scale factor applied to the decal.</param>
        /// <param name="decalData">DecalData datablock to use for the new decal.</param>
        /// <param name="isImmortal">Whether or not this decal is immortal. If immortal, it does not expire automatically and must be removed explicitly.</param>
        /// <returns>Returns the ID of the new Decal object or -1 on failure.</returns>
        /// <code>
        /// // Specify the decal position
        /// %position = "1.0 1.0 1.0";
        /// 
        /// // Specify the up vector
        /// %normal = "0.0 0.0 1.0";
        /// 
        /// // Add the new decal.
        /// %decalObj = decalManagerAddDecal( %position, %normal, 0.5, 0.35, ScorchBigDecal, false );
        /// </code>
        public static int DecalManagerAddDecal(Point3F position, Point3F normal, float rot, float scale, DecalData decalData, bool isImmortal = false) {
position.Alloc();normal.Alloc();             InternalUnsafeMethods.DecalManagerAddDecal__Args _args = new InternalUnsafeMethods.DecalManagerAddDecal__Args() {
                position = position.internalStructPtr,
                normal = normal.internalStructPtr,
                rot = rot,
                scale = scale,
                decalData = decalData.ObjectPtr,
                isImmortal = isImmortal,
             };
             int _engineResult = InternalUnsafeMethods.DecalManagerAddDecal()(_args);
position.Free();normal.Free();             return _engineResult;
        }

        /// <description>
        /// Removes all decals currently loaded in the decal manager.
        /// </description>
        /// <code>
        /// // Tell the decal manager to remove all existing decals.
        /// decalManagerClear();
        /// </code>
        public static void DecalManagerClear() {
             InternalUnsafeMethods.DecalManagerClear__Args _args = new InternalUnsafeMethods.DecalManagerClear__Args() {
             };
             InternalUnsafeMethods.DecalManagerClear()(_args);
        }

        /// <description>
        /// Returns whether the decal manager has unsaved modifications.
        /// </description>
        /// <returns>True if the decal manager has unsaved modifications, false if everything has been saved.</returns>
        /// <code>
        /// // Ask the decal manager if it has unsaved modifications.
        /// %hasUnsavedModifications = decalManagerDirty();
        /// </code>
        public static bool DecalManagerDirty() {
             InternalUnsafeMethods.DecalManagerDirty__Args _args = new InternalUnsafeMethods.DecalManagerDirty__Args() {
             };
             bool _engineResult = InternalUnsafeMethods.DecalManagerDirty()(_args);
             return _engineResult;
        }

        /// <description>
        /// Clears existing decals and replaces them with decals loaded from the specified file.
        /// </description>
        /// <param name="fileName">Filename to load the decals from.</param>
        /// <returns>True if the decal manager was able to load the requested file, false if it could not.</returns>
        /// <code>
        /// // Set the filename to load the decals from.
        /// %fileName = "./missionDecals.mis.decals";
        /// // Inform the decal manager to load the decals from the entered filename.
        /// decalManagerLoad( %fileName );
        /// </code>
        public static bool DecalManagerLoad(string fileName) {
             InternalUnsafeMethods.DecalManagerLoad__Args _args = new InternalUnsafeMethods.DecalManagerLoad__Args() {
                fileName = fileName,
             };
             bool _engineResult = InternalUnsafeMethods.DecalManagerLoad()(_args);
             return _engineResult;
        }

        /// <description>
        /// Saves the decals for the active mission in the entered filename.
        /// </description>
        /// <param name="decalSaveFile">Filename to save the decals to.</param>
        /// <code>
        /// // Set the filename to save the decals in. If no filename is set, then the
        /// // decals will default to <activeMissionName>.mis.decals
        /// %fileName = "./missionDecals.mis.decals";
        /// // Inform the decal manager to save the decals for the active mission.
        /// decalManagerSave( %fileName );
        /// </code>
        public static void DecalManagerSave(string decalSaveFile = "") {
             InternalUnsafeMethods.DecalManagerSave__Args _args = new InternalUnsafeMethods.DecalManagerSave__Args() {
                decalSaveFile = decalSaveFile,
             };
             InternalUnsafeMethods.DecalManagerSave()(_args);
        }

        /// <description>
        /// physicsDebugDraw( bool enable )
        /// </description>
        public static void PhysicsDebugDraw(bool enable) {
             InternalUnsafeMethods.PhysicsDebugDraw__Args _args = new InternalUnsafeMethods.PhysicsDebugDraw__Args() {
                enable = enable,
             };
             InternalUnsafeMethods.PhysicsDebugDraw()(_args);
        }

        /// <description>
        /// physicsRestoreState()
        /// </description>
        public static void PhysicsRestoreState() {
             InternalUnsafeMethods.PhysicsRestoreState__Args _args = new InternalUnsafeMethods.PhysicsRestoreState__Args() {
             };
             InternalUnsafeMethods.PhysicsRestoreState()(_args);
        }

        /// <description>
        /// physicsStoreState()
        /// </description>
        public static void PhysicsStoreState() {
             InternalUnsafeMethods.PhysicsStoreState__Args _args = new InternalUnsafeMethods.PhysicsStoreState__Args() {
             };
             InternalUnsafeMethods.PhysicsStoreState()(_args);
        }

        /// <description>
        /// physicsGetTimeScale()
        /// </description>
        public static float PhysicsGetTimeScale() {
             InternalUnsafeMethods.PhysicsGetTimeScale__Args _args = new InternalUnsafeMethods.PhysicsGetTimeScale__Args() {
             };
             float _engineResult = InternalUnsafeMethods.PhysicsGetTimeScale()(_args);
             return _engineResult;
        }

        /// <description>
        /// physicsSetTimeScale( F32 scale )
        /// </description>
        public static void PhysicsSetTimeScale(float scale) {
             InternalUnsafeMethods.PhysicsSetTimeScale__Args _args = new InternalUnsafeMethods.PhysicsSetTimeScale__Args() {
                scale = scale,
             };
             InternalUnsafeMethods.PhysicsSetTimeScale()(_args);
        }

        /// <description>
        /// physicsStopSimulation( String worldName )
        /// </description>
        public static bool PhysicsSimulationEnabled() {
             InternalUnsafeMethods.PhysicsSimulationEnabled__Args _args = new InternalUnsafeMethods.PhysicsSimulationEnabled__Args() {
             };
             bool _engineResult = InternalUnsafeMethods.PhysicsSimulationEnabled()(_args);
             return _engineResult;
        }

        /// <description>
        /// physicsStopSimulation( String worldName )
        /// </description>
        public static void PhysicsStopSimulation(string worldName) {
             InternalUnsafeMethods.PhysicsStopSimulation__Args _args = new InternalUnsafeMethods.PhysicsStopSimulation__Args() {
                worldName = worldName,
             };
             InternalUnsafeMethods.PhysicsStopSimulation()(_args);
        }

        /// <description>
        /// physicsStartSimulation( String worldName )
        /// </description>
        public static void PhysicsStartSimulation(string worldName) {
             InternalUnsafeMethods.PhysicsStartSimulation__Args _args = new InternalUnsafeMethods.PhysicsStartSimulation__Args() {
                worldName = worldName,
             };
             InternalUnsafeMethods.PhysicsStartSimulation()(_args);
        }

        /// <description>
        /// physicsDestroyWorld( String worldName )
        /// </description>
        public static void PhysicsDestroyWorld(string worldName) {
             InternalUnsafeMethods.PhysicsDestroyWorld__Args _args = new InternalUnsafeMethods.PhysicsDestroyWorld__Args() {
                worldName = worldName,
             };
             InternalUnsafeMethods.PhysicsDestroyWorld()(_args);
        }

        /// <description>
        /// physicsInitWorld( String worldName )
        /// </description>
        public static bool PhysicsInitWorld(string worldName) {
             InternalUnsafeMethods.PhysicsInitWorld__Args _args = new InternalUnsafeMethods.PhysicsInitWorld__Args() {
                worldName = worldName,
             };
             bool _engineResult = InternalUnsafeMethods.PhysicsInitWorld()(_args);
             return _engineResult;
        }

        /// <description>
        /// physicsDestroy()
        /// </description>
        public static void PhysicsDestroy() {
             InternalUnsafeMethods.PhysicsDestroy__Args _args = new InternalUnsafeMethods.PhysicsDestroy__Args() {
             };
             InternalUnsafeMethods.PhysicsDestroy()(_args);
        }

        /// <description>
        /// physicsInit( [string library] )
        /// </description>
        public static bool PhysicsInit(string library = "default") {
             InternalUnsafeMethods.PhysicsInit__Args _args = new InternalUnsafeMethods.PhysicsInit__Args() {
                library = library,
             };
             bool _engineResult = InternalUnsafeMethods.PhysicsInit()(_args);
             return _engineResult;
        }

        /// <description>
        /// physicsPluginPresent()
        /// </description>
        /// <summary>Returns true if a physics plugin exists and is initialized.</summary>
        /// <description>
        /// 
        /// </description>
        public static bool PhysicsPluginPresent() {
             InternalUnsafeMethods.PhysicsPluginPresent__Args _args = new InternalUnsafeMethods.PhysicsPluginPresent__Args() {
             };
             bool _engineResult = InternalUnsafeMethods.PhysicsPluginPresent()(_args);
             return _engineResult;
        }

        /// <description>
        /// Activates the shape replicator.
        /// </description>
        /// <code>
        /// // Call the function
        /// StartClientReplication()
        /// </code>
        public static void StartClientReplication() {
             InternalUnsafeMethods.StartClientReplication__Args _args = new InternalUnsafeMethods.StartClientReplication__Args() {
             };
             InternalUnsafeMethods.StartClientReplication()(_args);
        }

        /// <description>
        /// Activates the foliage replicator.
        /// </description>
        /// <code>
        /// // Call the function
        /// StartFoliageReplication();
        /// </code>
        public static void StartFoliageReplication() {
             InternalUnsafeMethods.StartFoliageReplication__Args _args = new InternalUnsafeMethods.StartFoliageReplication__Args() {
             };
             InternalUnsafeMethods.StartFoliageReplication()(_args);
        }

        /// <summary>Calculates how much an explosion effects a specific object.</summary>
        /// <description>
        /// Use this to determine how much damage to apply to objects based on their distance from the explosion's center point, and whether the explosion is blocked by other objects.
        /// </description>
        /// <param name="pos">Center position of the explosion.</param>
        /// <param name="id">Id of the object of which to check coverage.</param>
        /// <param name="covMask">Mask of object types that may block the explosion.</param>
        /// <returns>Coverage value from 0 (not affected by the explosion) to 1 (fully affected)</returns>
        /// <code>
        /// // Get the position of the explosion.
        /// %position = %explosion.getPosition();
        /// 
        /// // Set a list of TypeMasks (defined in gameFunctioncs.cpp), seperated by the | character.
        /// %TypeMasks = $TypeMasks::StaticObjectType | $TypeMasks::ItemObjectType
        /// 
        /// // Acquire the damage value from 0.0f - 1.0f.
        /// %coverage = calcExplosionCoverage( %position, %sceneObject, %TypeMasks );
        /// 
        /// // Apply damage to object
        /// %sceneObject.applyDamage( %coverage * 20 );
        /// </code>
        public static float CalcExplosionCoverage(Point3F pos, int id, uint covMask) {
pos.Alloc();             InternalUnsafeMethods.CalcExplosionCoverage__Args _args = new InternalUnsafeMethods.CalcExplosionCoverage__Args() {
                pos = pos.internalStructPtr,
                id = id,
                covMask = covMask,
             };
             float _engineResult = InternalUnsafeMethods.CalcExplosionCoverage()(_args);
pos.Free();             return _engineResult;
        }

        /// <description>
        /// Get the MissionArea object, if any.
        /// </description>
        public static MissionArea GetMissionAreaServerObject() {
             InternalUnsafeMethods.GetMissionAreaServerObject__Args _args = new InternalUnsafeMethods.GetMissionAreaServerObject__Args() {
             };
             IntPtr _engineResult = InternalUnsafeMethods.GetMissionAreaServerObject()(_args);
             return new MissionArea(_engineResult);
        }

        /// <summary>Prevents mouse movement from being processed</summary>
        /// <description>
        /// In the source, whenever a mouse move event occurs GameTSCtrl::onMouseMove() is called. Whenever snapToggle() is called, it will flag a variable that can prevent this from happening: gSnapLine. This variable is not exposed to script, so you need to call this function to trigger it.
        /// </description>
        /// <code>
        /// // Snapping is off by default, so we will toggle
        /// // it on first:
        /// PlayGui.snapToggle();
        /// 
        /// // Mouse movement should be disabled
        /// // Let's turn it back on
        /// PlayGui.snapToggle();
        /// </code>
        public static void SnapToggle() {
             InternalUnsafeMethods.SnapToggle__Args _args = new InternalUnsafeMethods.SnapToggle__Args() {
             };
             InternalUnsafeMethods.SnapToggle()(_args);
        }

        /// <summary>Set the FOV of the camera.</summary>
        /// <description>
        /// 
        /// </description>
        /// <param name="FOV">The camera's new FOV in degrees</param>
        public static void SetFov(float FOV) {
             InternalUnsafeMethods.SetFov__Args _args = new InternalUnsafeMethods.SetFov__Args() {
                FOV = FOV,
             };
             InternalUnsafeMethods.SetFov()(_args);
        }

        /// <summary>Set the zoom speed of the camera.</summary>
        /// <description>
        /// This affects how quickly the camera changes from one field of view to another.
        /// </description>
        /// <param name="speed">The camera's zoom speed in ms per 90deg FOV change</param>
        public static void SetZoomSpeed(int speed) {
             InternalUnsafeMethods.SetZoomSpeed__Args _args = new InternalUnsafeMethods.SetZoomSpeed__Args() {
                speed = speed,
             };
             InternalUnsafeMethods.SetZoomSpeed()(_args);
        }

        /// <summary>Set the default FOV for a camera.</summary>
        /// <description>
        /// 
        /// </description>
        /// <param name="defaultFOV">The default field of view in degrees</param>
        public static void SetDefaultFov(float defaultFOV) {
             InternalUnsafeMethods.SetDefaultFov__Args _args = new InternalUnsafeMethods.SetDefaultFov__Args() {
                defaultFOV = defaultFOV,
             };
             InternalUnsafeMethods.SetDefaultFov()(_args);
        }

        /// <description>
        /// ()
        /// </description>
        /// <summary>Get more results from a previous call to containerFindFirst().</summary>
        /// <description>
        /// 
        /// </description>
        /// <remarks> You must call containerFindFirst() to begin the search.
        /// </remarks>
        /// <returns>The next object found, or an empty string if nothing else was found.</returns>
        /// <see cref="containerFindFirst()" />
        public static string ContainerFindNext() {
             InternalUnsafeMethods.ContainerFindNext__Args _args = new InternalUnsafeMethods.ContainerFindNext__Args() {
             };
             IntPtr _engineResult = InternalUnsafeMethods.ContainerFindNext()(_args);
             return StringMarshal.IntPtrToUtf8String(_engineResult);
        }

        /// <description>
        /// (int mask, Point3F point, float x, float y, float z)
        /// </description>
        /// <summary>Find objects matching the bitmask type within a box centered at point, with extents x, y, z.</summary>
        /// <description>
        /// 
        /// </description>
        /// <returns>The first object found, or an empty string if nothing was found.  Thereafter, you can get more results using containerFindNext().</returns>
        /// <see cref="containerFindNext" />
        public static string ContainerFindFirst(uint typeMask, Point3F origin, Point3F size) {
origin.Alloc();size.Alloc();             InternalUnsafeMethods.ContainerFindFirst__Args _args = new InternalUnsafeMethods.ContainerFindFirst__Args() {
                typeMask = typeMask,
                origin = origin.internalStructPtr,
                size = size.internalStructPtr,
             };
             IntPtr _engineResult = InternalUnsafeMethods.ContainerFindFirst()(_args);
origin.Free();size.Free();             return StringMarshal.IntPtrToUtf8String(_engineResult);
        }

        /// <description>
        /// (...)
        /// </description>
        /// <summary>Creates a new AIConnection, and passes arguments to its onConnect script callback.</summary>
        /// <description>
        /// 
        /// </description>
        /// <returns>The newly created AIConnection</returns>
        /// <see cref="GameConnection for parameter information" />
        public static int AiConnect(params string[] args) { 
            List<string> _argList = new List<string>() {""};
            _argList.AddRange(args);

            StringVector nativeVecArgs = new StringVector {
                ElementCount = (uint)_argList.Count,
                Array = _argList.ToArray(),
                ArraySize = (uint)_argList.Count
            };
            nativeVecArgs.Alloc();
            int _engineResult = InternalUnsafeMethods.AiConnect()(ref nativeVecArgs.internalStruct);
            nativeVecArgs.Free();

            return _engineResult;
        }

        /// <description>
        /// 'playerName'[, 'AIClassType'] );
        /// </description>
        public static int AiAddPlayer(string name, string ns = "") {
             InternalUnsafeMethods.AiAddPlayer__Args _args = new InternalUnsafeMethods.AiAddPlayer__Args() {
                name = name,
                ns = ns,
             };
             int _engineResult = InternalUnsafeMethods.AiAddPlayer()(_args);
             return _engineResult;
        }

        /// <description>
        /// Get the root Scene object that is loaded.
        /// </description>
        /// <returns>The id of the Root Scene. Will be 0 if no root scene is loaded</returns>
        public static int GetRootScene() {
             InternalUnsafeMethods.GetRootScene__Args _args = new InternalUnsafeMethods.GetRootScene__Args() {
             };
             int _engineResult = InternalUnsafeMethods.GetRootScene()(_args);
             return _engineResult;
        }

        /// <description>
        /// Get the number of active Scene objects that are loaded.
        /// </description>
        /// <returns>The number of active scenes</returns>
        public static int GetSceneCount() {
             InternalUnsafeMethods.GetSceneCount__Args _args = new InternalUnsafeMethods.GetSceneCount__Args() {
             };
             int _engineResult = InternalUnsafeMethods.GetSceneCount()(_args);
             return _engineResult;
        }

        /// <description>
        /// Get the root Scene object that is loaded.
        /// </description>
        /// <returns>The id of the Root Scene. Will be 0 if no root scene is loaded</returns>
        public static Scene GetScene(uint sceneId = 0) {
             InternalUnsafeMethods.GetScene__Args _args = new InternalUnsafeMethods.GetScene__Args() {
                sceneId = sceneId,
             };
             IntPtr _engineResult = InternalUnsafeMethods.GetScene()(_args);
             return new Scene(_engineResult);
        }

        /// 
        public static void DumpActivePostFX() {
             InternalUnsafeMethods.DumpActivePostFX__Args _args = new InternalUnsafeMethods.DumpActivePostFX__Args() {
             };
             InternalUnsafeMethods.DumpActivePostFX()(_args);
        }

        /// <description>
        /// Creates a 64x64 normal map texture filled with noise. The texture is saved to randNormTex.png in the location of the game executable.
        /// </description>
        public static void DumpRandomNormalMap() {
             InternalUnsafeMethods.DumpRandomNormalMap__Args _args = new InternalUnsafeMethods.DumpRandomNormalMap__Args() {
             };
             InternalUnsafeMethods.DumpRandomNormalMap()(_args);
        }

        /// <description>
        /// tsUpdateImposterImages( bool forceupdate )
        /// </description>
        public static void TsUpdateImposterImages(bool forceUpdate = false) {
             InternalUnsafeMethods.TsUpdateImposterImages__Args _args = new InternalUnsafeMethods.TsUpdateImposterImages__Args() {
                forceUpdate = forceUpdate,
             };
             InternalUnsafeMethods.TsUpdateImposterImages()(_args);
        }

        /// <summary>Resizes the rendertargets of the Volumetric Fog object.</summary>
        /// <description>
        /// 
        /// </description>
        /// <param name="new_quality">new quality for the rendertargets 1 = full size, 2 = halfsize, 3 = 1/3, 4 = 1/4 ...</param>
        public static int SetFogVolumeQuality(uint new_quality) {
             InternalUnsafeMethods.SetFogVolumeQuality__Args _args = new InternalUnsafeMethods.SetFogVolumeQuality__Args() {
                new_quality = new_quality,
             };
             int _engineResult = InternalUnsafeMethods.SetFogVolumeQuality()(_args);
             return _engineResult;
        }

        /// <description>
        /// (Point3F pos) - gets the terrain height at the specified position.
        /// </description>
        /// <param name="pos">The world space point. Can be formatted as either ("x y z") or (x,y,z)</param>
        /// <remarks> This function is useful if you simply want to grab the terrain height underneath an object.
        /// </remarks>
        /// <returns>Returns the terrain height at the given point as an F32 value.</returns>
        public static float GetTerrainHeightBelowPosition(string ptOrX, string y = "", string z = "") {
             InternalUnsafeMethods.GetTerrainHeightBelowPosition__Args _args = new InternalUnsafeMethods.GetTerrainHeightBelowPosition__Args() {
                ptOrX = ptOrX,
                y = y,
                z = z,
             };
             float _engineResult = InternalUnsafeMethods.GetTerrainHeightBelowPosition()(_args);
             return _engineResult;
        }

        /// <description>
        /// (Point2 pos) - gets the terrain height at the specified position.
        /// </description>
        /// <param name="pos">The world space point, minus the z (height) value
        ///  Can be formatted as either ("x y") or (x,y)</param>
        /// <returns>Returns the terrain height at the given point as an F32 value.</returns>
        public static float GetTerrainHeight(string ptOrX, string y = "") {
             InternalUnsafeMethods.GetTerrainHeight__Args _args = new InternalUnsafeMethods.GetTerrainHeight__Args() {
                ptOrX = ptOrX,
                y = y,
             };
             float _engineResult = InternalUnsafeMethods.GetTerrainHeight()(_args);
             return _engineResult;
        }

        /// <description>
        /// (Point3F x/y/z) Gets the terrain block that is located under the given world point.
        /// </description>
        /// <param name="x/y/z">The world coordinates (floating point values) you wish to query at. These can be formatted as either a string ("x y z") or separately as (x, y, z)</param>
        /// <returns>Returns the ID of the requested terrain block (0 if not found).</returns>
        public static int GetTerrainUnderWorldPoint(string ptOrX, string y = "", string z = "") {
             InternalUnsafeMethods.GetTerrainUnderWorldPoint__Args _args = new InternalUnsafeMethods.GetTerrainUnderWorldPoint__Args() {
                ptOrX = ptOrX,
                y = y,
                z = z,
             };
             int _engineResult = InternalUnsafeMethods.GetTerrainUnderWorldPoint()(_args);
             return _engineResult;
        }

        /// <summary>Load all Path information from the mission.</summary>
        /// <description>
        /// This function is usually called from the loadMissionStage2() server-side function after the mission file has loaded.  Internally it places all Paths into the server's PathManager.  From this point the Paths are ready for transmission to the clients.
        /// </description>
        /// <code>
        /// // Inform the engine to load all Path information from the mission.
        /// pathOnMissionLoadDone();
        /// </code>
        /// <see cref="NetConnection::transmitPaths()" />
        /// <see cref="NetConnection::clearPaths()" />
        /// <see cref="Path" />
        public static void PathOnMissionLoadDone() {
             InternalUnsafeMethods.PathOnMissionLoadDone__Args _args = new InternalUnsafeMethods.PathOnMissionLoadDone__Args() {
             };
             InternalUnsafeMethods.PathOnMissionLoadDone()(_args);
        }

        /// <description>
        /// Return the SceneObject that contains the given zone.
        /// </description>
        /// <param name="zoneId">ID of zone.</param>
        /// <returns>A SceneObject or NULL if the given<paramref name="" /> zoneId is invalid.
        /// 
        /// </returns>
        /// <remarks> Only valid on the client.
        /// </remarks>
        public static SceneObject SceneGetZoneOwner(uint zoneId) {
             InternalUnsafeMethods.SceneGetZoneOwner__Args _args = new InternalUnsafeMethods.SceneGetZoneOwner__Args() {
                zoneId = zoneId,
             };
             IntPtr _engineResult = InternalUnsafeMethods.SceneGetZoneOwner()(_args);
             return new SceneObject(_engineResult);
        }

        /// <description>
        /// Dump the current zoning states of all zone spaces in the scene to the console.
        /// </description>
        /// <param name="updateFirst">If true, zoning states are brought up to date first; if false, the zoning states are dumped as is.</param>
        /// <remarks> Only valid on the client.
        /// </remarks>
        public static void SceneDumpZoneStates(bool updateFirst = true) {
             InternalUnsafeMethods.SceneDumpZoneStates__Args _args = new InternalUnsafeMethods.SceneDumpZoneStates__Args() {
                updateFirst = updateFirst,
             };
             InternalUnsafeMethods.SceneDumpZoneStates()(_args);
        }

        /// <summary>Cast a ray from start to end, checking for collision against items matching mask.</summary>
        /// <description>
        /// If pExempt is specified, then it is temporarily excluded from collision checks (For instance, you might want to exclude the player if said player was firing a weapon.)
        /// </description>
        /// <param name="start">An XYZ vector containing the tail position of the ray.</param>
        /// <param name="end">An XYZ vector containing the head position of the ray</param>
        /// <param name="mask">A bitmask corresponding to the type of objects to check for</param>
        /// <param name="pExempt">An optional ID for a single object that ignored for this raycast</param>
        /// <param name="useClientContainer">Optionally indicates the search should be within the client container.</param>
        /// <returns>A string containing either null, if nothing was struck, or these fields:
        /// <ul><li>The ID of the object that was struck.</li><li>The x, y, z position that it was struck.</li><li>The x, y, z of the normal of the face that was struck.</li><li>The distance between the start point and the position we hit.</li></ul></returns>
        public static string MaterialRayCast(Point3F start, Point3F end, uint mask, SceneObject pExempt = null, bool useClientContainer = false) {
start.Alloc();end.Alloc();             InternalUnsafeMethods.MaterialRayCast__Args _args = new InternalUnsafeMethods.MaterialRayCast__Args() {
                start = start.internalStructPtr,
                end = end.internalStructPtr,
                mask = mask,
                pExempt = pExempt.ObjectPtr,
                useClientContainer = useClientContainer,
             };
             IntPtr _engineResult = InternalUnsafeMethods.MaterialRayCast()(_args);
start.Free();end.Free();             return StringMarshal.IntPtrToUtf8String(_engineResult);
        }

        /// <summary>Cast a ray from start to end, checking for collision against items matching mask.</summary>
        /// <description>
        /// If pExempt is specified, then it is temporarily excluded from collision checks (For instance, you might want to exclude the player if said player was firing a weapon.)
        /// </description>
        /// <param name="start">An XYZ vector containing the tail position of the ray.</param>
        /// <param name="end">An XYZ vector containing the head position of the ray</param>
        /// <param name="mask">A bitmask corresponding to the type of objects to check for</param>
        /// <param name="pExempt">An optional ID for a single object that ignored for this raycast</param>
        /// <param name="useClientContainer">Optionally indicates the search should be within the client container.</param>
        /// <returns>A string containing either null, if nothing was struck, or these fields:
        /// <ul><li>The ID of the object that was struck.</li><li>The x, y, z position that it was struck.</li><li>The x, y, z of the normal of the face that was struck.</li><li>The distance between the start point and the position we hit.</li></ul></returns>
        public static string ContainerRayCast(Point3F start, Point3F end, uint mask, SceneObject pExempt = null, bool useClientContainer = false) {
start.Alloc();end.Alloc();             InternalUnsafeMethods.ContainerRayCast__Args _args = new InternalUnsafeMethods.ContainerRayCast__Args() {
                start = start.internalStructPtr,
                end = end.internalStructPtr,
                mask = mask,
                pExempt = pExempt.ObjectPtr,
                useClientContainer = useClientContainer,
             };
             IntPtr _engineResult = InternalUnsafeMethods.ContainerRayCast()(_args);
start.Free();end.Free();             return StringMarshal.IntPtrToUtf8String(_engineResult);
        }

        /// <summary>Get the distance of the closest point of the current item from the center of the current initContainerRadiusSearch.</summary>
        /// <description>
        /// 
        /// </description>
        /// <param name="useClientContainer">Optionally indicates the search should be within the client container.</param>
        /// <returns>distance from the closest point of the current object to the center of the search</returns>
        /// <see cref="containerSearchNext" />
        public static float ContainerSearchCurrRadiusDist(bool useClientContainer = false) {
             InternalUnsafeMethods.ContainerSearchCurrRadiusDist__Args _args = new InternalUnsafeMethods.ContainerSearchCurrRadiusDist__Args() {
                useClientContainer = useClientContainer,
             };
             float _engineResult = InternalUnsafeMethods.ContainerSearchCurrRadiusDist()(_args);
             return _engineResult;
        }

        /// <summary>Get distance of the center of the current item from the center of the current initContainerRadiusSearch.</summary>
        /// <description>
        /// 
        /// </description>
        /// <param name="useClientContainer">Optionally indicates the search should be within the client container.</param>
        /// <returns>distance from the center of the current object to the center of the search</returns>
        /// <see cref="containerSearchNext" />
        public static float ContainerSearchCurrDist(bool useClientContainer = false) {
             InternalUnsafeMethods.ContainerSearchCurrDist__Args _args = new InternalUnsafeMethods.ContainerSearchCurrDist__Args() {
                useClientContainer = useClientContainer,
             };
             float _engineResult = InternalUnsafeMethods.ContainerSearchCurrDist()(_args);
             return _engineResult;
        }

        /// <summary>Get next item from a search started with initContainerRadiusSearch() or initContainerTypeSearch().</summary>
        /// <description>
        /// 
        /// </description>
        /// <param name="useClientContainer">Optionally indicates the search should be within the client container.</param>
        /// <returns>the next object found in the search, or null if no more</returns>
        /// <code>
        /// // print the names of all nearby ShapeBase derived objects
        /// %position = %obj.getPosition;
        /// %radius = 20;
        /// %mask = $TypeMasks::ShapeBaseObjectType;
        /// initContainerRadiusSearch( %position, %radius, %mask );
        /// while ( (%targetObject = containerSearchNext()) != 0 )
        /// {
        ///    echo( "Found: "@ %targetObject.getName() );
        /// }
        /// 
        /// </code>
        /// <see cref="initContainerRadiusSearch()" />
        /// <see cref="initContainerTypeSearch()" />
        public static SceneObject ContainerSearchNext(bool useClientContainer = false) {
             InternalUnsafeMethods.ContainerSearchNext__Args _args = new InternalUnsafeMethods.ContainerSearchNext__Args() {
                useClientContainer = useClientContainer,
             };
             IntPtr _engineResult = InternalUnsafeMethods.ContainerSearchNext()(_args);
             return new SceneObject(_engineResult);
        }

        /// <summary>Start a search for all items of the types specified by the bitset mask.</summary>
        /// <description>
        /// 
        /// </description>
        /// <param name="mask">Bitmask of object types to include in the search</param>
        /// <param name="useClientContainer">Optionally indicates the search should be within the client container.</param>
        /// <see cref="containerSearchNext" />
        public static void InitContainerTypeSearch(uint mask, bool useClientContainer = false) {
             InternalUnsafeMethods.InitContainerTypeSearch__Args _args = new InternalUnsafeMethods.InitContainerTypeSearch__Args() {
                mask = mask,
                useClientContainer = useClientContainer,
             };
             InternalUnsafeMethods.InitContainerTypeSearch()(_args);
        }

        /// <summary>Start a search for items at the given position and within the given radius, filtering by mask.</summary>
        /// <description>
        /// 
        /// </description>
        /// <param name="pos">Center position for the search</param>
        /// <param name="radius">Search radius</param>
        /// <param name="mask">Bitmask of object types to include in the search</param>
        /// <param name="useClientContainer">Optionally indicates the search should be within the client container.</param>
        /// <see cref="containerSearchNext" />
        public static void InitContainerRadiusSearch(Point3F pos, float radius, uint mask, bool useClientContainer = false) {
pos.Alloc();             InternalUnsafeMethods.InitContainerRadiusSearch__Args _args = new InternalUnsafeMethods.InitContainerRadiusSearch__Args() {
                pos = pos.internalStructPtr,
                radius = radius,
                mask = mask,
                useClientContainer = useClientContainer,
             };
             InternalUnsafeMethods.InitContainerRadiusSearch()(_args);
pos.Free();        }

        /// <summary>See if any objects of the given types are present in box of given extent.</summary>
        /// <description>
        /// 
        /// </description>
        /// <remarks> Extent parameter is last since only one radius is often needed.  If one radius is provided, the yRadius and zRadius are assumed to be the same.  Unfortunately, if you need to use the client container, you'll need to set all of the radius parameters.  Fortunately, this function is mostly used on the server.
        /// </remarks>
        /// <param name="mask">Indicates the type of objects we are checking against.</param>
        /// <param name="center">Center of box.</param>
        /// <param name="xRadius">Search radius in the x-axis. See note above.</param>
        /// <param name="yRadius">Search radius in the y-axis. See note above.</param>
        /// <param name="zRadius">Search radius in the z-axis. See note above.</param>
        /// <param name="useClientContainer">Optionally indicates the search should be within the client container.</param>
        /// <returns>true if the box is empty, false if any object is found.</returns>
        public static bool ContainerBoxEmpty(uint mask, Point3F center, float xRadius, float yRadius = -1f, float zRadius = -1f, bool useClientContainer = false) {
center.Alloc();             InternalUnsafeMethods.ContainerBoxEmpty__Args _args = new InternalUnsafeMethods.ContainerBoxEmpty__Args() {
                mask = mask,
                center = center.internalStructPtr,
                xRadius = xRadius,
                yRadius = yRadius,
                zRadius = zRadius,
                useClientContainer = useClientContainer,
             };
             bool _engineResult = InternalUnsafeMethods.ContainerBoxEmpty()(_args);
center.Free();             return _engineResult;
        }

        /// <description>
        /// Set the reflection texture format.
        /// </description>
        public static void SetReflectFormat(GFXFormat format) {
             InternalUnsafeMethods.SetReflectFormat__Args _args = new InternalUnsafeMethods.SetReflectFormat__Args() {
                format = (int)format,
             };
             InternalUnsafeMethods.SetReflectFormat()(_args);
        }

        /// 
        public static void ClearClientPaths() {
             InternalUnsafeMethods.ClearClientPaths__Args _args = new InternalUnsafeMethods.ClearClientPaths__Args() {
             };
             InternalUnsafeMethods.ClearClientPaths()(_args);
        }

        /// 
        public static void ClearServerPaths() {
             InternalUnsafeMethods.ClearServerPaths__Args _args = new InternalUnsafeMethods.ClearServerPaths__Args() {
             };
             InternalUnsafeMethods.ClearServerPaths()(_args);
        }

        /// <description>
        /// string sShadowSystemName
        /// </description>
        public static bool SetShadowManager(string sShadowSystemName = "") {
             InternalUnsafeMethods.SetShadowManager__Args _args = new InternalUnsafeMethods.SetShadowManager__Args() {
                sShadowSystemName = sShadowSystemName,
             };
             bool _engineResult = InternalUnsafeMethods.SetShadowManager()(_args);
             return _engineResult;
        }

        /// <summary>Deactivates and then activates the currently active light manager.This causes most shaders to be regenerated and is often used when global rendering changes have occured.</summary>
        /// <description>
        /// 
        /// </description>
        public static void ResetLightManager() {
             InternalUnsafeMethods.ResetLightManager__Args _args = new InternalUnsafeMethods.ResetLightManager__Args() {
             };
             InternalUnsafeMethods.ResetLightManager()(_args);
        }

        /// <description>
        /// Returns the active light manager name.
        /// </description>
        public static string GetActiveLightManager() {
             InternalUnsafeMethods.GetActiveLightManager__Args _args = new InternalUnsafeMethods.GetActiveLightManager__Args() {
             };
             IntPtr _engineResult = InternalUnsafeMethods.GetActiveLightManager()(_args);
             return StringMarshal.IntPtrToUtf8String(_engineResult);
        }

        /// <description>
        /// Returns a tab seperated list of light manager names.
        /// </description>
        public static string GetLightManagerNames() {
             InternalUnsafeMethods.GetLightManagerNames__Args _args = new InternalUnsafeMethods.GetLightManagerNames__Args() {
             };
             IntPtr _engineResult = InternalUnsafeMethods.GetLightManagerNames()(_args);
             return StringMarshal.IntPtrToUtf8String(_engineResult);
        }

        /// <description>
        /// Will generate static lighting for the scene if supported by the active light manager.
        /// 
        /// If mode is "forceAlways", the lightmaps will be regenerated regardless of whether lighting cache files can be written to. If mode is "forceWritable", then the lightmaps will be regenerated only if the lighting cache files can be written.
        /// </description>
        /// <param name="completeCallbackFn">The name of the function to execute when the lighting is complete.</param>
        /// <param name="mode">One of "forceAlways",  "forceWritable" or "loadOnly".</param>
        /// <returns>Returns true if the scene lighting process was started.</returns>
        public static bool LightScene(string completeCallbackFn = "", string mode = "") {
             InternalUnsafeMethods.LightScene__Args _args = new InternalUnsafeMethods.LightScene__Args() {
                completeCallbackFn = completeCallbackFn,
                mode = mode,
             };
             bool _engineResult = InternalUnsafeMethods.LightScene()(_args);
             return _engineResult;
        }

        /// <description>
        /// Finds and activates the named light manager.
        /// </description>
        /// <returns>Returns true if the light manager is found and activated.</returns>
        public static bool SetLightManager(string name) {
             InternalUnsafeMethods.SetLightManager__Args _args = new InternalUnsafeMethods.SetLightManager__Args() {
                name = name,
             };
             bool _engineResult = InternalUnsafeMethods.SetLightManager()(_args);
             return _engineResult;
        }

        /// <description>
        /// A callback called by the engine when a light manager is deactivated.
        /// </description>
        /// <param name="name">The name of the light manager being deactivated.</param>
        public static void OnLightManagerDeactivate(string name) {
             InternalUnsafeMethods.OnLightManagerDeactivate__Args _args = new InternalUnsafeMethods.OnLightManagerDeactivate__Args() {
                name = name,
             };
             InternalUnsafeMethods.OnLightManagerDeactivate()(_args);
        }

        /// <description>
        /// A callback called by the engine when a light manager is activated.
        /// </description>
        /// <param name="name">The name of the light manager being activated.</param>
        public static void OnLightManagerActivate(string name) {
             InternalUnsafeMethods.OnLightManagerActivate__Args _args = new InternalUnsafeMethods.OnLightManagerActivate__Args() {
                name = name,
             };
             InternalUnsafeMethods.OnLightManagerActivate()(_args);
        }

        /// 
        public static string GetMapEntry(string texName) {
             InternalUnsafeMethods.GetMapEntry__Args _args = new InternalUnsafeMethods.GetMapEntry__Args() {
                texName = texName,
             };
             IntPtr _engineResult = InternalUnsafeMethods.GetMapEntry()(_args);
             return StringMarshal.IntPtrToUtf8String(_engineResult);
        }

        /// <summary>Dumps a formatted list of currently allocated material instances to the console.</summary>
        /// <description>
        /// 
        /// </description>
        public static void GetMaterialInstances(SimObject target = null, GuiTreeViewCtrl tree = null) {
             InternalUnsafeMethods.GetMaterialInstances__Args _args = new InternalUnsafeMethods.GetMaterialInstances__Args() {
                target = target.ObjectPtr,
                tree = tree.ObjectPtr,
             };
             InternalUnsafeMethods.GetMaterialInstances()(_args);
        }

        /// <summary>Dumps a formatted list of currently allocated material instances to the console.</summary>
        /// <description>
        /// 
        /// </description>
        public static void DumpMaterialInstances() {
             InternalUnsafeMethods.DumpMaterialInstances__Args _args = new InternalUnsafeMethods.DumpMaterialInstances__Args() {
             };
             InternalUnsafeMethods.DumpMaterialInstances()(_args);
        }

        /// <description>
        /// (string texName)
        /// </description>
        /// <summary>Returns the name of the material mapped to this texture.</summary>
        /// <description>
        /// If no materials are found, an empty string is returned.
        /// </description>
        /// <param name="texName">Name of the texture</param>
        public static string GetMaterialMapping(string texName) {
             InternalUnsafeMethods.GetMaterialMapping__Args _args = new InternalUnsafeMethods.GetMaterialMapping__Args() {
                texName = texName,
             };
             IntPtr _engineResult = InternalUnsafeMethods.GetMaterialMapping()(_args);
             return StringMarshal.IntPtrToUtf8String(_engineResult);
        }

        /// <description>
        /// (string texName, string matName)
        /// </description>
        /// <summary>Maps the given texture to the given material.</summary>
        /// <description>
        /// Generates a console warning before overwriting.
        /// 
        /// Material maps are used by terrain and interiors for triggering effects when an object moves onto a terrain block or interior surface using the associated texture.
        /// </description>
        public static void AddMaterialMapping(string texName, string matName) {
             InternalUnsafeMethods.AddMaterialMapping__Args _args = new InternalUnsafeMethods.AddMaterialMapping__Args() {
                texName = texName,
                matName = matName,
             };
             InternalUnsafeMethods.AddMaterialMapping()(_args);
        }

        /// <summary>Flushes all procedural shaders and re-initializes all active material instances.</summary>
        /// <description>
        /// 
        /// </description>
        public static void ReInitMaterials() {
             InternalUnsafeMethods.ReInitMaterials__Args _args = new InternalUnsafeMethods.ReInitMaterials__Args() {
             };
             InternalUnsafeMethods.ReInitMaterials()(_args);
        }

        /// <summary>Used to exclude/prevent all other instances using the same identifier specified</summary>
        /// <description>
        /// 
        /// </description>
        /// <remarks> Not used on OSX, Xbox, or in Win debug builds
        /// 
        /// </remarks>
        /// <param name="appIdentifier">Name of the app set up for exclusive use.</param>
        /// <returns>False if another app is running that specified the same appIdentifier</returns>
        public static bool ExcludeOtherInstance(string appIdentifer) {
             InternalUnsafeMethods.ExcludeOtherInstance__Args _args = new InternalUnsafeMethods.ExcludeOtherInstance__Args() {
                appIdentifer = appIdentifer,
             };
             bool _engineResult = InternalUnsafeMethods.ExcludeOtherInstance()(_args);
             return _engineResult;
        }

        /// <summary>Strip TorqueML control characters from the specified string, returning a 'clean' version.</summary>
        /// <description>
        /// 
        /// </description>
        /// <param name="inString">String to strip TorqueML control characters from.</param>
        /// <code>
        /// // Define the string to strip TorqueML control characters from
        /// %string = "<font:Arial:24>How Now <color:c43c12>Brown <color:000000>Cow";
        /// 
        /// // Request the stripped version of the string
        /// %strippedString = StripMLControlChars(%string);
        /// </code>
        /// <returns>Version of the inputted string with all TorqueML characters removed.</returns>
        /// <see cref="References" />
        public static string StripMLControlChars(string inString) {
             InternalUnsafeMethods.StripMLControlChars__Args _args = new InternalUnsafeMethods.StripMLControlChars__Args() {
                inString = inString,
             };
             IntPtr _engineResult = InternalUnsafeMethods.StripMLControlChars()(_args);
             return StringMarshal.IntPtrToUtf8String(_engineResult);
        }

        /// <description>
        /// Takes a screenshot with optional tiling to produce huge screenshots.
        /// </description>
        /// <param name="file">The output image file path.</param>
        /// <param name="format">Either JPEG or PNG.</param>
        /// <param name="tileCount">If greater than 1 will tile the current screen size to take a large format screenshot.</param>
        /// <param name="tileOverlap">The amount of horizontal and vertical overlap between the tiles used to remove tile edge artifacts from post effects.</param>
        public static void ScreenShot(string file, string format, uint tileCount = 1, float tileOverlap = 0f) {
             InternalUnsafeMethods.ScreenShot__Args _args = new InternalUnsafeMethods.ScreenShot__Args() {
                file = file,
                format = format,
                tileCount = tileCount,
                tileOverlap = tileOverlap,
             };
             InternalUnsafeMethods.ScreenShot()(_args);
        }

        /// <description>
        /// Returns a list of texture profiles in the format: ProfileName TextureCount TextureMB
        /// </description>
        public static string GetTextureProfileStats() {
             InternalUnsafeMethods.GetTextureProfileStats__Args _args = new InternalUnsafeMethods.GetTextureProfileStats__Args() {
             };
             IntPtr _engineResult = InternalUnsafeMethods.GetTextureProfileStats()(_args);
             return StringMarshal.IntPtrToUtf8String(_engineResult);
        }

        /// <description>
        /// Dumps a list of all active texture objects to the console.
        /// </description>
        /// <remarks> This function is only available in debug builds.
        /// </remarks>
        public static void DumpTextureObjects() {
             InternalUnsafeMethods.DumpTextureObjects__Args _args = new InternalUnsafeMethods.DumpTextureObjects__Args() {
             };
             InternalUnsafeMethods.DumpTextureObjects()(_args);
        }

        /// <description>
        /// Reload all the textures from disk.
        /// </description>
        public static void ReloadTextures() {
             InternalUnsafeMethods.ReloadTextures__Args _args = new InternalUnsafeMethods.ReloadTextures__Args() {
             };
             InternalUnsafeMethods.ReloadTextures()(_args);
        }

        /// <description>
        /// Release the unused pooled textures in texture manager freeing up video memory.
        /// </description>
        public static void CleanupTexturePool() {
             InternalUnsafeMethods.CleanupTexturePool__Args _args = new InternalUnsafeMethods.CleanupTexturePool__Args() {
             };
             InternalUnsafeMethods.CleanupTexturePool()(_args);
        }

        /// <description>
        /// Releases all textures and resurrects the texture manager.
        /// </description>
        public static void FlushTextureCache() {
             InternalUnsafeMethods.FlushTextureCache__Args _args = new InternalUnsafeMethods.FlushTextureCache__Args() {
             };
             InternalUnsafeMethods.FlushTextureCache()(_args);
        }

        /// <description>
        /// File1,file2,file3,file4,[chanels for r g b and a locations],saveAs
        /// </description>
        public static void SaveCompositeTexture(string pathR = "", string pathG = "", string pathB = "", string pathA = "", string inputKeyString = "", string saveAs = "") {
             InternalUnsafeMethods.SaveCompositeTexture__Args _args = new InternalUnsafeMethods.SaveCompositeTexture__Args() {
                pathR = pathR,
                pathG = pathG,
                pathB = pathB,
                pathA = pathA,
                inputKeyString = inputKeyString,
                saveAs = saveAs,
             };
             InternalUnsafeMethods.SaveCompositeTexture()(_args);
        }

        /// <description>
        /// Removes an existing global macro by name.
        /// </description>
        /// <see cref="addGlobalShaderMacro" />
        public static void RemoveGlobalShaderMacro(string name) {
             InternalUnsafeMethods.RemoveGlobalShaderMacro__Args _args = new InternalUnsafeMethods.RemoveGlobalShaderMacro__Args() {
                name = name,
             };
             InternalUnsafeMethods.RemoveGlobalShaderMacro()(_args);
        }

        /// <description>
        /// Adds a global shader macro which will be merged with the script defined macros on every shader.  The macro will replace the value of an existing macro of the same name.  For the new macro to take effect all the shaders in the system need to be reloaded.
        /// </description>
        /// <see cref="resetLightManager, removeGlobalShaderMacro" />
        public static void AddGlobalShaderMacro(string name, string value = "") {
             InternalUnsafeMethods.AddGlobalShaderMacro__Args _args = new InternalUnsafeMethods.AddGlobalShaderMacro__Args() {
                name = name,
                value = value,
             };
             InternalUnsafeMethods.AddGlobalShaderMacro()(_args);
        }

        /// <description>
        /// Returns the width, height, and bitdepth of the screen/desktop.
        /// </description>
        public static Point3F GetDesktopResolution() {
             InternalUnsafeMethods.GetDesktopResolution__Args _args = new InternalUnsafeMethods.GetDesktopResolution__Args() {
             };
             Point3F.InternalStruct _engineResult = InternalUnsafeMethods.GetDesktopResolution()(_args);
             return new Point3F(_engineResult);
        }

        /// <description>
        /// forces the gbuffer to be reinitialized in cases of improper/lack of buffer clears.
        /// </description>
        public static void ResetGFX() {
             InternalUnsafeMethods.ResetGFX__Args _args = new InternalUnsafeMethods.ResetGFX__Args() {
             };
             InternalUnsafeMethods.ResetGFX()(_args);
        }

        /// <description>
        /// Returns the best texture format for storage of HDR data for the active device.
        /// </description>
        public static GFXFormat GetBestHDRFormat() {
             InternalUnsafeMethods.GetBestHDRFormat__Args _args = new InternalUnsafeMethods.GetBestHDRFormat__Args() {
             };
             int _engineResult = InternalUnsafeMethods.GetBestHDRFormat()(_args);
             return (GFXFormat)_engineResult;
        }

        /// <description>
        /// Get the string describing the active GFX device.
        /// </description>
        public static string GetDisplayDeviceInformation() {
             InternalUnsafeMethods.GetDisplayDeviceInformation__Args _args = new InternalUnsafeMethods.GetDisplayDeviceInformation__Args() {
             };
             IntPtr _engineResult = InternalUnsafeMethods.GetDisplayDeviceInformation()(_args);
             return StringMarshal.IntPtrToUtf8String(_engineResult);
        }

        /// <summary>Sets the pixel shader version for the active device.</summary>
        /// <description>
        /// This can be used to force a lower pixel shader version than is supported by the device for testing or performance optimization.
        /// </description>
        /// <param name="version">The floating point shader version number.</param>
        /// <remarks> This will only affect shaders/materials created after the call and should be used before the game begins.
        /// </remarks>
        /// <see cref="$pref::Video::forcedPixVersion" />
        public static void SetPixelShaderVersion(float version) {
             InternalUnsafeMethods.SetPixelShaderVersion__Args _args = new InternalUnsafeMethods.SetPixelShaderVersion__Args() {
                version = version,
             };
             InternalUnsafeMethods.SetPixelShaderVersion()(_args);
        }

        /// <description>
        /// Returns the pixel shader version for the active device.
        /// </description>
        public static float GetPixelShaderVersion() {
             InternalUnsafeMethods.GetPixelShaderVersion__Args _args = new InternalUnsafeMethods.GetPixelShaderVersion__Args() {
             };
             float _engineResult = InternalUnsafeMethods.GetPixelShaderVersion()(_args);
             return _engineResult;
        }

        /// <description>
        /// Dumps a description of all state blocks.
        /// </description>
        /// <param name="filePath">A file to dump the state blocks to or an empty string to write to the console.</param>
        public static void DescribeGFXStateBlocks(string filePath) {
             InternalUnsafeMethods.DescribeGFXStateBlocks__Args _args = new InternalUnsafeMethods.DescribeGFXStateBlocks__Args() {
                filePath = filePath,
             };
             InternalUnsafeMethods.DescribeGFXStateBlocks()(_args);
        }

        /// <summary>Dumps a description of GFX resources to a file or the console.</summary>
        /// <description>
        /// 
        /// </description>
        /// <param name="resourceTypes">A space seperated list of resource types or an empty string for all resources.</param>
        /// <param name="filePath">A file to dump the list to or an empty string to write to the console.</param>
        /// <param name="unflaggedOnly">If true only unflagged resources are dumped. See flagCurrentGFXResources.</param>
        /// <remarks> The resource types can be one or more of the following:
        /// 
        ///   - texture
        ///   - texture target
        ///   - window target
        ///   - vertex buffers
        ///   - primitive buffers
        ///   - fences
        ///   - cubemaps
        ///   - shaders
        ///   - stateblocks
        /// 
        /// </remarks>
        public static void DescribeGFXResources(string resourceTypes, string filePath, bool unflaggedOnly = false) {
             InternalUnsafeMethods.DescribeGFXResources__Args _args = new InternalUnsafeMethods.DescribeGFXResources__Args() {
                resourceTypes = resourceTypes,
                filePath = filePath,
                unflaggedOnly = unflaggedOnly,
             };
             InternalUnsafeMethods.DescribeGFXResources()(_args);
        }

        /// <description>
        /// Clears the flagged state on all allocated GFX resources. See flagCurrentGFXResources for usage details.
        /// </description>
        /// <see cref="flagCurrentGFXResources, listGFXResources, describeGFXResources" />
        public static void ClearGFXResourceFlags() {
             InternalUnsafeMethods.ClearGFXResourceFlags__Args _args = new InternalUnsafeMethods.ClearGFXResourceFlags__Args() {
             };
             InternalUnsafeMethods.ClearGFXResourceFlags()(_args);
        }

        /// <summary>Flags all currently allocated GFX resources.</summary>
        /// <description>
        /// Used for resource allocation and leak tracking by flagging current resources then dumping a list of unflagged resources at some later point in execution.
        /// </description>
        /// <see cref="listGFXResources, clearGFXResourceFlags, describeGFXResources" />
        public static void FlagCurrentGFXResources() {
             InternalUnsafeMethods.FlagCurrentGFXResources__Args _args = new InternalUnsafeMethods.FlagCurrentGFXResources__Args() {
             };
             InternalUnsafeMethods.FlagCurrentGFXResources()(_args);
        }

        /// <description>
        /// Returns a list of the unflagged GFX resources. See flagCurrentGFXResources for usage details.
        /// </description>
        /// <see cref="flagCurrentGFXResources, clearGFXResourceFlags, describeGFXResources" />
        public static void ListGFXResources(bool unflaggedOnly = false) {
             InternalUnsafeMethods.ListGFXResources__Args _args = new InternalUnsafeMethods.ListGFXResources__Args() {
                unflaggedOnly = unflaggedOnly,
             };
             InternalUnsafeMethods.ListGFXResources()(_args);
        }

        /// <description>
        /// Returns a tab-seperated string of the detected devices across all adapters.
        /// </description>
        public static string GetDisplayDeviceList() {
             InternalUnsafeMethods.GetDisplayDeviceList__Args _args = new InternalUnsafeMethods.GetDisplayDeviceList__Args() {
             };
             IntPtr _engineResult = InternalUnsafeMethods.GetDisplayDeviceList()(_args);
             return StringMarshal.IntPtrToUtf8String(_engineResult);
        }

        /// <description>
        /// Copy the specified old font to a new name. The new copy will not have a platform font backing it, and so will never have characters added to it. But this is useful for making copies of fonts to add postprocessing effects to via exportCachedFont.
        /// </description>
        /// <param name="oldFontName">The name of the font face to copy.</param>
        /// <param name="oldFontSize">The size of the font to copy.</param>
        /// <param name="newFontName">The name of the new font face.</param>
        public static void DuplicateCachedFont(string oldFontName, int oldFontSize, string newFontName) {
             InternalUnsafeMethods.DuplicateCachedFont__Args _args = new InternalUnsafeMethods.DuplicateCachedFont__Args() {
                oldFontName = oldFontName,
                oldFontSize = oldFontSize,
                newFontName = newFontName,
             };
             InternalUnsafeMethods.DuplicateCachedFont()(_args);
        }

        /// <description>
        /// Import an image strip from exportCachedFont. Call with the same parameters you called exportCachedFont.
        /// </description>
        /// <param name="faceName">The name of the font face.</param>
        /// <param name="fontSize">The size of the font in pixels.</param>
        /// <param name="fileName">The file name and path for the input PNG.</param>
        /// <param name="padding">The padding between characters.</param>
        /// <param name="kerning">The kerning between characters.</param>
        public static void ImportCachedFont(string faceName, int fontSize, string fileName, int padding, int kerning) {
             InternalUnsafeMethods.ImportCachedFont__Args _args = new InternalUnsafeMethods.ImportCachedFont__Args() {
                faceName = faceName,
                fontSize = fontSize,
                fileName = fileName,
                padding = padding,
                kerning = kerning,
             };
             InternalUnsafeMethods.ImportCachedFont()(_args);
        }

        /// <description>
        /// Export specified font to the specified filename as a PNG. The image can then be processed in Photoshop or another tool and reimported using importCachedFont. Characters in the font are exported as one long strip.
        /// </description>
        /// <param name="faceName">The name of the font face.</param>
        /// <param name="fontSize">The size of the font in pixels.</param>
        /// <param name="fileName">The file name and path for the output PNG.</param>
        /// <param name="padding">The padding between characters.</param>
        /// <param name="kerning">The kerning between characters.</param>
        public static void ExportCachedFont(string faceName, int fontSize, string fileName, int padding, int kerning) {
             InternalUnsafeMethods.ExportCachedFont__Args _args = new InternalUnsafeMethods.ExportCachedFont__Args() {
                faceName = faceName,
                fontSize = fontSize,
                fileName = fileName,
                padding = padding,
                kerning = kerning,
             };
             InternalUnsafeMethods.ExportCachedFont()(_args);
        }

        /// <description>
        /// Populate the font cache for all fonts with Unicode code points in the specified range.
        /// </description>
        /// <param name="rangeStart">The start Unicode point.</param>
        /// <param name="rangeEnd">The end Unicode point.</param>
        /// <remarks> We only support BMP-0, so code points range from 0 to 65535.
        /// </remarks>
        public static void PopulateAllFontCacheRange(uint rangeStart, uint rangeEnd) {
             InternalUnsafeMethods.PopulateAllFontCacheRange__Args _args = new InternalUnsafeMethods.PopulateAllFontCacheRange__Args() {
                rangeStart = rangeStart,
                rangeEnd = rangeEnd,
             };
             InternalUnsafeMethods.PopulateAllFontCacheRange()(_args);
        }

        /// <description>
        /// Populate the font cache for all fonts with characters from the specified string.
        /// </description>
        public static void PopulateAllFontCacheString(string _string) {
             InternalUnsafeMethods.PopulateAllFontCacheString__Args _args = new InternalUnsafeMethods.PopulateAllFontCacheString__Args() {
                _string = _string,
             };
             InternalUnsafeMethods.PopulateAllFontCacheString()(_args);
        }

        /// <description>
        /// Force all cached fonts to serialize themselves to the cache.
        /// </description>
        public static void WriteFontCache() {
             InternalUnsafeMethods.WriteFontCache__Args _args = new InternalUnsafeMethods.WriteFontCache__Args() {
             };
             InternalUnsafeMethods.WriteFontCache()(_args);
        }

        /// <description>
        /// Dumps to the console a full description of all cached fonts, along with info on the codepoints each contains.
        /// </description>
        public static void DumpFontCacheStatus() {
             InternalUnsafeMethods.DumpFontCacheStatus__Args _args = new InternalUnsafeMethods.DumpFontCacheStatus__Args() {
             };
             InternalUnsafeMethods.DumpFontCacheStatus()(_args);
        }

        /// <description>
        /// Populate the font cache for the specified font with Unicode code points in the specified range.
        /// </description>
        /// <param name="faceName">The name of the font face.</param>
        /// <param name="fontSize">The size of the font in pixels.</param>
        /// <param name="rangeStart">The start Unicode point.</param>
        /// <param name="rangeEnd">The end Unicode point.</param>
        /// <remarks> We only support BMP-0, so code points range from 0 to 65535.
        /// </remarks>
        public static void PopulateFontCacheRange(string faceName, int fontSize, uint rangeStart, uint rangeEnd) {
             InternalUnsafeMethods.PopulateFontCacheRange__Args _args = new InternalUnsafeMethods.PopulateFontCacheRange__Args() {
                faceName = faceName,
                fontSize = fontSize,
                rangeStart = rangeStart,
                rangeEnd = rangeEnd,
             };
             InternalUnsafeMethods.PopulateFontCacheRange()(_args);
        }

        /// <description>
        /// Populate the font cache for the specified font with characters from the specified string.
        /// </description>
        /// <param name="faceName">The name of the font face.</param>
        /// <param name="fontSize">The size of the font in pixels.</param>
        /// <param name="string">The string to populate.</param>
        public static void PopulateFontCacheString(string faceName, int fontSize, string _string) {
             InternalUnsafeMethods.PopulateFontCacheString__Args _args = new InternalUnsafeMethods.PopulateFontCacheString__Args() {
                faceName = faceName,
                fontSize = fontSize,
                _string = _string,
             };
             InternalUnsafeMethods.PopulateFontCacheString()(_args);
        }

        /// <description>
        /// Load a journal file and capture it video.
        /// </description>
        public static void PlayJournalToVideo(string journalFile, string videoFile = "", string encoder = "THEORA", float framerate = 30f, Point2I resolution = null) {
resolution = resolution ?? new Point2I("0 0");
resolution.Alloc();             InternalUnsafeMethods.PlayJournalToVideo__Args _args = new InternalUnsafeMethods.PlayJournalToVideo__Args() {
                journalFile = journalFile,
                videoFile = videoFile,
                encoder = encoder,
                framerate = framerate,
                resolution = resolution.internalStructPtr,
             };
             InternalUnsafeMethods.PlayJournalToVideo()(_args);
resolution.Free();        }

        /// <description>
        /// Stops the video capture session.
        /// </description>
        /// <see cref="startVideoCapture" />
        public static void StopVideoCapture() {
             InternalUnsafeMethods.StopVideoCapture__Args _args = new InternalUnsafeMethods.StopVideoCapture__Args() {
             };
             InternalUnsafeMethods.StopVideoCapture()(_args);
        }

        /// <description>
        /// Begins a video capture session.
        /// </description>
        /// <see cref="stopVideoCapture" />
        public static void StartVideoCapture(GuiCanvas canvas, string filename, string encoder = "THEORA", float framerate = 30f, Point2I resolution = null) {
resolution = resolution ?? new Point2I("0 0");
resolution.Alloc();             InternalUnsafeMethods.StartVideoCapture__Args _args = new InternalUnsafeMethods.StartVideoCapture__Args() {
                canvas = canvas.ObjectPtr,
                filename = filename,
                encoder = encoder,
                framerate = framerate,
                resolution = resolution.internalStructPtr,
             };
             InternalUnsafeMethods.StartVideoCapture()(_args);
resolution.Free();        }

        /// <description>
        /// Returns image info in the following format: width TAB height TAB bytesPerPixel. It will return an empty string if the file is not found.
        /// </description>
        public static string GetBitmapInfo(string filename) {
             InternalUnsafeMethods.GetBitmapInfo__Args _args = new InternalUnsafeMethods.GetBitmapInfo__Args() {
                filename = filename,
             };
             IntPtr _engineResult = InternalUnsafeMethods.GetBitmapInfo()(_args);
             return StringMarshal.IntPtrToUtf8String(_engineResult);
        }

        /// <description>
        /// Returns the count of active DDSs files in memory.
        /// </description>
        public static int GetActiveDDSFiles() {
             InternalUnsafeMethods.GetActiveDDSFiles__Args _args = new InternalUnsafeMethods.GetActiveDDSFiles__Args() {
             };
             int _engineResult = InternalUnsafeMethods.GetActiveDDSFiles()(_args);
             return _engineResult;
        }

        /// <description>
        /// (string queueName, string message)
        /// </description>
        /// <summary>Dispatch a message object to a queue</summary>
        /// <description>
        /// 
        /// </description>
        /// <param name="queueName">Queue to dispatch the message to</param>
        /// <param name="message">Message to dispatch</param>
        /// <returns>true for success, false for failure</returns>
        /// <see cref="dispatchMessage" />
        public static bool DispatchMessageObject(string queueName = "", string message = "") {
             InternalUnsafeMethods.DispatchMessageObject__Args _args = new InternalUnsafeMethods.DispatchMessageObject__Args() {
                queueName = queueName,
                message = message,
             };
             bool _engineResult = InternalUnsafeMethods.DispatchMessageObject()(_args);
             return _engineResult;
        }

        /// <description>
        /// (string queueName, string message, string data)
        /// </description>
        /// <summary>Dispatch a message to a queue</summary>
        /// <description>
        /// 
        /// </description>
        /// <param name="queueName">Queue to dispatch the message to</param>
        /// <param name="message">Message to dispatch</param>
        /// <param name="data">Data for message</param>
        /// <returns>True for success, false for failure</returns>
        /// <see cref="dispatchMessageObject" />
        public static bool DispatchMessage(string queueName, string message, string data = "") {
             InternalUnsafeMethods.DispatchMessage__Args _args = new InternalUnsafeMethods.DispatchMessage__Args() {
                queueName = queueName,
                message = message,
                data = data,
             };
             bool _engineResult = InternalUnsafeMethods.DispatchMessage()(_args);
             return _engineResult;
        }

        /// <description>
        /// (string queueName, string listener)
        /// </description>
        /// <summary>Unregisters an event message</summary>
        /// <description>
        /// 
        /// </description>
        /// <param name="queueName">String containing the name of queue</param>
        /// <param name="listener">Name of event messenger</param>
        public static void UnregisterMessageListener(string queueName, string listenerName) {
             InternalUnsafeMethods.UnregisterMessageListener__Args _args = new InternalUnsafeMethods.UnregisterMessageListener__Args() {
                queueName = queueName,
                listenerName = listenerName,
             };
             InternalUnsafeMethods.UnregisterMessageListener()(_args);
        }

        /// <description>
        /// (string queueName, string listener)
        /// </description>
        /// <summary>Registers an event message</summary>
        /// <description>
        /// 
        /// </description>
        /// <param name="queueName">String containing the name of queue to attach listener to</param>
        /// <param name="listener">Name of event messenger</param>
        public static bool RegisterMessageListener(string queueName, string listenerName) {
             InternalUnsafeMethods.RegisterMessageListener__Args _args = new InternalUnsafeMethods.RegisterMessageListener__Args() {
                queueName = queueName,
                listenerName = listenerName,
             };
             bool _engineResult = InternalUnsafeMethods.RegisterMessageListener()(_args);
             return _engineResult;
        }

        /// <description>
        /// (string queueName)
        /// </description>
        /// <summary>Unregisters a dispatcher queue</summary>
        /// <description>
        /// 
        /// </description>
        /// <param name="queueName">String containing the name of queue</param>
        public static void UnregisterMessageQueue(string queueName) {
             InternalUnsafeMethods.UnregisterMessageQueue__Args _args = new InternalUnsafeMethods.UnregisterMessageQueue__Args() {
                queueName = queueName,
             };
             InternalUnsafeMethods.UnregisterMessageQueue()(_args);
        }

        /// <description>
        /// (string queueName)
        /// </description>
        /// <summary>Registeres a dispatcher queue</summary>
        /// <description>
        /// 
        /// </description>
        /// <param name="queueName">String containing the name of queue</param>
        public static void RegisterMessageQueue(string queueName) {
             InternalUnsafeMethods.RegisterMessageQueue__Args _args = new InternalUnsafeMethods.RegisterMessageQueue__Args() {
                queueName = queueName,
             };
             InternalUnsafeMethods.RegisterMessageQueue()(_args);
        }

        /// <description>
        /// (string queueName)
        /// </description>
        /// <summary>Determines if a dispatcher queue exists</summary>
        /// <description>
        /// 
        /// </description>
        /// <param name="queueName">String containing the name of queue</param>
        public static bool IsQueueRegistered(string queueName) {
             InternalUnsafeMethods.IsQueueRegistered__Args _args = new InternalUnsafeMethods.IsQueueRegistered__Args() {
                queueName = queueName,
             };
             bool _engineResult = InternalUnsafeMethods.IsQueueRegistered()(_args);
             return _engineResult;
        }

        /// 
        public static SimObject FindDataBlockByName(string pName) {
             InternalUnsafeMethods.FindDataBlockByName__Args _args = new InternalUnsafeMethods.FindDataBlockByName__Args() {
                pName = pName,
             };
             IntPtr _engineResult = InternalUnsafeMethods.FindDataBlockByName()(_args);
             return new SimObject(_engineResult);
        }

        /// 
        public static SimObject FindObjectByName(string pName) {
             InternalUnsafeMethods.FindObjectByName__Args _args = new InternalUnsafeMethods.FindObjectByName__Args() {
                pName = pName,
             };
             IntPtr _engineResult = InternalUnsafeMethods.FindObjectByName()(_args);
             return new SimObject(_engineResult);
        }

        /// 
        public static SimObject FindObjectById(uint pId) {
             InternalUnsafeMethods.FindObjectById__Args _args = new InternalUnsafeMethods.FindObjectById__Args() {
                pId = pId,
             };
             IntPtr _engineResult = InternalUnsafeMethods.FindObjectById()(_args);
             return new SimObject(_engineResult);
        }

        /// 
        public static void SetConsoleBool(string name, bool value) {
             InternalUnsafeMethods.SetConsoleBool__Args _args = new InternalUnsafeMethods.SetConsoleBool__Args() {
                name = name,
                value = value,
             };
             InternalUnsafeMethods.SetConsoleBool()(_args);
        }

        /// 
        public static bool GetConsoleBool(string name) {
             InternalUnsafeMethods.GetConsoleBool__Args _args = new InternalUnsafeMethods.GetConsoleBool__Args() {
                name = name,
             };
             bool _engineResult = InternalUnsafeMethods.GetConsoleBool()(_args);
             return _engineResult;
        }

        /// 
        public static void SetConsoleFloat(string name, float value) {
             InternalUnsafeMethods.SetConsoleFloat__Args _args = new InternalUnsafeMethods.SetConsoleFloat__Args() {
                name = name,
                value = value,
             };
             InternalUnsafeMethods.SetConsoleFloat()(_args);
        }

        /// 
        public static float GetConsoleFloat(string name) {
             InternalUnsafeMethods.GetConsoleFloat__Args _args = new InternalUnsafeMethods.GetConsoleFloat__Args() {
                name = name,
             };
             float _engineResult = InternalUnsafeMethods.GetConsoleFloat()(_args);
             return _engineResult;
        }

        /// 
        public static void SetConsoleInt(string name, int value) {
             InternalUnsafeMethods.SetConsoleInt__Args _args = new InternalUnsafeMethods.SetConsoleInt__Args() {
                name = name,
                value = value,
             };
             InternalUnsafeMethods.SetConsoleInt()(_args);
        }

        /// 
        public static int GetConsoleInt(string name) {
             InternalUnsafeMethods.GetConsoleInt__Args _args = new InternalUnsafeMethods.GetConsoleInt__Args() {
                name = name,
             };
             int _engineResult = InternalUnsafeMethods.GetConsoleInt()(_args);
             return _engineResult;
        }

        /// 
        public static void SetConsoleString(string name, string value) {
             InternalUnsafeMethods.SetConsoleString__Args _args = new InternalUnsafeMethods.SetConsoleString__Args() {
                name = name,
                value = value,
             };
             InternalUnsafeMethods.SetConsoleString()(_args);
        }

        /// 
        public static string GetConsoleString(string name) {
             InternalUnsafeMethods.GetConsoleString__Args _args = new InternalUnsafeMethods.GetConsoleString__Args() {
                name = name,
             };
             IntPtr _engineResult = InternalUnsafeMethods.GetConsoleString()(_args);
             return StringMarshal.IntPtrToUtf8String(_engineResult);
        }

        /// <description>
        /// Display a modal message box using the platform's native message box implementation.
        /// </description>
        /// <param name="title">The title to display on the message box window.</param>
        /// <param name="message">The text message to display in the box.</param>
        /// <param name="buttons">Which buttons to put on the message box.</param>
        /// <param name="icons">Which icon to show next to the message.</param>
        /// <returns>One of $MROK, $MRCancel, $MRRetry, and $MRDontSave identifying the button that the user pressed.</returns>
        /// <code>
        /// messageBox( "Error", "" );
        /// </code>
        public static int MessageBox(string title, string message, MBButtons buttons = MBButtons.OkCancel, MBIcons icons = MBIcons.Information) {
             InternalUnsafeMethods.MessageBox__Args _args = new InternalUnsafeMethods.MessageBox__Args() {
                title = title,
                message = message,
                buttons = (int)buttons,
                icons = (int)icons,
             };
             int _engineResult = InternalUnsafeMethods.MessageBox()(_args);
             return _engineResult;
        }

        /// <summary>Resets the profiler, clearing it of all its data.</summary>
        /// <description>
        /// If the profiler is currently running, it will first be disabled. All markers will retain their current enabled/disabled status.
        /// </description>
        public static void ProfilerReset() {
             InternalUnsafeMethods.ProfilerReset__Args _args = new InternalUnsafeMethods.ProfilerReset__Args() {
             };
             InternalUnsafeMethods.ProfilerReset()(_args);
        }

        /// <summary>Dumps current profiling stats to a file.</summary>
        /// <description>
        /// 
        /// </description>
        /// <remarks> If the profiler is currently running, it will be disabled.
        /// </remarks>
        /// <param name="fileName">Name and path of file to save profiling stats to. Must use forward slashes (/). Will attempt to create the file if it does not already exist.</param>
        /// <code>
        /// profilerDumpToFile( "C:/Torque/log1.txt" );
        /// </code>
        public static void ProfilerDumpToFile(string fileName) {
             InternalUnsafeMethods.ProfilerDumpToFile__Args _args = new InternalUnsafeMethods.ProfilerDumpToFile__Args() {
                fileName = fileName,
             };
             InternalUnsafeMethods.ProfilerDumpToFile()(_args);
        }

        /// <summary>Dumps current profiling stats to the console window.</summary>
        /// <description>
        /// 
        /// </description>
        /// <remarks> Markers disabled with profilerMarkerEnable() will be skipped over. If the profiler is currently running, it will be disabled.
        /// </remarks>
        public static void ProfilerDump() {
             InternalUnsafeMethods.ProfilerDump__Args _args = new InternalUnsafeMethods.ProfilerDump__Args() {
             };
             InternalUnsafeMethods.ProfilerDump()(_args);
        }

        /// <summary>Enables or disables the profiler.</summary>
        /// <description>
        /// Data is only gathered while the profiler is enabled.
        /// </description>
        /// <remarks> Profiler is not available in shipping builds.
        /// T3D has predefined profiling areas surrounded by markers, but you may need to define additional markers (in C++) around areas you wish to profile, by using the PROFILE_START( markerName ); and PROFILE_END(); macros.
        /// 
        /// </remarks>
        public static void ProfilerEnable(bool enable) {
             InternalUnsafeMethods.ProfilerEnable__Args _args = new InternalUnsafeMethods.ProfilerEnable__Args() {
                enable = enable,
             };
             InternalUnsafeMethods.ProfilerEnable()(_args);
        }

        /// <summary>Enable or disable a specific profile.</summary>
        /// <description>
        /// 
        /// </description>
        /// <param name="enable">Optional paramater to enable or disable the profile.</param>
        /// <param name="markerName">Name of a specific marker to enable or disable.</param>
        /// <remarks> Calling this function will first call profilerReset(), clearing all data from profiler. All profile markers are enabled by default.
        /// 
        /// </remarks>
        public static void ProfilerMarkerEnable(string markerName, bool enable = true) {
             InternalUnsafeMethods.ProfilerMarkerEnable__Args _args = new InternalUnsafeMethods.ProfilerMarkerEnable__Args() {
                markerName = markerName,
                enable = enable,
             };
             InternalUnsafeMethods.ProfilerMarkerEnable()(_args);
        }

        /// <description>
        /// stopPrecisionTimer( S32 id ) - Stop and destroy timer with the passed id.  Returns the elapsed milliseconds.
        /// </description>
        public static int StopPrecisionTimer(int id) {
             InternalUnsafeMethods.StopPrecisionTimer__Args _args = new InternalUnsafeMethods.StopPrecisionTimer__Args() {
                id = id,
             };
             int _engineResult = InternalUnsafeMethods.StopPrecisionTimer()(_args);
             return _engineResult;
        }

        /// <description>
        /// startPrecisionTimer() - Create and start a high resolution platform timer. Returns the timer id.
        /// </description>
        public static int StartPrecisionTimer() {
             InternalUnsafeMethods.StartPrecisionTimer__Args _args = new InternalUnsafeMethods.StartPrecisionTimer__Args() {
             };
             int _engineResult = InternalUnsafeMethods.StartPrecisionTimer()(_args);
             return _engineResult;
        }

        /// <description>
        /// Get a string explaining the last redbook error.
        /// </description>
        /// <summary>Deprecated</summary>
        /// <description>
        /// 
        /// </description>
        public static string RedbookGetLastError() {
             InternalUnsafeMethods.RedbookGetLastError__Args _args = new InternalUnsafeMethods.RedbookGetLastError__Args() {
             };
             IntPtr _engineResult = InternalUnsafeMethods.RedbookGetLastError()(_args);
             return StringMarshal.IntPtrToUtf8String(_engineResult);
        }

        /// <description>
        /// (int index) Get name of specified Redbook device.
        /// </description>
        /// <summary>Deprecated</summary>
        /// <description>
        /// 
        /// </description>
        public static string RedbookGetDeviceName(int index) {
             InternalUnsafeMethods.RedbookGetDeviceName__Args _args = new InternalUnsafeMethods.RedbookGetDeviceName__Args() {
                index = index,
             };
             IntPtr _engineResult = InternalUnsafeMethods.RedbookGetDeviceName()(_args);
             return StringMarshal.IntPtrToUtf8String(_engineResult);
        }

        /// <description>
        /// get the number of redbook devices.
        /// </description>
        /// <summary>Deprecated</summary>
        /// <description>
        /// 
        /// </description>
        public static int RedbookGetDeviceCount() {
             InternalUnsafeMethods.RedbookGetDeviceCount__Args _args = new InternalUnsafeMethods.RedbookGetDeviceCount__Args() {
             };
             int _engineResult = InternalUnsafeMethods.RedbookGetDeviceCount()(_args);
             return _engineResult;
        }

        /// <description>
        /// (float volume) Set playback volume.
        /// </description>
        /// <summary>Deprecated</summary>
        /// <description>
        /// 
        /// </description>
        public static bool RedbookSetVolume(float volume) {
             InternalUnsafeMethods.RedbookSetVolume__Args _args = new InternalUnsafeMethods.RedbookSetVolume__Args() {
                volume = volume,
             };
             bool _engineResult = InternalUnsafeMethods.RedbookSetVolume()(_args);
             return _engineResult;
        }

        /// <description>
        /// Get the volume.
        /// </description>
        /// <summary>Deprecated</summary>
        /// <description>
        /// 
        /// </description>
        public static float RedbookGetVolume() {
             InternalUnsafeMethods.RedbookGetVolume__Args _args = new InternalUnsafeMethods.RedbookGetVolume__Args() {
             };
             float _engineResult = InternalUnsafeMethods.RedbookGetVolume()(_args);
             return _engineResult;
        }

        /// <description>
        /// Return the number of tracks.
        /// </description>
        /// <summary>Deprecated</summary>
        /// <description>
        /// 
        /// </description>
        public static int RedbookGetTrackCount() {
             InternalUnsafeMethods.RedbookGetTrackCount__Args _args = new InternalUnsafeMethods.RedbookGetTrackCount__Args() {
             };
             int _engineResult = InternalUnsafeMethods.RedbookGetTrackCount()(_args);
             return _engineResult;
        }

        /// <description>
        /// Stop playing.
        /// </description>
        /// <summary>Deprecated</summary>
        /// <description>
        /// 
        /// </description>
        public static bool RedbookStop() {
             InternalUnsafeMethods.RedbookStop__Args _args = new InternalUnsafeMethods.RedbookStop__Args() {
             };
             bool _engineResult = InternalUnsafeMethods.RedbookStop()(_args);
             return _engineResult;
        }

        /// <description>
        /// (int track) Play the selected track.
        /// </description>
        /// <summary>Deprecated</summary>
        /// <description>
        /// 
        /// </description>
        public static bool RedbookPlay(int track) {
             InternalUnsafeMethods.RedbookPlay__Args _args = new InternalUnsafeMethods.RedbookPlay__Args() {
                track = track,
             };
             bool _engineResult = InternalUnsafeMethods.RedbookPlay()(_args);
             return _engineResult;
        }

        /// <description>
        /// Close the current Redbook device.
        /// </description>
        /// <summary>Deprecated</summary>
        /// <description>
        /// 
        /// </description>
        public static bool RedbookClose() {
             InternalUnsafeMethods.RedbookClose__Args _args = new InternalUnsafeMethods.RedbookClose__Args() {
             };
             bool _engineResult = InternalUnsafeMethods.RedbookClose()(_args);
             return _engineResult;
        }

        /// <description>
        /// (string device=NULL)
        /// </description>
        /// <summary>Deprecated</summary>
        /// <description>
        /// 
        /// </description>
        public static bool RedbookOpen(string device = "") {
             InternalUnsafeMethods.RedbookOpen__Args _args = new InternalUnsafeMethods.RedbookOpen__Args() {
                device = device,
             };
             bool _engineResult = InternalUnsafeMethods.RedbookOpen()(_args);
             return _engineResult;
        }

        /// <summary>Dumps a snapshot of current memory to a file.</summary>
        /// <description>
        /// The total memory used will also be output to the console.
        /// This function will attempt to create the file if it does not already exist.
        /// </description>
        /// <param name="fileName">Name and path of file to save profiling stats to. Must use forward slashes (/)</param>
        /// <code>
        /// dumpMemSnapshot( "C:/Torque/ProfilerLogs/profilerlog1.txt" );
        /// </code>
        /// <remarks> Available in debug builds only. In torqueConfig.h, TORQUE_DISABLE_MEMORY_MANAGER must be undefined to use this function.
        /// 
        /// </remarks>
        public static void DumpMemSnapshot(string fileName) {
             InternalUnsafeMethods.DumpMemSnapshot__Args _args = new InternalUnsafeMethods.DumpMemSnapshot__Args() {
                fileName = fileName,
             };
             InternalUnsafeMethods.DumpMemSnapshot()(_args);
        }

        /// <summary>Dumps information about the given allocated memory block.</summary>
        /// <description>
        /// 
        /// </description>
        /// <param name="allocNum">Memory block to dump information about.</param>
        /// <remarks> Available in debug builds only. In torqueConfig.h, TORQUE_DISABLE_MEMORY_MANAGER must be undefined to use this function.
        /// 
        /// </remarks>
        public static void DumpAlloc(int allocNum) {
             InternalUnsafeMethods.DumpAlloc__Args _args = new InternalUnsafeMethods.DumpAlloc__Args() {
                allocNum = allocNum,
             };
             InternalUnsafeMethods.DumpAlloc()(_args);
        }

        /// <summary>Dumps all unflagged memory allocations.</summary>
        /// <description>
        /// Dumps all memory allocations that were made after a call to flagCurrentAllocs(). Helpful when used with flagCurrentAllocs() for detecting memory leaks and analyzing general memory usage.
        /// </description>
        /// <param name="fileName">Optional file path and location to dump all memory allocations not flagged by flagCurrentAllocs(). If left blank, data will be dumped to the console.</param>
        /// <code>
        /// dumpMemSnapshot(); // dumps info to console
        /// dumpMemSnapshot( "C:/Torque/profilerlog1.txt" ); // dumps info to file
        /// </code>
        /// <remarks> Available in debug builds only. In torqueConfig.h, TORQUE_DISABLE_MEMORY_MANAGER must be undefined to use this function.
        /// 
        /// </remarks>
        public static void DumpUnflaggedAllocs(string fileName = "") {
             InternalUnsafeMethods.DumpUnflaggedAllocs__Args _args = new InternalUnsafeMethods.DumpUnflaggedAllocs__Args() {
                fileName = fileName,
             };
             InternalUnsafeMethods.DumpUnflaggedAllocs()(_args);
        }

        /// <summary>Flags all current memory allocations.</summary>
        /// <description>
        /// Flags all current memory allocations for exclusion in subsequent calls to dumpUnflaggedAllocs(). Helpful in detecting memory leaks and analyzing memory usage.
        /// </description>
        public static void FlagCurrentAllocs() {
             InternalUnsafeMethods.FlagCurrentAllocs__Args _args = new InternalUnsafeMethods.FlagCurrentAllocs__Args() {
             };
             InternalUnsafeMethods.FlagCurrentAllocs()(_args);
        }

        /// <summary>Dumps some useful statistics regarding free memory.</summary>
        /// <description>
        /// Dumps an analysis of 'free chunks' of memory. Does not print how much memory is free.
        /// </description>
        public static void FreeMemoryDump() {
             InternalUnsafeMethods.FreeMemoryDump__Args _args = new InternalUnsafeMethods.FreeMemoryDump__Args() {
             };
             InternalUnsafeMethods.FreeMemoryDump()(_args);
        }

        /// <summary>Used to validate memory space for the game.</summary>
        /// <description>
        /// 
        /// </description>
        public static void ValidateMemory() {
             InternalUnsafeMethods.ValidateMemory__Args _args = new InternalUnsafeMethods.ValidateMemory__Args() {
             };
             InternalUnsafeMethods.ValidateMemory()(_args);
        }

        /// <description>
        /// setMainDotCsDir()
        /// </description>
        public static void SetMainDotCsDir(string path) {
             InternalUnsafeMethods.SetMainDotCsDir__Args _args = new InternalUnsafeMethods.SetMainDotCsDir__Args() {
                path = path,
             };
             InternalUnsafeMethods.SetMainDotCsDir()(_args);
        }

        /// <description>
        /// getUserHomeDirectory()
        /// </description>
        public static string GetUserHomeDirectory() {
             InternalUnsafeMethods.GetUserHomeDirectory__Args _args = new InternalUnsafeMethods.GetUserHomeDirectory__Args() {
             };
             IntPtr _engineResult = InternalUnsafeMethods.GetUserHomeDirectory()(_args);
             return StringMarshal.IntPtrToUtf8String(_engineResult);
        }

        /// <description>
        /// getUserDataDirectory()
        /// </description>
        public static string GetUserDataDirectory() {
             InternalUnsafeMethods.GetUserDataDirectory__Args _args = new InternalUnsafeMethods.GetUserDataDirectory__Args() {
             };
             IntPtr _engineResult = InternalUnsafeMethods.GetUserDataDirectory()(_args);
             return StringMarshal.IntPtrToUtf8String(_engineResult);
        }

        /// <summary>Creates a name and extension for a potential temporary file</summary>
        /// <description>
        /// This does not create the actual file. It simply creates a random name for a file that does not exist.
        /// </description>
        /// <remarks> This is legacy function brought over from TGB, and does not appear to have much use. Possibly deprecate?
        /// </remarks>
        public static string GetTemporaryFileName() {
             InternalUnsafeMethods.GetTemporaryFileName__Args _args = new InternalUnsafeMethods.GetTemporaryFileName__Args() {
             };
             IntPtr _engineResult = InternalUnsafeMethods.GetTemporaryFileName()(_args);
             return StringMarshal.IntPtrToUtf8String(_engineResult);
        }

        /// <summary>Returns the OS temporary directory, "C:/Users/Mich/AppData/Local/Temp" for example</summary>
        /// <description>
        /// 
        /// </description>
        /// <remarks> This can be useful to adhering to OS standards and practices, but not really used in Torque 3D right now.
        /// </remarks>
        /// <remarks> Be very careful when getting into OS level File I/O.</remarks>
        /// <returns>String containing path to OS temp directory</returns>
        /// <remarks> This is legacy function brought over from TGB, and does not appear to have much use. Possibly deprecate?
        /// </remarks>
        public static string GetTemporaryDirectory() {
             InternalUnsafeMethods.GetTemporaryDirectory__Args _args = new InternalUnsafeMethods.GetTemporaryDirectory__Args() {
             };
             IntPtr _engineResult = InternalUnsafeMethods.GetTemporaryDirectory()(_args);
             return StringMarshal.IntPtrToUtf8String(_engineResult);
        }

        /// <description>
        /// Fatal Script Assertion
        /// </description>
        public static void Assert(bool condition, string message) {
             InternalUnsafeMethods.Assert__Args _args = new InternalUnsafeMethods.Assert__Args() {
                condition = condition,
                message = message,
             };
             InternalUnsafeMethods.Assert()(_args);
        }

        /// <description>
        /// ( int a, int b )
        /// </description>
        /// <summary>Returns a random number based on parameters passed in..</summary>
        /// <description>
        /// If no parameters are passed in, getRandom() will return a float between 0.0 and 1.0. If one parameter is passed an integer between 0 and the passed in value will be returned. Two parameters will return an integer between the specified numbers.
        /// </description>
        /// <param name="a">If this is the only parameter, a number between 0 and a is returned. Elsewise represents the lower bound.</param>
        /// <param name="b">Upper bound on the random number.  The random number will be <=<paramref name="" /> b.
        /// </param>
        /// <returns>A pseudo-random integer between<paramref name="" /> a and </returns>
        /// <remarks> All parameters are optional.</remarks>
        /// <see cref="setRandomSeed" />
        public static float GetRandom(int a = 2147483647, int b = 2147483647) {
             InternalUnsafeMethods.GetRandom__Args _args = new InternalUnsafeMethods.GetRandom__Args() {
                a = a,
                b = b,
             };
             float _engineResult = InternalUnsafeMethods.GetRandom()(_args);
             return _engineResult;
        }

        /// <description>
        /// Get the current seed used by the random number generator.
        /// </description>
        /// <returns>The current random number generator seed value.</returns>
        public static int GetRandomSeed() {
             InternalUnsafeMethods.GetRandomSeed__Args _args = new InternalUnsafeMethods.GetRandomSeed__Args() {
             };
             int _engineResult = InternalUnsafeMethods.GetRandomSeed()(_args);
             return _engineResult;
        }

        /// <description>
        /// Set the current seed for the random number generator.
        /// Based on this seed, a repeatable sequence of numbers will be produced by getRandom().
        /// </description>
        /// <param name="seed">The seed with which to initialize the randon number generator with.  The same seed will always leed tothe same sequence of pseudo-random numbers.
        /// If -1, the current timestamp will be used as the seed which is a good basis for randomization.</param>
        public static void SetRandomSeed(int seed = -1) {
             InternalUnsafeMethods.SetRandomSeed__Args _args = new InternalUnsafeMethods.SetRandomSeed__Args() {
                seed = seed,
             };
             InternalUnsafeMethods.SetRandomSeed()(_args);
        }

        /// <description>
        /// Get the center point of an axis-aligned box.
        /// </description>
        /// <param name="b">A Box3F, in string format using "minExtentX minExtentY minExtentZ maxExtentX maxExtentY maxExtentZ"</param>
        /// <returns>Center of the box.</returns>
        public static Point3F GetBoxCenter(Box3F box) {
box.Alloc();             InternalUnsafeMethods.GetBoxCenter__Args _args = new InternalUnsafeMethods.GetBoxCenter__Args() {
                box = box.internalStructPtr,
             };
             Point3F.InternalStruct _engineResult = InternalUnsafeMethods.GetBoxCenter()(_args);
box.Free();             return new Point3F(_engineResult);
        }

        /// <summary>Multiply the given point by the given transform assuming that w=1.</summary>
        /// <description>
        /// This function will multiply the given vector such that translation with take effect.
        /// </description>
        /// <param name="transform">A transform.</param>
        /// <param name="point">A vector.</param>
        /// <returns>The transformed vector.</returns>
        public static Point3F MatrixMulPoint(TransformF transform, Point3F point) {
transform.Alloc();point.Alloc();             InternalUnsafeMethods.MatrixMulPoint__Args _args = new InternalUnsafeMethods.MatrixMulPoint__Args() {
                transform = transform.internalStructPtr,
                point = point.internalStructPtr,
             };
             Point3F.InternalStruct _engineResult = InternalUnsafeMethods.MatrixMulPoint()(_args);
transform.Free();point.Free();             return new Point3F(_engineResult);
        }

        /// <summary>Multiply the vector by the transform assuming that w=0.</summary>
        /// <description>
        /// This function will multiply the given vector by the given transform such that translation will not affect the vector.
        /// </description>
        /// <param name="transform">A transform.</param>
        /// <param name="vector">A vector.</param>
        /// <returns>The transformed vector.</returns>
        public static Point3F MatrixMulVector(TransformF transform, Point3F vector) {
transform.Alloc();vector.Alloc();             InternalUnsafeMethods.MatrixMulVector__Args _args = new InternalUnsafeMethods.MatrixMulVector__Args() {
                transform = transform.internalStructPtr,
                vector = vector.internalStructPtr,
             };
             Point3F.InternalStruct _engineResult = InternalUnsafeMethods.MatrixMulVector()(_args);
transform.Free();vector.Free();             return new Point3F(_engineResult);
        }

        /// <summary>Multiply the two matrices.</summary>
        /// <description>
        /// 
        /// </description>
        /// <param name="left">First transform.</param>
        /// <param name="right">Right transform.</param>
        /// <returns>Concatenation of the two transforms.</returns>
        public static TransformF MatrixMultiply(TransformF left, TransformF right) {
left.Alloc();right.Alloc();             InternalUnsafeMethods.MatrixMultiply__Args _args = new InternalUnsafeMethods.MatrixMultiply__Args() {
                left = left.internalStructPtr,
                right = right.internalStructPtr,
             };
             TransformF.InternalStruct _engineResult = InternalUnsafeMethods.MatrixMultiply()(_args);
left.Free();right.Free();             return new TransformF(_engineResult);
        }

        /// <param name="Vector3F">X, Y, and Z rotation in *radians*.</param>
        /// <returns>A transform based on the given orientation.</returns>
        public static TransformF MatrixCreateFromEuler(Point3F angles) {
angles.Alloc();             InternalUnsafeMethods.MatrixCreateFromEuler__Args _args = new InternalUnsafeMethods.MatrixCreateFromEuler__Args() {
                angles = angles.internalStructPtr,
             };
             TransformF.InternalStruct _engineResult = InternalUnsafeMethods.MatrixCreateFromEuler()(_args);
angles.Free();             return new TransformF(_engineResult);
        }

        /// <description>
        /// Create a transform from the given translation and orientation.
        /// </description>
        /// <param name="position">The translation vector for the transform.</param>
        /// <param name="orientation">The axis and rotation that orients the transform.</param>
        /// <returns>A transform based on the given position and orientation.</returns>
        public static TransformF MatrixCreate(Point3F position, AngAxisF orientation) {
position.Alloc();orientation.Alloc();             InternalUnsafeMethods.MatrixCreate__Args _args = new InternalUnsafeMethods.MatrixCreate__Args() {
                position = position.internalStructPtr,
                orientation = orientation.internalStructPtr,
             };
             TransformF.InternalStruct _engineResult = InternalUnsafeMethods.MatrixCreate()(_args);
position.Free();orientation.Free();             return new TransformF(_engineResult);
        }

        /// <description>
        /// Compute the reflection of a vector based on a normal.
        /// </description>
        /// <param name="a">The vector.</param>
        /// <param name="b">The normal.</param>
        /// <returns>The reflected vector.</returns>
        public static Point3F VectorReflect(Point3F vec, Point3F normal) {
vec.Alloc();normal.Alloc();             InternalUnsafeMethods.VectorReflect__Args _args = new InternalUnsafeMethods.VectorReflect__Args() {
                vec = vec.internalStructPtr,
                normal = normal.internalStructPtr,
             };
             Point3F.InternalStruct _engineResult = InternalUnsafeMethods.VectorReflect()(_args);
vec.Free();normal.Free();             return new Point3F(_engineResult);
        }

        /// <description>
        /// Linearly interpolate between two vectors by<paramref name="" /> t.
        /// 
        /// </description>
        /// <param name="a">Vector to start interpolation from.</param>
        /// <param name="b">Vector to interpolate to.</param>
        /// <param name="t">Interpolation factor (0-1).  At zero,<paramref name="" /> a is returned and at one, </param>
        /// <returns>An interpolated vector between<paramref name="" /> a and </returns>
        /// <code>
        /// //-----------------------------------------------------------------------------
        /// //
        /// // VectorLerp( %a, %b );
        /// //
        /// // The point between vector a, (ax, ay, az), and vector b, (bx, by, bz), which is
        /// // weighted by the interpolation factor, t, is
        /// //
        /// //     r = a + t * ( b - a )
        /// //       = ( ax + t * ( bx - ax ), ay + t * ( by - ay ), az + t * ( bz - az ) )
        /// //
        /// //-----------------------------------------------------------------------------
        /// 
        /// %a = "1 1 0";
        /// %b = "2 0 1";
        /// %v = "0.25";
        /// 
        /// // %r = "( 1 + 0.25 * ( 2 - 1 ), 1 + 0.25 * ( 0 - 1 ), 0 + 0.25 * ( 1 - 0 ) )";
        /// // %r = "1.25 0.75 0.25";
        /// %r = VectorLerp( %a, %b );
        /// </code>
        public static Point3F VectorLerp(Point3F a, Point3F b, float t) {
a.Alloc();b.Alloc();             InternalUnsafeMethods.VectorLerp__Args _args = new InternalUnsafeMethods.VectorLerp__Args() {
                a = a.internalStructPtr,
                b = b.internalStructPtr,
                t = t,
             };
             Point3F.InternalStruct _engineResult = InternalUnsafeMethods.VectorLerp()(_args);
a.Free();b.Free();             return new Point3F(_engineResult);
        }

        /// <description>
        /// (Vector3F, float) rotate a vector in 2d
        /// </description>
        public static string VectorRot(Point3F v, float angle) {
v.Alloc();             InternalUnsafeMethods.VectorRot__Args _args = new InternalUnsafeMethods.VectorRot__Args() {
                v = v.internalStructPtr,
                angle = angle,
             };
             IntPtr _engineResult = InternalUnsafeMethods.VectorRot()(_args);
v.Free();             return StringMarshal.IntPtrToUtf8String(_engineResult);
        }

        /// <description>
        /// Create an orthogonal basis from the given vector.
        /// </description>
        /// <param name="aaf">The vector to create the orthogonal basis from.</param>
        /// <returns>A matrix representing the orthogonal basis.</returns>
        public static MatrixF VectorOrthoBasis(AngAxisF aa) {
aa.Alloc();             InternalUnsafeMethods.VectorOrthoBasis__Args _args = new InternalUnsafeMethods.VectorOrthoBasis__Args() {
                aa = aa.internalStructPtr,
             };
             MatrixF.InternalStruct _engineResult = InternalUnsafeMethods.VectorOrthoBasis()(_args);
aa.Free();             return new MatrixF(_engineResult);
        }

        /// <description>
        /// Calculate the magnitude of the given vector.
        /// </description>
        /// <param name="v">A vector.</param>
        /// <returns>The length of vector<paramref name="" /> v.
        /// 
        /// </returns>
        /// <code>
        /// //-----------------------------------------------------------------------------
        /// //
        /// // VectorLen( %a );
        /// //
        /// // The length or magnitude of  vector a, (ax, ay, az), is:
        /// //
        /// //     ||a|| = Sqrt( ax * ax + ay * ay + az * az )
        /// //
        /// //-----------------------------------------------------------------------------
        /// 
        /// %a = "1 1 0";
        /// 
        /// // %r = mSqrt( 1 * 1 + 1 * 1 + 0 * 0 );
        /// // %r = mSqrt( 2 );
        /// // %r = 1.414;
        /// %r = VectorLen( %a );
        /// </code>
        public static float VectorLen(Point3F v) {
v.Alloc();             InternalUnsafeMethods.VectorLen__Args _args = new InternalUnsafeMethods.VectorLen__Args() {
                v = v.internalStructPtr,
             };
             float _engineResult = InternalUnsafeMethods.VectorLen()(_args);
v.Free();             return _engineResult;
        }

        /// <description>
        /// Gets the midpoint between the two vectors.
        /// </description>
        /// <param name="a">The first vector.</param>
        /// <param name="b">The second vector.</param>
        /// <returns>The vector (<paramref name="" /> a + </returns>
        /// <code>
        /// //-----------------------------------------------------------------------------
        /// //
        /// // VectorMidPoint( %a, %b );
        /// //
        /// // The midpoint of vector a, (ax, ay, az), and vector b, (bx, by, bz) is:
        /// //
        /// //     (a + b)/2 = ( (ax + bx) /2, ay + by) /2, (az + bz) /2 )
        /// //
        /// //-----------------------------------------------------------------------------
        /// </code>
        public static Point3F VectorMidPoint(Point3F a, Point3F b) {
a.Alloc();b.Alloc();             InternalUnsafeMethods.VectorMidPoint__Args _args = new InternalUnsafeMethods.VectorMidPoint__Args() {
                a = a.internalStructPtr,
                b = b.internalStructPtr,
             };
             Point3F.InternalStruct _engineResult = InternalUnsafeMethods.VectorMidPoint()(_args);
a.Free();b.Free();             return new Point3F(_engineResult);
        }

        /// <description>
        /// Compute the distance between two vectors.
        /// </description>
        /// <param name="a">The first vector.</param>
        /// <param name="b">The second vector.</param>
        /// <returns>The length(<paramref name="" /> b - </returns>
        /// <code>
        /// //-----------------------------------------------------------------------------
        /// //
        /// // VectorDist( %a, %b );
        /// //
        /// // The distance between vector a, (ax, ay, az), and vector b, (bx, by, bz), is
        /// //
        /// //     a -> b = ||( b - a )||
        /// //            = ||( bx - ax, by - ay, bz - az )||
        /// //            = mSqrt( ( bx - ax ) * ( bx - ax ) + ( by - ay ) * ( by - ay ) + ( bz - az ) * ( bz - az ) )
        /// //
        /// //-----------------------------------------------------------------------------
        /// 
        /// %a = "1 1 0";
        /// %b = "2 0 1";
        /// 
        /// // %r = mSqrt( ( 2 - 1 ) * ( 2 - 1) + ( 0 - 1 ) * ( 0 - 1 ) + ( 1 - 0 ) * ( 1 - 0 ) );
        /// // %r = mSqrt( 3 );
        /// %r = VectorDist( %a, %b );
        /// </code>
        public static float VectorDist(Point3F a, Point3F b) {
a.Alloc();b.Alloc();             InternalUnsafeMethods.VectorDist__Args _args = new InternalUnsafeMethods.VectorDist__Args() {
                a = a.internalStructPtr,
                b = b.internalStructPtr,
             };
             float _engineResult = InternalUnsafeMethods.VectorDist()(_args);
a.Free();b.Free();             return _engineResult;
        }

        /// <description>
        /// Calculcate the cross product of two vectors.
        /// </description>
        /// <param name="a">The first vector.</param>
        /// <param name="b">The second vector.</param>
        /// <returns>The cross product<paramref name="" /> x </returns>
        /// <code>
        /// //-----------------------------------------------------------------------------
        /// //
        /// // VectorCross( %a, %b );
        /// //
        /// // The cross product of vector a, (ax, ay, az), and vector b, (bx, by, bz), is
        /// //
        /// //     a x b = ( ( ay * bz ) - ( az * by ), ( az * bx ) - ( ax * bz ), ( ax * by ) - ( ay * bx ) )
        /// //
        /// //-----------------------------------------------------------------------------
        /// 
        /// %a = "1 1 0";
        /// %b = "2 0 1";
        /// 
        /// // %r = "( ( 1 * 1 ) - ( 0 * 0 ), ( 0 * 2 ) - ( 1 * 1 ), ( 1 * 0 ) - ( 1 * 2 ) )";
        /// // %r = "1 -1 -2";
        /// %r = VectorCross( %a, %b );
        /// </code>
        public static Point3F VectorCross(Point3F a, Point3F b) {
a.Alloc();b.Alloc();             InternalUnsafeMethods.VectorCross__Args _args = new InternalUnsafeMethods.VectorCross__Args() {
                a = a.internalStructPtr,
                b = b.internalStructPtr,
             };
             Point3F.InternalStruct _engineResult = InternalUnsafeMethods.VectorCross()(_args);
a.Free();b.Free();             return new Point3F(_engineResult);
        }

        /// <description>
        /// Compute the dot product of two vectors.
        /// </description>
        /// <param name="a">The first vector.</param>
        /// <param name="b">The second vector.</param>
        /// <returns>The dot product<paramref name="" /> a * </returns>
        /// <code>
        /// //-----------------------------------------------------------------------------
        /// //
        /// // VectorDot( %a, %b );
        /// //
        /// // The dot product between vector a, (ax, ay, az), and vector b, (bx, by, bz), is:
        /// //
        /// //     a . b = ( ax * bx + ay * by + az * bz )
        /// //
        /// //-----------------------------------------------------------------------------
        /// 
        /// %a = "1 1 0";
        /// %b = "2 0 1";
        /// 
        /// // %r = "( 1 * 2 + 1 * 0 + 0 * 1 )";
        /// // %r = 2;
        /// %r = VectorDot( %a, %b );
        /// </code>
        public static float VectorDot(Point3F a, Point3F b) {
a.Alloc();b.Alloc();             InternalUnsafeMethods.VectorDot__Args _args = new InternalUnsafeMethods.VectorDot__Args() {
                a = a.internalStructPtr,
                b = b.internalStructPtr,
             };
             float _engineResult = InternalUnsafeMethods.VectorDot()(_args);
a.Free();b.Free();             return _engineResult;
        }

        /// <description>
        /// Brings a vector into its unit form, i.e. such that it has the magnitute 1.
        /// </description>
        /// <param name="v">The vector to normalize.</param>
        /// <returns>The vector<paramref name="" /> v scaled to length 1.
        /// 
        /// </returns>
        /// <code>
        /// //-----------------------------------------------------------------------------
        /// //
        /// // VectorNormalize( %a );
        /// //
        /// // The normalized vector a, (ax, ay, az), is:
        /// //
        /// //     a^ = a / ||a||
        /// //        = ( ax / ||a||, ay / ||a||, az / ||a|| )
        /// //
        /// //-----------------------------------------------------------------------------
        /// 
        /// %a = "1 1 0";
        /// %l = 1.414;
        /// 
        /// // %r = "( 1 / 1.141, 1 / 1.141, 0 / 1.141 )";
        /// // %r = "0.707 0.707 0";
        /// %r = VectorNormalize( %a );
        /// </code>
        public static Point3F VectorNormalize(Point3F v) {
v.Alloc();             InternalUnsafeMethods.VectorNormalize__Args _args = new InternalUnsafeMethods.VectorNormalize__Args() {
                v = v.internalStructPtr,
             };
             Point3F.InternalStruct _engineResult = InternalUnsafeMethods.VectorNormalize()(_args);
v.Free();             return new Point3F(_engineResult);
        }

        /// <description>
        /// Divide two vectors.
        /// </description>
        /// <param name="a">The first vector.</param>
        /// <param name="b">The second vector.</param>
        /// <returns>The vector<paramref name="" /> a / </returns>
        /// <code>
        /// //-----------------------------------------------------------------------------
        /// //
        /// // VectorDiv( %a, %b );
        /// //
        /// // The division of vector a, (ax, ay, az), and vector b, (bx, by, bz) is:
        /// //
        /// //     a * b = ( ax / bx, ay / by, az / bz )
        /// //
        /// //-----------------------------------------------------------------------------
        /// 
        /// %a = "1 1 1";
        /// %b = "2 2 2";
        /// 
        /// // %r = "( 1 / 2, 1 / 2, 1 / 2 )";
        /// // %r = "0.5 0.5 0.5";
        /// %r = VectorDiv( %a, %b );
        /// </code>
        public static Point3F VectorDiv(Point3F a, Point3F b) {
a.Alloc();b.Alloc();             InternalUnsafeMethods.VectorDiv__Args _args = new InternalUnsafeMethods.VectorDiv__Args() {
                a = a.internalStructPtr,
                b = b.internalStructPtr,
             };
             Point3F.InternalStruct _engineResult = InternalUnsafeMethods.VectorDiv()(_args);
a.Free();b.Free();             return new Point3F(_engineResult);
        }

        /// <description>
        /// Multiplies two vectors.
        /// </description>
        /// <param name="a">The first vector.</param>
        /// <param name="b">The second vector.</param>
        /// <returns>The vector<paramref name="" /> a * </returns>
        /// <code>
        /// //-----------------------------------------------------------------------------
        /// //
        /// // VectorMul( %a, %b );
        /// //
        /// // The multiplication of vector a, (ax, ay, az), and vector b, (bx, by, bz) is:
        /// //
        /// //     a * b = ( ax * bx, ay * by, az * bz )
        /// //
        /// //-----------------------------------------------------------------------------
        /// 
        /// %a = "1 0 0";
        /// %b = "0 1 0";
        /// 
        /// // %r = "( 1 * 0, 0 * 1, 0 * 0 )";
        /// // %r = "0 0 0";
        /// %r = VectorMul( %a, %b );
        /// </code>
        public static Point3F VectorMul(Point3F a, Point3F b) {
a.Alloc();b.Alloc();             InternalUnsafeMethods.VectorMul__Args _args = new InternalUnsafeMethods.VectorMul__Args() {
                a = a.internalStructPtr,
                b = b.internalStructPtr,
             };
             Point3F.InternalStruct _engineResult = InternalUnsafeMethods.VectorMul()(_args);
a.Free();b.Free();             return new Point3F(_engineResult);
        }

        /// <description>
        /// Scales a vector by a scalar.
        /// </description>
        /// <param name="a">The vector to scale.</param>
        /// <param name="scalar">The scale factor.</param>
        /// <returns>The vector<paramref name="" /> a * </returns>
        /// <code>
        /// //-----------------------------------------------------------------------------
        /// //
        /// // VectorScale( %a, %v );
        /// //
        /// // Scaling vector a, (ax, ay, az), but the scalar, v, is:
        /// //
        /// //     a * v = ( ax * v, ay * v, az * v )
        /// //
        /// //-----------------------------------------------------------------------------
        /// 
        /// %a = "1 1 0";
        /// %v = "2";
        /// 
        /// // %r = "( 1 * 2, 1 * 2, 0 * 2 )";
        /// // %r = "2 2 0";
        /// %r = VectorScale( %a, %v );
        /// </code>
        public static Point3F VectorScale(Point3F a, float scalar) {
a.Alloc();             InternalUnsafeMethods.VectorScale__Args _args = new InternalUnsafeMethods.VectorScale__Args() {
                a = a.internalStructPtr,
                scalar = scalar,
             };
             Point3F.InternalStruct _engineResult = InternalUnsafeMethods.VectorScale()(_args);
a.Free();             return new Point3F(_engineResult);
        }

        /// <description>
        /// Subtract two vectors.
        /// </description>
        /// <param name="a">The first vector.</param>
        /// <param name="b">The second vector.</param>
        /// <returns>The vector<paramref name="" /> a - </returns>
        /// <code>
        /// //-----------------------------------------------------------------------------
        /// //
        /// // VectorSub( %a, %b );
        /// //
        /// // The difference of vector a, (ax, ay, az), and vector b, (bx, by, bz) is:
        /// //
        /// //     a - b = ( ax - bx, ay - by, az - bz )
        /// //
        /// //-----------------------------------------------------------------------------
        /// 
        /// %a = "1 0 0";
        /// %b = "0 1 0";
        /// 
        /// // %r = "( 1 - 0, 0 - 1, 0 - 0 )";
        /// // %r = "1 -1 0";
        /// %r = VectorSub( %a, %b );
        /// </code>
        public static Point3F VectorSub(Point3F a, Point3F b) {
a.Alloc();b.Alloc();             InternalUnsafeMethods.VectorSub__Args _args = new InternalUnsafeMethods.VectorSub__Args() {
                a = a.internalStructPtr,
                b = b.internalStructPtr,
             };
             Point3F.InternalStruct _engineResult = InternalUnsafeMethods.VectorSub()(_args);
a.Free();b.Free();             return new Point3F(_engineResult);
        }

        /// <description>
        /// Add two vectors.
        /// </description>
        /// <param name="a">The first vector.</param>
        /// <param name="b">The second vector.</param>
        /// <returns>The vector<paramref name="" /> a + </returns>
        /// <code>
        /// //-----------------------------------------------------------------------------
        /// //
        /// // VectorAdd( %a, %b );
        /// //
        /// // The sum of vector a, (ax, ay, az), and vector b, (bx, by, bz) is:
        /// //
        /// //     a + b = ( ax + bx, ay + by, az + bz )
        /// //
        /// //-----------------------------------------------------------------------------
        /// %a = "1 0 0";
        /// %b = "0 1 0";
        /// 
        /// // %r = "( 1 + 0, 0 + 1, 0 + 0 )";
        /// // %r = "1 1 0";
        /// %r = VectorAdd( %a, %b );
        /// </code>
        public static Point3F VectorAdd(Point3F a, Point3F b) {
a.Alloc();b.Alloc();             InternalUnsafeMethods.VectorAdd__Args _args = new InternalUnsafeMethods.VectorAdd__Args() {
                a = a.internalStructPtr,
                b = b.internalStructPtr,
             };
             Point3F.InternalStruct _engineResult = InternalUnsafeMethods.VectorAdd()(_args);
a.Free();b.Free();             return new Point3F(_engineResult);
        }

        /// <description>
        /// Gets the direction from the rotation's angles.
        /// </description>
        /// <param name="Our">rotation.</param>
        public static Point3F GetRotationDirection(RotationF rot) {
rot.Alloc();             InternalUnsafeMethods.GetRotationDirection__Args _args = new InternalUnsafeMethods.GetRotationDirection__Args() {
                rot = rot.internalStructPtr,
             };
             Point3F.InternalStruct _engineResult = InternalUnsafeMethods.GetRotationDirection()(_args);
rot.Free();             return new Point3F(_engineResult);
        }

        /// <description>
        /// Gets the up vector of a rotation.
        /// </description>
        /// <param name="Our">rotation.</param>
        public static Point3F GetRotationUpVector(RotationF rot) {
rot.Alloc();             InternalUnsafeMethods.GetRotationUpVector__Args _args = new InternalUnsafeMethods.GetRotationUpVector__Args() {
                rot = rot.internalStructPtr,
             };
             Point3F.InternalStruct _engineResult = InternalUnsafeMethods.GetRotationUpVector()(_args);
rot.Free();             return new Point3F(_engineResult);
        }

        /// <description>
        /// Gets the right vector of a rotation.
        /// </description>
        /// <param name="Our">rotation.</param>
        public static Point3F GetRotationRightVector(RotationF rot) {
rot.Alloc();             InternalUnsafeMethods.GetRotationRightVector__Args _args = new InternalUnsafeMethods.GetRotationRightVector__Args() {
                rot = rot.internalStructPtr,
             };
             Point3F.InternalStruct _engineResult = InternalUnsafeMethods.GetRotationRightVector()(_args);
rot.Free();             return new Point3F(_engineResult);
        }

        /// <description>
        /// Get the forward vector of a rotation.
        /// </description>
        public static Point3F GetRotationForwardVector(RotationF rot) {
rot.Alloc();             InternalUnsafeMethods.GetRotationForwardVector__Args _args = new InternalUnsafeMethods.GetRotationForwardVector__Args() {
                rot = rot.internalStructPtr,
             };
             Point3F.InternalStruct _engineResult = InternalUnsafeMethods.GetRotationForwardVector()(_args);
rot.Free();             return new Point3F(_engineResult);
        }

        /// <description>
        /// Sets the up vector of the rotation.
        /// </description>
        /// <param name="Starting">rotation.</param>
        /// <param name="New">up vector.</param>
        /// <returns>New rotation with the set up vector.</returns>
        public static RotationF SetRotationUpVector(RotationF rot, Point3F upVec) {
rot.Alloc();upVec.Alloc();             InternalUnsafeMethods.SetRotationUpVector__Args _args = new InternalUnsafeMethods.SetRotationUpVector__Args() {
                rot = rot.internalStructPtr,
                upVec = upVec.internalStructPtr,
             };
             RotationF.InternalStruct _engineResult = InternalUnsafeMethods.SetRotationUpVector()(_args);
rot.Free();upVec.Free();             return new RotationF(_engineResult);
        }

        /// <description>
        /// Sets the right vector of the rotation.
        /// </description>
        /// <param name="Starting">rotation.</param>
        /// <param name="New">up vector.</param>
        /// <returns>New rotation with the set right vector.</returns>
        public static RotationF SetRotationRightVector(RotationF rot, Point3F rightVec) {
rot.Alloc();rightVec.Alloc();             InternalUnsafeMethods.SetRotationRightVector__Args _args = new InternalUnsafeMethods.SetRotationRightVector__Args() {
                rot = rot.internalStructPtr,
                rightVec = rightVec.internalStructPtr,
             };
             RotationF.InternalStruct _engineResult = InternalUnsafeMethods.SetRotationRightVector()(_args);
rot.Free();rightVec.Free();             return new RotationF(_engineResult);
        }

        /// <description>
        /// Provides a rotation orientation to look at a target from a given position.
        /// </description>
        /// <param name="origin">Position of the object doing the looking.</param>
        /// <param name="target">Position to be looked at.</param>
        /// <param name="up">The up angle to orient the rotation.</param>
        /// <returns>v orientation result.</returns>
        public static RotationF RotationLookAt(Point3F origin = null, Point3F target = null, Point3F up = null) {
origin = origin ?? new Point3F("0 0 0");
origin.Alloc();target = target ?? new Point3F("0 0 0");
target.Alloc();up = up ?? new Point3F("0 0 0");
up.Alloc();             InternalUnsafeMethods.RotationLookAt__Args _args = new InternalUnsafeMethods.RotationLookAt__Args() {
                origin = origin.internalStructPtr,
                target = target.internalStructPtr,
                up = up.internalStructPtr,
             };
             RotationF.InternalStruct _engineResult = InternalUnsafeMethods.RotationLookAt()(_args);
origin.Free();target.Free();up.Free();             return new RotationF(_engineResult);
        }

        /// <description>
        /// Interpolates between two rotations.
        /// </description>
        /// <param name="a">Rotation one.</param>
        /// <param name="b">Rotation two.</param>
        /// <param name="factor">The amount to interpolate between the two.</param>
        /// <returns>v, interpolated result.</returns>
        public static RotationF InterpolateRotation(RotationF a, RotationF b, float factor) {
a.Alloc();b.Alloc();             InternalUnsafeMethods.InterpolateRotation__Args _args = new InternalUnsafeMethods.InterpolateRotation__Args() {
                a = a.internalStructPtr,
                b = b.internalStructPtr,
                factor = factor,
             };
             RotationF.InternalStruct _engineResult = InternalUnsafeMethods.InterpolateRotation()(_args);
a.Free();b.Free();             return new RotationF(_engineResult);
        }

        /// <description>
        /// Subtracts two rotations.
        /// </description>
        /// <param name="a">Rotation one.</param>
        /// <param name="b">Rotation two.</param>
        /// <returns>v difference of both rotations.</returns>
        public static RotationF SubtractRotation(RotationF a, RotationF b) {
a.Alloc();b.Alloc();             InternalUnsafeMethods.SubtractRotation__Args _args = new InternalUnsafeMethods.SubtractRotation__Args() {
                a = a.internalStructPtr,
                b = b.internalStructPtr,
             };
             RotationF.InternalStruct _engineResult = InternalUnsafeMethods.SubtractRotation()(_args);
a.Free();b.Free();             return new RotationF(_engineResult);
        }

        /// <description>
        /// Adds two rotations together.
        /// </description>
        /// <param name="a">Rotation one.</param>
        /// <param name="b">Rotation two.</param>
        /// <returns>v sum of both rotations.</returns>
        public static RotationF AddRotation(RotationF a, RotationF b) {
a.Alloc();b.Alloc();             InternalUnsafeMethods.AddRotation__Args _args = new InternalUnsafeMethods.AddRotation__Args() {
                a = a.internalStructPtr,
                b = b.internalStructPtr,
             };
             RotationF.InternalStruct _engineResult = InternalUnsafeMethods.AddRotation()(_args);
a.Free();b.Free();             return new RotationF(_engineResult);
        }

        /// <description>
        /// Returns signed angle between two vectors, using a normal for orientation.
        /// </description>
        /// <param name="vecA">First input vector.</param>
        /// <param name="vecB">Second input vector.</param>
        /// <param name="norm">Normal/Cross Product vector.</param>
        /// <returns>Angle between both vectors in radians.</returns>
        public static float MGetSignedAngleBetweenVectors(Point3F vecA = null, Point3F vecB = null, Point3F norm = null) {
vecA = vecA ?? new Point3F("0 0 0");
vecA.Alloc();vecB = vecB ?? new Point3F("0 0 0");
vecB.Alloc();norm = norm ?? new Point3F("0 0 0");
norm.Alloc();             InternalUnsafeMethods.MGetSignedAngleBetweenVectors__Args _args = new InternalUnsafeMethods.MGetSignedAngleBetweenVectors__Args() {
                vecA = vecA.internalStructPtr,
                vecB = vecB.internalStructPtr,
                norm = norm.internalStructPtr,
             };
             float _engineResult = InternalUnsafeMethods.MGetSignedAngleBetweenVectors()(_args);
vecA.Free();vecB.Free();norm.Free();             return _engineResult;
        }

        /// <description>
        /// Returns angle between two vectors.
        /// </description>
        /// <param name="vecA">First input vector.</param>
        /// <param name="vecB">Second input vector.</param>
        /// <returns>Angle between both vectors in radians.</returns>
        public static float MGetAngleBetweenVectors(Point3F vecA, Point3F vecB) {
vecA.Alloc();vecB.Alloc();             InternalUnsafeMethods.MGetAngleBetweenVectors__Args _args = new InternalUnsafeMethods.MGetAngleBetweenVectors__Args() {
                vecA = vecA.internalStructPtr,
                vecB = vecB.internalStructPtr,
             };
             float _engineResult = InternalUnsafeMethods.MGetAngleBetweenVectors()(_args);
vecA.Free();vecB.Free();             return _engineResult;
        }

        /// <description>
        /// Returns a randomized point inside a sphere of a given radius.
        /// </description>
        /// <param name="radius">The radius of the sphere to find a point in.</param>
        /// <returns>Randomized point inside a sphere.</returns>
        public static Point3F MRandomPointInSphere(float radius) {
             InternalUnsafeMethods.MRandomPointInSphere__Args _args = new InternalUnsafeMethods.MRandomPointInSphere__Args() {
                radius = radius,
             };
             Point3F.InternalStruct _engineResult = InternalUnsafeMethods.MRandomPointInSphere()(_args);
             return new Point3F(_engineResult);
        }

        /// <description>
        /// Returns a randomized direction based on a starting axis and the min/max angles.
        /// </description>
        /// <param name="axis">Main axis to deviate the direction from.</param>
        /// <param name="angleMin">minimum amount of deviation from the axis.</param>
        /// <param name="angleMax">maximum amount of deviation from the axis.</param>
        /// <returns>Randomized direction vector.</returns>
        public static Point3F MRandomDir(Point3F axis, float angleMin, float angleMax) {
axis.Alloc();             InternalUnsafeMethods.MRandomDir__Args _args = new InternalUnsafeMethods.MRandomDir__Args() {
                axis = axis.internalStructPtr,
                angleMin = angleMin,
                angleMax = angleMax,
             };
             Point3F.InternalStruct _engineResult = InternalUnsafeMethods.MRandomDir()(_args);
axis.Free();             return new Point3F(_engineResult);
        }

        /// <description>
        /// Returns whether the value is an exact power of two.
        /// </description>
        /// <param name="v">Input value.</param>
        /// <returns>Whether the specified value is an exact power of two.</returns>
        public static bool MIsPow2(int v) {
             InternalUnsafeMethods.MIsPow2__Args _args = new InternalUnsafeMethods.MIsPow2__Args() {
                v = v,
             };
             bool _engineResult = InternalUnsafeMethods.MIsPow2()(_args);
             return _engineResult;
        }

        /// <description>
        /// Return the value of 2*PI (full-circle in radians).
        /// </description>
        /// <returns>The value of 2*PI.</returns>
        public static float M2Pi() {
             InternalUnsafeMethods.M2Pi__Args _args = new InternalUnsafeMethods.M2Pi__Args() {
             };
             float _engineResult = InternalUnsafeMethods.M2Pi()(_args);
             return _engineResult;
        }

        /// <description>
        /// Return the value of PI (half-circle in radians).
        /// </description>
        /// <returns>The value of PI.</returns>
        public static float MPi() {
             InternalUnsafeMethods.MPi__Args _args = new InternalUnsafeMethods.MPi__Args() {
             };
             float _engineResult = InternalUnsafeMethods.MPi()(_args);
             return _engineResult;
        }

        /// <description>
        /// Calculate linearly interpolated value between two specified numbers using specified normalized time.
        /// </description>
        /// <param name="v1">Interpolate From Input value.</param>
        /// <param name="v2">Interpolate To Input value.</param>
        /// <param name="time">Normalized time used to interpolate values (0-1).</param>
        /// <returns>The interpolated value between the two specified values at normalized time t.</returns>
        public static float MLerp(float v1, float v2, float time) {
             InternalUnsafeMethods.MLerp__Args _args = new InternalUnsafeMethods.MLerp__Args() {
                v1 = v1,
                v2 = v2,
                time = time,
             };
             float _engineResult = InternalUnsafeMethods.MLerp()(_args);
             return _engineResult;
        }

        /// <description>
        /// Calculate the lesser of two specified numbers.
        /// </description>
        /// <param name="v1">Input value.</param>
        /// <param name="v2">Input value.</param>
        /// <returns>The lesser value of the two specified values.</returns>
        public static float GetMin(float v1, float v2) {
             InternalUnsafeMethods.GetMin__Args _args = new InternalUnsafeMethods.GetMin__Args() {
                v1 = v1,
                v2 = v2,
             };
             float _engineResult = InternalUnsafeMethods.GetMin()(_args);
             return _engineResult;
        }

        /// <description>
        /// Calculate the greater of two specified numbers.
        /// </description>
        /// <param name="v1">Input value.</param>
        /// <param name="v2">Input value.</param>
        /// <returns>The greater value of the two specified values.</returns>
        public static float GetMax(float v1, float v2) {
             InternalUnsafeMethods.GetMax__Args _args = new InternalUnsafeMethods.GetMax__Args() {
                v1 = v1,
                v2 = v2,
             };
             float _engineResult = InternalUnsafeMethods.GetMax()(_args);
             return _engineResult;
        }

        /// <description>
        /// Wrap the specified value between two bounds.
        /// </description>
        /// <param name="v">Input value.</param>
        /// <param name="min">Minimum Bound.</param>
        /// <param name="max">Maximum Bound.</param>
        /// <returns>The specified value wrapped to the specified bounds.</returns>
        public static int MWrap(int v, int min, int max) {
             InternalUnsafeMethods.MWrap__Args _args = new InternalUnsafeMethods.MWrap__Args() {
                v = v,
                min = min,
                max = max,
             };
             int _engineResult = InternalUnsafeMethods.MWrap()(_args);
             return _engineResult;
        }

        /// <description>
        /// Wrap the specified value between two bounds.
        /// </description>
        /// <param name="v">Input value.</param>
        /// <param name="min">Minimum Bound.</param>
        /// <param name="max">Maximum Bound.</param>
        /// <returns>The specified value wrapped to the specified bounds.</returns>
        public static float MWrapF(float v, float min, float max) {
             InternalUnsafeMethods.MWrapF__Args _args = new InternalUnsafeMethods.MWrapF__Args() {
                v = v,
                min = min,
                max = max,
             };
             float _engineResult = InternalUnsafeMethods.MWrapF()(_args);
             return _engineResult;
        }

        /// <description>
        /// Clamp the specified value between 0 and 1 (inclusive).
        /// </description>
        /// <param name="v">Input value.</param>
        /// <returns>The specified value clamped between 0 and 1 (inclusive).</returns>
        public static float MSaturate(float v) {
             InternalUnsafeMethods.MSaturate__Args _args = new InternalUnsafeMethods.MSaturate__Args() {
                v = v,
             };
             float _engineResult = InternalUnsafeMethods.MSaturate()(_args);
             return _engineResult;
        }

        /// <description>
        /// Clamp the specified value between two bounds.
        /// </description>
        /// <param name="v">Input value.</param>
        /// <param name="min">Minimum Bound.</param>
        /// <param name="max">Maximum Bound.</param>
        /// <returns>The specified value clamped to the specified bounds.</returns>
        public static float MClamp(float v, float min, float max) {
             InternalUnsafeMethods.MClamp__Args _args = new InternalUnsafeMethods.MClamp__Args() {
                v = v,
                min = min,
                max = max,
             };
             float _engineResult = InternalUnsafeMethods.MClamp()(_args);
             return _engineResult;
        }

        /// <description>
        /// Convert specified degrees into radians.
        /// </description>
        /// <param name="degrees">Input Value (in degrees).</param>
        /// <returns>The specified degrees value converted to radians.</returns>
        public static float MDegToRad(float degrees) {
             InternalUnsafeMethods.MDegToRad__Args _args = new InternalUnsafeMethods.MDegToRad__Args() {
                degrees = degrees,
             };
             float _engineResult = InternalUnsafeMethods.MDegToRad()(_args);
             return _engineResult;
        }

        /// <description>
        /// Convert specified radians into degrees.
        /// </description>
        /// <param name="radians">Input Value (in radians).</param>
        /// <returns>The specified radians value converted to degrees.</returns>
        public static float MRadToDeg(float radians) {
             InternalUnsafeMethods.MRadToDeg__Args _args = new InternalUnsafeMethods.MRadToDeg__Args() {
                radians = radians,
             };
             float _engineResult = InternalUnsafeMethods.MRadToDeg()(_args);
             return _engineResult;
        }

        /// <description>
        /// Calculate the arc-tangent (slope) of a line defined by rise and run.
        /// </description>
        /// <param name="rise">of line.</param>
        /// <param name="run">of line.</param>
        /// <returns>The arc-tangent (slope) of a line defined by rise and run.</returns>
        public static float MAtan(float rise, float run) {
             InternalUnsafeMethods.MAtan__Args _args = new InternalUnsafeMethods.MAtan__Args() {
                rise = rise,
                run = run,
             };
             float _engineResult = InternalUnsafeMethods.MAtan()(_args);
             return _engineResult;
        }

        /// <description>
        /// Calculate the arc-cosine of v.
        /// </description>
        /// <param name="v">Input Value (in radians).</param>
        /// <returns>The arc-cosine of the input value.</returns>
        public static float MAcos(float v) {
             InternalUnsafeMethods.MAcos__Args _args = new InternalUnsafeMethods.MAcos__Args() {
                v = v,
             };
             float _engineResult = InternalUnsafeMethods.MAcos()(_args);
             return _engineResult;
        }

        /// <description>
        /// Calculate the arc-sine of v.
        /// </description>
        /// <param name="v">Input Value (in radians).</param>
        /// <returns>The arc-sine of the input value.</returns>
        public static float MAsin(float v) {
             InternalUnsafeMethods.MAsin__Args _args = new InternalUnsafeMethods.MAsin__Args() {
                v = v,
             };
             float _engineResult = InternalUnsafeMethods.MAsin()(_args);
             return _engineResult;
        }

        /// <description>
        /// Calculate the tangent of v.
        /// </description>
        /// <param name="v">Input Value (in radians).</param>
        /// <returns>The tangent of the input value.</returns>
        public static float MTan(float v) {
             InternalUnsafeMethods.MTan__Args _args = new InternalUnsafeMethods.MTan__Args() {
                v = v,
             };
             float _engineResult = InternalUnsafeMethods.MTan()(_args);
             return _engineResult;
        }

        /// <description>
        /// Calculate the cosine of v.
        /// </description>
        /// <param name="v">Input Value (in radians).</param>
        /// <returns>The cosine of the input value.</returns>
        public static float MCos(float v) {
             InternalUnsafeMethods.MCos__Args _args = new InternalUnsafeMethods.MCos__Args() {
                v = v,
             };
             float _engineResult = InternalUnsafeMethods.MCos()(_args);
             return _engineResult;
        }

        /// <description>
        /// Calculate the sine of v.
        /// </description>
        /// <param name="v">Input Value (in radians).</param>
        /// <returns>The sine of the input value.</returns>
        public static float MSin(float v) {
             InternalUnsafeMethods.MSin__Args _args = new InternalUnsafeMethods.MSin__Args() {
                v = v,
             };
             float _engineResult = InternalUnsafeMethods.MSin()(_args);
             return _engineResult;
        }

        /// <description>
        /// Calculate the natural logarithm of v.
        /// </description>
        /// <param name="v">Input Value.</param>
        /// <returns>The natural logarithm of the input value.</returns>
        public static float MLog(float v) {
             InternalUnsafeMethods.MLog__Args _args = new InternalUnsafeMethods.MLog__Args() {
                v = v,
             };
             float _engineResult = InternalUnsafeMethods.MLog()(_args);
             return _engineResult;
        }

        /// <description>
        /// Calculate b raised to the p-th power.
        /// </description>
        /// <param name="v">Input Value.</param>
        /// <param name="p">Power to raise value by.</param>
        /// <returns>v raised to the p-th power.</returns>
        public static float MPow(float v, float p) {
             InternalUnsafeMethods.MPow__Args _args = new InternalUnsafeMethods.MPow__Args() {
                v = v,
                p = p,
             };
             float _engineResult = InternalUnsafeMethods.MPow()(_args);
             return _engineResult;
        }

        /// <description>
        /// Calculate the square-root of v.
        /// </description>
        /// <param name="v">Input Value.</param>
        /// <returns>The square-root of the input value.</returns>
        public static float MSqrt(float v) {
             InternalUnsafeMethods.MSqrt__Args _args = new InternalUnsafeMethods.MSqrt__Args() {
                v = v,
             };
             float _engineResult = InternalUnsafeMethods.MSqrt()(_args);
             return _engineResult;
        }

        /// <description>
        /// Calculate the remainder of v/d.
        /// </description>
        /// <param name="v">Input Value.</param>
        /// <param name="d">Divisor Value.</param>
        /// <returns>The remainder of v/d.</returns>
        public static float MFMod(float v, float d) {
             InternalUnsafeMethods.MFMod__Args _args = new InternalUnsafeMethods.MFMod__Args() {
                v = v,
                d = d,
             };
             float _engineResult = InternalUnsafeMethods.MFMod()(_args);
             return _engineResult;
        }

        /// <description>
        /// Calculate absolute value of specified value.
        /// </description>
        /// <param name="v">Input Value.</param>
        /// <returns>Absolute value of specified value.</returns>
        public static float MAbs(float v) {
             InternalUnsafeMethods.MAbs__Args _args = new InternalUnsafeMethods.MAbs__Args() {
                v = v,
             };
             float _engineResult = InternalUnsafeMethods.MAbs()(_args);
             return _engineResult;
        }

        /// <description>
        /// Formats the specified number to the given number of decimal places.
        /// </description>
        /// <param name="v">Number to format.</param>
        /// <param name="precision">Number of decimal places to format to (1-9).</param>
        /// <returns>Number formatted to the specified number of decimal places.</returns>
        public static string MFloatLength(float v, uint precision) {
             InternalUnsafeMethods.MFloatLength__Args _args = new InternalUnsafeMethods.MFloatLength__Args() {
                v = v,
                precision = precision,
             };
             IntPtr _engineResult = InternalUnsafeMethods.MFloatLength()(_args);
             return StringMarshal.IntPtrToUtf8String(_engineResult);
        }

        /// <description>
        /// Round v up to the nearest integer.
        /// </description>
        /// <param name="v">Number to convert to integer.</param>
        /// <returns>Number converted to integer.</returns>
        public static int MCeil(float v) {
             InternalUnsafeMethods.MCeil__Args _args = new InternalUnsafeMethods.MCeil__Args() {
                v = v,
             };
             int _engineResult = InternalUnsafeMethods.MCeil()(_args);
             return _engineResult;
        }

        /// <description>
        /// Round v to the nth decimal place or the nearest whole number by default.
        /// </description>
        /// <param name="v">Value to roundn</param>
        /// <param name="n">Number of decimal places to round to, 0 by defaultn</param>
        /// <returns>The rounded value as a S32.</returns>
        public static float MRoundColour(float v, int n = 0) {
             InternalUnsafeMethods.MRoundColour__Args _args = new InternalUnsafeMethods.MRoundColour__Args() {
                v = v,
                n = n,
             };
             float _engineResult = InternalUnsafeMethods.MRoundColour()(_args);
             return _engineResult;
        }

        /// <description>
        /// Round v to the nearest number based on the delta
        /// </description>
        /// <param name="v">Value to round</param>
        /// <param name="d">Delta use when rounding</param>
        /// <returns>The rounded value as a S32.</returns>
        public static int MRoundDelta(float v = 0f, int d = 1) {
             InternalUnsafeMethods.MRoundDelta__Args _args = new InternalUnsafeMethods.MRoundDelta__Args() {
                v = v,
                d = d,
             };
             int _engineResult = InternalUnsafeMethods.MRoundDelta()(_args);
             return _engineResult;
        }

        /// <description>
        /// Round v to the nth decimal place or the nearest whole number by default.
        /// </description>
        /// <param name="v">Value to roundn</param>
        /// <returns>The rounded value as a S32.</returns>
        public static int MRound(float v) {
             InternalUnsafeMethods.MRound__Args _args = new InternalUnsafeMethods.MRound__Args() {
                v = v,
             };
             int _engineResult = InternalUnsafeMethods.MRound()(_args);
             return _engineResult;
        }

        /// <description>
        /// Round v down to the nearest integer.
        /// </description>
        /// <param name="v">Number to convert to integer.</param>
        /// <returns>Number converted to integer.</returns>
        public static int MFloor(float v) {
             InternalUnsafeMethods.MFloor__Args _args = new InternalUnsafeMethods.MFloor__Args() {
                v = v,
             };
             int _engineResult = InternalUnsafeMethods.MFloor()(_args);
             return _engineResult;
        }

        /// <description>
        /// Solve a quartic equation (4th degree polynomial) of form a*x^4 + b*x^3 + c*x^2 + d*x + e = 0.
        /// </description>
        /// <param name="a">First Coefficient.</param>
        /// <param name="b">Second Coefficient.</param>
        /// <param name="c">Third Coefficient.</param>
        /// <param name="d">Fourth Coefficient.</param>
        /// <param name="e">Fifth Coefficient.</param>
        /// <returns>A 5-tuple, containing: (sol x0 x1 x2 c3). (sol) is the number of solutions(being 0, 1, 2, 3 or 4), and (x0), (x1), (x2) and (x3) are the solutions, if any.</returns>
        public static string MSolveQuartic(float a, float b, float c, float d, float e) {
             InternalUnsafeMethods.MSolveQuartic__Args _args = new InternalUnsafeMethods.MSolveQuartic__Args() {
                a = a,
                b = b,
                c = c,
                d = d,
                e = e,
             };
             IntPtr _engineResult = InternalUnsafeMethods.MSolveQuartic()(_args);
             return StringMarshal.IntPtrToUtf8String(_engineResult);
        }

        /// <description>
        /// Solve a cubic equation (3rd degree polynomial) of form a*x^3 + b*x^2 + c*x + d = 0.
        /// </description>
        /// <param name="a">First Coefficient.</param>
        /// <param name="b">Second Coefficient.</param>
        /// <param name="c">Third Coefficient.</param>
        /// <param name="d">Fourth Coefficient.</param>
        /// <returns>A 4-tuple, containing: (sol x0 x1 x2). (sol) is the number of solutions(being 0, 1, 2 or 3), and (x0), (x1) and (x2) are the solutions, if any.</returns>
        public static string MSolveCubic(float a, float b, float c, float d) {
             InternalUnsafeMethods.MSolveCubic__Args _args = new InternalUnsafeMethods.MSolveCubic__Args() {
                a = a,
                b = b,
                c = c,
                d = d,
             };
             IntPtr _engineResult = InternalUnsafeMethods.MSolveCubic()(_args);
             return StringMarshal.IntPtrToUtf8String(_engineResult);
        }

        /// <description>
        /// Solve a quadratic equation (2nd degree polynomial) of form a*x^2 + b*x + c = 0.
        /// </description>
        /// <param name="a">First Coefficient.</param>
        /// <param name="b">Second Coefficient.</param>
        /// <param name="c">Third Coefficient.</param>
        /// <returns>A triple, containing: (sol x0 x1). (sol) is the number of solutions(being 0, 1, or 2), and (x0) and (x1) are the solutions, if any.</returns>
        public static string MSolveQuadratic(float a, float b, float c) {
             InternalUnsafeMethods.MSolveQuadratic__Args _args = new InternalUnsafeMethods.MSolveQuadratic__Args() {
                a = a,
                b = b,
                c = c,
             };
             IntPtr _engineResult = InternalUnsafeMethods.MSolveQuadratic()(_args);
             return StringMarshal.IntPtrToUtf8String(_engineResult);
        }

        /// <description>
        /// (pattern, [state]) -
        /// </description>
        /// <summary>Enable sampling for all keys that match the given name pattern. Slashes are treated as separators.</summary>
        /// <description>
        /// 
        /// </description>
        public static void EnableSamples(string pattern, bool state = true) {
             InternalUnsafeMethods.EnableSamples__Args _args = new InternalUnsafeMethods.EnableSamples__Args() {
                pattern = pattern,
                state = state,
             };
             InternalUnsafeMethods.EnableSamples()(_args);
        }

        /// <description>
        /// ()
        /// </description>
        /// <summary>Stops the rendering sampler</summary>
        /// <description>
        /// 
        /// </description>
        public static void StopSampling() {
             InternalUnsafeMethods.StopSampling__Args _args = new InternalUnsafeMethods.StopSampling__Args() {
             };
             InternalUnsafeMethods.StopSampling()(_args);
        }

        /// <description>
        /// (location, [backend]) -
        /// </description>
        /// <summary>Takes a string informing the backend where to store sample data and optionally a name of the specific logging backend to use.  The default is the CSV backend. In most cases, the logging store will be a file name.</summary>
        /// <code>
        /// beginSampling( "mysamples.csv" );
        /// </code>
        public static void BeginSampling(string location, string backend = "CSV") {
             InternalUnsafeMethods.BeginSampling__Args _args = new InternalUnsafeMethods.BeginSampling__Args() {
                location = location,
                backend = backend,
             };
             InternalUnsafeMethods.BeginSampling()(_args);
        }

        /// <description>
        /// ()
        /// </description>
        /// <summary>Reset FPS stats (fps::)</summary>
        /// <description>
        /// 
        /// </description>
        public static void ResetFPSTracker() {
             InternalUnsafeMethods.ResetFPSTracker__Args _args = new InternalUnsafeMethods.ResetFPSTracker__Args() {
             };
             InternalUnsafeMethods.ResetFPSTracker()(_args);
        }

        /// <summary>Dump the current contents of the networked string table to the console.</summary>
        /// <description>
        /// The results are returned in three columns.  The first column is the network string ID.  The second column is the string itself.  The third column is the reference count to the network string.
        /// </description>
        /// <remarks> This function is available only in debug builds.
        /// 
        /// </remarks>
        public static void DumpNetStringTable() {
             InternalUnsafeMethods.DumpNetStringTable__Args _args = new InternalUnsafeMethods.DumpNetStringTable__Args() {
             };
             InternalUnsafeMethods.DumpNetStringTable()(_args);
        }

        /// <description>
        /// allowConnections(bool allow)
        /// </description>
        /// <summary>Sets whether or not the global NetInterface allows connections from remote hosts.</summary>
        /// <description>
        /// 
        /// </description>
        /// <param name="allow">Set to true to allow remote connections.</param>
        public static void AllowConnections(bool allow) {
             InternalUnsafeMethods.AllowConnections__Args _args = new InternalUnsafeMethods.AllowConnections__Args() {
                allow = allow,
             };
             InternalUnsafeMethods.AllowConnections()(_args);
        }

        /// <summary>Returns the current %ActionMap.</summary>
        /// <description>
        /// 
        /// </description>
        /// <see cref="ActionMap" />
        public static ActionMap GetCurrentActionMap() {
             InternalUnsafeMethods.GetCurrentActionMap__Args _args = new InternalUnsafeMethods.GetCurrentActionMap__Args() {
             };
             IntPtr _engineResult = InternalUnsafeMethods.GetCurrentActionMap()(_args);
             return new ActionMap(_engineResult);
        }

        /// <summary>Compiles a LSO language file. if createIndex is true, will also create languageMap.cs with the global variables for each string index. The input file must follow this example layout: TXT_HELLO_WORLD = Hello world in english!</summary>
        public static void CompileLanguage(string inputFile, bool createMap = false) {
             InternalUnsafeMethods.CompileLanguage__Args _args = new InternalUnsafeMethods.CompileLanguage__Args() {
                inputFile = inputFile,
                createMap = createMap,
             };
             InternalUnsafeMethods.CompileLanguage()(_args);
        }

        /// <description>
        /// (string LangTable)
        /// </description>
        /// <summary>Sets the primary LangTable used by the game</summary>
        /// <description>
        /// 
        /// </description>
        /// <param name="LangTable">ID of the core LangTable</param>
        public static void SetCoreLangTable(string lgTable) {
             InternalUnsafeMethods.SetCoreLangTable__Args _args = new InternalUnsafeMethods.SetCoreLangTable__Args() {
                lgTable = lgTable,
             };
             InternalUnsafeMethods.SetCoreLangTable()(_args);
        }

        /// <description>
        /// ()
        /// </description>
        /// <summary>Gets the primary LangTable used by the game</summary>
        /// <description>
        /// 
        /// </description>
        /// <returns>ID of the core LangTable</returns>
        public static int GetCoreLangTable() {
             InternalUnsafeMethods.GetCoreLangTable__Args _args = new InternalUnsafeMethods.GetCoreLangTable__Args() {
             };
             int _engineResult = InternalUnsafeMethods.GetCoreLangTable()(_args);
             return _engineResult;
        }

        /// <description>
        /// ()
        /// </description>
        /// <summary>Dumps information about String memory usage</summary>
        /// <description>
        /// 
        /// </description>
        public static void DumpStringMemStats() {
             InternalUnsafeMethods.DumpStringMemStats__Args _args = new InternalUnsafeMethods.DumpStringMemStats__Args() {
             };
             InternalUnsafeMethods.DumpStringMemStats()(_args);
        }

        /// <description>
        /// ()
        /// </description>
        public static void SbmDumpStrings() {
             InternalUnsafeMethods.SbmDumpStrings__Args _args = new InternalUnsafeMethods.SbmDumpStrings__Args() {
             };
             InternalUnsafeMethods.SbmDumpStrings()(_args);
        }

        /// <description>
        /// ()
        /// </description>
        public static void SbmDumpStats() {
             InternalUnsafeMethods.SbmDumpStats__Args _args = new InternalUnsafeMethods.SbmDumpStats__Args() {
             };
             InternalUnsafeMethods.SbmDumpStats()(_args);
        }

        /// <description>
        /// Force the resource at specified input path to be reloaded
        /// </description>
        /// <param name="path">Path to the resource to be reloaded</param>
        /// <code>
        /// reloadResource( "art/shapes/box.dts" );
        /// </code>
        /// <remarks> Currently used by editors only
        /// </remarks>
        public static void ReloadResource(string path) {
             InternalUnsafeMethods.ReloadResource__Args _args = new InternalUnsafeMethods.ReloadResource__Args() {
                path = path,
             };
             InternalUnsafeMethods.ReloadResource()(_args);
        }

        /// <summary>List the currently managed resources</summary>
        /// <description>
        /// Currently used by editors only, internal
        /// </description>
        public static void ResourceDump() {
             InternalUnsafeMethods.ResourceDump__Args _args = new InternalUnsafeMethods.ResourceDump__Args() {
             };
             InternalUnsafeMethods.ResourceDump()(_args);
        }

        /// 
        public static int GetMaxFrameAllocation() {
             InternalUnsafeMethods.GetMaxFrameAllocation__Args _args = new InternalUnsafeMethods.GetMaxFrameAllocation__Args() {
             };
             int _engineResult = InternalUnsafeMethods.GetMaxFrameAllocation()(_args);
             return _engineResult;
        }

        /// <description>
        /// (bool enabled)
        /// </description>
        /// <summary>Enables logging of the connection protocols</summary>
        /// <description>
        /// When enabled a lot of network debugging information is sent to the console.
        /// </description>
        /// <param name="enabled">True to enable, false to disable</param>
        public static void DNetSetLogging(bool enabled) {
             InternalUnsafeMethods.DNetSetLogging__Args _args = new InternalUnsafeMethods.DNetSetLogging__Args() {
                enabled = enabled,
             };
             InternalUnsafeMethods.DNetSetLogging()(_args);
        }

        /// <summary>Gets a byte-based stock color by name.</summary>
        /// <description>
        /// 
        /// </description>
        /// <param name="stockColorName">- The stock color name to retrieve.</param>
        /// <returns>The stock color that matches the specified color name.  Returns nothing if the color name is not found.</returns>
        public static ColorI GetStockColorI(string stockColorName) {
             InternalUnsafeMethods.GetStockColorI__Args _args = new InternalUnsafeMethods.GetStockColorI__Args() {
                stockColorName = stockColorName,
             };
             ColorI.InternalStruct _engineResult = InternalUnsafeMethods.GetStockColorI()(_args);
             return new ColorI(_engineResult);
        }

        /// <summary>Gets a floating-point-based stock color by name.</summary>
        /// <description>
        /// 
        /// </description>
        /// <param name="stockColorName">- The stock color name to retrieve.</param>
        /// <returns>The stock color that matches the specified color name.  Returns nothing if the color name is not found.</returns>
        public static LinearColorF GetStockColorF(string stockColorName) {
             InternalUnsafeMethods.GetStockColorF__Args _args = new InternalUnsafeMethods.GetStockColorF__Args() {
                stockColorName = stockColorName,
             };
             LinearColorF.InternalStruct _engineResult = InternalUnsafeMethods.GetStockColorF()(_args);
             return new LinearColorF(_engineResult);
        }

        /// <summary>Gets whether the specified name is a stock color or not.</summary>
        /// <description>
        /// 
        /// </description>
        /// <param name="stockColorName">- The stock color name to test for.</param>
        /// <returns>Whether the specified name is a stock color or not.</returns>
        public static bool IsStockColor(string stockColorName) {
             InternalUnsafeMethods.IsStockColor__Args _args = new InternalUnsafeMethods.IsStockColor__Args() {
                stockColorName = stockColorName,
             };
             bool _engineResult = InternalUnsafeMethods.IsStockColor()(_args);
             return _engineResult;
        }

        /// <summary>Gets the stock color name at the specified index.</summary>
        /// <description>
        /// 
        /// </description>
        /// <param name="stockColorIndex">The zero-based index of the stock color name to retrieve.</param>
        /// <returns>The stock color name at the specified index or nothing if the string is invalid.</returns>
        public static string GetStockColorName(int stockColorIndex) {
             InternalUnsafeMethods.GetStockColorName__Args _args = new InternalUnsafeMethods.GetStockColorName__Args() {
                stockColorIndex = stockColorIndex,
             };
             IntPtr _engineResult = InternalUnsafeMethods.GetStockColorName()(_args);
             return StringMarshal.IntPtrToUtf8String(_engineResult);
        }

        /// <summary>Gets a count of available stock colors.</summary>
        /// <description>
        /// 
        /// </description>
        /// <returns>A count of available stock colors.</returns>
        public static int GetStockColorCount() {
             InternalUnsafeMethods.GetStockColorCount__Args _args = new InternalUnsafeMethods.GetStockColorCount__Args() {
             };
             int _engineResult = InternalUnsafeMethods.GetStockColorCount()(_args);
             return _engineResult;
        }

        /// <description>
        /// ()Forcibly disconnects any attached script debugging client.
        /// </description>
        public static void DbgDisconnect() {
             InternalUnsafeMethods.DbgDisconnect__Args _args = new InternalUnsafeMethods.DbgDisconnect__Args() {
             };
             InternalUnsafeMethods.DbgDisconnect()(_args);
        }

        /// <description>
        /// ()Returns true if a script debugging client is connected else return false.
        /// </description>
        public static bool DbgIsConnected() {
             InternalUnsafeMethods.DbgIsConnected__Args _args = new InternalUnsafeMethods.DbgIsConnected__Args() {
             };
             bool _engineResult = InternalUnsafeMethods.DbgIsConnected()(_args);
             return _engineResult;
        }

        /// <description>
        /// ( int port, string password, bool waitForClient )Open a debug server port on the specified port, requiring the specified password, and optionally waiting for the debug client to connect.
        /// </description>
        public static void DbgSetParameters(int port, string password, bool waitForClient = false) {
             InternalUnsafeMethods.DbgSetParameters__Args _args = new InternalUnsafeMethods.DbgSetParameters__Args() {
                port = port,
                password = password,
                waitForClient = waitForClient,
             };
             InternalUnsafeMethods.DbgSetParameters()(_args);
        }

        /// <summary>Initializes and open the telnet console.</summary>
        /// <description>
        /// 
        /// </description>
        /// <param name="port">Port to listen on for console connections (0 will shut down listening).</param>
        /// <param name="consolePass">Password for read/write access to console.</param>
        /// <param name="listenPass">Password for read access to console.</param>
        /// <param name="remoteEcho">[optional] Enable echoing back to the client, off by default.</param>
        public static void TelnetSetParameters(int port, string consolePass, string listenPass, bool remoteEcho = false) {
             InternalUnsafeMethods.TelnetSetParameters__Args _args = new InternalUnsafeMethods.TelnetSetParameters__Args() {
                port = port,
                consolePass = consolePass,
                listenPass = listenPass,
                remoteEcho = remoteEcho,
             };
             InternalUnsafeMethods.TelnetSetParameters()(_args);
        }

        /// <summary>Loads a serialized object from a file.</summary>
        /// <description>
        /// 
        /// </description>
        /// <param name="Name">and path to text file containing the object</param>
        public static SimObject LoadObject(string filename) {
             InternalUnsafeMethods.LoadObject__Args _args = new InternalUnsafeMethods.LoadObject__Args() {
                filename = filename,
             };
             IntPtr _engineResult = InternalUnsafeMethods.LoadObject()(_args);
             return new SimObject(_engineResult);
        }

        /// <summary>Serialize the object to a file.</summary>
        /// <description>
        /// 
        /// </description>
        /// <param name="object">The object to serialize.</param>
        /// <param name="filename">The file name and path.</param>
        public static bool SaveObject(SimObject _object, string filename) {
             InternalUnsafeMethods.SaveObject__Args _args = new InternalUnsafeMethods.SaveObject__Args() {
                _object = _object.ObjectPtr,
                filename = filename,
             };
             bool _engineResult = InternalUnsafeMethods.SaveObject()(_args);
             return _engineResult;
        }

        /// <description>
        /// Call the given function for each instance of the given class.
        /// </description>
        /// <param name="className">Name of the class for which to enumerate instances.</param>
        /// <param name="functionName">Name of function to call and pass each instance of the given class.</param>
        /// <remarks> This function is only available in debug builds and primarily meant as an aid in debugging.</remarks>
        public static void DebugEnumInstances(string className, string functionName) {
             InternalUnsafeMethods.DebugEnumInstances__Args _args = new InternalUnsafeMethods.DebugEnumInstances__Args() {
                className = className,
                functionName = functionName,
             };
             InternalUnsafeMethods.DebugEnumInstances()(_args);
        }

        /// <description>
        /// Delete all the datablocks we've downloaded.
        /// 
        /// This is usually done in preparation of downloading a new set of datablocks, such as occurs on a mission change, but it's also good post-mission cleanup.
        /// </description>
        public static void DeleteDataBlocks() {
             InternalUnsafeMethods.DeleteDataBlocks__Args _args = new InternalUnsafeMethods.DeleteDataBlocks__Args() {
             };
             InternalUnsafeMethods.DeleteDataBlocks()(_args);
        }

        /// <description>
        /// Preload all datablocks in client mode.
        /// 
        /// (Server parameter is set to false).  This will take some time to complete.
        /// </description>
        public static void PreloadClientDataBlocks() {
             InternalUnsafeMethods.PreloadClientDataBlocks__Args _args = new InternalUnsafeMethods.PreloadClientDataBlocks__Args() {
             };
             InternalUnsafeMethods.PreloadClientDataBlocks()(_args);
        }

        /// <description>
        /// ( string name )
        /// </description>
        /// <summary>Return true if the given name makes for a valid object name.</summary>
        /// <description>
        /// 
        /// </description>
        /// <param name="name">Name of object</param>
        /// <returns>True if name is allowed, false if denied (usually because it starts with a number, _, or invalid character</returns>
        public static bool IsValidObjectName(string name) {
             InternalUnsafeMethods.IsValidObjectName__Args _args = new InternalUnsafeMethods.IsValidObjectName__Args() {
                name = name,
             };
             bool _engineResult = InternalUnsafeMethods.IsValidObjectName()(_args);
             return _engineResult;
        }

        /// <description>
        /// ( String baseName, SimSet set, bool searchChildren )
        /// </description>
        /// <summary>Returns a unique unused internal name within the SimSet/Group based on a given base name.</summary>
        /// <description>
        /// 
        /// </description>
        /// <remarks> Currently only used by editors
        /// </remarks>
        public static string GetUniqueInternalName(string baseName, string setString, bool searchChildren) {
             InternalUnsafeMethods.GetUniqueInternalName__Args _args = new InternalUnsafeMethods.GetUniqueInternalName__Args() {
                baseName = baseName,
                setString = setString,
                searchChildren = searchChildren,
             };
             IntPtr _engineResult = InternalUnsafeMethods.GetUniqueInternalName()(_args);
             return StringMarshal.IntPtrToUtf8String(_engineResult);
        }

        /// <description>
        /// ( String baseName )
        /// </description>
        /// <summary>Returns a unique unused SimObject name based on a given base name.</summary>
        /// <description>
        /// 
        /// </description>
        /// <remarks> Currently only used by editors
        /// </remarks>
        public static string GetUniqueName(string baseName) {
             InternalUnsafeMethods.GetUniqueName__Args _args = new InternalUnsafeMethods.GetUniqueName__Args() {
                baseName = baseName,
             };
             IntPtr _engineResult = InternalUnsafeMethods.GetUniqueName()(_args);
             return StringMarshal.IntPtrToUtf8String(_engineResult);
        }

        /// <description>
        /// schedule(time, refobject|0, command, <arg1...argN>)
        /// </description>
        public static int Schedule(params string[] args) { 
            List<string> _argList = new List<string>() {""};
            _argList.AddRange(args);

            StringVector nativeVecArgs = new StringVector {
                ElementCount = (uint)_argList.Count,
                Array = _argList.ToArray(),
                ArraySize = (uint)_argList.Count
            };
            nativeVecArgs.Alloc();
            int _engineResult = InternalUnsafeMethods.Schedule()(ref nativeVecArgs.internalStruct);
            nativeVecArgs.Free();

            return _engineResult;
        }

        /// <description>
        /// getTimeSinceStart(%scheduleId);
        /// </description>
        public static int GetTimeSinceStart(int scheduleId) {
             InternalUnsafeMethods.GetTimeSinceStart__Args _args = new InternalUnsafeMethods.GetTimeSinceStart__Args() {
                scheduleId = scheduleId,
             };
             int _engineResult = InternalUnsafeMethods.GetTimeSinceStart()(_args);
             return _engineResult;
        }

        /// <description>
        /// getScheduleDuration(%scheduleId);
        /// </description>
        public static int GetScheduleDuration(int scheduleId) {
             InternalUnsafeMethods.GetScheduleDuration__Args _args = new InternalUnsafeMethods.GetScheduleDuration__Args() {
                scheduleId = scheduleId,
             };
             int _engineResult = InternalUnsafeMethods.GetScheduleDuration()(_args);
             return _engineResult;
        }

        /// <description>
        /// getEventTimeLeft(scheduleId) Get the time left in ms until this event will trigger.
        /// </description>
        public static int GetEventTimeLeft(int scheduleId) {
             InternalUnsafeMethods.GetEventTimeLeft__Args _args = new InternalUnsafeMethods.GetEventTimeLeft__Args() {
                scheduleId = scheduleId,
             };
             int _engineResult = InternalUnsafeMethods.GetEventTimeLeft()(_args);
             return _engineResult;
        }

        /// <description>
        /// isEventPending(%scheduleId);
        /// </description>
        public static bool IsEventPending(int scheduleId) {
             InternalUnsafeMethods.IsEventPending__Args _args = new InternalUnsafeMethods.IsEventPending__Args() {
                scheduleId = scheduleId,
             };
             bool _engineResult = InternalUnsafeMethods.IsEventPending()(_args);
             return _engineResult;
        }

        /// <description>
        /// cancelAll(objectId): cancel pending events on the specified object.  Events will be automatically cancelled if object is deleted.
        /// </description>
        public static void CancelAll(string objectId) {
             InternalUnsafeMethods.CancelAll__Args _args = new InternalUnsafeMethods.CancelAll__Args() {
                objectId = objectId,
             };
             InternalUnsafeMethods.CancelAll()(_args);
        }

        /// <description>
        /// cancel(eventId)
        /// </description>
        public static void Cancel(int eventId) {
             InternalUnsafeMethods.Cancel__Args _args = new InternalUnsafeMethods.Cancel__Args() {
                eventId = eventId,
             };
             InternalUnsafeMethods.Cancel()(_args);
        }

        /// <description>
        /// spawnObject(class [, dataBlock, name, properties, script])
        /// </description>
        public static int SpawnObject(string spawnClass, string spawnDataBlock = "", string spawnName = "", string spawnProperties = "", string spawnScript = "") {
             InternalUnsafeMethods.SpawnObject__Args _args = new InternalUnsafeMethods.SpawnObject__Args() {
                spawnClass = spawnClass,
                spawnDataBlock = spawnDataBlock,
                spawnName = spawnName,
                spawnProperties = spawnProperties,
                spawnScript = spawnScript,
             };
             int _engineResult = InternalUnsafeMethods.SpawnObject()(_args);
             return _engineResult;
        }

        /// <description>
        /// isObject(object)
        /// </description>
        public static bool IsObject(string objectName) {
             InternalUnsafeMethods.IsObject__Args _args = new InternalUnsafeMethods.IsObject__Args() {
                objectName = objectName,
             };
             bool _engineResult = InternalUnsafeMethods.IsObject()(_args);
             return _engineResult;
        }

        /// <description>
        /// nameToID(object)
        /// </description>
        public static int NameToID(string objectName) {
             InternalUnsafeMethods.NameToID__Args _args = new InternalUnsafeMethods.NameToID__Args() {
                objectName = objectName,
             };
             int _engineResult = InternalUnsafeMethods.NameToID()(_args);
             return _engineResult;
        }

        /// <summary>Retrofits a filepath that uses old Torque style</summary>
        /// <description>
        /// 
        /// </description>
        /// <returns>String containing filepath with new formatting</returns>
        public static string ExpandOldFilename(string filename) {
             InternalUnsafeMethods.ExpandOldFilename__Args _args = new InternalUnsafeMethods.ExpandOldFilename__Args() {
                filename = filename,
             };
             IntPtr _engineResult = InternalUnsafeMethods.ExpandOldFilename()(_args);
             return StringMarshal.IntPtrToUtf8String(_engineResult);
        }

        /// <summary>Grabs the full path of a specified file</summary>
        /// <description>
        /// 
        /// </description>
        /// <param name="filename">Name of the local file to locate</param>
        /// <returns>String containing the full filepath on disk</returns>
        public static string ExpandFilename(string filename) {
             InternalUnsafeMethods.ExpandFilename__Args _args = new InternalUnsafeMethods.ExpandFilename__Args() {
                filename = filename,
             };
             IntPtr _engineResult = InternalUnsafeMethods.ExpandFilename()(_args);
             return StringMarshal.IntPtrToUtf8String(_engineResult);
        }

        /// <summary>Create the given directory or the path leading to the given filename.</summary>
        /// <description>
        /// If
        /// </description>
        /// <paramref name="" /> path ends in a trailing slash, then all components in the given path will be created as directories (if not already in place).  If <param name="path">The path to create.</param>
        /// <remarks> Only present in a Tools build of Torque.
        /// </remarks>
        public static bool CreatePath(string path) {
             InternalUnsafeMethods.CreatePath__Args _args = new InternalUnsafeMethods.CreatePath__Args() {
                path = path,
             };
             bool _engineResult = InternalUnsafeMethods.CreatePath()(_args);
             return _engineResult;
        }

        /// <summary>Set the current working directory.</summary>
        /// <description>
        /// 
        /// </description>
        /// <param name="path">The absolute or relative (to the current working directory) path of the directory which should be made the new working directory.</param>
        /// <returns>True if the working directory was successfully changed to<paramref name="" /> path, false otherwise.
        /// 
        /// </returns>
        /// <remarks> Only present in a Tools build of Torque.
        /// </remarks>
        public static bool SetCurrentDirectory(string path) {
             InternalUnsafeMethods.SetCurrentDirectory__Args _args = new InternalUnsafeMethods.SetCurrentDirectory__Args() {
                path = path,
             };
             bool _engineResult = InternalUnsafeMethods.SetCurrentDirectory()(_args);
             return _engineResult;
        }

        /// <summary>Return the current working directory.</summary>
        /// <description>
        /// 
        /// </description>
        /// <returns>The absolute path of the current working directory.</returns>
        /// <remarks> Only present in a Tools build of Torque.
        /// </remarks>
        /// <see cref="getWorkingDirectory()" />
        public static string GetCurrentDirectory() {
             InternalUnsafeMethods.GetCurrentDirectory__Args _args = new InternalUnsafeMethods.GetCurrentDirectory__Args() {
             };
             IntPtr _engineResult = InternalUnsafeMethods.GetCurrentDirectory()(_args);
             return StringMarshal.IntPtrToUtf8String(_engineResult);
        }

        /// <summary>Copy a file to a new location.</summary>
        /// <description>
        /// 
        /// </description>
        /// <param name="fromFile">%Path of the file to copy.</param>
        /// <param name="toFile">%Path where to copy<paramref name="" /> fromFile to.
        /// </param>
        /// <param name="noOverwrite">If true, then<paramref name="" /> fromFile will not overwrite a file that may already exist at </param>
        /// <returns>True if the file was successfully copied, false otherwise.</returns>
        /// <remarks> Only present in a Tools build of Torque.
        /// </remarks>
        public static bool PathCopy(string fromFile = "", string toFile = "", bool noOverwrite = true) {
             InternalUnsafeMethods.PathCopy__Args _args = new InternalUnsafeMethods.PathCopy__Args() {
                fromFile = fromFile,
                toFile = toFile,
                noOverwrite = noOverwrite,
             };
             bool _engineResult = InternalUnsafeMethods.PathCopy()(_args);
             return _engineResult;
        }

        /// <summary>Open the given<paramref name="" /> file through the system.  This will usually open the file in its associated application.
        /// </summary>
        /// <param name="file">%Path of the file to open.</param>
        /// <remarks> Only present in a Tools build of Torque.
        /// </remarks>
        public static void OpenFile(string file) {
             InternalUnsafeMethods.OpenFile__Args _args = new InternalUnsafeMethods.OpenFile__Args() {
                file = file,
             };
             InternalUnsafeMethods.OpenFile()(_args);
        }

        /// <summary>Open the given folder in the system's file manager.</summary>
        /// <description>
        /// 
        /// </description>
        /// <param name="path">full path to a directory.</param>
        /// <remarks> Only present in a Tools build of Torque.
        /// </remarks>
        public static void OpenFolder(string path) {
             InternalUnsafeMethods.OpenFolder__Args _args = new InternalUnsafeMethods.OpenFolder__Args() {
                path = path,
             };
             InternalUnsafeMethods.OpenFolder()(_args);
        }

        /// <summary>Get the absolute path to the directory that contains the main.cs script from which the engine was started.</summary>
        /// <description>
        /// This directory will usually contain all the game assets and, in a user-side game installation, will usually be read-only.
        /// </description>
        /// <returns>The path to the main game assets.</returns>
        public static string GetMainDotCsDir() {
             InternalUnsafeMethods.GetMainDotCsDir__Args _args = new InternalUnsafeMethods.GetMainDotCsDir__Args() {
             };
             IntPtr _engineResult = InternalUnsafeMethods.GetMainDotCsDir()(_args);
             return StringMarshal.IntPtrToUtf8String(_engineResult);
        }

        /// <summary>Gets the name of the game's executable</summary>
        /// <description>
        /// 
        /// </description>
        /// <returns>String containing this game's executable name</returns>
        public static string GetExecutableName() {
             InternalUnsafeMethods.GetExecutableName__Args _args = new InternalUnsafeMethods.GetExecutableName__Args() {
             };
             IntPtr _engineResult = InternalUnsafeMethods.GetExecutableName()(_args);
             return StringMarshal.IntPtrToUtf8String(_engineResult);
        }

        /// <summary>Combines two separate strings containing a file path and file name together into a single string</summary>
        /// <description>
        /// 
        /// </description>
        /// <param name="path">String containing file path</param>
        /// <param name="file">String containing file name</param>
        /// <returns>String containing concatenated file name and path</returns>
        public static string PathConcat(string path = "", string file = "") {
             InternalUnsafeMethods.PathConcat__Args _args = new InternalUnsafeMethods.PathConcat__Args() {
                path = path,
                file = file,
             };
             IntPtr _engineResult = InternalUnsafeMethods.PathConcat()(_args);
             return StringMarshal.IntPtrToUtf8String(_engineResult);
        }

        /// <summary>Turns a full or local path to a relative one</summary>
        /// <description>
        /// For example, "./game/art" becomes "game/art"
        /// </description>
        /// <param name="path">Full path (may include a file) to convert</param>
        /// <param name="to">Optional base path used for the conversion.  If not supplied the current working directory is used.</param>
        /// <returns>String containing relative path</returns>
        public static string MakeRelativePath(string path = "", string to = "") {
             InternalUnsafeMethods.MakeRelativePath__Args _args = new InternalUnsafeMethods.MakeRelativePath__Args() {
                path = path,
                to = to,
             };
             IntPtr _engineResult = InternalUnsafeMethods.MakeRelativePath()(_args);
             return StringMarshal.IntPtrToUtf8String(_engineResult);
        }

        /// <summary>Converts a relative file path to a full path</summary>
        /// <description>
        /// For example, "./console.log" becomes "C:/Torque/t3d/examples/FPS Example/game/console.log"
        /// </description>
        /// <param name="path">Name of file or path to check</param>
        /// <param name="cwd">Optional current working directory from which to build the full path.</param>
        /// <returns>String containing non-relative directory of path</returns>
        public static string MakeFullPath(string path = "", string cwd = "") {
             InternalUnsafeMethods.MakeFullPath__Args _args = new InternalUnsafeMethods.MakeFullPath__Args() {
                path = path,
                cwd = cwd,
             };
             IntPtr _engineResult = InternalUnsafeMethods.MakeFullPath()(_args);
             return StringMarshal.IntPtrToUtf8String(_engineResult);
        }

        /// <summary>Reports the current directory</summary>
        /// <description>
        /// 
        /// </description>
        /// <returns>String containing full file path of working directory</returns>
        public static string GetWorkingDirectory() {
             InternalUnsafeMethods.GetWorkingDirectory__Args _args = new InternalUnsafeMethods.GetWorkingDirectory__Args() {
             };
             IntPtr _engineResult = InternalUnsafeMethods.GetWorkingDirectory()(_args);
             return StringMarshal.IntPtrToUtf8String(_engineResult);
        }

        /// <summary>Get the path of a file (removes name and extension)</summary>
        /// <description>
        /// 
        /// </description>
        /// <param name="fileName">Name and path of file to check</param>
        /// <returns>String containing the path, minus name and extension</returns>
        public static string FilePath(string fileName) {
             InternalUnsafeMethods.FilePath__Args _args = new InternalUnsafeMethods.FilePath__Args() {
                fileName = fileName,
             };
             IntPtr _engineResult = InternalUnsafeMethods.FilePath()(_args);
             return StringMarshal.IntPtrToUtf8String(_engineResult);
        }

        /// <summary>Get only the file name of a path and file name string (removes path)</summary>
        /// <description>
        /// 
        /// </description>
        /// <param name="fileName">Name and path of file to check</param>
        /// <returns>String containing the file name, minus the path</returns>
        public static string FileName(string fileName) {
             InternalUnsafeMethods.FileName__Args _args = new InternalUnsafeMethods.FileName__Args() {
                fileName = fileName,
             };
             IntPtr _engineResult = InternalUnsafeMethods.FileName()(_args);
             return StringMarshal.IntPtrToUtf8String(_engineResult);
        }

        /// <summary>Get the base of a file name (removes extension and path)</summary>
        /// <description>
        /// 
        /// </description>
        /// <param name="fileName">Name and path of file to check</param>
        /// <returns>String containing the file name, minus extension and path</returns>
        public static string FileBase(string fileName) {
             InternalUnsafeMethods.FileBase__Args _args = new InternalUnsafeMethods.FileBase__Args() {
                fileName = fileName,
             };
             IntPtr _engineResult = InternalUnsafeMethods.FileBase()(_args);
             return StringMarshal.IntPtrToUtf8String(_engineResult);
        }

        /// <summary>Get the extension of a file</summary>
        /// <description>
        /// 
        /// </description>
        /// <param name="fileName">Name and path of file</param>
        /// <returns>String containing the extension, such as ".exe" or ".cs"</returns>
        public static string FileExt(string fileName) {
             InternalUnsafeMethods.FileExt__Args _args = new InternalUnsafeMethods.FileExt__Args() {
                fileName = fileName,
             };
             IntPtr _engineResult = InternalUnsafeMethods.FileExt()(_args);
             return StringMarshal.IntPtrToUtf8String(_engineResult);
        }

        /// <summary>Delete a file from the hard drive</summary>
        /// <description>
        /// 
        /// </description>
        /// <param name="path">Name and path of the file to delete</param>
        /// <remarks> THERE IS NO RECOVERY FROM THIS. Deleted file is gone for good.
        /// </remarks>
        /// <returns>True if file was successfully deleted</returns>
        public static bool FileDelete(string path) {
             InternalUnsafeMethods.FileDelete__Args _args = new InternalUnsafeMethods.FileDelete__Args() {
                path = path,
             };
             bool _engineResult = InternalUnsafeMethods.FileDelete()(_args);
             return _engineResult;
        }

        /// <summary>Returns a platform specific formatted string with the creation time for the file.</summary>
        /// <param name="fileName">Name and path of file to check</param>
        /// <returns>Formatted string (OS specific) containing created time, "9/3/2010 12:33:47 PM" for example</returns>
        public static string FileCreatedTime(string fileName) {
             InternalUnsafeMethods.FileCreatedTime__Args _args = new InternalUnsafeMethods.FileCreatedTime__Args() {
                fileName = fileName,
             };
             IntPtr _engineResult = InternalUnsafeMethods.FileCreatedTime()(_args);
             return StringMarshal.IntPtrToUtf8String(_engineResult);
        }

        /// <summary>Returns a platform specific formatted string with the last modified time for the file.</summary>
        /// <description>
        /// 
        /// </description>
        /// <param name="fileName">Name and path of file to check</param>
        /// <returns>Formatted string (OS specific) containing modified time, "9/3/2010 12:33:47 PM" for example</returns>
        public static string FileModifiedTime(string fileName) {
             InternalUnsafeMethods.FileModifiedTime__Args _args = new InternalUnsafeMethods.FileModifiedTime__Args() {
                fileName = fileName,
             };
             IntPtr _engineResult = InternalUnsafeMethods.FileModifiedTime()(_args);
             return StringMarshal.IntPtrToUtf8String(_engineResult);
        }

        /// <summary>Determines the size of a file on disk</summary>
        /// <description>
        /// 
        /// </description>
        /// <param name="fileName">Name and path of the file to check</param>
        /// <returns>Returns filesize in bytes, or -1 if no file</returns>
        public static int FileSize(string fileName) {
             InternalUnsafeMethods.FileSize__Args _args = new InternalUnsafeMethods.FileSize__Args() {
                fileName = fileName,
             };
             int _engineResult = InternalUnsafeMethods.FileSize()(_args);
             return _engineResult;
        }

        /// <summary>Gathers a list of directories starting at the given path.</summary>
        /// <description>
        /// 
        /// </description>
        /// <param name="path">String containing the path of the directory</param>
        /// <param name="depth">Depth of search, as in how many subdirectories to parse through</param>
        /// <returns>Tab delimited string containing list of directories found during search, "" if no files were found</returns>
        public static string GetDirectoryList(string path = "", int depth = 0) {
             InternalUnsafeMethods.GetDirectoryList__Args _args = new InternalUnsafeMethods.GetDirectoryList__Args() {
                path = path,
                depth = depth,
             };
             IntPtr _engineResult = InternalUnsafeMethods.GetDirectoryList()(_args);
             return StringMarshal.IntPtrToUtf8String(_engineResult);
        }

        /// <summary>Stop watching resources for file changes</summary>
        /// <description>
        /// Typically this is called during shutdownCore().
        /// </description>
        /// <see cref="startFileChangeNotifications()" />
        public static void StopFileChangeNotifications() {
             InternalUnsafeMethods.StopFileChangeNotifications__Args _args = new InternalUnsafeMethods.StopFileChangeNotifications__Args() {
             };
             InternalUnsafeMethods.StopFileChangeNotifications()(_args);
        }

        /// <summary>Start watching resources for file changes</summary>
        /// <description>
        /// Typically this is called during initializeCore().
        /// </description>
        /// <see cref="stopFileChangeNotifications()" />
        public static void StartFileChangeNotifications() {
             InternalUnsafeMethods.StartFileChangeNotifications__Args _args = new InternalUnsafeMethods.StartFileChangeNotifications__Args() {
             };
             InternalUnsafeMethods.StartFileChangeNotifications()(_args);
        }

        /// <summary>Determines if a file name can be written to using File I/O</summary>
        /// <description>
        /// 
        /// </description>
        /// <param name="fileName">Name and path of file to check</param>
        /// <returns>Returns true if the file can be written to.</returns>
        public static bool IsWriteableFileName(string fileName) {
             InternalUnsafeMethods.IsWriteableFileName__Args _args = new InternalUnsafeMethods.IsWriteableFileName__Args() {
                fileName = fileName,
             };
             bool _engineResult = InternalUnsafeMethods.IsWriteableFileName()(_args);
             return _engineResult;
        }

        /// <summary>Determines if a specified directory exists or not</summary>
        /// <description>
        /// 
        /// </description>
        /// <param name="directory">String containing path in the form of "foo/bar"</param>
        /// <returns>Returns true if the directory was found.</returns>
        /// <remarks> Do not include a trailing slash '/'.
        /// </remarks>
        public static bool IsDirectory(string directory) {
             InternalUnsafeMethods.IsDirectory__Args _args = new InternalUnsafeMethods.IsDirectory__Args() {
                directory = directory,
             };
             bool _engineResult = InternalUnsafeMethods.IsDirectory()(_args);
             return _engineResult;
        }

        /// <summary>Determines if the specified file exists or not</summary>
        /// <description>
        /// 
        /// </description>
        /// <param name="fileName">The path to the file.</param>
        /// <returns>Returns true if the file was found.</returns>
        public static bool IsFile(string fileName) {
             InternalUnsafeMethods.IsFile__Args _args = new InternalUnsafeMethods.IsFile__Args() {
                fileName = fileName,
             };
             bool _engineResult = InternalUnsafeMethods.IsFile()(_args);
             return _engineResult;
        }

        /// <summary>Provides the CRC checksum of the given file.</summary>
        /// <description>
        /// 
        /// </description>
        /// <param name="fileName">The path to the file.</param>
        /// <returns>The calculated CRC checksum of the file, or -1 if the file could not be found.</returns>
        public static int GetFileCRC(string fileName) {
             InternalUnsafeMethods.GetFileCRC__Args _args = new InternalUnsafeMethods.GetFileCRC__Args() {
                fileName = fileName,
             };
             int _engineResult = InternalUnsafeMethods.GetFileCRC()(_args);
             return _engineResult;
        }

        /// <summary>Returns the number of files in the directory tree that match the given patterns</summary>
        /// <description>
        /// If you're interested in a list of files that match the given patterns and not just the number of files, use findFirstFileMultiExpr() and findNextFileMultiExpr().
        /// </description>
        /// <param name="pattern">The path and file name pattern to match against, such as *.cs.  Separate multiple patterns with TABs.  For example: "*.cs" TAB "*.dso"</param>
        /// <param name="recurse">If true, the search will exhaustively recurse into subdirectories of the given path and match the given filename pattern.</param>
        /// <returns>Number of files located using the patterns</returns>
        /// <code>
        /// // Count all DTS or Collada models
        /// %filePatterns = "*.dts" TAB "*.dae";
        /// echo( "Nunmer of shape files:" SPC getFileCountMultiExpr( %filePatterns ) );
        /// </code>
        /// <see cref="findFirstFileMultiExpr()" />
        /// <see cref="findNextFileMultiExpr()" />
        public static int GetFileCountMultiExpr(string pattern = "", bool recurse = true) {
             InternalUnsafeMethods.GetFileCountMultiExpr__Args _args = new InternalUnsafeMethods.GetFileCountMultiExpr__Args() {
                pattern = pattern,
                recurse = recurse,
             };
             int _engineResult = InternalUnsafeMethods.GetFileCountMultiExpr()(_args);
             return _engineResult;
        }

        /// <summary>Returns the next file matching a search begun in findFirstFileMultiExpr().</summary>
        /// <description>
        /// 
        /// </description>
        /// <param name="pattern">The path and file name pattern to match against.  This is optional and may be left out as it is not used by the code.  It is here for legacy reasons.</param>
        /// <returns>String of the next matching file path, or an empty string if no matching files were found.</returns>
        /// <code>
        /// // Find all DTS or Collada models
        /// %filePatterns = "*.dts" TAB "*.dae";
        /// %fullPath = findFirstFileMultiExpr( %filePatterns );
        /// while ( %fullPath !$= "" )
        /// {
        ///    echo( %fullPath );
        ///    %fullPath = findNextFileMultiExpr( %filePatterns );
        /// }
        /// </code>
        /// <see cref="findFirstFileMultiExpr()" />
        public static string FindNextFileMultiExpr(string pattern = "") {
             InternalUnsafeMethods.FindNextFileMultiExpr__Args _args = new InternalUnsafeMethods.FindNextFileMultiExpr__Args() {
                pattern = pattern,
             };
             IntPtr _engineResult = InternalUnsafeMethods.FindNextFileMultiExpr()(_args);
             return StringMarshal.IntPtrToUtf8String(_engineResult);
        }

        /// <summary>Returns the first file in the directory system matching the given patterns.</summary>
        /// <description>
        /// Use the corresponding findNextFileMultiExpr() to step through the results.  If you're only interested in the number of files returned by the pattern match, use getFileCountMultiExpr().
        /// 
        /// This function differs from findFirstFile() in that it supports multiple search patterns to be passed in.
        /// </description>
        /// <remarks> You cannot run multiple simultaneous file system searches with these functions.  Each call to findFirstFile() and findFirstFileMultiExpr() initiates a new search and renders a previous search invalid.
        /// 
        /// </remarks>
        /// <param name="pattern">The path and file name pattern to match against, such as *.cs.  Separate multiple patterns with TABs.  For example: "*.cs" TAB "*.dso"</param>
        /// <param name="recurse">If true, the search will exhaustively recurse into subdirectories of the given path and match the given filename patterns.</param>
        /// <returns>String of the first matching file path, or an empty string if no matching files were found.</returns>
        /// <code>
        /// // Find all DTS or Collada models
        /// %filePatterns = "*.dts" TAB "*.dae";
        /// %fullPath = findFirstFileMultiExpr( %filePatterns );
        /// while ( %fullPath !$= "" )
        /// {
        ///    echo( %fullPath );
        ///    %fullPath = findNextFileMultiExpr( %filePatterns );
        /// }
        /// </code>
        /// <see cref="findNextFileMultiExpr()" />
        /// <see cref="getFileCountMultiExpr()" />
        /// <see cref="findFirstFile()" />
        public static string FindFirstFileMultiExpr(string pattern = "", bool recurse = true) {
             InternalUnsafeMethods.FindFirstFileMultiExpr__Args _args = new InternalUnsafeMethods.FindFirstFileMultiExpr__Args() {
                pattern = pattern,
                recurse = recurse,
             };
             IntPtr _engineResult = InternalUnsafeMethods.FindFirstFileMultiExpr()(_args);
             return StringMarshal.IntPtrToUtf8String(_engineResult);
        }

        /// <summary>Returns the number of files in the directory tree that match the given patterns</summary>
        /// <description>
        /// This function differs from getFileCountMultiExpr() in that it supports a single search pattern being passed in.
        /// 
        /// If you're interested in a list of files that match the given pattern and not just the number of files, use findFirstFile() and findNextFile().
        /// </description>
        /// <param name="pattern">The path and file name pattern to match against.</param>
        /// <param name="recurse">If true, the search will exhaustively recurse into subdirectories of the given path and match the given filename pattern counting files in subdirectories.</param>
        /// <returns>Number of files located using the pattern</returns>
        /// <code>
        /// // Count the number of .cs files in a subdirectory and its subdirectories.
        /// getFileCount( "subdirectory/*.cs" );
        /// </code>
        /// <see cref="findFirstFile()" />
        /// <see cref="findNextFile()" />
        /// <see cref="getFileCountMultiExpr()" />
        public static int GetFileCount(string pattern = "", bool recurse = true) {
             InternalUnsafeMethods.GetFileCount__Args _args = new InternalUnsafeMethods.GetFileCount__Args() {
                pattern = pattern,
                recurse = recurse,
             };
             int _engineResult = InternalUnsafeMethods.GetFileCount()(_args);
             return _engineResult;
        }

        /// <summary>Returns the next file matching a search begun in findFirstFile().</summary>
        /// <description>
        /// 
        /// </description>
        /// <param name="pattern">The path and file name pattern to match against.  This is optional and may be left out as it is not used by the code.  It is here for legacy reasons.</param>
        /// <returns>The path of the next filename matched by the search or an empty string if no more files match.</returns>
        /// <code>
        /// // Execute all .cs files in a subdirectory and its subdirectories.
        /// for( %file = findFirstFile( "subdirectory/*.cs" ); %file !$= ""; %file = findNextFile() )
        ///    exec( %file );
        /// </code>
        /// <see cref="findFirstFile()" />
        public static string FindNextFile(string pattern = "") {
             InternalUnsafeMethods.FindNextFile__Args _args = new InternalUnsafeMethods.FindNextFile__Args() {
                pattern = pattern,
             };
             IntPtr _engineResult = InternalUnsafeMethods.FindNextFile()(_args);
             return StringMarshal.IntPtrToUtf8String(_engineResult);
        }

        /// <summary>Returns the first file in the directory system matching the given pattern.</summary>
        /// <description>
        /// Use the corresponding findNextFile() to step through the results.  If you're only interested in the number of files returned by the pattern match, use getFileCount().
        /// 
        /// This function differs from findFirstFileMultiExpr() in that it supports a single search pattern being passed in.
        /// </description>
        /// <remarks> You cannot run multiple simultaneous file system searches with these functions.  Each call to findFirstFile() and findFirstFileMultiExpr() initiates a new search and renders a previous search invalid.
        /// 
        /// </remarks>
        /// <param name="pattern">The path and file name pattern to match against.</param>
        /// <param name="recurse">If true, the search will exhaustively recurse into subdirectories of the given path and match the given filename pattern.</param>
        /// <returns>The path of the first file matched by the search or an empty string if no matching file could be found.</returns>
        /// <code>
        /// // Execute all .cs files in a subdirectory and its subdirectories.
        /// for( %file = findFirstFile( "subdirectory/*.cs" ); %file !$= ""; %file = findNextFile() )
        ///    exec( %file );
        /// </code>
        /// <see cref="findNextFile()" />
        /// <see cref="getFileCount()" />
        /// <see cref="findFirstFileMultiExpr()" />
        public static string FindFirstFile(string pattern = "", bool recurse = true) {
             InternalUnsafeMethods.FindFirstFile__Args _args = new InternalUnsafeMethods.FindFirstFile__Args() {
                pattern = pattern,
                recurse = recurse,
             };
             IntPtr _engineResult = InternalUnsafeMethods.FindFirstFile()(_args);
             return StringMarshal.IntPtrToUtf8String(_engineResult);
        }

        /// <description>
        /// Create a XML document containing a dump of the entire exported engine API.
        /// </description>
        /// <returns>A SimXMLDocument containing a dump of the engine's export information or NULL if the operation failed.</returns>
        public static SimXMLDocument ExportEngineAPIToXML() {
             InternalUnsafeMethods.ExportEngineAPIToXML__Args _args = new InternalUnsafeMethods.ExportEngineAPIToXML__Args() {
             };
             IntPtr _engineResult = InternalUnsafeMethods.ExportEngineAPIToXML()(_args);
             return new SimXMLDocument(_engineResult);
        }

        /// <summary>Dumps all current EngineObject instances to the console.</summary>
        /// <description>
        /// 
        /// </description>
        /// <remarks> This function is only available in debug builds.
        /// 
        /// </remarks>
        public static void DebugDumpAllObjects() {
             InternalUnsafeMethods.DebugDumpAllObjects__Args _args = new InternalUnsafeMethods.DebugDumpAllObjects__Args() {
             };
             InternalUnsafeMethods.DebugDumpAllObjects()(_args);
        }

        /// <description>
        /// Dumps the engine scripting documentation to the specified file overwriting any existing content.
        /// </description>
        /// <param name="outputFile">The relative or absolute output file path and name.</param>
        /// <returns>Returns true if successful.</returns>
        public static bool DumpEngineDocs(string outputFile) {
             InternalUnsafeMethods.DumpEngineDocs__Args _args = new InternalUnsafeMethods.DumpEngineDocs__Args() {
                outputFile = outputFile,
             };
             bool _engineResult = InternalUnsafeMethods.DumpEngineDocs()(_args);
             return _engineResult;
        }

        /// <summary>Links childNS to parentNS.</summary>
        /// <description>
        /// Links childNS to parentNS, or nothing if parentNS is NULL.
        /// Will unlink the namespace from previous namespace if a parent already exists.
        /// </description>
        public static bool LinkNamespaces(string childNSName, string parentNSName) {
             InternalUnsafeMethods.LinkNamespaces__Args _args = new InternalUnsafeMethods.LinkNamespaces__Args() {
                childNSName = childNSName,
                parentNSName = parentNSName,
             };
             bool _engineResult = InternalUnsafeMethods.LinkNamespaces()(_args);
             return _engineResult;
        }

        /// <summary>Determines the memory consumption of a class or object.</summary>
        /// <description>
        /// 
        /// </description>
        /// <param name="objectOrClass">The object or class being measured.</param>
        /// <returns>Returns the total size of an object in bytes.</returns>
        public static int sizeOf(string objectOrClass) {
             InternalUnsafeMethods.sizeOf__Args _args = new InternalUnsafeMethods.sizeOf__Args() {
                objectOrClass = objectOrClass,
             };
             int _engineResult = InternalUnsafeMethods.sizeOf()(_args);
             return _engineResult;
        }

        /// <summary>Dumps network statistics for each class to the console.</summary>
        /// <description>
        /// The returned <i>avg</i>, <i>min</i> and <i>max</i> values are in bits sent per update.  The <i>num</i> value is the total number of events collected.
        /// </description>
        /// <remarks> This method only works when TORQUE_NET_STATS is defined in torqueConfig.h.
        /// </remarks>
        public static void DumpNetStats() {
             InternalUnsafeMethods.DumpNetStats__Args _args = new InternalUnsafeMethods.DumpNetStats__Args() {
             };
             InternalUnsafeMethods.DumpNetStats()(_args);
        }

        /// <summary>Provide a list of classes that belong to the given category.</summary>
        /// <description>
        /// 
        /// </description>
        /// <param name="category">The category name.</param>
        /// <returns>A tab delimited list of classes.</returns>
        public static string EnumerateConsoleClassesByCategory(string category) {
             InternalUnsafeMethods.EnumerateConsoleClassesByCategory__Args _args = new InternalUnsafeMethods.EnumerateConsoleClassesByCategory__Args() {
                category = category,
             };
             IntPtr _engineResult = InternalUnsafeMethods.EnumerateConsoleClassesByCategory()(_args);
             return StringMarshal.IntPtrToUtf8String(_engineResult);
        }

        /// <summary>Returns a list of classes that derive from the named class.</summary>
        /// <description>
        /// If the named class is omitted this dumps all the classes.
        /// </description>
        /// <param name="className">The optional base class name.</param>
        /// <returns>A tab delimited list of classes.</returns>
        public static string EnumerateConsoleClasses(string className = "") {
             InternalUnsafeMethods.EnumerateConsoleClasses__Args _args = new InternalUnsafeMethods.EnumerateConsoleClasses__Args() {
                className = className,
             };
             IntPtr _engineResult = InternalUnsafeMethods.EnumerateConsoleClasses()(_args);
             return StringMarshal.IntPtrToUtf8String(_engineResult);
        }

        /// <summary>Returns the category of the given class.</summary>
        /// <description>
        /// 
        /// </description>
        /// <param name="className">The name of the class.</param>
        public static string GetCategoryOfClass(string className) {
             InternalUnsafeMethods.GetCategoryOfClass__Args _args = new InternalUnsafeMethods.GetCategoryOfClass__Args() {
                className = className,
             };
             IntPtr _engineResult = InternalUnsafeMethods.GetCategoryOfClass()(_args);
             return StringMarshal.IntPtrToUtf8String(_engineResult);
        }

        /// <summary>Returns the description string for the named class.</summary>
        /// <description>
        /// 
        /// </description>
        /// <param name="className">The name of the class.</param>
        /// <returns>The class description in string format.</returns>
        public static string GetDescriptionOfClass(string className) {
             InternalUnsafeMethods.GetDescriptionOfClass__Args _args = new InternalUnsafeMethods.GetDescriptionOfClass__Args() {
                className = className,
             };
             IntPtr _engineResult = InternalUnsafeMethods.GetDescriptionOfClass()(_args);
             return StringMarshal.IntPtrToUtf8String(_engineResult);
        }

        /// <summary>Returns true if the class is derived from the super class.</summary>
        /// <description>
        /// If either class doesn't exist this returns false.
        /// </description>
        /// <param name="className">The class name.</param>
        /// <param name="superClassName">The super class to look for.</param>
        public static bool IsMemberOfClass(string className, string superClassName) {
             InternalUnsafeMethods.IsMemberOfClass__Args _args = new InternalUnsafeMethods.IsMemberOfClass__Args() {
                className = className,
                superClassName = superClassName,
             };
             bool _engineResult = InternalUnsafeMethods.IsMemberOfClass()(_args);
             return _engineResult;
        }

        /// <summary>Returns true if the passed identifier is the name of a declared class.</summary>
        /// <description>
        /// 
        /// </description>
        public static bool IsClass(string identifier) {
             InternalUnsafeMethods.IsClass__Args _args = new InternalUnsafeMethods.IsClass__Args() {
                identifier = identifier,
             };
             bool _engineResult = InternalUnsafeMethods.IsClass()(_args);
             return _engineResult;
        }

        /// <summary>Returns a space delimited list of the active packages in stack order.</summary>
        /// <description>
        /// 
        /// </description>
        public static string GetPackageList() {
             InternalUnsafeMethods.GetPackageList__Args _args = new InternalUnsafeMethods.GetPackageList__Args() {
             };
             IntPtr _engineResult = InternalUnsafeMethods.GetPackageList()(_args);
             return StringMarshal.IntPtrToUtf8String(_engineResult);
        }

        /// <summary>Deactivates a previously activated package.</summary>
        /// <description>
        /// The package is deactivated by removing its namespace linkages to any function or method. If there are any packages above this one in the stack they are deactivated as well. If the package is not on the stack this function does nothing.
        /// </description>
        public static void DeactivatePackage(string packageName) {
             InternalUnsafeMethods.DeactivatePackage__Args _args = new InternalUnsafeMethods.DeactivatePackage__Args() {
                packageName = packageName,
             };
             InternalUnsafeMethods.DeactivatePackage()(_args);
        }

        /// <summary>Activates an existing package.</summary>
        /// <description>
        /// The activation occurs by updating the namespace linkage of existing functions and methods. If the package is already activated the function does nothing.
        /// </description>
        public static void ActivatePackage(string packageName) {
             InternalUnsafeMethods.ActivatePackage__Args _args = new InternalUnsafeMethods.ActivatePackage__Args() {
                packageName = packageName,
             };
             InternalUnsafeMethods.ActivatePackage()(_args);
        }

        /// <summary>Returns true if the identifier is the name of a declared package.</summary>
        /// <description>
        /// 
        /// </description>
        public static bool IsPackage(string identifier) {
             InternalUnsafeMethods.IsPackage__Args _args = new InternalUnsafeMethods.IsPackage__Args() {
                identifier = identifier,
             };
             bool _engineResult = InternalUnsafeMethods.IsPackage()(_args);
             return _engineResult;
        }

        /// <summary>Prints the scripting call stack to the console log.</summary>
        /// <description>
        /// Used to trace functions called from within functions. Can help discover what functions were called (and not yet exited) before the current point in scripts.
        /// </description>
        public static void Backtrace() {
             InternalUnsafeMethods.Backtrace__Args _args = new InternalUnsafeMethods.Backtrace__Args() {
             };
             InternalUnsafeMethods.Backtrace()(_args);
        }

        /// <description>
        /// Get max number of allowable dynamic vertices in a single vertex buffer.
        /// </description>
        /// <returns>the max number of allowable dynamic vertices in a single vertex buffer</returns>
        public static int GetMaxDynamicVerts() {
             InternalUnsafeMethods.GetMaxDynamicVerts__Args _args = new InternalUnsafeMethods.GetMaxDynamicVerts__Args() {
             };
             int _engineResult = InternalUnsafeMethods.GetMaxDynamicVerts()(_args);
             return _engineResult;
        }

        /// <description>
        /// Test whether the engine has been compiled with TORQUE_TOOLS, i.e. if it includes tool-related functionality.
        /// </description>
        /// <returns>True if this is a tool build; false otherwise.</returns>
        public static bool IsToolBuild() {
             InternalUnsafeMethods.IsToolBuild__Args _args = new InternalUnsafeMethods.IsToolBuild__Args() {
             };
             bool _engineResult = InternalUnsafeMethods.IsToolBuild()(_args);
             return _engineResult;
        }

        /// <description>
        /// Test whether the engine has been compiled with TORQUE_DEBUG, i.e. if it includes debugging functionality.
        /// </description>
        /// <returns>True if this is a debug build; false otherwise.</returns>
        public static bool IsDebugBuild() {
             InternalUnsafeMethods.IsDebugBuild__Args _args = new InternalUnsafeMethods.IsDebugBuild__Args() {
             };
             bool _engineResult = InternalUnsafeMethods.IsDebugBuild()(_args);
             return _engineResult;
        }

        /// <description>
        /// Test whether the engine has been compiled with TORQUE_SHIPPING, i.e. in a form meant for final release.
        /// </description>
        /// <returns>True if this is a shipping build; false otherwise.</returns>
        public static bool IsShippingBuild() {
             InternalUnsafeMethods.IsShippingBuild__Args _args = new InternalUnsafeMethods.IsShippingBuild__Args() {
             };
             bool _engineResult = InternalUnsafeMethods.IsShippingBuild()(_args);
             return _engineResult;
        }

        /// <description>
        /// Drops the engine into the native C++ debugger.
        /// 
        /// This function triggers a debug break and drops the process into the IDE's debugger.  If the process is not running with a debugger attached it will generate a runtime error on most platforms.
        /// </description>
        /// <remarks> This function is not available in shipping builds.</remarks>
        public static void Debug() {
             InternalUnsafeMethods.Debug__Args _args = new InternalUnsafeMethods.Debug__Args() {
             };
             InternalUnsafeMethods.Debug()(_args);
        }

        /// <description>
        /// Enable or disable tracing in the script code VM.
        /// 
        /// When enabled, the script code runtime will trace the invocation and returns from all functions that are called and log them to the console. This is helpful in observing the flow of the script program.
        /// </description>
        /// <param name="enable">New setting for script trace execution, on by default.</param>
        public static void Trace(bool enable = true) {
             InternalUnsafeMethods.Trace__Args _args = new InternalUnsafeMethods.Trace__Args() {
                enable = enable,
             };
             InternalUnsafeMethods.Trace()(_args);
        }

        /// <description>
        /// Undefine all global variables matching the given name<paramref name="" /> pattern.
        /// 
        /// </description>
        /// <param name="pattern">A global variable name pattern.  Must begin with '$'.</param>
        /// <code>
        /// // Define a global variable in the "My" namespace.
        /// $My::Variable = "value";
        /// 
        /// // Undefine all variable in the "My" namespace.
        /// deleteVariables( "$My::*" );
        /// </code>
        /// <see cref="strIsMatchExpr" />
        public static void DeleteVariables(string pattern) {
             InternalUnsafeMethods.DeleteVariables__Args _args = new InternalUnsafeMethods.DeleteVariables__Args() {
                pattern = pattern,
             };
             InternalUnsafeMethods.DeleteVariables()(_args);
        }

        /// <description>
        /// Write out the definitions of all global variables matching the given name<paramref name="" /> pattern.
        /// If 
        /// </description>
        /// <param name="pattern">A global variable name pattern.  Must begin with '$'.</param>
        /// <param name="filename">%Path of the file to which to write the definitions or "" to write the definitions to the console.</param>
        /// <param name="append">If true and<paramref name="" /> fileName is not "", then the definitions are appended to the specified file. Otherwise existing contents of the file (if any) will be overwritten.
        /// 
        /// </param>
        /// <code>
        /// // Write out all preference variables to a prefs.cs file.
        /// export( "$prefs::*", "prefs.cs" );
        /// </code>
        public static void Export(string pattern, string filename = "", bool append = false) {
             InternalUnsafeMethods.Export__Args _args = new InternalUnsafeMethods.Export__Args() {
                pattern = pattern,
                filename = filename,
                append = append,
             };
             InternalUnsafeMethods.Export()(_args);
        }

        /// <summary>Manually execute a special script file that contains game or editor preferences</summary>
        /// <description>
        /// 
        /// </description>
        /// <param name="relativeFileName">Name and path to file from project folder</param>
        /// <param name="noCalls">Deprecated</param>
        /// <param name="journalScript">Deprecated</param>
        /// <returns>True if script was successfully executed</returns>
        /// <remarks> Appears to be useless in Torque 3D, should be deprecated
        /// </remarks>
        public static bool ExecPrefs(string relativeFileName, bool noCalls = false, bool journalScript = false) {
             InternalUnsafeMethods.ExecPrefs__Args _args = new InternalUnsafeMethods.ExecPrefs__Args() {
                relativeFileName = relativeFileName,
                noCalls = noCalls,
                journalScript = journalScript,
             };
             bool _engineResult = InternalUnsafeMethods.ExecPrefs()(_args);
             return _engineResult;
        }

        /// <description>
        /// ([relativeFileName])
        /// </description>
        /// <remarks> Appears to be useless in Torque 3D, should be deprecated
        /// </remarks>
        public static string GetPrefsPath(string relativeFileName = "") {
             InternalUnsafeMethods.GetPrefsPath__Args _args = new InternalUnsafeMethods.GetPrefsPath__Args() {
                relativeFileName = relativeFileName,
             };
             IntPtr _engineResult = InternalUnsafeMethods.GetPrefsPath()(_args);
             return StringMarshal.IntPtrToUtf8String(_engineResult);
        }

        /// <description>
        /// ()
        /// </description>
        /// <summary>Pop and restore the last setting of $instantGroup off the stack.</summary>
        /// <description>
        /// 
        /// </description>
        /// <remarks> Currently only used for editors
        /// 
        /// </remarks>
        public static void PopInstantGroup() {
             InternalUnsafeMethods.PopInstantGroup__Args _args = new InternalUnsafeMethods.PopInstantGroup__Args() {
             };
             InternalUnsafeMethods.PopInstantGroup()(_args);
        }

        /// <description>
        /// ([group])
        /// </description>
        /// <summary>Pushes the current $instantGroup on a stack and sets it to the given value (or clears it).</summary>
        /// <description>
        /// 
        /// </description>
        /// <remarks> Currently only used for editors
        /// </remarks>
        public static void PushInstantGroup(string group = "") {
             InternalUnsafeMethods.PushInstantGroup__Args _args = new InternalUnsafeMethods.PushInstantGroup__Args() {
                group = group,
             };
             InternalUnsafeMethods.PushInstantGroup()(_args);
        }

        /// <description>
        /// (string path)
        /// </description>
        /// <summary>Attempts to extract a mod directory from path. Returns empty string on failure.</summary>
        /// <description>
        /// 
        /// </description>
        /// <param name="File">path of mod folder</param>
        /// <remarks> This is no longer relevant in Torque 3D (which does not use mod folders), should be deprecated
        /// </remarks>
        public static string GetModNameFromPath(string path) {
             InternalUnsafeMethods.GetModNameFromPath__Args _args = new InternalUnsafeMethods.GetModNameFromPath__Args() {
                path = path,
             };
             IntPtr _engineResult = InternalUnsafeMethods.GetModNameFromPath()(_args);
             return StringMarshal.IntPtrToUtf8String(_engineResult);
        }

        /// <description>
        /// ()Returns true if the calling script is a tools script.
        /// </description>
        public static bool IsCurrentScriptToolScript() {
             InternalUnsafeMethods.IsCurrentScriptToolScript__Args _args = new InternalUnsafeMethods.IsCurrentScriptToolScript__Args() {
             };
             bool _engineResult = InternalUnsafeMethods.IsCurrentScriptToolScript()(_args);
             return _engineResult;
        }

        /// <description>
        /// (string varName)
        /// </description>
        /// <summary>Determines if a variable exists and contains a value</summary>
        /// <description>
        /// 
        /// </description>
        /// <param name="varName">Name of the variable to search for</param>
        /// <returns>True if the variable was defined in script, false if not</returns>
        /// <code>
        /// isDefined( "$myVar" );
        /// </code>
        public static bool IsDefined(string varName, string varValue = "") {
             InternalUnsafeMethods.IsDefined__Args _args = new InternalUnsafeMethods.IsDefined__Args() {
                varName = varName,
                varValue = varValue,
             };
             bool _engineResult = InternalUnsafeMethods.IsDefined()(_args);
             return _engineResult;
        }

        /// <description>
        /// (string namespace, string method)
        /// </description>
        /// <summary>Provides the name of the package the method belongs to</summary>
        /// <description>
        /// 
        /// </description>
        /// <param name="namespace">Class or namespace, such as Player</param>
        /// <param name="method">Name of the funciton to search for</param>
        /// <returns>The name of the method's package</returns>
        public static string GetMethodPackage(string nameSpace, string method) {
             InternalUnsafeMethods.GetMethodPackage__Args _args = new InternalUnsafeMethods.GetMethodPackage__Args() {
                nameSpace = nameSpace,
                method = method,
             };
             IntPtr _engineResult = InternalUnsafeMethods.GetMethodPackage()(_args);
             return StringMarshal.IntPtrToUtf8String(_engineResult);
        }

        /// <description>
        /// (string namespace, string method)
        /// </description>
        /// <summary>Determines if a class/namespace method exists</summary>
        /// <description>
        /// 
        /// </description>
        /// <param name="namespace">Class or namespace, such as Player</param>
        /// <param name="method">Name of the function to search for</param>
        /// <returns>True if the method exists, false if not</returns>
        public static bool IsMethod(string nameSpace, string method) {
             InternalUnsafeMethods.IsMethod__Args _args = new InternalUnsafeMethods.IsMethod__Args() {
                nameSpace = nameSpace,
                method = method,
             };
             bool _engineResult = InternalUnsafeMethods.IsMethod()(_args);
             return _engineResult;
        }

        /// <description>
        /// (string funcName)
        /// </description>
        /// <summary>Provides the name of the package the function belongs to</summary>
        /// <description>
        /// 
        /// </description>
        /// <param name="funcName">String containing name of the function</param>
        /// <returns>The name of the function's package</returns>
        public static string GetFunctionPackage(string funcName) {
             InternalUnsafeMethods.GetFunctionPackage__Args _args = new InternalUnsafeMethods.GetFunctionPackage__Args() {
                funcName = funcName,
             };
             IntPtr _engineResult = InternalUnsafeMethods.GetFunctionPackage()(_args);
             return StringMarshal.IntPtrToUtf8String(_engineResult);
        }

        /// <description>
        /// (string funcName)
        /// </description>
        /// <summary>Determines if a function exists or not</summary>
        /// <description>
        /// 
        /// </description>
        /// <param name="funcName">String containing name of the function</param>
        /// <returns>True if the function exists, false if not</returns>
        public static bool IsFunction(string funcName) {
             InternalUnsafeMethods.IsFunction__Args _args = new InternalUnsafeMethods.IsFunction__Args() {
                funcName = funcName,
             };
             bool _engineResult = InternalUnsafeMethods.IsFunction()(_args);
             return _engineResult;
        }

        /// <description>
        /// (string varName, string value)
        /// </description>
        /// <summary>Sets the value of the named variable.</summary>
        /// <description>
        /// 
        /// </description>
        /// <param name="varName">Name of the variable to locate</param>
        /// <param name="value">New value of the variable</param>
        /// <returns>True if variable was successfully found and set</returns>
        public static void SetVariable(string varName, string value) {
             InternalUnsafeMethods.SetVariable__Args _args = new InternalUnsafeMethods.SetVariable__Args() {
                varName = varName,
                value = value,
             };
             InternalUnsafeMethods.SetVariable()(_args);
        }

        /// <description>
        /// (string varName)
        /// </description>
        /// <summary>Returns the value of the named variable or an empty string if not found.</summary>
        /// <description>
        /// 
        /// </description>
        /// <returns>Value contained by varName, "" if the variable does not exist</returns>
        public static string GetVariable(string varName) {
             InternalUnsafeMethods.GetVariable__Args _args = new InternalUnsafeMethods.GetVariable__Args() {
                varName = varName,
             };
             IntPtr _engineResult = InternalUnsafeMethods.GetVariable()(_args);
             return StringMarshal.IntPtrToUtf8String(_engineResult);
        }

        /// <description>
        /// eval(consoleString)
        /// </description>
        public static string Eval(string consoleString) {
             InternalUnsafeMethods.Eval__Args _args = new InternalUnsafeMethods.Eval__Args() {
                consoleString = consoleString,
             };
             IntPtr _engineResult = InternalUnsafeMethods.Eval()(_args);
             return StringMarshal.IntPtrToUtf8String(_engineResult);
        }

        /// <description>
        /// Execute the given script file.
        /// </description>
        /// <param name="fileName">Path to the file to execute</param>
        /// <param name="noCalls">Deprecated</param>
        /// <param name="journalScript">Deprecated</param>
        /// <returns>True if the script was successfully executed, false if not.</returns>
        /// <code>
        /// // Execute the init.cs script file found in the same directory as the current script file.
        /// exec( "./init.cs" );
        /// </code>
        /// <see cref="compile" />
        /// <see cref="eval" />
        public static bool Exec(string fileName, bool noCalls = false, bool journalScript = false) {
             InternalUnsafeMethods.Exec__Args _args = new InternalUnsafeMethods.Exec__Args() {
                fileName = fileName,
                noCalls = noCalls,
                journalScript = journalScript,
             };
             bool _engineResult = InternalUnsafeMethods.Exec()(_args);
             return _engineResult;
        }

        /// <description>
        /// Compile a file to bytecode.
        /// 
        /// This function will read the TorqueScript code in the specified file, compile it to internal bytecode, and, if DSO generation is enabled or<paramref name="" /> overrideNoDDSO is true, will store the compiled code in a .dso file in the current DSO path mirrorring the path of 
        /// </description>
        /// <param name="fileName">Path to the file to compile to bytecode.</param>
        /// <param name="overrideNoDSO">If true, force generation of DSOs even if the engine is compiled to not generate write compiled code to DSO files.</param>
        /// <returns>True if the file was successfully compiled, false if not.</returns>
        /// <remarks> The definitions contained in the given file will not be made available and no code will actually be executed.  Use exec() for that.
        /// 
        /// </remarks>
        /// <see cref="getDSOPath" />
        /// <see cref="exec" />
        public static bool Compile(string fileName, bool overrideNoDSO = false) {
             InternalUnsafeMethods.Compile__Args _args = new InternalUnsafeMethods.Compile__Args() {
                fileName = fileName,
                overrideNoDSO = overrideNoDSO,
             };
             bool _engineResult = InternalUnsafeMethods.Compile()(_args);
             return _engineResult;
        }

        /// <description>
        /// Get the absolute path to the file in which the compiled code for the given script file will be stored.
        /// </description>
        /// <param name="scriptFileName">%Path to the .cs script file.</param>
        /// <returns>The absolute path to the .dso file for the given script file.</returns>
        /// <remarks> The compiler will store newly compiled DSOs in the prefs path but pre-existing DSOs will be loaded from the current paths.
        /// 
        /// </remarks>
        /// <see cref="compile" />
        /// <see cref="getPrefsPath" />
        public static string GetDSOPath(string scriptFileName) {
             InternalUnsafeMethods.GetDSOPath__Args _args = new InternalUnsafeMethods.GetDSOPath__Args() {
                scriptFileName = scriptFileName,
             };
             IntPtr _engineResult = InternalUnsafeMethods.GetDSOPath()(_args);
             return StringMarshal.IntPtrToUtf8String(_engineResult);
        }

        /// <description>
        /// ( string functionName, string args... ) Apply the given arguments to the specified global function and return the result of the call.
        /// </description>
        /// <param name="functionName">The name of the function to call.  This function must be in the global namespace, i.e. you cannot call a function in a namespace through #call.  Use eval() for that.</param>
        /// <returns>The result of the function call.</returns>
        /// <code>
        /// function myFunction( %arg )
        /// {
        ///   return ( %arg SPC "World!" );
        /// }
        /// 
        /// echo( call( "myFunction", "Hello" ) ); // Prints "Hello World!" to the console.
        /// </code>
        public static string Call(params string[] args) { 
            List<string> _argList = new List<string>() {""};
            _argList.AddRange(args);

            StringVector nativeVecArgs = new StringVector {
                ElementCount = (uint)_argList.Count,
                Array = _argList.ToArray(),
                ArraySize = (uint)_argList.Count
            };
            nativeVecArgs.Alloc();
            IntPtr _engineResult = InternalUnsafeMethods.Call()(ref nativeVecArgs.internalStruct);
            nativeVecArgs.Free();

            return StringMarshal.IntPtrToUtf8String(_engineResult);
        }

        /// <description>
        /// Generate a new universally unique identifier (UUID).
        /// </description>
        /// <returns>A newly generated UUID.</returns>
        public static UUID GenerateUUID() {
             InternalUnsafeMethods.GenerateUUID__Args _args = new InternalUnsafeMethods.GenerateUUID__Args() {
             };
             UUID.InternalStruct _engineResult = InternalUnsafeMethods.GenerateUUID()(_args);
             return new UUID(_engineResult);
        }

        /// <description>
        /// Count the number of bits that are set in the given 32 bit integer.
        /// </description>
        /// <param name="v">An integer value.</param>
        /// <returns>The number of bits that are set in<paramref name="" /> v.
        /// 
        /// </returns>
        public static int CountBits(int v) {
             InternalUnsafeMethods.CountBits__Args _args = new InternalUnsafeMethods.CountBits__Args() {
                v = v,
             };
             int _engineResult = InternalUnsafeMethods.CountBits()(_args);
             return _engineResult;
        }

        /// <description>
        /// Test whether Torque is running in web-deployment mode.
        /// In this mode, Torque will usually run within a browser and certain restrictions apply (e.g. Torque will not be able to enter fullscreen exclusive mode).
        /// </description>
        /// <returns>True if Torque is running in web-deployment mode.</returns>
        public static bool GetWebDeployment() {
             InternalUnsafeMethods.GetWebDeployment__Args _args = new InternalUnsafeMethods.GetWebDeployment__Args() {
             };
             bool _engineResult = InternalUnsafeMethods.GetWebDeployment()(_args);
             return _engineResult;
        }

        /// <description>
        /// Close our startup splash window.
        /// </description>
        /// <remarks> This is currently only implemented on Windows.
        /// 
        /// </remarks>
        public static void CloseSplashWindow() {
             InternalUnsafeMethods.CloseSplashWindow__Args _args = new InternalUnsafeMethods.CloseSplashWindow__Args() {
             };
             InternalUnsafeMethods.CloseSplashWindow()(_args);
        }

        /// <description>
        /// Display a startup splash window suitable for showing while the engine still starts up.
        /// </description>
        /// <remarks> This is currently only implemented on Windows.
        /// 
        /// </remarks>
        /// <param name="path">relative path to splash screen image to display.</param>
        /// <returns>True if the splash window could be successfully initialized.</returns>
        public static bool DisplaySplashWindow(string path = "") {
             InternalUnsafeMethods.DisplaySplashWindow__Args _args = new InternalUnsafeMethods.DisplaySplashWindow__Args() {
                path = path,
             };
             bool _engineResult = InternalUnsafeMethods.DisplaySplashWindow()(_args);
             return _engineResult;
        }

        /// <description>
        /// Open the given URL or file in the user's web browser.
        /// </description>
        /// <param name="address">The address to open.  If this is not prefixed by a protocol specifier ("...://"), then the function checks whether the address refers to a file or directory and if so, prepends "file://" to<paramref name="" /> adress; if the file check fails, "http://" is prepended to </param>
        /// <code>
        /// gotoWebPage( "http://www.garagegames.com" );
        /// </code>
        public static void GotoWebPage(string address) {
             InternalUnsafeMethods.GotoWebPage__Args _args = new InternalUnsafeMethods.GotoWebPage__Args() {
                address = address,
             };
             InternalUnsafeMethods.GotoWebPage()(_args);
        }

        /// <description>
        /// Shut down the engine and exit its process.
        /// This function cleanly uninitializes the engine and then exits back to the system with a given return status code.
        /// </description>
        /// <param name="status">The status code to return to the OS.</param>
        /// <see cref="quitWithErrorMessage" />
        public static void QuitWithStatus(int status = 0) {
             InternalUnsafeMethods.QuitWithStatus__Args _args = new InternalUnsafeMethods.QuitWithStatus__Args() {
                status = status,
             };
             InternalUnsafeMethods.QuitWithStatus()(_args);
        }

        /// <description>
        /// Display an error message box showing the given<paramref name="" /> message and then shut down the engine and exit its process.
        /// This function cleanly uninitialized the engine and then exits back to the system with a process exit status indicating an error.
        /// 
        /// 
        /// </description>
        /// <param name="message">The message to log to the console and show in an error message box.</param>
        /// <param name="status">The status code to return to the OS.</param>
        /// <see cref="quit" />
        public static void QuitWithErrorMessage(string message, int status = 0) {
             InternalUnsafeMethods.QuitWithErrorMessage__Args _args = new InternalUnsafeMethods.QuitWithErrorMessage__Args() {
                message = message,
                status = status,
             };
             InternalUnsafeMethods.QuitWithErrorMessage()(_args);
        }

        /// 
        public static void RealQuit() {
             InternalUnsafeMethods.RealQuit__Args _args = new InternalUnsafeMethods.RealQuit__Args() {
             };
             InternalUnsafeMethods.RealQuit()(_args);
        }

        /// <description>
        /// Shut down the engine and exit its process.
        /// This function cleanly uninitializes the engine and then exits back to the system with a process exit status indicating a clean exit.
        /// </description>
        /// <see cref="quitWithErrorMessage" />
        public static void Quit() {
             InternalUnsafeMethods.Quit__Args _args = new InternalUnsafeMethods.Quit__Args() {
             };
             InternalUnsafeMethods.Quit()(_args);
        }

        /// <summary>Determines how log files are written.</summary>
        /// <description>
        /// Sets the operational mode of the console logging system.
        /// </description>
        /// <param name="mode">Parameter specifying the logging mode.  This can be:
        /// - 1: Open and close the console log file for each seperate string of output.  This will ensure that all parts get written out to disk and that no parts remain in intermediate buffers even if the process crashes.
        /// - 2: Keep the log file open and write to it continuously.  This will make the system operate faster but if the process crashes, parts of the output may not have been written to disk yet and will be missing from the log.
        /// 
        /// Additionally, when changing the log mode and thus opening a new log file, either of the two mode values may be combined by binary OR with 0x4 to cause the logging system to flush all console log messages that had already been issued to the console system into the newly created log file.</param>
        /// <remarks> Xbox 360 does not support logging to a file. Use Platform::OutputDebugStr in C++ instead.</remarks>
        public static void SetLogMode(int mode) {
             InternalUnsafeMethods.SetLogMode__Args _args = new InternalUnsafeMethods.SetLogMode__Args() {
                mode = mode,
             };
             InternalUnsafeMethods.SetLogMode()(_args);
        }

        /// <description>
        /// Replace all escape sequences in<paramref name="" /> text with their respective character codes.
        /// 
        /// This function replaces all escape sequences (\\n, \\t, etc) in the given string with the respective characters they represent.
        /// 
        /// The primary use of this function is for converting strings from their literal form into their compiled/translated form, as is normally done by the TorqueScript compiler.
        /// 
        /// 
        /// </description>
        /// <param name="text">A string.</param>
        /// <returns>A duplicate of<paramref name="" /> text with all escape sequences replaced by their respective character codes.
        /// 
        /// </returns>
        /// <code>
        /// // Print:
        /// //
        /// //    str
        /// //    ing
        /// //
        /// // to the console.  Note how the backslash in the string must be escaped here
        /// // in order to prevent the TorqueScript compiler from collapsing the escape
        /// // sequence in the resulting string.
        /// echo( collapseEscape( "str\ning" ) );
        /// </code>
        /// <see cref="expandEscape" />
        public static string CollapseEscape(string text) {
             InternalUnsafeMethods.CollapseEscape__Args _args = new InternalUnsafeMethods.CollapseEscape__Args() {
                text = text,
             };
             IntPtr _engineResult = InternalUnsafeMethods.CollapseEscape()(_args);
             return StringMarshal.IntPtrToUtf8String(_engineResult);
        }

        /// <summary>Replace all characters in<paramref name="" /> text that need to be escaped for the string to be a valid string literal with their respective escape sequences.
        /// 
        /// All characters in </summary>
        /// <param name="text">A string</param>
        /// <returns>A duplicate of the text parameter with all unescaped characters that cannot appear in string literals replaced by their respective escape sequences.</returns>
        /// <see cref="collapseEscape" />
        public static string ExpandEscape(string text) {
             InternalUnsafeMethods.ExpandEscape__Args _args = new InternalUnsafeMethods.ExpandEscape__Args() {
                text = text,
             };
             IntPtr _engineResult = InternalUnsafeMethods.ExpandEscape()(_args);
             return StringMarshal.IntPtrToUtf8String(_engineResult);
        }

        /// <summary>Logs the value of the given variable to the console.</summary>
        /// <description>
        /// Prints a string of the form "<variableName> = <variable value>" to the console.
        /// </description>
        /// <param name="variableName">Name of the local or global variable to print.</param>
        /// <code>
        /// %var = 1;
        /// debugv( "%var" ); // Prints "%var = 1"
        /// </code>
        public static void Debugv(string variableName) {
             InternalUnsafeMethods.Debugv__Args _args = new InternalUnsafeMethods.Debugv__Args() {
                variableName = variableName,
             };
             InternalUnsafeMethods.Debugv()(_args);
        }

        /// <description>
        /// ( string message... )
        /// </description>
        /// <summary>Logs an error message to the console.</summary>
        /// <description>
        /// Concatenates all given arguments to a single string and prints the string to the console as an error message (in the in-game console, these will show up using a red font by default). A newline is added automatically after the text.
        /// </description>
        /// <param name="message">Any number of string arguments.</param>
        public static void Error(params string[] args) { 
            List<string> _argList = new List<string>() {""};
            _argList.AddRange(args);

            StringVector nativeVecArgs = new StringVector {
                ElementCount = (uint)_argList.Count,
                Array = _argList.ToArray(),
                ArraySize = (uint)_argList.Count
            };
            nativeVecArgs.Alloc();
            InternalUnsafeMethods.Error()(ref nativeVecArgs.internalStruct);
            nativeVecArgs.Free();

        }

        /// <description>
        /// ( string message... )
        /// </description>
        /// <summary>Logs a warning message to the console.</summary>
        /// <description>
        /// Concatenates all given arguments to a single string and prints the string to the console as a warning message (in the in-game console, these will show up using a turquoise font by default). A newline is added automatically after the text.
        /// </description>
        /// <param name="message">Any number of string arguments.</param>
        public static void Warn(params string[] args) { 
            List<string> _argList = new List<string>() {""};
            _argList.AddRange(args);

            StringVector nativeVecArgs = new StringVector {
                ElementCount = (uint)_argList.Count,
                Array = _argList.ToArray(),
                ArraySize = (uint)_argList.Count
            };
            nativeVecArgs.Alloc();
            InternalUnsafeMethods.Warn()(ref nativeVecArgs.internalStruct);
            nativeVecArgs.Free();

        }

        /// <description>
        /// ( string message... )
        /// </description>
        /// <summary>Logs a message to the console.</summary>
        /// <description>
        /// Concatenates all given arguments to a single string and prints the string to the console. A newline is added automatically after the text.
        /// </description>
        /// <param name="message">Any number of string arguments.</param>
        public static void Echo(params string[] args) { 
            List<string> _argList = new List<string>() {""};
            _argList.AddRange(args);

            StringVector nativeVecArgs = new StringVector {
                ElementCount = (uint)_argList.Count,
                Array = _argList.ToArray(),
                ArraySize = (uint)_argList.Count
            };
            nativeVecArgs.Alloc();
            InternalUnsafeMethods.Echo()(ref nativeVecArgs.internalStruct);
            nativeVecArgs.Free();

        }

        /// <description>
        /// ( string textTagString )
        /// </description>
        /// <summary>Extracts the tag from a tagged string</summary>
        /// <description>
        /// Should only be used within the context of a function that receives a tagged string, and is not meant to be used outside of this context.
        /// </description>
        /// <param name="textTagString">The tagged string to extract.</param>
        /// <returns>The tag ID of the string.</returns>
        /// <see cref="\ref syntaxDataTypes under Tagged %Strings" />
        /// <see cref="detag()" />
        public static string GetTag(string textTagString) {
             InternalUnsafeMethods.GetTag__Args _args = new InternalUnsafeMethods.GetTag__Args() {
                textTagString = textTagString,
             };
             IntPtr _engineResult = InternalUnsafeMethods.GetTag()(_args);
             return StringMarshal.IntPtrToUtf8String(_engineResult);
        }

        /// <summary>Returns the string from a tag string.</summary>
        /// <description>
        /// Should only be used within the context of a function that receives a tagged string, and is not meant to be used outside of this context.  Use getTaggedString() to convert a tagged string ID back into a regular string at any time.
        /// </description>
        /// <code>
        /// // From scripts/client/message.cs
        /// function clientCmdChatMessage(%sender, %voice, %pitch, %msgString, %a1, %a2, %a3, %a4, %a5, %a6, %a7, %a8, %a9, %a10)
        /// {
        ///    onChatMessage(detag(%msgString), %voice, %pitch);
        /// }
        /// </code>
        /// <see cref="\ref syntaxDataTypes under Tagged %Strings" />
        /// <see cref="getTag()" />
        /// <see cref="getTaggedString()" />
        public static string Detag(string str) {
             InternalUnsafeMethods.Detag__Args _args = new InternalUnsafeMethods.Detag__Args() {
                str = str,
             };
             IntPtr _engineResult = InternalUnsafeMethods.Detag()(_args);
             return StringMarshal.IntPtrToUtf8String(_engineResult);
        }

        /// <description>
        /// Return the number of<paramref name="" /> delimiters substrings in 
        /// </description>
        /// <param name="text">A<paramref name="" /> delimiters list of substrings.
        /// </param>
        /// <param name="delimiters">Character or characters that separate the list of substrings in<paramref name="" /> text.
        /// </param>
        /// <returns>The number of<paramref name="" /> delimiters substrings in </returns>
        /// <code>
        /// getTokenCount( "a b c d e", " " ) // Returns 5
        /// </code>
        /// <see cref="getWordCount" />
        /// <see cref="getFieldCount" />
        /// <see cref="getRecordCount" />
        public static int GetTokenCount(string text, string delimiters) {
             InternalUnsafeMethods.GetTokenCount__Args _args = new InternalUnsafeMethods.GetTokenCount__Args() {
                text = text,
                delimiters = delimiters,
             };
             int _engineResult = InternalUnsafeMethods.GetTokenCount()(_args);
             return _engineResult;
        }

        /// <description>
        /// Remove the substring in<paramref name="" /> text separated by 
        /// </description>
        /// <param name="text">A<paramref name="" /> delimiters list of substrings.
        /// </param>
        /// <param name="delimiters">Character or characters that separate the list of substrings in<paramref name="" /> text.
        /// </param>
        /// <param name="index">The zero-based index of the word in<paramref name="" /> text.
        /// </param>
        /// <returns>A new string with the substring at the given index removed or the original string if<paramref name="" /> index is out of range.
        /// 
        /// </returns>
        /// <code>
        /// removeToken( "a b c d", " ", 2 ) // Returns "a b d"
        /// </code>
        /// <see cref="removeWord" />
        /// <see cref="removeField" />
        /// <see cref="removeRecord" />
        public static string RemoveToken(string text, string delimiters, int index) {
             InternalUnsafeMethods.RemoveToken__Args _args = new InternalUnsafeMethods.RemoveToken__Args() {
                text = text,
                delimiters = delimiters,
                index = index,
             };
             IntPtr _engineResult = InternalUnsafeMethods.RemoveToken()(_args);
             return StringMarshal.IntPtrToUtf8String(_engineResult);
        }

        /// <description>
        /// Replace the substring in<paramref name="" /> text separated by 
        /// </description>
        /// <param name="text">A<paramref name="" /> delimiters list of substrings.
        /// </param>
        /// <param name="delimiters">Character or characters that separate the list of substrings in<paramref name="" /> text.
        /// </param>
        /// <param name="index">The zero-based index of the substring to replace.</param>
        /// <param name="replacement">The string with which to replace the substring.</param>
        /// <returns>A new string with the substring at the given<paramref name="" /> index replaced by </returns>
        /// <code>
        /// setToken( "a b c d", " ", 2, "f" ) // Returns "a b f d"
        /// </code>
        /// <see cref="getToken" />
        /// <see cref="setWord" />
        /// <see cref="setField" />
        /// <see cref="setRecord" />
        public static string SetToken(string text, string delimiters, int index, string replacement) {
             InternalUnsafeMethods.SetToken__Args _args = new InternalUnsafeMethods.SetToken__Args() {
                text = text,
                delimiters = delimiters,
                index = index,
                replacement = replacement,
             };
             IntPtr _engineResult = InternalUnsafeMethods.SetToken()(_args);
             return StringMarshal.IntPtrToUtf8String(_engineResult);
        }

        /// <description>
        /// Extract a range of substrings separated by<paramref name="" /> delimiters at the given 
        /// </description>
        /// <param name="text">A<paramref name="" /> delimiters list of substrings.
        /// </param>
        /// <param name="delimiters">Character or characters that separate the list of substrings in<paramref name="" /> text.
        /// </param>
        /// <param name="startIndex">The zero-based index of the first substring to extract from<paramref name="" /> text.
        /// </param>
        /// <param name="endIndex">The zero-based index of the last substring to extract from<paramref name="" /> text.  If this is -1, all words beginning with </param>
        /// <returns>A string containing the specified range of substrings from<paramref name="" /> text or "" if </returns>
        /// <code>
        /// getTokens( "a b c d", " ", 1, 2, ) // Returns "b c"
        /// </code>
        /// <see cref="getToken" />
        /// <see cref="getTokenCount" />
        /// <see cref="getWords" />
        /// <see cref="getFields" />
        /// <see cref="getRecords" />
        public static string GetTokens(string text, string delimiters, int startIndex, int endIndex = -1) {
             InternalUnsafeMethods.GetTokens__Args _args = new InternalUnsafeMethods.GetTokens__Args() {
                text = text,
                delimiters = delimiters,
                startIndex = startIndex,
                endIndex = endIndex,
             };
             IntPtr _engineResult = InternalUnsafeMethods.GetTokens()(_args);
             return StringMarshal.IntPtrToUtf8String(_engineResult);
        }

        /// <description>
        /// Extract the substring at the given<paramref name="" /> index in the 
        /// </description>
        /// <param name="text">A<paramref name="" /> delimiters list of substrings.
        /// </param>
        /// <param name="delimiters">Character or characters that separate the list of substrings in<paramref name="" /> text.
        /// </param>
        /// <param name="index">The zero-based index of the substring to extract.</param>
        /// <returns>The substring at the given index or "" if the index is out of range.</returns>
        /// <code>
        /// getToken( "a b c d", " ", 2 ) // Returns "c"
        /// </code>
        /// <see cref="getTokens" />
        /// <see cref="getTokenCount" />
        /// <see cref="getWord" />
        /// <see cref="getField" />
        /// <see cref="getRecord" />
        public static string GetToken(string text, string delimiters, int index) {
             InternalUnsafeMethods.GetToken__Args _args = new InternalUnsafeMethods.GetToken__Args() {
                text = text,
                delimiters = delimiters,
                index = index,
             };
             IntPtr _engineResult = InternalUnsafeMethods.GetToken()(_args);
             return StringMarshal.IntPtrToUtf8String(_engineResult);
        }

        /// <description>
        /// ( string str, string token, string delimiters ) Tokenize a string using a set of delimiting characters.
        /// This function first skips all leading charaters in<paramref name="" /> str that are contained in 
        /// </description>
        /// <param name="str">A string.</param>
        /// <param name="token">The name of the variable in which to store the current token.  This variable is set in the scope in which nextToken is called.</param>
        /// <param name="delimiters">A string of characters.  Each character is considered a delimiter.</param>
        /// <returns>The remainder of<paramref name="" /> str after the token has been parsed out or "" if no more tokens were found in </returns>
        /// <code>
        /// // Prints:
        /// // a
        /// // b
        /// // c
        /// %str = "a   b c";
        /// while ( %str !$= "" )
        /// {
        ///    // First time, stores "a" in the variable %token and sets %str to "b c".
        ///    %str = nextToken( %str, "token", " " );
        ///    echo( %token );
        /// }
        /// </code>
        public static string NextToken(string str1, string token, string delim) {
             InternalUnsafeMethods.NextToken__Args _args = new InternalUnsafeMethods.NextToken__Args() {
                str1 = str1,
                token = token,
                delim = delim,
             };
             IntPtr _engineResult = InternalUnsafeMethods.NextToken()(_args);
             return StringMarshal.IntPtrToUtf8String(_engineResult);
        }

        /// <description>
        /// Return all but the first word in<paramref name="" /> text.
        /// 
        /// </description>
        /// <param name="text">A list of words separated by newlines, spaces, and/or tabs.</param>
        /// <returns><paramref name="" /> text with the first word removed.
        /// 
        /// </returns>
        /// <remarks> This is equal to 
        /// </remarks>
        /// <see cref="getWords" />
        public static string RestWords(string text) {
             InternalUnsafeMethods.RestWords__Args _args = new InternalUnsafeMethods.RestWords__Args() {
                text = text,
             };
             IntPtr _engineResult = InternalUnsafeMethods.RestWords()(_args);
             return StringMarshal.IntPtrToUtf8String(_engineResult);
        }

        /// <description>
        /// Return the first word in<paramref name="" /> text.
        /// 
        /// </description>
        /// <param name="text">A list of words separated by newlines, spaces, and/or tabs.</param>
        /// <returns>The word at index 0 in<paramref name="" /> text or "" if </returns>
        /// <remarks> This is equal to 
        /// </remarks>
        /// <see cref="getWord" />
        public static string FirstWord(string text) {
             InternalUnsafeMethods.FirstWord__Args _args = new InternalUnsafeMethods.FirstWord__Args() {
                text = text,
             };
             IntPtr _engineResult = InternalUnsafeMethods.FirstWord()(_args);
             return StringMarshal.IntPtrToUtf8String(_engineResult);
        }

        /// <description>
        /// Return the number of newline-separated records in<paramref name="" /> text.
        /// 
        /// </description>
        /// <param name="text">A list of records separated by newlines.</param>
        /// <returns>The number of newline-sepearated elements in<paramref name="" /> text.
        /// 
        /// </returns>
        /// <code>
        /// getRecordCount( "a b" NL "c d" NL "e f" ) // Returns 3
        /// </code>
        /// <see cref="getWordCount" />
        /// <see cref="getFieldCount" />
        public static int GetRecordCount(string text) {
             InternalUnsafeMethods.GetRecordCount__Args _args = new InternalUnsafeMethods.GetRecordCount__Args() {
                text = text,
             };
             int _engineResult = InternalUnsafeMethods.GetRecordCount()(_args);
             return _engineResult;
        }

        /// <description>
        /// Remove the record in<paramref name="" /> text at the given 
        /// </description>
        /// <param name="text">A list of records separated by newlines.</param>
        /// <param name="index">The zero-based index of the record in<paramref name="" /> text.
        /// </param>
        /// <returns>A new string with the record at the given<paramref name="" /> index removed or the original string if </returns>
        /// <code>
        /// removeRecord( "a b" NL "c d" NL "e f", 1 ) // Returns "a b" NL "e f"
        /// </code>
        /// <see cref="removeWord" />
        /// <see cref="removeField" />
        public static string RemoveRecord(string text, int index) {
             InternalUnsafeMethods.RemoveRecord__Args _args = new InternalUnsafeMethods.RemoveRecord__Args() {
                text = text,
                index = index,
             };
             IntPtr _engineResult = InternalUnsafeMethods.RemoveRecord()(_args);
             return StringMarshal.IntPtrToUtf8String(_engineResult);
        }

        /// <description>
        /// Replace the record in<paramref name="" /> text at the given 
        /// </description>
        /// <param name="text">A list of records separated by newlines.</param>
        /// <param name="index">The zero-based index of the record to replace.</param>
        /// <param name="replacement">The string with which to replace the record.</param>
        /// <returns>A new string with the record at the given<paramref name="" /> index replaced by </returns>
        /// <code>
        /// setRecord( "a b" NL "c d" NL "e f", 1, "g h" ) // Returns "a b" NL "g h" NL "e f"
        /// </code>
        /// <see cref="getRecord" />
        /// <see cref="setWord" />
        /// <see cref="setField" />
        public static string SetRecord(string text, int index, string replacement) {
             InternalUnsafeMethods.SetRecord__Args _args = new InternalUnsafeMethods.SetRecord__Args() {
                text = text,
                index = index,
                replacement = replacement,
             };
             IntPtr _engineResult = InternalUnsafeMethods.SetRecord()(_args);
             return StringMarshal.IntPtrToUtf8String(_engineResult);
        }

        /// <description>
        /// Extract a range of records from the given<paramref name="" /> startIndex onwards thru 
        /// </description>
        /// <param name="text">A list of records separated by newlines.</param>
        /// <param name="startIndex">The zero-based index of the first record to extract from<paramref name="" /> text.
        /// </param>
        /// <param name="endIndex">The zero-based index of the last record to extract from<paramref name="" /> text.  If this is -1, all records beginning with </param>
        /// <returns>A string containing the specified range of records from<paramref name="" /> text or "" if </returns>
        /// <code>
        /// getRecords( "a b" NL "c d" NL "e f", 1 ) // Returns "c d" NL "e f"
        /// </code>
        /// <see cref="getRecord" />
        /// <see cref="getRecordCount" />
        /// <see cref="getWords" />
        /// <see cref="getFields" />
        public static string GetRecords(string text, int startIndex, int endIndex = -1) {
             InternalUnsafeMethods.GetRecords__Args _args = new InternalUnsafeMethods.GetRecords__Args() {
                text = text,
                startIndex = startIndex,
                endIndex = endIndex,
             };
             IntPtr _engineResult = InternalUnsafeMethods.GetRecords()(_args);
             return StringMarshal.IntPtrToUtf8String(_engineResult);
        }

        /// <description>
        /// Extract the record at the given<paramref name="" /> index in the newline-separated list in 
        /// </description>
        /// <param name="text">A list of records separated by newlines.</param>
        /// <param name="index">The zero-based index of the record to extract.</param>
        /// <returns>The record at the given index or "" if<paramref name="" /> index is out of range.
        /// 
        /// </returns>
        /// <code>
        /// getRecord( "a b" NL "c d" NL "e f", 1 ) // Returns "c d"
        /// </code>
        /// <see cref="getRecords" />
        /// <see cref="getRecordCount" />
        /// <see cref="getWord" />
        /// <see cref="getField" />
        public static string GetRecord(string text, int index) {
             InternalUnsafeMethods.GetRecord__Args _args = new InternalUnsafeMethods.GetRecord__Args() {
                text = text,
                index = index,
             };
             IntPtr _engineResult = InternalUnsafeMethods.GetRecord()(_args);
             return StringMarshal.IntPtrToUtf8String(_engineResult);
        }

        /// <description>
        /// Return the number of newline and/or tab separated fields in<paramref name="" /> text.
        /// 
        /// </description>
        /// <param name="text">A list of fields separated by newlines and/or tabs.</param>
        /// <returns>The number of newline and/or tab sepearated elements in<paramref name="" /> text.
        /// 
        /// </returns>
        /// <code>
        /// getFieldCount( "a b" TAB "c d" TAB "e f" ) // Returns 3
        /// </code>
        /// <see cref="getWordCount" />
        /// <see cref="getRecordCount" />
        public static int GetFieldCount(string text) {
             InternalUnsafeMethods.GetFieldCount__Args _args = new InternalUnsafeMethods.GetFieldCount__Args() {
                text = text,
             };
             int _engineResult = InternalUnsafeMethods.GetFieldCount()(_args);
             return _engineResult;
        }

        /// <description>
        /// Remove the field in<paramref name="" /> text at the given 
        /// </description>
        /// <param name="text">A list of fields separated by newlines and/or tabs.</param>
        /// <param name="index">The zero-based index of the field in<paramref name="" /> text.
        /// </param>
        /// <returns>A new string with the field at the given index removed or the original string if<paramref name="" /> index is out of range.
        /// 
        /// </returns>
        /// <code>
        /// removeField( "a b" TAB "c d" TAB "e f", 1 ) // Returns "a b" TAB "e f"
        /// </code>
        /// <see cref="removeWord" />
        /// <see cref="removeRecord" />
        public static string RemoveField(string text, int index) {
             InternalUnsafeMethods.RemoveField__Args _args = new InternalUnsafeMethods.RemoveField__Args() {
                text = text,
                index = index,
             };
             IntPtr _engineResult = InternalUnsafeMethods.RemoveField()(_args);
             return StringMarshal.IntPtrToUtf8String(_engineResult);
        }

        /// <description>
        /// Replace the field in<paramref name="" /> text at the given 
        /// </description>
        /// <param name="text">A list of fields separated by newlines and/or tabs.</param>
        /// <param name="index">The zero-based index of the field to replace.</param>
        /// <param name="replacement">The string with which to replace the field.</param>
        /// <returns>A new string with the field at the given<paramref name="" /> index replaced by </returns>
        /// <code>
        /// setField( "a b" TAB "c d" TAB "e f", 1, "g h" ) // Returns "a b" TAB "g h" TAB "e f"
        /// </code>
        /// <see cref="getField" />
        /// <see cref="setWord" />
        /// <see cref="setRecord" />
        public static string SetField(string text, int index, string replacement) {
             InternalUnsafeMethods.SetField__Args _args = new InternalUnsafeMethods.SetField__Args() {
                text = text,
                index = index,
                replacement = replacement,
             };
             IntPtr _engineResult = InternalUnsafeMethods.SetField()(_args);
             return StringMarshal.IntPtrToUtf8String(_engineResult);
        }

        /// <description>
        /// Extract a range of fields from the given<paramref name="" /> startIndex onwards thru 
        /// </description>
        /// <param name="text">A list of fields separated by newlines and/or tabs.</param>
        /// <param name="startIndex">The zero-based index of the first field to extract from<paramref name="" /> text.
        /// </param>
        /// <param name="endIndex">The zero-based index of the last field to extract from<paramref name="" /> text.  If this is -1, all fields beginning with </param>
        /// <returns>A string containing the specified range of fields from<paramref name="" /> text or "" if </returns>
        /// <code>
        /// getFields( "a b" TAB "c d" TAB "e f", 1 ) // Returns "c d" TAB "e f"
        /// </code>
        /// <see cref="getField" />
        /// <see cref="getFieldCount" />
        /// <see cref="getWords" />
        /// <see cref="getRecords" />
        public static string GetFields(string text, int startIndex, int endIndex = -1) {
             InternalUnsafeMethods.GetFields__Args _args = new InternalUnsafeMethods.GetFields__Args() {
                text = text,
                startIndex = startIndex,
                endIndex = endIndex,
             };
             IntPtr _engineResult = InternalUnsafeMethods.GetFields()(_args);
             return StringMarshal.IntPtrToUtf8String(_engineResult);
        }

        /// <description>
        /// Extract the field at the given<paramref name="" /> index in the newline and/or tab separated list in 
        /// </description>
        /// <param name="text">A list of fields separated by newlines and/or tabs.</param>
        /// <param name="index">The zero-based index of the field to extract.</param>
        /// <returns>The field at the given index or "" if the index is out of range.</returns>
        /// <code>
        /// getField( "a b" TAB "c d" TAB "e f", 1 ) // Returns "c d"
        /// </code>
        /// <see cref="getFields" />
        /// <see cref="getFieldCount" />
        /// <see cref="getWord" />
        /// <see cref="getRecord" />
        public static string GetField(string text, int index) {
             InternalUnsafeMethods.GetField__Args _args = new InternalUnsafeMethods.GetField__Args() {
                text = text,
                index = index,
             };
             IntPtr _engineResult = InternalUnsafeMethods.GetField()(_args);
             return StringMarshal.IntPtrToUtf8String(_engineResult);
        }

        /// <summary>returns weekday as a word given a number or "" if number is bad</summary>
        /// <returns>weekday as a word given a number or "" if number is bad</returns>
        public static string WeekdayNumToStr(int num, bool abbreviate = false) {
             InternalUnsafeMethods.WeekdayNumToStr__Args _args = new InternalUnsafeMethods.WeekdayNumToStr__Args() {
                num = num,
                abbreviate = abbreviate,
             };
             IntPtr _engineResult = InternalUnsafeMethods.WeekdayNumToStr()(_args);
             return StringMarshal.IntPtrToUtf8String(_engineResult);
        }

        /// <summary>returns month as a word given a number or "" if number is bad</summary>
        /// <returns>month as a word given a number or "" if number is bad</returns>
        public static string MonthNumToStr(int num, bool abbreviate = false) {
             InternalUnsafeMethods.MonthNumToStr__Args _args = new InternalUnsafeMethods.MonthNumToStr__Args() {
                num = num,
                abbreviate = abbreviate,
             };
             IntPtr _engineResult = InternalUnsafeMethods.MonthNumToStr()(_args);
             return StringMarshal.IntPtrToUtf8String(_engineResult);
        }

        /// <description>
        /// Return the number of whitespace-separated words in<paramref name="" /> text.
        /// Words in 
        /// </description>
        /// <param name="text">A whitespace-separated list of words.</param>
        /// <returns>The number of whitespace-separated words in<paramref name="" /> text.
        /// 
        /// </returns>
        /// <code>
        /// getWordCount( "a b c d e" ) // Returns 5
        /// </code>
        /// <see cref="getTokenCount" />
        /// <see cref="getFieldCount" />
        /// <see cref="getRecordCount" />
        public static int GetWordCount(string text) {
             InternalUnsafeMethods.GetWordCount__Args _args = new InternalUnsafeMethods.GetWordCount__Args() {
                text = text,
             };
             int _engineResult = InternalUnsafeMethods.GetWordCount()(_args);
             return _engineResult;
        }

        /// <description>
        /// Remove the word in<paramref name="" /> text at the given 
        /// </description>
        /// <param name="text">A whitespace-separated list of words.</param>
        /// <param name="index">The zero-based index of the word in<paramref name="" /> text.
        /// </param>
        /// <returns>A new string with the word at the given index removed or the original string if<paramref name="" /> index is out of range.
        /// 
        /// </returns>
        /// <code>
        /// removeWord( "a b c d", 2 ) // Returns "a b d"
        /// </code>
        /// <see cref="removeToken" />
        /// <see cref="removeField" />
        /// <see cref="removeRecord" />
        public static string RemoveWord(string text, int index) {
             InternalUnsafeMethods.RemoveWord__Args _args = new InternalUnsafeMethods.RemoveWord__Args() {
                text = text,
                index = index,
             };
             IntPtr _engineResult = InternalUnsafeMethods.RemoveWord()(_args);
             return StringMarshal.IntPtrToUtf8String(_engineResult);
        }

        /// <description>
        /// Replace the word in<paramref name="" /> text at the given 
        /// </description>
        /// <param name="text">A whitespace-separated list of words.</param>
        /// <param name="index">The zero-based index of the word to replace.</param>
        /// <param name="replacement">The string with which to replace the word.</param>
        /// <returns>A new string with the word at the given<paramref name="" /> index replaced by </returns>
        /// <code>
        /// setWord( "a b c d", 2, "f" ) // Returns "a b f d"
        /// </code>
        /// <see cref="getWord" />
        /// <see cref="setToken" />
        /// <see cref="setField" />
        /// <see cref="setRecord" />
        public static string SetWord(string text, int index, string replacement) {
             InternalUnsafeMethods.SetWord__Args _args = new InternalUnsafeMethods.SetWord__Args() {
                text = text,
                index = index,
                replacement = replacement,
             };
             IntPtr _engineResult = InternalUnsafeMethods.SetWord()(_args);
             return StringMarshal.IntPtrToUtf8String(_engineResult);
        }

        /// <description>
        /// Extract a range of words from the given<paramref name="" /> startIndex onwards thru 
        /// </description>
        /// <param name="text">A whitespace-separated list of words.</param>
        /// <param name="startIndex">The zero-based index of the first word to extract from<paramref name="" /> text.
        /// </param>
        /// <param name="endIndex">The zero-based index of the last word to extract from<paramref name="" /> text.  If this is -1, all words beginning with </param>
        /// <returns>A string containing the specified range of words from<paramref name="" /> text or "" if </returns>
        /// <code>
        /// getWords( "a b c d", 1, 2, ) // Returns "b c"
        /// </code>
        /// <see cref="getWord" />
        /// <see cref="getWordCount" />
        /// <see cref="getTokens" />
        /// <see cref="getFields" />
        /// <see cref="getRecords" />
        public static string GetWords(string text, int startIndex, int endIndex = -1) {
             InternalUnsafeMethods.GetWords__Args _args = new InternalUnsafeMethods.GetWords__Args() {
                text = text,
                startIndex = startIndex,
                endIndex = endIndex,
             };
             IntPtr _engineResult = InternalUnsafeMethods.GetWords()(_args);
             return StringMarshal.IntPtrToUtf8String(_engineResult);
        }

        /// <description>
        /// Extract the word at the given<paramref name="" /> index in the whitespace-separated list in 
        /// </description>
        /// <param name="text">A whitespace-separated list of words.</param>
        /// <param name="index">The zero-based index of the word to extract.</param>
        /// <returns>The word at the given index or "" if the index is out of range.</returns>
        /// <code>
        /// getWord( "a b c", 1 ) // Returns "b"
        /// </code>
        /// <see cref="getWords" />
        /// <see cref="getWordCount" />
        /// <see cref="getToken" />
        /// <see cref="getField" />
        /// <see cref="getRecord" />
        public static string GetWord(string text, int index) {
             InternalUnsafeMethods.GetWord__Args _args = new InternalUnsafeMethods.GetWord__Args() {
                text = text,
                index = index,
             };
             IntPtr _engineResult = InternalUnsafeMethods.GetWord()(_args);
             return StringMarshal.IntPtrToUtf8String(_engineResult);
        }

        /// <description>
        /// [string1, string2, ...]Adds case sensitive strings to the StringTable.
        /// </description>
        public static void AddCaseSensitiveStrings(params string[] args) { 
            List<string> _argList = new List<string>() {""};
            _argList.AddRange(args);

            StringVector nativeVecArgs = new StringVector {
                ElementCount = (uint)_argList.Count,
                Array = _argList.ToArray(),
                ArraySize = (uint)_argList.Count
            };
            nativeVecArgs.Alloc();
            InternalUnsafeMethods.AddCaseSensitiveStrings()(ref nativeVecArgs.internalStruct);
            nativeVecArgs.Free();

        }

        /// <description>
        /// Returns true if the string is a valid ip address, excepts localhost.
        /// </description>
        /// <param name="str">The string to test.</param>
        /// <returns>true if<paramref name="" /> str is a valid ip address and false if not
        /// 
        /// </returns>
        /// <code>
        /// isValidIP( "localhost" ) // Returns true.
        /// </code>
        public static bool IsValidIP(string str) {
             InternalUnsafeMethods.IsValidIP__Args _args = new InternalUnsafeMethods.IsValidIP__Args() {
                str = str,
             };
             bool _engineResult = InternalUnsafeMethods.IsValidIP()(_args);
             return _engineResult;
        }

        /// <description>
        /// Returns true if the string is a valid port number.
        /// </description>
        /// <param name="str">The string to test.</param>
        /// <returns>true if<paramref name="" /> str is a port and false if not
        /// 
        /// </returns>
        /// <code>
        /// isValidPort( "8080" ) // Returns true.
        /// </code>
        public static bool IsValidPort(string str) {
             InternalUnsafeMethods.IsValidPort__Args _args = new InternalUnsafeMethods.IsValidPort__Args() {
                str = str,
             };
             bool _engineResult = InternalUnsafeMethods.IsValidPort()(_args);
             return _engineResult;
        }

        /// <description>
        /// Returns true if the string is a float.
        /// </description>
        /// <param name="str">The string to test.</param>
        /// <param name="sciOk">Test for correct scientific notation and accept it (ex. 1.2e+14)</param>
        /// <returns>true if<paramref name="" /> str is a float and false if not
        /// 
        /// </returns>
        /// <code>
        /// isFloat( "13.5" ) // Returns true.
        /// </code>
        public static bool IsFloat(string str, bool sciOk = false) {
             InternalUnsafeMethods.IsFloat__Args _args = new InternalUnsafeMethods.IsFloat__Args() {
                str = str,
                sciOk = sciOk,
             };
             bool _engineResult = InternalUnsafeMethods.IsFloat()(_args);
             return _engineResult;
        }

        /// <description>
        /// Returns true if the string is an integer.
        /// </description>
        /// <param name="str">The string to test.</param>
        /// <returns>true if<paramref name="" /> str is an integer and false if not
        /// 
        /// </returns>
        /// <code>
        /// isInt( "13" ) // Returns true.
        /// </code>
        public static bool IsInt(string str) {
             InternalUnsafeMethods.IsInt__Args _args = new InternalUnsafeMethods.IsInt__Args() {
                str = str,
             };
             bool _engineResult = InternalUnsafeMethods.IsInt()(_args);
             return _engineResult;
        }

        /// <description>
        /// Parse a Toggle Case word into separate words.
        /// </description>
        /// <param name="str">The string to parse.</param>
        /// <returns>new string space separated.</returns>
        /// <code>
        /// strToggleCaseToWords( "HelloWorld" ) // Returns "Hello World".
        /// </code>
        public static string StrToggleCaseToWords(string str) {
             InternalUnsafeMethods.StrToggleCaseToWords__Args _args = new InternalUnsafeMethods.StrToggleCaseToWords__Args() {
                str = str,
             };
             IntPtr _engineResult = InternalUnsafeMethods.StrToggleCaseToWords()(_args);
             return StringMarshal.IntPtrToUtf8String(_engineResult);
        }

        /// <description>
        /// Convert from a HSB (hue, saturation, brightness) to an integer RGB (red, green, blue) color. HSB is also know as HSL or HSV as well, with the last letter standing for lightness or value.
        /// </description>
        /// <param name="hsb">HSB (hue, saturation, brightness) value to be converted.</param>
        /// <returns>Integer color value to be converted in the form "R G B A", where R is red, G is green, B is blue, and A is alpha. Alpha isn't handled/converted so only pay attention to the RGB value</returns>
        /// <code>
        /// ColorHSBToRGB( "240 100 100" ) // Returns "0 0 255 0".
        /// </code>
        public static ColorI ColorHSBToRGB(Point3I hsb) {
hsb.Alloc();             InternalUnsafeMethods.ColorHSBToRGB__Args _args = new InternalUnsafeMethods.ColorHSBToRGB__Args() {
                hsb = hsb.internalStructPtr,
             };
             ColorI.InternalStruct _engineResult = InternalUnsafeMethods.ColorHSBToRGB()(_args);
hsb.Free();             return new ColorI(_engineResult);
        }

        /// <description>
        /// Convert from a hex color value to an integer RGB (red, green, blue) color (00 - FF to 0 to 255).
        /// </description>
        /// <param name="hex">Hex color value (#000000 - #FFFFFF) to be converted to an RGB (red, green, blue) value.</param>
        /// <returns>Integer color value to be converted in the form "R G B A", where R is red, G is green, B is blue, and A is alpha. Alpha isn't handled/converted so only pay attention to the RGB value</returns>
        /// <code>
        /// ColorHEXToRGB( "#0000FF" ) // Returns "0 0 255 0".
        /// </code>
        public static ColorI ColorHEXToRGB(string hex) {
             InternalUnsafeMethods.ColorHEXToRGB__Args _args = new InternalUnsafeMethods.ColorHEXToRGB__Args() {
                hex = hex,
             };
             ColorI.InternalStruct _engineResult = InternalUnsafeMethods.ColorHEXToRGB()(_args);
             return new ColorI(_engineResult);
        }

        /// <description>
        /// Convert from a integer RGB (red, green, blue) color to HSB (hue, saturation, brightness). HSB is also know as HSL or HSV as well, with the last letter standing for lightness or value.
        /// </description>
        /// <param name="color">Integer color value to be converted in the form "R G B A", where R is red, G is green, B is blue, and A is alpha. It excepts an alpha, but keep in mind this will not be converted.</param>
        /// <returns>HSB color value, alpha isn't handled/converted so it is only the RGB value</returns>
        /// <code>
        /// ColorRBGToHSB( "0 0 255 128" ) // Returns "240 100 100".
        /// </code>
        public static string ColorRGBToHSB(ColorI color) {
color.Alloc();             InternalUnsafeMethods.ColorRGBToHSB__Args _args = new InternalUnsafeMethods.ColorRGBToHSB__Args() {
                color = color.internalStructPtr,
             };
             IntPtr _engineResult = InternalUnsafeMethods.ColorRGBToHSB()(_args);
color.Free();             return StringMarshal.IntPtrToUtf8String(_engineResult);
        }

        /// <description>
        /// Convert from a integer RGB (red, green, blue) color to hex color value (0 to 255 to 00 - FF).
        /// </description>
        /// <param name="color">Integer color value to be converted in the form "R G B A", where R is red, G is green, B is blue, and A is alpha. It excepts an alpha, but keep in mind this will not be converted.</param>
        /// <returns>Hex color value (#000000 - #FFFFFF), alpha isn't handled/converted so it is only the RGB value</returns>
        /// <code>
        /// ColorRBGToHEX( "0 0 255 128" ) // Returns "#0000FF".
        /// </code>
        public static string ColorRGBToHEX(ColorI color) {
color.Alloc();             InternalUnsafeMethods.ColorRGBToHEX__Args _args = new InternalUnsafeMethods.ColorRGBToHEX__Args() {
                color = color.internalStructPtr,
             };
             IntPtr _engineResult = InternalUnsafeMethods.ColorRGBToHEX()(_args);
color.Free();             return StringMarshal.IntPtrToUtf8String(_engineResult);
        }

        /// <description>
        /// Convert from a integer color to an float color (0 to 255 to 0.0 - 1.0).
        /// </description>
        /// <param name="color">Integer color value to be converted in the form "R G B A", where R is red, G is green, B is blue, and A is alpha.</param>
        /// <returns>Converted color value (0.0 - 1.0)</returns>
        /// <code>
        /// ColorIntToFloat( "0 0 255 128" ) // Returns "0 0 1 0.5".
        /// </code>
        public static LinearColorF ColorIntToFloat(ColorI color) {
color.Alloc();             InternalUnsafeMethods.ColorIntToFloat__Args _args = new InternalUnsafeMethods.ColorIntToFloat__Args() {
                color = color.internalStructPtr,
             };
             LinearColorF.InternalStruct _engineResult = InternalUnsafeMethods.ColorIntToFloat()(_args);
color.Free();             return new LinearColorF(_engineResult);
        }

        /// <description>
        /// Convert from a float color to an integer color (0.0 - 1.0 to 0 to 255).
        /// </description>
        /// <param name="color">Float color value to be converted in the form "R G B A", where R is red, G is green, B is blue, and A is alpha.</param>
        /// <returns>Converted color value (0 - 255)</returns>
        /// <code>
        /// ColorFloatToInt( "0 0 1 0.5" ) // Returns "0 0 255 128".
        /// </code>
        public static ColorI ColorFloatToInt(LinearColorF color) {
color.Alloc();             InternalUnsafeMethods.ColorFloatToInt__Args _args = new InternalUnsafeMethods.ColorFloatToInt__Args() {
                color = color.internalStructPtr,
             };
             ColorI.InternalStruct _engineResult = InternalUnsafeMethods.ColorFloatToInt()(_args);
color.Free();             return new ColorI(_engineResult);
        }

        /// <description>
        /// Find the last occurrence of the given character in the given string.
        /// </description>
        /// <param name="str">The string to search.</param>
        /// <param name="chr">The character to look for.  Only the first character of this string will be searched for.</param>
        /// <param name="start">The index into<paramref name="" /> str at which to start searching for the given character.
        /// </param>
        /// <returns>The index of the last occurrence of<paramref name="" /> chr in </returns>
        /// <code>
        /// strrchrpos( "test", "t" ) // Returns 3.
        /// </code>
        public static int Strrchrpos(string str, string chr, int start = 0) {
             InternalUnsafeMethods.Strrchrpos__Args _args = new InternalUnsafeMethods.Strrchrpos__Args() {
                str = str,
                chr = chr,
                start = start,
             };
             int _engineResult = InternalUnsafeMethods.Strrchrpos()(_args);
             return _engineResult;
        }

        /// <description>
        /// Find the first occurrence of the given character in the given string.
        /// </description>
        /// <param name="str">The string to search.</param>
        /// <param name="chr">The character to look for.  Only the first character of this string will be searched for.</param>
        /// <param name="start">The index into<paramref name="" /> str at which to start searching for the given character.
        /// </param>
        /// <returns>The index of the first occurrence of<paramref name="" /> chr in </returns>
        /// <code>
        /// strchrpos( "test", "s" ) // Returns 2.
        /// </code>
        public static int Strchrpos(string str, string chr, int start = 0) {
             InternalUnsafeMethods.Strchrpos__Args _args = new InternalUnsafeMethods.Strchrpos__Args() {
                str = str,
                chr = chr,
                start = start,
             };
             int _engineResult = InternalUnsafeMethods.Strchrpos()(_args);
             return _engineResult;
        }

        /// <summary>Test whether the given string ends with the given suffix.</summary>
        /// <description>
        /// 
        /// </description>
        /// <param name="str">The string to test.</param>
        /// <param name="suffix">The potential suffix of<paramref name="" /> str.
        /// </param>
        /// <param name="caseSensitive">If true, the comparison will be case-sensitive; if false, differences in casing will not be taken into account.</param>
        /// <returns>True if the last characters in<paramref name="" /> str match the complete contents of </returns>
        /// <code>
        /// startsWith( "TEST123", "123" ) // Returns true.
        /// </code>
        /// <see cref="startsWith" />
        public static bool EndsWith(string str, string suffix, bool caseSensitive = false) {
             InternalUnsafeMethods.EndsWith__Args _args = new InternalUnsafeMethods.EndsWith__Args() {
                str = str,
                suffix = suffix,
                caseSensitive = caseSensitive,
             };
             bool _engineResult = InternalUnsafeMethods.EndsWith()(_args);
             return _engineResult;
        }

        /// <description>
        /// Test whether the given string begins with the given prefix.
        /// </description>
        /// <param name="str">The string to test.</param>
        /// <param name="prefix">The potential prefix of<paramref name="" /> str.
        /// </param>
        /// <param name="caseSensitive">If true, the comparison will be case-sensitive; if false, differences in casing will not be taken into account.</param>
        /// <returns>True if the first characters in<paramref name="" /> str match the complete contents of </returns>
        /// <code>
        /// startsWith( "TEST123", "test" ) // Returns true.
        /// </code>
        /// <see cref="endsWith" />
        public static bool StartsWith(string str, string prefix, bool caseSensitive = false) {
             InternalUnsafeMethods.StartsWith__Args _args = new InternalUnsafeMethods.StartsWith__Args() {
                str = str,
                prefix = prefix,
                caseSensitive = caseSensitive,
             };
             bool _engineResult = InternalUnsafeMethods.StartsWith()(_args);
             return _engineResult;
        }

        /// <description>
        /// Test whether the character at the given position is an alpha-numeric character.
        /// Alpha-numeric characters are characters that are either alphabetic (a-z, A-Z) or numbers (0-9).
        /// </description>
        /// <param name="str">The string to test.</param>
        /// <param name="index">The index of a character in<paramref name="" /> str.
        /// </param>
        /// <returns>True if the character at the given index in<paramref name="" /> str is an alpha-numeric character; false otherwise.
        /// 
        /// </returns>
        /// <see cref="isspace" />
        public static bool Isalnum(string str, int index) {
             InternalUnsafeMethods.Isalnum__Args _args = new InternalUnsafeMethods.Isalnum__Args() {
                str = str,
                index = index,
             };
             bool _engineResult = InternalUnsafeMethods.Isalnum()(_args);
             return _engineResult;
        }

        /// <description>
        /// Test whether the character at the given position is a whitespace character.
        /// Characters such as tab, space, or newline are considered whitespace.
        /// </description>
        /// <param name="str">The string to test.</param>
        /// <param name="index">The index of a character in<paramref name="" /> str.
        /// </param>
        /// <returns>True if the character at the given index in<paramref name="" /> str is a whitespace character; false otherwise.
        /// 
        /// </returns>
        /// <see cref="isalnum" />
        public static bool Isspace(string str, int index) {
             InternalUnsafeMethods.Isspace__Args _args = new InternalUnsafeMethods.Isspace__Args() {
                str = str,
                index = index,
             };
             bool _engineResult = InternalUnsafeMethods.Isspace()(_args);
             return _engineResult;
        }

        /// <description>
        /// Get the first occuring number from<paramref name="" /> str.
        /// 
        /// </description>
        /// <param name="str">The string from which to read out the first number.</param>
        /// <returns>String representation of the number or  if no number.</returns>
        public static string GetFirstNumber(string str) {
             InternalUnsafeMethods.GetFirstNumber__Args _args = new InternalUnsafeMethods.GetFirstNumber__Args() {
                str = str,
             };
             IntPtr _engineResult = InternalUnsafeMethods.GetFirstNumber()(_args);
             return StringMarshal.IntPtrToUtf8String(_engineResult);
        }

        /// <description>
        /// Strip a numeric suffix from the given string.
        /// </description>
        /// <param name="str">The string from which to strip its numeric suffix.</param>
        /// <returns>The string<paramref name="" /> str without its number suffix or the original string </returns>
        /// <code>
        /// stripTrailingNumber( "test123" ) // Returns "test".
        /// </code>
        /// <see cref="getTrailingNumber" />
        public static string StripTrailingNumber(string str) {
             InternalUnsafeMethods.StripTrailingNumber__Args _args = new InternalUnsafeMethods.StripTrailingNumber__Args() {
                str = str,
             };
             IntPtr _engineResult = InternalUnsafeMethods.StripTrailingNumber()(_args);
             return StringMarshal.IntPtrToUtf8String(_engineResult);
        }

        /// <description>
        /// Get the numeric suffix of the given input string.
        /// </description>
        /// <param name="str">The string from which to read out the numeric suffix.</param>
        /// <returns>The numeric value of the number suffix of<paramref name="" /> str or -1 if </returns>
        /// <code>
        /// getTrailingNumber( "test123" ) // Returns '123'.
        /// </code>
        /// <see cref="stripTrailingNumber" />
        public static int GetTrailingNumber(string str) {
             InternalUnsafeMethods.GetTrailingNumber__Args _args = new InternalUnsafeMethods.GetTrailingNumber__Args() {
                str = str,
             };
             int _engineResult = InternalUnsafeMethods.GetTrailingNumber()(_args);
             return _engineResult;
        }

        /// <description>
        /// Match a multiple patterns against a single string.
        /// </description>
        /// <param name="patterns">A tab-separated list of patterns.  Each pattern can include charaters, '*' to match any number of characters and '?' to match a single character.  Each of the patterns is tried in turn.</param>
        /// <param name="str">The string which should be matched against<paramref name="" /> patterns.
        /// </param>
        /// <param name="caseSensitive">If true, characters in the pattern are matched in case-sensitive fashion against this string.  If false, differences in casing are ignored.</param>
        /// <returns>True if<paramref name="" /> str matches any of the given </returns>
        /// <code>
        /// strIsMatchMultipleExpr( "*.cs *.gui *.mis", "mymission.mis" ) // Returns true.
        /// </code>
        /// <see cref="strIsMatchExpr" />
        public static bool StrIsMatchMultipleExpr(string patterns, string str, bool caseSensitive = false) {
             InternalUnsafeMethods.StrIsMatchMultipleExpr__Args _args = new InternalUnsafeMethods.StrIsMatchMultipleExpr__Args() {
                patterns = patterns,
                str = str,
                caseSensitive = caseSensitive,
             };
             bool _engineResult = InternalUnsafeMethods.StrIsMatchMultipleExpr()(_args);
             return _engineResult;
        }

        /// <description>
        /// Match a pattern against a string.
        /// </description>
        /// <param name="pattern">The wildcard pattern to match against.  The pattern can include characters, '*' to match any number of characters and '?' to match a single character.</param>
        /// <param name="str">The string which should be matched against<paramref name="" /> pattern.
        /// </param>
        /// <param name="caseSensitive">If true, characters in the pattern are matched in case-sensitive fashion against this string.  If false, differences in casing are ignored.</param>
        /// <returns>True if<paramref name="" /> str matches the given </returns>
        /// <code>
        /// strIsMatchExpr( "f?o*R", "foobar" ) // Returns true.
        /// </code>
        /// <see cref="strIsMatchMultipleExpr" />
        public static bool StrIsMatchExpr(string pattern, string str, bool caseSensitive = false) {
             InternalUnsafeMethods.StrIsMatchExpr__Args _args = new InternalUnsafeMethods.StrIsMatchExpr__Args() {
                pattern = pattern,
                str = str,
                caseSensitive = caseSensitive,
             };
             bool _engineResult = InternalUnsafeMethods.StrIsMatchExpr()(_args);
             return _engineResult;
        }

        /// <summary>Return a substring of<paramref name="" /> str starting at </summary>
        /// <param name="str">The string from which to extract a substring.</param>
        /// <param name="start">The offset at which to start copying out characters.</param>
        /// <param name="numChars">Optional argument to specify the number of characters to copy.  If this is -1, all characters up the end of the input string are copied.</param>
        /// <returns>A string that contains the given portion of the input string.</returns>
        /// <code>
        /// getSubStr( "foobar", 1, 2 ) // Returns "oo".
        /// </code>
        public static string GetSubStr(string str, int start, int numChars = -1) {
             InternalUnsafeMethods.GetSubStr__Args _args = new InternalUnsafeMethods.GetSubStr__Args() {
                str = str,
                start = start,
                numChars = numChars,
             };
             IntPtr _engineResult = InternalUnsafeMethods.GetSubStr()(_args);
             return StringMarshal.IntPtrToUtf8String(_engineResult);
        }

        /// <description>
        /// Return a string that repeats<paramref name="" /> str 
        /// </description>
        /// <param name="str">The string to repeat multiple times.</param>
        /// <param name="numTimes">The number of times to repeat<paramref name="" /> str in the result string.
        /// </param>
        /// <param name="delimiter">The string to put between each repetition of<paramref name="" /> str.
        /// </param>
        /// <returns>A string containing<paramref name="" /> str repeated </returns>
        /// <code>
        /// strrepeat( "a", 5, "b" ) // Returns "ababababa".
        /// </code>
        public static string Strrepeat(string str, int numTimes, string delimiter = "") {
             InternalUnsafeMethods.Strrepeat__Args _args = new InternalUnsafeMethods.Strrepeat__Args() {
                str = str,
                numTimes = numTimes,
                delimiter = delimiter,
             };
             IntPtr _engineResult = InternalUnsafeMethods.Strrepeat()(_args);
             return StringMarshal.IntPtrToUtf8String(_engineResult);
        }

        /// <description>
        /// Replace all occurrences of<paramref name="" /> from in 
        /// </description>
        /// <param name="source">The string in which to replace the occurrences of<paramref name="" /> from.
        /// </param>
        /// <param name="from">The string to replace in<paramref name="" /> source.
        /// </param>
        /// <param name="to">The string with which to replace occurrences of</param>
        /// <returns>A string with all occurrences of<paramref name="" /> from in </returns>
        /// <code>
        /// strreplace( "aabbccbb", "bb", "ee" ) // Returns "aaeeccee".
        /// </code>
        public static string Strreplace(string source, string from, string to) {
             InternalUnsafeMethods.Strreplace__Args _args = new InternalUnsafeMethods.Strreplace__Args() {
                source = source,
                from = from,
                to = to,
             };
             IntPtr _engineResult = InternalUnsafeMethods.Strreplace()(_args);
             return StringMarshal.IntPtrToUtf8String(_engineResult);
        }

        /// <description>
        /// Find the last occurrence of the given character in<paramref name="" /> str.
        /// </description>
        /// <param name="str">The string to search.</param>
        /// <param name="chr">The character to search for.  Only the first character from the string is taken.</param>
        /// <returns>The remainder of the input string starting with the given character or the empty string if the character could not be found.</returns>
        /// <see cref="strchr" />
        public static string Strrchr(string str, string chr) {
             InternalUnsafeMethods.Strrchr__Args _args = new InternalUnsafeMethods.Strrchr__Args() {
                str = str,
                chr = chr,
             };
             IntPtr _engineResult = InternalUnsafeMethods.Strrchr()(_args);
             return StringMarshal.IntPtrToUtf8String(_engineResult);
        }

        /// <description>
        /// Find the first occurrence of the given character in<paramref name="" /> str.
        /// 
        /// </description>
        /// <param name="str">The string to search.</param>
        /// <param name="chr">The character to search for.  Only the first character from the string is taken.</param>
        /// <returns>The remainder of the input string starting with the given character or the empty string if the character could not be found.</returns>
        /// <see cref="strrchr" />
        public static string Strchr(string str, string chr) {
             InternalUnsafeMethods.Strchr__Args _args = new InternalUnsafeMethods.Strchr__Args() {
                str = str,
                chr = chr,
             };
             IntPtr _engineResult = InternalUnsafeMethods.Strchr()(_args);
             return StringMarshal.IntPtrToUtf8String(_engineResult);
        }

        /// <description>
        /// Return an all upper-case version of the given string.
        /// </description>
        /// <param name="str">A string.</param>
        /// <returns>A version of<paramref name="" /> str with all characters converted to upper-case.
        /// 
        /// </returns>
        /// <code>
        /// strupr( "TesT1" ) // Returns "TEST1"
        /// </code>
        /// <see cref="strlwr" />
        public static string Strupr(string str) {
             InternalUnsafeMethods.Strupr__Args _args = new InternalUnsafeMethods.Strupr__Args() {
                str = str,
             };
             IntPtr _engineResult = InternalUnsafeMethods.Strupr()(_args);
             return StringMarshal.IntPtrToUtf8String(_engineResult);
        }

        /// <description>
        /// Return an all lower-case version of the given string.
        /// </description>
        /// <param name="str">A string.</param>
        /// <returns>A version of<paramref name="" /> str with all characters converted to lower-case.
        /// 
        /// </returns>
        /// <code>
        /// strlwr( "TesT1" ) // Returns "test1"
        /// </code>
        /// <see cref="strupr" />
        public static string Strlwr(string str) {
             InternalUnsafeMethods.Strlwr__Args _args = new InternalUnsafeMethods.Strlwr__Args() {
                str = str,
             };
             IntPtr _engineResult = InternalUnsafeMethods.Strlwr()(_args);
             return StringMarshal.IntPtrToUtf8String(_engineResult);
        }

        /// <description>
        /// Remove all occurrences of characters contained in<paramref name="" /> chars from 
        /// </description>
        /// <param name="str">The string to filter characters out from.</param>
        /// <param name="chars">A string of characters to filter out from<paramref name="" /> str.
        /// </param>
        /// <returns>A version of<paramref name="" /> str with all occurrences of characters contained in </returns>
        /// <code>
        /// stripChars( "teststring", "se" ); // Returns "tttring".
        /// </code>
        public static string StripChars(string str, string chars) {
             InternalUnsafeMethods.StripChars__Args _args = new InternalUnsafeMethods.StripChars__Args() {
                str = str,
                chars = chars,
             };
             IntPtr _engineResult = InternalUnsafeMethods.StripChars()(_args);
             return StringMarshal.IntPtrToUtf8String(_engineResult);
        }

        /// <description>
        /// Remove leading and trailing whitespace from the string.
        /// </description>
        /// <param name="str">A string.</param>
        /// <returns>A string that is the same as<paramref name="" /> str but with any leading (i.e. leftmost) and trailing (i.e. rightmost) whitespace removed.
        /// 
        /// </returns>
        /// <code>
        /// trim( "   string  " ); // Returns "string".
        /// </code>
        public static string Trim(string str) {
             InternalUnsafeMethods.Trim__Args _args = new InternalUnsafeMethods.Trim__Args() {
                str = str,
             };
             IntPtr _engineResult = InternalUnsafeMethods.Trim()(_args);
             return StringMarshal.IntPtrToUtf8String(_engineResult);
        }

        /// <description>
        /// Remove trailing whitespace from the string.
        /// </description>
        /// <param name="str">A string.</param>
        /// <returns>A string that is the same as<paramref name="" /> str but with any trailing (i.e. rightmost) whitespace removed.
        /// 
        /// </returns>
        /// <code>
        /// rtrim( "   string  " ); // Returns "   string".
        /// </code>
        /// <see cref="ltrim" />
        /// <see cref="trim" />
        public static string Rtrim(string str) {
             InternalUnsafeMethods.Rtrim__Args _args = new InternalUnsafeMethods.Rtrim__Args() {
                str = str,
             };
             IntPtr _engineResult = InternalUnsafeMethods.Rtrim()(_args);
             return StringMarshal.IntPtrToUtf8String(_engineResult);
        }

        /// <description>
        /// Remove leading whitespace from the string.
        /// </description>
        /// <param name="str">A string.</param>
        /// <returns>A string that is the same as<paramref name="" /> str but with any leading (i.e. leftmost) whitespace removed.
        /// 
        /// </returns>
        /// <code>
        /// ltrim( "   string  " ); // Returns "string  ".
        /// </code>
        /// <see cref="rtrim" />
        /// <see cref="trim" />
        public static string Ltrim(string str) {
             InternalUnsafeMethods.Ltrim__Args _args = new InternalUnsafeMethods.Ltrim__Args() {
                str = str,
             };
             IntPtr _engineResult = InternalUnsafeMethods.Ltrim()(_args);
             return StringMarshal.IntPtrToUtf8String(_engineResult);
        }

        /// <description>
        /// Find the start of<paramref name="" /> needle in 
        /// </description>
        /// <param name="haystack">The string to search.</param>
        /// <param name="needle">The string to search for.</param>
        /// <returns>The index at which the first occurrence of<paramref name="" /> needle was found in </returns>
        /// <code>
        /// strposr( "b ab", "b", 1 ) // Returns 2.
        /// </code>
        public static int Strposr(string haystack, string needle, int offset = 0) {
             InternalUnsafeMethods.Strposr__Args _args = new InternalUnsafeMethods.Strposr__Args() {
                haystack = haystack,
                needle = needle,
                offset = offset,
             };
             int _engineResult = InternalUnsafeMethods.Strposr()(_args);
             return _engineResult;
        }

        /// <description>
        /// Find the start of<paramref name="" /> needle in 
        /// </description>
        /// <param name="haystack">The string to search.</param>
        /// <param name="needle">The string to search for.</param>
        /// <returns>The index at which the first occurrence of<paramref name="" /> needle was found in </returns>
        /// <code>
        /// strpos( "b ab", "b", 1 ) // Returns 3.
        /// </code>
        public static int Strpos(string haystack, string needle, int offset = 0) {
             InternalUnsafeMethods.Strpos__Args _args = new InternalUnsafeMethods.Strpos__Args() {
                haystack = haystack,
                needle = needle,
                offset = offset,
             };
             int _engineResult = InternalUnsafeMethods.Strpos()(_args);
             return _engineResult;
        }

        /// <description>
        /// Find the start of<paramref name="" /> substring in the given 
        /// </description>
        /// <param name="string">The string to search.</param>
        /// <param name="substring">The string to search for.</param>
        /// <returns>The index into<paramref name="" /> string at which the first occurrence of </returns>
        /// <code>
        /// strstr( "abcd", "c" ) // Returns 2.
        /// </code>
        public static int Strstr(string _string, string substring) {
             InternalUnsafeMethods.Strstr__Args _args = new InternalUnsafeMethods.Strstr__Args() {
                _string = _string,
                substring = substring,
             };
             int _engineResult = InternalUnsafeMethods.Strstr()(_args);
             return _engineResult;
        }

        /// <description>
        /// Calculate the length of a string in characters, skipping everything between and including first and last.
        /// </description>
        /// <param name="str">A string.</param>
        /// <param name="first">First character to look for to skip block of text.</param>
        /// <param name="last">Second character to look for to skip block of text.</param>
        /// <returns>The length of the given string skipping blocks of text between characters.</returns>
        public static int Strlenskip(string str, string first, string last) {
             InternalUnsafeMethods.Strlenskip__Args _args = new InternalUnsafeMethods.Strlenskip__Args() {
                str = str,
                first = first,
                last = last,
             };
             int _engineResult = InternalUnsafeMethods.Strlenskip()(_args);
             return _engineResult;
        }

        /// <description>
        /// Get the length of the given string in bytes.
        /// </description>
        /// <remarks> This does <b>not</b> return a true character count for strings with multi-byte characters!
        /// </remarks>
        /// <param name="str">A string.</param>
        /// <returns>The length of the given string in bytes.</returns>
        public static int Strlen(string str) {
             InternalUnsafeMethods.Strlen__Args _args = new InternalUnsafeMethods.Strlen__Args() {
                str = str,
             };
             int _engineResult = InternalUnsafeMethods.Strlen()(_args);
             return _engineResult;
        }

        /// <description>
        /// Compares two strings using "natural order" case-<b>insensitive</b> comparison.
        /// Natural order means that rather than solely comparing single character code values, strings are ordered in a natural way.  For example, the string "hello10" is considered greater than the string "hello2" even though the first numeric character in "hello10" actually has a smaller character value than the corresponding character in "hello2".  However, since 10 is greater than 2, strnatcmp will put "hello10" after "hello2".
        /// </description>
        /// <param name="str1">The first string.</param>
        /// <param name="str2">The second string.</param>
        /// <returns>0 if the strings are equal, a value >0 if<paramref name="" /> str1 comes after </returns>
        /// <code>
        /// // Bubble sort 10 elements of %array using natural order
        /// do
        /// {
        ///    %swapped = false;
        ///    for( %i = 0; %i < 10 - 1; %i ++ )
        ///       if( strnatcmp( %array[ %i ], %array[ %i + 1 ] ) > 0 )
        ///       {
        ///          %temp = %array[ %i ];
        ///          %array[ %i ] = %array[ %i + 1 ];
        ///          %array[ %i + 1 ] = %temp;
        ///          %swapped = true;
        ///       }
        /// }
        /// while( %swapped );
        /// </code>
        /// <see cref="stricmp" />
        /// <see cref="strnatcmp" />
        public static int Strinatcmp(string str1, string str2) {
             InternalUnsafeMethods.Strinatcmp__Args _args = new InternalUnsafeMethods.Strinatcmp__Args() {
                str1 = str1,
                str2 = str2,
             };
             int _engineResult = InternalUnsafeMethods.Strinatcmp()(_args);
             return _engineResult;
        }

        /// <description>
        /// Compares two strings using "natural order" case-<b>sensitive</b> comparison.
        /// Natural order means that rather than solely comparing single character code values, strings are ordered in a natural way.  For example, the string "hello10" is considered greater than the string "hello2" even though the first numeric character in "hello10" actually has a smaller character value than the corresponding character in "hello2".  However, since 10 is greater than 2, strnatcmp will put "hello10" after "hello2".
        /// </description>
        /// <param name="str1">The first string.</param>
        /// <param name="str2">The second string.</param>
        /// <returns>0 if the strings are equal, a value >0 if<paramref name="" /> str1 comes after </returns>
        /// <code>
        /// // Bubble sort 10 elements of %array using natural order
        /// do
        /// {
        ///    %swapped = false;
        ///    for( %i = 0; %i < 10 - 1; %i ++ )
        ///       if( strnatcmp( %array[ %i ], %array[ %i + 1 ] ) > 0 )
        ///       {
        ///          %temp = %array[ %i ];
        ///          %array[ %i ] = %array[ %i + 1 ];
        ///          %array[ %i + 1 ] = %temp;
        ///          %swapped = true;
        ///       }
        /// }
        /// while( %swapped );
        /// </code>
        /// <see cref="strcmp" />
        /// <see cref="strinatcmp" />
        public static int Strnatcmp(string str1, string str2) {
             InternalUnsafeMethods.Strnatcmp__Args _args = new InternalUnsafeMethods.Strnatcmp__Args() {
                str1 = str1,
                str2 = str2,
             };
             int _engineResult = InternalUnsafeMethods.Strnatcmp()(_args);
             return _engineResult;
        }

        /// <description>
        /// Compares two strings using case-<b>insensitive</b> comparison.
        /// </description>
        /// <param name="str1">The first string.</param>
        /// <param name="str2">The second string.</param>
        /// <returns>0 if both strings are equal, a value <0 if the first character different in str1 has a smaller character code value than the character at the same position in str2, and a value >0 otherwise.</returns>
        /// <code>
        /// if( stricmp( "FOObar", "foobar" ) == 0 )
        ///    echo( "this is always true" );
        /// </code>
        /// <see cref="strcmp" />
        /// <see cref="strinatcmp" />
        public static int Stricmp(string str1, string str2) {
             InternalUnsafeMethods.Stricmp__Args _args = new InternalUnsafeMethods.Stricmp__Args() {
                str1 = str1,
                str2 = str2,
             };
             int _engineResult = InternalUnsafeMethods.Stricmp()(_args);
             return _engineResult;
        }

        /// <description>
        /// Compares two strings using case-<b>sensitive</b> comparison.
        /// </description>
        /// <param name="str1">The first string.</param>
        /// <param name="str2">The second string.</param>
        /// <returns>0 if both strings are equal, a value <0 if the first character different in str1 has a smaller character code value than the character at the same position in str2, and a value >1 otherwise.</returns>
        /// <code>
        /// if( strcmp( %var, "foobar" ) == 0 )
        ///    echo( "%var is equal to 'foobar'" );
        /// </code>
        /// <see cref="stricmp" />
        /// <see cref="strnatcmp" />
        public static int Strcmp(string str1, string str2) {
             InternalUnsafeMethods.Strcmp__Args _args = new InternalUnsafeMethods.Strcmp__Args() {
                str1 = str1,
                str2 = str2,
             };
             int _engineResult = InternalUnsafeMethods.Strcmp()(_args);
             return _engineResult;
        }

        /// <description>
        /// Format the given value as a string using printf-style formatting.
        /// </description>
        /// <param name="format">A printf-style format string.</param>
        /// <param name="value">The value argument matching the given format string.</param>
        /// <code>
        /// // Convert the given integer value to a string in a hex notation.
        /// %hex = strformat( "%x", %value );
        /// </code>
        /// <see href="http://en.wikipedia.org/wiki/Printf" />
        public static string Strformat(string format, string value) {
             InternalUnsafeMethods.Strformat__Args _args = new InternalUnsafeMethods.Strformat__Args() {
                format = format,
                value = value,
             };
             IntPtr _engineResult = InternalUnsafeMethods.Strformat()(_args);
             return StringMarshal.IntPtrToUtf8String(_engineResult);
        }

        /// <description>
        /// Return the integer character code value corresponding to the first character in the given string.
        /// </description>
        /// <param name="chr">a (one-character) string.</param>
        /// <returns>the UTF32 code value for the first character in the given string.</returns>
        public static int Strasc(string chr) {
             InternalUnsafeMethods.Strasc__Args _args = new InternalUnsafeMethods.Strasc__Args() {
                chr = chr,
             };
             int _engineResult = InternalUnsafeMethods.Strasc()(_args);
             return _engineResult;
        }

        /// <summary>Dumps all declared console functions to the console.</summary>
        /// <description>
        /// 
        /// </description>
        /// <param name="dumpScript">Optional parameter specifying whether or not functions defined in script should be dumped.</param>
        /// <param name="dumpEngine">Optional parameter specitying whether or not functions defined in the engine should be dumped.</param>
        public static void DumpConsoleFunctions(bool dumpScript = true, bool dumpEngine = true) {
             InternalUnsafeMethods.DumpConsoleFunctions__Args _args = new InternalUnsafeMethods.DumpConsoleFunctions__Args() {
                dumpScript = dumpScript,
                dumpEngine = dumpEngine,
             };
             InternalUnsafeMethods.DumpConsoleFunctions()(_args);
        }

        /// <summary>Dumps all declared console classes to the console.</summary>
        /// <description>
        /// 
        /// </description>
        /// <param name="dumpScript">Optional parameter specifying whether or not classes defined in script should be dumped.</param>
        /// <param name="dumpEngine">Optional parameter specifying whether or not classes defined in the engine should be dumped.</param>
        public static void DumpConsoleClasses(bool dumpScript = true, bool dumpEngine = true) {
             InternalUnsafeMethods.DumpConsoleClasses__Args _args = new InternalUnsafeMethods.DumpConsoleClasses__Args() {
                dumpScript = dumpScript,
                dumpEngine = dumpEngine,
             };
             InternalUnsafeMethods.DumpConsoleClasses()(_args);
        }

        /// <summary>Logs a warning message to the console.</summary>
        /// <description>
        /// 
        /// </description>
        /// <param name="message">The message text.</param>
        /// <remarks> By default, warnings will appear turquoise in the console.
        /// </remarks>
        public static void LogWarning(string message) {
             InternalUnsafeMethods.LogWarning__Args _args = new InternalUnsafeMethods.LogWarning__Args() {
                message = message,
             };
             InternalUnsafeMethods.LogWarning()(_args);
        }

        /// <summary>Logs an error message to the console.</summary>
        /// <description>
        /// 
        /// </description>
        /// <param name="message">The message text.</param>
        /// <remarks> By default, errors will appear red in the console.
        /// </remarks>
        public static void LogError(string message) {
             InternalUnsafeMethods.LogError__Args _args = new InternalUnsafeMethods.LogError__Args() {
                message = message,
             };
             InternalUnsafeMethods.LogError()(_args);
        }

        /// <summary>Logs a message to the console.</summary>
        /// <description>
        /// 
        /// </description>
        /// <param name="message">The message text.</param>
        /// <remarks> By default, messages will appear white in the console.
        /// </remarks>
        public static void Log(string message) {
             InternalUnsafeMethods.Log__Args _args = new InternalUnsafeMethods.Log__Args() {
                message = message,
             };
             InternalUnsafeMethods.Log()(_args);
        }

        /// <description>
        /// (string text)
        /// </description>
        /// <summary>Set the system clipboard.</summary>
        /// <description>
        /// 
        /// </description>
        public static bool SetClipboard(string text) {
             InternalUnsafeMethods.SetClipboard__Args _args = new InternalUnsafeMethods.SetClipboard__Args() {
                text = text,
             };
             bool _engineResult = InternalUnsafeMethods.SetClipboard()(_args);
             return _engineResult;
        }

        /// <description>
        /// ()
        /// </description>
        /// <summary>Get text from the clipboard.</summary>
        /// <description>
        /// 
        /// </description>
        public static string GetClipboard() {
             InternalUnsafeMethods.GetClipboard__Args _args = new InternalUnsafeMethods.GetClipboard__Args() {
             };
             IntPtr _engineResult = InternalUnsafeMethods.GetClipboard()(_args);
             return StringMarshal.IntPtrToUtf8String(_engineResult);
        }

        /// <description>
        /// ()
        /// </description>
        /// <summary>Clears the console output.</summary>
        /// <description>
        /// 
        /// </description>
        public static void Cls() {
             InternalUnsafeMethods.Cls__Args _args = new InternalUnsafeMethods.Cls__Args() {
             };
             InternalUnsafeMethods.Cls()(_args);
        }

        /// <description>
        /// Dump information about all current SFXSource instances to a string.
        /// The dump includes information about the playback status for each source, volume levels, virtualization, etc.
        /// </description>
        /// <param name="includeGroups">If true, direct instances of SFXSources (which represent logical sound groups) will be included. Otherwise only instances of subclasses of SFXSources are included in the dump.</param>
        /// <returns>A string containing a dump of information about all currently instantiated SFXSources.</returns>
        /// <see cref="SFXSource" />
        /// <see cref="sfxDumpSources" />
        public static string SfxDumpSourcesToString(bool includeGroups = false) {
             InternalUnsafeMethods.SfxDumpSourcesToString__Args _args = new InternalUnsafeMethods.SfxDumpSourcesToString__Args() {
                includeGroups = includeGroups,
             };
             IntPtr _engineResult = InternalUnsafeMethods.SfxDumpSourcesToString()(_args);
             return StringMarshal.IntPtrToUtf8String(_engineResult);
        }

        /// <description>
        /// Dump information about all current SFXSource instances to the console.
        /// The dump includes information about the playback status for each source, volume levels, virtualization, etc.
        /// </description>
        /// <param name="includeGroups">If true, direct instances of SFXSources (which represent logical sound groups) will be included. Otherwise only instances of subclasses of SFXSources are included in the dump.</param>
        /// <see cref="SFXSource" />
        /// <see cref="sfxDumpSourcesToString" />
        public static void SfxDumpSources(bool includeGroups = false) {
             InternalUnsafeMethods.SfxDumpSources__Args _args = new InternalUnsafeMethods.SfxDumpSources__Args() {
                includeGroups = includeGroups,
             };
             InternalUnsafeMethods.SfxDumpSources()(_args);
        }

        /// <description>
        /// Set the global scale factor to apply to volume attenuation of 3D sounds in the logarithmic model.
        /// </description>
        /// <param name="value">The new scale factor for logarithmic 3D sound falloff curves.</param>
        /// <remarks> This function has no effect if the currently distance model is set to SFXDistanceModel::Linear.
        /// 
        /// </remarks>
        /// <see cref="sfxGetDistanceModel" />
        /// <see cref="SFXDistanceModel" />
        public static void SfxSetRolloffFactor(float value) {
             InternalUnsafeMethods.SfxSetRolloffFactor__Args _args = new InternalUnsafeMethods.SfxSetRolloffFactor__Args() {
                value = value,
             };
             InternalUnsafeMethods.SfxSetRolloffFactor()(_args);
        }

        /// <description>
        /// Get the current global scale factor applied to volume attenuation of 3D sounds in the logarithmic model.
        /// </description>
        /// <returns>The current scale factor for logarithmic 3D sound falloff curves.</returns>
        /// <see cref="sfxGetDistanceModel" />
        /// <see cref="SFXDistanceModel" />
        public static float SfxGetRolloffFactor() {
             InternalUnsafeMethods.SfxGetRolloffFactor__Args _args = new InternalUnsafeMethods.SfxGetRolloffFactor__Args() {
             };
             float _engineResult = InternalUnsafeMethods.SfxGetRolloffFactor()(_args);
             return _engineResult;
        }

        /// <description>
        /// Set the global doppler effect scale factor.
        /// </description>
        /// <param name="value">The new doppler shift scale factor.</param>
        /// <see cref="sfxGetDopplerFactor" />
        public static void SfxSetDopplerFactor(float value) {
             InternalUnsafeMethods.SfxSetDopplerFactor__Args _args = new InternalUnsafeMethods.SfxSetDopplerFactor__Args() {
                value = value,
             };
             InternalUnsafeMethods.SfxSetDopplerFactor()(_args);
        }

        /// <description>
        /// Get the current global doppler effect setting.
        /// </description>
        /// <returns>The current global doppler effect scale factor (>=0).</returns>
        /// <see cref="sfxSetDopplerFactor" />
        public static float SfxGetDopplerFactor() {
             InternalUnsafeMethods.SfxGetDopplerFactor__Args _args = new InternalUnsafeMethods.SfxGetDopplerFactor__Args() {
             };
             float _engineResult = InternalUnsafeMethods.SfxGetDopplerFactor()(_args);
             return _engineResult;
        }

        /// <description>
        /// Set the falloff curve type to use for distance-based volume attenuation of 3D sounds.
        /// </description>
        /// <param name="model">The distance model to use for 3D sound.</param>
        /// <remarks> This setting takes effect globally and is applied to all 3D sounds.
        /// 
        /// </remarks>
        public static void SfxSetDistanceModel(SFXDistanceModel model) {
             InternalUnsafeMethods.SfxSetDistanceModel__Args _args = new InternalUnsafeMethods.SfxSetDistanceModel__Args() {
                model = (int)model,
             };
             InternalUnsafeMethods.SfxSetDistanceModel()(_args);
        }

        /// <description>
        /// Get the falloff curve type currently being applied to 3D sounds.
        /// </description>
        /// <returns>The current distance model type.</returns>
        public static SFXDistanceModel SfxGetDistanceModel() {
             InternalUnsafeMethods.SfxGetDistanceModel__Args _args = new InternalUnsafeMethods.SfxGetDistanceModel__Args() {
             };
             int _engineResult = InternalUnsafeMethods.SfxGetDistanceModel()(_args);
             return (SFXDistanceModel)_engineResult;
        }

        /// <description>
        /// Mark the given<paramref name="" /> source for deletion as soon as it moves into stopped state.
        /// 
        /// This function will retroactively turn the given 
        /// </description>
        /// <param name="source">A sound source.</param>
        public static void SfxDeleteWhenStopped(SFXSource source) {
             InternalUnsafeMethods.SfxDeleteWhenStopped__Args _args = new InternalUnsafeMethods.SfxDeleteWhenStopped__Args() {
                source = source.ObjectPtr,
             };
             InternalUnsafeMethods.SfxDeleteWhenStopped()(_args);
        }

        /// <description>
        /// Stop playback of the given<paramref name="" /> source (if it is not already stopped) and delete the 
        /// </description>
        /// <param name="source">A sound source.</param>
        public static void SfxStopAndDelete(SFXSource source) {
             InternalUnsafeMethods.SfxStopAndDelete__Args _args = new InternalUnsafeMethods.SfxStopAndDelete__Args() {
                source = source.ObjectPtr,
             };
             InternalUnsafeMethods.SfxStopAndDelete()(_args);
        }

        /// <description>
        /// Stop playback of the given<paramref name="" /> source.
        /// This is equivalent to calling SFXSource::stop().
        /// 
        /// 
        /// </description>
        /// <param name="source">The source to put into stopped state.</param>
        public static void SfxStop(SFXSource source) {
             InternalUnsafeMethods.SfxStop__Args _args = new InternalUnsafeMethods.SfxStop__Args() {
                source = source.ObjectPtr,
             };
             InternalUnsafeMethods.SfxStop()(_args);
        }

        /// <description>
        /// SFXSource sfxPlayOnce( ( SFXTrack track | SFXDescription description, string filename ) [, float x, float y, float z, float fadeInTime=-1 ] ) Create a new play-once source for the given profile or description+filename and start playback of the source.
        /// </description>
        public static int SfxPlayOnce(string sfxType, string arg0 = "", string arg1 = "", string arg2 = "", string arg3 = "", string arg4 = "-1.0f") {
             InternalUnsafeMethods.SfxPlayOnce__Args _args = new InternalUnsafeMethods.SfxPlayOnce__Args() {
                sfxType = sfxType,
                arg0 = arg0,
                arg1 = arg1,
                arg2 = arg2,
                arg3 = arg3,
                arg4 = arg4,
             };
             int _engineResult = InternalUnsafeMethods.SfxPlayOnce()(_args);
             return _engineResult;
        }

        /// <description>
        /// Start playing the given source or create a new source for the given track and play it.
        /// </description>
        public static int SfxPlay(string trackName, string pointOrX = "", string y = "", string z = "") {
             InternalUnsafeMethods.SfxPlay__Args _args = new InternalUnsafeMethods.SfxPlay__Args() {
                trackName = trackName,
                pointOrX = pointOrX,
                y = y,
                z = z,
             };
             int _engineResult = InternalUnsafeMethods.SfxPlay()(_args);
             return _engineResult;
        }

        /// <description>
        /// ( SFXTrack track | ( SFXDescription description, string filename ) [, float x, float y, float z ] ) Creates a new paused sound source using a profile or a description and filename.  The return value is the source which must be released by delete().
        /// </description>
        public static int SfxCreateSource(string sfxType, string arg0 = "", string arg1 = "", string arg2 = "", string arg3 = "") {
             InternalUnsafeMethods.SfxCreateSource__Args _args = new InternalUnsafeMethods.SfxCreateSource__Args() {
                sfxType = sfxType,
                arg0 = arg0,
                arg1 = arg1,
                arg2 = arg2,
                arg3 = arg3,
             };
             int _engineResult = InternalUnsafeMethods.SfxCreateSource()(_args);
             return _engineResult;
        }

        /// <description>
        /// Return information about the currently active sound device.
        /// The return value is a tab-delimited string of the following format:
        /// </description>
        /// <returns>A tab-separated list of properties of the currently active sound device or the empty string if no sound device has been initialized.</returns>
        /// <see cref="sfxCreateDevice" />
        /// <see cref="sfxGetAvailableDevices" />
        /// <see cref="$SFX::DEVICE_INFO_PROVIDER" />
        /// <see cref="$SFX::DEVICE_INFO_NAME" />
        /// <see cref="$SFX::DEVICE_INFO_USEHARDWARE" />
        /// <see cref="$SFX::DEVICE_INFO_MAXBUFFERS" />
        /// <see cref="$SFX::DEVICE_INFO_CAPS" />
        /// <see cref="$SFX::DEVICE_CAPS_REVERB" />
        /// <see cref="$SFX::DEVICE_CAPS_VOICEMANAGEMENT" />
        /// <see cref="$SFX::DEVICE_CAPS_OCCLUSION" />
        /// <see cref="$SFX::DEVICE_CAPS_DSPEFFECTS" />
        /// <see cref="$SFX::DEVICE_CAPS_MULTILISTENER" />
        /// <see cref="$SFX::DEVICE_CAPS_FMODDESIGNER" />
        public static string SfxGetDeviceInfo() {
             InternalUnsafeMethods.SfxGetDeviceInfo__Args _args = new InternalUnsafeMethods.SfxGetDeviceInfo__Args() {
             };
             IntPtr _engineResult = InternalUnsafeMethods.SfxGetDeviceInfo()(_args);
             return StringMarshal.IntPtrToUtf8String(_engineResult);
        }

        /// <description>
        /// Delete the currently active sound device and release all its resources.
        /// SFXSources that are still playing will be transitioned to virtualized playback mode. When creating a new device, they will automatically transition back to normal playback.
        /// 
        /// In the core scripts, this is done automatically for you during shutdown in the sfxShutdown() function.
        /// </description>
        /// <see cref="sfxCreateDevice" />
        public static void SfxDeleteDevice() {
             InternalUnsafeMethods.SfxDeleteDevice__Args _args = new InternalUnsafeMethods.SfxDeleteDevice__Args() {
             };
             InternalUnsafeMethods.SfxDeleteDevice()(_args);
        }

        /// <description>
        /// Try to create a new sound device using the given properties.
        /// If a sound device is currently initialized, it will be uninitialized first.  However, be aware that in this case, if this function fails, it will not restore the previously active device but rather leave the sound system in an uninitialized state.
        /// 
        /// Sounds that are already playing while the new device is created will be temporarily transitioned to virtualized playback and then resume normal playback once the device has been created.
        /// 
        /// In the core scripts, sound is automatically set up during startup in the sfxStartup() function.
        /// </description>
        /// <param name="provider">The name of the device provider as returned by sfxGetAvailableDevices().</param>
        /// <param name="device">The name of the device as returned by sfxGetAvailableDevices().</param>
        /// <param name="useHardware">Whether to enabled hardware mixing on the device or not.  Only relevant if supported by the given device.</param>
        /// <param name="maxBuffers">The maximum number of concurrent voices for this device to use or -1 for the device to pick its own reasonable default.</param>
        /// <returns>True if the initialization was successful, false if not.</returns>
        /// <remarks> This function must be called before any of the sound playback functions can be used.
        /// </remarks>
        /// <see cref="sfxGetAvailableDevices" />
        /// <see cref="sfxGetDeviceInfo" />
        /// <see cref="sfxDeleteDevice" />
        public static bool SfxCreateDevice(string provider, string device, bool useHardware, int maxBuffers) {
             InternalUnsafeMethods.SfxCreateDevice__Args _args = new InternalUnsafeMethods.SfxCreateDevice__Args() {
                provider = provider,
                device = device,
                useHardware = useHardware,
                maxBuffers = maxBuffers,
             };
             bool _engineResult = InternalUnsafeMethods.SfxCreateDevice()(_args);
             return _engineResult;
        }

        /// <description>
        /// Get a list of all available sound devices.
        /// The return value will be a newline-separated list of entries where each line describes one available sound device.  Each such line will have the following format:
        /// </description>
        /// <returns>A newline-separated list of information about all available sound devices.</returns>
        /// <see cref="sfxCreateDevice" />
        /// <see cref="sfxGetDeviceInfo" />
        /// <see cref="$SFX::DEVICE_INFO_PROVIDER" />
        /// <see cref="$SFX::DEVICE_INFO_NAME" />
        /// <see cref="$SFX::DEVICE_INFO_USEHARDWARE" />
        /// <see cref="$SFX::DEVICE_INFO_MAXBUFFERS" />
        public static string SfxGetAvailableDevices() {
             InternalUnsafeMethods.SfxGetAvailableDevices__Args _args = new InternalUnsafeMethods.SfxGetAvailableDevices__Args() {
             };
             IntPtr _engineResult = InternalUnsafeMethods.SfxGetAvailableDevices()(_args);
             return StringMarshal.IntPtrToUtf8String(_engineResult);
        }

        /// <description>
        /// Return a newline-separated list of all active states.
        /// </description>
        /// <returns>A list of the form</returns>
        /// <code>
        /// // Disable all active states.
        /// foreach$( %state in sfxGetActiveStates() )
        ///    %state.disable();
        /// </code>
        public static string SfxGetActiveStates() {
             InternalUnsafeMethods.SfxGetActiveStates__Args _args = new InternalUnsafeMethods.SfxGetActiveStates__Args() {
             };
             IntPtr _engineResult = InternalUnsafeMethods.SfxGetActiveStates()(_args);
             return StringMarshal.IntPtrToUtf8String(_engineResult);
        }

        /// <description>
        /// Get the type of build, "Debug" or "Release".
        /// </description>
        public static string GetBuildString() {
             InternalUnsafeMethods.GetBuildString__Args _args = new InternalUnsafeMethods.GetBuildString__Args() {
             };
             IntPtr _engineResult = InternalUnsafeMethods.GetBuildString()(_args);
             return StringMarshal.IntPtrToUtf8String(_engineResult);
        }

        /// <description>
        /// Get the time of compilation.
        /// </description>
        public static string GetCompileTimeString() {
             InternalUnsafeMethods.GetCompileTimeString__Args _args = new InternalUnsafeMethods.GetCompileTimeString__Args() {
             };
             IntPtr _engineResult = InternalUnsafeMethods.GetCompileTimeString()(_args);
             return StringMarshal.IntPtrToUtf8String(_engineResult);
        }

        /// <description>
        /// Get the name of the engine product that this is running from, as a string.
        /// </description>
        public static string GetEngineName() {
             InternalUnsafeMethods.GetEngineName__Args _args = new InternalUnsafeMethods.GetEngineName__Args() {
             };
             IntPtr _engineResult = InternalUnsafeMethods.GetEngineName()(_args);
             return StringMarshal.IntPtrToUtf8String(_engineResult);
        }

        /// <description>
        /// Get the version of the aplication build, as a human readable string.
        /// </description>
        public static string GetAppVersionString() {
             InternalUnsafeMethods.GetAppVersionString__Args _args = new InternalUnsafeMethods.GetAppVersionString__Args() {
             };
             IntPtr _engineResult = InternalUnsafeMethods.GetAppVersionString()(_args);
             return StringMarshal.IntPtrToUtf8String(_engineResult);
        }

        /// <description>
        /// Get the version of the engine build, as a human readable string.
        /// </description>
        public static string GetVersionString() {
             InternalUnsafeMethods.GetVersionString__Args _args = new InternalUnsafeMethods.GetVersionString__Args() {
             };
             IntPtr _engineResult = InternalUnsafeMethods.GetVersionString()(_args);
             return StringMarshal.IntPtrToUtf8String(_engineResult);
        }

        /// <description>
        /// Get the version of the application build, as a string.
        /// </description>
        public static int GetAppVersionNumber() {
             InternalUnsafeMethods.GetAppVersionNumber__Args _args = new InternalUnsafeMethods.GetAppVersionNumber__Args() {
             };
             int _engineResult = InternalUnsafeMethods.GetAppVersionNumber()(_args);
             return _engineResult;
        }

        /// <description>
        /// Get the version of the engine build, as a string.
        /// </description>
        public static int GetVersionNumber() {
             InternalUnsafeMethods.GetVersionNumber__Args _args = new InternalUnsafeMethods.GetVersionNumber__Args() {
             };
             int _engineResult = InternalUnsafeMethods.GetVersionNumber()(_args);
             return _engineResult;
        }

        /// <description>
        /// setServerInfo(index);
        /// </description>
        public static bool SetServerInfo(uint index) {
             InternalUnsafeMethods.SetServerInfo__Args _args = new InternalUnsafeMethods.SetServerInfo__Args() {
                index = index,
             };
             bool _engineResult = InternalUnsafeMethods.SetServerInfo()(_args);
             return _engineResult;
        }

        /// <description>
        /// getServerCount();
        /// </description>
        public static int GetServerCount() {
             InternalUnsafeMethods.GetServerCount__Args _args = new InternalUnsafeMethods.GetServerCount__Args() {
             };
             int _engineResult = InternalUnsafeMethods.GetServerCount()(_args);
             return _engineResult;
        }

        /// <description>
        /// stopHeartbeat();
        /// </description>
        public static void StopHeartbeat() {
             InternalUnsafeMethods.StopHeartbeat__Args _args = new InternalUnsafeMethods.StopHeartbeat__Args() {
             };
             InternalUnsafeMethods.StopHeartbeat()(_args);
        }

        /// <description>
        /// startHeartbeat();
        /// </description>
        public static void StartHeartbeat() {
             InternalUnsafeMethods.StartHeartbeat__Args _args = new InternalUnsafeMethods.StartHeartbeat__Args() {
             };
             InternalUnsafeMethods.StartHeartbeat()(_args);
        }

        /// <description>
        /// stopServerQuery();
        /// </description>
        public static void StopServerQuery() {
             InternalUnsafeMethods.StopServerQuery__Args _args = new InternalUnsafeMethods.StopServerQuery__Args() {
             };
             InternalUnsafeMethods.StopServerQuery()(_args);
        }

        /// <description>
        /// cancelServerQuery();
        /// </description>
        public static void CancelServerQuery() {
             InternalUnsafeMethods.CancelServerQuery__Args _args = new InternalUnsafeMethods.CancelServerQuery__Args() {
             };
             InternalUnsafeMethods.CancelServerQuery()(_args);
        }

        /// <description>
        /// querySingleServer(address, flags);
        /// </description>
        public static void QuerySingleServer(string addrText, byte flags = 0) {
             InternalUnsafeMethods.QuerySingleServer__Args _args = new InternalUnsafeMethods.QuerySingleServer__Args() {
                addrText = addrText,
                flags = flags,
             };
             InternalUnsafeMethods.QuerySingleServer()(_args);
        }

        /// <description>
        /// queryMasterServer(...);
        /// </description>
        public static void QueryMasterServer(uint flags, string gameType, string missionType, uint minPlayers, uint maxPlayers, uint maxBots, uint regionMask, uint maxPing, uint minCPU, uint filterFlags) {
             InternalUnsafeMethods.QueryMasterServer__Args _args = new InternalUnsafeMethods.QueryMasterServer__Args() {
                flags = flags,
                gameType = gameType,
                missionType = missionType,
                minPlayers = minPlayers,
                maxPlayers = maxPlayers,
                maxBots = maxBots,
                regionMask = regionMask,
                maxPing = maxPing,
                minCPU = minCPU,
                filterFlags = filterFlags,
             };
             InternalUnsafeMethods.QueryMasterServer()(_args);
        }

        /// <description>
        /// queryLanServers(...);
        /// </description>
        public static void QueryLanServers(uint lanPort, uint flags, string gameType, string missionType, uint minPlayers, uint maxPlayers, uint maxBots, uint regionMask, uint maxPing, uint minCPU, uint filterFlags) {
             InternalUnsafeMethods.QueryLanServers__Args _args = new InternalUnsafeMethods.QueryLanServers__Args() {
                lanPort = lanPort,
                flags = flags,
                gameType = gameType,
                missionType = missionType,
                minPlayers = minPlayers,
                maxPlayers = maxPlayers,
                maxBots = maxBots,
                regionMask = regionMask,
                maxPing = maxPing,
                minCPU = minCPU,
                filterFlags = filterFlags,
             };
             InternalUnsafeMethods.QueryLanServers()(_args);
        }

        /// <description>
        /// queryAllServers(...);
        /// </description>
        public static void QueryAllServers(uint lanPort, uint flags, string gameType, string missionType, uint minPlayers, uint maxPlayers, uint maxBots, uint regionMask, uint maxPing, uint minCPU, uint filterFlags) {
             InternalUnsafeMethods.QueryAllServers__Args _args = new InternalUnsafeMethods.QueryAllServers__Args() {
                lanPort = lanPort,
                flags = flags,
                gameType = gameType,
                missionType = missionType,
                minPlayers = minPlayers,
                maxPlayers = maxPlayers,
                maxBots = maxBots,
                regionMask = regionMask,
                maxPing = maxPing,
                minCPU = minCPU,
                filterFlags = filterFlags,
             };
             InternalUnsafeMethods.QueryAllServers()(_args);
        }

        /// <description>
        /// (string format, ...)
        /// </description>
        /// <summary>Build a string using the specified tagged string format.</summary>
        /// <description>
        /// This function takes an already tagged string (passed in as a tagged string ID) and one or more additional strings.  If the tagged string contains argument tags that range from %%1 through %%9, then each additional string will be substituted into the tagged string.  The final (non-tagged) combined string will be returned.  The maximum length of the tagged string plus any inserted additional strings is 511 characters.
        /// </description>
        /// <param name="format">A tagged string ID that contains zero or more argument tags, in the form of %%1 through %%9.</param>
        /// <param name="...">A variable number of arguments that are insterted into the tagged string based on the argument tags within the format string.</param>
        /// <returns>An ordinary string that is a combination of the original tagged string with any additional strings passed in inserted in place of each argument tag.</returns>
        /// <code>
        /// // Create a tagged string with argument tags
        /// %taggedStringID = addTaggedString("Welcome %1 to the game!");
        /// 
        /// // Some point later, combine the tagged string with some other string
        /// %string = buildTaggedString(%taggedStringID, %playerName);
        /// echo(%string);
        /// </code>
        /// <see cref="\ref syntaxDataTypes under Tagged %Strings" />
        /// <see cref="addTaggedString()" />
        /// <see cref="getTaggedString()" />
        public static string BuildTaggedString(params string[] args) { 
            List<string> _argList = new List<string>() {""};
            _argList.AddRange(args);

            StringVector nativeVecArgs = new StringVector {
                ElementCount = (uint)_argList.Count,
                Array = _argList.ToArray(),
                ArraySize = (uint)_argList.Count
            };
            nativeVecArgs.Alloc();
            IntPtr _engineResult = InternalUnsafeMethods.BuildTaggedString()(ref nativeVecArgs.internalStruct);
            nativeVecArgs.Free();

            return StringMarshal.IntPtrToUtf8String(_engineResult);
        }

        /// <summary>Use the getTaggedString function to convert a tag to a string.</summary>
        /// <description>
        /// This is not the same as detag() which can only be used within the context of a function that receives a tag. This function can be used any time and anywhere to convert a tag to a string.
        /// </description>
        /// <param name="tag">A numeric tag ID.</param>
        /// <returns>The string as found in the Net String table.</returns>
        /// <see cref="\ref syntaxDataTypes under Tagged %Strings" />
        /// <see cref="addTaggedString()" />
        /// <see cref="removeTaggedString()" />
        public static string GetTaggedString(string tag = "") {
             InternalUnsafeMethods.GetTaggedString__Args _args = new InternalUnsafeMethods.GetTaggedString__Args() {
                tag = tag,
             };
             IntPtr _engineResult = InternalUnsafeMethods.GetTaggedString()(_args);
             return StringMarshal.IntPtrToUtf8String(_engineResult);
        }

        /// <summary>Use the addTaggedString function to tag a new string and add it to the NetStringTable</summary>
        /// <description>
        /// 
        /// </description>
        /// <param name="str">The string to be tagged and placed in the NetStringTable. Tagging ignores case, so tagging the same string (excluding case differences) will be ignored as a duplicated tag.</param>
        /// <returns>Returns a string( containing a numeric value) equivalent to the string ID for the newly tagged string</returns>
        /// <see cref="\ref syntaxDataTypes under Tagged %Strings" />
        /// <see cref="removeTaggedString()" />
        /// <see cref="getTaggedString()" />
        public static string AddTaggedString(string str = "") {
             InternalUnsafeMethods.AddTaggedString__Args _args = new InternalUnsafeMethods.AddTaggedString__Args() {
                str = str,
             };
             IntPtr _engineResult = InternalUnsafeMethods.AddTaggedString()(_args);
             return StringMarshal.IntPtrToUtf8String(_engineResult);
        }

        /// <summary>Remove a tagged string from the Net String Table</summary>
        /// <description>
        /// 
        /// </description>
        /// <param name="tag">The tag associated with the string</param>
        /// <see cref="\ref syntaxDataTypes under Tagged %Strings" />
        /// <see cref="addTaggedString()" />
        /// <see cref="getTaggedString()" />
        public static void RemoveTaggedString(int tag = -1) {
             InternalUnsafeMethods.RemoveTaggedString__Args _args = new InternalUnsafeMethods.RemoveTaggedString__Args() {
                tag = tag,
             };
             InternalUnsafeMethods.RemoveTaggedString()(_args);
        }

        /// <description>
        /// (NetConnection client, string func, ...)
        /// </description>
        /// <summary>Send a command from the server to the client</summary>
        /// <description>
        /// 
        /// </description>
        /// <param name="client">The numeric ID of a client GameConnection</param>
        /// <param name="func">Name of the client function being called</param>
        /// <param name="...">Various parameters being passed to client command</param>
        /// <code>
        /// // Set up the client command.  Needs to be executed on the client, such as
        /// // within scripts/client/client.cs
        /// // Update the Ammo Counter with current ammo, if not any then hide the counter.
        /// function clientCmdSetAmmoAmountHud(%amount)
        /// {
        ///    if (!%amount)
        /// 	  AmmoAmount.setVisible(false);
        ///    else
        ///    {
        /// 	  AmmoAmount.setVisible(true);
        /// 	  AmmoAmount.setText("Ammo: "
        /// </code>
        public static void CommandToClient(params string[] args) { 
            List<string> _argList = new List<string>() {""};
            _argList.AddRange(args);

            StringVector nativeVecArgs = new StringVector {
                ElementCount = (uint)_argList.Count,
                Array = _argList.ToArray(),
                ArraySize = (uint)_argList.Count
            };
            nativeVecArgs.Alloc();
            InternalUnsafeMethods.CommandToClient()(ref nativeVecArgs.internalStruct);
            nativeVecArgs.Free();

        }

        /// <description>
        /// (string func, ...)
        /// </description>
        /// <summary>Send a command to the server.</summary>
        /// <description>
        /// 
        /// </description>
        /// <param name="func">Name of the server command being called</param>
        /// <param name="...">Various parameters being passed to server command</param>
        /// <code>
        /// // Create a standard function.  Needs to be executed on the client, such 
        /// // as within scripts/client/default.bind.cs
        /// function toggleCamera(%val)
        /// {
        /// 	// If key was down, call a server command named 'ToggleCamera'
        /// 	if (%val)
        /// 		commandToServer('ToggleCamera');
        /// }
        /// 
        /// // Server command being called from above.  Needs to be executed on the 
        /// // server, such as within scripts/server/commands.cs
        /// function serverCmdToggleCamera(%client)
        /// {
        ///    if (%client.getControlObject() == %client.player)
        ///    {
        /// 	  %client.camera.setVelocity("0 0 0");
        /// 	  %control = %client.camera;
        ///    }
        ///    else
        ///    {
        /// 	  %client.player.setVelocity("0 0 0");
        /// 	  %control = %client.player;
        ///   }
        ///    %client.setControlObject(%control);
        ///    clientCmdSyncEditorGui();
        /// }
        /// </code>
        public static void CommandToServer(params string[] args) { 
            List<string> _argList = new List<string>() {""};
            _argList.AddRange(args);

            StringVector nativeVecArgs = new StringVector {
                ElementCount = (uint)_argList.Count,
                Array = _argList.ToArray(),
                ArraySize = (uint)_argList.Count
            };
            nativeVecArgs.Alloc();
            InternalUnsafeMethods.CommandToServer()(ref nativeVecArgs.internalStruct);
            nativeVecArgs.Free();

        }

        /// <summary>Return the current local time as: weekday month day year hour min sec.</summary>
        /// <description>
        /// Local time is platform defined.
        /// </description>
        public static string GetLocalTime() {
             InternalUnsafeMethods.GetLocalTime__Args _args = new InternalUnsafeMethods.GetLocalTime__Args() {
             };
             IntPtr _engineResult = InternalUnsafeMethods.GetLocalTime()(_args);
             return StringMarshal.IntPtrToUtf8String(_engineResult);
        }

        /// <description>
        /// ()
        /// </description>
        /// <summary>Return the current real time in milliseconds.</summary>
        /// <description>
        /// Real time is platform defined; typically time since the computer booted.
        /// </description>
        public static int GetRealTime() {
             InternalUnsafeMethods.GetRealTime__Args _args = new InternalUnsafeMethods.GetRealTime__Args() {
             };
             int _engineResult = InternalUnsafeMethods.GetRealTime()(_args);
             return _engineResult;
        }

        /// <description>
        /// ()Return the current sim time in milliseconds.
        /// </description>
        /// <summary>Sim time is time since the game started.</summary>
        /// <description>
        /// 
        /// </description>
        public static int GetSimTime() {
             InternalUnsafeMethods.GetSimTime__Args _args = new InternalUnsafeMethods.GetSimTime__Args() {
             };
             int _engineResult = InternalUnsafeMethods.GetSimTime()(_args);
             return _engineResult;
        }

        /// <description>
        /// (string filename)
        /// </description>
        /// <summary>Begin playback of a journal from a specified field.</summary>
        /// <description>
        /// 
        /// </description>
        /// <param name="filename">Name and path of file journal file</param>
        public static void PlayJournal(string filename) {
             InternalUnsafeMethods.PlayJournal__Args _args = new InternalUnsafeMethods.PlayJournal__Args() {
                filename = filename,
             };
             InternalUnsafeMethods.PlayJournal()(_args);
        }

        /// <description>
        /// (string filename)Save the journal to the specified file.
        /// </description>
        public static void SaveJournal(string filename) {
             InternalUnsafeMethods.SaveJournal__Args _args = new InternalUnsafeMethods.SaveJournal__Args() {
                filename = filename,
             };
             InternalUnsafeMethods.SaveJournal()(_args);
        }

        /// <description>
        /// ()
        /// </description>
        /// <summary>Closes the current network port</summary>
        /// <description>
        /// 
        /// </description>
        public static void CloseNetPort() {
             InternalUnsafeMethods.CloseNetPort__Args _args = new InternalUnsafeMethods.CloseNetPort__Args() {
             };
             InternalUnsafeMethods.CloseNetPort()(_args);
        }

        /// <description>
        /// (protocol id)
        /// </description>
        /// <summary>Determines if a specified address type can be reached.</summary>
        /// <description>
        /// 
        /// </description>
        public static bool IsAddressTypeAvailable(int addressType) {
             InternalUnsafeMethods.IsAddressTypeAvailable__Args _args = new InternalUnsafeMethods.IsAddressTypeAvailable__Args() {
                addressType = addressType,
             };
             bool _engineResult = InternalUnsafeMethods.IsAddressTypeAvailable()(_args);
             return _engineResult;
        }

        /// <description>
        /// (int port, bool bind=true)
        /// </description>
        /// <summary>Set the network port for the game to use.</summary>
        /// <description>
        /// 
        /// </description>
        /// <param name="port">The port to use.</param>
        /// <param name="bind">True if bind() should be called on the port.</param>
        /// <returns>True if the port was successfully opened.
        /// This will trigger a windows firewall prompt.  If you don't have firewall tunneling tech you can set this to false to avoid the prompt.</returns>
        public static bool SetNetPort(int port, bool bind = true) {
             InternalUnsafeMethods.SetNetPort__Args _args = new InternalUnsafeMethods.SetNetPort__Args() {
                port = port,
                bind = bind,
             };
             bool _engineResult = InternalUnsafeMethods.SetNetPort()(_args);
             return _engineResult;
        }

        /// <description>
        /// (bool isLocked)
        /// </description>
        /// <summary>Lock or unlock the mouse to the window.</summary>
        /// <description>
        /// When true, prevents the mouse from leaving the bounds of the game window.
        /// </description>
        public static void LockMouse(bool isLocked) {
             InternalUnsafeMethods.LockMouse__Args _args = new InternalUnsafeMethods.LockMouse__Args() {
                isLocked = isLocked,
             };
             InternalUnsafeMethods.LockMouse()(_args);
        }

        /// <description>
        /// strToPlayerName(string);
        /// </description>
        public static string StrToPlayerName(string ptr) {
             InternalUnsafeMethods.StrToPlayerName__Args _args = new InternalUnsafeMethods.StrToPlayerName__Args() {
                ptr = ptr,
             };
             IntPtr _engineResult = InternalUnsafeMethods.StrToPlayerName()(_args);
             return StringMarshal.IntPtrToUtf8String(_engineResult);
        }

        /// <description>
        /// ()
        /// </description>
        /// <summary>Activates DirectInput.</summary>
        /// <description>
        /// Also activates any connected joysticks.
        /// </description>
        public static void ActivateDirectInput() {
             InternalUnsafeMethods.ActivateDirectInput__Args _args = new InternalUnsafeMethods.ActivateDirectInput__Args() {
             };
             InternalUnsafeMethods.ActivateDirectInput()(_args);
        }

        /// <description>
        /// ()
        /// </description>
        /// <summary>Disables DirectInput.</summary>
        /// <description>
        /// Also deactivates any connected joysticks.
        /// </description>
        public static void DeactivateDirectInput() {
             InternalUnsafeMethods.DeactivateDirectInput__Args _args = new InternalUnsafeMethods.DeactivateDirectInput__Args() {
             };
             InternalUnsafeMethods.DeactivateDirectInput()(_args);
        }

        /// <summary>Checks to see if text is a bad word</summary>
        /// <description>
        /// The text is considered to be a bad word if it has been added to the bad word filter.
        /// </description>
        /// <param name="text">Text to scan for bad words</param>
        /// <returns>True if the text has bad word(s), false if it is clean</returns>
        /// <see cref="addBadWord()" />
        /// <see cref="filterString()" />
        /// <code>
        /// // In this game, "Foobar" is banned
        /// %badWord = "Foobar";
        /// 
        /// // Add a banned word to the bad word filter
        /// addBadWord(%badWord);
        /// 
        /// // Create the base string, can come from anywhere like user chat
        /// %userText = "Foobar";
        /// 
        /// // Create a string of random letters
        /// %replacementChars = "knqwrtlzs";
        /// 
        /// // If the text contains a bad word, filter it before printing
        /// // Otherwise print the original text
        /// if(containsBadWords(%userText))
        /// {
        ///   // Filter the string
        ///   %filteredText = filterString(%userText, %replacementChars);
        /// 
        ///   // Print filtered text
        ///   echo(%filteredText);
        /// }
        /// else
        ///   echo(%userText);
        /// </code>
        public static bool ContainsBadWords(string text) {
             InternalUnsafeMethods.ContainsBadWords__Args _args = new InternalUnsafeMethods.ContainsBadWords__Args() {
                text = text,
             };
             bool _engineResult = InternalUnsafeMethods.ContainsBadWords()(_args);
             return _engineResult;
        }

        /// <summary>Replaces the characters in a string with designated text</summary>
        /// <description>
        /// Uses the bad word filter to determine which characters within the string will be replaced.
        /// </description>
        /// <param name="baseString">The original string to filter.</param>
        /// <param name="replacementChars">A string containing letters you wish to swap in the baseString.</param>
        /// <returns>The new scrambled string</returns>
        /// <see cref="addBadWord()" />
        /// <see cref="containsBadWords()" />
        /// <code>
        /// // Create the base string, can come from anywhere
        /// %baseString = "Foobar";
        /// 
        /// // Create a string of random letters
        /// %replacementChars = "knqwrtlzs";
        /// 
        /// // Filter the string
        /// %newString = filterString(%baseString, %replacementChars);
        /// 
        /// // Print the new string to console
        /// echo(%newString);
        /// </code>
        public static string FilterString(string baseString = "", string replacementChars = "") {
             InternalUnsafeMethods.FilterString__Args _args = new InternalUnsafeMethods.FilterString__Args() {
                baseString = baseString,
                replacementChars = replacementChars,
             };
             IntPtr _engineResult = InternalUnsafeMethods.FilterString()(_args);
             return StringMarshal.IntPtrToUtf8String(_engineResult);
        }

        /// <summary>Add a string to the bad word filter</summary>
        /// <description>
        /// The bad word filter is a table containing words which will not be displayed in chat windows. Instead, a designated replacement string will be displayed.  There are already a number of bad words automatically defined.
        /// </description>
        /// <param name="badWord">Exact text of the word to restrict.</param>
        /// <returns>True if word was successfully added, false if the word or a subset of it already exists in the table</returns>
        /// <see cref="filterString()" />
        /// <code>
        /// // In this game, "Foobar" is banned
        /// %badWord = "Foobar";
        /// 
        /// // Returns true, word was successfully added
        /// addBadWord(%badWord);
        /// 
        /// // Returns false, word has already been added
        /// addBadWord("Foobar");
        /// </code>
        public static bool AddBadWord(string badWord) {
             InternalUnsafeMethods.AddBadWord__Args _args = new InternalUnsafeMethods.AddBadWord__Args() {
                badWord = badWord,
             };
             bool _engineResult = InternalUnsafeMethods.AddBadWord()(_args);
             return _engineResult;
        }

    }
}