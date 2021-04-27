#include "Moravec.h"

vector<Point> Moravec::findPoints(int windowSize, int pointsCount, double tresholdCoef) {
    vector<int> dx{-1, 0, 1, -1, 1, -1, 0, -1};
    vector<int> dy{-1, -1, -1, 0, 0, 1, 1, 1};

    int w = image->getWidth();
    int h = image->getHeight();

    auto smoothed = make_shared<DoubleImageBorderPolicy>(FilterUtil::applyGauss(image, windowSize),
                                                         (IBorderPolicy &) DEFAULT_POLICY);

    auto moravec = make_shared<DoubleImage>(w, h);
    for (int i = 0; i < w; i++) {
        for (int j = 0; j < h; j++) {
            double min = std::numeric_limits<double>::max();
            for (int k = 0; k < dx.size(); k++) {
                double sum = 0;
                for (int u = -windowSize; u <= windowSize; u++) {
                    for (int v = -windowSize; v <= windowSize; v++) {
                        auto temp = getPixelWithBorderPolicy(i + u, j + v) -
                                    getPixelWithBorderPolicy(i + u + dx[k], j + v + dy[k]);
                        sum += temp * temp;
                    }
                }
                min = std::min(min, sum);
            }
            moravec->setPixel(i, j, min);
        }
    }
    saveImage(moravec, "before_filtering");
    image = moravec;
    vector<Point> points = this->localMaximum(tresholdCoef);
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
