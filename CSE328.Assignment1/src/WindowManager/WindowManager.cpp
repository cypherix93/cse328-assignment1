#include "WindowManager.h"

/* Constructor */
WindowManager::WindowManager()
{
}

/* Destructor */
WindowManager::~WindowManager()
{
}

/* Public Methods */
void WindowManager::Init() const
{
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        SDL_Log("Unable to initialize SDL: %s\n", SDL_GetError());
    }

    glewExperimental = GL_TRUE;

    if (glewInit() != GLEW_OK)
    {
        SDL_Log("GLEW failed to initialize.");
    }

    SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);

    SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
}

void WindowManager::Dispose() const
{
    SDL_GL_DeleteContext(_GLContext);
    SDL_DestroyWindow(_Window);
    SDL_Quit();
}

void WindowManager::OpenWindow(std::string title, int width, int height)
{
    auto windowFlags = SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE;

    _Window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, windowFlags);

    if (_Window == nullptr)
    {
        SDL_Log("SDL Window failed to initialize.");
    }
    _GLContext = SDL_GL_CreateContext(_Window);
    _IsRunning = true;

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_LIGHTING); //Enable lighting
    glEnable(GL_LIGHT0); //Enable light #0
    glEnable(GL_LIGHT1); //Enable light #1
    glEnable(GL_NORMALIZE); //Automatically normalize normals
    glShadeModel(GL_SMOOTH); //Enable smooth shading
    
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (double)width / (double)height, 1.0, 200.0);
}

void WindowManager::Start(int fps)
{
    auto delay = 1000 / fps;

    while (_IsRunning)
    {
        // Check all events and call handlers
        SDL_Event evt;
        while (SDL_PollEvent(&evt))
        {
            if (evt.type == SDL_QUIT)
            {
                _IsRunning = false;
            }
            else if (evt.type == SDL_KEYDOWN)
            {
                if (_KeypressEventHandler != nullptr)
                {
                    _KeypressEventHandler(evt.key);
                }
            }
            else if (evt.type == SDL_WINDOWEVENT)
            {
                if (_WindowEventHandler != nullptr)
                {
                    _WindowEventHandler(evt.window);
                }
            }
        }
        
        // Call draw handler
        if (_DrawEventHandler != nullptr)
        {
            _DrawEventHandler();
        }
        if (_UpdateEventHandler != nullptr)
        {
            _UpdateEventHandler();
        }

        // Swap buffers
        SDL_GL_SwapWindow(_Window);

        // Delay for a bit to have a smooth framerate
        SDL_Delay(delay);
    }
}

/* Event Handlers */
void WindowManager::OnUpdateEvent(UpdateHandlerFunc callback)
{
    _UpdateEventHandler = callback;
}
void WindowManager::OnDrawEvent(DrawHandlerFunc callback)
{
    _DrawEventHandler = callback;
}
void WindowManager::OnWindowEvent(WindowHandlerFunc callback)
{
    _WindowEventHandler = callback;
}
void WindowManager::OnKeypressEvent(KeypressHandlerFunc callback)
{
    _KeypressEventHandler = callback;
}
