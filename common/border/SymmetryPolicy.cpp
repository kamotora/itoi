#include "SymmetryPolicy.h"

double SymmetryPolicy::bordered_pixel(ProcessingImg &image, int x, int y) {
    int resX = x, resY = y;
    if (x < 0)
        resX = x * -1;
    else if (x >= image.get_width())
        resX = x - 2 * (x - image.get_width()) - 1;
    if (y < 0)
        resY = y * -1;
    else if (y >= image.get_height())
        resY = y - 2 * (y - image.get_height()) - 1;
    return image.get_pixel(resX, resY);
}

QString SymmetryPolicy::to_string() {
    return "symmetryBorderPolicy";
}
