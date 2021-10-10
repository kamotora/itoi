#include "AbstractImg.h"


int AbstractImg::to_index(int x, int y) const {
    if (x >= _width || x < 0 || y >= _height || y < 0)
        throw std::invalid_argument("error to convect x, y to index");
    return x + y * _width;
}


int AbstractImg::size() const {
    if (_width == 0 || _height == 0)
        throw std::invalid_argument("invalid size");
    return _width * _height;
}

int AbstractImg::height() const {
    return _height;
}


int AbstractImg::width() const {
    return _width;
}

AbstractImg::AbstractImg(int width, int height) : _width(width), _height(height) {}

AbstractImg::AbstractImg() {}
