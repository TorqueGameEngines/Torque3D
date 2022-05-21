file(GLOB TEMPLATE_FILES "*.bat" "*.command")
install(FILES ${TEMPLATE_FILES} DESTINATION .)

# Perform installation minus scripts
install(DIRECTORY "game" "source" DESTINATION .
        PATTERN "*.tscript"
        EXCLUDE PATTERN)

# Enumerate scripts and install with extension
file(GLOB_RECURSE SCRIPT_FILES "game/*.tscript")
foreach(ITEM ${SCRIPT_FILES})
    get_filename_component( dir ${ITEM} DIRECTORY )
    get_filename_component( scriptName ${ITEM} NAME )

    STRING(REGEX REPLACE "${CMAKE_SOURCE_DIR}/Templates/${TORQUE_TEMPLATE}/" "${CMAKE_INSTALL_PREFIX}/" INSTALL_DIR ${dir})
    STRING(REGEX REPLACE ".tscript" ".${TORQUE_SCRIPT_EXTENSION}" newScriptName ${scriptName})
    install( FILES ${ITEM} DESTINATION ${INSTALL_DIR} RENAME ${newScriptName} )
endforeach()

# Once the full tree is installed, perform configurations on several files
CONFIGURE_FILE("game/main.tscript.in" "${CMAKE_INSTALL_PREFIX}/game/main.${TORQUE_SCRIPT_EXTENSION}")
