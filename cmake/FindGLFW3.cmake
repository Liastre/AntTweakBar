# Created by Vasily Lobaskin (Liastre).
# Redistribution and use of this file is allowed according to the terms of the MIT license.

#.rst:
# FindGLFW3
# -------
#
# Try to find the GLFW v.3 library.
#
# This will define the following variables:
#
#   GLFW3_FOUND         - true if library found
#   GLFW3_INCLUDE_DIRS  - path to library headers
#   GLFW3_LIBRARIES     - path to library itself

#===================================
#========= SEARCH HEADERS ==========
#===================================
# search for glfw3.h
find_path(GLFW3_INCLUDE_DIR
    NAMES
        GLFW/glfw3.h
    HINTS
        "${GLFW3_LOCATION}/include"
        "$ENV{GLFW3_LOCATION}/include"
    PATHS
        "$ENV{PROGRAMFILES}/GLFW"
        "${OPENGL_INCLUDE_DIR}"
        /usr/openwin/share
        /usr/openwin
        /usr/X11R6
        /usr/include/X11
        /opt/graphics/OpenGL
        /opt/graphics/OpenGL/contrib/libglfw
        /usr/local
        /usr/include/GL
        /usr
    PATH_SUFFIXES
        include
    DOC
        "GLFW headers"
    )

#===================================
#======== SEARCH LIBRARIES =========
#===================================
if(WIN32)
    # windows, mingw, cygwin
    find_library(GLFW3_LIBRARY
        NAMES
            glfw32
            glfw32s
            glfw
            glfw3
        HINTS
            "${GLFW3_LOCATION}/lib"
            "${GLFW3_LOCATION}/lib/x64"
            "${GLFW3_LOCATION}/lib-msvc110"
            "${GLFW3_LOCATION}/lib-vc2012"
            "$ENV{GLFW3_LOCATION}/lib"
            "$ENV{GLFW3_LOCATION}/lib/x64"
            "$ENV{GLFW3_LOCATION}/lib-msvc110"
            "$ENV{GLFW3_LOCATION}/lib-vc2012"
        PATHS
            "$ENV{PROGRAMFILES}/GLFW"
            "${OPENGL_LIBRARY_DIR}"
            /usr
            /usr/lib/w32api
            /usr/local
            /usr/X11R6
        PATH_SUFFIXES
            lib
        DOC
            "GLFW library"
        )
elseif()
    # (*)NIX
    find_library(GLFW3_LIBRARY
        NAMES
            glfw
            glfw3
        HINTS
            "${GLFW3_LOCATION}/lib"
            "$ENV{GLFW3_LOCATION}/lib"
            "${GLFW3_LOCATION}/lib/x11"
            "$ENV{GLFW3_LOCATION}/lib/x11"
            # OS X
            "${GLFW3_LOCATION}/lib/cocoa"
            "$ENV{GLFW3_LOCATION}/lib/cocoa"
        PATHS
            /usr
            /usr/local
            /usr/openwin
            /usr/X11R6
        PATH_SUFFIXES
            lib
            lib64
            lib/${CMAKE_LIBRARY_ARCHITECTURE}
            lib/${CMAKE_LIBRARY_ARCHITECTURE}
        DOC
            "The GLFW library"
        )
endif()

#===================================
#=========== FUNCTIONS =============
#===================================
# parse GLFW header
function(parseversion FILENAME VARNAME)
    set(PATTERN "^#define ${VARNAME}.*$")
    file(STRINGS "${GLFW3_INCLUDE_DIR}/${FILENAME}" TMP REGEX ${PATTERN})
    string(REGEX MATCHALL "[0-9]+" TMP ${TMP})
    set(${VARNAME} ${TMP} PARENT_SCOPE)
endfunction()

#===================================
#========== SET UP OUTPUT ==========
#===================================
if(GLFW3_INCLUDE_DIR AND GLFW3_LIBRARY)
    # get GLFW version from the lib headers
    if(EXISTS "${GLFW3_INCLUDE_DIR}/GLFW/glfw3.h")
        parseversion(GLFW/glfw3.h GLFW_VERSION_MAJOR)
        parseversion(GLFW/glfw3.h GLFW_VERSION_MINOR)
        parseversion(GLFW/glfw3.h GLFW_VERSION_REVISION)
    endif()

    if(${GLFW_VERSION_MAJOR} OR ${GLFW_VERSION_MINOR} OR ${GLFW_VERSION_REVISION})
        set(GLFW_VERSION "${GLFW_VERSION_MAJOR}.${GLFW_VERSION_MINOR}.${GLFW_VERSION_REVISION}")
        mark_as_advanced(GLFW_VERSION)
    endif()

    set(GLFW3_FOUND TRUE)
endif()

mark_as_advanced(GLFW3_INCLUDE_DIR GLFW3_LIBRARY)
set(GLFW3_INCLUDE_DIRS ${GLFW3_INCLUDE_DIR})
set(GLFW3_LIBRARIES ${GLFW3_LIBRARY})

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(GLFW3
    REQUIRED_VARS
        GLFW3_LIBRARIES
        GLFW3_INCLUDE_DIRS
    VERSION_VAR
        GLFW_VERSION
    )
