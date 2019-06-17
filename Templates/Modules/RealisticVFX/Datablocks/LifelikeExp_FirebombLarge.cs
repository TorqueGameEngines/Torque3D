//-----------------------------------------------------------------------------
// Lifelike Effects Pack - Large Firebomb Explosion
// Copyright Adam deGrandis 2012
//
// Thanks for your support!
//
//-----------------------------------------------------------------------------
//exec ("art/datablocks/LifelikeEffectsPack/LifelikeExp_FirebombLarge.cs");


//-----------------------------------------------------------------------------
//	Emitters
//-----------------------------------------------------------------------------


datablock ParticleData(LifelikeFirebombLargeSmokeParticle)
{
   textureName          = "art/shapes/particles/LifelikeEffectsPack/smoke2";
   gravityCoefficient   = -0.1;
   lifetimeMS           = 1500;
   lifetimeVarianceMS   = 500;
   spinRandomMin = -50.0;
   spinRandomMax =  50.0;

   colors[0]     = "0.1 0.1 0.1 1";
   colors[1]     = "0.8 0.7 0.6 1";
   colors[2]     = "1 0.9 0.8 0";

   sizes[0]      = 4;
   sizes[1]      = 9;
   sizes[2]      = 12;

   times[0]      = 0.0;
   times[1]      = 0.3;
   times[2]      = 1.0;
};

datablock ParticleEmitterData(LifelikeFirebombLargeSmokeEmitter)
{
   ejectionPeriodMS = 25;
   periodVarianceMS = 5;
   ejectionVelocity = 2;
   velocityVariance = 1;
   thetaMin         = 0;
   thetaMax         = 90;
   phiReferenceVel  = 0;
   phiVariance      = 360;
   ejectionoffset   = 2;
   particles = "LifelikeFirebombLargeSmokeParticle";
   blendStyle = "NORMAL";
};

datablock ParticleData(LifelikeFirebombLargeFireBlastParticle)
{
   textureName          = "art/shapes/particles/LifelikeEffectsPack/fireblast";
   lifetimeMS           = 250;
   lifetimeVarianceMS   = 50;

   colors[0]     = "1 0.9 0.8 0";
   colors[1]     = "0.8 0.4 0 1";
   colors[2]     = "0.8 0.4 0 0";

   sizes[0]      = 2;
   sizes[1]      = 15;
   sizes[2]      = 2;

   times[0]      = 0.0;
   times[1]      = 0.3;
   times[2]      = 1.0;
};

datablock ParticleEmitterData(LifelikeFirebombLargeFireBlastEmitter)
{
   ejectionPeriodMS = 10;
   periodVarianceMS = 2;
   ejectionVelocity = 50;
   velocityVariance = 10;
   thetaMin         = 0;
   thetaMax         = 70;
   phiReferenceVel  = 0;
   phiVariance      = 360;
   orientOnVelocity = true;
   orientParticles  = true;
   particles = "LifelikeFirebombLargeFireBlastParticle";
   blendStyle = "ADDITIVE";
};

datablock ParticleData(LifelikeFirebombLargeSparks1Particle)
{
   textureName          = "art/shapes/particles/LifelikeEffectsPack/spark1";
   lifetimeMS           = 300;
   lifetimeVarianceMS   = 20;
   gravityCoefficient   = 0;

   colors[0]     = "1.0 0.9 0.8 0.4";
   colors[1]     = "1.0 0.9 0.8 1";
   colors[2]     = "0.8 0.4 0 0.0";

   sizes[0]      = 6;
   sizes[1]      = 4;
   sizes[2]      = 1;

   times[0]      = 0.0;
   times[1]      = 0.5;
   times[2]      = 1.0;
};

datablock ParticleEmitterData(LifelikeFirebombLargeSparks1Emitter)
{
   ejectionPeriodMS = 7;
   periodVarianceMS = 2;
   ejectionVelocity = 40;
   velocityVariance = 30;
   thetaMin         = 0;
   thetaMax         = 90;
   phiReferenceVel  = 0;
   phiVariance      = 360;
   ejectionoffset   = 0;
   orientOnVelocity = true;
   orientParticles  = true;
   particles = "LifelikeFirebombLargeSparks1Particle";
   blendStyle = "ADDITIVE";
};


datablock ParticleData(LifelikeFirebombLargeGlowParticle)
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

datablock ParticleEmitterData(LifelikeFirebombLargeGlowEmitter)
{
   ejectionPeriodMS = 20;
   periodVarianceMS = 5;
   ejectionVelocity = 3;
   velocityVariance = 2;
   thetaMin         = 0;
   thetaMax         = 120;
   phiReferenceVel  = 0;
   phiVariance      = 360;
   
   particles = "LifelikeFirebombLargeGlowParticle";
   blendStyle = "ADDITIVE";
};


datablock ParticleData(LifelikeFirebombLargeFireballParticle)
{
   textureName          = "art/shapes/particles/LifelikeEffectsPack/flame1";
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

datablock ParticleEmitterData(LifelikeFirebombLargeFireballEmitter)
{
   ejectionPeriodMS = 7;
   periodVarianceMS = 3;
   ejectionVelocity = 3;
   velocityVariance = 2;
   thetaMin         = 0;
   thetaMax         = 120;
   phiReferenceVel  = 0;
   phiVariance      = 360;
   ejectionoffset   = 3;
   
   particles = "LifelikeFirebombLargeFireballParticle";
   blendStyle = "ADDITIVE";
};



//-----------------------------------------------------------------------------
//	Debris
//-----------------------------------------------------------------------------

datablock ParticleData(LifelikeFirebombLargeDebrisTrailParticle)
{
   textureName = "art/shapes/particles/LifelikeEffectsPack/flame1";

   gravityCoefficient   = -0.2; 
   lifetimeMS           = 500;
   lifetimeVarianceMS   = 300;
   spinRandomMin        = -300;
   spinRandomMax        = 300;

   sizes[0]      = 1;
   sizes[1]      = 3;
   sizes[2]      = 1;

   times[0]      = 0.0;
   times[1]      = 0.2;
   times[2]      = 1.0;
   
   colors[0] = "1 0.9 0.8 1";
   colors[1] = "0.8 0.4 0 0.5";
   colors[2] = "0.8 0.4 0 0";

};

datablock ParticleEmitterData(LifelikeFirebombLargeDebrisTrailEmitter)
{
   ejectionPeriodMS = 20;
   periodVarianceMS = 10;
   ejectionVelocity = 5;
   velocityVariance = 2;
   thetaMin         = 0;
   thetaMax         = 10;
   phiReferenceVel  = 0;
   phiVariance      = 360;

   particles        = "LifelikeFirebombLargeDebrisTrailParticle";
   blendStyle = "ADDITIVE";
   ejectionOffset = "2";
};

datablock DebrisData(LifelikeFirebombLargeDebris)
{
   shapeFile = "art/shapes/particles/LifelikeEffectsPack/invisibledebris.dts";
   emitters[0] = LifelikeFirebombLargeDebrisTrailEmitter;
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
   velocity = 30;
   velocityVariance = 10;
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



datablock ExplosionData(LifelikeFirebombLargeExplosion)
{
   //soundProfile = YourSoundDatablock;
   lifeTimeMS = 150;

   // Volume
   particleEmitter = LifelikeFirebombLargeGlowEmitter;  
   particleDensity = 5;
   particleRadius = 3;

   // Point emission
   emitter[0] = LifelikeFirebombLargeSmokeEmitter; 
   emitter[1] = LifelikeFirebombLargeFireballEmitter; 
   emitter[2] = LifelikeFirebombLargeFireBlastEmitter;
   emitter[3] = LifelikeFirebombLargeSparks1Emitter; 
      
   // Debris
   debris = LifelikeFirebombLargeDebris;
   debrisThetaMin = 10;
   debrisThetaMax = 60;
   debrisNum = 4;
   debrisNumVariance = 2;
   debrisVelocity = 25;
   debrisVelocityVariance = 5;
     
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