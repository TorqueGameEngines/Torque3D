add_library(tinyxml STATIC "tinyxml2.cpp")

# NOTE: Some stuff include tinyxml by tinyxml/tinyxml2.h instead of just tinyxml2.h
target_include_directories(tinyxml PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/../)
