//
// Created by kamotora on 31.03.2021.
//

#ifndef ITOI_LAB3_H
#define ITOI_LAB3_H


#include <QString>
#include "../core/InputImage.h"
#include "../point/Moravec.h"
#include "../point/Harris.h"
#include "../descriptor/DescriptorUtil.h"

class Lab3 {
private:
    const QString &imageName, &ext;
    int pointsCount = 100;
    int windowSize = 4;
    double harrisThresholdCoef = 0.2;
    double moravecThresholdCoef = 0.2;
    InputImage inputImage;
public:
    Lab3(const QString &imageName, const QString &ext) : imageName(imageName), ext(ext) {
        this->inputImage = InputImage::fromResources(imageName + ext);
    }

public:
    static void demo() {

        Lab3("shrek", ".jpg").workMoravec()->workHarris();


        Lab3("cat_dog", ".jpg").workMoravec()->workHarris();

        Lab3("cat_dog_brighted", ".jpg").workMoravec()->workHarris();

        Lab3("cat_dog_rotated", ".jpg").workMoravec()->workHarris();

        Lab3("cat_dog_noised", ".png").workMoravec()->workHarris();

        Lab3("cat_dog_mirror", ".jpg").workMoravec()->workHarris();


//
//        Lab3("lenna", ".png").workMoravec()->workHarris();
//
//        Lab3("lenna_brighted", ".png").workMoravec()->workHarris();
//
//        Lab3("lenna_rotated", ".png").workMoravec()->workHarris();
//
//        Lab3("lenna_noised", ".png").workMoravec()->workHarris();
//
//        Lab3("lenna_mirror", ".png").workMoravec()->workHarris();
    }

    Lab3 *workMoravec() {
        cout << "start moravec processing " << imageName.toStdString() << endl;
        auto inputDouble = inputImage.toDoubleImage();
        auto moravec = new Moravec(make_shared<DoubleImage>(inputDouble), imageName, ext);
        auto points = moravec->findPoints(pointsCount, windowSize, moravecThresholdCoef);
        auto result = InputImage::fromDoubleImage(inputDouble).getImage();
        InputImage::saveToResources(DescriptorUtil::markPoints(points, result),
                                    imageName + "_moravec_" + QString::fromStdString(to_string(pointsCount)) + ext);
        return this;
    }

    Lab3 *workHarris() {
        cout << "start harris processing " << imageName.toStdString() << endl;
        auto inputDouble = inputImage.toDoubleImage();
        auto harris = new Harris(make_shared<DoubleImage>(inputDouble), imageName, ext);
        auto points = harris->findPoints(pointsCount, 3, harrisThresholdCoef);
        auto result = InputImage::fromDoubleImage(inputDouble).getImage();
        InputImage::saveToResources(DescriptorUtil::markPoints(points, result),
                                    imageName + "_harris_" + QString::fromStdString(to_string(pointsCount)) + ext);
        return this;
    }
};


#endif //ITOI_LAB3_H
