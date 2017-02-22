#include "Pixel.h"

using namespace Drawing;

Pixel::Pixel(int x, int y)
{
    X = x;
    Y = y;
}

Pixel::~Pixel()
{
}

bool Pixel::IsNearPoint(int x, int y, int threshold) const
{
    return
        (X - threshold < x) && (x < X + threshold) &&
        (Y - threshold < y) && (y < Y + threshold);
}

bool Drawing::operator==(const Pixel left, const Pixel right)
{
    return left.X == right.X && left.Y == right.Y;
}

bool Drawing::operator!=(const Pixel left, const Pixel right)
{
    return !(left == right);
}
