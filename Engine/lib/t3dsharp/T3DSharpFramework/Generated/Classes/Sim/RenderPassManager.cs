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
    /// <summary>A grouping of render bin managers which forms a render pass.</summary>
    /// <description>
    /// The render pass is used to order a set of RenderBinManager objects which are used when rendering a scene.  This class does little work itself other than managing its list of render bins.
    /// 
    /// In 'core/scripts/client/renderManager.cs' you will find the DiffuseRenderPassManager which is used by the C++ engine to render the scene.
    /// </description>
    /// <see cref="RenderBinManager" />
    public unsafe class RenderPassManager : SimObject {
        public RenderPassManager(bool pRegister = false) 
            : base(pRegister) {
        }
        
        public RenderPassManager(string pName, bool pRegister) 
            : this(false) {
            Name = pName;
            if (pRegister) {
                RegisterObject();
            }
        }
        
        public RenderPassManager(string pName) 
            : this(pName, false) {
        }
        
        public RenderPassManager(string pName, string pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(Engine.Sim.FindObject<SimObject>(pParent));
        }
        
        public RenderPassManager(string pName, SimObject pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(pParent);
        }
        
        public RenderPassManager(SimObject pObj) 
            : base(pObj) {
        }
        
        public RenderPassManager(IntPtr pObj) 
            : base(pObj) {
        }
        
		protected override void CreateObjectPtr()
		{
			ObjectPtr = InternalUnsafeMethods.Create()(new InternalUnsafeMethods.Create__Args());
		}

        #region UnsafeNativeMethods
        new internal struct InternalUnsafeMethods {
            [StructLayout(LayoutKind.Sequential)]
            internal struct RemoveManager__Args
            {
                internal IntPtr renderBin;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _RemoveManager(IntPtr _this, RemoveManager__Args args);
            private static _RemoveManager _RemoveManagerFunc;
            internal static _RemoveManager RemoveManager() {
                if (_RemoveManagerFunc == null) {
                    _RemoveManagerFunc =
                        (_RemoveManager)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnRenderPassManager_removeManager"), typeof(_RemoveManager));
                }
                
                return _RemoveManagerFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct AddManager__Args
            {
                internal IntPtr renderBin;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _AddManager(IntPtr _this, AddManager__Args args);
            private static _AddManager _AddManagerFunc;
            internal static _AddManager AddManager() {
                if (_AddManagerFunc == null) {
                    _AddManagerFunc =
                        (_AddManager)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnRenderPassManager_addManager"), typeof(_AddManager));
                }
                
                return _AddManagerFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct GetManager__Args
            {
                internal int index;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate IntPtr _GetManager(IntPtr _this, GetManager__Args args);
            private static _GetManager _GetManagerFunc;
            internal static _GetManager GetManager() {
                if (_GetManagerFunc == null) {
                    _GetManagerFunc =
                        (_GetManager)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnRenderPassManager_getManager"), typeof(_GetManager));
                }
                
                return _GetManagerFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct GetManagerCount__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate int _GetManagerCount(IntPtr _this, GetManagerCount__Args args);
            private static _GetManagerCount _GetManagerCountFunc;
            internal static _GetManagerCount GetManagerCount() {
                if (_GetManagerCountFunc == null) {
                    _GetManagerCountFunc =
                        (_GetManagerCount)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnRenderPassManager_getManagerCount"), typeof(_GetManagerCount));
                }
                
                return _GetManagerCountFunc;
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
                                "fnRenderPassManager_staticGetType"), typeof(_StaticGetType));
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
                                "fnRenderPassManager_create"), typeof(_Create));
                }
                
                return _CreateFunc;
            }
        }
        #endregion

        /// <description>
        /// Removes a render bin manager.
        /// </description>
        public void RemoveManager(RenderBinManager renderBin) {
             InternalUnsafeMethods.RemoveManager__Args _args = new InternalUnsafeMethods.RemoveManager__Args() {
                renderBin = renderBin.ObjectPtr,
             };
             InternalUnsafeMethods.RemoveManager()(ObjectPtr, _args);
        }

        /// <description>
        /// Add as a render bin manager to the pass.
        /// </description>
        public void AddManager(RenderBinManager renderBin) {
             InternalUnsafeMethods.AddManager__Args _args = new InternalUnsafeMethods.AddManager__Args() {
                renderBin = renderBin.ObjectPtr,
             };
             InternalUnsafeMethods.AddManager()(ObjectPtr, _args);
        }

        /// <description>
        /// Returns the render bin manager at the index or null if the index is out of range.
        /// </description>
        public RenderBinManager GetManager(int index) {
             InternalUnsafeMethods.GetManager__Args _args = new InternalUnsafeMethods.GetManager__Args() {
                index = index,
             };
             IntPtr _engineResult = InternalUnsafeMethods.GetManager()(ObjectPtr, _args);
             return new RenderBinManager(_engineResult);
        }

        /// <description>
        /// Returns the total number of bin managers.
        /// </description>
        public int GetManagerCount() {
             InternalUnsafeMethods.GetManagerCount__Args _args = new InternalUnsafeMethods.GetManagerCount__Args() {
             };
             int _engineResult = InternalUnsafeMethods.GetManagerCount()(ObjectPtr, _args);
             return _engineResult;
        }

        /// <description>
        /// Get the type info object for the RenderPassManager class.
        /// </description>
        /// <returns>The type info object for RenderPassManager</returns>
        public static EngineTypeInfo StaticGetType() {
             InternalUnsafeMethods.StaticGetType__Args _args = new InternalUnsafeMethods.StaticGetType__Args() {
             };
             IntPtr _engineResult = InternalUnsafeMethods.StaticGetType()(_args);
             return new EngineTypeInfo(_engineResult);
        }
    }
}