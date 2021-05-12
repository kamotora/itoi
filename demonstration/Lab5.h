#ifndef ITOI_LAB5_H
#define ITOI_LAB5_H


#include <QPixmap>
#include "../distortions/Distortion.h"
#include "../core/InputImage.h"
#include "../distortions/Shift.h"
#include "../descriptor/SiftCreator.h"
#include "../descriptor/HistogramCreator.h"
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
                         basketsSize(basketsSize), gridSize(gridSize), cellSize(cellSize) {
        this->inputImage = make_shared<InputImage>(InputImage::fromResources(imageName + ext));
    }

    void workSift(const shared_ptr<InputImage> &firstInput, const shared_ptr<InputImage> &secondInput) {
        auto firstDouble = make_shared<DoubleImage>(firstInput->toDoubleImage());
        auto secondDouble = make_shared<DoubleImage>(secondInput->toDoubleImage());
        auto matching = SiftCreator::create(firstDouble, secondDouble, gridSize, cellSize, basketsSize,
                                            pointsCount);
        auto resultImage = DescriptorUtil::markMatching(firstDouble, secondDouble, matching);
        InputImage::saveToResources(resultImage,
                                    QStringLiteral("%1_MATCHING_SIFT_%2%3")
                                            .arg(firstInput->getName())
                                            .arg(secondInput->getName())
                                            .arg(ext));
    }

    void workHog(const shared_ptr<InputImage> &firstInput, const shared_ptr<InputImage> &secondInput) {
        auto firstDouble = make_shared<DoubleImage>(firstInput->toDoubleImage());
        auto secondDouble = make_shared<DoubleImage>(secondInput->toDoubleImage());
        auto matching = HistogramCreator::create(firstDouble, secondDouble, gridSize, cellSize, basketsSize,
                                                 pointsCount);
        auto resultImage = DescriptorUtil::markMatching(firstDouble, secondDouble, matching);
        InputImage::saveToResources(resultImage,
                                    QStringLiteral("%1_MATCHING_HISTOGRAM_%2%3")
                                            .arg(firstInput->getName())
                                            .arg(secondInput->getName())
                                            .arg(ext));
    }

    static void demo() {
        Lab5("lenna", ".png", 3, 32, 50, 16, 4)
                .workSiftWithRotatedRight(45)
//                ->workSiftWithRotatedLeft(30)
//                ->workSiftWithRotatedRight(90)
//                ->workSiftWithRotatedLeft(180)
//                ->workSiftWithShiftedXY(40)
//                ->workHogWithShiftedXY(40)
//                ->workHogWithRotatedRight(90)
                ->workHogWithContrast()
                ->workSiftWithContrast()
                ;
//
//        Lab5("shrek", ".jpg", 3, 32, 30, 16, 4)
//                .workSiftWithRotatedRight(45)
//                ->workSiftWithRotatedRight(90)
//                ->workSiftWithRotatedRight(120)
//                ->workSiftWithShiftedXY(35)
//                ->workHogWithShiftedXY(35)
//                ;
//
//        Lab5("butterfly", ".jpg", 3, 32, 100, 16, 4)
//                .workSiftWithRotatedRight(37)
//                ->workSiftWithRotatedRight(90)
//                ->workSiftWithRotatedLeft(180)
//                ->workSiftWithShiftedXY(60)
//                ->workHogWithShiftedXY(60)
//                ->workHogWithRotatedLeft(180)
//                ;
    }

    Lab5 *workSiftWithRotatedRight(double angle) {
        workSift(inputImage, createWithDistortion(make_shared<Rotate>(angle)));
        return this;
    }

    Lab5 *workHogWithRotatedRight(double angle) {
        workHog(inputImage, createWithDistortion(make_shared<Rotate>(angle)));
        return this;
    }

    Lab5 *workSiftWithRotatedLeft(double angle) {
        workSift(inputImage, createWithDistortion(make_shared<Rotate>(-angle)));
        return this;
    }

    Lab5 *workHogWithRotatedLeft(double angle) {
        workHog(inputImage, createWithDistortion(make_shared<Rotate>(-angle)));
        return this;
    }

    Lab5 *workSiftWithShiftedXY(int value) {
        auto shifted = createShifted(value);
        workSift(shifted.first,shifted.second);
        return this;
    }

    Lab5 *workHogWithShiftedXY(int value) {
        auto shifted = createShifted(value);
        workHog(shifted.first,shifted.second);
        return this;
    }

    shared_ptr<InputImage> createShiftedInputImage(int shiftX, int shiftY) {
        return createWithDistortion(make_shared<Shift>(shiftX, shiftY));
    }

    pair<shared_ptr<InputImage>, shared_ptr<InputImage>> createShifted(int diff = 30) {
        auto firstInput = createShiftedInputImage(diff, diff);
        auto secondInput = createShiftedInputImage(-diff, -diff);
        return make_pair(firstInput, secondInput);
    }

    Lab5 *workHogWithContrast(double contrastFactor = 1.5) {
        workHog(inputImage, createWithDistortion(make_shared<Contrast>(contrastFactor)));
        return this;
    }

    Lab5 *workSiftWithContrast(double contrastFactor = 1.5) {
        workSift(inputImage, createWithDistortion(make_shared<Contrast>(contrastFactor)));
        return this;
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
