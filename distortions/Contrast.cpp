
#include "Contrast.h"

QPixmap Contrast::distort(QPixmap pixmap) {
    int w = pixmap.width();
    int h = pixmap.height();
    QImage src = pixmap.toImage();
    QImage res = QImage(w, h, QImage::Format_RGB32);
    for (int x = 0; x < w; ++x) {
        for (int y = 0; y < h; ++y) {
            QColor color = src.pixelColor(x, y);
            int r, g, b;
            color.getRgb(&r, &g, &b);
            res.setPixelColor(x, y, QColor(change(r), change(g), change(b), src.pixelColor(x,y).alpha()));
        }
    }
    return QPixmap::fromImage(res);
}

int Contrast::change(double value) const {
    double result = value / 255.0;
    result -= 0.5;
    result *= _factor;
    result += 0.5;
    result *= 255;
    return (int) Helper::simpleRound(result);
}

