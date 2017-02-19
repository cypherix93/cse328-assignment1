#include "LineDrawer.h"

vector<Pixel> Drawing::GetLinePixelsFromVertices(vector<Pixel> vertices)
{
    vector<Pixel> result;

    // If it is empty return empty
    if (vertices.size() == 0)
    {
        return result;
    }
    // Just return the first point if there's only point selected
    if (vertices.size() == 1)
    {
        result.push_back(vertices[0]);
        return result;
    }

    for (size_t i = 0; i < vertices.size() - 1; i++)
    {
        auto linePixels = GetSingleLinePixels(vertices[i], vertices[i + 1]);

        result.insert(result.end(), linePixels.begin(), linePixels.end());
    }

    return result;
}

vector<Pixel> Drawing::GetSingleLinePixels(Pixel v1, Pixel v2)
{
    // Pick where to start and end
    Pixel* start;
    Pixel* end;

    if (v1.X < v2.X)
    {
        start = &v1;
        end = &v2;
    }
    else
    {
        start = &v2;
        end = &v1;
    }

    vector<Pixel> result;

    auto dx = fabs(end->X - start->X);
    auto dy = fabs(end->Y - start->Y);
    auto p = 2 * dy - dx;
    auto twoDy = 2 * dy, twoDyMinusDx = 2 * (dy - dx);

    auto y = start->Y;

    for (auto x = start->X; x < end->X; x++)
    {
        if (p < 0)
        {
            p += twoDy;
        }
        else
        {
            y++;
            p += twoDyMinusDx;
        }

        result.push_back(Pixel(x, y));
    }

    return result;
}
