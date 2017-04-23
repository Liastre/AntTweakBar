#===================================
#========== LIBRARY NAME ===========
#===================================
set(CMAKE_DEBUG_POSTFIX d)

#===================================
#======== LIBRARY SOURCES ==========
#===================================
file(GLOB library_sources
    AntTweakBar.rc
    TwColors.cpp
    TwFonts.cpp
    TwOpenGL.cpp
    TwOpenGLCore.cpp
    TwBar.cpp
    TwMgr.cpp
    LoadOGL.cpp
    LoadOGLCore.cpp
)
if(ANTTWEAKBAR_GLFW3)
    list(APPEND library_sources TwEventGLFW.cpp)
endif()
if(ANTTWEAKBAR_FREEGLUT)
    list(APPEND library_sources TwEventGLUT.cpp)
endif()
if(ANTTWEAKBAR_SDL2)
    list(APPEND library_sources TwEventSDL.cpp)
endif()
if(ANTTWEAKBAR_SFML2)
    list(APPEND library_sources TwEventSFML.cpp)
endif()

#===================================
#============== BUILD ==============
#===================================
add_library (${ANTTWEAKBAR_LIBRARY} SHARED ${library_sources})

if(ANTTWEAKBAR_GLFW3)
    if(NOT ${GLFW3_FOUND})
        add_dependencies(${ANTTWEAKBAR_LIBRARY} ${GLFW3_NAME})
    endif()
    target_link_libraries(${ANTTWEAKBAR_LIBRARY} ${OPENGL_LIBRARIES} ${GLFW3_LIBRARIES})
endif(ANTTWEAKBAR_GLFW3)

if(ANTTWEAKBAR_FREEGLUT)
    if(NOT ${FREEGLUT_FOUND})
        add_dependencies(${ANTTWEAKBAR_LIBRARY} ${FREEGLUT_NAME})
    endif()
    target_link_libraries(${ANTTWEAKBAR_LIBRARY} ${OPENGL_LIBRARIES} ${FREEGLUT_LIBRARIES})
endif(ANTTWEAKBAR_FREEGLUT)

if(ANTTWEAKBAR_SDL2)
    if(NOT ${SDL2_FOUND})
        add_dependencies(${ANTTWEAKBAR_LIBRARY} ${SDL2_NAME})
    endif()
    target_link_libraries(${ANTTWEAKBAR_LIBRARY} ${OPENGL_LIBRARIES} ${SDL2_LIBRARIES})
endif(ANTTWEAKBAR_SDL2)

if(ANTTWEAKBAR_SFML2)
    if(NOT ${SFML_FOUND})
        add_dependencies(${ANTTWEAKBAR_LIBRARY} ${SFML_NAME})
    endif()
    target_compile_definitions(${ANTTWEAKBAR_LIBRARY} INTERFACE ${SFML_DEFINITIONS})
    target_link_libraries(${ANTTWEAKBAR_LIBRARY} ${SFML_LIBRARIES} ${SFML_DEPENDENCIES} glu32)
endif(ANTTWEAKBAR_SFML2)