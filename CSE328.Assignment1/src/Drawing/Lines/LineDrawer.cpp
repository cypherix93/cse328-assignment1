#include "LineDrawer.h"

static vector<Pixel> computeMidPointAlgorithm(int x1, int y1, int x2, int y2);

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

    for (auto i = 0; i < vertices.size() - 1; i++)
    {
        auto linePixels = GetSingleLinePixels(vertices[i], vertices[i + 1]);

        result.insert(result.end(), linePixels.begin(), linePixels.end());

        linePixels.clear();
        linePixels.shrink_to_fit();
    }

    return result;
}

vector<Pixel> Drawing::GetSingleLinePixels(Pixel start, Pixel end)
{
    vector<Pixel> result;
    
    // Special cases
    // If both pixels are literally the same, do nothing
    if (start == end)
    {
        result.push_back(start);
        return result;
    }
    
    auto dx = end.X - start.X;
    auto dy = end.Y - start.Y;

    vector<Pixel> linePixels;

    auto addToVector = [&](int x, int y)
    {
        result.push_back(Pixel(start.X + x, start.Y + y));
    };

    linePixels = computeMidPointAlgorithm(start.X, start.Y, end.X, end.Y);

    if (abs(dy) > abs(dx))
    {
        for (auto linePixel : linePixels)
        {
            addToVector(linePixel.Y, linePixel.X);
        }
    }
    else
    {
        for (auto linePixel : linePixels)
        {
            addToVector(linePixel.X, linePixel.Y);
        }
    }

    linePixels.clear();
    linePixels.shrink_to_fit();

    return result;
}

static vector<Pixel> computeMidPointAlgorithm(int x1, int y1, int x2, int y2)
{
    vector<Pixel> result;

    auto x = 0;
    auto y = 0;

    auto dx = x2 - x1;
    auto dy = y2 - y1;

    auto dxAbs = abs(dx);
    auto dyAbs = abs(dy);

    if (dyAbs > dxAbs)
    {
        result = computeMidPointAlgorithm(y1, x1, y2, x2);
        for (auto res : result)
        {
//            swap(res.X, res.Y);
        }
        return result;
    }

    auto xInc = (dx > 0) ? 1 : -1;
    auto yInc = (dy > 0) ? 1 : -1;

    // If straight line along X axis
    if (dy == 0)
    {
        while (abs(x) < dxAbs)
        {
            result.push_back(Pixel(x, 0));
            x += xInc;
        }
        return result;
    }
    // If straight line along Y axis
    if (dx == 0)
    {
        while (abs(y) < dyAbs)
        {
            result.push_back(Pixel(0, y));
            y += yInc;
        }
        return result;
    }

    auto p = dyAbs - dxAbs / 2;
    auto incE = dyAbs;
    auto incNE = dyAbs - dxAbs;
        
    while (abs(x) < dxAbs)
    {
        if (p < 0)
        {
            p += incE;
        }
        else
        {
            y += yInc;
            p += incNE;
        }
        result.push_back(Pixel(x, y));
        x += xInc;
    }

    return result;
}

