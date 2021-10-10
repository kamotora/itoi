#ifndef ITOI_DESCRIPTORPAIR_H
#define ITOI_DESCRIPTORPAIR_H

#include "vector"
#include "AbstractDescriptor.h"

class DescriptorPair {
private:
    vector<pair<Point, Point>> pointsPairs;
    vector<shared_ptr<AbstractDescriptor>> descriptorsA;
    vector<shared_ptr<AbstractDescriptor>> descriptorsB;

public:
    DescriptorPair(const vector<pair<Point, Point>> &pointsPairs,
                   const vector<shared_ptr<AbstractDescriptor>> &descriptorsA,
                   const vector<shared_ptr<AbstractDescriptor>> &descriptorsB) : pointsPairs(pointsPairs),
                                                                            descriptorsA(descriptorsA),
                                                                            descriptorsB(descriptorsB) {}

    [[nodiscard]]
    const vector<pair<Point, Point>> &getPointsPairs() const;

    [[nodiscard]]
    const vector<shared_ptr<AbstractDescriptor>> &getDescriptorsA() const;

    [[nodiscard]]
    const vector<shared_ptr<AbstractDescriptor>> &getDescriptorsB() const;
};


#endif //ITOI_DESCRIPTORPAIR_H
