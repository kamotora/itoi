//
// Created by kamotora on 30.03.2021.
//

#include "Harris.h"

vector<Point> Harris::findPoints(int windowSize, int pointsCount, double tresholdCoef) {
    int w = image->getWidth();
    int h = image->getHeight();

    auto smoothed = FilterUtil::applyGauss(image, 1.3);

    auto dx = make_shared<DoubleImageBorderPolicy>(FilterUtil::derivX(image), (IBorderPolicy &) DEFAULT_POLICY);
    auto dy = make_shared<DoubleImageBorderPolicy>(FilterUtil::derivY(image), (IBorderPolicy &) DEFAULT_POLICY);


    vector<vector<double>> a, b, c;


    double sigma = static_cast<double>(windowSize * 2) / 6;
    vector<vector<double>> gaussKernel;

    double coeff = 1 / (2 * M_PI * sigma * sigma);
    double delitel = 2 * sigma * sigma;

    for (int u = -windowSize; u <= windowSize; u++) {
        vector<double> gaussRow;
        for (int v = -windowSize; v <= windowSize; v++) {
            gaussRow.push_back(coeff * exp(-(u * u + v * v) / delitel));
        }
        gaussKernel.push_back(gaussRow);
    }
    for (int y = 0; y < h; y++) {
        vector<double> aRow, bRow, cRow;
        for (int x = 0; x < w; x++) {
            double sumA = 0, sumB = 0, sumC = 0;

            for (int u = -windowSize; u <= windowSize; u++) {
                for (int v = -windowSize; v <= windowSize; v++) {
                    double i_x = dx->getBorderedPixel((x + v), y + u);
                    double i_y = dx->getBorderedPixel((x + v), y + u);
                    sumA += i_x * i_x * gaussKernel[windowSize + u][windowSize + v];
                    sumB += i_x * i_y * gaussKernel[windowSize + u][windowSize + v];
                    sumC += i_y * i_y * gaussKernel[windowSize + u][windowSize + v];
                }
            }
            aRow.push_back(sumA);
            bRow.push_back(sumB);
            cRow.push_back(sumC);
        }
        a.push_back(aRow);
        b.push_back(bRow);
        c.push_back(cRow);
    }
    auto harris = make_shared<DoubleImage>(w, h);

    for (int x = 0; x < w; x++) {
        for (int y = 0; y < h; y++) {
            double sc = a[y][x] + c[y][x];
            double d = a[y][x] * c[y][x] - b[y][x] * b[y][x];
            double det = sc * sc - 4 * d;
            double L1 = (sc + sqrt(det)) / 2;
            double L2 = (sc - sqrt(det)) / 2;
            double cHarris = std::max(L1, L2);
            harris->setPixel(x, y, cHarris);
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

QString Harris::getMethodName() {
    return "harris";
}

Harris::Harris(const shared_ptr<DoubleImage> &image, const QString &imageName, const QString &imageExt)
        : AbstractPointsFinder(image, imageName, imageExt) {}
