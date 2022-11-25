cmake_minimum_required(VERSION 3.4.0 FATAL_ERROR)

get_filename_component(executable_name ${CMAKE_CURRENT_SOURCE_DIR} NAME)

add_executable("${executable_name}_moto" OpenMoto.cpp)
add_executable("${executable_name}_monkey" OpenMonkey.cpp)
add_executable("${executable_name}_catamarano" OpenCatamarano.cpp)
add_executable("${executable_name}_sailingboat" OpenSailingBoat.cpp)

find_package(glfw3 3.3 REQUIRED)

include_directories(/usr/include/GL/)

find_library(GLEW_LIB NAMES glew)
find_library(GL_LIB NAMES GL)

target_link_libraries("${executable_name}_moto" glfw)
target_link_libraries("${executable_name}_moto" ${GLEW_LIB})
target_link_libraries("${executable_name}_moto" ${GL_LIB})
target_link_libraries("${executable_name}_monkey" glfw)
target_link_libraries("${executable_name}_monkey" ${GLEW_LIB})
target_link_libraries("${executable_name}_monkey" ${GL_LIB})
target_link_libraries("${executable_name}_catamarano" glfw)
target_link_libraries("${executable_name}_catamarano" ${GLEW_LIB})
target_link_libraries("${executable_name}_catamarano" ${GL_LIB})
target_link_libraries("${executable_name}_sailingboat" glfw)
target_link_libraries("${executable_name}_sailingboat" ${GLEW_LIB})
target_link_libraries("${executable_name}_sailingboat" ${GL_LIB})

configure_file("./Monkey.obj" "${PROJECT_BINARY_DIR}/Executables/${executable_name}/Monkey.obj" COPYONLY)
configure_file("./Moto.obj" "${PROJECT_BINARY_DIR}/Executables/${executable_name}/Moto.obj" COPYONLY)
configure_file("./Catamarano.obj" "${PROJECT_BINARY_DIR}/Executables/${executable_name}/Catamarano.obj" COPYONLY)
configure_file("./Proper_Sailing_Boat.obj" "${PROJECT_BINARY_DIR}/Executables/${executable_name}/Proper_Sailing_Boat.obj" COPYONLY)
configure_file("./vertShader.glsl" "${PROJECT_BINARY_DIR}/Executables/${executable_name}/vertShader.glsl" COPYONLY)
configure_file("./fragShader.glsl" "${PROJECT_BINARY_DIR}/Executables/${executable_name}/fragShader.glsl" COPYONLY)
set(EXECUTABLE_OUTPUT_PATH "${PROJECT_BINARY_DIR}/Executables/${executable_name}")