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
    /// 
    public unsafe class AssetQuery : SimObject {
        public AssetQuery(bool pRegister = false) 
            : base(pRegister) {
        }
        
        public AssetQuery(string pName, bool pRegister) 
            : this(false) {
            Name = pName;
            if (pRegister) {
                RegisterObject();
            }
        }
        
        public AssetQuery(string pName) 
            : this(pName, false) {
        }
        
        public AssetQuery(string pName, string pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(Engine.Sim.FindObject<SimObject>(pParent));
        }
        
        public AssetQuery(string pName, SimObject pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(pParent);
        }
        
        public AssetQuery(SimObject pObj) 
            : base(pObj) {
        }
        
        public AssetQuery(IntPtr pObj) 
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
                                "fnAssetQuery_staticGetType"), typeof(_StaticGetType));
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
                                "fnAssetQuery_create"), typeof(_Create));
                }
                
                return _CreateFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct GetAsset__Args
            {
                internal int resultIndex;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            
            internal delegate IntPtr _GetAsset(IntPtr _this, GetAsset__Args args);
            private static _GetAsset _GetAssetFunc;
            internal static _GetAsset GetAsset() {
                if (_GetAssetFunc == null) {
                    _GetAssetFunc =
                        (_GetAsset)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnAssetQuery_getAsset"), typeof(_GetAsset));
                }
                
                return _GetAssetFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct GetCount__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate int _GetCount(IntPtr _this, GetCount__Args args);
            private static _GetCount _GetCountFunc;
            internal static _GetCount GetCount() {
                if (_GetCountFunc == null) {
                    _GetCountFunc =
                        (_GetCount)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnAssetQuery_getCount"), typeof(_GetCount));
                }
                
                return _GetCountFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct Set__Args
            {
                internal int queryId;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            [return: MarshalAs(UnmanagedType.I1)]
            internal delegate bool _Set(IntPtr _this, Set__Args args);
            private static _Set _SetFunc;
            internal static _Set Set() {
                if (_SetFunc == null) {
                    _SetFunc =
                        (_Set)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnAssetQuery_set"), typeof(_Set));
                }
                
                return _SetFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct Clear__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _Clear(IntPtr _this, Clear__Args args);
            private static _Clear _ClearFunc;
            internal static _Clear Clear() {
                if (_ClearFunc == null) {
                    _ClearFunc =
                        (_Clear)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnAssetQuery_clear"), typeof(_Clear));
                }
                
                return _ClearFunc;
            }
        }
        #endregion

        /// <description>
        /// Get the type info object for the AssetQuery class.
        /// </description>
        /// <returns>The type info object for AssetQuery</returns>
        public static EngineTypeInfo StaticGetType() {
             InternalUnsafeMethods.StaticGetType__Args _args = new InternalUnsafeMethods.StaticGetType__Args() {
             };
             IntPtr _engineResult = InternalUnsafeMethods.StaticGetType()(_args);
             return new EngineTypeInfo(_engineResult);
        }

        /// <description>
        /// Gets the asset Id at the specified query result index.
        /// </description>
        /// <param name="resultIndex">The query result index to use.</param>
        /// <returns>(assetId)The asset Id at the specified index or NULL if not valid.</returns>
        public string GetAsset(int resultIndex = -1) {
             InternalUnsafeMethods.GetAsset__Args _args = new InternalUnsafeMethods.GetAsset__Args() {
                resultIndex = resultIndex,
             };
             IntPtr _engineResult = InternalUnsafeMethods.GetAsset()(ObjectPtr, _args);
             return StringMarshal.IntPtrToUtf8String(_engineResult);
        }

        /// <description>
        /// Gets the count of asset Id results.
        /// </description>
        /// <returns>(int)The count of asset Id results.</returns>
        public int GetCount() {
             InternalUnsafeMethods.GetCount__Args _args = new InternalUnsafeMethods.GetCount__Args() {
             };
             int _engineResult = InternalUnsafeMethods.GetCount()(ObjectPtr, _args);
             return _engineResult;
        }

        /// <description>
        /// Sets the asset query to a copy of the specified asset query.
        /// </description>
        /// <param name="assetQuery">The asset query to copy.</param>
        /// <returns>Whether the operation succeeded or not.</returns>
        public bool Set(int queryId) {
             InternalUnsafeMethods.Set__Args _args = new InternalUnsafeMethods.Set__Args() {
                queryId = queryId,
             };
             bool _engineResult = InternalUnsafeMethods.Set()(ObjectPtr, _args);
             return _engineResult;
        }

        /// <description>
        /// Clears all asset Id results.Clears all asset Id results.
        /// </description>
        /// <returns>() No return value.</returns>
        public void Clear() {
             InternalUnsafeMethods.Clear__Args _args = new InternalUnsafeMethods.Clear__Args() {
             };
             InternalUnsafeMethods.Clear()(ObjectPtr, _args);
        }


        /// <value>
        /// <description>
        /// Gets the number of results in the asset query.
        /// </description>
        /// </value>
        public int Count {
            get => GenericMarshal.StringTo<int>(GetFieldValue("count"));
            set => SetFieldValue("count", GenericMarshal.ToString(value));
        }
    }
}