#include "AbstractPointsFinder.h"

AbstractPointsFinder::AbstractPointsFinder(const shared_ptr<DoubleImage> &image) : image(image) {}

vector<Point> AbstractPointsFinder::localMaximum(vector<Point> &points, int windowSize, double thresholdCoeff) {
    int w = image->getWidth();
    int h = image->getHeight();

//    image->normalize();

    double min = std::numeric_limits<double>::max(),
            max = std::numeric_limits<double>::min();
    // min and max search
    for (int i = 0; i < image->getSize(); i++) {
        double temp = image->getPixel(i);
        if (max < temp) max = temp;
        if (min > temp) min = temp;
    }

    double threshold = min + (max - min) * thresholdCoeff;
    vector<Point> result;
    for (int i = 0; i < w; i++) {
        for (int j = 0; j < h; j++) {
            bool isCorrect = true;
            double sLocal = image->getPixel(i, j);
            for (int px = -windowSize; px <= windowSize && isCorrect; px++) {
                for (int py = -windowSize; py <= windowSize && isCorrect; py++) {
                    if (px != 0 || py != 0) {
                        isCorrect = sLocal > getPixelWithBorderPolicy(i + px, j + py);
                    }
                }
            }
            if (isCorrect && sLocal > threshold) {
                result.emplace_back(i, j, sLocal);
            }
        }
    }
    return result;
}

vector<Point> AbstractPointsFinder::filter(vector<Point> &points, int pointsCount, int maxSize) {
    int r = 3;
    while (points.size() > pointsCount && r < maxSize) {
        for (int i = 0; i < points.size(); i++) {
            for (int j = 0; j < points.size(); j++) {
//                double xd = points[i].getX() - points[j].getX();
//                double yd = points[i].getY() - points[j].getY();
//                double dist = sqrt(xd * xd + yd * yd);
                double dist = points[i].distance(points[j]);
                if (dist <= r) {
                    if (points[i] < points[j]) {
                        points.erase(points.begin() + i);
                        i--;
                        j = points.size();
                    }
                }
            }
        }
        r++;
    }
    return points;
}

shared_ptr<DoubleImage> AbstractPointsFinder::setPoints(vector<Point> &points) {
    auto result = make_shared<DoubleImage>(*(image.get()));
    for (const auto &item : points) {
        auto pair = round(item.getX(), item.getY());
        result->setPixel(pair.first, pair.second, 150);
        setPoint(item.getX() - 1, item.getY(), result);
        setPoint(item.getX() + 1, item.getY(), result);
        setPoint(item.getX(), item.getY() - 1, result);
        setPoint(item.getX(), item.getY() + 1, result);
    }
    return result;
}

pair<int, int> AbstractPointsFinder::round(int x, int y) {
    int resX = (x < 0) ? 0 : (x >= image->getWidth() ? image->getWidth() - 1 : x);
    int resY = (y < 0) ? 0 : (y >= image->getHeight() ? image->getHeight() - 1 : y);
    return make_pair(resX, resY);
}

void AbstractPointsFinder::setPoint(int x, int y, const shared_ptr<DoubleImage>& sharedPtr) {
    auto pair = round(x, y);
    sharedPtr->setPixel(pair.first, pair.second, 0);
}

double AbstractPointsFinder::getPixelWithBorderPolicy(int x, int y, IBorderPolicy &borderPolicy) const {
    return borderPolicy.getPixel(*image, x, y);
}
