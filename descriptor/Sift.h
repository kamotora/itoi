#ifndef ITOI_SIFT_H
#define ITOI_SIFT_H


#include "AbstractDescriptor.h"
#include "../common/ProcessingImg.h"
#include "Basket.h"
#include "../common/Kernels.h"

#include "../common/Filter.h"

class Sift : public AbstractDescriptor {
private:
    static int rotateX(int x, int y, double angle);

    static int rotateY(int x, int y, double angle);

public:
    Sift(const shared_ptr<ProcessingImg> &borderedGradient,
         const shared_ptr<ProcessingImg> &borderedGradientAngle, Point point, int gridSize,
         int cellSize, int basketSize, bool needNormalize = true);
};


#endif //ITOI_SIFT_H
