project(${TORQUE_APP_NAME})

# Enable ObjectiveC compilation when compiling for Apple platforms
if (APPLE)
	enable_language(OBJC)
endif (APPLE)

################# Helper Function Calls ###################
forwardDef(TORQUE_OPENGL)
forwardDef(TORQUE_D3D11)
forwardDef(TORQUE_ADVANCED_LIGHTING)
forwardDef(TORQUE_BASIC_LIGHTING)
set(TORQUE_SDL ON) # we need sdl to do our platform interop
forwardDef(TORQUE_SDL)

if(TORQUE_TESTING)
set(TORQUE_COMPILE_DEFINITIONS ${TORQUE_COMPILE_DEFINITIONS} TORQUE_TESTS_ENABLED)
set(TORQUE_COMPILE_DEFINITIONS ${TORQUE_COMPILE_DEFINITIONS} "_VARIADIC_MAX=10")
endif()

if(APPLE)
  include(torqueMacosEngine.cmake)
else()
  include(torqueEveryEngine.cmake)
endif(APPLE)