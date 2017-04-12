# Created by Vasily Lobaskin (Liastre).
# Redistribution and use of this file is allowed according to the terms of the MIT license.

#.rst:
# FindFREEGLUT
# -------
#
# Try to find the FREEGLUT library.
#
# This will define the following variables:
#
#   FREEGLUT_FOUND         - true if library found
#   FREEGLUT_INCLUDE_DIRS  - path to library headers
#   FREEGLUT_LIBRARIES     - path to library itself

#===================================
#========= SEARCH HEADERS ==========
#===================================
find_path(FREEGLUT_INCLUDE_DIR
    NAMES
        GL/freeglut.h
    PATHS
        $ENV{include}
        ${OPENGL_INCLUDE_DIR}
        /usr
        /usr/local
    PATH_SUFFIXES
        include
    )

#===================================
#======== SEARCH LIBRARIES =========
#===================================
find_library(FREEGLUT_LIBRARY
    NAMES
        freeglut_static
        freeglut
    PATHS
        $ENV{lib}
        /usr/lib
        /usr/local/lib
    PATH_SUFFIXES
        bin
    )

#===================================
#========== SET UP OUTPUT ==========
#===================================
include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(FREEGLUT
    REQUIRED_VARS
        FREEGLUT_LIBRARY
        FREEGLUT_INCLUDE_DIR
    )
mark_as_advanced(GLFW3_INCLUDE_DIR GLFW3_LIBRARY)

set(FREEGLUT_INCLUDE_DIRS ${FREEGLUT_INCLUDE_DIR})
set(FREEGLUT_LIBRARIES ${FREEGLUT_LIBRARY})