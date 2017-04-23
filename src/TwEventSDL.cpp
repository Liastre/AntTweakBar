//  ---------------------------------------------------------------------------
//
//  @file       TwEventSDL.c
//  @brief      Helper: 
//              translate and re-send mouse and keyboard events 
//              from SDL event loop to AntTweakBar
//  
//  @author     Philippe Decaudin
//  @license    This file is part of the AntTweakBar library.
//              For conditions of distribution and use, see License.txt
//
//  note:       AntTweakBar.dll does not need to link with SDL, 
//              it just needs some definitions for its helper functions.
//
//  ---------------------------------------------------------------------------

#define ANTTWEAKBAR_SDL2
#include <AntTweakBar.hpp>


// TwEventSDL returns zero if msg has not been handled,
// and a non-zero value if it has been handled by the AntTweakBar library.
TW_EXPORT_API int TwEventSDL2(const void *sdlEvent)
{
    int handled = 0;
    static int s_KeyMod = 0;
    const SDL_Event *event = (const SDL_Event *)sdlEvent;

    if( event==NULL )
        return 0;

    switch( event->type )
    {
        case SDL_TEXTINPUT:
            if (event->text.text[0]!=0 && event->text.text[1]==0) {
                if (s_KeyMod & TW_KMOD_CTRL && event->text.text[0]<32)
                    handled = TwKeyPressed(event->text.text[0]+'a'-1, s_KeyMod);
                else {
                    if (s_KeyMod & KMOD_RALT)
                        s_KeyMod &= ~KMOD_CTRL;
                    handled = TwKeyPressed(event->text.text[0], s_KeyMod);
                }
            }
            s_KeyMod = 0;
            break;
        case SDL_KEYDOWN:
        {
            int key = 0;
            switch (event->key.keysym.sym) {
            case SDLK_BACKSPACE:
                key = TW_KEY_BACKSPACE;
                break;
            case SDLK_ESCAPE:
                key = TW_KEY_ESCAPE;
                break;
            case SDLK_UP:
                key = TW_KEY_UP;
                break;
            case SDLK_DOWN:
                key = TW_KEY_DOWN;
                break;
            case SDLK_RIGHT:
                key = TW_KEY_RIGHT;
                break;
            case SDLK_LEFT:
                key = TW_KEY_LEFT;
                break;
            case SDLK_INSERT:
                key = TW_KEY_INSERT;
                break;
            case SDLK_HOME:
                key = TW_KEY_HOME;
                break;
            case SDLK_END:
                key = TW_KEY_END;
                break;
            case SDLK_PAGEUP:
                key = TW_KEY_PAGE_UP;
                break;
            case SDLK_PAGEDOWN:
                key = TW_KEY_PAGE_DOWN;
                break;
            default:
                if (event->key.keysym.sym>=SDLK_F1 && event->key.keysym.sym<=SDLK_F12)
                    key = event->key.keysym.sym+TW_KEY_F1-SDLK_F1;
            }
            if (key!=0)
                handled = TwKeyPressed(key, event->key.keysym.mod);

            else if (event->key.keysym.mod & TW_KMOD_ALT)
                handled = TwKeyPressed(event->key.keysym.sym & 0xFF, event->key.keysym.mod);
            else
                s_KeyMod = event->key.keysym.mod;
            break;
        }
        case SDL_KEYUP:
            s_KeyMod = 0;
            break;
        case SDL_MOUSEMOTION:
            handled = TwMouseMotion(event->motion.x, event->motion.y);
            break;
        case SDL_MOUSEBUTTONUP:
        case SDL_MOUSEBUTTONDOWN:
            handled = TwMouseButton((event->type==SDL_MOUSEBUTTONUP)?TW_MOUSE_RELEASED:TW_MOUSE_PRESSED, (TwMouseButtonID)event->button.button);
            break;
        case SDL_MOUSEWHEEL:
            handled = TwMouseWheel(event->wheel.y);
            break;
        case SDL_WINDOWEVENT_RESIZED:
            // tell the new size to TweakBar
            TwWindowSize(event->window.data1, event->window.data1);
            // do not set 'handled', SDL_VIDEORESIZE may be also processed by the calling application
            break;
    }

    return handled;
}
