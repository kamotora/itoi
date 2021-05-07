#ifndef ITOI_LAB5_H
#define ITOI_LAB5_H


#include <QPixmap>
#include "../distortions/Distortion.h"
#include "../core/InputImage.h"
#include "../distortions/Shift.h"
#include "../descriptor/SiftCreator.h"
#include "../distortions/Contrast.h"
#include "../distortions/Noise.h"
#include "../distortions/Rotate.h"

class Lab5 {
private:
    const QString &imageName, &ext;
    int windowSize, pointsCount, gridSize, cellSize, basketsSize;
    shared_ptr<InputImage> inputImage;
public:
    Lab5(const QString &imageName, const QString &ext, int windowSize, int basketsSize, int pointsCount, int gridSize,
         int cellSize) : imageName(imageName), ext(ext), windowSize(windowSize), pointsCount(pointsCount),
                         basketsSize(basketsSize),
                         gridSize(gridSize), cellSize(cellSize) {
        this->inputImage = make_shared<InputImage>(InputImage::fromResources(imageName + ext));
    }

    static void demo() {
        Lab5("lenna", ".png", 3, 8,
             32, 4, 2)
                .workWithRotatedRight(40)
                ->workWithRotatedLeft(60)
//                ->workWithContrast()
                ;

//
//        Lab5("butterfly", ".jpg", 4, 8,
//             64, 4, 4)
//                .workWithShiftedXY(60)
//                ->workWithContrast()
//                ->workWithShiftedX(80);
//
//        Lab5("shrek", ".jpg", 4, 8,
//             24, 2, 2)
//                .workWithContrast()
//                ->workWithShiftedXY(30)
//                ->workWithShiftedY(50);
    }

    Lab5 *workWithShiftedXY(int diff = 30) {
        auto firstInput = createShiftedInputImage(diff, diff);
        auto secondInput = createShiftedInputImage(-diff, -diff);
        work(firstInput, secondInput);
        return this;
    }

    Lab5 *workWithShiftedY(int diffY = 50) {
        auto firstInput = createShiftedInputImage(0, diffY);
        auto secondInput = createShiftedInputImage(0, -diffY);
        work(firstInput, secondInput);
        return this;
    }

    Lab5 *workWithShiftedX(int diffX = 50) {
        auto firstInput = createShiftedInputImage(diffX, 0);
        auto secondInput = createShiftedInputImage(-diffX, 0);
        work(firstInput, secondInput);
        return this;
    }

    Lab5 *workWithContrast(double contrastFactor = 1.3) {
        work(inputImage, createWithDistortion(make_shared<Contrast>(contrastFactor)));
        return this;
    }

    Lab5 *workWithRotatedRight(double angle) {
        work(inputImage, createWithDistortion(make_shared<Rotate>(angle)));
        return this;
    }

    Lab5 *workWithRotatedLeft(double angle) {
        work(inputImage, createWithDistortion(make_shared<Rotate>(-angle)));
        return this;
    }

    Lab5 *workWithSameImages() {
        work(inputImage, inputImage);
        return this;
    }

    void work(const shared_ptr<InputImage> &firstInput, const shared_ptr<InputImage> &secondInput) {
        auto firstDouble = make_shared<DoubleImage>(firstInput->toDoubleImage());
        auto secondDouble = make_shared<DoubleImage>(secondInput->toDoubleImage());
        auto matching = SiftCreator::create(firstDouble, secondDouble, gridSize, cellSize, basketsSize,
                                                 pointsCount);
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


#endif //ITOI_LAB5_H
