#ifndef ITOI_OCTAVEFACTORY_H
#define ITOI_OCTAVEFACTORY_H


#include "../common/ProcessingImg.h"
#include "../common/Filter.h"
#include "Element.h"
#include "Octave.h"
#include <cmath>

class OctaveFactory {
public:
    static vector<shared_ptr<struct Octave>>
    generate_octaves(int octavesCount, int nLevels, double sigma0, ProcessingImg &LoadedImg, double sigmaA = 0.5);

    static shared_ptr<struct Octave>
    generateOneOctave(int nLevels, double sigma0, const shared_ptr<ProcessingImg> &start_image, double k,
                      double globalSigma);

    static double calculateDeltaSigma(double oldSigma, double newSigma);

    static shared_ptr<ProcessingImg> L(ProcessingImg &LoadedImg, vector<shared_ptr<Octave>> pyramid, double sigma);

    static shared_ptr<ProcessingImg> getHalfSizeImage(const shared_ptr<ProcessingImg> &image);
};


#endif //ITOI_OCTAVEFACTORY_H
