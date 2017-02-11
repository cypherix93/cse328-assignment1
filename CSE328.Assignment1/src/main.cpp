#include <iostream>
#include "Display/Display.h"
#include <GL/freeglut.h>

int main(int argc, char** argv)
{
    Display display(800, 600, "Hey there");

    while(!display.IsClosed())
    {
        glClearColor(0.0f, 0.0f, 0.15f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        display.Update();
    }

    return 0;
}
