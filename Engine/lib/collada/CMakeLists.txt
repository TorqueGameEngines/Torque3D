file(GLOB COLLADA_SOURCES "src/1.4/dom/*.cpp" "src/dae/*.cpp" "src/modules/LIBXMLPlugin/*.cpp"
                          "src/modules/stdErrPlugin/*.cpp" "src/modules/STLDatabase/*.cpp")

add_library(collada STATIC ${COLLADA_SOURCES})
target_include_directories(collada PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include ${CMAKE_CURRENT_SOURCE_DIR}/include/1.4)
target_compile_definitions(collada PUBLIC DOM_INCLUDE_TINYXML PCRE_STATIC)
find_package(tinyxml2 CONFIG REQUIRED)
find_package(unofficial-pcre CONFIG REQUIRED)
target_link_libraries(collada PUBLIC tinyxml2::tinyxml2 unofficial::pcre::pcre unofficial::pcre::pcre16 unofficial::pcre::pcre32 unofficial::pcre::pcrecpp)
