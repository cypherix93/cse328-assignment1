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

    private:
    WindowManager* _WindowManager;

    // Lifecycle Hooks
    static void Setup();
    static void Start();
};

