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

};

#endif // __INPUT_H__