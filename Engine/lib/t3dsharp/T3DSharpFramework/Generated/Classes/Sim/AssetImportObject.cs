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
    /// <summary>Defines properties for an AssetImportObject object.</summary>
    /// <description>
    /// 
    /// </description>
    public unsafe class AssetImportObject : SimObject {
        public AssetImportObject(bool pRegister = false) 
            : base(pRegister) {
        }
        
        public AssetImportObject(string pName, bool pRegister) 
            : this(false) {
            Name = pName;
            if (pRegister) {
                RegisterObject();
            }
        }
        
        public AssetImportObject(string pName) 
            : this(pName, false) {
        }
        
        public AssetImportObject(string pName, string pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(Engine.Sim.FindObject<SimObject>(pParent));
        }
        
        public AssetImportObject(string pName, SimObject pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(pParent);
        }
        
        public AssetImportObject(SimObject pObj) 
            : base(pObj) {
        }
        
        public AssetImportObject(IntPtr pObj) 
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
                                "fnAssetImportObject_staticGetType"), typeof(_StaticGetType));
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
                                "fnAssetImportObject_create"), typeof(_Create));
                }
                
                return _CreateFunc;
            }
        }
        #endregion

        /// <description>
        /// Get the type info object for the AssetImportObject class.
        /// </description>
        /// <returns>The type info object for AssetImportObject</returns>
        public static EngineTypeInfo StaticGetType() {
             InternalUnsafeMethods.StaticGetType__Args _args = new InternalUnsafeMethods.StaticGetType__Args() {
             };
             IntPtr _engineResult = InternalUnsafeMethods.StaticGetType()(_args);
             return new EngineTypeInfo(_engineResult);
        }


        /// <value>
        /// <description>
        /// What type is the importing asset
        /// </description>
        /// </value>
        public string AssetType {
            get => GenericMarshal.StringTo<string>(GetFieldValue("assetType"));
            set => SetFieldValue("assetType", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// What is the source file path of the importing asset
        /// </description>
        /// </value>
        public string FilePath {
            get => GenericMarshal.StringTo<string>(GetFieldValue("filePath"));
            set => SetFieldValue("filePath", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// What is the asset's name
        /// </description>
        /// </value>
        public string AssetName {
            get => GenericMarshal.StringTo<string>(GetFieldValue("AssetName"));
            set => SetFieldValue("AssetName", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// What is the original, unmodified by processing, asset name
        /// </description>
        /// </value>
        public string CleanAssetName {
            get => GenericMarshal.StringTo<string>(GetFieldValue("cleanAssetName"));
            set => SetFieldValue("cleanAssetName", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// What is the current status of this asset item in it's import process
        /// </description>
        /// </value>
        public string Status {
            get => GenericMarshal.StringTo<string>(GetFieldValue("status"));
            set => SetFieldValue("status", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// If there is a warning or error status, what type is the condition for this asset item
        /// </description>
        /// </value>
        public string StatusType {
            get => GenericMarshal.StringTo<string>(GetFieldValue("statusType"));
            set => SetFieldValue("statusType", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// What is the articulated information of the status of the asset. Contains the error or warning log data
        /// </description>
        /// </value>
        public string StatusInfo {
            get => GenericMarshal.StringTo<string>(GetFieldValue("statusInfo"));
            set => SetFieldValue("statusInfo", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Is the asset item currently flagged as dirty
        /// </description>
        /// </value>
        public bool Dirty {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("dirty"));
            set => SetFieldValue("dirty", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Is this asset item marked to be skipped. If it is, it's usually due to being marked as deleted
        /// </description>
        /// </value>
        public bool Skip {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("skip"));
            set => SetFieldValue("skip", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Has the asset item been processed
        /// </description>
        /// </value>
        public bool Processed {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("processed"));
            set => SetFieldValue("processed", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Is this specific asset item generated as part of the import process of another item
        /// </description>
        /// </value>
        public bool GeneratedAsset {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("generatedAsset"));
            set => SetFieldValue("generatedAsset", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// What is the ultimate asset taml file path for this import item
        /// </description>
        /// </value>
        public string TamlFilePath {
            get => GenericMarshal.StringTo<string>(GetFieldValue("tamlFilePath"));
            set => SetFieldValue("tamlFilePath", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Specific to ImageAsset type. What is the image asset's suffix type. Options are: Albedo, Normal, Roughness, AO, Metalness, PBRConfig
        /// </description>
        /// </value>
        public string ImageType {
            get => GenericMarshal.StringTo<string>(GetFieldValue("imageType"));
            set => SetFieldValue("imageType", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Specific to ShapeAsset type. Processed information about the shape file. Contains numbers and lists of meshes, materials and animations
        /// </description>
        /// </value>
        public GuiTreeViewCtrl ShapeInfo {
            get => GenericMarshal.StringTo<GuiTreeViewCtrl>(GetFieldValue("shapeInfo"));
            set => SetFieldValue("shapeInfo", GenericMarshal.ToString(value));
        }
    }
}