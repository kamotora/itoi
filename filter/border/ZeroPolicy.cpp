#include "ZeroPolicy.h"

double ZeroPolicy::getBorderedPixel(DoubleImage &image, int x, int y) {
    int resX = (x < 0) ? 0 : (x > image.getWidth() ? image.getWidth() : x);
    int resY = (y < 0) ? 0 : (y > image.getHeight() ? image.getHeight() : y);
    return image.getPixel(resX, resY);
}
