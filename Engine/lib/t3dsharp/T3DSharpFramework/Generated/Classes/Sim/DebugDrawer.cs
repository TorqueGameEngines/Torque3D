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
    /// <summary>A debug helper for rendering debug primitives to the scene.</summary>
    /// <description>
    /// The DebugDrawer is used to render debug primitives to the scene for testing.  It is often useful when debugging collision code or complex 3d algorithms to have them draw debug information, like culling hulls or bounding volumes, normals, simple lines, and so forth.
    /// 
    /// A key feature of the DebugDrawer is that each primitive gets a "time to live" (TTL) which allows them to continue to render to the scene for a fixed period of time.  You can freeze or resume the system at any time to allow you to examine the output.
    /// </description>
    /// <code>
    /// DebugDraw.drawLine( %player.getMuzzlePoint( 0 ), %hitPoint );
    /// DebugDraw.setLastTTL( 5000 ); // 5 seconds.
    /// </code>
    /// <remarks> This feature can easily be used to cheat in online games, so you should be sure it is disabled in your shipping game.  By default the DebugDrawer is disabled in all TORQUE_SHIPPING builds.
    /// </remarks>
    public unsafe class DebugDrawer : SimObject {
        public DebugDrawer(bool pRegister = false) 
            : base(pRegister) {
        }
        
        public DebugDrawer(string pName, bool pRegister) 
            : this(false) {
            Name = pName;
            if (pRegister) {
                RegisterObject();
            }
        }
        
        public DebugDrawer(string pName) 
            : this(pName, false) {
        }
        
        public DebugDrawer(string pName, string pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(Engine.Sim.FindObject<SimObject>(pParent));
        }
        
        public DebugDrawer(string pName, SimObject pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(pParent);
        }
        
        public DebugDrawer(SimObject pObj) 
            : base(pObj) {
        }
        
        public DebugDrawer(IntPtr pObj) 
            : base(pObj) {
        }
        
		protected override void CreateObjectPtr()
		{
			ObjectPtr = InternalUnsafeMethods.Create()(new InternalUnsafeMethods.Create__Args());
		}

        #region UnsafeNativeMethods
        new internal struct InternalUnsafeMethods {
            [StructLayout(LayoutKind.Sequential)]
            internal struct ToggleDrawing__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _ToggleDrawing(IntPtr _this, ToggleDrawing__Args args);
            private static _ToggleDrawing _ToggleDrawingFunc;
            internal static _ToggleDrawing ToggleDrawing() {
                if (_ToggleDrawingFunc == null) {
                    _ToggleDrawingFunc =
                        (_ToggleDrawing)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnDebugDrawer_toggleDrawing"), typeof(_ToggleDrawing));
                }
                
                return _ToggleDrawingFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct ToggleFreeze__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _ToggleFreeze(IntPtr _this, ToggleFreeze__Args args);
            private static _ToggleFreeze _ToggleFreezeFunc;
            internal static _ToggleFreeze ToggleFreeze() {
                if (_ToggleFreezeFunc == null) {
                    _ToggleFreezeFunc =
                        (_ToggleFreeze)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnDebugDrawer_toggleFreeze"), typeof(_ToggleFreeze));
                }
                
                return _ToggleFreezeFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct SetLastZTest__Args
            {
                [MarshalAs(UnmanagedType.I1)]
                internal bool enabled;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _SetLastZTest(IntPtr _this, SetLastZTest__Args args);
            private static _SetLastZTest _SetLastZTestFunc;
            internal static _SetLastZTest SetLastZTest() {
                if (_SetLastZTestFunc == null) {
                    _SetLastZTestFunc =
                        (_SetLastZTest)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnDebugDrawer_setLastZTest"), typeof(_SetLastZTest));
                }
                
                return _SetLastZTestFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct SetLastTTL__Args
            {
                internal uint ms;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _SetLastTTL(IntPtr _this, SetLastTTL__Args args);
            private static _SetLastTTL _SetLastTTLFunc;
            internal static _SetLastTTL SetLastTTL() {
                if (_SetLastTTLFunc == null) {
                    _SetLastTTLFunc =
                        (_SetLastTTL)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnDebugDrawer_setLastTTL"), typeof(_SetLastTTL));
                }
                
                return _SetLastTTLFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct DrawBox__Args
            {
                internal IntPtr a;
                internal IntPtr b;
                internal IntPtr color;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _DrawBox(IntPtr _this, DrawBox__Args args);
            private static _DrawBox _DrawBoxFunc;
            internal static _DrawBox DrawBox() {
                if (_DrawBoxFunc == null) {
                    _DrawBoxFunc =
                        (_DrawBox)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnDebugDrawer_drawBox"), typeof(_DrawBox));
                }
                
                return _DrawBoxFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct DrawLine__Args
            {
                internal IntPtr a;
                internal IntPtr b;
                internal IntPtr color;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _DrawLine(IntPtr _this, DrawLine__Args args);
            private static _DrawLine _DrawLineFunc;
            internal static _DrawLine DrawLine() {
                if (_DrawLineFunc == null) {
                    _DrawLineFunc =
                        (_DrawLine)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnDebugDrawer_drawLine"), typeof(_DrawLine));
                }
                
                return _DrawLineFunc;
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
                                "fnDebugDrawer_staticGetType"), typeof(_StaticGetType));
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
                                "fnDebugDrawer_create"), typeof(_Create));
                }
                
                return _CreateFunc;
            }
        }
        #endregion

        /// <description>
        /// Toggles the rendering of DebugDrawer primitives.
        /// </description>
        public void ToggleDrawing() {
             InternalUnsafeMethods.ToggleDrawing__Args _args = new InternalUnsafeMethods.ToggleDrawing__Args() {
             };
             InternalUnsafeMethods.ToggleDrawing()(ObjectPtr, _args);
        }

        /// <description>
        /// Toggles freeze mode which keeps the currently rendered primitives from expiring.
        /// </description>
        public void ToggleFreeze() {
             InternalUnsafeMethods.ToggleFreeze__Args _args = new InternalUnsafeMethods.ToggleFreeze__Args() {
             };
             InternalUnsafeMethods.ToggleFreeze()(ObjectPtr, _args);
        }

        /// <description>
        /// Sets the z buffer reading state for the last rendered primitive.
        /// </description>
        public void SetLastZTest(bool enabled) {
             InternalUnsafeMethods.SetLastZTest__Args _args = new InternalUnsafeMethods.SetLastZTest__Args() {
                enabled = enabled,
             };
             InternalUnsafeMethods.SetLastZTest()(ObjectPtr, _args);
        }

        /// <description>
        /// Sets the "time to live" (TTL) for the last rendered primitive.
        /// </description>
        public void SetLastTTL(uint ms) {
             InternalUnsafeMethods.SetLastTTL__Args _args = new InternalUnsafeMethods.SetLastTTL__Args() {
                ms = ms,
             };
             InternalUnsafeMethods.SetLastTTL()(ObjectPtr, _args);
        }

        /// <description>
        /// Draws an axis aligned box primitive within the two 3d points.
        /// </description>
        public void DrawBox(Point3F a, Point3F b, LinearColorF color = null) {
a.Alloc();b.Alloc();color = color ?? new LinearColorF("1 1 1 1");
color.Alloc();             InternalUnsafeMethods.DrawBox__Args _args = new InternalUnsafeMethods.DrawBox__Args() {
                a = a.internalStructPtr,
                b = b.internalStructPtr,
                color = color.internalStructPtr,
             };
             InternalUnsafeMethods.DrawBox()(ObjectPtr, _args);
a.Free();b.Free();color.Free();        }

        /// <description>
        /// Draws a line primitive between two 3d points.
        /// </description>
        public void DrawLine(Point3F a, Point3F b, LinearColorF color = null) {
a.Alloc();b.Alloc();color = color ?? new LinearColorF("1 1 1 1");
color.Alloc();             InternalUnsafeMethods.DrawLine__Args _args = new InternalUnsafeMethods.DrawLine__Args() {
                a = a.internalStructPtr,
                b = b.internalStructPtr,
                color = color.internalStructPtr,
             };
             InternalUnsafeMethods.DrawLine()(ObjectPtr, _args);
a.Free();b.Free();color.Free();        }

        /// <description>
        /// Get the type info object for the DebugDrawer class.
        /// </description>
        /// <returns>The type info object for DebugDrawer</returns>
        public static EngineTypeInfo StaticGetType() {
             InternalUnsafeMethods.StaticGetType__Args _args = new InternalUnsafeMethods.StaticGetType__Args() {
             };
             IntPtr _engineResult = InternalUnsafeMethods.StaticGetType()(_args);
             return new EngineTypeInfo(_engineResult);
        }
    }
}