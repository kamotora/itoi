//
// Created by kamotora on 25.02.2021.
//

#include "OctavesCreator.h"

vector<Octave> OctavesCreator::generateOctaves(int octavesCount, int nLevels, double sigma0, DoubleImage &inputImage,
                                                 double imageSigma) {
        double k = pow(2.0, 1.0 / /*(nLevels - 1)*/ nLevels); // интервал между масштабами в октаве
        auto deltaSigma = calculateDeltaSigma(imageSigma, sigma0);
        DoubleImage startImage = FilterUtil::applyGaussSeparable(inputImage, deltaSigma);
        auto globalSigma = sigma0;
        vector<Octave> octaves;
        for (int i = 0; i < octavesCount; i++) {
            auto octave = generateOneOctaveParallel(nLevels, sigma0, startImage, k, globalSigma);
            octaves.push_back(octave);
            globalSigma *= 2l;
            startImage = getHalfSizeImage(octave.getLast().getImage());
        }
        return octaves;
}

//todo ошибка здесь
Octave OctavesCreator::generateOneOctaveParallel(int nLevels, double sigma0, const DoubleImage &startImage, double k,
                                                 double globalSigma) {
    Octave result;
    OctaveElement startElement(sigma0, globalSigma, startImage);
    result.addElement(startElement);
    auto oldSigma = startElement.getLocalSigma();
    double curK = k;
    for (int i = 1; i <= nLevels; i++) {
        auto newSigma = oldSigma * curK;
        auto deltaSigma = calculateDeltaSigma(oldSigma, newSigma);
        auto newImage = FilterUtil::applyGaussSeparable(startElement.getImage(), deltaSigma);
        OctaveElement element(newSigma, globalSigma * curK, newImage);
        result.addElement(element);
        curK *= k;
    }
    return result;
}

double OctavesCreator::calculateDeltaSigma(double oldSigma, double newSigma) {
    return sqrt(newSigma * newSigma - oldSigma * oldSigma);
}

DoubleImage OctavesCreator::getHalfSizeImage(DoubleImage &image) {
    DoubleImage result(image.getWidth() / 2, image.getHeight() / 2);
    int curPixel = 0;
    for (int x = 0; x < image.getWidth(); x += 2)
        for (int y = 0; y < image.getHeight(); y += 2)
            result.setPixel(curPixel++, image.getPixel(x, y));

    return result;
}
