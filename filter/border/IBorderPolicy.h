#ifndef ITOI_IBORDERPOLICY_H
#define ITOI_IBORDERPOLICY_H

#include "memory"
#include "../../core/DoubleImage.h"

using namespace std;

class IBorderPolicy {
protected:
    static bool isBorder(DoubleImage &image, int x, int y);
public:
    double getPixel(DoubleImage &image, int x, int y);

    virtual double getBorderedPixel(DoubleImage &image, int x, int y);
};


#endif //ITOI_IBORDERPOLICY_H
