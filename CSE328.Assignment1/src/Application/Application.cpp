#include "Application.h"

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


/* Event Handlers*/
void InitHandler()
{
    glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, WINDOW_WIDTH, WINDOW_HEIGHT, 0);

    glPointSize(2);
}

void DrawHandler()
{
    glClearColor(0.0f, 0.15f, 0.25f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glColor3f(1.0f, 1.0f, 1.0f);

    glBegin(GL_POINTS);

    pixelsToDraw = GetLinePixelsFromVertices(selectedPixels);

    for (auto pixel : pixelsToDraw)
    {
        glVertex2i(pixel.X, pixel.Y);
    }

    glEnd();
}

void UpdateHandler()
{

}

//Called when the window is resized
void ResizeHandler(SDL_WindowEvent evt)
{
    if (evt.event == SDL_WINDOWEVENT_RESIZED)
    {
        auto w = evt.data1;
        auto h = evt.data2;

        glViewport(0, 0, w, h);
    }
}

//Called when the mouse button is pressed
void MouseButtonHandler(SDL_MouseButtonEvent evt)
{
    if (evt.button == SDL_BUTTON_LEFT)
    {
        selectedPixels.push_back(Pixel(evt.x, evt.y));
    }
}
