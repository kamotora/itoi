#include "MirrorPolicy.h"

double MirrorPolicy::getBorderedPixel(DoubleImage &image, int x, int y) {
    x = abs(x);
    y = abs(y);
    if (x >= image.getWidth()) x = image.getWidth() - (x - image.getWidth() + 1);
    if (y >= image.getHeight()) y = image.getHeight() - (y - image.getHeight() + 1);
    return image.getPixel(x, y);
}

QString MirrorPolicy::toString() {
    return "mirrorBorderPolicy";
}
