#include "Globals.h"
#include "Log.h"
#include "Input.h"
#include "Application.h"
#include "UI.h"

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
        case SDL_QUIT: return false;
        case SDL_KEYDOWN:
            switch (event.key.keysym.sym) {
            case SDLK_ESCAPE: return false;
            }
            break;
        }
    }
    return true;
}