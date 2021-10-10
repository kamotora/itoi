#include "AbstractInterestPointsAlgo.h"

AbstractInterestPointsAlgo::AbstractInterestPointsAlgo(const shared_ptr<ProcessingImg> &image, const QString &imageName,
                                                       const QString &imageExt)
        : image(image), imageName(imageName), imageExt(imageExt) {
    if (imageName.isNull())
        cout << "imageName for points finder == null. We will not save intermediate results" << endl;
}

vector<Point> AbstractInterestPointsAlgo::localMaximum(double thresholdCoeff) {
    vector<int> dx{-1, 0, 1, -1, 1, -1, 0, -1};
    vector<int> dy{-1, -1, -1, 0, 0, 1, 1, 1};
    int w = image->get_width();
    int h = image->get_height();

//    image->normalize();

    double min = std::numeric_limits<double>::max(),
            max = std::numeric_limits<double>::min();
    // min and max search
    for (int i = 0; i < image->get_size(); i++) {
        double temp = image->get_pixel(i);
        if (max < temp) max = temp;
        if (min > temp) min = temp;
    }

    double threshold = min + (max - min) * thresholdCoeff;
    vector<Point> result;
    for (int i = 0; i < w; i++) {
        for (int j = 0; j < h; j++) {
            bool isCorrect = true;
            double currentValue = image->get_pixel(i, j);
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

vector<Point> AbstractInterestPointsAlgo::filter(vector<Point> &points, int pointsCount) {
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

vector<Point> AbstractInterestPointsAlgo::filter(vector<Point> &points, double radius) {
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

shared_ptr<ProcessingImg> AbstractInterestPointsAlgo::setPoints(vector<Point> &points) {
    auto result = make_shared<ProcessingImg>(*(image.get()));
    for (const auto &item : points) {
        auto pair = round(item.get_x(), item.get_y());
        result->set_pixel(pair.first, pair.second, 150);
        setPoint(item.get_x() - 1, item.get_y(), result);
        setPoint(item.get_x() + 1, item.get_y(), result);
        setPoint(item.get_x(), item.get_y() - 1, result);
        setPoint(item.get_x(), item.get_y() + 1, result);
    }
    return result;
}

pair<int, int> AbstractInterestPointsAlgo::round(int x, int y) {
    int resX = (x < 0) ? 0 : (x >= image->get_width() ? image->get_width() - 1 : x);
    int resY = (y < 0) ? 0 : (y >= image->get_height() ? image->get_height() - 1 : y);
    return make_pair(resX, resY);
}

void AbstractInterestPointsAlgo::setPoint(int x, int y, const shared_ptr<ProcessingImg> &sharedPtr) {
    auto pair = round(x, y);
    sharedPtr->set_pixel(pair.first, pair.second, 0);
}

double AbstractInterestPointsAlgo::getPixelWithBorderPolicy(int x, int y, IBorderPolicy &borderPolicy) const {
    return borderPolicy.get_pixel(*image, x, y);
}


void AbstractInterestPointsAlgo::drawPoints(vector<Point> &points, const QString &name) {
    auto res = make_shared<ProcessingImg>(image->get_width(), image->get_height());
    for (int i = 0; i < res->get_size(); i++)
        res->set_pixel(i, 0);
    for (const auto &item : points)
        res->set_pixel(item.get_x(), item.get_y(), 255);
    saveImage(res, "map_" + name);
}

void AbstractInterestPointsAlgo::saveImage(const shared_ptr<ProcessingImg> &outputImage, const QString &nameSuffix) {
    LoadedImg::save(LoadedImg::from_processing_img(*outputImage).native_image(),
                    imageName + "_" + method_name() + "_" + nameSuffix + imageExt);
}
