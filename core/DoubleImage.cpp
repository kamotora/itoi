#include "DoubleImage.h"

DoubleImage::DoubleImage(InputImage &inputImage) {
    this->width = inputImage.getWidth();
    this->height = inputImage.getHeight();
    data = std::make_unique<double[]>(width * height);
    for (int i = 0; i < width * height; i++) {
        setPixel(i, inputImage.getPixel(i));
    }
}


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
    data = make_unique<double[]>(width * height);
    for (int i = 0; i < width * height; i++) {
        setPixel(i, other.getPixel(i));
    }
}

DoubleImage::DoubleImage(DoubleImage &&other) noexcept {
    copy(other);
}

double DoubleImage::getPixel(int i) {
    return data.get()[i];
}

DoubleImage::DoubleImage(unique_ptr<double[]> byteSource, const int width, const int height) {
    this->width = width;
    this->height = height;
    this->data = std::move(byteSource);
}

void DoubleImage::applyFunc(const std::function<double(double)>& f) {
    for (int i = 0; i < width * height; ++i) {
        f(getPixel(i));
    }
}
