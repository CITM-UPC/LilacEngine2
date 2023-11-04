#include "Globals.h"
#include "Log.h"
#include "Input.h"
#include "Application.h"
#include "UI.h"
#include "..\MyGameEngine\Camera.h"

#define MAX_KEYS 300

Input::Input(Application* app, bool start_enabled) : Module(app, start_enabled)
{
    keyboard = new KEY_STATE[MAX_KEYS];
    memset(keyboard, KEY_IDLE, sizeof(KEY_STATE) * MAX_KEYS);
    //memset(mouse_buttons, KEY_IDLE, sizeof(KEY_STATE) * MAX_MOUSE_BUTTONS);
}

Input::~Input()
{
    delete[] keyboard;
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

    const Uint8* keys = SDL_GetKeyboardState(NULL);

    for (int i = 0; i < MAX_KEYS; ++i)
    {
        if (keys[i] == 1)
        {
            if (keyboard[i] == KEY_IDLE)
                keyboard[i] = KEY_DOWN;
            else
                keyboard[i] = KEY_REPEAT;
        }
        else
        {
            if (keyboard[i] == KEY_REPEAT || keyboard[i] == KEY_DOWN)
                keyboard[i] = KEY_UP;
            else
                keyboard[i] = KEY_IDLE;
        }
    }

    Uint32 buttons = SDL_GetMouseState(&mouse_x, &mouse_y);

    mouse_x /= WINDOW_WIDTH;
    mouse_y /= WINDOW_HEIGHT;
    mouse_z = 0;

    for (int i = 0; i < 5; ++i)
    {
        if (buttons & SDL_BUTTON(i))
        {
            if (mouse_buttons[i] == KEY_IDLE)
                mouse_buttons[i] = KEY_DOWN;
            else
                mouse_buttons[i] = KEY_REPEAT;
        }
        else
        {
            if (mouse_buttons[i] == KEY_REPEAT || mouse_buttons[i] == KEY_DOWN)
                mouse_buttons[i] = KEY_UP;
            else
                mouse_buttons[i] = KEY_IDLE;
        }
    }

    mouse_x_motion = mouse_y_motion = 0;

    bool quit = false;
    static SDL_Event e;
    while (SDL_PollEvent(&e) != 0)
    {
        app->ui->HandleInput(&e);
        switch (e.type)
        {
        case SDL_DROPFILE:
            dropped_filedir = e.drop.file;
            LOG("%s was dropped\n", dropped_filedir);
            SDL_free(dropped_filedir);
            break;
        case SDL_MOUSEWHEEL:
            mouse_z = e.wheel.y;
            break;
        case SDL_MOUSEMOTION:
            mouse_x = e.motion.x / WINDOW_WIDTH;
            mouse_y = e.motion.y / WINDOW_HEIGHT;

            mouse_x_motion = e.motion.xrel / WINDOW_WIDTH;
            mouse_y_motion = e.motion.yrel / WINDOW_HEIGHT;
            break;

        case SDL_QUIT:
            quit = true;
            break;

        /*case SDL_WINDOWEVENT:
        {
            if (e.window.event == SDL_WINDOWEVENT_RESIZED)
                App->renderer->OnResize(e.window.data1, e.window.data2);
        }*/

        // Initialize mouse in ImGui
            ImGui_ImplSDL2_ProcessEvent(&e);
            if (e.type == SDL_QUIT)
                return UPDATE_STOP;
            if (e.type == SDL_WINDOWEVENT && e.window.event == SDL_WINDOWEVENT_CLOSE && e.window.windowID == SDL_GetWindowID(App->window->window))
                return UPDATE_STOP;
        }
    }
    if (quit == true || keyboard[SDL_SCANCODE_ESCAPE] == KEY_UP)
        return UPDATE_STOP;


    return UPDATE_CONTINUE;
}
 //Called before quitting
bool Input::CleanUp()
{

    LOG("Quitting SDL input event subsystem");
    SDL_QuitSubSystem(SDL_INIT_EVENTS);
    return true;
}