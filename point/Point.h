//
// Created by kamotora on 30.03.2021.
//

#ifndef ITOI_POINT_H
#define ITOI_POINT_H

#include <cmath>


class Point {
protected:
    int x, y;
    double value;
public:
    Point(int x, int y, double value);

    [[nodiscard]]
    double getValue() const;

    [[nodiscard]] int getX() const;

    [[nodiscard]] int getY() const;

    double distance(Point &point) const;

    bool operator<(Point point) const;

    bool operator>(Point point) const;

    static double sqr(int i) ;
};


#endif //ITOI_POINT_H
