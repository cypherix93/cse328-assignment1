#include "Display.h"
#include <GL/glew.h>

/* Constructor */
Display::Display(int width, int height, const std::string& title)
{
    SDL_Init(SDL_INIT_EVERYTHING);
    SetupWindow(title, width, height);
}

/* Destructor */
Display::~Display()
{
    DestroyWindow();
    SDL_Quit();
}

/* Public Methods */
void Display::Clear(float r, float g, float b, float a)
{
    glClearColor(r, g, b, a);
    glClear(GL_COLOR_BUFFER_BIT);
}
void Display::Update()
{
    SDL_GL_SwapWindow(_Window);

    SDL_Event e;

    while (SDL_PollEvent(&e))
    {
        if (e.type == SDL_QUIT)
            _IsWindowClosed = true;
    }
}
bool Display::IsWindowClosed()
{
    return _IsWindowClosed;
}

/* Private Methods */
void Display::SetupWindow(const std::string& title, int width, int height)
{
    SetupColors();

    auto windowFlags = SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE;

    _Window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, windowFlags);
    _GLContext = SDL_GL_CreateContext(_Window);
    _IsWindowClosed = false;

    SetupGlew();
}
void Display::SetupColors()
{
    SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);

    SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
}
void Display::SetupGlew()
{
    auto status = glewInit();

    if (status != GLEW_OK)
    {
        std::cerr << "Glew failed to initialize." << std::endl;
    }
}
void Display::DestroyWindow()
{
    SDL_GL_DeleteContext(_GLContext);
    SDL_DestroyWindow(_Window);    
}
