//-----------------------------------------------------------------------------
// Lifelike Effects Pack - Small Complex Explosion
// Copyright Adam deGrandis 2012
//
// Thanks for your support!
//
//-----------------------------------------------------------------------------
//exec ("art/datablocks/LifelikeEffectsPack/LifelikeExp_ComplexSmall.cs");


//-----------------------------------------------------------------------------
//	Emitters
//-----------------------------------------------------------------------------

datablock ParticleData(LifelikeComplexSmallSmokeParticle)
{
   textureName          = "art/shapes/particles/LifelikeEffectsPack/smoke1";
   gravityCoefficient   = -0.02;
   lifetimeMS           = 2000;
   lifetimeVarianceMS   = 200;
   spinRandomMin = -50.0;
   spinRandomMax =  50.0;

   colors[0]     = "0.1 0.1 0 1";
   colors[1]     = "0.7 0.7 0.6 1";
   colors[2]     = "1 0.9 0.8 0.0";

   sizes[0]      = 2;
   sizes[1]      = 4;
   sizes[2]      = 6;

   times[0]      = 0.0;
   times[1]      = 0.1;
   times[2]      = 1.0;
};

datablock ParticleEmitterData(LifelikeComplexSmallSmokeEmitter)
{
   ejectionPeriodMS = 15;
   periodVarianceMS = 5;
   ejectionVelocity = 1;
   velocityVariance = 0;
   thetaMin         = 0;
   thetaMax         = 120;
   phiReferenceVel  = 0;
   phiVariance      = 360;
   ejectionoffset   = 0.7;
   particles = "LifelikeComplexSmallSmokeParticle";
   blendStyle = "NORMAL";
};


datablock ParticleData(LifelikeComplexSmallFireballParticle)
{
   textureName          = "art/shapes/particles/LifelikeEffectsPack/fireball";
   gravityCoefficient   = -0.3;
   lifetimeMS           = 500;
   lifetimeVarianceMS   = 100;
   spinRandomMin = -100.0;
   spinRandomMax =  100.0;
   
   colors[0]     = "1 0.9 0.8 1";
   colors[1]     = "0.8 0.4 0.0 1";
   colors[2]     = "0.8 0.4 0.0 0";

   sizes[0]      = 1;
   sizes[1]      = 4;
   sizes[2]      = 2;

   times[0]      = 0.0;
   times[1]      = 0.3;
   times[2]      = 1.0;
};

datablock ParticleEmitterData(LifelikeComplexSmallFireballEmitter)
{
   ejectionPeriodMS = 10;
   periodVarianceMS = 3;
   ejectionVelocity = 2;
   velocityVariance = 1;
   thetaMin         = 0;
   thetaMax         = 120;
   phiReferenceVel  = 0;
   phiVariance      = 360;
   ejectionoffset   = 1.3;
   
   particles = "LifelikeComplexSmallFireballParticle";
   blendStyle = "ADDITIVE";
};

datablock ParticleData(LifelikeComplexSmallGlowParticle)
{
   textureName          = "art/shapes/particles/LifelikeEffectsPack/flame1";
   gravityCoefficient   = -0.3;
   lifetimeMS           = 400;
   lifetimeVarianceMS   = 100;
   spinRandomMin = -200.0;
   spinRandomMax =  200.0;

   colors[0]     = "0.9 0.8 1 0.4";
   colors[1]     = "0.8 0.4 0.0 0.1";
   colors[2]     = "0.8 0.4 0.0 0";

   sizes[0]      = 3;
   sizes[1]      = 6;
   sizes[2]      = 2;

   times[0]      = 0.0;
   times[1]      = 0.3;
   times[2]      = 1.0;
};

datablock ParticleEmitterData(LifelikeComplexSmallGlowEmitter)
{
   ejectionPeriodMS = 20;
   periodVarianceMS = 5;
   ejectionVelocity = 3;
   velocityVariance = 2;
   thetaMin         = 0;
   thetaMax         = 120;
   phiReferenceVel  = 0;
   phiVariance      = 360;
      particles = "LifelikeComplexSmallGlowParticle";
   blendStyle = "ADDITIVE";
};

datablock ParticleData(LifelikeComplexSmallSparks2Particle)
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

datablock ParticleEmitterData(LifelikeComplexSmallSparks2Emitter)
{
   ejectionPeriodMS = 10;
   periodVarianceMS = 1;
   ejectionVelocity = 40.0;
   velocityVariance = 10.0;
   ejectionOffset   = 0;
   thetaMin         = 0;
   thetaMax         = 70;
   phiReferenceVel  = 0;
   phiVariance      = 360;
   particles = "LifelikeComplexSmallSparks2Particle";
   blendStyle = "ADDITIVE";
};

datablock ParticleData(LifelikeComplexSmallSparks1Particle)
{
   textureName          = "art/shapes/particles/LifelikeEffectsPack/spark3";
   lifetimeMS           = 300;
   lifetimeVarianceMS   = 20;
   useInvAlpha =  false;

   colors[0]     = "1.0 0.9 0.8 1";
   colors[1]     = "1.0 0.9 0.8 1";
   colors[2]     = "0.8 0.4 0 0.0";

   sizes[0]      = 1;
   sizes[1]      = 3.5;
   sizes[2]      = 6;

   times[0]      = 0.0;
   times[1]      = 0.5;
   times[2]      = 1.0;
};

datablock ParticleEmitterData(LifelikeComplexSmallSparks1Emitter)
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
   particles = "LifelikeComplexSmallSparks1Particle";
   blendStyle = "ADDITIVE";
};



//-----------------------------------------------------------------------------
//	Explosions
//-----------------------------------------------------------------------------


datablock ExplosionData(LifelikeComplexSmallExplosion)
{
   //soundProfile = YourSoundDatablock;
   lifeTimeMS = 130;
   
   // Volume
   particleEmitter = LifelikeComplexSmallGlowEmitter; 
   particleDensity = 20;
   particleRadius = 1.2;

   // Point emission
   emitter[0] = LifelikeComplexSmallSmokeEmitter; 
   emitter[1] = LifelikeComplexSmallFireballEmitter; 
   emitter[2] = LifelikeComplexSmallSparks1Emitter;
   emitter[3] = LifelikeComplexSmallSparks2Emitter; 
      
   shakeCamera = true;
   camShakeFreq = "10.0 11.0 9.0";
   camShakeAmp = "20.0 20.0 20.0";
   camShakeDuration = 1.5;
   camShakeRadius = 5.0;

   lightStartRadius = 10.0;
   lightEndRadius = 0.0;
   lightStartColor = "1 0.9 0.8";
   lightEndColor = "0.8 0.4 0.0";
   lightStartBrightness = 2.0;
   lightEndBrightness = 0.0;
   
};