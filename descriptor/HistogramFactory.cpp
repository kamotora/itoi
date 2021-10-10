#include "HistogramFactory.h"


HistogramFactory::HistogramFactory(const shared_ptr<ProcessingImg> &firstImage,
                                   const shared_ptr<ProcessingImg> &secondImage, int gridSize,
                                   int cellSize, int basketSize, int pointsCount)
        : AbstractDescriptorFactory(firstImage, secondImage, gridSize, cellSize, basketSize, pointsCount) {}

shared_ptr<DescriptorPair>
HistogramFactory::create(const shared_ptr<ProcessingImg> &first, const shared_ptr<ProcessingImg> &second,
                         int _gridSize,
                         int _cellSize, int _basketSize, int _pointsCount, bool is_need_show) {
    auto factory = HistogramFactory(first, second, _gridSize, _cellSize, _basketSize, _pointsCount);
    auto first_descriptor = factory.create_descriptors(factory.get_first_image());

    auto second_descriptor = factory.create_descriptors(factory.get_second_image());

    return match(first_descriptor, second_descriptor, is_need_show);
}


vector<shared_ptr<AbstractDescriptor>>
HistogramFactory::create_descriptors(const shared_ptr<ProcessingImg> &img) {
    auto x = Filter::sobel_x(img);
    auto y = Filter::sobel_y(img);

    auto gradient = count_gradient(x, y);
    auto gradientAngle = count_gradient_angle(x, y);

    auto points = (new Harris(img))->find_points(pointsCount);

    return create_descriptors(gradient, gradientAngle, points);
}


vector<shared_ptr<AbstractDescriptor>>
HistogramFactory::create_descriptors(const shared_ptr<ProcessingImg> &gradient,
                                     const shared_ptr<ProcessingImg> &gradientAngle,
                                     const vector<Point> &points) {
    vector<shared_ptr<AbstractDescriptor>> descriptors;
    descriptors.reserve(points.size());
    for (const auto &item: points)
        descriptors.push_back(
                make_shared<Histogram>(gradient, gradientAngle, item, grid_size, cell_size, basket_size));
    return descriptors;
}