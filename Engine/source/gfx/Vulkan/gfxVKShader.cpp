#include "platform/platform.h"
#include "gfx/Vulkan/gfxVKShader.h"
#include "core/frameAllocator.h"
#include "core/stream/fileStream.h"
#include "core/util/safeDelete.h"
#include "console/console.h"



static bool loadSPIRVFile(const String& path, Vector<U8>& outData)
{
   FileStream fs;
   if (!fs.open(path, Torque::FS::File::Read))
   {
      Con::errorf("Failed to open SPIR-V file: %s", path.c_str());
      return false;
   }

   outData.setSize(fs.getStreamSize());
   fs.read(outData.size(), outData.address());

   return true;
}

VkShaderModule GFXVKShader::_loadSPIRVShaderModule(const Torque::Path& path, GFXShaderStage stage) {
   Vector<U8> code;
   if (!loadSPIRVFile(path.getFullPath(), code))
      return VK_NULL_HANDLE;

   VkShaderModuleCreateInfo createInfo{};
   createInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
   createInfo.codeSize = code.size();
   createInfo.pCode = reinterpret_cast<const uint32_t*>(code.address());

   VkShaderModule shaderModule;
   VkResult res = vkCreateShaderModule(VKDEVICE, &createInfo, NULL, &shaderModule);
   AssertISV(res == VK_SUCCESS, "Failed to create shader module");

   _reflectSPIRV(code, stage);

   return shaderModule;
}

void GFXVKShader::_reflectSPIRV(const Vector<U8>& code, GFXShaderStage stage)
{
   spirv_cross::Compiler compiler(reinterpret_cast<const uint32_t*>(code.address()), code.size() / 4);
   const spirv_cross::ShaderResources resources = compiler.get_shader_resources();

   // --- Uniform Buffers ---
   for (const auto& ubo : resources.uniform_buffers)
   {
      // Buffer-level descriptor
      GFXShaderConstDesc desc;
      desc.name = String(ubo.name.c_str());
      desc.shaderStage = stage;
      desc.constType = GFXSCT_ConstBuffer;

      const auto& blockType = compiler.get_type(ubo.base_type_id);
      desc.size = compiler.get_declared_struct_size(blockType);
      desc.bindPoint = compiler.get_decoration(ubo.id, spv::DecorationBinding);

      //mBuffers[desc.name] = desc;

      // Loop variables inside buffer
      for (uint32_t i = 0; i < blockType.member_types.size(); ++i)
      {
         GFXShaderConstDesc varDesc;
         varDesc.name = String::ToString("$%s", compiler.get_member_name(ubo.base_type_id, i).c_str());
         varDesc.shaderStage = stage;
         varDesc.offset = compiler.type_struct_member_offset(blockType, i);
         varDesc.size = compiler.get_declared_struct_member_size(blockType, i);
         varDesc.bindPoint = desc.bindPoint;

         const auto& memberType = compiler.get_type(blockType.member_types[i]);
         varDesc.constType = convertConstType(memberType);
         varDesc.arraySize = memberType.array.empty() ? 1 : memberType.array[0];
         varDesc.samplerReg = -1;

         mShaderConsts.push_back(varDesc);
      }
   }

   // --- Sampled Images (Combined samplers) ---
   for (const auto& sampler : resources.sampled_images)
   {
      GFXShaderConstDesc desc;
      desc.name = String::ToString("$%s", sampler.name.c_str());
      desc.shaderStage = stage;
      desc.constType = GFXSCT_Sampler;
      desc.samplerReg = compiler.get_decoration(sampler.id, spv::DecorationBinding);
      desc.bindPoint = -1;

      mShaderResources.push_back(desc);
   }

   // --- Storage Buffers (SSBOs) ---
   for (const auto& ssbo : resources.storage_buffers)
   {
      GFXShaderConstDesc desc;
      desc.name = String::ToString("$%s", ssbo.name.c_str());
      desc.shaderStage = stage;
      desc.constType = GFXSCT_StructuredBuffer;

      const auto& type = compiler.get_type(ssbo.base_type_id);
      desc.size = compiler.get_declared_struct_size(type);
      desc.samplerReg = compiler.get_decoration(ssbo.id, spv::DecorationBinding);

      mShaderResources.push_back(desc);
   }

   // --- Storage Images ---
   for (const auto& storageImage : resources.storage_images)
   {
      GFXShaderConstDesc desc;
      desc.name = String::ToString("$%s", storageImage.name.c_str());
      desc.shaderStage = stage;
      desc.constType = GFXSCT_UAV;
      desc.samplerReg = compiler.get_decoration(storageImage.id, spv::DecorationBinding);
      desc.bindPoint = -1;

      mShaderResources.push_back(desc);
   }

   // --- Loose Uniforms ---
   for (const auto& uniform : resources.gl_plain_uniforms)
   {
      GFXShaderConstDesc desc;
      desc.name = String::ToString("$%s", uniform.name.c_str());
      desc.shaderStage = stage;
      const auto& uniformType = compiler.get_type(uniform.base_type_id);
      desc.constType = convertConstType(uniformType);
      desc.bindPoint = compiler.get_decoration(uniform.id, spv::DecorationBinding);

      mShaderConsts.push_back(desc);
   }
}

GFXVKShader::GFXVKShader()
{
   mVertShader = VK_NULL_HANDLE;
   mFragShader = VK_NULL_HANDLE;
   mGeomShader = VK_NULL_HANDLE;
   mCompShader = VK_NULL_HANDLE;
}

GFXVKShader::~GFXVKShader()
{


   vkDestroyShaderModule(VKDEVICE, mVertShader, NULL);
   vkDestroyShaderModule(VKDEVICE, mFragShader, NULL);
   vkDestroyShaderModule(VKDEVICE, mGeomShader, NULL);
   vkDestroyShaderModule(VKDEVICE, mCompShader, NULL);
}

bool GFXVKShader::_init()
{
   
   vkDestroyShaderModule(VKDEVICE, mVertShader, NULL);
   vkDestroyShaderModule(VKDEVICE, mFragShader, NULL);
   vkDestroyShaderModule(VKDEVICE, mGeomShader, NULL);
   vkDestroyShaderModule(VKDEVICE, mCompShader, NULL);

   mShaderConsts.clear();
   mShaderResources.clear();

   if (!mVertexFile.isEmpty())
   {
      mVertShader = _loadSPIRVShaderModule(mVertexFile, GFXShaderStage::VERTEX_SHADER);
   }

   if (!mPixelFile.isEmpty())
      mFragShader = _loadSPIRVShaderModule(mPixelFile, GFXShaderStage::PIXEL_SHADER);

   if (!mGeometryFile.isEmpty())
      mGeomShader = _loadSPIRVShaderModule(mGeometryFile, GFXShaderStage::GEOMETRY_SHADER);

   if (!mComputeFile.isEmpty())
      mCompShader = _loadSPIRVShaderModule(mComputeFile, GFXShaderStage::COMPUTE_SHADER);

   return false;
}

Vector<VkPipelineShaderStageCreateInfo> GFXVKShader::getShaderStages() const {
   Vector<VkPipelineShaderStageCreateInfo> stages;

   if (mVertShader) {
      VkPipelineShaderStageCreateInfo s = {};
      s.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
      s.stage = VK_SHADER_STAGE_VERTEX_BIT;
      s.module = mVertShader;
      s.pName = "main";
      stages.push_back(s);
   }

   if (mFragShader) {
      VkPipelineShaderStageCreateInfo s = {};
      s.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
      s.stage = VK_SHADER_STAGE_FRAGMENT_BIT;
      s.module = mFragShader;
      s.pName = "main";
      stages.push_back(s);
   }

   if (mGeomShader) {
      VkPipelineShaderStageCreateInfo s = {};
      s.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
      s.stage = VK_SHADER_STAGE_GEOMETRY_BIT;
      s.module = mGeomShader;
      s.pName = "main";
      stages.push_back(s);
   }

   return stages;
}

GFXShaderConstType GFXVKShader::convertConstType(const spirv_cross::SPIRType typeDesc)
{
   // Handle float types
   if (typeDesc.basetype == spirv_cross::SPIRType::Float)
   {
      if (typeDesc.columns > 1)
      {
         // Matrix types (rows = vector size, columns = matrix columns)
         int rows = typeDesc.vecsize;    // number of rows (vector size)
         int cols = typeDesc.columns;    // number of columns (matrix columns)

         if (rows == 2 && cols == 2)       return GFXSCT_Float2x2;
         else if (rows == 3 && cols == 3)  return GFXSCT_Float3x3;
         else if (rows == 3 && cols == 4)  return GFXSCT_Float3x4;
         else if (rows == 4 && cols == 3)  return GFXSCT_Float4x3;
         else if (rows == 4 && cols == 4)  return GFXSCT_Float4x4;
         else                              return GFXSCT_Float; // fallback scalar
      }
      else
      {
         // Scalar or vector float
         switch (typeDesc.vecsize)
         {
         case 1: return GFXSCT_Float;
         case 2: return GFXSCT_Float2;
         case 3: return GFXSCT_Float3;
         case 4: return GFXSCT_Float4;
         default: return GFXSCT_Float;
         }
      }
   }
   else if (typeDesc.basetype == spirv_cross::SPIRType::Int)
   {
      switch (typeDesc.vecsize)
      {
      case 1: return GFXSCT_Int;
      case 2: return GFXSCT_Int2;
      case 3: return GFXSCT_Int3;
      case 4: return GFXSCT_Int4;
      default: return GFXSCT_Int;
      }
   }
   else if (typeDesc.basetype == spirv_cross::SPIRType::UInt)
   {
      switch (typeDesc.vecsize)
      {
      case 1: return GFXSCT_UInt;
      case 2: return GFXSCT_UInt2;
      case 3: return GFXSCT_UInt3;
      case 4: return GFXSCT_UInt4;
      default: return GFXSCT_UInt;
      }
   }
   else if (typeDesc.basetype == spirv_cross::SPIRType::Boolean)
   {
      switch (typeDesc.vecsize)
      {
      case 1: return GFXSCT_Bool;
      case 2: return GFXSCT_Bool2;
      case 3: return GFXSCT_Bool3;
      case 4: return GFXSCT_Bool4;
      default: return GFXSCT_Bool;
      }
   }

   return GFXSCT_Uknown;
}
