//
// Created by kamotora on 03.05.2021.
//

#ifndef ITOI_LAB4_H
#define ITOI_LAB4_H


#include <QPixmap>
#include "../distortions/Distortion.h"
#include "../core/InputImage.h"
#include "../distortions/Shift.h"
#include "../descriptor/PatchCreator.h"
#include "../distortions/Contrast.h"
#include "../distortions/Noise.h"

class Lab4 {
private:
    const QString &imageName, &ext;
    int windowSize, pointsCount, gridHalfSize, cellHalfSize;
    shared_ptr<InputImage> inputImage;
public:
    Lab4(const QString &imageName, const QString &ext, int windowSize, int pointsCount, int gridHalfSize,
         int cellHalfSize) : imageName(imageName), ext(ext), windowSize(windowSize), pointsCount(pointsCount),
                             gridHalfSize(gridHalfSize), cellHalfSize(cellHalfSize) {
        this->inputImage = make_shared<InputImage>(InputImage::fromResources(imageName + ext));
    }

    static void demo() {
        Lab4("lenna", ".png", 3,
             32, 4, 2)
                .workWithShiftedXY(40)
                ->workWithShiftedY(60)
                ->workWithContrast();


        Lab4("butterfly", ".jpg", 4,
             64, 4, 4)
                .workWithShiftedXY(60)
                ->workWithContrast()
                ->workWithShiftedX(80);

        Lab4("shrek", ".jpg", 4,
             24, 2, 2)
                .workWithContrast()
                ->workWithShiftedXY(30)
                ->workWithShiftedY(50);
    }

    Lab4 *workWithShiftedXY(int diff = 30) {
        auto firstInput = createShiftedInputImage(diff, diff);
        auto secondInput = createShiftedInputImage(-diff, -diff);
        work(firstInput, secondInput);
        return this;
    }

    Lab4 *workWithShiftedY(int diffY = 50) {
        auto firstInput = createShiftedInputImage(0, diffY);
        auto secondInput = createShiftedInputImage(0, -diffY);
        work(firstInput, secondInput);
        return this;
    }
    Lab4 *workWithShiftedX(int diffX = 50) {
        auto firstInput = createShiftedInputImage(diffX, 0);
        auto secondInput = createShiftedInputImage(-diffX, 0);
        work(firstInput, secondInput);
        return this;
    }

    Lab4 *workWithContrast(double contrastFactor = 1.3) {
        work(inputImage, createWithDistortion(make_shared<Contrast>(contrastFactor)));
        return this;
    }


    Lab4 *workWithSameImages() {
        work(inputImage, inputImage);
        return this;
    }

    void work(const shared_ptr<InputImage> &firstInput, const shared_ptr<InputImage> &secondInput) {
        auto firstDouble = make_shared<DoubleImage>(firstInput->toDoubleImage());
        auto secondDouble = make_shared<DoubleImage>(secondInput->toDoubleImage());
        auto matching = PatchCreator::create(firstDouble, secondDouble, pointsCount, gridHalfSize,
                                             cellHalfSize);
        auto resultImage = DescriptorUtil::markMatching(firstDouble, secondDouble, matching);
        InputImage::saveToResources(resultImage,
                                    QStringLiteral("%1_MATCHING_%2%3")
                                            .arg(firstInput->getName())
                                            .arg(secondInput->getName())
                                            .arg(ext));
    }

    shared_ptr<InputImage> createShiftedInputImage(int shiftX, int shiftY) {
        return createWithDistortion(make_shared<Shift>(shiftX, shiftY));
    }

    shared_ptr<InputImage> createWithDistortion(const shared_ptr<Distortion> &distortion) {
        auto result = make_shared<InputImage>(
                InputImage::from(distortion->distort(QPixmap::fromImage(inputImage->getImage()))));
        result->setName(imageName + "_" + distortion->getName());
        InputImage::saveToResources(result->getImage(), result->getName() + ext);
        return result;
    }
};


#endif //ITOI_LAB4_H
