#include "FilterUtil.h"

#include <utility>


DoubleImage FilterUtil::applyCrossCorel(DoubleImage &image, DoubleImage &kernel, IBorderPolicy &borderPolicy) {
    int kernelW = kernel.getWidth();
    int kernelH = kernel.getHeight();
    if (!(kernelW % 2) || !(kernelH % 2)) {
        cerr << "Invalid kernel size" << endl;
    }
    int kernelKW = kernelW / 2;
    int kernelKH = kernelH / 2;
    auto result = DoubleImage(image.getWidth(), image.getHeight());
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

shared_ptr<DoubleImage>
FilterUtil::applyConvolution(const shared_ptr<DoubleImage> &image, DoubleImage &kernel, IBorderPolicy &borderPolicy) {
    int kernelW = kernel.getWidth();
    int kernelH = kernel.getHeight();
    if (!(kernelW % 2) || !(kernelH % 2)) {
        cerr << "Invalid kernel size. Width: " << kernelW << ", height: " << kernelH << endl;
    }
    int kernelKW = kernelW / 2;
    int kernelKH = kernelH / 2;
    auto result = make_shared<DoubleImage>(image->getWidth(), image->getHeight());
    for (int x = 0; x < image->getWidth(); x++) {
        for (int y = 0; y < image->getHeight(); y++) {
            double res = 0;
            for (int i = 0, u = -kernelKW; i < kernelW; i++, u++) {
                for (int j = 0, v = -kernelKH; j < kernelH; j++, v++) {
                    res += borderPolicy.getPixel(*image, x - u, y - v) * kernel.getPixel(i, j);
                }
            }
            result->setPixel(x, y, res);
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

shared_ptr<DoubleImage> FilterUtil::derivX(const shared_ptr<DoubleImage> &image, IBorderPolicy &borderPolicy) {
    auto kernel = Kernels::GetSobelSeparableX();
    return applySeparable(image, kernel, false, borderPolicy);
}

shared_ptr<DoubleImage> FilterUtil::derivY(const shared_ptr<DoubleImage> &image, IBorderPolicy &borderPolicy) {
    auto kernel = Kernels::GetSobelSeparableY();
    return applySeparable(image, kernel, false, borderPolicy);
}

shared_ptr<DoubleImage>
FilterUtil::applyGauss(const shared_ptr<DoubleImage> &image, double sigma, IBorderPolicy &policy, bool normalize) {
    auto gaussFilter = Kernels::GetGauss(sigma);
    auto res = FilterUtil::applyConvolution(image, gaussFilter, policy);
    if (normalize)
        return make_shared<DoubleImage>(res->normalize());
    return res;
}

shared_ptr<DoubleImage>
FilterUtil::applyGauss(const shared_ptr<DoubleImage> &image, int halfSize, IBorderPolicy &policy, bool normalize) {
    auto gaussFilter = Kernels::GetGauss(halfSize, normalize);
    auto res = FilterUtil::applyConvolution(image, gaussFilter, policy);
    if (normalize)
        return make_shared<DoubleImage>(res->normalize());
    return res;
}

shared_ptr<DoubleImage>
FilterUtil::applyGaussSeparable(const shared_ptr<DoubleImage> &image, double sigma, IBorderPolicy &policy,
                                bool normalize) {
    auto result = applySeparable(image, Kernels::GetGaussSeparableXY(sigma), normalize, policy);
    if (normalize)
        return make_shared<DoubleImage>(result->normalize());
    return result;
}

shared_ptr<DoubleImage>
FilterUtil::applyGaussSeparable(const shared_ptr<DoubleImage> &image, int halfSize, IBorderPolicy &policy,
                                bool normalize) {
    auto result = applySeparable(image, Kernels::GetGaussSeparableXY(halfSize, normalize), normalize, policy);
    if (normalize)
        return make_shared<DoubleImage>(result->normalize());
    return result;
}

shared_ptr<DoubleImage>
FilterUtil::applySeparable(const shared_ptr<DoubleImage> &image, pair<DoubleImage, DoubleImage> pair, bool normalize,
                           IBorderPolicy &policy) {
    auto resX = applyConvolution(image, pair.first, policy);
    auto resY = applyConvolution(resX, pair.second, policy);
    if (normalize)
        return make_shared<DoubleImage>(resY->normalize());
    return resY;
}

double FilterUtil::getSeparableValue(pair<DoubleImage, DoubleImage> &pair, int x, int y) {
    return pair.first.getPixel(x, 0) * pair.second.getPixel(0, y);
}
