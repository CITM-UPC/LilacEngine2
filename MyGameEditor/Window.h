#ifndef __WINDOW_H__
#define __WINDOW_H__
#pragma once

#include "Globals.h"
#include "Module.h"

#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 720

class Window : public Module
{
public:
    Window(Application* app);
    virtual ~Window();

    bool Awake();
    bool Start();
    bool CleanUp();

    static SDL_Window* initSDLWindowWithOpenGL();
    static SDL_GLContext createSdlGlContext(SDL_Window* window);
    static void initOpenGL();

public:
    SDL_Window* window;
    SDL_GLContext glContext;
};

#endif // !__WINDOW_H__