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
    /// <summary>A sound source that drives multi-source playback.</summary>
    /// <description>
    /// This class acts as an interpreter for SFXPlayLists.  It goes through the slots of the playlist it is attached to and performs the actions described by each of the slots in turn.
    /// As SFXControllers are created implicitly by the SFX system when instantiating a source for a play list it is in most cases not necessary to directly deal with the class.
    /// The following example demonstrates how a controller would commonly be created.
    /// </description>
    /// <code>
    /// // Create a play list from two SFXProfiles.
    /// %playList = new SFXPlayList()
    /// {
    ///    // Use a looped description so the list playback will loop.
    ///    description = AudioMusicLoop2D;
    /// 
    ///    track[ 0 ] = Profile1;
    ///    track[ 1 ] = Profile2;
    /// };
    /// 
    /// // Play the list.  This will implicitly create a controller.
    /// sfxPlayOnce( %playList );
    /// </code>
    /// <remarks> Play lists are updated at regular intervals by the sound system.  This processing determines the granularity at which playlist action timing takes place.
    /// </remarks>
    /// <remarks> This class cannot be instantiated directly.  Use sfxPlayOnce() or sfxCreateSource() with the playlist you want to play to create an instance of this class.
    /// </remarks>
    /// <see cref="SFXPlayList" />
    public unsafe class SFXController : SFXSource {
        public SFXController(bool pRegister = false) 
            : base(pRegister) {
        }
        
        public SFXController(string pName, bool pRegister) 
            : this(false) {
            Name = pName;
            if (pRegister) {
                RegisterObject();
            }
        }
        
        public SFXController(string pName) 
            : this(pName, false) {
        }
        
        public SFXController(string pName, string pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(Engine.Sim.FindObject<SimObject>(pParent));
        }
        
        public SFXController(string pName, SimObject pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(pParent);
        }
        
        public SFXController(SimObject pObj) 
            : base(pObj) {
        }
        
        public SFXController(IntPtr pObj) 
            : base(pObj) {
        }
        
		protected override void CreateObjectPtr()
		{
			ObjectPtr = InternalUnsafeMethods.Create()(new InternalUnsafeMethods.Create__Args());
		}

        #region UnsafeNativeMethods
        new internal struct InternalUnsafeMethods {
            [StructLayout(LayoutKind.Sequential)]
            internal struct SetCurrentSlot__Args
            {
                internal int index;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _SetCurrentSlot(IntPtr _this, SetCurrentSlot__Args args);
            private static _SetCurrentSlot _SetCurrentSlotFunc;
            internal static _SetCurrentSlot SetCurrentSlot() {
                if (_SetCurrentSlotFunc == null) {
                    _SetCurrentSlotFunc =
                        (_SetCurrentSlot)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnSFXController_setCurrentSlot"), typeof(_SetCurrentSlot));
                }
                
                return _SetCurrentSlotFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct GetCurrentSlot__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate int _GetCurrentSlot(IntPtr _this, GetCurrentSlot__Args args);
            private static _GetCurrentSlot _GetCurrentSlotFunc;
            internal static _GetCurrentSlot GetCurrentSlot() {
                if (_GetCurrentSlotFunc == null) {
                    _GetCurrentSlotFunc =
                        (_GetCurrentSlot)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnSFXController_getCurrentSlot"), typeof(_GetCurrentSlot));
                }
                
                return _GetCurrentSlotFunc;
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
                                "fnSFXController_staticGetType"), typeof(_StaticGetType));
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
                                "fnSFXController_create"), typeof(_Create));
                }
                
                return _CreateFunc;
            }
        }
        #endregion

        /// <description>
        /// Set the index of the playlist slot to play by the controller.  This can be used to seek in the playlist.
        /// </description>
        /// <param name="index">Index of the playlist slot.</param>
        public void SetCurrentSlot(int index) {
             InternalUnsafeMethods.SetCurrentSlot__Args _args = new InternalUnsafeMethods.SetCurrentSlot__Args() {
                index = index,
             };
             InternalUnsafeMethods.SetCurrentSlot()(ObjectPtr, _args);
        }

        /// <description>
        /// Get the index of the playlist slot currently processed by the controller.
        /// </description>
        /// <returns>The slot index currently being played.</returns>
        /// <see cref="SFXPlayList" />
        public int GetCurrentSlot() {
             InternalUnsafeMethods.GetCurrentSlot__Args _args = new InternalUnsafeMethods.GetCurrentSlot__Args() {
             };
             int _engineResult = InternalUnsafeMethods.GetCurrentSlot()(ObjectPtr, _args);
             return _engineResult;
        }

        /// <description>
        /// Get the type info object for the SFXController class.
        /// </description>
        /// <returns>The type info object for SFXController</returns>
        public static EngineTypeInfo StaticGetType() {
             InternalUnsafeMethods.StaticGetType__Args _args = new InternalUnsafeMethods.StaticGetType__Args() {
             };
             IntPtr _engineResult = InternalUnsafeMethods.StaticGetType()(_args);
             return new EngineTypeInfo(_engineResult);
        }


        /// <value>
        /// <description>
        /// If true, the controller logs its operation to the console.
        /// This is a non-networked field that will work locally only.
        /// </description>
        /// </value>
        public bool Trace {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("trace"));
            set => SetFieldValue("trace", GenericMarshal.ToString(value));
        }
    }
}