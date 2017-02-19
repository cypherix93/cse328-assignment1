#pragma once
#include <vector>
#include <algorithm>
#include "../Pixel/Pixel.h"

using namespace std;
using namespace Drawing;

namespace Drawing
{
    vector<Pixel> GetLinePixelsFromVertices(vector<Pixel> vertices);

    vector<Pixel> GetSingleLinePixels(Pixel, Pixel);
}

