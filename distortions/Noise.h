//
// Created by kamotora on 04.05.2021.
//

#ifndef ITOI_NOISE_H
#define ITOI_NOISE_H

#include "Distortion.h"
#include <QTime>
#include "../core/helper.h"

class Noise : public Distortion {
private:
    int pointsCount;
public:
    explicit Noise(int pointsCount = 2000) : pointsCount(pointsCount) {};

    QPixmap distort(QPixmap pixmap) override {
        qsrand(QTime::currentTime().msec());
        auto result = pixmap.toImage().copy();
        auto image = pixmap.toImage();
        for (int i = 0; i < pointsCount; ++i) {
            int x = qrand() % pixmap.width();
            int y = qrand() % pixmap.height();
            auto color = image.pixelColor(x, y);
            int r = color.red() + (qrand() % 100);
            int g = color.green() + (qrand() % 100);
            int b = color.blue() + (qrand() % 100);
            result.setPixelColor(QPoint(x, y),QColor(
                                         Helper::simpleRound(r),
                                         Helper::simpleRound(g),
                                         Helper::simpleRound(b),
                                         image.pixelColor(x, y).alpha()));
        }
        return QPixmap::fromImage(result);
    }

    inline QString getName() override { return QStringLiteral("NOISE_POINTS_%1").arg(pointsCount); }
};


#endif //ITOI_NOISE_H
