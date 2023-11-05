#include "EngineCore.h"
#include <GL/glew.h>
#include <glm/ext/matrix_transform.hpp>
#include <IL/il.h>
#include "Mesh.h"
#include "GraphicObject.h"

EngineCore::EngineCore()
{

}

void EngineCore::Awake()
{

}

void EngineCore::Start()
{

}

void EngineCore::Update(double dt)
{

}

static void drawAxis()
{
    glLineWidth(4.0);
    glBegin(GL_LINES);

    // Red = X
    glColor3ub(255, 0, 0);
    glVertex3d(0, 0, 0);
    glVertex3d(1, 0, 0);

    // Y should be up!
    // Green = Y
    glColor3ub(0, 255, 0);
    glVertex3d(0, 0, 0);
    glVertex3d(0, 1, 0);

    // Blue = Z
    glColor3ub(0, 0, 255);
    glVertex3d(0, 0, 0);
    glVertex3d(0, 0, 1);
    glEnd();
}

static void drawGrid(int grid_size, int grid_step)
{
    glLineWidth(1.0);
    glColor3ub(128, 128, 128);

    glBegin(GL_LINES);
    for (int i = -grid_size; i <= grid_size; i += grid_step) {
        //XY plane
        glVertex2i(i, -grid_size);
        glVertex2i(i, grid_size);
        glVertex2i(-grid_size, i);
        glVertex2i(grid_size, i);

        //XZ plane
        glVertex3i(i, 0, -grid_size);
        glVertex3i(i, 0, grid_size);
        glVertex3i(-grid_size, 0, i);
        glVertex3i(grid_size, 0, i);
    }
    glEnd();
}

void EngineCore::Render(RenderModes renderMode)
{
    ilInit();

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
    glClearDepth(1.0f);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glEnable(GL_COLOR_MATERIAL);

    //glEnable(GL_LIGHTING);

    glLoadMatrixf(camera.GetViewMatrix());

    drawGrid(100, 10);
    drawAxis();

    static auto mesh_ptrs = Mesh::loadFromFile("Assets/BakerHouse.fbx");
    
    GraphicObject mesh1(mesh_ptrs.front());
    GraphicObject mesh2(mesh_ptrs.back());
    
    GraphicObject house;
    
    house.addChild(std::move(mesh1));
    house.addChild(std::move(mesh2));
    
    GraphicObject root;
    root.addChild(std::move(house));
    
    root.paint();
     
    // JULS: This should be commented, if not catastrophic error (srly)
    //assert(glGetError() == GL_NONE);
}