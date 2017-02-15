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

    void Clear(float r = 0, float g = 0, float b = 0, float a = 1) const;
    void Update();
    bool IsRunning() const;
    
    private:
    SDL_Window* _Window = nullptr;
    SDL_GLContext _GLContext;
    SDL_Surface* _Surface = nullptr;

    bool _IsRunning;

    void DestroyWindow() const;
    void SetupWindow();
};

