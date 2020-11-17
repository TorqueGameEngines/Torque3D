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
    /// <summary>A GUI progress bar useful as a spell casting bar.</summary>
    /// <description>
    /// 
    /// </description>
    public unsafe class afxSpellCastBar : GuiControl {
        public afxSpellCastBar(bool pRegister = false) 
            : base(pRegister) {
        }
        
        public afxSpellCastBar(string pName, bool pRegister) 
            : this(false) {
            Name = pName;
            if (pRegister) {
                RegisterObject();
            }
        }
        
        public afxSpellCastBar(string pName) 
            : this(pName, false) {
        }
        
        public afxSpellCastBar(string pName, string pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(Engine.Sim.FindObject<SimObject>(pParent));
        }
        
        public afxSpellCastBar(string pName, SimObject pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(pParent);
        }
        
        public afxSpellCastBar(SimObject pObj) 
            : base(pObj) {
        }
        
        public afxSpellCastBar(IntPtr pObj) 
            : base(pObj) {
        }
        
		protected override void CreateObjectPtr()
		{
			ObjectPtr = InternalUnsafeMethods.Create()(new InternalUnsafeMethods.Create__Args());
		}

        #region UnsafeNativeMethods
        new internal struct InternalUnsafeMethods {
            [StructLayout(LayoutKind.Sequential)]
            internal struct SetProgress__Args
            {
                internal float percentDone;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _SetProgress(IntPtr _this, SetProgress__Args args);
            private static _SetProgress _SetProgressFunc;
            internal static _SetProgress SetProgress() {
                if (_SetProgressFunc == null) {
                    _SetProgressFunc =
                        (_SetProgress)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnafxSpellCastBar_setProgress"), typeof(_SetProgress));
                }
                
                return _SetProgressFunc;
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
                                "fnafxSpellCastBar_staticGetType"), typeof(_StaticGetType));
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
                                "fnafxSpellCastBar_create"), typeof(_Create));
                }
                
                return _CreateFunc;
            }
        }
        #endregion

        /// <description>
        /// Set the progress percentage on the progress-bar.
        /// </description>
        public void SetProgress(float percentDone) {
             InternalUnsafeMethods.SetProgress__Args _args = new InternalUnsafeMethods.SetProgress__Args() {
                percentDone = percentDone,
             };
             InternalUnsafeMethods.SetProgress()(ObjectPtr, _args);
        }

        /// <description>
        /// Get the type info object for the afxSpellCastBar class.
        /// </description>
        /// <returns>The type info object for afxSpellCastBar</returns>
        public static EngineTypeInfo StaticGetType() {
             InternalUnsafeMethods.StaticGetType__Args _args = new InternalUnsafeMethods.StaticGetType__Args() {
             };
             IntPtr _engineResult = InternalUnsafeMethods.StaticGetType()(_args);
             return new EngineTypeInfo(_engineResult);
        }


        /// <value>
        /// <description>
        /// ...
        /// </description>
        /// </value>
        public LinearColorF BackgroundColor {
            get => GenericMarshal.StringTo<LinearColorF>(GetFieldValue("backgroundColor"));
            set => SetFieldValue("backgroundColor", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// ...
        /// </description>
        /// </value>
        public LinearColorF BorderColor {
            get => GenericMarshal.StringTo<LinearColorF>(GetFieldValue("borderColor"));
            set => SetFieldValue("borderColor", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// ...
        /// </description>
        /// </value>
        public LinearColorF FillColor {
            get => GenericMarshal.StringTo<LinearColorF>(GetFieldValue("fillColor"));
            set => SetFieldValue("fillColor", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// ...
        /// </description>
        /// </value>
        public LinearColorF FillColorFinal {
            get => GenericMarshal.StringTo<LinearColorF>(GetFieldValue("fillColorFinal"));
            set => SetFieldValue("fillColorFinal", GenericMarshal.ToString(value));
        }
    }
}