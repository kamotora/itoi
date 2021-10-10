#include "Sift.h"

Sift::Sift(const shared_ptr<ProcessingImg> &borderedGradient,
           const shared_ptr<ProcessingImg> &borderedGradientAngle, Point point,
           int gridSize, int cellSize, int basketSize, bool needNormalize)
        : AbstractDescriptor((Point &) point) {
    this->descriptor.reserve(gridSize * gridSize * basketSize);

    vector<vector<Basket>> baskets(gridSize, vector(gridSize, Basket(basketSize)));

    int border = gridSize * cellSize;
    int halfBorder = border / 2;

    auto gauss = Kernels::get_gauss_separable_xy(halfBorder / 2.0);
    int left = -halfBorder, right = border - halfBorder;

    for (int x = left; x < right; x++) {
        for (int y = left; y < right; y++) {
            int rotatedX = rotateX(x, y, point.get_angle());
            int rotatedY = rotateY(x, y, point.get_angle());

            if (rotatedX < left || rotatedX >= right || rotatedY < left || rotatedY >= right) continue;

            int realX = point.get_x() + x;
            int realY = point.get_y() + y;

            double phi = DEFAULT_POLICY->get_pixel(*borderedGradientAngle, realX, realY);
            double gradientValue = DEFAULT_POLICY->get_pixel(*borderedGradient, realX, realY);
            double gaussValue = Filter::get_separable_value(gauss, halfBorder + rotatedX, halfBorder + rotatedY);

            int i = (rotatedX - left) / cellSize;
            int j = (rotatedY - left) / cellSize;
            baskets[i][j].add(phi + point.get_angle(), gradientValue * gaussValue);
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


int Sift::rotateX(int x, int y, double angle) {
    return (int) (x * cos(angle) + y * sin(angle));
}

int Sift::rotateY(int x, int y, double angle) {
    return (int) (y * cos(angle) - x * sin(angle));
}

