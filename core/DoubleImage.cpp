#include "DoubleImage.h"

int DoubleImage::getHeight() const {
    return height;
}

int DoubleImage::getWidth() const {
    return width;
}

void DoubleImage::setPixel(int x, int y, double value) {
    setPixel(xyToI(x, y), value);
}

void DoubleImage::setPixel(int i, double value) {
    data[i] = value;
}

double DoubleImage::getPixel(int x, int y) const {
    return getPixel(xyToI(x, y));
}

DoubleImage &DoubleImage::operator=(DoubleImage &&other) noexcept {
    copy(other);
    return *this;
}

void DoubleImage::copy(DoubleImage &other) {
    width = other.getWidth();
    height = other.getHeight();
    data.reset();
    data = make_unique<double[]>(getSize());
    for (int i = 0; i < getSize(); i++) {
        setPixel(i, other.getPixel(i));
    }
}

//DoubleImage::DoubleImage(DoubleImage &&other) noexcept {
//    copy(other);
//}

double DoubleImage::getPixel(int i) const {
    return data[i];
}

DoubleImage::DoubleImage(vector<double> array, const int width, const int height) {
    this->width = width;
    this->height = height;
    this->data = make_unique<double[]>(array.size());
    for (int i = 0; i < array.size(); i++)
        setPixel(i, array[i]);
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
    this->data = std::make_unique<double[]>(getSize());
//    fill(data.get(), data.get() + getSize(), 0);
}

const unique_ptr<double[]> &DoubleImage::getData() {
    return data;
}

int DoubleImage::getSize() const {
    if (width == 0 || height == 0)
        throw invalid_argument("invalid image params");
    return width * height;
}

DoubleImage DoubleImage::normalize(float diff) {
    return DoubleImage(Helper::normalizeMinMax(data, getSize(), diff), width, height);
}

void DoubleImage::applyFunc(const function<double(double)> &f) {
    for (int i = 0; i < getSize(); i++)
        setPixel(i, f(getPixel(i)));
}

DoubleImage::DoubleImage(DoubleImage const &other) {
    width = other.getWidth();
    height = other.getHeight();
    data = make_unique<double[]>(getSize());
    for (int i = 0; i < getSize(); i++) {
        setPixel(i, other.getPixel(i));
    }
}

int DoubleImage::xyToI(int x, int y) const {
    if (x >= width || x < 0 || y >= height || y < 0)
        throw invalid_argument("invalid (x,y)");
    return x + y * width;
}

