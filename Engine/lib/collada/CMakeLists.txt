file(GLOB COLLADA_SOURCES "src/1.4/dom/*.cpp" "src/dae/*.cpp" "src/modules/LIBXMLPlugin/*.cpp"
                          "src/modules/stdErrPlugin/*.cpp" "src/modules/STLDatabase/*.cpp")

add_library(collada STATIC ${COLLADA_SOURCES})
target_include_directories(collada PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include ${CMAKE_CURRENT_SOURCE_DIR}/include/1.4)
target_compile_definitions(collada PUBLIC DOM_INCLUDE_TINYXML PCRE_STATIC)
target_link_libraries(collada PUBLIC tinyxml pcre)
