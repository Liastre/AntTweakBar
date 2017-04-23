# Created by Vasily Lobaskin (Liastre).
# Redistribution and use of this file is allowed according to the terms of the MIT license.

#.rst:
# FindSDL2
# -------
#
# Try to find the SDL2 library.
#
# This will define the following variables:
#
#   SDL2_FOUND         - true if library found
#   SDL2_INCLUDE_DIRS  - path to library headers
#   SDL2_LIBRARIES     - path to library itself
#   SDL2_DEFINITIONS   - platform based compiler flags

#===================================
#========= SEARCH HEADERS ==========
#===================================
find_path(SDL2_INCLUDE_DIR
    NAMES
        SDL2/SDL.h
    HINTS
        "${SDL2_LOCATION}"
        "$ENV{SDL2_LOCATION}"
    PATHS
        $ENV{include}
        ~/Library/Frameworks
        /Library/Frameworks
        /usr/local
        /usr
    # Fink
        /sw
    # DarwinPorts
        /opt/local
    # Blastwave
        /opt/csw
        /opt
    PATH_SUFFIXES
        include
    )

#===================================
#======== SEARCH LIBRARIES =========
#===================================
set(SDL2_PATHS
    $ENV{include}
    ~/Library/Frameworks
    /Library/Frameworks
    /usr/local
    /usr
    # Fink
    /sw
    # DarwinPorts
    /opt/local
    # Blastwave
    /opt/csw
    /opt
    )

find_library(SDL2_LIBRARY
    NAMES
        SDL2
    HINTS
        "${SDL2_LOCATION}"
        "$ENV{SDL2_LOCATION}"
    PATHS
        ${SDL2_PATHS}
    PATH_SUFFIXES
        bin
        lib
        lib64
    )

find_library(SDL2MAIN_LIBRARY
    NAMES
        SDL2main
    HINTS
        "${SDL2_LOCATION}"
        "$ENV{SDL2_LOCATION}"
    PATHS
        ${SDL2_PATHS}
    PATH_SUFFIXES
        lib
        lib64
    )

#===================================
#========== DEPENDENCIES ===========
#===================================
# environment
if(MINGW)
    set(ENVIRONMENT_LIBRARIES ${ENVIRONMENT_LIBRARIES} mingw32)
endif()

# dependencies
if(WIN32)
    set(SDL2_DEFINITION
        winmm
        imm32
        version
        )
endif(WIN32)

#===================================
#========== SET UP OUTPUT ==========
#===================================
include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(SDL2
    REQUIRED_VARS
        SDL2_LIBRARY
        SDL2MAIN_LIBRARY
        SDL2_INCLUDE_DIR
    )
mark_as_advanced(SDL2_INCLUDE_DIR SDL2_LIBRARY)

if(SDL2_FOUND)
    set(SDL2_INCLUDE_DIRS ${SDL2_INCLUDE_DIR})
    set(SDL2_LIBRARIES ${ENVIRONMENT_LIBRARIES} ${SDL2MAIN_LIBRARY} ${SDL2_LIBRARY} ${SDL2_DEFINITION})
else()
    set(SDL2_LIBRARIES ${ENVIRONMENT_LIBRARIES})
    set(SDL2_DEFINITIONS ${SDL2_DEFINITION})
endif()
