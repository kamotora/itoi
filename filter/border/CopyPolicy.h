#ifndef ITOI_COPYPOLICY_H
#define ITOI_COPYPOLICY_H


#include "IBorderPolicy.h"

class CopyPolicy : public IBorderPolicy {
public:
    double getBorderedPixel(DoubleImage &image, int x, int y) override;
};


#endif //ITOI_COPYPOLICY_H
