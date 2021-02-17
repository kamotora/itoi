#ifndef ITOI_COPYPOLICY_H
#define ITOI_COPYPOLICY_H


#include "IBorderPolicy.h"

class CopyPolicy : public IBorderPolicy {
protected:
    double getBorderedPixel(DoubleImage &image, int x, int y) override;
public:
    QString toString() override;
};


#endif //ITOI_COPYPOLICY_H
