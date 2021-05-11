#ifndef ITOI_ABSTRACTPOINTSFINDER_H
#define ITOI_ABSTRACTPOINTSFINDER_H

#include "vector"
#include "Point.h"
#include "../core/DoubleImage.h"
#include "../filter/border/CopyPolicy.h"
#include "../core/DoubleImageBorderPolicy.h"
#include "../core/InputImage.h"

using namespace std;

class AbstractPointsFinder {
protected:
    shared_ptr<DoubleImage> image;
    QString imageName, imageExt;
    constexpr static MirrorPolicy DEFAULT_POLICY = MirrorPolicy();

    pair<int, int> round(int x, int y);

    double getPixelWithBorderPolicy(int x, int y, IBorderPolicy &borderPolicy = (IBorderPolicy &) DEFAULT_POLICY) const;

    void setPoint(int x, int y, const shared_ptr<DoubleImage> &sharedPtr);

public:
    explicit AbstractPointsFinder(const shared_ptr<DoubleImage> &image, const QString &imageName = QString::null,
                                  const QString &imageExt = QString::null);

    virtual vector<Point> findPoints(int pointsCount, int windowSize, double tresholdCoef = 0.1) = 0;

    virtual QString getMethodName() = 0;

    vector<Point> localMaximum(double thresholdCoeff);

    shared_ptr<DoubleImage> setPoints(vector<Point> &points);

    void drawPoints(vector<Point> &points, const QString &name);

    void saveImage(const shared_ptr<DoubleImage> &outputImage, const QString &nameSuffix);

    static vector<Point> filter(vector<Point> &points, double radius);

    static vector<Point> filter(vector<Point> &points, int pointsCount);
};


#endif //ITOI_ABSTRACTPOINTSFINDER_H
