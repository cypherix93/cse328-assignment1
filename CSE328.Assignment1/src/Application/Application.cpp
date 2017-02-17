#include "Application.h"
#include "../WindowManager/WindowManager.h"

float _angle = -70.0f;

//Called when a key is pressed
void handleKeypress(SDL_KeyboardEvent evt)
{
    switch (evt.keysym.sym) {
        case SDLK_ESCAPE: //Escape key
            exit(0);
    }
}

//Called when the window is resized
void handleResize(SDL_WindowEvent evt)
{
    if (evt.event == SDL_WINDOWEVENT_RESIZED)
    {
        auto w = evt.data1;
        auto h = evt.data2;

        glViewport(0, 0, w, h);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        gluPerspective(45.0, (double)w / (double)h, 1.0, 200.0);
    }
}

//Draws the 3D scene
void drawScene()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glTranslatef(0.0f, 0.0f, -8.0f);

    //Add ambient light
    GLfloat ambientColor[] = { 0.2f, 0.2f, 0.2f, 1.0f }; //Color (0.2, 0.2, 0.2)
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientColor);

    //Add positioned light
    GLfloat lightColor0[] = { 0.5f, 0.5f, 0.5f, 1.0f }; //Color (0.5, 0.5, 0.5)
    GLfloat lightPos0[] = { 4.0f, 0.0f, 8.0f, 1.0f }; //Positioned at (4, 0, 8)
    glLightfv(GL_LIGHT0, GL_DIFFUSE, lightColor0);
    glLightfv(GL_LIGHT0, GL_POSITION, lightPos0);

    //Add directed light
    GLfloat lightColor1[] = { 0.5f, 0.2f, 0.2f, 1.0f }; //Color (0.5, 0.2, 0.2)
                                                        //Coming from the direction (-1, 0.5, 0.5)
    GLfloat lightPos1[] = { -1.0f, 0.5f, 0.5f, 0.0f };
    glLightfv(GL_LIGHT1, GL_DIFFUSE, lightColor1);
    glLightfv(GL_LIGHT1, GL_POSITION, lightPos1);

    glRotatef(_angle, 0.0f, 1.0f, 1.0f);
    //Set the colour here
    glColor3f(1.0f, 0.0f, 0.0f);
    glBegin(GL_QUADS);

    //Front
    glNormal3f(0.0f, 0.0f, 1.0f);
    //glNormal3f(-1.0f, 0.0f, 1.0f);
    glVertex3f(-1.5f, -1.0f, 1.5f);
    //glNormal3f(1.0f, 0.0f, 1.0f);
    glVertex3f(1.5f, -1.0f, 1.5f);
    //glNormal3f(1.0f, 0.0f, 1.0f);
    glVertex3f(1.5f, 1.0f, 1.5f);
    //glNormal3f(-1.0f, 0.0f, 1.0f);
    glVertex3f(-1.5f, 1.0f, 1.5f);

    //Right
    glNormal3f(1.0f, 0.0f, 0.0f);
    //glNormal3f(1.0f, 0.0f, -1.0f);
    glVertex3f(1.5f, -1.0f, -1.5f);
    //glNormal3f(1.0f, 0.0f, -1.0f);
    glVertex3f(1.5f, 1.0f, -1.5f);
    //glNormal3f(1.0f, 0.0f, 1.0f);
    glVertex3f(1.5f, 1.0f, 1.5f);
    //glNormal3f(1.0f, 0.0f, 1.0f);
    glVertex3f(1.5f, -1.0f, 1.5f);

    //Back
    glNormal3f(0.0f, 0.0f, -1.0f);
    //glNormal3f(-1.0f, 0.0f, -1.0f);
    glVertex3f(-1.5f, -1.0f, -1.5f);
    //glNormal3f(-1.0f, 0.0f, -1.0f);
    glVertex3f(-1.5f, 1.0f, -1.5f);
    //glNormal3f(1.0f, 0.0f, -1.0f);
    glVertex3f(1.5f, 1.0f, -1.5f);
    //glNormal3f(1.0f, 0.0f, -1.0f);
    glVertex3f(1.5f, -1.0f, -1.5f);

    //Left
    glNormal3f(-1.0f, 0.0f, 0.0f);
    //glNormal3f(-1.0f, 0.0f, -1.0f);
    glVertex3f(-1.5f, -1.0f, -1.5f);
    //glNormal3f(-1.0f, 0.0f, 1.0f);
    glVertex3f(-1.5f, -1.0f, 1.5f);
    //glNormal3f(-1.0f, 0.0f, 1.0f);
    glVertex3f(-1.5f, 1.0f, 1.5f);
    //glNormal3f(-1.0f, 0.0f, -1.0f);
    glVertex3f(-1.5f, 1.0f, -1.5f);

    glEnd();
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
    _WindowManager->OnDrawEvent(drawScene);
    _WindowManager->OnKeypressEvent(handleKeypress);
    _WindowManager->OnWindowEvent(handleResize);

    _WindowManager->OnUpdateEvent([]()
    {
        _angle += 1.5f;
        if (_angle > 360)
        {
            _angle -= 360;
        }
    });
}

void Application::Start()
{
    Setup();

    // Open GLUT Window
    _WindowManager->OpenWindow("Hey there!", WINDOW_WIDTH, WINDOW_HEIGHT);

    // Start Window Lifecycle
    _WindowManager->Start();
}