//
// Created by kamotora on 29.04.2021.
//

#include "DescriptorUtil.h"

shared_ptr<DoubleImage> DescriptorUtil::getGradient(const shared_ptr<DoubleImage> &image, bool normalize) {
    auto result = getGradient(FilterUtil::derivX(image), FilterUtil::derivY(image));
    return normalize ? make_shared<DoubleImage>(result->normalize()) : result;
}

shared_ptr<DoubleImage>
DescriptorUtil::getGradient(const shared_ptr<DoubleImage> &first, const shared_ptr<DoubleImage> &second) {
    if (first->getHeight() != second->getHeight() || first->getWidth() != second->getWidth())
        throw invalid_argument("different images size");
    auto gradient = make_shared<DoubleImage>(first->getWidth(), first->getHeight());

    for (int i = 0; i < gradient->getSize(); i++) {
        auto firstPixel = first->getPixel(i);
        auto secondPixel = second->getPixel(i);
        gradient->setPixel(i, sqrt(firstPixel * firstPixel + secondPixel * secondPixel));
    }

    return gradient;
}

shared_ptr<MatchInfo> DescriptorUtil::match(const vector<shared_ptr<AbstractDescriptor>> &firstList,
                                            const vector<shared_ptr<AbstractDescriptor>> &secondList) {
    vector<pair<Point, Point>> pointsMatching;

    for (const auto &item : firstList) {
        auto closest = getClosest(item, secondList);
        if (closest == nullptr)
            continue;
        pointsMatching.emplace_back(item->getPoint(), closest->getPoint());
    }

    return make_shared<MatchInfo>(pointsMatching, firstList, secondList);
}

shared_ptr<AbstractDescriptor> DescriptorUtil::getClosest(const shared_ptr<AbstractDescriptor> &descriptor,
                                                          const vector<shared_ptr<AbstractDescriptor>> &descriptors) {
    vector<double> distances;
    distances.reserve(descriptors.size());
    for (const auto &patchDescriptor : descriptors) {
        distances.push_back(AbstractDescriptor::distance(descriptor, patchDescriptor));
    }
    int a = getMinIndex(distances, -1);
    int b = getMinIndex(distances, a);

    double r = distances[a] / distances[b];
    return (r <= 0.8) ? descriptors[a] : nullptr;
}

int DescriptorUtil::getMinIndex(vector<double> distances, int excludeIndex) {
    int selectedIndex = -1;
    for (int i = 0; i < distances.size(); i++)
        if (i != excludeIndex && (selectedIndex == -1 || distances[i] < distances[selectedIndex]))
            selectedIndex = i;

    return selectedIndex;
}

QImage DescriptorUtil::markMatching(const shared_ptr<DoubleImage> &imageA, const shared_ptr<DoubleImage> &imageB,
                                    const shared_ptr<MatchInfo> &matchInfo) {
    auto markedImageA = markPoints(matchInfo->getDescriptorsA(), InputImage::fromDoubleImage(*imageA).getImage());
    auto markedImageB = markPoints(matchInfo->getDescriptorsB(), InputImage::fromDoubleImage(*imageB).getImage());
    QImage resultImage = QImage(markedImageA.width() + markedImageB.width(),
                                max(markedImageA.height(), markedImageB.height()),
                                QImage::Format_RGB32);
    QPainter painter(&resultImage);
    painter.drawImage(QRect(0, 0, markedImageA.width(), markedImageA.height()), markedImageA);
    painter.drawImage(QRect(markedImageA.width(), 0, markedImageA.width(), markedImageA.height()),
                      markedImageB);

    painter.setPen(QColor(255, 255, 0));
    for (auto pointsPair : matchInfo->getPointsPairs()) {

        auto pointA = pointsPair.first;
        auto pointB = pointsPair.second;
        painter.drawLine(pointA.getX(), pointA.getY(), pointB.getX() + markedImageA.width(), pointB.getY());
    }
    return resultImage;
}

void DescriptorUtil::drawPlus(const Point &item, QImage &image) {
    int plusSize = 2;
    for (int i = -plusSize; i <= plusSize; i++) {
        if (i == 0)
            continue;
        setPoint(item.getX() + i, item.getY(), image);
        setPoint(item.getX(), item.getY() + i, image);
    }
}

pair<int, int> DescriptorUtil::round(int x, int y, QImage &image) {
    int resX = (x < 0) ? 0 : (x >= image.width() ? image.width() - 1 : x);
    int resY = (y < 0) ? 0 : (y >= image.height() ? image.height() - 1 : y);
    return make_pair(resX, resY);
}

void DescriptorUtil::setPoint(int x, int y, QImage &image) {
    auto pair = round(x, y, image);
    image.setPixelColor(pair.first, pair.second, qRgb(255, 0, 0));
}

QImage DescriptorUtil::markPoints(const vector<Point> &points, const QImage &image) {
    QImage resultImage(image);
    for (const auto &item : points) {
        drawPlus(item, resultImage);
    }
    return resultImage;
}

QImage DescriptorUtil::markPoints(const vector<shared_ptr<AbstractDescriptor>> &descriptors, const QImage &image) {
    QImage resultImage(image);
    for (const auto &item : descriptors) {
        drawPlus(item->getPoint(), resultImage);
    }
    return resultImage;
}