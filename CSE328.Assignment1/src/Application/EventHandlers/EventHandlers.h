#pragma once
#include "SDL.h"

namespace EventHandlers
{
    void InitHandler();
    void DrawHandler();
    void UpdateHandler();
    void ResizeHandler(struct SDL_WindowEvent);
    void MouseButtonHandler(SDL_MouseButtonEvent);
}
