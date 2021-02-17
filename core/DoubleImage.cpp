#include "DoubleImage.h"

int DoubleImage::getHeight() const {
    return height;
}

int DoubleImage::getWidth() const {
    return width;
}

void DoubleImage::setPixel(int x, int y, double value) {
    setPixel(x + y * width, value);
}

void DoubleImage::setPixel(int i, double value) {
    data.get()[i] = value;
}

void DoubleImage::setPixel(int i, unsigned char value) {
    data.get()[i] = value;
}

double DoubleImage::getPixel(int x, int y) {
    return getPixel(x + y * width);
}

DoubleImage &DoubleImage::operator=(DoubleImage &&other) noexcept {
    copy(other);
    return *this;
}

void DoubleImage::copy(DoubleImage &other) {
    width = other.getWidth();
    height = other.getHeight();
    data = make_unique<double[]>(getSize());
    for (int i = 0; i < getSize(); i++) {
        setPixel(i, other.getPixel(i));
    }
}

DoubleImage::DoubleImage(DoubleImage &&other) noexcept {
    copy(other);
}

double DoubleImage::getPixel(int i) {
    return data.get()[i];
}

DoubleImage::DoubleImage(vector<double> array, const int width, const int height) {
    this->width = width;
    this->height = height;
    this->data = make_unique<double[]>(array.size());
    for(int i = 0; i < array.size(); i++)
        data.get()[i] = array[i];
}

DoubleImage::DoubleImage(unique_ptr<double[]> byteSource, const int width, const int height) {
    this->width = width;
    this->height = height;
    this->data = std::move(byteSource);
}

//void DoubleImage::applyFunc(const std::function<double(double)>& f) {
//    for (int i = 0; i < width * height; ++i) {
//        f(getPixel(i));
//    }
//}

DoubleImage::DoubleImage(int width, int height) {
    this->width = width;
    this->height = height;
    data = std::make_unique<double[]>(width * height);
}

const unique_ptr<double[]> &DoubleImage::getData() {
    return data;
}

int DoubleImage::getSize() {
    return width * height;
}

DoubleImage DoubleImage::normalize(float diff) {
    return DoubleImage(Helper::normalizeMinMax(data, getSize(), diff), width, height);
}

void DoubleImage::applyFunc(const function<double(double)> &f) {
    for(int i = 0; i < getSize(); i++)
        setPixel(i, f(getPixel(i)));
}

