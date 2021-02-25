#ifndef ITOI_OCTAVEELEMENT_H
#define ITOI_OCTAVEELEMENT_H


#include "../core/DoubleImage.h"

class OctaveElement {
private:
    double localSigma, globalSigma;
    const DoubleImage& image;
public:
    OctaveElement(double localSigma, double globalSigma, const DoubleImage &image);

    [[nodiscard]] double getLocalSigma() const;

    [[nodiscard]] double getGlobalSigma() const;

    DoubleImage &getImage() const;
};


#endif //ITOI_OCTAVEELEMENT_H
