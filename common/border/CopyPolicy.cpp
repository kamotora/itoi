#include "CopyPolicy.h"

double CopyPolicy::bordered_pixel(ProcessingImg &image, int x, int y) {
    int resX = (x < 0) ? 0 : (x >= image.get_width() ? image.get_width() - 1 : x);
    int resY = (y < 0) ? 0 : (y >= image.get_height() ? image.get_height() - 1 : y);
    return image.get_pixel(resX, resY);
}

QString CopyPolicy::to_string() {
    return "copyBorderPolicy";
}
