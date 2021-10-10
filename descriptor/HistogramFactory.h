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
                                                              const shared_ptr<ProcessingImg> &gradientAngle,
                                                              const vector<Point> &points);

public:

    HistogramFactory(const shared_ptr<ProcessingImg> &firstImage,
                     const shared_ptr<ProcessingImg> &second,
                     int gridSize,
                     int cellSize,
                     int basketSize,
                     int pointsCount);

    static shared_ptr<DescriptorPair> create(const shared_ptr<ProcessingImg> &first,
                                             const shared_ptr<ProcessingImg> &second,
                                             int _gridSize, int _cellSize,
                                             int _basketSize, int _pointsCount, bool is_need_show = false);
};


#endif //ITOI_HISTOGRAMFACTORY_H
