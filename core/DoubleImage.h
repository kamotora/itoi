#ifndef ITOI_DOUBLEIMAGE_H
#define ITOI_DOUBLEIMAGE_H

#include <memory>
#include "InputImage.h"

using namespace std;

class DoubleImage {
private:
    int width, height;
    unique_ptr<double[]> data;
public:
    explicit DoubleImage(InputImage &inputImage);

    DoubleImage(unique_ptr<double[]> byteSource, int width, int height);
//    todo реализовать при необходимости
//    DoubleImage(const DoubleImage &source);
//
//    DoubleImage(const double *doubleSource, const int width, const int height);

    DoubleImage(DoubleImage &&other) noexcept;

    DoubleImage &operator=(DoubleImage &&other) noexcept;

    void setPixel(int x, int y, double value);

    double getPixel(int x, int y);

    double getPixel(int i);

    void setPixel(int i, double value);

    void copy(DoubleImage &other);

    void applyFunc(const std::function<double(double)>& f);

    [[nodiscard]] int getHeight() const;

    [[nodiscard]] int getWidth() const;
};


#endif //ITOI_DOUBLEIMAGE_H
