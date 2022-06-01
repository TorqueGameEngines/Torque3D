file(GLOB TEMPLATE_FILES "*.bat" "*.command")
foreach(TEMPLATE_FILE ${TEMPLATE_FILES})
    file(COPY ${TEMPLATE_FILE} DESTINATION "${TORQUE_APP_ROOT_DIRECTORY}")
endforeach()

# Perform installation minus scripts
file(COPY "game" "source" DESTINATION "${TORQUE_APP_ROOT_DIRECTORY}" PATTERN "*.tscript" EXCLUDE PATTERN
                                                                     PATTERN "*.in" EXCLUDE PATTERN)	
# Enumerate scripts and install with extension
file(GLOB_RECURSE SCRIPT_FILES "game/*.tscript")
foreach(ITEM ${SCRIPT_FILES})
    get_filename_component( dir ${ITEM} DIRECTORY )
    get_filename_component( scriptName ${ITEM} NAME )

    STRING(REGEX REPLACE "${CMAKE_SOURCE_DIR}/Templates/${TORQUE_TEMPLATE}/" "${TORQUE_APP_ROOT_DIRECTORY}/" INSTALL_DIR ${dir})
    STRING(REGEX REPLACE ".tscript" ".${TORQUE_SCRIPT_EXTENSION}" newScriptName ${scriptName})

    # Copy the file and perform a rename at the same time
    file(COPY_FILE ${ITEM} ${INSTALL_DIR}/${newScriptName})
endforeach()

# Once the full tree is installed, perform configurations
CONFIGURE_FILE("game/main.tscript.in" "${TORQUE_APP_GAME_DIRECTORY}/main.${TORQUE_SCRIPT_EXTENSION}")
