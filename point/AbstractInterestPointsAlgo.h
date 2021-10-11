#ifndef ITOI_ABSTRACTINTERESTPOINTSALGO_H
#define ITOI_ABSTRACTINTERESTPOINTSALGO_H

#include "vector"
#include "Point.h"
#include "../common/ProcessingImg.h"
#include "../common/border/CopyPolicy.h"
#include "../common/LoadedImg.h"
#include "../common/border/MirrorPolicy.h"

using namespace std;

class AbstractInterestPointsAlgo {
protected:
    shared_ptr<ProcessingImg> image;
    QString imageName, imageExt;
    constexpr static MirrorPolicy DEFAULT_POLICY = MirrorPolicy();

    pair<int, int> round(int x, int y);

    double getPixelWithBorderPolicy(int x, int y, IBorderPolicy &borderPolicy = (IBorderPolicy &) DEFAULT_POLICY) const;

    void setPoint(int x, int y, const shared_ptr<ProcessingImg> &sharedPtr);

public:
    /**
     * Чтобы сохранить промежуточные результаты, нужно указать imageName и imageExt
     */
    explicit AbstractInterestPointsAlgo(const shared_ptr<ProcessingImg> &image,
                                        const QString &imageName = QString::null,
                                        const QString &imageExt = QString::null);

    virtual vector<Point> find_points(int pointsCount, int windowSize, double treshold = 0.1) = 0;

    virtual QString method_name() = 0;

    vector<Point> localMaximum(double thresholdCoeff);

    shared_ptr<ProcessingImg> setPoints(vector<Point> &points);

    void drawPoints(vector<Point> &points, const QString &name);

    void saveImage(const shared_ptr<ProcessingImg> &outputImage, const QString &nameSuffix);

    static vector<Point> filter(vector<Point> &points, double radius);

    static vector<Point> filter(vector<Point> &points, int pointsCount);
};


#endif //ITOI_ABSTRACTINTERESTPOINTSALGO_H
