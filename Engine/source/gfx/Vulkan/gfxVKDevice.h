#ifndef _GFXVKDEVICE_H_
#define _GFXVKDEVICE_H_

#include "platform/platform.h"
#include "gfx/gfxDevice.h"
#include "gfx/gfxInit.h"
#include "windowManager/platformWindow.h"
#include "gfx/gfxFence.h"
#include "gfx/gfxResource.h"

#include <glad/vulkan.h>    // Loads Vulkan functions (after you create VkInstance)
#include <vulkan/vulkan.h>  // Declares Vulkan types and enums
#include <SDL_vulkan.h>     // For SDL_Vulkan_* helper functions

#ifndef _GFXVKVERTEXDECL_H_
#include "gfx/Vulkan/gfxVKVertexDecl.h"
#endif // !_GFXVKVERTEXDECL_H_


#define VK static_cast<GFXVKDevice*>(GFX)
#define VKINSTANCE VK->getInstance()
#define VKPHYSICAL VK->getPhysicalDevice()
#define VKDEVICE VK->getDevice()

#define VK_CHECK(x) do { VkResult err = x; AssertFatal(err == VK_SUCCESS, "Vulkan error"); } while(0)

#define MAX_FRAMES_IN_FLIGHT 2

class PlatformWindow;

class GFXVKDevice : public GFXDevice
{
   U32 mAdapterIndex;
   U32 mCurrentFrameIndex;
   U32 mCurrentImageIndex;

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


   VkSwapchainKHR mSwapChain;

   VkSemaphore mImageAvailableSemaphores[MAX_FRAMES_IN_FLIGHT];
   VkSemaphore mRenderFinishedSemaphores[MAX_FRAMES_IN_FLIGHT];
   VkFence mInFlightFences[MAX_FRAMES_IN_FLIGHT];

   Vector<VkFramebuffer> mFramebuffers;
   VkCommandBuffer mCommandBuffers[MAX_FRAMES_IN_FLIGHT];

   VkCommandBuffer mCurrentCommandBuffer;

   typedef Map<String, GFXVKVertexDecl*> VertexDeclMap;
   VertexDeclMap mVertexDecls;

public:
   /// <summary>
   /// Default constructor
   /// </summary>
   /// <param name="index">Adapter index</param>
   GFXVKDevice(U32 index);

   virtual ~GFXVKDevice();

   // Initialization
   static void enumerateAdapters(Vector<GFXAdapter*>& adapterList);
   static GFXDevice* createInstance(U32 adapterIndex);
   void enumerateVideoModes() override;

   void init(const GFXVideoMode& mode, PlatformWindow* window = NULL) override;
   GFXAdapterType getAdapterType() override { return Vulkan; }

   bool beginSceneInternal() override;
   void endSceneInternal() override;

   // Render Data Handling
   // {
   GFXVertexDecl* allocVertexDecl(const GFXVertexFormat* vertexFormat) override;
   void setVertexDecl(const GFXVertexDecl* decl) override;
   // }

   // Rendering
   // {
   void drawPrimitive(GFXPrimitiveType primType, U32 vertexStart, U32 primitiveCount) override;
   void drawIndexedPrimitive( GFXPrimitiveType primType,
                              U32 startVertex,
                              U32 minIndex,
                              U32 numVerts,
                              U32 startIndex,
                              U32 primitiveCount) override;
   // }


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
