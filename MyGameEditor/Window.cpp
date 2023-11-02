#include "Application.h"
#include "Window.h"
#include "Log.h"

Window::Window(Application* app) : Module(app), window(nullptr), context(nullptr) 
{

}

Window::~Window() 
{

}

bool Window::Awake()
{
    LOG("Init Window");
    window = initSDLWindowWithOpenGL();
    context = createSdlGlContext(window);
    initOpenGL();
    
    return true;
}

bool Window::Start()
{
    return true;
}


bool Window::CleanUp()
{
    LOG("Cleaning Window");
    if (context) SDL_GL_DeleteContext(context);
    if (window) SDL_DestroyWindow(window);
    SDL_Quit();

    return true;
}

SDL_Window* Window::initSDLWindowWithOpenGL()
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0) throw exception(SDL_GetError());

    SDL_version compiled;
    SDL_VERSION(&compiled);
    cout << "SDL Compiled with " << to_string(compiled.major) << '.' << to_string(compiled.minor) << '.' << to_string(compiled.patch);

    SDL_version linked;
    SDL_GetVersion(&linked);
    cout << "SDL Linked with " << to_string(linked.major) << '.' << to_string(linked.minor) << '.' << to_string(linked.patch);

    // setup SDL window
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
    SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

    // GL 3.1 + GLSL 130
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, 0);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);

    auto window = SDL_CreateWindow("TITLE", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_OPENGL);
    if (!window) throw exception(SDL_GetError());

    return window;
}

SDL_GLContext Window::createSdlGlContext(SDL_Window* window)
{
    auto gl_context = SDL_GL_CreateContext(window);
    if (!gl_context) throw exception(SDL_GetError());
    if (SDL_GL_MakeCurrent(window, gl_context) != 0) throw exception(SDL_GetError());
    if (SDL_GL_SetSwapInterval(1) != 0) throw exception(SDL_GetError());
    return gl_context;
}

void Window::initOpenGL()
{
    auto glew_init_error = glewInit();
    if (glew_init_error != GLEW_OK) throw exception((char*)glewGetErrorString(glew_init_error));
    if (!GLEW_VERSION_3_1) throw exception("OpenGL 3.1 Not Supported!");
    glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
    glClearColor(0.25, 0.25, .25, 1);
}

void Window::SetTitle(const char* title)
{
    SDL_SetWindowTitle(window, title);
}

void Window::SetWindowBrightness(float brightness) {
    SDL_SetWindowBrightness(window, brightness);
}

void Window::SetFullscreen(bool fullscreen) {
    SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN);
}

void Window::SetResizable(bool resizable) {
    SDL_SetWindowResizable(window, (SDL_bool)resizable);
}

void Window::SetBorderless(bool borderless) {
    SDL_SetWindowBordered(window, (SDL_bool)borderless);
}

void Window::SetFullDesktop(bool fullDesktop) {
    SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN_DESKTOP);
}