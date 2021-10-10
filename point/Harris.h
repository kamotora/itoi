#ifndef ITOI_HARRIS_H
#define ITOI_HARRIS_H


#include "AbstractInterestPointsAlgo.h"
#include "../common/Filter.h"

class Harris : public AbstractInterestPointsAlgo {
public:
    Harris(const shared_ptr<ProcessingImg> &image, const QString &imageName, const QString &imageExt);

    Harris(const shared_ptr<ProcessingImg> &image);

    vector<Point> find_points(int pointsCount, int windowSize = 4, double tresholdCoef = 0.05) override;

    QString method_name() override;

    static vector<double> eigen_values(vector<vector<double>> matrix);
};


#endif //ITOI_HARRIS_H
