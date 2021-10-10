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

    [[nodiscard]] int get_x() const;

    [[nodiscard]] int get_y() const;

    double distance(Point &point) const;

    bool operator<(Point point) const;

    bool operator>(Point point) const;

    static double sqr(int i) ;
    [[nodiscard]]
    double get_angle() const;
    void set_angle(double _angle);
};


#endif //ITOI_POINT_H
