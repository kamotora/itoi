
#include "HistogramDescriptor.h"

HistogramDescriptor::HistogramDescriptor(const shared_ptr<DoubleImage> &gradient,
                                         const shared_ptr<DoubleImage> &gradientAngle, Point point,
                                         int gridSize, int cellSize, int basketSize, bool needNormalize)
        : AbstractDescriptor(point) {
    this->point = point;
    this->descriptor.reserve(gridSize * gridSize * basketSize);

    vector<vector<Basket>> baskets(gridSize, vector(gridSize, Basket(basketSize)));
    int border = gridSize * cellSize;
    int halfBorder = border / 2;

    auto gauss = Kernels::GetGaussSeparableXY(halfBorder);
    int left = -halfBorder, right = border - halfBorder;
    auto borderedGradientAngle = DoubleImageBorderPolicy(gradientAngle);
    auto borderedGradient = DoubleImageBorderPolicy(gradient);

    for (int x = left; x < right; x++) {
        for (int y = left; y < right; y++) {
            int realX = (point.getX() + x);
            int realY = (point.getY() + y);
            double phi = borderedGradientAngle.getBorderedPixel(realX, realY);
            double gradientValue = borderedGradient.getBorderedPixel(realX, realY);
            double gaussValue = FilterUtil::getSeparableValue(gauss, halfBorder + x, halfBorder + y);

            int i = (x - left) / cellSize;
            int j = (y - left) / cellSize;
            baskets[i][j].add(phi, gradientValue * gaussValue);
        }
    }

    for (int i = 0; i < gridSize; i++) {
        for (int j = 0; j < gridSize; j++) {
            auto basket = baskets[i][j].getBasket();
            this->descriptor.insert(this->descriptor.end(), basket.begin(), basket.end());
        }
    }
    if (needNormalize)
        normalize();
}


