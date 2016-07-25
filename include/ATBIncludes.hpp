// =============== DESCRIPTION ===============
// Include this header for easy third party
// headers management. Use next defines:
// ANTTWEAKBAR_USE_GLFW3
// ANTTWEAKBAR_USE_SFML2
// ANTTWEAKBAR_USE_GLUT
// ANTTWEAKBAR_USE_SDL2
// ===========================================

#ifndef ANTTWEAKBAR_ATBINCLUDES_HPP
#define ANTTWEAKBAR_ATBINCLUDES_HPP

#if defined(ANTTWEAKBAR_USE_OPENGL)
// OS specified includes start
#   if defined(_WIN32) || defined(_WIN64)
#       include <windows.h>
#   endif
//  OS specified includes end
#   include <GL/gl.h>
#   include <GL/glu.h>
#endif

#ifdef ANTTWEAKBAR_USE_GLFW3
#   include <GLFW/glfw3.h>
#endif
#ifdef ANTTWEAKBAR_USE_GLUT
#   define GLUT_DISABLE_ATEXIT_HACK
#   include <GL/glut.h>
#endif
#ifdef ANTTWEAKBAR_USE_SDL2
#   include <SDL.h>
#endif
#ifdef ANTTWEAKBAR_USE_SFML2
#   include <SFML/Graphics.hpp>
#endif

#endif //ANTTWEAKBAR_ATBINCLUDES_HPP
