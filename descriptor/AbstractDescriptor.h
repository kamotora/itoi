#ifndef ITOI_ABSTRACTDESCRIPTOR_H
#define ITOI_ABSTRACTDESCRIPTOR_H

#include "vector"
#include <numeric>
#include <algorithm>
#include "../point/Point.h"
#include "../common/border/MirrorPolicy.h"

using namespace std;

class AbstractDescriptor {
protected:
    IBorderPolicy *DEFAULT_POLICY = new MirrorPolicy();

    explicit AbstractDescriptor(Point point);

    vector<double> descriptor;
    Point point;
public:
    [[nodiscard]]
    const Point &getPoint() const;

    [[nodiscard]]
    const vector<double> &getDescriptor() const;

    void setDescriptor(vector<double> newDescriptor);

    void normalize();
};


#endif //ITOI_ABSTRACTDESCRIPTOR_H
