#include "SiftFactory.h"

SiftFactory::SiftFactory(const shared_ptr<ProcessingImg> &firstImage,
                         const shared_ptr<ProcessingImg> &secondImage,
                         int gridSize, int cellSize, int basketSize, int pointsCount)
        : AbstractDescriptorFactory(firstImage, secondImage, gridSize, cellSize, basketSize, pointsCount) {
    this->gauss_kernel = make_shared<pair<ProcessingImg, ProcessingImg>>(
            Kernels::gauss_separable_xy(gridSize * cellSize / 2));
}

shared_ptr<DescriptorPair>
SiftFactory::create(const shared_ptr<ProcessingImg> &first, const shared_ptr<ProcessingImg> &second,
                    int _gridSize,
                    int _cellSize, int _basketSize, int _pointsCount) {
    auto creator = SiftFactory(first, second, _gridSize, _cellSize, _basketSize, _pointsCount);

    return match(creator.create_descriptors(creator.get_first_image()),
                 creator.create_descriptors(creator.get_second_image()));
}


vector<shared_ptr<AbstractDescriptor>>
SiftFactory::create_descriptors(const shared_ptr<ProcessingImg> &img) {
    auto x = Filter::sobel_x(img);
    auto y = Filter::sobel_y(img);
    auto gradient = count_gradient_angle(x, y);
    auto gradientAngle = count_gradient_angle(x, y);
    auto points = (new Harris(img))->find_points(pointsCount);
    return create_descriptors(gradient, gradientAngle, points);
}


vector<shared_ptr<AbstractDescriptor>>
SiftFactory::create_descriptors(const shared_ptr<ProcessingImg> &gradient,
                                const shared_ptr<ProcessingImg> &gradient_angle,
                                const vector<Point> &points) const {
    vector<shared_ptr<AbstractDescriptor>> descriptors;
    for (const auto &point: points) {
        auto angles = calculate_angles(gradient, gradient_angle, point);
        for (const auto &angle: angles) {
            auto descriptor = Sift(gradient, gradient_angle, Point(point, angle),
                                   grid_size, cell_size, basket_size);
            descriptors.push_back(make_shared<AbstractDescriptor>(descriptor));
        }
    }
    return descriptors;
}

vector<double> SiftFactory::calculate_angles(const shared_ptr<ProcessingImg> &gradient,
                                             const shared_ptr<ProcessingImg> &gradient_angle,
                                             const Point &point) const {
    auto basket = Basket(BASKET_SIZE);
    int border = grid_size * cell_size;
    int half_border = border / 2;
    for (int x = -half_border; x < border - half_border; x++) {
        for (int y = -half_border; y < border - half_border; y++) {
            int real_x = point.get_x() + x;
            int real_y = point.get_y() + y;
            double phi = DEFAULT_POLICY->get_pixel(*gradient_angle, real_x, real_y);
            double gradient_value = DEFAULT_POLICY->get_pixel(*gradient, real_x, real_y);
            double gauss_value = Filter::get_separable_value(*gauss_kernel, half_border + x, half_border + y);

            basket.add(phi, gradient_value * gauss_value);
        }
    }

    auto peeks = basket.get_highest_angles();
    return peeks;
}



