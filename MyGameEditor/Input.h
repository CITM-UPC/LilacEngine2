#ifndef __INPUT_H__
#define __INPUT_H__
#pragma once

#include "Module.h"

class Input : public Module
{
public:
    Input(Application* app);
    virtual ~Input();

    bool Awake();
    bool PreUpdate();

    bool processSDLEvents();
    //void drag
private:
    int mouse_x;
    int mouse_y;
    int mouse_z;
    int mouse_x_motion;
    int mouse_y_motion;
    char* dropped_filedir;
};

#endif // __INPUT_H__