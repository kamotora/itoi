#include "DescriptorDrawer.h"


QImage DescriptorDrawer::markMatching(const shared_ptr<ProcessingImg> &imageA, const shared_ptr<ProcessingImg> &imageB,
                                      const shared_ptr<DescriptorPair> &matchInfo) {
    auto markedImageA = markPoints(matchInfo->getDescriptorsA(), LoadedImg::from_processing_img(*imageA).native_image());
    auto markedImageB = markPoints(matchInfo->getDescriptorsB(), LoadedImg::from_processing_img(*imageB).native_image());
    auto minMaxHeight = minmax(markedImageA.height(), markedImageB.height());
    QImage resultImage = QImage(markedImageA.width() + markedImageB.width(), minMaxHeight.second, QImage::Format_RGB32);

    auto diffHeight = abs(markedImageA.height() - markedImageB.height());

    QPainter painter(&resultImage);
    painter.fillRect(0, minMaxHeight.first, markedImageA.width(), diffHeight, QColor(0, 0, 0));
    painter.drawImage(QRect(0, 0, markedImageA.width(), markedImageA.height()), markedImageA);
    painter.drawImage(QRect(markedImageA.width(), 0, markedImageB.width(), markedImageB.height()),
                      markedImageB);

    painter.setPen(QColor(255, 255, 0));
    for (auto pointsPair: matchInfo->getPointsPairs()) {

        auto pointA = pointsPair.first;
        auto pointB = pointsPair.second;
        painter.drawLine(pointA.get_x(), pointA.get_y(), pointB.get_x() + markedImageA.width(), pointB.get_y());
    }
    return resultImage;
}

void DescriptorDrawer::drawPlus(const Point &item, QImage &image) {
    int plusSize = 2;
    for (int i = -plusSize; i <= plusSize; i++) {
        if (i == 0)
            continue;
        setPoint(item.get_x() + i, item.get_y(), image);
        setPoint(item.get_x(), item.get_y() + i, image);
    }
}

pair<int, int> DescriptorDrawer::round(int x, int y, QImage &image) {
    int resX = (x < 0) ? 0 : (x >= image.width() ? image.width() - 1 : x);
    int resY = (y < 0) ? 0 : (y >= image.height() ? image.height() - 1 : y);
    return make_pair(resX, resY);
}

void DescriptorDrawer::setPoint(int x, int y, QImage &image) {
    auto pair = round(x, y, image);
    image.setPixelColor(pair.first, pair.second, qRgb(255, 0, 0));
}

QImage DescriptorDrawer::mark_points(const vector<Point> &points, const QImage &image) {
    QImage resultImage(image);
    for (const auto &item: points) {
        drawPlus(item, resultImage);
    }
    return resultImage;
}

QImage DescriptorDrawer::markPoints(const vector<shared_ptr<AbstractDescriptor>> &descriptors, const QImage &image) {
    QImage resultImage(image);
    for (const auto &item: descriptors)
        drawPointWithAngle(item->getPoint(), resultImage);
    return resultImage;
}

void DescriptorDrawer::drawPointWithAngle(const Point &point, QImage &image) {

    QPainter painter(&image);
    double angle = point.get_angle();
    painter.setPen(QPen(QColor(255, 0, 0)));
    painter.drawEllipse(QPoint(point.get_x(), point.get_y()), 2, 2);
    if (angle > -10) {
        int dx = (int) (cos(angle) * 10);
        int dy = (int) (sin(angle) * 10);

        painter.drawLine(point.get_x(), point.get_y(), point.get_x() + dx, point.get_y() + dy);
    }
}