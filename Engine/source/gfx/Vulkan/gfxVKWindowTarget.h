#pragma once
#ifndef _GFXVKWINDOWTARGET_H_
#define _GFXVKWINDOWTARGET_H_

#ifndef _GFXVULKANDEVICE_H_
#include "gfx/Vulkan/gfxVKDevice.h"
#endif

#ifndef _GFXTARGET_H_
#include "gfx/gfxTarget.h"
#endif // !_GFXTARGET_H_

class GFXVKWindowTarget : public GFXWindowTarget
{
   friend class GFXVKDevice;

   VkSurfaceKHR mSurface;
   VkSwapchainKHR mSwapchain;
   Vector<VkImage> mSwapchainImages;
   Vector<VkImageView> mSwapchainViews;
   Vector<VkFramebuffer> mFramebuffers;
   VkImage mDepthImage;
   VkDeviceMemory mDepthMemory;
   VkImageView mDepthView;
   VkFormat mSwapchainFormat;
   VkExtent2D mExtent;

   Point2I mSize;
   bool mSecondaryWindow;

   void resetMode() override;

public:
   GFXVKWindowTarget(PlatformWindow* win);
   ~GFXVKWindowTarget();

   // GFXWindow Target.
   const Point2I getSize() override;
   GFXFormat getFormat() override;
   bool present() override;
   void activate() override;
   void zombify() override;
   void resurrect() override;
   void resolveTo(GFXTextureObject* tex) override;

   void _initSurface();
   void _createSwapchain();
   void _createDepthBuffer();
   void _createFramebuffers();
   void _cleanup();

   VkSurfaceKHR getVKSurface() { return mSurface; }

};


#endif // !_GFXVKWINDOWTARGET_H_
