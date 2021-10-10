#ifndef ITOI_MORAVEC_H
#define ITOI_MORAVEC_H


#include "AbstractInterestPointsAlgo.h"
#include "../common/Filter.h"

class Moravec : public AbstractInterestPointsAlgo {
private:
    vector<int> dx{-1, 0, 1, -1, 1, -1, 0, -1};
    vector<int> dy{-1, -1, -1, 0, 0, 1, 1, 1};

public:
    vector<Point> find_points(int pointsCount, int windowSize, double tresholdCoef) override;

    Moravec(const shared_ptr<ProcessingImg> &image, const QString &imageName, const QString &imageExt);

    QString method_name() override;
};


#endif //ITOI_MORAVEC_H
