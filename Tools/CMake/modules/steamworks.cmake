option(TORQUE_STEAMWORKS "Add Steamworks API plugin (download and extract sdk to lib/steamSDK)" OFF)
option(TORQUE_STEAMWORKS_REQUIRED "Check if the engine should not launch without the Steam client running." OFF)
option(TORQUE_STEAM_GAMESERVER "Check if the Steam game server modules should be installed." OFF)
option(USE_GS_AUTH_API "Use steams game server authentication api." ON)

if("${TORQUE_STEAMWORKS_APPID}" STREQUAL "")
    set(TORQUE_STEAMWORKS_APPID 0 CACHE STRING "The Steam App ID of your game.")
endif()

if(TORQUE_STEAMWORKS)

    if(("${TORQUE_STEAMWORKS_APPID}" STREQUAL "") OR ("${TORQUE_STEAMWORKS_APPID}" STREQUAL "0"))
        message(FATAL_ERROR "No Steamworks App ID entered")
    endif()

    set(TORQUE_INCLUDE_DIRECTORIES ${TORQUE_INCLUDE_DIRECTORIES} "${TORQUE_LIB_ROOT_DIRECTORY}/SteamSDK/public/steam")

    if(WIN32)
        if(TORQUE_CPU_X64)
            set(TORQUE_LINK_LIBRARIES ${TORQUE_LINK_LIBRARIES} "${TORQUE_LIB_ROOT_DIRECTORY}/SteamSDK/redistributable_bin/win64/steam_api64.lib")
            set(TORQUE_ADDITIONAL_LIBRARY_BINARIES ${TORQUE_ADDITIONAL_LIBRARY_BINARIES} "${TORQUE_LIB_ROOT_DIRECTORY}/SteamSDK/redistributable_bin/win64/steam_api64.dll")
        else()
            set(TORQUE_LINK_LIBRARIES ${TORQUE_LINK_LIBRARIES} "${TORQUE_LIB_ROOT_DIRECTORY}/SteamSDK/redistributable_bin/steam_api.lib")
            set(TORQUE_ADDITIONAL_LIBRARY_BINARIES ${TORQUE_ADDITIONAL_LIBRARY_BINARIES} "${TORQUE_LIB_ROOT_DIRECTORY}/SteamSDK/redistributable_bin/steam_api.dll")
        endif()
    endif(WIN32)

    if(UNIX AND NOT APPLE)
        if(TORQUE_CPU_X64)
            set(TORQUE_ADDITIONAL_LIBRARY_BINARIES ${TORQUE_ADDITIONAL_LIBRARY_BINARIES} "${TORQUE_LIB_ROOT_DIRECTORY}/SteamSDK/redistributable_bin/linux64/libsteam_api.so")
        else()
            set(TORQUE_ADDITIONAL_LIBRARY_BINARIES ${TORQUE_ADDITIONAL_LIBRARY_BINARIES} "${TORQUE_LIB_ROOT_DIRECTORY}/SteamSDK/redistributable_bin/linux32/libsteam_api.so")
        endif()
    endif()

    if(APPLE)
        set(TORQUE_ADDITIONAL_LIBRARY_BINARIES ${TORQUE_ADDITIONAL_LIBRARY_BINARIES} "${TORQUE_LIB_ROOT_DIRECTORY}/SteamSDK/redistributable_bin/osx/libsteam_api.dylib")
    endif()

    # Generate torqueConfig.h in our temp directory
    configure_file("${TORQUE_LIB_ROOT_DIRECTORY}/SteamSDK/steam_appid.txt.in" "${TORQUE_APP_GAME_DIRECTORY}/steam_appid.txt")
    configure_file("${TORQUE_LIB_ROOT_DIRECTORY}/SteamSDK/steamConfig.h.in" "${TORQUE_APP_ROOT_DIRECTORY}/source/steamConfig.h")

endif(TORQUE_STEAMWORKS)