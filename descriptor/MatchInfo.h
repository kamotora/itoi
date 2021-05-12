//
// Created by kamotora on 29.04.2021.
//

#ifndef ITOI_MATCHINFO_H
#define ITOI_MATCHINFO_H

#include "vector"
#include "AbstractDescriptor.h"

class MatchInfo {
private:
    vector<pair<Point, Point>> pointsPairs;
    vector<shared_ptr<AbstractDescriptor>> descriptorsA;
    vector<shared_ptr<AbstractDescriptor>> descriptorsB;

public:
    MatchInfo(const vector<pair<Point, Point>> &pointsPairs,
              const vector<shared_ptr<AbstractDescriptor>> &descriptorsA,
              const vector<shared_ptr<AbstractDescriptor>> &descriptorsB);

    [[nodiscard]]
    const vector<pair<Point, Point>> &getPointsPairs() const;

    [[nodiscard]]
    const vector<shared_ptr<AbstractDescriptor>> &getDescriptorsA() const;

    [[nodiscard]]
    const vector<shared_ptr<AbstractDescriptor>> &getDescriptorsB() const;
};


#endif //ITOI_MATCHINFO_H
