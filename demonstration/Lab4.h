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
        Lab4("lenna", ".png", 4,
             36, 4, 4)
                .workWithContrast()
                ->workWithShifted20()
                ->workWithShifted50()
                ;


        Lab4("butterfly", ".jpg", 4,
             64, 4, 4)
                .workWithContrast()
                ->workWithShifted20()
                ->workWithShifted50()
                ;

        Lab4("shrek", ".jpg", 4,
             64, 4, 4)
                .workWithContrast()
                ->workWithShifted20()
                ->workWithShifted50()
                ;
    }

    Lab4 *workWithShifted20() {
        auto firstInput = createShiftedInputImage(20, 20);
        auto secondInput = createShiftedInputImage(-20, -20);
        work(firstInput, secondInput);
        return this;
    }

    Lab4 * workWithShifted50() {
        auto firstInput = createShiftedInputImage(0, 50);
        auto secondInput = createShiftedInputImage(0, -50);
        work(firstInput, secondInput);
        return this;
    }

    Lab4 * workWithContrast() {
        work(inputImage, createWithDistortion(make_shared<Contrast>(1.5)));
        return this;
    }

    void work(const shared_ptr<InputImage> &firstInput, const shared_ptr<InputImage> &secondInput) {
        auto firstDouble = make_shared<DoubleImage>(firstInput->toDoubleImage());
        auto secondDouble = make_shared<DoubleImage>(secondInput->toDoubleImage());
        auto matching = PatchCreator::processWithPatches(firstDouble, secondDouble, pointsCount, gridHalfSize,
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
