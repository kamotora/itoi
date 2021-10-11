#ifndef ITOI_SYMMETRYPOLICY_H
#define ITOI_SYMMETRYPOLICY_H


#include "IBorderPolicy.h"

class SymmetryPolicy: public IBorderPolicy {
protected:
    double bordered_pixel(ProcessingImg &image, int x, int y) override;

};


#endif //ITOI_SYMMETRYPOLICY_H