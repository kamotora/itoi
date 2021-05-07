#include "SiftBasket.h"

vector<double> SiftBasket::getPeeks() {
    vector<pair<int, double>> values;
    values.reserve(size);
    for (int i = 0; i < size; i++) {
        values.emplace_back(i, basket[i]);
    }
    sort(values.begin(), values.end(),
         [](pair<int, double> a, pair<int, double> b) {
             return b.second < a.second;
         });

    vector<double> result;

    for (int i = 0; i < 2; i++) {
        if (i == 1) {
            if (values[i].second < result[0] * 0.8)
                break;
        }
        int idx = values[i].first;
        double x = values[i].first + 0.5;
        int prevIdx = (idx - 1 + size) % size;
        double prevX = x - 1;
        int nextIdx = (idx + 1) % size;
        double nextX = x + 1;

        double value = basket[idx];
        double prevValue = basket[prevIdx];
        double nextValue = basket[nextIdx];

        result.push_back(PI2 - normalize(getRealPeek(prevX, prevValue, x, value, nextX, nextValue) * step));

    }

    return result;
}

double SiftBasket::getRealPeek(double x1, double y1, double x2, double y2, double x3, double y3) {

    double a = (y3 - (x3 * (y2 - y1) + x2 * y1 - x1 * y2) / (x2 - x1)) /
               (x3 * (x3 - x1 - x2) + x1 * x2);
    double b = (y2 - y1) / (x2 - x1) - a * (x1 + x2);
    return -b / (2 * a);
}

SiftBasket::SiftBasket(int size) : Basket(size) {}
