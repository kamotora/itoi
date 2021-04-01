#include "Moravec.h"

vector<Point> Moravec::findPoints(int windowSize, int pointsCount) {
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
                    if (ix != 0 && iy != 0) {
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
                }
                moravec->setPixel(x, y, local);
            }
        }
    }
    image = moravec;
    vector<Point> points = this->localMaximum(windowSize);
    int maxSize = std::min(w / 2, h / 2);
    return filter(points, pointsCount, maxSize);
}

Moravec::Moravec(const shared_ptr<DoubleImage> &image) : AbstractPointsFinder(image) {}
