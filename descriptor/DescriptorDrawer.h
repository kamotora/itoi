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

    static void set_point(int x, int y, QImage &image);

    static pair<int, int> round(int x, int y, QImage &image);

    static void draw_plus(const Point &item, QImage &image);
public:
    static QImage mark_points(const vector<Point> &points, const QImage &image);

    static QImage draw_points(const vector<shared_ptr<AbstractDescriptor>> &descriptors, const QImage &image);

    static QImage draw_matching(const shared_ptr<ProcessingImg> &firstImage, const shared_ptr<ProcessingImg> &secondImage,
                                const shared_ptr<DescriptorPair> &matchInfo);

    static void draw_vectored_point(const Point &point, QImage &image);
};


#endif //ITOI_DESCRIPTORDRAWER_H
