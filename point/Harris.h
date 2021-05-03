//
// Created by kamotora on 30.03.2021.
//

#ifndef ITOI_HARRIS_H
#define ITOI_HARRIS_H


#include "AbstractPointsFinder.h"
#include "../filter/FilterUtil.h"

class Harris : public AbstractPointsFinder {
public:
    Harris(const shared_ptr<DoubleImage> &image, const QString &imageName, const QString &imageExt);

    Harris(const shared_ptr<DoubleImage> &image);

    vector<Point> findPoints(int pointsCount, int windowSize = 4, double tresholdCoef = 0.1) override;

    QString getMethodName() override;

    static vector<double> getEigenValues(vector<vector<double>> matrix);
};


#endif //ITOI_HARRIS_H
