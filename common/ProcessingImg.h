#ifndef ITOI_PROCESSINGIMG_H
#define ITOI_PROCESSINGIMG_H

#include <memory>
#include "AbstractImg.h"
#include "vector"

using namespace std;

class ProcessingImg : public AbstractImg {
private:
    unique_ptr<double[]> data;
public:
    ProcessingImg(unique_ptr<double[]> byteSource, int _width, int _height);

    ProcessingImg(vector<double> array, int _width, int _height);

    ProcessingImg(int _width, int _height);

    ProcessingImg(ProcessingImg const &other);

    ProcessingImg() = default;

    ProcessingImg &operator=(ProcessingImg &&other) noexcept;

    void set_pixel(int x, int y, double value);

    [[nodiscard]]
    virtual double pixel(int x, int y) const;

    [[nodiscard]]
    virtual double pixel(int i) const;

    void set_pixel(int i, double value);

    void copy(ProcessingImg &other);

    ProcessingImg normalize(float diff = 1.0);


};


#endif //ITOI_PROCESSINGIMG_H
