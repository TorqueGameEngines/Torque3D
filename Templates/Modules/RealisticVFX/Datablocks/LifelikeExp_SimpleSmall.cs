//-----------------------------------------------------------------------------
// Lifelike Effects Pack - Small Simple Explosion
// Copyright Adam deGrandis 2012
//
// Thanks for your support!
//
//-----------------------------------------------------------------------------
//exec ("art/datablocks/LifelikeEffectsPack/LifelikeExp_SimpleSmall.cs");


//-----------------------------------------------------------------------------
//	Emitters
//-----------------------------------------------------------------------------



datablock ParticleData(SimpleSmallSmokeParticle)
{
   textureName          = "art/shapes/particles/LifelikeEffectsPack/smoke1";
   dragCoeffiecient     = 0.0;
   gravityCoefficient   = -0.02;
   inheritedVelFactor   = 0.0;
   constantAcceleration = 0.0;
   lifetimeMS           = 3300;
   lifetimeVarianceMS   = 200;
   spinRandomMin = -50.0;
   spinRandomMax =  50.0;

   colors[0]     = "0.1 0.1 0.1 1";
   colors[1]     = "0.7 0.7 0.6 1";
   colors[2]     = "1 0.9 0.8 0.0";

   sizes[0]      = 2;
   sizes[1]      = 4;
   sizes[2]      = 6;

   times[0]      = 0.0;
   times[1]      = 0.1;
   times[2]      = 1.0;
};

datablock ParticleEmitterData(SimpleSmallSmokeEmitter)
{
   ejectionPeriodMS = 20;
   periodVarianceMS = 5;
   ejectionVelocity = 1;
   velocityVariance = 0;
   thetaMin         = 0;
   thetaMax         = 120;
   phiReferenceVel  = 0;
   phiVariance      = 360;
   ejectionoffset   = 0.7;
   particles = "SimpleSmallSmokeParticle";
   blendStyle = "NORMAL";
};

datablock ParticleData(SimpleSmallSparksParticle)
{
   textureName          = "art/shapes/particles/LifelikeEffectsPack/spark1";
   lifetimeMS           = 200;
   lifetimeVarianceMS   = 20;

   colors[0]     = "1.0 0.9 0.8 0.2";
   colors[1]     = "1.0 0.9 0.8 1";
   colors[2]     = "0.8 0.4 0 0.0";

   sizes[0]      = 0.5;
   sizes[1]      = 2;
   sizes[2]      = 0.5;

   times[0]      = 0.0;
   times[1]      = 0.5;
   times[2]      = 1.0;
};

datablock ParticleEmitterData(SimpleSmallSparksEmitter)
{
   ejectionPeriodMS = 10;
   periodVarianceMS = 5;
   ejectionVelocity = 20;
   velocityVariance = 10;
   thetaMin         = 0;
   thetaMax         = 70;
   phiReferenceVel  = 0;
   phiVariance      = 360;
   ejectionoffset   = 0;
   orientOnVelocity = true;
   orientParticles  = true;
   particles = "SimpleSmallSparksParticle";
   blendStyle = "ADDITIVE";
};

datablock ParticleData(SimpleSmallFireballParticle)
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
   sizes[1]      = 4;
   sizes[2]      = 3;

   times[0]      = 0.0;
   times[1]      = 0.3;
   times[2]      = 1.0;
};

datablock ParticleEmitterData(SimpleSmallFireballEmitter)
{
   ejectionPeriodMS = 10;
   periodVarianceMS = 3;
   ejectionVelocity = 2;
   velocityVariance = 1;
   thetaMin         = 0;
   thetaMax         = 120;
   phiReferenceVel  = 0;
   phiVariance      = 360;
   ejectionoffset   = 1;
   
   particles = "SimpleSmallFireballParticle";
   blendStyle = "ADDITIVE";
};

datablock ParticleData(SimpleSmallGlowParticle)
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

datablock ParticleEmitterData(SimpleSmallGlowEmitter)
{
   ejectionPeriodMS = 40;
   periodVarianceMS = 5;
   ejectionVelocity = 3;
   velocityVariance = 2;
   thetaMin         = 0;
   thetaMax         = 120;
   phiReferenceVel  = 0;
   phiVariance      = 360;
   
   particles = "SimpleSmallGlowParticle";
   blendStyle = "ADDITIVE";
};



//-----------------------------------------------------------------------------
//	Explosions
//-----------------------------------------------------------------------------


datablock ExplosionData(LifelikeSimpleSmallExplosion)
{
   //soundProfile = YourSoundDatablock;
   lifeTimeMS = 125;

   // Volume
   particleEmitter = SimpleSmallGlowEmitter; 
   particleDensity = 20;
   particleRadius = 1;

   // Point emission
   emitter[0] = SimpleSmallSmokeEmitter; 
   emitter[1] = SimpleSmallFireballEmitter; 
   emitter[2] = SimpleSmallSparksEmitter;
   
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