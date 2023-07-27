################# Set Engine Linkages ###################

# When on Windows, we need to link against winsock and windows codecs
if (WIN32)
	set(TORQUE_LINK_LIBRARIES ${TORQUE_LINK_LIBRARIES} WS2_32.LIB windowscodecs.lib)	
	if (TORQUE_D3D11)
		set(TORQUE_LINK_LIBRARIES ${TORQUE_LINK_LIBRARIES} dxguid.lib)
	endif (TORQUE_D3D11)
endif (WIN32)

# Only link Apple frameworks when on an Apple platform
if (APPLE)
    addFramework("Cocoa")
    addFramework("AppKit")
    addFramework("CoreData")
    addFramework("Foundation")
    #These are needed by sdl2 static lib
    addFramework("ForceFeedback")
    addFramework("IOKit")
    #grrr damn you sdl!
    addFramework("Carbon")
    set(TORQUE_LINK_LIBRARIES ${TORQUE_LINK_LIBRARIES} iconv)
    if(NOT TORQUE_DEDICATED)
        addFramework("OpenGL")
        addFramework("CoreVideo")
        if(TORQUE_SFX_OPENAL)
            addFramework("OpenAL")
            addFramework("CoreAudio")
            addFramework("AudioUnit")
            addFramework("AudioToolbox")
        endif(TORQUE_SFX_OPENAL)
    endif()
endif (APPLE)

set(TORQUE_LINK_LIBRARIES ${TORQUE_LINK_LIBRARIES} nativeFileDialogs)

# Linux requires X11 & freetype
if (UNIX AND NOT APPLE)
	set(TORQUE_LINK_LIBRARIES ${TORQUE_LINK_LIBRARIES} "X11" "Xft" "dl" "pthread")  
	find_package(Freetype REQUIRED)
	set(TORQUE_INCLUDE_DIRECTORIES ${TORQUE_INCLUDE_DIRECTORIES} ${FREETYPE_INCLUDE_DIRS})
	set(TORQUE_LINK_LIBRARIES ${TORQUE_LINK_LIBRARIES} ${FREETYPE_LIBRARIES})
endif (UNIX AND NOT APPLE)