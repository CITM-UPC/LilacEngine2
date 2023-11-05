#include "Globals.h"
#include "Log.h"
#include "Input.h"
#include "Application.h"
#include "UI.h"
#include <glm/ext/matrix_transform.hpp>
#include "../MyGameEngine/Camera.h"
#include "../MyGameEngine/glmath.h"
#include "../MyGameEngine/types.h"

#define MAX_KEYS 300
#define SCREEN_SIZE 1

Input::Input(Application* app) : Module(app)
{
    keyboard = new KEY_STATE[MAX_KEYS];
    memset(keyboard, KEY_IDLE, sizeof(KEY_STATE) * MAX_KEYS);
    memset(mouse_buttons, KEY_IDLE, sizeof(KEY_STATE) * MAX_MOUSE_BUTTONS);
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

bool Input::Update(double dt)
{   
    bool ret = true;

    InputCamera(dt);

    return ret;
}

bool Input::processSDLEvents()
{
    // Initialize
    SDL_PumpEvents();
    const Uint8* keys = SDL_GetKeyboardState(NULL);
    static SDL_Event event;

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

    mouse_x /= SCREEN_SIZE;
    mouse_y /= SCREEN_SIZE;
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
            mouse_z = event.wheel.y;
            break;
        case SDL_MOUSEMOTION:
            mouse_x = event.motion.x / SCREEN_SIZE;
            mouse_y = event.motion.y / SCREEN_SIZE;

            mouse_x_motion = event.motion.xrel / SCREEN_SIZE;
            mouse_y_motion = event.motion.yrel / SCREEN_SIZE;
            break;

        case SDL_KEYDOWN:
            switch (event.key.keysym.sym) {
            case SDLK_ESCAPE: return false;
            }
            break;
        case SDL_QUIT: return false;
        }
    }

    return true;
}

void Input::InputCamera(double dt) {
    // CAMERA MOVEMENT
    // - “WASD” fps-like movement and free look around must be enabled
    // - Mouse wheel should zoom in and out
    // - Alt+Left click should orbit the object
    // - F should focus the camera around the geometry
    // - Holding SHIFT duplicates movement speed

    double speed = 10 * dt;
    if (GetKey(SDL_SCANCODE_LSHIFT) == KEY_REPEAT || GetKey(SDL_SCANCODE_RSHIFT) == KEY_REPEAT)
        speed = 45 * dt;

    if (GetMouseButton(SDL_BUTTON_RIGHT) == KEY_REPEAT)
    {
        //if (GetKey(SDL_SCANCODE_W) == KEY_REPEAT)
        //    app->engine->camera.eye += app->engine->camera.center * speed;
        //if (GetKey(SDL_SCANCODE_S) == KEY_REPEAT)
        //    app->engine->camera.eye -= app->engine->camera.center * speed;
        //if (GetKey(SDL_SCANCODE_A) == KEY_REPEAT)
        //    app->engine->camera.eye -= app->engine->camera.cameraRight * speed;
        //if (GetKey(SDL_SCANCODE_D) == KEY_REPEAT)
        //    app->engine->camera.eye += app->engine->camera.cameraRight * speed;
    }

    ////Zooming Camera Input
    //app->engine->camera.eye += GetMouseZ();
    ///*if (app->engine->camera.fov < 1.0f)
    //    app->engine->camera.fov = 1.0f;
    //if (app->engine->camera.fov > 115.0f)
    //    app->engine->camera.fov = 115.0f;*/
    //
    
    //Orbit Object with Alt_Left + Left Click
    if (GetKey(SDL_SCANCODE_LALT) == KEY_REPEAT && GetMouseButton(SDL_BUTTON_LEFT) == KEY_REPEAT)
    {
        int dx = -App->input->GetMouseXMotion();
        int dy = -App->input->GetMouseYMotion();

        float Sensitivity = 0.25f;

        app->engine->camera.Position -= app->engine->camera.Reference;

        if (dx != 0)
        {
            float DeltaX = (float)dx * Sensitivity;

            app->engine->camera.X = app->engine->camera.Rotate(app->engine->camera.X, DeltaX, vec3(0.0f, 1.0f, 0.0f));
            app->engine->camera.Y = app->engine->camera.Rotate(app->engine->camera.Y, DeltaX, vec3(0.0f, 1.0f, 0.0f));
            app->engine->camera.Z = app->engine->camera.Rotate(app->engine->camera.Z, DeltaX, vec3(0.0f, 1.0f, 0.0f));
        }
        glm:
        if (dy != 0)
        {
            float DeltaY = (float)dy * Sensitivity;

            app->engine->camera.Y = rotate(app->engine->camera.Y, DeltaY, app->engine->camera.X);
            app->engine->camera.Z = rotate(app->engine->camera.Z, DeltaY, app->engine->camera.X);

            if (app->engine->camera.Y.y < 0.0f)
            {
                app->engine->camera.Z = vec3d(0.0f, app->engine->camera.Z.y > 0.0f ? 1.0f : -1.0f, 0.0f);
                app->engine->camera.Y = cross(app->engine->camera.Z, app->engine->camera.X);
            }
        }

        app->engine->camera.Position = app->engine->camera.Reference + app->engine->camera.Z * length(app->engine->camera.Position);
    }

    app->engine->camera.CalculateViewMatrix();
}