//
// Created by kamotora on 29.04.2021.
//

#ifndef ITOI_DESCRIPTORUTIL_H
#define ITOI_DESCRIPTORUTIL_H

#include <QImage>
#include "../core/DoubleImage.h"
#include "../core/helper.h"
#include "../filter/FilterUtil.h"
#include "PatchDescriptor.h"
#include "MatchInfo.h"
#include "cmath"
#include "../core/InputImage.h"
#include <QPainter>

using namespace std;

class DescriptorUtil {
private:

    static void setPoint(int x, int y, QImage &image);

    static pair<int, int> round(int x, int y, QImage &image);

    static void drawPlus(const Point &item, QImage &image);

    static shared_ptr<DoubleImage>
    getGradient(const shared_ptr<DoubleImage> &first, const shared_ptr<DoubleImage> &second,
                double (*counterFunc)(double, double));

    static int getMinIndex(vector<double> distances, int excludeIndex);

public:
    static shared_ptr<DoubleImage>
    getGradientAngle(const shared_ptr<DoubleImage> &first, const shared_ptr<DoubleImage> &second);

    static shared_ptr<DoubleImage>
    getGradient(const shared_ptr<DoubleImage> &first, const shared_ptr<DoubleImage> &second);


    static shared_ptr<DoubleImage> getGradient(const shared_ptr<DoubleImage> &image, bool normalize = true);

    static shared_ptr<AbstractDescriptor>
    getClosest(const shared_ptr<AbstractDescriptor> &descriptor,
               const vector<shared_ptr<AbstractDescriptor>> &descriptors,
               bool showAll = false);

    static shared_ptr<MatchInfo>
    match(const vector<shared_ptr<AbstractDescriptor>> &firstList,
          const vector<shared_ptr<AbstractDescriptor>> &secondList,
          bool showAll = false);

    static QImage markPoints(const vector<Point> &points, const QImage &image);

    static QImage markPoints(const vector<shared_ptr<AbstractDescriptor>> &descriptors, const QImage &image);

    static QImage markMatching(const shared_ptr<DoubleImage> &imageA, const shared_ptr<DoubleImage> &imageB,
                               const shared_ptr<MatchInfo> &matchInfo);

    static void drawPointWithAngle(const Point &point, QImage &image);
};


#endif //ITOI_DESCRIPTORUTIL_H
