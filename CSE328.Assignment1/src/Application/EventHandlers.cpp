#include "Application.h"

bool isUserSelecting = true;
Pixel* interactingVertex = nullptr;

/* Event Handlers*/
void InitHandler()
{
    glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, WINDOW_WIDTH, WINDOW_HEIGHT, 0);
}

void DrawHandler()
{
    glClearColor(0.0f, 0.15f, 0.25f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // Draw the lines
    glPointSize(2);
    glColor3f(1.0f, 1.0f, 1.0f);

    glBegin(GL_POINTS);

    auto linePixels = GetLinePixelsFromVertices(selectedPixels);
    // Draw the lines
    for (auto pixel : linePixels)
    {
        glVertex2i(pixel.X, pixel.Y);
    }
    // Scan convert the polygon
    if (!isUserSelecting)
    {
        auto scanConvertedPixels = GetScanConvertedPixels(linePixels);
        for (auto pixel : scanConvertedPixels)
        {
            glVertex2i(pixel.X, pixel.Y);
        }
        scanConvertedPixels.clear();
        scanConvertedPixels.shrink_to_fit();
    }
    linePixels.clear();
    linePixels.shrink_to_fit();

    glEnd();

    // Draw the selected vertices
    glPointSize(6);
    glColor3f(1.0f, 0.0f, 0.0f);

    glBegin(GL_POINTS);
    for (auto pixel : selectedPixels)
    {
        glVertex2i(pixel.X, pixel.Y);
    }
    glEnd();

    // Draw the interacting vertex
    if (interactingVertex != nullptr)
    {
        glPointSize(10);
        glColor3f(0.0f, 1.0f, 0.0f);

        glBegin(GL_POINTS);
        glVertex2i(interactingVertex->X, interactingVertex->Y);
        glEnd();
    }
}

// Called when a keyboard key is pressed
void KeyboardButtonHandler(SDL_KeyboardEvent evt)
{
    if (evt.keysym.sym == SDLK_F5)
    {
        // Reset the app
        isUserSelecting = true;

        // Reset interacting pixel
        interactingVertex = nullptr;
        
        // Empty the previously selected pixels
        selectedPixels.clear();
        selectedPixels.shrink_to_fit();
    }
}

//Called when the mouse button is pressed
void MouseButtonHandler(SDL_MouseButtonEvent evt)
{
    if (evt.button == SDL_BUTTON_LEFT)
    {
        if (isUserSelecting)
        {
            selectedPixels.push_back(Pixel(evt.x, evt.y));
        }
        else
        {
            auto selected = false;
            for (auto &pixel : selectedPixels)
            {
                if (pixel.IsNearPoint(evt.x, evt.y, 6))
                {
                    interactingVertex = &pixel;
                    selected = true;
                }
            }

            // Deselect the selected vertex if left click again
            if (!selected)
            {
                interactingVertex = nullptr;
            }
        }
    }
    if (evt.button == SDL_BUTTON_RIGHT)
    {
        if (isUserSelecting)
        {
            // Can't create polygon without at least 3 points
            if (selectedPixels.size() < 3)
                return;

            selectedPixels.push_back(selectedPixels[0]);

            isUserSelecting = false;
        }
        else if (interactingVertex != nullptr)
        {
            for (auto &pixel : selectedPixels)
            {
                if (pixel == *interactingVertex)
                {
                    pixel.X = evt.x;
                    pixel.Y = evt.y;
                }
            }
        }
    }
}
