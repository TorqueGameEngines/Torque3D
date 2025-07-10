#ifndef _GFXVKNUMTRANSLATE_H_
#define _GFXVKENUMTRANSLATE_H_

#include "gfx/gfxEnums.h"
#include "gfx/Vulkan/gfxVKDevice.h"

namespace GFXVKEnumTranslate
{
   void init();
}

// These externs map GFX enums to Vulkan enums
extern VkPrimitiveTopology GFXVKPrimType[GFXPT_COUNT];
extern VkBlendFactor GFXVKBlend[GFXBlend_COUNT];
extern VkBlendOp GFXVKBlendOp[GFXBlendOp_COUNT];
extern VkCompareOp GFXVKCmpFunc[GFXCmp_COUNT];
extern VkSamplerAddressMode GFXVKTextureAddress[GFXAddress_COUNT];
extern VkFilter GFXVKTextureFilter[GFXTextureFilter_COUNT];
extern VkStencilOp GFXVKStencilOp[GFXStencilOp_COUNT];
extern VkFormat GFXVKTextureFormat[GFXFormat_COUNT];
extern VkCullModeFlagBits GFXVKCullMode[GFXCull_COUNT];
extern VkPolygonMode GFXVKFillMode[GFXFill_COUNT];

#endif
