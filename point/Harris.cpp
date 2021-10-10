#include "Harris.h"

vector<Point> Harris::find_points(int pointsCount, int windowSize, double tresholdCoef) {
    int w = image->width();
    int h = image->height();
    auto gaussKernel = Kernels::gauss_separable_xy(windowSize, true);
    image = Filter::applySeparable(image, gaussKernel);

    auto dx = Filter::sobel_x(image);
    auto dy = Filter::sobel_y(image);
    auto harris = make_shared<ProcessingImg>(w, h);

    for (int x = 0; x < w; x++) {
        for (int y = 0; y < h; y++) {
            vector<vector<double>> currentMatrix(2, vector<double>(2, 0));
            for (int u = -windowSize; u <= windowSize; u++) {
                for (int v = -windowSize; v <= windowSize; v++) {
                    double values[2] = {0, 0};
                    values[0] = ((IBorderPolicy &) DEFAULT_POLICY).get_pixel(*dx, x + u, y + v);
                    values[1] = ((IBorderPolicy &) DEFAULT_POLICY).get_pixel(*dy, x + u, y + v);
                    double gaussPoint = Filter::get_separable_value(gaussKernel, u + windowSize, v + windowSize);
                    for (int i = 0; i < 2; i++) {
                        for (int j = 0; j < 2; j++) {
                            currentMatrix[i][j] += values[i] * values[j] * gaussPoint;
                        }
                    }
                }
            }
            vector<double> eigenvalues = eigen_values(currentMatrix);
            harris->set_pixel(x, y, *min_element(eigenvalues.begin(), eigenvalues.end()));
        }
    }
    if (!imageName.isNull())
        saveImage(harris, "before_filtering");
    image = harris;
    vector<Point> points = localMaximum(tresholdCoef);
    if (!imageName.isNull())
        drawPoints(points, "localMaximums");
    auto pointsAfterFiltering = filter(points, pointsCount);
    if (!imageName.isNull())
        drawPoints(pointsAfterFiltering, "after_filtering");
    return pointsAfterFiltering;
}

vector<double> Harris::eigen_values(vector<vector<double>> matrix) {
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

QString Harris::method_name() {
    return "harris";
}

Harris::Harris(
        const shared_ptr<ProcessingImg> &image,
        const QString &imageName,
        const QString &imageExt)
        : AbstractInterestPointsAlgo(image, imageName, imageExt) {}

Harris::Harris(
        const shared_ptr<ProcessingImg> &image) : AbstractInterestPointsAlgo(image) {}
