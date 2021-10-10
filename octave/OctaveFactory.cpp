#include "OctaveFactory.h"
#include "../common/LoadedImg.h"


vector<shared_ptr<struct Octave>>
OctaveFactory::generate_octaves(int octavesCount, int nLevels, double sigma0, ProcessingImg &LoadedImg,
                                double sigmaA) {
    double k = pow(2.0, 1.0 / nLevels); // интервал между масштабами в октаве
    auto deltaSigma = calculateDeltaSigma(sigmaA, sigma0);
    auto startImage = Filter::applyGauss(make_shared<ProcessingImg>(LoadedImg), deltaSigma);
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

shared_ptr<Octave>
OctaveFactory::generateOneOctave(int nLevels, double sigma0, const shared_ptr<ProcessingImg> &startImage, double k,
                                 double globalSigma) {
    auto result = make_shared<Octave>();
    auto startElement = make_shared<Element>(sigma0, globalSigma, startImage);
    result->addElement(startElement);
    auto oldSigma = sigma0;
    double curK = k;
    for (int i = 1; i <= nLevels; i++) {

        auto newSigma = oldSigma * curK;
        auto deltaSigma = calculateDeltaSigma(oldSigma, newSigma);
        auto newImage = Filter::applyGauss(startElement->getImage(), deltaSigma);
        Element element(newSigma, globalSigma * curK, newImage);
        result->addElement(make_shared<Element>(element));
        curK *= k;
    }
    return result;
}

double OctaveFactory::calculateDeltaSigma(double oldSigma, double newSigma) {
    return sqrt(newSigma * newSigma - oldSigma * oldSigma);
}

shared_ptr<ProcessingImg> OctaveFactory::getHalfSizeImage(const shared_ptr<ProcessingImg> &image) {
    auto res = ProcessingImg(image->width() / 2, image->height() / 2);

    for (int x = 0; x < res.width(); x++)
        for (int y = 0; y < res.height(); y++)
            res.set_pixel(x, y, image->pixel(x * 2, y * 2));
    if (res.size() != ((image->width() / 2) * (image->height() / 2))) {
        cerr << "Invalid function" << endl;
        throw runtime_error("invalid");
    }
    return make_shared<ProcessingImg>(res.normalize());
//    return make_shared<ProcessingImg>(pixels, image->width() / 2, image->height() / 2);;
}


shared_ptr<ProcessingImg> OctaveFactory::L(ProcessingImg &LoadedImg, vector<shared_ptr<Octave>> pyramid, double sigma) {
    auto targetLayer = pyramid[0]->get_elements()[0];

    //Поиск нужной октавы
    int octaveLevel = 0;
    int octaveCount = 0;
    for (auto &octave : pyramid) {
        for (auto &layer : octave->get_elements()) {
            if (fabs(layer->getGlobalSigma() - sigma) < fabs(targetLayer->getGlobalSigma() - sigma)) {
                targetLayer = layer;
                octaveLevel = octaveCount;
            }
        }
        octaveCount++;
    }

    int transformationCoef =static_cast<int>(pow(2, octaveLevel));
    auto output = make_shared<ProcessingImg>(LoadedImg.width(), LoadedImg.height());
    for (int x = 0; x < LoadedImg.width(); x++)
        for (int y = 0; y < LoadedImg.height(); y++) {
            //преобразование координат
            int x_n = static_cast<int>(x / transformationCoef);
            int y_n = static_cast<int>(y / transformationCoef);
            if (y_n >= targetLayer->getImage()->height()) y_n = targetLayer->getImage()->height() - 1;
            if (x_n >= targetLayer->getImage()->width()) x_n = targetLayer->getImage()->width() - 1;

            output->set_pixel(x, y, targetLayer->getImage()->pixel(x_n, y_n));
        }
    return output;
}

