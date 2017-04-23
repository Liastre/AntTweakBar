#===================================
#============= SYSTEM ==============
#===================================
cmake_minimum_required(VERSION 3.0)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

#===================================
#============ COMPILER =============
#===================================
# MinGW
if(MINGW)
    SET(CXX_COVERAGE_COMPILE_FLAGS  "-static-libgcc -static-libstdc++")
    #SET(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} ${CXX_COVERAGE_COMPILE_FLAGS}")
endif()

#===================================
#============= PROJECT =============
#===================================
project(AntTweakBar CXX)
set(ANTTWEAKBAR_VERSION_MAJOR "1")
set(ANTTWEAKBAR_VERSION_MINOR "17")
set(ANTTWEAKBAR_VERSION_PATCH "0")
set(ANTTWEAKBAR_VERSION_EXTRA "")
set(ANTTWEAKBAR_LIBRARY ${PROJECT_NAME}${ANTTWEAKBAR_VERSION_MAJOR})

#===================================
#============= OPTIONS =============
#===================================
# build
option(ANTTWEAKBAR_SHARED "Build shared library" ON)
option(ANTTWEAKBAR_BUILD_EXAMPLES "Build examples" ON)

# dependencies
option(ANTTWEAKBAR_OPENGL   "Use OpenGL as renderer"    ON)
option(ANTTWEAKBAR_GLFW3    "GLFW 3 library support"    OFF)
set   (ANTTWEAKBAR_GLFW3_INSTALL_PATH CACHE PATH "GLFW 3 user defined path to compiled library")
option(ANTTWEAKBAR_FREEGLUT     "GLUT library support"  OFF)
set   (ANTTWEAKBAR_FREEGLUT_INSTALL_PATH CACHE PATH "GLUT user defined path to compiled library")
option(ANTTWEAKBAR_SDL2     "SDL 2 library support"     OFF)
set   (ANTTWEAKBAR_SDL2_INSTALL_PATH CACHE PATH "SDL 2 user defined path to compiled library")
option(ANTTWEAKBAR_SFML2    "SFML 2 library support"    ON)
set   (ANTTWEAKBAR_SFML2_INSTALL_PATH CACHE PATH "SFML 2 user defined path to compiled library")

#===================================
#============= OUTPUT ==============
#===================================
set(AntTweakBar_build_output_dir        ${CMAKE_BINARY_DIR})
set(AntTweakBar_binary_output_dir       ${CMAKE_BINARY_DIR}/binary)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY      ${AntTweakBar_binary_output_dir})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY      ${AntTweakBar_binary_output_dir})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY      ${AntTweakBar_binary_output_dir})

#===================================
#========== DEPENDENCIES ===========
#===================================
# modules
include(${CMAKE_ROOT}/Modules/ExternalProject.cmake)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

# renderer should be choisen
if(NOT( ANTTWEAKBAR_OPENGL OR
        ANTTWEAKBAR_USE_VULKAN))
    message(SEND_ERROR "You forgot to choose renderer!")
endif()

add_subdirectory("${CMAKE_CURRENT_LIST_DIR}/thirdparty")
include_directories(${thirdparty_includes})

#===================================
#============= BUILD ===============
#===================================
include_directories(include)
include_directories(${AntTweakBar_binary_dir})
add_subdirectory(src)
if(ANTTWEAKBAR_BUILD_EXAMPLES)
    add_subdirectory(examples)
endif()
if(ANTTWEAKBAR_SHARED)
    set(BUILD_SHARED_LIBS ON)
endif()