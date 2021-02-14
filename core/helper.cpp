#include "helper.h"

unsigned char Helper::toSRGB(const QColor &rgbPixel) {
    auto result = 0.213 * rgbPixel.red() + 0.715 * rgbPixel.green() + 0.072 * rgbPixel.blue();
    return result;
}

//todo разобраться, где применяется
void Helper::normalizeMinMax(unique_ptr<double[]> data, int size) {
    double max = data[0];
    double min = data[0];
    for (int i = 0; i < size; i++) {
        if (data[i] < min) min = data[i];
        if (data[i] > max) max = data[i];
    }
    // normalizing
    for (int i = 0; i < size; i++) {
        data[i] = (data[i] - min) * (1.0 / (max - min));
    }
}