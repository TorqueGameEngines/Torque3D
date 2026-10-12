# Bullet module
option(TORQUE_PHYSICS_BULLET "Use Bullet physics" OFF)

if(TORQUE_PHYSICS_BULLET)
  message("Enabling Bullet Module")
  find_package(Bullet CONFIG REQUIRED)
  set(TORQUE_LINK_THIRDPARTY ${TORQUE_LINK_THIRDPARTY} BulletDynamics BulletCollision LinearMath Bullet3Common)
  set(TORQUE_COMPILE_DEFINITIONS ${TORQUE_COMPILE_DEFINITIONS} TORQUE_PHYSICS_BULLET TORQUE_PHYSICS_ENABLED)
  # No more add_subdirectory — vcpkg's bullet3 port provides the targets above.
endif(TORQUE_PHYSICS_BULLET)
