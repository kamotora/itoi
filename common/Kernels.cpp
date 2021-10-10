#include <cmath>
#include "Kernels.h"

ProcessingImg Kernels::sobel_x() {
    return ProcessingImg({
                               1.0, 0, -1.0,
                               2.0, 0, -2.0,
                               1.0, 0, -1.0
                       }, 3, 3);
}

ProcessingImg Kernels::sobel_y() {
    return ProcessingImg({
                               1.0, 2.0, 1.0,
                               0.0, 0.0, 0.0,
                               -1.0, -2.0, -1.0
                       }, 3, 3);
}

pair<ProcessingImg, ProcessingImg> Kernels::sobel_separable_y() {
    return make_pair(ProcessingImg({1, 0, -1}, 3, 1), ProcessingImg({1, 2, 1}, 1, 3));
}

pair<ProcessingImg, ProcessingImg> Kernels::sobel_separable_x() {
    return make_pair(ProcessingImg({1, 2, 1}, 3, 1), ProcessingImg({1, 0, -1}, 1, 3));
}


ProcessingImg Kernels::get_gauss(int halfSize, bool isNeedNormalize) {
    return get_gauss(halfSize / 3.0, isNeedNormalize);
}

ProcessingImg Kernels::get_gauss(double sigma, bool isNeedNormalize) {
    auto halfSize = static_cast<int>(sigma * 3);
    int size = 2 * halfSize + 1;
    auto matrix_gauss = vector<double>(size * size);
    double normalize = 0.0;
    for (int x = -halfSize, i = 0; x <= halfSize; x++, i++) {
        for (int y = -halfSize, j = 0; y <= halfSize; y++, j++) {
            auto value = gauss_kernel_value(x, y, sigma);
            matrix_gauss[i * size + j] = value;
            normalize += value;
        }
    }
    if (isNeedNormalize) {
        for (int i = 0; i < size * size; i++)
            matrix_gauss[i] /= normalize;
    }

    return ProcessingImg(matrix_gauss, size, size);
}

pair<ProcessingImg, ProcessingImg> Kernels::get_gauss_separable_xy(double sigma, bool normalize) {
    auto kernel = gauss_separable_x(ceil(3 * sigma), sigma, normalize);
    return separable_from_kernel(kernel);
}

pair<ProcessingImg, ProcessingImg> Kernels::gauss_separable_xy(int halfSize, bool normalize) {
    auto kernel = gauss_separable_x(halfSize, halfSize / 3.0, normalize);
    return separable_from_kernel(kernel);
}

pair<ProcessingImg, ProcessingImg> Kernels::separable_from_kernel(const vector<double> &kernel) {
    int size = kernel.size();
    return make_pair(ProcessingImg(kernel, size, 1), ProcessingImg(kernel, 1, size));
}

double Kernels::gauss_kernel_value(int x, int y, double sigma) {
    auto ss2 = sigma * sigma * 2;
    auto top = exp(-(x * x + y * y) / (ss2));
    auto bottom = M_PI * ss2;
    return top / bottom;
}

vector<double> Kernels::gauss_separable_x(int halfSize, double sigma, bool normalize) {
    auto size = halfSize * 2 + 1;
    auto row = vector<double>(size);
    double coef = 1 / (sqrt(2 * M_PI) * sigma);
    for (int x = -halfSize; x <= halfSize; x++) {
        row[x + halfSize] = coef * exp(-(x * x) / (2 * (sigma * sigma)));
    }
    double sum = 0;
    for (int i = 0; i < size; i++) {
        sum += row[i];
    }
    if (normalize)
        for (int i = 0; i < size; i++) {
            row[i] /= sum;
        }
    return row;
}