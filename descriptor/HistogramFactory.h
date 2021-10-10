#ifndef ITOI_HISTOGRAMFACTORY_H
#define ITOI_HISTOGRAMFACTORY_H


#include "../common/ProcessingImg.h"
#include "DescriptorPair.h"
#include "Histogram.h"
#include "AbstractDescriptorFactory.h"

class HistogramFactory : public AbstractDescriptorFactory {
private:
    vector<shared_ptr<AbstractDescriptor>> create_descriptors(const shared_ptr<ProcessingImg> &img);

    vector<shared_ptr<AbstractDescriptor>> create_descriptors(const shared_ptr<ProcessingImg> &gradient,
                                                              const shared_ptr<ProcessingImg> &angle_gradient,
                                                              const vector<Point> &points);

public:

    HistogramFactory(const shared_ptr<ProcessingImg> &first,
                     const shared_ptr<ProcessingImg> &second,
                     int grid_size,
                     int cell_size,
                     int basket_size,
                     int points_count);

    static shared_ptr<DescriptorPair> create(const shared_ptr<ProcessingImg> &first,
                                             const shared_ptr<ProcessingImg> &second,
                                             int _grid_size, int _cell_size,
                                             int _basket_size, int _points_count, bool is_need_show = false);
};


#endif //ITOI_HISTOGRAMFACTORY_H
