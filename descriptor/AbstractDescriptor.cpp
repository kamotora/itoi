//
// Created by kamotora on 28.04.2021.
//

#include "AbstractDescriptor.h"

void AbstractDescriptor::normalize() {
    double sum = accumulate(descriptor.begin(), descriptor.end(), 0.0);;
    if (abs(sum) < 1e-3)
        return;
    vector<double> normalized(descriptor.size());
    transform(descriptor.begin(), descriptor.end(),
              normalized.begin(), [sum](double &operand) { return operand / sum; });
    setDescriptor(normalized);
}

double AbstractDescriptor::distance(const shared_ptr<AbstractDescriptor> &descriptorA,
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

const vector<double> &AbstractDescriptor::getDescriptor() const {
    return descriptor;
}

void AbstractDescriptor::setDescriptor(vector<double> newDescriptor) {
    AbstractDescriptor::descriptor = newDescriptor;
}

AbstractDescriptor::AbstractDescriptor(Point point) : point(point) {

}

const Point &AbstractDescriptor::getPoint() const {
    return point;
}
