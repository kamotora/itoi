//
// Created by kamotora on 07.05.2021.
//

#include "AnglePoint.h"

AnglePoint::AnglePoint(const Point &point, double angle) : Point(point), angle(angle) {

}

double AnglePoint::getAngle() const {
    return angle;
}
