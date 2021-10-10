#ifndef ITOI_DESCRIPTORPAIR_H
#define ITOI_DESCRIPTORPAIR_H

#include "vector"
#include "AbstractDescriptor.h"

class DescriptorPair {
private:
    vector<pair<Point, Point>> _points;
    vector<shared_ptr<AbstractDescriptor>> _first;
    vector<shared_ptr<AbstractDescriptor>> _second;

public:
    DescriptorPair(const vector<pair<Point, Point>> &pointsPairs,
                   const vector<shared_ptr<AbstractDescriptor>> &descriptorsA,
                   const vector<shared_ptr<AbstractDescriptor>> &descriptorsB) : _points(pointsPairs),
                                                                                 _first(descriptorsA),
                                                                                 _second(descriptorsB) {}

    [[nodiscard]]
    const vector<pair<Point, Point>> &points() const;

    [[nodiscard]]
    const vector<shared_ptr<AbstractDescriptor>> &first() const;

    [[nodiscard]]
    const vector<shared_ptr<AbstractDescriptor>> &second() const;
};


#endif //ITOI_DESCRIPTORPAIR_H
