#ifndef ITOI_HISTOGRAMDESCRIPTOR_H
#define ITOI_HISTOGRAMDESCRIPTOR_H


#include "AbstractDescriptor.h"
#include "../core/DoubleImage.h"
#include "../filter/Kernels.h"
#include "../filter/FilterUtil.h"
#include "../core/DoubleImageBorderPolicy.h"
#include "Basket.h"
#include "MatchInfo.h"
#include "DescriptorUtil.h"
#include "../point/Harris.h"

class HistogramDescriptor : public AbstractDescriptor {
public:
    HistogramDescriptor(const shared_ptr<DoubleImage> &gradient, const shared_ptr<DoubleImage> &gradientAngle,
                        Point point, int gridSize, int cellSize, int basketSize, bool needNormalize = true);
};


#endif //ITOI_HISTOGRAMDESCRIPTOR_H
