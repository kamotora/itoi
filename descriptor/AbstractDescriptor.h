//
// Created by kamotora on 28.04.2021.
//

#ifndef ITOI_ABSTRACTDESCRIPTOR_H
#define ITOI_ABSTRACTDESCRIPTOR_H

#include "vector"
#include <numeric>
#include <algorithm>
#include "../point/Point.h"
#include "../core/helper.h"

using namespace std;

class AbstractDescriptor {
protected:
    AbstractDescriptor(Point point);

    vector<double> descriptor;
    Point point;
public:
    const Point &getPoint() const;

    const vector<double> &getDescriptor() const;

    void setDescriptor(vector<double> newDescriptor);

    void normalize();

    static double distance(const shared_ptr<AbstractDescriptor>& descriptorA, const shared_ptr<AbstractDescriptor>& descriptorB);
};


#endif //ITOI_ABSTRACTDESCRIPTOR_H
