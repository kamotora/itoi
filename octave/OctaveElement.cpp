//
// Created by kamotora on 25.02.2021.
//

#include "OctaveElement.h"

OctaveElement::OctaveElement(double localSigma, double globalSigma, const DoubleImage &image) : localSigma(localSigma),
                                                                            globalSigma(globalSigma), image(image) {}

double OctaveElement::getLocalSigma() const {
    return localSigma;
}

double OctaveElement::getGlobalSigma() const {
    return globalSigma;
}

DoubleImage &OctaveElement::getImage() const {
    return const_cast<DoubleImage &>(image);
}

