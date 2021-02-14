#ifndef ITOI_HELPER_H
#define ITOI_HELPER_H

#include <QColor>
#include "memory"

using namespace std;

class Helper {
public:
    static unsigned char toSRGB(const QColor &rgbPixel);

    void normalizeMinMax(unique_ptr<double[]> data, int size);
};
#endif //ITOI_HELPER_H
