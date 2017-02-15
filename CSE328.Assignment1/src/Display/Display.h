#pragma once
#include <iostream>
#include <SDL.h>
#include <GL/glew.h>

class Display
{
    public:
    Display(int width, int height, const std::string& title);
    virtual ~Display();

    int Width;
    int Height;
    std::string Title;

    void Clear(float r = 0, float g = 0, float b = 0, float a = 1);
    void Update();
    bool IsWindowClosed();

    protected:

    private:
    SDL_Window* _Window;
    SDL_GLContext _GLContext;

    bool _IsWindowClosed;

    void DestroyWindow();
    void SetupWindow();
};

