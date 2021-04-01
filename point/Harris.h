//
// Created by kamotora on 30.03.2021.
//

#ifndef ITOI_HARRIS_H
#define ITOI_HARRIS_H


#include "AbstractPointsFinder.h"
#include "../filter/FilterUtil.h"

class Harris : public AbstractPointsFinder {
public:
    Harris(const shared_ptr<struct DoubleImage>& sharedPtr);

    vector<Point> findPoints(int windowSize, int pointsCount) override;
};


#endif //ITOI_HARRIS_H
