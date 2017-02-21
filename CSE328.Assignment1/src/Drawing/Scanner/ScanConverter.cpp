#include "ScanConverter.h"

static map<int, vector<int>> SortDrawnPixels(vector<Pixel>);

vector<Pixel> Drawing::GetScanConvertedPixels(vector<Pixel> linePixels)
{
    vector<Pixel> result;

    auto groupedCoords = SortDrawnPixels(linePixels);

    // Loop through the group
    for (auto group : groupedCoords)
    {
        auto size = group.second.size();

        // X values should be sorted already, so let's loop over them in pairs and insert pixels
        for (auto i = 0; i < size - 1; i += 2)
        {
            auto startX = group.second[i];
            auto endX = group.second[i + 1];

            // If they are adjacent, we skip this current one
            if (endX - startX == 1)
            {
                i--;
                continue;
            }

            auto y = group.first;

            for (auto x = startX; x <= endX; x++)
            {
                result.push_back(Pixel(x, y));
            }
        }
    }

    return result;
}

static map<int, vector<int>> SortDrawnPixels(vector<Pixel> pixels)
{
    map<int, vector<int>> result;

    for (auto pixel : pixels)
    {
        auto val = result.find(pixel.Y);

        // If map already exists, then append the X value to the X list
        if (val != result.end())
        {
            val->second.push_back(pixel.X);
        }
        else
        {
            result.insert(pair<int, vector<int>>(pixel.Y, { pixel.X }));
        }
    }

    // Sort the X values in each Y group
    for (auto &group : result)
    {
        sort(group.second.begin(), group.second.end());
    }

    return result;
}
