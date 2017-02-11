#include <iostream>
#include "Display/Display.h"
#include <GL/freeglut.h>

int main(int argc, char** argv)
{
    Display display(800, 600, "Hey there");

    while(!display.IsClosed())
    {
        display.Clear(0.0f, 0.0f, 0.15f, 1.0f);
        display.Update();
    }

    return 0;
}
