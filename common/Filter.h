#ifndef ITOI_FILTER_H
#define ITOI_FILTER_H

#include <ostream>
#include "ProcessingImg.h"
#include <iomanip>
#include "iostream"
#include "border/IBorderPolicy.h"
#include "border/MirrorPolicy.h"
#include "Kernels.h"

using namespace std;

class Filter {
public:
    constexpr static MirrorPolicy DEFAULT_POLICY = MirrorPolicy();

    static shared_ptr<ProcessingImg> apply_kernel(const shared_ptr<ProcessingImg> &image, ProcessingImg &kernel,
                                                  IBorderPolicy &borderPolicy = (IBorderPolicy &) DEFAULT_POLICY);

    static shared_ptr<ProcessingImg> sobel_x(const shared_ptr<ProcessingImg> &image,
                                             IBorderPolicy &borderPolicy = (IBorderPolicy &) DEFAULT_POLICY);

    static shared_ptr<ProcessingImg> sobel_y(const shared_ptr<ProcessingImg> &image,
                                             IBorderPolicy &borderPolicy = (IBorderPolicy &) DEFAULT_POLICY);


    static shared_ptr<ProcessingImg> gauss(const shared_ptr<ProcessingImg> &image, double sigma,
                                           IBorderPolicy &policy = (IBorderPolicy &) DEFAULT_POLICY,
                                           bool normalize = false);

    static shared_ptr<ProcessingImg>
    apply_separable(const shared_ptr<ProcessingImg> &image, pair<ProcessingImg, ProcessingImg>, bool normalize = true,
                    IBorderPolicy &policy = (IBorderPolicy &) DEFAULT_POLICY);

    static shared_ptr<ProcessingImg>
    gauss_separable(const shared_ptr<ProcessingImg> &image, double sigma,
                    IBorderPolicy &policy = (IBorderPolicy &) DEFAULT_POLICY, bool normalize = false);


    static double get_separable_value(pair<ProcessingImg, ProcessingImg> &pair, int x, int y);


    static shared_ptr<ProcessingImg>
    gauss_separable(const shared_ptr<ProcessingImg> &image, int halfSize, IBorderPolicy &policy, bool normalize);

    static shared_ptr<ProcessingImg>
    gauss(const shared_ptr<ProcessingImg> &image, int halfSize, IBorderPolicy &policy, bool normalize);
};


#endif //ITOI_FILTER_H
