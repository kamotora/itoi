
#include "Histogram.h"

Histogram::Histogram(const shared_ptr<ProcessingImg> &gradient,
                     const shared_ptr<ProcessingImg> &gradient_angle, Point point,
                     int grid_size, int cell_size, int basket_size, bool need_normalize)
        : AbstractDescriptor(point) {
    this->point = point;
    this->descriptor.reserve(grid_size * grid_size * basket_size);

    vector<vector<Basket>> baskets(grid_size, vector(grid_size, Basket(basket_size)));
    int border = grid_size * cell_size;
    int halfBorder = border / 2;

    auto gauss = Kernels::gauss_separable_xy(halfBorder);
    int left = -halfBorder, right = border - halfBorder;


    for (int x = left; x < right; x++) {
        for (int y = left; y < right; y++) {
            int realX = (point.get_x() + x);
            int realY = (point.get_y() + y);
            double phi = DEFAULT_POLICY->get_pixel(*gradient_angle, realX, realY);
            double gradientValue = DEFAULT_POLICY->get_pixel(*gradient, realX, realY);
            double gaussValue = Filter::get_separable_value(gauss, halfBorder + x, halfBorder + y);

            int i = (x - left) / cell_size;
            int j = (y - left) / cell_size;
            baskets[i][j].add(phi, gradientValue * gaussValue);
        }
    }

    for (int i = 0; i < grid_size; i++) {
        for (int j = 0; j < grid_size; j++) {
            auto basket = baskets[i][j].get_basket();
            this->descriptor.insert(this->descriptor.end(), basket.begin(), basket.end());
        }
    }
    if (need_normalize)
        normalize();
}


