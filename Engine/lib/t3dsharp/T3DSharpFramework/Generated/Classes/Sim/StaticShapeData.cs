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
    /// <summary>The most basic ShapeBaseData derrived shape datablock available in Torque 3D.</summary>
    /// <description>
    /// When it comes to placing 3D objects in the scene, you effectively have two options:
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
    /// <see cref="StaticShape" />
    /// <see cref="ShapeBaseData" />
    /// <see cref="TSStatic" />
    public unsafe class StaticShapeData : ShapeBaseData {
        public StaticShapeData(bool pRegister = false) 
            : base(pRegister) {
        }
        
        public StaticShapeData(string pName, bool pRegister) 
            : this(false) {
            Name = pName;
            if (pRegister) {
                RegisterObject();
            }
        }
        
        public StaticShapeData(string pName) 
            : this(pName, false) {
        }
        
        public StaticShapeData(string pName, string pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(Engine.Sim.FindObject<SimObject>(pParent));
        }
        
        public StaticShapeData(string pName, SimObject pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(pParent);
        }
        
        public StaticShapeData(SimObject pObj) 
            : base(pObj) {
        }
        
        public StaticShapeData(IntPtr pObj) 
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
                                "fnStaticShapeData_staticGetType"), typeof(_StaticGetType));
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
                                "fnStaticShapeData_create"), typeof(_Create));
                }
                
                return _CreateFunc;
            }
        }
        #endregion

        /// <description>
        /// Get the type info object for the StaticShapeData class.
        /// </description>
        /// <returns>The type info object for StaticShapeData</returns>
        public static EngineTypeInfo StaticGetType() {
             InternalUnsafeMethods.StaticGetType__Args _args = new InternalUnsafeMethods.StaticGetType__Args() {
             };
             IntPtr _engineResult = InternalUnsafeMethods.StaticGetType()(_args);
             return new EngineTypeInfo(_engineResult);
        }


        /// <value>
        /// <description>
        /// Deprecated
        /// </description>
        /// </value>
        public bool NoIndividualDamage {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("noIndividualDamage"));
            set => SetFieldValue("noIndividualDamage", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <summary>An integer value which, if speficied, is added to the value retured by getType().</summary>
        /// <description>
        /// This allows you to extend the type mask for a StaticShape that uses this datablock.  Type masks are used for container queries, etc.
        /// </description>
        /// </value>
        public int DynamicType {
            get => GenericMarshal.StringTo<int>(GetFieldValue("dynamicType"));
            set => SetFieldValue("dynamicType", GenericMarshal.ToString(value));
        }
    }
}