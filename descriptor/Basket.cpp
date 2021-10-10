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

const vector<double> &Basket::get_basket() const {
    return basket;
}

// пики
vector<double> Basket::get_highest_angles() {
    auto firstMax = get_max_angle();
    auto secondMax = get_max_angle(firstMax.first, firstMax.second * 0.8);
//    auto result = secondMax._first != -1 ? vector<double>{firstMax.second, secondMax.second} : vector<double>{firstMax.second};
    vector<double> result;
    auto values = vector<pair<int, double>>{firstMax, secondMax};
    for (int k = 0; k < 2; k++) {
        if (k == 1 && values[k].first == -1)
            break;

        int i = values[k].first;
        double x = values[k].first + 0.5;
        int prevI = (i - 1 + size) % size;
        int nextI = (i + 1) % size;

        double value = basket[i], prevValue = basket[prevI], nextValue = basket[nextI];
        result.push_back(normalize(interpolate(x - 1, prevValue, x, value, x + 1, nextValue) * step));
    }

    for (double & i : result)
        i = PI2 - i;
    return result;
}

double Basket::interpolate(double x1, double y1, double x2, double y2, double x3, double y3) {
    double a = (y3 - (x3 * (y2 - y1) + x2 * y1 - x1 * y2) / (x2 - x1)) /
               (x3 * (x3 - x1 - x2) + x1 * x2);
    double b = (y2 - y1) / (x2 - x1) - a * (x1 + x2);
    return -b / (2 * a);
}

pair<int, double> Basket::get_max_angle(int excludeIndex, double min) {
    auto max = numeric_limits<double>::min();
    int maxIndex = -1;
    for (int i = 0; i < size; i++) {
        if (basket[i] > min && i != excludeIndex && basket[i] > max) {
            max = basket[i];
            maxIndex = i;
        }
    }
    return make_pair(maxIndex, (maxIndex + 0.5) * step);
}
