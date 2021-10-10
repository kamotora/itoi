#include "CopyPolicy.h"

double CopyPolicy::bordered_pixel(ProcessingImg &image, int x, int y) {
    int resX = (x < 0) ? 0 : (x >= image.width() ? image.width() - 1 : x);
    int resY = (y < 0) ? 0 : (y >= image.height() ? image.height() - 1 : y);
    return image.pixel(resX, resY);
}

