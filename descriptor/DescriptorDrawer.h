#ifndef ITOI_DESCRIPTORDRAWER_H
#define ITOI_DESCRIPTORDRAWER_H


#include <QImage>
#include "../common/ProcessingImg.h"

#include "../common/Filter.h"
#include "DescriptorPair.h"
#include "cmath"
#include "../common/LoadedImg.h"
#include <QPainter>

using namespace std;

class DescriptorDrawer {
private:

    static void setPoint(int x, int y, QImage &image);

    static pair<int, int> round(int x, int y, QImage &image);

    static void drawPlus(const Point &item, QImage &image);
public:
    static QImage mark_points(const vector<Point> &points, const QImage &image);

    static QImage markPoints(const vector<shared_ptr<AbstractDescriptor>> &descriptors, const QImage &image);

    static QImage markMatching(const shared_ptr<ProcessingImg> &imageA, const shared_ptr<ProcessingImg> &imageB,
                               const shared_ptr<DescriptorPair> &matchInfo);

    static void drawPointWithAngle(const Point &point, QImage &image);
};


#endif //ITOI_DESCRIPTORDRAWER_H
