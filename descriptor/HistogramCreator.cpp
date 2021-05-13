//
// Created by kamotora on 07.05.2021.
//

#include "HistogramCreator.h"


HistogramCreator::HistogramCreator(const shared_ptr<DoubleImage> &firstImage,
                                   const shared_ptr<DoubleImage> &secondImage, int gridSize,
                                   int cellSize, int basketSize, int pointsCount) : firstImage(firstImage),
                                                                                    secondImage(secondImage),
                                                                                    gridSize(gridSize),
                                                                                    cellSize(cellSize),
                                                                                    basketSize(basketSize),
                                                                                    pointsCount(pointsCount) {}

shared_ptr<MatchInfo>
HistogramCreator::create(const shared_ptr<DoubleImage> &first, const shared_ptr<DoubleImage> &second, int _gridSize,
                         int _cellSize, int _basketSize, int _pointsCount, bool showAll) {
    auto creator = HistogramCreator(first, second, _gridSize, _cellSize, _basketSize, _pointsCount);
    auto firstDescriptor = creator.createDescriptors(creator.getFirstImage());

    auto secondDescriptor = creator.createDescriptors(creator.getSecondImage());

    return DescriptorUtil::match(firstDescriptor, secondDescriptor, showAll);
}


vector<shared_ptr<AbstractDescriptor>>
HistogramCreator::createDescriptors(const shared_ptr<DoubleImage> &img) {
    auto x = FilterUtil::derivX(img);
    auto y = FilterUtil::derivY(img);

    auto gradient = DescriptorUtil::getGradient(x, y);
    auto gradientAngle = DescriptorUtil::getGradientAngle(x, y);

    auto points = (new Harris(img))->findPoints(pointsCount);

    return createDescriptors(gradient, gradientAngle, points);
}


vector<shared_ptr<AbstractDescriptor>> HistogramCreator::createDescriptors(const shared_ptr<DoubleImage> &gradient,
                                                                           const shared_ptr<DoubleImage> &gradientAngle,
                                                                           const vector<Point> &points) {
    vector<shared_ptr<AbstractDescriptor>> descriptors;
    descriptors.reserve(points.size());
    for (const auto &item : points)
        descriptors.push_back(
                make_shared<HistogramDescriptor>(gradient, gradientAngle, item, gridSize, cellSize, basketSize));
    return descriptors;
}

const shared_ptr<DoubleImage> &HistogramCreator::getFirstImage() const {
    return firstImage;
}

const shared_ptr<DoubleImage> &HistogramCreator::getSecondImage() const {
    return secondImage;
}
