#if(TORQUE_SFX_OPENAL AND NOT TORQUE_DEDICATED)
    project(libvorbis)
    file(GLOB LIBVORBIS_SOURCE_FILES "lib/*.c")
    file(GLOB LIBVORBIS_HEADER_FILES "include/vorbis/*.h") 
    set(LIBVORBIS_FILES ${LIBVORBIS_SOURCE_FILES} ${LIBVORBIS_HEADER_FILES}) 

    add_library(libvorbis ${LIBVORBIS_FILES})
    target_include_directories(libvorbis PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include")
    target_link_libraries(libvorbis PUBLIC libogg)

    if (UNIX)
        target_include_directories(libvorbis PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/lib")
    endif (UNIX)

    set(TORQUE_INCLUDE_DIRECTORIES ${TORQUE_INCLUDE_DIRECTORIES} "${CMAKE_CURRENT_SOURCE_DIR}/include/vorbis")
    #set(TORQUE_LINK_LIBRARIES ${TORQUE_LINK_LIBRARIES} libvorbis PARENT_SCOPE)
#endif()