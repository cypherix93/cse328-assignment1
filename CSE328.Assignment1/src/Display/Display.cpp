#include "Display.h"

/* Constructor */
Display::Display(int width, int height, const std::string& title)
{
    Width = width;
    Height = height;
    Title = title;

    SetupWindow();
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
void Display::SetupWindow()
{
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        SDL_Log("Unable to initialize SDL: %s\n", SDL_GetError());
    }

    auto windowFlags = SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE;

    _Window = SDL_CreateWindow(Title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, Width, Height, windowFlags);

    if (_Window == nullptr)
    {
        SDL_Log("SDL Window failed to initialize.");
    }
    _GLContext = SDL_GL_CreateContext(_Window);
    _IsWindowClosed = false;

    glewExperimental = GL_TRUE;

    if (glewInit() != GLEW_OK)
    {
        SDL_Log("GLEW failed to initialize.");
    }
}
void Display::DestroyWindow()
{
    SDL_GL_DeleteContext(_GLContext);
    SDL_DestroyWindow(_Window);    
}
