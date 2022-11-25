cmake_minimum_required(VERSION 3.4.0 FATAL_ERROR)

get_filename_component(executable_name ${CMAKE_CURRENT_SOURCE_DIR} NAME)

add_executable(${executable_name} main.cpp)

find_package(glfw3 3.3 REQUIRED)

include_directories(/usr/include/GL/)

find_library(GLEW_LIB NAMES glew)
find_library(GL_LIB NAMES GL)

target_link_libraries(${executable_name} glfw)
target_link_libraries(${executable_name} ${GLEW_LIB})
target_link_libraries(${executable_name} ${GL_LIB})

set(EXECUTABLE_OUTPUT_PATH "${PROJECT_BINARY_DIR}/Executables/${executable_name}")
