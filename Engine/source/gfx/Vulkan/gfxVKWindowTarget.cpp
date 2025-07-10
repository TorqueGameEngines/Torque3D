#include "platform/platform.h"
#include "windowManager/platformWindow.h"
#include "windowManager/sdl/sdlWindow.h"

#include "gfx/Vulkan/gfxVKWindowTarget.h"
#include "gfx/Vulkan/gfxVKEnumTranslate.h"
#include "gfx/gfxDebugEvent.h"
#include "gfx/gfxStringEnumTranslate.h"

void GFXVKWindowTarget::resetMode()
{
}

GFXVKWindowTarget::GFXVKWindowTarget(PlatformWindow* win)
   :  GFXWindowTarget(win),
      mSurface(VK_NULL_HANDLE),
      mSwapchain(VK_NULL_HANDLE),
      mDepthImage(VK_NULL_HANDLE),
      mDepthMemory(VK_NULL_HANDLE),
      mDepthView(VK_NULL_HANDLE),
      mSwapchainFormat(VK_FORMAT_UNDEFINED),
      mExtent({ 0, 0 })
{
   mSecondaryWindow = false;
}

GFXVKWindowTarget::~GFXVKWindowTarget()
{
   _cleanup();
}

void GFXVKWindowTarget::_cleanup()
{
   for (VkFramebuffer fb : mFramebuffers)
      vkDestroyFramebuffer(VKDEVICE, fb, NULL);
   mFramebuffers.clear();

   for (VkImageView view : mSwapchainViews)
      vkDestroyImageView(VKDEVICE, view, NULL);
   mSwapchainViews.clear();

   if (mDepthView)
      vkDestroyImageView(VKDEVICE, mDepthView, NULL);
   if (mDepthImage)
      vkDestroyImage(VKDEVICE, mDepthImage, NULL);
   if (mDepthMemory)
      vkFreeMemory(VKDEVICE, mDepthMemory, NULL);

   if (mSwapchain)
      vkDestroySwapchainKHR(VKDEVICE, mSwapchain, NULL);
   if (mSurface)
      vkDestroySurfaceKHR(VKINSTANCE, mSurface, NULL);

   mSurface = VK_NULL_HANDLE;
   mSwapchain = VK_NULL_HANDLE;
   mDepthImage = VK_NULL_HANDLE;
   mDepthMemory = VK_NULL_HANDLE;
   mDepthView = VK_NULL_HANDLE;
   mSwapchainFormat = VK_FORMAT_UNDEFINED;
   mExtent = { 0, 0 };
}

const Point2I GFXVKWindowTarget::getSize()
{
   return  mWindow->getVideoMode().resolution;
}

GFXFormat GFXVKWindowTarget::getFormat()
{
   return GFXFormat();
}

bool GFXVKWindowTarget::present()
{
   return false;
}

void GFXVKWindowTarget::activate()
{
}

void GFXVKWindowTarget::zombify()
{
}

void GFXVKWindowTarget::resurrect()
{
}

void GFXVKWindowTarget::resolveTo(GFXTextureObject* tex)
{
}

void GFXVKWindowTarget::_initSurface()
{
   SDL_Vulkan_CreateSurface(static_cast<PlatformWindowSDL*>(getWindow())->getSDLWindow(), VKINSTANCE, &mSurface);
}

void GFXVKWindowTarget::_createSwapchain()
{
   VkSurfaceCapabilitiesKHR caps;
   vkGetPhysicalDeviceSurfaceCapabilitiesKHR(VKPHYSICAL, mSurface, &caps);

   mExtent = caps.currentExtent;
   mSwapchainFormat = VK_FORMAT_B8G8R8A8_UNORM;

   VkSwapchainCreateInfoKHR info{};
   info.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
   info.surface = mSurface;
   info.minImageCount = caps.minImageCount;
   info.imageFormat = mSwapchainFormat;
   info.imageColorSpace = VK_COLOR_SPACE_SRGB_NONLINEAR_KHR;
   info.imageExtent = mExtent;
   info.imageArrayLayers = 1;
   info.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;
   info.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
   info.preTransform = caps.currentTransform;
   info.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
   info.presentMode = VK_PRESENT_MODE_FIFO_KHR;
   info.clipped = VK_TRUE;

   vkCreateSwapchainKHR(VKDEVICE, &info, nullptr, &mSwapchain);

   U32 count = 0;
   vkGetSwapchainImagesKHR(VKDEVICE, mSwapchain, &count, nullptr);
   mSwapchainImages.setSize(count);
   vkGetSwapchainImagesKHR(VKDEVICE, mSwapchain, &count, mSwapchainImages.address());

   mSwapchainViews.setSize(count);
   for (U32 i = 0; i < count; ++i)
   {
      VkImageViewCreateInfo view{};
      view.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
      view.image = mSwapchainImages[i];
      view.viewType = VK_IMAGE_VIEW_TYPE_2D;
      view.format = mSwapchainFormat;
      view.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
      view.subresourceRange.levelCount = 1;
      view.subresourceRange.layerCount = 1;
      vkCreateImageView(VKDEVICE, &view, nullptr, &mSwapchainViews[i]);
   }
}

void GFXVKWindowTarget::_createDepthBuffer()
{
   VkFormat format = VK_FORMAT_D24_UNORM_S8_UINT;

   VkImageCreateInfo image{};
   image.sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;
   image.imageType = VK_IMAGE_TYPE_2D;
   image.extent.width = mExtent.width;
   image.extent.height = mExtent.height;
   image.extent.depth = 1;
   image.mipLevels = 1;
   image.arrayLayers = 1;
   image.format = format;
   image.tiling = VK_IMAGE_TILING_OPTIMAL;
   image.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
   image.usage = VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT;
   image.samples = VK_SAMPLE_COUNT_1_BIT;
   image.sharingMode = VK_SHARING_MODE_EXCLUSIVE;

   vkCreateImage(VKDEVICE, &image, nullptr, &mDepthImage);

   VkMemoryRequirements memReq;
   vkGetImageMemoryRequirements(VKDEVICE, mDepthImage, &memReq);

   VkPhysicalDeviceMemoryProperties memProps;
   vkGetPhysicalDeviceMemoryProperties(VKPHYSICAL, &memProps);

   uint32_t index = U32_MAX;
   for (uint32_t i = 0; i < memProps.memoryTypeCount; ++i)
   {
      if ((memReq.memoryTypeBits & (1 << i)) &&
         (memProps.memoryTypes[i].propertyFlags & VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT))
      {
         index = i;
         break;
      }
   }

   AssertFatal(index != U32_MAX, "GFXVKWindowTarget::_createDepthBuffer - Possible overflow.");

   VkMemoryAllocateInfo alloc{};
   alloc.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
   alloc.allocationSize = memReq.size;
   alloc.memoryTypeIndex = index;
   vkAllocateMemory(VKDEVICE, &alloc, nullptr, &mDepthMemory);
   vkBindImageMemory(VKDEVICE, mDepthImage, mDepthMemory, 0);

   VkImageViewCreateInfo view{};
   view.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
   view.image = mDepthImage;
   view.viewType = VK_IMAGE_VIEW_TYPE_2D;
   view.format = format;
   view.subresourceRange.aspectMask = VK_IMAGE_ASPECT_DEPTH_BIT | VK_IMAGE_ASPECT_STENCIL_BIT;
   view.subresourceRange.levelCount = 1;
   view.subresourceRange.layerCount = 1;

   vkCreateImageView(VKDEVICE, &view, nullptr, &mDepthView);
}

void GFXVKWindowTarget::_createFramebuffers()
{
   mFramebuffers.setSize(mSwapchainViews.size());

   for (uint32_t i = 0; i < mSwapchainViews.size(); ++i)
   {
      VkImageView attachments[] = { mSwapchainViews[i], mDepthView };

      VkFramebufferCreateInfo fb{};
      fb.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
      fb.renderPass = VK->getRenderPass();
      fb.attachmentCount = 2;
      fb.pAttachments = attachments;
      fb.width = mExtent.width;
      fb.height = mExtent.height;
      fb.layers = 1;

      vkCreateFramebuffer(VKDEVICE, &fb, nullptr, &mFramebuffers[i]);
   }
}

