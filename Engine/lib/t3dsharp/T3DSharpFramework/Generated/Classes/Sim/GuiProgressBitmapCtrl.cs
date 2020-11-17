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
    /// <summary>A horizontal progress bar rendered from a repeating image.</summary>
    /// <description>
    /// This class is used give progress feedback to the user.  Unlike GuiProgressCtrl which simply renders a filled rectangle, GuiProgressBitmapCtrl renders the bar using a bitmap.
    /// 
    /// This bitmap can either be simple, plain image which is then stretched into the current extents of the bar as it fills up or it can be a bitmap array with three entries.  In the case of a bitmap array, the first entry in the array is used to render the left cap of the bar and the third entry in the array is used to render the right cap of the bar.  The second entry is streched in-between the two caps.
    /// </description>
    /// <code>
    /// // This example shows one way to break down a long-running computation into phases
    /// // and incrementally update a progress bar between the phases.
    /// 
    /// new GuiProgressBitmapCtrl( Progress )
    /// {
    ///    bitmap = "core/art/gui/images/loading";
    ///    extent = "300 50";
    ///    position = "100 100";
    /// };
    /// 
    /// // Put the control on the canvas.
    /// %wrapper = new GuiControl();
    /// %wrapper.addObject( Progress );
    /// Canvas.pushDialog( %wrapper );
    /// 
    /// // Start the computation.
    /// schedule( 1, 0, "phase1" );
    /// 
    /// function phase1()
    /// {
    ///    Progress.setValue( 0 );
    /// 
    ///    // Perform some computation.
    ///    //...
    /// 
    ///    // Update progress.
    ///    Progress.setValue( 0.25 );
    /// 
    ///    // Schedule next phase.  Don't call directly so engine gets a change to run refresh.
    ///    schedule( 1, 0, "phase2" );
    /// }
    /// 
    /// function phase2()
    /// {
    ///    // Perform some computation.
    ///    //...
    /// 
    ///    // Update progress.
    ///    Progress.setValue( 0.7 );
    /// 
    ///    // Schedule next phase.  Don't call directly so engine gets a change to run refresh.
    ///    schedule( 1, 0, "phase3" );
    /// }
    /// 
    /// function phase3()
    /// {
    ///    // Perform some computation.
    ///    //...
    /// 
    ///    // Update progress.
    ///    Progress.setValue( 0.9 );
    /// 
    ///    // Schedule next phase.  Don't call directly so engine gets a change to run refresh.
    ///    schedule( 1, 0, "phase4" );
    /// }
    /// 
    /// function phase4()
    /// {
    ///    // Perform some computation.
    ///    //...
    /// 
    ///    // Final update of progress.
    ///    Progress.setValue( 1.0 );
    /// }
    /// </code>
    /// <see cref="GuiProgressCtrl" />
    public unsafe class GuiProgressBitmapCtrl : GuiTextCtrl {
        public GuiProgressBitmapCtrl(bool pRegister = false) 
            : base(pRegister) {
        }
        
        public GuiProgressBitmapCtrl(string pName, bool pRegister) 
            : this(false) {
            Name = pName;
            if (pRegister) {
                RegisterObject();
            }
        }
        
        public GuiProgressBitmapCtrl(string pName) 
            : this(pName, false) {
        }
        
        public GuiProgressBitmapCtrl(string pName, string pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(Engine.Sim.FindObject<SimObject>(pParent));
        }
        
        public GuiProgressBitmapCtrl(string pName, SimObject pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(pParent);
        }
        
        public GuiProgressBitmapCtrl(SimObject pObj) 
            : base(pObj) {
        }
        
        public GuiProgressBitmapCtrl(IntPtr pObj) 
            : base(pObj) {
        }
        
		protected override void CreateObjectPtr()
		{
			ObjectPtr = InternalUnsafeMethods.Create()(new InternalUnsafeMethods.Create__Args());
		}

        #region UnsafeNativeMethods
        new internal struct InternalUnsafeMethods {
            [StructLayout(LayoutKind.Sequential)]
            internal struct SetBitmap__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string filename;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _SetBitmap(IntPtr _this, SetBitmap__Args args);
            private static _SetBitmap _SetBitmapFunc;
            internal static _SetBitmap SetBitmap() {
                if (_SetBitmapFunc == null) {
                    _SetBitmapFunc =
                        (_SetBitmap)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnGuiProgressBitmapCtrl_setBitmap"), typeof(_SetBitmap));
                }
                
                return _SetBitmapFunc;
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
                                "fnGuiProgressBitmapCtrl_staticGetType"), typeof(_StaticGetType));
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
                                "fnGuiProgressBitmapCtrl_create"), typeof(_Create));
                }
                
                return _CreateFunc;
            }
        }
        #endregion

        /// <description>
        /// Set the bitmap to use for rendering the progress bar.
        /// </description>
        /// <param name="filename">~Path to the bitmap file.</param>
        /// <remarks> Directly assign to #bitmap rather than using this method.
        /// 
        /// </remarks>
        /// <see cref="GuiProgressBitmapCtrl::setBitmap" />
        public void SetBitmap(string filename) {
             InternalUnsafeMethods.SetBitmap__Args _args = new InternalUnsafeMethods.SetBitmap__Args() {
                filename = filename,
             };
             InternalUnsafeMethods.SetBitmap()(ObjectPtr, _args);
        }

        /// <description>
        /// Get the type info object for the GuiProgressBitmapCtrl class.
        /// </description>
        /// <returns>The type info object for GuiProgressBitmapCtrl</returns>
        public static EngineTypeInfo StaticGetType() {
             InternalUnsafeMethods.StaticGetType__Args _args = new InternalUnsafeMethods.StaticGetType__Args() {
             };
             IntPtr _engineResult = InternalUnsafeMethods.StaticGetType()(_args);
             return new EngineTypeInfo(_engineResult);
        }


        /// <value>
        /// <description>
        /// ~Path to the bitmap file to use for rendering the progress bar.
        /// 
        /// If the profile assigned to the control already has a bitmap assigned, this property need not be set in which case the bitmap from the profile is used.
        /// </description>
        /// </value>
        public string Bitmap {
            get => GenericMarshal.StringTo<string>(GetFieldValue("bitmap"));
            set => SetFieldValue("bitmap", GenericMarshal.ToString(value));
        }
    }
}