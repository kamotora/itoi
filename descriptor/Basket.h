#ifndef ITOI_BASKET_H
#define ITOI_BASKET_H

#include <cmath>
#include "vector"
#include "algorithm"

using namespace std;

class Basket {
protected:
    static inline double PI2 = 2 * M_PI;
    vector<double> basket;
    int size;
    double step;
public:
    Basket(int size);

    void add(double angle, double value);

    static double normalize(double angle);

    const vector<double> &getBasket() const;
};


#endif //ITOI_BASKET_H
