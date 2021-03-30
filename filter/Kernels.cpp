#include <cmath>
#include "Kernels.h"

DoubleImage Kernels::GetSobelX() {
    return DoubleImage({
                               1.0, 0, -1.0,
                               2.0, 0, -2.0,
                               1.0, 0, -1.0
                       }, 3, 3);
}

DoubleImage Kernels::GetSobelY() {
    return DoubleImage({
                               1.0, 2.0, 1.0,
                               0.0, 0.0, 0.0,
                               -1.0, -2.0, -1.0
                       }, 3, 3);
}

pair<DoubleImage, DoubleImage> Kernels::GetSobelSeparableY() {
    return make_pair(DoubleImage({1, 2, 3}, 3, 1), DoubleImage({1, 0, -1}, 1, 3));
}


DoubleImage Kernels::GetIncreaseSharpness() {
    return DoubleImage({
                               -1.0, -1.0, -1.0,
                               -1.0, 9.0, -1.0,
                               -1.0, -1.0, -1.0
                       }, 3, 3);
}

DoubleImage Kernels::GetGauss(double sigma, bool isNeedNormalize) {
    auto halfSize = static_cast<int>(sigma * 3);
    int size = 2 * halfSize + 1;
    auto matrix_gauss = vector<double>(size * size);
    double normalize = 0.0;
    for (int x = -halfSize, i = 0; x <= halfSize; x++, i++) {
        for (int y = -halfSize, j = 0; y <= halfSize; y++, j++) {
            auto value = GetGaussKernelValue(x, y, sigma);
            matrix_gauss[i * size + j] = value;
            normalize += value;
        }
    }
    if (isNeedNormalize) {
        for (int i = 0; i < size * size; i++)
            matrix_gauss[i] /= normalize;
    }

    return DoubleImage(matrix_gauss, size, size);
}

//DoubleImage Kernels::GetGauss(double sigma, int radius, bool normalize) {
//    double coeff = 1 / (2 * M_PI * sigma * sigma);
//    double divider = 2 * sigma * sigma;
//    double sum = 1;
//    // -radius .. 0 .. radius
//    // 2 radius + point at 0, so + 1
//    int w = (2 * radius) + 1;
//    int h = (2 * radius) + 1;
//    auto matrix_gauss = vector<double>(w * h);
//    int k = 0;
//    for (int u = -radius; u <= radius; u++) {
//        //qDebug() << "U :" << u << ' ';
//        for (int v = -radius; v <= radius; v++) {
//            double gaussValue = coeff * exp(-(u * u + v * v) / divider);
//            matrix_gauss[k++] = gaussValue;
//            sum += gaussValue;
//
//        }
//        //qDebug() << "Size gauss::" << k << endl;
//        //qDebug() << "radius gauss::" << radius << endl;
//    }
//    if (normalize)
//        for (int i = 0; i < w * h; ++i)
//            matrix_gauss[i] /= sum;
//    return DoubleImage(matrix_gauss, w, h);
//}

pair<DoubleImage, DoubleImage> Kernels::GetGaussSeparableXY(double sigma, bool normalize) {
    auto kernel = GetGaussSeparableX(sigma, normalize);
    return make_pair(DoubleImage(kernel, kernel.size(), 1), DoubleImage(kernel, 1, kernel.size()));
}

double Kernels::GetGaussKernelValue(int x, int y, double sigma) {
    auto ss2 = sigma * sigma * 2;
    auto top = exp(-(x * x + y * y) / (ss2));
    auto bottom = M_PI * ss2;
    return top / bottom;
}

vector<double> Kernels::GetGaussSeparableX(double sigma, bool normalize) {
    int halfSize = static_cast<int>(sigma) * 3;
    int size = 2 * halfSize + 1;
    auto row = vector<double>(size);
    double sum = 0.0;
    auto ss2 = sigma * sigma * 2;
    for (int i = -halfSize, k = 0; i <= halfSize; i++, k++) {
        double value = exp(-(i * i) / ss2) / (M_PI * ss2);
//        auto value = GetGaussKernelValue(i, halfSize, sigma);
        row[k] = value;
        sum += value;
    }
    if (normalize)
        for (int i = 0; i < size; ++i)
            row[i] /= sum;
    return row;
}
