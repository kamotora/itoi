//
// Created by kamotora on 31.03.2021.
//

#ifndef ITOI_LAB3_H
#define ITOI_LAB3_H


#include <QString>
#include "../core/InputImage.h"
#include "../point/Moravec.h"
#include "../point/Harris.h"

class Lab3 {
private:
    const QString &imageName, &ext;
    int pointsCount = 1000;
    int windowSize = 4;
    double harrisThresholdCoef = 0.1;
    double moravecThresholdCoef = 0.05;
    InputImage inputImage;
public:
    Lab3(const QString &imageName, const QString &ext) : imageName(imageName), ext(ext) {
        this->inputImage = InputImage::fromResources(imageName + ext);
    }

    void drawPlus(const Point &item, QImage &image) {
        int plusSize = 2;
        for (int i = -plusSize; i <= plusSize; i++) {
            if (i == 0)
                continue;
            setPoint(item.getX() + i, item.getY(), image);
            setPoint(item.getX(), item.getY() + i, image);
        }
    }

    static pair<int, int> round(int x, int y, QImage &image) {
        int resX = (x < 0) ? 0 : (x >= image.width() ? image.width() - 1 : x);
        int resY = (y < 0) ? 0 : (y >= image.height() ? image.height() - 1 : y);
        return make_pair(resX, resY);
    }

    static void setPoint(int x, int y, QImage &image) {
        auto pair = round(x, y, image);
        image.setPixelColor(pair.first, pair.second, qRgb(255, 0, 0));
    }

public:
    static void demo() {
        Lab3("lenna", ".png").workMoravec()->workHarris();

        Lab3("lenna_brighted", ".png").workMoravec()->workHarris();

        Lab3("lenna_rotated", ".png").workMoravec()->workHarris();

        Lab3("lenna_noised", ".png").workMoravec()->workHarris();

        Lab3("lenna_mirror", ".png").workMoravec()->workHarris();
    }

    Lab3 *workMoravec() {
        auto inputDouble = inputImage.toDoubleImage();
        auto moravec = new Moravec(make_shared<DoubleImage>(inputDouble), imageName, ext);
        auto points = moravec->findPoints(windowSize, pointsCount, moravecThresholdCoef);
        auto result = InputImage::fromDoubleImage(inputDouble).getImage();
        for (const auto &item : points) {
            drawPlus(item, result);
        }
        InputImage::saveToResources(result,
                                    imageName + "_moravec_" + QString::fromStdString(to_string(pointsCount)) + ext);
        return this;
    }

    Lab3 *workHarris() {
        auto inputDouble = inputImage.toDoubleImage();
        auto harris = new Harris(make_shared<DoubleImage>(inputDouble), imageName, ext);
        auto points = harris->findPoints(3, pointsCount, harrisThresholdCoef);
        auto result = InputImage::fromDoubleImage(inputDouble).getImage();
        for (const auto &item : points) {
            drawPlus(item, result);
        }
        InputImage::saveToResources(result,
                                    imageName + "_harris_" + QString::fromStdString(to_string(pointsCount)) + ext);
        return this;
    }
};


#endif //ITOI_LAB3_H
