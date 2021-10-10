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
