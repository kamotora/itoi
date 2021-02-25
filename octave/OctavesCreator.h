#ifndef ITOI_OCTAVESCREATOR_H
#define ITOI_OCTAVESCREATOR_H


#include "../core/DoubleImage.h"
#include "../filter/FilterUtil.h"
#include "OctaveElement.h"
#include "Octave.h"
#include <cmath>

class OctavesCreator {
private:
    static DoubleImage getHalfSizeImage(DoubleImage &image);
public:
    static vector<Octave> generateOctaves(int octavesCount, int nLevels, double sigma0, DoubleImage &inputImage, double imageSigma = 0.5);

    static Octave
    generateOneOctaveParallel(int nLevels, double sigma0, const DoubleImage &startImage, double k, double globalSigma);

    static double calculateDeltaSigma(double oldSigma, double newSigma);

};


#endif //ITOI_OCTAVESCREATOR_H
