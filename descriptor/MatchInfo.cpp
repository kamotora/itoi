//
// Created by kamotora on 29.04.2021.
//

#include "MatchInfo.h"

MatchInfo::MatchInfo(const vector<pair<Point, Point>> &pointsPairs,
                         const vector<shared_ptr<AbstractDescriptor>> &descriptorsA,
                         const vector<shared_ptr<AbstractDescriptor>> &descriptorsB) : pointsPairs(pointsPairs),
                                                                                       descriptorsA(descriptorsA),
                                                                                       descriptorsB(descriptorsB) {}

const vector<pair<Point, Point>> &MatchInfo::getPointsPairs() const {
    return pointsPairs;
}

const vector<shared_ptr<AbstractDescriptor>> &MatchInfo::getDescriptorsA() const {
    return descriptorsA;
}

const vector<shared_ptr<AbstractDescriptor>> &MatchInfo::getDescriptorsB() const {
    return descriptorsB;
}
