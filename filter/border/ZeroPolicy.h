#ifndef ITOI_ZEROPOLICY_H
#define ITOI_ZEROPOLICY_H


#include "IBorderPolicy.h"

class ZeroPolicy: public IBorderPolicy {
public:
    double getBorderedPixel(DoubleImage &image, int x, int y) override;
};


#endif //ITOI_ZEROPOLICY_H
