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
    if (first->get_height() != second->get_height() || first->get_width() != second->get_width())
        throw invalid_argument("different images size");
    auto gradient = make_shared<ProcessingImg>(first->get_width(), first->get_height());

    for (int i = 0; i < gradient->get_size(); i++) {
        auto firstPixel = first->get_pixel(i);
        auto secondPixel = second->get_pixel(i);
        gradient->set_pixel(i, counterFunc(firstPixel, secondPixel));
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
    return count_gradient(first, second, [](double firstPixel, double secondPixel) {
        return atan2(secondPixel, firstPixel);
    });
}


shared_ptr<DescriptorPair> AbstractDescriptorFactory::match(const vector<shared_ptr<AbstractDescriptor>> &firstList,
                                                            const vector<shared_ptr<AbstractDescriptor>> &secondList,
                                                            bool showAll) {
    vector<pair<Point, Point>> pointsMatching;

    for (const auto &item: firstList) {
        auto closest = getClosest(item, secondList, showAll);
        if (closest == nullptr)
            continue;
        pointsMatching.emplace_back(item->getPoint(), closest->getPoint());
    }

    return make_shared<DescriptorPair>(pointsMatching, firstList, secondList);
}

shared_ptr<AbstractDescriptor> AbstractDescriptorFactory::getClosest(const shared_ptr<AbstractDescriptor> &descriptor,
                                                                     const vector<shared_ptr<AbstractDescriptor>> &descriptors,
                                                                     bool showAll) {
    vector<double> distances;
    distances.reserve(descriptors.size());
    for (const auto &descriptorB: descriptors) {
        distances.push_back(dist(descriptor, descriptorB));
    }
    int a = get_min_ind(distances, -1);
    if (showAll)
        return descriptors[a];
    int b = get_min_ind(distances, a);

    double r = distances[a] / distances[b];
    return (r <= MAX_CLOSEST) ? descriptors[a] : nullptr;
}


int AbstractDescriptorFactory::get_min_ind(vector<double> distances, int excludeIndex) {
    int selectedIndex = -1;
    for (int i = 0; i < distances.size(); i++)
        if (i != excludeIndex && (selectedIndex == -1 || distances[i] < distances[selectedIndex]))
            selectedIndex = i;

    return selectedIndex;
}

double AbstractDescriptorFactory::dist(const shared_ptr<AbstractDescriptor> &descriptorA,
                                       const shared_ptr<AbstractDescriptor> &descriptorB) {
    auto descA = descriptorA->getDescriptor();
    auto descB = descriptorB->getDescriptor();
    if (descA.size() != descB.size())
        throw invalid_argument("size of descriptors not equal");
    double sum = 0;
    for (int i = 0; i < descA.size(); i++) {
        sum += (descA[i] - descB[i]) * (descA[i] - descB[i]);
    }
    return sqrt(sum);
}