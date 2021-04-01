#ifndef ITOI_MORAVEC_H
#define ITOI_MORAVEC_H


#include "AbstractPointsFinder.h"
#include "../filter/FilterUtil.h"

class Moravec : public AbstractPointsFinder {
public:
    Moravec(const shared_ptr<DoubleImage> &image);

    vector<Point> findPoints(int windowSize, int pointsCount) override;
};


#endif //ITOI_MORAVEC_H
