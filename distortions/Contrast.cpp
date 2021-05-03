
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

            double r_n = r / 255.0;
            r_n -= 0.5;
            r_n *= _factor;
            r_n += 0.5;
            r_n *= 255;
            double g_n = g / 255.0;
            g_n -= 0.5;
            g_n *= _factor;
            g_n += 0.5;
            g_n *= 255;
            double b_n = b / 255.0;
            b_n -= 0.5;
            b_n *= _factor;
            b_n += 0.5;
            b_n *= 255;
            if (r_n > 255)
                r_n = 255;
            if (r_n < 0)
                r_n = 0;
            if (g_n > 255)
                g_n = 255;
            if (g_n < 0)
                g_n = 0;
            if (b_n > 255)
                b = 255;
            if (b_n < 0)
                b_n = 0;
            res.setPixelColor(x, y, qRgb((int) r_n, (int) g_n, (int) b_n));
        }
    }
    return QPixmap::fromImage(res);
}

