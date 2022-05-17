file(GLOB PCRE_SOURCES "*.c" "*.cc")

add_library(pcre STATIC ${PCRE_SOURCES})
target_compile_definitions(pcre PUBLIC PCRE_STATIC HAVE_CONFIG_H)
target_include_directories(pcre PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

if(WIN32)
    set_property(TARGET pcre PROPERTY COMPILE_FLAGS /TP) #/TP = compile as C++
endif()
