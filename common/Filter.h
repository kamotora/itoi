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
    static void print(ostream &out, ProcessingImg &matrix);

    static ProcessingImg applyCrossCorel(ProcessingImg &image, ProcessingImg &kernel, IBorderPolicy &borderPolicy);

    static shared_ptr<ProcessingImg> applyConvolution(const shared_ptr<ProcessingImg>& image, ProcessingImg &kernel,
                                                    IBorderPolicy &borderPolicy = (IBorderPolicy &) DEFAULT_POLICY);

    static shared_ptr<ProcessingImg> sobel_x(const shared_ptr<ProcessingImg>& image,
                                             IBorderPolicy &borderPolicy = (IBorderPolicy &) DEFAULT_POLICY);

    static shared_ptr<ProcessingImg> sobel_y(const shared_ptr<ProcessingImg>& image,
                                             IBorderPolicy &borderPolicy = (IBorderPolicy &) DEFAULT_POLICY);


    static shared_ptr<ProcessingImg> applyGauss(const shared_ptr<ProcessingImg>& image, double sigma,
                                              IBorderPolicy &policy = (IBorderPolicy &) DEFAULT_POLICY, bool normalize = false);

    static shared_ptr<ProcessingImg> applySeparable(const shared_ptr<ProcessingImg>& image, pair<ProcessingImg,ProcessingImg>, bool normalize = true,
                                                  IBorderPolicy &policy = (IBorderPolicy &) DEFAULT_POLICY);

    static shared_ptr<ProcessingImg>
    applyGaussSeparable(const shared_ptr<ProcessingImg> &image, double sigma,
                        IBorderPolicy &policy = (IBorderPolicy &) DEFAULT_POLICY, bool normalize = false);


    static double get_separable_value(pair<ProcessingImg, ProcessingImg> &pair, int x, int y) ;


    static shared_ptr<ProcessingImg>
    applyGaussSeparable(const shared_ptr<ProcessingImg> &image, int halfSize, IBorderPolicy &policy, bool normalize);

    static shared_ptr<ProcessingImg>
    applyGauss(const shared_ptr<ProcessingImg> &image, int halfSize, IBorderPolicy &policy, bool normalize);
};


#endif //ITOI_FILTER_H
