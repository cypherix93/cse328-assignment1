#pragma once
#include <iostream>
#include <SDL.h>

class Display
{
    public:
    Display(int width, int height, const std::string& title);
    virtual ~Display();

    void Clear(float r, float g, float b, float a);
    void Update();
    bool IsWindowClosed();

    protected:

    private:
    SDL_Window* _Window;
    SDL_GLContext _GLContext;

    bool _IsWindowClosed;

    void SetupColors();
    void SetupGlew();
    void SetupWindow(const std::string& title, int width, int height);
    void DestroyWindow();
};

