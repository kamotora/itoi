#include "ZeroPolicy.h"

double ZeroPolicy::bordered_pixel(ProcessingImg &image, int x, int y) {
    if(x < 0 || x >= image.width() || y < 0 || y >= image.height())
        return 0;
    return image.pixel(x, y);
}

