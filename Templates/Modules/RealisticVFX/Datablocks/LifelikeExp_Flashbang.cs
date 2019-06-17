//-----------------------------------------------------------------------------
// Lifelike Effects Pack - Flashbang Explosion
// Copyright Adam deGrandis 2012
//
// Thanks for your support!
//
//-----------------------------------------------------------------------------
//exec ("art/datablocks/LifelikeEffectsPack/LifelikeExp_Flashbang.cs");


//-----------------------------------------------------------------------------
//	Emitters
//-----------------------------------------------------------------------------


datablock ParticleData(LifelikeFlashbangPointBurstParticle)
{
   textureName          = "art/shapes/particles/LifelikeEffectsPack/PointBurst";
   lifetimeMS           = 350;
   lifetimeVarianceMS   = 0;
   spinRandomMin = -20.0;
   spinRandomMax =  20.0;

   colors[0]     = "1.0 0.9 0.8 1";
   colors[1]     = "1.0 0.9 0.8 0.2";
   colors[2]     = "1.0 0.9 0.8 0.0";

   sizes[0]      = 2;
   sizes[1]      = 5;
   sizes[2]      = 1;

   times[0]      = 0.0;
   times[1]      = 0.1;
   times[2]      = 1.0;
};

datablock ParticleEmitterData(LifelikeFlashbangPointBurstEmitter)
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
   particles = "LifelikeFlashbangPointBurstParticle";
   blendStyle = "ADDITIVE";
};

datablock ParticleData(LifelikeFlashbangSmokeParticle)
{
   textureName          = "art/shapes/particles/LifelikeEffectsPack/flame1";
   gravityCoefficient   = -0.02;
   lifetimeMS           = 1500;
   lifetimeVarianceMS   = 200;
   spinRandomMin = -100.0;
   spinRandomMax =  100.0;

   colors[0]     = "0.5 0.5 0.5 0.5";
   colors[1]     = "1 1 1 0.3";
   colors[2]     = "1 1 1 0.0";

   sizes[0]      = 2;
   sizes[1]      = 3;
   sizes[2]      = 5;

   times[0]      = 0.0;
   times[1]      = 0.2;
   times[2]      = 1.0;
};

datablock ParticleEmitterData(LifelikeFlashbangSmokeEmitter)
{
   ejectionPeriodMS = 10;
   periodVarianceMS = 2;
   ejectionVelocity = 1;
   velocityVariance = 0;
   thetaMin         = 0;
   thetaMax         = 120;
   phiReferenceVel  = 0;
   phiVariance      = 360;
   ejectionoffset   = 1;
   particles = "LifelikeFlashbangSmokeParticle";
   blendStyle = "NORMAL";
};



datablock ParticleData(LifelikeFlashbangGlowParticle)
{
   textureName          = "art/shapes/particles/LifelikeEffectsPack/flame1";
   gravityCoefficient   = -0.3;
   lifetimeMS           = 400;
   lifetimeVarianceMS   = 100;
   spinRandomMin = -200.0;
   spinRandomMax =  200.0;

   colors[0]     = "0.9 0.8 1 0.4";
   colors[1]     = "0.9 0.8 1 0.1";
   colors[2]     = "0.9 0.8 1 0";

   sizes[0]      = 3;
   sizes[1]      = 6;
   sizes[2]      = 2;

   times[0]      = 0.0;
   times[1]      = 0.3;
   times[2]      = 1.0;
};

datablock ParticleEmitterData(LifelikeFlashbangGlowEmitter)
{
   ejectionPeriodMS = 30;
   periodVarianceMS = 5;
   ejectionVelocity = 3;
   velocityVariance = 2;
   thetaMin         = 0;
   thetaMax         = 120;
   phiReferenceVel  = 0;
   phiVariance      = 360;
   particles = "LifelikeFlashbangGlowParticle";
   blendStyle = "ADDITIVE";
};

datablock ParticleData(LifelikeFlashbangSparks2Particle)
{
   textureName          = "art/shapes/particles/LifelikeEffectsPack/spark2";
   dragCoefficient      = 4;
   gravityCoefficient   = 1;
   lifetimeMS           = 1000;
   lifetimeVarianceMS   = 200;
   spinRandomMin = -0.0;
   spinRandomMax =  0.0;

   colors[0]     = "1 1 1 0.5";
   colors[1]     = "1.0 0.9 0.8 1";
   colors[2]     = "0.9 0.8 0.7 0";

   sizes[0]      = 2.0;
   sizes[1]      = 1.5;
   sizes[2]      = 0.5;

   times[0]      = 0.0;
   times[1]      = 0.2;
   times[2]      = 1.0;
};

datablock ParticleEmitterData(LifelikeFlashbangSparks2Emitter)
{
   ejectionPeriodMS = 6;
   periodVarianceMS = 1;
   ejectionVelocity = 30.0;
   velocityVariance = 10.0;
   ejectionOffset   = 0;
   thetaMin         = 0;
   thetaMax         = 70;
   phiReferenceVel  = 0;
   phiVariance      = 360;
   particles = "LifelikeFlashbangSparks2Particle";
   blendStyle = "ADDITIVE";
};

datablock ParticleData(LifelikeFlashbangSparks1Particle)
{
   textureName          = "art/shapes/particles/LifelikeEffectsPack/spark3";
   lifetimeMS           = 200;
   lifetimeVarianceMS   = 20;
   useInvAlpha =  false;

   colors[0]     = "1.0 0.9 0.8 1";
   colors[1]     = "1.0 0.9 0.8 1";
   colors[2]     = "1.0 0.9 0.8 0.0";

   sizes[0]      = 1;
   sizes[1]      = 3.5;
   sizes[2]      = 6;

   times[0]      = 0.0;
   times[1]      = 0.5;
   times[2]      = 1.0;
};

datablock ParticleEmitterData(LifelikeFlashbangSparks1Emitter)
{
   ejectionPeriodMS = 20;
   periodVarianceMS = 5;
   ejectionVelocity = 17;
   velocityVariance = 5;
   thetaMin         = 0;
   thetaMax         = 70;
   phiReferenceVel  = 0;
   phiVariance      = 360;
   ejectionoffset   = 0;
   orientOnVelocity = true;
   orientParticles  = true;
   particles = "LifelikeFlashbangSparks1Particle";
   blendStyle = "ADDITIVE";
};



//-----------------------------------------------------------------------------
//	Explosions
//-----------------------------------------------------------------------------


datablock ExplosionData(LifelikeFlashbangExplosion)
{
   //soundProfile = YourSoundDatablock;
   lifeTimeMS = 70;
   
   // Volume
   particleEmitter = LifelikeFlashbangGlowEmitter; 
   particleDensity = 10;
   particleRadius = 2;

   // Point emission
   emitter[0] = LifelikeFlashbangSmokeEmitter; 
   emitter[1] = LifelikeFlashbangPointBurstEmitter; 
   emitter[2] = LifelikeFlashbangSparks1Emitter;
   emitter[3] = LifelikeFlashbangSparks2Emitter; 
      
   shakeCamera = true;
   camShakeFreq = "10.0 11.0 9.0";
   camShakeAmp = "20.0 20.0 20.0";
   camShakeDuration = 1.5;
   camShakeRadius = 3.0;

   lightStartRadius = 10.0;
   lightEndRadius = 0.0;
   lightStartColor = "1 0.9 0.8";
   lightEndColor = "1 0.9 0.8";
   lightStartBrightness = 2.0;
   lightEndBrightness = 0.0;
   
};