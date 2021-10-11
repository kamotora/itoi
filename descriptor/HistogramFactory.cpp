#include "HistogramFactory.h"


HistogramFactory::HistogramFactory(const shared_ptr<ProcessingImg> &first,
                                   const shared_ptr<ProcessingImg> &secondImage, int grid_size,
                                   int cell_size, int basket_size, int points_count)
        : AbstractDescriptorFactory(first, secondImage, grid_size, cell_size, basket_size, points_count) {}

shared_ptr<DescriptorPair>
HistogramFactory::create(const shared_ptr<ProcessingImg> &first, const shared_ptr<ProcessingImg> &second,
                         int _grid_size,
                         int _cell_size, int _basket_size, int _points_count, bool is_need_show) {
    auto factory = HistogramFactory(first, second,
                                    _grid_size, _cell_size,
                                    _basket_size, _points_count);

    return match(factory.create_descriptors(factory.get_first_image()),
                 factory.create_descriptors(factory.get_second_image()),
                 is_need_show);
}


vector<shared_ptr<AbstractDescriptor>>
HistogramFactory::create_descriptors(const shared_ptr<ProcessingImg> &img) {
    auto x = Filter::sobel_x(img);
    auto y = Filter::sobel_y(img);

    auto points = (new Harris(img))->find_points(pointsCount);

    return create_descriptors(count_gradient(x, y),
                              count_gradient_angle(x, y),
                              points);
}


vector<shared_ptr<AbstractDescriptor>>
HistogramFactory::create_descriptors(const shared_ptr<ProcessingImg> &gradient,
                                     const shared_ptr<ProcessingImg> &angle_gradient,
                                     const vector<Point> &points) {
    vector<shared_ptr<AbstractDescriptor>> descriptors;
    descriptors.reserve(points.size());
    for (const auto &item: points)
        descriptors.push_back(
                make_shared<Histogram>(gradient, angle_gradient, item, grid_size, cell_size, basket_size));
    return descriptors;
}