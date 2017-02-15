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