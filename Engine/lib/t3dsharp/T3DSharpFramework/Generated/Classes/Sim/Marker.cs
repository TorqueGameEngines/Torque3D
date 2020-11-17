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
    /// <summary>A single joint, or knot, along a path. Should be stored inside a Path container object. A path markers can be</summary>
    /// <description>
    /// one of three primary movement types: "normal", "Position Only", or "Kink".
    /// </description>
    /// <code>
    /// new path()
    /// 	{
    ///      isLooping = "1";
    /// 
    ///      new Marker()
    /// 		{
    /// 			seqNum = "0";
    /// 			type = "Normal";
    /// 			msToNext = "1000";
    /// 			smoothingType = "Spline";
    /// 			position = "-0.054708 -35.0612 234.802";
    /// 			rotation = "1 0 0 0";
    ///       };
    /// 
    /// 	};
    /// </code>
    /// <see cref="Path" />
    public unsafe class Marker : SceneObject {
        public Marker(bool pRegister = false) 
            : base(pRegister) {
        }
        
        public Marker(string pName, bool pRegister) 
            : this(false) {
            Name = pName;
            if (pRegister) {
                RegisterObject();
            }
        }
        
        public Marker(string pName) 
            : this(pName, false) {
        }
        
        public Marker(string pName, string pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(Engine.Sim.FindObject<SimObject>(pParent));
        }
        
        public Marker(string pName, SimObject pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(pParent);
        }
        
        public Marker(SimObject pObj) 
            : base(pObj) {
        }
        
        public Marker(IntPtr pObj) 
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
                                "fnMarker_staticGetType"), typeof(_StaticGetType));
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
                                "fnMarker_create"), typeof(_Create));
                }
                
                return _CreateFunc;
            }
        }
        #endregion

        /// <description>
        /// Get the type info object for the Marker class.
        /// </description>
        /// <returns>The type info object for Marker</returns>
        public static EngineTypeInfo StaticGetType() {
             InternalUnsafeMethods.StaticGetType__Args _args = new InternalUnsafeMethods.StaticGetType__Args() {
             };
             IntPtr _engineResult = InternalUnsafeMethods.StaticGetType()(_args);
             return new EngineTypeInfo(_engineResult);
        }


        /// <value>
        /// <description>
        /// Marker position in sequence of markers on this path.
        /// </description>
        /// </value>
        public int SeqNum {
            get => GenericMarshal.StringTo<int>(GetFieldValue("seqNum"));
            set => SetFieldValue("seqNum", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Type of this marker/knot. A "normal" knot will have a smooth camera translation/rotation effect.
        /// "Position Only" will do the same for translations, leaving rotation un-touched.
        /// Lastly, a "Kink" means the rotation will take effect immediately for an abrupt rotation change.
        /// </description>
        /// </value>
        public MarkerKnotType Type {
            get => GenericMarshal.StringTo<MarkerKnotType>(GetFieldValue("type"));
            set => SetFieldValue("type", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Milliseconds to next marker in sequence.
        /// </description>
        /// </value>
        public int MsToNext {
            get => GenericMarshal.StringTo<int>(GetFieldValue("msToNext"));
            set => SetFieldValue("msToNext", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Path smoothing at this marker/knot. "Linear" means no smoothing, while "Spline" means to smooth.
        /// </description>
        /// </value>
        public MarkerSmoothingType SmoothingType {
            get => GenericMarshal.StringTo<MarkerSmoothingType>(GetFieldValue("smoothingType"));
            set => SetFieldValue("smoothingType", GenericMarshal.ToString(value));
        }
    }
}