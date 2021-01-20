datablock ReflectorDesc( DefaultCubeDesc )
{  
   texSize = 64;
   nearDist = 0.1;
   farDist = 1000.0;
   objectTypeMask = 0xFFFFFFFF;
   detailAdjust = 1.0;
   priority = 1.0;
   maxRateMs = 15;
   useOcclusionQuery = true;
};

datablock ParticleEmitterNodeData(DefaultEmitterNodeData)
{
   timeMultiple = 1;
};


datablock ParticleData(DefaultParticle)
{
   textureName = "core/gameObjects/images/defaultParticle";
   dragCoefficient = 0.498534;
   gravityCoefficient = 0;
   inheritedVelFactor = 0.499022;
   constantAcceleration = 0.0;
   lifetimeMS = 1313;
   lifetimeVarianceMS = 500;
   useInvAlpha = true;
   spinRandomMin = -360;
   spinRandomMax = 360;
   spinSpeed = 1;

   colors[0] = "0.992126 0.00787402 0.0314961 1";
   colors[1] = "1 0.834646 0 0.645669";
   colors[2] = "1 0.299213 0 0.330709";
   colors[3] = "0.732283 1 0 0";
   
   sizes[0] = 0;
   sizes[1] = 0.497467;
   sizes[2] = 0.73857;
   sizes[3] = 0.997986;
   
   times[0] = 0.0;
   times[1] = 0.247059;
   times[2] = 0.494118;
   times[3] = 1;
   
   animTexName = "core/gameObjects/images/defaultParticle";
};

datablock ParticleEmitterData(DefaultEmitter)
{
   ejectionPeriodMS = "50";
   ejectionVelocity = "1";
   velocityVariance = "0";
   ejectionOffset = "0.2";
   thetaMax = "40";
   particles = "DefaultParticle";
   blendStyle = "ADDITIVE";
   softParticles = "0";
   softnessDistance = "1";
};

//-----------------------------------------------------------------------------
// DefaultTrigger is used by the mission editor.  This is also an example
// of trigger methods and callbacks.

datablock TriggerData(DefaultTrigger)
{
   // The period is value is used to control how often the console
   // onTriggerTick callback is called while there are any objects
   // in the trigger.  The default value is 100 MS.
   tickPeriodMS = 100;
};

datablock TriggerData(ClientTrigger : DefaultTrigger)
{
   clientSide = true;
};

datablock RibbonNodeData(DefaultRibbonNodeData)
{
   timeMultiple = 1.0;
};

//ribbon data////////////////////////////////////////

datablock RibbonData(BasicRibbon)
{
   size[0] = 0.5;
   color[0] = "1.0 0.0 0.0 1.0";
   position[0] = 0.0;
 
   size[1] = 0.0;
   color[1] = "1.0 0.0 0.0 0.0";
   position[1] = 1.0;
 
   RibbonLength = 40;
   fadeAwayStep = 0.1;
   UseFadeOut = true;
   RibbonMaterial = BasicRibbonMat;

   category = "FX";
};

datablock RibbonData(TexturedRibbon)
{
   RibbonMaterial = TexturedRibbonMat;
   size[0] = 0.5;
   color[0] = "1.0 1.0 1.0 1.0";
   position[0] = 0.0;
 
   size[1] = 0.5;
   color[1] = "1.0 1.0 1.0 1.0";
   position[1] = 1.0;
 
   RibbonLength = 40;
   fadeAwayStep = 0.1;
   UseFadeOut = true;
   tileScale = 1;
   fixedTexCoords = true;
   TexcoordsRelativeToDistance = true;

   category = "FX";
};

datablock MissionMarkerData(WayPointMarker)
{
   category = "Misc";
   shapeFile = "core/gameObjects/shapes/octahedron.dts";
};

datablock MissionMarkerData(SpawnSphereMarker)
{
   category = "Misc";
   shapeFile = "core/gameObjects/shapes/octahedron.dts";
};

datablock MissionMarkerData(CameraBookmarkMarker)
{
   category = "Misc";
   shapeFile = "core/gameObjects/shapes/camera.dts";
};

datablock CameraData(Observer)
{
   mode = "Observer";
};

datablock LightAnimData( NullLightAnim )
{   
   animEnabled = false;
};

datablock LightAnimData( PulseLightAnim )
{   
   brightnessA = 0;
   brightnessZ = 1;
   brightnessPeriod = 1;
   brightnessKeys = "aza";
   brightnessSmooth = true;
};

datablock LightAnimData( SpinLightAnim )
{
   rotA[2] = "0";
   rotZ[2] = "360";
   rotPeriod[2] = "1";
   rotKeys[2] = "az";
   rotSmooth[2] = true;
};
