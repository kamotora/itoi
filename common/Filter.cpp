#include "Filter.h"

#include <utility>

shared_ptr<ProcessingImg>
Filter::apply_kernel(const shared_ptr<ProcessingImg> &image, ProcessingImg &kernel, IBorderPolicy &borderPolicy) {
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


shared_ptr<ProcessingImg> Filter::sobel_x(const shared_ptr<ProcessingImg> &image, IBorderPolicy &borderPolicy) {
    auto kernel = Kernels::sobel_separable_x();
    return apply_separable(image, kernel, false, borderPolicy);
}

shared_ptr<ProcessingImg> Filter::sobel_y(const shared_ptr<ProcessingImg> &image, IBorderPolicy &borderPolicy) {
    auto kernel = Kernels::sobel_separable_y();
    return apply_separable(image, kernel, false, borderPolicy);
}

shared_ptr<ProcessingImg>
Filter::gauss(const shared_ptr<ProcessingImg> &image, double sigma, IBorderPolicy &policy, bool normalize) {
    auto gaussFilter = Kernels::get_gauss(sigma);
    auto res = Filter::apply_kernel(image, gaussFilter, policy);
    if (normalize)
        return make_shared<ProcessingImg>(res->normalize());
    return res;
}

shared_ptr<ProcessingImg>
Filter::gauss(const shared_ptr<ProcessingImg> &image, int halfSize, IBorderPolicy &policy, bool normalize) {
    auto gaussFilter = Kernels::get_gauss(halfSize, normalize);
    auto res = Filter::apply_kernel(image, gaussFilter, policy);
    if (normalize)
        return make_shared<ProcessingImg>(res->normalize());
    return res;
}

shared_ptr<ProcessingImg>
Filter::gauss_separable(const shared_ptr<ProcessingImg> &image, double sigma, IBorderPolicy &policy,
                        bool normalize) {
    auto result = apply_separable(image, Kernels::get_gauss_separable_xy(sigma), normalize, policy);
    if (normalize)
        return make_shared<ProcessingImg>(result->normalize());
    return result;
}

shared_ptr<ProcessingImg>
Filter::gauss_separable(const shared_ptr<ProcessingImg> &image, int halfSize, IBorderPolicy &policy,
                        bool normalize) {
    auto result = apply_separable(image, Kernels::gauss_separable_xy(halfSize, normalize), normalize, policy);
    if (normalize)
        return make_shared<ProcessingImg>(result->normalize());
    return result;
}

shared_ptr<ProcessingImg>
Filter::apply_separable(const shared_ptr<ProcessingImg> &image, pair<ProcessingImg, ProcessingImg> pair, bool normalize,
                        IBorderPolicy &policy) {
    auto resX = apply_kernel(image, pair.first, policy);
    auto resY = apply_kernel(resX, pair.second, policy);
    if (normalize)
        return make_shared<ProcessingImg>(resY->normalize());
    return resY;
}

double Filter::get_separable_value(pair<ProcessingImg, ProcessingImg> &pair, int x, int y) {
    return pair.first.pixel(x, 0) * pair.second.pixel(0, y);
}
