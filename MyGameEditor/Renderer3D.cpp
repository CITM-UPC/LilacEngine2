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
    App->engine->Awake();

    return true;
}

bool Renderer3D::Start()
{
    App->engine->Start();

    App->engine->camera.fov = 65;
    App->engine->camera.aspect = static_cast<double>(WINDOW_WIDTH) / WINDOW_HEIGHT;
    App->engine->camera.zNear = 0.1;
    App->engine->camera.zFar = 1500;
    App->engine->camera.eye = vec3(0, 0, 250);
    App->engine->camera.center = vec3(0, 0, -100);
    App->engine->camera.up = vec3(0, 0, 1);

    return true;
}

bool Renderer3D::PreUpdate()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

    return true;
}

bool Renderer3D::Update(double dt)
{
    App->engine->Update(dt);

    // hekbas texting camera movement
    double radius = 950;

    dtSum += dt;
    double speed = 0.6 * dtSum;

    App->engine->camera.eye.x = sin(speed) * radius;
    App->engine->camera.eye.y = cos(speed) * radius;

    return true;
}

bool Renderer3D::PostUpdate()
{
    App->engine->Render(EngineCore::RenderModes::DEBUG);

    App->ui->RenderUI();

    SDL_GL_SwapWindow(app->window->window);

    return true;
}

bool Renderer3D::CleanUp()
{

    return true;
}