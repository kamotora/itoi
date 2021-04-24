#include "Moravec.h"
#include "../core/InputImage.h"

vector<Point> Moravec::findPoints(int windowSize, int pointsCount, double tresholdCoef) {
    int w = image->getWidth();
    int h = image->getHeight();

    auto smoothed = make_shared<DoubleImageBorderPolicy>(FilterUtil::applyGauss(image, 1.3),
                                                         (IBorderPolicy &) DEFAULT_POLICY);

    auto moravec = make_shared<DoubleImage>(w, h);
    for (int x = 0; x < w; x++) {
        for (int y = 0; y < h; y++) {
            auto local = std::numeric_limits<double>::max();
            for (int iy = -1; iy <= 1; iy++) {
                for (int ix = -1; ix <= 1; ix++) {
                    double sum = 0;
                    for (int u = -windowSize; u <= windowSize; u++) {
                        for (int v = -windowSize; v <= windowSize; v++) {
                            double tmp = smoothed->getBorderedPixel(x, y) -
                                         smoothed->getBorderedPixel((x + ix + u), y + iy + v);
                            sum += tmp * tmp;
                        }
                    }
                    local = std::min(sum, local);
                }
                moravec->setPixel(x, y, local);
            }
        }
    }
    saveImage(moravec, "before_filtering");
    image = moravec;
    vector<Point> points = this->localMaximum(windowSize, tresholdCoef);
    drawPoints(points, "localMaximums");
    int maxSize = std::min(w / 2, h / 2);
    auto filteredPoints = filter(points, pointsCount, maxSize);
    drawPoints(filteredPoints, "after_filtering");
    return filteredPoints;
}

QString Moravec::getMethodName() {
    return "moravec";
}

Moravec::Moravec(const shared_ptr<DoubleImage> &image, const QString &imageName, const QString &imageExt)
        : AbstractPointsFinder(image, imageName, imageExt) {}
