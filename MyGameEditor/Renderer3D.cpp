#include "Application.h"
#include "Renderer3D.h"
#include "Globals.h"
#include "Log.h"
#include "..\MyGameEngine\GraphicObject.h"
#include "..\MyGameEngine\Mesh.h"

Renderer3D::Renderer3D(Application* app) : Module(app) 
{

}

Renderer3D::~Renderer3D() 
{

}

bool Renderer3D::Awake()
{
    LOG("Init Renderer 3D");
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
    app->engine->camera.eye = vec3(5, 1.75, 5);
    app->engine->camera.center = vec3(0, 1, 0);
    app->engine->camera.up = vec3(0, 1, 0);

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
    LOG("Cleaning Renderer");

    return true;
}

void Renderer3D::SetVsync(bool vsync) {
    //SDL_RenderSetVSync(renderer, vsync);
}