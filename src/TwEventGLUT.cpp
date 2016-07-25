//  ---------------------------------------------------------------------------
//
//  @file       TwEventGLUT.c
//  @brief      Helper: 
//              translate and re-send mouse and keyboard events 
//              from GLUT event callbacks to AntTweakBar
//  
//  @author     Philippe Decaudin
//  @date       2006/05/10
//  @license    This file is part of the AntTweakBar library.
//              For conditions of distribution and use, see License.txt
//
//  ---------------------------------------------------------------------------

#ifdef _MSC_VER
#   pragma warning(disable: 4505)   // glut generates 'unreferenced function' warnings
#   pragma warning(disable: 4100)   // unreferenced parameter
#endif // _MSC_VER

#define ANTTWEAKBAR_USE_GLUT
#include <AntTweakBar.hpp>

int TwEventMouseButtonGLUT(int button, int state, int mouseX, int mouseY)
{
    TwMouseAction action = (state==GLUT_DOWN) ? TW_MOUSE_PRESSED : TW_MOUSE_RELEASED;
    TwMouseMotion(mouseX, mouseY);

    switch( button )
    {
    case GLUT_LEFT_BUTTON:
        return TwMouseButton(action, TW_MOUSE_LEFT);
    case GLUT_RIGHT_BUTTON:
        return TwMouseButton(action, TW_MOUSE_RIGHT);
    case GLUT_MIDDLE_BUTTON:
        return TwMouseButton(action, TW_MOUSE_MIDDLE);
    case 3:
        if (state==GLUT_UP) {
            TwMouseWheel(1);
        }
        break;
    case 4:
        if (state==GLUT_UP) {
            TwMouseWheel(-1);
        }
        break;
    default:
        break;
    }

    return 0;
}

int TwEventMouseMotionGLUT(int mouseX, int mouseY)
{
    return TwMouseMotion(mouseX, mouseY);
}

// GLUT does not send modifiers state to 'Key' and 'Special' callbacks,
// and we cannot call glutGetModifiers here because we do not want to link
// AntTweakBar with glut, so the following function is used to store
// a pointer to the glutGetModifiers function of the calling application.
// It must be called at initialisation of the application.
int (*g_GLUTGetModifiers)(void) = NULL;
// Required because the GLUT key event functions do not report key modifiers states.
TW_EXPORT_API int twSetModifiersFuncPointerGLUT(int (*glutGetModifiersFunc)(void))
{
    g_GLUTGetModifiers = glutGetModifiersFunc;
    return (g_GLUTGetModifiers==NULL) ? 0 : 1;
}

int TwEventKeyboardGLUT(unsigned char glutKey, int mouseX, int mouseY)
{
    int kmod = 0;

    if( g_GLUTGetModifiers!=NULL )
    {
        int glutMod = g_GLUTGetModifiers();

        if( glutMod&GLUT_ACTIVE_SHIFT )
            kmod |= TW_KMOD_SHIFT;
        if( glutMod&GLUT_ACTIVE_CTRL )
            kmod |= TW_KMOD_CTRL;
        if( glutMod&GLUT_ACTIVE_ALT )
            kmod |= TW_KMOD_ALT;
    }

    if( (kmod&TW_KMOD_CTRL) && (glutKey>0 && glutKey<27) )  // CTRL special case
        glutKey += 'a'-1;

    return TwKeyPressed((int)glutKey, kmod);
}

int TwEventSpecialGLUT(int key, int mouseX, int mouseY)
{
    int k = 0, kmod = 0;

    if( g_GLUTGetModifiers!=NULL )
    {
        int glutMod = g_GLUTGetModifiers();

        if( glutMod&GLUT_ACTIVE_SHIFT )
            kmod |= TW_KMOD_SHIFT;
        if( glutMod&GLUT_ACTIVE_CTRL )
            kmod |= TW_KMOD_CTRL;
        if( glutMod&GLUT_ACTIVE_ALT )
            kmod |= TW_KMOD_ALT;
    }

    if( key>=GLUT_KEY_F1 && key<=GLUT_KEY_F12 )
        k = TW_KEY_F1 + (key-GLUT_KEY_F1);
    else
    {
        switch( key )
        {
        case GLUT_KEY_LEFT:
            k = TW_KEY_LEFT;
            break;
        case GLUT_KEY_UP:
            k = TW_KEY_UP;
            break;
        case GLUT_KEY_RIGHT:
            k = TW_KEY_RIGHT;
            break;
        case GLUT_KEY_DOWN:
            k = TW_KEY_DOWN;
            break;
        case GLUT_KEY_PAGE_UP:
            k = TW_KEY_PAGE_UP;
            break;
        case GLUT_KEY_PAGE_DOWN:
            k = TW_KEY_PAGE_DOWN;
            break;
        case GLUT_KEY_HOME:
            k = TW_KEY_HOME;
            break;
        case GLUT_KEY_END:
            k = TW_KEY_END;
            break;
        case GLUT_KEY_INSERT:
            k = TW_KEY_INSERT;
            break;
        }
    }

    if( k>0 && k<TW_KEY_LAST )
        return TwKeyPressed(k, kmod);
    else
        return 0;
}

// Callbacks that returning error code:
TW_EXPORT_API int twCursorPosCallbackGLUT_d(int posX, int posY) {
    return TwEventMouseMotionGLUT(posX, posY);
}
// directly redirect GLUT mouse button and wheel events to AntTweakBar
TW_EXPORT_API int twMouseButtonCallbackGLUT_d(int button, int state, int posX, int posY) {
    return TwEventMouseButtonGLUT(button, state, posX, posY);
}
// Directly redirect GLUT keyboard keys events for the current window to AntTweakBar
TW_EXPORT_API int twKeyCallbackGLUT_d(unsigned char key, int mouseX, int mouseY) {
    return TwEventKeyboardGLUT(key, mouseX, mouseY);
}
// Directly redirect GLUT special keyboard keys events to AntTweakBar
TW_EXPORT_API int twSpecialKeyCallbackGLUT_d(int key, int mouseX, int mouseY) {
    return TwEventSpecialGLUT(key, mouseX, mouseY);
}

// Callbacks without returning error code:
// directly redirect GLUT mouse position events to AntTweakBar
TW_EXPORT_API void twCursorPosCallbackGLUT (int posX, int posY) {
    TwEventMouseMotionGLUT(posX, posY);
}
// directly redirect GLUT mouse button and wheel events to AntTweakBar
TW_EXPORT_API void twMouseButtonCallbackGLUT (int button, int state, int posX, int posY) {
    TwEventMouseButtonGLUT(button, state, posX, posY);
}
// Directly redirect GLUT keyboard keys events for the current window to AntTweakBar
TW_EXPORT_API void twKeyCallbackGLUT(unsigned char key, int mouseX, int mouseY) {
    TwEventKeyboardGLUT(key, mouseX, mouseY);
}
// Directly redirect GLUT special keyboard keys events to AntTweakBar
TW_EXPORT_API void twSpecialKeyCallbackGLUT(int key, int mouseX, int mouseY) {
    TwEventSpecialGLUT(key, mouseX, mouseY);
}
