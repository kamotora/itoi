#include "FilterUtil.h"


DoubleImage FilterUtil::filterCrossCorel(DoubleImage &image, DoubleImage &kernel) {
    int krnW = kernel->getW();
    int krnH = kernel->getH();
    if (!(krnW % 2) || !(krnH % 2)) {
        cerr << "Invalid kernel size" << endl;
    }
    int krnKW = krnW / 2;
    int krnKH = krnH / 2;
    double *result = new double[w * h];
    for (int iH = 0; iH < image.getHeight(); iH++) {
        for (int iW = 0; iW < image.getWidth(); iW++) {
            double v = 0;
            for (int jH = 0, kH = -krnKH; jH < kernel.getHeight(); jH++, kH++) {
                for (int jW = 0, kW = -krnKW; jW < kernel.getWidth(); jW++, kW++) {
                    v += image->getValue(iW + kW, iH + kH) * kernel->getValue(jW, jH);
                }
            }
            result[iH * w + iW] = v;
        }
    }
    DoubleImage *resultMatrix = new DoubleImage(w, h, result);
    delete[] result;
    return resultMatrix;
}

DoubleImage *FilterUtil::filterConvolute(DoubleImage &image, DoubleImage &kernel) {
    int krnW = kernel->getW();
    int krnH = kernel->getH();
    if (!(krnW % 2) || !(krnH % 2)) {
        cerr << "Invalid kernel size" << endl;
    }
    int krnKW = krnW / 2;
    int krnKH = krnH / 2;
    int w = image->getW();
    int h = image->getH();
    double *result = new double[w * h];
    for (int iH = 0; iH < h; iH++) {
        for (int iW = 0; iW < w; iW++) {
            double v = 0;
            for (int jH = 0, kH = -krnKH; jH < krnH; jH++, kH++) {
                for (int jW = 0, kW = -krnKW; jW < krnW; jW++, kW++) {
                    v += image->getValue(iW - kW, iH - kH) * kernel->getValue(jW, jH);
                }
            }
            result[iH * w + iW] = v;
        }
    }
    MatrixD *resultMatrix = new MatrixD(w, h, result);
    delete[] result;
    return resultMatrix;
}

void FilterUtil::print(ostream &out, DoubleImage &matrix) {
    int w = matrix.getWidth();
    int h = matrix.getHeight();
    out << "Image [" << w << "," << h << "]" << endl;
    out << std::fixed;
    for (int y = 0; y < h; y++) {
        for (int x = 0; x < w; x++) {
            out << setprecision(3) << setw(7) << right << matrix.getPixel(x, y);
        }
        out << endl;
    }
    out.flush();
}