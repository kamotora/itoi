//
// Created by kamotora on 07.05.2021.
//

#ifndef ITOI_SIFTDESCRIPTOR_H
#define ITOI_SIFTDESCRIPTOR_H


#include "AbstractDescriptor.h"
#include "../core/DoubleImage.h"
#include "Basket.h"
#include "../filter/Kernels.h"
#include "../core/DoubleImageBorderPolicy.h"
#include "../filter/FilterUtil.h"

class SiftDescriptor : public AbstractDescriptor {
private:
    static int rotateX(int x, int y, double angle);

    static int rotateY(int x, int y, double angle);

public:
    SiftDescriptor(const shared_ptr<DoubleImageBorderPolicy> &borderedGradient,
                   const shared_ptr<DoubleImageBorderPolicy> &borderedGradientAngle, Point point, int gridSize,
                   int cellSize, int basketSize, bool needNormalize = true);
};


#endif //ITOI_SIFTDESCRIPTOR_H
