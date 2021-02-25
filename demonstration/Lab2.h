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
        auto input = InputImage::fromResources("butterfly.jpg");
        auto inputDouble = input.toDoubleImage();
        auto octaves = OctavesCreator::generateOctaves(nOctaves, nLevels, sigma0, inputDouble);
        for (int i = 0; i < octaves.size(); i++) {
            auto elements = octaves[i].getElements();
            for (int j = 0; j < elements.size(); j++) {
                auto element = elements[j];
                InputImage::fromDoubleImage(element.getImage()).saveToResources(
                        "octave_" + to_string(i) +
                        "_img_" + "butterfly" +
                        "_local_" + to_string(element.getLocalSigma()) +
                        "_global_" + to_string(element.getGlobalSigma())
                        + ".jpg");
            }
        }
    }


};


#endif //ITOI_LAB2_H
