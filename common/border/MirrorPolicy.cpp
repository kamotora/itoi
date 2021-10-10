#include "MirrorPolicy.h"

double MirrorPolicy::bordered_pixel(ProcessingImg &image, int x, int y) {
    x = abs(x);
    y = abs(y);
    if (x >= image.get_width()) x = image.get_width() - (x - image.get_width() + 1);
    if (y >= image.get_height()) y = image.get_height() - (y - image.get_height() + 1);
    return image.get_pixel(x, y);
}

QString MirrorPolicy::to_string() {
    return "mirrorBorderPolicy";
}
