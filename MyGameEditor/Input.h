#ifndef __INPUT_H__
#define __INPUT_H__
#pragma once

#include "Module.h"

#define MAX_MOUSE_BUTTONS 5

enum KEY_STATE
{
    KEY_IDLE = 0,
    KEY_DOWN,
    KEY_REPEAT,
    KEY_UP
};

class Input : public Module
{
public:
    Input(Application* app);
    virtual ~Input();

    bool Awake();
    bool PreUpdate();
    bool Update(double dt);

    bool processSDLEvents();

    // Camera

    KEY_STATE GetMouseButton(int id) 
    {
        return mouse_buttons[id];
    }

    KEY_STATE GetKey(int id) 
    {
        return keyboard[id];
    }

    int GetMouseXMotion() 
    {
        return mouse_x_motion;
    }

    int GetMouseYMotion() 
    {
        return mouse_y_motion;
    }

    void InputCamera(double dt);

private:
    int mouse_x;
    int mouse_y;
    int mouse_z;
    int mouse_x_motion;
    int mouse_y_motion;
    std::string dropped_filedir;
    KEY_STATE mouse_buttons[MAX_MOUSE_BUTTONS];
    KEY_STATE* keyboard;
};

#endif // __INPUT_H__