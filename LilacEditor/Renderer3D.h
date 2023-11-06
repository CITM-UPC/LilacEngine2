#ifndef __RENDERER_3D__
#define __RENDERER_3D__
#pragma once

#include "Module.h"

class EngineCore;

class Renderer3D : public Module
{
public:
    Renderer3D(Application* app);

    virtual ~Renderer3D();

    bool Awake();
    bool Start();

    bool PreUpdate();
    bool Update(double dt);
    bool PostUpdate();
    bool CleanUp();

    //void OnResize(int width, int height);
    void SetVsync(bool vsync);

private:
    double dtSum = 0;
};

#endif // !__RENDERER_3D__