//
// Created by kamotora on 30.03.2021.
//

#include "Point.h"

int Point::getX() const {
    return x;
}

int Point::getY() const {
    return y;
}

Point::Point(int x, int y, double value) : x(x), y(y), value(value) {}

double Point::distance(Point &point) const {
    return sqrt(sqr(x - point.x) + sqr(x - point.x));
}

bool Point::operator<(Point point) const {
    return value < point.value;
}

bool Point::operator>(Point point) const {
    return value > point.value;
}

double Point::getValue() const {
    return value;
}

double Point::sqr(int i) {
    return i * i;
}
