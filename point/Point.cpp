#include "Point.h"

int Point::get_x() const {
    return x;
}

int Point::get_y() const {
    return y;
}

Point::Point(int x, int y, double value) : x(x), y(y), value(value) {}


Point::Point(const Point &point, double angle) : Point(point) {
    set_angle(angle);
}

Point::Point(int x, int y, double value, double angle) : Point(Point(x, y, value), angle) {}

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

void Point::set_angle(double _angle) {
    this->angle = _angle;
}

double Point::get_angle() const {
    return angle;
}

