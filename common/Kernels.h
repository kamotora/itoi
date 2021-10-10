#ifndef IP_KERNELSHANDLER_H
#define IP_KERNELSHANDLER_H

#include "ProcessingImg.h"

class Kernels {
private:
    static vector<double> gauss_separable_x(int halfSize, double sigma, bool normalize);
    static pair<ProcessingImg, ProcessingImg> separable_from_kernel(const vector<double> &kernel);
public:
    static ProcessingImg sobel_x();

    static ProcessingImg sobel_y();

    static ProcessingImg get_gauss(double sigma, bool isNeedNormalize = false);

    static pair<ProcessingImg, ProcessingImg> get_gauss_separable_xy(double sigma, bool normalize = true);

    static pair<ProcessingImg, ProcessingImg> sobel_separable_x();

    static pair<ProcessingImg, ProcessingImg> sobel_separable_y();

    static double gauss_kernel_value(int x, int y, double sigma);

    static pair<ProcessingImg, ProcessingImg> gauss_separable_xy(int halfSize, bool normalize = true);

    static ProcessingImg get_gauss(int halfSize, bool isNeedNormalize = true);
};


#endif //IP_KERNELSHANDLER_H
