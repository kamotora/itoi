#include "MirrorPolicy.h"

double MirrorPolicy::bordered_pixel(ProcessingImg &image, int x, int y) {
    x = abs(x);
    y = abs(y);
    if (x >= image.width()) x = image.width() - (x - image.width() + 1);
    if (y >= image.height()) y = image.height() - (y - image.height() + 1);
    return image.pixel(x, y);
}

