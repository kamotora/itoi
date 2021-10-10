#include "Moravec.h"

vector<Point> Moravec::find_points(int pointsCount, int windowSize, double tresholdCoef) {
    int w = image->width();
    int h = image->height();

    auto moravec = make_shared<ProcessingImg>(w, h);
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
            moravec->set_pixel(i, j, min);
        }
    }
    saveImage(moravec, "before_filtering");
    image = moravec;
    vector<Point> points = this->localMaximum(tresholdCoef);
    drawPoints(points, "localMaximums");
    auto filteredPoints = filter(points, pointsCount);
    drawPoints(filteredPoints, "after_filtering");
    return filteredPoints;
}

QString Moravec::method_name() {
    return "moravec";
}

Moravec::Moravec(const shared_ptr<ProcessingImg> &image, const QString &imageName, const QString &imageExt)
        : AbstractInterestPointsAlgo(image, imageName, imageExt) {}
