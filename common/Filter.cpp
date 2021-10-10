#include "Filter.h"

#include <utility>


ProcessingImg Filter::applyCrossCorel(ProcessingImg &image, ProcessingImg &kernel, IBorderPolicy &borderPolicy) {
    int kernelW = kernel.width();
    int kernelH = kernel.height();
    if (!(kernelW % 2) || !(kernelH % 2)) {
        cerr << "Invalid kernel size" << endl;
    }
    int kernelKW = kernelW / 2;
    int kernelKH = kernelH / 2;
    auto result = ProcessingImg(image.width(), image.height());
    for (int x = 0; x < image.width(); x++) {
        for (int y = 0; y < image.height(); y++) {
            double res = 0;
            for (int i = 0, u = -kernelKW; i < kernel.width(); i++, u++) {
                for (int j = 0, v = -kernelKH; j < kernel.height(); j++, v++) {
                    res += borderPolicy.get_pixel(image, x + u, y + v) * kernel.pixel(i, j);
                }
            }
            result.set_pixel(x, y, res);
        }
    }
    return result;
}

shared_ptr<ProcessingImg>
Filter::applyConvolution(const shared_ptr<ProcessingImg> &image, ProcessingImg &kernel, IBorderPolicy &borderPolicy) {
    int kernelW = kernel.width();
    int kernelH = kernel.height();
    if (!(kernelW % 2) || !(kernelH % 2)) {
        cerr << "Invalid kernel size. Width: " << kernelW << ", _height: " << kernelH << endl;
    }
    int kernelKW = kernelW / 2;
    int kernelKH = kernelH / 2;
    auto result = make_shared<ProcessingImg>(image->width(), image->height());
    for (int x = 0; x < image->width(); x++) {
        for (int y = 0; y < image->height(); y++) {
            double res = 0;
            for (int i = 0, u = -kernelKW; i < kernelW; i++, u++) {
                for (int j = 0, v = -kernelKH; j < kernelH; j++, v++) {
                    res += borderPolicy.get_pixel(*image, x - u, y - v) * kernel.pixel(i, j);
                }
            }
            result->set_pixel(x, y, res);
        }
    }
    return result;
}

void Filter::print(ostream &out, ProcessingImg &matrix) {
    int w = matrix.width();
    int h = matrix.height();
    out << "Image [" << w << "," << h << "]" << endl;
    out << std::fixed;
    for (int y = 0; y < h; y++) {
        for (int x = 0; x < w; x++) {
            out << setprecision(3) << setw(7) << right << matrix.pixel(x, y);
        }
        out << endl;
    }
    out.flush();
}

shared_ptr<ProcessingImg> Filter::sobel_x(const shared_ptr<ProcessingImg> &image, IBorderPolicy &borderPolicy) {
    auto kernel = Kernels::sobel_separable_x();
    return applySeparable(image, kernel, false, borderPolicy);
}

shared_ptr<ProcessingImg> Filter::sobel_y(const shared_ptr<ProcessingImg> &image, IBorderPolicy &borderPolicy) {
    auto kernel = Kernels::sobel_separable_y();
    return applySeparable(image, kernel, false, borderPolicy);
}

shared_ptr<ProcessingImg>
Filter::applyGauss(const shared_ptr<ProcessingImg> &image, double sigma, IBorderPolicy &policy, bool normalize) {
    auto gaussFilter = Kernels::get_gauss(sigma);
    auto res = Filter::applyConvolution(image, gaussFilter, policy);
    if (normalize)
        return make_shared<ProcessingImg>(res->normalize());
    return res;
}

shared_ptr<ProcessingImg>
Filter::applyGauss(const shared_ptr<ProcessingImg> &image, int halfSize, IBorderPolicy &policy, bool normalize) {
    auto gaussFilter = Kernels::get_gauss(halfSize, normalize);
    auto res = Filter::applyConvolution(image, gaussFilter, policy);
    if (normalize)
        return make_shared<ProcessingImg>(res->normalize());
    return res;
}

shared_ptr<ProcessingImg>
Filter::applyGaussSeparable(const shared_ptr<ProcessingImg> &image, double sigma, IBorderPolicy &policy,
                            bool normalize) {
    auto result = applySeparable(image, Kernels::get_gauss_separable_xy(sigma), normalize, policy);
    if (normalize)
        return make_shared<ProcessingImg>(result->normalize());
    return result;
}

shared_ptr<ProcessingImg>
Filter::applyGaussSeparable(const shared_ptr<ProcessingImg> &image, int halfSize, IBorderPolicy &policy,
                            bool normalize) {
    auto result = applySeparable(image, Kernels::gauss_separable_xy(halfSize, normalize), normalize, policy);
    if (normalize)
        return make_shared<ProcessingImg>(result->normalize());
    return result;
}

shared_ptr<ProcessingImg>
Filter::applySeparable(const shared_ptr<ProcessingImg> &image, pair<ProcessingImg, ProcessingImg> pair, bool normalize,
                       IBorderPolicy &policy) {
    auto resX = applyConvolution(image, pair.first, policy);
    auto resY = applyConvolution(resX, pair.second, policy);
    if (normalize)
        return make_shared<ProcessingImg>(resY->normalize());
    return resY;
}

double Filter::get_separable_value(pair<ProcessingImg, ProcessingImg> &pair, int x, int y) {
    return pair.first.pixel(x, 0) * pair.second.pixel(0, y);
}
