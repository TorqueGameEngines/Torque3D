//-----------------------------------------------------------------------------
// Lifelike Effects Pack - Small Ground Explosion
// Copyright Adam deGrandis 2012
//
// Thanks for your support!
//
//-----------------------------------------------------------------------------
//exec ("art/datablocks/LifelikeEffectsPack/LifelikeExp_GroundHitSmall.cs");


//-----------------------------------------------------------------------------
//	Emitters
//-----------------------------------------------------------------------------


datablock ParticleData(LifelikeGroundHitSmallPointBurstParticle)
{
   textureName          = "art/shapes/particles/LifelikeEffectsPack/PointBurst";
   lifetimeMS           = 350;
   lifetimeVarianceMS   = 0;
   spinRandomMin = -20.0;
   spinRandomMax =  20.0;

   colors[0]     = "1.0 0.9 0.8 1";
   colors[1]     = "0.8 0.4 0.0 0.2";
   colors[2]     = "0.8 0.4 0.0 0.0";

   sizes[0]      = 4;
   sizes[1]      = 13;
   sizes[2]      = 1;

   times[0]      = 0.0;
   times[1]      = 0.1;
   times[2]      = 1.0;
};

datablock ParticleEmitterData(LifelikeGroundHitSmallPointBurstEmitter)
{
   ejectionPeriodMS = 60;
   periodVarianceMS = 5;
   ejectionVelocity = 0;
   velocityVariance = 0;
   thetaMin         = 0;
   thetaMax         = 120;
   phiReferenceVel  = 0;
   phiVariance      = 360;
   ejectionoffset   = 0;
   particles = "LifelikeGroundHitSmallPointBurstParticle";
   blendStyle = "ADDITIVE";
};


datablock ParticleData(LifelikeGroundHitSmallSmokeParticle)
{
   textureName          = "art/shapes/particles/LifelikeEffectsPack/smoke2";
   gravityCoefficient   = 0.5;
   lifetimeMS           = 1500;
   lifetimeVarianceMS   = 500;
   spinRandomMin = -50.0;
   spinRandomMax =  50.0;

   colors[0]     = "0.3 0.2 0.1 0";
   colors[1]     = "0.6 0.5 0.4 1";
   colors[2]     = "0.6 0.5 0.4 0";

   sizes[0]      = 2;
   sizes[1]      = 7;
   sizes[2]      = 12.5;

   times[0]      = 0.0;
   times[1]      = 0.1;
   times[2]      = 1.0;
};

datablock ParticleEmitterData(LifelikeGroundHitSmallSmokeEmitter)
{
   ejectionPeriodMS = 40;
   periodVarianceMS = 5;
   ejectionVelocity = 6;
   velocityVariance = 3;
   thetaMin         = 0;
   thetaMax         = 50;
   phiReferenceVel  = 0;
   phiVariance      = 360;
   ejectionoffset   = 0;
   particles = "LifelikeGroundHitSmallSmokeParticle";
   blendStyle = "NORMAL";
};


datablock ParticleData(LifelikeGroundHitSmallDirtDebrisParticle)
{
   textureName          = "art/shapes/particles/LifelikeEffectsPack/dirtDebris";
   //dragCoefficient      = 4;
   gravityCoefficient   = 3;
   lifetimeMS           = 1200;
   lifetimeVarianceMS   = 500;
   spinRandomMin = -40.0;
   spinRandomMax =  40.0;

   colors[0]     = "1 1 1 1";
   colors[1]     = "1.0 0.9 0.8 1";
   colors[2]     = "0.9 0.8 0.7 0";

   sizes[0]      = 2;
   sizes[1]      = 5;
   sizes[2]      = 7;

   times[0]      = 0.0;
   times[1]      = 0.2;
   times[2]      = 1.0;
};

datablock ParticleEmitterData(LifelikeGroundHitSmallDirtDebrisEmitter)
{
   ejectionPeriodMS = 10;
   periodVarianceMS = 1;
   ejectionVelocity = 20.0;
   velocityVariance = 7.0;
   ejectionOffset   = 0;
   thetaMin         = 0;
   thetaMax         = 40;
   phiReferenceVel  = 0;
   phiVariance      = 360;
   particles = "LifelikeGroundHitSmallDirtDebrisParticle";
   blendStyle = "NORMAL";
};


datablock ParticleData(LifelikeGroundHitSmallDirtBlastParticle)
{
   textureName          = "art/shapes/particles/LifelikeEffectsPack/dirtBlast1";
   lifetimeMS           = 800;
   lifetimeVarianceMS   = 50;
   gravityCoefficient   = 1;

   colors[0]     = "0.6 0.5 0.4 1";
   colors[1]     = "0.6 0.5 0.4 1";
   colors[2]     = "0.6 0.5 0.4 0";

   sizes[0]      = 1;
   sizes[1]      = 10;
   sizes[2]      = 13;

   times[0]      = 0.0;
   times[1]      = 0.2;
   times[2]      = 1.0;
};

datablock ParticleEmitterData(LifelikeGroundHitSmallDirtBlastEmitter)
{
   ejectionPeriodMS = 30;
   periodVarianceMS = 2;
   ejectionVelocity = 13;
   velocityVariance = 2;
   thetaMin         = 0;
   thetaMax         = 50;
   phiReferenceVel  = 0;
   phiVariance      = 360;
   ejectionoffset   = 0;
   orientOnVelocity = true;
   orientParticles  = true;
   particles = "LifelikeGroundHitSmallDirtBlastParticle";
   blendStyle = "NORMAL";
};



//-----------------------------------------------------------------------------
//	Explosions
//-----------------------------------------------------------------------------



datablock ExplosionData(LifelikeGroundHitSmallExplosion)
{
   //soundProfile = YourSoundDatablock;
   lifeTimeMS = 150;

   // Volume
   particleEmitter = LifelikeGroundHitSmallSmokeEmitter;  
   particleDensity = 10;
   particleRadius = 1.5;

   // Point emission
   emitter[0] = LifelikeGroundHitSmallSmokeEmitter; 
   emitter[1] = LifelikeGroundHitSmallPointBurstEmitter; 
   emitter[2] = LifelikeGroundHitSmallDirtBlastEmitter;
   emitter[3] = LifelikeGroundHitSmallDirtDebrisEmitter; 
       
   shakeCamera = true;
   camShakeFreq = "10.0 11.0 9.0";
   camShakeAmp = "20.0 20.0 20.0";
   camShakeDuration = 1.5;
   camShakeRadius = 10.0;

   lightStartRadius = 10.0;
   lightEndRadius = 0.0;
   lightStartColor = "1 0.9 0.8";
   lightEndColor = "0.8 0.4 0.0";
   lightStartBrightness = 2.0;
   lightEndBrightness = 0.0;
   
};