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

    // UI
    void SetTitle(const char* title);
    void SetWindowBrightness(float brightness);
    void SetResizable(bool resizable);
    void SetFullscreen(bool fullscreen);
    void SetBorderless(bool resizable);
    void SetFullDesktop(bool fullDesktop);
    void SetWidth();
    void SetHeight();
public:
    SDL_Window* window;
    SDL_GLContext context;
};

#endif // !__WINDOW_H__