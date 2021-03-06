#include "IBorderPolicy.h"

double IBorderPolicy::getPixel(DoubleImage &image, int x, int y) {
    if (!isBorder(image, x, y))
        return image.getPixel(x, y);
    return getBorderedPixel(image, x, y);
}

bool IBorderPolicy::isBorder(DoubleImage &image, int x, int y) {
    return x < 0 || y < 0 || x >= image.getWidth() || y >= image.getHeight();
}
