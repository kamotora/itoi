#include "FilterUtil.h"


DoubleImage FilterUtil::applyCrossCorel(DoubleImage &image, DoubleImage &kernel, IBorderPolicy &borderPolicy) {
    int kernelW = kernel.getWidth();
    int kernelH = kernel.getHeight();
    if (!(kernelW % 2) || !(kernelH % 2)) {
        cerr << "Invalid kernel size" << endl;
    }
    int kernelKW = kernelW / 2;
    int kernelKH = kernelH / 2;
    auto result  = DoubleImage(image.getWidth(), image.getHeight());
    for (int x = 0; x < image.getWidth(); x++) {
        for (int y = 0; y < image.getHeight(); y++) {
            double res = 0;
            for (int i = 0, u = -kernelKW; i < kernel.getWidth(); i++, u++) {
                for (int j = 0, v = -kernelKH; j < kernel.getHeight(); j++, v++) {
                    res += borderPolicy.getPixel(image, x + u, y + v) * kernel.getPixel(i, j);
                }
            }
            result.setPixel(x, y, res);
        }
    }
    return result;
}

DoubleImage FilterUtil::applyConvolution(DoubleImage &image, DoubleImage &kernel, IBorderPolicy &borderPolicy) {
    int kernelW = kernel.getWidth();
    int kernelH = kernel.getHeight();
    if (!(kernelW % 2) || !(kernelH % 2)) {
        cerr << "Invalid kernel size. Width: " << kernelW << ", height: " << kernelH << endl;
    }
    int kernelKW = kernelW / 2;
    int kernelKH = kernelH / 2;
    auto result  = DoubleImage(image.getWidth(), image.getHeight());
    for (int x = 0; x < image.getWidth(); x++) {
        for (int y = 0; y < image.getHeight(); y++) {
            double res = 0;
            for (int i = 0, u = -kernelKW; i < kernelW; i++, u++) {
                for (int j = 0, v = -kernelKH; j < kernelH; j++, v++) {
                    res += borderPolicy.getPixel(image, x - u, y - v) * kernel.getPixel(i, j);
                }
            }
            result.setPixel(x, y, res);
        }
    }
    return result;
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

DoubleImage FilterUtil::derivX(DoubleImage &image, IBorderPolicy &borderPolicy) {
    auto kernel = Kernels::GetSobelX();
    return applyConvolution(image, kernel, borderPolicy);
}

DoubleImage FilterUtil::derivY(DoubleImage &image, IBorderPolicy &borderPolicy) {
    auto kernel = Kernels::GetSobelY();
    return applyConvolution(image, kernel, borderPolicy);
}

DoubleImage FilterUtil::applyGauss(DoubleImage &image, double sigma, IBorderPolicy &policy, bool normalize){
    auto gaussFilter = Kernels::GetGauss(sigma);
    auto res = FilterUtil::applyConvolution(image, gaussFilter, policy);
    if(normalize)
        return res.normalize();
    return res;
}

DoubleImage FilterUtil::applyGaussSeparable(DoubleImage &image, double sigma, IBorderPolicy &policy, bool normalize) {
    auto result = applySeparable(image, Kernels::GetGaussSeparableXY(sigma), policy);
    if(normalize)
        return result.normalize();
    return result;
}

DoubleImage FilterUtil::applySeparable(DoubleImage &image, pair<DoubleImage, DoubleImage> pair, IBorderPolicy &policy) {
    auto resX = applyConvolution(image, pair.first, policy);
    auto resY = applyConvolution(resX, pair.second, policy);
    return resY;
}
