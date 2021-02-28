#ifndef ITOI_LAB2_H
#define ITOI_LAB2_H


#include <cmath>
#include "../core/InputImage.h"
#include "../octave/OctavesCreator.h"

class Lab2 {
private:
    // todo nOctaves сделать на основе изображения
    int nOctaves = 5, nLevels = 2;
    double sigma0 = 1, sigmaA = 0, sigmaL = 7.13;
public:
    void work() {
        //todo normalization
        const string imageName = "butterfly";
        const string ext = ".jpg";
        auto input = InputImage::fromResources(QString::fromStdString(imageName + ext));
        auto inputDouble = input.toDoubleImage();
        auto octaves = OctavesCreator::generateOctaves(nOctaves, nLevels, sigma0, inputDouble);
//        auto L = OctavesCreator::L(inputDouble, octaves, sigmaL);
//        InputImage::fromDoubleImage(*L).saveToResources(QString::fromStdString("L.jpg"));
        for (int i = 0; i < octaves.size(); i++) {
            auto elements = octaves[i];
            for (auto &&element : elements->getElements()) {
//            for (int j = 0; j < elements.size(); j++) {
//                auto element = elements.begin()[j];
                InputImage::fromDoubleImage(*element->getImage()).saveToResources(
                        "octave_" + to_string(i) +
                        "_img_" + imageName +
                        "_local_" + to_string(element->getLocalSigma()) +
                        "_global_" + to_string(element->getGlobalSigma())
                        + ext);
            }
        }
        saveAsCompoundImage(imageName, ext, octaves, nOctaves, nLevels);
    }

    static void
    saveAsCompoundImage(const string &name, const string &ext, const vector<shared_ptr<Octave>> &octaves, int nOctaves,
                        int nLevels) {
        vector<vector<InputImage>> imagesByLvl(nOctaves);
        for (int i = 0; i < nLevels; i++) {
            for (int j = 0; j < nOctaves; j++) {
                imagesByLvl[i].push_back(InputImage::fromDoubleImage(*octaves[j]->getElements()[i]->getImage()));
            }
        }
        for (int i = 0; i < nLevels; i++) {
            auto resultImage = imagesByLvl[i][0].getImage();
            for (int j = 0; j < nOctaves; j++) {
                auto curImage = imagesByLvl[i][j].getImage();
                for (int x = 0; x < curImage.width(); x++)
                    for (int y = 0; y < curImage.height(); y++)
                        resultImage.setPixel(x,
                                             (resultImage.height() - curImage.height() + y), curImage.pixel(x, y));
            }
            InputImage::saveToResources(resultImage,
                                        QString::fromStdString(name + "_compound_lvl_" + to_string(i) + ext));
        }
    }
};


#endif //ITOI_LAB2_H
