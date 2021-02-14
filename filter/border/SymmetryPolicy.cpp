#include "SymmetryPolicy.h"

double SymmetryPolicy::getBorderedPixel(DoubleImage &image, int x, int y) {
    if (x < 0)
        x *= -1;
    else if (x >= image.getWidth())
        x -= 2 * (x - image.getWidth());
    if (y < 0)
        y *= -1;
    else if (y >= image.getHeight())
        y -= 2 * (y - image.getHeight());
    return image.getPixel(x, y);
}
