#ifndef _GFXVULKANDEVICE_H_
#define _GFXVULKANDEVICE_H_

#include "platform/platform.h"
#include "gfx/gfxDevice.h"
#include "gfx/gfxInit.h"
#include "windowManager/platformWindow.h"
#include "gfx/gfxFence.h"
#include "gfx/gfxResource.h"

#include <glad/vulkan.h>    // Loads Vulkan functions (after you create VkInstance)
#include <vulkan/vulkan.h>  // Declares Vulkan types and enums
#include <SDL_vulkan.h>     // For SDL_Vulkan_* helper functions

#define VK static_cast<GFXVKDevice*>(GFX)
#define VKINSTANCE VK->getInstance()
#define VKPHYSICAL VK->getPhysicalDevice()
#define VKDEVICE VK->getDevice()

#define VK_CHECK(x) do { VkResult err = x; AssertFatal(err == VK_SUCCESS, "Vulkan error"); } while(0)

class PlatformWindow;

class GFXVKDevice : public GFXDevice
{
   U32  mAdapterIndex;

   // Vulkan types are converted to pointers
   // that are managed in vulkan.
   U32 mGraphicsQueueFamily;
   U32 mPresentQueueFamily;

   VkInstance mInstance;
   VkDebugUtilsMessengerEXT mDebugMessenger;
   VkPhysicalDevice mPhysicalDevice;
   VkSurfaceKHR mSurface;
   VkDevice mDevice;
   VkQueue mGraphicsQueue;
   VkQueue mPresentQueue;
   VkRenderPass mRenderPass;
   VkPipelineLayout mPipelineLayout;
   VkPipeline mGraphicsPipeline;
   VkCommandPool mCommandPool;

public:
   /// <summary>
   /// Default constructor
   /// </summary>
   /// <param name="index">Adapter index</param>
   GFXVKDevice(U32 index);

   virtual ~GFXVKDevice();

   static void enumerateAdapters(Vector<GFXAdapter*>& adapterList);
   static GFXDevice* createInstance(U32 adapterIndex);
   void enumerateVideoModes() override;

   void init(const GFXVideoMode& mode, PlatformWindow* window = NULL) override;
   GFXAdapterType getAdapterType() override { return Vulkan; }

   // Vulkan accessors
   VkInstance getInstance() { return mInstance; }
   VkDevice getDevice() { return mDevice; }
   VkPhysicalDevice getPhysicalDevice() { return mPhysicalDevice; }
   VkRenderPass getRenderPass() { return mRenderPass; }

private:
   friend class GFXVKWindowTarget;

   static GFXAdapter::CreateDeviceInstanceDelegate mCreateDeviceInstance;
   GFXWindowTarget* allocWindowTarget(PlatformWindow* window) override;

};

#endif // !_GFXVULKANDEVICE_H_
