# Bullet module
option(TORQUE_PHYSICS_BULLET "Use Bullet physics" OFF)

if(TORQUE_PHYSICS_BULLET)
  message("Enabling Bullet Module")

  torqueAddSourceDirectories("${CMAKE_SOURCE_DIR}/Engine/source/T3D/physics/bullet")
  set(TORQUE_LINK_LIBRARIES ${TORQUE_LINK_LIBRARIES} BulletSoftBody Bullet3Dynamics BulletInverseDynamics BulletCollision
                                                     Bullet2FileLoader BulletDynamics Bullet3OpenCL_clew Bullet3Common
                                                     LinearMath Bullet3Geometry Bullet3Collision)
  set(TORQUE_COMPILE_DEFINITIONS ${TORQUE_COMPILE_DEFINITIONS} TORQUE_PHYSICS_BULLET TORQUE_PHYSICS_ENABLED)
  set(TORQUE_INCLUDE_DIRECTORIES ${TORQUE_INCLUDE_DIRECTORIES} "${CMAKE_SOURCE_DIR}/Engine/lib/bullet/src" )

  # Since Bullet lives elsewhere we need to ensure it is known to Torque when providing a link to it
  set(BUILD_SHARED_LIBS OFF CACHE BOOL "Bullet Shared Libs" FORCE)
  set(BUILD_CPU_DEMOS OFF CACHE BOOL "Bullet CPU Demos" FORCE)
  set(BUILD_BULLET2_DEMOS OFF CACHE BOOL "Bullet2 Demos" FORCE)
  add_subdirectory("${CMAKE_SOURCE_DIR}/Engine/lib/bullet" ${CMAKE_BINARY_DIR}/temp/bullet EXCLUDE_FROM_ALL)
endif(TORQUE_PHYSICS_BULLET)
