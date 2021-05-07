#ifndef ITOI_SIFTBASKET_H
#define ITOI_SIFTBASKET_H


#include "Basket.h"

class SiftBasket: public Basket{
public:
    SiftBasket(int size);

    vector<double> getPeeks();
    static double getRealPeek(double x1, double y1, double x2, double y2, double x3, double y3);
};


#endif //ITOI_SIFTBASKET_H
