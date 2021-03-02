#ifndef ITOI_OCTAVEELEMENT_H
#define ITOI_OCTAVEELEMENT_H


#include "../core/DoubleImage.h"
#include "../filter/FilterUtil.h"

class OctaveElement {
private:
    double localSigma, globalSigma;
    shared_ptr<DoubleImage> image;
public:
    OctaveElement(double localSigma, double globalSigma, const shared_ptr<DoubleImage> &image) : localSigma(localSigma),
                                                                                                 globalSigma(
                                                                                                         globalSigma),
                                                                                                 image(image) {}

    [[nodiscard]] double getLocalSigma() const {
        return localSigma;
    }

    [[nodiscard]] double getGlobalSigma() const {
        return globalSigma;
    }

    [[nodiscard]] const shared_ptr<DoubleImage> &getImage() const {
        return image;
    }
};


#endif //ITOI_OCTAVEELEMENT_H
