#ifndef ITOI_IBORDERPOLICY_H
#define ITOI_IBORDERPOLICY_H

#include <QString>
#include "memory"
#include "../ProcessingImg.h"

using namespace std;

class IBorderPolicy {
protected:
    static bool isBorder(ProcessingImg &image, int x, int y);
    IBorderPolicy() = default;

    virtual double bordered_pixel(ProcessingImg &image, int x, int y) = 0;
public:
    double get_pixel(ProcessingImg &image, int x, int y);
    virtual QString to_string() = 0;
};


#endif //ITOI_IBORDERPOLICY_H
