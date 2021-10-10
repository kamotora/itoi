#ifndef ITOI_LAB2_H
#define ITOI_LAB2_H


#include <cmath>
#include "../common/LoadedImg.h"
#include "../octave/OctaveFactory.h"


class Lab2 {
private:
    int nOctaves, nLevels;
    double sigma0, sigmaA, sigmaL;
    const QString &imageName, &ext;

    Lab2(int nOctaves, int nLevels, double sigma0, double sigmaA, double sigmaL, const QString &imageName,
         const QString &ext) : nOctaves(nOctaves), nLevels(nLevels), sigma0(sigma0), sigmaA(sigmaA), sigmaL(sigmaL),
                               imageName(imageName), ext(ext) {}


    void work() {
        auto input = LoadedImg::by_image_name(imageName + ext);
        auto inputDouble = input.to_processing_img();
        auto octaves = OctaveFactory::generate_octaves(nOctaves, nLevels, sigma0, inputDouble, sigmaA);
        for (int i = 0; i < octaves.size(); i++) {
            auto elements = octaves[i]->get_elements();
            for (int j = 0; j < elements.size(); j++) {
                std::ostringstream streamStr;
                streamStr << setprecision(3);
                streamStr << imageName.toStdString()
                          << "_octave_" << i << "_lvl_" << j <<
                          "_local_" << elements[j]->getLocalSigma() <<
                          "_global_" << elements[j]->getGlobalSigma() <<
                          ext.toStdString();
                LoadedImg::from_processing_img(*elements[j]->getImage()).save(streamStr.str());
            }
        }
        auto L = OctaveFactory::L(inputDouble, octaves, sigmaL);
        LoadedImg::from_processing_img(*L).save(
                imageName + "L_" + QString::fromStdString(to_string(sigmaL)) + ext);
        saveAsCompoundImage(octaves);
    }

    void saveAsCompoundImage(const vector<shared_ptr<Octave>> &octaves) {
        for (int i = 0; i < nLevels; i++) {
            auto resultImage = LoadedImg::from_processing_img(
                    *octaves[0]->get_elements()[i]->getImage()).native_image();
            for (int j = 0; j < nOctaves; j++) {
                auto curImage = LoadedImg::from_processing_img(
                        *octaves[j]->get_elements()[i]->getImage()).native_image();
                for (int x = 0; x < curImage.width(); x++)
                    for (int y = 0; y < curImage.height(); y++)
                        resultImage.setPixel(x,
                                             (resultImage.height() - curImage.height() + y), curImage.pixel(x, y));
            }
            LoadedImg::save(resultImage,
                            imageName + QString::fromStdString("_compound_lvl_" + to_string(i)) + ext);
        }
    }

public:
//    int main(int argc, char *argv[]) {
    static void test() {
        cout << "Start test for Lab2..." << endl;
//        a
        {
            Lab2(5, 2, 1, 0.5, 7.13, "butterfly", ".jpg")
                    .work();
            Lab2(3, 2, 1.5, 0.8, 4, "shrek", ".jpg")
                    .work();
            Lab2(3, 4, 0.7, 0.3, 3, "cat_dog", ".jpg")
                    .work();
        }
//        b
        {
            Lab2(2, 4, 1, 0.5, 3, "butterfly1", ".jpg")
                    .work();
            Lab2(3, 3, 1, 0.5, 6, "butterfly2", ".jpg")
                    .work();
            Lab2(4, 2, 1, 0.5, 9, "butterfly3", ".jpg")
                    .work();
        }
    }
};


#endif //ITOI_LAB2_H
