
#include "Histogram.h"

Histogram::Histogram(const shared_ptr<ProcessingImg> &gradient,
                     const shared_ptr<ProcessingImg> &gradientAngle, Point point,
                     int gridSize, int cellSize, int basketSize, bool needNormalize)
        : AbstractDescriptor(point) {
    this->point = point;
    this->descriptor.reserve(gridSize * gridSize * basketSize);

    vector<vector<Basket>> baskets(gridSize, vector(gridSize, Basket(basketSize)));
    int border = gridSize * cellSize;
    int halfBorder = border / 2;

    auto gauss = Kernels::gauss_separable_xy(halfBorder);
    int left = -halfBorder, right = border - halfBorder;


    for (int x = left; x < right; x++) {
        for (int y = left; y < right; y++) {
            int realX = (point.get_x() + x);
            int realY = (point.get_y() + y);
            double phi = DEFAULT_POLICY->get_pixel(*gradientAngle, realX, realY);
            double gradientValue = DEFAULT_POLICY->get_pixel(*gradient, realX, realY);
            double gaussValue = Filter::get_separable_value(gauss, halfBorder + x, halfBorder + y);

            int i = (x - left) / cellSize;
            int j = (y - left) / cellSize;
            baskets[i][j].add(phi, gradientValue * gaussValue);
        }
    }

    for (int i = 0; i < gridSize; i++) {
        for (int j = 0; j < gridSize; j++) {
            auto basket = baskets[i][j].get_basket();
            this->descriptor.insert(this->descriptor.end(), basket.begin(), basket.end());
        }
    }
    if (needNormalize)
        normalize();
}


