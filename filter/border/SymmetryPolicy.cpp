#include "SymmetryPolicy.h"

double SymmetryPolicy::getBorderedPixel(DoubleImage &image, int x, int y) {
    int resX = x, resY = y;
    if (x < 0)
        resX = x * -1;
    else if (x >= image.getWidth())
        resX = x - 2 * (x - image.getWidth()) - 1;
    if (y < 0)
        resY = y * -1;
    else if (y >= image.getHeight())
        resY = y - 2 * (y - image.getHeight()) - 1;
    return image.getPixel(resX, resY);
}
