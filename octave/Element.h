#ifndef ITOI_ELEMENT_H
#define ITOI_ELEMENT_H


#include "../common/ProcessingImg.h"
#include "../common/Filter.h"

class Element {
private:
    double localSigma, globalSigma;
    shared_ptr<ProcessingImg> image;
public:
    Element(double localSigma, double globalSigma, const shared_ptr<ProcessingImg> &image) : localSigma(localSigma),
                                                                                             globalSigma(
                                                                                                         globalSigma),
                                                                                             image(image) {}

    [[nodiscard]] double getLocalSigma() const {
        return localSigma;
    }

    [[nodiscard]] double getGlobalSigma() const {
        return globalSigma;
    }

    [[nodiscard]] const shared_ptr<ProcessingImg> &getImage() const {
        return image;
    }
};


#endif //ITOI_ELEMENT_H
