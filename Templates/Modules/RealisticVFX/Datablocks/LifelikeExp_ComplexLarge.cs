//-----------------------------------------------------------------------------
// Lifelike Effects Pack - Large Complex Explosion
// Copyright Adam deGrandis 2012
//
// Thanks for your support!
//
//-----------------------------------------------------------------------------
//exec ("art/datablocks/LifelikeEffectsPack/LifelikeExp_ComplexLarge.cs");


//-----------------------------------------------------------------------------
//	Emitters
//-----------------------------------------------------------------------------

datablock ParticleData(LifelikeComplexLargeSmokeParticle)
{
   textureName          = "art/shapes/particles/LifelikeEffectsPack/smoke1";
   gravityCoefficient   = -0.05;
   lifetimeMS           = 3300;
   lifetimeVarianceMS   = 200;
   spinRandomMin = -50.0;
   spinRandomMax =  50.0;

   colors[0]     = "0.1 0.1 0 1";
   colors[1]     = "0.7 0.7 0.6 1";
   colors[2]     = "1 0.9 0.8 0.0";

   sizes[0]      = 4;
   sizes[1]      = 8;
   sizes[2]      = 12;

   times[0]      = 0.0;
   times[1]      = 0.1;
   times[2]      = 1.0;
};

datablock ParticleEmitterData(LifelikeComplexLargeSmokeEmitter)
{
   ejectionPeriodMS = 10;
   periodVarianceMS = 5;
   ejectionVelocity = 2;
   velocityVariance = 0;
   thetaMin         = 0;
   thetaMax         = 120;
   phiReferenceVel  = 0;
   phiVariance      = 360;
   ejectionoffset   = 2;
   particles = "LifelikeComplexLargeSmokeParticle";
   blendStyle = "NORMAL";
};


datablock ParticleData(LifelikeComplexLargeFireballParticle)
{
   textureName          = "art/shapes/particles/LifelikeEffectsPack/fireball";
   gravityCoefficient   = -0.3;
   lifetimeMS           = 700;
   lifetimeVarianceMS   = 100;
   spinRandomMin = -100.0;
   spinRandomMax =  100.0;
   
   colors[0]     = "1 0.9 0.8 1";
   colors[1]     = "0.8 0.4 0.0 1";
   colors[2]     = "0.8 0.4 0.0 0";

   sizes[0]      = 1;
   sizes[1]      = 7;
   sizes[2]      = 4;

   times[0]      = 0.0;
   times[1]      = 0.3;
   times[2]      = 1.0;
};

datablock ParticleEmitterData(LifelikeComplexLargeFireballEmitter)
{
   ejectionPeriodMS = 5;
   periodVarianceMS = 3;
   ejectionVelocity = 3;
   velocityVariance = 2;
   thetaMin         = 0;
   thetaMax         = 120;
   phiReferenceVel  = 0;
   phiVariance      = 360;
   ejectionoffset   = 3;
   
   particles = "LifelikeComplexLargeFireballParticle";
   blendStyle = "ADDITIVE";
};

datablock ParticleData(LifelikeComplexLargeGlowParticle)
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

   sizes[0]      = 7;
   sizes[1]      = 11;
   sizes[2]      = 5;

   times[0]      = 0.0;
   times[1]      = 0.3;
   times[2]      = 1.0;
};

datablock ParticleEmitterData(LifelikeComplexLargeGlowEmitter)
{
   ejectionPeriodMS = 20;
   periodVarianceMS = 5;
   ejectionVelocity = 3;
   velocityVariance = 2;
   thetaMin         = 0;
   thetaMax         = 120;
   phiReferenceVel  = 0;
   phiVariance      = 360;
      particles = "LifelikeComplexLargeGlowParticle";
   blendStyle = "ADDITIVE";
};

datablock ParticleData(LifelikeComplexLargeSparks2Particle)
{
   textureName          = "art/shapes/particles/LifelikeEffectsPack/spark2";
   dragCoefficient      = 4;
   gravityCoefficient   = 1;
   lifetimeMS           = 1500;
   lifetimeVarianceMS   = 500;
   spinRandomMin = -0.0;
   spinRandomMax =  0.0;

   colors[0]     = "1 1 1 0.0";
   colors[1]     = "1.0 0.9 0.8 1";
   colors[2]     = "0.9 0.8 0.7 0";

   sizes[0]      = 4.0;
   sizes[1]      = 3.0;
   sizes[2]      = 1.0;

   times[0]      = 0.0;
   times[1]      = 0.2;
   times[2]      = 1.0;
};

datablock ParticleEmitterData(LifelikeComplexLargeSparks2Emitter)
{
   ejectionPeriodMS = 2;
   periodVarianceMS = 1;
   ejectionVelocity = 70.0;
   velocityVariance = 10.0;
   ejectionOffset   = 0;
   thetaMin         = 0;
   thetaMax         = 70;
   phiReferenceVel  = 0;
   phiVariance      = 360;
   particles = "LifelikeComplexLargeSparks2Particle";
   blendStyle = "ADDITIVE";
};

datablock ParticleData(LifelikeComplexLargeSparks1Particle)
{
   textureName          = "art/shapes/particles/LifelikeEffectsPack/spark3";
   lifetimeMS           = 350;
   lifetimeVarianceMS   = 20;
   useInvAlpha =  false;

   colors[0]     = "1.0 0.9 0.8 1";
   colors[1]     = "1.0 0.9 0.8 1";
   colors[2]     = "0.8 0.4 0 0.0";

   sizes[0]      = 2;
   sizes[1]      = 7;
   sizes[2]      = 12;

   times[0]      = 0.0;
   times[1]      = 0.5;
   times[2]      = 1.0;
};

datablock ParticleEmitterData(LifelikeComplexLargeSparks1Emitter)
{
   ejectionPeriodMS = 20;
   periodVarianceMS = 5;
   ejectionVelocity = 35;
   velocityVariance = 10;
   thetaMin         = 0;
   thetaMax         = 70;
   phiReferenceVel  = 0;
   phiVariance      = 360;
   ejectionoffset   = 0;
   orientOnVelocity = true;
   orientParticles  = true;
   particles = "LifelikeComplexLargeSparks1Particle";
   blendStyle = "ADDITIVE";
};



//-----------------------------------------------------------------------------
//	Explosions
//-----------------------------------------------------------------------------


datablock ExplosionData(LifelikeComplexLargeExplosion)
{
   //soundProfile = YourSoundDatablock;
   lifeTimeMS = 200;
   
   // Volume
   particleEmitter = LifelikeComplexLargeGlowEmitter; 
   particleDensity = 40;
   particleRadius = 2;

   // Point emission
   emitter[0] = LifelikeComplexLargeSmokeEmitter; 
   emitter[1] = LifelikeComplexLargeFireballEmitter; 
   emitter[2] = LifelikeComplexLargeSparks1Emitter;
   emitter[3] = LifelikeComplexLargeSparks2Emitter; 

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