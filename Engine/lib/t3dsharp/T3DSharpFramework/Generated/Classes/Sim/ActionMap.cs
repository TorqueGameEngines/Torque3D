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
    /// <summary>ActionMaps assign platform input events to console commands.</summary>
    /// <description>
    /// Any platform input event can be bound in a single, generic way. In theory, the game doesn't need to know if the event came from the keyboard, mouse, joystick or some other input device. This allows users of the game to map keys and actions according to their own preferences. Game action maps are arranged in a stack for processing so individual parts of the game can define specific actions. For example, when the player jumps into a vehicle it could push a vehicle action map and pop the default player action map.
    /// </description>
    /// <code>
    /// if ( isObject( moveMap ) )
    ///   moveMap.delete();
    /// new ActionMap(moveMap);
    /// </code>
    /// <code>
    /// // Simple function that prints to console
    /// // %val - Sent by the device letting the user know
    /// // if an input was pressed (true) or released (false)
    /// function testInput(%val)
    /// {
    ///    if(%val)
    ///     echo("Key is down");
    ///    else
    ///     echo("Key was released");
    /// }
    /// 
    /// // Bind the 'K' key to the testInput function
    /// moveMap.bind(keyboard, "k", testInput);
    /// </code>
    /// <code>
    /// // Print to the console when the spacebar is pressed
    /// function onSpaceDown()
    /// {
    ///    echo("Space bar down!");
    /// }
    /// 
    /// // Print to the console when the spacebar is released
    /// function onSpaceUp()
    /// {
    ///    echo("Space bar up!");
    /// }
    /// 
    /// // Bind the commands onSpaceDown and onSpaceUp to spacebar events
    /// moveMap.bindCmd(keyboard, "space", "onSpaceDown();", "onSpaceUp();");
    /// </code>
    /// <code>
    /// // Create the two ActionMaps
    /// if ( isObject( moveMap ) )
    ///   moveMap.delete();
    /// new ActionMap(moveMap);
    /// 
    /// if ( isObject( carMap ) )
    ///   carMap.delete();
    /// new ActionMap(carMap);
    /// </code>
    /// <code>
    /// // Print to the console the player is jumping
    /// function playerJump(%val)
    /// {
    ///    if(%val)
    ///     echo("Player jumping!");
    /// }
    /// 
    /// // Print to the console the vehicle is charging
    /// function turboCharge()
    /// {
    ///    if(%val)
    ///     echo("Vehicle turbo charging!");
    /// }
    /// </code>
    /// <code>
    /// // Bind the spacebar to the playerJump function
    /// // when moveMap is the active ActionMap
    /// moveMap.bind(keyboard, "space", playerJump);
    /// 
    /// // Bind the spacebar to the turboCharge function
    /// // when carMap is the active ActionMap
    /// carMap.bind(keyboard, "space", turboCharge);
    /// </code>
    /// <code>
    /// // Make moveMap the active action map
    /// // You should now be able to activate playerJump with spacebar
    /// moveMap.push();
    /// </code>
    /// <code>
    /// // Deactivate moveMap
    /// moveMap.pop();
    /// 
    /// // Activate carMap
    /// carMap.push();
    /// </code>
    public unsafe class ActionMap : SimObject {
        public ActionMap(bool pRegister = false) 
            : base(pRegister) {
        }
        
        public ActionMap(string pName, bool pRegister) 
            : this(false) {
            Name = pName;
            if (pRegister) {
                RegisterObject();
            }
        }
        
        public ActionMap(string pName) 
            : this(pName, false) {
        }
        
        public ActionMap(string pName, string pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(Engine.Sim.FindObject<SimObject>(pParent));
        }
        
        public ActionMap(string pName, SimObject pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(pParent);
        }
        
        public ActionMap(SimObject pObj) 
            : base(pObj) {
        }
        
        public ActionMap(IntPtr pObj) 
            : base(pObj) {
        }
        
		protected override void CreateObjectPtr()
		{
			ObjectPtr = InternalUnsafeMethods.Create()(new InternalUnsafeMethods.Create__Args());
		}

        #region UnsafeNativeMethods
        new internal struct InternalUnsafeMethods {
            [StructLayout(LayoutKind.Sequential)]
            internal struct GetDeadZone__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string device;
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string action;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            
            internal delegate IntPtr _GetDeadZone(IntPtr _this, GetDeadZone__Args args);
            private static _GetDeadZone _GetDeadZoneFunc;
            internal static _GetDeadZone GetDeadZone() {
                if (_GetDeadZoneFunc == null) {
                    _GetDeadZoneFunc =
                        (_GetDeadZone)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnActionMap_getDeadZone"), typeof(_GetDeadZone));
                }
                
                return _GetDeadZoneFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct GetScale__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string device;
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string action;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate float _GetScale(IntPtr _this, GetScale__Args args);
            private static _GetScale _GetScaleFunc;
            internal static _GetScale GetScale() {
                if (_GetScaleFunc == null) {
                    _GetScaleFunc =
                        (_GetScale)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnActionMap_getScale"), typeof(_GetScale));
                }
                
                return _GetScaleFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct IsInverted__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string device;
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string action;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            [return: MarshalAs(UnmanagedType.I1)]
            internal delegate bool _IsInverted(IntPtr _this, IsInverted__Args args);
            private static _IsInverted _IsInvertedFunc;
            internal static _IsInverted IsInverted() {
                if (_IsInvertedFunc == null) {
                    _IsInvertedFunc =
                        (_IsInverted)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnActionMap_isInverted"), typeof(_IsInverted));
                }
                
                return _IsInvertedFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct GetCommand__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string device;
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string action;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            
            internal delegate IntPtr _GetCommand(IntPtr _this, GetCommand__Args args);
            private static _GetCommand _GetCommandFunc;
            internal static _GetCommand GetCommand() {
                if (_GetCommandFunc == null) {
                    _GetCommandFunc =
                        (_GetCommand)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnActionMap_getCommand"), typeof(_GetCommand));
                }
                
                return _GetCommandFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct GetBinding__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string command;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            
            internal delegate IntPtr _GetBinding(IntPtr _this, GetBinding__Args args);
            private static _GetBinding _GetBindingFunc;
            internal static _GetBinding GetBinding() {
                if (_GetBindingFunc == null) {
                    _GetBindingFunc =
                        (_GetBinding)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnActionMap_getBinding"), typeof(_GetBinding));
                }
                
                return _GetBindingFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct Pop__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _Pop(IntPtr _this, Pop__Args args);
            private static _Pop _PopFunc;
            internal static _Pop Pop() {
                if (_PopFunc == null) {
                    _PopFunc =
                        (_Pop)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnActionMap_pop"), typeof(_Pop));
                }
                
                return _PopFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct Push__Args
            {
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _Push(IntPtr _this, Push__Args args);
            private static _Push _PushFunc;
            internal static _Push Push() {
                if (_PushFunc == null) {
                    _PushFunc =
                        (_Push)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnActionMap_push"), typeof(_Push));
                }
                
                return _PushFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct Save__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string fileName;
                [MarshalAs(UnmanagedType.I1)]
                internal bool append;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _Save(IntPtr _this, Save__Args args);
            private static _Save _SaveFunc;
            internal static _Save Save() {
                if (_SaveFunc == null) {
                    _SaveFunc =
                        (_Save)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnActionMap_save"), typeof(_Save));
                }
                
                return _SaveFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct UnbindObj__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string device;
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string action;
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string obj;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            [return: MarshalAs(UnmanagedType.I1)]
            internal delegate bool _UnbindObj(IntPtr _this, UnbindObj__Args args);
            private static _UnbindObj _UnbindObjFunc;
            internal static _UnbindObj UnbindObj() {
                if (_UnbindObjFunc == null) {
                    _UnbindObjFunc =
                        (_UnbindObj)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnActionMap_unbindObj"), typeof(_UnbindObj));
                }
                
                return _UnbindObjFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct Unbind__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string device;
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string action;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            [return: MarshalAs(UnmanagedType.I1)]
            internal delegate bool _Unbind(IntPtr _this, Unbind__Args args);
            private static _Unbind _UnbindFunc;
            internal static _Unbind Unbind() {
                if (_UnbindFunc == null) {
                    _UnbindFunc =
                        (_Unbind)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnActionMap_unbind"), typeof(_Unbind));
                }
                
                return _UnbindFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct BindHold__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string device;
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string action;
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string holdFunction;
                [MarshalAs(UnmanagedType.I1)]
                internal bool returnHoldTime;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _BindHold(IntPtr _this, BindHold__Args args);
            private static _BindHold _BindHoldFunc;
            internal static _BindHold BindHold() {
                if (_BindHoldFunc == null) {
                    _BindHoldFunc =
                        (_BindHold)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnActionMap_bindHold"), typeof(_BindHold));
                }
                
                return _BindHoldFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct BindContext__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string device;
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string action;
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string holdFunction;
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string tapFunction;
                internal uint holdTime;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            internal delegate void _BindContext(IntPtr _this, BindContext__Args args);
            private static _BindContext _BindContextFunc;
            internal static _BindContext BindContext() {
                if (_BindContextFunc == null) {
                    _BindContextFunc =
                        (_BindContext)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnActionMap_bindContext"), typeof(_BindContext));
                }
                
                return _BindContextFunc;
            }

            [StructLayout(LayoutKind.Sequential)]
            internal struct BindCmd__Args
            {
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string device;
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string action;
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string makeCmd;
                [MarshalAs(UnmanagedType.LPUTF8Str)]
                internal string breakCmd;
            }

            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            [return: MarshalAs(UnmanagedType.I1)]
            internal delegate bool _BindCmd(IntPtr _this, BindCmd__Args args);
            private static _BindCmd _BindCmdFunc;
            internal static _BindCmd BindCmd() {
                if (_BindCmdFunc == null) {
                    _BindCmdFunc =
                        (_BindCmd)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnActionMap_bindCmd"), typeof(_BindCmd));
                }
                
                return _BindCmdFunc;
            }


            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            [return: MarshalAs(UnmanagedType.I1)]
            internal delegate bool _BindObj(IntPtr _this, ref StringVector.InternalStruct args);
            private static _BindObj _BindObjFunc;
            internal static _BindObj BindObj() {
                if (_BindObjFunc == null) {
                    _BindObjFunc =
                        (_BindObj)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnActionMap_bindObj"), typeof(_BindObj));
                }
                
                return _BindObjFunc;
            }


            [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
            [return: MarshalAs(UnmanagedType.I1)]
            internal delegate bool _Bind(IntPtr _this, ref StringVector.InternalStruct args);
            private static _Bind _BindFunc;
            internal static _Bind Bind() {
                if (_BindFunc == null) {
                    _BindFunc =
                        (_Bind)Marshal.GetDelegateForFunctionPointer(
                            Torque3D.DllLoadUtils.GetProcAddress(
                                Torque3D.Torque3DLibHandle,
                                "fnActionMap_bind"), typeof(_Bind));
                }
                
                return _BindFunc;
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
                                "fnActionMap_staticGetType"), typeof(_StaticGetType));
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
                                "fnActionMap_create"), typeof(_Create));
                }
                
                return _CreateFunc;
            }
        }
        #endregion

        /// <summary>Gets the Dead zone for the specified device and action.</summary>
        /// <description>
        /// 
        /// </description>
        /// <param name="device">The device that was bound.  Can be a keyboard, mouse, joystick or a gamepad.</param>
        /// <param name="action">The device action that was bound. The action is dependant upon the device. Specify a key for keyboards.</param>
        /// <returns>The dead zone for the specified device and action. Returns "0 0" if there is no dead zone or an empty string("") if the mapping was not found.</returns>
        /// <code>
        /// %deadZone = moveMap.getDeadZone( "gamepad", "thumbrx");
        /// </code>
        public string GetDeadZone(string device, string action) {
             InternalUnsafeMethods.GetDeadZone__Args _args = new InternalUnsafeMethods.GetDeadZone__Args() {
                device = device,
                action = action,
             };
             IntPtr _engineResult = InternalUnsafeMethods.GetDeadZone()(ObjectPtr, _args);
             return StringMarshal.IntPtrToUtf8String(_engineResult);
        }

        /// <summary>Get any scaling on the specified device and action.</summary>
        /// <description>
        /// 
        /// </description>
        /// <param name="device">The device that was bound. Can be keyboard, mouse, joystick or gamepad.</param>
        /// <param name="action">The device action that was bound. The action is dependant upon the device. Specify a key for keyboards.</param>
        /// <returns>Any scaling applied to the specified device and action.</returns>
        /// <code>
        /// %scale = %moveMap.getScale( "gamepad", "thumbrx");
        /// </code>
        public float GetScale(string device, string action) {
             InternalUnsafeMethods.GetScale__Args _args = new InternalUnsafeMethods.GetScale__Args() {
                device = device,
                action = action,
             };
             float _engineResult = InternalUnsafeMethods.GetScale()(ObjectPtr, _args);
             return _engineResult;
        }

        /// <summary>Determines if the specified device and action is inverted.</summary>
        /// <description>
        /// Should only be used for scrolling devices or gamepad/joystick axes.
        /// </description>
        /// <param name="device">The device that was bound. Can be a keyboard, mouse, joystick or a gamepad.</param>
        /// <param name="action">The device action that was bound.  The action is dependant upon the device. Specify a key for keyboards.</param>
        /// <returns>True if the specified device and action is inverted.</returns>
        /// <code>
        /// %if ( moveMap.isInverted( "mouse", "xaxis"))
        ///    echo("Mouse's xAxis is inverted");
        /// </code>
        public bool IsInverted(string device, string action) {
             InternalUnsafeMethods.IsInverted__Args _args = new InternalUnsafeMethods.IsInverted__Args() {
                device = device,
                action = action,
             };
             bool _engineResult = InternalUnsafeMethods.IsInverted()(ObjectPtr, _args);
             return _engineResult;
        }

        /// <summary>Gets ActionMap command for the device and action.</summary>
        /// <description>
        /// 
        /// </description>
        /// <param name="device">The device that was bound. Can be a keyboard, mouse, joystick or a gamepad.</param>
        /// <param name="action">The device action that was bound.  The action is dependant upon the device. Specify a key for keyboards.</param>
        /// <returns>The command against the specified device and action.</returns>
        /// <code>
        /// // Find what function is bound to a device's action
        /// // In this example, "jump()" was assigned to the space key in another script
        /// %command = moveMap.getCommand("keyboard", "space");
        /// 
        /// // Should print "jump" in the console
        /// echo(%command)
        /// </code>
        public string GetCommand(string device, string action) {
             InternalUnsafeMethods.GetCommand__Args _args = new InternalUnsafeMethods.GetCommand__Args() {
                device = device,
                action = action,
             };
             IntPtr _engineResult = InternalUnsafeMethods.GetCommand()(ObjectPtr, _args);
             return StringMarshal.IntPtrToUtf8String(_engineResult);
        }

        /// <summary>Gets the ActionMap binding for the specified command.</summary>
        /// <description>
        /// Use getField() on the return value to get the device and action of the binding.
        /// </description>
        /// <param name="command">The function to search bindings for.</param>
        /// <returns>The binding against the specified command. Returns an empty string("") if a binding wasn't found.</returns>
        /// <code>
        /// // Find what the function "jump()" is bound to in moveMap
        /// %bind = moveMap.getBinding( "jump" );
        /// 
        /// if ( %bind !$= "" )
        /// {
        /// // Find out what device is used in the binding
        ///   %device = getField( %bind, 0 );
        /// 
        /// // Find out what action (such as a key) is used in the binding
        ///   %action = getField( %bind, 1 );
        /// }
        /// </code>
        /// <see cref="getField" />
        public string GetBinding(string command) {
             InternalUnsafeMethods.GetBinding__Args _args = new InternalUnsafeMethods.GetBinding__Args() {
                command = command,
             };
             IntPtr _engineResult = InternalUnsafeMethods.GetBinding()(ObjectPtr, _args);
             return StringMarshal.IntPtrToUtf8String(_engineResult);
        }

        /// <summary>Pop the ActionMap off the %ActionMap stack.</summary>
        /// <description>
        /// Deactivates an %ActionMap and removes it from the
        /// </description>
        /// <code>
        /// // Deactivate moveMap
        /// moveMap.pop();
        /// </code>
        /// <see cref="ActionMap" />
        public void Pop() {
             InternalUnsafeMethods.Pop__Args _args = new InternalUnsafeMethods.Pop__Args() {
             };
             InternalUnsafeMethods.Pop()(ObjectPtr, _args);
        }

        /// <summary>Push the ActionMap onto the %ActionMap stack.</summary>
        /// <description>
        /// Activates an ActionMap and placees it at the top of the ActionMap stack.
        /// </description>
        /// <code>
        /// // Make moveMap the active action map
        /// moveMap.push();
        /// </code>
        /// <see cref="ActionMap" />
        public void Push() {
             InternalUnsafeMethods.Push__Args _args = new InternalUnsafeMethods.Push__Args() {
             };
             InternalUnsafeMethods.Push()(ObjectPtr, _args);
        }

        /// <summary>Saves the ActionMap to a file or dumps it to the console.</summary>
        /// <description>
        /// 
        /// </description>
        /// <param name="fileName">The file path to save the ActionMap to. If a filename is not specified  the ActionMap will be dumped to the console.</param>
        /// <param name="append">Whether to write the ActionMap at the end of the file or overwrite it.</param>
        /// <code>
        /// // Write out the actionmap into the config.cs file
        /// moveMap.save( "scripts/client/config.cs" );
        /// </code>
        public void Save(string fileName = "", bool append = false) {
             InternalUnsafeMethods.Save__Args _args = new InternalUnsafeMethods.Save__Args() {
                fileName = fileName,
                append = append,
             };
             InternalUnsafeMethods.Save()(ObjectPtr, _args);
        }

        /// <summary>Remove any object-binding on an input device and action.</summary>
        /// <description>
        /// 
        /// </description>
        /// <param name="device">The device to bind to.  Can be keyboard, mouse, joystick or gamepad.</param>
        /// <param name="action">The device action to unbind from. The action is dependant upon the device. Specify a key for keyboards.</param>
        /// <param name="obj">The object to perform unbind against.</param>
        /// <returns>True if the unbind was successful, false if the device was unknown or description failed.</returns>
        /// <code>
        /// moveMap.unbindObj("keyboard", "numpad1", "rangeChange", %player);
        /// </code>
        public bool UnbindObj(string device, string action, string obj) {
             InternalUnsafeMethods.UnbindObj__Args _args = new InternalUnsafeMethods.UnbindObj__Args() {
                device = device,
                action = action,
                obj = obj,
             };
             bool _engineResult = InternalUnsafeMethods.UnbindObj()(ObjectPtr, _args);
             return _engineResult;
        }

        /// <summary>Removes the binding on an input device and action.</summary>
        /// <description>
        /// 
        /// </description>
        /// <param name="device">The device to unbind from. Can be a keyboard, mouse, joystick or a gamepad.</param>
        /// <param name="action">The device action to unbind from. The action is dependant upon the device. Specify a key for keyboards.</param>
        /// <returns>True if the unbind was successful, false if the device was unknown or description failed.</returns>
        /// <code>
        /// moveMap.unbind("keyboard", "space");
        /// </code>
        public bool Unbind(string device, string action) {
             InternalUnsafeMethods.Unbind__Args _args = new InternalUnsafeMethods.Unbind__Args() {
                device = device,
                action = action,
             };
             bool _engineResult = InternalUnsafeMethods.Unbind()(ObjectPtr, _args);
             return _engineResult;
        }

        /// <description>
        /// actionMap.bindCmd( device, action, holdFunction, returnHoldTime)
        /// </description>
        public void BindHold(string device = "", string action = "", string holdFunction = "", bool returnHoldTime = false) {
             InternalUnsafeMethods.BindHold__Args _args = new InternalUnsafeMethods.BindHold__Args() {
                device = device,
                action = action,
                holdFunction = holdFunction,
                returnHoldTime = returnHoldTime,
             };
             InternalUnsafeMethods.BindHold()(ObjectPtr, _args);
        }

        /// <description>
        /// actionMap.bindCmd( device, action, holdFunction, tapFunction, holdTime)
        /// </description>
        public void BindContext(string device = "", string action = "", string holdFunction = "", string tapFunction = "", uint holdTime = 0) {
             InternalUnsafeMethods.BindContext__Args _args = new InternalUnsafeMethods.BindContext__Args() {
                device = device,
                action = action,
                holdFunction = holdFunction,
                tapFunction = tapFunction,
                holdTime = holdTime,
             };
             InternalUnsafeMethods.BindContext()(ObjectPtr, _args);
        }

        /// <summary>Associates a make command and optional break command to a specified input device action.</summary>
        /// <description>
        /// Must include parenthesis and semicolon in the make and break command strings.
        /// </description>
        /// <param name="device">The device to bind to. Can be a keyboard, mouse, joystick or gamepad.</param>
        /// <param name="action">The device action to bind to. The action is dependant upon the device. Specify a key for keyboards.</param>
        /// <param name="makeCmd">The command to execute when the device/action is made.</param>
        /// <param name="breakCmd">[optional] The command to execute when the device or action is unmade.</param>
        /// <returns>True the bind was successful, false if the device was unknown or description failed.</returns>
        /// <code>
        /// // Print to the console when the spacebar is pressed
        /// function onSpaceDown()
        /// {
        ///    echo("Space bar down!");
        /// }
        /// 
        /// // Print to the console when the spacebar is released
        /// function onSpaceUp()
        /// {
        ///    echo("Space bar up!");
        /// }
        /// 
        /// // Bind the commands onSpaceDown() and onSpaceUp() to spacebar events
        /// 
        /// moveMap.bindCmd(keyboard, "space", "onSpaceDown();", "onSpaceUp();");
        /// </code>
        public bool BindCmd(string device, string action, string makeCmd, string breakCmd = "") {
             InternalUnsafeMethods.BindCmd__Args _args = new InternalUnsafeMethods.BindCmd__Args() {
                device = device,
                action = action,
                makeCmd = makeCmd,
                breakCmd = breakCmd,
             };
             bool _engineResult = InternalUnsafeMethods.BindCmd()(ObjectPtr, _args);
             return _engineResult;
        }

        /// <description>
        /// (device, action, [modifier, spec, mod...], command, object)
        /// </description>
        public bool BindObj(params string[] args) { 
            List<string> _argList = new List<string>() {"", ""};
            _argList.AddRange(args);

            StringVector nativeVecArgs = new StringVector {
                ElementCount = (uint)_argList.Count,
                Array = _argList.ToArray(),
                ArraySize = (uint)_argList.Count
            };
            nativeVecArgs.Alloc();
            bool _engineResult = InternalUnsafeMethods.BindObj()(ObjectPtr, ref nativeVecArgs.internalStruct);
            nativeVecArgs.Free();

            return _engineResult;
        }

        /// <description>
        /// actionMap.bind( device, action, [modifier, spec, mod...], command )
        /// </description>
        public bool Bind(params string[] args) { 
            List<string> _argList = new List<string>() {"", ""};
            _argList.AddRange(args);

            StringVector nativeVecArgs = new StringVector {
                ElementCount = (uint)_argList.Count,
                Array = _argList.ToArray(),
                ArraySize = (uint)_argList.Count
            };
            nativeVecArgs.Alloc();
            bool _engineResult = InternalUnsafeMethods.Bind()(ObjectPtr, ref nativeVecArgs.internalStruct);
            nativeVecArgs.Free();

            return _engineResult;
        }

        /// <description>
        /// Get the type info object for the ActionMap class.
        /// </description>
        /// <returns>The type info object for ActionMap</returns>
        public static EngineTypeInfo StaticGetType() {
             InternalUnsafeMethods.StaticGetType__Args _args = new InternalUnsafeMethods.StaticGetType__Args() {
             };
             IntPtr _engineResult = InternalUnsafeMethods.StaticGetType()(_args);
             return new EngineTypeInfo(_engineResult);
        }
    }
}