#include "EventHandlers.h"
#include <list>
#include "../../Drawing/Pixel/Pixel.h"
#include "../Application.h"

using namespace Drawing;
using namespace EventHandlers;

static list<Pixel> pixelsToDraw;

/* Event Handlers*/
void EventHandlers::InitHandler()
{
    glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, WINDOW_WIDTH, WINDOW_HEIGHT, 0);

    glPointSize(2);
}

void EventHandlers::DrawHandler()
{
    glClearColor(0.0f, 0.15f, 0.25f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glColor3f(1.0f, 1.0f, 1.0f);

    glBegin(GL_POINTS);

    for (auto pixel : pixelsToDraw)
    {
        glVertex2i(pixel.X, pixel.Y);
    }

    glEnd();
}

void EventHandlers::UpdateHandler()
{

}

//Called when the window is resized
void EventHandlers::ResizeHandler(SDL_WindowEvent evt)
{
    if (evt.event == SDL_WINDOWEVENT_RESIZED)
    {
        auto w = evt.data1;
        auto h = evt.data2;

        glViewport(0, 0, w, h);
    }
}

//Called when the mouse button is pressed
void EventHandlers::MouseButtonHandler(SDL_MouseButtonEvent evt)
{
    if (evt.button == SDL_BUTTON_LEFT)
    {
        pixelsToDraw.push_back(Pixel(evt.x, evt.y));
    }
}
