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
    /// <summary>A renderable, collidable convex shape defined by a collection of surface planes.</summary>
    /// <description>
    /// %ConvexShape is intended to be used as a temporary asset for quickly blocking out a scene or filling in approximate shapes to be later replaced with final assets. This is most easily done by using the WorldEditor's Sketch Tool.
    /// </description>
    public unsafe class ConvexShape : SceneObject {
        public ConvexShape(bool pRegister = false) 
            : base(pRegister) {
        }
        
        public ConvexShape(string pName, bool pRegister) 
            : this(false) {
            Name = pName;
            if (pRegister) {
                RegisterObject();
            }
        }
        
        public ConvexShape(string pName) 
            : this(pName, false) {
        }
        
        public ConvexShape(string pName, string pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(Engine.Sim.FindObject<SimObject>(pParent));
        }
        
        public ConvexShape(string pName, SimObject pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(pParent);
        }
        
        public ConvexShape(SimObject pObj) 
            : base(pObj) {
        }
        
        public ConvexShape(IntPtr pObj) 
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
                                "fnConvexShape_staticGetType"), typeof(_StaticGetType));
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
                                "fnConvexShape_create"), typeof(_Create));
                }
                
                return _CreateFunc;
            }
        }
        #endregion

        /// <description>
        /// Get the type info object for the ConvexShape class.
        /// </description>
        /// <returns>The type info object for ConvexShape</returns>
        public static EngineTypeInfo StaticGetType() {
             InternalUnsafeMethods.StaticGetType__Args _args = new InternalUnsafeMethods.StaticGetType__Args() {
             };
             IntPtr _engineResult = InternalUnsafeMethods.StaticGetType()(_args);
             return new EngineTypeInfo(_engineResult);
        }


        /// <value>
        /// <description>
        /// Material used to render the ConvexShape surface.
        /// </description>
        /// </value>
        public string Material {
            get => GenericMarshal.StringTo<string>(GetFieldValue("Material"));
            set => SetFieldValue("Material", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Do not modify, for internal use.
        /// </description>
        /// </value>
        public string Surface {
            get => GenericMarshal.StringTo<string>(GetFieldValue("surface"));
            set => SetFieldValue("surface", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Do not modify, for internal use.
        /// </description>
        /// </value>
        public string SurfaceTexture {
            get => GenericMarshal.StringTo<string>(GetFieldValue("surfaceTexture"));
            set => SetFieldValue("surfaceTexture", GenericMarshal.ToString(value));
        }
    }
}