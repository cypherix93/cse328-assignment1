#pragma once
#include <GL/glut.h>

#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 720

class WindowManager
{
    public:
    WindowManager();
    virtual ~WindowManager();

    void Init(int argc, char** argv) const;
    void OpenWindow() const;
};

