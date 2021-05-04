
#include "Scale.h"

QPixmap Scale::distort(QPixmap pixmap) {
    return pixmap.scaled((int) (pixmap.width() * _coeff), (int) (pixmap.height() * _coeff));
}
