#include <iostream>
#include "Display/Display.h"
#include <GL/freeglut.h>

#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 720

int main(int argc, char** argv)
{
    Display display(WINDOW_WIDTH, WINDOW_HEIGHT, "Hey there");

    while(display.IsRunning())
    {
        display.Clear(0.0f, 0.0f, 0.15f, 1.0f);
        display.Update();
    }

    return 0;
}
