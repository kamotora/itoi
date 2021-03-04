//
// Created by kamotora on 25.02.2021.
//

#include "OctavesCreator.h"
#include "../core/InputImage.h"


vector<shared_ptr<struct Octave>>
OctavesCreator::generateOctaves(int octavesCount, int nLevels, double sigma0, DoubleImage &inputImage,
                                double sigmaA) {
    double k = pow(2.0, 1.0 / nLevels); // интервал между масштабами в октаве
    auto deltaSigma = calculateDeltaSigma(sigmaA, sigma0);
    auto startImage = FilterUtil::applyGaussSeparable(make_shared<DoubleImage>(inputImage), deltaSigma);
    auto globalSigma = sigma0;
    vector<shared_ptr<Octave>> octaves;
    for (int i = 0; i < octavesCount; i++) {
        auto octave = generateOneOctave(nLevels, sigma0, startImage, k, globalSigma);
        octaves.push_back(octave);
        globalSigma *= 2l;
        startImage = getHalfSizeImage(octave->getLast()->getImage());
    }
    return octaves;
}
// скорее всего, что-то здесь не так
shared_ptr<Octave>
OctavesCreator::generateOneOctave(int nLevels, double sigma0, const shared_ptr<DoubleImage> &startImage, double k,
                                  double globalSigma) {
    auto result = make_shared<Octave>();
    auto startElement = make_shared<OctaveElement>(sigma0, globalSigma, startImage);
    result->addElement(startElement);
    auto oldSigma = sigma0;
    double curK = k;
    for (int i = 1; i <= nLevels; i++) {

        auto newSigma = oldSigma * curK;
        auto deltaSigma = calculateDeltaSigma(oldSigma, newSigma);
        auto newImage = FilterUtil::applyGaussSeparable(startElement->getImage(), deltaSigma);
        OctaveElement element(newSigma, globalSigma * curK, newImage);
        result->addElement(make_shared<OctaveElement>(element));
        curK *= k;
    }
    return result;
}

double OctavesCreator::calculateDeltaSigma(double oldSigma, double newSigma) {
    return sqrt(newSigma * newSigma - oldSigma * oldSigma);
}

shared_ptr<DoubleImage> OctavesCreator::getHalfSizeImage(const shared_ptr<DoubleImage> &image) {
    auto res = DoubleImage(image->getWidth() / 2, image->getHeight() / 2);

    for (int x = 0; x < res.getWidth(); x++)
        for (int y = 0; y < res.getHeight(); y++)
            res.setPixel(x, y, image->getPixel(x * 2, y * 2));
    if (res.getSize() != ((image->getWidth() / 2) * (image->getHeight() / 2))) {
        cerr << "Invalid function" << endl;
        throw runtime_error("invalid");
    }
    return make_shared<DoubleImage>(res.normalize());
//    return make_shared<DoubleImage>(pixels, image->getWidth() / 2, image->getHeight() / 2);;
}


shared_ptr<DoubleImage> OctavesCreator::L(DoubleImage &inputImage, vector<shared_ptr<Octave>> pyramid, double sigma) {
    auto targetLayer = pyramid[0]->getElements()[0];

    //Поиск нужной октавы
    int octaveLevel = 0;
    int octaveCount = 0;
    for (auto &octave : pyramid) {
        for (auto &layer : octave->getElements()) {
            if (fabs(layer->getGlobalSigma() - sigma) < fabs(targetLayer->getGlobalSigma() - sigma)) {
                targetLayer = layer;
                octaveLevel = octaveCount;
            }
        }
        octaveCount++;
    }

    int transformationCoef =static_cast<int>(pow(2, octaveLevel));
    auto output = make_shared<DoubleImage>(inputImage.getWidth(), inputImage.getHeight());
    for (int x = 0; x < inputImage.getWidth(); x++)
        for (int y = 0; y < inputImage.getHeight(); y++) {
            //преобразование координат
            int x_n = static_cast<int>(x / transformationCoef);
            int y_n = static_cast<int>(y / transformationCoef);
            if (y_n >= targetLayer->getImage()->getHeight()) y_n = targetLayer->getImage()->getHeight() - 1;
            if (x_n >= targetLayer->getImage()->getWidth()) x_n = targetLayer->getImage()->getWidth() - 1;

            output->setPixel(x, y, targetLayer->getImage()->getPixel(x_n, y_n));
        }
    return output;
}

