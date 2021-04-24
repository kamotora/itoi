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
    constexpr static CopyPolicy DEFAULT_POLICY = CopyPolicy();
    pair<int, int> round(int x, int y);
    double getPixelWithBorderPolicy(int x, int y, IBorderPolicy &borderPolicy = (IBorderPolicy &) DEFAULT_POLICY) const;
    void setPoint(int x, int y, const shared_ptr<DoubleImage>& sharedPtr);
public:
    explicit AbstractPointsFinder(const shared_ptr<DoubleImage> &image, const QString& imageName, const QString& imageExt);
    virtual vector<Point> findPoints(int windowSize, int pointsCount, double tresholdCoef = 0.005) = 0;
    virtual QString getMethodName() = 0;
    vector<Point> localMaximum(int windowSize, double thresholdCoeff);
    static vector<Point> filter(vector<Point> &points, int pointsCount, int maxSize);
    shared_ptr<DoubleImage> setPoints(vector<Point> &points);

    void drawPoints(vector<Point> &points, const QString &name);
    void saveImage(const shared_ptr<DoubleImage> &outputImage, const QString &nameSuffix);
};


#endif //ITOI_ABSTRACTPOINTSFINDER_H
