
#ifndef IP_SHIFT_H
#define IP_SHIFT_H

#include "Distortion.h"
#include "../common/ProcessingImg.h"

using namespace std;

class Shift : public Distortion {
public:
    Shift(int x, int y) : _x(x), _y(y) {};

    QPixmap distort(QPixmap pixmap) override;

    inline QString getName() override { return QStringLiteral("SHIFTED_X_%1_Y_%2").arg(_x).arg(_y); }

private:
    int _x;
    int _y;
};


#endif //IP_SHIFT_H
