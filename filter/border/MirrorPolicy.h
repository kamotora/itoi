//
// Created by kamotora on 14.02.2021.
//

#ifndef ITOI_MIRRORPOLICY_H
#define ITOI_MIRRORPOLICY_H


#include "IBorderPolicy.h"

class MirrorPolicy : public IBorderPolicy{
public:
    double getBorderedPixel(DoubleImage &image, int x, int y) override;
};


#endif //ITOI_MIRRORPOLICY_H
