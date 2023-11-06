#include "Globals.h"
#include "Log.h"
#include "Input.h"
#include "Application.h"
#include "UI.h"
#include "..\MyGameEngine\Camera.h"

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
            LOG("%s was dropped\n", dropped_filedir.c_str());
   
            // Manage whether if the file extension is fine and if it has been already dropped
            manageFileSystem(dropped_filedir);
            break;
        case SDL_MOUSEWHEEL:
            mouse_z = event.wheel.y;
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
        ///* MOUSE CAMERA MOVEMENT */
        //// Compute mouse input displacement
        //float mouseSensitivity = 10.0f * dt;
        //int deltaX = GetMouseXMotion();
        //int deltaY = -GetMouseYMotion();
        //
        //app->engine->camera.yaw += deltaX * mouseSensitivity;
        //app->engine->camera.pitch += deltaY * mouseSensitivity;
        //
        //// Limiting Camera Pitch to prevent flipping
        //if (app->engine->camera.pitch > 89.0f)
        //    app->engine->camera.pitch = 89.0f;
        //if (app->engine->camera.pitch < -89.0f)
        //    app->engine->camera.pitch = -89.0f;

        if (GetKey(SDL_SCANCODE_W) == KEY_REPEAT)
            app->engine->camera.eye += app->engine->camera.center * speed;
        if (GetKey(SDL_SCANCODE_S) == KEY_REPEAT)
            app->engine->camera.eye -= app->engine->camera.center * speed;
        if (GetKey(SDL_SCANCODE_A) == KEY_REPEAT)
            app->engine->camera.eye -= app->engine->camera.cameraRight * speed;
        if (GetKey(SDL_SCANCODE_D) == KEY_REPEAT)
            app->engine->camera.eye += app->engine->camera.cameraRight * speed;
    }

    ////Zooming Camera Input
    //app->engine->camera.eye += GetMouseZ();
    ///*if (app->engine->camera.fov < 1.0f)
    //    app->engine->camera.fov = 1.0f;
    //if (app->engine->camera.fov > 115.0f)
    //    app->engine->camera.fov = 115.0f;*/
    //
    //    //Orbit Object with Alt_Left + Left Click
    if (GetKey(SDL_SCANCODE_LALT) == KEY_REPEAT && GetMouseButton(SDL_BUTTON_LEFT) == KEY_DOWN)
    {
        float mouseSensitivity = 10.0f * dt;
        int deltaX = GetMouseXMotion();
        int deltaY = -GetMouseYMotion();
        float radius = 10.0f;
        double dtSum = 0;
        dtSum += dt;
        speed = 0.6 * dtSum;
        app->engine->camera.eye.x = sin(speed) * radius;
        app->engine->camera.eye.z = cos(speed) * radius;
    }

    app->engine->camera.cameraUpdate();
}

void Input::manageFileSystem(std::string dropped_filedir) {
    // Extract the file name from the dropped_filedir
    filesystem::path filePath(dropped_filedir);
    std::string fileName = filePath.filename().string();

    // Specify the directory where you want to copy the file
    std::filesystem::path destinationDirectory = "Assets";

    if (fileName.ends_with(".fbx") || fileName.ends_with(".png") || fileName.ends_with(".dds")) {
        //Combine the destination directory and the file name to get the full destination path
        std::filesystem::path destinationPath = destinationDirectory / fileName;
        
        // Check if the filealready exists
        std::error_code ec;
        std::filesystem::copy(filePath, destinationPath, ec);
        
        if (!ec) {
            if (dropped_filedir.ends_with(".fbx")) {
                LOG("New mesh has been successfully copied: %s\n", dropped_filedir.c_str());
            }
            else if (dropped_filedir.ends_with(".png") || dropped_filedir.ends_with(".dds")) {
                LOG("New texture has been successfully copied: %s\n", dropped_filedir.c_str());

                // here should be applied to put the texture in the selected GameObject 
            }
        }
        else {
            LOG("Error copying file: %s\n", ec.message().c_str());
        }
    }
    else {
        LOG("Unsupported file format: %s\n", dropped_filedir.c_str());
    }
}