# Lilac Engine
## Description
Videogame engine created for the Videogame Engines subject. This has been made during our third year of UPC's bachelor degree on Design and Development of Videogames. This README has all the controls and features of the project.

This engine has been made with:
* [SDL 2](https://www.libsdl.org)
* [Dear ImGui](https://github.com/ocornut/imgui)
* [Assimp](https://github.com/assimp/assimp)
* [OpenGL](https://www.opengl.org)
* [GLEW](https://glew.sourceforge.net)
* [GLM](https://www.opengl.org/sdk/libs/GLM/)
* [DevIL](https://openil.sourceforge.net)

Click [HERE](https://github.com/CITM-UPC/LilacEngine2) to see the repository of the project.

## Developers
* [Júlia Serra Trujillo](https://github.com/softdrawss)
* [Joel Chaves Moreno](https://github.com/JoeyCM)

## Controls
* Right click + WASD -> Move camera
* Right click + LSHIFT + WASD -> Faster movement of the camera
* Right click + Mouse Input -> Look around
* LALT + Left click -> Camera orbitation
* Mousewheel -> Zoom in and out
* F -> Focuses the camera around the geometry

## Features

### Drag and drop
Drag and drop allows the user to directly drop FBX assets and textures in the scene.

### Top Bar
General:
* Editor: Choose to open and close the different windows of the scene.
  * Console
  * Configuration
  * Hierarchy
  * Inspector
  * Shapes
* GitHub Page: Takes the user to the Repository of the project.
* About: Displays information of the project and license.
* Quit: When pressed closes the application.

Load:
* Shows the different meshes that the user can display, when clicking one, it spawns on screen.

### Configuration
* Application: Shows the name of the project, the name of the organization and the FPS graph.
* Window: Adjust brightness of the scene and different window options like, resize, fullscreen or borderless.
* Renderer: Enable or disable Vsync.
* Input: Shows mouse position on X and Y, delta and the wheel response.
* Audio: Shows if there's an audio track on scene.
* Hardware: Displays the software version of SDL and OpenGL. Shows the hardware components like CPU, GPU and RAM of the machine that is being used to run the application, the amount of RAM that is still availiable and the expected RAM to use.

### Hierarchy
Displays the different game objects that are in scene. Each of these is displayed with all its components.

### Shapes
Shows different properties of the game object thats is selected.

### Console
Logs the geometry loading process from ASSIMP as well as other different processes.

### Inspector
When an object is selected, shows the different parameters of it. Transform shows position, rotation and scale of the object; mesh, the information about the loaded mesh; texture, displays the path and size.
