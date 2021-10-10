#ifndef ITOI_LAB5_H
#define ITOI_LAB5_H


#include <QPixmap>
#include "../distortions/Distortion.h"
#include "../common/LoadedImg.h"
#include "../distortions/Shift.h"
#include "../descriptor/SiftFactory.h"
#include "../descriptor/HistogramFactory.h"
#include "../distortions/Contrast.h"
#include "../distortions/Rotate.h"


class Lab5 {
private:
    const QString &imageName, &ext;
    int windowSize, pointsCount, gridSize, cellSize, basketsSize;
    shared_ptr<LoadedImg> loadedImg;

    Lab5(const QString &imageName, const QString &ext, int windowSize, int basketsSize, int pointsCount, int gridSize,
         int cellSize) : imageName(imageName), ext(ext), windowSize(windowSize), pointsCount(pointsCount),
                         basketsSize(basketsSize), gridSize(gridSize), cellSize(cellSize) {
        this->loadedImg = make_shared<LoadedImg>(LoadedImg::by_image_name(imageName + ext));
    }

    void sift(const shared_ptr<LoadedImg> &firstInput, const shared_ptr<LoadedImg> &secondInput) {
        auto firstDouble = make_shared<ProcessingImg>(firstInput->to_processing_img());
        auto secondDouble = make_shared<ProcessingImg>(secondInput->to_processing_img());
        auto matching = SiftFactory::create(firstDouble, secondDouble, gridSize, cellSize, basketsSize,
                                            pointsCount);
        auto resultImage = DescriptorDrawer::draw_matching(firstDouble, secondDouble, matching);
        LoadedImg::save(resultImage,
                        QStringLiteral("%1_MATCHING_SIFT_%2%3")
                                .arg(firstInput->get_name())
                                .arg(secondInput->get_name())
                                .arg(ext));
    }

    void
    hog(const shared_ptr<LoadedImg> &firstInput, const shared_ptr<LoadedImg> &secondInput, bool showAll = false) {
        auto firstDouble = make_shared<ProcessingImg>(firstInput->to_processing_img());
        auto secondDouble = make_shared<ProcessingImg>(secondInput->to_processing_img());
        auto matching = HistogramFactory::create(firstDouble, secondDouble, 8, 4, 8, pointsCount, showAll);
        auto resultImage = DescriptorDrawer::draw_matching(firstDouble, secondDouble, matching);
        LoadedImg::save(resultImage,
                        QStringLiteral("%1_MATCHING_HISTOGRAM_%2%3")
                                .arg(firstInput->get_name())
                                .arg(secondInput->get_name())
                                .arg(ext));
    }


    Lab5 *sift_with_rotated_right(double angle) {
        sift(loadedImg, createWithDistortion(make_shared<Rotate>(angle)));
        return this;
    }

    Lab5 *hog_with_rotated_right(double angle) {
        hog(loadedImg, createWithDistortion(make_shared<Rotate>(angle)), true);
        return this;
    }

    Lab5 *sift_with_rotated_left(double angle) {
        sift(loadedImg, createWithDistortion(make_shared<Rotate>(-angle)));
        return this;
    }

    Lab5 *hog_with_rotated_left(double angle) {
        hog(loadedImg, createWithDistortion(make_shared<Rotate>(-angle)), true);
        return this;
    }

    Lab5 *sift_with_shifted_xy(int value) {
        auto shifted = createShifted(value);
        sift(shifted.first, shifted.second);
        return this;
    }

    Lab5 *hog_with_shifted_xy(int value) {
        auto shifted = createShifted(value);
        hog(shifted.first, shifted.second);
        return this;
    }

    shared_ptr<LoadedImg> createShiftedLoadedImg(int shiftX, int shiftY) {
        return createWithDistortion(make_shared<Shift>(shiftX, shiftY));
    }

    pair<shared_ptr<LoadedImg>, shared_ptr<LoadedImg>> createShifted(int diff = 30) {
        auto firstInput = createShiftedLoadedImg(diff, diff);
        auto secondInput = createShiftedLoadedImg(-diff, -diff);
        return make_pair(firstInput, secondInput);
    }

    Lab5 *hog_with_contrast(double contrastFactor = 1.5) {
        hog(loadedImg, createWithDistortion(make_shared<Contrast>(contrastFactor)));
        return this;
    }

    Lab5 *sift_with_contrast(double contrastFactor = 1.5) {
        sift(loadedImg, createWithDistortion(make_shared<Contrast>(contrastFactor)));
        return this;
    }

    shared_ptr<LoadedImg> createWithDistortion(const shared_ptr<Distortion> &distortion) {
        auto result = make_shared<LoadedImg>(
                LoadedImg::copy(distortion->distort(QPixmap::fromImage(loadedImg->native_image()))));
        result->set_name(imageName + "_" + distortion->getName());
        LoadedImg::save(result->native_image(), result->get_name() + ext);
        return result;
    }

public:
    static void test() {
        Lab5("lenna", ".png", 3, 8, 50, 4, 8)
                .hog_with_rotated_right(90)
                ->hog_with_rotated_right(45)
                ->hog_with_rotated_right(30)
                ->hog_with_rotated_right(77)
                ->hog_with_rotated_right(138)
                ->hog_with_rotated_right(90)
                ->hog_with_rotated_right(180)
                ->sift_with_shifted_xy(40)
                ->sift_with_shifted_xy(40)
                ->hog_with_contrast()
                ->sift_with_contrast();

        Lab5("shrek", ".jpg", 3, 8, 30, 4, 8)
                .sift_with_rotated_right(45)
                ->sift_with_rotated_right(90)
                ->sift_with_rotated_right(120)
                ->sift_with_shifted_xy(35)
                ->sift_with_shifted_xy(35);
//
        Lab5("butterfly", ".jpg", 3, 8, 100, 4, 8)
                .sift_with_rotated_left(180)
                ->sift_with_rotated_left(37)
                ->sift_with_rotated_left(90)
                ->sift_with_rotated_left(180)
                ->sift_with_shifted_xy(60)
                ->sift_with_shifted_xy(60)
                ->sift_with_rotated_left(180);
    }
};


#endif //ITOI_LAB5_H
