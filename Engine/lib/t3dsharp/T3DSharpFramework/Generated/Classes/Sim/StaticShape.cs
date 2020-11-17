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
    /// <summary>The most basic 3D shape with a datablock available in Torque 3D.</summary>
    /// <description>
    /// When it comes to placing 3D objects in the scene, you technically have two options:
    /// 
    /// 1. TSStatic objects
    /// 
    /// 2. ShapeBase derived objects
    /// 
    /// Since ShapeBase and ShapeBaseData are not meant to be instantiated in script, you will use one of its child classes instead. Several game related objects are derived from ShapeBase: Player, Vehicle, Item, and so on.
    /// 
    /// When you need a 3D object with datablock capabilities, you will use an object derived from ShapeBase. When you need an object with extremely low overhead, and with no other purpose than to be a 3D object in the scene, you will use TSStatic.
    /// 
    /// The most basic child of ShapeBase is StaticShape. It does not introduce any of the additional functionality you see in Player, Item, Vehicle or the other game play heavy classes. At its core, it is comparable to a TSStatic, but with a datbalock.  Having a datablock provides a location for common variables as well as having access to various ShapeBaseData, GameBaseData and SimDataBlock callbacks.
    /// </description>
    /// <code>
    /// // Create a StaticShape using a datablock
    /// datablock StaticShapeData(BasicShapeData)
    /// {
    ///   shapeFile = "art/shapes/items/kit/healthkit.dts";
    ///   testVar = "Simple string, not a stock variable";
    /// };
    /// 
    /// new StaticShape()
    /// {
    ///   dataBlock = "BasicShapeData";
    ///   position = "0.0 0.0 0.0";
    ///   rotation = "1 0 0 0";
    ///   scale = "1 1 1";
    /// };
    /// </code>
    /// <see cref="StaticShapeData" />
    /// <see cref="ShapeBase" />
    /// <see cref="TSStatic" />
    public unsafe class StaticShape : ShapeBase {
        public StaticShape(bool pRegister = false) 
            : base(pRegister) {
        }
        
        public StaticShape(string pName, bool pRegister) 
            : this(false) {
            Name = pName;
            if (pRegister) {
                RegisterObject();
            }
        }
        
        public StaticShape(string pName) 
            : this(pName, false) {
        }
        
        public StaticShape(string pName, string pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(Engine.Sim.FindObject<SimObject>(pParent));
        }
        
        public StaticShape(string pName, SimObject pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(pParent);
        }
        
        public StaticShape(SimObject pObj) 
            : base(pObj) {
        }
        
        public StaticShape(IntPtr pObj) 
            : base(pObj) {
        }
        
		protected override void CreateObjectPtr()
		{
			ObjectPtr = InternalUnsafeMethods.Create()(new InternalUnsafeMethods.Create__Args());
		}

        #region UnsafeNativeMethods
        new internal struct InternalUnsafeMethods {
            [StructLayout(LayoutKind.Sequential)]
            internal struct GetPoweredState__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            [return: MarshalAs(UnmanagedType.I1)]
            internal delegate bool _GetPoweredState(IntPtr _this, GetPoweredState__Args args);
            private static _GetPoweredState _GetPoweredStateFunc;
            internal static _GetPoweredState GetPoweredState() {
                if (_GetPoweredStateFunc == null) {
                    _GetPoweredStateFunc =
                        (_GetPoweredState)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnStaticShape_getPoweredState"), typeof(_GetPoweredState));
                }
                
                return _GetPoweredStateFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct SetPoweredState__Args
            {
                [MarshalAs(UnmanagedType.I1)]
                internal bool isPowered;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _SetPoweredState(IntPtr _this, SetPoweredState__Args args);
            private static _SetPoweredState _SetPoweredStateFunc;
            internal static _SetPoweredState SetPoweredState() {
                if (_SetPoweredStateFunc == null) {
                    _SetPoweredStateFunc =
                        (_SetPoweredState)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnStaticShape_setPoweredState"), typeof(_SetPoweredState));
                }
                
                return _SetPoweredStateFunc;
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
                                "fnStaticShape_staticGetType"), typeof(_StaticGetType));
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
                                "fnStaticShape_create"), typeof(_Create));
                }
                
                return _CreateFunc;
            }
        }
        #endregion

        /// 
        public bool GetPoweredState() {
             InternalUnsafeMethods.GetPoweredState__Args _args = new InternalUnsafeMethods.GetPoweredState__Args() {
             };
             bool _engineResult = InternalUnsafeMethods.GetPoweredState()(ObjectPtr, _args);
             return _engineResult;
        }

        /// <description>
        /// (bool isPowered)
        /// </description>
        public void SetPoweredState(bool isPowered) {
             InternalUnsafeMethods.SetPoweredState__Args _args = new InternalUnsafeMethods.SetPoweredState__Args() {
                isPowered = isPowered,
             };
             InternalUnsafeMethods.SetPoweredState()(ObjectPtr, _args);
        }

        /// <description>
        /// Get the type info object for the StaticShape class.
        /// </description>
        /// <returns>The type info object for StaticShape</returns>
        public static EngineTypeInfo StaticGetType() {
             InternalUnsafeMethods.StaticGetType__Args _args = new InternalUnsafeMethods.StaticGetType__Args() {
             };
             IntPtr _engineResult = InternalUnsafeMethods.StaticGetType()(_args);
             return new EngineTypeInfo(_engineResult);
        }
    }
}