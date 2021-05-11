#include "SiftDescriptor.h"

SiftDescriptor::SiftDescriptor(const shared_ptr<DoubleImageBorderPolicy> &borderedGradient,
                               const shared_ptr<DoubleImageBorderPolicy> &borderedGradientAngle, Point point,
                               int gridSize, int cellSize, int basketSize, bool needNormalize)
        : AbstractDescriptor((Point &) point) {
//    this->descriptor.reserve(gridSize * gridSize * basketSize);

    vector<vector<Basket>> baskets(gridSize, vector(gridSize, Basket(basketSize)));

    int border = gridSize * cellSize;
    int halfBorder = border / 2;

    auto gauss = Kernels::GetGaussSeparableXY(halfBorder / 2.0);
    int left = -halfBorder, right = border - halfBorder;

    for (int x = left; x < right; x++) {
        for (int y = left; y < right; y++) {
            int rotatedX = rotateX(x, y, point.getAngle());
            int rotatedY = rotateY(x, y, point.getAngle());

            if (rotatedX < left || rotatedX >= right || rotatedY < left || rotatedY >= right) continue;

            int realX = point.getX() + x;
            int realY = point.getY() + y;

            double phi = borderedGradientAngle->getBorderedPixel(realX, realY);
            double gradientValue = borderedGradient->getBorderedPixel(realX, realY);
            double gaussValue = FilterUtil::getSeparableValue(gauss, halfBorder + rotatedX, halfBorder + rotatedY);

            int i = (rotatedX - left) / cellSize;
            int j = (rotatedY - left) / cellSize;
            baskets[i][j].add(phi + point.getAngle(), gradientValue * gaussValue);
        }
    }

    for (int i = 0; i < gridSize; i++) {
        for (int j = 0; j < gridSize; j++) {
            auto basket = baskets[i][j].getBasket();
            for (const auto &item : basket)
                descriptor.push_back(item);
//            this->descriptor.insert(this->descriptor.end(), basket.begin(), basket.end());
        }
    }
    if (needNormalize)
        normalize();
}


int SiftDescriptor::rotateX(int x, int y, double angle) {
    return (int) (x * cos(angle) + y * sin(angle));
}

int SiftDescriptor::rotateY(int x, int y, double angle) {
    return (int) (y * cos(angle) - x * sin(angle));
}

