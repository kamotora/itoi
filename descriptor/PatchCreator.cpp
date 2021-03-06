//
// Created by kamotora on 28.04.2021.
//

#include "PatchCreator.h"

shared_ptr<MatchInfo> PatchCreator::create(const shared_ptr<DoubleImage> &first,
                                           const shared_ptr<DoubleImage> &second,
                                           int gridHalfSize,
                                           int cellHalfSize,
                                           int pointsCount) {
    auto gradientFirst = DescriptorUtil::getGradient(first, true);
    auto gradientSecond = DescriptorUtil::getGradient(second, true);

    auto pointsFirst = (new Harris(first))->findPoints(pointsCount);
    auto pointsSecond = (new Harris(second))->findPoints(pointsCount);

    auto descriptorsFirst = getDescriptors(gradientFirst, pointsFirst, gridHalfSize, cellHalfSize);
    auto descriptorsSecond = getDescriptors(gradientSecond, pointsSecond, gridHalfSize, cellHalfSize);

    return DescriptorUtil::match(descriptorsFirst, descriptorsSecond);
}


vector<shared_ptr<AbstractDescriptor>> PatchCreator::getDescriptors(const shared_ptr<DoubleImage> &gradient,
                                                                    const vector<Point> &interestingPoints,
                                                                    int gridHalfSize,
                                                                    int cellHalfSize) {
    vector<shared_ptr<AbstractDescriptor>> result;
    result.reserve(interestingPoints.size());
    for (const auto &item : interestingPoints) {
        result.push_back(make_shared<PatchDescriptor>(gradient, item, gridHalfSize, cellHalfSize));
    }
    return result;
}