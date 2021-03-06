#include "helper.h"

unsigned char Helper::toGrayscale(const QColor &rgbPixel) {
    auto result = 0.213 * rgbPixel.red() + 0.715 * rgbPixel.green() + 0.072 * rgbPixel.blue();
    return result;
}

unique_ptr<double[]> Helper::normalizeMinMax(const unique_ptr<double[]> &data, int size, double newDiff) {
    double max = data[0];
    double min = data[0];
    for (int i = 0; i < size; i++) {
        if (data[i] < min) min = data[i];
        if (data[i] > max) max = data[i];
    }
    // normalizing
    auto res = make_unique<double[]>(size);
    for (int i = 0; i < size; i++) {
        res[i] = (data[i] - min) * (newDiff / (max - min));
    }
    return res;
}

double Helper::sqr(double value) {
    return value * value;
}

double Helper::simpleRound(double value) {
    return (value < 0) ? 0 : (value >= 255 ? 255 : value);
}

int Helper::simpleRound(int value) {
    return (value < 0) ? 0 : (value >= 255 ? 255 : value);
}

int Helper::sign(double value){
    if (value > 0) return 1;
    if (value < 0) return -1;
    return 0;
}