#ifndef ITOI_LAB2_H
#define ITOI_LAB2_H


#include <cmath>
#include "../core/InputImage.h"
#include "../octave/OctavesCreator.h"

class Lab2 {
private:
    int nOctaves, nLevels;
    double sigma0, sigmaA, sigmaL;
    const QString &imageName, &ext;
public:
    Lab2(int nOctaves, int nLevels, double sigma0, double sigmaA, double sigmaL, const QString &imageName,
         const QString &ext) : nOctaves(nOctaves), nLevels(nLevels), sigma0(sigma0), sigmaA(sigmaA), sigmaL(sigmaL),
                               imageName(imageName), ext(ext) {}

    static void demo() {
//        a
        {
            Lab2(5, 2, 1, 0.5, 7.13, "butterfly", ".jpg").work();
            Lab2(3, 2, 1.5, 0.8, 4, "shrek", ".jpg").work();
            Lab2(3, 4, 0.7, 0.3, 3, "cat_dog", ".jpg").work();
        }
//        b
        {
            Lab2(2, 4, 1, 0.5, 3, "butterfly1", ".jpg").work();
            Lab2(3, 3, 1, 0.5, 6, "butterfly2", ".jpg").work();
            Lab2(4, 2, 1, 0.5, 9, "butterfly3", ".jpg").work();
        }
    }

    void work() {
        auto input = InputImage::fromResources(imageName + ext);
        auto inputDouble = input.toDoubleImage();
        auto octaves = OctavesCreator::generateOctaves(nOctaves, nLevels, sigma0, inputDouble, sigmaA);
        for (int i = 0; i < octaves.size(); i++) {
            auto elements = octaves[i]->getElements();
            for (int j = 0; j < elements.size(); j++) {
                std::ostringstream streamStr;
                streamStr << setprecision(3);
                streamStr << imageName.toStdString()
                          << "_octave_" << i << "_lvl_" << j <<
                          "_local_" << elements[j]->getLocalSigma() <<
                          "_global_" << elements[j]->getGlobalSigma() <<
                          ext.toStdString();
                InputImage::fromDoubleImage(*elements[j]->getImage()).saveToResources(streamStr.str());
            }
        }
        auto L = OctavesCreator::L(inputDouble, octaves, sigmaL);
        InputImage::fromDoubleImage(*L).saveToResources(
                imageName + "L_" + QString::fromStdString(to_string(sigmaL)) + ext);
        saveAsCompoundImage(octaves);
    }

    void saveAsCompoundImage(const vector<shared_ptr<Octave>> &octaves) {
        for (int i = 0; i < nLevels; i++) {
            auto resultImage = InputImage::fromDoubleImage(*octaves[0]->getElements()[i]->getImage()).getImage();
            for (int j = 0; j < nOctaves; j++) {
                auto curImage = InputImage::fromDoubleImage(*octaves[j]->getElements()[i]->getImage()).getImage();
                for (int x = 0; x < curImage.width(); x++)
                    for (int y = 0; y < curImage.height(); y++)
                        resultImage.setPixel(x,
                                             (resultImage.height() - curImage.height() + y), curImage.pixel(x, y));
            }
            InputImage::saveToResources(resultImage,
                                        imageName + QString::fromStdString("_compound_lvl_" + to_string(i)) + ext);
        }
    }
};


#endif //ITOI_LAB2_H
