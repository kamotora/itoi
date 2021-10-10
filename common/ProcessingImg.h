#ifndef ITOI_PROCESSINGIMG_H
#define ITOI_PROCESSINGIMG_H

#include <memory>
#include "AbstractImg.h"
#include "vector"

using namespace std;

class ProcessingImg : public AbstractImg {
private:
    int width, height;
    unique_ptr<double[]> data;
public:
    ProcessingImg(unique_ptr<double[]> byteSource, int width, int height);

    ProcessingImg(vector<double> array, int width, int height);

    ProcessingImg(int width, int height);

    ProcessingImg(ProcessingImg const &other);

    ProcessingImg() = default;

    ProcessingImg &operator=(ProcessingImg &&other) noexcept;

    void set_pixel(int x, int y, double value);

    virtual double get_pixel(int x, int y) const;

    virtual double get_pixel(int i) const;

    void set_pixel(int i, double value);

    void copy(ProcessingImg &other);

    ProcessingImg normalize(float diff = 1.0);

    [[nodiscard]]
    int get_height() const;

    [[nodiscard]]
    int get_width() const;
};


#endif //ITOI_PROCESSINGIMG_H
