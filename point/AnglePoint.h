//
// Created by kamotora on 07.05.2021.
//

#ifndef ITOI_ANGLEPOINT_H
#define ITOI_ANGLEPOINT_H


#include "Point.h"

class AnglePoint : public Point{
protected:
    double angle;
public:
    AnglePoint(const Point &point, double angle);

    double getAngle() const;
};


#endif //ITOI_ANGLEPOINT_H
