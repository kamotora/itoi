#include "ProcessingImg.h"

void ProcessingImg::set_pixel(int x, int y, double value) {
    set_pixel(to_index(x, y), value);
}

void ProcessingImg::set_pixel(int i, double value) {
    data[i] = value;
}

double ProcessingImg::pixel(int x, int y) const {
    return pixel(to_index(x, y));
}

ProcessingImg &ProcessingImg::operator=(ProcessingImg &&other) noexcept {
    copy(other);
    return *this;
}

void ProcessingImg::copy(ProcessingImg &other) {
    _width = other.width();
    _height = other.height();
    data.reset();
    data = make_unique<double[]>(size());
    for (int i = 0; i < size(); i++) {
        set_pixel(i, other.pixel(i));
    }
}

//ProcessingImg::ProcessingImg(ProcessingImg &&other) noexcept {
//    copy(other);
//}

double ProcessingImg::pixel(int i) const {
    return data[i];
}

ProcessingImg::ProcessingImg(vector<double> array, const int _width, const int _height) : AbstractImg(_width, _height) {
    this->data = make_unique<double[]>(array.size());
    for (int i = 0; i < array.size(); i++)
        set_pixel(i, array[i]);
}

ProcessingImg::ProcessingImg(unique_ptr<double[]> byteSource, const int _width, const int _height) : AbstractImg(_width,
                                                                                                                 _height) {
    this->data = std::move(byteSource);
}

ProcessingImg::ProcessingImg(int _width, int _height) : AbstractImg(_width, _height) {
    this->data = std::make_unique<double[]>(size());
}

ProcessingImg ProcessingImg::normalize(float diff) {
    double max = data[0];
    double min = data[0];
    for (int i = 0; i < size(); i++) {
        if (data[i] < min) min = data[i];
        if (data[i] > max) max = data[i];
    }
    // normalizing
    auto res = make_unique<double[]>(size());
    for (int i = 0; i < size(); i++) {
        res[i] = (data[i] - min) * (diff / (max - min));
    }
    return {std::move(res), _width, _height};
}

ProcessingImg::ProcessingImg(ProcessingImg const &other) : AbstractImg(other.width(), other.height()) {
    data = make_unique<double[]>(size());
    for (int i = 0; i < size(); i++) {
        set_pixel(i, other.pixel(i));
    }
}

