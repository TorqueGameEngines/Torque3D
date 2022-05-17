file(GLOB OPCODE_SOURCES "*.cpp" "Ice/*.cpp")

add_library(opcode STATIC ${OPCODE_SOURCES})
target_compile_definitions(opcode PUBLIC ICE_NO_DLL TORQUE_OPCODE)
target_include_directories(opcode PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
