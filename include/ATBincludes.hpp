// =============== DESCRIPTION ===============
// Include this header for easy third party
// headers management. Use next defines:
// ANTTWEAKBAR_GLFW3
// ANTTWEAKBAR_SFML2
// ANTTWEAKBAR_FREEGLUT
// ANTTWEAKBAR_SDL2
// ===========================================

#ifndef ANTTWEAKBAR_ATBINCLUDES_HPP
#define ANTTWEAKBAR_ATBINCLUDES_HPP

#include "ATBprecomp.hpp"


#if defined(ANTTWEAKBAR_OPENGL)
// TODO: if OSx

// TODO: if anything else
#   include <GL/gl.h>
#   include <GL/glu.h>
#endif

#ifdef ANTTWEAKBAR_GLFW3
#   include <GLFW/glfw3.h>
#endif
#ifdef ANTTWEAKBAR_FREEGLUT
#   define GLUT_DISABLE_ATEXIT_HACK
#   include <GL/glut.h>
#endif
#ifdef ANTTWEAKBAR_SDL2
#   include <SDL2/SDL.h>
#endif
#ifdef ANTTWEAKBAR_SFML2
#   include <SFML/Graphics.hpp>
#endif

#endif //ANTTWEAKBAR_ATBINCLUDES_HPP
