#include "ZeroPolicy.h"

double ZeroPolicy::getBorderedPixel(DoubleImage &image, int x, int y) {
    if(x < 0 || x >= image.getWidth() || y < 0 || y >= image.getHeight())
        return 0;
    return image.getPixel(x, y);
}

QString ZeroPolicy::toString() {
    return "zeroBorderPolicy";
}
