//-----------------------------------------------------------------------------
// Lifelike Effects Pack - Large Ground Explosion
// Copyright Adam deGrandis 2012
//
// Thanks for your support!
//
//-----------------------------------------------------------------------------
//exec ("art/datablocks/LifelikeEffectsPack/LifelikeExp_GroundHitLarge.cs");


//-----------------------------------------------------------------------------
//	Emitters
//-----------------------------------------------------------------------------


datablock ParticleData(LifelikeGroundHitLargePointBurstParticle)
{
   textureName          = "art/shapes/particles/LifelikeEffectsPack/PointBurst";
   lifetimeMS           = 350;
   lifetimeVarianceMS   = 0;
   spinRandomMin = -20.0;
   spinRandomMax =  20.0;

   colors[0]     = "1.0 0.9 0.8 1";
   colors[1]     = "0.8 0.4 0.0 0.2";
   colors[2]     = "0.8 0.4 0.0 0.0";

   sizes[0]      = 8;
   sizes[1]      = 25;
   sizes[2]      = 2;

   times[0]      = 0.0;
   times[1]      = 0.1;
   times[2]      = 1.0;
};

datablock ParticleEmitterData(LifelikeGroundHitLargePointBurstEmitter)
{
   ejectionPeriodMS = 40;
   periodVarianceMS = 5;
   ejectionVelocity = 0;
   velocityVariance = 0;
   thetaMin         = 0;
   thetaMax         = 120;
   phiReferenceVel  = 0;
   phiVariance      = 360;
   ejectionoffset   = 0;
   particles = "LifelikeGroundHitLargePointBurstParticle";
   blendStyle = "ADDITIVE";
};


datablock ParticleData(LifelikeGroundHitLargeSmokeParticle)
{
   textureName          = "art/shapes/particles/LifelikeEffectsPack/smoke2";
   gravityCoefficient   = 0.5;
   lifetimeMS           = 3000;
   lifetimeVarianceMS   = 500;
   spinRandomMin = -50.0;
   spinRandomMax =  50.0;

   colors[0]     = "0.3 0.2 0.1 0";
   colors[1]     = "0.6 0.5 0.4 1";
   colors[2]     = "0.6 0.5 0.4 0";

   sizes[0]      = 4;
   sizes[1]      = 14;
   sizes[2]      = 25;

   times[0]      = 0.0;
   times[1]      = 0.1;
   times[2]      = 1.0;
};

datablock ParticleEmitterData(LifelikeGroundHitLargeSmokeEmitter)
{
   ejectionPeriodMS = 15;
   periodVarianceMS = 5;
   ejectionVelocity = 10;
   velocityVariance = 5;
   thetaMin         = 0;
   thetaMax         = 50;
   phiReferenceVel  = 0;
   phiVariance      = 360;
   ejectionoffset   = 0;
   particles = "LifelikeGroundHitLargeSmokeParticle";
   blendStyle = "NORMAL";
};


datablock ParticleData(LifelikeGroundHitLargeDirtDebrisParticle)
{
   textureName          = "art/shapes/particles/LifelikeEffectsPack/dirtDebris";
   //dragCoefficient      = 4;
   gravityCoefficient   = 3;
   lifetimeMS           = 1500;
   lifetimeVarianceMS   = 500;
   spinRandomMin = -40.0;
   spinRandomMax =  40.0;

   colors[0]     = "1 1 1 1";
   colors[1]     = "1.0 0.9 0.8 1";
   colors[2]     = "0.9 0.8 0.7 0";

   sizes[0]      = 5;
   sizes[1]      = 10;
   sizes[2]      = 14;

   times[0]      = 0.0;
   times[1]      = 0.2;
   times[2]      = 1.0;
};

datablock ParticleEmitterData(LifelikeGroundHitLargeDirtDebrisEmitter)
{
   ejectionPeriodMS = 10;
   periodVarianceMS = 1;
   ejectionVelocity = 30.0;
   velocityVariance = 10.0;
   ejectionOffset   = 0;
   thetaMin         = 0;
   thetaMax         = 40;
   phiReferenceVel  = 0;
   phiVariance      = 360;
   particles = "LifelikeGroundHitLargeDirtDebrisParticle";
   blendStyle = "NORMAL";
};


datablock ParticleData(LifelikeGroundHitLargeDirtBlastParticle)
{
   textureName          = "art/shapes/particles/LifelikeEffectsPack/dirtBlast1";
   lifetimeMS           = 850;
   lifetimeVarianceMS   = 50;
   gravityCoefficient   = 1;

   colors[0]     = "0.6 0.5 0.4 1";
   colors[1]     = "0.6 0.5 0.4 1";
   colors[2]     = "0.6 0.5 0.4 0";

   sizes[0]      = 5;
   sizes[1]      = 30;
   sizes[2]      = 30;

   times[0]      = 0.0;
   times[1]      = 0.2;
   times[2]      = 1.0;
};

datablock ParticleEmitterData(LifelikeGroundHitLargeDirtBlastEmitter)
{
   ejectionPeriodMS = 20;
   periodVarianceMS = 2;
   ejectionVelocity = 20;
   velocityVariance = 2;
   thetaMin         = 0;
   thetaMax         = 50;
   phiReferenceVel  = 0;
   phiVariance      = 360;
   ejectionoffset   = 0;
   orientOnVelocity = true;
   orientParticles  = true;
   particles = "LifelikeGroundHitLargeDirtBlastParticle";
   blendStyle = "NORMAL";
};



//-----------------------------------------------------------------------------
//	Explosions
//-----------------------------------------------------------------------------



datablock ExplosionData(LifelikeGroundHitLargeExplosion)
{
   //soundProfile = YourSoundDatablock;
   lifeTimeMS = 200;

   // Volume
   particleEmitter = LifelikeGroundHitLargeSmokeEmitter;  
   particleDensity = 5;
   particleRadius = 3;

   // Point emission
   emitter[0] = LifelikeGroundHitLargeSmokeEmitter; 
   emitter[1] = LifelikeGroundHitLargePointBurstEmitter; 
   emitter[2] = LifelikeGroundHitLargeDirtBlastEmitter;
   emitter[3] = LifelikeGroundHitLargeDirtDebrisEmitter; 
      
   // Sub explosion objects
   //subExplosion[0] = LifelikeGroundHitLargeExplosion;
   
     
   shakeCamera = true;
   camShakeFreq = "10.0 11.0 9.0";
   camShakeAmp = "20.0 20.0 20.0";
   camShakeDuration = 1.5;
   camShakeRadius = 20.0;

   lightStartRadius = 20.0;
   lightEndRadius = 0.0;
   lightStartColor = "1 0.9 0.8";
   lightEndColor = "0.8 0.4 0.0";
   lightStartBrightness = 2.0;
   lightEndBrightness = 0.0;
   
};