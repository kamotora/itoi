#ifndef IP_KERNELSHANDLER_H
#define IP_KERNELSHANDLER_H

#include "../core/DoubleImage.h"

class Kernels {
public:
    static DoubleImage GetSobelX();

    static DoubleImage GetSobelY();

    static DoubleImage GetIncreaseSharpness();

    static DoubleImage GetGauss(double sigma, bool isNeedNormalize = false);
    static vector<double> GetGaussSeparableX(double sigma, bool normalize  = false);

    static pair<DoubleImage, DoubleImage> GetGaussSeparableXY(double sigma, bool normalize = false);

    static pair<DoubleImage, DoubleImage> GetSobelSeparableY();

    static double GetGaussKernelValue(int x, int y, double sigma);
};


#endif //IP_KERNELSHANDLER_H
