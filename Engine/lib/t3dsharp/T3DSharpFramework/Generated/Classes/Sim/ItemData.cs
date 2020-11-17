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
    /// <summary>Stores properties for an individual Item type.</summary>
    /// <description>
    /// Items represent an object in the world, usually one that the player will interact with.  One example is a health kit on the group that is automatically picked up when the player comes into contact with it.
    /// 
    /// ItemData provides the common properties for a set of Items.  These properties include a DTS or DAE model used to render the Item in the world, its physical properties for when the Item interacts with the world (such as being tossed by the player), and any lights that emit from the Item.
    /// </description>
    /// <code>
    /// datablock ItemData(HealthKitSmall)
    /// {
    ///    category ="Health";
    ///    className = "HealthPatch";
    ///    shapeFile = "art/shapes/items/kit/healthkit.dts";
    ///    gravityMod = "1.0";
    ///    mass = 2;
    ///    friction = 1;
    ///    elasticity = 0.3;
    ///    density = 2;
    ///    drag = 0.5;
    ///    maxVelocity = "10.0";
    ///    emap = true;
    ///    sticky = false;
    ///    dynamicType = "0"
    /// ;   lightOnlyStatic = false;
    ///    lightType = "NoLight";
    ///    lightColor = "1.0 1.0 1.0 1.0";
    ///    lightTime = 1000;
    ///    lightRadius = 10.0;
    ///    simpleServerCollision = true;   // Dynamic properties used by the scripts
    /// 
    ///    pickupName = "a small health kit";
    ///    repairAmount = 50;
    /// };
    /// </code>
    public unsafe class ItemData : ShapeBaseData {
        public ItemData(bool pRegister = false) 
            : base(pRegister) {
        }
        
        public ItemData(string pName, bool pRegister) 
            : this(false) {
            Name = pName;
            if (pRegister) {
                RegisterObject();
            }
        }
        
        public ItemData(string pName) 
            : this(pName, false) {
        }
        
        public ItemData(string pName, string pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(Engine.Sim.FindObject<SimObject>(pParent));
        }
        
        public ItemData(string pName, SimObject pParent, bool pRegister = false) 
            : this(pName, pRegister) {
            CopyFrom(pParent);
        }
        
        public ItemData(SimObject pObj) 
            : base(pObj) {
        }
        
        public ItemData(IntPtr pObj) 
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
                                "fnItemData_staticGetType"), typeof(_StaticGetType));
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
                                "fnItemData_create"), typeof(_Create));
                }
                
                return _CreateFunc;
            }
        }
        #endregion

        /// <description>
        /// Get the type info object for the ItemData class.
        /// </description>
        /// <returns>The type info object for ItemData</returns>
        public static EngineTypeInfo StaticGetType() {
             InternalUnsafeMethods.StaticGetType__Args _args = new InternalUnsafeMethods.StaticGetType__Args() {
             };
             IntPtr _engineResult = InternalUnsafeMethods.StaticGetType()(_args);
             return new EngineTypeInfo(_engineResult);
        }


        /// <value>
        /// <description>
        /// A floating-point value specifying how much velocity is lost to impact and sliding friction.
        /// </description>
        /// </value>
        public float Friction {
            get => GenericMarshal.StringTo<float>(GetFieldValue("friction"));
            set => SetFieldValue("friction", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// A floating-point value specifying how 'bouncy' this ItemData is.
        /// </description>
        /// </value>
        public float Elasticity {
            get => GenericMarshal.StringTo<float>(GetFieldValue("elasticity"));
            set => SetFieldValue("elasticity", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <summary>If true, ItemData will 'stick' to any surface it collides with.</summary>
        /// <description>
        /// When an item does stick to a surface, the Item::onStickyCollision() callback is called.  The Item has methods to retrieve the world position and normal the Item is stuck to.
        /// </description>
        /// <remarks> Valid objects to stick to must be of StaticShapeObjectType.
        /// </remarks>
        /// </value>
        public bool Sticky {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("sticky"));
            set => SetFieldValue("sticky", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Floating point value to multiply the existing gravity with, just for this ItemData.
        /// </description>
        /// </value>
        public float GravityMod {
            get => GenericMarshal.StringTo<float>(GetFieldValue("gravityMod"));
            set => SetFieldValue("gravityMod", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Maximum velocity that this ItemData is able to move.
        /// </description>
        /// </value>
        public float MaxVelocity {
            get => GenericMarshal.StringTo<float>(GetFieldValue("maxVelocity"));
            set => SetFieldValue("maxVelocity", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <description>
        /// Type of light to apply to this ItemData. Options are NoLight, ConstantLight, PulsingLight. Default is NoLight.
        /// </description>
        /// </value>
        public ItemLightType LightType {
            get => GenericMarshal.StringTo<ItemLightType>(GetFieldValue("lightType"));
            set => SetFieldValue("lightType", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <summary>Color value to make this light. Example: "1.0,1.0,1.0"</summary>
        /// <description>
        /// 
        /// </description>
        /// <see cref="lightType" />
        /// </value>
        public LinearColorF LightColor {
            get => GenericMarshal.StringTo<LinearColorF>(GetFieldValue("lightColor"));
            set => SetFieldValue("lightColor", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <summary>Time value for the light of this ItemData, used to control the pulse speed of the PulsingLight LightType.</summary>
        /// <description>
        /// 
        /// </description>
        /// <see cref="lightType" />
        /// </value>
        public int LightTime {
            get => GenericMarshal.StringTo<int>(GetFieldValue("lightTime"));
            set => SetFieldValue("lightTime", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <summary>Distance from the center point of this ItemData for the light to affect</summary>
        /// <description>
        /// 
        /// </description>
        /// <see cref="lightType" />
        /// </value>
        public float LightRadius {
            get => GenericMarshal.StringTo<float>(GetFieldValue("lightRadius"));
            set => SetFieldValue("lightRadius", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <summary>If true, this ItemData will only cast a light if the Item for this ItemData has a static value of true.</summary>
        /// <description>
        /// 
        /// </description>
        /// <see cref="lightType" />
        /// </value>
        public bool LightOnlyStatic {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("lightOnlyStatic"));
            set => SetFieldValue("lightOnlyStatic", GenericMarshal.ToString(value));
        }


        /// <value>
        /// <summary>Determines if only simple server-side collision will be used (for pick ups).</summary>
        /// <description>
        /// If set to true then only simple, server-side collision detection will be used.  This is often the case if the item is used for a pick up object, such as ammo.  If set to false then a full collision volume will be used as defined by the shape.  The default is true.
        /// </description>
        /// <remarks> Only applies when using a physics library.
        /// </remarks>
        /// <see cref="TurretShape and ProximityMine for examples that should set this to false to allow them to be shot by projectiles." />
        /// </value>
        public bool SimpleServerCollision {
            get => GenericMarshal.StringTo<bool>(GetFieldValue("simpleServerCollision"));
            set => SetFieldValue("simpleServerCollision", GenericMarshal.ToString(value));
        }
    }
}