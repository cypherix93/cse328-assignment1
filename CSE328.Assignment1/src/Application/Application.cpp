#include "Application.h"
#include "../WindowManager/WindowManager.h"

static unsigned int _Pixels[WINDOW_WIDTH][WINDOW_HEIGHT][3];

void InitHandler()
{
    glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, (double)WINDOW_WIDTH, 0, (double)WINDOW_HEIGHT);

    glPointSize(2);
}

void DrawHandler()
{
    auto red = (float)(rand() % 100) / 255;

    glClearColor(red, 0.15f, 0.25f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glColor3f(1.0f, 1.0f, 1.0f);

    glBegin(GL_POINTS);

    for (int i = 0; i < 10; i++)
    {
        glVertex2i(10 + 5 * i, 110);
    }

    glEnd();

    glFlush();
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

/* Constructor */
Application::Application()
{
    _WindowManager = new WindowManager();
    _WindowManager->Init();
}

/* Destructor */
Application::~Application()
{
    _WindowManager->Dispose();
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
}

void Application::Start()
{
    Setup();

    // Open GLUT Window
    _WindowManager->OpenWindow("Hey there!", WINDOW_WIDTH, WINDOW_HEIGHT);

    // Start Window Lifecycle
    _WindowManager->Start();
}