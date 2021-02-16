#ifndef IP_KERNELSHANDLER_H
#define IP_KERNELSHANDLER_H

#include "../core/DoubleImage.h"

class Kernels {
public:
    static DoubleImage GetSobelX();

    static DoubleImage GetSobelY();

    static DoubleImage GetIncreaseSharpness();

    static DoubleImage GetGauss(double sigma);

    static DoubleImage GetGauss(double sigma, int radius, bool normalize = false);
};


#endif //IP_KERNELSHANDLER_H
