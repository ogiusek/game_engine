cmake_minimum_required(VERSION 3.0)
project(program)

set(CMAKE_CXX_STANDARD 11)

add_executable(program src/main.cpp)

# set_target_properties(program PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/dist)

target_link_libraries(program SDL2 GL GLU SDL2_ttf SDL2_image)
