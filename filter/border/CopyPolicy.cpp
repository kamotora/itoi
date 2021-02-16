#include "CopyPolicy.h"

double CopyPolicy::getBorderedPixel(DoubleImage &image, int x, int y) {
    int resX = (x < 0) ? 0 : (x >= image.getWidth() ? image.getWidth() - 1 : x);
    int resY = (y < 0) ? 0 : (y >= image.getHeight() ? image.getHeight() - 1 : y);
    return image.getPixel(resX, resY);
}
