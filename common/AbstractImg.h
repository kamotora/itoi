#ifndef ITOI_ABSTRACTIMG_H
#define ITOI_ABSTRACTIMG_H

#include <stdexcept>

class AbstractImg {
protected:
    int width, height;
public:
    [[nodiscard]]
    int to_index(int x, int y) const;

    [[nodiscard]]
    int get_size() const;
};


#endif //ITOI_ABSTRACTIMG_H
