#pragma once

#ifndef _MATERIAL_PROPERTIES_MANAGER_H_
#define _MATERIAL_PROPERTIES_MANAGER_H_

#ifndef _SIMBASE_H_
#include "console/simBase.h"
#endif

#ifndef _TVECTOR_H_
#include "core/util/tvector.h"
#endif

#ifndef _TDICTIONARY_H_
#include "core/util/tDictionary.h"
#endif

#ifndef _GAMEBASE_H_
#include "T3D/gameBase/gameBase.h"
#endif

#ifndef SOUND_ASSET_H
#include "T3D/assets/SoundAsset.h"
#endif

#ifndef _BASEMATINSTANCE_H_
#include "materials/baseMatInstance.h"
#endif

#ifndef _MATERIALDEFINITION_H_
#include "materials/materialDefinition.h"
#endif

class ParticleEmitterData;
class DecalData;
class ExplosionData;


// -----------------------------------------------------------------------
// Defines all audio/visual responses for a single surface type
// -----------------------------------------------------------------------
class MaterialPropertiesData : public SimDataBlock
{
   typedef SimDataBlock Parent;
public:
   // ---- Sounds -------------------------------------------------------
   // Three velocity thresholds let slow/medium/fast impacts sound different.
   // e.g. a grenade roll vs a sniper hit.
   F32  softSoundVelocity;    // below this = soft sound
   F32  hardSoundVelocity;    // above this = hard sound, else medium

   DECLARE_SOUNDASSET(MaterialPropertiesData, SoftImpactSound)
   DECLARE_ASSET_SETGET(MaterialPropertiesData, SoftImpactSound)
   DECLARE_SOUNDASSET(MaterialPropertiesData, MediumImpactSound)
   DECLARE_ASSET_SETGET(MaterialPropertiesData, MediumImpactSound)
   DECLARE_SOUNDASSET(MaterialPropertiesData, HardImpactSound)
   DECLARE_ASSET_SETGET(MaterialPropertiesData, HardImpactSound)

   // Optional: separate sounds for melee (crowbar clink vs bullet ping
   // on the same metal surface feel very different)
   DECLARE_SOUNDASSET(MaterialPropertiesData, MeleeSoftSound)
   DECLARE_ASSET_SETGET(MaterialPropertiesData, MeleeSoftSound)
   DECLARE_SOUNDASSET(MaterialPropertiesData, MeleeHardSound)
   DECLARE_ASSET_SETGET(MaterialPropertiesData, MeleeHardSound)

   // ---- Decals -------------------------------------------------------
   // Small decal for bullets, large for explosions/big impacts
   DecalData* bulletDecal;
   S32 bulletDecalID;

   DecalData* largeDecal;     // used when impactForce > largeDecalForceThreshold
   S32 largeDecalID;

   F32         largeDecalForceThreshold;

   // How much to randomly rotate the decal (degrees). 360 for fully random,
   // 0 for always axis-aligned.
   F32  decalRotationVariance;

   // ---- Particle emitters --------------------------------------------
   // Each represents a different class of visual debris.
   // Use whichever make sense for this surface; null = skip.

   ParticleEmitterData* dustEmitter;      // general puff (concrete dust, dirt)
   S32 dustEmitterID;
   ParticleEmitterData* chunkEmitter;     // solid fragments (wood splinters, rock chips)
   S32 chunkEmitterID;
   ParticleEmitterData* sparkEmitter;     // sparks (metal surfaces)
   S32 sparkEmitterID;
   ParticleEmitterData* bloodEmitter;     // flesh hits
   S32 bloodEmitterID;
   ParticleEmitterData* splashEmitter;    // water/liquid surfaces
   S32 splashEmitterID;

   // Emitter lifetime overrides (0 = use datablock default)
   F32  dustEmitterDuration;
   F32  chunkEmitterDuration;
   F32  sparkEmitterDuration;
   F32  bloodEmitterDuration;

   // ---- Velocity-scaled emitter density ------------------------------
   // At minEffectVelocity, emit minParticleScale fraction of normal particles.
   // Scales linearly up to full density at fullEffectVelocity.
   F32  minEffectVelocity;
   F32  fullEffectVelocity;
   F32  minParticleScale;   // 0.0-1.0

   // ---- Explosion override -------------------------------------------
   // Some surfaces have a surface-specific explosion (e.g. hitting a
   // gas canister material, or a water surface).
   // If set, projectiles use this instead of their own explosion.
   ExplosionData* surfaceExplosion;   // nullable
   S32 surfaceExplosionID;

   // ---- Material-specific damage multiplier -------------------------
   // Lets you make glass fragile (2.0x) or armour resistant (0.5x)
   // without touching the projectile datablock.
   F32  damageMultiplier;

   // ---- Ricochet behaviour ------------------------------------------
   // If true, bullets may ricochet off this surface.
   bool  allowRicochet;
   F32   ricochetChance;      // 0.0-1.0
   F32   ricochetMinAngle;    // minimum glance angle (degrees) for ricochet
   F32   ricochetSpeedRetain; // fraction of speed kept after ricochet

   // ---- Penetration behaviour ---------------------------------------
   // Bullets can punch through this surface (e.g. thin wood, drywall).
   bool  allowPenetration;
   F32   penetrationResistance;  // how much velocity is lost (0=none, 1=stops bullet)
   F32   maxPenetrationThickness;// world units. Bullet stops if surface is thicker.

   // ---- Infrastructure -----------------------------------------------
   DECLARE_CONOBJECT(MaterialPropertiesData);
   MaterialPropertiesData();
   bool onAdd() override;
   bool preload(bool server, String& errorStr) override;
   static void initPersistFields();
   void packData(BitStream*) override;
   void unpackData(BitStream*) override;
};

class MaterialPropertiesManager : public SimObject
{
   typedef SimObject Parent;

public:
   typedef HashMap<String, String> typeMatMap;
   typeMatMap mMaterialMap;
   typedef HashMap<StringTableEntry, MaterialPropertiesData*> typeEffectMap;
   typeEffectMap  mEffectMap;

   MaterialPropertiesData* mDefault;
   DECLARE_CONOBJECT(MaterialPropertiesManager);
   /// <summary>
   /// Register an effect to a specific name
   /// </summary>
   /// <param name="name">Name of the effect.</param>
   /// <param name="impact_effect_data">The effect data</param>
   void registerEffect(StringTableEntry name, MaterialPropertiesData* impact_effect_data);

   /// <summary>
   /// Map material name to an effect name.
   /// </summary>
   /// <param name="mat_name">Material string to check for.</param>
   /// <param name="effect_name">The effect name to match to this string.</param>
   void mapMaterialToEffect(StringTableEntry mat_name, StringTableEntry effect_name);

   /// <summary>
   /// Returns the material effect data that relates to this material, otherwise re
   /// </summary>
   /// <param name="mat">The BaseMatInstance to match to a material.</param>
   /// <param name="surface_hint">Optional surface hint.</param>
   /// <returns>The MaterialEffectData resolved from this function.</returns>
   MaterialPropertiesData* resolve(BaseMatInstance* mat, StringTableEntry surface_hint = StringTable->EmptyString());

   void fireEffect(BaseMatInstance* mat,
                  const Point3F& pos,
                  const Point3F& normal,
                  F32 impactVelocity,
                  F32 impactForce,
                  bool isMelee,
                  bool clientOnly = true);

   void setDefaultEffect(MaterialPropertiesData* data);
   MaterialPropertiesData* getDefaultEffect() const { return mDefault; }

   void clear();

   MaterialPropertiesManager() : mDefault(nullptr) {}
};

extern MaterialPropertiesManager MaterialFXManager;

struct MaterialEffectResult
{
   MaterialPropertiesData* mat_effect = NULL;
   bool didRicochet = false;
   VectorF ricochetDirection;
   F32 ricochetSpeed = 0.0f;
   bool didPenetrate = false;
   F32 remainingVelocityFactor = 1.0f;
   F32 finalDamageMultiplier = 1.0f;
};

MaterialEffectResult resolveImpact(BaseMatInstance* mat,
   const VectorF& incomingVelocity,
   const VectorF& surfaceNormal,
   F32 impactForce,
   bool isMelee);

#endif // !_MATERIAL_EFFECT_MANAGER_H_
