#ifndef ITOI_SYMMETRYPOLICY_H
#define ITOI_SYMMETRYPOLICY_H


#include "IBorderPolicy.h"

class SymmetryPolicy: public IBorderPolicy {
public:
    double getBorderedPixel(DoubleImage &image, int x, int y) override;
};


#endif //ITOI_SYMMETRYPOLICY_H
