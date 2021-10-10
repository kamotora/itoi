#include "ZeroPolicy.h"

double ZeroPolicy::bordered_pixel(ProcessingImg &image, int x, int y) {
    if(x < 0 || x >= image.get_width() || y < 0 || y >= image.get_height())
        return 0;
    return image.get_pixel(x, y);
}

QString ZeroPolicy::to_string() {
    return "zeroBorderPolicy";
}
