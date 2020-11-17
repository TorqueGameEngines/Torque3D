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
    /// <summary>A datablock which defines performance and quality properties for dynamic reflections.</summary>
    /// <description>
    /// ReflectorDesc is not itself a reflection and does not render reflections. It is a dummy class for holding and exposing to the user a set of reflection related properties. Objects which support dynamic reflections may then reference a ReflectorDesc.
    /// </description>
    /// <code>
    /// datablock ReflectorDesc( ExampleReflectorDesc )
    /// {
    ///    texSize = 256;
    ///    nearDist = 0.1;
    ///    farDist = 500;
    ///    objectTypeMask = 0xFFFFFFFF;
    ///    detailAdjust = 1.0;
    ///    priority = 1.0;
    ///    maxRateMs = 0;
    ///    useOcclusionQuery = true;
    /// };
    /// </code>
    /// <see cref="ShapeBaseData::cubeReflectorDesc" />
    public unsafe class ReflectorDesc : SimDataBlock {
        public ReflectorDesc(bool pRegister = false) 
            : base(pRegister) {
        }
        
        public ReflectorDesc(string pName, bool pRegister) 
            : this(false) {
            Name = pName;
            if (pRegister) {
                RegisterObject();
            }
        }
        
        public ReflectorDesc(string pName) 
            : this(pName, false) {
        }
        
        public ReflectorDesc(string pName, string pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(Engine.Sim.FindObject<SimObject>(pParent));
        }
        
        public ReflectorDesc(string pName, SimObject pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(pParent);
        }
        
        public ReflectorDesc(SimObject pObj) 
            : base(pObj) {
        }
        
        public ReflectorDesc(IntPtr pObj) 
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
                                "fnReflectorDesc_staticGetType"), typeof(_StaticGetType));
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
                                "fnReflectorDesc_create"), typeof(_Create));
                }
                
                return _CreateFunc;
            }
        }
        #endregion

        /// <description>
        /// Get the type info object for the ReflectorDesc class.
        /// </description>
        /// <returns>The type info object for ReflectorDesc</returns>
        public static EngineTypeInfo StaticGetType() {
             InternalUnsafeMethods.StaticGetType__Args _args = new InternalUnsafeMethods.StaticGetType__Args() {
             };
             IntPtr _engineResult = InternalUnsafeMethods.StaticGetType()(_args);
             return new EngineTypeInfo(_engineResult);
        }


        /// <value>
        /// <description>
        /// Size in pixels of the (square) reflection texture. For a cubemap this value is interpreted as size of each face.
        /// </description>
        /// </value>
        public int TexSize {
            get => GenericMarshal.StringTo<int>(GetFieldValue("texSize"));
            set => SetFieldValue("texSize", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Near plane distance to use when rendering this reflection. Adjust this to limit self-occlusion artifacts.
        /// </description>
        /// </value>
        public float NearDist {
            get => GenericMarshal.StringTo<float>(GetFieldValue("nearDist"));
            set => SetFieldValue("nearDist", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Far plane distance to use when rendering reflections.
        /// </description>
        /// </value>
        public float FarDist {
            get => GenericMarshal.StringTo<float>(GetFieldValue("farDist"));
            set => SetFieldValue("farDist", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Object types which render into this reflection.
        /// </description>
        /// </value>
        public int ObjectTypeMask {
            get => GenericMarshal.StringTo<int>(GetFieldValue("objectTypeMask"));
            set => SetFieldValue("objectTypeMask", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Scale applied to lod calculation of objects rendering into this reflection ( modulates $pref::TS::detailAdjust ).
        /// </description>
        /// </value>
        public float DetailAdjust {
            get => GenericMarshal.StringTo<float>(GetFieldValue("detailAdjust"));
            set => SetFieldValue("detailAdjust", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Priority for updating this reflection, relative to others.
        /// </description>
        /// </value>
        public float Priority {
            get => GenericMarshal.StringTo<float>(GetFieldValue("priority"));
            set => SetFieldValue("priority", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// If less than maxRateMs has elapsed since this relfection was last updated, then do not update it again. This 'skip' can be disabled by setting maxRateMs to zero.
        /// </description>
        /// </value>
        public int MaxRateMs {
            get => GenericMarshal.StringTo<int>(GetFieldValue("maxRateMs"));
            set => SetFieldValue("maxRateMs", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// If available on the device use HOQs to determine if the reflective object is visible before updating its reflection.
        /// </description>
        /// </value>
        public bool UseOcclusionQuery {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("useOcclusionQuery"));
            set => SetFieldValue("useOcclusionQuery", GenericMarshal.ToString(value));
        }
    }
}