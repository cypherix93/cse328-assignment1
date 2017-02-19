#include "LineDrawer.h"

vector<Pixel> Drawing::GetLinePixelsFromVertices(vector<Pixel> vertices)
{
    vector<Pixel> result;

    // Just return the first point if there's only point selected
    if (vertices.size() == 1)
    {
        result.push_back(vertices[0]);
    }

    for (size_t i = 0; i < vertices.size() - 1; i++)
    {
        auto linePixels = GetSingleLinePixels(vertices[i], vertices[i + 1]);

        result.insert(result.end(), linePixels.begin(), linePixels.end());
    }

    return result;
}

vector<Pixel> Drawing::GetSingleLinePixels(Pixel start, Pixel end)
{
    // Pick where to start
    auto left = min(start.X, end.X);
    auto right = max(start.X, end.X);

    vector<Pixel> result;
    for (size_t i = left; i < right; i++)
    {
        result.push_back(Pixel(i, start.Y));
    }

    return result;
}
