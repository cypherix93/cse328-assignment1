#pragma once
#include <iostream>
#include <stdlib.h>
#include <GL/freeglut.h>
#include "../WindowManager/WindowManager.h"

using namespace std;

class Application
{
    public:
    Application();
    virtual ~Application();

    // Lifecycle Hooks
    void Setup();
    void Start();

    private:
    WindowManager* _WindowManager;
};