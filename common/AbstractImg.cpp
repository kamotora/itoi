#include "AbstractImg.h"


int AbstractImg::to_index(int x, int y) const {
    if (x >= width || x < 0 || y >= height || y < 0)
        throw std::invalid_argument("error to convect x, y to index");
    return x + y * width;
}


int AbstractImg::get_size() const {
    if (width == 0 || height == 0)
        throw std::invalid_argument("invalid size");
    return width * height;
}