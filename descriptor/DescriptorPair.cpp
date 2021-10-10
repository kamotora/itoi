#include "DescriptorPair.h"

const vector<pair<Point, Point>> &DescriptorPair::points() const {
    return _points;
}

const vector<shared_ptr<AbstractDescriptor>> &DescriptorPair::first() const {
    return _first;
}

const vector<shared_ptr<AbstractDescriptor>> &DescriptorPair::second() const {
    return _second;
}
