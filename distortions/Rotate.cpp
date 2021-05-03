
#include "Rotate.h"

inline QPixmap Rotate::distort(QPixmap pixmap) {
    return pixmap.transformed(QMatrix().rotate(_degrees));
}
