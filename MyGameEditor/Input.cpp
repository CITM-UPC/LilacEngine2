#include "Globals.h"
#include "Log.h"
#include "Input.h"
#include "Application.h"
#include "UI.h"
#include "..\MyGameEngine\Camera.h"

Input::Input(Application* app) : Module(app)
{
}

Input::~Input()
{
}

bool Input::Awake()
{
    LOG("Init SDL input event system");
    bool ret = true;
    SDL_Init(0);

    if (SDL_InitSubSystem(SDL_INIT_EVENTS) < 0)
    {
        LOG("SDL_EVENTS could not initialize! SDL_Error: %s\n", SDL_GetError());
        ret = false;
    }

    return ret;
}

bool Input::PreUpdate()
{
    bool ret = true;

    ret = processSDLEvents();

    return ret;
}

bool Input::processSDLEvents()
{
    SDL_PumpEvents();

    static SDL_Event event;

    while (SDL_PollEvent(&event) != 0)
    {
        app->ui->HandleInput(&event);
        switch (event.type)
        {
        case SDL_DROPFILE:
            dropped_filedir = event.drop.file;
            LOG("%s was dropped\n", dropped_filedir);
            SDL_free(dropped_filedir);
            break;
        case SDL_MOUSEWHEEL:
            //mouse_z = event.wheel.y;
            break;
        case SDL_KEYDOWN:
            switch (event.key.keysym.sym) {
            case SDLK_ESCAPE: return false;
            case SDLK_w:
                break;
            case SDLK_a:
                break;
            case SDLK_s:
                break;
            case SDLK_d:
                break;
            case SDLK_f:
                break;
            case SDLK_LSHIFT:
                break;
            case SDLK_RSHIFT:
                break;
            }
            break;
        case SDL_QUIT: return false;
        }
    }
    return true;
}