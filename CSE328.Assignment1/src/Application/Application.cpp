#include <list>
#include "Application.h"
#include "../WindowManager/WindowManager.h"
#include "EventHandlers/EventHandlers.h"

using namespace EventHandlers;

/* Constructor */
Application::Application()
{
    _WindowManager = new WindowManager();
}

/* Destructor */
Application::~Application()
{
    free(_WindowManager);
}

/* Public Methods*/
void Application::Setup()
{
    //Set handler functions
    _WindowManager->OnInit(InitHandler);
    _WindowManager->OnDrawEvent(DrawHandler);
    _WindowManager->OnUpdateEvent(UpdateHandler);

    _WindowManager->OnWindowEvent(ResizeHandler);

    _WindowManager->OnMouseEvent(MouseButtonHandler);
}

void Application::Start()
{
    Setup();

    // Open GLUT Window
    _WindowManager->OpenWindow("CSE 328 Assignment 1", WINDOW_WIDTH, WINDOW_HEIGHT);

    // Start Window Lifecycle
    _WindowManager->Start();
}
