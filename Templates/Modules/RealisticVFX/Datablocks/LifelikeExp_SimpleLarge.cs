//-----------------------------------------------------------------------------
// Lifelike Effects Pack - Large Simple Explosion
// Copyright Adam deGrandis 2012
//
// Thanks for your support!
//
//-----------------------------------------------------------------------------
//exec ("art/datablocks/LifelikeEffectsPack/LifelikeExp_SimpleLarge.cs");


//-----------------------------------------------------------------------------
//	Emitters
//-----------------------------------------------------------------------------


datablock ParticleData(SimpleLargeSmokeParticle)
{
   textureName          = "art/shapes/particles/LifelikeEffectsPack/smoke1";
   dragCoeffiecient     = 0.0;
   gravityCoefficient   = -0.05;
   inheritedVelFactor   = 0.0;
   constantAcceleration = 0.0;
   lifetimeMS           = 3300;
   lifetimeVarianceMS   = 200;
   spinRandomMin = -50.0;
   spinRandomMax =  50.0;

   colors[0]     = "0.1 0.1 0.1 1";
   colors[1]     = "0.7 0.7 0.6 1";
   colors[2]     = "1 0.9 0.8 0.0";

   sizes[0]      = 4;
   sizes[1]      = 8;
   sizes[2]      = 12;

   times[0]      = 0.0;
   times[1]      = 0.1;
   times[2]      = 1.0;
};

datablock ParticleEmitterData(SimpleLargeSmokeEmitter)
{
   ejectionPeriodMS = 20;
   periodVarianceMS = 5;
   ejectionVelocity = 2;
   velocityVariance = 0;
   thetaMin         = 0;
   thetaMax         = 120;
   phiReferenceVel  = 0;
   phiVariance      = 360;
   ejectionoffset   = 2;
   particles = "SimpleLargeSmokeParticle";
   blendStyle = "NORMAL";
};

datablock ParticleData(SimpleLargeSparksParticle)
{
   textureName          = "art/shapes/particles/LifelikeEffectsPack/spark1";
   lifetimeMS           = 250;
   lifetimeVarianceMS   = 20;

   colors[0]     = "1.0 0.9 0.8 0.2";
   colors[1]     = "1.0 0.9 0.8 1";
   colors[2]     = "0.8 0.4 0 0.0";

   sizes[0]      = 1;
   sizes[1]      = 3;
   sizes[2]      = 1;

   times[0]      = 0.0;
   times[1]      = 0.5;
   times[2]      = 1.0;
};

datablock ParticleEmitterData(SimpleLargeSparksEmitter)
{
   ejectionPeriodMS = 10;
   periodVarianceMS = 5;
   ejectionVelocity = 25;
   velocityVariance = 10;
   thetaMin         = 0;
   thetaMax         = 70;
   phiReferenceVel  = 0;
   phiVariance      = 360;
   ejectionoffset   = 0;
   orientOnVelocity = true;
   orientParticles  = true;
   particles = "SimpleLargeSparksParticle";
   blendStyle = "ADDITIVE";
};

datablock ParticleData(SimpleLargeFireballParticle)
{
   textureName          = "art/shapes/particles/LifelikeEffectsPack/fireball";
   gravityCoefficient   = -0.1;
   lifetimeMS           = 500;
   lifetimeVarianceMS   = 100;
   spinRandomMin = -100.0;
   spinRandomMax =  100.0;

   colors[0]     = "1 0.9 0.8 1";
   colors[1]     = "0.9 0.5 0.1 1";
   colors[2]     = "0.8 0.4 0.0 0";

   sizes[0]      = 1;
   sizes[1]      = 7;
   sizes[2]      = 6;

   times[0]      = 0.0;
   times[1]      = 0.3;
   times[2]      = 1.0;
};

datablock ParticleEmitterData(SimpleLargeFireballEmitter)
{
   ejectionPeriodMS = 10;
   periodVarianceMS = 3;
   ejectionVelocity = 3;
   velocityVariance = 2;
   thetaMin         = 0;
   thetaMax         = 120;
   phiReferenceVel  = 0;
   phiVariance      = 360;
   ejectionoffset   = 2.5;
   
   particles = "SimpleLargeFireballParticle";
   blendStyle = "ADDITIVE";
};

datablock ParticleData(SimpleLargeGlowParticle)
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

datablock ParticleEmitterData(SimpleLargeGlowEmitter)
{
   ejectionPeriodMS = 40;
   periodVarianceMS = 5;
   ejectionVelocity = 3;
   velocityVariance = 2;
   thetaMin         = 0;
   thetaMax         = 120;
   phiReferenceVel  = 0;
   phiVariance      = 360;
   
   particles = "SimpleLargeGlowParticle";
   blendStyle = "ADDITIVE";
};



//-----------------------------------------------------------------------------
//	Explosions
//-----------------------------------------------------------------------------


datablock ExplosionData(LifelikeSimpleLargeExplosion)
{
   //soundProfile = YourSoundDatablock;
   lifeTimeMS = 125;

   // Volume
   particleEmitter = SimpleLargeGlowEmitter; 
   particleDensity = 20;
   particleRadius = 2;

   // Point emission
   emitter[0] = SimpleLargeSmokeEmitter; 
   emitter[1] = SimpleLargeFireballEmitter; 
   emitter[2] = SimpleLargeSparksEmitter;
   
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