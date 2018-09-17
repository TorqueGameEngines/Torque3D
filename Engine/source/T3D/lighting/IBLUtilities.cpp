#include "console/engineAPI.h"
#include "materials/shaderData.h"
#include "gfx/gfxTextureManager.h"
#include "gfx/gfxTransformSaver.h"
#include "gfx/bitmap/cubemapSaver.h"

namespace IBLUtilities
{
   void GenerateIrradianceMap(GFXTextureTargetRef renderTarget, GFXCubemapHandle cubemap, GFXCubemapHandle &cubemapOut)
   {
      GFXTransformSaver saver;

      GFXStateBlockRef irrStateBlock;

      ShaderData *irrShaderData;
      GFXShaderRef irrShader = Sim::findObject("IrradianceShader", irrShaderData) ? irrShaderData->getShader() : NULL;
      if (!irrShader)
      {
         Con::errorf("IBLUtilities::GenerateIrradianceMap() - could not find IrradianceShader");
         return;
      }

      GFXShaderConstBufferRef irrConsts = irrShader->allocConstBuffer();
      GFXShaderConstHandle* irrEnvMapSC = irrShader->getShaderConstHandle("$environmentMap");
      GFXShaderConstHandle* irrFaceSC = irrShader->getShaderConstHandle("$face");

      GFXStateBlockDesc desc;
      desc.zEnable = false;
      desc.samplersDefined = true;
      desc.samplers[0].addressModeU = GFXAddressClamp;
      desc.samplers[0].addressModeV = GFXAddressClamp;
      desc.samplers[0].addressModeW = GFXAddressClamp;
      desc.samplers[0].magFilter = GFXTextureFilterLinear;
      desc.samplers[0].minFilter = GFXTextureFilterLinear;
      desc.samplers[0].mipFilter = GFXTextureFilterLinear;

      irrStateBlock = GFX->createStateBlock(desc);

      GFX->pushActiveRenderTarget();
      GFX->setShader(irrShader);
      GFX->setShaderConstBuffer(irrConsts);
      GFX->setStateBlock(irrStateBlock);
      GFX->setVertexBuffer(NULL);
      GFX->setCubeTexture(0, cubemap);

      for (U32 i = 0; i < 6; i++)
      {
         renderTarget->attachTexture(GFXTextureTarget::Color0, cubemapOut, i);
         irrConsts->setSafe(irrFaceSC, (S32)i);
         GFX->setActiveRenderTarget(renderTarget);
         GFX->clear(GFXClearTarget, LinearColorF::BLACK, 1.0f, 0);
         GFX->drawPrimitive(GFXTriangleList, 0, 3);
         renderTarget->resolve();
      }

      GFX->popActiveRenderTarget();
   }

   void GeneratePrefilterMap(GFXTextureTargetRef renderTarget, GFXCubemapHandle cubemap, U32 mipLevels, GFXCubemapHandle &cubemapOut)
   {
      GFXTransformSaver saver;

      ShaderData *prefilterShaderData;
      GFXShaderRef prefilterShader = Sim::findObject("PrefiterCubemapShader", prefilterShaderData) ? prefilterShaderData->getShader() : NULL;
      if (!prefilterShader)
      {
         Con::errorf("IBLUtilities::GeneratePrefilterMap() - could not find PrefiterCubemapShader");
         return;
      }

      GFXShaderConstBufferRef prefilterConsts = prefilterShader->allocConstBuffer();
      GFXShaderConstHandle* prefilterEnvMapSC = prefilterShader->getShaderConstHandle("$environmentMap");
      GFXShaderConstHandle* prefilterFaceSC = prefilterShader->getShaderConstHandle("$face");
      GFXShaderConstHandle* prefilterRoughnessSC = prefilterShader->getShaderConstHandle("$roughness");
      GFXShaderConstHandle* prefilterMipSizeSC = prefilterShader->getShaderConstHandle("$mipSize");
	  GFXShaderConstHandle* prefilterResolutionSC = prefilterShader->getShaderConstHandle("$resolution");
	  
      GFX->pushActiveRenderTarget();
      GFX->setShader(prefilterShader);
      GFX->setShaderConstBuffer(prefilterConsts);
      GFX->setCubeTexture(0, cubemap);

      U32 prefilterSize = cubemapOut->getSize();

      for (U32 face = 0; face < 6; face++)
      {
         prefilterConsts->setSafe(prefilterFaceSC, (S32)face);
		 prefilterConsts->setSafe(prefilterResolutionSC, renderTarget->getSize().x);
         for (U32 mip = 0; mip < mipLevels; mip++)
         {
            S32 mipSize = prefilterSize >> mip;
            F32 roughness = (float)mip / (float)(mipLevels - 1);
            prefilterConsts->setSafe(prefilterRoughnessSC, roughness);
            prefilterConsts->setSafe(prefilterMipSizeSC, mipSize);
            U32 size = prefilterSize * mPow(0.5f, mip);
            renderTarget->attachTexture(GFXTextureTarget::Color0, cubemapOut, face, mip);
            GFX->setActiveRenderTarget(renderTarget, false);//we set the viewport ourselves
            GFX->setViewport(RectI(0, 0, size, size));
            GFX->clear(GFXClearTarget, LinearColorF::BLACK, 1.0f, 0);
            GFX->drawPrimitive(GFXTriangleList, 0, 3);
            renderTarget->resolve();
         }
      }

      GFX->popActiveRenderTarget();
   }

   void GenerateBRDFTexture(GFXTexHandle &textureOut)
   {
      GFXTransformSaver saver;

      ShaderData *brdfShaderData;
      GFXShaderRef brdfShader = Sim::findObject("BRDFLookupShader", brdfShaderData) ? brdfShaderData->getShader() : NULL;
      if (!brdfShader)
      {
         Con::errorf("IBLUtilities::GenerateBRDFTexture() - could not find BRDFLookupShader");
         return;
      }

      U32 textureSize = textureOut->getWidth();

      GFXTextureTargetRef renderTarget = GFX->allocRenderToTextureTarget();
      GFX->pushActiveRenderTarget();

      GFX->setShader(brdfShader);
      renderTarget->attachTexture(GFXTextureTarget::Color0, textureOut);
      GFX->setActiveRenderTarget(renderTarget);//potential bug here with the viewport not updating with the new size
      GFX->setViewport(RectI(0, 0, textureSize, textureSize));//see above comment
      GFX->clear(GFXClearTarget, LinearColorF::BLUE, 1.0f, 0);
      GFX->drawPrimitive(GFXTriangleList, 0, 3);
      renderTarget->resolve();

      GFX->popActiveRenderTarget();
   }

   void bakeReflection(String outputPath, S32 resolution)
   {
      //GFXDEBUGEVENT_SCOPE(ReflectionProbe_Bake, ColorI::WHITE);

      /*PostEffect *preCapture = dynamic_cast<PostEffect*>(Sim::findObject("AL_PreCapture"));
      PostEffect *deferredShading = dynamic_cast<PostEffect*>(Sim::findObject("AL_DeferredShading"));
      if (preCapture)
         preCapture->enable();
      if (deferredShading)
         deferredShading->disable();

      //if (mReflectionModeType == StaticCubemap || mReflectionModeType == BakedCubemap || mReflectionModeType == SkyLight)
      {
         if (!mCubemap)
         {
            mCubemap = new CubemapData();
            mCubemap->registerObject();
         }
      }

      if (mReflectionModeType == DynamicCubemap && mDynamicCubemap.isNull())
      {
         //mCubemap->createMap();
         mDynamicCubemap = GFX->createCubemap();
         mDynamicCubemap->initDynamic(resolution, GFXFormatR8G8B8);
      }
      else if (mReflectionModeType != DynamicCubemap)
      {
         if (mReflectionPath.isEmpty() || !mPersistentId)
         {
            if (!mPersistentId)
               mPersistentId = getOrCreatePersistentId();

            mReflectionPath = outputPath.c_str();

            mProbeUniqueID = std::to_string(mPersistentId->getUUID().getHash()).c_str();
         }
      }

      bool validCubemap = true;

      // Save the current transforms so we can restore
      // it for child control rendering below.
      GFXTransformSaver saver;

      //bool saveEditingMission = gEditingMission;
      //gEditingMission = false;

      //Set this to true to use the prior method where it goes through the SPT_Reflect path for the bake
      bool probeRenderState = ReflectionProbe::smRenderReflectionProbes;
      ReflectionProbe::smRenderReflectionProbes = false;
      for (U32 i = 0; i < 6; ++i)
      {
         GFXTexHandle blendTex;
         blendTex.set(resolution, resolution, GFXFormatR8G8B8A8, &GFXRenderTargetProfile, "");

         GFXTextureTargetRef mBaseTarget = GFX->allocRenderToTextureTarget();

         GFX->clearTextureStateImmediate(0);
         if (mReflectionModeType == DynamicCubemap)
            mBaseTarget->attachTexture(GFXTextureTarget::Color0, mDynamicCubemap, i);
         else
            mBaseTarget->attachTexture(GFXTextureTarget::Color0, blendTex);

         // Standard view that will be overridden below.
         VectorF vLookatPt(0.0f, 0.0f, 0.0f), vUpVec(0.0f, 0.0f, 0.0f), vRight(0.0f, 0.0f, 0.0f);

         switch (i)
         {
            case 0: // D3DCUBEMAP_FACE_POSITIVE_X:
               vLookatPt = VectorF(1.0f, 0.0f, 0.0f);
               vUpVec = VectorF(0.0f, 1.0f, 0.0f);
               break;
            case 1: // D3DCUBEMAP_FACE_NEGATIVE_X:
               vLookatPt = VectorF(-1.0f, 0.0f, 0.0f);
               vUpVec = VectorF(0.0f, 1.0f, 0.0f);
               break;
            case 2: // D3DCUBEMAP_FACE_POSITIVE_Y:
               vLookatPt = VectorF(0.0f, 1.0f, 0.0f);
               vUpVec = VectorF(0.0f, 0.0f, -1.0f);
               break;
            case 3: // D3DCUBEMAP_FACE_NEGATIVE_Y:
               vLookatPt = VectorF(0.0f, -1.0f, 0.0f);
               vUpVec = VectorF(0.0f, 0.0f, 1.0f);
               break;
            case 4: // D3DCUBEMAP_FACE_POSITIVE_Z:
               vLookatPt = VectorF(0.0f, 0.0f, 1.0f);
               vUpVec = VectorF(0.0f, 1.0f, 0.0f);
               break;
            case 5: // D3DCUBEMAP_FACE_NEGATIVE_Z:
               vLookatPt = VectorF(0.0f, 0.0f, -1.0f);
               vUpVec = VectorF(0.0f, 1.0f, 0.0f);
               break;
         }

         // create camera matrix
         VectorF cross = mCross(vUpVec, vLookatPt);
         cross.normalizeSafe();

         MatrixF matView(true);
         matView.setColumn(0, cross);
         matView.setColumn(1, vLookatPt);
         matView.setColumn(2, vUpVec);
         matView.setPosition(getPosition());
         matView.inverse();

         // set projection to 90 degrees vertical and horizontal
         F32 left, right, top, bottom;
         F32 nearPlane = 0.01f;
         F32 farDist = 1000.f;

         MathUtils::makeFrustum(&left, &right, &top, &bottom, M_HALFPI_F, 1.0f, nearPlane);
         Frustum frustum(false, left, right, top, bottom, nearPlane, farDist);

         renderFrame(&mBaseTarget, matView, frustum, StaticObjectType | StaticShapeObjectType & EDITOR_RENDER_TYPEMASK, gCanvasClearColor);

         mBaseTarget->resolve();

         mCubemap->setCubeFaceTexture(i, blendTex);
      }

      if (mReflectionModeType != DynamicCubemap && validCubemap)
      {
         if (mCubemap->mCubemap)
            mCubemap->updateFaces();
         else
            mCubemap->createMap();

         char fileName[256];
         dSprintf(fileName, 256, "%s%s.DDS", mReflectionPath.c_str(), mProbeUniqueID.c_str());

         CubemapSaver::save(mCubemap->mCubemap, fileName);

         if (!Platform::isFile(fileName))
         {
            validCubemap = false; //if we didn't save right, just 
            Con::errorf("Failed to properly save out the skylight baked cubemap!");
         }

         mDirty = false;
      }

      //calculateSHTerms();

      ReflectionProbe::smRenderReflectionProbes = probeRenderState;
      setMaskBits(-1);

      if (preCapture)
         preCapture->disable();
      if (deferredShading)
         deferredShading->enable();*/
   }

   LinearColorF decodeSH(Point3F normal, const LinearColorF SHTerms[9], const F32 SHConstants[5])
   {
      float x = normal.x;
      float y = normal.y;
      float z = normal.z;

      LinearColorF l00 = SHTerms[0];

      LinearColorF l10 = SHTerms[1];
      LinearColorF l11 = SHTerms[2];
      LinearColorF l12 = SHTerms[3];

      LinearColorF l20 = SHTerms[4];
      LinearColorF l21 = SHTerms[5];
      LinearColorF l22 = SHTerms[6];
      LinearColorF l23 = SHTerms[7];
      LinearColorF l24 = SHTerms[8];

      LinearColorF result = (
         l00 * SHConstants[0] +

         l12 * SHConstants[1] * x +
         l10 * SHConstants[1] * y +
         l11 * SHConstants[1] * z +

         l20 * SHConstants[2] * x*y +
         l21 * SHConstants[2] * y*z +
         l22 * SHConstants[3] * (3.0*z*z - 1.0) +
         l23 * SHConstants[2] * x*z +
         l24 * SHConstants[4] * (x*x - y * y)
         );

      return LinearColorF(mMax(result.red, 0), mMax(result.green, 0), mMax(result.blue, 0));
   }

   MatrixF getSideMatrix(U32 side)
   {
      // Standard view that will be overridden below.
      VectorF vLookatPt(0.0f, 0.0f, 0.0f), vUpVec(0.0f, 0.0f, 0.0f), vRight(0.0f, 0.0f, 0.0f);

      switch (side)
      {
         case 0: // D3DCUBEMAP_FACE_POSITIVE_X:
            vLookatPt = VectorF(1.0f, 0.0f, 0.0f);
            vUpVec = VectorF(0.0f, 1.0f, 0.0f);
            break;
         case 1: // D3DCUBEMAP_FACE_NEGATIVE_X:
            vLookatPt = VectorF(-1.0f, 0.0f, 0.0f);
            vUpVec = VectorF(0.0f, 1.0f, 0.0f);
            break;
         case 2: // D3DCUBEMAP_FACE_POSITIVE_Y:
            vLookatPt = VectorF(0.0f, 1.0f, 0.0f);
            vUpVec = VectorF(0.0f, 0.0f, -1.0f);
            break;
         case 3: // D3DCUBEMAP_FACE_NEGATIVE_Y:
            vLookatPt = VectorF(0.0f, -1.0f, 0.0f);
            vUpVec = VectorF(0.0f, 0.0f, 1.0f);
            break;
         case 4: // D3DCUBEMAP_FACE_POSITIVE_Z:
            vLookatPt = VectorF(0.0f, 0.0f, 1.0f);
            vUpVec = VectorF(0.0f, 1.0f, 0.0f);
            break;
         case 5: // D3DCUBEMAP_FACE_NEGATIVE_Z:
            vLookatPt = VectorF(0.0f, 0.0f, -1.0f);
            vUpVec = VectorF(0.0f, 1.0f, 0.0f);
            break;
      }

      // create camera matrix
      VectorF cross = mCross(vUpVec, vLookatPt);
      cross.normalizeSafe();

      MatrixF rotMat(true);
      rotMat.setColumn(0, cross);
      rotMat.setColumn(1, vLookatPt);
      rotMat.setColumn(2, vUpVec);
      //rotMat.inverse();

      return rotMat;
   }

   F32 harmonics(U32 termId, Point3F normal)
   {
      F32 x = normal.x;
      F32 y = normal.y;
      F32 z = normal.z;

      switch (termId)
      {
         case 0:
            return 1.0;
         case 1:
            return y;
         case 2:
            return z;
         case 3:
            return x;
         case 4:
            return x * y;
         case 5:
            return y * z;
         case 6:
            return 3.0*z*z - 1.0;
         case 7:
            return x * z;
         default:
            return x * x - y * y;
      }
   }

   LinearColorF sampleSide(GBitmap* cubeFaceBitmaps[6], const U32& cubemapResolution, const U32& termindex, const U32& sideIndex)
   {
      MatrixF sideRot = getSideMatrix(sideIndex);

      LinearColorF result = LinearColorF::ZERO;
      F32 divider = 0;

      for (int y = 0; y<cubemapResolution; y++)
      {
         for (int x = 0; x<cubemapResolution; x++)
         {
            Point2F sidecoord = ((Point2F(x, y) + Point2F(0.5, 0.5)) / Point2F(cubemapResolution, cubemapResolution))*2.0 - Point2F(1.0, 1.0);
            Point3F normal = Point3F(sidecoord.x, sidecoord.y, -1.0);
            normal.normalize();

            F32 minBrightness = Con::getFloatVariable("$pref::GI::Cubemap_Sample_MinBrightness", 0.001f);

            LinearColorF texel = cubeFaceBitmaps[sideIndex]->sampleTexel(y, x);
            texel = LinearColorF(mMax(texel.red, minBrightness), mMax(texel.green, minBrightness), mMax(texel.blue, minBrightness)) * Con::getFloatVariable("$pref::GI::Cubemap_Gain", 1.5);

            Point3F dir;
            sideRot.mulP(normal, &dir);

            result += texel * harmonics(termindex, dir) * -normal.z;
            divider += -normal.z;
         }
      }

      result /= divider;

      return result;
   }

   //
   //SH Calculations
   // From http://sunandblackcat.com/tipFullView.php?l=eng&topicid=32&topic=Spherical-Harmonics-From-Cube-Texture
   // With shader decode logic from https://github.com/nicknikolov/cubemap-sh
   void calculateSHTerms(GFXCubemapHandle cubemap, LinearColorF SHTerms[9], F32 SHConstants[5])
   {
      if (!cubemap)
         return;

      const VectorF cubemapFaceNormals[6] =
      {
         // D3DCUBEMAP_FACE_POSITIVE_X:
         VectorF(1.0f, 0.0f, 0.0f),
         // D3DCUBEMAP_FACE_NEGATIVE_X:
         VectorF(-1.0f, 0.0f, 0.0f),
         // D3DCUBEMAP_FACE_POSITIVE_Y:
         VectorF(0.0f, 1.0f, 0.0f),
         // D3DCUBEMAP_FACE_NEGATIVE_Y:
         VectorF(0.0f, -1.0f, 0.0f),
         // D3DCUBEMAP_FACE_POSITIVE_Z:
         VectorF(0.0f, 0.0f, 1.0f),
         // D3DCUBEMAP_FACE_NEGATIVE_Z:
         VectorF(0.0f, 0.0f, -1.0f),
      };

      U32 cubemapResolution = cubemap->getSize();

      GBitmap* cubeFaceBitmaps[6];

      for (U32 i = 0; i < 6; i++)
      {
         cubeFaceBitmaps[i] = new GBitmap(cubemapResolution, cubemapResolution, false, GFXFormatR16G16B16A16F);
      }

      //If we fail to parse the cubemap for whatever reason, we really can't continue
      if (!CubemapSaver::getBitmaps(cubemap, GFXFormatR8G8B8, cubeFaceBitmaps))
         return;

      //Set up our constants
      F32 L0 = Con::getFloatVariable("$pref::GI::SH_Term_L0", 1.0f);
      F32 L1 = Con::getFloatVariable("$pref::GI::SH_Term_L1", 1.8f);
      F32 L2 = Con::getFloatVariable("$pref::GI::SH_Term_L2", 0.83f);
      F32 L2m2_L2m1_L21 = Con::getFloatVariable("$pref::GI::SH_Term_L2m2", 2.9f);
      F32 L20 = Con::getFloatVariable("$pref::GI::SH_Term_L20", 0.58f);
      F32 L22 = Con::getFloatVariable("$pref::GI::SH_Term_L22", 1.1f);

      SHConstants[0] = L0;
      SHConstants[1] = L1;
      SHConstants[2] = L2 * L2m2_L2m1_L21;
      SHConstants[3] = L2 * L20;
      SHConstants[4] = L2 * L22;

      for (U32 i = 0; i < 9; i++)
      {
         //Clear it, just to be sure
         SHTerms[i] = LinearColorF(0.f, 0.f, 0.f);

         //Now, encode for each side
         SHTerms[i] = sampleSide(cubeFaceBitmaps, cubemapResolution, i, 0); //POS_X
         SHTerms[i] += sampleSide(cubeFaceBitmaps, cubemapResolution, i, 1); //NEG_X
         SHTerms[i] += sampleSide(cubeFaceBitmaps, cubemapResolution, i, 2); //POS_Y
         SHTerms[i] += sampleSide(cubeFaceBitmaps, cubemapResolution, i, 3); //NEG_Y
         SHTerms[i] += sampleSide(cubeFaceBitmaps, cubemapResolution, i, 4); //POS_Z
         SHTerms[i] += sampleSide(cubeFaceBitmaps, cubemapResolution, i, 5); //NEG_Z

                                                      //Average
         SHTerms[i] /= 6;
      }

      for (U32 i = 0; i < 6; i++)
         SAFE_DELETE(cubeFaceBitmaps[i]);

      /*bool mExportSHTerms = false;
      if (mExportSHTerms)
      {
         for (U32 f = 0; f < 6; f++)
         {
            char fileName[256];
            dSprintf(fileName, 256, "%s%s_DecodedFaces_%d.png", mReflectionPath.c_str(),
               mProbeUniqueID.c_str(), f);

            LinearColorF color = decodeSH(cubemapFaceNormals[f]);

            FileStream stream;
            if (stream.open(fileName, Torque::FS::File::Write))
            {
               GBitmap bitmap(mCubemapResolution, mCubemapResolution, false, GFXFormatR8G8B8);

               bitmap.fill(color.toColorI());

               bitmap.writeBitmap("png", stream);
            }
         }

         for (U32 f = 0; f < 9; f++)
         {
            char fileName[256];
            dSprintf(fileName, 256, "%s%s_SHTerms_%d.png", mReflectionPath.c_str(),
               mProbeUniqueID.c_str(), f);

            LinearColorF color = mProbeInfo->SHTerms[f];

            FileStream stream;
            if (stream.open(fileName, Torque::FS::File::Write))
            {
               GBitmap bitmap(mCubemapResolution, mCubemapResolution, false, GFXFormatR8G8B8);

               bitmap.fill(color.toColorI());

               bitmap.writeBitmap("png", stream);
            }
         }
      }*/
   }

   F32 areaElement(F32 x, F32 y)
   {
      return mAtan2(x * y, (F32)mSqrt(x * x + y * y + 1.0));
   }

   F32 texelSolidAngle(F32 aU, F32 aV, U32 width, U32 height)
   {
      // transform from [0..res - 1] to [- (1 - 1 / res) .. (1 - 1 / res)]
      // ( 0.5 is for texel center addressing)
      const F32 U = (2.0 * (aU + 0.5) / width) - 1.0;
      const F32 V = (2.0 * (aV + 0.5) / height) - 1.0;

      // shift from a demi texel, mean 1.0 / size  with U and V in [-1..1]
      const F32 invResolutionW = 1.0 / width;
      const F32 invResolutionH = 1.0 / height;

      // U and V are the -1..1 texture coordinate on the current face.
      // get projected area for this texel
      const F32 x0 = U - invResolutionW;
      const F32 y0 = V - invResolutionH;
      const F32 x1 = U + invResolutionW;
      const F32 y1 = V + invResolutionH;
      const F32 angle = areaElement(x0, y0) - areaElement(x0, y1) - areaElement(x1, y0) + areaElement(x1, y1);

      return angle;
   }
};