#ifndef ITOI_LAB4_H
#define ITOI_LAB4_H


#include <QPixmap>
#include "../distortions/Distortion.h"
#include "../common/LoadedImg.h"
#include "../distortions/Shift.h"
#include "../descriptor/HistogramFactory.h"

#include "../distortions/Contrast.h"


class Lab4 {
private:
    const QString &imageName, &ext;
    int windowSize, pointsCount, gridSize, cellSize, basketsSize;
    shared_ptr<LoadedImg> loadedImg;

    Lab4(const QString &imageName, const QString &ext, int windowSize, int basketsSize, int pointsCount, int gridSize,
         int cellSize) : imageName(imageName), ext(ext), windowSize(windowSize), pointsCount(pointsCount),
                         basketsSize(basketsSize),
                         gridSize(gridSize), cellSize(cellSize) {
        this->loadedImg = make_shared<LoadedImg>(LoadedImg::by_image_name(imageName + ext));
    }

    Lab4 *shifted_xy(int diff = 30) {
        auto firstInput = create_shifted_loaded_img(diff, diff);
        auto secondInput = create_shifted_loaded_img(-diff, -diff);
        work(firstInput, secondInput);
        return this;
    }

    Lab4 *shifted_y(int diffY = 50) {
        auto firstInput = create_shifted_loaded_img(0, diffY);
        auto secondInput = create_shifted_loaded_img(0, -diffY);
        work(firstInput, secondInput);
        return this;
    }

    Lab4 *shifted_x(int diffX = 50) {
        auto firstInput = create_shifted_loaded_img(diffX, 0);
        auto secondInput = create_shifted_loaded_img(-diffX, 0);
        work(firstInput, secondInput);
        return this;
    }

    Lab4 *contrast(double contrastFactor = 1.3) {
        work(loadedImg, create_with_distortion(make_shared<Contrast>(contrastFactor)));
        return this;
    }

    Lab4 *same_images() {
        work(loadedImg, loadedImg);
        return this;
    }

    void work(const shared_ptr<LoadedImg> &firstInput, const shared_ptr<LoadedImg> &secondInput) {
        auto firstDouble = make_shared<ProcessingImg>(firstInput->to_processing_img());
        auto secondDouble = make_shared<ProcessingImg>(secondInput->to_processing_img());
        auto matching = HistogramFactory::create(firstDouble, secondDouble, gridSize, cellSize, basketsSize,
                                                 pointsCount);
        auto resultImage = DescriptorDrawer::markMatching(firstDouble, secondDouble, matching);
        LoadedImg::save(resultImage,
                        QStringLiteral("%1_MATCHING_%2%3")
                                .arg(firstInput->get_name())
                                .arg(secondInput->get_name())
                                .arg(ext));
    }

    shared_ptr<LoadedImg> create_shifted_loaded_img(int shiftX, int shiftY) {
        return create_with_distortion(make_shared<Shift>(shiftX, shiftY));
    }

    shared_ptr<LoadedImg> create_with_distortion(const shared_ptr<Distortion> &distortion) {
        auto result = make_shared<LoadedImg>(
                LoadedImg::copy(distortion->distort(QPixmap::fromImage(loadedImg->native_image()))));
        result->set_name(imageName + "_" + distortion->getName());
        LoadedImg::save(result->native_image(), result->get_name() + ext);
        return result;
    }
public:
    static void test() {
//        Lab4("lenna", ".png", 3, 8,
//             32, 8, 4)
//                .shifted_xy(40)
//                ->shifted_y(60)
//                ->contrast();
//
//
//        Lab4("butterfly", ".jpg", 3, 8,
//             64, 8, 4)
//                .shifted_xy(60)
//                ->contrast()
//                ->shifted_x(80);

        Lab4("shrek", ".jpg", 3, 8,
             36, 8, 4)
                .contrast(1.5)
                ->shifted_xy(30)
                ->shifted_xy(50);
    }
};


#endif //ITOI_LAB4_H
