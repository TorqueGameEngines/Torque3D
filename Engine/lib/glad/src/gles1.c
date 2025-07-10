#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <glad/gles1.h>

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



int GLAD_GL_VERSION_ES_CM_1_0 = 0;
int GLAD_GL_AMD_compressed_3DC_texture = 0;
int GLAD_GL_AMD_compressed_ATC_texture = 0;
int GLAD_GL_APPLE_copy_texture_levels = 0;
int GLAD_GL_APPLE_framebuffer_multisample = 0;
int GLAD_GL_APPLE_sync = 0;
int GLAD_GL_APPLE_texture_2D_limited_npot = 0;
int GLAD_GL_APPLE_texture_format_BGRA8888 = 0;
int GLAD_GL_APPLE_texture_max_level = 0;
int GLAD_GL_ARM_rgba8 = 0;
int GLAD_GL_EXT_blend_minmax = 0;
int GLAD_GL_EXT_debug_marker = 0;
int GLAD_GL_EXT_discard_framebuffer = 0;
int GLAD_GL_EXT_map_buffer_range = 0;
int GLAD_GL_EXT_multi_draw_arrays = 0;
int GLAD_GL_EXT_multisampled_render_to_texture = 0;
int GLAD_GL_EXT_read_format_bgra = 0;
int GLAD_GL_EXT_robustness = 0;
int GLAD_GL_EXT_sRGB = 0;
int GLAD_GL_EXT_texture_compression_dxt1 = 0;
int GLAD_GL_EXT_texture_filter_anisotropic = 0;
int GLAD_GL_EXT_texture_format_BGRA8888 = 0;
int GLAD_GL_EXT_texture_lod_bias = 0;
int GLAD_GL_EXT_texture_storage = 0;
int GLAD_GL_IMG_multisampled_render_to_texture = 0;
int GLAD_GL_IMG_read_format = 0;
int GLAD_GL_IMG_texture_compression_pvrtc = 0;
int GLAD_GL_IMG_texture_env_enhanced_fixed_function = 0;
int GLAD_GL_IMG_user_clip_plane = 0;
int GLAD_GL_KHR_debug = 0;
int GLAD_GL_NV_fence = 0;
int GLAD_GL_OES_EGL_image = 0;
int GLAD_GL_OES_EGL_image_external = 0;
int GLAD_GL_OES_blend_equation_separate = 0;
int GLAD_GL_OES_blend_func_separate = 0;
int GLAD_GL_OES_blend_subtract = 0;
int GLAD_GL_OES_byte_coordinates = 0;
int GLAD_GL_OES_compressed_ETC1_RGB8_sub_texture = 0;
int GLAD_GL_OES_compressed_ETC1_RGB8_texture = 0;
int GLAD_GL_OES_compressed_paletted_texture = 0;
int GLAD_GL_OES_depth24 = 0;
int GLAD_GL_OES_depth32 = 0;
int GLAD_GL_OES_draw_texture = 0;
int GLAD_GL_OES_element_index_uint = 0;
int GLAD_GL_OES_extended_matrix_palette = 0;
int GLAD_GL_OES_fbo_render_mipmap = 0;
int GLAD_GL_OES_fixed_point = 0;
int GLAD_GL_OES_framebuffer_object = 0;
int GLAD_GL_OES_mapbuffer = 0;
int GLAD_GL_OES_matrix_get = 0;
int GLAD_GL_OES_matrix_palette = 0;
int GLAD_GL_OES_packed_depth_stencil = 0;
int GLAD_GL_OES_point_size_array = 0;
int GLAD_GL_OES_point_sprite = 0;
int GLAD_GL_OES_query_matrix = 0;
int GLAD_GL_OES_read_format = 0;
int GLAD_GL_OES_required_internalformat = 0;
int GLAD_GL_OES_rgb8_rgba8 = 0;
int GLAD_GL_OES_single_precision = 0;
int GLAD_GL_OES_stencil1 = 0;
int GLAD_GL_OES_stencil4 = 0;
int GLAD_GL_OES_stencil8 = 0;
int GLAD_GL_OES_stencil_wrap = 0;
int GLAD_GL_OES_surfaceless_context = 0;
int GLAD_GL_OES_texture_cube_map = 0;
int GLAD_GL_OES_texture_env_crossbar = 0;
int GLAD_GL_OES_texture_mirrored_repeat = 0;
int GLAD_GL_OES_texture_npot = 0;
int GLAD_GL_OES_vertex_array_object = 0;
int GLAD_GL_QCOM_driver_control = 0;
int GLAD_GL_QCOM_extended_get = 0;
int GLAD_GL_QCOM_extended_get2 = 0;
int GLAD_GL_QCOM_perfmon_global_mode = 0;
int GLAD_GL_QCOM_tiled_rendering = 0;
int GLAD_GL_QCOM_writeonly_rendering = 0;



PFNGLACTIVETEXTUREPROC glad_glActiveTexture = NULL;
PFNGLALPHAFUNCPROC glad_glAlphaFunc = NULL;
PFNGLALPHAFUNCXPROC glad_glAlphaFuncx = NULL;
PFNGLALPHAFUNCXOESPROC glad_glAlphaFuncxOES = NULL;
PFNGLBINDBUFFERPROC glad_glBindBuffer = NULL;
PFNGLBINDFRAMEBUFFEROESPROC glad_glBindFramebufferOES = NULL;
PFNGLBINDRENDERBUFFEROESPROC glad_glBindRenderbufferOES = NULL;
PFNGLBINDTEXTUREPROC glad_glBindTexture = NULL;
PFNGLBINDVERTEXARRAYOESPROC glad_glBindVertexArrayOES = NULL;
PFNGLBLENDEQUATIONOESPROC glad_glBlendEquationOES = NULL;
PFNGLBLENDEQUATIONSEPARATEOESPROC glad_glBlendEquationSeparateOES = NULL;
PFNGLBLENDFUNCPROC glad_glBlendFunc = NULL;
PFNGLBLENDFUNCSEPARATEOESPROC glad_glBlendFuncSeparateOES = NULL;
PFNGLBUFFERDATAPROC glad_glBufferData = NULL;
PFNGLBUFFERSUBDATAPROC glad_glBufferSubData = NULL;
PFNGLCHECKFRAMEBUFFERSTATUSOESPROC glad_glCheckFramebufferStatusOES = NULL;
PFNGLCLEARPROC glad_glClear = NULL;
PFNGLCLEARCOLORPROC glad_glClearColor = NULL;
PFNGLCLEARCOLORXPROC glad_glClearColorx = NULL;
PFNGLCLEARCOLORXOESPROC glad_glClearColorxOES = NULL;
PFNGLCLEARDEPTHFPROC glad_glClearDepthf = NULL;
PFNGLCLEARDEPTHFOESPROC glad_glClearDepthfOES = NULL;
PFNGLCLEARDEPTHXPROC glad_glClearDepthx = NULL;
PFNGLCLEARDEPTHXOESPROC glad_glClearDepthxOES = NULL;
PFNGLCLEARSTENCILPROC glad_glClearStencil = NULL;
PFNGLCLIENTACTIVETEXTUREPROC glad_glClientActiveTexture = NULL;
PFNGLCLIENTWAITSYNCAPPLEPROC glad_glClientWaitSyncAPPLE = NULL;
PFNGLCLIPPLANEFPROC glad_glClipPlanef = NULL;
PFNGLCLIPPLANEFIMGPROC glad_glClipPlanefIMG = NULL;
PFNGLCLIPPLANEFOESPROC glad_glClipPlanefOES = NULL;
PFNGLCLIPPLANEXPROC glad_glClipPlanex = NULL;
PFNGLCLIPPLANEXIMGPROC glad_glClipPlanexIMG = NULL;
PFNGLCLIPPLANEXOESPROC glad_glClipPlanexOES = NULL;
PFNGLCOLOR4FPROC glad_glColor4f = NULL;
PFNGLCOLOR4UBPROC glad_glColor4ub = NULL;
PFNGLCOLOR4XPROC glad_glColor4x = NULL;
PFNGLCOLOR4XOESPROC glad_glColor4xOES = NULL;
PFNGLCOLORMASKPROC glad_glColorMask = NULL;
PFNGLCOLORPOINTERPROC glad_glColorPointer = NULL;
PFNGLCOMPRESSEDTEXIMAGE2DPROC glad_glCompressedTexImage2D = NULL;
PFNGLCOMPRESSEDTEXSUBIMAGE2DPROC glad_glCompressedTexSubImage2D = NULL;
PFNGLCOPYTEXIMAGE2DPROC glad_glCopyTexImage2D = NULL;
PFNGLCOPYTEXSUBIMAGE2DPROC glad_glCopyTexSubImage2D = NULL;
PFNGLCOPYTEXTURELEVELSAPPLEPROC glad_glCopyTextureLevelsAPPLE = NULL;
PFNGLCULLFACEPROC glad_glCullFace = NULL;
PFNGLCURRENTPALETTEMATRIXOESPROC glad_glCurrentPaletteMatrixOES = NULL;
PFNGLDELETEBUFFERSPROC glad_glDeleteBuffers = NULL;
PFNGLDELETEFENCESNVPROC glad_glDeleteFencesNV = NULL;
PFNGLDELETEFRAMEBUFFERSOESPROC glad_glDeleteFramebuffersOES = NULL;
PFNGLDELETERENDERBUFFERSOESPROC glad_glDeleteRenderbuffersOES = NULL;
PFNGLDELETESYNCAPPLEPROC glad_glDeleteSyncAPPLE = NULL;
PFNGLDELETETEXTURESPROC glad_glDeleteTextures = NULL;
PFNGLDELETEVERTEXARRAYSOESPROC glad_glDeleteVertexArraysOES = NULL;
PFNGLDEPTHFUNCPROC glad_glDepthFunc = NULL;
PFNGLDEPTHMASKPROC glad_glDepthMask = NULL;
PFNGLDEPTHRANGEFPROC glad_glDepthRangef = NULL;
PFNGLDEPTHRANGEFOESPROC glad_glDepthRangefOES = NULL;
PFNGLDEPTHRANGEXPROC glad_glDepthRangex = NULL;
PFNGLDEPTHRANGEXOESPROC glad_glDepthRangexOES = NULL;
PFNGLDISABLEPROC glad_glDisable = NULL;
PFNGLDISABLECLIENTSTATEPROC glad_glDisableClientState = NULL;
PFNGLDISABLEDRIVERCONTROLQCOMPROC glad_glDisableDriverControlQCOM = NULL;
PFNGLDISCARDFRAMEBUFFEREXTPROC glad_glDiscardFramebufferEXT = NULL;
PFNGLDRAWARRAYSPROC glad_glDrawArrays = NULL;
PFNGLDRAWELEMENTSPROC glad_glDrawElements = NULL;
PFNGLDRAWTEXFOESPROC glad_glDrawTexfOES = NULL;
PFNGLDRAWTEXFVOESPROC glad_glDrawTexfvOES = NULL;
PFNGLDRAWTEXIOESPROC glad_glDrawTexiOES = NULL;
PFNGLDRAWTEXIVOESPROC glad_glDrawTexivOES = NULL;
PFNGLDRAWTEXSOESPROC glad_glDrawTexsOES = NULL;
PFNGLDRAWTEXSVOESPROC glad_glDrawTexsvOES = NULL;
PFNGLDRAWTEXXOESPROC glad_glDrawTexxOES = NULL;
PFNGLDRAWTEXXVOESPROC glad_glDrawTexxvOES = NULL;
PFNGLEGLIMAGETARGETRENDERBUFFERSTORAGEOESPROC glad_glEGLImageTargetRenderbufferStorageOES = NULL;
PFNGLEGLIMAGETARGETTEXTURE2DOESPROC glad_glEGLImageTargetTexture2DOES = NULL;
PFNGLENABLEPROC glad_glEnable = NULL;
PFNGLENABLECLIENTSTATEPROC glad_glEnableClientState = NULL;
PFNGLENABLEDRIVERCONTROLQCOMPROC glad_glEnableDriverControlQCOM = NULL;
PFNGLENDTILINGQCOMPROC glad_glEndTilingQCOM = NULL;
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
PFNGLFENCESYNCAPPLEPROC glad_glFenceSyncAPPLE = NULL;
PFNGLFINISHPROC glad_glFinish = NULL;
PFNGLFINISHFENCENVPROC glad_glFinishFenceNV = NULL;
PFNGLFLUSHPROC glad_glFlush = NULL;
PFNGLFLUSHMAPPEDBUFFERRANGEEXTPROC glad_glFlushMappedBufferRangeEXT = NULL;
PFNGLFOGFPROC glad_glFogf = NULL;
PFNGLFOGFVPROC glad_glFogfv = NULL;
PFNGLFOGXPROC glad_glFogx = NULL;
PFNGLFOGXOESPROC glad_glFogxOES = NULL;
PFNGLFOGXVPROC glad_glFogxv = NULL;
PFNGLFOGXVOESPROC glad_glFogxvOES = NULL;
PFNGLFRAMEBUFFERRENDERBUFFEROESPROC glad_glFramebufferRenderbufferOES = NULL;
PFNGLFRAMEBUFFERTEXTURE2DMULTISAMPLEEXTPROC glad_glFramebufferTexture2DMultisampleEXT = NULL;
PFNGLFRAMEBUFFERTEXTURE2DMULTISAMPLEIMGPROC glad_glFramebufferTexture2DMultisampleIMG = NULL;
PFNGLFRAMEBUFFERTEXTURE2DOESPROC glad_glFramebufferTexture2DOES = NULL;
PFNGLFRONTFACEPROC glad_glFrontFace = NULL;
PFNGLFRUSTUMFPROC glad_glFrustumf = NULL;
PFNGLFRUSTUMFOESPROC glad_glFrustumfOES = NULL;
PFNGLFRUSTUMXPROC glad_glFrustumx = NULL;
PFNGLFRUSTUMXOESPROC glad_glFrustumxOES = NULL;
PFNGLGENBUFFERSPROC glad_glGenBuffers = NULL;
PFNGLGENFENCESNVPROC glad_glGenFencesNV = NULL;
PFNGLGENFRAMEBUFFERSOESPROC glad_glGenFramebuffersOES = NULL;
PFNGLGENRENDERBUFFERSOESPROC glad_glGenRenderbuffersOES = NULL;
PFNGLGENTEXTURESPROC glad_glGenTextures = NULL;
PFNGLGENVERTEXARRAYSOESPROC glad_glGenVertexArraysOES = NULL;
PFNGLGENERATEMIPMAPOESPROC glad_glGenerateMipmapOES = NULL;
PFNGLGETBOOLEANVPROC glad_glGetBooleanv = NULL;
PFNGLGETBUFFERPARAMETERIVPROC glad_glGetBufferParameteriv = NULL;
PFNGLGETBUFFERPOINTERVOESPROC glad_glGetBufferPointervOES = NULL;
PFNGLGETCLIPPLANEFPROC glad_glGetClipPlanef = NULL;
PFNGLGETCLIPPLANEFOESPROC glad_glGetClipPlanefOES = NULL;
PFNGLGETCLIPPLANEXPROC glad_glGetClipPlanex = NULL;
PFNGLGETCLIPPLANEXOESPROC glad_glGetClipPlanexOES = NULL;
PFNGLGETDRIVERCONTROLSTRINGQCOMPROC glad_glGetDriverControlStringQCOM = NULL;
PFNGLGETDRIVERCONTROLSQCOMPROC glad_glGetDriverControlsQCOM = NULL;
PFNGLGETERRORPROC glad_glGetError = NULL;
PFNGLGETFENCEIVNVPROC glad_glGetFenceivNV = NULL;
PFNGLGETFIXEDVPROC glad_glGetFixedv = NULL;
PFNGLGETFIXEDVOESPROC glad_glGetFixedvOES = NULL;
PFNGLGETFLOATVPROC glad_glGetFloatv = NULL;
PFNGLGETFRAMEBUFFERATTACHMENTPARAMETERIVOESPROC glad_glGetFramebufferAttachmentParameterivOES = NULL;
PFNGLGETGRAPHICSRESETSTATUSEXTPROC glad_glGetGraphicsResetStatusEXT = NULL;
PFNGLGETINTEGER64VAPPLEPROC glad_glGetInteger64vAPPLE = NULL;
PFNGLGETINTEGERVPROC glad_glGetIntegerv = NULL;
PFNGLGETLIGHTFVPROC glad_glGetLightfv = NULL;
PFNGLGETLIGHTXVPROC glad_glGetLightxv = NULL;
PFNGLGETLIGHTXVOESPROC glad_glGetLightxvOES = NULL;
PFNGLGETMATERIALFVPROC glad_glGetMaterialfv = NULL;
PFNGLGETMATERIALXVPROC glad_glGetMaterialxv = NULL;
PFNGLGETMATERIALXVOESPROC glad_glGetMaterialxvOES = NULL;
PFNGLGETPOINTERVPROC glad_glGetPointerv = NULL;
PFNGLGETRENDERBUFFERPARAMETERIVOESPROC glad_glGetRenderbufferParameterivOES = NULL;
PFNGLGETSTRINGPROC glad_glGetString = NULL;
PFNGLGETSYNCIVAPPLEPROC glad_glGetSyncivAPPLE = NULL;
PFNGLGETTEXENVFVPROC glad_glGetTexEnvfv = NULL;
PFNGLGETTEXENVIVPROC glad_glGetTexEnviv = NULL;
PFNGLGETTEXENVXVPROC glad_glGetTexEnvxv = NULL;
PFNGLGETTEXENVXVOESPROC glad_glGetTexEnvxvOES = NULL;
PFNGLGETTEXGENFVOESPROC glad_glGetTexGenfvOES = NULL;
PFNGLGETTEXGENIVOESPROC glad_glGetTexGenivOES = NULL;
PFNGLGETTEXGENXVOESPROC glad_glGetTexGenxvOES = NULL;
PFNGLGETTEXPARAMETERFVPROC glad_glGetTexParameterfv = NULL;
PFNGLGETTEXPARAMETERIVPROC glad_glGetTexParameteriv = NULL;
PFNGLGETTEXPARAMETERXVPROC glad_glGetTexParameterxv = NULL;
PFNGLGETTEXPARAMETERXVOESPROC glad_glGetTexParameterxvOES = NULL;
PFNGLGETNUNIFORMFVEXTPROC glad_glGetnUniformfvEXT = NULL;
PFNGLGETNUNIFORMIVEXTPROC glad_glGetnUniformivEXT = NULL;
PFNGLHINTPROC glad_glHint = NULL;
PFNGLINSERTEVENTMARKEREXTPROC glad_glInsertEventMarkerEXT = NULL;
PFNGLISBUFFERPROC glad_glIsBuffer = NULL;
PFNGLISENABLEDPROC glad_glIsEnabled = NULL;
PFNGLISFENCENVPROC glad_glIsFenceNV = NULL;
PFNGLISFRAMEBUFFEROESPROC glad_glIsFramebufferOES = NULL;
PFNGLISRENDERBUFFEROESPROC glad_glIsRenderbufferOES = NULL;
PFNGLISSYNCAPPLEPROC glad_glIsSyncAPPLE = NULL;
PFNGLISTEXTUREPROC glad_glIsTexture = NULL;
PFNGLISVERTEXARRAYOESPROC glad_glIsVertexArrayOES = NULL;
PFNGLLIGHTMODELFPROC glad_glLightModelf = NULL;
PFNGLLIGHTMODELFVPROC glad_glLightModelfv = NULL;
PFNGLLIGHTMODELXPROC glad_glLightModelx = NULL;
PFNGLLIGHTMODELXOESPROC glad_glLightModelxOES = NULL;
PFNGLLIGHTMODELXVPROC glad_glLightModelxv = NULL;
PFNGLLIGHTMODELXVOESPROC glad_glLightModelxvOES = NULL;
PFNGLLIGHTFPROC glad_glLightf = NULL;
PFNGLLIGHTFVPROC glad_glLightfv = NULL;
PFNGLLIGHTXPROC glad_glLightx = NULL;
PFNGLLIGHTXOESPROC glad_glLightxOES = NULL;
PFNGLLIGHTXVPROC glad_glLightxv = NULL;
PFNGLLIGHTXVOESPROC glad_glLightxvOES = NULL;
PFNGLLINEWIDTHPROC glad_glLineWidth = NULL;
PFNGLLINEWIDTHXPROC glad_glLineWidthx = NULL;
PFNGLLINEWIDTHXOESPROC glad_glLineWidthxOES = NULL;
PFNGLLOADIDENTITYPROC glad_glLoadIdentity = NULL;
PFNGLLOADMATRIXFPROC glad_glLoadMatrixf = NULL;
PFNGLLOADMATRIXXPROC glad_glLoadMatrixx = NULL;
PFNGLLOADMATRIXXOESPROC glad_glLoadMatrixxOES = NULL;
PFNGLLOADPALETTEFROMMODELVIEWMATRIXOESPROC glad_glLoadPaletteFromModelViewMatrixOES = NULL;
PFNGLLOGICOPPROC glad_glLogicOp = NULL;
PFNGLMAPBUFFEROESPROC glad_glMapBufferOES = NULL;
PFNGLMAPBUFFERRANGEEXTPROC glad_glMapBufferRangeEXT = NULL;
PFNGLMATERIALFPROC glad_glMaterialf = NULL;
PFNGLMATERIALFVPROC glad_glMaterialfv = NULL;
PFNGLMATERIALXPROC glad_glMaterialx = NULL;
PFNGLMATERIALXOESPROC glad_glMaterialxOES = NULL;
PFNGLMATERIALXVPROC glad_glMaterialxv = NULL;
PFNGLMATERIALXVOESPROC glad_glMaterialxvOES = NULL;
PFNGLMATRIXINDEXPOINTEROESPROC glad_glMatrixIndexPointerOES = NULL;
PFNGLMATRIXMODEPROC glad_glMatrixMode = NULL;
PFNGLMULTMATRIXFPROC glad_glMultMatrixf = NULL;
PFNGLMULTMATRIXXPROC glad_glMultMatrixx = NULL;
PFNGLMULTMATRIXXOESPROC glad_glMultMatrixxOES = NULL;
PFNGLMULTIDRAWARRAYSEXTPROC glad_glMultiDrawArraysEXT = NULL;
PFNGLMULTIDRAWELEMENTSEXTPROC glad_glMultiDrawElementsEXT = NULL;
PFNGLMULTITEXCOORD4FPROC glad_glMultiTexCoord4f = NULL;
PFNGLMULTITEXCOORD4XPROC glad_glMultiTexCoord4x = NULL;
PFNGLMULTITEXCOORD4XOESPROC glad_glMultiTexCoord4xOES = NULL;
PFNGLNORMAL3FPROC glad_glNormal3f = NULL;
PFNGLNORMAL3XPROC glad_glNormal3x = NULL;
PFNGLNORMAL3XOESPROC glad_glNormal3xOES = NULL;
PFNGLNORMALPOINTERPROC glad_glNormalPointer = NULL;
PFNGLORTHOFPROC glad_glOrthof = NULL;
PFNGLORTHOFOESPROC glad_glOrthofOES = NULL;
PFNGLORTHOXPROC glad_glOrthox = NULL;
PFNGLORTHOXOESPROC glad_glOrthoxOES = NULL;
PFNGLPIXELSTOREIPROC glad_glPixelStorei = NULL;
PFNGLPOINTPARAMETERFPROC glad_glPointParameterf = NULL;
PFNGLPOINTPARAMETERFVPROC glad_glPointParameterfv = NULL;
PFNGLPOINTPARAMETERXPROC glad_glPointParameterx = NULL;
PFNGLPOINTPARAMETERXOESPROC glad_glPointParameterxOES = NULL;
PFNGLPOINTPARAMETERXVPROC glad_glPointParameterxv = NULL;
PFNGLPOINTPARAMETERXVOESPROC glad_glPointParameterxvOES = NULL;
PFNGLPOINTSIZEPROC glad_glPointSize = NULL;
PFNGLPOINTSIZEPOINTEROESPROC glad_glPointSizePointerOES = NULL;
PFNGLPOINTSIZEXPROC glad_glPointSizex = NULL;
PFNGLPOINTSIZEXOESPROC glad_glPointSizexOES = NULL;
PFNGLPOLYGONOFFSETPROC glad_glPolygonOffset = NULL;
PFNGLPOLYGONOFFSETXPROC glad_glPolygonOffsetx = NULL;
PFNGLPOLYGONOFFSETXOESPROC glad_glPolygonOffsetxOES = NULL;
PFNGLPOPGROUPMARKEREXTPROC glad_glPopGroupMarkerEXT = NULL;
PFNGLPOPMATRIXPROC glad_glPopMatrix = NULL;
PFNGLPUSHGROUPMARKEREXTPROC glad_glPushGroupMarkerEXT = NULL;
PFNGLPUSHMATRIXPROC glad_glPushMatrix = NULL;
PFNGLQUERYMATRIXXOESPROC glad_glQueryMatrixxOES = NULL;
PFNGLREADPIXELSPROC glad_glReadPixels = NULL;
PFNGLREADNPIXELSEXTPROC glad_glReadnPixelsEXT = NULL;
PFNGLRENDERBUFFERSTORAGEMULTISAMPLEAPPLEPROC glad_glRenderbufferStorageMultisampleAPPLE = NULL;
PFNGLRENDERBUFFERSTORAGEMULTISAMPLEEXTPROC glad_glRenderbufferStorageMultisampleEXT = NULL;
PFNGLRENDERBUFFERSTORAGEMULTISAMPLEIMGPROC glad_glRenderbufferStorageMultisampleIMG = NULL;
PFNGLRENDERBUFFERSTORAGEOESPROC glad_glRenderbufferStorageOES = NULL;
PFNGLRESOLVEMULTISAMPLEFRAMEBUFFERAPPLEPROC glad_glResolveMultisampleFramebufferAPPLE = NULL;
PFNGLROTATEFPROC glad_glRotatef = NULL;
PFNGLROTATEXPROC glad_glRotatex = NULL;
PFNGLROTATEXOESPROC glad_glRotatexOES = NULL;
PFNGLSAMPLECOVERAGEPROC glad_glSampleCoverage = NULL;
PFNGLSAMPLECOVERAGEXPROC glad_glSampleCoveragex = NULL;
PFNGLSAMPLECOVERAGEXOESPROC glad_glSampleCoveragexOES = NULL;
PFNGLSCALEFPROC glad_glScalef = NULL;
PFNGLSCALEXPROC glad_glScalex = NULL;
PFNGLSCALEXOESPROC glad_glScalexOES = NULL;
PFNGLSCISSORPROC glad_glScissor = NULL;
PFNGLSETFENCENVPROC glad_glSetFenceNV = NULL;
PFNGLSHADEMODELPROC glad_glShadeModel = NULL;
PFNGLSTARTTILINGQCOMPROC glad_glStartTilingQCOM = NULL;
PFNGLSTENCILFUNCPROC glad_glStencilFunc = NULL;
PFNGLSTENCILMASKPROC glad_glStencilMask = NULL;
PFNGLSTENCILOPPROC glad_glStencilOp = NULL;
PFNGLTESTFENCENVPROC glad_glTestFenceNV = NULL;
PFNGLTEXCOORDPOINTERPROC glad_glTexCoordPointer = NULL;
PFNGLTEXENVFPROC glad_glTexEnvf = NULL;
PFNGLTEXENVFVPROC glad_glTexEnvfv = NULL;
PFNGLTEXENVIPROC glad_glTexEnvi = NULL;
PFNGLTEXENVIVPROC glad_glTexEnviv = NULL;
PFNGLTEXENVXPROC glad_glTexEnvx = NULL;
PFNGLTEXENVXOESPROC glad_glTexEnvxOES = NULL;
PFNGLTEXENVXVPROC glad_glTexEnvxv = NULL;
PFNGLTEXENVXVOESPROC glad_glTexEnvxvOES = NULL;
PFNGLTEXGENFOESPROC glad_glTexGenfOES = NULL;
PFNGLTEXGENFVOESPROC glad_glTexGenfvOES = NULL;
PFNGLTEXGENIOESPROC glad_glTexGeniOES = NULL;
PFNGLTEXGENIVOESPROC glad_glTexGenivOES = NULL;
PFNGLTEXGENXOESPROC glad_glTexGenxOES = NULL;
PFNGLTEXGENXVOESPROC glad_glTexGenxvOES = NULL;
PFNGLTEXIMAGE2DPROC glad_glTexImage2D = NULL;
PFNGLTEXPARAMETERFPROC glad_glTexParameterf = NULL;
PFNGLTEXPARAMETERFVPROC glad_glTexParameterfv = NULL;
PFNGLTEXPARAMETERIPROC glad_glTexParameteri = NULL;
PFNGLTEXPARAMETERIVPROC glad_glTexParameteriv = NULL;
PFNGLTEXPARAMETERXPROC glad_glTexParameterx = NULL;
PFNGLTEXPARAMETERXOESPROC glad_glTexParameterxOES = NULL;
PFNGLTEXPARAMETERXVPROC glad_glTexParameterxv = NULL;
PFNGLTEXPARAMETERXVOESPROC glad_glTexParameterxvOES = NULL;
PFNGLTEXSTORAGE1DEXTPROC glad_glTexStorage1DEXT = NULL;
PFNGLTEXSTORAGE2DEXTPROC glad_glTexStorage2DEXT = NULL;
PFNGLTEXSTORAGE3DEXTPROC glad_glTexStorage3DEXT = NULL;
PFNGLTEXSUBIMAGE2DPROC glad_glTexSubImage2D = NULL;
PFNGLTEXTURESTORAGE1DEXTPROC glad_glTextureStorage1DEXT = NULL;
PFNGLTEXTURESTORAGE2DEXTPROC glad_glTextureStorage2DEXT = NULL;
PFNGLTEXTURESTORAGE3DEXTPROC glad_glTextureStorage3DEXT = NULL;
PFNGLTRANSLATEFPROC glad_glTranslatef = NULL;
PFNGLTRANSLATEXPROC glad_glTranslatex = NULL;
PFNGLTRANSLATEXOESPROC glad_glTranslatexOES = NULL;
PFNGLUNMAPBUFFEROESPROC glad_glUnmapBufferOES = NULL;
PFNGLVERTEXPOINTERPROC glad_glVertexPointer = NULL;
PFNGLVIEWPORTPROC glad_glViewport = NULL;
PFNGLWAITSYNCAPPLEPROC glad_glWaitSyncAPPLE = NULL;
PFNGLWEIGHTPOINTEROESPROC glad_glWeightPointerOES = NULL;


static void glad_gl_load_GL_VERSION_ES_CM_1_0( GLADuserptrloadfunc load, void* userptr) {
    if(!GLAD_GL_VERSION_ES_CM_1_0) return;
    glad_glActiveTexture = (PFNGLACTIVETEXTUREPROC) load(userptr, "glActiveTexture");
    glad_glAlphaFunc = (PFNGLALPHAFUNCPROC) load(userptr, "glAlphaFunc");
    glad_glAlphaFuncx = (PFNGLALPHAFUNCXPROC) load(userptr, "glAlphaFuncx");
    glad_glBindBuffer = (PFNGLBINDBUFFERPROC) load(userptr, "glBindBuffer");
    glad_glBindTexture = (PFNGLBINDTEXTUREPROC) load(userptr, "glBindTexture");
    glad_glBlendFunc = (PFNGLBLENDFUNCPROC) load(userptr, "glBlendFunc");
    glad_glBufferData = (PFNGLBUFFERDATAPROC) load(userptr, "glBufferData");
    glad_glBufferSubData = (PFNGLBUFFERSUBDATAPROC) load(userptr, "glBufferSubData");
    glad_glClear = (PFNGLCLEARPROC) load(userptr, "glClear");
    glad_glClearColor = (PFNGLCLEARCOLORPROC) load(userptr, "glClearColor");
    glad_glClearColorx = (PFNGLCLEARCOLORXPROC) load(userptr, "glClearColorx");
    glad_glClearDepthf = (PFNGLCLEARDEPTHFPROC) load(userptr, "glClearDepthf");
    glad_glClearDepthx = (PFNGLCLEARDEPTHXPROC) load(userptr, "glClearDepthx");
    glad_glClearStencil = (PFNGLCLEARSTENCILPROC) load(userptr, "glClearStencil");
    glad_glClientActiveTexture = (PFNGLCLIENTACTIVETEXTUREPROC) load(userptr, "glClientActiveTexture");
    glad_glClipPlanef = (PFNGLCLIPPLANEFPROC) load(userptr, "glClipPlanef");
    glad_glClipPlanex = (PFNGLCLIPPLANEXPROC) load(userptr, "glClipPlanex");
    glad_glColor4f = (PFNGLCOLOR4FPROC) load(userptr, "glColor4f");
    glad_glColor4ub = (PFNGLCOLOR4UBPROC) load(userptr, "glColor4ub");
    glad_glColor4x = (PFNGLCOLOR4XPROC) load(userptr, "glColor4x");
    glad_glColorMask = (PFNGLCOLORMASKPROC) load(userptr, "glColorMask");
    glad_glColorPointer = (PFNGLCOLORPOINTERPROC) load(userptr, "glColorPointer");
    glad_glCompressedTexImage2D = (PFNGLCOMPRESSEDTEXIMAGE2DPROC) load(userptr, "glCompressedTexImage2D");
    glad_glCompressedTexSubImage2D = (PFNGLCOMPRESSEDTEXSUBIMAGE2DPROC) load(userptr, "glCompressedTexSubImage2D");
    glad_glCopyTexImage2D = (PFNGLCOPYTEXIMAGE2DPROC) load(userptr, "glCopyTexImage2D");
    glad_glCopyTexSubImage2D = (PFNGLCOPYTEXSUBIMAGE2DPROC) load(userptr, "glCopyTexSubImage2D");
    glad_glCullFace = (PFNGLCULLFACEPROC) load(userptr, "glCullFace");
    glad_glDeleteBuffers = (PFNGLDELETEBUFFERSPROC) load(userptr, "glDeleteBuffers");
    glad_glDeleteTextures = (PFNGLDELETETEXTURESPROC) load(userptr, "glDeleteTextures");
    glad_glDepthFunc = (PFNGLDEPTHFUNCPROC) load(userptr, "glDepthFunc");
    glad_glDepthMask = (PFNGLDEPTHMASKPROC) load(userptr, "glDepthMask");
    glad_glDepthRangef = (PFNGLDEPTHRANGEFPROC) load(userptr, "glDepthRangef");
    glad_glDepthRangex = (PFNGLDEPTHRANGEXPROC) load(userptr, "glDepthRangex");
    glad_glDisable = (PFNGLDISABLEPROC) load(userptr, "glDisable");
    glad_glDisableClientState = (PFNGLDISABLECLIENTSTATEPROC) load(userptr, "glDisableClientState");
    glad_glDrawArrays = (PFNGLDRAWARRAYSPROC) load(userptr, "glDrawArrays");
    glad_glDrawElements = (PFNGLDRAWELEMENTSPROC) load(userptr, "glDrawElements");
    glad_glEnable = (PFNGLENABLEPROC) load(userptr, "glEnable");
    glad_glEnableClientState = (PFNGLENABLECLIENTSTATEPROC) load(userptr, "glEnableClientState");
    glad_glFinish = (PFNGLFINISHPROC) load(userptr, "glFinish");
    glad_glFlush = (PFNGLFLUSHPROC) load(userptr, "glFlush");
    glad_glFogf = (PFNGLFOGFPROC) load(userptr, "glFogf");
    glad_glFogfv = (PFNGLFOGFVPROC) load(userptr, "glFogfv");
    glad_glFogx = (PFNGLFOGXPROC) load(userptr, "glFogx");
    glad_glFogxv = (PFNGLFOGXVPROC) load(userptr, "glFogxv");
    glad_glFrontFace = (PFNGLFRONTFACEPROC) load(userptr, "glFrontFace");
    glad_glFrustumf = (PFNGLFRUSTUMFPROC) load(userptr, "glFrustumf");
    glad_glFrustumx = (PFNGLFRUSTUMXPROC) load(userptr, "glFrustumx");
    glad_glGenBuffers = (PFNGLGENBUFFERSPROC) load(userptr, "glGenBuffers");
    glad_glGenTextures = (PFNGLGENTEXTURESPROC) load(userptr, "glGenTextures");
    glad_glGetBooleanv = (PFNGLGETBOOLEANVPROC) load(userptr, "glGetBooleanv");
    glad_glGetBufferParameteriv = (PFNGLGETBUFFERPARAMETERIVPROC) load(userptr, "glGetBufferParameteriv");
    glad_glGetClipPlanef = (PFNGLGETCLIPPLANEFPROC) load(userptr, "glGetClipPlanef");
    glad_glGetClipPlanex = (PFNGLGETCLIPPLANEXPROC) load(userptr, "glGetClipPlanex");
    glad_glGetError = (PFNGLGETERRORPROC) load(userptr, "glGetError");
    glad_glGetFixedv = (PFNGLGETFIXEDVPROC) load(userptr, "glGetFixedv");
    glad_glGetFloatv = (PFNGLGETFLOATVPROC) load(userptr, "glGetFloatv");
    glad_glGetIntegerv = (PFNGLGETINTEGERVPROC) load(userptr, "glGetIntegerv");
    glad_glGetLightfv = (PFNGLGETLIGHTFVPROC) load(userptr, "glGetLightfv");
    glad_glGetLightxv = (PFNGLGETLIGHTXVPROC) load(userptr, "glGetLightxv");
    glad_glGetMaterialfv = (PFNGLGETMATERIALFVPROC) load(userptr, "glGetMaterialfv");
    glad_glGetMaterialxv = (PFNGLGETMATERIALXVPROC) load(userptr, "glGetMaterialxv");
    glad_glGetPointerv = (PFNGLGETPOINTERVPROC) load(userptr, "glGetPointerv");
    glad_glGetString = (PFNGLGETSTRINGPROC) load(userptr, "glGetString");
    glad_glGetTexEnvfv = (PFNGLGETTEXENVFVPROC) load(userptr, "glGetTexEnvfv");
    glad_glGetTexEnviv = (PFNGLGETTEXENVIVPROC) load(userptr, "glGetTexEnviv");
    glad_glGetTexEnvxv = (PFNGLGETTEXENVXVPROC) load(userptr, "glGetTexEnvxv");
    glad_glGetTexParameterfv = (PFNGLGETTEXPARAMETERFVPROC) load(userptr, "glGetTexParameterfv");
    glad_glGetTexParameteriv = (PFNGLGETTEXPARAMETERIVPROC) load(userptr, "glGetTexParameteriv");
    glad_glGetTexParameterxv = (PFNGLGETTEXPARAMETERXVPROC) load(userptr, "glGetTexParameterxv");
    glad_glHint = (PFNGLHINTPROC) load(userptr, "glHint");
    glad_glIsBuffer = (PFNGLISBUFFERPROC) load(userptr, "glIsBuffer");
    glad_glIsEnabled = (PFNGLISENABLEDPROC) load(userptr, "glIsEnabled");
    glad_glIsTexture = (PFNGLISTEXTUREPROC) load(userptr, "glIsTexture");
    glad_glLightModelf = (PFNGLLIGHTMODELFPROC) load(userptr, "glLightModelf");
    glad_glLightModelfv = (PFNGLLIGHTMODELFVPROC) load(userptr, "glLightModelfv");
    glad_glLightModelx = (PFNGLLIGHTMODELXPROC) load(userptr, "glLightModelx");
    glad_glLightModelxv = (PFNGLLIGHTMODELXVPROC) load(userptr, "glLightModelxv");
    glad_glLightf = (PFNGLLIGHTFPROC) load(userptr, "glLightf");
    glad_glLightfv = (PFNGLLIGHTFVPROC) load(userptr, "glLightfv");
    glad_glLightx = (PFNGLLIGHTXPROC) load(userptr, "glLightx");
    glad_glLightxv = (PFNGLLIGHTXVPROC) load(userptr, "glLightxv");
    glad_glLineWidth = (PFNGLLINEWIDTHPROC) load(userptr, "glLineWidth");
    glad_glLineWidthx = (PFNGLLINEWIDTHXPROC) load(userptr, "glLineWidthx");
    glad_glLoadIdentity = (PFNGLLOADIDENTITYPROC) load(userptr, "glLoadIdentity");
    glad_glLoadMatrixf = (PFNGLLOADMATRIXFPROC) load(userptr, "glLoadMatrixf");
    glad_glLoadMatrixx = (PFNGLLOADMATRIXXPROC) load(userptr, "glLoadMatrixx");
    glad_glLogicOp = (PFNGLLOGICOPPROC) load(userptr, "glLogicOp");
    glad_glMaterialf = (PFNGLMATERIALFPROC) load(userptr, "glMaterialf");
    glad_glMaterialfv = (PFNGLMATERIALFVPROC) load(userptr, "glMaterialfv");
    glad_glMaterialx = (PFNGLMATERIALXPROC) load(userptr, "glMaterialx");
    glad_glMaterialxv = (PFNGLMATERIALXVPROC) load(userptr, "glMaterialxv");
    glad_glMatrixMode = (PFNGLMATRIXMODEPROC) load(userptr, "glMatrixMode");
    glad_glMultMatrixf = (PFNGLMULTMATRIXFPROC) load(userptr, "glMultMatrixf");
    glad_glMultMatrixx = (PFNGLMULTMATRIXXPROC) load(userptr, "glMultMatrixx");
    glad_glMultiTexCoord4f = (PFNGLMULTITEXCOORD4FPROC) load(userptr, "glMultiTexCoord4f");
    glad_glMultiTexCoord4x = (PFNGLMULTITEXCOORD4XPROC) load(userptr, "glMultiTexCoord4x");
    glad_glNormal3f = (PFNGLNORMAL3FPROC) load(userptr, "glNormal3f");
    glad_glNormal3x = (PFNGLNORMAL3XPROC) load(userptr, "glNormal3x");
    glad_glNormalPointer = (PFNGLNORMALPOINTERPROC) load(userptr, "glNormalPointer");
    glad_glOrthof = (PFNGLORTHOFPROC) load(userptr, "glOrthof");
    glad_glOrthox = (PFNGLORTHOXPROC) load(userptr, "glOrthox");
    glad_glPixelStorei = (PFNGLPIXELSTOREIPROC) load(userptr, "glPixelStorei");
    glad_glPointParameterf = (PFNGLPOINTPARAMETERFPROC) load(userptr, "glPointParameterf");
    glad_glPointParameterfv = (PFNGLPOINTPARAMETERFVPROC) load(userptr, "glPointParameterfv");
    glad_glPointParameterx = (PFNGLPOINTPARAMETERXPROC) load(userptr, "glPointParameterx");
    glad_glPointParameterxv = (PFNGLPOINTPARAMETERXVPROC) load(userptr, "glPointParameterxv");
    glad_glPointSize = (PFNGLPOINTSIZEPROC) load(userptr, "glPointSize");
    glad_glPointSizex = (PFNGLPOINTSIZEXPROC) load(userptr, "glPointSizex");
    glad_glPolygonOffset = (PFNGLPOLYGONOFFSETPROC) load(userptr, "glPolygonOffset");
    glad_glPolygonOffsetx = (PFNGLPOLYGONOFFSETXPROC) load(userptr, "glPolygonOffsetx");
    glad_glPopMatrix = (PFNGLPOPMATRIXPROC) load(userptr, "glPopMatrix");
    glad_glPushMatrix = (PFNGLPUSHMATRIXPROC) load(userptr, "glPushMatrix");
    glad_glReadPixels = (PFNGLREADPIXELSPROC) load(userptr, "glReadPixels");
    glad_glRotatef = (PFNGLROTATEFPROC) load(userptr, "glRotatef");
    glad_glRotatex = (PFNGLROTATEXPROC) load(userptr, "glRotatex");
    glad_glSampleCoverage = (PFNGLSAMPLECOVERAGEPROC) load(userptr, "glSampleCoverage");
    glad_glSampleCoveragex = (PFNGLSAMPLECOVERAGEXPROC) load(userptr, "glSampleCoveragex");
    glad_glScalef = (PFNGLSCALEFPROC) load(userptr, "glScalef");
    glad_glScalex = (PFNGLSCALEXPROC) load(userptr, "glScalex");
    glad_glScissor = (PFNGLSCISSORPROC) load(userptr, "glScissor");
    glad_glShadeModel = (PFNGLSHADEMODELPROC) load(userptr, "glShadeModel");
    glad_glStencilFunc = (PFNGLSTENCILFUNCPROC) load(userptr, "glStencilFunc");
    glad_glStencilMask = (PFNGLSTENCILMASKPROC) load(userptr, "glStencilMask");
    glad_glStencilOp = (PFNGLSTENCILOPPROC) load(userptr, "glStencilOp");
    glad_glTexCoordPointer = (PFNGLTEXCOORDPOINTERPROC) load(userptr, "glTexCoordPointer");
    glad_glTexEnvf = (PFNGLTEXENVFPROC) load(userptr, "glTexEnvf");
    glad_glTexEnvfv = (PFNGLTEXENVFVPROC) load(userptr, "glTexEnvfv");
    glad_glTexEnvi = (PFNGLTEXENVIPROC) load(userptr, "glTexEnvi");
    glad_glTexEnviv = (PFNGLTEXENVIVPROC) load(userptr, "glTexEnviv");
    glad_glTexEnvx = (PFNGLTEXENVXPROC) load(userptr, "glTexEnvx");
    glad_glTexEnvxv = (PFNGLTEXENVXVPROC) load(userptr, "glTexEnvxv");
    glad_glTexImage2D = (PFNGLTEXIMAGE2DPROC) load(userptr, "glTexImage2D");
    glad_glTexParameterf = (PFNGLTEXPARAMETERFPROC) load(userptr, "glTexParameterf");
    glad_glTexParameterfv = (PFNGLTEXPARAMETERFVPROC) load(userptr, "glTexParameterfv");
    glad_glTexParameteri = (PFNGLTEXPARAMETERIPROC) load(userptr, "glTexParameteri");
    glad_glTexParameteriv = (PFNGLTEXPARAMETERIVPROC) load(userptr, "glTexParameteriv");
    glad_glTexParameterx = (PFNGLTEXPARAMETERXPROC) load(userptr, "glTexParameterx");
    glad_glTexParameterxv = (PFNGLTEXPARAMETERXVPROC) load(userptr, "glTexParameterxv");
    glad_glTexSubImage2D = (PFNGLTEXSUBIMAGE2DPROC) load(userptr, "glTexSubImage2D");
    glad_glTranslatef = (PFNGLTRANSLATEFPROC) load(userptr, "glTranslatef");
    glad_glTranslatex = (PFNGLTRANSLATEXPROC) load(userptr, "glTranslatex");
    glad_glVertexPointer = (PFNGLVERTEXPOINTERPROC) load(userptr, "glVertexPointer");
    glad_glViewport = (PFNGLVIEWPORTPROC) load(userptr, "glViewport");
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
static void glad_gl_load_GL_EXT_map_buffer_range( GLADuserptrloadfunc load, void* userptr) {
    if(!GLAD_GL_EXT_map_buffer_range) return;
    glad_glFlushMappedBufferRangeEXT = (PFNGLFLUSHMAPPEDBUFFERRANGEEXTPROC) load(userptr, "glFlushMappedBufferRangeEXT");
    glad_glMapBufferRangeEXT = (PFNGLMAPBUFFERRANGEEXTPROC) load(userptr, "glMapBufferRangeEXT");
}
static void glad_gl_load_GL_EXT_multi_draw_arrays( GLADuserptrloadfunc load, void* userptr) {
    if(!GLAD_GL_EXT_multi_draw_arrays) return;
    glad_glMultiDrawArraysEXT = (PFNGLMULTIDRAWARRAYSEXTPROC) load(userptr, "glMultiDrawArraysEXT");
    glad_glMultiDrawElementsEXT = (PFNGLMULTIDRAWELEMENTSEXTPROC) load(userptr, "glMultiDrawElementsEXT");
}
static void glad_gl_load_GL_EXT_multisampled_render_to_texture( GLADuserptrloadfunc load, void* userptr) {
    if(!GLAD_GL_EXT_multisampled_render_to_texture) return;
    glad_glFramebufferTexture2DMultisampleEXT = (PFNGLFRAMEBUFFERTEXTURE2DMULTISAMPLEEXTPROC) load(userptr, "glFramebufferTexture2DMultisampleEXT");
    glad_glRenderbufferStorageMultisampleEXT = (PFNGLRENDERBUFFERSTORAGEMULTISAMPLEEXTPROC) load(userptr, "glRenderbufferStorageMultisampleEXT");
}
static void glad_gl_load_GL_EXT_robustness( GLADuserptrloadfunc load, void* userptr) {
    if(!GLAD_GL_EXT_robustness) return;
    glad_glGetGraphicsResetStatusEXT = (PFNGLGETGRAPHICSRESETSTATUSEXTPROC) load(userptr, "glGetGraphicsResetStatusEXT");
    glad_glGetnUniformfvEXT = (PFNGLGETNUNIFORMFVEXTPROC) load(userptr, "glGetnUniformfvEXT");
    glad_glGetnUniformivEXT = (PFNGLGETNUNIFORMIVEXTPROC) load(userptr, "glGetnUniformivEXT");
    glad_glReadnPixelsEXT = (PFNGLREADNPIXELSEXTPROC) load(userptr, "glReadnPixelsEXT");
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
static void glad_gl_load_GL_IMG_multisampled_render_to_texture( GLADuserptrloadfunc load, void* userptr) {
    if(!GLAD_GL_IMG_multisampled_render_to_texture) return;
    glad_glFramebufferTexture2DMultisampleIMG = (PFNGLFRAMEBUFFERTEXTURE2DMULTISAMPLEIMGPROC) load(userptr, "glFramebufferTexture2DMultisampleIMG");
    glad_glRenderbufferStorageMultisampleIMG = (PFNGLRENDERBUFFERSTORAGEMULTISAMPLEIMGPROC) load(userptr, "glRenderbufferStorageMultisampleIMG");
}
static void glad_gl_load_GL_IMG_user_clip_plane( GLADuserptrloadfunc load, void* userptr) {
    if(!GLAD_GL_IMG_user_clip_plane) return;
    glad_glClipPlanefIMG = (PFNGLCLIPPLANEFIMGPROC) load(userptr, "glClipPlanefIMG");
    glad_glClipPlanexIMG = (PFNGLCLIPPLANEXIMGPROC) load(userptr, "glClipPlanexIMG");
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
static void glad_gl_load_GL_OES_EGL_image( GLADuserptrloadfunc load, void* userptr) {
    if(!GLAD_GL_OES_EGL_image) return;
    glad_glEGLImageTargetRenderbufferStorageOES = (PFNGLEGLIMAGETARGETRENDERBUFFERSTORAGEOESPROC) load(userptr, "glEGLImageTargetRenderbufferStorageOES");
    glad_glEGLImageTargetTexture2DOES = (PFNGLEGLIMAGETARGETTEXTURE2DOESPROC) load(userptr, "glEGLImageTargetTexture2DOES");
}
static void glad_gl_load_GL_OES_blend_equation_separate( GLADuserptrloadfunc load, void* userptr) {
    if(!GLAD_GL_OES_blend_equation_separate) return;
    glad_glBlendEquationSeparateOES = (PFNGLBLENDEQUATIONSEPARATEOESPROC) load(userptr, "glBlendEquationSeparateOES");
}
static void glad_gl_load_GL_OES_blend_func_separate( GLADuserptrloadfunc load, void* userptr) {
    if(!GLAD_GL_OES_blend_func_separate) return;
    glad_glBlendFuncSeparateOES = (PFNGLBLENDFUNCSEPARATEOESPROC) load(userptr, "glBlendFuncSeparateOES");
}
static void glad_gl_load_GL_OES_blend_subtract( GLADuserptrloadfunc load, void* userptr) {
    if(!GLAD_GL_OES_blend_subtract) return;
    glad_glBlendEquationOES = (PFNGLBLENDEQUATIONOESPROC) load(userptr, "glBlendEquationOES");
}
static void glad_gl_load_GL_OES_draw_texture( GLADuserptrloadfunc load, void* userptr) {
    if(!GLAD_GL_OES_draw_texture) return;
    glad_glDrawTexfOES = (PFNGLDRAWTEXFOESPROC) load(userptr, "glDrawTexfOES");
    glad_glDrawTexfvOES = (PFNGLDRAWTEXFVOESPROC) load(userptr, "glDrawTexfvOES");
    glad_glDrawTexiOES = (PFNGLDRAWTEXIOESPROC) load(userptr, "glDrawTexiOES");
    glad_glDrawTexivOES = (PFNGLDRAWTEXIVOESPROC) load(userptr, "glDrawTexivOES");
    glad_glDrawTexsOES = (PFNGLDRAWTEXSOESPROC) load(userptr, "glDrawTexsOES");
    glad_glDrawTexsvOES = (PFNGLDRAWTEXSVOESPROC) load(userptr, "glDrawTexsvOES");
    glad_glDrawTexxOES = (PFNGLDRAWTEXXOESPROC) load(userptr, "glDrawTexxOES");
    glad_glDrawTexxvOES = (PFNGLDRAWTEXXVOESPROC) load(userptr, "glDrawTexxvOES");
}
static void glad_gl_load_GL_OES_fixed_point( GLADuserptrloadfunc load, void* userptr) {
    if(!GLAD_GL_OES_fixed_point) return;
    glad_glAlphaFuncxOES = (PFNGLALPHAFUNCXOESPROC) load(userptr, "glAlphaFuncxOES");
    glad_glClearColorxOES = (PFNGLCLEARCOLORXOESPROC) load(userptr, "glClearColorxOES");
    glad_glClearDepthxOES = (PFNGLCLEARDEPTHXOESPROC) load(userptr, "glClearDepthxOES");
    glad_glClipPlanexOES = (PFNGLCLIPPLANEXOESPROC) load(userptr, "glClipPlanexOES");
    glad_glColor4xOES = (PFNGLCOLOR4XOESPROC) load(userptr, "glColor4xOES");
    glad_glDepthRangexOES = (PFNGLDEPTHRANGEXOESPROC) load(userptr, "glDepthRangexOES");
    glad_glFogxOES = (PFNGLFOGXOESPROC) load(userptr, "glFogxOES");
    glad_glFogxvOES = (PFNGLFOGXVOESPROC) load(userptr, "glFogxvOES");
    glad_glFrustumxOES = (PFNGLFRUSTUMXOESPROC) load(userptr, "glFrustumxOES");
    glad_glGetClipPlanexOES = (PFNGLGETCLIPPLANEXOESPROC) load(userptr, "glGetClipPlanexOES");
    glad_glGetFixedvOES = (PFNGLGETFIXEDVOESPROC) load(userptr, "glGetFixedvOES");
    glad_glGetLightxvOES = (PFNGLGETLIGHTXVOESPROC) load(userptr, "glGetLightxvOES");
    glad_glGetMaterialxvOES = (PFNGLGETMATERIALXVOESPROC) load(userptr, "glGetMaterialxvOES");
    glad_glGetTexEnvxvOES = (PFNGLGETTEXENVXVOESPROC) load(userptr, "glGetTexEnvxvOES");
    glad_glGetTexParameterxvOES = (PFNGLGETTEXPARAMETERXVOESPROC) load(userptr, "glGetTexParameterxvOES");
    glad_glLightModelxOES = (PFNGLLIGHTMODELXOESPROC) load(userptr, "glLightModelxOES");
    glad_glLightModelxvOES = (PFNGLLIGHTMODELXVOESPROC) load(userptr, "glLightModelxvOES");
    glad_glLightxOES = (PFNGLLIGHTXOESPROC) load(userptr, "glLightxOES");
    glad_glLightxvOES = (PFNGLLIGHTXVOESPROC) load(userptr, "glLightxvOES");
    glad_glLineWidthxOES = (PFNGLLINEWIDTHXOESPROC) load(userptr, "glLineWidthxOES");
    glad_glLoadMatrixxOES = (PFNGLLOADMATRIXXOESPROC) load(userptr, "glLoadMatrixxOES");
    glad_glMaterialxOES = (PFNGLMATERIALXOESPROC) load(userptr, "glMaterialxOES");
    glad_glMaterialxvOES = (PFNGLMATERIALXVOESPROC) load(userptr, "glMaterialxvOES");
    glad_glMultMatrixxOES = (PFNGLMULTMATRIXXOESPROC) load(userptr, "glMultMatrixxOES");
    glad_glMultiTexCoord4xOES = (PFNGLMULTITEXCOORD4XOESPROC) load(userptr, "glMultiTexCoord4xOES");
    glad_glNormal3xOES = (PFNGLNORMAL3XOESPROC) load(userptr, "glNormal3xOES");
    glad_glOrthoxOES = (PFNGLORTHOXOESPROC) load(userptr, "glOrthoxOES");
    glad_glPointParameterxOES = (PFNGLPOINTPARAMETERXOESPROC) load(userptr, "glPointParameterxOES");
    glad_glPointParameterxvOES = (PFNGLPOINTPARAMETERXVOESPROC) load(userptr, "glPointParameterxvOES");
    glad_glPointSizexOES = (PFNGLPOINTSIZEXOESPROC) load(userptr, "glPointSizexOES");
    glad_glPolygonOffsetxOES = (PFNGLPOLYGONOFFSETXOESPROC) load(userptr, "glPolygonOffsetxOES");
    glad_glRotatexOES = (PFNGLROTATEXOESPROC) load(userptr, "glRotatexOES");
    glad_glSampleCoveragexOES = (PFNGLSAMPLECOVERAGEXOESPROC) load(userptr, "glSampleCoveragexOES");
    glad_glScalexOES = (PFNGLSCALEXOESPROC) load(userptr, "glScalexOES");
    glad_glTexEnvxOES = (PFNGLTEXENVXOESPROC) load(userptr, "glTexEnvxOES");
    glad_glTexEnvxvOES = (PFNGLTEXENVXVOESPROC) load(userptr, "glTexEnvxvOES");
    glad_glTexParameterxOES = (PFNGLTEXPARAMETERXOESPROC) load(userptr, "glTexParameterxOES");
    glad_glTexParameterxvOES = (PFNGLTEXPARAMETERXVOESPROC) load(userptr, "glTexParameterxvOES");
    glad_glTranslatexOES = (PFNGLTRANSLATEXOESPROC) load(userptr, "glTranslatexOES");
}
static void glad_gl_load_GL_OES_framebuffer_object( GLADuserptrloadfunc load, void* userptr) {
    if(!GLAD_GL_OES_framebuffer_object) return;
    glad_glBindFramebufferOES = (PFNGLBINDFRAMEBUFFEROESPROC) load(userptr, "glBindFramebufferOES");
    glad_glBindRenderbufferOES = (PFNGLBINDRENDERBUFFEROESPROC) load(userptr, "glBindRenderbufferOES");
    glad_glCheckFramebufferStatusOES = (PFNGLCHECKFRAMEBUFFERSTATUSOESPROC) load(userptr, "glCheckFramebufferStatusOES");
    glad_glDeleteFramebuffersOES = (PFNGLDELETEFRAMEBUFFERSOESPROC) load(userptr, "glDeleteFramebuffersOES");
    glad_glDeleteRenderbuffersOES = (PFNGLDELETERENDERBUFFERSOESPROC) load(userptr, "glDeleteRenderbuffersOES");
    glad_glFramebufferRenderbufferOES = (PFNGLFRAMEBUFFERRENDERBUFFEROESPROC) load(userptr, "glFramebufferRenderbufferOES");
    glad_glFramebufferTexture2DOES = (PFNGLFRAMEBUFFERTEXTURE2DOESPROC) load(userptr, "glFramebufferTexture2DOES");
    glad_glGenFramebuffersOES = (PFNGLGENFRAMEBUFFERSOESPROC) load(userptr, "glGenFramebuffersOES");
    glad_glGenRenderbuffersOES = (PFNGLGENRENDERBUFFERSOESPROC) load(userptr, "glGenRenderbuffersOES");
    glad_glGenerateMipmapOES = (PFNGLGENERATEMIPMAPOESPROC) load(userptr, "glGenerateMipmapOES");
    glad_glGetFramebufferAttachmentParameterivOES = (PFNGLGETFRAMEBUFFERATTACHMENTPARAMETERIVOESPROC) load(userptr, "glGetFramebufferAttachmentParameterivOES");
    glad_glGetRenderbufferParameterivOES = (PFNGLGETRENDERBUFFERPARAMETERIVOESPROC) load(userptr, "glGetRenderbufferParameterivOES");
    glad_glIsFramebufferOES = (PFNGLISFRAMEBUFFEROESPROC) load(userptr, "glIsFramebufferOES");
    glad_glIsRenderbufferOES = (PFNGLISRENDERBUFFEROESPROC) load(userptr, "glIsRenderbufferOES");
    glad_glRenderbufferStorageOES = (PFNGLRENDERBUFFERSTORAGEOESPROC) load(userptr, "glRenderbufferStorageOES");
}
static void glad_gl_load_GL_OES_mapbuffer( GLADuserptrloadfunc load, void* userptr) {
    if(!GLAD_GL_OES_mapbuffer) return;
    glad_glGetBufferPointervOES = (PFNGLGETBUFFERPOINTERVOESPROC) load(userptr, "glGetBufferPointervOES");
    glad_glMapBufferOES = (PFNGLMAPBUFFEROESPROC) load(userptr, "glMapBufferOES");
    glad_glUnmapBufferOES = (PFNGLUNMAPBUFFEROESPROC) load(userptr, "glUnmapBufferOES");
}
static void glad_gl_load_GL_OES_matrix_palette( GLADuserptrloadfunc load, void* userptr) {
    if(!GLAD_GL_OES_matrix_palette) return;
    glad_glCurrentPaletteMatrixOES = (PFNGLCURRENTPALETTEMATRIXOESPROC) load(userptr, "glCurrentPaletteMatrixOES");
    glad_glLoadPaletteFromModelViewMatrixOES = (PFNGLLOADPALETTEFROMMODELVIEWMATRIXOESPROC) load(userptr, "glLoadPaletteFromModelViewMatrixOES");
    glad_glMatrixIndexPointerOES = (PFNGLMATRIXINDEXPOINTEROESPROC) load(userptr, "glMatrixIndexPointerOES");
    glad_glWeightPointerOES = (PFNGLWEIGHTPOINTEROESPROC) load(userptr, "glWeightPointerOES");
}
static void glad_gl_load_GL_OES_point_size_array( GLADuserptrloadfunc load, void* userptr) {
    if(!GLAD_GL_OES_point_size_array) return;
    glad_glPointSizePointerOES = (PFNGLPOINTSIZEPOINTEROESPROC) load(userptr, "glPointSizePointerOES");
}
static void glad_gl_load_GL_OES_query_matrix( GLADuserptrloadfunc load, void* userptr) {
    if(!GLAD_GL_OES_query_matrix) return;
    glad_glQueryMatrixxOES = (PFNGLQUERYMATRIXXOESPROC) load(userptr, "glQueryMatrixxOES");
}
static void glad_gl_load_GL_OES_single_precision( GLADuserptrloadfunc load, void* userptr) {
    if(!GLAD_GL_OES_single_precision) return;
    glad_glClearDepthfOES = (PFNGLCLEARDEPTHFOESPROC) load(userptr, "glClearDepthfOES");
    glad_glClipPlanefOES = (PFNGLCLIPPLANEFOESPROC) load(userptr, "glClipPlanefOES");
    glad_glDepthRangefOES = (PFNGLDEPTHRANGEFOESPROC) load(userptr, "glDepthRangefOES");
    glad_glFrustumfOES = (PFNGLFRUSTUMFOESPROC) load(userptr, "glFrustumfOES");
    glad_glGetClipPlanefOES = (PFNGLGETCLIPPLANEFOESPROC) load(userptr, "glGetClipPlanefOES");
    glad_glOrthofOES = (PFNGLORTHOFOESPROC) load(userptr, "glOrthofOES");
}
static void glad_gl_load_GL_OES_texture_cube_map( GLADuserptrloadfunc load, void* userptr) {
    if(!GLAD_GL_OES_texture_cube_map) return;
    glad_glGetTexGenfvOES = (PFNGLGETTEXGENFVOESPROC) load(userptr, "glGetTexGenfvOES");
    glad_glGetTexGenivOES = (PFNGLGETTEXGENIVOESPROC) load(userptr, "glGetTexGenivOES");
    glad_glGetTexGenxvOES = (PFNGLGETTEXGENXVOESPROC) load(userptr, "glGetTexGenxvOES");
    glad_glTexGenfOES = (PFNGLTEXGENFOESPROC) load(userptr, "glTexGenfOES");
    glad_glTexGenfvOES = (PFNGLTEXGENFVOESPROC) load(userptr, "glTexGenfvOES");
    glad_glTexGeniOES = (PFNGLTEXGENIOESPROC) load(userptr, "glTexGeniOES");
    glad_glTexGenivOES = (PFNGLTEXGENIVOESPROC) load(userptr, "glTexGenivOES");
    glad_glTexGenxOES = (PFNGLTEXGENXOESPROC) load(userptr, "glTexGenxOES");
    glad_glTexGenxvOES = (PFNGLTEXGENXVOESPROC) load(userptr, "glTexGenxvOES");
}
static void glad_gl_load_GL_OES_vertex_array_object( GLADuserptrloadfunc load, void* userptr) {
    if(!GLAD_GL_OES_vertex_array_object) return;
    glad_glBindVertexArrayOES = (PFNGLBINDVERTEXARRAYOESPROC) load(userptr, "glBindVertexArrayOES");
    glad_glDeleteVertexArraysOES = (PFNGLDELETEVERTEXARRAYSOESPROC) load(userptr, "glDeleteVertexArraysOES");
    glad_glGenVertexArraysOES = (PFNGLGENVERTEXARRAYSOESPROC) load(userptr, "glGenVertexArraysOES");
    glad_glIsVertexArrayOES = (PFNGLISVERTEXARRAYOESPROC) load(userptr, "glIsVertexArrayOES");
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

static int glad_gl_find_extensions_gles1( int version) {
    const char *exts = NULL;
    unsigned int num_exts_i = 0;
    char **exts_i = NULL;
    if (!glad_gl_get_extensions(version, &exts, &num_exts_i, &exts_i)) return 0;

    GLAD_GL_AMD_compressed_3DC_texture = glad_gl_has_extension(version, exts, num_exts_i, exts_i, "GL_AMD_compressed_3DC_texture");
    GLAD_GL_AMD_compressed_ATC_texture = glad_gl_has_extension(version, exts, num_exts_i, exts_i, "GL_AMD_compressed_ATC_texture");
    GLAD_GL_APPLE_copy_texture_levels = glad_gl_has_extension(version, exts, num_exts_i, exts_i, "GL_APPLE_copy_texture_levels");
    GLAD_GL_APPLE_framebuffer_multisample = glad_gl_has_extension(version, exts, num_exts_i, exts_i, "GL_APPLE_framebuffer_multisample");
    GLAD_GL_APPLE_sync = glad_gl_has_extension(version, exts, num_exts_i, exts_i, "GL_APPLE_sync");
    GLAD_GL_APPLE_texture_2D_limited_npot = glad_gl_has_extension(version, exts, num_exts_i, exts_i, "GL_APPLE_texture_2D_limited_npot");
    GLAD_GL_APPLE_texture_format_BGRA8888 = glad_gl_has_extension(version, exts, num_exts_i, exts_i, "GL_APPLE_texture_format_BGRA8888");
    GLAD_GL_APPLE_texture_max_level = glad_gl_has_extension(version, exts, num_exts_i, exts_i, "GL_APPLE_texture_max_level");
    GLAD_GL_ARM_rgba8 = glad_gl_has_extension(version, exts, num_exts_i, exts_i, "GL_ARM_rgba8");
    GLAD_GL_EXT_blend_minmax = glad_gl_has_extension(version, exts, num_exts_i, exts_i, "GL_EXT_blend_minmax");
    GLAD_GL_EXT_debug_marker = glad_gl_has_extension(version, exts, num_exts_i, exts_i, "GL_EXT_debug_marker");
    GLAD_GL_EXT_discard_framebuffer = glad_gl_has_extension(version, exts, num_exts_i, exts_i, "GL_EXT_discard_framebuffer");
    GLAD_GL_EXT_map_buffer_range = glad_gl_has_extension(version, exts, num_exts_i, exts_i, "GL_EXT_map_buffer_range");
    GLAD_GL_EXT_multi_draw_arrays = glad_gl_has_extension(version, exts, num_exts_i, exts_i, "GL_EXT_multi_draw_arrays");
    GLAD_GL_EXT_multisampled_render_to_texture = glad_gl_has_extension(version, exts, num_exts_i, exts_i, "GL_EXT_multisampled_render_to_texture");
    GLAD_GL_EXT_read_format_bgra = glad_gl_has_extension(version, exts, num_exts_i, exts_i, "GL_EXT_read_format_bgra");
    GLAD_GL_EXT_robustness = glad_gl_has_extension(version, exts, num_exts_i, exts_i, "GL_EXT_robustness");
    GLAD_GL_EXT_sRGB = glad_gl_has_extension(version, exts, num_exts_i, exts_i, "GL_EXT_sRGB");
    GLAD_GL_EXT_texture_compression_dxt1 = glad_gl_has_extension(version, exts, num_exts_i, exts_i, "GL_EXT_texture_compression_dxt1");
    GLAD_GL_EXT_texture_filter_anisotropic = glad_gl_has_extension(version, exts, num_exts_i, exts_i, "GL_EXT_texture_filter_anisotropic");
    GLAD_GL_EXT_texture_format_BGRA8888 = glad_gl_has_extension(version, exts, num_exts_i, exts_i, "GL_EXT_texture_format_BGRA8888");
    GLAD_GL_EXT_texture_lod_bias = glad_gl_has_extension(version, exts, num_exts_i, exts_i, "GL_EXT_texture_lod_bias");
    GLAD_GL_EXT_texture_storage = glad_gl_has_extension(version, exts, num_exts_i, exts_i, "GL_EXT_texture_storage");
    GLAD_GL_IMG_multisampled_render_to_texture = glad_gl_has_extension(version, exts, num_exts_i, exts_i, "GL_IMG_multisampled_render_to_texture");
    GLAD_GL_IMG_read_format = glad_gl_has_extension(version, exts, num_exts_i, exts_i, "GL_IMG_read_format");
    GLAD_GL_IMG_texture_compression_pvrtc = glad_gl_has_extension(version, exts, num_exts_i, exts_i, "GL_IMG_texture_compression_pvrtc");
    GLAD_GL_IMG_texture_env_enhanced_fixed_function = glad_gl_has_extension(version, exts, num_exts_i, exts_i, "GL_IMG_texture_env_enhanced_fixed_function");
    GLAD_GL_IMG_user_clip_plane = glad_gl_has_extension(version, exts, num_exts_i, exts_i, "GL_IMG_user_clip_plane");
    GLAD_GL_KHR_debug = glad_gl_has_extension(version, exts, num_exts_i, exts_i, "GL_KHR_debug");
    GLAD_GL_NV_fence = glad_gl_has_extension(version, exts, num_exts_i, exts_i, "GL_NV_fence");
    GLAD_GL_OES_EGL_image = glad_gl_has_extension(version, exts, num_exts_i, exts_i, "GL_OES_EGL_image");
    GLAD_GL_OES_EGL_image_external = glad_gl_has_extension(version, exts, num_exts_i, exts_i, "GL_OES_EGL_image_external");
    GLAD_GL_OES_blend_equation_separate = glad_gl_has_extension(version, exts, num_exts_i, exts_i, "GL_OES_blend_equation_separate");
    GLAD_GL_OES_blend_func_separate = glad_gl_has_extension(version, exts, num_exts_i, exts_i, "GL_OES_blend_func_separate");
    GLAD_GL_OES_blend_subtract = glad_gl_has_extension(version, exts, num_exts_i, exts_i, "GL_OES_blend_subtract");
    GLAD_GL_OES_byte_coordinates = glad_gl_has_extension(version, exts, num_exts_i, exts_i, "GL_OES_byte_coordinates");
    GLAD_GL_OES_compressed_ETC1_RGB8_sub_texture = glad_gl_has_extension(version, exts, num_exts_i, exts_i, "GL_OES_compressed_ETC1_RGB8_sub_texture");
    GLAD_GL_OES_compressed_ETC1_RGB8_texture = glad_gl_has_extension(version, exts, num_exts_i, exts_i, "GL_OES_compressed_ETC1_RGB8_texture");
    GLAD_GL_OES_compressed_paletted_texture = glad_gl_has_extension(version, exts, num_exts_i, exts_i, "GL_OES_compressed_paletted_texture");
    GLAD_GL_OES_depth24 = glad_gl_has_extension(version, exts, num_exts_i, exts_i, "GL_OES_depth24");
    GLAD_GL_OES_depth32 = glad_gl_has_extension(version, exts, num_exts_i, exts_i, "GL_OES_depth32");
    GLAD_GL_OES_draw_texture = glad_gl_has_extension(version, exts, num_exts_i, exts_i, "GL_OES_draw_texture");
    GLAD_GL_OES_element_index_uint = glad_gl_has_extension(version, exts, num_exts_i, exts_i, "GL_OES_element_index_uint");
    GLAD_GL_OES_extended_matrix_palette = glad_gl_has_extension(version, exts, num_exts_i, exts_i, "GL_OES_extended_matrix_palette");
    GLAD_GL_OES_fbo_render_mipmap = glad_gl_has_extension(version, exts, num_exts_i, exts_i, "GL_OES_fbo_render_mipmap");
    GLAD_GL_OES_fixed_point = glad_gl_has_extension(version, exts, num_exts_i, exts_i, "GL_OES_fixed_point");
    GLAD_GL_OES_framebuffer_object = glad_gl_has_extension(version, exts, num_exts_i, exts_i, "GL_OES_framebuffer_object");
    GLAD_GL_OES_mapbuffer = glad_gl_has_extension(version, exts, num_exts_i, exts_i, "GL_OES_mapbuffer");
    GLAD_GL_OES_matrix_get = glad_gl_has_extension(version, exts, num_exts_i, exts_i, "GL_OES_matrix_get");
    GLAD_GL_OES_matrix_palette = glad_gl_has_extension(version, exts, num_exts_i, exts_i, "GL_OES_matrix_palette");
    GLAD_GL_OES_packed_depth_stencil = glad_gl_has_extension(version, exts, num_exts_i, exts_i, "GL_OES_packed_depth_stencil");
    GLAD_GL_OES_point_size_array = glad_gl_has_extension(version, exts, num_exts_i, exts_i, "GL_OES_point_size_array");
    GLAD_GL_OES_point_sprite = glad_gl_has_extension(version, exts, num_exts_i, exts_i, "GL_OES_point_sprite");
    GLAD_GL_OES_query_matrix = glad_gl_has_extension(version, exts, num_exts_i, exts_i, "GL_OES_query_matrix");
    GLAD_GL_OES_read_format = glad_gl_has_extension(version, exts, num_exts_i, exts_i, "GL_OES_read_format");
    GLAD_GL_OES_required_internalformat = glad_gl_has_extension(version, exts, num_exts_i, exts_i, "GL_OES_required_internalformat");
    GLAD_GL_OES_rgb8_rgba8 = glad_gl_has_extension(version, exts, num_exts_i, exts_i, "GL_OES_rgb8_rgba8");
    GLAD_GL_OES_single_precision = glad_gl_has_extension(version, exts, num_exts_i, exts_i, "GL_OES_single_precision");
    GLAD_GL_OES_stencil1 = glad_gl_has_extension(version, exts, num_exts_i, exts_i, "GL_OES_stencil1");
    GLAD_GL_OES_stencil4 = glad_gl_has_extension(version, exts, num_exts_i, exts_i, "GL_OES_stencil4");
    GLAD_GL_OES_stencil8 = glad_gl_has_extension(version, exts, num_exts_i, exts_i, "GL_OES_stencil8");
    GLAD_GL_OES_stencil_wrap = glad_gl_has_extension(version, exts, num_exts_i, exts_i, "GL_OES_stencil_wrap");
    GLAD_GL_OES_surfaceless_context = glad_gl_has_extension(version, exts, num_exts_i, exts_i, "GL_OES_surfaceless_context");
    GLAD_GL_OES_texture_cube_map = glad_gl_has_extension(version, exts, num_exts_i, exts_i, "GL_OES_texture_cube_map");
    GLAD_GL_OES_texture_env_crossbar = glad_gl_has_extension(version, exts, num_exts_i, exts_i, "GL_OES_texture_env_crossbar");
    GLAD_GL_OES_texture_mirrored_repeat = glad_gl_has_extension(version, exts, num_exts_i, exts_i, "GL_OES_texture_mirrored_repeat");
    GLAD_GL_OES_texture_npot = glad_gl_has_extension(version, exts, num_exts_i, exts_i, "GL_OES_texture_npot");
    GLAD_GL_OES_vertex_array_object = glad_gl_has_extension(version, exts, num_exts_i, exts_i, "GL_OES_vertex_array_object");
    GLAD_GL_QCOM_driver_control = glad_gl_has_extension(version, exts, num_exts_i, exts_i, "GL_QCOM_driver_control");
    GLAD_GL_QCOM_extended_get = glad_gl_has_extension(version, exts, num_exts_i, exts_i, "GL_QCOM_extended_get");
    GLAD_GL_QCOM_extended_get2 = glad_gl_has_extension(version, exts, num_exts_i, exts_i, "GL_QCOM_extended_get2");
    GLAD_GL_QCOM_perfmon_global_mode = glad_gl_has_extension(version, exts, num_exts_i, exts_i, "GL_QCOM_perfmon_global_mode");
    GLAD_GL_QCOM_tiled_rendering = glad_gl_has_extension(version, exts, num_exts_i, exts_i, "GL_QCOM_tiled_rendering");
    GLAD_GL_QCOM_writeonly_rendering = glad_gl_has_extension(version, exts, num_exts_i, exts_i, "GL_QCOM_writeonly_rendering");

    glad_gl_free_extensions(exts_i, num_exts_i);

    return 1;
}

static int glad_gl_find_core_gles1(void) {
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

    GLAD_GL_VERSION_ES_CM_1_0 = (major == 1 && minor >= 0) || major > 1;

    return GLAD_MAKE_VERSION(major, minor);
}

int gladLoadGLES1UserPtr( GLADuserptrloadfunc load, void *userptr) {
    int version;

    glad_glGetString = (PFNGLGETSTRINGPROC) load(userptr, "glGetString");
    if(glad_glGetString == NULL) return 0;
    if(glad_glGetString(GL_VERSION) == NULL) return 0;
    version = glad_gl_find_core_gles1();

    glad_gl_load_GL_VERSION_ES_CM_1_0(load, userptr);

    if (!glad_gl_find_extensions_gles1(version)) return 0;
    glad_gl_load_GL_APPLE_copy_texture_levels(load, userptr);
    glad_gl_load_GL_APPLE_framebuffer_multisample(load, userptr);
    glad_gl_load_GL_APPLE_sync(load, userptr);
    glad_gl_load_GL_EXT_debug_marker(load, userptr);
    glad_gl_load_GL_EXT_discard_framebuffer(load, userptr);
    glad_gl_load_GL_EXT_map_buffer_range(load, userptr);
    glad_gl_load_GL_EXT_multi_draw_arrays(load, userptr);
    glad_gl_load_GL_EXT_multisampled_render_to_texture(load, userptr);
    glad_gl_load_GL_EXT_robustness(load, userptr);
    glad_gl_load_GL_EXT_texture_storage(load, userptr);
    glad_gl_load_GL_IMG_multisampled_render_to_texture(load, userptr);
    glad_gl_load_GL_IMG_user_clip_plane(load, userptr);
    glad_gl_load_GL_NV_fence(load, userptr);
    glad_gl_load_GL_OES_EGL_image(load, userptr);
    glad_gl_load_GL_OES_blend_equation_separate(load, userptr);
    glad_gl_load_GL_OES_blend_func_separate(load, userptr);
    glad_gl_load_GL_OES_blend_subtract(load, userptr);
    glad_gl_load_GL_OES_draw_texture(load, userptr);
    glad_gl_load_GL_OES_fixed_point(load, userptr);
    glad_gl_load_GL_OES_framebuffer_object(load, userptr);
    glad_gl_load_GL_OES_mapbuffer(load, userptr);
    glad_gl_load_GL_OES_matrix_palette(load, userptr);
    glad_gl_load_GL_OES_point_size_array(load, userptr);
    glad_gl_load_GL_OES_query_matrix(load, userptr);
    glad_gl_load_GL_OES_single_precision(load, userptr);
    glad_gl_load_GL_OES_texture_cube_map(load, userptr);
    glad_gl_load_GL_OES_vertex_array_object(load, userptr);
    glad_gl_load_GL_QCOM_driver_control(load, userptr);
    glad_gl_load_GL_QCOM_extended_get(load, userptr);
    glad_gl_load_GL_QCOM_extended_get2(load, userptr);
    glad_gl_load_GL_QCOM_tiled_rendering(load, userptr);



    return version;
}


int gladLoadGLES1( GLADloadfunc load) {
    return gladLoadGLES1UserPtr( glad_gl_get_proc_from_userptr, GLAD_GNUC_EXTENSION (void*) load);
}



 

#ifdef GLAD_GLES1

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

#include <glad/egl.h>

struct _glad_gles1_userptr {
    void *handle;
    PFNEGLGETPROCADDRESSPROC get_proc_address_ptr;
};


static GLADapiproc glad_gles1_get_proc(void *vuserptr, const char* name) {
    struct _glad_gles1_userptr userptr = *(struct _glad_gles1_userptr*) vuserptr;
    GLADapiproc result = NULL;

    result = glad_dlsym_handle(userptr.handle, name);
    if (result == NULL) {
        result = userptr.get_proc_address_ptr(name);
    }

    return result;
}

static void* _gles1_handle = NULL;

static void* glad_gles1_dlopen_handle(void) {
#if GLAD_PLATFORM_APPLE
    static const char *NAMES[] = {"libGLESv1_CM.dylib"};
#elif GLAD_PLATFORM_WIN32
    static const char *NAMES[] = {"GLESv1_CM.dll", "libGLESv1_CM", "libGLES_CM.dll"};
#else
    static const char *NAMES[] = {"libGLESv1_CM.so.1", "libGLESv1_CM.so", "libGLES_CM.so.1"};
#endif

    if (_gles1_handle == NULL) {
        _gles1_handle = glad_get_dlopen_handle(NAMES, sizeof(NAMES) / sizeof(NAMES[0]));
    }

    return _gles1_handle;
}

static struct _glad_gles1_userptr glad_gles1_build_userptr(void *handle) {
    struct _glad_gles1_userptr userptr;
    userptr.handle = handle;
    userptr.get_proc_address_ptr = eglGetProcAddress;
    return userptr;
}

int gladLoaderLoadGLES1(void) {
    int version = 0;
    void *handle = NULL;
    int did_load = 0;
    struct _glad_gles1_userptr userptr;

    if (eglGetProcAddress == NULL) {
        return 0;
    }

    did_load = _gles1_handle == NULL;
    handle = glad_gles1_dlopen_handle();
    if (handle != NULL) {
        userptr = glad_gles1_build_userptr(handle);

        version = gladLoadGLES1UserPtr(glad_gles1_get_proc, &userptr);

        if (!version && did_load) {
            gladLoaderUnloadGLES1();
        }
    }

    return version;
}



void gladLoaderUnloadGLES1(void) {
    if (_gles1_handle != NULL) {
        glad_close_dlopen_handle(_gles1_handle);
        _gles1_handle = NULL;
    }
}

#endif /* GLAD_GLES1 */

#ifdef __cplusplus
}
#endif
