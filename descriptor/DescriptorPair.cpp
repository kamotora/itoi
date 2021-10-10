#include "DescriptorPair.h"

const vector<pair<Point, Point>> &DescriptorPair::getPointsPairs() const {
    return pointsPairs;
}

const vector<shared_ptr<AbstractDescriptor>> &DescriptorPair::getDescriptorsA() const {
    return descriptorsA;
}

const vector<shared_ptr<AbstractDescriptor>> &DescriptorPair::getDescriptorsB() const {
    return descriptorsB;
}
