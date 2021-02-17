#ifndef ITOI_IBORDERPOLICY_H
#define ITOI_IBORDERPOLICY_H

#include "memory"
#include "../../core/DoubleImage.h"

using namespace std;

class IBorderPolicy {
protected:
    static bool isBorder(DoubleImage &image, int x, int y);
    IBorderPolicy() = default;

    virtual double getBorderedPixel(DoubleImage &image, int x, int y) = 0;
public:
    double getPixel(DoubleImage &image, int x, int y);
    virtual QString toString() = 0;
};


#endif //ITOI_IBORDERPOLICY_H
