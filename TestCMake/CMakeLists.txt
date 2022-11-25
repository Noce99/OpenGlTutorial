project(primo-cubo-cmake)

cmake_minimum_required(VERSION 3.4.0 FATAL_ERROR)

set(SOURCES main.cpp)


find_package(glfw3 3.3 REQUIRED)

include_directories(/usr/include/GL/)

find_library(GLEW_LIB NAMES glew)
find_library(GL_LIB NAMES GL)

target_link_libraries(run glfw)
target_link_libraries(run ${GLEW_LIB})
target_link_libraries(run ${GL_LIB})

add_executable(run ${SOURCES})
