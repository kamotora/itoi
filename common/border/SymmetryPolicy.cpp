#include "SymmetryPolicy.h"

double SymmetryPolicy::bordered_pixel(ProcessingImg &image, int x, int y) {
    int resX = x, resY = y;
    if (x < 0)
        resX = x * -1;
    else if (x >= image.width())
        resX = x - 2 * (x - image.width()) - 1;
    if (y < 0)
        resY = y * -1;
    else if (y >= image.height())
        resY = y - 2 * (y - image.height()) - 1;
    return image.pixel(resX, resY);
}

