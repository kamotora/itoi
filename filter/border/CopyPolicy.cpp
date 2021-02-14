#include "CopyPolicy.h"

double CopyPolicy::getBorderedPixel(DoubleImage &image, int x, int y) {
    x = (x < 0) ? 0 : (x >= image.getWidth() ? image.getWidth() - 1 : x);
    y = (y < 0) ? 0 : (y >= image.getHeight() ? image.getHeight() - 1 : y);
    return image.getPixel(x, y);
}
