
#ifndef _GFXVKVERTEXDECL_H_
#define _GFXVKVERTEXDECL_H_

#ifndef _GFXVERTEXFORMAT_H_
#include "gfx/gfxVertexFormat.h"
#endif

#ifndef _GFXVKDEVICE_H_
#include "gfx/Vulkan/gfxVKDevice.h"
#endif // !_GFXVKDEVICE_H_

class GFXVKVertexDecl : public GFXVertexDecl
{
public:
   Vector<VkVertexInputBindingDescription> bindingDescriptions;
   Vector<VkVertexInputAttributeDescription> attributeDescriptions;
};

#endif
