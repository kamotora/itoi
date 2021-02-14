#include "ZeroPolicy.h"

double ZeroPolicy::getBorderedPixel(DoubleImage &image, int x, int y) {
    x = (x < 0) ? 0 : (x > image.getWidth() ? image.getWidth() : x);
    y = (y < 0) ? 0 : (y > image.getHeight() ? image.getHeight() : y);
    return image.getPixel(x, y);
}
