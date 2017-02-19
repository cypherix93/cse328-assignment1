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
    };
}
