#include "Application.h"
#include "Renderer3D.h"
#include "Globals.h"

Renderer3D::Renderer3D(Application* app) : Module(app) 
{

}

Renderer3D::~Renderer3D() 
{

}

bool Renderer3D::Awake()
{
    app->engine->Awake();
    
    return true;
}

bool Renderer3D::Start()
{
    app->engine->Start();

    app->engine->camera.fov = 65;
    app->engine->camera.aspect = static_cast<double>(WINDOW_WIDTH) / WINDOW_HEIGHT;
    app->engine->camera.zNear = 0.1;
    app->engine->camera.zFar = 1500;
    app->engine->camera.eye = vec3(0, 0, 250);
    app->engine->camera.center = vec3(0, 0, -100);
    app->engine->camera.up = vec3(0, 0, 1);

    return true;
}

bool Renderer3D::PreUpdate()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

    return true;
}

bool Renderer3D::Update(double dt)
{
    app->engine->Update(dt);

    // hekbas texting camera movement
    double radius = 950;

    dtSum += dt;
    double speed = 0.6 * dtSum;

    app->engine->camera.eye.x = sin(speed) * radius;
    app->engine->camera.eye.y = cos(speed) * radius;

    return true;
}

bool Renderer3D::PostUpdate()
{
    app->engine->Render(EngineCore::RenderModes::DEBUG);

    app->ui->RenderUI();

    SDL_GL_SwapWindow(app->window->window);

    return true;
}

bool Renderer3D::CleanUp()
{
    return true;
}

void Renderer3D::SetVsync(bool vsync) {
    //SDL_RenderSetVSync(renderer, vsync);
}