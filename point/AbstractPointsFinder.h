#ifndef ITOI_ABSTRACTPOINTSFINDER_H
#define ITOI_ABSTRACTPOINTSFINDER_H

#include "vector"
#include "Point.h"
#include "../core/DoubleImage.h"
#include "../filter/border/CopyPolicy.h"
#include "../core/DoubleImageBorderPolicy.h"

using namespace std;

class AbstractPointsFinder {
protected:
    shared_ptr<DoubleImage> image;
    constexpr static CopyPolicy DEFAULT_POLICY = CopyPolicy();
    pair<int, int> round(int x, int y);
    double getPixelWithBorderPolicy(int x, int y, IBorderPolicy &borderPolicy = (IBorderPolicy &) DEFAULT_POLICY) const;
    void setPoint(int x, int y, const shared_ptr<DoubleImage>& sharedPtr);
public:
    explicit AbstractPointsFinder(const shared_ptr<DoubleImage> &image);
    virtual vector<Point> findPoints(int windowSize, int pointsCount) = 0;
    vector<Point> localMaximum(vector<Point> &points, int windowSize, double thresholdCoeff = 0.005);
    static vector<Point> filter(vector<Point> &points, int pointsCount, int maxSize);
    shared_ptr<DoubleImage> setPoints(vector<Point> &points);
};


#endif //ITOI_ABSTRACTPOINTSFINDER_H
