#include "platform/platform.h"

#include "console/consoleTypes.h"
#include "materials/materialPropertiesManager.h"
#include "T3D/decal/decalManager.h"
#include "T3D/decal/decalData.h"
#include "T3D/fx/particleEmitter.h"
#include "T3D/fx/explosion.h"
#include "sfx/sfxSystem.h"
#include "math/mathUtils.h"
#include "math/mRandom.h"
#include "core/stream/bitStream.h"
#include "console/engineAPI.h"

//------------------------------------------------------
// EFFECT DATA
//------------------------------------------------------

IMPLEMENT_CO_DATABLOCK_V1(MaterialPropertiesData);

MaterialPropertiesData::MaterialPropertiesData()
{
   softSoundVelocity = 5.0f;
   hardSoundVelocity = 40.0f;

   INIT_ASSET(SoftImpactSound);
   INIT_ASSET(MediumImpactSound);
   INIT_ASSET(HardImpactSound);
   INIT_ASSET(RicochetSound);
   INIT_ASSET(MeleeSoftSound);
   INIT_ASSET(MeleeHardSound);

   bulletDecal = NULL;
   bulletDecalID = 0;

   largeDecal = NULL;
   largeDecalID = 0;

   largeDecalForceThreshold = 500.0f;
   decalRotationVariance = 360.0f;

   dustEmitter = NULL;
   dustEmitterID = 0;

   chunkEmitter = NULL;
   chunkEmitterID = 0;

   sparkEmitter = NULL;
   sparkEmitterID = 0;

   bloodEmitter = NULL;
   bloodEmitterID = 0;

   splashEmitter = NULL;
   splashEmitterID = 0;

   dustEmitterDuration = 0.0f;
   chunkEmitterDuration = 0.0f;
   sparkEmitterDuration = 0.0f;
   bloodEmitterDuration = 0.0f;

   minEffectVelocity = 1.0f;
   fullEffectVelocity = 30.0f;
   minParticleScale = 0.1f;

   surfaceExplosion = NULL;
   surfaceExplosionID = 0;
   damageMultiplier = 1.0f;

   allowRicochet = false;
   ricochetChance = 0.3f;
   ricochetMinAngle = 75.0f;
   ricochetSpeedRetain = 0.6f;

   allowPenetration = false;
   penetrationResistance = 0.5f;
   maxPenetrationThickness = 0.3f;
}

bool MaterialPropertiesData::onAdd()
{
   if (!Parent::onAdd())
      return false;

   MaterialFXManager.registerEffect(getName(), this);

   return true;
}

void MaterialPropertiesData::initPersistFields()
{
   docsURL;

   addGroup("Sounds");
   addFieldV("softSoundVelocity", TypeRangedF32,
      Offset(softSoundVelocity, MaterialPropertiesData),
      &CommonValidators::PositiveFloat,
      "Impact velocity below which the soft sound plays.");
   addFieldV("hardSoundVelocity", TypeRangedF32,
      Offset(hardSoundVelocity, MaterialPropertiesData),
      &CommonValidators::PositiveFloat,
      "Impact velocity above which the hard sound plays.");

   INITPERSISTFIELD_SOUNDASSET(SoftImpactSound, MaterialPropertiesData,
      "Sound for low-velocity impacts.");
   INITPERSISTFIELD_SOUNDASSET(MediumImpactSound, MaterialPropertiesData,
      "Sound for medium-velocity impacts.");
   INITPERSISTFIELD_SOUNDASSET(HardImpactSound, MaterialPropertiesData,
      "Sound for high-velocity impacts (bullets, fast projectiles).");
   INITPERSISTFIELD_SOUNDASSET(RicochetSound, MaterialPropertiesData,
      "Sound for high-velocity ricochets (bullets, fast projectiles).");
   INITPERSISTFIELD_SOUNDASSET(MeleeSoftSound, MaterialPropertiesData,
      "Melee soft hit sound override. Falls back to SoftImpactSound.");
   INITPERSISTFIELD_SOUNDASSET(MeleeHardSound, MaterialPropertiesData,
      "Melee hard hit sound override. Falls back to HardImpactSound.");
   endGroup("Sounds");

   addGroup("Decals");
   addField("bulletDecal", TYPEID<DecalData>(),
      Offset(bulletDecal, MaterialPropertiesData),
      "Small decal placed for bullet impacts.");
   addField("largeDecal", TYPEID<DecalData>(),
      Offset(largeDecal, MaterialPropertiesData),
      "Larger decal used when impact force exceeds largeDecalForceThreshold.");
   addFieldV("largeDecalForceThreshold", TypeRangedF32,
      Offset(largeDecalForceThreshold, MaterialPropertiesData),
      &CommonValidators::PositiveFloat,
      "Impact force above which the large decal is used instead of bulletDecal.");
   addFieldV("decalRotationVariance", TypeRangedF32,
      Offset(decalRotationVariance, MaterialPropertiesData),
      &CommonValidators::DegreeRange,
      "How much to randomly rotate placed decals. 360 = fully random.");
   endGroup("Decals");

   addGroup("Particle Emitters");
   addField("dustEmitter", TYPEID<ParticleEmitterData>(),
      Offset(dustEmitter, MaterialPropertiesData),
      "General dust/puff emitter (concrete, dirt, sand).");
   addField("chunkEmitter", TYPEID<ParticleEmitterData>(),
      Offset(chunkEmitter, MaterialPropertiesData),
      "Solid fragment emitter (wood chips, stone shards).");
   addField("sparkEmitter", TYPEID<ParticleEmitterData>(),
      Offset(sparkEmitter, MaterialPropertiesData),
      "Spark emitter for metal surfaces.");
   addField("bloodEmitter", TYPEID<ParticleEmitterData>(),
      Offset(bloodEmitter, MaterialPropertiesData),
      "Blood emitter for flesh hits.");
   addField("splashEmitter", TYPEID<ParticleEmitterData>(),
      Offset(splashEmitter, MaterialPropertiesData),
      "Liquid splash emitter.");

   addFieldV("dustEmitterDuration", TypeRangedF32,
      Offset(dustEmitterDuration, MaterialPropertiesData),
      &CommonValidators::PositiveFloat,
      "Override emitter lifetime in seconds (0 = use datablock default).");
   addFieldV("chunkEmitterDuration", TypeRangedF32,
      Offset(chunkEmitterDuration, MaterialPropertiesData),
      &CommonValidators::PositiveFloat, "");
   addFieldV("sparkEmitterDuration", TypeRangedF32,
      Offset(sparkEmitterDuration, MaterialPropertiesData),
      &CommonValidators::PositiveFloat, "");
   addFieldV("bloodEmitterDuration", TypeRangedF32,
      Offset(bloodEmitterDuration, MaterialPropertiesData),
      &CommonValidators::PositiveFloat, "");
   endGroup("Particle Emitters");

   addGroup("Velocity Scaling");
   addFieldV("minEffectVelocity", TypeRangedF32,
      Offset(minEffectVelocity, MaterialPropertiesData),
      &CommonValidators::PositiveFloat,
      "Impact velocity at which particle emission starts.");
   addFieldV("fullEffectVelocity", TypeRangedF32,
      Offset(fullEffectVelocity, MaterialPropertiesData),
      &CommonValidators::PositiveFloat,
      "Impact velocity at which full particle density is reached.");
   addFieldV("minParticleScale", TypeRangedF32,
      Offset(minParticleScale, MaterialPropertiesData),
      &CommonValidators::NormalizedFloat,
      "Fraction of particles emitted at minEffectVelocity (0-1).");
   endGroup("Velocity Scaling");

   addGroup("Surface Properties");
   addFieldV("damageMultiplier", TypeRangedF32,
      Offset(damageMultiplier, MaterialPropertiesData),
      &CommonValidators::PositiveFloat,
      "Multiplies incoming damage. >1.0 = fragile, <1.0 = resistant.");
   addField("surfaceExplosion", TYPEID<ExplosionData>(),
      Offset(surfaceExplosion, MaterialPropertiesData),
      "If set, projectiles use this explosion instead of their own "
      "when hitting this surface.");
   endGroup("Surface Properties");

   addGroup("Ricochet");
   addField("allowRicochet", TypeBool,
      Offset(allowRicochet, MaterialPropertiesData),
      "Bullets may ricochet off this surface.");
   addFieldV("ricochetChance", TypeRangedF32,
      Offset(ricochetChance, MaterialPropertiesData),
      &CommonValidators::NormalizedFloat,
      "Probability of ricochet per impact (0-1).");
   addFieldV("ricochetMinAngle", TypeRangedF32,
      Offset(ricochetMinAngle, MaterialPropertiesData),
      &CommonValidators::PosDegreeRangeQuarter,
      "Minimum glance angle in degrees for ricochet to occur.");
   addFieldV("ricochetSpeedRetain", TypeRangedF32,
      Offset(ricochetSpeedRetain, MaterialPropertiesData),
      &CommonValidators::NormalizedFloat,
      "Fraction of velocity retained after ricochet.");
   endGroup("Ricochet");

   addGroup("Penetration");
   addField("allowPenetration", TypeBool,
      Offset(allowPenetration, MaterialPropertiesData),
      "Bullets can punch through this surface type.");
   addFieldV("penetrationResistance", TypeRangedF32,
      Offset(penetrationResistance, MaterialPropertiesData),
      &CommonValidators::NormalizedFloat,
      "Fraction of bullet velocity absorbed per unit of thickness (0-1).");
   addFieldV("maxPenetrationThickness", TypeRangedF32,
      Offset(maxPenetrationThickness, MaterialPropertiesData),
      &CommonValidators::PositiveFloat,
      "Maximum surface thickness in world units a bullet can punch through.");
   endGroup("Penetration");

   Parent::initPersistFields();
}

bool MaterialPropertiesData::preload(bool server, String& errorStr)
{
   if (!Parent::preload(server, errorStr))
      return false;

   if (!server)
   {
      auto resolveDB = [&](auto*& ptr, SimObjectId id, const char* fieldName)
      {
         if (!ptr && id != 0)
            if (!Sim::findObject(id, ptr))
               Con::errorf("ImpactEffectData(%s): bad datablockId (%s): %d",
                  getName(), fieldName, id);
      };

      resolveDB(bulletDecal, bulletDecalID, "bulletDecal");
      resolveDB(largeDecal, largeDecalID, "largeDecal");
      resolveDB(dustEmitter, dustEmitterID, "dustEmitter");
      resolveDB(chunkEmitter, chunkEmitterID, "chunkEmitter");
      resolveDB(sparkEmitter, sparkEmitterID, "sparkEmitter");
      resolveDB(bloodEmitter, bloodEmitterID, "bloodEmitter");
      resolveDB(splashEmitter, splashEmitterID, "splashEmitter");
      resolveDB(surfaceExplosion, surfaceExplosionID, "surfaceExplosion");

      // preload our sounds if they exist.
      if (isSoftImpactSoundValid())
      {
         getSoftImpactSoundProfile();
      }

      if (isMediumImpactSoundValid())
      {
         getMediumImpactSoundProfile();
      }

      if (isHardImpactSoundValid())
      {
         getHardImpactSoundProfile();
      }

      if (isRicochetSoundValid())
      {
         getRicochetSoundProfile();
      }

      if (isMeleeSoftSoundValid())
      {
         getMeleeSoftSoundProfile();
      }

      if (isMeleeHardSoundValid())
      {
         getMeleeHardSoundProfile();
      }

   }

   return true;
}

void MaterialPropertiesData::packData(BitStream* stream)
{
   Parent::packData(stream);

   stream->write(softSoundVelocity);
   stream->write(hardSoundVelocity);

   PACKDATA_SOUNDASSET(SoftImpactSound);
   PACKDATA_SOUNDASSET(MediumImpactSound);
   PACKDATA_SOUNDASSET(HardImpactSound);
   PACKDATA_SOUNDASSET(RicochetSound);
   PACKDATA_SOUNDASSET(MeleeSoftSound);
   PACKDATA_SOUNDASSET(MeleeHardSound);

   auto writeDB = [&](SimDataBlock* db)
   {
      if (stream->writeFlag(db != nullptr))
         stream->writeRangedU32(db->getId(),
            DataBlockObjectIdFirst, DataBlockObjectIdLast);
   };
   writeDB(bulletDecal);
   writeDB(largeDecal);
   stream->write(largeDecalForceThreshold);
   stream->write(decalRotationVariance);

   writeDB(dustEmitter);
   writeDB(chunkEmitter);
   writeDB(sparkEmitter);
   writeDB(bloodEmitter);
   writeDB(splashEmitter);
   stream->write(dustEmitterDuration);
   stream->write(chunkEmitterDuration);
   stream->write(sparkEmitterDuration);
   stream->write(bloodEmitterDuration);

   stream->write(minEffectVelocity);
   stream->write(fullEffectVelocity);
   stream->write(minParticleScale);

   writeDB(surfaceExplosion);
   stream->write(damageMultiplier);

   stream->writeFlag(allowRicochet);
   stream->write(ricochetChance);
   stream->write(ricochetMinAngle);
   stream->write(ricochetSpeedRetain);

   stream->writeFlag(allowPenetration);
   stream->write(penetrationResistance);
   stream->write(maxPenetrationThickness);
}

void MaterialPropertiesData::unpackData(BitStream* stream)
{
   Parent::unpackData(stream);

   stream->read(&softSoundVelocity);
   stream->read(&hardSoundVelocity);

   UNPACKDATA_SOUNDASSET(SoftImpactSound);
   UNPACKDATA_SOUNDASSET(MediumImpactSound);
   UNPACKDATA_SOUNDASSET(HardImpactSound);
   UNPACKDATA_SOUNDASSET(RicochetSound);
   UNPACKDATA_SOUNDASSET(MeleeSoftSound);
   UNPACKDATA_SOUNDASSET(MeleeHardSound);

   // Resolve IDs after network transmission
   if (stream->readFlag()) bulletDecalID = stream->readRangedU32(DataBlockObjectIdFirst, DataBlockObjectIdLast);
   if (stream->readFlag()) largeDecalID = stream->readRangedU32(DataBlockObjectIdFirst, DataBlockObjectIdLast);
   stream->read(&largeDecalForceThreshold);
   stream->read(&decalRotationVariance);

   if (stream->readFlag()) dustEmitterID = stream->readRangedU32(DataBlockObjectIdFirst, DataBlockObjectIdLast);
   if (stream->readFlag()) chunkEmitterID = stream->readRangedU32(DataBlockObjectIdFirst, DataBlockObjectIdLast);
   if (stream->readFlag()) sparkEmitterID = stream->readRangedU32(DataBlockObjectIdFirst, DataBlockObjectIdLast);
   if (stream->readFlag()) bloodEmitterID = stream->readRangedU32(DataBlockObjectIdFirst, DataBlockObjectIdLast);
   if (stream->readFlag()) splashEmitterID = stream->readRangedU32(DataBlockObjectIdFirst, DataBlockObjectIdLast);
   stream->read(&dustEmitterDuration);
   stream->read(&chunkEmitterDuration);
   stream->read(&sparkEmitterDuration);
   stream->read(&bloodEmitterDuration);

   stream->read(&minEffectVelocity);
   stream->read(&fullEffectVelocity);
   stream->read(&minParticleScale);

   if (stream->readFlag()) surfaceExplosionID = stream->readRangedU32(DataBlockObjectIdFirst, DataBlockObjectIdLast);
   stream->read(&damageMultiplier);

   allowRicochet = stream->readFlag();
   stream->read(&ricochetChance);
   stream->read(&ricochetMinAngle);
   stream->read(&ricochetSpeedRetain);

   allowPenetration = stream->readFlag();
   stream->read(&penetrationResistance);
   stream->read(&maxPenetrationThickness);
}

//------------------------------------------------------
// MATERIAL EFFECT MANAGER
//------------------------------------------------------

IMPLEMENT_CONOBJECT(MaterialPropertiesManager);

MaterialPropertiesManager MaterialFXManager;

void MaterialPropertiesManager::clear()
{
   mEffectMap.clear();
   mMaterialMap.clear();
   mDefault = NULL;
}

void MaterialPropertiesManager::registerEffect(StringTableEntry name, MaterialPropertiesData* impact_effect_data)
{
   mEffectMap[name] = impact_effect_data;
}

void MaterialPropertiesManager::mapMaterialToEffect(StringTableEntry mat_name, StringTableEntry effect_name)
{
   mMaterialMap[String(mat_name)] = String(effect_name);
}

MaterialPropertiesData* MaterialPropertiesManager::resolve(BaseMatInstance* mat, StringTableEntry surface_hint)
{
   if (surface_hint && surface_hint[0])
   {
      auto iter = mEffectMap.find(String(surface_hint));
      if (iter != mEffectMap.end())
         return iter->value;
   }

   if (mat)
   {
      Material* baseMat = dynamic_cast<Material*>(mat->getMaterial());
      if (baseMat)
      {
         StringTableEntry effectField = baseMat->getDataField(StringTable->insert("impactEffect"), NULL);
         if (effectField && effectField[0])
         {
            MaterialPropertiesData* mat_effect = NULL;
            if (Sim::findObject(effectField, mat_effect))
               return mat_effect;

            typeEffectMap::iterator iter = mEffectMap.find(effectField);
            if (iter != mEffectMap.end())
               return iter->value;
         }

         StringTableEntry matName = baseMat->getName();
         if (matName && matName[0])
         {
            typeMatMap::iterator mapIt = mMaterialMap.find(String(matName));
            if (mapIt != mMaterialMap.end())
            {
               typeEffectMap::iterator effectIt = mEffectMap.find(mapIt->value);
               if (effectIt != mEffectMap.end())
                  return effectIt->value;
            }
         }

         if (matName && matName[0])
         {
            String matStr(matName);
            for (auto& pair : mMaterialMap)
            {
               if (matStr.find(pair.key, 0, String::NoCase) != String::NPos)
               {
                  auto effectIt = mEffectMap.find(pair.value);
                  if (effectIt != mEffectMap.end())
                     return effectIt->value;
               }
            }
         }
      }
   }

   return mDefault;
}

void MaterialPropertiesManager::fireEffect(BaseMatInstance* mat,
                                       const Point3F& pos,
                                       const Point3F& normal,
                                       F32 impactVelocity,
                                       F32 impactForce,
                                       bool isMelee,
                                       bool isRicochet,
                                       bool clientOnly)
{
   MaterialPropertiesData* fx = resolve(mat);
   if (!fx) return;

   SFXTrack* snd = NULL;

   if (isMelee)
   {
      snd = (impactVelocity >= fx->hardSoundVelocity)
         ? fx->getMeleeHardSoundProfile()
         : fx->getMeleeSoftSoundProfile();

      // Fall back to projectile sounds if melee sounds not set
      if (!snd)
      {
         snd = (impactVelocity >= fx->hardSoundVelocity)
            ? fx->getHardImpactSoundProfile()
            : fx->getSoftImpactSoundProfile();
      }
   }
   else
   {
      if (impactVelocity < fx->softSoundVelocity)
            snd = fx->getSoftImpactSoundProfile();
        else if (impactVelocity >= fx->hardSoundVelocity)
            snd = fx->getHardImpactSoundProfile();
        else
            snd = fx->getMediumImpactSoundProfile();

      if (isRicochet && fx->isRicochetSoundValid())
         snd = fx->getRicochetSoundProfile();
   }

   if (snd)
   {
      MatrixF soundMat(true);
      soundMat.setColumn(3, pos);
      SFX->playOnce(snd, &soundMat);
   }

   F32 densityScale = 1.0f;
   if (impactVelocity < fx->fullEffectVelocity)
   {
      F32 t = (impactVelocity - fx->minEffectVelocity) / (fx->fullEffectVelocity - fx->minEffectVelocity);
      t = mClampF(t, 0.0f, 1.0f);
      densityScale = mLerp(fx->minParticleScale, 1.0f, t);
   }

   auto spawnEmitter = [&](ParticleEmitterData* eData, F32 duration)
   {
      if (!eData || densityScale < 0.01f) return;

      ParticleEmitter* pe = new ParticleEmitter;
      pe->onNewDataBlock(eData, false);
      if (!pe->registerObject()) { delete pe; return; }

      U32 ms = (duration > 0)
         ? (U32)(duration * 1000.0f)
         : 80u;  // short burst default

      pe->emitParticles(pos, Point3F(0, 0, 1), normal,
         VectorF(0, 0, 0),
         (U32)(ms * densityScale));
      pe->deleteWhenEmpty();
   };

   spawnEmitter(fx->dustEmitter, fx->dustEmitterDuration);
   spawnEmitter(fx->chunkEmitter, fx->chunkEmitterDuration);
   spawnEmitter(fx->sparkEmitter, fx->sparkEmitterDuration);
   spawnEmitter(fx->bloodEmitter, fx->bloodEmitterDuration);

   DecalData* decal = (impactForce >= fx->largeDecalForceThreshold && fx->largeDecal)
      ? fx->largeDecal
      : fx->bulletDecal;
   if (decal)
   {
      F32 rot = (fx->decalRotationVariance > 0)
         ? gRandGen.randF() * mDegToRad(fx->decalRotationVariance)
         : 0.0f;
      gDecalManager->addDecal(pos, normal, rot, decal);
   }


}

void MaterialPropertiesManager::setDefaultEffect(MaterialPropertiesData* data)
{
   mDefault = data;
}

MaterialPropertiesResult resolveImpact( BaseMatInstance* mat,
                                    const VectorF& incomingVelocity,
                                    const VectorF& surfaceNormal,
                                    F32 impactForce,
                                    bool isMelee)
{

   MaterialPropertiesResult result;

   result.mat_effect = MaterialFXManager.resolve(mat);
   if (!result.mat_effect)
   {
      result.finalDamageMultiplier = 1.0f;
      return result;
   }

   MaterialPropertiesData* fx = result.mat_effect;
   result.finalDamageMultiplier = fx->damageMultiplier;

   F32 speed = incomingVelocity.len();

   if (fx->allowRicochet && !isMelee && speed > 0.1f)
   {
      VectorF inDir = incomingVelocity / speed;

      F32 cosGlance = mFabs(mDot(inDir, surfaceNormal));
      F32 glanceDeg = mRadToDeg(mAcos(mClampF(cosGlance, 0.0f, 1.0f)));


      bool angleOk = glanceDeg >= fx->ricochetMinAngle;

      if (angleOk && gRandGen.randF() < fx->ricochetChance)
      {
         result.didRicochet = true;

         VectorF reflected = inDir - surfaceNormal * (2.0f * mDot(inDir, surfaceNormal));

         F32 scatter = mDegToRad(5.0f);
         VectorF euler(
            (gRandGen.randF() - 0.5f) * scatter,
            (gRandGen.randF() - 0.5f) * scatter,
            (gRandGen.randF() - 0.5f) * scatter);

         MatrixF scatterMat;
         scatterMat.set(EulerF(euler));
         scatterMat.mulV(reflected);
         reflected.normalizeSafe();

         result.ricochetDirection = reflected;
         result.ricochetSpeed = speed * fx->ricochetSpeedRetain;
      }
   }

   if (fx->allowPenetration && !isMelee && !result.didRicochet)
   {
      result.didPenetrate = true;
      result.remainingVelocityFactor = mMax(0.0f, 1.0f - fx->penetrationResistance);
   }

   return result;
}

DefineEngineMethod(MaterialPropertiesManager, map, void, (const char* materialPattern, MaterialPropertiesData* effect), ,
   "Map a material name pattern to a MaterialEffectData.\n"
   "Pattern is a substring match on the material name, so 'Concrete' matches 'Concrete_Cracked'.\n"
   "@param materialPattern Substring to match against material names.\n"
   "@param effect The MaterialEffectData datablock to use for matching materials.")
{
   if (!effect)
   {
      Con::errorf("MaterialEffectManager::map() -- effect is null, pattern: %s", materialPattern);
      return;
   }
   // Register the effect by its datablock name so resolve() can find it,
   // then map the pattern string to that name.
   StringTableEntry effectName = StringTable->insert(effect->getName());
   object->registerEffect(effectName, effect);
   object->mapMaterialToEffect(StringTable->insert(materialPattern), effectName);
}

DefineEngineMethod(MaterialPropertiesManager, setDefault, void, (MaterialPropertiesData* effect), ,
   "Set the fallback MaterialEffectData used when no material pattern matches.\n"
   "@param effect The MaterialEffectData datablock to use as the default.")
{
   if (!effect)
   {
      Con::errorf("MaterialEffectManager::setDefault() -- effect is null");
      return;
   }
   object->setDefaultEffect(effect);
}

DefineEngineMethod(MaterialPropertiesManager, clear, void, (), ,
   "Clear the effect manager maps.\n")
{
   object->clear();
}
