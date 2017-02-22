#pragma once

namespace Drawing
{
    class Pixel
    {
        public:
        Pixel(int x, int y);
        virtual ~Pixel();

        int X;
        int Y;

        bool IsNearPoint(int x, int y, int threshold = 4) const;
    };

    bool operator==(const Pixel left, const Pixel right);
    bool operator!=(const Pixel left, const Pixel right);
}
