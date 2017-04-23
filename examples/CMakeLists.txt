#===================================
#============= BUILD ===============
#===================================
# GLFW examples
if(ANTTWEAKBAR_GLFW3)
    # TwCubeGLFW3
    add_executable (TwCubeGLFW3 TwCubeGLFW3.cpp)
    target_link_libraries (TwCubeGLFW3 ${ANTTWEAKBAR_LIBRARY})
    # TwLightsReflectionGLFW3
    add_executable (TwLightsReflectionGLFW3 TwLightsReflectionGLFW3.cpp)
    target_link_libraries (TwLightsReflectionGLFW3 ${ANTTWEAKBAR_LIBRARY})
endif()

# GLUT examples
if(ANTTWEAKBAR_FREEGLUT)
    # TwObjectViewerGLUT
    add_executable (TwObjectViewerGLUT TwObjectViewerGLUT.cpp)
    target_link_libraries (TwObjectViewerGLUT ${ANTTWEAKBAR_LIBRARY})
    # TwSplitScreenGLUT
    add_executable (TwSplitScreenGLUT TwSplitScreenGLUT.cpp)
    target_link_libraries (TwSplitScreenGLUT ${ANTTWEAKBAR_LIBRARY})
    # TwMultiDialogsGLUT
    add_executable (TwMultiDialogsGLUT TwMultiDialogsGLUT.cpp)
    target_link_libraries (TwMultiDialogsGLUT ${ANTTWEAKBAR_LIBRARY})
endif()

# SDL examples
if(ANTTWEAKBAR_SDL2)
    add_executable (TwColoredCubesSDL2 TwColoredCubesSDL2.cpp)
    target_link_libraries (TwColoredCubesSDL2 ${ANTTWEAKBAR_LIBRARY})
    add_executable (TwGLCoreSDL2 TwGLCoreSDL2.cpp)
    target_link_libraries (TwGLCoreSDL2 ${ANTTWEAKBAR_LIBRARY})
endif()

# SFML examples
if(ANTTWEAKBAR_SFML2)
    add_executable (TwParticlesSFML2 TwParticlesSFML2.cpp)
    target_link_libraries(TwParticlesSFML2 ${ANTTWEAKBAR_LIBRARY})
endif()
