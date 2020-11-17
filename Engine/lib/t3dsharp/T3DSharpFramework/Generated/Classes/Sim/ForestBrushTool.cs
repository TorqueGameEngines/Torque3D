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
    /// <summary>Defines the brush properties when painting trees in Forest Editor</summary>
    /// <description>
    /// Editor use only.
    /// </description>
    public unsafe class ForestBrushTool : ForestTool {
        public ForestBrushTool(bool pRegister = false) 
            : base(pRegister) {
        }
        
        public ForestBrushTool(string pName, bool pRegister) 
            : this(false) {
            Name = pName;
            if (pRegister) {
                RegisterObject();
            }
        }
        
        public ForestBrushTool(string pName) 
            : this(pName, false) {
        }
        
        public ForestBrushTool(string pName, string pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(Engine.Sim.FindObject<SimObject>(pParent));
        }
        
        public ForestBrushTool(string pName, SimObject pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(pParent);
        }
        
        public ForestBrushTool(SimObject pObj) 
            : base(pObj) {
        }
        
        public ForestBrushTool(IntPtr pObj) 
            : base(pObj) {
        }
        
		protected override void CreateObjectPtr()
		{
			ObjectPtr = InternalUnsafeMethods.Create()(new InternalUnsafeMethods.Create__Args());
		}

        #region UnsafeNativeMethods
        new internal struct InternalUnsafeMethods {
            [StructLayout(LayoutKind.Sequential)]
            internal struct CollectElements__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _CollectElements(IntPtr _this, CollectElements__Args args);
            private static _CollectElements _CollectElementsFunc;
            internal static _CollectElements CollectElements() {
                if (_CollectElementsFunc == null) {
                    _CollectElementsFunc =
                        (_CollectElements)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnForestBrushTool_collectElements"), typeof(_CollectElements));
                }
                
                return _CollectElementsFunc;
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
                                "fnForestBrushTool_staticGetType"), typeof(_StaticGetType));
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
                                "fnForestBrushTool_create"), typeof(_Create));
                }
                
                return _CreateFunc;
            }
        }
        #endregion

        /// 
        public void CollectElements() {
             InternalUnsafeMethods.CollectElements__Args _args = new InternalUnsafeMethods.CollectElements__Args() {
             };
             InternalUnsafeMethods.CollectElements()(ObjectPtr, _args);
        }

        /// <description>
        /// Get the type info object for the ForestBrushTool class.
        /// </description>
        /// <returns>The type info object for ForestBrushTool</returns>
        public static EngineTypeInfo StaticGetType() {
             InternalUnsafeMethods.StaticGetType__Args _args = new InternalUnsafeMethods.StaticGetType__Args() {
             };
             IntPtr _engineResult = InternalUnsafeMethods.StaticGetType()(_args);
             return new EngineTypeInfo(_engineResult);
        }


        /// <value>
        /// 
        /// </value>
        public ForestBrushMode Mode {
            get => GenericMarshal.StringTo<ForestBrushMode>(GetFieldValue("mode"));
            set => SetFieldValue("mode", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Brush Size
        /// </description>
        /// </value>
        public float Size {
            get => GenericMarshal.StringTo<float>(GetFieldValue("size"));
            set => SetFieldValue("size", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Brush Pressure
        /// </description>
        /// </value>
        public float Pressure {
            get => GenericMarshal.StringTo<float>(GetFieldValue("pressure"));
            set => SetFieldValue("pressure", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Brush Hardness
        /// </description>
        /// </value>
        public float Hardness {
            get => GenericMarshal.StringTo<float>(GetFieldValue("hardness"));
            set => SetFieldValue("hardness", GenericMarshal.ToString(value));
        }
    }
}