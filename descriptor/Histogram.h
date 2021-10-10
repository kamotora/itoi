#ifndef ITOI_HISTOGRAM_H
#define ITOI_HISTOGRAM_H


#include "AbstractDescriptor.h"
#include "../common/ProcessingImg.h"
#include "../common/Kernels.h"
#include "../common/Filter.h"

#include "Basket.h"
#include "DescriptorPair.h"
#include "DescriptorDrawer.h"
#include "../point/Harris.h"

class Histogram : public AbstractDescriptor {
public:
    Histogram(const shared_ptr<ProcessingImg> &gradient, const shared_ptr<ProcessingImg> &gradient_angle,
              Point point, int grid_size, int cell_size, int basket_size, bool need_normalize = true);
};


#endif //ITOI_HISTOGRAM_H
