#ifndef ITOI_ABSTRACTIMG_H
#define ITOI_ABSTRACTIMG_H

#include <stdexcept>

class AbstractImg {
protected:
    int _width, _height;
public:
    AbstractImg(int width, int height);

    AbstractImg();

    [[nodiscard]]
    int to_index(int x, int y) const;

    [[nodiscard]]
    int size() const;

    [[nodiscard]]
    int height() const;

    [[nodiscard]]
    int width() const;
};


#endif //ITOI_ABSTRACTIMG_H
