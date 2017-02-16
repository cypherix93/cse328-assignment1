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
void WindowManager::Init(int argc, char** argv) const
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
}

void WindowManager::OpenWindow() const
{
    glutCreateWindow("Rotating 3D Cuboid");

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_LIGHTING); //Enable lighting
    glEnable(GL_LIGHT0); //Enable light #0
    glEnable(GL_LIGHT1); //Enable light #1
    glEnable(GL_NORMALIZE); //Automatically normalize normals
                            //glShadeModel(GL_SMOOTH); //Enable smooth shading
}

void WindowManager::Start(int fps)
{
    _FPS = fps;

    // Setup Draw Handler
    if (_DrawHandler != nullptr)
    {
        std::bind(glutDisplayFunc, _DrawHandler);
    }

    // Setup Event Handlers
    if (_ResizeHandler != nullptr)
    {
        std::bind(glutReshapeFunc, _ResizeHandler);
    }
    if (_KeypressHandler != nullptr)
    {
        std::bind(glutKeyboardFunc, _KeypressHandler);
    }

    // Setup Update Handler
    if (_UpdateHandler != nullptr)
    {
        _UpdateHandler(0);
    }

    glutMainLoop();
}

void WindowManager::OnUpdate(void(*callback)(int))
{
    auto delay = 1000 / _FPS;

    _UpdateHandler = [this, callback, delay](int value)
    {
        callback(value);

        glutPostRedisplay();
        std::bind(glutTimerFunc, delay, _UpdateHandler, 0);
    };
}

void WindowManager::OnDraw(void(*callback)())
{
    _DrawHandler = callback;
}

void WindowManager::OnResize(void(*callback)(int, int))
{
    _ResizeHandler = callback;
}

void WindowManager::OnKeypress(void(*callback)(unsigned char key, int x, int y))
{
    _KeypressHandler = callback;
}
