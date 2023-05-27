file(GLOB RECAST_SOURCES "DebugUtils/Source/*.cpp" "Recast/Source/*.cpp" "Detour/Source/*.cpp" "DetourCrowd/Source/*.cpp"
                         "DetourTileCache/Source/*.cpp")

add_library(recast STATIC ${RECAST_SOURCES})
target_include_directories(recast PUBLIC "DebugUtils/Include" "Recast/Include" "Detour/Include"
                                         "DetourTileCache/Include" "DetourCrowd/Include")
