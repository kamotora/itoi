#ifndef ITOI_MIRRORPOLICY_H
#define ITOI_MIRRORPOLICY_H

#include "IBorderPolicy.h"

class MirrorPolicy : public IBorderPolicy{
protected:
    double getBorderedPixel(DoubleImage &image, int x, int y) override;

public:
    QString toString() override;
};


#endif //ITOI_MIRRORPOLICY_H
