#ifndef ITOI_ABSTRACTDESCRIPTORFACTORY_H
#define ITOI_ABSTRACTDESCRIPTORFACTORY_H


#include "../common/border/IBorderPolicy.h"
#include "../common/border/MirrorPolicy.h"
#include "cmath"
#include "AbstractDescriptor.h"
#include "DescriptorPair.h"

static const double MAX_CLOSEST = 0.8;

class AbstractDescriptorFactory {
protected:
    IBorderPolicy *DEFAULT_POLICY = new MirrorPolicy();
    const shared_ptr<ProcessingImg> &firstImage;
    const shared_ptr<ProcessingImg> &secondImage;
    int grid_size;
    int cell_size;
    int basket_size;
    int pointsCount;

    AbstractDescriptorFactory(const shared_ptr<ProcessingImg> &firstImage, const shared_ptr<ProcessingImg> &secondImage,
                              int gridSize, int cellSize, int basketSize, int pointsCount) : firstImage(firstImage),
                                                                                             secondImage(secondImage),
                                                                                             grid_size(gridSize),
                                                                                             cell_size(cellSize),
                                                                                             basket_size(basketSize),
                                                                                             pointsCount(pointsCount) {}

    [[nodiscard]]
    const shared_ptr<ProcessingImg> &get_first_image() const;

    [[nodiscard]]
    const shared_ptr<ProcessingImg> &get_second_image() const;

    static shared_ptr<ProcessingImg>
    count_gradient(const shared_ptr<ProcessingImg> &first, const shared_ptr<ProcessingImg> &second,
                   double (*counterFunc)(double, double));

    static shared_ptr<ProcessingImg>
    count_gradient(const shared_ptr<ProcessingImg> &first, const shared_ptr<ProcessingImg> &second);

    static shared_ptr<ProcessingImg>
    count_gradient_angle(const shared_ptr<ProcessingImg> &first_pixel, const shared_ptr<ProcessingImg> &second_pixel);

    static int get_min_ind(vector<double> distances, int exclude_idx);

    static shared_ptr<AbstractDescriptor>
    getClosest(const shared_ptr<AbstractDescriptor> &descriptor,
               const vector<shared_ptr<AbstractDescriptor>> &descriptors,
               bool need_show_all = false);

    static shared_ptr<DescriptorPair>
    match(const vector<shared_ptr<AbstractDescriptor>> &first,
          const vector<shared_ptr<AbstractDescriptor>> &second,
          bool need_show_all = false);

    static double
    dist(const shared_ptr<AbstractDescriptor> &first, const shared_ptr<AbstractDescriptor> &second);
};


#endif //ITOI_ABSTRACTDESCRIPTORFACTORY_H
