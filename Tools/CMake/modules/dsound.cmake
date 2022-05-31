# OpenAL module
option(TORQUE_SFX_DIRECTX "Use DirectSound SFX" OFF)

if(TORQUE_SFX_DIRECTX AND WIN32)
  message("Enabling DirectSound Module")

  file(GLOB TORQUE_DSOUND_SOURCES "${CMAKE_SOURCE_DIR}/Engine/source/sfx/dsound/*.cpp" "${CMAKE_SOURCE_DIR}/Engine/source/sfx/xaudio/*.cpp")

  set(TORQUE_SOURCE_FILES ${TORQUE_SOURCE_FILES} ${TORQUE_DSOUND_SOURCES})
endif(TORQUE_SFX_DIRECTX AND WIN32)
