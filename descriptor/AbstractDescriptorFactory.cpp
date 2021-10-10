#include "AbstractDescriptorFactory.h"

const shared_ptr<ProcessingImg> &AbstractDescriptorFactory::get_first_image() const {
    return firstImage;
}

const shared_ptr<ProcessingImg> &AbstractDescriptorFactory::get_second_image() const {
    return secondImage;
}

shared_ptr<ProcessingImg>
AbstractDescriptorFactory::count_gradient(const shared_ptr<ProcessingImg> &first,
                                          const shared_ptr<ProcessingImg> &second,
                                          double (*counterFunc)(double, double)) {
    if (first->height() != second->height() || first->width() != second->width())
        throw invalid_argument("different images size");
    auto gradient = make_shared<ProcessingImg>(first->width(), first->height());

    for (int i = 0; i < gradient->size(); i++) {
        gradient->set_pixel(i, counterFunc(first->pixel(i), second->pixel(i)));
    }

    return gradient;
}

shared_ptr<ProcessingImg>
AbstractDescriptorFactory::count_gradient(const shared_ptr<ProcessingImg> &first,
                                          const shared_ptr<ProcessingImg> &second) {
    return count_gradient(first, second, [](double firstPixel, double secondPixel) {
        return sqrt((firstPixel * firstPixel) + (secondPixel * secondPixel));
    });
}

shared_ptr<ProcessingImg>
AbstractDescriptorFactory::count_gradient_angle(const shared_ptr<ProcessingImg> &first,
                                                const shared_ptr<ProcessingImg> &second) {
    return count_gradient(first, second, [](double first_pixel, double second_pixel) {
        return atan2(second_pixel, first_pixel);
    });
}


shared_ptr<DescriptorPair> AbstractDescriptorFactory::match(const vector<shared_ptr<AbstractDescriptor>> &first,
                                                            const vector<shared_ptr<AbstractDescriptor>> &second,
                                                            bool need_show_all) {
    vector<pair<Point, Point>> pointsMatching;

    for (const auto &item: first) {
        auto closest = getClosest(item, second, need_show_all);
        if (closest == nullptr)
            continue;
        pointsMatching.emplace_back(item->get_point(), closest->get_point());
    }

    return make_shared<DescriptorPair>(pointsMatching, first, second);
}

shared_ptr<AbstractDescriptor> AbstractDescriptorFactory::getClosest(const shared_ptr<AbstractDescriptor> &descriptor,
                                                                     const vector<shared_ptr<AbstractDescriptor>> &descriptors,
                                                                     bool need_show_all) {
    vector<double> distances;
    distances.reserve(descriptors.size());
    for (const auto &descriptorB: descriptors) {
        distances.push_back(dist(descriptor, descriptorB));
    }
    int a = get_min_ind(distances, -1);
    if (need_show_all)
        return descriptors[a];
    int b = get_min_ind(distances, a);

    double r = distances[a] / distances[b];
    return (r <= MAX_CLOSEST) ? descriptors[a] : nullptr;
}


int AbstractDescriptorFactory::get_min_ind(vector<double> distances, int exclude_idx) {
    int idx = -1;
    for (int i = 0; i < distances.size(); i++)
        if (i != exclude_idx && (idx == -1 || distances[i] < distances[idx]))
            idx = i;

    return idx;
}

double AbstractDescriptorFactory::dist(const shared_ptr<AbstractDescriptor> &first,
                                       const shared_ptr<AbstractDescriptor> &second) {
    auto first_desc = first->get_descriptor();
    auto second_desc = second->get_descriptor();
    if (first_desc.size() != second_desc.size())
        throw invalid_argument("size of descriptors not equal");
    double sum = 0;
    for (int i = 0; i < first_desc.size(); i++) {
        sum += (first_desc[i] - second_desc[i]) * (first_desc[i] - second_desc[i]);
    }
    return sqrt(sum);
}