# Install script for directory: /home/enrico/Documenti/Programmazione/OpenGlC++/src

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/usr/local")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Install shared libraries without execute permission?
if(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  set(CMAKE_INSTALL_SO_NO_EXE "0")
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

# Set default install directory permissions.
if(NOT DEFINED CMAKE_OBJDUMP)
  set(CMAKE_OBJDUMP "/usr/bin/objdump")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  include("/home/enrico/Documenti/Programmazione/OpenGlC++/build/01_FinestraColorata/cmake_install.cmake")
  include("/home/enrico/Documenti/Programmazione/OpenGlC++/build/02_DisegnoUnPunto/cmake_install.cmake")
  include("/home/enrico/Documenti/Programmazione/OpenGlC++/build/03_DisegnaUnPuntoColorato/cmake_install.cmake")
  include("/home/enrico/Documenti/Programmazione/OpenGlC++/build/04_ShaderLog/cmake_install.cmake")
  include("/home/enrico/Documenti/Programmazione/OpenGlC++/build/05_ReadShaderFromFile/cmake_install.cmake")
  include("/home/enrico/Documenti/Programmazione/OpenGlC++/build/06_DisegnareUnTriangolo/cmake_install.cmake")
  include("/home/enrico/Documenti/Programmazione/OpenGlC++/build/07_TriangoloAnimato/cmake_install.cmake")
  include("/home/enrico/Documenti/Programmazione/OpenGlC++/build/08_PuntoCheSiGonfia/cmake_install.cmake")
  include("/home/enrico/Documenti/Programmazione/OpenGlC++/build/09_TriangoloRotante/cmake_install.cmake")
  include("/home/enrico/Documenti/Programmazione/OpenGlC++/build/10_PrimoCubo/cmake_install.cmake")
  include("/home/enrico/Documenti/Programmazione/OpenGlC++/build/11_CuboRotante/cmake_install.cmake")
  include("/home/enrico/Documenti/Programmazione/OpenGlC++/build/12_CubiRotanti/cmake_install.cmake")
  include("/home/enrico/Documenti/Programmazione/OpenGlC++/build/13_IstancingCubiRotanti/cmake_install.cmake")
  include("/home/enrico/Documenti/Programmazione/OpenGlC++/build/15_CubeAndPyramid/cmake_install.cmake")
  include("/home/enrico/Documenti/Programmazione/OpenGlC++/build/16_CubicSolarSystem/cmake_install.cmake")
  include("/home/enrico/Documenti/Programmazione/OpenGlC++/build/17_OggettoRotante/cmake_install.cmake")
  include("/home/enrico/Documenti/Programmazione/OpenGlC++/build/18_RotazioneCamera/cmake_install.cmake")
  include("/home/enrico/Documenti/Programmazione/OpenGlC++/build/19_RotazioneCameraLookAt/cmake_install.cmake")
  include("/home/enrico/Documenti/Programmazione/OpenGlC++/build/20_19ConRewindowing/cmake_install.cmake")
  include("/home/enrico/Documenti/Programmazione/OpenGlC++/build/21_PulsingSphere/cmake_install.cmake")
  include("/home/enrico/Documenti/Programmazione/OpenGlC++/build/22_OpenBlenderObj/cmake_install.cmake")
  include("/home/enrico/Documenti/Programmazione/OpenGlC++/build/23_GourandLighting/cmake_install.cmake")

endif()

if(CMAKE_INSTALL_COMPONENT)
  set(CMAKE_INSTALL_MANIFEST "install_manifest_${CMAKE_INSTALL_COMPONENT}.txt")
else()
  set(CMAKE_INSTALL_MANIFEST "install_manifest.txt")
endif()

string(REPLACE ";" "\n" CMAKE_INSTALL_MANIFEST_CONTENT
       "${CMAKE_INSTALL_MANIFEST_FILES}")
file(WRITE "/home/enrico/Documenti/Programmazione/OpenGlC++/build/${CMAKE_INSTALL_MANIFEST}"
     "${CMAKE_INSTALL_MANIFEST_CONTENT}")
