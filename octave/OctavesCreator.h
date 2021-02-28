#ifndef ITOI_OCTAVESCREATOR_H
#define ITOI_OCTAVESCREATOR_H


#include "../core/DoubleImage.h"
#include "../filter/FilterUtil.h"
#include "OctaveElement.h"
#include "Octave.h"
#include <cmath>

class OctavesCreator {
public:
    static vector<shared_ptr<struct Octave>>
    generateOctaves(int octavesCount, int nLevels, double sigma0, DoubleImage &inputImage, double imageSigma = 0.5);

    static shared_ptr<struct Octave>
    generateOneOctave(int nLevels, double sigma0, const shared_ptr<DoubleImage>& startImage, double k, double globalSigma);

    static double calculateDeltaSigma(double oldSigma, double newSigma);

    static shared_ptr<DoubleImage> L(DoubleImage &inputImage, vector<shared_ptr<Octave>> pyramid, double sigma);

    static shared_ptr<DoubleImage> getHalfSizeImage(const shared_ptr<DoubleImage> &image);
};


#endif //ITOI_OCTAVESCREATOR_H
