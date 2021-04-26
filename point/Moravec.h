#ifndef ITOI_MORAVEC_H
#define ITOI_MORAVEC_H


#include "AbstractPointsFinder.h"
#include "../filter/FilterUtil.h"

class Moravec : public AbstractPointsFinder {
public:
    vector<Point> findPoints(int windowSize, int pointsCount, double tresholdCoef) override;

    Moravec(const shared_ptr<DoubleImage> &image, const QString &imageName, const QString &imageExt);

    QString getMethodName() override;
};


#endif //ITOI_MORAVEC_H
