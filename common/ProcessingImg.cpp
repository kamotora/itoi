#include "ProcessingImg.h"

int ProcessingImg::get_height() const {
    return height;
}

int ProcessingImg::get_width() const {
    return width;
}

void ProcessingImg::set_pixel(int x, int y, double value) {
    set_pixel(to_index(x, y), value);
}

void ProcessingImg::set_pixel(int i, double value) {
    data[i] = value;
}

double ProcessingImg::get_pixel(int x, int y) const {
    return get_pixel(to_index(x, y));
}

ProcessingImg &ProcessingImg::operator=(ProcessingImg &&other) noexcept {
    copy(other);
    return *this;
}

void ProcessingImg::copy(ProcessingImg &other) {
    width = other.get_width();
    height = other.get_height();
    data.reset();
    data = make_unique<double[]>(get_size());
    for (int i = 0; i < get_size(); i++) {
        set_pixel(i, other.get_pixel(i));
    }
}

//ProcessingImg::ProcessingImg(ProcessingImg &&other) noexcept {
//    copy(other);
//}

double ProcessingImg::get_pixel(int i) const {
    return data[i];
}

ProcessingImg::ProcessingImg(vector<double> array, const int width, const int height) {
    this->width = width;
    this->height = height;
    this->data = make_unique<double[]>(array.size());
    for (int i = 0; i < array.size(); i++)
        set_pixel(i, array[i]);
}

ProcessingImg::ProcessingImg(unique_ptr<double[]> byteSource, const int width, const int height) {
    this->width = width;
    this->height = height;
    this->data = std::move(byteSource);
}

ProcessingImg::ProcessingImg(int width, int height) {
    this->width = width;
    this->height = height;
    this->data = std::make_unique<double[]>(get_size());
}

ProcessingImg ProcessingImg::normalize(float diff) {
    double max = data[0];
    double min = data[0];
    for (int i = 0; i < get_size(); i++) {
        if (data[i] < min) min = data[i];
        if (data[i] > max) max = data[i];
    }
    // normalizing
    auto res = make_unique<double[]>(get_size());
    for (int i = 0; i < get_size(); i++) {
        res[i] = (data[i] - min) * (diff / (max - min));
    }
    return {std::move(res), width, height};
}

ProcessingImg::ProcessingImg(ProcessingImg const &other) {
    width = other.get_width();
    height = other.get_height();
    data = make_unique<double[]>(get_size());
    for (int i = 0; i < get_size(); i++) {
        set_pixel(i, other.get_pixel(i));
    }
}

