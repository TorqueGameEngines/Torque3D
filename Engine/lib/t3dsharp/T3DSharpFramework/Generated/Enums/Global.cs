namespace T3DSharpFramework.Generated.Enums.Global {
    /// 
    public enum VPathObjectOrientationType {
        FREE = 0, 
        INTERPOLATE = 1, 
        TOPATH = 2, 
        TOOBJECT = 3, 
        TOPOINT = 4 
    }

    /// 
    public enum VPathNodeOrientationType {
        FREE = 0, 
        TOPOINT = 1 
    }

    /// 
    public enum VPathEditorMode {
        GIZMO = 0, 
        ADDNODE = 1, 
        DELETENODE = 2 
    }

    /// 
    public enum VPathType {
        BEZIER = 1, 
        LINEAR = 0 
    }

    /// 
    public enum VScriptEventCommandType {
        EXPRESSION = 0, 
        METHOD = 1 
    }

    /// 
    public enum VDataTableDataType {
        EXPRESSION = 0, 
        STATIC = 1, 
        VARIABLE = 2 
    }

    /// 
    public enum VActionToggle {
        ON = 0, 
        OFF = 1 
    }

    /// <description>
    /// The method used to include water surfaces in the NavMesh.
    /// </description>
    public enum NavMeshWaterMethod {
        Ignore = 0, 
        Solid = 1, 
        Impassable = 2 
    }

    /// <description>
    /// The size of a cover point.
    /// </description>
    public enum CoverPointSize {
        Prone = 0, 
        Crouch = 1, 
        Stand = 2 
    }

    /// <description>
    /// Possible wave operation types.
    /// </description>
    public enum afxXM_WaveOpType {
        Add = 0, 
        Multiply = 1, 
        Replace = 2, 
        Mult = 1 
    }

    /// <description>
    /// Possible wave parameter types.
    /// </description>
    public enum afxXM_WaveParamType {
        None = 0, 
        Pos = 1, 
        Pos_x = 2, 
        Pos_y = 3, 
        Pos_z = 4, 
        Ori = 5, 
        Pos2 = 6, 
        Pos2_x = 7, 
        Pos2_y = 8, 
        Pos2_z = 9, 
        Scale = 10, 
        Scale_x = 11, 
        Scale_y = 12, 
        Scale_z = 13, 
        Color = 14, 
        Color_red = 15, 
        Color_green = 16, 
        Color_blue = 17, 
        Color_alpha = 18, 
        Vis = 19, 
        Position = 1, 
        Position_x = 2, 
        Position_y = 3, 
        Position_z = 4, 
        Orientation = 5, 
        Position2 = 6, 
        Position2_x = 7, 
        Position2_y = 8, 
        Position2_z = 9, 
        Color_r = 15, 
        Color_g = 16, 
        Color_b = 17, 
        Color_a = 18, 
        Visibility = 19 
    }

    /// <description>
    /// Possible waveform types.
    /// </description>
    public enum afxXM_WaveFormType {
        None = 0, 
        Sine = 1, 
        Square = 2, 
        Triangle = 3, 
        Sawtooth = 4, 
        Noise = 5, 
        One = 6 
    }

    /// <description>
    /// Possible box conform alignment types.
    /// </description>
    public enum afxXM_BoxConformType {
        Plusx = 0, 
        Minusx = 1, 
        Plusy = 2, 
        Minusy = 3, 
        Plusz = 4, 
        Minusz = 5, 
        X = 0, 
        Y = 2, 
        Z = 4 
    }

    /// <description>
    /// Possible loop types for an afxPath.
    /// </description>
    public enum afxPath3DLoopType {
        Constant = 0, 
        Cycle = 1, 
        Oscillate = 2 
    }

    /// <description>
    /// Possible particle pool types.
    /// </description>
    public enum afxParticlePool_PoolType {
        Normal = 0, 
        Twominuspass = 1, 
        Twopass = 1 
    }

    /// <description>
    /// Possible RPG spell target types.
    /// </description>
    public enum afxRPGMagicSpell_TargetType {
        Nothing = 0, 
        Self = 1, 
        Friend = 2, 
        Enemy = 3, 
        Corpse = 4, 
        Free = 5 
    }

    /// <description>
    /// Possible zodiac plane facing types.
    /// </description>
    public enum afxZodiacPlane_FacingType {
        Up = 0, 
        Down = 1, 
        Forward = 2, 
        Backward = 3, 
        Right = 4, 
        Left = 5, 
        Front = 2, 
        Back = 3 
    }

    /// <description>
    /// Possible zodiac blend types.
    /// </description>
    public enum afxZodiacPlane_BlendType {
        Normal = 0, 
        Additive = 1, 
        Subtractive = 2 
    }

    /// <description>
    /// Possible zodiac blend types.
    /// </description>
    public enum afxZodiac_BlendType {
        Normal = 0, 
        Additive = 1, 
        Subtractive = 2 
    }

    /// <description>
    /// Possible projectile launch direction types.
    /// </description>
    public enum afxProjectile_LaunchDirType {
        TowardPos2Constraint = 0, 
        OrientConstraint = 1, 
        LaunchDirField = 2 
    }

    /// <description>
    /// Possible player movement operation types.
    /// </description>
    public enum afxPlayerMovement_OpType {
        Add = 0, 
        Multiply = 1, 
        Replace = 2, 
        Mult = 1 
    }

    /// <description>
    /// Possible phrase effect types.
    /// </description>
    public enum afxPhraseEffect_PhraseType {
        Triggered = 0, 
        Continuous = 1 
    }

    /// <description>
    /// Possible phrase effect state types.
    /// </description>
    public enum afxPhraseEffect_StateType {
        On = 1, 
        Off = 2, 
        Both = 3 
    }

    /// <description>
    /// Possible phrase effect match types.
    /// </description>
    public enum afxPhraseEffect_MatchType {
        Any = 0, 
        All = 1 
    }

    /// <description>
    /// Possible particle emitter path origin types.
    /// </description>
    public enum afxParticleEmitterPath_OriginType {
        Origin = 0, 
        Point = 1, 
        Vector = 2, 
        Tangent = 3 
    }

    /// <description>
    /// Possible texture function types.
    /// </description>
    public enum afxBillboard_TexFuncType {
        Replace = 0, 
        Modulate = 1, 
        Add = 2 
    }

    /// <description>
    /// Possible blending types.
    /// </description>
    public enum afxBillboard_BlendStyle {
        NORMAL = 1, 
        ADDITIVE = 2, 
        SUBTRACTIVE = 3, 
        PREMULTALPHA = 4 
    }

    /// <description>
    /// An enumeration of battery levels of a joystick.
    /// </description>
    public enum SDLPowerEnum {
        Unknown = -1, 
        Empty = 0, 
        Low = 1, 
        Medium = 2, 
        Full = 3, 
        Wired = 4, 
        Max = 5 
    }

    /// <description>
    /// The type of device connected.
    /// </description>
    public enum SDLJoystickType {
        Unknown = 0, 
        Game_Controller = 1, 
        Wheel = 2, 
        Arcade_Stick = 3, 
        Flight_Stick = 4, 
        Dance_Pad = 5, 
        Guitar = 6, 
        Drum_Kit = 7, 
        Arcade_Pad = 8, 
        Throttle = 9 
    }

    /// <description>
    /// GuiSeparatorCtrl orientations
    /// </description>
    public enum GuiSeparatorType {
        Vertical = 0, 
        Horizontal = 1 
    }

    /// 
    public enum GuiParticleGraphType {
        Bar = 3, 
        Filled = 2, 
        Point = 0, 
        Polyline = 1 
    }

    /// <description>
    /// The charting style of a single plotting curve in a GuiGraphCtrl.
    /// </description>
    public enum GuiGraphType {
        Bar = 3, 
        Filled = 2, 
        Point = 0, 
        PolyLine = 1 
    }

    /// <description>
    /// Active brush mode type.
    /// </description>
    public enum ForestBrushMode {
        Paint = 0, 
        Erase = 1, 
        EraseSelected = 2 
    }

    /// <description>
    /// How to snap when snapping is enabled.
    /// </description>
    public enum WorldEditorAlignmentType {
        None = 0, 
        PlusX = 1, 
        PlusY = 2, 
        PlusZ = 3, 
        MinusX = 4, 
        MinusY = 5, 
        MinusZ = 6 
    }

    /// <description>
    /// How to drop objects when placed or dropped in the world.
    /// </description>
    public enum WorldEditorDropType {
        AtOrigin = 0, 
        AtCamera = 1, 
        AtCameraRot = 2, 
        BelowCamera = 3, 
        ScreenCenter = 4, 
        AtCentroid = 5, 
        ToTerrain = 6, 
        BelowSelection = 7, 
        AtGizmo = 8 
    }

    /// 
    public enum GizmoMode {
        None = 0, 
        Move = 1, 
        Rotate = 2, 
        Scale = 3 
    }

    /// <description>
    /// Whether the gizmo should be aligned with the world, or with the object.
    /// </description>
    public enum GizmoAlignment {
        World = 0, 
        Object = 1 
    }

    /// <description>
    /// Routine to use for converting Theora's Y'CbCr pixel format to RGB color space.
    /// </description>
    public enum GuiTheoraTranscoder {
        Auto = 0, 
        Generic = 1, 
        SSE2420RGBA = 2 
    }

    /// 
    public enum ShadowType {
        Spot = 0, 
        PSSM = 1, 
        DualParaboloidSinglePass = 3, 
        DualParaboloid = 4, 
        CubeMap = 5 
    }

    /// <description>
    /// The shadow filtering modes for Advanced Lighting shadows.
    /// </description>
    public enum ShadowFilterMode {
        None = 0, 
        SoftShadow = 1, 
        SoftShadowHighQuality = 2 
    }

    /// 
    public enum _TamlFormatMode {
        Xml = 1, 
        Binary = 2 
    }

    /// <description>
    /// Type of mesh data available in a shape.
    /// </description>
    public enum ImageAssetType {
        Albedo = 0, 
        Normal = 1, 
        PBRConfig = 2, 
        GUI = 3, 
        Roughness = 4, 
        AO = 5, 
        Metalness = 6, 
        Glow = 7, 
        Particle = 8, 
        Decal = 9, 
        Cubemap = 10 
    }

    /// <description>
    /// Type of mesh data available in a shape.
    /// </description>
    public enum ReflectionModeEnum {
        No_Reflections = 0, 
        Static_Cubemap = 1, 
        Baked_Cubemap = 2, 
        Dynamic_Cubemap = 5 
    }

    /// <description>
    /// Type of mesh data available in a shape.
    /// </description>
    public enum ReflectProbeType {
        Sphere = 1, 
        Box = 0 
    }

    /// <summary>How the weapons are linked to triggers for this TurretShape.</summary>
    /// <description>
    /// 
    /// </description>
    public enum TurretShapeFireLinkType {
        FireTogether = 0, 
        GroupedFire = 1, 
        IndividualFire = 2 
    }

    /// <description>
    /// How to handle the physics simulation with the client's and server.
    /// </description>
    public enum PhysicsSimType {
        ClientOnly = 0, 
        ServerOnly = 1, 
        ClientServer = 2 
    }

    /// <description>
    /// The type of visual blending style to apply to the particles.
    /// </description>
    public enum ParticleBlendStyle {
        NORMAL = 1, 
        ADDITIVE = 2, 
        SUBTRACTIVE = 3, 
        PREMULTALPHA = 4 
    }

    /// <description>
    /// Type of mesh data available in a shape.
    /// </description>
    public enum TSMeshType {
        None = 0, 
        Bounds = 1, 
        Collision_Mesh = 2, 
        Visible_Mesh = 3 
    }

    /// <summary>The type of light to attach to this ShapeBaseImage.</summary>
    /// <description>
    /// 
    /// </description>
    public enum ShapeBaseImageLightType {
        NoLight = 0, 
        ConstantLight = 1, 
        SpotLight = 2, 
        PulsingLight = 3, 
        WeaponFireLight = 4 
    }

    /// <summary>What kind of recoil this ShapeBaseImage should emit when fired.</summary>
    /// <description>
    /// 
    /// </description>
    public enum ShapeBaseImageRecoilState {
        NoRecoil = 0, 
        LightRecoil = 1, 
        MediumRecoil = 2, 
        HeavyRecoil = 3 
    }

    /// <summary>How the spin animation should be played.</summary>
    /// <description>
    /// 
    /// </description>
    public enum ShapeBaseImageSpinState {
        Ignore = 0, 
        Stop = 1, 
        SpinUp = 2, 
        SpinDown = 3, 
        FullSpeed = 4 
    }

    /// <summary>The loaded state of this ShapeBaseImage.</summary>
    /// <description>
    /// 
    /// </description>
    public enum ShapeBaseImageLoadedState {
        Ignore = 0, 
        Loaded = 1, 
        Empty = 2 
    }

    /// <summary>The pose of the Player.</summary>
    /// <description>
    /// 
    /// </description>
    public enum PlayerPose {
        Stand = 0, 
        Sprint = 1, 
        Crouch = 2, 
        Prone = 3, 
        Swim = 4 
    }

    /// <description>
    /// Possible physical zone force types.
    /// </description>
    public enum PhysicalZone_ForceType {
        Vector = 0, 
        Spherical = 1, 
        Cylindrical = 2, 
        Sphere = 1, 
        Cylinder = 2 
    }

    /// <summary>The type of light the Item has</summary>
    /// <description>
    /// 
    /// </description>
    public enum ItemLightType {
        NoLight = 0, 
        ConstantLight = 1, 
        PulsingLight = 2 
    }

    /// <description>
    /// Movement behavior type for Camera.
    /// </description>
    public enum CameraMotionMode {
        Stationary = 0, 
        FreeRotate = 1, 
        Fly = 2, 
        OrbitObject = 3, 
        OrbitPoint = 4, 
        TrackObject = 5, 
        Overhead = 6, 
        EditOrbit = 7 
    }

    /// <description>
    /// Specifies how the viewport should be set up for a PostEffect's target.
    /// </description>
    /// <remarks> Applies to both the diffuse target and the depth target (if defined).
    /// </remarks>
    public enum PFXTargetViewport {
        PFXTargetViewport_TargetSize = 0, 
        PFXTargetViewport_GFXViewport = 1, 
        PFXTargetViewport_NamedInTexture0 = 2 
    }

    /// <description>
    /// Describes when the target texture should be cleared
    /// </description>
    public enum PFXTargetClear {
        PFXTargetClear_None = 0, 
        PFXTargetClear_OnCreate = 1, 
        PFXTargetClear_OnDraw = 2 
    }

    /// <description>
    /// When to process this effect during the frame.
    /// </description>
    public enum PFXRenderTime {
        PFXBeforeBin = 0, 
        PFXAfterBin = 1, 
        PFXAfterDiffuse = 2, 
        PFXEndOfFrame = 3, 
        PFXTexGenOnDemand = 4 
    }

    /// <description>
    /// Style of rendering for a GuiTSCtrl.
    /// </description>
    public enum GuiTSRenderStyles {
        Standard = 0, 
        Stereo_side_by_side = 1, 
        Stereo_separate = 2 
    }

    /// 
    public enum TSShapeConstructorAnimType {
        Frames = 0, 
        Seconds = 1, 
        Milliseconds = 1000 
    }

    /// 
    public enum TSShapeConstructorLodType {
        DetectDTS = 0, 
        SingleSize = 1, 
        TrailingNumber = 2 
    }

    /// <description>
    /// Axis to use for upwards direction when importing from Collada.
    /// </description>
    public enum TSShapeConstructorUpAxis {
        X_AXIS = 0, 
        Y_AXIS = 1, 
        Z_AXIS = 2, 
        DEFAULT = 3 
    }

    /// <description>
    /// Description
    /// </description>
    public enum baseTexFormat {
        NONE = 0, 
        DDS = 1, 
        PNG = 2 
    }

    /// <description>
    /// The type of knot that this marker will be.
    /// </description>
    public enum MarkerKnotType {
        Normal = 0, 
        Position_Only = 1, 
        Kink = 2 
    }

    /// <description>
    /// The type of smoothing this marker will have for pathed objects.
    /// </description>
    public enum MarkerSmoothingType {
        Spline = 1, 
        Linear = 0 
    }

    /// <description>
    /// What size to render the target texture. Sizes are based on the Window the render is occuring in.
    /// </description>
    public enum RenderTexTargetSize {
        Windowsize = 0, 
        Windowsizescaled = 1, 
        Fixedsize = 2 
    }

    /// <description>
    /// When using the Wave material animation, one of these Wave Types will be used to determine the type of wave to display.
    /// </description>
    public enum MaterialWaveType {
        Sin = 0, 
        Triangle = 1, 
        Square = 2 
    }

    /// <description>
    /// The type of graphical blending operation to apply to this material
    /// </description>
    public enum MaterialBlendOp {
        None = 0, 
        Mul = 1, 
        PreMul = 2, 
        Add = 3, 
        AddAlpha = 4, 
        Sub = 5, 
        LerpAlpha = 6 
    }

    /// <description>
    /// The type of animation effect to apply to this material.
    /// </description>
    public enum MaterialAnimType {
        Scroll = 1, 
        Rotate = 2, 
        Wave = 4, 
        Scale = 8, 
        Sequence = 16 
    }

    /// 
    public enum GuiFontCharset {
        ANSI = 0, 
        SYMBOL = 1, 
        SHIFTJIS = 2, 
        HANGEUL = 3, 
        HANGUL = 4, 
        GB2312 = 5, 
        CHINESEBIG5 = 6, 
        OEM = 7, 
        JOHAB = 8, 
        HEBREW = 9, 
        ARABIC = 10, 
        GREEK = 11, 
        TURKISH = 12, 
        VIETNAMESE = 13, 
        THAI = 14, 
        EASTEUROPE = 15, 
        RUSSIAN = 16, 
        MAC = 17, 
        BALTIC = 18 
    }

    /// 
    public enum GuiAlignmentType {
        Left = 0, 
        Center = 2, 
        Right = 1, 
        Top = 3, 
        Bottom = 4 
    }

    /// <description>
    /// Vertical sizing behavior of a GuiControl.
    /// </description>
    public enum GuiVerticalSizing {
        Bottom = 0, 
        Height = 1, 
        Top = 2, 
        Center = 3, 
        Relative = 4, 
        AspectTop = 5, 
        AspectBottom = 6, 
        AspectCenter = 7, 
        WindowRelative = 8 
    }

    /// <description>
    /// Horizontal sizing behavior of a GuiControl.
    /// </description>
    public enum GuiHorizontalSizing {
        Right = 0, 
        Width = 1, 
        Left = 2, 
        Center = 3, 
        Relative = 4, 
        AspectLeft = 5, 
        AspectRight = 6, 
        AspectCenter = 7, 
        WindowRelative = 8 
    }

    /// 
    public enum GuiGradientPickMode {
        HorizColor = 0, 
        HorizAlpha = 1 
    }

    /// 
    public enum GuiColorPickMode {
        Pallete = 0, 
        HorizColor = 1, 
        VertColor = 2, 
        HorizBrightnessColor = 3, 
        VertBrightnessColor = 4, 
        BlendColor = 5, 
        HorizAlpha = 6, 
        VertAlpha = 7, 
        Dropper = 8 
    }

    /// <description>
    /// Where the control should put the tab headers for selecting individual pages.
    /// </description>
    public enum GuiTabPosition {
        Top = 0, 
        Bottom = 1 
    }

    /// <description>
    /// Determines how child controls are stacked vertically.
    /// </description>
    public enum GuiVerticalStackingType {
        Top_to_Bottom = 0, 
        Bottom_to_Top = 1 
    }

    /// <description>
    /// Determines how child controls are stacked horizontally.
    /// </description>
    public enum GuiHorizontalStackingType {
        Left_to_Right = 0, 
        Right_to_Left = 1 
    }

    /// <description>
    /// Stacking method used to position child controls.
    /// </description>
    public enum GuiStackingType {
        Vertical = 0, 
        Horizontal = 1, 
        Dynamic = 2 
    }

    /// <description>
    /// Which side of the splitter to keep at a fixed size (if any).
    /// </description>
    public enum GuiSplitFixedPanel {
        None = 0, 
        FirstPanel = 1, 
        SecondPanel = 2 
    }

    /// <description>
    /// Axis along which to divide the container's space.
    /// </description>
    public enum GuiSplitOrientation {
        Vertical = 0, 
        Horizontal = 1 
    }

    /// <description>
    /// Display behavior of a scroll bar.  Determines when a scrollbar will be visible.
    /// </description>
    public enum GuiScrollBarBehavior {
        AlwaysOn = 0, 
        AlwaysOff = 1, 
        Dynamic = 2 
    }

    /// 
    public enum GuiFrameState {
        AlwaysOn = 0, 
        AlwaysOff = 1, 
        Dynamic = 2 
    }

    /// 
    public enum GuiDockingType {
        None = 1, 
        Client = 2, 
        Top = 4, 
        Bottom = 8, 
        Left = 16, 
        Right = 32 
    }

    /// <description>
    /// Direction in which to scroll the child control.
    /// </description>
    public enum GuiAutoScrollDirection {
        Up = 0, 
        Down = 1, 
        Left = 2, 
        Right = 3 
    }

    /// 
    public enum GuiIconButtonIconLocation {
        None = 0, 
        Left = 1, 
        Right = 2, 
        Center = 3 
    }

    /// 
    public enum GuiIconButtonTextLocation {
        None = 0, 
        Bottom = 1, 
        Right = 2, 
        Top = 3, 
        Left = 4, 
        Center = 5 
    }

    /// <description>
    /// Type of button control.
    /// </description>
    public enum GuiButtonType {
        PushButton = 0, 
        ToggleButton = 1, 
        RadioButton = 2 
    }

    /// <description>
    /// Rendering behavior when placing bitmaps in controls.
    /// </description>
    public enum GuiBitmapMode {
        Stretched = 0, 
        Centered = 1 
    }

    /// <description>
    /// The blend operators.
    /// </description>
    public enum GFXBlendOp {
        GFXBlendOpAdd = 0, 
        GFXBlendOpSubtract = 1, 
        GFXBlendOpRevSubtract = 2, 
        GFXBlendOpMin = 3, 
        GFXBlendOpMax = 4 
    }

    /// <description>
    /// The stencil operators.
    /// </description>
    public enum GFXStencilOp {
        GFXStencilOpKeep = 0, 
        GFXStencilOpZero = 1, 
        GFXStencilOpReplace = 2, 
        GFXStencilOpIncrSat = 3, 
        GFXStencilOpDecrSat = 4, 
        GFXStencilOpInvert = 5, 
        GFXStencilOpIncr = 6, 
        GFXStencilOpDecr = 7 
    }

    /// <description>
    /// The render cull modes.
    /// </description>
    public enum GFXCullMode {
        GFXCullNone = 0, 
        GFXCullCW = 1, 
        GFXCullCCW = 2 
    }

    /// <description>
    /// The texture formats.
    /// </description>
    /// <remarks> Not all formats are supported on all platforms.
    /// </remarks>
    public enum GFXFormat {
        GFXFormatR8G8B8 = 10, 
        GFXFormatR8G8B8A8 = 12, 
        GFXFormatR8G8B8A8_SRGB = 15, 
        GFXFormatR8G8B8X8 = 13, 
        GFXFormatR32F = 16, 
        GFXFormatR5G6B5 = 3, 
        GFXFormatR5G5B5A1 = 4, 
        GFXFormatR5G5B5X1 = 5, 
        GFXFormatA4L4 = 2, 
        GFXFormatA8L8 = 6, 
        GFXFormatA8 = 0, 
        GFXFormatL8 = 1, 
        GFXFormatBC1 = 29, 
        GFXFormatBC2 = 30, 
        GFXFormatBC3 = 31, 
        GFXFormatBC4 = 32, 
        GFXFormatBC5 = 33, 
        GFXFormatD32 = 21, 
        GFXFormatD24X8 = 22, 
        GFXFormatD24S8 = 23, 
        GFXFormatD24FS8 = 24, 
        GFXFormatD16 = 9, 
        GFXFormatR32G32B32A32F = 28, 
        GFXFormatR16G16B16A16F = 27, 
        GFXFormatL16 = 7, 
        GFXFormatR16G16B16A16 = 26, 
        GFXFormatR16G16 = 17, 
        GFXFormatR16F = 8, 
        GFXFormatR16G16F = 18, 
        GFXFormatR10G10B10A2 = 19 
    }

    /// <description>
    /// The texture transform state flags.
    /// </description>
    public enum GFXTextureTransformFlags {
        GFXTTFDisable = 0, 
        GFXTTFFCoord1D = 1, 
        GFXTTFFCoord2D = 2, 
        GFXTTFFCoord3D = 3, 
        GFXTTFFCoord4D = 4, 
        GFXTTFProjected = 256 
    }

    /// <description>
    /// The texture arguments.
    /// </description>
    public enum GFXTextureArgument {
        GFXTADiffuse = 0, 
        GFXTACurrent = 1, 
        GFXTATexture = 2, 
        GFXTATFactor = 3, 
        GFXTASpecular = 4, 
        GFXTATemp = 5, 
        GFXTAConstant = 6, 
        OneMinus = 16, 
        AlphaReplicate = 32 
    }

    /// <description>
    /// The texture operators.
    /// </description>
    public enum GFXTextureOp {
        GFXTOPDisable = 0, 
        GFXTOPSelectARG1 = 1, 
        GFXTOPSelectARG2 = 2, 
        GFXTOPModulate = 3, 
        GFXTOPModulate2X = 4, 
        GFXTOPModulate4X = 5, 
        GFXTOPAdd = 6, 
        GFXTOPAddSigned = 7, 
        GFXTOPAddSigned2X = 8, 
        GFXTOPSubtract = 9, 
        GFXTOPAddSmooth = 10, 
        GFXTOPBlendDiffuseAlpha = 11, 
        GFXTOPBlendTextureAlpha = 12, 
        GFXTOPBlendFactorAlpha = 13, 
        GFXTOPBlendTextureAlphaPM = 14, 
        GFXTOPBlendCURRENTALPHA = 15, 
        GFXTOPPreModulate = 16, 
        GFXTOPModulateAlphaAddColor = 17, 
        GFXTOPModulateColorAddAlpha = 18, 
        GFXTOPModulateInvAlphaAddColor = 19, 
        GFXTOPModulateInvColorAddAlpha = 20, 
        GFXTOPBumpEnvMap = 21, 
        GFXTOPBumpEnvMapLuminance = 22, 
        GFXTOPDotProduct3 = 23, 
        GFXTOPLERP = 24 
    }

    /// <description>
    /// The texture filter types.
    /// </description>
    public enum GFXTextureFilterType {
        GFXTextureFilterNone = 0, 
        GFXTextureFilterPoint = 1, 
        GFXTextureFilterLinear = 2, 
        GFXTextureFilterAnisotropic = 3, 
        GFXTextureFilterPyramidalQuad = 4, 
        GFXTextureFilterGaussianQuad = 5 
    }

    /// <description>
    /// The texture address modes.
    /// </description>
    public enum GFXTextureAddressMode {
        GFXAddressWrap = 0, 
        GFXAddressMirror = 1, 
        GFXAddressClamp = 2, 
        GFXAddressBorder = 3, 
        GFXAddressMirrorOnce = 4 
    }

    /// <description>
    /// The supported comparison functions.
    /// </description>
    public enum GFXCmpFunc {
        GFXCmpNever = 0, 
        GFXCmpLess = 1, 
        GFXCmpEqual = 2, 
        GFXCmpLessEqual = 3, 
        GFXCmpGreater = 4, 
        GFXCmpNotEqual = 5, 
        GFXCmpGreaterEqual = 6, 
        GFXCmpAlways = 7 
    }

    /// <description>
    /// The supported blend modes.
    /// </description>
    public enum GFXBlend {
        GFXBlendZero = 0, 
        GFXBlendOne = 1, 
        GFXBlendSrcColor = 2, 
        GFXBlendInvSrcColor = 3, 
        GFXBlendSrcAlpha = 4, 
        GFXBlendInvSrcAlpha = 5, 
        GFXBlendDestAlpha = 6, 
        GFXBlendInvDestAlpha = 7, 
        GFXBlendDestColor = 8, 
        GFXBlendInvDestColor = 9, 
        GFXBlendSrcAlphaSat = 10 
    }

    /// <description>
    /// Back-end graphics API used by the GFX subsystem.
    /// </description>
    public enum GFXAdapterType {
        OpenGL = 0, 
        D3D11 = 1, 
        NullDevice = 2 
    }

    /// <description>
    /// Return value for messageBox() indicating which button was pressed by the user.
    /// </description>
    public enum MBReturnVal {
        OK = 1, 
        Cancelled = 2, 
        Retry = 3, 
        DontSave = 4 
    }

    /// <description>
    /// What icon to show on a message box.
    /// </description>
    public enum MBIcons {
        Information = 1, 
        Warning = 0, 
        Stop = 3, 
        Question = 2 
    }

    /// <description>
    /// Which buttons to display on a message box.
    /// </description>
    public enum MBButtons {
        Ok = 0, 
        OkCancel = 1, 
        RetryCancel = 2, 
        SaveDontSave = 3, 
        SaveDontSaveCancel = 4 
    }

    /// <summary>Priority levels for logging entries</summary>
    /// <description>
    /// 
    /// </description>
    public enum LogLevel {
        Normal = 0, 
        Warning = 1, 
        Error = 2 
    }

    /// <description>
    /// Channels are individual properties of sound sources that may be animated over time.
    /// </description>
    /// <see cref="SFXParameter" />
    public enum SFXChannel {
        Volume = 0, 
        Pitch = 1, 
        Priority = 2, 
        PositionX = 3, 
        PositionY = 4, 
        PositionZ = 5, 
        RotationX = 6, 
        RotationY = 7, 
        RotationZ = 8, 
        VelocityX = 9, 
        VelocityY = 10, 
        VelocityZ = 11, 
        ReferenceDistance = 12, 
        MaxDistance = 13, 
        ConeInsideAngle = 14, 
        ConeOutsideAngle = 15, 
        ConeOutsideVolume = 16, 
        Cursor = 17, 
        Status = 18, 
        User0 = 19, 
        User1 = 20, 
        User2 = 21, 
        User3 = 22 
    }

    /// <description>
    /// Type of volume distance attenuation curve.
    /// The distance model determines the falloff curve applied to the volume of 3D sounds over distance.
    /// </description>
    public enum SFXDistanceModel {
        Linear = 0, 
        Logarithmic = 1, 
        Exponential = 2 
    }

    /// <description>
    /// Playback status of sound source.
    /// </description>
    public enum SFXStatus {
        Playing = 1, 
        Stopped = 2, 
        Paused = 3 
    }

    /// <description>
    /// Reaction behavior when a state is changed incompatibly on a slot that has already started playing.
    /// </description>
    /// <see cref="SFXPlayList::stateMode" />
    public enum SFXPlayListStateMode {
        StopWhenDeactivated = 0, 
        PauseWhenDeactivated = 1, 
        IgnoreWhenDeactivated = 2 
    }

    /// <description>
    /// Behavior when hitting the play stage of a slot that is still playing from a previous cycle.
    /// </description>
    /// <see cref="SFXPlayList::replay" />
    public enum SFXPlayListReplayMode {
        IgnorePlaying = 0, 
        RestartPlaying = 1, 
        KeepPlaying = 2, 
        StartNew = 3, 
        SkipIfPlaying = 4 
    }

    /// <description>
    /// Playlist behavior when transitioning in and out of invididual slots.
    /// 
    /// Transition behaviors apply when the playback controller starts processing a playlist slot and when it ends processing a slot.  Using transition behaviors, playback can be synchronized.
    /// </description>
    /// <see cref="SFXPlayList::transitionIn" />
    /// <see cref="SFXPlayList::transitionOut" />
    public enum SFXPlayListTransitionMode {
        None = 0, 
        Wait = 1, 
        WaitAll = 2, 
        Stop = 3, 
        StopAll = 4 
    }

    /// <description>
    /// Randomization pattern to apply to playlist slot playback order.
    /// </description>
    /// <see cref="SFXPlayList::random" />
    public enum SFXPlayListRandomMode {
        NotRandom = 0, 
        StrictRandom = 1, 
        OrderedRandom = 2 
    }

    /// <description>
    /// Playlist behavior when description is set to loop.
    /// </description>
    /// <see cref="SFXDescription::isLooping" />
    /// <see cref="SFXPlayList::loopMode" />
    public enum SFXPlayListLoopMode {
        All = 0, 
        Single = 1 
    }
}