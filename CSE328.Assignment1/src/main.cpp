#ifdef _MSC_VER
#    pragma comment(linker, "/subsystem:windows /ENTRY:mainCRTStartup")
#endif
#include "Application/Application.h"

int main(int argc, char** argv)
{
    Application app;
    
    app.Start();

    return 0;
}
