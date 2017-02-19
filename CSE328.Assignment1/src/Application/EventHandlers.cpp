﻿#include "Application.h"

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

    pixelsToDraw.clear();
    pixelsToDraw.shrink_to_fit();
}

void UpdateHandler()
{

}

//Called when the mouse button is pressed
void MouseButtonHandler(SDL_MouseButtonEvent evt)
{
    if (evt.button == SDL_BUTTON_LEFT)
    {
        selectedPixels.push_back(Pixel(evt.x, evt.y));
    }
}