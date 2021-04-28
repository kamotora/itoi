//
// Created by kamotora on 30.03.2021.
//

#include "Harris.h"

vector<Point> Harris::findPoints(int windowSize, int pointsCount, double tresholdCoef) {
    int w = image->getWidth();
    int h = image->getHeight();

    auto gaussKernel = Kernels::GetGauss(windowSize);

    auto dx = make_shared<DoubleImageBorderPolicy>(FilterUtil::derivX(image), (IBorderPolicy &) DEFAULT_POLICY);
    auto dy = make_shared<DoubleImageBorderPolicy>(FilterUtil::derivY(image), (IBorderPolicy &) DEFAULT_POLICY);
    auto harris = make_shared<DoubleImage>(w, h);

    for (int x = 0; x < w; x++) {
        for (int y = 0; y < h; y++) {
            vector<vector<double>> currentMatrix(2, vector<double>(2, 0));
            for (int u = -windowSize; u <= windowSize; u++) {
                for (int v = -windowSize; v <= windowSize; v++) {
                    double Ix = dx->getBorderedPixel(x + u, y + v);
                    double Iy = dy->getBorderedPixel(x + u, y + v);
                    double gaussPoint = gaussKernel.getPixel(u + windowSize, v + windowSize);
                    currentMatrix[0][0] += Ix * Ix * gaussPoint;
                    currentMatrix[0][1] += Ix * Iy * gaussPoint;
                    currentMatrix[1][0] += Ix * Iy * gaussPoint;
                    currentMatrix[1][1] += Iy * Iy * gaussPoint;
                }
            }
            vector<double> eigenvalues = getEigenValues(currentMatrix);
            harris->setPixel(x, y, min(eigenvalues[0], eigenvalues[1]));
        }
    }
    saveImage(harris, "before_filtering");
    image = harris;
    vector<Point> points = localMaximum(tresholdCoef);
    drawPoints(points, "localMaximums");
    auto pointsAfterFiltering = filter(points, pointsCount, std::min(w / 2, h / 2));
    drawPoints(pointsAfterFiltering, "after_filtering");
    return pointsAfterFiltering;
}

vector<double> Harris::getEigenValues(vector<vector<double>> matrix) {
    vector<double> eigenvalues(2);

    double a = 1;
    double b = -matrix[0][0] - matrix[1][1];
    double c = matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0];
    double d = b * b - 4 * a * c;
    if (abs(d) < 1e-4)
        d = 0;
    if (d < 0) {
        return eigenvalues;
    }

    eigenvalues[0] = (-b + sqrt(d)) / (2 * a);
    eigenvalues[1] = (-b - sqrt(d)) / (2 * a);

    return eigenvalues;
}

QString Harris::getMethodName() {
    return "harris";
}

Harris::Harris(const shared_ptr<DoubleImage> &image, const QString &imageName, const QString &imageExt)
        : AbstractPointsFinder(image, imageName, imageExt) {}
