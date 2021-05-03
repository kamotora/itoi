
#include "Shift.h"

QPixmap Shift::distort(QPixmap pixmap) {
    QRect r = pixmap.rect();
    r.moveTo(_x, _y);
    return pixmap.copy(r);
}