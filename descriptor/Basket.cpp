#include "Basket.h"

Basket::Basket(int size) : size(size) {
    basket.resize(size);
    step = PI2 / (double) size;
}

void Basket::add(double angle, double value) {
    angle = normalize(angle) / step;
    int i = (int) angle;
    double center = i + 0.5;
    double weight = abs(center - angle);
    int neighbourI = (i + 1) % size;
    if (angle <= center) {
        neighbourI = (i - 1 + size) % size;
    }

    basket[i] += weight * value;
    basket[neighbourI] += (1 - weight) * value;
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

// пики
vector<double> Basket::getHighestAngles() {
    auto firstMax = getMaxAngle();
    auto secondMax = getMaxAngle(firstMax.second, firstMax.first * 0.8);
    auto result = secondMax.second != -1 ? vector<double>{firstMax.first, secondMax.first} : vector<double>{firstMax.first};
    for (int i = 0; i < result.size(); i++)
        result[i] = PI2 - result[i];
    return result;
}

pair<double, int> Basket::getMaxAngle(int excludeIndex, double min) {
    auto max = numeric_limits<double>::min();
    int maxIndex = -1;
    for (int i = 0; i < size; i++) {
        if (basket[i] > min && i != excludeIndex && basket[i] > max) {
            max = basket[i];
            maxIndex = i;
        }
    }
    return make_pair((maxIndex + 0.5) * step, maxIndex);
}
