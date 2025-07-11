
#include "platform/platform.h"
#include "console/console.h"
#include "gfx/Vulkan/gfxVKDevice.h"
#include "gfx/Vulkan/gfxVKWindowTarget.h"
#include "gfx/Vulkan/gfxVKEnumTranslate.h"
#include "core/stream/fileStream.h"
#include "core/strings/unicode.h"
#include "core/util/journal/process.h"

#include "windowManager/sdl/sdlWindow.h"
#include "SDL.h"
#include "gfx/gl/gfxGLVertexAttribLocation.h"

//
// Register this device with GFXInit
//
class GFXVKRegisterDevice
{
public:
   GFXVKRegisterDevice()
   {
      GFXInit::getRegisterDeviceSignal().notify(&GFXVKDevice::enumerateAdapters);
   }
};

static GFXVKRegisterDevice pVKRegisterDevice;

GFXVKDevice::GFXVKDevice(U32 index)
{
   mAdapterIndex = index;
   mCurrentFrameIndex = 0;
   mCurrentImageIndex = 0;

   mGraphicsQueueFamily = U32_MAX;
   mPresentQueueFamily = U32_MAX;

   mInstance = VK_NULL_HANDLE;
   mSurface = VK_NULL_HANDLE;
   mDebugMessenger = VK_NULL_HANDLE;
   mPhysicalDevice = VK_NULL_HANDLE;
   mDevice = VK_NULL_HANDLE;
   mGraphicsQueue = VK_NULL_HANDLE;
   mPresentQueue = VK_NULL_HANDLE;
   mRenderPass = VK_NULL_HANDLE;
   mPipelineLayout = VK_NULL_HANDLE;
   mGraphicsPipeline = VK_NULL_HANDLE;
   mCommandPool = VK_NULL_HANDLE;
   mSwapChain = VK_NULL_HANDLE;

   mCurrentCommandBuffer = VK_NULL_HANDLE;
}

GFXVKDevice::~GFXVKDevice()
{

   for (int i = 0; i < MAX_FRAMES_IN_FLIGHT; ++i) {
      vkDestroySemaphore(mDevice, mRenderFinishedSemaphores[i], NULL);
      vkDestroySemaphore(mDevice, mImageAvailableSemaphores[i], NULL);
      vkDestroyFence(mDevice, mInFlightFences[i], NULL);
   }
}

void GFXVKDevice::init(const GFXVideoMode& mode, PlatformWindow* window)
{
   AssertFatal(window, "GFXVKDevice::init - PlatformWindow must be valid!");

   SDL_Window* sdlWindow = static_cast<PlatformWindowSDL*>(window)->getSDLWindow();
   // Setup the app info for instance creation.
   VkApplicationInfo appInfo = {};
   appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
   appInfo.pApplicationName = TORQUE_APP_NAME;
   appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
   appInfo.pEngineName = "Torque3D";
   appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
   appInfo.apiVersion = VK_API_VERSION_1_2;

   U32 extCount = 0;
   SDL_Vulkan_GetInstanceExtensions(sdlWindow, &extCount, nullptr);

   Vector<const char*> extensions(extCount);
   SDL_Vulkan_GetInstanceExtensions(sdlWindow, &extCount, extensions.address());

   VkInstanceCreateInfo createInfo = {};
   createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
   createInfo.pApplicationInfo = &appInfo;
   createInfo.enabledExtensionCount = extCount;
   createInfo.ppEnabledExtensionNames = extensions.address();

   // Add validation layers if in debug
#ifdef TORQUE_DEBUG
   const char* validationLayer = "VK_LAYER_KHRONOS_validation";
   createInfo.enabledLayerCount = 1;
   createInfo.ppEnabledLayerNames = &validationLayer;
#else
   createInfo.enabledLayerCount = 0;
#endif

   VK_CHECK(vkCreateInstance(&createInfo, NULL, &mInstance));
   gladLoaderLoadVulkan(mInstance, NULL, NULL); // Loads instance-level functions

   // --- 2. Enumerate and select physical device ---
   U32 deviceCount = 0;
   vkEnumeratePhysicalDevices(mInstance, &deviceCount, NULL);
   Vector<VkPhysicalDevice> devices(deviceCount);
   vkEnumeratePhysicalDevices(mInstance, &deviceCount, devices.address());

   AssertFatal(mAdapterIndex < deviceCount, "Adapter index out of range!");
   mPhysicalDevice = devices[mAdapterIndex];

   // --- 3. Find queue families ---
   U32 queueFamilyCount = 0;
   vkGetPhysicalDeviceQueueFamilyProperties(mPhysicalDevice, &queueFamilyCount, NULL);
   Vector<VkQueueFamilyProperties> queueFamilies(queueFamilyCount);
   vkGetPhysicalDeviceQueueFamilyProperties(mPhysicalDevice, &queueFamilyCount, queueFamilies.address());

   mGraphicsQueueFamily = U32_MAX;
   mPresentQueueFamily = U32_MAX;

   for (U32 i = 0; i < queueFamilyCount; ++i)
   {
      if ((queueFamilies[i].queueFlags & VK_QUEUE_GRAPHICS_BIT) && mGraphicsQueueFamily == U32_MAX)
         mGraphicsQueueFamily = i;

      VkBool32 presentSupport = false;
      vkGetPhysicalDeviceSurfaceSupportKHR(mPhysicalDevice, i, mSurface, &presentSupport);
      if (presentSupport && mPresentQueueFamily == U32_MAX)
         mPresentQueueFamily = i;

      if (mGraphicsQueueFamily != U32_MAX && mPresentQueueFamily != U32_MAX)
         break;
   }

   AssertFatal(mGraphicsQueueFamily != U32_MAX, "No graphics queue found!");
   AssertFatal(mPresentQueueFamily != U32_MAX, "No present queue found!");

   // --- 4. Create logical device and queues ---
   float queuePriority = 1.0f;
   Vector<VkDeviceQueueCreateInfo> queueCreateInfos;

   if (mGraphicsQueueFamily == mPresentQueueFamily)
   {
      VkDeviceQueueCreateInfo queueCreateInfo = {};
      queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
      queueCreateInfo.queueFamilyIndex = mGraphicsQueueFamily;
      queueCreateInfo.queueCount = 1;
      queueCreateInfo.pQueuePriorities = &queuePriority;
      queueCreateInfos.push_back(queueCreateInfo);
   }
   else
   {
      VkDeviceQueueCreateInfo graphicsQueueCreateInfo = {};
      graphicsQueueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
      graphicsQueueCreateInfo.queueFamilyIndex = mGraphicsQueueFamily;
      graphicsQueueCreateInfo.queueCount = 1;
      graphicsQueueCreateInfo.pQueuePriorities = &queuePriority;
      queueCreateInfos.push_back(graphicsQueueCreateInfo);

      VkDeviceQueueCreateInfo presentQueueCreateInfo = {};
      presentQueueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
      presentQueueCreateInfo.queueFamilyIndex = mPresentQueueFamily;
      presentQueueCreateInfo.queueCount = 1;
      presentQueueCreateInfo.pQueuePriorities = &queuePriority;
      queueCreateInfos.push_back(presentQueueCreateInfo);
   }

   VkPhysicalDeviceFeatures deviceFeatures = {}; // enable features if needed
   deviceFeatures.geometryShader = VK_TRUE; // we need to support geometry shaders.
   deviceFeatures.imageCubeArray = VK_TRUE; // we need cubemap array support.

   VkDeviceCreateInfo deviceCreateInfo = {};
   deviceCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
   deviceCreateInfo.queueCreateInfoCount = queueCreateInfos.size();
   deviceCreateInfo.pQueueCreateInfos = queueCreateInfos.address();
   deviceCreateInfo.pEnabledFeatures = &deviceFeatures;

   const char* deviceExtensions[] = {
       VK_KHR_SWAPCHAIN_EXTENSION_NAME
   };
   deviceCreateInfo.enabledExtensionCount = 1;
   deviceCreateInfo.ppEnabledExtensionNames = deviceExtensions;

   VK_CHECK(vkCreateDevice(mPhysicalDevice, &deviceCreateInfo, NULL, &mDevice));
   gladLoaderLoadVulkan(mInstance, mPhysicalDevice, mDevice); // Loads everything

   vkGetDeviceQueue(mDevice, mGraphicsQueueFamily, 0, &mGraphicsQueue);
   vkGetDeviceQueue(mDevice, mPresentQueueFamily, 0, &mPresentQueue);

   // --- 5. Create Command Pool ---
   VkCommandPoolCreateInfo poolInfo = {};
   poolInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
   poolInfo.queueFamilyIndex = mGraphicsQueueFamily;
   poolInfo.flags = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT;

   VK_CHECK(vkCreateCommandPool(mDevice, &poolInfo, NULL, &mCommandPool));

   mInitialized = true;

}

bool GFXVKDevice::beginSceneInternal()
{
   vkWaitForFences(mDevice, 1, &mInFlightFences[mCurrentFrameIndex], VK_TRUE, UINT64_MAX);
   vkResetFences(mDevice, 1, &mInFlightFences[mCurrentFrameIndex]);

   VkResult result = vkAcquireNextImageKHR(
      mDevice,
      mSwapChain,
      UINT64_MAX,
      mImageAvailableSemaphores[mCurrentFrameIndex],
      VK_NULL_HANDLE,
      &mCurrentImageIndex
   );

   if (result == VK_ERROR_OUT_OF_DATE_KHR) {
      //recreateSwapchain();
      return false;
   }

   // Reset and begin command buffer
   mCurrentCommandBuffer = mCommandBuffers[mCurrentFrameIndex];

   vkResetCommandBuffer(mCurrentCommandBuffer, 0);

   VkCommandBufferBeginInfo beginInfo{};
   beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
   beginInfo.flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;

   vkBeginCommandBuffer(mCurrentCommandBuffer, &beginInfo);

   // Begin render pass (just an example)
   VkRenderPassBeginInfo renderPassInfo{};
   renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
   renderPassInfo.renderPass = mRenderPass;
   renderPassInfo.framebuffer = mFramebuffers[mCurrentImageIndex];
   renderPassInfo.renderArea.offset = { 0, 0 };
   //renderPassInfo.renderArea.extent = mSwapchainExtent;

   VkClearValue clearValues[2];
   clearValues[0].color = { 0.0f, 0.0f, 0.0f, 1.0f };
   clearValues[1].depthStencil = { 1.0f, 0 };

   renderPassInfo.clearValueCount = 2;
   renderPassInfo.pClearValues = clearValues;

   vkCmdBeginRenderPass(mCurrentCommandBuffer, &renderPassInfo, VK_SUBPASS_CONTENTS_INLINE);

   return true;
}

void GFXVKDevice::endSceneInternal()
{
   // End render pass and command buffer
   vkCmdEndRenderPass(mCurrentCommandBuffer);
   vkEndCommandBuffer(mCurrentCommandBuffer);

   // Submit command buffer
   VkSubmitInfo submitInfo{};
   submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;

   VkSemaphore waitSemaphores[] = { mImageAvailableSemaphores[mCurrentFrameIndex] };
   VkPipelineStageFlags waitStages[] = { VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT };

   submitInfo.waitSemaphoreCount = 1;
   submitInfo.pWaitSemaphores = waitSemaphores;
   submitInfo.pWaitDstStageMask = waitStages;

   submitInfo.commandBufferCount = 1;
   submitInfo.pCommandBuffers = &mCurrentCommandBuffer;

   VkSemaphore signalSemaphores[] = { mRenderFinishedSemaphores[mCurrentFrameIndex] };
   submitInfo.signalSemaphoreCount = 1;
   submitInfo.pSignalSemaphores = signalSemaphores;

   if (vkQueueSubmit(mGraphicsQueue, 1, &submitInfo, mInFlightFences[mCurrentFrameIndex]) != VK_SUCCESS) {
      AssertFatal(false, "Failed to submit Vulkan command buffer.");
   }

   // Present the frame
   VkPresentInfoKHR presentInfo{};
   presentInfo.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;

   presentInfo.waitSemaphoreCount = 1;
   presentInfo.pWaitSemaphores = signalSemaphores;

   VkSwapchainKHR swapchains[] = { mSwapChain };
   presentInfo.swapchainCount = 1;
   presentInfo.pSwapchains = swapchains;
   presentInfo.pImageIndices = &mCurrentImageIndex;

   vkQueuePresentKHR(mPresentQueue, &presentInfo);

   // Move to next frame
   mCurrentFrameIndex = (mCurrentFrameIndex + 1) % MAX_FRAMES_IN_FLIGHT;
}

GFXVertexDecl* GFXVKDevice::allocVertexDecl(const GFXVertexFormat* vertexFormat)
{
   PROFILE_SCOPE(GFXVKDevice_allocVertexDecl);

   GFXVKVertexDecl* decl = mVertexDecls[vertexFormat->getDescription()];
   if (decl)
      return decl;

   const U32 elemCount = vertexFormat->getElementCount();

   Vector<VkVertexInputAttributeDescription> attributeDescs;
   Vector<VkVertexInputBindingDescription> bindingDescs;

   U32 maxStream = 0;

   // First, determine the highest stream index
   for (U32 i = 0; i < elemCount; ++i)
   {
      const U32 stream = vertexFormat->getElement(i).getStreamIndex();
      if (stream + 1 > maxStream)
         maxStream = stream + 1;
   }

   // Prepare per-stream stride and offset tracking
   Vector<U32> streamStrides;
   streamStrides.setSize(maxStream);
   dMemset(streamStrides.address(), 0, sizeof(U32) * maxStream);

   Vector<U32> streamOffsets;
   streamOffsets.setSize(maxStream);
   dMemset(streamOffsets.address(), 0, sizeof(U32) * maxStream);

   U32 texCoordIndex = 0;

   for (U32 i = 0; i < elemCount; ++i)
   {
      const GFXVertexElement& element = vertexFormat->getElement(i);
      const U32 stream = element.getStreamIndex();
      const U32 sizeInBytes = element.getSizeInBytes();

      VkVertexInputAttributeDescription attrib{};
      attrib.binding = stream;
      attrib.offset = streamOffsets[stream];
      attrib.format = GFXVKDeclType[element.getType()];

      streamOffsets[stream] += sizeInBytes;
      streamStrides[stream] += sizeInBytes;

      // Assign location based on semantic
      if (element.isSemantic(GFXSemantic::POSITION))
         attrib.location = Torque::GL_VertexAttrib_Position;
      else if (element.isSemantic(GFXSemantic::NORMAL))
         attrib.location = Torque::GL_VertexAttrib_Normal;
      else if (element.isSemantic(GFXSemantic::TANGENT))
         attrib.location = Torque::GL_VertexAttrib_Tangent;
      else if (element.isSemantic(GFXSemantic::TANGENTW))
         attrib.location = Torque::GL_VertexAttrib_TangentW;
      else if (element.isSemantic(GFXSemantic::BINORMAL))
         attrib.location = Torque::GL_VertexAttrib_Binormal;
      else if (element.isSemantic(GFXSemantic::COLOR))
         attrib.location = Torque::GL_VertexAttrib_Color;
      else if (element.isSemantic(GFXSemantic::BLENDWEIGHT))
         attrib.location = Torque::GL_VertexAttrib_BlendWeight0 + element.getSemanticIndex();
      else if (element.isSemantic(GFXSemantic::BLENDINDICES))
         attrib.location = Torque::GL_VertexAttrib_BlendIndex0 + element.getSemanticIndex();
      else // Texture coordinates
      {
         attrib.location = Torque::GL_VertexAttrib_TexCoord0 + texCoordIndex;
         ++texCoordIndex;
      }

      attributeDescs.push_back(attrib);
   }

   // Fill in one binding per stream
   for (U32 i = 0; i < maxStream; ++i)
   {
      VkVertexInputBindingDescription binding{};
      binding.binding = i;
      binding.inputRate = (vertexFormat->hasInstancing() && i == 1)
         ? VK_VERTEX_INPUT_RATE_INSTANCE
         : VK_VERTEX_INPUT_RATE_VERTEX;
      binding.stride = streamStrides[i];

      bindingDescs.push_back(binding);
   }

   // Create and store the declaration
   decl = new GFXVKVertexDecl();
   decl->bindingDescriptions = std::move(bindingDescs);
   decl->attributeDescriptions = std::move(attributeDescs);

   mVertexDecls[vertexFormat->getDescription()] = decl;
   return decl;
}

void GFXVKDevice::setVertexDecl(const GFXVertexDecl* decl)
{
   const GFXVKVertexDecl* vkDecl = NULL;
   if (decl)
   {
      vkDecl = static_cast<const GFXVKVertexDecl*>(decl);

      VkPipelineVertexInputStateCreateInfo vertexInputInfo{};
      vertexInputInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;
      vertexInputInfo.vertexBindingDescriptionCount = vkDecl->bindingDescriptions.size();
      vertexInputInfo.pVertexBindingDescriptions = vkDecl->bindingDescriptions.begin();
      vertexInputInfo.vertexAttributeDescriptionCount = vkDecl->attributeDescriptions.size();
      vertexInputInfo.pVertexAttributeDescriptions = vkDecl->attributeDescriptions.begin();
   }
}

void GFXVKDevice::drawPrimitive(GFXPrimitiveType primType, U32 vertexStart, U32 primitiveCount)
{
}

void GFXVKDevice::drawIndexedPrimitive(GFXPrimitiveType primType, U32 startVertex, U32 minIndex, U32 numVerts, U32 startIndex, U32 primitiveCount)
{
}

void GFXVKDevice::enumerateAdapters(Vector<GFXAdapter*>& adapterList)
{
   // Create temporary vulkan instance.
   VkApplicationInfo appInfo = {};
   appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
   appInfo.pApplicationName = TORQUE_APP_NAME;
   appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
   appInfo.pEngineName = "Torque3D";
   appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
   appInfo.apiVersion = VK_API_VERSION_1_2;

   VkInstanceCreateInfo instCreateInfo = {};
   instCreateInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
   instCreateInfo.pApplicationInfo = &appInfo;

   // Create a dummy window & openGL context so that gl functions can be used here
   SDL_Window* tempWindow = SDL_CreateWindow(
      "",                                // window title
      SDL_WINDOWPOS_UNDEFINED,           // initial x position
      SDL_WINDOWPOS_UNDEFINED,           // initial y position
      640,                               // width, in pixels
      480,                               // height, in pixels
      SDL_WINDOW_VULKAN | SDL_WINDOW_HIDDEN // flags - see below
   );
   if (!tempWindow)
   {
      const char* err = SDL_GetError();
      Con::printf(err);
      AssertFatal(0, err);
      return;
   }

   // SDL Vulkan extensions
   U32 extCount = 0;
   SDL_Vulkan_GetInstanceExtensions(tempWindow, &extCount, NULL);
   Vector<const char*> extensions(extCount);
   SDL_Vulkan_GetInstanceExtensions(tempWindow, &extCount, extensions.address());
   instCreateInfo.enabledExtensionCount = extCount;
   instCreateInfo.ppEnabledExtensionNames = extensions.address();

   
   if (!gladLoaderLoadVulkan(NULL, NULL, NULL))
   {
      Con::errorf("GLAD failed to load Vulkan instance functions.");
      return;
   }

   VkInstance instance;
   if (vkCreateInstance(&instCreateInfo, NULL, &instance) != VK_SUCCESS)
   {
      Con::errorf("Failed to create Vulkan instance for adapter enumeration.");
      return;
   }

   U32 gpu_count;

   if (vkEnumeratePhysicalDevices(instance, &gpu_count, NULL))
   {
      Con::errorf("Failed to enumerate physical devices for vulkan.");
      vkDestroyInstance(instance, NULL);
      return;
   }

   VkPhysicalDevice* physical_devices = (VkPhysicalDevice*)dMalloc(sizeof(VkPhysicalDevice) * gpu_count);
   if (vkEnumeratePhysicalDevices(instance, &gpu_count, physical_devices))
   {
      Con::errorf("Failed to enumerate physical devices for vulkan.");
      vkDestroyInstance(instance, NULL);
      return;
   }

   for (U32 i = 0; i < gpu_count; ++i)
   {
      if (!gladLoaderLoadVulkan(instance, physical_devices[i], NULL))
      {
         Con::errorf("GLAD failed to load Vulkan instance functions.");
         return;
      }

      VkPhysicalDeviceProperties props;
      vkGetPhysicalDeviceProperties(physical_devices[i], &props);

      VkPhysicalDeviceFeatures features;
      vkGetPhysicalDeviceFeatures(physical_devices[i], &features);
      if (!features.geometryShader || !features.imageCubeArray) // we need cube array support and geometry shaders
         continue;

      GFXAdapter* adapter = new GFXAdapter();
      adapter->mIndex = i;

      // Copy device name (ensure null-termination)
      dStrncpy(adapter->mName, props.deviceName, GFXAdapter::MaxAdapterNameLen);
      adapter->mName[GFXAdapter::MaxAdapterNameLen - 1] = '\0';
      adapter->mType = Vulkan;
      adapter->mShaderModel = 0.f;
      adapter->mCreateDeviceInstanceDelegate = mCreateDeviceInstance;

      // we need to implement this on the opengl side too.
      // U32 numDisplays = SDL_GetNumVideoDisplays();
      U32 count = SDL_GetNumDisplayModes(0);
      if (count < 0)
      {
         AssertFatal(0, "");
         return;
      }

      SDL_DisplayMode mode;
      for (U32 m = 0; m < count; ++m)
      {
         SDL_GetDisplayMode(0, m, &mode);
         GFXVideoMode outMode;
         outMode.resolution.set(mode.w, mode.h);
         outMode.refreshRate = mode.refresh_rate;
         outMode.bitDepth = 32;
         outMode.wideScreen = (mode.w / mode.h) > (4 / 3);
         outMode.fullScreen = true;

         adapter->mAvailableModes.push_back(outMode);
      }


      // Add to the list of available adapters.
      adapterList.push_back(adapter);

   }

   // Cleanup window & vk instance
   SDL_DestroyWindow(tempWindow);
   dFree(physical_devices);
   vkDestroyInstance(instance, nullptr);

}

GFXAdapter::CreateDeviceInstanceDelegate GFXVKDevice::mCreateDeviceInstance(GFXVKDevice::createInstance);

GFXDevice* GFXVKDevice::createInstance(U32 adapterIndex)
{
   return nullptr;
}

void GFXVKDevice::enumerateVideoModes()
{
   mVideoModes.clear();
   int count = SDL_GetNumDisplayModes(0);
   if (count < 0)
   {
      AssertFatal(0, "");
      return;
   }

   SDL_DisplayMode mode;
   for (int i = 0; i < count; ++i)
   {
      SDL_GetDisplayMode(0, i, &mode);
      GFXVideoMode outMode;
      outMode.resolution.set(mode.w, mode.h);
      outMode.refreshRate = mode.refresh_rate;
      outMode.bitDepth = 32;
      outMode.wideScreen = (mode.w / mode.h) > (4 / 3);
      outMode.fullScreen = true;
      mVideoModes.push_back(outMode);
   }

}

GFXWindowTarget* GFXVKDevice::allocWindowTarget(PlatformWindow* window)
{
   AssertFatal(window, "GFXVKDevice::allocWindowTarget - no window provided!");

   GFXVKWindowTarget* vkwt = new GFXVKWindowTarget(window);
   vkwt->mWindow = window;
   vkwt->mSize = window->getClientExtent();

   if (!mInitialized)
   {
      vkwt->mSecondaryWindow = false;

      // surface needs to be made before we do a full vulkan initialization.
      vkwt->_initSurface();
      mSurface = vkwt->getVKSurface();
      init(window->getVideoMode(), window);

      vkwt->_createSwapchain();
      vkwt->_createDepthBuffer();
      vkwt->_createFramebuffers();

      mSwapChain = vkwt->mSwapchain;
      mFramebuffers = vkwt->mFramebuffers;
   }
   else
   {
      vkwt->mSecondaryWindow = true;
      vkwt->_initSurface();
      vkwt->_createSwapchain();
      vkwt->_createDepthBuffer();
      vkwt->_createFramebuffers();
   }

   return vkwt;
}
