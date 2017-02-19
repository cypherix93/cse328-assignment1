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
    vector<Pixel> result;

    // Special cases
    // If both pixels are literally the same, do nothing
    if (v1 == v2)
    {
        result.push_back(v1);
        return result;
    }
    // If straight line along X axis
    if (v1.Y == v2.Y)
    {
        for (auto x = v1.X; x < v2.X; x++)
        {
            result.push_back(Pixel(x, v1.Y));
        }
        return result;
    }
    // If straight line along Y axis
    if (v1.X == v2.X)
    {
        for (auto y = v1.Y; y < v2.Y; y++)
        {
            result.push_back(Pixel(v1.X, y));
        }
        return result;
    }

    // Mid point algorithm
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

    auto dx = end->X - start->X;
    auto dy = end->Y - start->Y;

    auto dyAbs = fabs(dy);
    auto p = dyAbs - dx / 2;
    auto incE = dyAbs;
    auto incNE = dyAbs - dx;

    auto x = 0;
    auto y = 0;

    while (x < dx)
    {
        if (p < 0)
        {
            p += incE;
        }
        else
        {
            if (dy < 0)
            {
                y--;
            }
            else
            {
                y++;
            }

            p += incNE;
        }

        result.push_back(Pixel(start->X + x, start->Y + y));

        x++;
    }

    return result;
}
