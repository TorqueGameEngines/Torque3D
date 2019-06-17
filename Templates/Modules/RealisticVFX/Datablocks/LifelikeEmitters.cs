//-----------------------------------------------------------------------------
// Lifelike Effects Pack - Ambient Particle Emitters
// Copyright Adam deGrandis 2012
//
// This file houses all the ambient emitters in the Lifelike Effects Pack.
// Thanks for your support!
//
//-----------------------------------------------------------------------------
//exec ("art/datablocks/LifelikeEffectsPack/LifelikeEmitters.cs");

//-----------------------------------------------------------------------------
// Smoke
//-----------------------------------------------------------------------------

datablock ParticleData(LifelikeSmokeLargeBlackParticle)
{
   textureName = "art/shapes/particles/LifelikeEffectsPack/smoke1";

   gravityCoefficient   = -0.2;  
   inheritedVelFactor   = 0.00;
   lifetimeMS           = 4000;
   lifetimeVarianceMS   = 250;
   spinRandomMin        = -30;
   spinRandomMax        = 30;

   sizes[0]      = 2;
   sizes[1]      = 4;
   sizes[2]      = 12;

   times[0]      = 0.0;
   times[1]      = 0.2;
   times[2]      = 1.0;
   
   colors[0]     = "0.1 0.1 0 0.1";
   colors[1]     = "0.7 0.7 0.6 1";
   colors[2]     = "1 0.9 0.8 0.0";
   
   windCoefficient = 1;

};

datablock ParticleEmitterData(LifelikeSmokeLargeBlackEmitter)
{
   ejectionPeriodMS = 130;
   periodVarianceMS = 50;
   ejectionVelocity = 1.0;
   velocityVariance = 0.0;
   thetaMin         = 0.0;
   thetaMax         = 90.0;
   phiReferenceVel  = 0;
   phiVariance      = 360;
   particles        = LifelikeSmokeLargeBlackParticle;
   blendStyle = "NORMAL";
   ejectionOffset = 0.5;
};


datablock ParticleData(LifelikeSmokeSmallBlackParticle)
{
   textureName = "art/shapes/particles/LifelikeEffectsPack/smoke1";

   gravityCoefficient   = -0.1;  
   lifetimeMS           = 2000;
   lifetimeVarianceMS   = 500;
   spinRandomMin        = -30;
   spinRandomMax        = 30;

   sizes[0]      = 1;
   sizes[1]      = 2;
   sizes[2]      = 3;

   times[0]      = 0.0;
   times[1]      = 0.2;
   times[2]      = 1.0;
   
   colors[0]     = "0.1 0.1 0 0.1";
   colors[1]     = "0.7 0.7 0.6 0.5";
   colors[2]     = "1 0.9 0.8 0.0";
   
   windCoefficient = 1;

};

datablock ParticleEmitterData(LifelikeSmokeSmallBlackEmitter)
{
   ejectionPeriodMS = 150;
   periodVarianceMS = 50;
   ejectionVelocity = 1.0;
   velocityVariance = 0.0;
   thetaMin         = 0.0;
   thetaMax         = 50.0;
   phiReferenceVel  = 0;
   phiVariance      = 360;
   particles        = LifelikeSmokeSmallBlackParticle;
   blendStyle = "NORMAL";
   ejectionOffset = 0.1;
};




datablock ParticleData(LifelikeSmokeLargeWhiteParticle)
{
   textureName = "art/shapes/particles/LifelikeEffectsPack/smoke2";

   gravityCoefficient   = -0.2;  
   inheritedVelFactor   = 0.00;
   lifetimeMS           = 4000;
   lifetimeVarianceMS   = 250;
   spinRandomMin        = -30;
   spinRandomMax        = 30;

   sizes[0]      = 2;
   sizes[1]      = 4;
   sizes[2]      = 12;

   times[0]      = 0.0;
   times[1]      = 0.2;
   times[2]      = 1.0;
   
   colors[0]     = "0.1 0.1 0 0.1";
   colors[1]     = "0.7 0.7 0.6 1";
   colors[2]     = "1 0.9 0.8 0.0";
   
   windCoefficient = 1;

};

datablock ParticleEmitterData(LifelikeSmokeLargeWhiteEmitter)
{
   ejectionPeriodMS = 130;
   periodVarianceMS = 50;
   ejectionVelocity = 1.0;
   velocityVariance = 0.0;
   thetaMin         = 0.0;
   thetaMax         = 90.0;
   phiReferenceVel  = 0;
   phiVariance      = 360;
   particles        = LifelikeSmokeLargeWhiteParticle;
   blendStyle = "NORMAL";
   ejectionOffset = 0.5;
};


datablock ParticleData(LifelikeSmokeSmallWhiteParticle)
{
   textureName = "art/shapes/particles/LifelikeEffectsPack/smoke2";

   gravityCoefficient   = -0.1;  
   lifetimeMS           = 2000;
   lifetimeVarianceMS   = 500;
   spinRandomMin        = -30;
   spinRandomMax        = 30;

   sizes[0]      = 1;
   sizes[1]      = 2;
   sizes[2]      = 3;

   times[0]      = 0.0;
   times[1]      = 0.2;
   times[2]      = 1.0;
   
   colors[0]     = "0.1 0.1 0 0.1";
   colors[1]     = "0.7 0.7 0.6 0.5";
   colors[2]     = "1 0.9 0.8 0.0";
   
   windCoefficient = 1;

};

datablock ParticleEmitterData(LifelikeSmokeSmallWhiteEmitter)
{
   ejectionPeriodMS = 150;
   periodVarianceMS = 50;
   ejectionVelocity = 1.0;
   velocityVariance = 0.0;
   thetaMin         = 0.0;
   thetaMax         = 70.0;
   phiReferenceVel  = 0;
   phiVariance      = 360;
   particles        = LifelikeSmokeSmallWhiteParticle;
   blendStyle = "NORMAL";
   ejectionOffset = 0.1;
};



//-----------------------------------------------------------------------------
// Fire
//-----------------------------------------------------------------------------


datablock ParticleData(LifelikeFireSmallParticle)
{
   textureName          = "art/shapes/particles/LifelikeEffectsPack/flame1";
   gravityCoefficient   = "-0.2";   
   lifetimeMS           = 1000;
   lifetimeVarianceMS   = 200;
   useInvAlpha          = true;
   spinRandomMin        = -140.0;
   spinRandomMax        = 140.0;

   sizes[0]      = "0.5";
   sizes[1]      = "1";
   sizes[2]      = "0.7";

   colors[0] = "0.8 0.6 1 0.5";
   colors[1] = "0.8 0.4 0 1";
   colors[2] = "0.8 0.4 0 0";
   
   times[0]      = 0.0;
   times[1]      = 0.2;
   times[2]      = 1.0;
};


datablock ParticleEmitterData(LifelikeFireSmallEmitter)
{
   ejectionPeriodMS = 70;
   periodVarianceMS = 30;

   ejectionVelocity = 0.3;
   velocityVariance = 0.2;

   thetaMin         = 0.0;
   thetaMax         = 70.0;

   ejectionOffset   = 0.15;
   
   particles        = "LifelikeFireSmallParticle";
   blendStyle = "ADDITIVE";
};



datablock ParticleData(LifelikeFireBigParticle)
{
   textureName          = "art/shapes/particles/LifelikeEffectsPack/flame1";
   gravityCoefficient   = "-0.2";  
   lifetimeMS           = 1400;
   lifetimeVarianceMS   = 500;
   useInvAlpha          = true;
   spinRandomMin        = -140.0;
   spinRandomMax        = 140.0;

   sizes[0]      = "1";
   sizes[1]      = "2";
   sizes[2]      = "1.5";

   colors[0] = "0.8 0.6 1 0.5";
   colors[1] = "0.8 0.4 0 0.9";
   colors[2] = "0.8 0.4 0 0";
   
   times[0]      = 0.0;
   times[1]      = 0.2;
   times[2]      = 1.0;
};

datablock ParticleEmitterData(LifelikeFireBigEmitter)
{
   ejectionPeriodMS = 70;
   periodVarianceMS = 30;

   ejectionVelocity = 0.5;
   velocityVariance = 0.0;

   thetaMin         = 0.0;
   thetaMax         = 70.0;

   ejectionOffset   = 0.5;
   
   particles        = LifelikeFireBigParticle;
   blendStyle = "ADDITIVE";
};



//-----------------------------------------------------------------------------
// Embers
//-----------------------------------------------------------------------------


datablock ParticleData(LifelikeEmbersSmallParticle)
{
   textureName          = "art/shapes/particles/LifelikeEffectsPack/ember1";
   gravityCoefficient   = "-0.2";   
   lifetimeMS           = 1500;
   lifetimeVarianceMS   = 200;
   useInvAlpha          = true;
   spinRandomMin        = -140.0;
   spinRandomMax        = 140.0;

   sizes[0]      = "0.5";
   sizes[1]      = "1";
   sizes[2]      = "0.7";

   colors[0] = "1 0.9 0.8 0.5";
   colors[1] = "1 0.9 0.8 1";
   colors[2] = "0.8 0.4 0 0";
   
   times[0]      = 0.0;
   times[1]      = 0.2;
   times[2]      = 1.0;
};

datablock ParticleEmitterData(LifelikeEmbersSmallEmitter)
{
   ejectionPeriodMS = 70;
   periodVarianceMS = 30;

   ejectionVelocity = 0.3;
   velocityVariance = 0.2;

   thetaMin         = 0.0;
   thetaMax         = 70.0;

   ejectionOffset   = 0.15;
   
   particles        = LifelikeEmbersSmallParticle;
   blendStyle = "ADDITIVE";
};


datablock ParticleData(LifelikeEmbersBigParticle)
{
   textureName          = "art/shapes/particles/LifelikeEffectsPack/ember1";
   gravityCoefficient   = "-0.2";  
   lifetimeMS           = 2000;
   lifetimeVarianceMS   = 500;
   useInvAlpha          = true;
   spinRandomMin        = -140.0;
   spinRandomMax        = 140.0;

   sizes[0]      = "1";
   sizes[1]      = "2";
   sizes[2]      = "1.5";

   colors[0] = "1 0.9 0.8 0.5";
   colors[1] = "1 0.9 0.8 1";
   colors[2] = "0.8 0.4 0 0";
   
   times[0]      = 0.0;
   times[1]      = 0.2;
   times[2]      = 1.0;
};

datablock ParticleEmitterData(LifelikeEmbersBigEmitter)
{
   ejectionPeriodMS = 70;
   periodVarianceMS = 30;

   ejectionVelocity = 0.5;
   velocityVariance = 0.0;

   thetaMin         = 0.0;
   thetaMax         = 70.0;

   ejectionOffset   = 0.5;
   
   particles        = LifelikeEmbersBigParticle;
   blendStyle = "ADDITIVE";
};



//-----------------------------------------------------------------------------
// Special
//-----------------------------------------------------------------------------

datablock ParticleData(LifelikeFlareSmokeParticle)
{
   textureName = "art/shapes/particles/LifelikeEffectsPack/smoke2";

   gravityCoefficient   = -0.2;  
   inheritedVelFactor   = 0.00;
   lifetimeMS           = 4000;
   lifetimeVarianceMS   = 250;
   spinRandomMin        = -30;
   spinRandomMax        = 30;

   sizes[0]      = 2;
   sizes[1]      = 4;
   sizes[2]      = 12;

   times[0]      = 0.0;
   times[1]      = 0.2;
   times[2]      = 1.0;
   
   colors[0]     = "1 0.1 0.1 0.1";
   colors[1]     = "1 0.3 0.3 1";
   colors[2]     = "1 0.6 0.6 0.0";
   
   windCoefficient = 1;

};

datablock ParticleEmitterData(LifelikeFlareSmokeEmitter)
{
   ejectionPeriodMS = 130;
   periodVarianceMS = 50;
   ejectionVelocity = 1.0;
   velocityVariance = 0.0;
   thetaMin         = 0.0;
   thetaMax         = 90.0;
   phiReferenceVel  = 0;
   phiVariance      = 360;
   particles        = LifelikeFlareSmokeParticle;
   blendStyle = "NORMAL";
   ejectionOffset = 0.5;
};