#pragma once
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <SDL.h>
#include <functional>

typedef std::function<void(void)> DrawHandlerFunc;
typedef std::function<void(void)> UpdateHandlerFunc;
typedef std::function<void(SDL_WindowEvent)> WindowHandlerFunc;
typedef std::function<void(SDL_KeyboardEvent)> KeypressHandlerFunc;

class WindowManager
{
    public:
    WindowManager();
    virtual ~WindowManager();

    // Lifecycle functions
    void Init() const;
    void Dispose() const;
    void OpenWindow(std::string title, int width, int height);
    void Start();

    // Event Handler Register functions
    void OnUpdateEvent(UpdateHandlerFunc);
    void OnDrawEvent(DrawHandlerFunc);
    void OnWindowEvent(WindowHandlerFunc);
    void OnKeypressEvent(KeypressHandlerFunc);


    private:
    SDL_Window* _Window = nullptr;
    SDL_GLContext _GLContext;
    bool _IsRunning;

    UpdateHandlerFunc _UpdateEventHandler = nullptr;
    DrawHandlerFunc _DrawEventHandler = nullptr;
    WindowHandlerFunc _WindowEventHandler = nullptr;
    KeypressHandlerFunc _KeypressEventHandler = nullptr;
};

