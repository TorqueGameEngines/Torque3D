//-----------------------------------------------------------------------------
// Lifelike Effects Pack - Flak Explosion
// Copyright Adam deGrandis 2012
//
// Thanks for your support!
//
//-----------------------------------------------------------------------------
//exec ("art/datablocks/LifelikeEffectsPack/LifelikeExp_Flak.cs");


//-----------------------------------------------------------------------------
//	Emitters
//-----------------------------------------------------------------------------


datablock ParticleData(LifelikeFlakPointBurstParticle)
{
   textureName          = "art/shapes/particles/LifelikeEffectsPack/PointBurst";
   lifetimeMS           = 150;
   spinRandomMin = -50.0;
   spinRandomMax =  50.0;

   colors[0]     = "1.0 0.9 0.8 1";
   colors[1]     = "1 0.6 0.2 1";
   colors[2]     = "0.8 0.4 0.0 0.0";

   sizes[0]      = 1;
   sizes[1]      = 8;
   sizes[2]      = 2;

   times[0]      = 0.0;
   times[1]      = 0.3;
   times[2]      = 1.0;
};

datablock ParticleEmitterData(LifelikeFlakPointBurstEmitter)
{
   ejectionPeriodMS = 40;
   periodVarianceMS = 5;
   ejectionVelocity = 0.1;
   velocityVariance = 0;
   thetaMin         = 0;
   thetaMax         = 120;
   phiReferenceVel  = 0;
   phiVariance      = 360;
   particles = "LifelikeFlakPointBurstParticle";
   blendStyle = "ADDITIVE";
};


datablock ParticleData(LifelikeFlakSmokeParticle)
{
   textureName          = "art/shapes/particles/LifelikeEffectsPack/smoke1";
   lifetimeMS           = 3300;
   lifetimeVarianceMS   = 200;
   spinRandomMin = -50.0;
   spinRandomMax =  50.0;

   colors[0]     = "0.5 0.4 0.1 0";
   colors[1]     = "0.7 0.7 0.6 1";
   colors[2]     = "1 0.9 0.8 0.0";

   sizes[0]      = 3;
   sizes[1]      = 5;
   sizes[2]      = 6;

   times[0]      = 0.0;
   times[1]      = 0.05;
   times[2]      = 1.0;
};

datablock ParticleEmitterData(LifelikeFlakSmokeEmitter)
{
   ejectionPeriodMS = 20;
   periodVarianceMS = 5;
   ejectionVelocity = 1;
   thetaMin         = 0;
   thetaMax         = 180;
   phiReferenceVel  = 0;
   phiVariance      = 360;
   ejectionoffset   = 2;
   particles = "LifelikeFlakSmokeParticle";
   blendStyle = "NORMAL";
};



datablock ParticleData(LifelikeFlakSparksParticle)
{
   textureName          = "art/shapes/particles/LifelikeEffectsPack/spark1";
   lifetimeMS           = 100;
   lifetimeVarianceMS   = 50;

   colors[0]     = "1.0 0.9 0.8 1";
   colors[1]     = "1.0 0.9 0.8 1";
   colors[2]     = "0.8 0.4 0 0.0";

   sizes[0]      = 1;
   sizes[1]      = 3;
   sizes[2]      = 1;

   times[0]      = 0.0;
   times[1]      = 0.5;
   times[2]      = 1.0;
};

datablock ParticleEmitterData(LifelikeFlakSparksEmitter)
{
   ejectionPeriodMS = 10;
   periodVarianceMS = 5;
   ejectionVelocity = 35;
   velocityVariance = 10;
   thetaMin         = 0;
   thetaMax         = 180;
   phiReferenceVel  = 0;
   phiVariance      = 360;
   ejectionoffset   = 0;
   orientOnVelocity = true;
   orientParticles  = true;
   particles = "LifelikeFlakSparksParticle";
   blendStyle = "ADDITIVE";
};

datablock ParticleData(LifelikeFlakHazeParticle)
{
   textureName          = "art/shapes/particles/LifelikeEffectsPack/flame1";
   lifetimeMS           = 2500;
   lifetimeVarianceMS   = 500;
   spinRandomMin = -50.0;
   spinRandomMax =  50.0;

   colors[0]     = "0.4 0.3 0.1 0";
   colors[1]     = "0.1 0.1 0.1 0.7";
   colors[2]     = "0.1 0.1 0.1 0";

   sizes[0]      = 2;
   sizes[1]      = 3;
   sizes[2]      = 4;

   times[0]      = 0.0;
   times[1]      = 0.1;
   times[2]      = 1.0;
};

datablock ParticleEmitterData(LifelikeFlakHazeEmitter)
{
   ejectionPeriodMS = 20;
   periodVarianceMS = 5;
   ejectionVelocity = 0;
   velocityVariance = 0;
   thetaMin         = 0;
   thetaMax         = 180;
   phiReferenceVel  = 0;
   phiVariance      = 360;
   ejectionOffset   = 1;
   
   particles = "LifelikeFlakHazeParticle";
   blendStyle = "NORMAL";
};



//-----------------------------------------------------------------------------
//	Explosions
//-----------------------------------------------------------------------------


datablock ExplosionData(LifelikeFlakExplosion)
{
   //soundProfile = YourSoundDatablock;
   lifeTimeMS = 100;

   // Volume
   particleEmitter = LifelikeFlakHazeEmitter; 
   particleDensity = 30;
   particleRadius = 1;

   // Point emission
   emitter[0] = LifelikeFlakSmokeEmitter; 
   emitter[1] = LifelikeFlakPointBurstEmitter; 
   emitter[2] = LifelikeFlakSparksEmitter;
   
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