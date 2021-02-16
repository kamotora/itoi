#ifndef ITOI_IBORDERPOLICY_H
#define ITOI_IBORDERPOLICY_H

#include "memory"
#include "../../core/DoubleImage.h"

using namespace std;

class IBorderPolicy {
protected:
    static IBorderPolicy *borderPolicy;
    static bool isBorder(DoubleImage &image, int x, int y);
    IBorderPolicy() = default;

public:
    double getPixel(DoubleImage &image, int x, int y);
    //todo protected
    virtual double getBorderedPixel(DoubleImage &image, int x, int y) = 0;
};


#endif //ITOI_IBORDERPOLICY_H
