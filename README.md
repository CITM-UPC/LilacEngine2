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
* Right click + LSHIFT + WASD -> Move camera
* Right click + Mouse Input -> Look around
* LALT + Left click -> Camera orbitation
* Mousewheel -> Zoom in and out
* F -> Set camera position to (0,0,0)

## Features

### Top Bar
General:
* Editor: Choose to open and colose the different windows of the scene
  * Console
  * Configuration
  * Hierarchy
  * Inspector
  * Shapes
* GitHub Page: Takes the user to the Repository of the project
* About: Displays information of the project
* Quit: When pressed closes the application
* Load: Shows the different meshes that the user can display on scene. When one mesh is clicked, spawns on scene.

### Configuration
* Application: Shows the name of the project, the name of the organization and the FPS graph.
* Window: Adjust brightness and different window options like, resize, fullscreen or borderless.
* Renderer: Enable or disable Vsync.
* Input: Shows mouse position, delta and the wheel response.
* Audio: Shows if there's an audio track on scene.
* Hardware: Displays the software version of SDL and OpenGL. Shows the hardware components like CPU, GPU and RAM of the machine that is being used to run the application.

### Hierarchy
Displays the different game objects that are in scene.

### Resources
Shows different porperties of the game object thats is selected.

### Console
Displays information of what's happening in the scene. Shows the different phases of the application and when a mesh is loading the console shows the LOG of the loaded mesh.

### Inspector
When an object is selected, shows the different options of what to do with it. Transform options, like rotations, scaling and position; mesh options to display normals; texture options to show or hide the texture of the object.
