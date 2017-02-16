#pragma once
#include <GL/glut.h>
#include <functional>

#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 720

#define FPS 60

class WindowManager
{
    public:
    WindowManager();
    virtual ~WindowManager();

    // Lifecycle functions
    void Init(int argc, char** argv) const;
    void OpenWindow() const;
    void Start(int fps = FPS);

    // Event Handler Register functions
    void OnUpdate(void(*callback)(int));
    void OnDraw(void(*callback)(void));
    void OnResize(void(*callback)(int, int));
    void OnKeypress(void(*callback)(unsigned char, int, int));


    private:
    int _FPS = FPS;

    std::function<void(int)> _UpdateHandler = nullptr;
    std::function<void(void)> _DrawHandler = nullptr;
    std::function<void(int, int)> _ResizeHandler = nullptr;
    std::function<void(unsigned char, int, int)> _KeypressHandler = nullptr;
};

