#include "ScanConverter.h"

static map<int, vector<int>> SortDrawnPixels(vector<Pixel>);

vector<Pixel> Drawing::GetScanConvertedPixels(vector<Pixel> linePixels)
{
    vector<Pixel> result;

    auto groupedCoords = SortDrawnPixels(linePixels);

    // Loop through the group
    for (auto group : groupedCoords)
    {
        auto vec = group.second;

        auto y = group.first;
        auto startX = *min_element(vec.begin(), vec.end());
        auto endX = *max_element(vec.begin(), vec.end());

        for (auto x = startX; x <= endX; x++)
        {
            result.push_back(Pixel(x, y));
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
            auto vec = val->second;

            // Insert X into the vector if it already doesnt exist
            if (find(vec.begin(), vec.end(), pixel.X) == vec.end())
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
