#ifndef _GFXVKSHADER_H_
#define _GFXVKSHADER_H_


#include "core/util/path.h"
#include "core/util/tDictionary.h"

#ifndef _GFXSHADER_H_
#include "gfx/gfxShader.h"
#endif

#ifndef _GFXRESOURCE_H_
#include "gfx/gfxResource.h"
#endif

#ifndef _GFXVKDEVICE_H_
#include "gfx/Vulkan/gfxVKDevice.h"
#endif // !_GFXVKDEVICE_H_

// for shader reflection.
#include <spirv_cross/spirv_cross.hpp>

class GFXVKShader : public GFXShader
{
public:
   GFXVKShader();
   virtual ~GFXVKShader();

   Vector<VkPipelineShaderStageCreateInfo> getShaderStages() const;

   // GFXShader
   GFXShaderConstBufferRef allocConstBuffer() override;
   const Vector<GFXShaderConstDesc>& getShaderConstDesc() const override;
   GFXShaderConstHandle* getShaderConstHandle(const String& name) override;
   GFXShaderConstHandle* findShaderConstHandle(const String& name) override;
   U32 getAlignmentValue(const GFXShaderConstType constType) const override;

   // GFXResource
   void zombify() override;
   void resurrect() override;

protected:
   VkShaderModule _loadSPIRVShaderModule(const Torque::Path& path, GFXShaderStage stage);
   void _reflectSPIRV(const Vector<U8>& code, GFXShaderStage stage);

   bool _init() override;

   GFXShaderConstType convertConstType(const spirv_cross::SPIRType typeDesc);

   Vector<GFXShaderConstDesc> mShaderConsts;
   Vector<GFXShaderConstDesc> mShaderResources;

   VkShaderModule mVertShader;
   VkShaderModule mFragShader;
   VkShaderModule mGeomShader;
   VkShaderModule mCompShader;


};

#endif // !_GFXVKSHADER_H_
