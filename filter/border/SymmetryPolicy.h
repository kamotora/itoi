#ifndef ITOI_SYMMETRYPOLICY_H
#define ITOI_SYMMETRYPOLICY_H


#include "IBorderPolicy.h"

class SymmetryPolicy: public IBorderPolicy {
protected:
    double getBorderedPixel(DoubleImage &image, int x, int y) override;

public:
    QString toString() override;
};


#endif //ITOI_SYMMETRYPOLICY_H
