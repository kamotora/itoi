#ifndef ITOI_FILTERUTIL_H
#define ITOI_FILTERUTIL_H

#include <ostream>
#include "../core/DoubleImage.h"
#include <iomanip>
#include "iostream"
#include "border/IBorderPolicy.h"
#include "border/MirrorPolicy.h"
#include "Kernels.h"
using namespace std;

class FilterUtil {
public:
    constexpr static MirrorPolicy DEFAULT_POLICY = MirrorPolicy();
    static void print(ostream &out, DoubleImage &matrix);

    static DoubleImage applyCrossCorel(DoubleImage &image, DoubleImage &kernel, IBorderPolicy &borderPolicy);

    static shared_ptr<DoubleImage> applyConvolution(const shared_ptr<DoubleImage>& image, DoubleImage &kernel,
                                                    IBorderPolicy &borderPolicy = (IBorderPolicy &) DEFAULT_POLICY);

    static shared_ptr<DoubleImage> derivX(const shared_ptr<DoubleImage>& image,
                                          IBorderPolicy &borderPolicy = (IBorderPolicy &) DEFAULT_POLICY);

    static shared_ptr<DoubleImage> derivY(const shared_ptr<DoubleImage>& image,
                                          IBorderPolicy &borderPolicy = (IBorderPolicy &) DEFAULT_POLICY);


    static shared_ptr<DoubleImage> applyGauss(const shared_ptr<DoubleImage>& image, double sigma,
                                              IBorderPolicy &policy = (IBorderPolicy &) DEFAULT_POLICY, bool normalize = false);

    static shared_ptr<DoubleImage> applySeparable(const shared_ptr<DoubleImage>& image, pair<DoubleImage,DoubleImage>, bool normalize = true,
                                                  IBorderPolicy &policy = (IBorderPolicy &) DEFAULT_POLICY);

    static shared_ptr<DoubleImage>
    applyGaussSeparable(const shared_ptr<DoubleImage> &image, double sigma,
                        IBorderPolicy &policy = (IBorderPolicy &) DEFAULT_POLICY, bool normalize = false);


    static double getSeparableValue(pair<DoubleImage, DoubleImage> &pair, int x, int y) ;


    static shared_ptr<DoubleImage>
    applyGaussSeparable(const shared_ptr<DoubleImage> &image, int halfSize, IBorderPolicy &policy, bool normalize);

    static shared_ptr<DoubleImage>
    applyGauss(const shared_ptr<DoubleImage> &image, int halfSize, IBorderPolicy &policy, bool normalize);
};


#endif //ITOI_FILTERUTIL_H
