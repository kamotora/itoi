#include "AbstractPointsFinder.h"

AbstractPointsFinder::AbstractPointsFinder(const shared_ptr<DoubleImage> &image, const QString &imageName,
                                           const QString &imageExt)
        : image(image), imageName(imageName), imageExt(imageExt) {
    if (imageName.isNull())
        cout << "imageName for points finder == null. We will not save intermediate results" << endl;
}

vector<Point> AbstractPointsFinder::localMaximum(double thresholdCoeff) {
    vector<int> dx{-1, 0, 1, -1, 1, -1, 0, -1};
    vector<int> dy{-1, -1, -1, 0, 0, 1, 1, 1};
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
            double currentValue = image->getPixel(i, j);
            for (int k = 0; k < dx.size() && isCorrect; k++) {
                if (i + dx[k] < 0 || i + dx[k] >= w || j + dy[k] < 0 || j + dy[k] >= h)
                    continue;
                if (currentValue < getPixelWithBorderPolicy(i + dx[k], j + dy[k]))
                    isCorrect = false;
            }
            if (isCorrect && currentValue > threshold) {
                result.emplace_back(i, j, currentValue, 0);
            }
        }
    }
    return result;
}

vector<Point> AbstractPointsFinder::filter(vector<Point> &points, int pointsCount) {
    if (pointsCount >= points.size())
        return points;
    sort(points.begin(), points.end(), [](Point a, Point b) {
        return b < a;
    });
    double l = 0, r = numeric_limits<double>::max();
    for (int i = pointsCount; i > 0; i--) {
        double middle = (l + r) / 2;
        if (filter(points, middle).size() > pointsCount) {
            l = middle;
        } else {
            r = middle;
        }
    }
    auto filtered = filter(points, l);
    return vector<Point>(points.begin(), points.begin() + min((int) filtered.size(), pointsCount));
}

vector<Point> AbstractPointsFinder::filter(vector<Point> &points, double radius) {
    vector<Point> filtered;
    for (int i = 0; i < points.size(); ++i) {
        bool ok = true;
        for (int j = 0; j < points.size(); ++j) {
            if (i == j) continue;
            if (points[i].distance(points[j]) < radius) {
                ok = false;
                break;
            }
        }
        if (ok) {
            filtered.push_back(points[i]);
        }
    }
    return filtered;
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

void AbstractPointsFinder::setPoint(int x, int y, const shared_ptr<DoubleImage> &sharedPtr) {
    auto pair = round(x, y);
    sharedPtr->setPixel(pair.first, pair.second, 0);
}

double AbstractPointsFinder::getPixelWithBorderPolicy(int x, int y, IBorderPolicy &borderPolicy) const {
    return borderPolicy.getPixel(*image, x, y);
}


void AbstractPointsFinder::drawPoints(vector<Point> &points, const QString &name) {
    auto res = make_shared<DoubleImage>(image->getWidth(), image->getHeight());
    for (int i = 0; i < res->getSize(); i++)
        res->setPixel(i, 0);
    for (const auto &item : points)
        res->setPixel(item.getX(), item.getY(), 255);
    saveImage(res, "map_" + name);
}

void AbstractPointsFinder::saveImage(const shared_ptr<DoubleImage> &outputImage, const QString &nameSuffix) {
    InputImage::saveToResources(InputImage::fromDoubleImage(*outputImage).getImage(),
                                imageName + "_" + getMethodName() + "_" + nameSuffix + imageExt);
}
