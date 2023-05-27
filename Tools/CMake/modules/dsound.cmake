# OpenAL module
option(TORQUE_SFX_DIRECTX "Use DirectSound SFX" OFF)

if(TORQUE_SFX_DIRECTX AND WIN32)
  message("Enabling DirectSound Module")

  torqueAddSourceDirectories("${CMAKE_SOURCE_DIR}/Engine/source/sfx/dsound" "${CMAKE_SOURCE_DIR}/Engine/source/sfx/xaudio")
endif(TORQUE_SFX_DIRECTX AND WIN32)
