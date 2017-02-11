#pragma once
#include <iostream>
#include <SDL.h>

class Display
{
    public:
    Display(int width, int height, const std::string& title);
    virtual ~Display();

    void Update();
    bool IsClosed();

    protected:
    private:
    SDL_Window* _Window;
    SDL_GLContext _GLContext;

    bool _IsClosed;
};

