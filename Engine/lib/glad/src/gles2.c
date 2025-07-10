#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <glad/gles2.h>

#ifndef GLAD_IMPL_UTIL_C_
#define GLAD_IMPL_UTIL_C_

#ifdef _MSC_VER
#define GLAD_IMPL_UTIL_SSCANF sscanf_s
#else
#define GLAD_IMPL_UTIL_SSCANF sscanf
#endif

#endif /* GLAD_IMPL_UTIL_C_ */

#ifdef __cplusplus
extern "C" {
#endif



int GLAD_GL_ES_VERSION_2_0 = 0;
int GLAD_GL_ES_VERSION_3_0 = 0;
int GLAD_GL_ES_VERSION_3_1 = 0;
int GLAD_GL_ES_VERSION_3_2 = 0;
int GLAD_GL_AMD_compressed_3DC_texture = 0;
int GLAD_GL_AMD_compressed_ATC_texture = 0;
int GLAD_GL_AMD_framebuffer_multisample_advanced = 0;
int GLAD_GL_AMD_performance_monitor = 0;
int GLAD_GL_AMD_program_binary_Z400 = 0;
int GLAD_GL_ANDROID_extension_pack_es31a = 0;
int GLAD_GL_ANGLE_depth_texture = 0;
int GLAD_GL_ANGLE_framebuffer_blit = 0;
int GLAD_GL_ANGLE_framebuffer_multisample = 0;
int GLAD_GL_ANGLE_instanced_arrays = 0;
int GLAD_GL_ANGLE_pack_reverse_row_order = 0;
int GLAD_GL_ANGLE_program_binary = 0;
int GLAD_GL_ANGLE_texture_compression_dxt3 = 0;
int GLAD_GL_ANGLE_texture_compression_dxt5 = 0;
int GLAD_GL_ANGLE_texture_usage = 0;
int GLAD_GL_ANGLE_translated_shader_source = 0;
int GLAD_GL_APPLE_clip_distance = 0;
int GLAD_GL_APPLE_color_buffer_packed_float = 0;
int GLAD_GL_APPLE_copy_texture_levels = 0;
int GLAD_GL_APPLE_framebuffer_multisample = 0;
int GLAD_GL_APPLE_rgb_422 = 0;
int GLAD_GL_APPLE_sync = 0;
int GLAD_GL_APPLE_texture_format_BGRA8888 = 0;
int GLAD_GL_APPLE_texture_max_level = 0;
int GLAD_GL_APPLE_texture_packed_float = 0;
int GLAD_GL_ARM_mali_program_binary = 0;
int GLAD_GL_ARM_mali_shader_binary = 0;
int GLAD_GL_ARM_rgba8 = 0;
int GLAD_GL_ARM_shader_framebuffer_fetch = 0;
int GLAD_GL_ARM_shader_framebuffer_fetch_depth_stencil = 0;
int GLAD_GL_ARM_texture_unnormalized_coordinates = 0;
int GLAD_GL_DMP_program_binary = 0;
int GLAD_GL_DMP_shader_binary = 0;
int GLAD_GL_EXT_EGL_image_array = 0;
int GLAD_GL_EXT_EGL_image_storage = 0;
int GLAD_GL_EXT_EGL_image_storage_compression = 0;
int GLAD_GL_EXT_YUV_target = 0;
int GLAD_GL_EXT_base_instance = 0;
int GLAD_GL_EXT_blend_func_extended = 0;
int GLAD_GL_EXT_blend_minmax = 0;
int GLAD_GL_EXT_buffer_storage = 0;
int GLAD_GL_EXT_clear_texture = 0;
int GLAD_GL_EXT_clip_control = 0;
int GLAD_GL_EXT_clip_cull_distance = 0;
int GLAD_GL_EXT_color_buffer_float = 0;
int GLAD_GL_EXT_color_buffer_half_float = 0;
int GLAD_GL_EXT_conservative_depth = 0;
int GLAD_GL_EXT_copy_image = 0;
int GLAD_GL_EXT_debug_label = 0;
int GLAD_GL_EXT_debug_marker = 0;
int GLAD_GL_EXT_depth_clamp = 0;
int GLAD_GL_EXT_discard_framebuffer = 0;
int GLAD_GL_EXT_disjoint_timer_query = 0;
int GLAD_GL_EXT_draw_buffers = 0;
int GLAD_GL_EXT_draw_buffers_indexed = 0;
int GLAD_GL_EXT_draw_elements_base_vertex = 0;
int GLAD_GL_EXT_draw_instanced = 0;
int GLAD_GL_EXT_draw_transform_feedback = 0;
int GLAD_GL_EXT_external_buffer = 0;
int GLAD_GL_EXT_float_blend = 0;
int GLAD_GL_EXT_fragment_shading_rate = 0;
int GLAD_GL_EXT_geometry_point_size = 0;
int GLAD_GL_EXT_geometry_shader = 0;
int GLAD_GL_EXT_gpu_shader5 = 0;
int GLAD_GL_EXT_instanced_arrays = 0;
int GLAD_GL_EXT_map_buffer_range = 0;
int GLAD_GL_EXT_memory_object = 0;
int GLAD_GL_EXT_memory_object_fd = 0;
int GLAD_GL_EXT_memory_object_win32 = 0;
int GLAD_GL_EXT_multi_draw_arrays = 0;
int GLAD_GL_EXT_multi_draw_indirect = 0;
int GLAD_GL_EXT_multisampled_compatibility = 0;
int GLAD_GL_EXT_multisampled_render_to_texture = 0;
int GLAD_GL_EXT_multisampled_render_to_texture2 = 0;
int GLAD_GL_EXT_multiview_draw_buffers = 0;
int GLAD_GL_EXT_multiview_tessellation_geometry_shader = 0;
int GLAD_GL_EXT_multiview_texture_multisample = 0;
int GLAD_GL_EXT_multiview_timer_query = 0;
int GLAD_GL_EXT_occlusion_query_boolean = 0;
int GLAD_GL_EXT_polygon_offset_clamp = 0;
int GLAD_GL_EXT_post_depth_coverage = 0;
int GLAD_GL_EXT_primitive_bounding_box = 0;
int GLAD_GL_EXT_protected_textures = 0;
int GLAD_GL_EXT_pvrtc_sRGB = 0;
int GLAD_GL_EXT_raster_multisample = 0;
int GLAD_GL_EXT_read_format_bgra = 0;
int GLAD_GL_EXT_render_snorm = 0;
int GLAD_GL_EXT_robustness = 0;
int GLAD_GL_EXT_sRGB = 0;
int GLAD_GL_EXT_sRGB_write_control = 0;
int GLAD_GL_EXT_semaphore = 0;
int GLAD_GL_EXT_semaphore_fd = 0;
int GLAD_GL_EXT_semaphore_win32 = 0;
int GLAD_GL_EXT_separate_depth_stencil = 0;
int GLAD_GL_EXT_separate_shader_objects = 0;
int GLAD_GL_EXT_shader_framebuffer_fetch = 0;
int GLAD_GL_EXT_shader_framebuffer_fetch_non_coherent = 0;
int GLAD_GL_EXT_shader_group_vote = 0;
int GLAD_GL_EXT_shader_implicit_conversions = 0;
int GLAD_GL_EXT_shader_integer_mix = 0;
int GLAD_GL_EXT_shader_io_blocks = 0;
int GLAD_GL_EXT_shader_non_constant_global_initializers = 0;
int GLAD_GL_EXT_shader_pixel_local_storage = 0;
int GLAD_GL_EXT_shader_pixel_local_storage2 = 0;
int GLAD_GL_EXT_shader_samples_identical = 0;
int GLAD_GL_EXT_shader_texture_lod = 0;
int GLAD_GL_EXT_shadow_samplers = 0;
int GLAD_GL_EXT_sparse_texture = 0;
int GLAD_GL_EXT_sparse_texture2 = 0;
int GLAD_GL_EXT_tessellation_point_size = 0;
int GLAD_GL_EXT_tessellation_shader = 0;
int GLAD_GL_EXT_texture_border_clamp = 0;
int GLAD_GL_EXT_texture_buffer = 0;
int GLAD_GL_EXT_texture_compression_astc_decode_mode = 0;
int GLAD_GL_EXT_texture_compression_bptc = 0;
int GLAD_GL_EXT_texture_compression_dxt1 = 0;
int GLAD_GL_EXT_texture_compression_rgtc = 0;
int GLAD_GL_EXT_texture_compression_s3tc = 0;
int GLAD_GL_EXT_texture_compression_s3tc_srgb = 0;
int GLAD_GL_EXT_texture_cube_map_array = 0;
int GLAD_GL_EXT_texture_filter_anisotropic = 0;
int GLAD_GL_EXT_texture_filter_minmax = 0;
int GLAD_GL_EXT_texture_format_BGRA8888 = 0;
int GLAD_GL_EXT_texture_format_sRGB_override = 0;
int GLAD_GL_EXT_texture_mirror_clamp_to_edge = 0;
int GLAD_GL_EXT_texture_norm16 = 0;
int GLAD_GL_EXT_texture_query_lod = 0;
int GLAD_GL_EXT_texture_rg = 0;
int GLAD_GL_EXT_texture_sRGB_R8 = 0;
int GLAD_GL_EXT_texture_sRGB_RG8 = 0;
int GLAD_GL_EXT_texture_sRGB_decode = 0;
int GLAD_GL_EXT_texture_shadow_lod = 0;
int GLAD_GL_EXT_texture_storage = 0;
int GLAD_GL_EXT_texture_storage_compression = 0;
int GLAD_GL_EXT_texture_type_2_10_10_10_REV = 0;
int GLAD_GL_EXT_texture_view = 0;
int GLAD_GL_EXT_unpack_subimage = 0;
int GLAD_GL_EXT_win32_keyed_mutex = 0;
int GLAD_GL_EXT_window_rectangles = 0;
int GLAD_GL_FJ_shader_binary_GCCSO = 0;
int GLAD_GL_IMG_bindless_texture = 0;
int GLAD_GL_IMG_framebuffer_downsample = 0;
int GLAD_GL_IMG_multisampled_render_to_texture = 0;
int GLAD_GL_IMG_program_binary = 0;
int GLAD_GL_IMG_read_format = 0;
int GLAD_GL_IMG_shader_binary = 0;
int GLAD_GL_IMG_texture_compression_pvrtc = 0;
int GLAD_GL_IMG_texture_compression_pvrtc2 = 0;
int GLAD_GL_IMG_texture_filter_cubic = 0;
int GLAD_GL_INTEL_blackhole_render = 0;
int GLAD_GL_INTEL_conservative_rasterization = 0;
int GLAD_GL_INTEL_framebuffer_CMAA = 0;
int GLAD_GL_INTEL_performance_query = 0;
int GLAD_GL_KHR_blend_equation_advanced = 0;
int GLAD_GL_KHR_blend_equation_advanced_coherent = 0;
int GLAD_GL_KHR_context_flush_control = 0;
int GLAD_GL_KHR_debug = 0;
int GLAD_GL_KHR_no_error = 0;
int GLAD_GL_KHR_parallel_shader_compile = 0;
int GLAD_GL_KHR_robust_buffer_access_behavior = 0;
int GLAD_GL_KHR_robustness = 0;
int GLAD_GL_KHR_shader_subgroup = 0;
int GLAD_GL_KHR_texture_compression_astc_hdr = 0;
int GLAD_GL_KHR_texture_compression_astc_ldr = 0;
int GLAD_GL_KHR_texture_compression_astc_sliced_3d = 0;
int GLAD_GL_MESA_bgra = 0;
int GLAD_GL_MESA_framebuffer_flip_x = 0;
int GLAD_GL_MESA_framebuffer_flip_y = 0;
int GLAD_GL_MESA_framebuffer_swap_xy = 0;
int GLAD_GL_MESA_program_binary_formats = 0;
int GLAD_GL_MESA_shader_integer_functions = 0;
int GLAD_GL_NVX_blend_equation_advanced_multi_draw_buffers = 0;
int GLAD_GL_NV_bindless_texture = 0;
int GLAD_GL_NV_blend_equation_advanced = 0;
int GLAD_GL_NV_blend_equation_advanced_coherent = 0;
int GLAD_GL_NV_blend_minmax_factor = 0;
int GLAD_GL_NV_clip_space_w_scaling = 0;
int GLAD_GL_NV_compute_shader_derivatives = 0;
int GLAD_GL_NV_conditional_render = 0;
int GLAD_GL_NV_conservative_raster = 0;
int GLAD_GL_NV_conservative_raster_pre_snap = 0;
int GLAD_GL_NV_conservative_raster_pre_snap_triangles = 0;
int GLAD_GL_NV_copy_buffer = 0;
int GLAD_GL_NV_coverage_sample = 0;
int GLAD_GL_NV_depth_nonlinear = 0;
int GLAD_GL_NV_draw_buffers = 0;
int GLAD_GL_NV_draw_instanced = 0;
int GLAD_GL_NV_draw_vulkan_image = 0;
int GLAD_GL_NV_explicit_attrib_location = 0;
int GLAD_GL_NV_fbo_color_attachments = 0;
int GLAD_GL_NV_fence = 0;
int GLAD_GL_NV_fill_rectangle = 0;
int GLAD_GL_NV_fragment_coverage_to_color = 0;
int GLAD_GL_NV_fragment_shader_barycentric = 0;
int GLAD_GL_NV_fragment_shader_interlock = 0;
int GLAD_GL_NV_framebuffer_blit = 0;
int GLAD_GL_NV_framebuffer_mixed_samples = 0;
int GLAD_GL_NV_framebuffer_multisample = 0;
int GLAD_GL_NV_generate_mipmap_sRGB = 0;
int GLAD_GL_NV_geometry_shader_passthrough = 0;
int GLAD_GL_NV_gpu_shader5 = 0;
int GLAD_GL_NV_image_formats = 0;
int GLAD_GL_NV_instanced_arrays = 0;
int GLAD_GL_NV_internalformat_sample_query = 0;
int GLAD_GL_NV_memory_attachment = 0;
int GLAD_GL_NV_memory_object_sparse = 0;
int GLAD_GL_NV_mesh_shader = 0;
int GLAD_GL_NV_non_square_matrices = 0;
int GLAD_GL_NV_path_rendering = 0;
int GLAD_GL_NV_path_rendering_shared_edge = 0;
int GLAD_GL_NV_pixel_buffer_object = 0;
int GLAD_GL_NV_polygon_mode = 0;
int GLAD_GL_NV_primitive_shading_rate = 0;
int GLAD_GL_NV_read_buffer = 0;
int GLAD_GL_NV_read_buffer_front = 0;
int GLAD_GL_NV_read_depth = 0;
int GLAD_GL_NV_read_depth_stencil = 0;
int GLAD_GL_NV_read_stencil = 0;
int GLAD_GL_NV_representative_fragment_test = 0;
int GLAD_GL_NV_sRGB_formats = 0;
int GLAD_GL_NV_sample_locations = 0;
int GLAD_GL_NV_sample_mask_override_coverage = 0;
int GLAD_GL_NV_scissor_exclusive = 0;
int GLAD_GL_NV_shader_atomic_fp16_vector = 0;
int GLAD_GL_NV_shader_noperspective_interpolation = 0;
int GLAD_GL_NV_shader_subgroup_partitioned = 0;
int GLAD_GL_NV_shader_texture_footprint = 0;
int GLAD_GL_NV_shading_rate_image = 0;
int GLAD_GL_NV_shadow_samplers_array = 0;
int GLAD_GL_NV_shadow_samplers_cube = 0;
int GLAD_GL_NV_stereo_view_rendering = 0;
int GLAD_GL_NV_texture_border_clamp = 0;
int GLAD_GL_NV_texture_compression_s3tc_update = 0;
int GLAD_GL_NV_texture_npot_2D_mipmap = 0;
int GLAD_GL_NV_timeline_semaphore = 0;
int GLAD_GL_NV_viewport_array = 0;
int GLAD_GL_NV_viewport_array2 = 0;
int GLAD_GL_NV_viewport_swizzle = 0;
int GLAD_GL_OES_EGL_image = 0;
int GLAD_GL_OES_EGL_image_external = 0;
int GLAD_GL_OES_EGL_image_external_essl3 = 0;
int GLAD_GL_OES_compressed_ETC1_RGB8_sub_texture = 0;
int GLAD_GL_OES_compressed_ETC1_RGB8_texture = 0;
int GLAD_GL_OES_compressed_paletted_texture = 0;
int GLAD_GL_OES_copy_image = 0;
int GLAD_GL_OES_depth24 = 0;
int GLAD_GL_OES_depth32 = 0;
int GLAD_GL_OES_depth_texture = 0;
int GLAD_GL_OES_draw_buffers_indexed = 0;
int GLAD_GL_OES_draw_elements_base_vertex = 0;
int GLAD_GL_OES_element_index_uint = 0;
int GLAD_GL_OES_fbo_render_mipmap = 0;
int GLAD_GL_OES_fragment_precision_high = 0;
int GLAD_GL_OES_geometry_point_size = 0;
int GLAD_GL_OES_geometry_shader = 0;
int GLAD_GL_OES_get_program_binary = 0;
int GLAD_GL_OES_gpu_shader5 = 0;
int GLAD_GL_OES_mapbuffer = 0;
int GLAD_GL_OES_packed_depth_stencil = 0;
int GLAD_GL_OES_primitive_bounding_box = 0;
int GLAD_GL_OES_required_internalformat = 0;
int GLAD_GL_OES_rgb8_rgba8 = 0;
int GLAD_GL_OES_sample_shading = 0;
int GLAD_GL_OES_sample_variables = 0;
int GLAD_GL_OES_shader_image_atomic = 0;
int GLAD_GL_OES_shader_io_blocks = 0;
int GLAD_GL_OES_shader_multisample_interpolation = 0;
int GLAD_GL_OES_standard_derivatives = 0;
int GLAD_GL_OES_stencil1 = 0;
int GLAD_GL_OES_stencil4 = 0;
int GLAD_GL_OES_surfaceless_context = 0;
int GLAD_GL_OES_tessellation_point_size = 0;
int GLAD_GL_OES_tessellation_shader = 0;
int GLAD_GL_OES_texture_3D = 0;
int GLAD_GL_OES_texture_border_clamp = 0;
int GLAD_GL_OES_texture_buffer = 0;
int GLAD_GL_OES_texture_compression_astc = 0;
int GLAD_GL_OES_texture_cube_map_array = 0;
int GLAD_GL_OES_texture_float = 0;
int GLAD_GL_OES_texture_float_linear = 0;
int GLAD_GL_OES_texture_half_float = 0;
int GLAD_GL_OES_texture_half_float_linear = 0;
int GLAD_GL_OES_texture_npot = 0;
int GLAD_GL_OES_texture_stencil8 = 0;
int GLAD_GL_OES_texture_storage_multisample_2d_array = 0;
int GLAD_GL_OES_texture_view = 0;
int GLAD_GL_OES_vertex_array_object = 0;
int GLAD_GL_OES_vertex_half_float = 0;
int GLAD_GL_OES_vertex_type_10_10_10_2 = 0;
int GLAD_GL_OES_viewport_array = 0;
int GLAD_GL_OVR_multiview = 0;
int GLAD_GL_OVR_multiview2 = 0;
int GLAD_GL_OVR_multiview_multisampled_render_to_texture = 0;
int GLAD_GL_QCOM_YUV_texture_gather = 0;
int GLAD_GL_QCOM_alpha_test = 0;
int GLAD_GL_QCOM_binning_control = 0;
int GLAD_GL_QCOM_driver_control = 0;
int GLAD_GL_QCOM_extended_get = 0;
int GLAD_GL_QCOM_extended_get2 = 0;
int GLAD_GL_QCOM_frame_extrapolation = 0;
int GLAD_GL_QCOM_framebuffer_foveated = 0;
int GLAD_GL_QCOM_motion_estimation = 0;
int GLAD_GL_QCOM_perfmon_global_mode = 0;
int GLAD_GL_QCOM_render_shared_exponent = 0;
int GLAD_GL_QCOM_shader_framebuffer_fetch_noncoherent = 0;
int GLAD_GL_QCOM_shader_framebuffer_fetch_rate = 0;
int GLAD_GL_QCOM_shading_rate = 0;
int GLAD_GL_QCOM_texture_foveated = 0;
int GLAD_GL_QCOM_texture_foveated2 = 0;
int GLAD_GL_QCOM_texture_foveated_subsampled_layout = 0;
int GLAD_GL_QCOM_tiled_rendering = 0;
int GLAD_GL_QCOM_writeonly_rendering = 0;
int GLAD_GL_VIV_shader_binary = 0;



PFNGLACQUIREKEYEDMUTEXWIN32EXTPROC glad_glAcquireKeyedMutexWin32EXT = NULL;
PFNGLACTIVESHADERPROGRAMPROC glad_glActiveShaderProgram = NULL;
PFNGLACTIVESHADERPROGRAMEXTPROC glad_glActiveShaderProgramEXT = NULL;
PFNGLACTIVETEXTUREPROC glad_glActiveTexture = NULL;
PFNGLALPHAFUNCQCOMPROC glad_glAlphaFuncQCOM = NULL;
PFNGLAPPLYFRAMEBUFFERATTACHMENTCMAAINTELPROC glad_glApplyFramebufferAttachmentCMAAINTEL = NULL;
PFNGLATTACHSHADERPROC glad_glAttachShader = NULL;
PFNGLBEGINCONDITIONALRENDERNVPROC glad_glBeginConditionalRenderNV = NULL;
PFNGLBEGINPERFMONITORAMDPROC glad_glBeginPerfMonitorAMD = NULL;
PFNGLBEGINPERFQUERYINTELPROC glad_glBeginPerfQueryINTEL = NULL;
PFNGLBEGINQUERYPROC glad_glBeginQuery = NULL;
PFNGLBEGINQUERYEXTPROC glad_glBeginQueryEXT = NULL;
PFNGLBEGINTRANSFORMFEEDBACKPROC glad_glBeginTransformFeedback = NULL;
PFNGLBINDATTRIBLOCATIONPROC glad_glBindAttribLocation = NULL;
PFNGLBINDBUFFERPROC glad_glBindBuffer = NULL;
PFNGLBINDBUFFERBASEPROC glad_glBindBufferBase = NULL;
PFNGLBINDBUFFERRANGEPROC glad_glBindBufferRange = NULL;
PFNGLBINDFRAGDATALOCATIONEXTPROC glad_glBindFragDataLocationEXT = NULL;
PFNGLBINDFRAGDATALOCATIONINDEXEDEXTPROC glad_glBindFragDataLocationIndexedEXT = NULL;
PFNGLBINDFRAMEBUFFERPROC glad_glBindFramebuffer = NULL;
PFNGLBINDIMAGETEXTUREPROC glad_glBindImageTexture = NULL;
PFNGLBINDPROGRAMPIPELINEPROC glad_glBindProgramPipeline = NULL;
PFNGLBINDPROGRAMPIPELINEEXTPROC glad_glBindProgramPipelineEXT = NULL;
PFNGLBINDRENDERBUFFERPROC glad_glBindRenderbuffer = NULL;
PFNGLBINDSAMPLERPROC glad_glBindSampler = NULL;
PFNGLBINDSHADINGRATEIMAGENVPROC glad_glBindShadingRateImageNV = NULL;
PFNGLBINDTEXTUREPROC glad_glBindTexture = NULL;
PFNGLBINDTRANSFORMFEEDBACKPROC glad_glBindTransformFeedback = NULL;
PFNGLBINDVERTEXARRAYPROC glad_glBindVertexArray = NULL;
PFNGLBINDVERTEXARRAYOESPROC glad_glBindVertexArrayOES = NULL;
PFNGLBINDVERTEXBUFFERPROC glad_glBindVertexBuffer = NULL;
PFNGLBLENDBARRIERPROC glad_glBlendBarrier = NULL;
PFNGLBLENDBARRIERKHRPROC glad_glBlendBarrierKHR = NULL;
PFNGLBLENDBARRIERNVPROC glad_glBlendBarrierNV = NULL;
PFNGLBLENDCOLORPROC glad_glBlendColor = NULL;
PFNGLBLENDEQUATIONPROC glad_glBlendEquation = NULL;
PFNGLBLENDEQUATIONSEPARATEPROC glad_glBlendEquationSeparate = NULL;
PFNGLBLENDEQUATIONSEPARATEIPROC glad_glBlendEquationSeparatei = NULL;
PFNGLBLENDEQUATIONSEPARATEIEXTPROC glad_glBlendEquationSeparateiEXT = NULL;
PFNGLBLENDEQUATIONSEPARATEIOESPROC glad_glBlendEquationSeparateiOES = NULL;
PFNGLBLENDEQUATIONIPROC glad_glBlendEquationi = NULL;
PFNGLBLENDEQUATIONIEXTPROC glad_glBlendEquationiEXT = NULL;
PFNGLBLENDEQUATIONIOESPROC glad_glBlendEquationiOES = NULL;
PFNGLBLENDFUNCPROC glad_glBlendFunc = NULL;
PFNGLBLENDFUNCSEPARATEPROC glad_glBlendFuncSeparate = NULL;
PFNGLBLENDFUNCSEPARATEIPROC glad_glBlendFuncSeparatei = NULL;
PFNGLBLENDFUNCSEPARATEIEXTPROC glad_glBlendFuncSeparateiEXT = NULL;
PFNGLBLENDFUNCSEPARATEIOESPROC glad_glBlendFuncSeparateiOES = NULL;
PFNGLBLENDFUNCIPROC glad_glBlendFunci = NULL;
PFNGLBLENDFUNCIEXTPROC glad_glBlendFunciEXT = NULL;
PFNGLBLENDFUNCIOESPROC glad_glBlendFunciOES = NULL;
PFNGLBLENDPARAMETERINVPROC glad_glBlendParameteriNV = NULL;
PFNGLBLITFRAMEBUFFERPROC glad_glBlitFramebuffer = NULL;
PFNGLBLITFRAMEBUFFERANGLEPROC glad_glBlitFramebufferANGLE = NULL;
PFNGLBLITFRAMEBUFFERNVPROC glad_glBlitFramebufferNV = NULL;
PFNGLBUFFERATTACHMEMORYNVPROC glad_glBufferAttachMemoryNV = NULL;
PFNGLBUFFERDATAPROC glad_glBufferData = NULL;
PFNGLBUFFERPAGECOMMITMENTMEMNVPROC glad_glBufferPageCommitmentMemNV = NULL;
PFNGLBUFFERSTORAGEEXTPROC glad_glBufferStorageEXT = NULL;
PFNGLBUFFERSTORAGEEXTERNALEXTPROC glad_glBufferStorageExternalEXT = NULL;
PFNGLBUFFERSTORAGEMEMEXTPROC glad_glBufferStorageMemEXT = NULL;
PFNGLBUFFERSUBDATAPROC glad_glBufferSubData = NULL;
PFNGLCHECKFRAMEBUFFERSTATUSPROC glad_glCheckFramebufferStatus = NULL;
PFNGLCLEARPROC glad_glClear = NULL;
PFNGLCLEARBUFFERFIPROC glad_glClearBufferfi = NULL;
PFNGLCLEARBUFFERFVPROC glad_glClearBufferfv = NULL;
PFNGLCLEARBUFFERIVPROC glad_glClearBufferiv = NULL;
PFNGLCLEARBUFFERUIVPROC glad_glClearBufferuiv = NULL;
PFNGLCLEARCOLORPROC glad_glClearColor = NULL;
PFNGLCLEARDEPTHFPROC glad_glClearDepthf = NULL;
PFNGLCLEARPIXELLOCALSTORAGEUIEXTPROC glad_glClearPixelLocalStorageuiEXT = NULL;
PFNGLCLEARSTENCILPROC glad_glClearStencil = NULL;
PFNGLCLEARTEXIMAGEEXTPROC glad_glClearTexImageEXT = NULL;
PFNGLCLEARTEXSUBIMAGEEXTPROC glad_glClearTexSubImageEXT = NULL;
PFNGLCLIENTWAITSYNCPROC glad_glClientWaitSync = NULL;
PFNGLCLIENTWAITSYNCAPPLEPROC glad_glClientWaitSyncAPPLE = NULL;
PFNGLCLIPCONTROLEXTPROC glad_glClipControlEXT = NULL;
PFNGLCOLORMASKPROC glad_glColorMask = NULL;
PFNGLCOLORMASKIPROC glad_glColorMaski = NULL;
PFNGLCOLORMASKIEXTPROC glad_glColorMaskiEXT = NULL;
PFNGLCOLORMASKIOESPROC glad_glColorMaskiOES = NULL;
PFNGLCOMPILESHADERPROC glad_glCompileShader = NULL;
PFNGLCOMPRESSEDTEXIMAGE2DPROC glad_glCompressedTexImage2D = NULL;
PFNGLCOMPRESSEDTEXIMAGE3DPROC glad_glCompressedTexImage3D = NULL;
PFNGLCOMPRESSEDTEXIMAGE3DOESPROC glad_glCompressedTexImage3DOES = NULL;
PFNGLCOMPRESSEDTEXSUBIMAGE2DPROC glad_glCompressedTexSubImage2D = NULL;
PFNGLCOMPRESSEDTEXSUBIMAGE3DPROC glad_glCompressedTexSubImage3D = NULL;
PFNGLCOMPRESSEDTEXSUBIMAGE3DOESPROC glad_glCompressedTexSubImage3DOES = NULL;
PFNGLCONSERVATIVERASTERPARAMETERINVPROC glad_glConservativeRasterParameteriNV = NULL;
PFNGLCOPYBUFFERSUBDATAPROC glad_glCopyBufferSubData = NULL;
PFNGLCOPYBUFFERSUBDATANVPROC glad_glCopyBufferSubDataNV = NULL;
PFNGLCOPYIMAGESUBDATAPROC glad_glCopyImageSubData = NULL;
PFNGLCOPYIMAGESUBDATAEXTPROC glad_glCopyImageSubDataEXT = NULL;
PFNGLCOPYIMAGESUBDATAOESPROC glad_glCopyImageSubDataOES = NULL;
PFNGLCOPYPATHNVPROC glad_glCopyPathNV = NULL;
PFNGLCOPYTEXIMAGE2DPROC glad_glCopyTexImage2D = NULL;
PFNGLCOPYTEXSUBIMAGE2DPROC glad_glCopyTexSubImage2D = NULL;
PFNGLCOPYTEXSUBIMAGE3DPROC glad_glCopyTexSubImage3D = NULL;
PFNGLCOPYTEXSUBIMAGE3DOESPROC glad_glCopyTexSubImage3DOES = NULL;
PFNGLCOPYTEXTURELEVELSAPPLEPROC glad_glCopyTextureLevelsAPPLE = NULL;
PFNGLCOVERFILLPATHINSTANCEDNVPROC glad_glCoverFillPathInstancedNV = NULL;
PFNGLCOVERFILLPATHNVPROC glad_glCoverFillPathNV = NULL;
PFNGLCOVERSTROKEPATHINSTANCEDNVPROC glad_glCoverStrokePathInstancedNV = NULL;
PFNGLCOVERSTROKEPATHNVPROC glad_glCoverStrokePathNV = NULL;
PFNGLCOVERAGEMASKNVPROC glad_glCoverageMaskNV = NULL;
PFNGLCOVERAGEMODULATIONNVPROC glad_glCoverageModulationNV = NULL;
PFNGLCOVERAGEMODULATIONTABLENVPROC glad_glCoverageModulationTableNV = NULL;
PFNGLCOVERAGEOPERATIONNVPROC glad_glCoverageOperationNV = NULL;
PFNGLCREATEMEMORYOBJECTSEXTPROC glad_glCreateMemoryObjectsEXT = NULL;
PFNGLCREATEPERFQUERYINTELPROC glad_glCreatePerfQueryINTEL = NULL;
PFNGLCREATEPROGRAMPROC glad_glCreateProgram = NULL;
PFNGLCREATESEMAPHORESNVPROC glad_glCreateSemaphoresNV = NULL;
PFNGLCREATESHADERPROC glad_glCreateShader = NULL;
PFNGLCREATESHADERPROGRAMVPROC glad_glCreateShaderProgramv = NULL;
PFNGLCREATESHADERPROGRAMVEXTPROC glad_glCreateShaderProgramvEXT = NULL;
PFNGLCULLFACEPROC glad_glCullFace = NULL;
PFNGLDEBUGMESSAGECALLBACKPROC glad_glDebugMessageCallback = NULL;
PFNGLDEBUGMESSAGECALLBACKKHRPROC glad_glDebugMessageCallbackKHR = NULL;
PFNGLDEBUGMESSAGECONTROLPROC glad_glDebugMessageControl = NULL;
PFNGLDEBUGMESSAGECONTROLKHRPROC glad_glDebugMessageControlKHR = NULL;
PFNGLDEBUGMESSAGEINSERTPROC glad_glDebugMessageInsert = NULL;
PFNGLDEBUGMESSAGEINSERTKHRPROC glad_glDebugMessageInsertKHR = NULL;
PFNGLDELETEBUFFERSPROC glad_glDeleteBuffers = NULL;
PFNGLDELETEFENCESNVPROC glad_glDeleteFencesNV = NULL;
PFNGLDELETEFRAMEBUFFERSPROC glad_glDeleteFramebuffers = NULL;
PFNGLDELETEMEMORYOBJECTSEXTPROC glad_glDeleteMemoryObjectsEXT = NULL;
PFNGLDELETEPATHSNVPROC glad_glDeletePathsNV = NULL;
PFNGLDELETEPERFMONITORSAMDPROC glad_glDeletePerfMonitorsAMD = NULL;
PFNGLDELETEPERFQUERYINTELPROC glad_glDeletePerfQueryINTEL = NULL;
PFNGLDELETEPROGRAMPROC glad_glDeleteProgram = NULL;
PFNGLDELETEPROGRAMPIPELINESPROC glad_glDeleteProgramPipelines = NULL;
PFNGLDELETEPROGRAMPIPELINESEXTPROC glad_glDeleteProgramPipelinesEXT = NULL;
PFNGLDELETEQUERIESPROC glad_glDeleteQueries = NULL;
PFNGLDELETEQUERIESEXTPROC glad_glDeleteQueriesEXT = NULL;
PFNGLDELETERENDERBUFFERSPROC glad_glDeleteRenderbuffers = NULL;
PFNGLDELETESAMPLERSPROC glad_glDeleteSamplers = NULL;
PFNGLDELETESEMAPHORESEXTPROC glad_glDeleteSemaphoresEXT = NULL;
PFNGLDELETESHADERPROC glad_glDeleteShader = NULL;
PFNGLDELETESYNCPROC glad_glDeleteSync = NULL;
PFNGLDELETESYNCAPPLEPROC glad_glDeleteSyncAPPLE = NULL;
PFNGLDELETETEXTURESPROC glad_glDeleteTextures = NULL;
PFNGLDELETETRANSFORMFEEDBACKSPROC glad_glDeleteTransformFeedbacks = NULL;
PFNGLDELETEVERTEXARRAYSPROC glad_glDeleteVertexArrays = NULL;
PFNGLDELETEVERTEXARRAYSOESPROC glad_glDeleteVertexArraysOES = NULL;
PFNGLDEPTHFUNCPROC glad_glDepthFunc = NULL;
PFNGLDEPTHMASKPROC glad_glDepthMask = NULL;
PFNGLDEPTHRANGEARRAYFVNVPROC glad_glDepthRangeArrayfvNV = NULL;
PFNGLDEPTHRANGEARRAYFVOESPROC glad_glDepthRangeArrayfvOES = NULL;
PFNGLDEPTHRANGEINDEXEDFNVPROC glad_glDepthRangeIndexedfNV = NULL;
PFNGLDEPTHRANGEINDEXEDFOESPROC glad_glDepthRangeIndexedfOES = NULL;
PFNGLDEPTHRANGEFPROC glad_glDepthRangef = NULL;
PFNGLDETACHSHADERPROC glad_glDetachShader = NULL;
PFNGLDISABLEPROC glad_glDisable = NULL;
PFNGLDISABLEDRIVERCONTROLQCOMPROC glad_glDisableDriverControlQCOM = NULL;
PFNGLDISABLEVERTEXATTRIBARRAYPROC glad_glDisableVertexAttribArray = NULL;
PFNGLDISABLEIPROC glad_glDisablei = NULL;
PFNGLDISABLEIEXTPROC glad_glDisableiEXT = NULL;
PFNGLDISABLEINVPROC glad_glDisableiNV = NULL;
PFNGLDISABLEIOESPROC glad_glDisableiOES = NULL;
PFNGLDISCARDFRAMEBUFFEREXTPROC glad_glDiscardFramebufferEXT = NULL;
PFNGLDISPATCHCOMPUTEPROC glad_glDispatchCompute = NULL;
PFNGLDISPATCHCOMPUTEINDIRECTPROC glad_glDispatchComputeIndirect = NULL;
PFNGLDRAWARRAYSPROC glad_glDrawArrays = NULL;
PFNGLDRAWARRAYSINDIRECTPROC glad_glDrawArraysIndirect = NULL;
PFNGLDRAWARRAYSINSTANCEDPROC glad_glDrawArraysInstanced = NULL;
PFNGLDRAWARRAYSINSTANCEDANGLEPROC glad_glDrawArraysInstancedANGLE = NULL;
PFNGLDRAWARRAYSINSTANCEDBASEINSTANCEEXTPROC glad_glDrawArraysInstancedBaseInstanceEXT = NULL;
PFNGLDRAWARRAYSINSTANCEDEXTPROC glad_glDrawArraysInstancedEXT = NULL;
PFNGLDRAWARRAYSINSTANCEDNVPROC glad_glDrawArraysInstancedNV = NULL;
PFNGLDRAWBUFFERSPROC glad_glDrawBuffers = NULL;
PFNGLDRAWBUFFERSEXTPROC glad_glDrawBuffersEXT = NULL;
PFNGLDRAWBUFFERSINDEXEDEXTPROC glad_glDrawBuffersIndexedEXT = NULL;
PFNGLDRAWBUFFERSNVPROC glad_glDrawBuffersNV = NULL;
PFNGLDRAWELEMENTSPROC glad_glDrawElements = NULL;
PFNGLDRAWELEMENTSBASEVERTEXPROC glad_glDrawElementsBaseVertex = NULL;
PFNGLDRAWELEMENTSBASEVERTEXEXTPROC glad_glDrawElementsBaseVertexEXT = NULL;
PFNGLDRAWELEMENTSBASEVERTEXOESPROC glad_glDrawElementsBaseVertexOES = NULL;
PFNGLDRAWELEMENTSINDIRECTPROC glad_glDrawElementsIndirect = NULL;
PFNGLDRAWELEMENTSINSTANCEDPROC glad_glDrawElementsInstanced = NULL;
PFNGLDRAWELEMENTSINSTANCEDANGLEPROC glad_glDrawElementsInstancedANGLE = NULL;
PFNGLDRAWELEMENTSINSTANCEDBASEINSTANCEEXTPROC glad_glDrawElementsInstancedBaseInstanceEXT = NULL;
PFNGLDRAWELEMENTSINSTANCEDBASEVERTEXPROC glad_glDrawElementsInstancedBaseVertex = NULL;
PFNGLDRAWELEMENTSINSTANCEDBASEVERTEXBASEINSTANCEEXTPROC glad_glDrawElementsInstancedBaseVertexBaseInstanceEXT = NULL;
PFNGLDRAWELEMENTSINSTANCEDBASEVERTEXEXTPROC glad_glDrawElementsInstancedBaseVertexEXT = NULL;
PFNGLDRAWELEMENTSINSTANCEDBASEVERTEXOESPROC glad_glDrawElementsInstancedBaseVertexOES = NULL;
PFNGLDRAWELEMENTSINSTANCEDEXTPROC glad_glDrawElementsInstancedEXT = NULL;
PFNGLDRAWELEMENTSINSTANCEDNVPROC glad_glDrawElementsInstancedNV = NULL;
PFNGLDRAWMESHTASKSINDIRECTNVPROC glad_glDrawMeshTasksIndirectNV = NULL;
PFNGLDRAWMESHTASKSNVPROC glad_glDrawMeshTasksNV = NULL;
PFNGLDRAWRANGEELEMENTSPROC glad_glDrawRangeElements = NULL;
PFNGLDRAWRANGEELEMENTSBASEVERTEXPROC glad_glDrawRangeElementsBaseVertex = NULL;
PFNGLDRAWRANGEELEMENTSBASEVERTEXEXTPROC glad_glDrawRangeElementsBaseVertexEXT = NULL;
PFNGLDRAWRANGEELEMENTSBASEVERTEXOESPROC glad_glDrawRangeElementsBaseVertexOES = NULL;
PFNGLDRAWTRANSFORMFEEDBACKEXTPROC glad_glDrawTransformFeedbackEXT = NULL;
PFNGLDRAWTRANSFORMFEEDBACKINSTANCEDEXTPROC glad_glDrawTransformFeedbackInstancedEXT = NULL;
PFNGLDRAWVKIMAGENVPROC glad_glDrawVkImageNV = NULL;
PFNGLEGLIMAGETARGETRENDERBUFFERSTORAGEOESPROC glad_glEGLImageTargetRenderbufferStorageOES = NULL;
PFNGLEGLIMAGETARGETTEXSTORAGEEXTPROC glad_glEGLImageTargetTexStorageEXT = NULL;
PFNGLEGLIMAGETARGETTEXTURE2DOESPROC glad_glEGLImageTargetTexture2DOES = NULL;
PFNGLEGLIMAGETARGETTEXTURESTORAGEEXTPROC glad_glEGLImageTargetTextureStorageEXT = NULL;
PFNGLENABLEPROC glad_glEnable = NULL;
PFNGLENABLEDRIVERCONTROLQCOMPROC glad_glEnableDriverControlQCOM = NULL;
PFNGLENABLEVERTEXATTRIBARRAYPROC glad_glEnableVertexAttribArray = NULL;
PFNGLENABLEIPROC glad_glEnablei = NULL;
PFNGLENABLEIEXTPROC glad_glEnableiEXT = NULL;
PFNGLENABLEINVPROC glad_glEnableiNV = NULL;
PFNGLENABLEIOESPROC glad_glEnableiOES = NULL;
PFNGLENDCONDITIONALRENDERNVPROC glad_glEndConditionalRenderNV = NULL;
PFNGLENDPERFMONITORAMDPROC glad_glEndPerfMonitorAMD = NULL;
PFNGLENDPERFQUERYINTELPROC glad_glEndPerfQueryINTEL = NULL;
PFNGLENDQUERYPROC glad_glEndQuery = NULL;
PFNGLENDQUERYEXTPROC glad_glEndQueryEXT = NULL;
PFNGLENDTILINGQCOMPROC glad_glEndTilingQCOM = NULL;
PFNGLENDTRANSFORMFEEDBACKPROC glad_glEndTransformFeedback = NULL;
PFNGLEXTGETBUFFERPOINTERVQCOMPROC glad_glExtGetBufferPointervQCOM = NULL;
PFNGLEXTGETBUFFERSQCOMPROC glad_glExtGetBuffersQCOM = NULL;
PFNGLEXTGETFRAMEBUFFERSQCOMPROC glad_glExtGetFramebuffersQCOM = NULL;
PFNGLEXTGETPROGRAMBINARYSOURCEQCOMPROC glad_glExtGetProgramBinarySourceQCOM = NULL;
PFNGLEXTGETPROGRAMSQCOMPROC glad_glExtGetProgramsQCOM = NULL;
PFNGLEXTGETRENDERBUFFERSQCOMPROC glad_glExtGetRenderbuffersQCOM = NULL;
PFNGLEXTGETSHADERSQCOMPROC glad_glExtGetShadersQCOM = NULL;
PFNGLEXTGETTEXLEVELPARAMETERIVQCOMPROC glad_glExtGetTexLevelParameterivQCOM = NULL;
PFNGLEXTGETTEXSUBIMAGEQCOMPROC glad_glExtGetTexSubImageQCOM = NULL;
PFNGLEXTGETTEXTURESQCOMPROC glad_glExtGetTexturesQCOM = NULL;
PFNGLEXTISPROGRAMBINARYQCOMPROC glad_glExtIsProgramBinaryQCOM = NULL;
PFNGLEXTTEXOBJECTSTATEOVERRIDEIQCOMPROC glad_glExtTexObjectStateOverrideiQCOM = NULL;
PFNGLEXTRAPOLATETEX2DQCOMPROC glad_glExtrapolateTex2DQCOM = NULL;
PFNGLFENCESYNCPROC glad_glFenceSync = NULL;
PFNGLFENCESYNCAPPLEPROC glad_glFenceSyncAPPLE = NULL;
PFNGLFINISHPROC glad_glFinish = NULL;
PFNGLFINISHFENCENVPROC glad_glFinishFenceNV = NULL;
PFNGLFLUSHPROC glad_glFlush = NULL;
PFNGLFLUSHMAPPEDBUFFERRANGEPROC glad_glFlushMappedBufferRange = NULL;
PFNGLFLUSHMAPPEDBUFFERRANGEEXTPROC glad_glFlushMappedBufferRangeEXT = NULL;
PFNGLFRAGMENTCOVERAGECOLORNVPROC glad_glFragmentCoverageColorNV = NULL;
PFNGLFRAMEBUFFERFETCHBARRIEREXTPROC glad_glFramebufferFetchBarrierEXT = NULL;
PFNGLFRAMEBUFFERFETCHBARRIERQCOMPROC glad_glFramebufferFetchBarrierQCOM = NULL;
PFNGLFRAMEBUFFERFOVEATIONCONFIGQCOMPROC glad_glFramebufferFoveationConfigQCOM = NULL;
PFNGLFRAMEBUFFERFOVEATIONPARAMETERSQCOMPROC glad_glFramebufferFoveationParametersQCOM = NULL;
PFNGLFRAMEBUFFERPARAMETERIPROC glad_glFramebufferParameteri = NULL;
PFNGLFRAMEBUFFERPARAMETERIMESAPROC glad_glFramebufferParameteriMESA = NULL;
PFNGLFRAMEBUFFERPIXELLOCALSTORAGESIZEEXTPROC glad_glFramebufferPixelLocalStorageSizeEXT = NULL;
PFNGLFRAMEBUFFERRENDERBUFFERPROC glad_glFramebufferRenderbuffer = NULL;
PFNGLFRAMEBUFFERSAMPLELOCATIONSFVNVPROC glad_glFramebufferSampleLocationsfvNV = NULL;
PFNGLFRAMEBUFFERSHADINGRATEEXTPROC glad_glFramebufferShadingRateEXT = NULL;
PFNGLFRAMEBUFFERTEXTUREPROC glad_glFramebufferTexture = NULL;
PFNGLFRAMEBUFFERTEXTURE2DPROC glad_glFramebufferTexture2D = NULL;
PFNGLFRAMEBUFFERTEXTURE2DDOWNSAMPLEIMGPROC glad_glFramebufferTexture2DDownsampleIMG = NULL;
PFNGLFRAMEBUFFERTEXTURE2DMULTISAMPLEEXTPROC glad_glFramebufferTexture2DMultisampleEXT = NULL;
PFNGLFRAMEBUFFERTEXTURE2DMULTISAMPLEIMGPROC glad_glFramebufferTexture2DMultisampleIMG = NULL;
PFNGLFRAMEBUFFERTEXTURE3DOESPROC glad_glFramebufferTexture3DOES = NULL;
PFNGLFRAMEBUFFERTEXTUREEXTPROC glad_glFramebufferTextureEXT = NULL;
PFNGLFRAMEBUFFERTEXTURELAYERPROC glad_glFramebufferTextureLayer = NULL;
PFNGLFRAMEBUFFERTEXTURELAYERDOWNSAMPLEIMGPROC glad_glFramebufferTextureLayerDownsampleIMG = NULL;
PFNGLFRAMEBUFFERTEXTUREMULTISAMPLEMULTIVIEWOVRPROC glad_glFramebufferTextureMultisampleMultiviewOVR = NULL;
PFNGLFRAMEBUFFERTEXTUREMULTIVIEWOVRPROC glad_glFramebufferTextureMultiviewOVR = NULL;
PFNGLFRAMEBUFFERTEXTUREOESPROC glad_glFramebufferTextureOES = NULL;
PFNGLFRONTFACEPROC glad_glFrontFace = NULL;
PFNGLGENBUFFERSPROC glad_glGenBuffers = NULL;
PFNGLGENFENCESNVPROC glad_glGenFencesNV = NULL;
PFNGLGENFRAMEBUFFERSPROC glad_glGenFramebuffers = NULL;
PFNGLGENPATHSNVPROC glad_glGenPathsNV = NULL;
PFNGLGENPERFMONITORSAMDPROC glad_glGenPerfMonitorsAMD = NULL;
PFNGLGENPROGRAMPIPELINESPROC glad_glGenProgramPipelines = NULL;
PFNGLGENPROGRAMPIPELINESEXTPROC glad_glGenProgramPipelinesEXT = NULL;
PFNGLGENQUERIESPROC glad_glGenQueries = NULL;
PFNGLGENQUERIESEXTPROC glad_glGenQueriesEXT = NULL;
PFNGLGENRENDERBUFFERSPROC glad_glGenRenderbuffers = NULL;
PFNGLGENSAMPLERSPROC glad_glGenSamplers = NULL;
PFNGLGENSEMAPHORESEXTPROC glad_glGenSemaphoresEXT = NULL;
PFNGLGENTEXTURESPROC glad_glGenTextures = NULL;
PFNGLGENTRANSFORMFEEDBACKSPROC glad_glGenTransformFeedbacks = NULL;
PFNGLGENVERTEXARRAYSPROC glad_glGenVertexArrays = NULL;
PFNGLGENVERTEXARRAYSOESPROC glad_glGenVertexArraysOES = NULL;
PFNGLGENERATEMIPMAPPROC glad_glGenerateMipmap = NULL;
PFNGLGETACTIVEATTRIBPROC glad_glGetActiveAttrib = NULL;
PFNGLGETACTIVEUNIFORMPROC glad_glGetActiveUniform = NULL;
PFNGLGETACTIVEUNIFORMBLOCKNAMEPROC glad_glGetActiveUniformBlockName = NULL;
PFNGLGETACTIVEUNIFORMBLOCKIVPROC glad_glGetActiveUniformBlockiv = NULL;
PFNGLGETACTIVEUNIFORMSIVPROC glad_glGetActiveUniformsiv = NULL;
PFNGLGETATTACHEDSHADERSPROC glad_glGetAttachedShaders = NULL;
PFNGLGETATTRIBLOCATIONPROC glad_glGetAttribLocation = NULL;
PFNGLGETBOOLEANI_VPROC glad_glGetBooleani_v = NULL;
PFNGLGETBOOLEANVPROC glad_glGetBooleanv = NULL;
PFNGLGETBUFFERPARAMETERI64VPROC glad_glGetBufferParameteri64v = NULL;
PFNGLGETBUFFERPARAMETERIVPROC glad_glGetBufferParameteriv = NULL;
PFNGLGETBUFFERPOINTERVPROC glad_glGetBufferPointerv = NULL;
PFNGLGETBUFFERPOINTERVOESPROC glad_glGetBufferPointervOES = NULL;
PFNGLGETCOVERAGEMODULATIONTABLENVPROC glad_glGetCoverageModulationTableNV = NULL;
PFNGLGETDEBUGMESSAGELOGPROC glad_glGetDebugMessageLog = NULL;
PFNGLGETDEBUGMESSAGELOGKHRPROC glad_glGetDebugMessageLogKHR = NULL;
PFNGLGETDRIVERCONTROLSTRINGQCOMPROC glad_glGetDriverControlStringQCOM = NULL;
PFNGLGETDRIVERCONTROLSQCOMPROC glad_glGetDriverControlsQCOM = NULL;
PFNGLGETERRORPROC glad_glGetError = NULL;
PFNGLGETFENCEIVNVPROC glad_glGetFenceivNV = NULL;
PFNGLGETFIRSTPERFQUERYIDINTELPROC glad_glGetFirstPerfQueryIdINTEL = NULL;
PFNGLGETFLOATI_VNVPROC glad_glGetFloati_vNV = NULL;
PFNGLGETFLOATI_VOESPROC glad_glGetFloati_vOES = NULL;
PFNGLGETFLOATVPROC glad_glGetFloatv = NULL;
PFNGLGETFRAGDATAINDEXEXTPROC glad_glGetFragDataIndexEXT = NULL;
PFNGLGETFRAGDATALOCATIONPROC glad_glGetFragDataLocation = NULL;
PFNGLGETFRAGMENTSHADINGRATESEXTPROC glad_glGetFragmentShadingRatesEXT = NULL;
PFNGLGETFRAMEBUFFERATTACHMENTPARAMETERIVPROC glad_glGetFramebufferAttachmentParameteriv = NULL;
PFNGLGETFRAMEBUFFERPARAMETERIVPROC glad_glGetFramebufferParameteriv = NULL;
PFNGLGETFRAMEBUFFERPARAMETERIVMESAPROC glad_glGetFramebufferParameterivMESA = NULL;
PFNGLGETFRAMEBUFFERPIXELLOCALSTORAGESIZEEXTPROC glad_glGetFramebufferPixelLocalStorageSizeEXT = NULL;
PFNGLGETGRAPHICSRESETSTATUSPROC glad_glGetGraphicsResetStatus = NULL;
PFNGLGETGRAPHICSRESETSTATUSEXTPROC glad_glGetGraphicsResetStatusEXT = NULL;
PFNGLGETGRAPHICSRESETSTATUSKHRPROC glad_glGetGraphicsResetStatusKHR = NULL;
PFNGLGETIMAGEHANDLENVPROC glad_glGetImageHandleNV = NULL;
PFNGLGETINTEGER64I_VPROC glad_glGetInteger64i_v = NULL;
PFNGLGETINTEGER64VPROC glad_glGetInteger64v = NULL;
PFNGLGETINTEGER64VAPPLEPROC glad_glGetInteger64vAPPLE = NULL;
PFNGLGETINTEGER64VEXTPROC glad_glGetInteger64vEXT = NULL;
PFNGLGETINTEGERI_VPROC glad_glGetIntegeri_v = NULL;
PFNGLGETINTEGERI_VEXTPROC glad_glGetIntegeri_vEXT = NULL;
PFNGLGETINTEGERVPROC glad_glGetIntegerv = NULL;
PFNGLGETINTERNALFORMATSAMPLEIVNVPROC glad_glGetInternalformatSampleivNV = NULL;
PFNGLGETINTERNALFORMATIVPROC glad_glGetInternalformativ = NULL;
PFNGLGETMEMORYOBJECTDETACHEDRESOURCESUIVNVPROC glad_glGetMemoryObjectDetachedResourcesuivNV = NULL;
PFNGLGETMEMORYOBJECTPARAMETERIVEXTPROC glad_glGetMemoryObjectParameterivEXT = NULL;
PFNGLGETMULTISAMPLEFVPROC glad_glGetMultisamplefv = NULL;
PFNGLGETNEXTPERFQUERYIDINTELPROC glad_glGetNextPerfQueryIdINTEL = NULL;
PFNGLGETOBJECTLABELPROC glad_glGetObjectLabel = NULL;
PFNGLGETOBJECTLABELEXTPROC glad_glGetObjectLabelEXT = NULL;
PFNGLGETOBJECTLABELKHRPROC glad_glGetObjectLabelKHR = NULL;
PFNGLGETOBJECTPTRLABELPROC glad_glGetObjectPtrLabel = NULL;
PFNGLGETOBJECTPTRLABELKHRPROC glad_glGetObjectPtrLabelKHR = NULL;
PFNGLGETPATHCOMMANDSNVPROC glad_glGetPathCommandsNV = NULL;
PFNGLGETPATHCOORDSNVPROC glad_glGetPathCoordsNV = NULL;
PFNGLGETPATHDASHARRAYNVPROC glad_glGetPathDashArrayNV = NULL;
PFNGLGETPATHLENGTHNVPROC glad_glGetPathLengthNV = NULL;
PFNGLGETPATHMETRICRANGENVPROC glad_glGetPathMetricRangeNV = NULL;
PFNGLGETPATHMETRICSNVPROC glad_glGetPathMetricsNV = NULL;
PFNGLGETPATHPARAMETERFVNVPROC glad_glGetPathParameterfvNV = NULL;
PFNGLGETPATHPARAMETERIVNVPROC glad_glGetPathParameterivNV = NULL;
PFNGLGETPATHSPACINGNVPROC glad_glGetPathSpacingNV = NULL;
PFNGLGETPERFCOUNTERINFOINTELPROC glad_glGetPerfCounterInfoINTEL = NULL;
PFNGLGETPERFMONITORCOUNTERDATAAMDPROC glad_glGetPerfMonitorCounterDataAMD = NULL;
PFNGLGETPERFMONITORCOUNTERINFOAMDPROC glad_glGetPerfMonitorCounterInfoAMD = NULL;
PFNGLGETPERFMONITORCOUNTERSTRINGAMDPROC glad_glGetPerfMonitorCounterStringAMD = NULL;
PFNGLGETPERFMONITORCOUNTERSAMDPROC glad_glGetPerfMonitorCountersAMD = NULL;
PFNGLGETPERFMONITORGROUPSTRINGAMDPROC glad_glGetPerfMonitorGroupStringAMD = NULL;
PFNGLGETPERFMONITORGROUPSAMDPROC glad_glGetPerfMonitorGroupsAMD = NULL;
PFNGLGETPERFQUERYDATAINTELPROC glad_glGetPerfQueryDataINTEL = NULL;
PFNGLGETPERFQUERYIDBYNAMEINTELPROC glad_glGetPerfQueryIdByNameINTEL = NULL;
PFNGLGETPERFQUERYINFOINTELPROC glad_glGetPerfQueryInfoINTEL = NULL;
PFNGLGETPOINTERVPROC glad_glGetPointerv = NULL;
PFNGLGETPOINTERVKHRPROC glad_glGetPointervKHR = NULL;
PFNGLGETPROGRAMBINARYPROC glad_glGetProgramBinary = NULL;
PFNGLGETPROGRAMBINARYOESPROC glad_glGetProgramBinaryOES = NULL;
PFNGLGETPROGRAMINFOLOGPROC glad_glGetProgramInfoLog = NULL;
PFNGLGETPROGRAMINTERFACEIVPROC glad_glGetProgramInterfaceiv = NULL;
PFNGLGETPROGRAMPIPELINEINFOLOGPROC glad_glGetProgramPipelineInfoLog = NULL;
PFNGLGETPROGRAMPIPELINEINFOLOGEXTPROC glad_glGetProgramPipelineInfoLogEXT = NULL;
PFNGLGETPROGRAMPIPELINEIVPROC glad_glGetProgramPipelineiv = NULL;
PFNGLGETPROGRAMPIPELINEIVEXTPROC glad_glGetProgramPipelineivEXT = NULL;
PFNGLGETPROGRAMRESOURCEINDEXPROC glad_glGetProgramResourceIndex = NULL;
PFNGLGETPROGRAMRESOURCELOCATIONPROC glad_glGetProgramResourceLocation = NULL;
PFNGLGETPROGRAMRESOURCELOCATIONINDEXEXTPROC glad_glGetProgramResourceLocationIndexEXT = NULL;
PFNGLGETPROGRAMRESOURCENAMEPROC glad_glGetProgramResourceName = NULL;
PFNGLGETPROGRAMRESOURCEFVNVPROC glad_glGetProgramResourcefvNV = NULL;
PFNGLGETPROGRAMRESOURCEIVPROC glad_glGetProgramResourceiv = NULL;
PFNGLGETPROGRAMIVPROC glad_glGetProgramiv = NULL;
PFNGLGETQUERYOBJECTI64VEXTPROC glad_glGetQueryObjecti64vEXT = NULL;
PFNGLGETQUERYOBJECTIVEXTPROC glad_glGetQueryObjectivEXT = NULL;
PFNGLGETQUERYOBJECTUI64VEXTPROC glad_glGetQueryObjectui64vEXT = NULL;
PFNGLGETQUERYOBJECTUIVPROC glad_glGetQueryObjectuiv = NULL;
PFNGLGETQUERYOBJECTUIVEXTPROC glad_glGetQueryObjectuivEXT = NULL;
PFNGLGETQUERYIVPROC glad_glGetQueryiv = NULL;
PFNGLGETQUERYIVEXTPROC glad_glGetQueryivEXT = NULL;
PFNGLGETRENDERBUFFERPARAMETERIVPROC glad_glGetRenderbufferParameteriv = NULL;
PFNGLGETSAMPLERPARAMETERIIVPROC glad_glGetSamplerParameterIiv = NULL;
PFNGLGETSAMPLERPARAMETERIIVEXTPROC glad_glGetSamplerParameterIivEXT = NULL;
PFNGLGETSAMPLERPARAMETERIIVOESPROC glad_glGetSamplerParameterIivOES = NULL;
PFNGLGETSAMPLERPARAMETERIUIVPROC glad_glGetSamplerParameterIuiv = NULL;
PFNGLGETSAMPLERPARAMETERIUIVEXTPROC glad_glGetSamplerParameterIuivEXT = NULL;
PFNGLGETSAMPLERPARAMETERIUIVOESPROC glad_glGetSamplerParameterIuivOES = NULL;
PFNGLGETSAMPLERPARAMETERFVPROC glad_glGetSamplerParameterfv = NULL;
PFNGLGETSAMPLERPARAMETERIVPROC glad_glGetSamplerParameteriv = NULL;
PFNGLGETSEMAPHOREPARAMETERIVNVPROC glad_glGetSemaphoreParameterivNV = NULL;
PFNGLGETSEMAPHOREPARAMETERUI64VEXTPROC glad_glGetSemaphoreParameterui64vEXT = NULL;
PFNGLGETSHADERINFOLOGPROC glad_glGetShaderInfoLog = NULL;
PFNGLGETSHADERPRECISIONFORMATPROC glad_glGetShaderPrecisionFormat = NULL;
PFNGLGETSHADERSOURCEPROC glad_glGetShaderSource = NULL;
PFNGLGETSHADERIVPROC glad_glGetShaderiv = NULL;
PFNGLGETSHADINGRATEIMAGEPALETTENVPROC glad_glGetShadingRateImagePaletteNV = NULL;
PFNGLGETSHADINGRATESAMPLELOCATIONIVNVPROC glad_glGetShadingRateSampleLocationivNV = NULL;
PFNGLGETSTRINGPROC glad_glGetString = NULL;
PFNGLGETSTRINGIPROC glad_glGetStringi = NULL;
PFNGLGETSYNCIVPROC glad_glGetSynciv = NULL;
PFNGLGETSYNCIVAPPLEPROC glad_glGetSyncivAPPLE = NULL;
PFNGLGETTEXLEVELPARAMETERFVPROC glad_glGetTexLevelParameterfv = NULL;
PFNGLGETTEXLEVELPARAMETERIVPROC glad_glGetTexLevelParameteriv = NULL;
PFNGLGETTEXPARAMETERIIVPROC glad_glGetTexParameterIiv = NULL;
PFNGLGETTEXPARAMETERIIVEXTPROC glad_glGetTexParameterIivEXT = NULL;
PFNGLGETTEXPARAMETERIIVOESPROC glad_glGetTexParameterIivOES = NULL;
PFNGLGETTEXPARAMETERIUIVPROC glad_glGetTexParameterIuiv = NULL;
PFNGLGETTEXPARAMETERIUIVEXTPROC glad_glGetTexParameterIuivEXT = NULL;
PFNGLGETTEXPARAMETERIUIVOESPROC glad_glGetTexParameterIuivOES = NULL;
PFNGLGETTEXPARAMETERFVPROC glad_glGetTexParameterfv = NULL;
PFNGLGETTEXPARAMETERIVPROC glad_glGetTexParameteriv = NULL;
PFNGLGETTEXTUREHANDLEIMGPROC glad_glGetTextureHandleIMG = NULL;
PFNGLGETTEXTUREHANDLENVPROC glad_glGetTextureHandleNV = NULL;
PFNGLGETTEXTURESAMPLERHANDLEIMGPROC glad_glGetTextureSamplerHandleIMG = NULL;
PFNGLGETTEXTURESAMPLERHANDLENVPROC glad_glGetTextureSamplerHandleNV = NULL;
PFNGLGETTRANSFORMFEEDBACKVARYINGPROC glad_glGetTransformFeedbackVarying = NULL;
PFNGLGETTRANSLATEDSHADERSOURCEANGLEPROC glad_glGetTranslatedShaderSourceANGLE = NULL;
PFNGLGETUNIFORMBLOCKINDEXPROC glad_glGetUniformBlockIndex = NULL;
PFNGLGETUNIFORMINDICESPROC glad_glGetUniformIndices = NULL;
PFNGLGETUNIFORMLOCATIONPROC glad_glGetUniformLocation = NULL;
PFNGLGETUNIFORMFVPROC glad_glGetUniformfv = NULL;
PFNGLGETUNIFORMI64VNVPROC glad_glGetUniformi64vNV = NULL;
PFNGLGETUNIFORMIVPROC glad_glGetUniformiv = NULL;
PFNGLGETUNIFORMUIVPROC glad_glGetUniformuiv = NULL;
PFNGLGETUNSIGNEDBYTEI_VEXTPROC glad_glGetUnsignedBytei_vEXT = NULL;
PFNGLGETUNSIGNEDBYTEVEXTPROC glad_glGetUnsignedBytevEXT = NULL;
PFNGLGETVERTEXATTRIBIIVPROC glad_glGetVertexAttribIiv = NULL;
PFNGLGETVERTEXATTRIBIUIVPROC glad_glGetVertexAttribIuiv = NULL;
PFNGLGETVERTEXATTRIBPOINTERVPROC glad_glGetVertexAttribPointerv = NULL;
PFNGLGETVERTEXATTRIBFVPROC glad_glGetVertexAttribfv = NULL;
PFNGLGETVERTEXATTRIBIVPROC glad_glGetVertexAttribiv = NULL;
PFNGLGETVKPROCADDRNVPROC glad_glGetVkProcAddrNV = NULL;
PFNGLGETNUNIFORMFVPROC glad_glGetnUniformfv = NULL;
PFNGLGETNUNIFORMFVEXTPROC glad_glGetnUniformfvEXT = NULL;
PFNGLGETNUNIFORMFVKHRPROC glad_glGetnUniformfvKHR = NULL;
PFNGLGETNUNIFORMIVPROC glad_glGetnUniformiv = NULL;
PFNGLGETNUNIFORMIVEXTPROC glad_glGetnUniformivEXT = NULL;
PFNGLGETNUNIFORMIVKHRPROC glad_glGetnUniformivKHR = NULL;
PFNGLGETNUNIFORMUIVPROC glad_glGetnUniformuiv = NULL;
PFNGLGETNUNIFORMUIVKHRPROC glad_glGetnUniformuivKHR = NULL;
PFNGLHINTPROC glad_glHint = NULL;
PFNGLIMPORTMEMORYFDEXTPROC glad_glImportMemoryFdEXT = NULL;
PFNGLIMPORTMEMORYWIN32HANDLEEXTPROC glad_glImportMemoryWin32HandleEXT = NULL;
PFNGLIMPORTMEMORYWIN32NAMEEXTPROC glad_glImportMemoryWin32NameEXT = NULL;
PFNGLIMPORTSEMAPHOREFDEXTPROC glad_glImportSemaphoreFdEXT = NULL;
PFNGLIMPORTSEMAPHOREWIN32HANDLEEXTPROC glad_glImportSemaphoreWin32HandleEXT = NULL;
PFNGLIMPORTSEMAPHOREWIN32NAMEEXTPROC glad_glImportSemaphoreWin32NameEXT = NULL;
PFNGLINSERTEVENTMARKEREXTPROC glad_glInsertEventMarkerEXT = NULL;
PFNGLINTERPOLATEPATHSNVPROC glad_glInterpolatePathsNV = NULL;
PFNGLINVALIDATEFRAMEBUFFERPROC glad_glInvalidateFramebuffer = NULL;
PFNGLINVALIDATESUBFRAMEBUFFERPROC glad_glInvalidateSubFramebuffer = NULL;
PFNGLISBUFFERPROC glad_glIsBuffer = NULL;
PFNGLISENABLEDPROC glad_glIsEnabled = NULL;
PFNGLISENABLEDIPROC glad_glIsEnabledi = NULL;
PFNGLISENABLEDIEXTPROC glad_glIsEnablediEXT = NULL;
PFNGLISENABLEDINVPROC glad_glIsEnablediNV = NULL;
PFNGLISENABLEDIOESPROC glad_glIsEnablediOES = NULL;
PFNGLISFENCENVPROC glad_glIsFenceNV = NULL;
PFNGLISFRAMEBUFFERPROC glad_glIsFramebuffer = NULL;
PFNGLISIMAGEHANDLERESIDENTNVPROC glad_glIsImageHandleResidentNV = NULL;
PFNGLISMEMORYOBJECTEXTPROC glad_glIsMemoryObjectEXT = NULL;
PFNGLISPATHNVPROC glad_glIsPathNV = NULL;
PFNGLISPOINTINFILLPATHNVPROC glad_glIsPointInFillPathNV = NULL;
PFNGLISPOINTINSTROKEPATHNVPROC glad_glIsPointInStrokePathNV = NULL;
PFNGLISPROGRAMPROC glad_glIsProgram = NULL;
PFNGLISPROGRAMPIPELINEPROC glad_glIsProgramPipeline = NULL;
PFNGLISPROGRAMPIPELINEEXTPROC glad_glIsProgramPipelineEXT = NULL;
PFNGLISQUERYPROC glad_glIsQuery = NULL;
PFNGLISQUERYEXTPROC glad_glIsQueryEXT = NULL;
PFNGLISRENDERBUFFERPROC glad_glIsRenderbuffer = NULL;
PFNGLISSAMPLERPROC glad_glIsSampler = NULL;
PFNGLISSEMAPHOREEXTPROC glad_glIsSemaphoreEXT = NULL;
PFNGLISSHADERPROC glad_glIsShader = NULL;
PFNGLISSYNCPROC glad_glIsSync = NULL;
PFNGLISSYNCAPPLEPROC glad_glIsSyncAPPLE = NULL;
PFNGLISTEXTUREPROC glad_glIsTexture = NULL;
PFNGLISTEXTUREHANDLERESIDENTNVPROC glad_glIsTextureHandleResidentNV = NULL;
PFNGLISTRANSFORMFEEDBACKPROC glad_glIsTransformFeedback = NULL;
PFNGLISVERTEXARRAYPROC glad_glIsVertexArray = NULL;
PFNGLISVERTEXARRAYOESPROC glad_glIsVertexArrayOES = NULL;
PFNGLLABELOBJECTEXTPROC glad_glLabelObjectEXT = NULL;
PFNGLLINEWIDTHPROC glad_glLineWidth = NULL;
PFNGLLINKPROGRAMPROC glad_glLinkProgram = NULL;
PFNGLMAKEIMAGEHANDLENONRESIDENTNVPROC glad_glMakeImageHandleNonResidentNV = NULL;
PFNGLMAKEIMAGEHANDLERESIDENTNVPROC glad_glMakeImageHandleResidentNV = NULL;
PFNGLMAKETEXTUREHANDLENONRESIDENTNVPROC glad_glMakeTextureHandleNonResidentNV = NULL;
PFNGLMAKETEXTUREHANDLERESIDENTNVPROC glad_glMakeTextureHandleResidentNV = NULL;
PFNGLMAPBUFFEROESPROC glad_glMapBufferOES = NULL;
PFNGLMAPBUFFERRANGEPROC glad_glMapBufferRange = NULL;
PFNGLMAPBUFFERRANGEEXTPROC glad_glMapBufferRangeEXT = NULL;
PFNGLMATRIXFRUSTUMEXTPROC glad_glMatrixFrustumEXT = NULL;
PFNGLMATRIXLOAD3X2FNVPROC glad_glMatrixLoad3x2fNV = NULL;
PFNGLMATRIXLOAD3X3FNVPROC glad_glMatrixLoad3x3fNV = NULL;
PFNGLMATRIXLOADIDENTITYEXTPROC glad_glMatrixLoadIdentityEXT = NULL;
PFNGLMATRIXLOADTRANSPOSE3X3FNVPROC glad_glMatrixLoadTranspose3x3fNV = NULL;
PFNGLMATRIXLOADTRANSPOSEDEXTPROC glad_glMatrixLoadTransposedEXT = NULL;
PFNGLMATRIXLOADTRANSPOSEFEXTPROC glad_glMatrixLoadTransposefEXT = NULL;
PFNGLMATRIXLOADDEXTPROC glad_glMatrixLoaddEXT = NULL;
PFNGLMATRIXLOADFEXTPROC glad_glMatrixLoadfEXT = NULL;
PFNGLMATRIXMULT3X2FNVPROC glad_glMatrixMult3x2fNV = NULL;
PFNGLMATRIXMULT3X3FNVPROC glad_glMatrixMult3x3fNV = NULL;
PFNGLMATRIXMULTTRANSPOSE3X3FNVPROC glad_glMatrixMultTranspose3x3fNV = NULL;
PFNGLMATRIXMULTTRANSPOSEDEXTPROC glad_glMatrixMultTransposedEXT = NULL;
PFNGLMATRIXMULTTRANSPOSEFEXTPROC glad_glMatrixMultTransposefEXT = NULL;
PFNGLMATRIXMULTDEXTPROC glad_glMatrixMultdEXT = NULL;
PFNGLMATRIXMULTFEXTPROC glad_glMatrixMultfEXT = NULL;
PFNGLMATRIXORTHOEXTPROC glad_glMatrixOrthoEXT = NULL;
PFNGLMATRIXPOPEXTPROC glad_glMatrixPopEXT = NULL;
PFNGLMATRIXPUSHEXTPROC glad_glMatrixPushEXT = NULL;
PFNGLMATRIXROTATEDEXTPROC glad_glMatrixRotatedEXT = NULL;
PFNGLMATRIXROTATEFEXTPROC glad_glMatrixRotatefEXT = NULL;
PFNGLMATRIXSCALEDEXTPROC glad_glMatrixScaledEXT = NULL;
PFNGLMATRIXSCALEFEXTPROC glad_glMatrixScalefEXT = NULL;
PFNGLMATRIXTRANSLATEDEXTPROC glad_glMatrixTranslatedEXT = NULL;
PFNGLMATRIXTRANSLATEFEXTPROC glad_glMatrixTranslatefEXT = NULL;
PFNGLMAXSHADERCOMPILERTHREADSKHRPROC glad_glMaxShaderCompilerThreadsKHR = NULL;
PFNGLMEMORYBARRIERPROC glad_glMemoryBarrier = NULL;
PFNGLMEMORYBARRIERBYREGIONPROC glad_glMemoryBarrierByRegion = NULL;
PFNGLMEMORYOBJECTPARAMETERIVEXTPROC glad_glMemoryObjectParameterivEXT = NULL;
PFNGLMINSAMPLESHADINGPROC glad_glMinSampleShading = NULL;
PFNGLMINSAMPLESHADINGOESPROC glad_glMinSampleShadingOES = NULL;
PFNGLMULTIDRAWARRAYSEXTPROC glad_glMultiDrawArraysEXT = NULL;
PFNGLMULTIDRAWARRAYSINDIRECTEXTPROC glad_glMultiDrawArraysIndirectEXT = NULL;
PFNGLMULTIDRAWELEMENTSBASEVERTEXEXTPROC glad_glMultiDrawElementsBaseVertexEXT = NULL;
PFNGLMULTIDRAWELEMENTSEXTPROC glad_glMultiDrawElementsEXT = NULL;
PFNGLMULTIDRAWELEMENTSINDIRECTEXTPROC glad_glMultiDrawElementsIndirectEXT = NULL;
PFNGLMULTIDRAWMESHTASKSINDIRECTCOUNTNVPROC glad_glMultiDrawMeshTasksIndirectCountNV = NULL;
PFNGLMULTIDRAWMESHTASKSINDIRECTNVPROC glad_glMultiDrawMeshTasksIndirectNV = NULL;
PFNGLNAMEDBUFFERATTACHMEMORYNVPROC glad_glNamedBufferAttachMemoryNV = NULL;
PFNGLNAMEDBUFFERPAGECOMMITMENTMEMNVPROC glad_glNamedBufferPageCommitmentMemNV = NULL;
PFNGLNAMEDBUFFERSTORAGEEXTERNALEXTPROC glad_glNamedBufferStorageExternalEXT = NULL;
PFNGLNAMEDBUFFERSTORAGEMEMEXTPROC glad_glNamedBufferStorageMemEXT = NULL;
PFNGLNAMEDFRAMEBUFFERSAMPLELOCATIONSFVNVPROC glad_glNamedFramebufferSampleLocationsfvNV = NULL;
PFNGLNAMEDRENDERBUFFERSTORAGEMULTISAMPLEADVANCEDAMDPROC glad_glNamedRenderbufferStorageMultisampleAdvancedAMD = NULL;
PFNGLOBJECTLABELPROC glad_glObjectLabel = NULL;
PFNGLOBJECTLABELKHRPROC glad_glObjectLabelKHR = NULL;
PFNGLOBJECTPTRLABELPROC glad_glObjectPtrLabel = NULL;
PFNGLOBJECTPTRLABELKHRPROC glad_glObjectPtrLabelKHR = NULL;
PFNGLPATCHPARAMETERIPROC glad_glPatchParameteri = NULL;
PFNGLPATCHPARAMETERIEXTPROC glad_glPatchParameteriEXT = NULL;
PFNGLPATCHPARAMETERIOESPROC glad_glPatchParameteriOES = NULL;
PFNGLPATHCOMMANDSNVPROC glad_glPathCommandsNV = NULL;
PFNGLPATHCOORDSNVPROC glad_glPathCoordsNV = NULL;
PFNGLPATHCOVERDEPTHFUNCNVPROC glad_glPathCoverDepthFuncNV = NULL;
PFNGLPATHDASHARRAYNVPROC glad_glPathDashArrayNV = NULL;
PFNGLPATHGLYPHINDEXARRAYNVPROC glad_glPathGlyphIndexArrayNV = NULL;
PFNGLPATHGLYPHINDEXRANGENVPROC glad_glPathGlyphIndexRangeNV = NULL;
PFNGLPATHGLYPHRANGENVPROC glad_glPathGlyphRangeNV = NULL;
PFNGLPATHGLYPHSNVPROC glad_glPathGlyphsNV = NULL;
PFNGLPATHMEMORYGLYPHINDEXARRAYNVPROC glad_glPathMemoryGlyphIndexArrayNV = NULL;
PFNGLPATHPARAMETERFNVPROC glad_glPathParameterfNV = NULL;
PFNGLPATHPARAMETERFVNVPROC glad_glPathParameterfvNV = NULL;
PFNGLPATHPARAMETERINVPROC glad_glPathParameteriNV = NULL;
PFNGLPATHPARAMETERIVNVPROC glad_glPathParameterivNV = NULL;
PFNGLPATHSTENCILDEPTHOFFSETNVPROC glad_glPathStencilDepthOffsetNV = NULL;
PFNGLPATHSTENCILFUNCNVPROC glad_glPathStencilFuncNV = NULL;
PFNGLPATHSTRINGNVPROC glad_glPathStringNV = NULL;
PFNGLPATHSUBCOMMANDSNVPROC glad_glPathSubCommandsNV = NULL;
PFNGLPATHSUBCOORDSNVPROC glad_glPathSubCoordsNV = NULL;
PFNGLPAUSETRANSFORMFEEDBACKPROC glad_glPauseTransformFeedback = NULL;
PFNGLPIXELSTOREIPROC glad_glPixelStorei = NULL;
PFNGLPOINTALONGPATHNVPROC glad_glPointAlongPathNV = NULL;
PFNGLPOLYGONMODENVPROC glad_glPolygonModeNV = NULL;
PFNGLPOLYGONOFFSETPROC glad_glPolygonOffset = NULL;
PFNGLPOLYGONOFFSETCLAMPEXTPROC glad_glPolygonOffsetClampEXT = NULL;
PFNGLPOPDEBUGGROUPPROC glad_glPopDebugGroup = NULL;
PFNGLPOPDEBUGGROUPKHRPROC glad_glPopDebugGroupKHR = NULL;
PFNGLPOPGROUPMARKEREXTPROC glad_glPopGroupMarkerEXT = NULL;
PFNGLPRIMITIVEBOUNDINGBOXPROC glad_glPrimitiveBoundingBox = NULL;
PFNGLPRIMITIVEBOUNDINGBOXEXTPROC glad_glPrimitiveBoundingBoxEXT = NULL;
PFNGLPRIMITIVEBOUNDINGBOXOESPROC glad_glPrimitiveBoundingBoxOES = NULL;
PFNGLPROGRAMBINARYPROC glad_glProgramBinary = NULL;
PFNGLPROGRAMBINARYOESPROC glad_glProgramBinaryOES = NULL;
PFNGLPROGRAMPARAMETERIPROC glad_glProgramParameteri = NULL;
PFNGLPROGRAMPARAMETERIEXTPROC glad_glProgramParameteriEXT = NULL;
PFNGLPROGRAMPATHFRAGMENTINPUTGENNVPROC glad_glProgramPathFragmentInputGenNV = NULL;
PFNGLPROGRAMUNIFORM1FPROC glad_glProgramUniform1f = NULL;
PFNGLPROGRAMUNIFORM1FEXTPROC glad_glProgramUniform1fEXT = NULL;
PFNGLPROGRAMUNIFORM1FVPROC glad_glProgramUniform1fv = NULL;
PFNGLPROGRAMUNIFORM1FVEXTPROC glad_glProgramUniform1fvEXT = NULL;
PFNGLPROGRAMUNIFORM1IPROC glad_glProgramUniform1i = NULL;
PFNGLPROGRAMUNIFORM1I64NVPROC glad_glProgramUniform1i64NV = NULL;
PFNGLPROGRAMUNIFORM1I64VNVPROC glad_glProgramUniform1i64vNV = NULL;
PFNGLPROGRAMUNIFORM1IEXTPROC glad_glProgramUniform1iEXT = NULL;
PFNGLPROGRAMUNIFORM1IVPROC glad_glProgramUniform1iv = NULL;
PFNGLPROGRAMUNIFORM1IVEXTPROC glad_glProgramUniform1ivEXT = NULL;
PFNGLPROGRAMUNIFORM1UIPROC glad_glProgramUniform1ui = NULL;
PFNGLPROGRAMUNIFORM1UI64NVPROC glad_glProgramUniform1ui64NV = NULL;
PFNGLPROGRAMUNIFORM1UI64VNVPROC glad_glProgramUniform1ui64vNV = NULL;
PFNGLPROGRAMUNIFORM1UIEXTPROC glad_glProgramUniform1uiEXT = NULL;
PFNGLPROGRAMUNIFORM1UIVPROC glad_glProgramUniform1uiv = NULL;
PFNGLPROGRAMUNIFORM1UIVEXTPROC glad_glProgramUniform1uivEXT = NULL;
PFNGLPROGRAMUNIFORM2FPROC glad_glProgramUniform2f = NULL;
PFNGLPROGRAMUNIFORM2FEXTPROC glad_glProgramUniform2fEXT = NULL;
PFNGLPROGRAMUNIFORM2FVPROC glad_glProgramUniform2fv = NULL;
PFNGLPROGRAMUNIFORM2FVEXTPROC glad_glProgramUniform2fvEXT = NULL;
PFNGLPROGRAMUNIFORM2IPROC glad_glProgramUniform2i = NULL;
PFNGLPROGRAMUNIFORM2I64NVPROC glad_glProgramUniform2i64NV = NULL;
PFNGLPROGRAMUNIFORM2I64VNVPROC glad_glProgramUniform2i64vNV = NULL;
PFNGLPROGRAMUNIFORM2IEXTPROC glad_glProgramUniform2iEXT = NULL;
PFNGLPROGRAMUNIFORM2IVPROC glad_glProgramUniform2iv = NULL;
PFNGLPROGRAMUNIFORM2IVEXTPROC glad_glProgramUniform2ivEXT = NULL;
PFNGLPROGRAMUNIFORM2UIPROC glad_glProgramUniform2ui = NULL;
PFNGLPROGRAMUNIFORM2UI64NVPROC glad_glProgramUniform2ui64NV = NULL;
PFNGLPROGRAMUNIFORM2UI64VNVPROC glad_glProgramUniform2ui64vNV = NULL;
PFNGLPROGRAMUNIFORM2UIEXTPROC glad_glProgramUniform2uiEXT = NULL;
PFNGLPROGRAMUNIFORM2UIVPROC glad_glProgramUniform2uiv = NULL;
PFNGLPROGRAMUNIFORM2UIVEXTPROC glad_glProgramUniform2uivEXT = NULL;
PFNGLPROGRAMUNIFORM3FPROC glad_glProgramUniform3f = NULL;
PFNGLPROGRAMUNIFORM3FEXTPROC glad_glProgramUniform3fEXT = NULL;
PFNGLPROGRAMUNIFORM3FVPROC glad_glProgramUniform3fv = NULL;
PFNGLPROGRAMUNIFORM3FVEXTPROC glad_glProgramUniform3fvEXT = NULL;
PFNGLPROGRAMUNIFORM3IPROC glad_glProgramUniform3i = NULL;
PFNGLPROGRAMUNIFORM3I64NVPROC glad_glProgramUniform3i64NV = NULL;
PFNGLPROGRAMUNIFORM3I64VNVPROC glad_glProgramUniform3i64vNV = NULL;
PFNGLPROGRAMUNIFORM3IEXTPROC glad_glProgramUniform3iEXT = NULL;
PFNGLPROGRAMUNIFORM3IVPROC glad_glProgramUniform3iv = NULL;
PFNGLPROGRAMUNIFORM3IVEXTPROC glad_glProgramUniform3ivEXT = NULL;
PFNGLPROGRAMUNIFORM3UIPROC glad_glProgramUniform3ui = NULL;
PFNGLPROGRAMUNIFORM3UI64NVPROC glad_glProgramUniform3ui64NV = NULL;
PFNGLPROGRAMUNIFORM3UI64VNVPROC glad_glProgramUniform3ui64vNV = NULL;
PFNGLPROGRAMUNIFORM3UIEXTPROC glad_glProgramUniform3uiEXT = NULL;
PFNGLPROGRAMUNIFORM3UIVPROC glad_glProgramUniform3uiv = NULL;
PFNGLPROGRAMUNIFORM3UIVEXTPROC glad_glProgramUniform3uivEXT = NULL;
PFNGLPROGRAMUNIFORM4FPROC glad_glProgramUniform4f = NULL;
PFNGLPROGRAMUNIFORM4FEXTPROC glad_glProgramUniform4fEXT = NULL;
PFNGLPROGRAMUNIFORM4FVPROC glad_glProgramUniform4fv = NULL;
PFNGLPROGRAMUNIFORM4FVEXTPROC glad_glProgramUniform4fvEXT = NULL;
PFNGLPROGRAMUNIFORM4IPROC glad_glProgramUniform4i = NULL;
PFNGLPROGRAMUNIFORM4I64NVPROC glad_glProgramUniform4i64NV = NULL;
PFNGLPROGRAMUNIFORM4I64VNVPROC glad_glProgramUniform4i64vNV = NULL;
PFNGLPROGRAMUNIFORM4IEXTPROC glad_glProgramUniform4iEXT = NULL;
PFNGLPROGRAMUNIFORM4IVPROC glad_glProgramUniform4iv = NULL;
PFNGLPROGRAMUNIFORM4IVEXTPROC glad_glProgramUniform4ivEXT = NULL;
PFNGLPROGRAMUNIFORM4UIPROC glad_glProgramUniform4ui = NULL;
PFNGLPROGRAMUNIFORM4UI64NVPROC glad_glProgramUniform4ui64NV = NULL;
PFNGLPROGRAMUNIFORM4UI64VNVPROC glad_glProgramUniform4ui64vNV = NULL;
PFNGLPROGRAMUNIFORM4UIEXTPROC glad_glProgramUniform4uiEXT = NULL;
PFNGLPROGRAMUNIFORM4UIVPROC glad_glProgramUniform4uiv = NULL;
PFNGLPROGRAMUNIFORM4UIVEXTPROC glad_glProgramUniform4uivEXT = NULL;
PFNGLPROGRAMUNIFORMHANDLEUI64IMGPROC glad_glProgramUniformHandleui64IMG = NULL;
PFNGLPROGRAMUNIFORMHANDLEUI64NVPROC glad_glProgramUniformHandleui64NV = NULL;
PFNGLPROGRAMUNIFORMHANDLEUI64VIMGPROC glad_glProgramUniformHandleui64vIMG = NULL;
PFNGLPROGRAMUNIFORMHANDLEUI64VNVPROC glad_glProgramUniformHandleui64vNV = NULL;
PFNGLPROGRAMUNIFORMMATRIX2FVPROC glad_glProgramUniformMatrix2fv = NULL;
PFNGLPROGRAMUNIFORMMATRIX2FVEXTPROC glad_glProgramUniformMatrix2fvEXT = NULL;
PFNGLPROGRAMUNIFORMMATRIX2X3FVPROC glad_glProgramUniformMatrix2x3fv = NULL;
PFNGLPROGRAMUNIFORMMATRIX2X3FVEXTPROC glad_glProgramUniformMatrix2x3fvEXT = NULL;
PFNGLPROGRAMUNIFORMMATRIX2X4FVPROC glad_glProgramUniformMatrix2x4fv = NULL;
PFNGLPROGRAMUNIFORMMATRIX2X4FVEXTPROC glad_glProgramUniformMatrix2x4fvEXT = NULL;
PFNGLPROGRAMUNIFORMMATRIX3FVPROC glad_glProgramUniformMatrix3fv = NULL;
PFNGLPROGRAMUNIFORMMATRIX3FVEXTPROC glad_glProgramUniformMatrix3fvEXT = NULL;
PFNGLPROGRAMUNIFORMMATRIX3X2FVPROC glad_glProgramUniformMatrix3x2fv = NULL;
PFNGLPROGRAMUNIFORMMATRIX3X2FVEXTPROC glad_glProgramUniformMatrix3x2fvEXT = NULL;
PFNGLPROGRAMUNIFORMMATRIX3X4FVPROC glad_glProgramUniformMatrix3x4fv = NULL;
PFNGLPROGRAMUNIFORMMATRIX3X4FVEXTPROC glad_glProgramUniformMatrix3x4fvEXT = NULL;
PFNGLPROGRAMUNIFORMMATRIX4FVPROC glad_glProgramUniformMatrix4fv = NULL;
PFNGLPROGRAMUNIFORMMATRIX4FVEXTPROC glad_glProgramUniformMatrix4fvEXT = NULL;
PFNGLPROGRAMUNIFORMMATRIX4X2FVPROC glad_glProgramUniformMatrix4x2fv = NULL;
PFNGLPROGRAMUNIFORMMATRIX4X2FVEXTPROC glad_glProgramUniformMatrix4x2fvEXT = NULL;
PFNGLPROGRAMUNIFORMMATRIX4X3FVPROC glad_glProgramUniformMatrix4x3fv = NULL;
PFNGLPROGRAMUNIFORMMATRIX4X3FVEXTPROC glad_glProgramUniformMatrix4x3fvEXT = NULL;
PFNGLPUSHDEBUGGROUPPROC glad_glPushDebugGroup = NULL;
PFNGLPUSHDEBUGGROUPKHRPROC glad_glPushDebugGroupKHR = NULL;
PFNGLPUSHGROUPMARKEREXTPROC glad_glPushGroupMarkerEXT = NULL;
PFNGLQUERYCOUNTEREXTPROC glad_glQueryCounterEXT = NULL;
PFNGLRASTERSAMPLESEXTPROC glad_glRasterSamplesEXT = NULL;
PFNGLREADBUFFERPROC glad_glReadBuffer = NULL;
PFNGLREADBUFFERINDEXEDEXTPROC glad_glReadBufferIndexedEXT = NULL;
PFNGLREADBUFFERNVPROC glad_glReadBufferNV = NULL;
PFNGLREADPIXELSPROC glad_glReadPixels = NULL;
PFNGLREADNPIXELSPROC glad_glReadnPixels = NULL;
PFNGLREADNPIXELSEXTPROC glad_glReadnPixelsEXT = NULL;
PFNGLREADNPIXELSKHRPROC glad_glReadnPixelsKHR = NULL;
PFNGLRELEASEKEYEDMUTEXWIN32EXTPROC glad_glReleaseKeyedMutexWin32EXT = NULL;
PFNGLRELEASESHADERCOMPILERPROC glad_glReleaseShaderCompiler = NULL;
PFNGLRENDERBUFFERSTORAGEPROC glad_glRenderbufferStorage = NULL;
PFNGLRENDERBUFFERSTORAGEMULTISAMPLEPROC glad_glRenderbufferStorageMultisample = NULL;
PFNGLRENDERBUFFERSTORAGEMULTISAMPLEANGLEPROC glad_glRenderbufferStorageMultisampleANGLE = NULL;
PFNGLRENDERBUFFERSTORAGEMULTISAMPLEAPPLEPROC glad_glRenderbufferStorageMultisampleAPPLE = NULL;
PFNGLRENDERBUFFERSTORAGEMULTISAMPLEADVANCEDAMDPROC glad_glRenderbufferStorageMultisampleAdvancedAMD = NULL;
PFNGLRENDERBUFFERSTORAGEMULTISAMPLEEXTPROC glad_glRenderbufferStorageMultisampleEXT = NULL;
PFNGLRENDERBUFFERSTORAGEMULTISAMPLEIMGPROC glad_glRenderbufferStorageMultisampleIMG = NULL;
PFNGLRENDERBUFFERSTORAGEMULTISAMPLENVPROC glad_glRenderbufferStorageMultisampleNV = NULL;
PFNGLRESETMEMORYOBJECTPARAMETERNVPROC glad_glResetMemoryObjectParameterNV = NULL;
PFNGLRESOLVEDEPTHVALUESNVPROC glad_glResolveDepthValuesNV = NULL;
PFNGLRESOLVEMULTISAMPLEFRAMEBUFFERAPPLEPROC glad_glResolveMultisampleFramebufferAPPLE = NULL;
PFNGLRESUMETRANSFORMFEEDBACKPROC glad_glResumeTransformFeedback = NULL;
PFNGLSAMPLECOVERAGEPROC glad_glSampleCoverage = NULL;
PFNGLSAMPLEMASKIPROC glad_glSampleMaski = NULL;
PFNGLSAMPLERPARAMETERIIVPROC glad_glSamplerParameterIiv = NULL;
PFNGLSAMPLERPARAMETERIIVEXTPROC glad_glSamplerParameterIivEXT = NULL;
PFNGLSAMPLERPARAMETERIIVOESPROC glad_glSamplerParameterIivOES = NULL;
PFNGLSAMPLERPARAMETERIUIVPROC glad_glSamplerParameterIuiv = NULL;
PFNGLSAMPLERPARAMETERIUIVEXTPROC glad_glSamplerParameterIuivEXT = NULL;
PFNGLSAMPLERPARAMETERIUIVOESPROC glad_glSamplerParameterIuivOES = NULL;
PFNGLSAMPLERPARAMETERFPROC glad_glSamplerParameterf = NULL;
PFNGLSAMPLERPARAMETERFVPROC glad_glSamplerParameterfv = NULL;
PFNGLSAMPLERPARAMETERIPROC glad_glSamplerParameteri = NULL;
PFNGLSAMPLERPARAMETERIVPROC glad_glSamplerParameteriv = NULL;
PFNGLSCISSORPROC glad_glScissor = NULL;
PFNGLSCISSORARRAYVNVPROC glad_glScissorArrayvNV = NULL;
PFNGLSCISSORARRAYVOESPROC glad_glScissorArrayvOES = NULL;
PFNGLSCISSOREXCLUSIVEARRAYVNVPROC glad_glScissorExclusiveArrayvNV = NULL;
PFNGLSCISSOREXCLUSIVENVPROC glad_glScissorExclusiveNV = NULL;
PFNGLSCISSORINDEXEDNVPROC glad_glScissorIndexedNV = NULL;
PFNGLSCISSORINDEXEDOESPROC glad_glScissorIndexedOES = NULL;
PFNGLSCISSORINDEXEDVNVPROC glad_glScissorIndexedvNV = NULL;
PFNGLSCISSORINDEXEDVOESPROC glad_glScissorIndexedvOES = NULL;
PFNGLSELECTPERFMONITORCOUNTERSAMDPROC glad_glSelectPerfMonitorCountersAMD = NULL;
PFNGLSEMAPHOREPARAMETERIVNVPROC glad_glSemaphoreParameterivNV = NULL;
PFNGLSEMAPHOREPARAMETERUI64VEXTPROC glad_glSemaphoreParameterui64vEXT = NULL;
PFNGLSETFENCENVPROC glad_glSetFenceNV = NULL;
PFNGLSHADERBINARYPROC glad_glShaderBinary = NULL;
PFNGLSHADERSOURCEPROC glad_glShaderSource = NULL;
PFNGLSHADINGRATECOMBINEROPSEXTPROC glad_glShadingRateCombinerOpsEXT = NULL;
PFNGLSHADINGRATEEXTPROC glad_glShadingRateEXT = NULL;
PFNGLSHADINGRATEIMAGEBARRIERNVPROC glad_glShadingRateImageBarrierNV = NULL;
PFNGLSHADINGRATEIMAGEPALETTENVPROC glad_glShadingRateImagePaletteNV = NULL;
PFNGLSHADINGRATEQCOMPROC glad_glShadingRateQCOM = NULL;
PFNGLSHADINGRATESAMPLEORDERCUSTOMNVPROC glad_glShadingRateSampleOrderCustomNV = NULL;
PFNGLSHADINGRATESAMPLEORDERNVPROC glad_glShadingRateSampleOrderNV = NULL;
PFNGLSIGNALSEMAPHOREEXTPROC glad_glSignalSemaphoreEXT = NULL;
PFNGLSIGNALVKFENCENVPROC glad_glSignalVkFenceNV = NULL;
PFNGLSIGNALVKSEMAPHORENVPROC glad_glSignalVkSemaphoreNV = NULL;
PFNGLSTARTTILINGQCOMPROC glad_glStartTilingQCOM = NULL;
PFNGLSTENCILFILLPATHINSTANCEDNVPROC glad_glStencilFillPathInstancedNV = NULL;
PFNGLSTENCILFILLPATHNVPROC glad_glStencilFillPathNV = NULL;
PFNGLSTENCILFUNCPROC glad_glStencilFunc = NULL;
PFNGLSTENCILFUNCSEPARATEPROC glad_glStencilFuncSeparate = NULL;
PFNGLSTENCILMASKPROC glad_glStencilMask = NULL;
PFNGLSTENCILMASKSEPARATEPROC glad_glStencilMaskSeparate = NULL;
PFNGLSTENCILOPPROC glad_glStencilOp = NULL;
PFNGLSTENCILOPSEPARATEPROC glad_glStencilOpSeparate = NULL;
PFNGLSTENCILSTROKEPATHINSTANCEDNVPROC glad_glStencilStrokePathInstancedNV = NULL;
PFNGLSTENCILSTROKEPATHNVPROC glad_glStencilStrokePathNV = NULL;
PFNGLSTENCILTHENCOVERFILLPATHINSTANCEDNVPROC glad_glStencilThenCoverFillPathInstancedNV = NULL;
PFNGLSTENCILTHENCOVERFILLPATHNVPROC glad_glStencilThenCoverFillPathNV = NULL;
PFNGLSTENCILTHENCOVERSTROKEPATHINSTANCEDNVPROC glad_glStencilThenCoverStrokePathInstancedNV = NULL;
PFNGLSTENCILTHENCOVERSTROKEPATHNVPROC glad_glStencilThenCoverStrokePathNV = NULL;
PFNGLSUBPIXELPRECISIONBIASNVPROC glad_glSubpixelPrecisionBiasNV = NULL;
PFNGLTESTFENCENVPROC glad_glTestFenceNV = NULL;
PFNGLTEXATTACHMEMORYNVPROC glad_glTexAttachMemoryNV = NULL;
PFNGLTEXBUFFERPROC glad_glTexBuffer = NULL;
PFNGLTEXBUFFEREXTPROC glad_glTexBufferEXT = NULL;
PFNGLTEXBUFFEROESPROC glad_glTexBufferOES = NULL;
PFNGLTEXBUFFERRANGEPROC glad_glTexBufferRange = NULL;
PFNGLTEXBUFFERRANGEEXTPROC glad_glTexBufferRangeEXT = NULL;
PFNGLTEXBUFFERRANGEOESPROC glad_glTexBufferRangeOES = NULL;
PFNGLTEXESTIMATEMOTIONQCOMPROC glad_glTexEstimateMotionQCOM = NULL;
PFNGLTEXESTIMATEMOTIONREGIONSQCOMPROC glad_glTexEstimateMotionRegionsQCOM = NULL;
PFNGLTEXIMAGE2DPROC glad_glTexImage2D = NULL;
PFNGLTEXIMAGE3DPROC glad_glTexImage3D = NULL;
PFNGLTEXIMAGE3DOESPROC glad_glTexImage3DOES = NULL;
PFNGLTEXPAGECOMMITMENTEXTPROC glad_glTexPageCommitmentEXT = NULL;
PFNGLTEXPAGECOMMITMENTMEMNVPROC glad_glTexPageCommitmentMemNV = NULL;
PFNGLTEXPARAMETERIIVPROC glad_glTexParameterIiv = NULL;
PFNGLTEXPARAMETERIIVEXTPROC glad_glTexParameterIivEXT = NULL;
PFNGLTEXPARAMETERIIVOESPROC glad_glTexParameterIivOES = NULL;
PFNGLTEXPARAMETERIUIVPROC glad_glTexParameterIuiv = NULL;
PFNGLTEXPARAMETERIUIVEXTPROC glad_glTexParameterIuivEXT = NULL;
PFNGLTEXPARAMETERIUIVOESPROC glad_glTexParameterIuivOES = NULL;
PFNGLTEXPARAMETERFPROC glad_glTexParameterf = NULL;
PFNGLTEXPARAMETERFVPROC glad_glTexParameterfv = NULL;
PFNGLTEXPARAMETERIPROC glad_glTexParameteri = NULL;
PFNGLTEXPARAMETERIVPROC glad_glTexParameteriv = NULL;
PFNGLTEXSTORAGE1DEXTPROC glad_glTexStorage1DEXT = NULL;
PFNGLTEXSTORAGE2DPROC glad_glTexStorage2D = NULL;
PFNGLTEXSTORAGE2DEXTPROC glad_glTexStorage2DEXT = NULL;
PFNGLTEXSTORAGE2DMULTISAMPLEPROC glad_glTexStorage2DMultisample = NULL;
PFNGLTEXSTORAGE3DPROC glad_glTexStorage3D = NULL;
PFNGLTEXSTORAGE3DEXTPROC glad_glTexStorage3DEXT = NULL;
PFNGLTEXSTORAGE3DMULTISAMPLEPROC glad_glTexStorage3DMultisample = NULL;
PFNGLTEXSTORAGE3DMULTISAMPLEOESPROC glad_glTexStorage3DMultisampleOES = NULL;
PFNGLTEXSTORAGEATTRIBS2DEXTPROC glad_glTexStorageAttribs2DEXT = NULL;
PFNGLTEXSTORAGEATTRIBS3DEXTPROC glad_glTexStorageAttribs3DEXT = NULL;
PFNGLTEXSTORAGEMEM2DEXTPROC glad_glTexStorageMem2DEXT = NULL;
PFNGLTEXSTORAGEMEM2DMULTISAMPLEEXTPROC glad_glTexStorageMem2DMultisampleEXT = NULL;
PFNGLTEXSTORAGEMEM3DEXTPROC glad_glTexStorageMem3DEXT = NULL;
PFNGLTEXSTORAGEMEM3DMULTISAMPLEEXTPROC glad_glTexStorageMem3DMultisampleEXT = NULL;
PFNGLTEXSUBIMAGE2DPROC glad_glTexSubImage2D = NULL;
PFNGLTEXSUBIMAGE3DPROC glad_glTexSubImage3D = NULL;
PFNGLTEXSUBIMAGE3DOESPROC glad_glTexSubImage3DOES = NULL;
PFNGLTEXTUREATTACHMEMORYNVPROC glad_glTextureAttachMemoryNV = NULL;
PFNGLTEXTUREFOVEATIONPARAMETERSQCOMPROC glad_glTextureFoveationParametersQCOM = NULL;
PFNGLTEXTUREPAGECOMMITMENTMEMNVPROC glad_glTexturePageCommitmentMemNV = NULL;
PFNGLTEXTURESTORAGE1DEXTPROC glad_glTextureStorage1DEXT = NULL;
PFNGLTEXTURESTORAGE2DEXTPROC glad_glTextureStorage2DEXT = NULL;
PFNGLTEXTURESTORAGE3DEXTPROC glad_glTextureStorage3DEXT = NULL;
PFNGLTEXTURESTORAGEMEM2DEXTPROC glad_glTextureStorageMem2DEXT = NULL;
PFNGLTEXTURESTORAGEMEM2DMULTISAMPLEEXTPROC glad_glTextureStorageMem2DMultisampleEXT = NULL;
PFNGLTEXTURESTORAGEMEM3DEXTPROC glad_glTextureStorageMem3DEXT = NULL;
PFNGLTEXTURESTORAGEMEM3DMULTISAMPLEEXTPROC glad_glTextureStorageMem3DMultisampleEXT = NULL;
PFNGLTEXTUREVIEWEXTPROC glad_glTextureViewEXT = NULL;
PFNGLTEXTUREVIEWOESPROC glad_glTextureViewOES = NULL;
PFNGLTRANSFORMFEEDBACKVARYINGSPROC glad_glTransformFeedbackVaryings = NULL;
PFNGLTRANSFORMPATHNVPROC glad_glTransformPathNV = NULL;
PFNGLUNIFORM1FPROC glad_glUniform1f = NULL;
PFNGLUNIFORM1FVPROC glad_glUniform1fv = NULL;
PFNGLUNIFORM1IPROC glad_glUniform1i = NULL;
PFNGLUNIFORM1I64NVPROC glad_glUniform1i64NV = NULL;
PFNGLUNIFORM1I64VNVPROC glad_glUniform1i64vNV = NULL;
PFNGLUNIFORM1IVPROC glad_glUniform1iv = NULL;
PFNGLUNIFORM1UIPROC glad_glUniform1ui = NULL;
PFNGLUNIFORM1UI64NVPROC glad_glUniform1ui64NV = NULL;
PFNGLUNIFORM1UI64VNVPROC glad_glUniform1ui64vNV = NULL;
PFNGLUNIFORM1UIVPROC glad_glUniform1uiv = NULL;
PFNGLUNIFORM2FPROC glad_glUniform2f = NULL;
PFNGLUNIFORM2FVPROC glad_glUniform2fv = NULL;
PFNGLUNIFORM2IPROC glad_glUniform2i = NULL;
PFNGLUNIFORM2I64NVPROC glad_glUniform2i64NV = NULL;
PFNGLUNIFORM2I64VNVPROC glad_glUniform2i64vNV = NULL;
PFNGLUNIFORM2IVPROC glad_glUniform2iv = NULL;
PFNGLUNIFORM2UIPROC glad_glUniform2ui = NULL;
PFNGLUNIFORM2UI64NVPROC glad_glUniform2ui64NV = NULL;
PFNGLUNIFORM2UI64VNVPROC glad_glUniform2ui64vNV = NULL;
PFNGLUNIFORM2UIVPROC glad_glUniform2uiv = NULL;
PFNGLUNIFORM3FPROC glad_glUniform3f = NULL;
PFNGLUNIFORM3FVPROC glad_glUniform3fv = NULL;
PFNGLUNIFORM3IPROC glad_glUniform3i = NULL;
PFNGLUNIFORM3I64NVPROC glad_glUniform3i64NV = NULL;
PFNGLUNIFORM3I64VNVPROC glad_glUniform3i64vNV = NULL;
PFNGLUNIFORM3IVPROC glad_glUniform3iv = NULL;
PFNGLUNIFORM3UIPROC glad_glUniform3ui = NULL;
PFNGLUNIFORM3UI64NVPROC glad_glUniform3ui64NV = NULL;
PFNGLUNIFORM3UI64VNVPROC glad_glUniform3ui64vNV = NULL;
PFNGLUNIFORM3UIVPROC glad_glUniform3uiv = NULL;
PFNGLUNIFORM4FPROC glad_glUniform4f = NULL;
PFNGLUNIFORM4FVPROC glad_glUniform4fv = NULL;
PFNGLUNIFORM4IPROC glad_glUniform4i = NULL;
PFNGLUNIFORM4I64NVPROC glad_glUniform4i64NV = NULL;
PFNGLUNIFORM4I64VNVPROC glad_glUniform4i64vNV = NULL;
PFNGLUNIFORM4IVPROC glad_glUniform4iv = NULL;
PFNGLUNIFORM4UIPROC glad_glUniform4ui = NULL;
PFNGLUNIFORM4UI64NVPROC glad_glUniform4ui64NV = NULL;
PFNGLUNIFORM4UI64VNVPROC glad_glUniform4ui64vNV = NULL;
PFNGLUNIFORM4UIVPROC glad_glUniform4uiv = NULL;
PFNGLUNIFORMBLOCKBINDINGPROC glad_glUniformBlockBinding = NULL;
PFNGLUNIFORMHANDLEUI64IMGPROC glad_glUniformHandleui64IMG = NULL;
PFNGLUNIFORMHANDLEUI64NVPROC glad_glUniformHandleui64NV = NULL;
PFNGLUNIFORMHANDLEUI64VIMGPROC glad_glUniformHandleui64vIMG = NULL;
PFNGLUNIFORMHANDLEUI64VNVPROC glad_glUniformHandleui64vNV = NULL;
PFNGLUNIFORMMATRIX2FVPROC glad_glUniformMatrix2fv = NULL;
PFNGLUNIFORMMATRIX2X3FVPROC glad_glUniformMatrix2x3fv = NULL;
PFNGLUNIFORMMATRIX2X3FVNVPROC glad_glUniformMatrix2x3fvNV = NULL;
PFNGLUNIFORMMATRIX2X4FVPROC glad_glUniformMatrix2x4fv = NULL;
PFNGLUNIFORMMATRIX2X4FVNVPROC glad_glUniformMatrix2x4fvNV = NULL;
PFNGLUNIFORMMATRIX3FVPROC glad_glUniformMatrix3fv = NULL;
PFNGLUNIFORMMATRIX3X2FVPROC glad_glUniformMatrix3x2fv = NULL;
PFNGLUNIFORMMATRIX3X2FVNVPROC glad_glUniformMatrix3x2fvNV = NULL;
PFNGLUNIFORMMATRIX3X4FVPROC glad_glUniformMatrix3x4fv = NULL;
PFNGLUNIFORMMATRIX3X4FVNVPROC glad_glUniformMatrix3x4fvNV = NULL;
PFNGLUNIFORMMATRIX4FVPROC glad_glUniformMatrix4fv = NULL;
PFNGLUNIFORMMATRIX4X2FVPROC glad_glUniformMatrix4x2fv = NULL;
PFNGLUNIFORMMATRIX4X2FVNVPROC glad_glUniformMatrix4x2fvNV = NULL;
PFNGLUNIFORMMATRIX4X3FVPROC glad_glUniformMatrix4x3fv = NULL;
PFNGLUNIFORMMATRIX4X3FVNVPROC glad_glUniformMatrix4x3fvNV = NULL;
PFNGLUNMAPBUFFERPROC glad_glUnmapBuffer = NULL;
PFNGLUNMAPBUFFEROESPROC glad_glUnmapBufferOES = NULL;
PFNGLUSEPROGRAMPROC glad_glUseProgram = NULL;
PFNGLUSEPROGRAMSTAGESPROC glad_glUseProgramStages = NULL;
PFNGLUSEPROGRAMSTAGESEXTPROC glad_glUseProgramStagesEXT = NULL;
PFNGLVALIDATEPROGRAMPROC glad_glValidateProgram = NULL;
PFNGLVALIDATEPROGRAMPIPELINEPROC glad_glValidateProgramPipeline = NULL;
PFNGLVALIDATEPROGRAMPIPELINEEXTPROC glad_glValidateProgramPipelineEXT = NULL;
PFNGLVERTEXATTRIB1FPROC glad_glVertexAttrib1f = NULL;
PFNGLVERTEXATTRIB1FVPROC glad_glVertexAttrib1fv = NULL;
PFNGLVERTEXATTRIB2FPROC glad_glVertexAttrib2f = NULL;
PFNGLVERTEXATTRIB2FVPROC glad_glVertexAttrib2fv = NULL;
PFNGLVERTEXATTRIB3FPROC glad_glVertexAttrib3f = NULL;
PFNGLVERTEXATTRIB3FVPROC glad_glVertexAttrib3fv = NULL;
PFNGLVERTEXATTRIB4FPROC glad_glVertexAttrib4f = NULL;
PFNGLVERTEXATTRIB4FVPROC glad_glVertexAttrib4fv = NULL;
PFNGLVERTEXATTRIBBINDINGPROC glad_glVertexAttribBinding = NULL;
PFNGLVERTEXATTRIBDIVISORPROC glad_glVertexAttribDivisor = NULL;
PFNGLVERTEXATTRIBDIVISORANGLEPROC glad_glVertexAttribDivisorANGLE = NULL;
PFNGLVERTEXATTRIBDIVISOREXTPROC glad_glVertexAttribDivisorEXT = NULL;
PFNGLVERTEXATTRIBDIVISORNVPROC glad_glVertexAttribDivisorNV = NULL;
PFNGLVERTEXATTRIBFORMATPROC glad_glVertexAttribFormat = NULL;
PFNGLVERTEXATTRIBI4IPROC glad_glVertexAttribI4i = NULL;
PFNGLVERTEXATTRIBI4IVPROC glad_glVertexAttribI4iv = NULL;
PFNGLVERTEXATTRIBI4UIPROC glad_glVertexAttribI4ui = NULL;
PFNGLVERTEXATTRIBI4UIVPROC glad_glVertexAttribI4uiv = NULL;
PFNGLVERTEXATTRIBIFORMATPROC glad_glVertexAttribIFormat = NULL;
PFNGLVERTEXATTRIBIPOINTERPROC glad_glVertexAttribIPointer = NULL;
PFNGLVERTEXATTRIBPOINTERPROC glad_glVertexAttribPointer = NULL;
PFNGLVERTEXBINDINGDIVISORPROC glad_glVertexBindingDivisor = NULL;
PFNGLVIEWPORTPROC glad_glViewport = NULL;
PFNGLVIEWPORTARRAYVNVPROC glad_glViewportArrayvNV = NULL;
PFNGLVIEWPORTARRAYVOESPROC glad_glViewportArrayvOES = NULL;
PFNGLVIEWPORTINDEXEDFNVPROC glad_glViewportIndexedfNV = NULL;
PFNGLVIEWPORTINDEXEDFOESPROC glad_glViewportIndexedfOES = NULL;
PFNGLVIEWPORTINDEXEDFVNVPROC glad_glViewportIndexedfvNV = NULL;
PFNGLVIEWPORTINDEXEDFVOESPROC glad_glViewportIndexedfvOES = NULL;
PFNGLVIEWPORTPOSITIONWSCALENVPROC glad_glViewportPositionWScaleNV = NULL;
PFNGLVIEWPORTSWIZZLENVPROC glad_glViewportSwizzleNV = NULL;
PFNGLWAITSEMAPHOREEXTPROC glad_glWaitSemaphoreEXT = NULL;
PFNGLWAITSYNCPROC glad_glWaitSync = NULL;
PFNGLWAITSYNCAPPLEPROC glad_glWaitSyncAPPLE = NULL;
PFNGLWAITVKSEMAPHORENVPROC glad_glWaitVkSemaphoreNV = NULL;
PFNGLWEIGHTPATHSNVPROC glad_glWeightPathsNV = NULL;
PFNGLWINDOWRECTANGLESEXTPROC glad_glWindowRectanglesEXT = NULL;


static void glad_gl_load_GL_ES_VERSION_2_0( GLADuserptrloadfunc load, void* userptr) {
    if(!GLAD_GL_ES_VERSION_2_0) return;
    glad_glActiveTexture = (PFNGLACTIVETEXTUREPROC) load(userptr, "glActiveTexture");
    glad_glAttachShader = (PFNGLATTACHSHADERPROC) load(userptr, "glAttachShader");
    glad_glBindAttribLocation = (PFNGLBINDATTRIBLOCATIONPROC) load(userptr, "glBindAttribLocation");
    glad_glBindBuffer = (PFNGLBINDBUFFERPROC) load(userptr, "glBindBuffer");
    glad_glBindFramebuffer = (PFNGLBINDFRAMEBUFFERPROC) load(userptr, "glBindFramebuffer");
    glad_glBindRenderbuffer = (PFNGLBINDRENDERBUFFERPROC) load(userptr, "glBindRenderbuffer");
    glad_glBindTexture = (PFNGLBINDTEXTUREPROC) load(userptr, "glBindTexture");
    glad_glBlendColor = (PFNGLBLENDCOLORPROC) load(userptr, "glBlendColor");
    glad_glBlendEquation = (PFNGLBLENDEQUATIONPROC) load(userptr, "glBlendEquation");
    glad_glBlendEquationSeparate = (PFNGLBLENDEQUATIONSEPARATEPROC) load(userptr, "glBlendEquationSeparate");
    glad_glBlendFunc = (PFNGLBLENDFUNCPROC) load(userptr, "glBlendFunc");
    glad_glBlendFuncSeparate = (PFNGLBLENDFUNCSEPARATEPROC) load(userptr, "glBlendFuncSeparate");
    glad_glBufferData = (PFNGLBUFFERDATAPROC) load(userptr, "glBufferData");
    glad_glBufferSubData = (PFNGLBUFFERSUBDATAPROC) load(userptr, "glBufferSubData");
    glad_glCheckFramebufferStatus = (PFNGLCHECKFRAMEBUFFERSTATUSPROC) load(userptr, "glCheckFramebufferStatus");
    glad_glClear = (PFNGLCLEARPROC) load(userptr, "glClear");
    glad_glClearColor = (PFNGLCLEARCOLORPROC) load(userptr, "glClearColor");
    glad_glClearDepthf = (PFNGLCLEARDEPTHFPROC) load(userptr, "glClearDepthf");
    glad_glClearStencil = (PFNGLCLEARSTENCILPROC) load(userptr, "glClearStencil");
    glad_glColorMask = (PFNGLCOLORMASKPROC) load(userptr, "glColorMask");
    glad_glCompileShader = (PFNGLCOMPILESHADERPROC) load(userptr, "glCompileShader");
    glad_glCompressedTexImage2D = (PFNGLCOMPRESSEDTEXIMAGE2DPROC) load(userptr, "glCompressedTexImage2D");
    glad_glCompressedTexSubImage2D = (PFNGLCOMPRESSEDTEXSUBIMAGE2DPROC) load(userptr, "glCompressedTexSubImage2D");
    glad_glCopyTexImage2D = (PFNGLCOPYTEXIMAGE2DPROC) load(userptr, "glCopyTexImage2D");
    glad_glCopyTexSubImage2D = (PFNGLCOPYTEXSUBIMAGE2DPROC) load(userptr, "glCopyTexSubImage2D");
    glad_glCreateProgram = (PFNGLCREATEPROGRAMPROC) load(userptr, "glCreateProgram");
    glad_glCreateShader = (PFNGLCREATESHADERPROC) load(userptr, "glCreateShader");
    glad_glCullFace = (PFNGLCULLFACEPROC) load(userptr, "glCullFace");
    glad_glDeleteBuffers = (PFNGLDELETEBUFFERSPROC) load(userptr, "glDeleteBuffers");
    glad_glDeleteFramebuffers = (PFNGLDELETEFRAMEBUFFERSPROC) load(userptr, "glDeleteFramebuffers");
    glad_glDeleteProgram = (PFNGLDELETEPROGRAMPROC) load(userptr, "glDeleteProgram");
    glad_glDeleteRenderbuffers = (PFNGLDELETERENDERBUFFERSPROC) load(userptr, "glDeleteRenderbuffers");
    glad_glDeleteShader = (PFNGLDELETESHADERPROC) load(userptr, "glDeleteShader");
    glad_glDeleteTextures = (PFNGLDELETETEXTURESPROC) load(userptr, "glDeleteTextures");
    glad_glDepthFunc = (PFNGLDEPTHFUNCPROC) load(userptr, "glDepthFunc");
    glad_glDepthMask = (PFNGLDEPTHMASKPROC) load(userptr, "glDepthMask");
    glad_glDepthRangef = (PFNGLDEPTHRANGEFPROC) load(userptr, "glDepthRangef");
    glad_glDetachShader = (PFNGLDETACHSHADERPROC) load(userptr, "glDetachShader");
    glad_glDisable = (PFNGLDISABLEPROC) load(userptr, "glDisable");
    glad_glDisableVertexAttribArray = (PFNGLDISABLEVERTEXATTRIBARRAYPROC) load(userptr, "glDisableVertexAttribArray");
    glad_glDrawArrays = (PFNGLDRAWARRAYSPROC) load(userptr, "glDrawArrays");
    glad_glDrawElements = (PFNGLDRAWELEMENTSPROC) load(userptr, "glDrawElements");
    glad_glEnable = (PFNGLENABLEPROC) load(userptr, "glEnable");
    glad_glEnableVertexAttribArray = (PFNGLENABLEVERTEXATTRIBARRAYPROC) load(userptr, "glEnableVertexAttribArray");
    glad_glFinish = (PFNGLFINISHPROC) load(userptr, "glFinish");
    glad_glFlush = (PFNGLFLUSHPROC) load(userptr, "glFlush");
    glad_glFramebufferRenderbuffer = (PFNGLFRAMEBUFFERRENDERBUFFERPROC) load(userptr, "glFramebufferRenderbuffer");
    glad_glFramebufferTexture2D = (PFNGLFRAMEBUFFERTEXTURE2DPROC) load(userptr, "glFramebufferTexture2D");
    glad_glFrontFace = (PFNGLFRONTFACEPROC) load(userptr, "glFrontFace");
    glad_glGenBuffers = (PFNGLGENBUFFERSPROC) load(userptr, "glGenBuffers");
    glad_glGenFramebuffers = (PFNGLGENFRAMEBUFFERSPROC) load(userptr, "glGenFramebuffers");
    glad_glGenRenderbuffers = (PFNGLGENRENDERBUFFERSPROC) load(userptr, "glGenRenderbuffers");
    glad_glGenTextures = (PFNGLGENTEXTURESPROC) load(userptr, "glGenTextures");
    glad_glGenerateMipmap = (PFNGLGENERATEMIPMAPPROC) load(userptr, "glGenerateMipmap");
    glad_glGetActiveAttrib = (PFNGLGETACTIVEATTRIBPROC) load(userptr, "glGetActiveAttrib");
    glad_glGetActiveUniform = (PFNGLGETACTIVEUNIFORMPROC) load(userptr, "glGetActiveUniform");
    glad_glGetAttachedShaders = (PFNGLGETATTACHEDSHADERSPROC) load(userptr, "glGetAttachedShaders");
    glad_glGetAttribLocation = (PFNGLGETATTRIBLOCATIONPROC) load(userptr, "glGetAttribLocation");
    glad_glGetBooleanv = (PFNGLGETBOOLEANVPROC) load(userptr, "glGetBooleanv");
    glad_glGetBufferParameteriv = (PFNGLGETBUFFERPARAMETERIVPROC) load(userptr, "glGetBufferParameteriv");
    glad_glGetError = (PFNGLGETERRORPROC) load(userptr, "glGetError");
    glad_glGetFloatv = (PFNGLGETFLOATVPROC) load(userptr, "glGetFloatv");
    glad_glGetFramebufferAttachmentParameteriv = (PFNGLGETFRAMEBUFFERATTACHMENTPARAMETERIVPROC) load(userptr, "glGetFramebufferAttachmentParameteriv");
    glad_glGetIntegerv = (PFNGLGETINTEGERVPROC) load(userptr, "glGetIntegerv");
    glad_glGetProgramInfoLog = (PFNGLGETPROGRAMINFOLOGPROC) load(userptr, "glGetProgramInfoLog");
    glad_glGetProgramiv = (PFNGLGETPROGRAMIVPROC) load(userptr, "glGetProgramiv");
    glad_glGetRenderbufferParameteriv = (PFNGLGETRENDERBUFFERPARAMETERIVPROC) load(userptr, "glGetRenderbufferParameteriv");
    glad_glGetShaderInfoLog = (PFNGLGETSHADERINFOLOGPROC) load(userptr, "glGetShaderInfoLog");
    glad_glGetShaderPrecisionFormat = (PFNGLGETSHADERPRECISIONFORMATPROC) load(userptr, "glGetShaderPrecisionFormat");
    glad_glGetShaderSource = (PFNGLGETSHADERSOURCEPROC) load(userptr, "glGetShaderSource");
    glad_glGetShaderiv = (PFNGLGETSHADERIVPROC) load(userptr, "glGetShaderiv");
    glad_glGetString = (PFNGLGETSTRINGPROC) load(userptr, "glGetString");
    glad_glGetTexParameterfv = (PFNGLGETTEXPARAMETERFVPROC) load(userptr, "glGetTexParameterfv");
    glad_glGetTexParameteriv = (PFNGLGETTEXPARAMETERIVPROC) load(userptr, "glGetTexParameteriv");
    glad_glGetUniformLocation = (PFNGLGETUNIFORMLOCATIONPROC) load(userptr, "glGetUniformLocation");
    glad_glGetUniformfv = (PFNGLGETUNIFORMFVPROC) load(userptr, "glGetUniformfv");
    glad_glGetUniformiv = (PFNGLGETUNIFORMIVPROC) load(userptr, "glGetUniformiv");
    glad_glGetVertexAttribPointerv = (PFNGLGETVERTEXATTRIBPOINTERVPROC) load(userptr, "glGetVertexAttribPointerv");
    glad_glGetVertexAttribfv = (PFNGLGETVERTEXATTRIBFVPROC) load(userptr, "glGetVertexAttribfv");
    glad_glGetVertexAttribiv = (PFNGLGETVERTEXATTRIBIVPROC) load(userptr, "glGetVertexAttribiv");
    glad_glHint = (PFNGLHINTPROC) load(userptr, "glHint");
    glad_glIsBuffer = (PFNGLISBUFFERPROC) load(userptr, "glIsBuffer");
    glad_glIsEnabled = (PFNGLISENABLEDPROC) load(userptr, "glIsEnabled");
    glad_glIsFramebuffer = (PFNGLISFRAMEBUFFERPROC) load(userptr, "glIsFramebuffer");
    glad_glIsProgram = (PFNGLISPROGRAMPROC) load(userptr, "glIsProgram");
    glad_glIsRenderbuffer = (PFNGLISRENDERBUFFERPROC) load(userptr, "glIsRenderbuffer");
    glad_glIsShader = (PFNGLISSHADERPROC) load(userptr, "glIsShader");
    glad_glIsTexture = (PFNGLISTEXTUREPROC) load(userptr, "glIsTexture");
    glad_glLineWidth = (PFNGLLINEWIDTHPROC) load(userptr, "glLineWidth");
    glad_glLinkProgram = (PFNGLLINKPROGRAMPROC) load(userptr, "glLinkProgram");
    glad_glPixelStorei = (PFNGLPIXELSTOREIPROC) load(userptr, "glPixelStorei");
    glad_glPolygonOffset = (PFNGLPOLYGONOFFSETPROC) load(userptr, "glPolygonOffset");
    glad_glReadPixels = (PFNGLREADPIXELSPROC) load(userptr, "glReadPixels");
    glad_glReleaseShaderCompiler = (PFNGLRELEASESHADERCOMPILERPROC) load(userptr, "glReleaseShaderCompiler");
    glad_glRenderbufferStorage = (PFNGLRENDERBUFFERSTORAGEPROC) load(userptr, "glRenderbufferStorage");
    glad_glSampleCoverage = (PFNGLSAMPLECOVERAGEPROC) load(userptr, "glSampleCoverage");
    glad_glScissor = (PFNGLSCISSORPROC) load(userptr, "glScissor");
    glad_glShaderBinary = (PFNGLSHADERBINARYPROC) load(userptr, "glShaderBinary");
    glad_glShaderSource = (PFNGLSHADERSOURCEPROC) load(userptr, "glShaderSource");
    glad_glStencilFunc = (PFNGLSTENCILFUNCPROC) load(userptr, "glStencilFunc");
    glad_glStencilFuncSeparate = (PFNGLSTENCILFUNCSEPARATEPROC) load(userptr, "glStencilFuncSeparate");
    glad_glStencilMask = (PFNGLSTENCILMASKPROC) load(userptr, "glStencilMask");
    glad_glStencilMaskSeparate = (PFNGLSTENCILMASKSEPARATEPROC) load(userptr, "glStencilMaskSeparate");
    glad_glStencilOp = (PFNGLSTENCILOPPROC) load(userptr, "glStencilOp");
    glad_glStencilOpSeparate = (PFNGLSTENCILOPSEPARATEPROC) load(userptr, "glStencilOpSeparate");
    glad_glTexImage2D = (PFNGLTEXIMAGE2DPROC) load(userptr, "glTexImage2D");
    glad_glTexParameterf = (PFNGLTEXPARAMETERFPROC) load(userptr, "glTexParameterf");
    glad_glTexParameterfv = (PFNGLTEXPARAMETERFVPROC) load(userptr, "glTexParameterfv");
    glad_glTexParameteri = (PFNGLTEXPARAMETERIPROC) load(userptr, "glTexParameteri");
    glad_glTexParameteriv = (PFNGLTEXPARAMETERIVPROC) load(userptr, "glTexParameteriv");
    glad_glTexSubImage2D = (PFNGLTEXSUBIMAGE2DPROC) load(userptr, "glTexSubImage2D");
    glad_glUniform1f = (PFNGLUNIFORM1FPROC) load(userptr, "glUniform1f");
    glad_glUniform1fv = (PFNGLUNIFORM1FVPROC) load(userptr, "glUniform1fv");
    glad_glUniform1i = (PFNGLUNIFORM1IPROC) load(userptr, "glUniform1i");
    glad_glUniform1iv = (PFNGLUNIFORM1IVPROC) load(userptr, "glUniform1iv");
    glad_glUniform2f = (PFNGLUNIFORM2FPROC) load(userptr, "glUniform2f");
    glad_glUniform2fv = (PFNGLUNIFORM2FVPROC) load(userptr, "glUniform2fv");
    glad_glUniform2i = (PFNGLUNIFORM2IPROC) load(userptr, "glUniform2i");
    glad_glUniform2iv = (PFNGLUNIFORM2IVPROC) load(userptr, "glUniform2iv");
    glad_glUniform3f = (PFNGLUNIFORM3FPROC) load(userptr, "glUniform3f");
    glad_glUniform3fv = (PFNGLUNIFORM3FVPROC) load(userptr, "glUniform3fv");
    glad_glUniform3i = (PFNGLUNIFORM3IPROC) load(userptr, "glUniform3i");
    glad_glUniform3iv = (PFNGLUNIFORM3IVPROC) load(userptr, "glUniform3iv");
    glad_glUniform4f = (PFNGLUNIFORM4FPROC) load(userptr, "glUniform4f");
    glad_glUniform4fv = (PFNGLUNIFORM4FVPROC) load(userptr, "glUniform4fv");
    glad_glUniform4i = (PFNGLUNIFORM4IPROC) load(userptr, "glUniform4i");
    glad_glUniform4iv = (PFNGLUNIFORM4IVPROC) load(userptr, "glUniform4iv");
    glad_glUniformMatrix2fv = (PFNGLUNIFORMMATRIX2FVPROC) load(userptr, "glUniformMatrix2fv");
    glad_glUniformMatrix3fv = (PFNGLUNIFORMMATRIX3FVPROC) load(userptr, "glUniformMatrix3fv");
    glad_glUniformMatrix4fv = (PFNGLUNIFORMMATRIX4FVPROC) load(userptr, "glUniformMatrix4fv");
    glad_glUseProgram = (PFNGLUSEPROGRAMPROC) load(userptr, "glUseProgram");
    glad_glValidateProgram = (PFNGLVALIDATEPROGRAMPROC) load(userptr, "glValidateProgram");
    glad_glVertexAttrib1f = (PFNGLVERTEXATTRIB1FPROC) load(userptr, "glVertexAttrib1f");
    glad_glVertexAttrib1fv = (PFNGLVERTEXATTRIB1FVPROC) load(userptr, "glVertexAttrib1fv");
    glad_glVertexAttrib2f = (PFNGLVERTEXATTRIB2FPROC) load(userptr, "glVertexAttrib2f");
    glad_glVertexAttrib2fv = (PFNGLVERTEXATTRIB2FVPROC) load(userptr, "glVertexAttrib2fv");
    glad_glVertexAttrib3f = (PFNGLVERTEXATTRIB3FPROC) load(userptr, "glVertexAttrib3f");
    glad_glVertexAttrib3fv = (PFNGLVERTEXATTRIB3FVPROC) load(userptr, "glVertexAttrib3fv");
    glad_glVertexAttrib4f = (PFNGLVERTEXATTRIB4FPROC) load(userptr, "glVertexAttrib4f");
    glad_glVertexAttrib4fv = (PFNGLVERTEXATTRIB4FVPROC) load(userptr, "glVertexAttrib4fv");
    glad_glVertexAttribPointer = (PFNGLVERTEXATTRIBPOINTERPROC) load(userptr, "glVertexAttribPointer");
    glad_glViewport = (PFNGLVIEWPORTPROC) load(userptr, "glViewport");
}
static void glad_gl_load_GL_ES_VERSION_3_0( GLADuserptrloadfunc load, void* userptr) {
    if(!GLAD_GL_ES_VERSION_3_0) return;
    glad_glBeginQuery = (PFNGLBEGINQUERYPROC) load(userptr, "glBeginQuery");
    glad_glBeginTransformFeedback = (PFNGLBEGINTRANSFORMFEEDBACKPROC) load(userptr, "glBeginTransformFeedback");
    glad_glBindBufferBase = (PFNGLBINDBUFFERBASEPROC) load(userptr, "glBindBufferBase");
    glad_glBindBufferRange = (PFNGLBINDBUFFERRANGEPROC) load(userptr, "glBindBufferRange");
    glad_glBindSampler = (PFNGLBINDSAMPLERPROC) load(userptr, "glBindSampler");
    glad_glBindTransformFeedback = (PFNGLBINDTRANSFORMFEEDBACKPROC) load(userptr, "glBindTransformFeedback");
    glad_glBindVertexArray = (PFNGLBINDVERTEXARRAYPROC) load(userptr, "glBindVertexArray");
    glad_glBlitFramebuffer = (PFNGLBLITFRAMEBUFFERPROC) load(userptr, "glBlitFramebuffer");
    glad_glClearBufferfi = (PFNGLCLEARBUFFERFIPROC) load(userptr, "glClearBufferfi");
    glad_glClearBufferfv = (PFNGLCLEARBUFFERFVPROC) load(userptr, "glClearBufferfv");
    glad_glClearBufferiv = (PFNGLCLEARBUFFERIVPROC) load(userptr, "glClearBufferiv");
    glad_glClearBufferuiv = (PFNGLCLEARBUFFERUIVPROC) load(userptr, "glClearBufferuiv");
    glad_glClientWaitSync = (PFNGLCLIENTWAITSYNCPROC) load(userptr, "glClientWaitSync");
    glad_glCompressedTexImage3D = (PFNGLCOMPRESSEDTEXIMAGE3DPROC) load(userptr, "glCompressedTexImage3D");
    glad_glCompressedTexSubImage3D = (PFNGLCOMPRESSEDTEXSUBIMAGE3DPROC) load(userptr, "glCompressedTexSubImage3D");
    glad_glCopyBufferSubData = (PFNGLCOPYBUFFERSUBDATAPROC) load(userptr, "glCopyBufferSubData");
    glad_glCopyTexSubImage3D = (PFNGLCOPYTEXSUBIMAGE3DPROC) load(userptr, "glCopyTexSubImage3D");
    glad_glDeleteQueries = (PFNGLDELETEQUERIESPROC) load(userptr, "glDeleteQueries");
    glad_glDeleteSamplers = (PFNGLDELETESAMPLERSPROC) load(userptr, "glDeleteSamplers");
    glad_glDeleteSync = (PFNGLDELETESYNCPROC) load(userptr, "glDeleteSync");
    glad_glDeleteTransformFeedbacks = (PFNGLDELETETRANSFORMFEEDBACKSPROC) load(userptr, "glDeleteTransformFeedbacks");
    glad_glDeleteVertexArrays = (PFNGLDELETEVERTEXARRAYSPROC) load(userptr, "glDeleteVertexArrays");
    glad_glDrawArraysInstanced = (PFNGLDRAWARRAYSINSTANCEDPROC) load(userptr, "glDrawArraysInstanced");
    glad_glDrawBuffers = (PFNGLDRAWBUFFERSPROC) load(userptr, "glDrawBuffers");
    glad_glDrawElementsInstanced = (PFNGLDRAWELEMENTSINSTANCEDPROC) load(userptr, "glDrawElementsInstanced");
    glad_glDrawRangeElements = (PFNGLDRAWRANGEELEMENTSPROC) load(userptr, "glDrawRangeElements");
    glad_glEndQuery = (PFNGLENDQUERYPROC) load(userptr, "glEndQuery");
    glad_glEndTransformFeedback = (PFNGLENDTRANSFORMFEEDBACKPROC) load(userptr, "glEndTransformFeedback");
    glad_glFenceSync = (PFNGLFENCESYNCPROC) load(userptr, "glFenceSync");
    glad_glFlushMappedBufferRange = (PFNGLFLUSHMAPPEDBUFFERRANGEPROC) load(userptr, "glFlushMappedBufferRange");
    glad_glFramebufferTextureLayer = (PFNGLFRAMEBUFFERTEXTURELAYERPROC) load(userptr, "glFramebufferTextureLayer");
    glad_glGenQueries = (PFNGLGENQUERIESPROC) load(userptr, "glGenQueries");
    glad_glGenSamplers = (PFNGLGENSAMPLERSPROC) load(userptr, "glGenSamplers");
    glad_glGenTransformFeedbacks = (PFNGLGENTRANSFORMFEEDBACKSPROC) load(userptr, "glGenTransformFeedbacks");
    glad_glGenVertexArrays = (PFNGLGENVERTEXARRAYSPROC) load(userptr, "glGenVertexArrays");
    glad_glGetActiveUniformBlockName = (PFNGLGETACTIVEUNIFORMBLOCKNAMEPROC) load(userptr, "glGetActiveUniformBlockName");
    glad_glGetActiveUniformBlockiv = (PFNGLGETACTIVEUNIFORMBLOCKIVPROC) load(userptr, "glGetActiveUniformBlockiv");
    glad_glGetActiveUniformsiv = (PFNGLGETACTIVEUNIFORMSIVPROC) load(userptr, "glGetActiveUniformsiv");
    glad_glGetBufferParameteri64v = (PFNGLGETBUFFERPARAMETERI64VPROC) load(userptr, "glGetBufferParameteri64v");
    glad_glGetBufferPointerv = (PFNGLGETBUFFERPOINTERVPROC) load(userptr, "glGetBufferPointerv");
    glad_glGetFragDataLocation = (PFNGLGETFRAGDATALOCATIONPROC) load(userptr, "glGetFragDataLocation");
    glad_glGetInteger64i_v = (PFNGLGETINTEGER64I_VPROC) load(userptr, "glGetInteger64i_v");
    glad_glGetInteger64v = (PFNGLGETINTEGER64VPROC) load(userptr, "glGetInteger64v");
    glad_glGetIntegeri_v = (PFNGLGETINTEGERI_VPROC) load(userptr, "glGetIntegeri_v");
    glad_glGetInternalformativ = (PFNGLGETINTERNALFORMATIVPROC) load(userptr, "glGetInternalformativ");
    glad_glGetProgramBinary = (PFNGLGETPROGRAMBINARYPROC) load(userptr, "glGetProgramBinary");
    glad_glGetQueryObjectuiv = (PFNGLGETQUERYOBJECTUIVPROC) load(userptr, "glGetQueryObjectuiv");
    glad_glGetQueryiv = (PFNGLGETQUERYIVPROC) load(userptr, "glGetQueryiv");
    glad_glGetSamplerParameterfv = (PFNGLGETSAMPLERPARAMETERFVPROC) load(userptr, "glGetSamplerParameterfv");
    glad_glGetSamplerParameteriv = (PFNGLGETSAMPLERPARAMETERIVPROC) load(userptr, "glGetSamplerParameteriv");
    glad_glGetStringi = (PFNGLGETSTRINGIPROC) load(userptr, "glGetStringi");
    glad_glGetSynciv = (PFNGLGETSYNCIVPROC) load(userptr, "glGetSynciv");
    glad_glGetTransformFeedbackVarying = (PFNGLGETTRANSFORMFEEDBACKVARYINGPROC) load(userptr, "glGetTransformFeedbackVarying");
    glad_glGetUniformBlockIndex = (PFNGLGETUNIFORMBLOCKINDEXPROC) load(userptr, "glGetUniformBlockIndex");
    glad_glGetUniformIndices = (PFNGLGETUNIFORMINDICESPROC) load(userptr, "glGetUniformIndices");
    glad_glGetUniformuiv = (PFNGLGETUNIFORMUIVPROC) load(userptr, "glGetUniformuiv");
    glad_glGetVertexAttribIiv = (PFNGLGETVERTEXATTRIBIIVPROC) load(userptr, "glGetVertexAttribIiv");
    glad_glGetVertexAttribIuiv = (PFNGLGETVERTEXATTRIBIUIVPROC) load(userptr, "glGetVertexAttribIuiv");
    glad_glInvalidateFramebuffer = (PFNGLINVALIDATEFRAMEBUFFERPROC) load(userptr, "glInvalidateFramebuffer");
    glad_glInvalidateSubFramebuffer = (PFNGLINVALIDATESUBFRAMEBUFFERPROC) load(userptr, "glInvalidateSubFramebuffer");
    glad_glIsQuery = (PFNGLISQUERYPROC) load(userptr, "glIsQuery");
    glad_glIsSampler = (PFNGLISSAMPLERPROC) load(userptr, "glIsSampler");
    glad_glIsSync = (PFNGLISSYNCPROC) load(userptr, "glIsSync");
    glad_glIsTransformFeedback = (PFNGLISTRANSFORMFEEDBACKPROC) load(userptr, "glIsTransformFeedback");
    glad_glIsVertexArray = (PFNGLISVERTEXARRAYPROC) load(userptr, "glIsVertexArray");
    glad_glMapBufferRange = (PFNGLMAPBUFFERRANGEPROC) load(userptr, "glMapBufferRange");
    glad_glPauseTransformFeedback = (PFNGLPAUSETRANSFORMFEEDBACKPROC) load(userptr, "glPauseTransformFeedback");
    glad_glProgramBinary = (PFNGLPROGRAMBINARYPROC) load(userptr, "glProgramBinary");
    glad_glProgramParameteri = (PFNGLPROGRAMPARAMETERIPROC) load(userptr, "glProgramParameteri");
    glad_glReadBuffer = (PFNGLREADBUFFERPROC) load(userptr, "glReadBuffer");
    glad_glRenderbufferStorageMultisample = (PFNGLRENDERBUFFERSTORAGEMULTISAMPLEPROC) load(userptr, "glRenderbufferStorageMultisample");
    glad_glResumeTransformFeedback = (PFNGLRESUMETRANSFORMFEEDBACKPROC) load(userptr, "glResumeTransformFeedback");
    glad_glSamplerParameterf = (PFNGLSAMPLERPARAMETERFPROC) load(userptr, "glSamplerParameterf");
    glad_glSamplerParameterfv = (PFNGLSAMPLERPARAMETERFVPROC) load(userptr, "glSamplerParameterfv");
    glad_glSamplerParameteri = (PFNGLSAMPLERPARAMETERIPROC) load(userptr, "glSamplerParameteri");
    glad_glSamplerParameteriv = (PFNGLSAMPLERPARAMETERIVPROC) load(userptr, "glSamplerParameteriv");
    glad_glTexImage3D = (PFNGLTEXIMAGE3DPROC) load(userptr, "glTexImage3D");
    glad_glTexStorage2D = (PFNGLTEXSTORAGE2DPROC) load(userptr, "glTexStorage2D");
    glad_glTexStorage3D = (PFNGLTEXSTORAGE3DPROC) load(userptr, "glTexStorage3D");
    glad_glTexSubImage3D = (PFNGLTEXSUBIMAGE3DPROC) load(userptr, "glTexSubImage3D");
    glad_glTransformFeedbackVaryings = (PFNGLTRANSFORMFEEDBACKVARYINGSPROC) load(userptr, "glTransformFeedbackVaryings");
    glad_glUniform1ui = (PFNGLUNIFORM1UIPROC) load(userptr, "glUniform1ui");
    glad_glUniform1uiv = (PFNGLUNIFORM1UIVPROC) load(userptr, "glUniform1uiv");
    glad_glUniform2ui = (PFNGLUNIFORM2UIPROC) load(userptr, "glUniform2ui");
    glad_glUniform2uiv = (PFNGLUNIFORM2UIVPROC) load(userptr, "glUniform2uiv");
    glad_glUniform3ui = (PFNGLUNIFORM3UIPROC) load(userptr, "glUniform3ui");
    glad_glUniform3uiv = (PFNGLUNIFORM3UIVPROC) load(userptr, "glUniform3uiv");
    glad_glUniform4ui = (PFNGLUNIFORM4UIPROC) load(userptr, "glUniform4ui");
    glad_glUniform4uiv = (PFNGLUNIFORM4UIVPROC) load(userptr, "glUniform4uiv");
    glad_glUniformBlockBinding = (PFNGLUNIFORMBLOCKBINDINGPROC) load(userptr, "glUniformBlockBinding");
    glad_glUniformMatrix2x3fv = (PFNGLUNIFORMMATRIX2X3FVPROC) load(userptr, "glUniformMatrix2x3fv");
    glad_glUniformMatrix2x4fv = (PFNGLUNIFORMMATRIX2X4FVPROC) load(userptr, "glUniformMatrix2x4fv");
    glad_glUniformMatrix3x2fv = (PFNGLUNIFORMMATRIX3X2FVPROC) load(userptr, "glUniformMatrix3x2fv");
    glad_glUniformMatrix3x4fv = (PFNGLUNIFORMMATRIX3X4FVPROC) load(userptr, "glUniformMatrix3x4fv");
    glad_glUniformMatrix4x2fv = (PFNGLUNIFORMMATRIX4X2FVPROC) load(userptr, "glUniformMatrix4x2fv");
    glad_glUniformMatrix4x3fv = (PFNGLUNIFORMMATRIX4X3FVPROC) load(userptr, "glUniformMatrix4x3fv");
    glad_glUnmapBuffer = (PFNGLUNMAPBUFFERPROC) load(userptr, "glUnmapBuffer");
    glad_glVertexAttribDivisor = (PFNGLVERTEXATTRIBDIVISORPROC) load(userptr, "glVertexAttribDivisor");
    glad_glVertexAttribI4i = (PFNGLVERTEXATTRIBI4IPROC) load(userptr, "glVertexAttribI4i");
    glad_glVertexAttribI4iv = (PFNGLVERTEXATTRIBI4IVPROC) load(userptr, "glVertexAttribI4iv");
    glad_glVertexAttribI4ui = (PFNGLVERTEXATTRIBI4UIPROC) load(userptr, "glVertexAttribI4ui");
    glad_glVertexAttribI4uiv = (PFNGLVERTEXATTRIBI4UIVPROC) load(userptr, "glVertexAttribI4uiv");
    glad_glVertexAttribIPointer = (PFNGLVERTEXATTRIBIPOINTERPROC) load(userptr, "glVertexAttribIPointer");
    glad_glWaitSync = (PFNGLWAITSYNCPROC) load(userptr, "glWaitSync");
}
static void glad_gl_load_GL_ES_VERSION_3_1( GLADuserptrloadfunc load, void* userptr) {
    if(!GLAD_GL_ES_VERSION_3_1) return;
    glad_glActiveShaderProgram = (PFNGLACTIVESHADERPROGRAMPROC) load(userptr, "glActiveShaderProgram");
    glad_glBindImageTexture = (PFNGLBINDIMAGETEXTUREPROC) load(userptr, "glBindImageTexture");
    glad_glBindProgramPipeline = (PFNGLBINDPROGRAMPIPELINEPROC) load(userptr, "glBindProgramPipeline");
    glad_glBindVertexBuffer = (PFNGLBINDVERTEXBUFFERPROC) load(userptr, "glBindVertexBuffer");
    glad_glCreateShaderProgramv = (PFNGLCREATESHADERPROGRAMVPROC) load(userptr, "glCreateShaderProgramv");
    glad_glDeleteProgramPipelines = (PFNGLDELETEPROGRAMPIPELINESPROC) load(userptr, "glDeleteProgramPipelines");
    glad_glDispatchCompute = (PFNGLDISPATCHCOMPUTEPROC) load(userptr, "glDispatchCompute");
    glad_glDispatchComputeIndirect = (PFNGLDISPATCHCOMPUTEINDIRECTPROC) load(userptr, "glDispatchComputeIndirect");
    glad_glDrawArraysIndirect = (PFNGLDRAWARRAYSINDIRECTPROC) load(userptr, "glDrawArraysIndirect");
    glad_glDrawElementsIndirect = (PFNGLDRAWELEMENTSINDIRECTPROC) load(userptr, "glDrawElementsIndirect");
    glad_glFramebufferParameteri = (PFNGLFRAMEBUFFERPARAMETERIPROC) load(userptr, "glFramebufferParameteri");
    glad_glGenProgramPipelines = (PFNGLGENPROGRAMPIPELINESPROC) load(userptr, "glGenProgramPipelines");
    glad_glGetBooleani_v = (PFNGLGETBOOLEANI_VPROC) load(userptr, "glGetBooleani_v");
    glad_glGetFramebufferParameteriv = (PFNGLGETFRAMEBUFFERPARAMETERIVPROC) load(userptr, "glGetFramebufferParameteriv");
    glad_glGetMultisamplefv = (PFNGLGETMULTISAMPLEFVPROC) load(userptr, "glGetMultisamplefv");
    glad_glGetProgramInterfaceiv = (PFNGLGETPROGRAMINTERFACEIVPROC) load(userptr, "glGetProgramInterfaceiv");
    glad_glGetProgramPipelineInfoLog = (PFNGLGETPROGRAMPIPELINEINFOLOGPROC) load(userptr, "glGetProgramPipelineInfoLog");
    glad_glGetProgramPipelineiv = (PFNGLGETPROGRAMPIPELINEIVPROC) load(userptr, "glGetProgramPipelineiv");
    glad_glGetProgramResourceIndex = (PFNGLGETPROGRAMRESOURCEINDEXPROC) load(userptr, "glGetProgramResourceIndex");
    glad_glGetProgramResourceLocation = (PFNGLGETPROGRAMRESOURCELOCATIONPROC) load(userptr, "glGetProgramResourceLocation");
    glad_glGetProgramResourceName = (PFNGLGETPROGRAMRESOURCENAMEPROC) load(userptr, "glGetProgramResourceName");
    glad_glGetProgramResourceiv = (PFNGLGETPROGRAMRESOURCEIVPROC) load(userptr, "glGetProgramResourceiv");
    glad_glGetTexLevelParameterfv = (PFNGLGETTEXLEVELPARAMETERFVPROC) load(userptr, "glGetTexLevelParameterfv");
    glad_glGetTexLevelParameteriv = (PFNGLGETTEXLEVELPARAMETERIVPROC) load(userptr, "glGetTexLevelParameteriv");
    glad_glIsProgramPipeline = (PFNGLISPROGRAMPIPELINEPROC) load(userptr, "glIsProgramPipeline");
    glad_glMemoryBarrier = (PFNGLMEMORYBARRIERPROC) load(userptr, "glMemoryBarrier");
    glad_glMemoryBarrierByRegion = (PFNGLMEMORYBARRIERBYREGIONPROC) load(userptr, "glMemoryBarrierByRegion");
    glad_glProgramUniform1f = (PFNGLPROGRAMUNIFORM1FPROC) load(userptr, "glProgramUniform1f");
    glad_glProgramUniform1fv = (PFNGLPROGRAMUNIFORM1FVPROC) load(userptr, "glProgramUniform1fv");
    glad_glProgramUniform1i = (PFNGLPROGRAMUNIFORM1IPROC) load(userptr, "glProgramUniform1i");
    glad_glProgramUniform1iv = (PFNGLPROGRAMUNIFORM1IVPROC) load(userptr, "glProgramUniform1iv");
    glad_glProgramUniform1ui = (PFNGLPROGRAMUNIFORM1UIPROC) load(userptr, "glProgramUniform1ui");
    glad_glProgramUniform1uiv = (PFNGLPROGRAMUNIFORM1UIVPROC) load(userptr, "glProgramUniform1uiv");
    glad_glProgramUniform2f = (PFNGLPROGRAMUNIFORM2FPROC) load(userptr, "glProgramUniform2f");
    glad_glProgramUniform2fv = (PFNGLPROGRAMUNIFORM2FVPROC) load(userptr, "glProgramUniform2fv");
    glad_glProgramUniform2i = (PFNGLPROGRAMUNIFORM2IPROC) load(userptr, "glProgramUniform2i");
    glad_glProgramUniform2iv = (PFNGLPROGRAMUNIFORM2IVPROC) load(userptr, "glProgramUniform2iv");
    glad_glProgramUniform2ui = (PFNGLPROGRAMUNIFORM2UIPROC) load(userptr, "glProgramUniform2ui");
    glad_glProgramUniform2uiv = (PFNGLPROGRAMUNIFORM2UIVPROC) load(userptr, "glProgramUniform2uiv");
    glad_glProgramUniform3f = (PFNGLPROGRAMUNIFORM3FPROC) load(userptr, "glProgramUniform3f");
    glad_glProgramUniform3fv = (PFNGLPROGRAMUNIFORM3FVPROC) load(userptr, "glProgramUniform3fv");
    glad_glProgramUniform3i = (PFNGLPROGRAMUNIFORM3IPROC) load(userptr, "glProgramUniform3i");
    glad_glProgramUniform3iv = (PFNGLPROGRAMUNIFORM3IVPROC) load(userptr, "glProgramUniform3iv");
    glad_glProgramUniform3ui = (PFNGLPROGRAMUNIFORM3UIPROC) load(userptr, "glProgramUniform3ui");
    glad_glProgramUniform3uiv = (PFNGLPROGRAMUNIFORM3UIVPROC) load(userptr, "glProgramUniform3uiv");
    glad_glProgramUniform4f = (PFNGLPROGRAMUNIFORM4FPROC) load(userptr, "glProgramUniform4f");
    glad_glProgramUniform4fv = (PFNGLPROGRAMUNIFORM4FVPROC) load(userptr, "glProgramUniform4fv");
    glad_glProgramUniform4i = (PFNGLPROGRAMUNIFORM4IPROC) load(userptr, "glProgramUniform4i");
    glad_glProgramUniform4iv = (PFNGLPROGRAMUNIFORM4IVPROC) load(userptr, "glProgramUniform4iv");
    glad_glProgramUniform4ui = (PFNGLPROGRAMUNIFORM4UIPROC) load(userptr, "glProgramUniform4ui");
    glad_glProgramUniform4uiv = (PFNGLPROGRAMUNIFORM4UIVPROC) load(userptr, "glProgramUniform4uiv");
    glad_glProgramUniformMatrix2fv = (PFNGLPROGRAMUNIFORMMATRIX2FVPROC) load(userptr, "glProgramUniformMatrix2fv");
    glad_glProgramUniformMatrix2x3fv = (PFNGLPROGRAMUNIFORMMATRIX2X3FVPROC) load(userptr, "glProgramUniformMatrix2x3fv");
    glad_glProgramUniformMatrix2x4fv = (PFNGLPROGRAMUNIFORMMATRIX2X4FVPROC) load(userptr, "glProgramUniformMatrix2x4fv");
    glad_glProgramUniformMatrix3fv = (PFNGLPROGRAMUNIFORMMATRIX3FVPROC) load(userptr, "glProgramUniformMatrix3fv");
    glad_glProgramUniformMatrix3x2fv = (PFNGLPROGRAMUNIFORMMATRIX3X2FVPROC) load(userptr, "glProgramUniformMatrix3x2fv");
    glad_glProgramUniformMatrix3x4fv = (PFNGLPROGRAMUNIFORMMATRIX3X4FVPROC) load(userptr, "glProgramUniformMatrix3x4fv");
    glad_glProgramUniformMatrix4fv = (PFNGLPROGRAMUNIFORMMATRIX4FVPROC) load(userptr, "glProgramUniformMatrix4fv");
    glad_glProgramUniformMatrix4x2fv = (PFNGLPROGRAMUNIFORMMATRIX4X2FVPROC) load(userptr, "glProgramUniformMatrix4x2fv");
    glad_glProgramUniformMatrix4x3fv = (PFNGLPROGRAMUNIFORMMATRIX4X3FVPROC) load(userptr, "glProgramUniformMatrix4x3fv");
    glad_glSampleMaski = (PFNGLSAMPLEMASKIPROC) load(userptr, "glSampleMaski");
    glad_glTexStorage2DMultisample = (PFNGLTEXSTORAGE2DMULTISAMPLEPROC) load(userptr, "glTexStorage2DMultisample");
    glad_glUseProgramStages = (PFNGLUSEPROGRAMSTAGESPROC) load(userptr, "glUseProgramStages");
    glad_glValidateProgramPipeline = (PFNGLVALIDATEPROGRAMPIPELINEPROC) load(userptr, "glValidateProgramPipeline");
    glad_glVertexAttribBinding = (PFNGLVERTEXATTRIBBINDINGPROC) load(userptr, "glVertexAttribBinding");
    glad_glVertexAttribFormat = (PFNGLVERTEXATTRIBFORMATPROC) load(userptr, "glVertexAttribFormat");
    glad_glVertexAttribIFormat = (PFNGLVERTEXATTRIBIFORMATPROC) load(userptr, "glVertexAttribIFormat");
    glad_glVertexBindingDivisor = (PFNGLVERTEXBINDINGDIVISORPROC) load(userptr, "glVertexBindingDivisor");
}
static void glad_gl_load_GL_ES_VERSION_3_2( GLADuserptrloadfunc load, void* userptr) {
    if(!GLAD_GL_ES_VERSION_3_2) return;
    glad_glBlendBarrier = (PFNGLBLENDBARRIERPROC) load(userptr, "glBlendBarrier");
    glad_glBlendEquationSeparatei = (PFNGLBLENDEQUATIONSEPARATEIPROC) load(userptr, "glBlendEquationSeparatei");
    glad_glBlendEquationi = (PFNGLBLENDEQUATIONIPROC) load(userptr, "glBlendEquationi");
    glad_glBlendFuncSeparatei = (PFNGLBLENDFUNCSEPARATEIPROC) load(userptr, "glBlendFuncSeparatei");
    glad_glBlendFunci = (PFNGLBLENDFUNCIPROC) load(userptr, "glBlendFunci");
    glad_glColorMaski = (PFNGLCOLORMASKIPROC) load(userptr, "glColorMaski");
    glad_glCopyImageSubData = (PFNGLCOPYIMAGESUBDATAPROC) load(userptr, "glCopyImageSubData");
    glad_glDebugMessageCallback = (PFNGLDEBUGMESSAGECALLBACKPROC) load(userptr, "glDebugMessageCallback");
    glad_glDebugMessageControl = (PFNGLDEBUGMESSAGECONTROLPROC) load(userptr, "glDebugMessageControl");
    glad_glDebugMessageInsert = (PFNGLDEBUGMESSAGEINSERTPROC) load(userptr, "glDebugMessageInsert");
    glad_glDisablei = (PFNGLDISABLEIPROC) load(userptr, "glDisablei");
    glad_glDrawElementsBaseVertex = (PFNGLDRAWELEMENTSBASEVERTEXPROC) load(userptr, "glDrawElementsBaseVertex");
    glad_glDrawElementsInstancedBaseVertex = (PFNGLDRAWELEMENTSINSTANCEDBASEVERTEXPROC) load(userptr, "glDrawElementsInstancedBaseVertex");
    glad_glDrawRangeElementsBaseVertex = (PFNGLDRAWRANGEELEMENTSBASEVERTEXPROC) load(userptr, "glDrawRangeElementsBaseVertex");
    glad_glEnablei = (PFNGLENABLEIPROC) load(userptr, "glEnablei");
    glad_glFramebufferTexture = (PFNGLFRAMEBUFFERTEXTUREPROC) load(userptr, "glFramebufferTexture");
    glad_glGetDebugMessageLog = (PFNGLGETDEBUGMESSAGELOGPROC) load(userptr, "glGetDebugMessageLog");
    glad_glGetGraphicsResetStatus = (PFNGLGETGRAPHICSRESETSTATUSPROC) load(userptr, "glGetGraphicsResetStatus");
    glad_glGetObjectLabel = (PFNGLGETOBJECTLABELPROC) load(userptr, "glGetObjectLabel");
    glad_glGetObjectPtrLabel = (PFNGLGETOBJECTPTRLABELPROC) load(userptr, "glGetObjectPtrLabel");
    glad_glGetPointerv = (PFNGLGETPOINTERVPROC) load(userptr, "glGetPointerv");
    glad_glGetSamplerParameterIiv = (PFNGLGETSAMPLERPARAMETERIIVPROC) load(userptr, "glGetSamplerParameterIiv");
    glad_glGetSamplerParameterIuiv = (PFNGLGETSAMPLERPARAMETERIUIVPROC) load(userptr, "glGetSamplerParameterIuiv");
    glad_glGetTexParameterIiv = (PFNGLGETTEXPARAMETERIIVPROC) load(userptr, "glGetTexParameterIiv");
    glad_glGetTexParameterIuiv = (PFNGLGETTEXPARAMETERIUIVPROC) load(userptr, "glGetTexParameterIuiv");
    glad_glGetnUniformfv = (PFNGLGETNUNIFORMFVPROC) load(userptr, "glGetnUniformfv");
    glad_glGetnUniformiv = (PFNGLGETNUNIFORMIVPROC) load(userptr, "glGetnUniformiv");
    glad_glGetnUniformuiv = (PFNGLGETNUNIFORMUIVPROC) load(userptr, "glGetnUniformuiv");
    glad_glIsEnabledi = (PFNGLISENABLEDIPROC) load(userptr, "glIsEnabledi");
    glad_glMinSampleShading = (PFNGLMINSAMPLESHADINGPROC) load(userptr, "glMinSampleShading");
    glad_glObjectLabel = (PFNGLOBJECTLABELPROC) load(userptr, "glObjectLabel");
    glad_glObjectPtrLabel = (PFNGLOBJECTPTRLABELPROC) load(userptr, "glObjectPtrLabel");
    glad_glPatchParameteri = (PFNGLPATCHPARAMETERIPROC) load(userptr, "glPatchParameteri");
    glad_glPopDebugGroup = (PFNGLPOPDEBUGGROUPPROC) load(userptr, "glPopDebugGroup");
    glad_glPrimitiveBoundingBox = (PFNGLPRIMITIVEBOUNDINGBOXPROC) load(userptr, "glPrimitiveBoundingBox");
    glad_glPushDebugGroup = (PFNGLPUSHDEBUGGROUPPROC) load(userptr, "glPushDebugGroup");
    glad_glReadnPixels = (PFNGLREADNPIXELSPROC) load(userptr, "glReadnPixels");
    glad_glSamplerParameterIiv = (PFNGLSAMPLERPARAMETERIIVPROC) load(userptr, "glSamplerParameterIiv");
    glad_glSamplerParameterIuiv = (PFNGLSAMPLERPARAMETERIUIVPROC) load(userptr, "glSamplerParameterIuiv");
    glad_glTexBuffer = (PFNGLTEXBUFFERPROC) load(userptr, "glTexBuffer");
    glad_glTexBufferRange = (PFNGLTEXBUFFERRANGEPROC) load(userptr, "glTexBufferRange");
    glad_glTexParameterIiv = (PFNGLTEXPARAMETERIIVPROC) load(userptr, "glTexParameterIiv");
    glad_glTexParameterIuiv = (PFNGLTEXPARAMETERIUIVPROC) load(userptr, "glTexParameterIuiv");
    glad_glTexStorage3DMultisample = (PFNGLTEXSTORAGE3DMULTISAMPLEPROC) load(userptr, "glTexStorage3DMultisample");
}
static void glad_gl_load_GL_AMD_framebuffer_multisample_advanced( GLADuserptrloadfunc load, void* userptr) {
    if(!GLAD_GL_AMD_framebuffer_multisample_advanced) return;
    glad_glNamedRenderbufferStorageMultisampleAdvancedAMD = (PFNGLNAMEDRENDERBUFFERSTORAGEMULTISAMPLEADVANCEDAMDPROC) load(userptr, "glNamedRenderbufferStorageMultisampleAdvancedAMD");
    glad_glRenderbufferStorageMultisampleAdvancedAMD = (PFNGLRENDERBUFFERSTORAGEMULTISAMPLEADVANCEDAMDPROC) load(userptr, "glRenderbufferStorageMultisampleAdvancedAMD");
}
static void glad_gl_load_GL_AMD_performance_monitor( GLADuserptrloadfunc load, void* userptr) {
    if(!GLAD_GL_AMD_performance_monitor) return;
    glad_glBeginPerfMonitorAMD = (PFNGLBEGINPERFMONITORAMDPROC) load(userptr, "glBeginPerfMonitorAMD");
    glad_glDeletePerfMonitorsAMD = (PFNGLDELETEPERFMONITORSAMDPROC) load(userptr, "glDeletePerfMonitorsAMD");
    glad_glEndPerfMonitorAMD = (PFNGLENDPERFMONITORAMDPROC) load(userptr, "glEndPerfMonitorAMD");
    glad_glGenPerfMonitorsAMD = (PFNGLGENPERFMONITORSAMDPROC) load(userptr, "glGenPerfMonitorsAMD");
    glad_glGetPerfMonitorCounterDataAMD = (PFNGLGETPERFMONITORCOUNTERDATAAMDPROC) load(userptr, "glGetPerfMonitorCounterDataAMD");
    glad_glGetPerfMonitorCounterInfoAMD = (PFNGLGETPERFMONITORCOUNTERINFOAMDPROC) load(userptr, "glGetPerfMonitorCounterInfoAMD");
    glad_glGetPerfMonitorCounterStringAMD = (PFNGLGETPERFMONITORCOUNTERSTRINGAMDPROC) load(userptr, "glGetPerfMonitorCounterStringAMD");
    glad_glGetPerfMonitorCountersAMD = (PFNGLGETPERFMONITORCOUNTERSAMDPROC) load(userptr, "glGetPerfMonitorCountersAMD");
    glad_glGetPerfMonitorGroupStringAMD = (PFNGLGETPERFMONITORGROUPSTRINGAMDPROC) load(userptr, "glGetPerfMonitorGroupStringAMD");
    glad_glGetPerfMonitorGroupsAMD = (PFNGLGETPERFMONITORGROUPSAMDPROC) load(userptr, "glGetPerfMonitorGroupsAMD");
    glad_glSelectPerfMonitorCountersAMD = (PFNGLSELECTPERFMONITORCOUNTERSAMDPROC) load(userptr, "glSelectPerfMonitorCountersAMD");
}
static void glad_gl_load_GL_ANGLE_framebuffer_blit( GLADuserptrloadfunc load, void* userptr) {
    if(!GLAD_GL_ANGLE_framebuffer_blit) return;
    glad_glBlitFramebufferANGLE = (PFNGLBLITFRAMEBUFFERANGLEPROC) load(userptr, "glBlitFramebufferANGLE");
}
static void glad_gl_load_GL_ANGLE_framebuffer_multisample( GLADuserptrloadfunc load, void* userptr) {
    if(!GLAD_GL_ANGLE_framebuffer_multisample) return;
    glad_glRenderbufferStorageMultisampleANGLE = (PFNGLRENDERBUFFERSTORAGEMULTISAMPLEANGLEPROC) load(userptr, "glRenderbufferStorageMultisampleANGLE");
}
static void glad_gl_load_GL_ANGLE_instanced_arrays( GLADuserptrloadfunc load, void* userptr) {
    if(!GLAD_GL_ANGLE_instanced_arrays) return;
    glad_glDrawArraysInstancedANGLE = (PFNGLDRAWARRAYSINSTANCEDANGLEPROC) load(userptr, "glDrawArraysInstancedANGLE");
    glad_glDrawElementsInstancedANGLE = (PFNGLDRAWELEMENTSINSTANCEDANGLEPROC) load(userptr, "glDrawElementsInstancedANGLE");
    glad_glVertexAttribDivisorANGLE = (PFNGLVERTEXATTRIBDIVISORANGLEPROC) load(userptr, "glVertexAttribDivisorANGLE");
}
static void glad_gl_load_GL_ANGLE_translated_shader_source( GLADuserptrloadfunc load, void* userptr) {
    if(!GLAD_GL_ANGLE_translated_shader_source) return;
    glad_glGetTranslatedShaderSourceANGLE = (PFNGLGETTRANSLATEDSHADERSOURCEANGLEPROC) load(userptr, "glGetTranslatedShaderSourceANGLE");
}
static void glad_gl_load_GL_APPLE_copy_texture_levels( GLADuserptrloadfunc load, void* userptr) {
    if(!GLAD_GL_APPLE_copy_texture_levels) return;
    glad_glCopyTextureLevelsAPPLE = (PFNGLCOPYTEXTURELEVELSAPPLEPROC) load(userptr, "glCopyTextureLevelsAPPLE");
}
static void glad_gl_load_GL_APPLE_framebuffer_multisample( GLADuserptrloadfunc load, void* userptr) {
    if(!GLAD_GL_APPLE_framebuffer_multisample) return;
    glad_glRenderbufferStorageMultisampleAPPLE = (PFNGLRENDERBUFFERSTORAGEMULTISAMPLEAPPLEPROC) load(userptr, "glRenderbufferStorageMultisampleAPPLE");
    glad_glResolveMultisampleFramebufferAPPLE = (PFNGLRESOLVEMULTISAMPLEFRAMEBUFFERAPPLEPROC) load(userptr, "glResolveMultisampleFramebufferAPPLE");
}
static void glad_gl_load_GL_APPLE_sync( GLADuserptrloadfunc load, void* userptr) {
    if(!GLAD_GL_APPLE_sync) return;
    glad_glClientWaitSyncAPPLE = (PFNGLCLIENTWAITSYNCAPPLEPROC) load(userptr, "glClientWaitSyncAPPLE");
    glad_glDeleteSyncAPPLE = (PFNGLDELETESYNCAPPLEPROC) load(userptr, "glDeleteSyncAPPLE");
    glad_glFenceSyncAPPLE = (PFNGLFENCESYNCAPPLEPROC) load(userptr, "glFenceSyncAPPLE");
    glad_glGetInteger64vAPPLE = (PFNGLGETINTEGER64VAPPLEPROC) load(userptr, "glGetInteger64vAPPLE");
    glad_glGetSyncivAPPLE = (PFNGLGETSYNCIVAPPLEPROC) load(userptr, "glGetSyncivAPPLE");
    glad_glIsSyncAPPLE = (PFNGLISSYNCAPPLEPROC) load(userptr, "glIsSyncAPPLE");
    glad_glWaitSyncAPPLE = (PFNGLWAITSYNCAPPLEPROC) load(userptr, "glWaitSyncAPPLE");
}
static void glad_gl_load_GL_EXT_EGL_image_storage( GLADuserptrloadfunc load, void* userptr) {
    if(!GLAD_GL_EXT_EGL_image_storage) return;
    glad_glEGLImageTargetTexStorageEXT = (PFNGLEGLIMAGETARGETTEXSTORAGEEXTPROC) load(userptr, "glEGLImageTargetTexStorageEXT");
    glad_glEGLImageTargetTextureStorageEXT = (PFNGLEGLIMAGETARGETTEXTURESTORAGEEXTPROC) load(userptr, "glEGLImageTargetTextureStorageEXT");
}
static void glad_gl_load_GL_EXT_base_instance( GLADuserptrloadfunc load, void* userptr) {
    if(!GLAD_GL_EXT_base_instance) return;
    glad_glDrawArraysInstancedBaseInstanceEXT = (PFNGLDRAWARRAYSINSTANCEDBASEINSTANCEEXTPROC) load(userptr, "glDrawArraysInstancedBaseInstanceEXT");
    glad_glDrawElementsInstancedBaseInstanceEXT = (PFNGLDRAWELEMENTSINSTANCEDBASEINSTANCEEXTPROC) load(userptr, "glDrawElementsInstancedBaseInstanceEXT");
    glad_glDrawElementsInstancedBaseVertexBaseInstanceEXT = (PFNGLDRAWELEMENTSINSTANCEDBASEVERTEXBASEINSTANCEEXTPROC) load(userptr, "glDrawElementsInstancedBaseVertexBaseInstanceEXT");
}
static void glad_gl_load_GL_EXT_blend_func_extended( GLADuserptrloadfunc load, void* userptr) {
    if(!GLAD_GL_EXT_blend_func_extended) return;
    glad_glBindFragDataLocationEXT = (PFNGLBINDFRAGDATALOCATIONEXTPROC) load(userptr, "glBindFragDataLocationEXT");
    glad_glBindFragDataLocationIndexedEXT = (PFNGLBINDFRAGDATALOCATIONINDEXEDEXTPROC) load(userptr, "glBindFragDataLocationIndexedEXT");
    glad_glGetFragDataIndexEXT = (PFNGLGETFRAGDATAINDEXEXTPROC) load(userptr, "glGetFragDataIndexEXT");
    glad_glGetProgramResourceLocationIndexEXT = (PFNGLGETPROGRAMRESOURCELOCATIONINDEXEXTPROC) load(userptr, "glGetProgramResourceLocationIndexEXT");
}
static void glad_gl_load_GL_EXT_buffer_storage( GLADuserptrloadfunc load, void* userptr) {
    if(!GLAD_GL_EXT_buffer_storage) return;
    glad_glBufferStorageEXT = (PFNGLBUFFERSTORAGEEXTPROC) load(userptr, "glBufferStorageEXT");
}
static void glad_gl_load_GL_EXT_clear_texture( GLADuserptrloadfunc load, void* userptr) {
    if(!GLAD_GL_EXT_clear_texture) return;
    glad_glClearTexImageEXT = (PFNGLCLEARTEXIMAGEEXTPROC) load(userptr, "glClearTexImageEXT");
    glad_glClearTexSubImageEXT = (PFNGLCLEARTEXSUBIMAGEEXTPROC) load(userptr, "glClearTexSubImageEXT");
}
static void glad_gl_load_GL_EXT_clip_control( GLADuserptrloadfunc load, void* userptr) {
    if(!GLAD_GL_EXT_clip_control) return;
    glad_glClipControlEXT = (PFNGLCLIPCONTROLEXTPROC) load(userptr, "glClipControlEXT");
}
static void glad_gl_load_GL_EXT_copy_image( GLADuserptrloadfunc load, void* userptr) {
    if(!GLAD_GL_EXT_copy_image) return;
    glad_glCopyImageSubDataEXT = (PFNGLCOPYIMAGESUBDATAEXTPROC) load(userptr, "glCopyImageSubDataEXT");
}
static void glad_gl_load_GL_EXT_debug_label( GLADuserptrloadfunc load, void* userptr) {
    if(!GLAD_GL_EXT_debug_label) return;
    glad_glGetObjectLabelEXT = (PFNGLGETOBJECTLABELEXTPROC) load(userptr, "glGetObjectLabelEXT");
    glad_glLabelObjectEXT = (PFNGLLABELOBJECTEXTPROC) load(userptr, "glLabelObjectEXT");
}
static void glad_gl_load_GL_EXT_debug_marker( GLADuserptrloadfunc load, void* userptr) {
    if(!GLAD_GL_EXT_debug_marker) return;
    glad_glInsertEventMarkerEXT = (PFNGLINSERTEVENTMARKEREXTPROC) load(userptr, "glInsertEventMarkerEXT");
    glad_glPopGroupMarkerEXT = (PFNGLPOPGROUPMARKEREXTPROC) load(userptr, "glPopGroupMarkerEXT");
    glad_glPushGroupMarkerEXT = (PFNGLPUSHGROUPMARKEREXTPROC) load(userptr, "glPushGroupMarkerEXT");
}
static void glad_gl_load_GL_EXT_discard_framebuffer( GLADuserptrloadfunc load, void* userptr) {
    if(!GLAD_GL_EXT_discard_framebuffer) return;
    glad_glDiscardFramebufferEXT = (PFNGLDISCARDFRAMEBUFFEREXTPROC) load(userptr, "glDiscardFramebufferEXT");
}
static void glad_gl_load_GL_EXT_disjoint_timer_query( GLADuserptrloadfunc load, void* userptr) {
    if(!GLAD_GL_EXT_disjoint_timer_query) return;
    glad_glBeginQueryEXT = (PFNGLBEGINQUERYEXTPROC) load(userptr, "glBeginQueryEXT");
    glad_glDeleteQueriesEXT = (PFNGLDELETEQUERIESEXTPROC) load(userptr, "glDeleteQueriesEXT");
    glad_glEndQueryEXT = (PFNGLENDQUERYEXTPROC) load(userptr, "glEndQueryEXT");
    glad_glGenQueriesEXT = (PFNGLGENQUERIESEXTPROC) load(userptr, "glGenQueriesEXT");
    glad_glGetInteger64vEXT = (PFNGLGETINTEGER64VEXTPROC) load(userptr, "glGetInteger64vEXT");
    glad_glGetQueryObjecti64vEXT = (PFNGLGETQUERYOBJECTI64VEXTPROC) load(userptr, "glGetQueryObjecti64vEXT");
    glad_glGetQueryObjectivEXT = (PFNGLGETQUERYOBJECTIVEXTPROC) load(userptr, "glGetQueryObjectivEXT");
    glad_glGetQueryObjectui64vEXT = (PFNGLGETQUERYOBJECTUI64VEXTPROC) load(userptr, "glGetQueryObjectui64vEXT");
    glad_glGetQueryObjectuivEXT = (PFNGLGETQUERYOBJECTUIVEXTPROC) load(userptr, "glGetQueryObjectuivEXT");
    glad_glGetQueryivEXT = (PFNGLGETQUERYIVEXTPROC) load(userptr, "glGetQueryivEXT");
    glad_glIsQueryEXT = (PFNGLISQUERYEXTPROC) load(userptr, "glIsQueryEXT");
    glad_glQueryCounterEXT = (PFNGLQUERYCOUNTEREXTPROC) load(userptr, "glQueryCounterEXT");
}
static void glad_gl_load_GL_EXT_draw_buffers( GLADuserptrloadfunc load, void* userptr) {
    if(!GLAD_GL_EXT_draw_buffers) return;
    glad_glDrawBuffersEXT = (PFNGLDRAWBUFFERSEXTPROC) load(userptr, "glDrawBuffersEXT");
}
static void glad_gl_load_GL_EXT_draw_buffers_indexed( GLADuserptrloadfunc load, void* userptr) {
    if(!GLAD_GL_EXT_draw_buffers_indexed) return;
    glad_glBlendEquationSeparateiEXT = (PFNGLBLENDEQUATIONSEPARATEIEXTPROC) load(userptr, "glBlendEquationSeparateiEXT");
    glad_glBlendEquationiEXT = (PFNGLBLENDEQUATIONIEXTPROC) load(userptr, "glBlendEquationiEXT");
    glad_glBlendFuncSeparateiEXT = (PFNGLBLENDFUNCSEPARATEIEXTPROC) load(userptr, "glBlendFuncSeparateiEXT");
    glad_glBlendFunciEXT = (PFNGLBLENDFUNCIEXTPROC) load(userptr, "glBlendFunciEXT");
    glad_glColorMaskiEXT = (PFNGLCOLORMASKIEXTPROC) load(userptr, "glColorMaskiEXT");
    glad_glDisableiEXT = (PFNGLDISABLEIEXTPROC) load(userptr, "glDisableiEXT");
    glad_glEnableiEXT = (PFNGLENABLEIEXTPROC) load(userptr, "glEnableiEXT");
    glad_glIsEnablediEXT = (PFNGLISENABLEDIEXTPROC) load(userptr, "glIsEnablediEXT");
}
static void glad_gl_load_GL_EXT_draw_elements_base_vertex( GLADuserptrloadfunc load, void* userptr) {
    if(!GLAD_GL_EXT_draw_elements_base_vertex) return;
    glad_glDrawElementsBaseVertexEXT = (PFNGLDRAWELEMENTSBASEVERTEXEXTPROC) load(userptr, "glDrawElementsBaseVertexEXT");
    glad_glDrawElementsInstancedBaseVertexEXT = (PFNGLDRAWELEMENTSINSTANCEDBASEVERTEXEXTPROC) load(userptr, "glDrawElementsInstancedBaseVertexEXT");
    glad_glDrawRangeElementsBaseVertexEXT = (PFNGLDRAWRANGEELEMENTSBASEVERTEXEXTPROC) load(userptr, "glDrawRangeElementsBaseVertexEXT");
    glad_glMultiDrawElementsBaseVertexEXT = (PFNGLMULTIDRAWELEMENTSBASEVERTEXEXTPROC) load(userptr, "glMultiDrawElementsBaseVertexEXT");
}
static void glad_gl_load_GL_EXT_draw_instanced( GLADuserptrloadfunc load, void* userptr) {
    if(!GLAD_GL_EXT_draw_instanced) return;
    glad_glDrawArraysInstancedEXT = (PFNGLDRAWARRAYSINSTANCEDEXTPROC) load(userptr, "glDrawArraysInstancedEXT");
    glad_glDrawElementsInstancedEXT = (PFNGLDRAWELEMENTSINSTANCEDEXTPROC) load(userptr, "glDrawElementsInstancedEXT");
}
static void glad_gl_load_GL_EXT_draw_transform_feedback( GLADuserptrloadfunc load, void* userptr) {
    if(!GLAD_GL_EXT_draw_transform_feedback) return;
    glad_glDrawTransformFeedbackEXT = (PFNGLDRAWTRANSFORMFEEDBACKEXTPROC) load(userptr, "glDrawTransformFeedbackEXT");
    glad_glDrawTransformFeedbackInstancedEXT = (PFNGLDRAWTRANSFORMFEEDBACKINSTANCEDEXTPROC) load(userptr, "glDrawTransformFeedbackInstancedEXT");
}
static void glad_gl_load_GL_EXT_external_buffer( GLADuserptrloadfunc load, void* userptr) {
    if(!GLAD_GL_EXT_external_buffer) return;
    glad_glBufferStorageExternalEXT = (PFNGLBUFFERSTORAGEEXTERNALEXTPROC) load(userptr, "glBufferStorageExternalEXT");
    glad_glNamedBufferStorageExternalEXT = (PFNGLNAMEDBUFFERSTORAGEEXTERNALEXTPROC) load(userptr, "glNamedBufferStorageExternalEXT");
}
static void glad_gl_load_GL_EXT_fragment_shading_rate( GLADuserptrloadfunc load, void* userptr) {
    if(!GLAD_GL_EXT_fragment_shading_rate) return;
    glad_glFramebufferShadingRateEXT = (PFNGLFRAMEBUFFERSHADINGRATEEXTPROC) load(userptr, "glFramebufferShadingRateEXT");
    glad_glGetFragmentShadingRatesEXT = (PFNGLGETFRAGMENTSHADINGRATESEXTPROC) load(userptr, "glGetFragmentShadingRatesEXT");
    glad_glShadingRateCombinerOpsEXT = (PFNGLSHADINGRATECOMBINEROPSEXTPROC) load(userptr, "glShadingRateCombinerOpsEXT");
    glad_glShadingRateEXT = (PFNGLSHADINGRATEEXTPROC) load(userptr, "glShadingRateEXT");
}
static void glad_gl_load_GL_EXT_geometry_shader( GLADuserptrloadfunc load, void* userptr) {
    if(!GLAD_GL_EXT_geometry_shader) return;
    glad_glFramebufferTextureEXT = (PFNGLFRAMEBUFFERTEXTUREEXTPROC) load(userptr, "glFramebufferTextureEXT");
}
static void glad_gl_load_GL_EXT_instanced_arrays( GLADuserptrloadfunc load, void* userptr) {
    if(!GLAD_GL_EXT_instanced_arrays) return;
    glad_glDrawArraysInstancedEXT = (PFNGLDRAWARRAYSINSTANCEDEXTPROC) load(userptr, "glDrawArraysInstancedEXT");
    glad_glDrawElementsInstancedEXT = (PFNGLDRAWELEMENTSINSTANCEDEXTPROC) load(userptr, "glDrawElementsInstancedEXT");
    glad_glVertexAttribDivisorEXT = (PFNGLVERTEXATTRIBDIVISOREXTPROC) load(userptr, "glVertexAttribDivisorEXT");
}
static void glad_gl_load_GL_EXT_map_buffer_range( GLADuserptrloadfunc load, void* userptr) {
    if(!GLAD_GL_EXT_map_buffer_range) return;
    glad_glFlushMappedBufferRangeEXT = (PFNGLFLUSHMAPPEDBUFFERRANGEEXTPROC) load(userptr, "glFlushMappedBufferRangeEXT");
    glad_glMapBufferRangeEXT = (PFNGLMAPBUFFERRANGEEXTPROC) load(userptr, "glMapBufferRangeEXT");
}
static void glad_gl_load_GL_EXT_memory_object( GLADuserptrloadfunc load, void* userptr) {
    if(!GLAD_GL_EXT_memory_object) return;
    glad_glBufferStorageMemEXT = (PFNGLBUFFERSTORAGEMEMEXTPROC) load(userptr, "glBufferStorageMemEXT");
    glad_glCreateMemoryObjectsEXT = (PFNGLCREATEMEMORYOBJECTSEXTPROC) load(userptr, "glCreateMemoryObjectsEXT");
    glad_glDeleteMemoryObjectsEXT = (PFNGLDELETEMEMORYOBJECTSEXTPROC) load(userptr, "glDeleteMemoryObjectsEXT");
    glad_glGetMemoryObjectParameterivEXT = (PFNGLGETMEMORYOBJECTPARAMETERIVEXTPROC) load(userptr, "glGetMemoryObjectParameterivEXT");
    glad_glGetUnsignedBytei_vEXT = (PFNGLGETUNSIGNEDBYTEI_VEXTPROC) load(userptr, "glGetUnsignedBytei_vEXT");
    glad_glGetUnsignedBytevEXT = (PFNGLGETUNSIGNEDBYTEVEXTPROC) load(userptr, "glGetUnsignedBytevEXT");
    glad_glIsMemoryObjectEXT = (PFNGLISMEMORYOBJECTEXTPROC) load(userptr, "glIsMemoryObjectEXT");
    glad_glMemoryObjectParameterivEXT = (PFNGLMEMORYOBJECTPARAMETERIVEXTPROC) load(userptr, "glMemoryObjectParameterivEXT");
    glad_glNamedBufferStorageMemEXT = (PFNGLNAMEDBUFFERSTORAGEMEMEXTPROC) load(userptr, "glNamedBufferStorageMemEXT");
    glad_glTexStorageMem2DEXT = (PFNGLTEXSTORAGEMEM2DEXTPROC) load(userptr, "glTexStorageMem2DEXT");
    glad_glTexStorageMem2DMultisampleEXT = (PFNGLTEXSTORAGEMEM2DMULTISAMPLEEXTPROC) load(userptr, "glTexStorageMem2DMultisampleEXT");
    glad_glTexStorageMem3DEXT = (PFNGLTEXSTORAGEMEM3DEXTPROC) load(userptr, "glTexStorageMem3DEXT");
    glad_glTexStorageMem3DMultisampleEXT = (PFNGLTEXSTORAGEMEM3DMULTISAMPLEEXTPROC) load(userptr, "glTexStorageMem3DMultisampleEXT");
    glad_glTextureStorageMem2DEXT = (PFNGLTEXTURESTORAGEMEM2DEXTPROC) load(userptr, "glTextureStorageMem2DEXT");
    glad_glTextureStorageMem2DMultisampleEXT = (PFNGLTEXTURESTORAGEMEM2DMULTISAMPLEEXTPROC) load(userptr, "glTextureStorageMem2DMultisampleEXT");
    glad_glTextureStorageMem3DEXT = (PFNGLTEXTURESTORAGEMEM3DEXTPROC) load(userptr, "glTextureStorageMem3DEXT");
    glad_glTextureStorageMem3DMultisampleEXT = (PFNGLTEXTURESTORAGEMEM3DMULTISAMPLEEXTPROC) load(userptr, "glTextureStorageMem3DMultisampleEXT");
}
static void glad_gl_load_GL_EXT_memory_object_fd( GLADuserptrloadfunc load, void* userptr) {
    if(!GLAD_GL_EXT_memory_object_fd) return;
    glad_glImportMemoryFdEXT = (PFNGLIMPORTMEMORYFDEXTPROC) load(userptr, "glImportMemoryFdEXT");
}
static void glad_gl_load_GL_EXT_memory_object_win32( GLADuserptrloadfunc load, void* userptr) {
    if(!GLAD_GL_EXT_memory_object_win32) return;
    glad_glImportMemoryWin32HandleEXT = (PFNGLIMPORTMEMORYWIN32HANDLEEXTPROC) load(userptr, "glImportMemoryWin32HandleEXT");
    glad_glImportMemoryWin32NameEXT = (PFNGLIMPORTMEMORYWIN32NAMEEXTPROC) load(userptr, "glImportMemoryWin32NameEXT");
}
static void glad_gl_load_GL_EXT_multi_draw_arrays( GLADuserptrloadfunc load, void* userptr) {
    if(!GLAD_GL_EXT_multi_draw_arrays) return;
    glad_glMultiDrawArraysEXT = (PFNGLMULTIDRAWARRAYSEXTPROC) load(userptr, "glMultiDrawArraysEXT");
    glad_glMultiDrawElementsEXT = (PFNGLMULTIDRAWELEMENTSEXTPROC) load(userptr, "glMultiDrawElementsEXT");
}
static void glad_gl_load_GL_EXT_multi_draw_indirect( GLADuserptrloadfunc load, void* userptr) {
    if(!GLAD_GL_EXT_multi_draw_indirect) return;
    glad_glMultiDrawArraysIndirectEXT = (PFNGLMULTIDRAWARRAYSINDIRECTEXTPROC) load(userptr, "glMultiDrawArraysIndirectEXT");
    glad_glMultiDrawElementsIndirectEXT = (PFNGLMULTIDRAWELEMENTSINDIRECTEXTPROC) load(userptr, "glMultiDrawElementsIndirectEXT");
}
static void glad_gl_load_GL_EXT_multisampled_render_to_texture( GLADuserptrloadfunc load, void* userptr) {
    if(!GLAD_GL_EXT_multisampled_render_to_texture) return;
    glad_glFramebufferTexture2DMultisampleEXT = (PFNGLFRAMEBUFFERTEXTURE2DMULTISAMPLEEXTPROC) load(userptr, "glFramebufferTexture2DMultisampleEXT");
    glad_glRenderbufferStorageMultisampleEXT = (PFNGLRENDERBUFFERSTORAGEMULTISAMPLEEXTPROC) load(userptr, "glRenderbufferStorageMultisampleEXT");
}
static void glad_gl_load_GL_EXT_multiview_draw_buffers( GLADuserptrloadfunc load, void* userptr) {
    if(!GLAD_GL_EXT_multiview_draw_buffers) return;
    glad_glDrawBuffersIndexedEXT = (PFNGLDRAWBUFFERSINDEXEDEXTPROC) load(userptr, "glDrawBuffersIndexedEXT");
    glad_glGetIntegeri_vEXT = (PFNGLGETINTEGERI_VEXTPROC) load(userptr, "glGetIntegeri_vEXT");
    glad_glReadBufferIndexedEXT = (PFNGLREADBUFFERINDEXEDEXTPROC) load(userptr, "glReadBufferIndexedEXT");
}
static void glad_gl_load_GL_EXT_occlusion_query_boolean( GLADuserptrloadfunc load, void* userptr) {
    if(!GLAD_GL_EXT_occlusion_query_boolean) return;
    glad_glBeginQueryEXT = (PFNGLBEGINQUERYEXTPROC) load(userptr, "glBeginQueryEXT");
    glad_glDeleteQueriesEXT = (PFNGLDELETEQUERIESEXTPROC) load(userptr, "glDeleteQueriesEXT");
    glad_glEndQueryEXT = (PFNGLENDQUERYEXTPROC) load(userptr, "glEndQueryEXT");
    glad_glGenQueriesEXT = (PFNGLGENQUERIESEXTPROC) load(userptr, "glGenQueriesEXT");
    glad_glGetQueryObjectuivEXT = (PFNGLGETQUERYOBJECTUIVEXTPROC) load(userptr, "glGetQueryObjectuivEXT");
    glad_glGetQueryivEXT = (PFNGLGETQUERYIVEXTPROC) load(userptr, "glGetQueryivEXT");
    glad_glIsQueryEXT = (PFNGLISQUERYEXTPROC) load(userptr, "glIsQueryEXT");
}
static void glad_gl_load_GL_EXT_polygon_offset_clamp( GLADuserptrloadfunc load, void* userptr) {
    if(!GLAD_GL_EXT_polygon_offset_clamp) return;
    glad_glPolygonOffsetClampEXT = (PFNGLPOLYGONOFFSETCLAMPEXTPROC) load(userptr, "glPolygonOffsetClampEXT");
}
static void glad_gl_load_GL_EXT_primitive_bounding_box( GLADuserptrloadfunc load, void* userptr) {
    if(!GLAD_GL_EXT_primitive_bounding_box) return;
    glad_glPrimitiveBoundingBoxEXT = (PFNGLPRIMITIVEBOUNDINGBOXEXTPROC) load(userptr, "glPrimitiveBoundingBoxEXT");
}
static void glad_gl_load_GL_EXT_raster_multisample( GLADuserptrloadfunc load, void* userptr) {
    if(!GLAD_GL_EXT_raster_multisample) return;
    glad_glRasterSamplesEXT = (PFNGLRASTERSAMPLESEXTPROC) load(userptr, "glRasterSamplesEXT");
}
static void glad_gl_load_GL_EXT_robustness( GLADuserptrloadfunc load, void* userptr) {
    if(!GLAD_GL_EXT_robustness) return;
    glad_glGetGraphicsResetStatusEXT = (PFNGLGETGRAPHICSRESETSTATUSEXTPROC) load(userptr, "glGetGraphicsResetStatusEXT");
    glad_glGetnUniformfvEXT = (PFNGLGETNUNIFORMFVEXTPROC) load(userptr, "glGetnUniformfvEXT");
    glad_glGetnUniformivEXT = (PFNGLGETNUNIFORMIVEXTPROC) load(userptr, "glGetnUniformivEXT");
    glad_glReadnPixelsEXT = (PFNGLREADNPIXELSEXTPROC) load(userptr, "glReadnPixelsEXT");
}
static void glad_gl_load_GL_EXT_semaphore( GLADuserptrloadfunc load, void* userptr) {
    if(!GLAD_GL_EXT_semaphore) return;
    glad_glDeleteSemaphoresEXT = (PFNGLDELETESEMAPHORESEXTPROC) load(userptr, "glDeleteSemaphoresEXT");
    glad_glGenSemaphoresEXT = (PFNGLGENSEMAPHORESEXTPROC) load(userptr, "glGenSemaphoresEXT");
    glad_glGetSemaphoreParameterui64vEXT = (PFNGLGETSEMAPHOREPARAMETERUI64VEXTPROC) load(userptr, "glGetSemaphoreParameterui64vEXT");
    glad_glGetUnsignedBytei_vEXT = (PFNGLGETUNSIGNEDBYTEI_VEXTPROC) load(userptr, "glGetUnsignedBytei_vEXT");
    glad_glGetUnsignedBytevEXT = (PFNGLGETUNSIGNEDBYTEVEXTPROC) load(userptr, "glGetUnsignedBytevEXT");
    glad_glIsSemaphoreEXT = (PFNGLISSEMAPHOREEXTPROC) load(userptr, "glIsSemaphoreEXT");
    glad_glSemaphoreParameterui64vEXT = (PFNGLSEMAPHOREPARAMETERUI64VEXTPROC) load(userptr, "glSemaphoreParameterui64vEXT");
    glad_glSignalSemaphoreEXT = (PFNGLSIGNALSEMAPHOREEXTPROC) load(userptr, "glSignalSemaphoreEXT");
    glad_glWaitSemaphoreEXT = (PFNGLWAITSEMAPHOREEXTPROC) load(userptr, "glWaitSemaphoreEXT");
}
static void glad_gl_load_GL_EXT_semaphore_fd( GLADuserptrloadfunc load, void* userptr) {
    if(!GLAD_GL_EXT_semaphore_fd) return;
    glad_glImportSemaphoreFdEXT = (PFNGLIMPORTSEMAPHOREFDEXTPROC) load(userptr, "glImportSemaphoreFdEXT");
}
static void glad_gl_load_GL_EXT_semaphore_win32( GLADuserptrloadfunc load, void* userptr) {
    if(!GLAD_GL_EXT_semaphore_win32) return;
    glad_glImportSemaphoreWin32HandleEXT = (PFNGLIMPORTSEMAPHOREWIN32HANDLEEXTPROC) load(userptr, "glImportSemaphoreWin32HandleEXT");
    glad_glImportSemaphoreWin32NameEXT = (PFNGLIMPORTSEMAPHOREWIN32NAMEEXTPROC) load(userptr, "glImportSemaphoreWin32NameEXT");
}
static void glad_gl_load_GL_EXT_separate_shader_objects( GLADuserptrloadfunc load, void* userptr) {
    if(!GLAD_GL_EXT_separate_shader_objects) return;
    glad_glActiveShaderProgramEXT = (PFNGLACTIVESHADERPROGRAMEXTPROC) load(userptr, "glActiveShaderProgramEXT");
    glad_glBindProgramPipelineEXT = (PFNGLBINDPROGRAMPIPELINEEXTPROC) load(userptr, "glBindProgramPipelineEXT");
    glad_glCreateShaderProgramvEXT = (PFNGLCREATESHADERPROGRAMVEXTPROC) load(userptr, "glCreateShaderProgramvEXT");
    glad_glDeleteProgramPipelinesEXT = (PFNGLDELETEPROGRAMPIPELINESEXTPROC) load(userptr, "glDeleteProgramPipelinesEXT");
    glad_glGenProgramPipelinesEXT = (PFNGLGENPROGRAMPIPELINESEXTPROC) load(userptr, "glGenProgramPipelinesEXT");
    glad_glGetProgramPipelineInfoLogEXT = (PFNGLGETPROGRAMPIPELINEINFOLOGEXTPROC) load(userptr, "glGetProgramPipelineInfoLogEXT");
    glad_glGetProgramPipelineivEXT = (PFNGLGETPROGRAMPIPELINEIVEXTPROC) load(userptr, "glGetProgramPipelineivEXT");
    glad_glIsProgramPipelineEXT = (PFNGLISPROGRAMPIPELINEEXTPROC) load(userptr, "glIsProgramPipelineEXT");
    glad_glProgramParameteriEXT = (PFNGLPROGRAMPARAMETERIEXTPROC) load(userptr, "glProgramParameteriEXT");
    glad_glProgramUniform1fEXT = (PFNGLPROGRAMUNIFORM1FEXTPROC) load(userptr, "glProgramUniform1fEXT");
    glad_glProgramUniform1fvEXT = (PFNGLPROGRAMUNIFORM1FVEXTPROC) load(userptr, "glProgramUniform1fvEXT");
    glad_glProgramUniform1iEXT = (PFNGLPROGRAMUNIFORM1IEXTPROC) load(userptr, "glProgramUniform1iEXT");
    glad_glProgramUniform1ivEXT = (PFNGLPROGRAMUNIFORM1IVEXTPROC) load(userptr, "glProgramUniform1ivEXT");
    glad_glProgramUniform1uiEXT = (PFNGLPROGRAMUNIFORM1UIEXTPROC) load(userptr, "glProgramUniform1uiEXT");
    glad_glProgramUniform1uivEXT = (PFNGLPROGRAMUNIFORM1UIVEXTPROC) load(userptr, "glProgramUniform1uivEXT");
    glad_glProgramUniform2fEXT = (PFNGLPROGRAMUNIFORM2FEXTPROC) load(userptr, "glProgramUniform2fEXT");
    glad_glProgramUniform2fvEXT = (PFNGLPROGRAMUNIFORM2FVEXTPROC) load(userptr, "glProgramUniform2fvEXT");
    glad_glProgramUniform2iEXT = (PFNGLPROGRAMUNIFORM2IEXTPROC) load(userptr, "glProgramUniform2iEXT");
    glad_glProgramUniform2ivEXT = (PFNGLPROGRAMUNIFORM2IVEXTPROC) load(userptr, "glProgramUniform2ivEXT");
    glad_glProgramUniform2uiEXT = (PFNGLPROGRAMUNIFORM2UIEXTPROC) load(userptr, "glProgramUniform2uiEXT");
    glad_glProgramUniform2uivEXT = (PFNGLPROGRAMUNIFORM2UIVEXTPROC) load(userptr, "glProgramUniform2uivEXT");
    glad_glProgramUniform3fEXT = (PFNGLPROGRAMUNIFORM3FEXTPROC) load(userptr, "glProgramUniform3fEXT");
    glad_glProgramUniform3fvEXT = (PFNGLPROGRAMUNIFORM3FVEXTPROC) load(userptr, "glProgramUniform3fvEXT");
    glad_glProgramUniform3iEXT = (PFNGLPROGRAMUNIFORM3IEXTPROC) load(userptr, "glProgramUniform3iEXT");
    glad_glProgramUniform3ivEXT = (PFNGLPROGRAMUNIFORM3IVEXTPROC) load(userptr, "glProgramUniform3ivEXT");
    glad_glProgramUniform3uiEXT = (PFNGLPROGRAMUNIFORM3UIEXTPROC) load(userptr, "glProgramUniform3uiEXT");
    glad_glProgramUniform3uivEXT = (PFNGLPROGRAMUNIFORM3UIVEXTPROC) load(userptr, "glProgramUniform3uivEXT");
    glad_glProgramUniform4fEXT = (PFNGLPROGRAMUNIFORM4FEXTPROC) load(userptr, "glProgramUniform4fEXT");
    glad_glProgramUniform4fvEXT = (PFNGLPROGRAMUNIFORM4FVEXTPROC) load(userptr, "glProgramUniform4fvEXT");
    glad_glProgramUniform4iEXT = (PFNGLPROGRAMUNIFORM4IEXTPROC) load(userptr, "glProgramUniform4iEXT");
    glad_glProgramUniform4ivEXT = (PFNGLPROGRAMUNIFORM4IVEXTPROC) load(userptr, "glProgramUniform4ivEXT");
    glad_glProgramUniform4uiEXT = (PFNGLPROGRAMUNIFORM4UIEXTPROC) load(userptr, "glProgramUniform4uiEXT");
    glad_glProgramUniform4uivEXT = (PFNGLPROGRAMUNIFORM4UIVEXTPROC) load(userptr, "glProgramUniform4uivEXT");
    glad_glProgramUniformMatrix2fvEXT = (PFNGLPROGRAMUNIFORMMATRIX2FVEXTPROC) load(userptr, "glProgramUniformMatrix2fvEXT");
    glad_glProgramUniformMatrix2x3fvEXT = (PFNGLPROGRAMUNIFORMMATRIX2X3FVEXTPROC) load(userptr, "glProgramUniformMatrix2x3fvEXT");
    glad_glProgramUniformMatrix2x4fvEXT = (PFNGLPROGRAMUNIFORMMATRIX2X4FVEXTPROC) load(userptr, "glProgramUniformMatrix2x4fvEXT");
    glad_glProgramUniformMatrix3fvEXT = (PFNGLPROGRAMUNIFORMMATRIX3FVEXTPROC) load(userptr, "glProgramUniformMatrix3fvEXT");
    glad_glProgramUniformMatrix3x2fvEXT = (PFNGLPROGRAMUNIFORMMATRIX3X2FVEXTPROC) load(userptr, "glProgramUniformMatrix3x2fvEXT");
    glad_glProgramUniformMatrix3x4fvEXT = (PFNGLPROGRAMUNIFORMMATRIX3X4FVEXTPROC) load(userptr, "glProgramUniformMatrix3x4fvEXT");
    glad_glProgramUniformMatrix4fvEXT = (PFNGLPROGRAMUNIFORMMATRIX4FVEXTPROC) load(userptr, "glProgramUniformMatrix4fvEXT");
    glad_glProgramUniformMatrix4x2fvEXT = (PFNGLPROGRAMUNIFORMMATRIX4X2FVEXTPROC) load(userptr, "glProgramUniformMatrix4x2fvEXT");
    glad_glProgramUniformMatrix4x3fvEXT = (PFNGLPROGRAMUNIFORMMATRIX4X3FVEXTPROC) load(userptr, "glProgramUniformMatrix4x3fvEXT");
    glad_glUseProgramStagesEXT = (PFNGLUSEPROGRAMSTAGESEXTPROC) load(userptr, "glUseProgramStagesEXT");
    glad_glValidateProgramPipelineEXT = (PFNGLVALIDATEPROGRAMPIPELINEEXTPROC) load(userptr, "glValidateProgramPipelineEXT");
}
static void glad_gl_load_GL_EXT_shader_framebuffer_fetch_non_coherent( GLADuserptrloadfunc load, void* userptr) {
    if(!GLAD_GL_EXT_shader_framebuffer_fetch_non_coherent) return;
    glad_glFramebufferFetchBarrierEXT = (PFNGLFRAMEBUFFERFETCHBARRIEREXTPROC) load(userptr, "glFramebufferFetchBarrierEXT");
}
static void glad_gl_load_GL_EXT_shader_pixel_local_storage2( GLADuserptrloadfunc load, void* userptr) {
    if(!GLAD_GL_EXT_shader_pixel_local_storage2) return;
    glad_glClearPixelLocalStorageuiEXT = (PFNGLCLEARPIXELLOCALSTORAGEUIEXTPROC) load(userptr, "glClearPixelLocalStorageuiEXT");
    glad_glFramebufferPixelLocalStorageSizeEXT = (PFNGLFRAMEBUFFERPIXELLOCALSTORAGESIZEEXTPROC) load(userptr, "glFramebufferPixelLocalStorageSizeEXT");
    glad_glGetFramebufferPixelLocalStorageSizeEXT = (PFNGLGETFRAMEBUFFERPIXELLOCALSTORAGESIZEEXTPROC) load(userptr, "glGetFramebufferPixelLocalStorageSizeEXT");
}
static void glad_gl_load_GL_EXT_sparse_texture( GLADuserptrloadfunc load, void* userptr) {
    if(!GLAD_GL_EXT_sparse_texture) return;
    glad_glTexPageCommitmentEXT = (PFNGLTEXPAGECOMMITMENTEXTPROC) load(userptr, "glTexPageCommitmentEXT");
}
static void glad_gl_load_GL_EXT_tessellation_shader( GLADuserptrloadfunc load, void* userptr) {
    if(!GLAD_GL_EXT_tessellation_shader) return;
    glad_glPatchParameteriEXT = (PFNGLPATCHPARAMETERIEXTPROC) load(userptr, "glPatchParameteriEXT");
}
static void glad_gl_load_GL_EXT_texture_border_clamp( GLADuserptrloadfunc load, void* userptr) {
    if(!GLAD_GL_EXT_texture_border_clamp) return;
    glad_glGetSamplerParameterIivEXT = (PFNGLGETSAMPLERPARAMETERIIVEXTPROC) load(userptr, "glGetSamplerParameterIivEXT");
    glad_glGetSamplerParameterIuivEXT = (PFNGLGETSAMPLERPARAMETERIUIVEXTPROC) load(userptr, "glGetSamplerParameterIuivEXT");
    glad_glGetTexParameterIivEXT = (PFNGLGETTEXPARAMETERIIVEXTPROC) load(userptr, "glGetTexParameterIivEXT");
    glad_glGetTexParameterIuivEXT = (PFNGLGETTEXPARAMETERIUIVEXTPROC) load(userptr, "glGetTexParameterIuivEXT");
    glad_glSamplerParameterIivEXT = (PFNGLSAMPLERPARAMETERIIVEXTPROC) load(userptr, "glSamplerParameterIivEXT");
    glad_glSamplerParameterIuivEXT = (PFNGLSAMPLERPARAMETERIUIVEXTPROC) load(userptr, "glSamplerParameterIuivEXT");
    glad_glTexParameterIivEXT = (PFNGLTEXPARAMETERIIVEXTPROC) load(userptr, "glTexParameterIivEXT");
    glad_glTexParameterIuivEXT = (PFNGLTEXPARAMETERIUIVEXTPROC) load(userptr, "glTexParameterIuivEXT");
}
static void glad_gl_load_GL_EXT_texture_buffer( GLADuserptrloadfunc load, void* userptr) {
    if(!GLAD_GL_EXT_texture_buffer) return;
    glad_glTexBufferEXT = (PFNGLTEXBUFFEREXTPROC) load(userptr, "glTexBufferEXT");
    glad_glTexBufferRangeEXT = (PFNGLTEXBUFFERRANGEEXTPROC) load(userptr, "glTexBufferRangeEXT");
}
static void glad_gl_load_GL_EXT_texture_storage( GLADuserptrloadfunc load, void* userptr) {
    if(!GLAD_GL_EXT_texture_storage) return;
    glad_glTexStorage1DEXT = (PFNGLTEXSTORAGE1DEXTPROC) load(userptr, "glTexStorage1DEXT");
    glad_glTexStorage2DEXT = (PFNGLTEXSTORAGE2DEXTPROC) load(userptr, "glTexStorage2DEXT");
    glad_glTexStorage3DEXT = (PFNGLTEXSTORAGE3DEXTPROC) load(userptr, "glTexStorage3DEXT");
    glad_glTextureStorage1DEXT = (PFNGLTEXTURESTORAGE1DEXTPROC) load(userptr, "glTextureStorage1DEXT");
    glad_glTextureStorage2DEXT = (PFNGLTEXTURESTORAGE2DEXTPROC) load(userptr, "glTextureStorage2DEXT");
    glad_glTextureStorage3DEXT = (PFNGLTEXTURESTORAGE3DEXTPROC) load(userptr, "glTextureStorage3DEXT");
}
static void glad_gl_load_GL_EXT_texture_storage_compression( GLADuserptrloadfunc load, void* userptr) {
    if(!GLAD_GL_EXT_texture_storage_compression) return;
    glad_glTexStorageAttribs2DEXT = (PFNGLTEXSTORAGEATTRIBS2DEXTPROC) load(userptr, "glTexStorageAttribs2DEXT");
    glad_glTexStorageAttribs3DEXT = (PFNGLTEXSTORAGEATTRIBS3DEXTPROC) load(userptr, "glTexStorageAttribs3DEXT");
}
static void glad_gl_load_GL_EXT_texture_view( GLADuserptrloadfunc load, void* userptr) {
    if(!GLAD_GL_EXT_texture_view) return;
    glad_glTextureViewEXT = (PFNGLTEXTUREVIEWEXTPROC) load(userptr, "glTextureViewEXT");
}
static void glad_gl_load_GL_EXT_win32_keyed_mutex( GLADuserptrloadfunc load, void* userptr) {
    if(!GLAD_GL_EXT_win32_keyed_mutex) return;
    glad_glAcquireKeyedMutexWin32EXT = (PFNGLACQUIREKEYEDMUTEXWIN32EXTPROC) load(userptr, "glAcquireKeyedMutexWin32EXT");
    glad_glReleaseKeyedMutexWin32EXT = (PFNGLRELEASEKEYEDMUTEXWIN32EXTPROC) load(userptr, "glReleaseKeyedMutexWin32EXT");
}
static void glad_gl_load_GL_EXT_window_rectangles( GLADuserptrloadfunc load, void* userptr) {
    if(!GLAD_GL_EXT_window_rectangles) return;
    glad_glWindowRectanglesEXT = (PFNGLWINDOWRECTANGLESEXTPROC) load(userptr, "glWindowRectanglesEXT");
}
static void glad_gl_load_GL_IMG_bindless_texture( GLADuserptrloadfunc load, void* userptr) {
    if(!GLAD_GL_IMG_bindless_texture) return;
    glad_glGetTextureHandleIMG = (PFNGLGETTEXTUREHANDLEIMGPROC) load(userptr, "glGetTextureHandleIMG");
    glad_glGetTextureSamplerHandleIMG = (PFNGLGETTEXTURESAMPLERHANDLEIMGPROC) load(userptr, "glGetTextureSamplerHandleIMG");
    glad_glProgramUniformHandleui64IMG = (PFNGLPROGRAMUNIFORMHANDLEUI64IMGPROC) load(userptr, "glProgramUniformHandleui64IMG");
    glad_glProgramUniformHandleui64vIMG = (PFNGLPROGRAMUNIFORMHANDLEUI64VIMGPROC) load(userptr, "glProgramUniformHandleui64vIMG");
    glad_glUniformHandleui64IMG = (PFNGLUNIFORMHANDLEUI64IMGPROC) load(userptr, "glUniformHandleui64IMG");
    glad_glUniformHandleui64vIMG = (PFNGLUNIFORMHANDLEUI64VIMGPROC) load(userptr, "glUniformHandleui64vIMG");
}
static void glad_gl_load_GL_IMG_framebuffer_downsample( GLADuserptrloadfunc load, void* userptr) {
    if(!GLAD_GL_IMG_framebuffer_downsample) return;
    glad_glFramebufferTexture2DDownsampleIMG = (PFNGLFRAMEBUFFERTEXTURE2DDOWNSAMPLEIMGPROC) load(userptr, "glFramebufferTexture2DDownsampleIMG");
    glad_glFramebufferTextureLayerDownsampleIMG = (PFNGLFRAMEBUFFERTEXTURELAYERDOWNSAMPLEIMGPROC) load(userptr, "glFramebufferTextureLayerDownsampleIMG");
}
static void glad_gl_load_GL_IMG_multisampled_render_to_texture( GLADuserptrloadfunc load, void* userptr) {
    if(!GLAD_GL_IMG_multisampled_render_to_texture) return;
    glad_glFramebufferTexture2DMultisampleIMG = (PFNGLFRAMEBUFFERTEXTURE2DMULTISAMPLEIMGPROC) load(userptr, "glFramebufferTexture2DMultisampleIMG");
    glad_glRenderbufferStorageMultisampleIMG = (PFNGLRENDERBUFFERSTORAGEMULTISAMPLEIMGPROC) load(userptr, "glRenderbufferStorageMultisampleIMG");
}
static void glad_gl_load_GL_INTEL_framebuffer_CMAA( GLADuserptrloadfunc load, void* userptr) {
    if(!GLAD_GL_INTEL_framebuffer_CMAA) return;
    glad_glApplyFramebufferAttachmentCMAAINTEL = (PFNGLAPPLYFRAMEBUFFERATTACHMENTCMAAINTELPROC) load(userptr, "glApplyFramebufferAttachmentCMAAINTEL");
}
static void glad_gl_load_GL_INTEL_performance_query( GLADuserptrloadfunc load, void* userptr) {
    if(!GLAD_GL_INTEL_performance_query) return;
    glad_glBeginPerfQueryINTEL = (PFNGLBEGINPERFQUERYINTELPROC) load(userptr, "glBeginPerfQueryINTEL");
    glad_glCreatePerfQueryINTEL = (PFNGLCREATEPERFQUERYINTELPROC) load(userptr, "glCreatePerfQueryINTEL");
    glad_glDeletePerfQueryINTEL = (PFNGLDELETEPERFQUERYINTELPROC) load(userptr, "glDeletePerfQueryINTEL");
    glad_glEndPerfQueryINTEL = (PFNGLENDPERFQUERYINTELPROC) load(userptr, "glEndPerfQueryINTEL");
    glad_glGetFirstPerfQueryIdINTEL = (PFNGLGETFIRSTPERFQUERYIDINTELPROC) load(userptr, "glGetFirstPerfQueryIdINTEL");
    glad_glGetNextPerfQueryIdINTEL = (PFNGLGETNEXTPERFQUERYIDINTELPROC) load(userptr, "glGetNextPerfQueryIdINTEL");
    glad_glGetPerfCounterInfoINTEL = (PFNGLGETPERFCOUNTERINFOINTELPROC) load(userptr, "glGetPerfCounterInfoINTEL");
    glad_glGetPerfQueryDataINTEL = (PFNGLGETPERFQUERYDATAINTELPROC) load(userptr, "glGetPerfQueryDataINTEL");
    glad_glGetPerfQueryIdByNameINTEL = (PFNGLGETPERFQUERYIDBYNAMEINTELPROC) load(userptr, "glGetPerfQueryIdByNameINTEL");
    glad_glGetPerfQueryInfoINTEL = (PFNGLGETPERFQUERYINFOINTELPROC) load(userptr, "glGetPerfQueryInfoINTEL");
}
static void glad_gl_load_GL_KHR_blend_equation_advanced( GLADuserptrloadfunc load, void* userptr) {
    if(!GLAD_GL_KHR_blend_equation_advanced) return;
    glad_glBlendBarrierKHR = (PFNGLBLENDBARRIERKHRPROC) load(userptr, "glBlendBarrierKHR");
}
static void glad_gl_load_GL_KHR_debug( GLADuserptrloadfunc load, void* userptr) {
    if(!GLAD_GL_KHR_debug) return;
    glad_glDebugMessageCallbackKHR = (PFNGLDEBUGMESSAGECALLBACKKHRPROC) load(userptr, "glDebugMessageCallbackKHR");
    glad_glDebugMessageControlKHR = (PFNGLDEBUGMESSAGECONTROLKHRPROC) load(userptr, "glDebugMessageControlKHR");
    glad_glDebugMessageInsertKHR = (PFNGLDEBUGMESSAGEINSERTKHRPROC) load(userptr, "glDebugMessageInsertKHR");
    glad_glGetDebugMessageLogKHR = (PFNGLGETDEBUGMESSAGELOGKHRPROC) load(userptr, "glGetDebugMessageLogKHR");
    glad_glGetObjectLabelKHR = (PFNGLGETOBJECTLABELKHRPROC) load(userptr, "glGetObjectLabelKHR");
    glad_glGetObjectPtrLabelKHR = (PFNGLGETOBJECTPTRLABELKHRPROC) load(userptr, "glGetObjectPtrLabelKHR");
    glad_glGetPointervKHR = (PFNGLGETPOINTERVKHRPROC) load(userptr, "glGetPointervKHR");
    glad_glObjectLabelKHR = (PFNGLOBJECTLABELKHRPROC) load(userptr, "glObjectLabelKHR");
    glad_glObjectPtrLabelKHR = (PFNGLOBJECTPTRLABELKHRPROC) load(userptr, "glObjectPtrLabelKHR");
    glad_glPopDebugGroupKHR = (PFNGLPOPDEBUGGROUPKHRPROC) load(userptr, "glPopDebugGroupKHR");
    glad_glPushDebugGroupKHR = (PFNGLPUSHDEBUGGROUPKHRPROC) load(userptr, "glPushDebugGroupKHR");
}
static void glad_gl_load_GL_KHR_parallel_shader_compile( GLADuserptrloadfunc load, void* userptr) {
    if(!GLAD_GL_KHR_parallel_shader_compile) return;
    glad_glMaxShaderCompilerThreadsKHR = (PFNGLMAXSHADERCOMPILERTHREADSKHRPROC) load(userptr, "glMaxShaderCompilerThreadsKHR");
}
static void glad_gl_load_GL_KHR_robustness( GLADuserptrloadfunc load, void* userptr) {
    if(!GLAD_GL_KHR_robustness) return;
    glad_glGetGraphicsResetStatusKHR = (PFNGLGETGRAPHICSRESETSTATUSKHRPROC) load(userptr, "glGetGraphicsResetStatusKHR");
    glad_glGetnUniformfvKHR = (PFNGLGETNUNIFORMFVKHRPROC) load(userptr, "glGetnUniformfvKHR");
    glad_glGetnUniformivKHR = (PFNGLGETNUNIFORMIVKHRPROC) load(userptr, "glGetnUniformivKHR");
    glad_glGetnUniformuivKHR = (PFNGLGETNUNIFORMUIVKHRPROC) load(userptr, "glGetnUniformuivKHR");
    glad_glReadnPixelsKHR = (PFNGLREADNPIXELSKHRPROC) load(userptr, "glReadnPixelsKHR");
}
static void glad_gl_load_GL_MESA_framebuffer_flip_y( GLADuserptrloadfunc load, void* userptr) {
    if(!GLAD_GL_MESA_framebuffer_flip_y) return;
    glad_glFramebufferParameteriMESA = (PFNGLFRAMEBUFFERPARAMETERIMESAPROC) load(userptr, "glFramebufferParameteriMESA");
    glad_glGetFramebufferParameterivMESA = (PFNGLGETFRAMEBUFFERPARAMETERIVMESAPROC) load(userptr, "glGetFramebufferParameterivMESA");
}
static void glad_gl_load_GL_NV_bindless_texture( GLADuserptrloadfunc load, void* userptr) {
    if(!GLAD_GL_NV_bindless_texture) return;
    glad_glGetImageHandleNV = (PFNGLGETIMAGEHANDLENVPROC) load(userptr, "glGetImageHandleNV");
    glad_glGetTextureHandleNV = (PFNGLGETTEXTUREHANDLENVPROC) load(userptr, "glGetTextureHandleNV");
    glad_glGetTextureSamplerHandleNV = (PFNGLGETTEXTURESAMPLERHANDLENVPROC) load(userptr, "glGetTextureSamplerHandleNV");
    glad_glIsImageHandleResidentNV = (PFNGLISIMAGEHANDLERESIDENTNVPROC) load(userptr, "glIsImageHandleResidentNV");
    glad_glIsTextureHandleResidentNV = (PFNGLISTEXTUREHANDLERESIDENTNVPROC) load(userptr, "glIsTextureHandleResidentNV");
    glad_glMakeImageHandleNonResidentNV = (PFNGLMAKEIMAGEHANDLENONRESIDENTNVPROC) load(userptr, "glMakeImageHandleNonResidentNV");
    glad_glMakeImageHandleResidentNV = (PFNGLMAKEIMAGEHANDLERESIDENTNVPROC) load(userptr, "glMakeImageHandleResidentNV");
    glad_glMakeTextureHandleNonResidentNV = (PFNGLMAKETEXTUREHANDLENONRESIDENTNVPROC) load(userptr, "glMakeTextureHandleNonResidentNV");
    glad_glMakeTextureHandleResidentNV = (PFNGLMAKETEXTUREHANDLERESIDENTNVPROC) load(userptr, "glMakeTextureHandleResidentNV");
    glad_glProgramUniformHandleui64NV = (PFNGLPROGRAMUNIFORMHANDLEUI64NVPROC) load(userptr, "glProgramUniformHandleui64NV");
    glad_glProgramUniformHandleui64vNV = (PFNGLPROGRAMUNIFORMHANDLEUI64VNVPROC) load(userptr, "glProgramUniformHandleui64vNV");
    glad_glUniformHandleui64NV = (PFNGLUNIFORMHANDLEUI64NVPROC) load(userptr, "glUniformHandleui64NV");
    glad_glUniformHandleui64vNV = (PFNGLUNIFORMHANDLEUI64VNVPROC) load(userptr, "glUniformHandleui64vNV");
}
static void glad_gl_load_GL_NV_blend_equation_advanced( GLADuserptrloadfunc load, void* userptr) {
    if(!GLAD_GL_NV_blend_equation_advanced) return;
    glad_glBlendBarrierNV = (PFNGLBLENDBARRIERNVPROC) load(userptr, "glBlendBarrierNV");
    glad_glBlendParameteriNV = (PFNGLBLENDPARAMETERINVPROC) load(userptr, "glBlendParameteriNV");
}
static void glad_gl_load_GL_NV_clip_space_w_scaling( GLADuserptrloadfunc load, void* userptr) {
    if(!GLAD_GL_NV_clip_space_w_scaling) return;
    glad_glViewportPositionWScaleNV = (PFNGLVIEWPORTPOSITIONWSCALENVPROC) load(userptr, "glViewportPositionWScaleNV");
}
static void glad_gl_load_GL_NV_conditional_render( GLADuserptrloadfunc load, void* userptr) {
    if(!GLAD_GL_NV_conditional_render) return;
    glad_glBeginConditionalRenderNV = (PFNGLBEGINCONDITIONALRENDERNVPROC) load(userptr, "glBeginConditionalRenderNV");
    glad_glEndConditionalRenderNV = (PFNGLENDCONDITIONALRENDERNVPROC) load(userptr, "glEndConditionalRenderNV");
}
static void glad_gl_load_GL_NV_conservative_raster( GLADuserptrloadfunc load, void* userptr) {
    if(!GLAD_GL_NV_conservative_raster) return;
    glad_glSubpixelPrecisionBiasNV = (PFNGLSUBPIXELPRECISIONBIASNVPROC) load(userptr, "glSubpixelPrecisionBiasNV");
}
static void glad_gl_load_GL_NV_conservative_raster_pre_snap_triangles( GLADuserptrloadfunc load, void* userptr) {
    if(!GLAD_GL_NV_conservative_raster_pre_snap_triangles) return;
    glad_glConservativeRasterParameteriNV = (PFNGLCONSERVATIVERASTERPARAMETERINVPROC) load(userptr, "glConservativeRasterParameteriNV");
}
static void glad_gl_load_GL_NV_copy_buffer( GLADuserptrloadfunc load, void* userptr) {
    if(!GLAD_GL_NV_copy_buffer) return;
    glad_glCopyBufferSubDataNV = (PFNGLCOPYBUFFERSUBDATANVPROC) load(userptr, "glCopyBufferSubDataNV");
}
static void glad_gl_load_GL_NV_coverage_sample( GLADuserptrloadfunc load, void* userptr) {
    if(!GLAD_GL_NV_coverage_sample) return;
    glad_glCoverageMaskNV = (PFNGLCOVERAGEMASKNVPROC) load(userptr, "glCoverageMaskNV");
    glad_glCoverageOperationNV = (PFNGLCOVERAGEOPERATIONNVPROC) load(userptr, "glCoverageOperationNV");
}
static void glad_gl_load_GL_NV_draw_buffers( GLADuserptrloadfunc load, void* userptr) {
    if(!GLAD_GL_NV_draw_buffers) return;
    glad_glDrawBuffersNV = (PFNGLDRAWBUFFERSNVPROC) load(userptr, "glDrawBuffersNV");
}
static void glad_gl_load_GL_NV_draw_instanced( GLADuserptrloadfunc load, void* userptr) {
    if(!GLAD_GL_NV_draw_instanced) return;
    glad_glDrawArraysInstancedNV = (PFNGLDRAWARRAYSINSTANCEDNVPROC) load(userptr, "glDrawArraysInstancedNV");
    glad_glDrawElementsInstancedNV = (PFNGLDRAWELEMENTSINSTANCEDNVPROC) load(userptr, "glDrawElementsInstancedNV");
}
static void glad_gl_load_GL_NV_draw_vulkan_image( GLADuserptrloadfunc load, void* userptr) {
    if(!GLAD_GL_NV_draw_vulkan_image) return;
    glad_glDrawVkImageNV = (PFNGLDRAWVKIMAGENVPROC) load(userptr, "glDrawVkImageNV");
    glad_glGetVkProcAddrNV = (PFNGLGETVKPROCADDRNVPROC) load(userptr, "glGetVkProcAddrNV");
    glad_glSignalVkFenceNV = (PFNGLSIGNALVKFENCENVPROC) load(userptr, "glSignalVkFenceNV");
    glad_glSignalVkSemaphoreNV = (PFNGLSIGNALVKSEMAPHORENVPROC) load(userptr, "glSignalVkSemaphoreNV");
    glad_glWaitVkSemaphoreNV = (PFNGLWAITVKSEMAPHORENVPROC) load(userptr, "glWaitVkSemaphoreNV");
}
static void glad_gl_load_GL_NV_fence( GLADuserptrloadfunc load, void* userptr) {
    if(!GLAD_GL_NV_fence) return;
    glad_glDeleteFencesNV = (PFNGLDELETEFENCESNVPROC) load(userptr, "glDeleteFencesNV");
    glad_glFinishFenceNV = (PFNGLFINISHFENCENVPROC) load(userptr, "glFinishFenceNV");
    glad_glGenFencesNV = (PFNGLGENFENCESNVPROC) load(userptr, "glGenFencesNV");
    glad_glGetFenceivNV = (PFNGLGETFENCEIVNVPROC) load(userptr, "glGetFenceivNV");
    glad_glIsFenceNV = (PFNGLISFENCENVPROC) load(userptr, "glIsFenceNV");
    glad_glSetFenceNV = (PFNGLSETFENCENVPROC) load(userptr, "glSetFenceNV");
    glad_glTestFenceNV = (PFNGLTESTFENCENVPROC) load(userptr, "glTestFenceNV");
}
static void glad_gl_load_GL_NV_fragment_coverage_to_color( GLADuserptrloadfunc load, void* userptr) {
    if(!GLAD_GL_NV_fragment_coverage_to_color) return;
    glad_glFragmentCoverageColorNV = (PFNGLFRAGMENTCOVERAGECOLORNVPROC) load(userptr, "glFragmentCoverageColorNV");
}
static void glad_gl_load_GL_NV_framebuffer_blit( GLADuserptrloadfunc load, void* userptr) {
    if(!GLAD_GL_NV_framebuffer_blit) return;
    glad_glBlitFramebufferNV = (PFNGLBLITFRAMEBUFFERNVPROC) load(userptr, "glBlitFramebufferNV");
}
static void glad_gl_load_GL_NV_framebuffer_mixed_samples( GLADuserptrloadfunc load, void* userptr) {
    if(!GLAD_GL_NV_framebuffer_mixed_samples) return;
    glad_glCoverageModulationNV = (PFNGLCOVERAGEMODULATIONNVPROC) load(userptr, "glCoverageModulationNV");
    glad_glCoverageModulationTableNV = (PFNGLCOVERAGEMODULATIONTABLENVPROC) load(userptr, "glCoverageModulationTableNV");
    glad_glGetCoverageModulationTableNV = (PFNGLGETCOVERAGEMODULATIONTABLENVPROC) load(userptr, "glGetCoverageModulationTableNV");
    glad_glRasterSamplesEXT = (PFNGLRASTERSAMPLESEXTPROC) load(userptr, "glRasterSamplesEXT");
}
static void glad_gl_load_GL_NV_framebuffer_multisample( GLADuserptrloadfunc load, void* userptr) {
    if(!GLAD_GL_NV_framebuffer_multisample) return;
    glad_glRenderbufferStorageMultisampleNV = (PFNGLRENDERBUFFERSTORAGEMULTISAMPLENVPROC) load(userptr, "glRenderbufferStorageMultisampleNV");
}
static void glad_gl_load_GL_NV_gpu_shader5( GLADuserptrloadfunc load, void* userptr) {
    if(!GLAD_GL_NV_gpu_shader5) return;
    glad_glGetUniformi64vNV = (PFNGLGETUNIFORMI64VNVPROC) load(userptr, "glGetUniformi64vNV");
    glad_glProgramUniform1i64NV = (PFNGLPROGRAMUNIFORM1I64NVPROC) load(userptr, "glProgramUniform1i64NV");
    glad_glProgramUniform1i64vNV = (PFNGLPROGRAMUNIFORM1I64VNVPROC) load(userptr, "glProgramUniform1i64vNV");
    glad_glProgramUniform1ui64NV = (PFNGLPROGRAMUNIFORM1UI64NVPROC) load(userptr, "glProgramUniform1ui64NV");
    glad_glProgramUniform1ui64vNV = (PFNGLPROGRAMUNIFORM1UI64VNVPROC) load(userptr, "glProgramUniform1ui64vNV");
    glad_glProgramUniform2i64NV = (PFNGLPROGRAMUNIFORM2I64NVPROC) load(userptr, "glProgramUniform2i64NV");
    glad_glProgramUniform2i64vNV = (PFNGLPROGRAMUNIFORM2I64VNVPROC) load(userptr, "glProgramUniform2i64vNV");
    glad_glProgramUniform2ui64NV = (PFNGLPROGRAMUNIFORM2UI64NVPROC) load(userptr, "glProgramUniform2ui64NV");
    glad_glProgramUniform2ui64vNV = (PFNGLPROGRAMUNIFORM2UI64VNVPROC) load(userptr, "glProgramUniform2ui64vNV");
    glad_glProgramUniform3i64NV = (PFNGLPROGRAMUNIFORM3I64NVPROC) load(userptr, "glProgramUniform3i64NV");
    glad_glProgramUniform3i64vNV = (PFNGLPROGRAMUNIFORM3I64VNVPROC) load(userptr, "glProgramUniform3i64vNV");
    glad_glProgramUniform3ui64NV = (PFNGLPROGRAMUNIFORM3UI64NVPROC) load(userptr, "glProgramUniform3ui64NV");
    glad_glProgramUniform3ui64vNV = (PFNGLPROGRAMUNIFORM3UI64VNVPROC) load(userptr, "glProgramUniform3ui64vNV");
    glad_glProgramUniform4i64NV = (PFNGLPROGRAMUNIFORM4I64NVPROC) load(userptr, "glProgramUniform4i64NV");
    glad_glProgramUniform4i64vNV = (PFNGLPROGRAMUNIFORM4I64VNVPROC) load(userptr, "glProgramUniform4i64vNV");
    glad_glProgramUniform4ui64NV = (PFNGLPROGRAMUNIFORM4UI64NVPROC) load(userptr, "glProgramUniform4ui64NV");
    glad_glProgramUniform4ui64vNV = (PFNGLPROGRAMUNIFORM4UI64VNVPROC) load(userptr, "glProgramUniform4ui64vNV");
    glad_glUniform1i64NV = (PFNGLUNIFORM1I64NVPROC) load(userptr, "glUniform1i64NV");
    glad_glUniform1i64vNV = (PFNGLUNIFORM1I64VNVPROC) load(userptr, "glUniform1i64vNV");
    glad_glUniform1ui64NV = (PFNGLUNIFORM1UI64NVPROC) load(userptr, "glUniform1ui64NV");
    glad_glUniform1ui64vNV = (PFNGLUNIFORM1UI64VNVPROC) load(userptr, "glUniform1ui64vNV");
    glad_glUniform2i64NV = (PFNGLUNIFORM2I64NVPROC) load(userptr, "glUniform2i64NV");
    glad_glUniform2i64vNV = (PFNGLUNIFORM2I64VNVPROC) load(userptr, "glUniform2i64vNV");
    glad_glUniform2ui64NV = (PFNGLUNIFORM2UI64NVPROC) load(userptr, "glUniform2ui64NV");
    glad_glUniform2ui64vNV = (PFNGLUNIFORM2UI64VNVPROC) load(userptr, "glUniform2ui64vNV");
    glad_glUniform3i64NV = (PFNGLUNIFORM3I64NVPROC) load(userptr, "glUniform3i64NV");
    glad_glUniform3i64vNV = (PFNGLUNIFORM3I64VNVPROC) load(userptr, "glUniform3i64vNV");
    glad_glUniform3ui64NV = (PFNGLUNIFORM3UI64NVPROC) load(userptr, "glUniform3ui64NV");
    glad_glUniform3ui64vNV = (PFNGLUNIFORM3UI64VNVPROC) load(userptr, "glUniform3ui64vNV");
    glad_glUniform4i64NV = (PFNGLUNIFORM4I64NVPROC) load(userptr, "glUniform4i64NV");
    glad_glUniform4i64vNV = (PFNGLUNIFORM4I64VNVPROC) load(userptr, "glUniform4i64vNV");
    glad_glUniform4ui64NV = (PFNGLUNIFORM4UI64NVPROC) load(userptr, "glUniform4ui64NV");
    glad_glUniform4ui64vNV = (PFNGLUNIFORM4UI64VNVPROC) load(userptr, "glUniform4ui64vNV");
}
static void glad_gl_load_GL_NV_instanced_arrays( GLADuserptrloadfunc load, void* userptr) {
    if(!GLAD_GL_NV_instanced_arrays) return;
    glad_glVertexAttribDivisorNV = (PFNGLVERTEXATTRIBDIVISORNVPROC) load(userptr, "glVertexAttribDivisorNV");
}
static void glad_gl_load_GL_NV_internalformat_sample_query( GLADuserptrloadfunc load, void* userptr) {
    if(!GLAD_GL_NV_internalformat_sample_query) return;
    glad_glGetInternalformatSampleivNV = (PFNGLGETINTERNALFORMATSAMPLEIVNVPROC) load(userptr, "glGetInternalformatSampleivNV");
}
static void glad_gl_load_GL_NV_memory_attachment( GLADuserptrloadfunc load, void* userptr) {
    if(!GLAD_GL_NV_memory_attachment) return;
    glad_glBufferAttachMemoryNV = (PFNGLBUFFERATTACHMEMORYNVPROC) load(userptr, "glBufferAttachMemoryNV");
    glad_glGetMemoryObjectDetachedResourcesuivNV = (PFNGLGETMEMORYOBJECTDETACHEDRESOURCESUIVNVPROC) load(userptr, "glGetMemoryObjectDetachedResourcesuivNV");
    glad_glNamedBufferAttachMemoryNV = (PFNGLNAMEDBUFFERATTACHMEMORYNVPROC) load(userptr, "glNamedBufferAttachMemoryNV");
    glad_glResetMemoryObjectParameterNV = (PFNGLRESETMEMORYOBJECTPARAMETERNVPROC) load(userptr, "glResetMemoryObjectParameterNV");
    glad_glTexAttachMemoryNV = (PFNGLTEXATTACHMEMORYNVPROC) load(userptr, "glTexAttachMemoryNV");
    glad_glTextureAttachMemoryNV = (PFNGLTEXTUREATTACHMEMORYNVPROC) load(userptr, "glTextureAttachMemoryNV");
}
static void glad_gl_load_GL_NV_memory_object_sparse( GLADuserptrloadfunc load, void* userptr) {
    if(!GLAD_GL_NV_memory_object_sparse) return;
    glad_glBufferPageCommitmentMemNV = (PFNGLBUFFERPAGECOMMITMENTMEMNVPROC) load(userptr, "glBufferPageCommitmentMemNV");
    glad_glNamedBufferPageCommitmentMemNV = (PFNGLNAMEDBUFFERPAGECOMMITMENTMEMNVPROC) load(userptr, "glNamedBufferPageCommitmentMemNV");
    glad_glTexPageCommitmentMemNV = (PFNGLTEXPAGECOMMITMENTMEMNVPROC) load(userptr, "glTexPageCommitmentMemNV");
    glad_glTexturePageCommitmentMemNV = (PFNGLTEXTUREPAGECOMMITMENTMEMNVPROC) load(userptr, "glTexturePageCommitmentMemNV");
}
static void glad_gl_load_GL_NV_mesh_shader( GLADuserptrloadfunc load, void* userptr) {
    if(!GLAD_GL_NV_mesh_shader) return;
    glad_glDrawMeshTasksIndirectNV = (PFNGLDRAWMESHTASKSINDIRECTNVPROC) load(userptr, "glDrawMeshTasksIndirectNV");
    glad_glDrawMeshTasksNV = (PFNGLDRAWMESHTASKSNVPROC) load(userptr, "glDrawMeshTasksNV");
    glad_glMultiDrawMeshTasksIndirectCountNV = (PFNGLMULTIDRAWMESHTASKSINDIRECTCOUNTNVPROC) load(userptr, "glMultiDrawMeshTasksIndirectCountNV");
    glad_glMultiDrawMeshTasksIndirectNV = (PFNGLMULTIDRAWMESHTASKSINDIRECTNVPROC) load(userptr, "glMultiDrawMeshTasksIndirectNV");
}
static void glad_gl_load_GL_NV_non_square_matrices( GLADuserptrloadfunc load, void* userptr) {
    if(!GLAD_GL_NV_non_square_matrices) return;
    glad_glUniformMatrix2x3fvNV = (PFNGLUNIFORMMATRIX2X3FVNVPROC) load(userptr, "glUniformMatrix2x3fvNV");
    glad_glUniformMatrix2x4fvNV = (PFNGLUNIFORMMATRIX2X4FVNVPROC) load(userptr, "glUniformMatrix2x4fvNV");
    glad_glUniformMatrix3x2fvNV = (PFNGLUNIFORMMATRIX3X2FVNVPROC) load(userptr, "glUniformMatrix3x2fvNV");
    glad_glUniformMatrix3x4fvNV = (PFNGLUNIFORMMATRIX3X4FVNVPROC) load(userptr, "glUniformMatrix3x4fvNV");
    glad_glUniformMatrix4x2fvNV = (PFNGLUNIFORMMATRIX4X2FVNVPROC) load(userptr, "glUniformMatrix4x2fvNV");
    glad_glUniformMatrix4x3fvNV = (PFNGLUNIFORMMATRIX4X3FVNVPROC) load(userptr, "glUniformMatrix4x3fvNV");
}
static void glad_gl_load_GL_NV_path_rendering( GLADuserptrloadfunc load, void* userptr) {
    if(!GLAD_GL_NV_path_rendering) return;
    glad_glCopyPathNV = (PFNGLCOPYPATHNVPROC) load(userptr, "glCopyPathNV");
    glad_glCoverFillPathInstancedNV = (PFNGLCOVERFILLPATHINSTANCEDNVPROC) load(userptr, "glCoverFillPathInstancedNV");
    glad_glCoverFillPathNV = (PFNGLCOVERFILLPATHNVPROC) load(userptr, "glCoverFillPathNV");
    glad_glCoverStrokePathInstancedNV = (PFNGLCOVERSTROKEPATHINSTANCEDNVPROC) load(userptr, "glCoverStrokePathInstancedNV");
    glad_glCoverStrokePathNV = (PFNGLCOVERSTROKEPATHNVPROC) load(userptr, "glCoverStrokePathNV");
    glad_glDeletePathsNV = (PFNGLDELETEPATHSNVPROC) load(userptr, "glDeletePathsNV");
    glad_glGenPathsNV = (PFNGLGENPATHSNVPROC) load(userptr, "glGenPathsNV");
    glad_glGetPathCommandsNV = (PFNGLGETPATHCOMMANDSNVPROC) load(userptr, "glGetPathCommandsNV");
    glad_glGetPathCoordsNV = (PFNGLGETPATHCOORDSNVPROC) load(userptr, "glGetPathCoordsNV");
    glad_glGetPathDashArrayNV = (PFNGLGETPATHDASHARRAYNVPROC) load(userptr, "glGetPathDashArrayNV");
    glad_glGetPathLengthNV = (PFNGLGETPATHLENGTHNVPROC) load(userptr, "glGetPathLengthNV");
    glad_glGetPathMetricRangeNV = (PFNGLGETPATHMETRICRANGENVPROC) load(userptr, "glGetPathMetricRangeNV");
    glad_glGetPathMetricsNV = (PFNGLGETPATHMETRICSNVPROC) load(userptr, "glGetPathMetricsNV");
    glad_glGetPathParameterfvNV = (PFNGLGETPATHPARAMETERFVNVPROC) load(userptr, "glGetPathParameterfvNV");
    glad_glGetPathParameterivNV = (PFNGLGETPATHPARAMETERIVNVPROC) load(userptr, "glGetPathParameterivNV");
    glad_glGetPathSpacingNV = (PFNGLGETPATHSPACINGNVPROC) load(userptr, "glGetPathSpacingNV");
    glad_glGetProgramResourcefvNV = (PFNGLGETPROGRAMRESOURCEFVNVPROC) load(userptr, "glGetProgramResourcefvNV");
    glad_glInterpolatePathsNV = (PFNGLINTERPOLATEPATHSNVPROC) load(userptr, "glInterpolatePathsNV");
    glad_glIsPathNV = (PFNGLISPATHNVPROC) load(userptr, "glIsPathNV");
    glad_glIsPointInFillPathNV = (PFNGLISPOINTINFILLPATHNVPROC) load(userptr, "glIsPointInFillPathNV");
    glad_glIsPointInStrokePathNV = (PFNGLISPOINTINSTROKEPATHNVPROC) load(userptr, "glIsPointInStrokePathNV");
    glad_glMatrixFrustumEXT = (PFNGLMATRIXFRUSTUMEXTPROC) load(userptr, "glMatrixFrustumEXT");
    glad_glMatrixLoad3x2fNV = (PFNGLMATRIXLOAD3X2FNVPROC) load(userptr, "glMatrixLoad3x2fNV");
    glad_glMatrixLoad3x3fNV = (PFNGLMATRIXLOAD3X3FNVPROC) load(userptr, "glMatrixLoad3x3fNV");
    glad_glMatrixLoadIdentityEXT = (PFNGLMATRIXLOADIDENTITYEXTPROC) load(userptr, "glMatrixLoadIdentityEXT");
    glad_glMatrixLoadTranspose3x3fNV = (PFNGLMATRIXLOADTRANSPOSE3X3FNVPROC) load(userptr, "glMatrixLoadTranspose3x3fNV");
    glad_glMatrixLoadTransposedEXT = (PFNGLMATRIXLOADTRANSPOSEDEXTPROC) load(userptr, "glMatrixLoadTransposedEXT");
    glad_glMatrixLoadTransposefEXT = (PFNGLMATRIXLOADTRANSPOSEFEXTPROC) load(userptr, "glMatrixLoadTransposefEXT");
    glad_glMatrixLoaddEXT = (PFNGLMATRIXLOADDEXTPROC) load(userptr, "glMatrixLoaddEXT");
    glad_glMatrixLoadfEXT = (PFNGLMATRIXLOADFEXTPROC) load(userptr, "glMatrixLoadfEXT");
    glad_glMatrixMult3x2fNV = (PFNGLMATRIXMULT3X2FNVPROC) load(userptr, "glMatrixMult3x2fNV");
    glad_glMatrixMult3x3fNV = (PFNGLMATRIXMULT3X3FNVPROC) load(userptr, "glMatrixMult3x3fNV");
    glad_glMatrixMultTranspose3x3fNV = (PFNGLMATRIXMULTTRANSPOSE3X3FNVPROC) load(userptr, "glMatrixMultTranspose3x3fNV");
    glad_glMatrixMultTransposedEXT = (PFNGLMATRIXMULTTRANSPOSEDEXTPROC) load(userptr, "glMatrixMultTransposedEXT");
    glad_glMatrixMultTransposefEXT = (PFNGLMATRIXMULTTRANSPOSEFEXTPROC) load(userptr, "glMatrixMultTransposefEXT");
    glad_glMatrixMultdEXT = (PFNGLMATRIXMULTDEXTPROC) load(userptr, "glMatrixMultdEXT");
    glad_glMatrixMultfEXT = (PFNGLMATRIXMULTFEXTPROC) load(userptr, "glMatrixMultfEXT");
    glad_glMatrixOrthoEXT = (PFNGLMATRIXORTHOEXTPROC) load(userptr, "glMatrixOrthoEXT");
    glad_glMatrixPopEXT = (PFNGLMATRIXPOPEXTPROC) load(userptr, "glMatrixPopEXT");
    glad_glMatrixPushEXT = (PFNGLMATRIXPUSHEXTPROC) load(userptr, "glMatrixPushEXT");
    glad_glMatrixRotatedEXT = (PFNGLMATRIXROTATEDEXTPROC) load(userptr, "glMatrixRotatedEXT");
    glad_glMatrixRotatefEXT = (PFNGLMATRIXROTATEFEXTPROC) load(userptr, "glMatrixRotatefEXT");
    glad_glMatrixScaledEXT = (PFNGLMATRIXSCALEDEXTPROC) load(userptr, "glMatrixScaledEXT");
    glad_glMatrixScalefEXT = (PFNGLMATRIXSCALEFEXTPROC) load(userptr, "glMatrixScalefEXT");
    glad_glMatrixTranslatedEXT = (PFNGLMATRIXTRANSLATEDEXTPROC) load(userptr, "glMatrixTranslatedEXT");
    glad_glMatrixTranslatefEXT = (PFNGLMATRIXTRANSLATEFEXTPROC) load(userptr, "glMatrixTranslatefEXT");
    glad_glPathCommandsNV = (PFNGLPATHCOMMANDSNVPROC) load(userptr, "glPathCommandsNV");
    glad_glPathCoordsNV = (PFNGLPATHCOORDSNVPROC) load(userptr, "glPathCoordsNV");
    glad_glPathCoverDepthFuncNV = (PFNGLPATHCOVERDEPTHFUNCNVPROC) load(userptr, "glPathCoverDepthFuncNV");
    glad_glPathDashArrayNV = (PFNGLPATHDASHARRAYNVPROC) load(userptr, "glPathDashArrayNV");
    glad_glPathGlyphIndexArrayNV = (PFNGLPATHGLYPHINDEXARRAYNVPROC) load(userptr, "glPathGlyphIndexArrayNV");
    glad_glPathGlyphIndexRangeNV = (PFNGLPATHGLYPHINDEXRANGENVPROC) load(userptr, "glPathGlyphIndexRangeNV");
    glad_glPathGlyphRangeNV = (PFNGLPATHGLYPHRANGENVPROC) load(userptr, "glPathGlyphRangeNV");
    glad_glPathGlyphsNV = (PFNGLPATHGLYPHSNVPROC) load(userptr, "glPathGlyphsNV");
    glad_glPathMemoryGlyphIndexArrayNV = (PFNGLPATHMEMORYGLYPHINDEXARRAYNVPROC) load(userptr, "glPathMemoryGlyphIndexArrayNV");
    glad_glPathParameterfNV = (PFNGLPATHPARAMETERFNVPROC) load(userptr, "glPathParameterfNV");
    glad_glPathParameterfvNV = (PFNGLPATHPARAMETERFVNVPROC) load(userptr, "glPathParameterfvNV");
    glad_glPathParameteriNV = (PFNGLPATHPARAMETERINVPROC) load(userptr, "glPathParameteriNV");
    glad_glPathParameterivNV = (PFNGLPATHPARAMETERIVNVPROC) load(userptr, "glPathParameterivNV");
    glad_glPathStencilDepthOffsetNV = (PFNGLPATHSTENCILDEPTHOFFSETNVPROC) load(userptr, "glPathStencilDepthOffsetNV");
    glad_glPathStencilFuncNV = (PFNGLPATHSTENCILFUNCNVPROC) load(userptr, "glPathStencilFuncNV");
    glad_glPathStringNV = (PFNGLPATHSTRINGNVPROC) load(userptr, "glPathStringNV");
    glad_glPathSubCommandsNV = (PFNGLPATHSUBCOMMANDSNVPROC) load(userptr, "glPathSubCommandsNV");
    glad_glPathSubCoordsNV = (PFNGLPATHSUBCOORDSNVPROC) load(userptr, "glPathSubCoordsNV");
    glad_glPointAlongPathNV = (PFNGLPOINTALONGPATHNVPROC) load(userptr, "glPointAlongPathNV");
    glad_glProgramPathFragmentInputGenNV = (PFNGLPROGRAMPATHFRAGMENTINPUTGENNVPROC) load(userptr, "glProgramPathFragmentInputGenNV");
    glad_glStencilFillPathInstancedNV = (PFNGLSTENCILFILLPATHINSTANCEDNVPROC) load(userptr, "glStencilFillPathInstancedNV");
    glad_glStencilFillPathNV = (PFNGLSTENCILFILLPATHNVPROC) load(userptr, "glStencilFillPathNV");
    glad_glStencilStrokePathInstancedNV = (PFNGLSTENCILSTROKEPATHINSTANCEDNVPROC) load(userptr, "glStencilStrokePathInstancedNV");
    glad_glStencilStrokePathNV = (PFNGLSTENCILSTROKEPATHNVPROC) load(userptr, "glStencilStrokePathNV");
    glad_glStencilThenCoverFillPathInstancedNV = (PFNGLSTENCILTHENCOVERFILLPATHINSTANCEDNVPROC) load(userptr, "glStencilThenCoverFillPathInstancedNV");
    glad_glStencilThenCoverFillPathNV = (PFNGLSTENCILTHENCOVERFILLPATHNVPROC) load(userptr, "glStencilThenCoverFillPathNV");
    glad_glStencilThenCoverStrokePathInstancedNV = (PFNGLSTENCILTHENCOVERSTROKEPATHINSTANCEDNVPROC) load(userptr, "glStencilThenCoverStrokePathInstancedNV");
    glad_glStencilThenCoverStrokePathNV = (PFNGLSTENCILTHENCOVERSTROKEPATHNVPROC) load(userptr, "glStencilThenCoverStrokePathNV");
    glad_glTransformPathNV = (PFNGLTRANSFORMPATHNVPROC) load(userptr, "glTransformPathNV");
    glad_glWeightPathsNV = (PFNGLWEIGHTPATHSNVPROC) load(userptr, "glWeightPathsNV");
}
static void glad_gl_load_GL_NV_polygon_mode( GLADuserptrloadfunc load, void* userptr) {
    if(!GLAD_GL_NV_polygon_mode) return;
    glad_glPolygonModeNV = (PFNGLPOLYGONMODENVPROC) load(userptr, "glPolygonModeNV");
}
static void glad_gl_load_GL_NV_read_buffer( GLADuserptrloadfunc load, void* userptr) {
    if(!GLAD_GL_NV_read_buffer) return;
    glad_glReadBufferNV = (PFNGLREADBUFFERNVPROC) load(userptr, "glReadBufferNV");
}
static void glad_gl_load_GL_NV_sample_locations( GLADuserptrloadfunc load, void* userptr) {
    if(!GLAD_GL_NV_sample_locations) return;
    glad_glFramebufferSampleLocationsfvNV = (PFNGLFRAMEBUFFERSAMPLELOCATIONSFVNVPROC) load(userptr, "glFramebufferSampleLocationsfvNV");
    glad_glNamedFramebufferSampleLocationsfvNV = (PFNGLNAMEDFRAMEBUFFERSAMPLELOCATIONSFVNVPROC) load(userptr, "glNamedFramebufferSampleLocationsfvNV");
    glad_glResolveDepthValuesNV = (PFNGLRESOLVEDEPTHVALUESNVPROC) load(userptr, "glResolveDepthValuesNV");
}
static void glad_gl_load_GL_NV_scissor_exclusive( GLADuserptrloadfunc load, void* userptr) {
    if(!GLAD_GL_NV_scissor_exclusive) return;
    glad_glScissorExclusiveArrayvNV = (PFNGLSCISSOREXCLUSIVEARRAYVNVPROC) load(userptr, "glScissorExclusiveArrayvNV");
    glad_glScissorExclusiveNV = (PFNGLSCISSOREXCLUSIVENVPROC) load(userptr, "glScissorExclusiveNV");
}
static void glad_gl_load_GL_NV_shading_rate_image( GLADuserptrloadfunc load, void* userptr) {
    if(!GLAD_GL_NV_shading_rate_image) return;
    glad_glBindShadingRateImageNV = (PFNGLBINDSHADINGRATEIMAGENVPROC) load(userptr, "glBindShadingRateImageNV");
    glad_glGetShadingRateImagePaletteNV = (PFNGLGETSHADINGRATEIMAGEPALETTENVPROC) load(userptr, "glGetShadingRateImagePaletteNV");
    glad_glGetShadingRateSampleLocationivNV = (PFNGLGETSHADINGRATESAMPLELOCATIONIVNVPROC) load(userptr, "glGetShadingRateSampleLocationivNV");
    glad_glShadingRateImageBarrierNV = (PFNGLSHADINGRATEIMAGEBARRIERNVPROC) load(userptr, "glShadingRateImageBarrierNV");
    glad_glShadingRateImagePaletteNV = (PFNGLSHADINGRATEIMAGEPALETTENVPROC) load(userptr, "glShadingRateImagePaletteNV");
    glad_glShadingRateSampleOrderCustomNV = (PFNGLSHADINGRATESAMPLEORDERCUSTOMNVPROC) load(userptr, "glShadingRateSampleOrderCustomNV");
    glad_glShadingRateSampleOrderNV = (PFNGLSHADINGRATESAMPLEORDERNVPROC) load(userptr, "glShadingRateSampleOrderNV");
}
static void glad_gl_load_GL_NV_timeline_semaphore( GLADuserptrloadfunc load, void* userptr) {
    if(!GLAD_GL_NV_timeline_semaphore) return;
    glad_glCreateSemaphoresNV = (PFNGLCREATESEMAPHORESNVPROC) load(userptr, "glCreateSemaphoresNV");
    glad_glGetSemaphoreParameterivNV = (PFNGLGETSEMAPHOREPARAMETERIVNVPROC) load(userptr, "glGetSemaphoreParameterivNV");
    glad_glSemaphoreParameterivNV = (PFNGLSEMAPHOREPARAMETERIVNVPROC) load(userptr, "glSemaphoreParameterivNV");
}
static void glad_gl_load_GL_NV_viewport_array( GLADuserptrloadfunc load, void* userptr) {
    if(!GLAD_GL_NV_viewport_array) return;
    glad_glDepthRangeArrayfvNV = (PFNGLDEPTHRANGEARRAYFVNVPROC) load(userptr, "glDepthRangeArrayfvNV");
    glad_glDepthRangeIndexedfNV = (PFNGLDEPTHRANGEINDEXEDFNVPROC) load(userptr, "glDepthRangeIndexedfNV");
    glad_glDisableiNV = (PFNGLDISABLEINVPROC) load(userptr, "glDisableiNV");
    glad_glEnableiNV = (PFNGLENABLEINVPROC) load(userptr, "glEnableiNV");
    glad_glGetFloati_vNV = (PFNGLGETFLOATI_VNVPROC) load(userptr, "glGetFloati_vNV");
    glad_glIsEnablediNV = (PFNGLISENABLEDINVPROC) load(userptr, "glIsEnablediNV");
    glad_glScissorArrayvNV = (PFNGLSCISSORARRAYVNVPROC) load(userptr, "glScissorArrayvNV");
    glad_glScissorIndexedNV = (PFNGLSCISSORINDEXEDNVPROC) load(userptr, "glScissorIndexedNV");
    glad_glScissorIndexedvNV = (PFNGLSCISSORINDEXEDVNVPROC) load(userptr, "glScissorIndexedvNV");
    glad_glViewportArrayvNV = (PFNGLVIEWPORTARRAYVNVPROC) load(userptr, "glViewportArrayvNV");
    glad_glViewportIndexedfNV = (PFNGLVIEWPORTINDEXEDFNVPROC) load(userptr, "glViewportIndexedfNV");
    glad_glViewportIndexedfvNV = (PFNGLVIEWPORTINDEXEDFVNVPROC) load(userptr, "glViewportIndexedfvNV");
}
static void glad_gl_load_GL_NV_viewport_swizzle( GLADuserptrloadfunc load, void* userptr) {
    if(!GLAD_GL_NV_viewport_swizzle) return;
    glad_glViewportSwizzleNV = (PFNGLVIEWPORTSWIZZLENVPROC) load(userptr, "glViewportSwizzleNV");
}
static void glad_gl_load_GL_OES_EGL_image( GLADuserptrloadfunc load, void* userptr) {
    if(!GLAD_GL_OES_EGL_image) return;
    glad_glEGLImageTargetRenderbufferStorageOES = (PFNGLEGLIMAGETARGETRENDERBUFFERSTORAGEOESPROC) load(userptr, "glEGLImageTargetRenderbufferStorageOES");
    glad_glEGLImageTargetTexture2DOES = (PFNGLEGLIMAGETARGETTEXTURE2DOESPROC) load(userptr, "glEGLImageTargetTexture2DOES");
}
static void glad_gl_load_GL_OES_copy_image( GLADuserptrloadfunc load, void* userptr) {
    if(!GLAD_GL_OES_copy_image) return;
    glad_glCopyImageSubDataOES = (PFNGLCOPYIMAGESUBDATAOESPROC) load(userptr, "glCopyImageSubDataOES");
}
static void glad_gl_load_GL_OES_draw_buffers_indexed( GLADuserptrloadfunc load, void* userptr) {
    if(!GLAD_GL_OES_draw_buffers_indexed) return;
    glad_glBlendEquationSeparateiOES = (PFNGLBLENDEQUATIONSEPARATEIOESPROC) load(userptr, "glBlendEquationSeparateiOES");
    glad_glBlendEquationiOES = (PFNGLBLENDEQUATIONIOESPROC) load(userptr, "glBlendEquationiOES");
    glad_glBlendFuncSeparateiOES = (PFNGLBLENDFUNCSEPARATEIOESPROC) load(userptr, "glBlendFuncSeparateiOES");
    glad_glBlendFunciOES = (PFNGLBLENDFUNCIOESPROC) load(userptr, "glBlendFunciOES");
    glad_glColorMaskiOES = (PFNGLCOLORMASKIOESPROC) load(userptr, "glColorMaskiOES");
    glad_glDisableiOES = (PFNGLDISABLEIOESPROC) load(userptr, "glDisableiOES");
    glad_glEnableiOES = (PFNGLENABLEIOESPROC) load(userptr, "glEnableiOES");
    glad_glIsEnablediOES = (PFNGLISENABLEDIOESPROC) load(userptr, "glIsEnablediOES");
}
static void glad_gl_load_GL_OES_draw_elements_base_vertex( GLADuserptrloadfunc load, void* userptr) {
    if(!GLAD_GL_OES_draw_elements_base_vertex) return;
    glad_glDrawElementsBaseVertexOES = (PFNGLDRAWELEMENTSBASEVERTEXOESPROC) load(userptr, "glDrawElementsBaseVertexOES");
    glad_glDrawElementsInstancedBaseVertexOES = (PFNGLDRAWELEMENTSINSTANCEDBASEVERTEXOESPROC) load(userptr, "glDrawElementsInstancedBaseVertexOES");
    glad_glDrawRangeElementsBaseVertexOES = (PFNGLDRAWRANGEELEMENTSBASEVERTEXOESPROC) load(userptr, "glDrawRangeElementsBaseVertexOES");
    glad_glMultiDrawElementsBaseVertexEXT = (PFNGLMULTIDRAWELEMENTSBASEVERTEXEXTPROC) load(userptr, "glMultiDrawElementsBaseVertexEXT");
}
static void glad_gl_load_GL_OES_geometry_shader( GLADuserptrloadfunc load, void* userptr) {
    if(!GLAD_GL_OES_geometry_shader) return;
    glad_glFramebufferTextureOES = (PFNGLFRAMEBUFFERTEXTUREOESPROC) load(userptr, "glFramebufferTextureOES");
}
static void glad_gl_load_GL_OES_get_program_binary( GLADuserptrloadfunc load, void* userptr) {
    if(!GLAD_GL_OES_get_program_binary) return;
    glad_glGetProgramBinaryOES = (PFNGLGETPROGRAMBINARYOESPROC) load(userptr, "glGetProgramBinaryOES");
    glad_glProgramBinaryOES = (PFNGLPROGRAMBINARYOESPROC) load(userptr, "glProgramBinaryOES");
}
static void glad_gl_load_GL_OES_mapbuffer( GLADuserptrloadfunc load, void* userptr) {
    if(!GLAD_GL_OES_mapbuffer) return;
    glad_glGetBufferPointervOES = (PFNGLGETBUFFERPOINTERVOESPROC) load(userptr, "glGetBufferPointervOES");
    glad_glMapBufferOES = (PFNGLMAPBUFFEROESPROC) load(userptr, "glMapBufferOES");
    glad_glUnmapBufferOES = (PFNGLUNMAPBUFFEROESPROC) load(userptr, "glUnmapBufferOES");
}
static void glad_gl_load_GL_OES_primitive_bounding_box( GLADuserptrloadfunc load, void* userptr) {
    if(!GLAD_GL_OES_primitive_bounding_box) return;
    glad_glPrimitiveBoundingBoxOES = (PFNGLPRIMITIVEBOUNDINGBOXOESPROC) load(userptr, "glPrimitiveBoundingBoxOES");
}
static void glad_gl_load_GL_OES_sample_shading( GLADuserptrloadfunc load, void* userptr) {
    if(!GLAD_GL_OES_sample_shading) return;
    glad_glMinSampleShadingOES = (PFNGLMINSAMPLESHADINGOESPROC) load(userptr, "glMinSampleShadingOES");
}
static void glad_gl_load_GL_OES_tessellation_shader( GLADuserptrloadfunc load, void* userptr) {
    if(!GLAD_GL_OES_tessellation_shader) return;
    glad_glPatchParameteriOES = (PFNGLPATCHPARAMETERIOESPROC) load(userptr, "glPatchParameteriOES");
}
static void glad_gl_load_GL_OES_texture_3D( GLADuserptrloadfunc load, void* userptr) {
    if(!GLAD_GL_OES_texture_3D) return;
    glad_glCompressedTexImage3DOES = (PFNGLCOMPRESSEDTEXIMAGE3DOESPROC) load(userptr, "glCompressedTexImage3DOES");
    glad_glCompressedTexSubImage3DOES = (PFNGLCOMPRESSEDTEXSUBIMAGE3DOESPROC) load(userptr, "glCompressedTexSubImage3DOES");
    glad_glCopyTexSubImage3DOES = (PFNGLCOPYTEXSUBIMAGE3DOESPROC) load(userptr, "glCopyTexSubImage3DOES");
    glad_glFramebufferTexture3DOES = (PFNGLFRAMEBUFFERTEXTURE3DOESPROC) load(userptr, "glFramebufferTexture3DOES");
    glad_glTexImage3DOES = (PFNGLTEXIMAGE3DOESPROC) load(userptr, "glTexImage3DOES");
    glad_glTexSubImage3DOES = (PFNGLTEXSUBIMAGE3DOESPROC) load(userptr, "glTexSubImage3DOES");
}
static void glad_gl_load_GL_OES_texture_border_clamp( GLADuserptrloadfunc load, void* userptr) {
    if(!GLAD_GL_OES_texture_border_clamp) return;
    glad_glGetSamplerParameterIivOES = (PFNGLGETSAMPLERPARAMETERIIVOESPROC) load(userptr, "glGetSamplerParameterIivOES");
    glad_glGetSamplerParameterIuivOES = (PFNGLGETSAMPLERPARAMETERIUIVOESPROC) load(userptr, "glGetSamplerParameterIuivOES");
    glad_glGetTexParameterIivOES = (PFNGLGETTEXPARAMETERIIVOESPROC) load(userptr, "glGetTexParameterIivOES");
    glad_glGetTexParameterIuivOES = (PFNGLGETTEXPARAMETERIUIVOESPROC) load(userptr, "glGetTexParameterIuivOES");
    glad_glSamplerParameterIivOES = (PFNGLSAMPLERPARAMETERIIVOESPROC) load(userptr, "glSamplerParameterIivOES");
    glad_glSamplerParameterIuivOES = (PFNGLSAMPLERPARAMETERIUIVOESPROC) load(userptr, "glSamplerParameterIuivOES");
    glad_glTexParameterIivOES = (PFNGLTEXPARAMETERIIVOESPROC) load(userptr, "glTexParameterIivOES");
    glad_glTexParameterIuivOES = (PFNGLTEXPARAMETERIUIVOESPROC) load(userptr, "glTexParameterIuivOES");
}
static void glad_gl_load_GL_OES_texture_buffer( GLADuserptrloadfunc load, void* userptr) {
    if(!GLAD_GL_OES_texture_buffer) return;
    glad_glTexBufferOES = (PFNGLTEXBUFFEROESPROC) load(userptr, "glTexBufferOES");
    glad_glTexBufferRangeOES = (PFNGLTEXBUFFERRANGEOESPROC) load(userptr, "glTexBufferRangeOES");
}
static void glad_gl_load_GL_OES_texture_storage_multisample_2d_array( GLADuserptrloadfunc load, void* userptr) {
    if(!GLAD_GL_OES_texture_storage_multisample_2d_array) return;
    glad_glTexStorage3DMultisampleOES = (PFNGLTEXSTORAGE3DMULTISAMPLEOESPROC) load(userptr, "glTexStorage3DMultisampleOES");
}
static void glad_gl_load_GL_OES_texture_view( GLADuserptrloadfunc load, void* userptr) {
    if(!GLAD_GL_OES_texture_view) return;
    glad_glTextureViewOES = (PFNGLTEXTUREVIEWOESPROC) load(userptr, "glTextureViewOES");
}
static void glad_gl_load_GL_OES_vertex_array_object( GLADuserptrloadfunc load, void* userptr) {
    if(!GLAD_GL_OES_vertex_array_object) return;
    glad_glBindVertexArrayOES = (PFNGLBINDVERTEXARRAYOESPROC) load(userptr, "glBindVertexArrayOES");
    glad_glDeleteVertexArraysOES = (PFNGLDELETEVERTEXARRAYSOESPROC) load(userptr, "glDeleteVertexArraysOES");
    glad_glGenVertexArraysOES = (PFNGLGENVERTEXARRAYSOESPROC) load(userptr, "glGenVertexArraysOES");
    glad_glIsVertexArrayOES = (PFNGLISVERTEXARRAYOESPROC) load(userptr, "glIsVertexArrayOES");
}
static void glad_gl_load_GL_OES_viewport_array( GLADuserptrloadfunc load, void* userptr) {
    if(!GLAD_GL_OES_viewport_array) return;
    glad_glDepthRangeArrayfvOES = (PFNGLDEPTHRANGEARRAYFVOESPROC) load(userptr, "glDepthRangeArrayfvOES");
    glad_glDepthRangeIndexedfOES = (PFNGLDEPTHRANGEINDEXEDFOESPROC) load(userptr, "glDepthRangeIndexedfOES");
    glad_glDisableiOES = (PFNGLDISABLEIOESPROC) load(userptr, "glDisableiOES");
    glad_glEnableiOES = (PFNGLENABLEIOESPROC) load(userptr, "glEnableiOES");
    glad_glGetFloati_vOES = (PFNGLGETFLOATI_VOESPROC) load(userptr, "glGetFloati_vOES");
    glad_glIsEnablediOES = (PFNGLISENABLEDIOESPROC) load(userptr, "glIsEnablediOES");
    glad_glScissorArrayvOES = (PFNGLSCISSORARRAYVOESPROC) load(userptr, "glScissorArrayvOES");
    glad_glScissorIndexedOES = (PFNGLSCISSORINDEXEDOESPROC) load(userptr, "glScissorIndexedOES");
    glad_glScissorIndexedvOES = (PFNGLSCISSORINDEXEDVOESPROC) load(userptr, "glScissorIndexedvOES");
    glad_glViewportArrayvOES = (PFNGLVIEWPORTARRAYVOESPROC) load(userptr, "glViewportArrayvOES");
    glad_glViewportIndexedfOES = (PFNGLVIEWPORTINDEXEDFOESPROC) load(userptr, "glViewportIndexedfOES");
    glad_glViewportIndexedfvOES = (PFNGLVIEWPORTINDEXEDFVOESPROC) load(userptr, "glViewportIndexedfvOES");
}
static void glad_gl_load_GL_OVR_multiview( GLADuserptrloadfunc load, void* userptr) {
    if(!GLAD_GL_OVR_multiview) return;
    glad_glFramebufferTextureMultiviewOVR = (PFNGLFRAMEBUFFERTEXTUREMULTIVIEWOVRPROC) load(userptr, "glFramebufferTextureMultiviewOVR");
}
static void glad_gl_load_GL_OVR_multiview_multisampled_render_to_texture( GLADuserptrloadfunc load, void* userptr) {
    if(!GLAD_GL_OVR_multiview_multisampled_render_to_texture) return;
    glad_glFramebufferTextureMultisampleMultiviewOVR = (PFNGLFRAMEBUFFERTEXTUREMULTISAMPLEMULTIVIEWOVRPROC) load(userptr, "glFramebufferTextureMultisampleMultiviewOVR");
}
static void glad_gl_load_GL_QCOM_alpha_test( GLADuserptrloadfunc load, void* userptr) {
    if(!GLAD_GL_QCOM_alpha_test) return;
    glad_glAlphaFuncQCOM = (PFNGLALPHAFUNCQCOMPROC) load(userptr, "glAlphaFuncQCOM");
}
static void glad_gl_load_GL_QCOM_driver_control( GLADuserptrloadfunc load, void* userptr) {
    if(!GLAD_GL_QCOM_driver_control) return;
    glad_glDisableDriverControlQCOM = (PFNGLDISABLEDRIVERCONTROLQCOMPROC) load(userptr, "glDisableDriverControlQCOM");
    glad_glEnableDriverControlQCOM = (PFNGLENABLEDRIVERCONTROLQCOMPROC) load(userptr, "glEnableDriverControlQCOM");
    glad_glGetDriverControlStringQCOM = (PFNGLGETDRIVERCONTROLSTRINGQCOMPROC) load(userptr, "glGetDriverControlStringQCOM");
    glad_glGetDriverControlsQCOM = (PFNGLGETDRIVERCONTROLSQCOMPROC) load(userptr, "glGetDriverControlsQCOM");
}
static void glad_gl_load_GL_QCOM_extended_get( GLADuserptrloadfunc load, void* userptr) {
    if(!GLAD_GL_QCOM_extended_get) return;
    glad_glExtGetBufferPointervQCOM = (PFNGLEXTGETBUFFERPOINTERVQCOMPROC) load(userptr, "glExtGetBufferPointervQCOM");
    glad_glExtGetBuffersQCOM = (PFNGLEXTGETBUFFERSQCOMPROC) load(userptr, "glExtGetBuffersQCOM");
    glad_glExtGetFramebuffersQCOM = (PFNGLEXTGETFRAMEBUFFERSQCOMPROC) load(userptr, "glExtGetFramebuffersQCOM");
    glad_glExtGetRenderbuffersQCOM = (PFNGLEXTGETRENDERBUFFERSQCOMPROC) load(userptr, "glExtGetRenderbuffersQCOM");
    glad_glExtGetTexLevelParameterivQCOM = (PFNGLEXTGETTEXLEVELPARAMETERIVQCOMPROC) load(userptr, "glExtGetTexLevelParameterivQCOM");
    glad_glExtGetTexSubImageQCOM = (PFNGLEXTGETTEXSUBIMAGEQCOMPROC) load(userptr, "glExtGetTexSubImageQCOM");
    glad_glExtGetTexturesQCOM = (PFNGLEXTGETTEXTURESQCOMPROC) load(userptr, "glExtGetTexturesQCOM");
    glad_glExtTexObjectStateOverrideiQCOM = (PFNGLEXTTEXOBJECTSTATEOVERRIDEIQCOMPROC) load(userptr, "glExtTexObjectStateOverrideiQCOM");
}
static void glad_gl_load_GL_QCOM_extended_get2( GLADuserptrloadfunc load, void* userptr) {
    if(!GLAD_GL_QCOM_extended_get2) return;
    glad_glExtGetProgramBinarySourceQCOM = (PFNGLEXTGETPROGRAMBINARYSOURCEQCOMPROC) load(userptr, "glExtGetProgramBinarySourceQCOM");
    glad_glExtGetProgramsQCOM = (PFNGLEXTGETPROGRAMSQCOMPROC) load(userptr, "glExtGetProgramsQCOM");
    glad_glExtGetShadersQCOM = (PFNGLEXTGETSHADERSQCOMPROC) load(userptr, "glExtGetShadersQCOM");
    glad_glExtIsProgramBinaryQCOM = (PFNGLEXTISPROGRAMBINARYQCOMPROC) load(userptr, "glExtIsProgramBinaryQCOM");
}
static void glad_gl_load_GL_QCOM_frame_extrapolation( GLADuserptrloadfunc load, void* userptr) {
    if(!GLAD_GL_QCOM_frame_extrapolation) return;
    glad_glExtrapolateTex2DQCOM = (PFNGLEXTRAPOLATETEX2DQCOMPROC) load(userptr, "glExtrapolateTex2DQCOM");
}
static void glad_gl_load_GL_QCOM_framebuffer_foveated( GLADuserptrloadfunc load, void* userptr) {
    if(!GLAD_GL_QCOM_framebuffer_foveated) return;
    glad_glFramebufferFoveationConfigQCOM = (PFNGLFRAMEBUFFERFOVEATIONCONFIGQCOMPROC) load(userptr, "glFramebufferFoveationConfigQCOM");
    glad_glFramebufferFoveationParametersQCOM = (PFNGLFRAMEBUFFERFOVEATIONPARAMETERSQCOMPROC) load(userptr, "glFramebufferFoveationParametersQCOM");
}
static void glad_gl_load_GL_QCOM_motion_estimation( GLADuserptrloadfunc load, void* userptr) {
    if(!GLAD_GL_QCOM_motion_estimation) return;
    glad_glTexEstimateMotionQCOM = (PFNGLTEXESTIMATEMOTIONQCOMPROC) load(userptr, "glTexEstimateMotionQCOM");
    glad_glTexEstimateMotionRegionsQCOM = (PFNGLTEXESTIMATEMOTIONREGIONSQCOMPROC) load(userptr, "glTexEstimateMotionRegionsQCOM");
}
static void glad_gl_load_GL_QCOM_shader_framebuffer_fetch_noncoherent( GLADuserptrloadfunc load, void* userptr) {
    if(!GLAD_GL_QCOM_shader_framebuffer_fetch_noncoherent) return;
    glad_glFramebufferFetchBarrierQCOM = (PFNGLFRAMEBUFFERFETCHBARRIERQCOMPROC) load(userptr, "glFramebufferFetchBarrierQCOM");
}
static void glad_gl_load_GL_QCOM_shading_rate( GLADuserptrloadfunc load, void* userptr) {
    if(!GLAD_GL_QCOM_shading_rate) return;
    glad_glShadingRateQCOM = (PFNGLSHADINGRATEQCOMPROC) load(userptr, "glShadingRateQCOM");
}
static void glad_gl_load_GL_QCOM_texture_foveated( GLADuserptrloadfunc load, void* userptr) {
    if(!GLAD_GL_QCOM_texture_foveated) return;
    glad_glTextureFoveationParametersQCOM = (PFNGLTEXTUREFOVEATIONPARAMETERSQCOMPROC) load(userptr, "glTextureFoveationParametersQCOM");
}
static void glad_gl_load_GL_QCOM_tiled_rendering( GLADuserptrloadfunc load, void* userptr) {
    if(!GLAD_GL_QCOM_tiled_rendering) return;
    glad_glEndTilingQCOM = (PFNGLENDTILINGQCOMPROC) load(userptr, "glEndTilingQCOM");
    glad_glStartTilingQCOM = (PFNGLSTARTTILINGQCOMPROC) load(userptr, "glStartTilingQCOM");
}



#if defined(GL_ES_VERSION_3_0) || defined(GL_VERSION_3_0)
#define GLAD_GL_IS_SOME_NEW_VERSION 1
#else
#define GLAD_GL_IS_SOME_NEW_VERSION 0
#endif

static int glad_gl_get_extensions( int version, const char **out_exts, unsigned int *out_num_exts_i, char ***out_exts_i) {
#if GLAD_GL_IS_SOME_NEW_VERSION
    if(GLAD_VERSION_MAJOR(version) < 3) {
#else
    (void) version;
    (void) out_num_exts_i;
    (void) out_exts_i;
#endif
        if (glad_glGetString == NULL) {
            return 0;
        }
        *out_exts = (const char *)glad_glGetString(GL_EXTENSIONS);
#if GLAD_GL_IS_SOME_NEW_VERSION
    } else {
        unsigned int index = 0;
        unsigned int num_exts_i = 0;
        char **exts_i = NULL;
        if (glad_glGetStringi == NULL || glad_glGetIntegerv == NULL) {
            return 0;
        }
        glad_glGetIntegerv(GL_NUM_EXTENSIONS, (int*) &num_exts_i);
        if (num_exts_i > 0) {
            exts_i = (char **) malloc(num_exts_i * (sizeof *exts_i));
        }
        if (exts_i == NULL) {
            return 0;
        }
        for(index = 0; index < num_exts_i; index++) {
            const char *gl_str_tmp = (const char*) glad_glGetStringi(GL_EXTENSIONS, index);
            size_t len = strlen(gl_str_tmp) + 1;

            char *local_str = (char*) malloc(len * sizeof(char));
            if(local_str != NULL) {
                memcpy(local_str, gl_str_tmp, len * sizeof(char));
            }

            exts_i[index] = local_str;
        }

        *out_num_exts_i = num_exts_i;
        *out_exts_i = exts_i;
    }
#endif
    return 1;
}
static void glad_gl_free_extensions(char **exts_i, unsigned int num_exts_i) {
    if (exts_i != NULL) {
        unsigned int index;
        for(index = 0; index < num_exts_i; index++) {
            free((void *) (exts_i[index]));
        }
        free((void *)exts_i);
        exts_i = NULL;
    }
}
static int glad_gl_has_extension(int version, const char *exts, unsigned int num_exts_i, char **exts_i, const char *ext) {
    if(GLAD_VERSION_MAJOR(version) < 3 || !GLAD_GL_IS_SOME_NEW_VERSION) {
        const char *extensions;
        const char *loc;
        const char *terminator;
        extensions = exts;
        if(extensions == NULL || ext == NULL) {
            return 0;
        }
        while(1) {
            loc = strstr(extensions, ext);
            if(loc == NULL) {
                return 0;
            }
            terminator = loc + strlen(ext);
            if((loc == extensions || *(loc - 1) == ' ') &&
                (*terminator == ' ' || *terminator == '\0')) {
                return 1;
            }
            extensions = terminator;
        }
    } else {
        unsigned int index;
        for(index = 0; index < num_exts_i; index++) {
            const char *e = exts_i[index];
            if(strcmp(e, ext) == 0) {
                return 1;
            }
        }
    }
    return 0;
}

static GLADapiproc glad_gl_get_proc_from_userptr(void *userptr, const char* name) {
    return (GLAD_GNUC_EXTENSION (GLADapiproc (*)(const char *name)) userptr)(name);
}

static int glad_gl_find_extensions_gles2( int version) {
    const char *exts = NULL;
    unsigned int num_exts_i = 0;
    char **exts_i = NULL;
    if (!glad_gl_get_extensions(version, &exts, &num_exts_i, &exts_i)) return 0;

    GLAD_GL_AMD_compressed_3DC_texture = glad_gl_has_extension(version, exts, num_exts_i, exts_i, "GL_AMD_compressed_3DC_texture");
    GLAD_GL_AMD_compressed_ATC_texture = glad_gl_has_extension(version, exts, num_exts_i, exts_i, "GL_AMD_compressed_ATC_texture");
    GLAD_GL_AMD_framebuffer_multisample_advanced = glad_gl_has_extension(version, exts, num_exts_i, exts_i, "GL_AMD_framebuffer_multisample_advanced");
    GLAD_GL_AMD_performance_monitor = glad_gl_has_extension(version, exts, num_exts_i, exts_i, "GL_AMD_performance_monitor");
    GLAD_GL_AMD_program_binary_Z400 = glad_gl_has_extension(version, exts, num_exts_i, exts_i, "GL_AMD_program_binary_Z400");
    GLAD_GL_ANDROID_extension_pack_es31a = glad_gl_has_extension(version, exts, num_exts_i, exts_i, "GL_ANDROID_extension_pack_es31a");
    GLAD_GL_ANGLE_depth_texture = glad_gl_has_extension(version, exts, num_exts_i, exts_i, "GL_ANGLE_depth_texture");
    GLAD_GL_ANGLE_framebuffer_blit = glad_gl_has_extension(version, exts, num_exts_i, exts_i, "GL_ANGLE_framebuffer_blit");
    GLAD_GL_ANGLE_framebuffer_multisample = glad_gl_has_extension(version, exts, num_exts_i, exts_i, "GL_ANGLE_framebuffer_multisample");
    GLAD_GL_ANGLE_instanced_arrays = glad_gl_has_extension(version, exts, num_exts_i, exts_i, "GL_ANGLE_instanced_arrays");
    GLAD_GL_ANGLE_pack_reverse_row_order = glad_gl_has_extension(version, exts, num_exts_i, exts_i, "GL_ANGLE_pack_reverse_row_order");
    GLAD_GL_ANGLE_program_binary = glad_gl_has_extension(version, exts, num_exts_i, exts_i, "GL_ANGLE_program_binary");
    GLAD_GL_ANGLE_texture_compression_dxt3 = glad_gl_has_extension(version, exts, num_exts_i, exts_i, "GL_ANGLE_texture_compression_dxt3");
    GLAD_GL_ANGLE_texture_compression_dxt5 = glad_gl_has_extension(version, exts, num_exts_i, exts_i, "GL_ANGLE_texture_compression_dxt5");
    GLAD_GL_ANGLE_texture_usage = glad_gl_has_extension(version, exts, num_exts_i, exts_i, "GL_ANGLE_texture_usage");
    GLAD_GL_ANGLE_translated_shader_source = glad_gl_has_extension(version, exts, num_exts_i, exts_i, "GL_ANGLE_translated_shader_source");
    GLAD_GL_APPLE_clip_distance = glad_gl_has_extension(version, exts, num_exts_i, exts_i, "GL_APPLE_clip_distance");
    GLAD_GL_APPLE_color_buffer_packed_float = glad_gl_has_extension(version, exts, num_exts_i, exts_i, "GL_APPLE_color_buffer_packed_float");
    GLAD_GL_APPLE_copy_texture_levels = glad_gl_has_extension(version, exts, num_exts_i, exts_i, "GL_APPLE_copy_texture_levels");
    GLAD_GL_APPLE_framebuffer_multisample = glad_gl_has_extension(version, exts, num_exts_i, exts_i, "GL_APPLE_framebuffer_multisample");
    GLAD_GL_APPLE_rgb_422 = glad_gl_has_extension(version, exts, num_exts_i, exts_i, "GL_APPLE_rgb_422");
    GLAD_GL_APPLE_sync = glad_gl_has_extension(version, exts, num_exts_i, exts_i, "GL_APPLE_sync");
    GLAD_GL_APPLE_texture_format_BGRA8888 = glad_gl_has_extension(version, exts, num_exts_i, exts_i, "GL_APPLE_texture_format_BGRA8888");
    GLAD_GL_APPLE_texture_max_level = glad_gl_has_extension(version, exts, num_exts_i, exts_i, "GL_APPLE_texture_max_level");
    GLAD_GL_APPLE_texture_packed_float = glad_gl_has_extension(version, exts, num_exts_i, exts_i, "GL_APPLE_texture_packed_float");
    GLAD_GL_ARM_mali_program_binary = glad_gl_has_extension(version, exts, num_exts_i, exts_i, "GL_ARM_mali_program_binary");
    GLAD_GL_ARM_mali_shader_binary = glad_gl_has_extension(version, exts, num_exts_i, exts_i, "GL_ARM_mali_shader_binary");
    GLAD_GL_ARM_rgba8 = glad_gl_has_extension(version, exts, num_exts_i, exts_i, "GL_ARM_rgba8");
    GLAD_GL_ARM_shader_framebuffer_fetch = glad_gl_has_extension(version, exts, num_exts_i, exts_i, "GL_ARM_shader_framebuffer_fetch");
    GLAD_GL_ARM_shader_framebuffer_fetch_depth_stencil = glad_gl_has_extension(version, exts, num_exts_i, exts_i, "GL_ARM_shader_framebuffer_fetch_depth_stencil");
    GLAD_GL_ARM_texture_unnormalized_coordinates = glad_gl_has_extension(version, exts, num_exts_i, exts_i, "GL_ARM_texture_unnormalized_coordinates");
    GLAD_GL_DMP_program_binary = glad_gl_has_extension(version, exts, num_exts_i, exts_i, "GL_DMP_program_binary");
    GLAD_GL_DMP_shader_binary = glad_gl_has_extension(version, exts, num_exts_i, exts_i, "GL_DMP_shader_binary");
    GLAD_GL_EXT_EGL_image_array = glad_gl_has_extension(version, exts, num_exts_i, exts_i, "GL_EXT_EGL_image_array");
    GLAD_GL_EXT_EGL_image_storage = glad_gl_has_extension(version, exts, num_exts_i, exts_i, "GL_EXT_EGL_image_storage");
    GLAD_GL_EXT_EGL_image_storage_compression = glad_gl_has_extension(version, exts, num_exts_i, exts_i, "GL_EXT_EGL_image_storage_compression");
    GLAD_GL_EXT_YUV_target = glad_gl_has_extension(version, exts, num_exts_i, exts_i, "GL_EXT_YUV_target");
    GLAD_GL_EXT_base_instance = glad_gl_has_extension(version, exts, num_exts_i, exts_i, "GL_EXT_base_instance");
    GLAD_GL_EXT_blend_func_extended = glad_gl_has_extension(version, exts, num_exts_i, exts_i, "GL_EXT_blend_func_extended");
    GLAD_GL_EXT_blend_minmax = glad_gl_has_extension(version, exts, num_exts_i, exts_i, "GL_EXT_blend_minmax");
    GLAD_GL_EXT_buffer_storage = glad_gl_has_extension(version, exts, num_exts_i, exts_i, "GL_EXT_buffer_storage");
    GLAD_GL_EXT_clear_texture = glad_gl_has_extension(version, exts, num_exts_i, exts_i, "GL_EXT_clear_texture");
    GLAD_GL_EXT_clip_control = glad_gl_has_extension(version, exts, num_exts_i, exts_i, "GL_EXT_clip_control");
    GLAD_GL_EXT_clip_cull_distance = glad_gl_has_extension(version, exts, num_exts_i, exts_i, "GL_EXT_clip_cull_distance");
    GLAD_GL_EXT_color_buffer_float = glad_gl_has_extension(version, exts, num_exts_i, exts_i, "GL_EXT_color_buffer_float");
    GLAD_GL_EXT_color_buffer_half_float = glad_gl_has_extension(version, exts, num_exts_i, exts_i, "GL_EXT_color_buffer_half_float");
    GLAD_GL_EXT_conservative_depth = glad_gl_has_extension(version, exts, num_exts_i, exts_i, "GL_EXT_conservative_depth");
    GLAD_GL_EXT_copy_image = glad_gl_has_extension(version, exts, num_exts_i, exts_i, "GL_EXT_copy_image");
    GLAD_GL_EXT_debug_label = glad_gl_has_extension(version, exts, num_exts_i, exts_i, "GL_EXT_debug_label");
    GLAD_GL_EXT_debug_marker = glad_gl_has_extension(version, exts, num_exts_i, exts_i, "GL_EXT_debug_marker");
    GLAD_GL_EXT_depth_clamp = glad_gl_has_extension(version, exts, num_exts_i, exts_i, "GL_EXT_depth_clamp");
    GLAD_GL_EXT_discard_framebuffer = glad_gl_has_extension(version, exts, num_exts_i, exts_i, "GL_EXT_discard_framebuffer");
    GLAD_GL_EXT_disjoint_timer_query = glad_gl_has_extension(version, exts, num_exts_i, exts_i, "GL_EXT_disjoint_timer_query");
    GLAD_GL_EXT_draw_buffers = glad_gl_has_extension(version, exts, num_exts_i, exts_i, "GL_EXT_draw_buffers");
    GLAD_GL_EXT_draw_buffers_indexed = glad_gl_has_extension(version, exts, num_exts_i, exts_i, "GL_EXT_draw_buffers_indexed");
    GLAD_GL_EXT_draw_elements_base_vertex = glad_gl_has_extension(version, exts, num_exts_i, exts_i, "GL_EXT_draw_elements_base_vertex");
    GLAD_GL_EXT_draw_instanced = glad_gl_has_extension(version, exts, num_exts_i, exts_i, "GL_EXT_draw_instanced");
    GLAD_GL_EXT_draw_transform_feedback = glad_gl_has_extension(version, exts, num_exts_i, exts_i, "GL_EXT_draw_transform_feedback");
    GLAD_GL_EXT_external_buffer = glad_gl_has_extension(version, exts, num_exts_i, exts_i, "GL_EXT_external_buffer");
    GLAD_GL_EXT_float_blend = glad_gl_has_extension(version, exts, num_exts_i, exts_i, "GL_EXT_float_blend");
    GLAD_GL_EXT_fragment_shading_rate = glad_gl_has_extension(version, exts, num_exts_i, exts_i, "GL_EXT_fragment_shading_rate");
    GLAD_GL_EXT_geometry_point_size = glad_gl_has_extension(version, exts, num_exts_i, exts_i, "GL_EXT_geometry_point_size");
    GLAD_GL_EXT_geometry_shader = glad_gl_has_extension(version, exts, num_exts_i, exts_i, "GL_EXT_geometry_shader");
    GLAD_GL_EXT_gpu_shader5 = glad_gl_has_extension(version, exts, num_exts_i, exts_i, "GL_EXT_gpu_shader5");
    GLAD_GL_EXT_instanced_arrays = glad_gl_has_extension(version, exts, num_exts_i, exts_i, "GL_EXT_instanced_arrays");
    GLAD_GL_EXT_map_buffer_range = glad_gl_has_extension(version, exts, num_exts_i, exts_i, "GL_EXT_map_buffer_range");
    GLAD_GL_EXT_memory_object = glad_gl_has_extension(version, exts, num_exts_i, exts_i, "GL_EXT_memory_object");
    GLAD_GL_EXT_memory_object_fd = glad_gl_has_extension(version, exts, num_exts_i, exts_i, "GL_EXT_memory_object_fd");
    GLAD_GL_EXT_memory_object_win32 = glad_gl_has_extension(version, exts, num_exts_i, exts_i, "GL_EXT_memory_object_win32");
    GLAD_GL_EXT_multi_draw_arrays = glad_gl_has_extension(version, exts, num_exts_i, exts_i, "GL_EXT_multi_draw_arrays");
    GLAD_GL_EXT_multi_draw_indirect = glad_gl_has_extension(version, exts, num_exts_i, exts_i, "GL_EXT_multi_draw_indirect");
    GLAD_GL_EXT_multisampled_compatibility = glad_gl_has_extension(version, exts, num_exts_i, exts_i, "GL_EXT_multisampled_compatibility");
    GLAD_GL_EXT_multisampled_render_to_texture = glad_gl_has_extension(version, exts, num_exts_i, exts_i, "GL_EXT_multisampled_render_to_texture");
    GLAD_GL_EXT_multisampled_render_to_texture2 = glad_gl_has_extension(version, exts, num_exts_i, exts_i, "GL_EXT_multisampled_render_to_texture2");
    GLAD_GL_EXT_multiview_draw_buffers = glad_gl_has_extension(version, exts, num_exts_i, exts_i, "GL_EXT_multiview_draw_buffers");
    GLAD_GL_EXT_multiview_tessellation_geometry_shader = glad_gl_has_extension(version, exts, num_exts_i, exts_i, "GL_EXT_multiview_tessellation_geometry_shader");
    GLAD_GL_EXT_multiview_texture_multisample = glad_gl_has_extension(version, exts, num_exts_i, exts_i, "GL_EXT_multiview_texture_multisample");
    GLAD_GL_EXT_multiview_timer_query = glad_gl_has_extension(version, exts, num_exts_i, exts_i, "GL_EXT_multiview_timer_query");
    GLAD_GL_EXT_occlusion_query_boolean = glad_gl_has_extension(version, exts, num_exts_i, exts_i, "GL_EXT_occlusion_query_boolean");
    GLAD_GL_EXT_polygon_offset_clamp = glad_gl_has_extension(version, exts, num_exts_i, exts_i, "GL_EXT_polygon_offset_clamp");
    GLAD_GL_EXT_post_depth_coverage = glad_gl_has_extension(version, exts, num_exts_i, exts_i, "GL_EXT_post_depth_coverage");
    GLAD_GL_EXT_primitive_bounding_box = glad_gl_has_extension(version, exts, num_exts_i, exts_i, "GL_EXT_primitive_bounding_box");
    GLAD_GL_EXT_protected_textures = glad_gl_has_extension(version, exts, num_exts_i, exts_i, "GL_EXT_protected_textures");
    GLAD_GL_EXT_pvrtc_sRGB = glad_gl_has_extension(version, exts, num_exts_i, exts_i, "GL_EXT_pvrtc_sRGB");
    GLAD_GL_EXT_raster_multisample = glad_gl_has_extension(version, exts, num_exts_i, exts_i, "GL_EXT_raster_multisample");
    GLAD_GL_EXT_read_format_bgra = glad_gl_has_extension(version, exts, num_exts_i, exts_i, "GL_EXT_read_format_bgra");
    GLAD_GL_EXT_render_snorm = glad_gl_has_extension(version, exts, num_exts_i, exts_i, "GL_EXT_render_snorm");
    GLAD_GL_EXT_robustness = glad_gl_has_extension(version, exts, num_exts_i, exts_i, "GL_EXT_robustness");
    GLAD_GL_EXT_sRGB = glad_gl_has_extension(version, exts, num_exts_i, exts_i, "GL_EXT_sRGB");
    GLAD_GL_EXT_sRGB_write_control = glad_gl_has_extension(version, exts, num_exts_i, exts_i, "GL_EXT_sRGB_write_control");
    GLAD_GL_EXT_semaphore = glad_gl_has_extension(version, exts, num_exts_i, exts_i, "GL_EXT_semaphore");
    GLAD_GL_EXT_semaphore_fd = glad_gl_has_extension(version, exts, num_exts_i, exts_i, "GL_EXT_semaphore_fd");
    GLAD_GL_EXT_semaphore_win32 = glad_gl_has_extension(version, exts, num_exts_i, exts_i, "GL_EXT_semaphore_win32");
    GLAD_GL_EXT_separate_depth_stencil = glad_gl_has_extension(version, exts, num_exts_i, exts_i, "GL_EXT_separate_depth_stencil");
    GLAD_GL_EXT_separate_shader_objects = glad_gl_has_extension(version, exts, num_exts_i, exts_i, "GL_EXT_separate_shader_objects");
    GLAD_GL_EXT_shader_framebuffer_fetch = glad_gl_has_extension(version, exts, num_exts_i, exts_i, "GL_EXT_shader_framebuffer_fetch");
    GLAD_GL_EXT_shader_framebuffer_fetch_non_coherent = glad_gl_has_extension(version, exts, num_exts_i, exts_i, "GL_EXT_shader_framebuffer_fetch_non_coherent");
    GLAD_GL_EXT_shader_group_vote = glad_gl_has_extension(version, exts, num_exts_i, exts_i, "GL_EXT_shader_group_vote");
    GLAD_GL_EXT_shader_implicit_conversions = glad_gl_has_extension(version, exts, num_exts_i, exts_i, "GL_EXT_shader_implicit_conversions");
    GLAD_GL_EXT_shader_integer_mix = glad_gl_has_extension(version, exts, num_exts_i, exts_i, "GL_EXT_shader_integer_mix");
    GLAD_GL_EXT_shader_io_blocks = glad_gl_has_extension(version, exts, num_exts_i, exts_i, "GL_EXT_shader_io_blocks");
    GLAD_GL_EXT_shader_non_constant_global_initializers = glad_gl_has_extension(version, exts, num_exts_i, exts_i, "GL_EXT_shader_non_constant_global_initializers");
    GLAD_GL_EXT_shader_pixel_local_storage = glad_gl_has_extension(version, exts, num_exts_i, exts_i, "GL_EXT_shader_pixel_local_storage");
    GLAD_GL_EXT_shader_pixel_local_storage2 = glad_gl_has_extension(version, exts, num_exts_i, exts_i, "GL_EXT_shader_pixel_local_storage2");
    GLAD_GL_EXT_shader_samples_identical = glad_gl_has_extension(version, exts, num_exts_i, exts_i, "GL_EXT_shader_samples_identical");
    GLAD_GL_EXT_shader_texture_lod = glad_gl_has_extension(version, exts, num_exts_i, exts_i, "GL_EXT_shader_texture_lod");
    GLAD_GL_EXT_shadow_samplers = glad_gl_has_extension(version, exts, num_exts_i, exts_i, "GL_EXT_shadow_samplers");
    GLAD_GL_EXT_sparse_texture = glad_gl_has_extension(version, exts, num_exts_i, exts_i, "GL_EXT_sparse_texture");
    GLAD_GL_EXT_sparse_texture2 = glad_gl_has_extension(version, exts, num_exts_i, exts_i, "GL_EXT_sparse_texture2");
    GLAD_GL_EXT_tessellation_point_size = glad_gl_has_extension(version, exts, num_exts_i, exts_i, "GL_EXT_tessellation_point_size");
    GLAD_GL_EXT_tessellation_shader = glad_gl_has_extension(version, exts, num_exts_i, exts_i, "GL_EXT_tessellation_shader");
    GLAD_GL_EXT_texture_border_clamp = glad_gl_has_extension(version, exts, num_exts_i, exts_i, "GL_EXT_texture_border_clamp");
    GLAD_GL_EXT_texture_buffer = glad_gl_has_extension(version, exts, num_exts_i, exts_i, "GL_EXT_texture_buffer");
    GLAD_GL_EXT_texture_compression_astc_decode_mode = glad_gl_has_extension(version, exts, num_exts_i, exts_i, "GL_EXT_texture_compression_astc_decode_mode");
    GLAD_GL_EXT_texture_compression_bptc = glad_gl_has_extension(version, exts, num_exts_i, exts_i, "GL_EXT_texture_compression_bptc");
    GLAD_GL_EXT_texture_compression_dxt1 = glad_gl_has_extension(version, exts, num_exts_i, exts_i, "GL_EXT_texture_compression_dxt1");
    GLAD_GL_EXT_texture_compression_rgtc = glad_gl_has_extension(version, exts, num_exts_i, exts_i, "GL_EXT_texture_compression_rgtc");
    GLAD_GL_EXT_texture_compression_s3tc = glad_gl_has_extension(version, exts, num_exts_i, exts_i, "GL_EXT_texture_compression_s3tc");
    GLAD_GL_EXT_texture_compression_s3tc_srgb = glad_gl_has_extension(version, exts, num_exts_i, exts_i, "GL_EXT_texture_compression_s3tc_srgb");
    GLAD_GL_EXT_texture_cube_map_array = glad_gl_has_extension(version, exts, num_exts_i, exts_i, "GL_EXT_texture_cube_map_array");
    GLAD_GL_EXT_texture_filter_anisotropic = glad_gl_has_extension(version, exts, num_exts_i, exts_i, "GL_EXT_texture_filter_anisotropic");
    GLAD_GL_EXT_texture_filter_minmax = glad_gl_has_extension(version, exts, num_exts_i, exts_i, "GL_EXT_texture_filter_minmax");
    GLAD_GL_EXT_texture_format_BGRA8888 = glad_gl_has_extension(version, exts, num_exts_i, exts_i, "GL_EXT_texture_format_BGRA8888");
    GLAD_GL_EXT_texture_format_sRGB_override = glad_gl_has_extension(version, exts, num_exts_i, exts_i, "GL_EXT_texture_format_sRGB_override");
    GLAD_GL_EXT_texture_mirror_clamp_to_edge = glad_gl_has_extension(version, exts, num_exts_i, exts_i, "GL_EXT_texture_mirror_clamp_to_edge");
    GLAD_GL_EXT_texture_norm16 = glad_gl_has_extension(version, exts, num_exts_i, exts_i, "GL_EXT_texture_norm16");
    GLAD_GL_EXT_texture_query_lod = glad_gl_has_extension(version, exts, num_exts_i, exts_i, "GL_EXT_texture_query_lod");
    GLAD_GL_EXT_texture_rg = glad_gl_has_extension(version, exts, num_exts_i, exts_i, "GL_EXT_texture_rg");
    GLAD_GL_EXT_texture_sRGB_R8 = glad_gl_has_extension(version, exts, num_exts_i, exts_i, "GL_EXT_texture_sRGB_R8");
    GLAD_GL_EXT_texture_sRGB_RG8 = glad_gl_has_extension(version, exts, num_exts_i, exts_i, "GL_EXT_texture_sRGB_RG8");
    GLAD_GL_EXT_texture_sRGB_decode = glad_gl_has_extension(version, exts, num_exts_i, exts_i, "GL_EXT_texture_sRGB_decode");
    GLAD_GL_EXT_texture_shadow_lod = glad_gl_has_extension(version, exts, num_exts_i, exts_i, "GL_EXT_texture_shadow_lod");
    GLAD_GL_EXT_texture_storage = glad_gl_has_extension(version, exts, num_exts_i, exts_i, "GL_EXT_texture_storage");
    GLAD_GL_EXT_texture_storage_compression = glad_gl_has_extension(version, exts, num_exts_i, exts_i, "GL_EXT_texture_storage_compression");
    GLAD_GL_EXT_texture_type_2_10_10_10_REV = glad_gl_has_extension(version, exts, num_exts_i, exts_i, "GL_EXT_texture_type_2_10_10_10_REV");
    GLAD_GL_EXT_texture_view = glad_gl_has_extension(version, exts, num_exts_i, exts_i, "GL_EXT_texture_view");
    GLAD_GL_EXT_unpack_subimage = glad_gl_has_extension(version, exts, num_exts_i, exts_i, "GL_EXT_unpack_subimage");
    GLAD_GL_EXT_win32_keyed_mutex = glad_gl_has_extension(version, exts, num_exts_i, exts_i, "GL_EXT_win32_keyed_mutex");
    GLAD_GL_EXT_window_rectangles = glad_gl_has_extension(version, exts, num_exts_i, exts_i, "GL_EXT_window_rectangles");
    GLAD_GL_FJ_shader_binary_GCCSO = glad_gl_has_extension(version, exts, num_exts_i, exts_i, "GL_FJ_shader_binary_GCCSO");
    GLAD_GL_IMG_bindless_texture = glad_gl_has_extension(version, exts, num_exts_i, exts_i, "GL_IMG_bindless_texture");
    GLAD_GL_IMG_framebuffer_downsample = glad_gl_has_extension(version, exts, num_exts_i, exts_i, "GL_IMG_framebuffer_downsample");
    GLAD_GL_IMG_multisampled_render_to_texture = glad_gl_has_extension(version, exts, num_exts_i, exts_i, "GL_IMG_multisampled_render_to_texture");
    GLAD_GL_IMG_program_binary = glad_gl_has_extension(version, exts, num_exts_i, exts_i, "GL_IMG_program_binary");
    GLAD_GL_IMG_read_format = glad_gl_has_extension(version, exts, num_exts_i, exts_i, "GL_IMG_read_format");
    GLAD_GL_IMG_shader_binary = glad_gl_has_extension(version, exts, num_exts_i, exts_i, "GL_IMG_shader_binary");
    GLAD_GL_IMG_texture_compression_pvrtc = glad_gl_has_extension(version, exts, num_exts_i, exts_i, "GL_IMG_texture_compression_pvrtc");
    GLAD_GL_IMG_texture_compression_pvrtc2 = glad_gl_has_extension(version, exts, num_exts_i, exts_i, "GL_IMG_texture_compression_pvrtc2");
    GLAD_GL_IMG_texture_filter_cubic = glad_gl_has_extension(version, exts, num_exts_i, exts_i, "GL_IMG_texture_filter_cubic");
    GLAD_GL_INTEL_blackhole_render = glad_gl_has_extension(version, exts, num_exts_i, exts_i, "GL_INTEL_blackhole_render");
    GLAD_GL_INTEL_conservative_rasterization = glad_gl_has_extension(version, exts, num_exts_i, exts_i, "GL_INTEL_conservative_rasterization");
    GLAD_GL_INTEL_framebuffer_CMAA = glad_gl_has_extension(version, exts, num_exts_i, exts_i, "GL_INTEL_framebuffer_CMAA");
    GLAD_GL_INTEL_performance_query = glad_gl_has_extension(version, exts, num_exts_i, exts_i, "GL_INTEL_performance_query");
    GLAD_GL_KHR_blend_equation_advanced = glad_gl_has_extension(version, exts, num_exts_i, exts_i, "GL_KHR_blend_equation_advanced");
    GLAD_GL_KHR_blend_equation_advanced_coherent = glad_gl_has_extension(version, exts, num_exts_i, exts_i, "GL_KHR_blend_equation_advanced_coherent");
    GLAD_GL_KHR_context_flush_control = glad_gl_has_extension(version, exts, num_exts_i, exts_i, "GL_KHR_context_flush_control");
    GLAD_GL_KHR_debug = glad_gl_has_extension(version, exts, num_exts_i, exts_i, "GL_KHR_debug");
    GLAD_GL_KHR_no_error = glad_gl_has_extension(version, exts, num_exts_i, exts_i, "GL_KHR_no_error");
    GLAD_GL_KHR_parallel_shader_compile = glad_gl_has_extension(version, exts, num_exts_i, exts_i, "GL_KHR_parallel_shader_compile");
    GLAD_GL_KHR_robust_buffer_access_behavior = glad_gl_has_extension(version, exts, num_exts_i, exts_i, "GL_KHR_robust_buffer_access_behavior");
    GLAD_GL_KHR_robustness = glad_gl_has_extension(version, exts, num_exts_i, exts_i, "GL_KHR_robustness");
    GLAD_GL_KHR_shader_subgroup = glad_gl_has_extension(version, exts, num_exts_i, exts_i, "GL_KHR_shader_subgroup");
    GLAD_GL_KHR_texture_compression_astc_hdr = glad_gl_has_extension(version, exts, num_exts_i, exts_i, "GL_KHR_texture_compression_astc_hdr");
    GLAD_GL_KHR_texture_compression_astc_ldr = glad_gl_has_extension(version, exts, num_exts_i, exts_i, "GL_KHR_texture_compression_astc_ldr");
    GLAD_GL_KHR_texture_compression_astc_sliced_3d = glad_gl_has_extension(version, exts, num_exts_i, exts_i, "GL_KHR_texture_compression_astc_sliced_3d");
    GLAD_GL_MESA_bgra = glad_gl_has_extension(version, exts, num_exts_i, exts_i, "GL_MESA_bgra");
    GLAD_GL_MESA_framebuffer_flip_x = glad_gl_has_extension(version, exts, num_exts_i, exts_i, "GL_MESA_framebuffer_flip_x");
    GLAD_GL_MESA_framebuffer_flip_y = glad_gl_has_extension(version, exts, num_exts_i, exts_i, "GL_MESA_framebuffer_flip_y");
    GLAD_GL_MESA_framebuffer_swap_xy = glad_gl_has_extension(version, exts, num_exts_i, exts_i, "GL_MESA_framebuffer_swap_xy");
    GLAD_GL_MESA_program_binary_formats = glad_gl_has_extension(version, exts, num_exts_i, exts_i, "GL_MESA_program_binary_formats");
    GLAD_GL_MESA_shader_integer_functions = glad_gl_has_extension(version, exts, num_exts_i, exts_i, "GL_MESA_shader_integer_functions");
    GLAD_GL_NVX_blend_equation_advanced_multi_draw_buffers = glad_gl_has_extension(version, exts, num_exts_i, exts_i, "GL_NVX_blend_equation_advanced_multi_draw_buffers");
    GLAD_GL_NV_bindless_texture = glad_gl_has_extension(version, exts, num_exts_i, exts_i, "GL_NV_bindless_texture");
    GLAD_GL_NV_blend_equation_advanced = glad_gl_has_extension(version, exts, num_exts_i, exts_i, "GL_NV_blend_equation_advanced");
    GLAD_GL_NV_blend_equation_advanced_coherent = glad_gl_has_extension(version, exts, num_exts_i, exts_i, "GL_NV_blend_equation_advanced_coherent");
    GLAD_GL_NV_blend_minmax_factor = glad_gl_has_extension(version, exts, num_exts_i, exts_i, "GL_NV_blend_minmax_factor");
    GLAD_GL_NV_clip_space_w_scaling = glad_gl_has_extension(version, exts, num_exts_i, exts_i, "GL_NV_clip_space_w_scaling");
    GLAD_GL_NV_compute_shader_derivatives = glad_gl_has_extension(version, exts, num_exts_i, exts_i, "GL_NV_compute_shader_derivatives");
    GLAD_GL_NV_conditional_render = glad_gl_has_extension(version, exts, num_exts_i, exts_i, "GL_NV_conditional_render");
    GLAD_GL_NV_conservative_raster = glad_gl_has_extension(version, exts, num_exts_i, exts_i, "GL_NV_conservative_raster");
    GLAD_GL_NV_conservative_raster_pre_snap = glad_gl_has_extension(version, exts, num_exts_i, exts_i, "GL_NV_conservative_raster_pre_snap");
    GLAD_GL_NV_conservative_raster_pre_snap_triangles = glad_gl_has_extension(version, exts, num_exts_i, exts_i, "GL_NV_conservative_raster_pre_snap_triangles");
    GLAD_GL_NV_copy_buffer = glad_gl_has_extension(version, exts, num_exts_i, exts_i, "GL_NV_copy_buffer");
    GLAD_GL_NV_coverage_sample = glad_gl_has_extension(version, exts, num_exts_i, exts_i, "GL_NV_coverage_sample");
    GLAD_GL_NV_depth_nonlinear = glad_gl_has_extension(version, exts, num_exts_i, exts_i, "GL_NV_depth_nonlinear");
    GLAD_GL_NV_draw_buffers = glad_gl_has_extension(version, exts, num_exts_i, exts_i, "GL_NV_draw_buffers");
    GLAD_GL_NV_draw_instanced = glad_gl_has_extension(version, exts, num_exts_i, exts_i, "GL_NV_draw_instanced");
    GLAD_GL_NV_draw_vulkan_image = glad_gl_has_extension(version, exts, num_exts_i, exts_i, "GL_NV_draw_vulkan_image");
    GLAD_GL_NV_explicit_attrib_location = glad_gl_has_extension(version, exts, num_exts_i, exts_i, "GL_NV_explicit_attrib_location");
    GLAD_GL_NV_fbo_color_attachments = glad_gl_has_extension(version, exts, num_exts_i, exts_i, "GL_NV_fbo_color_attachments");
    GLAD_GL_NV_fence = glad_gl_has_extension(version, exts, num_exts_i, exts_i, "GL_NV_fence");
    GLAD_GL_NV_fill_rectangle = glad_gl_has_extension(version, exts, num_exts_i, exts_i, "GL_NV_fill_rectangle");
    GLAD_GL_NV_fragment_coverage_to_color = glad_gl_has_extension(version, exts, num_exts_i, exts_i, "GL_NV_fragment_coverage_to_color");
    GLAD_GL_NV_fragment_shader_barycentric = glad_gl_has_extension(version, exts, num_exts_i, exts_i, "GL_NV_fragment_shader_barycentric");
    GLAD_GL_NV_fragment_shader_interlock = glad_gl_has_extension(version, exts, num_exts_i, exts_i, "GL_NV_fragment_shader_interlock");
    GLAD_GL_NV_framebuffer_blit = glad_gl_has_extension(version, exts, num_exts_i, exts_i, "GL_NV_framebuffer_blit");
    GLAD_GL_NV_framebuffer_mixed_samples = glad_gl_has_extension(version, exts, num_exts_i, exts_i, "GL_NV_framebuffer_mixed_samples");
    GLAD_GL_NV_framebuffer_multisample = glad_gl_has_extension(version, exts, num_exts_i, exts_i, "GL_NV_framebuffer_multisample");
    GLAD_GL_NV_generate_mipmap_sRGB = glad_gl_has_extension(version, exts, num_exts_i, exts_i, "GL_NV_generate_mipmap_sRGB");
    GLAD_GL_NV_geometry_shader_passthrough = glad_gl_has_extension(version, exts, num_exts_i, exts_i, "GL_NV_geometry_shader_passthrough");
    GLAD_GL_NV_gpu_shader5 = glad_gl_has_extension(version, exts, num_exts_i, exts_i, "GL_NV_gpu_shader5");
    GLAD_GL_NV_image_formats = glad_gl_has_extension(version, exts, num_exts_i, exts_i, "GL_NV_image_formats");
    GLAD_GL_NV_instanced_arrays = glad_gl_has_extension(version, exts, num_exts_i, exts_i, "GL_NV_instanced_arrays");
    GLAD_GL_NV_internalformat_sample_query = glad_gl_has_extension(version, exts, num_exts_i, exts_i, "GL_NV_internalformat_sample_query");
    GLAD_GL_NV_memory_attachment = glad_gl_has_extension(version, exts, num_exts_i, exts_i, "GL_NV_memory_attachment");
    GLAD_GL_NV_memory_object_sparse = glad_gl_has_extension(version, exts, num_exts_i, exts_i, "GL_NV_memory_object_sparse");
    GLAD_GL_NV_mesh_shader = glad_gl_has_extension(version, exts, num_exts_i, exts_i, "GL_NV_mesh_shader");
    GLAD_GL_NV_non_square_matrices = glad_gl_has_extension(version, exts, num_exts_i, exts_i, "GL_NV_non_square_matrices");
    GLAD_GL_NV_path_rendering = glad_gl_has_extension(version, exts, num_exts_i, exts_i, "GL_NV_path_rendering");
    GLAD_GL_NV_path_rendering_shared_edge = glad_gl_has_extension(version, exts, num_exts_i, exts_i, "GL_NV_path_rendering_shared_edge");
    GLAD_GL_NV_pixel_buffer_object = glad_gl_has_extension(version, exts, num_exts_i, exts_i, "GL_NV_pixel_buffer_object");
    GLAD_GL_NV_polygon_mode = glad_gl_has_extension(version, exts, num_exts_i, exts_i, "GL_NV_polygon_mode");
    GLAD_GL_NV_primitive_shading_rate = glad_gl_has_extension(version, exts, num_exts_i, exts_i, "GL_NV_primitive_shading_rate");
    GLAD_GL_NV_read_buffer = glad_gl_has_extension(version, exts, num_exts_i, exts_i, "GL_NV_read_buffer");
    GLAD_GL_NV_read_buffer_front = glad_gl_has_extension(version, exts, num_exts_i, exts_i, "GL_NV_read_buffer_front");
    GLAD_GL_NV_read_depth = glad_gl_has_extension(version, exts, num_exts_i, exts_i, "GL_NV_read_depth");
    GLAD_GL_NV_read_depth_stencil = glad_gl_has_extension(version, exts, num_exts_i, exts_i, "GL_NV_read_depth_stencil");
    GLAD_GL_NV_read_stencil = glad_gl_has_extension(version, exts, num_exts_i, exts_i, "GL_NV_read_stencil");
    GLAD_GL_NV_representative_fragment_test = glad_gl_has_extension(version, exts, num_exts_i, exts_i, "GL_NV_representative_fragment_test");
    GLAD_GL_NV_sRGB_formats = glad_gl_has_extension(version, exts, num_exts_i, exts_i, "GL_NV_sRGB_formats");
    GLAD_GL_NV_sample_locations = glad_gl_has_extension(version, exts, num_exts_i, exts_i, "GL_NV_sample_locations");
    GLAD_GL_NV_sample_mask_override_coverage = glad_gl_has_extension(version, exts, num_exts_i, exts_i, "GL_NV_sample_mask_override_coverage");
    GLAD_GL_NV_scissor_exclusive = glad_gl_has_extension(version, exts, num_exts_i, exts_i, "GL_NV_scissor_exclusive");
    GLAD_GL_NV_shader_atomic_fp16_vector = glad_gl_has_extension(version, exts, num_exts_i, exts_i, "GL_NV_shader_atomic_fp16_vector");
    GLAD_GL_NV_shader_noperspective_interpolation = glad_gl_has_extension(version, exts, num_exts_i, exts_i, "GL_NV_shader_noperspective_interpolation");
    GLAD_GL_NV_shader_subgroup_partitioned = glad_gl_has_extension(version, exts, num_exts_i, exts_i, "GL_NV_shader_subgroup_partitioned");
    GLAD_GL_NV_shader_texture_footprint = glad_gl_has_extension(version, exts, num_exts_i, exts_i, "GL_NV_shader_texture_footprint");
    GLAD_GL_NV_shading_rate_image = glad_gl_has_extension(version, exts, num_exts_i, exts_i, "GL_NV_shading_rate_image");
    GLAD_GL_NV_shadow_samplers_array = glad_gl_has_extension(version, exts, num_exts_i, exts_i, "GL_NV_shadow_samplers_array");
    GLAD_GL_NV_shadow_samplers_cube = glad_gl_has_extension(version, exts, num_exts_i, exts_i, "GL_NV_shadow_samplers_cube");
    GLAD_GL_NV_stereo_view_rendering = glad_gl_has_extension(version, exts, num_exts_i, exts_i, "GL_NV_stereo_view_rendering");
    GLAD_GL_NV_texture_border_clamp = glad_gl_has_extension(version, exts, num_exts_i, exts_i, "GL_NV_texture_border_clamp");
    GLAD_GL_NV_texture_compression_s3tc_update = glad_gl_has_extension(version, exts, num_exts_i, exts_i, "GL_NV_texture_compression_s3tc_update");
    GLAD_GL_NV_texture_npot_2D_mipmap = glad_gl_has_extension(version, exts, num_exts_i, exts_i, "GL_NV_texture_npot_2D_mipmap");
    GLAD_GL_NV_timeline_semaphore = glad_gl_has_extension(version, exts, num_exts_i, exts_i, "GL_NV_timeline_semaphore");
    GLAD_GL_NV_viewport_array = glad_gl_has_extension(version, exts, num_exts_i, exts_i, "GL_NV_viewport_array");
    GLAD_GL_NV_viewport_array2 = glad_gl_has_extension(version, exts, num_exts_i, exts_i, "GL_NV_viewport_array2");
    GLAD_GL_NV_viewport_swizzle = glad_gl_has_extension(version, exts, num_exts_i, exts_i, "GL_NV_viewport_swizzle");
    GLAD_GL_OES_EGL_image = glad_gl_has_extension(version, exts, num_exts_i, exts_i, "GL_OES_EGL_image");
    GLAD_GL_OES_EGL_image_external = glad_gl_has_extension(version, exts, num_exts_i, exts_i, "GL_OES_EGL_image_external");
    GLAD_GL_OES_EGL_image_external_essl3 = glad_gl_has_extension(version, exts, num_exts_i, exts_i, "GL_OES_EGL_image_external_essl3");
    GLAD_GL_OES_compressed_ETC1_RGB8_sub_texture = glad_gl_has_extension(version, exts, num_exts_i, exts_i, "GL_OES_compressed_ETC1_RGB8_sub_texture");
    GLAD_GL_OES_compressed_ETC1_RGB8_texture = glad_gl_has_extension(version, exts, num_exts_i, exts_i, "GL_OES_compressed_ETC1_RGB8_texture");
    GLAD_GL_OES_compressed_paletted_texture = glad_gl_has_extension(version, exts, num_exts_i, exts_i, "GL_OES_compressed_paletted_texture");
    GLAD_GL_OES_copy_image = glad_gl_has_extension(version, exts, num_exts_i, exts_i, "GL_OES_copy_image");
    GLAD_GL_OES_depth24 = glad_gl_has_extension(version, exts, num_exts_i, exts_i, "GL_OES_depth24");
    GLAD_GL_OES_depth32 = glad_gl_has_extension(version, exts, num_exts_i, exts_i, "GL_OES_depth32");
    GLAD_GL_OES_depth_texture = glad_gl_has_extension(version, exts, num_exts_i, exts_i, "GL_OES_depth_texture");
    GLAD_GL_OES_draw_buffers_indexed = glad_gl_has_extension(version, exts, num_exts_i, exts_i, "GL_OES_draw_buffers_indexed");
    GLAD_GL_OES_draw_elements_base_vertex = glad_gl_has_extension(version, exts, num_exts_i, exts_i, "GL_OES_draw_elements_base_vertex");
    GLAD_GL_OES_element_index_uint = glad_gl_has_extension(version, exts, num_exts_i, exts_i, "GL_OES_element_index_uint");
    GLAD_GL_OES_fbo_render_mipmap = glad_gl_has_extension(version, exts, num_exts_i, exts_i, "GL_OES_fbo_render_mipmap");
    GLAD_GL_OES_fragment_precision_high = glad_gl_has_extension(version, exts, num_exts_i, exts_i, "GL_OES_fragment_precision_high");
    GLAD_GL_OES_geometry_point_size = glad_gl_has_extension(version, exts, num_exts_i, exts_i, "GL_OES_geometry_point_size");
    GLAD_GL_OES_geometry_shader = glad_gl_has_extension(version, exts, num_exts_i, exts_i, "GL_OES_geometry_shader");
    GLAD_GL_OES_get_program_binary = glad_gl_has_extension(version, exts, num_exts_i, exts_i, "GL_OES_get_program_binary");
    GLAD_GL_OES_gpu_shader5 = glad_gl_has_extension(version, exts, num_exts_i, exts_i, "GL_OES_gpu_shader5");
    GLAD_GL_OES_mapbuffer = glad_gl_has_extension(version, exts, num_exts_i, exts_i, "GL_OES_mapbuffer");
    GLAD_GL_OES_packed_depth_stencil = glad_gl_has_extension(version, exts, num_exts_i, exts_i, "GL_OES_packed_depth_stencil");
    GLAD_GL_OES_primitive_bounding_box = glad_gl_has_extension(version, exts, num_exts_i, exts_i, "GL_OES_primitive_bounding_box");
    GLAD_GL_OES_required_internalformat = glad_gl_has_extension(version, exts, num_exts_i, exts_i, "GL_OES_required_internalformat");
    GLAD_GL_OES_rgb8_rgba8 = glad_gl_has_extension(version, exts, num_exts_i, exts_i, "GL_OES_rgb8_rgba8");
    GLAD_GL_OES_sample_shading = glad_gl_has_extension(version, exts, num_exts_i, exts_i, "GL_OES_sample_shading");
    GLAD_GL_OES_sample_variables = glad_gl_has_extension(version, exts, num_exts_i, exts_i, "GL_OES_sample_variables");
    GLAD_GL_OES_shader_image_atomic = glad_gl_has_extension(version, exts, num_exts_i, exts_i, "GL_OES_shader_image_atomic");
    GLAD_GL_OES_shader_io_blocks = glad_gl_has_extension(version, exts, num_exts_i, exts_i, "GL_OES_shader_io_blocks");
    GLAD_GL_OES_shader_multisample_interpolation = glad_gl_has_extension(version, exts, num_exts_i, exts_i, "GL_OES_shader_multisample_interpolation");
    GLAD_GL_OES_standard_derivatives = glad_gl_has_extension(version, exts, num_exts_i, exts_i, "GL_OES_standard_derivatives");
    GLAD_GL_OES_stencil1 = glad_gl_has_extension(version, exts, num_exts_i, exts_i, "GL_OES_stencil1");
    GLAD_GL_OES_stencil4 = glad_gl_has_extension(version, exts, num_exts_i, exts_i, "GL_OES_stencil4");
    GLAD_GL_OES_surfaceless_context = glad_gl_has_extension(version, exts, num_exts_i, exts_i, "GL_OES_surfaceless_context");
    GLAD_GL_OES_tessellation_point_size = glad_gl_has_extension(version, exts, num_exts_i, exts_i, "GL_OES_tessellation_point_size");
    GLAD_GL_OES_tessellation_shader = glad_gl_has_extension(version, exts, num_exts_i, exts_i, "GL_OES_tessellation_shader");
    GLAD_GL_OES_texture_3D = glad_gl_has_extension(version, exts, num_exts_i, exts_i, "GL_OES_texture_3D");
    GLAD_GL_OES_texture_border_clamp = glad_gl_has_extension(version, exts, num_exts_i, exts_i, "GL_OES_texture_border_clamp");
    GLAD_GL_OES_texture_buffer = glad_gl_has_extension(version, exts, num_exts_i, exts_i, "GL_OES_texture_buffer");
    GLAD_GL_OES_texture_compression_astc = glad_gl_has_extension(version, exts, num_exts_i, exts_i, "GL_OES_texture_compression_astc");
    GLAD_GL_OES_texture_cube_map_array = glad_gl_has_extension(version, exts, num_exts_i, exts_i, "GL_OES_texture_cube_map_array");
    GLAD_GL_OES_texture_float = glad_gl_has_extension(version, exts, num_exts_i, exts_i, "GL_OES_texture_float");
    GLAD_GL_OES_texture_float_linear = glad_gl_has_extension(version, exts, num_exts_i, exts_i, "GL_OES_texture_float_linear");
    GLAD_GL_OES_texture_half_float = glad_gl_has_extension(version, exts, num_exts_i, exts_i, "GL_OES_texture_half_float");
    GLAD_GL_OES_texture_half_float_linear = glad_gl_has_extension(version, exts, num_exts_i, exts_i, "GL_OES_texture_half_float_linear");
    GLAD_GL_OES_texture_npot = glad_gl_has_extension(version, exts, num_exts_i, exts_i, "GL_OES_texture_npot");
    GLAD_GL_OES_texture_stencil8 = glad_gl_has_extension(version, exts, num_exts_i, exts_i, "GL_OES_texture_stencil8");
    GLAD_GL_OES_texture_storage_multisample_2d_array = glad_gl_has_extension(version, exts, num_exts_i, exts_i, "GL_OES_texture_storage_multisample_2d_array");
    GLAD_GL_OES_texture_view = glad_gl_has_extension(version, exts, num_exts_i, exts_i, "GL_OES_texture_view");
    GLAD_GL_OES_vertex_array_object = glad_gl_has_extension(version, exts, num_exts_i, exts_i, "GL_OES_vertex_array_object");
    GLAD_GL_OES_vertex_half_float = glad_gl_has_extension(version, exts, num_exts_i, exts_i, "GL_OES_vertex_half_float");
    GLAD_GL_OES_vertex_type_10_10_10_2 = glad_gl_has_extension(version, exts, num_exts_i, exts_i, "GL_OES_vertex_type_10_10_10_2");
    GLAD_GL_OES_viewport_array = glad_gl_has_extension(version, exts, num_exts_i, exts_i, "GL_OES_viewport_array");
    GLAD_GL_OVR_multiview = glad_gl_has_extension(version, exts, num_exts_i, exts_i, "GL_OVR_multiview");
    GLAD_GL_OVR_multiview2 = glad_gl_has_extension(version, exts, num_exts_i, exts_i, "GL_OVR_multiview2");
    GLAD_GL_OVR_multiview_multisampled_render_to_texture = glad_gl_has_extension(version, exts, num_exts_i, exts_i, "GL_OVR_multiview_multisampled_render_to_texture");
    GLAD_GL_QCOM_YUV_texture_gather = glad_gl_has_extension(version, exts, num_exts_i, exts_i, "GL_QCOM_YUV_texture_gather");
    GLAD_GL_QCOM_alpha_test = glad_gl_has_extension(version, exts, num_exts_i, exts_i, "GL_QCOM_alpha_test");
    GLAD_GL_QCOM_binning_control = glad_gl_has_extension(version, exts, num_exts_i, exts_i, "GL_QCOM_binning_control");
    GLAD_GL_QCOM_driver_control = glad_gl_has_extension(version, exts, num_exts_i, exts_i, "GL_QCOM_driver_control");
    GLAD_GL_QCOM_extended_get = glad_gl_has_extension(version, exts, num_exts_i, exts_i, "GL_QCOM_extended_get");
    GLAD_GL_QCOM_extended_get2 = glad_gl_has_extension(version, exts, num_exts_i, exts_i, "GL_QCOM_extended_get2");
    GLAD_GL_QCOM_frame_extrapolation = glad_gl_has_extension(version, exts, num_exts_i, exts_i, "GL_QCOM_frame_extrapolation");
    GLAD_GL_QCOM_framebuffer_foveated = glad_gl_has_extension(version, exts, num_exts_i, exts_i, "GL_QCOM_framebuffer_foveated");
    GLAD_GL_QCOM_motion_estimation = glad_gl_has_extension(version, exts, num_exts_i, exts_i, "GL_QCOM_motion_estimation");
    GLAD_GL_QCOM_perfmon_global_mode = glad_gl_has_extension(version, exts, num_exts_i, exts_i, "GL_QCOM_perfmon_global_mode");
    GLAD_GL_QCOM_render_shared_exponent = glad_gl_has_extension(version, exts, num_exts_i, exts_i, "GL_QCOM_render_shared_exponent");
    GLAD_GL_QCOM_shader_framebuffer_fetch_noncoherent = glad_gl_has_extension(version, exts, num_exts_i, exts_i, "GL_QCOM_shader_framebuffer_fetch_noncoherent");
    GLAD_GL_QCOM_shader_framebuffer_fetch_rate = glad_gl_has_extension(version, exts, num_exts_i, exts_i, "GL_QCOM_shader_framebuffer_fetch_rate");
    GLAD_GL_QCOM_shading_rate = glad_gl_has_extension(version, exts, num_exts_i, exts_i, "GL_QCOM_shading_rate");
    GLAD_GL_QCOM_texture_foveated = glad_gl_has_extension(version, exts, num_exts_i, exts_i, "GL_QCOM_texture_foveated");
    GLAD_GL_QCOM_texture_foveated2 = glad_gl_has_extension(version, exts, num_exts_i, exts_i, "GL_QCOM_texture_foveated2");
    GLAD_GL_QCOM_texture_foveated_subsampled_layout = glad_gl_has_extension(version, exts, num_exts_i, exts_i, "GL_QCOM_texture_foveated_subsampled_layout");
    GLAD_GL_QCOM_tiled_rendering = glad_gl_has_extension(version, exts, num_exts_i, exts_i, "GL_QCOM_tiled_rendering");
    GLAD_GL_QCOM_writeonly_rendering = glad_gl_has_extension(version, exts, num_exts_i, exts_i, "GL_QCOM_writeonly_rendering");
    GLAD_GL_VIV_shader_binary = glad_gl_has_extension(version, exts, num_exts_i, exts_i, "GL_VIV_shader_binary");

    glad_gl_free_extensions(exts_i, num_exts_i);

    return 1;
}

static int glad_gl_find_core_gles2(void) {
    int i;
    const char* version;
    const char* prefixes[] = {
        "OpenGL ES-CM ",
        "OpenGL ES-CL ",
        "OpenGL ES ",
        "OpenGL SC ",
        NULL
    };
    int major = 0;
    int minor = 0;
    version = (const char*) glad_glGetString(GL_VERSION);
    if (!version) return 0;
    for (i = 0;  prefixes[i];  i++) {
        const size_t length = strlen(prefixes[i]);
        if (strncmp(version, prefixes[i], length) == 0) {
            version += length;
            break;
        }
    }

    GLAD_IMPL_UTIL_SSCANF(version, "%d.%d", &major, &minor);

    GLAD_GL_ES_VERSION_2_0 = (major == 2 && minor >= 0) || major > 2;
    GLAD_GL_ES_VERSION_3_0 = (major == 3 && minor >= 0) || major > 3;
    GLAD_GL_ES_VERSION_3_1 = (major == 3 && minor >= 1) || major > 3;
    GLAD_GL_ES_VERSION_3_2 = (major == 3 && minor >= 2) || major > 3;

    return GLAD_MAKE_VERSION(major, minor);
}

int gladLoadGLES2UserPtr( GLADuserptrloadfunc load, void *userptr) {
    int version;

    glad_glGetString = (PFNGLGETSTRINGPROC) load(userptr, "glGetString");
    if(glad_glGetString == NULL) return 0;
    if(glad_glGetString(GL_VERSION) == NULL) return 0;
    version = glad_gl_find_core_gles2();

    glad_gl_load_GL_ES_VERSION_2_0(load, userptr);
    glad_gl_load_GL_ES_VERSION_3_0(load, userptr);
    glad_gl_load_GL_ES_VERSION_3_1(load, userptr);
    glad_gl_load_GL_ES_VERSION_3_2(load, userptr);

    if (!glad_gl_find_extensions_gles2(version)) return 0;
    glad_gl_load_GL_AMD_framebuffer_multisample_advanced(load, userptr);
    glad_gl_load_GL_AMD_performance_monitor(load, userptr);
    glad_gl_load_GL_ANGLE_framebuffer_blit(load, userptr);
    glad_gl_load_GL_ANGLE_framebuffer_multisample(load, userptr);
    glad_gl_load_GL_ANGLE_instanced_arrays(load, userptr);
    glad_gl_load_GL_ANGLE_translated_shader_source(load, userptr);
    glad_gl_load_GL_APPLE_copy_texture_levels(load, userptr);
    glad_gl_load_GL_APPLE_framebuffer_multisample(load, userptr);
    glad_gl_load_GL_APPLE_sync(load, userptr);
    glad_gl_load_GL_EXT_EGL_image_storage(load, userptr);
    glad_gl_load_GL_EXT_base_instance(load, userptr);
    glad_gl_load_GL_EXT_blend_func_extended(load, userptr);
    glad_gl_load_GL_EXT_buffer_storage(load, userptr);
    glad_gl_load_GL_EXT_clear_texture(load, userptr);
    glad_gl_load_GL_EXT_clip_control(load, userptr);
    glad_gl_load_GL_EXT_copy_image(load, userptr);
    glad_gl_load_GL_EXT_debug_label(load, userptr);
    glad_gl_load_GL_EXT_debug_marker(load, userptr);
    glad_gl_load_GL_EXT_discard_framebuffer(load, userptr);
    glad_gl_load_GL_EXT_disjoint_timer_query(load, userptr);
    glad_gl_load_GL_EXT_draw_buffers(load, userptr);
    glad_gl_load_GL_EXT_draw_buffers_indexed(load, userptr);
    glad_gl_load_GL_EXT_draw_elements_base_vertex(load, userptr);
    glad_gl_load_GL_EXT_draw_instanced(load, userptr);
    glad_gl_load_GL_EXT_draw_transform_feedback(load, userptr);
    glad_gl_load_GL_EXT_external_buffer(load, userptr);
    glad_gl_load_GL_EXT_fragment_shading_rate(load, userptr);
    glad_gl_load_GL_EXT_geometry_shader(load, userptr);
    glad_gl_load_GL_EXT_instanced_arrays(load, userptr);
    glad_gl_load_GL_EXT_map_buffer_range(load, userptr);
    glad_gl_load_GL_EXT_memory_object(load, userptr);
    glad_gl_load_GL_EXT_memory_object_fd(load, userptr);
    glad_gl_load_GL_EXT_memory_object_win32(load, userptr);
    glad_gl_load_GL_EXT_multi_draw_arrays(load, userptr);
    glad_gl_load_GL_EXT_multi_draw_indirect(load, userptr);
    glad_gl_load_GL_EXT_multisampled_render_to_texture(load, userptr);
    glad_gl_load_GL_EXT_multiview_draw_buffers(load, userptr);
    glad_gl_load_GL_EXT_occlusion_query_boolean(load, userptr);
    glad_gl_load_GL_EXT_polygon_offset_clamp(load, userptr);
    glad_gl_load_GL_EXT_primitive_bounding_box(load, userptr);
    glad_gl_load_GL_EXT_raster_multisample(load, userptr);
    glad_gl_load_GL_EXT_robustness(load, userptr);
    glad_gl_load_GL_EXT_semaphore(load, userptr);
    glad_gl_load_GL_EXT_semaphore_fd(load, userptr);
    glad_gl_load_GL_EXT_semaphore_win32(load, userptr);
    glad_gl_load_GL_EXT_separate_shader_objects(load, userptr);
    glad_gl_load_GL_EXT_shader_framebuffer_fetch_non_coherent(load, userptr);
    glad_gl_load_GL_EXT_shader_pixel_local_storage2(load, userptr);
    glad_gl_load_GL_EXT_sparse_texture(load, userptr);
    glad_gl_load_GL_EXT_tessellation_shader(load, userptr);
    glad_gl_load_GL_EXT_texture_border_clamp(load, userptr);
    glad_gl_load_GL_EXT_texture_buffer(load, userptr);
    glad_gl_load_GL_EXT_texture_storage(load, userptr);
    glad_gl_load_GL_EXT_texture_storage_compression(load, userptr);
    glad_gl_load_GL_EXT_texture_view(load, userptr);
    glad_gl_load_GL_EXT_win32_keyed_mutex(load, userptr);
    glad_gl_load_GL_EXT_window_rectangles(load, userptr);
    glad_gl_load_GL_IMG_bindless_texture(load, userptr);
    glad_gl_load_GL_IMG_framebuffer_downsample(load, userptr);
    glad_gl_load_GL_IMG_multisampled_render_to_texture(load, userptr);
    glad_gl_load_GL_INTEL_framebuffer_CMAA(load, userptr);
    glad_gl_load_GL_INTEL_performance_query(load, userptr);
    glad_gl_load_GL_KHR_blend_equation_advanced(load, userptr);
    glad_gl_load_GL_KHR_debug(load, userptr);
    glad_gl_load_GL_KHR_parallel_shader_compile(load, userptr);
    glad_gl_load_GL_KHR_robustness(load, userptr);
    glad_gl_load_GL_MESA_framebuffer_flip_y(load, userptr);
    glad_gl_load_GL_NV_bindless_texture(load, userptr);
    glad_gl_load_GL_NV_blend_equation_advanced(load, userptr);
    glad_gl_load_GL_NV_clip_space_w_scaling(load, userptr);
    glad_gl_load_GL_NV_conditional_render(load, userptr);
    glad_gl_load_GL_NV_conservative_raster(load, userptr);
    glad_gl_load_GL_NV_conservative_raster_pre_snap_triangles(load, userptr);
    glad_gl_load_GL_NV_copy_buffer(load, userptr);
    glad_gl_load_GL_NV_coverage_sample(load, userptr);
    glad_gl_load_GL_NV_draw_buffers(load, userptr);
    glad_gl_load_GL_NV_draw_instanced(load, userptr);
    glad_gl_load_GL_NV_draw_vulkan_image(load, userptr);
    glad_gl_load_GL_NV_fence(load, userptr);
    glad_gl_load_GL_NV_fragment_coverage_to_color(load, userptr);
    glad_gl_load_GL_NV_framebuffer_blit(load, userptr);
    glad_gl_load_GL_NV_framebuffer_mixed_samples(load, userptr);
    glad_gl_load_GL_NV_framebuffer_multisample(load, userptr);
    glad_gl_load_GL_NV_gpu_shader5(load, userptr);
    glad_gl_load_GL_NV_instanced_arrays(load, userptr);
    glad_gl_load_GL_NV_internalformat_sample_query(load, userptr);
    glad_gl_load_GL_NV_memory_attachment(load, userptr);
    glad_gl_load_GL_NV_memory_object_sparse(load, userptr);
    glad_gl_load_GL_NV_mesh_shader(load, userptr);
    glad_gl_load_GL_NV_non_square_matrices(load, userptr);
    glad_gl_load_GL_NV_path_rendering(load, userptr);
    glad_gl_load_GL_NV_polygon_mode(load, userptr);
    glad_gl_load_GL_NV_read_buffer(load, userptr);
    glad_gl_load_GL_NV_sample_locations(load, userptr);
    glad_gl_load_GL_NV_scissor_exclusive(load, userptr);
    glad_gl_load_GL_NV_shading_rate_image(load, userptr);
    glad_gl_load_GL_NV_timeline_semaphore(load, userptr);
    glad_gl_load_GL_NV_viewport_array(load, userptr);
    glad_gl_load_GL_NV_viewport_swizzle(load, userptr);
    glad_gl_load_GL_OES_EGL_image(load, userptr);
    glad_gl_load_GL_OES_copy_image(load, userptr);
    glad_gl_load_GL_OES_draw_buffers_indexed(load, userptr);
    glad_gl_load_GL_OES_draw_elements_base_vertex(load, userptr);
    glad_gl_load_GL_OES_geometry_shader(load, userptr);
    glad_gl_load_GL_OES_get_program_binary(load, userptr);
    glad_gl_load_GL_OES_mapbuffer(load, userptr);
    glad_gl_load_GL_OES_primitive_bounding_box(load, userptr);
    glad_gl_load_GL_OES_sample_shading(load, userptr);
    glad_gl_load_GL_OES_tessellation_shader(load, userptr);
    glad_gl_load_GL_OES_texture_3D(load, userptr);
    glad_gl_load_GL_OES_texture_border_clamp(load, userptr);
    glad_gl_load_GL_OES_texture_buffer(load, userptr);
    glad_gl_load_GL_OES_texture_storage_multisample_2d_array(load, userptr);
    glad_gl_load_GL_OES_texture_view(load, userptr);
    glad_gl_load_GL_OES_vertex_array_object(load, userptr);
    glad_gl_load_GL_OES_viewport_array(load, userptr);
    glad_gl_load_GL_OVR_multiview(load, userptr);
    glad_gl_load_GL_OVR_multiview_multisampled_render_to_texture(load, userptr);
    glad_gl_load_GL_QCOM_alpha_test(load, userptr);
    glad_gl_load_GL_QCOM_driver_control(load, userptr);
    glad_gl_load_GL_QCOM_extended_get(load, userptr);
    glad_gl_load_GL_QCOM_extended_get2(load, userptr);
    glad_gl_load_GL_QCOM_frame_extrapolation(load, userptr);
    glad_gl_load_GL_QCOM_framebuffer_foveated(load, userptr);
    glad_gl_load_GL_QCOM_motion_estimation(load, userptr);
    glad_gl_load_GL_QCOM_shader_framebuffer_fetch_noncoherent(load, userptr);
    glad_gl_load_GL_QCOM_shading_rate(load, userptr);
    glad_gl_load_GL_QCOM_texture_foveated(load, userptr);
    glad_gl_load_GL_QCOM_tiled_rendering(load, userptr);



    return version;
}


int gladLoadGLES2( GLADloadfunc load) {
    return gladLoadGLES2UserPtr( glad_gl_get_proc_from_userptr, GLAD_GNUC_EXTENSION (void*) load);
}



 

#ifdef GLAD_GLES2

#ifndef GLAD_LOADER_LIBRARY_C_
#define GLAD_LOADER_LIBRARY_C_

#include <stddef.h>
#include <stdlib.h>

#if GLAD_PLATFORM_WIN32
#include <windows.h>
#else
#include <dlfcn.h>
#endif


static void* glad_get_dlopen_handle(const char *lib_names[], int length) {
    void *handle = NULL;
    int i;

    for (i = 0; i < length; ++i) {
#if GLAD_PLATFORM_WIN32
  #if GLAD_PLATFORM_UWP
        size_t buffer_size = (strlen(lib_names[i]) + 1) * sizeof(WCHAR);
        LPWSTR buffer = (LPWSTR) malloc(buffer_size);
        if (buffer != NULL) {
            int ret = MultiByteToWideChar(CP_ACP, 0, lib_names[i], -1, buffer, buffer_size);
            if (ret != 0) {
                handle = (void*) LoadPackagedLibrary(buffer, 0);
            }
            free((void*) buffer);
        }
  #else
        handle = (void*) LoadLibraryA(lib_names[i]);
  #endif
#else
        handle = dlopen(lib_names[i], RTLD_LAZY | RTLD_LOCAL);
#endif
        if (handle != NULL) {
            return handle;
        }
    }

    return NULL;
}

static void glad_close_dlopen_handle(void* handle) {
    if (handle != NULL) {
#if GLAD_PLATFORM_WIN32
        FreeLibrary((HMODULE) handle);
#else
        dlclose(handle);
#endif
    }
}

static GLADapiproc glad_dlsym_handle(void* handle, const char *name) {
    if (handle == NULL) {
        return NULL;
    }

#if GLAD_PLATFORM_WIN32
    return (GLADapiproc) GetProcAddress((HMODULE) handle, name);
#else
    return GLAD_GNUC_EXTENSION (GLADapiproc) dlsym(handle, name);
#endif
}

#endif /* GLAD_LOADER_LIBRARY_C_ */

#if GLAD_PLATFORM_EMSCRIPTEN
  typedef void* (GLAD_API_PTR *PFNEGLGETPROCADDRESSPROC)(const char *name);
  extern void* emscripten_GetProcAddress(const char *name);
#else
  #include <glad/egl.h>
#endif


struct _glad_gles2_userptr {
    void *handle;
    PFNEGLGETPROCADDRESSPROC get_proc_address_ptr;
};


static GLADapiproc glad_gles2_get_proc(void *vuserptr, const char* name) {
    struct _glad_gles2_userptr userptr = *(struct _glad_gles2_userptr*) vuserptr;
    GLADapiproc result = NULL;

#if !GLAD_PLATFORM_EMSCRIPTEN
    result = glad_dlsym_handle(userptr.handle, name);
#endif
    if (result == NULL) {
        result = userptr.get_proc_address_ptr(name);
    }

    return result;
}

static void* _gles2_handle = NULL;

static void* glad_gles2_dlopen_handle(void) {
#if GLAD_PLATFORM_EMSCRIPTEN
#elif GLAD_PLATFORM_APPLE
    static const char *NAMES[] = {"libGLESv2.dylib"};
#elif GLAD_PLATFORM_WIN32
    static const char *NAMES[] = {"GLESv2.dll", "libGLESv2.dll"};
#else
    static const char *NAMES[] = {"libGLESv2.so.2", "libGLESv2.so"};
#endif

#if GLAD_PLATFORM_EMSCRIPTEN
    return NULL;
#else
    if (_gles2_handle == NULL) {
        _gles2_handle = glad_get_dlopen_handle(NAMES, sizeof(NAMES) / sizeof(NAMES[0]));
    }

    return _gles2_handle;
#endif
}

static struct _glad_gles2_userptr glad_gles2_build_userptr(void *handle) {
    struct _glad_gles2_userptr userptr;
#if GLAD_PLATFORM_EMSCRIPTEN
    userptr.get_proc_address_ptr = emscripten_GetProcAddress;
#else
    userptr.handle = handle;
    userptr.get_proc_address_ptr = eglGetProcAddress;
#endif
    return userptr;
}

int gladLoaderLoadGLES2(void) {
    int version = 0;
    void *handle = NULL;
    int did_load = 0;
    struct _glad_gles2_userptr userptr;

#if GLAD_PLATFORM_EMSCRIPTEN
    userptr.get_proc_address_ptr = emscripten_GetProcAddress;
    version = gladLoadGLES2UserPtr(glad_gles2_get_proc, &userptr);
#else
    if (eglGetProcAddress == NULL) {
        return 0;
    }

    did_load = _gles2_handle == NULL;
    handle = glad_gles2_dlopen_handle();
    if (handle != NULL) {
        userptr = glad_gles2_build_userptr(handle);

        version = gladLoadGLES2UserPtr(glad_gles2_get_proc, &userptr);

        if (!version && did_load) {
            gladLoaderUnloadGLES2();
        }
    }
#endif

    return version;
}



void gladLoaderUnloadGLES2(void) {
    if (_gles2_handle != NULL) {
        glad_close_dlopen_handle(_gles2_handle);
        _gles2_handle = NULL;
    }
}

#endif /* GLAD_GLES2 */

#ifdef __cplusplus
}
#endif
