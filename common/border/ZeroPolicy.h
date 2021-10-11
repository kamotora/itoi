#ifndef ITOI_ZEROPOLICY_H
#define ITOI_ZEROPOLICY_H


#include "IBorderPolicy.h"

class ZeroPolicy: public IBorderPolicy {
protected:
    double bordered_pixel(ProcessingImg &image, int x, int y) override;

};


#endif //ITOI_ZEROPOLICY_H