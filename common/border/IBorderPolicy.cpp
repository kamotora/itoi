#include "IBorderPolicy.h"

double IBorderPolicy::get_pixel(ProcessingImg &image, int x, int y) {
    if (!isBorder(image, x, y))
        return image.pixel(x, y);
    return bordered_pixel(image, x, y);
}

bool IBorderPolicy::isBorder(ProcessingImg &image, int x, int y) {
    return x < 0 || y < 0 || x >= image.width() || y >= image.height();
}
