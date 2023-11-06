#ifndef __INPUT_H__
#define __INPUT_H__
#pragma once

#include "Module.h"
#include "..\LilacEngine\Camera.h"
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
    //bool CleanUp();
    bool processSDLEvents();

    // Mouse
    KEY_STATE GetMouseButton(int id) 
    {
        return mouse_buttons[id - 1];
    }

    KEY_STATE GetKey(int id) 
    {
        return keyboard[id];
    }

    vec2 GetMouseMotion() {
        return vec2(mouse_x, mouse_y);
    }

    int GetMouseXMotion() 
    {
        return mouse_x;
    }

    int GetMouseYMotion() 
    {
        return mouse_y;
    }

    int GetMouseWheelScroll() {
        return mouse_WheelScroll;
    }

    // Camera
    void InputCamera(double dt);

    // File System
    void manageFileSystem(std::string dropped_filedir);

private:
    // Mouse
    int mouse_x;
    int mouse_y;
    int	mouse_WheelScroll;
    KEY_STATE mouse_buttons[MAX_MOUSE_BUTTONS];
    KEY_STATE* keyboard; 
    
    // File System
    std::string dropped_filedir;
};

#endif // __INPUT_H__