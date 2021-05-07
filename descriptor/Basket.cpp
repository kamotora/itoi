#include "Basket.h"

Basket::Basket(int size) : size(size) {
    basket.resize(size);
    step = PI2 / (double) size;
}

void Basket::add(double angle, double value) {
    angle = normalize(angle);

    angle /= step;
    int binIdx = (int) angle;
    double binCenter = binIdx + 0.5;
    double weight = abs(binCenter - angle);
    int neighbourIdx = (binIdx + 1) % size;
    if (angle <= binCenter) {
        neighbourIdx = (binIdx - 1 + size) % size;
    }

    basket[binIdx] += weight * value;
    basket[neighbourIdx] += (1 - weight) * value;
}

double Basket::normalize(double angle) {
    while (angle < 0)
        angle += PI2;
    while (angle >= PI2)
        angle -= PI2;
    return angle;
}

const vector<double> &Basket::getBasket() const {
    return basket;
}
