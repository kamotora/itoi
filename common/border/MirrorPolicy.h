#ifndef ITOI_MIRRORPOLICY_H
#define ITOI_MIRRORPOLICY_H

#include "IBorderPolicy.h"
#include "../ProcessingImg.h"
#include <QString>

class MirrorPolicy : public IBorderPolicy{
protected:
    double bordered_pixel(ProcessingImg &image, int x, int y) override;
};


#endif //ITOI_MIRRORPOLICY_H
