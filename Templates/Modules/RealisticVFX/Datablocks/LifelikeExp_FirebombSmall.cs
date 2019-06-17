//-----------------------------------------------------------------------------
// Lifelike Effects Pack - Small Firebomb Explosion
// Copyright Adam deGrandis 2012
//
// Thanks for your support!
//
//-----------------------------------------------------------------------------
//exec ("art/datablocks/LifelikeEffectsPack/LifelikeExp_FirebombSmall.cs");


//-----------------------------------------------------------------------------
//	Emitters
//-----------------------------------------------------------------------------


datablock ParticleData(LifelikeFirebombSmallSmokeParticle)
{
   textureName          = "art/shapes/particles/LifelikeEffectsPack/smoke2";
   gravityCoefficient   = -0.05;
   lifetimeMS           = 1500;
   lifetimeVarianceMS   = 500;
   spinRandomMin = -50.0;
   spinRandomMax =  50.0;

   colors[0]     = "0.1 0.1 0.1 1";
   colors[1]     = "0.8 0.7 0.6 1";
   colors[2]     = "1 0.9 0.8 0";

   sizes[0]      = 2;
   sizes[1]      = 4.5;
   sizes[2]      = 6;

   times[0]      = 0.0;
   times[1]      = 0.3;
   times[2]      = 1.0;
};

datablock ParticleEmitterData(LifelikeFirebombSmallSmokeEmitter)
{
   ejectionPeriodMS = 30;
   periodVarianceMS = 5;
   ejectionVelocity = 2;
   velocityVariance = 1;
   thetaMin         = 0;
   thetaMax         = 90;
   phiReferenceVel  = 0;
   phiVariance      = 360;
   ejectionoffset   = 1;
   particles = "LifelikeFirebombSmallSmokeParticle";
   blendStyle = "NORMAL";
};

datablock ParticleData(LifelikeFirebombSmallFireBlastParticle)
{
   textureName          = "art/shapes/particles/LifelikeEffectsPack/fireblast";
   lifetimeMS           = 250;
   lifetimeVarianceMS   = 50;

   colors[0]     = "1 0.9 0.8 0.5";
   colors[1]     = "0.8 0.4 0 1";
   colors[2]     = "0.8 0.4 0 0";

   sizes[0]      = 1;
   sizes[1]      = 8;
   sizes[2]      = 1;

   times[0]      = 0.0;
   times[1]      = 0.3;
   times[2]      = 1.0;
};

datablock ParticleEmitterData(LifelikeFirebombSmallFireBlastEmitter)
{
   ejectionPeriodMS = 10;
   periodVarianceMS = 2;
   ejectionVelocity = 20;
   velocityVariance = 10;
   thetaMin         = 0;
   thetaMax         = 70;
   phiReferenceVel  = 0;
   phiVariance      = 360;
   orientOnVelocity = true;
   orientParticles  = true;
   particles = "LifelikeFirebombSmallFireBlastParticle";
   blendStyle = "ADDITIVE";
};

datablock ParticleData(LifelikeFirebombSmallSparks1Particle)
{
   textureName          = "art/shapes/particles/LifelikeEffectsPack/spark1";
   lifetimeMS           = 300;
   lifetimeVarianceMS   = 20;
   gravityCoefficient   = 0;

   colors[0]     = "1.0 0.9 0.8 0.4";
   colors[1]     = "1.0 0.9 0.8 1";
   colors[2]     = "0.8 0.4 0 0.0";

   sizes[0]      = 3;
   sizes[1]      = 2;
   sizes[2]      = 1;

   times[0]      = 0.0;
   times[1]      = 0.5;
   times[2]      = 1.0;
};

datablock ParticleEmitterData(LifelikeFirebombSmallSparks1Emitter)
{
   ejectionPeriodMS = 12;
   periodVarianceMS = 2;
   ejectionVelocity = 20;
   velocityVariance = 15;
   thetaMin         = 0;
   thetaMax         = 90;
   phiReferenceVel  = 0;
   phiVariance      = 360;
   ejectionoffset   = 0;
   orientOnVelocity = true;
   orientParticles  = true;
   particles = "LifelikeFirebombSmallSparks1Particle";
   blendStyle = "ADDITIVE";
};


datablock ParticleData(LifelikeFirebombSmallGlowParticle)
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

datablock ParticleEmitterData(LifelikeFirebombSmallGlowEmitter)
{
   ejectionPeriodMS = 20;
   periodVarianceMS = 5;
   ejectionVelocity = 3;
   velocityVariance = 2;
   thetaMin         = 0;
   thetaMax         = 120;
   phiReferenceVel  = 0;
   phiVariance      = 360;
   
   particles = "LifelikeFirebombSmallGlowParticle";
   blendStyle = "ADDITIVE";
};


datablock ParticleData(LifelikeFirebombSmallFireballParticle)
{
   textureName          = "art/shapes/particles/LifelikeEffectsPack/flame1";
   gravityCoefficient   = -0.15;
   lifetimeMS           = 700;
   lifetimeVarianceMS   = 100;
   spinRandomMin = -200.0;
   spinRandomMax =  200.0;
   
   colors[0]     = "1 0.9 0.8 1";
   colors[1]     = "0.8 0.4 0.0 1";
   colors[2]     = "0.8 0.4 0.0 0";

   sizes[0]      = 1;
   sizes[1]      = 4;
   sizes[2]      = 3;

   times[0]      = 0.0;
   times[1]      = 0.3;
   times[2]      = 1.0;
};

datablock ParticleEmitterData(LifelikeFirebombSmallFireballEmitter)
{
   ejectionPeriodMS = 14;
   periodVarianceMS = 3;
   ejectionVelocity = 3;
   velocityVariance = 2;
   thetaMin         = 0;
   thetaMax         = 120;
   phiReferenceVel  = 0;
   phiVariance      = 360;
   ejectionoffset   = 1.5;
   
   particles = "LifelikeFirebombSmallFireballParticle";
   blendStyle = "ADDITIVE";
};



//-----------------------------------------------------------------------------
//	Debris
//-----------------------------------------------------------------------------

datablock ParticleData(LifelikeFirebombSmallDebrisTrailParticle)
{
   textureName = "art/shapes/particles/LifelikeEffectsPack/flame1";

   gravityCoefficient   = -0.2; 
   lifetimeMS           = 500;
   lifetimeVarianceMS   = 300;
   spinRandomMin        = -300;
   spinRandomMax        = 300;

   sizes[0]      = 0.5;
   sizes[1]      = 1.5;
   sizes[2]      = 0.5;

   times[0]      = 0.0;
   times[1]      = 0.2;
   times[2]      = 1.0;
   
   colors[0] = "1 0.9 0.8 1";
   colors[1] = "0.8 0.4 0 0.5";
   colors[2] = "0.8 0.4 0 0";

};

datablock ParticleEmitterData(LifelikeFirebombSmallDebrisTrailEmitter)
{
   ejectionPeriodMS = 20;
   periodVarianceMS = 10;
   ejectionVelocity = 5;
   velocityVariance = 2;
   thetaMin         = 0;
   thetaMax         = 10;
   phiReferenceVel  = 0;
   phiVariance      = 360;

   particles        = "LifelikeFirebombSmallDebrisTrailParticle";
   blendStyle = "ADDITIVE";
   ejectionOffset = "1";
};

datablock DebrisData(LifelikeFirebombSmallDebris)
{
   shapeFile = "art/shapes/particles/LifelikeEffectsPack/invisibledebris.dts";
   emitters[0] = LifelikeFirebombSmallDebrisTrailEmitter;
   elasticity = 0.4;
   friction = 0.25;
   numBounces = 1;
   bounceVariance = 0;
   explodeOnMaxBounce = false;
   staticOnMaxBounce = false;
   snapOnMaxBounce = false;
   minSpinSpeed = 100;
   maxSpinSpeed = 200;
   render2D = false;
   lifetime = 2;
   lifetimeVariance = 1;
   velocity = 10;
   velocityVariance = 4;
   fade = false;
   useRadiusMass = false;
   baseRadius = 0.3;
   gravModifier = 3.0;
   terminalVelocity = 50;
   ignoreWater = false;
};


//-----------------------------------------------------------------------------
//	Explosions
//-----------------------------------------------------------------------------



datablock ExplosionData(LifelikeFirebombSmallExplosion)
{
   //soundProfile = YourSoundDatablock;
   lifeTimeMS = 120;

   // Volume
   particleEmitter = LifelikeFirebombSmallGlowEmitter;  
   particleDensity = 5;
   particleRadius = 1.5;

   // Point emission
   emitter[0] = LifelikeFirebombSmallSmokeEmitter; 
   emitter[1] = LifelikeFirebombSmallFireballEmitter; 
   emitter[2] = LifelikeFirebombSmallFireBlastEmitter;
   emitter[3] = LifelikeFirebombSmallSparks1Emitter; 
      
   // Debris
   debris = LifelikeFirebombSmallDebris;
   debrisThetaMin = 10;
   debrisThetaMax = 60;
   debrisNum = 4;
   debrisNumVariance = 2;
   debrisVelocity = 15;
   debrisVelocityVariance = 5;
     
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