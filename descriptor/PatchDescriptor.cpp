//
// Created by kamotora on 28.04.2021.
//

#include "PatchDescriptor.h"

PatchDescriptor::PatchDescriptor(const shared_ptr<DoubleImage>& gradient, Point point, int gridHalfSize, int cellHalfSize)
        : AbstractDescriptor(point) {
    int cellSize = cellHalfSize * 2 + 1;

    auto borderedGradient = make_shared<DoubleImageBorderPolicy>(gradient);
    for (int cellX = -gridHalfSize; cellX <= gridHalfSize; cellX++) {
        for (int cellY = -gridHalfSize; cellY <= gridHalfSize; cellY++) {
            double sum = 0;
            for (int pixelX = -cellHalfSize; pixelX <= cellHalfSize; pixelX++) {
                for (int pixelY = -cellHalfSize; pixelY <= cellHalfSize; pixelY++) {
                    int realX = point.getX() + cellX * cellSize + pixelX;
                    int realY = point.getY() + cellY * cellSize + pixelY;

                    sum += borderedGradient->getBorderedPixel(realX, realY);
                }
            }

            sum /= cellSize * cellSize;
            descriptor.push_back(sum);
        }
    }
    normalize();
}