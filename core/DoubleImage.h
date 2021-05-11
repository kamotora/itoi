#ifndef ITOI_DOUBLEIMAGE_H
#define ITOI_DOUBLEIMAGE_H

#include <memory>
#include "helper.h"

using namespace std;

class DoubleImage {
private:
    int width, height;
    unique_ptr<double[]> data;
public:
    DoubleImage(unique_ptr<double[]> byteSource, int width, int height);
    DoubleImage(vector<double> array, int width, int height);

    DoubleImage(int width, int height);
//    todo реализовать при необходимости
//    DoubleImage(const double *doubleSource, const int width, const int height);
//    DoubleImage(DoubleImage &&other) noexcept;
    DoubleImage(DoubleImage const &other);
    DoubleImage() = default;
    DoubleImage &operator=(DoubleImage &&other) noexcept;

    void setPixel(int x, int y, double value);

    virtual double getPixel(int x, int y) const;

    virtual double getPixel(int i) const;

    void setPixel(int i, double value);

    void copy(DoubleImage &other);

    void applyFunc(const std::function<double(double)> &f);

    [[nodiscard]]
    int getHeight() const;

    [[nodiscard]]
    int getWidth() const;

    const unique_ptr<double[]> &getData();

    [[nodiscard]]
    int getSize() const;

    DoubleImage normalize(float diff = 1.0);

    [[nodiscard]]
    int xyToI(int x, int y) const;

    vector<double> getCopyData();
};


#endif //ITOI_DOUBLEIMAGE_H
