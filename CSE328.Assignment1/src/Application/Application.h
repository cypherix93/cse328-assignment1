#pragma once
#include <iostream>
#include <list>
#include "../WindowManager/WindowManager.h"
#include <SDL.h>
#include <GL/freeglut.h>
#include "../Drawing/Pixel/Pixel.h"

using namespace std;
using namespace Drawing;

#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 720

static list<Pixel> pixelsToDraw;

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

void InitHandler();
void DrawHandler();
void UpdateHandler();
void ResizeHandler(SDL_WindowEvent);
void MouseButtonHandler(SDL_MouseButtonEvent);