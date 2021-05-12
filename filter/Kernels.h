#ifndef IP_KERNELSHANDLER_H
#define IP_KERNELSHANDLER_H

#include "../core/DoubleImage.h"

class Kernels {
private:
    static vector<double> GetGaussSeparableX(int halfSize, double sigma, bool normalize);
    static pair<DoubleImage, DoubleImage> GetSeparableFromKernel(const vector<double> &kernel);
public:
    static DoubleImage GetSobelX();

    static DoubleImage GetSobelY();

    static DoubleImage GetIncreaseSharpness();

    static DoubleImage GetGauss(double sigma, bool isNeedNormalize = false);

    static pair<DoubleImage, DoubleImage> GetGaussSeparableXY(double sigma, bool normalize = true);

    static pair<DoubleImage, DoubleImage> GetSobelSeparableX();

    static pair<DoubleImage, DoubleImage> GetSobelSeparableY();

    static double GetGaussKernelValue(int x, int y, double sigma);

    static pair<DoubleImage, DoubleImage> GetGaussSeparableXY(int halfSize, bool normalize = true);

    static DoubleImage GetGauss(int halfSize, bool isNeedNormalize = true);
};


#endif //IP_KERNELSHANDLER_H
