//
// Created by kamotora on 30.03.2021.
//

#ifndef ITOI_POINT_H
#define ITOI_POINT_H

#include <cmath>

class Point {
protected:
    int x, y;
    double angle = 0;
    double value;
public:
    Point(int x, int y, double value);
    Point(int x, int y, double value, double angle);
    Point(const Point &point, double angle);

    [[nodiscard]]
    double getValue() const;

    [[nodiscard]] int getX() const;

    [[nodiscard]] int getY() const;

    double distance(Point &point) const;

    bool operator<(Point point) const;

    bool operator>(Point point) const;

    static double sqr(int i) ;
    [[nodiscard]]
    double getAngle() const;
    void setAngle(double _angle);
};


#endif //ITOI_POINT_H
