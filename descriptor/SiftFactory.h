#ifndef ITOI_SIFTFACTORY_H
#define ITOI_SIFTFACTORY_H


#include "../common/ProcessingImg.h"
#include "DescriptorPair.h"
#include "Sift.h"
#include "Basket.h"
#include "../point/Harris.h"
#include "DescriptorDrawer.h"
#include "AbstractDescriptorFactory.h"

class SiftFactory : public AbstractDescriptorFactory {
private:
    static inline int BASKET_SIZE = 36;
    shared_ptr<pair<ProcessingImg, ProcessingImg>> gauss_kernel;

    vector<shared_ptr<AbstractDescriptor>> create_descriptors(const shared_ptr<ProcessingImg> &img);

    [[nodiscard]]
    vector<shared_ptr<AbstractDescriptor>> create_descriptors(const shared_ptr<ProcessingImg> &gradient,
                                                              const shared_ptr<ProcessingImg> &gradient_angle,
                                                              const vector<Point> &points) const;

public:
    SiftFactory(const shared_ptr<ProcessingImg> &firstImage,
                const shared_ptr<ProcessingImg> &second,
                int gridSize,
                int cellSize,
                int basketSize,
                int pointsCount);

    static shared_ptr<DescriptorPair> create(const shared_ptr<ProcessingImg> &first,
                                             const shared_ptr<ProcessingImg> &second,
                                             int _gridSize, int _cellSize,
                                             int _basketSize = BASKET_SIZE, int _pointsCount = 100);

    [[nodiscard]]
    vector<double>
    calculate_angles(const shared_ptr<ProcessingImg> &gradient,
                     const shared_ptr<ProcessingImg> &gradient_angle,
                     const Point &point) const;
};


#endif //ITOI_SIFTFACTORY_H
