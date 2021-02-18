#ifndef ITOI_LAB1_H
#define ITOI_LAB1_H

#include "../core/InputImage.h"
#include "../core/DoubleImage.h"
#include "../filter/FilterUtil.h"
#include "../filter/border/IBorderPolicy.h"
#include "../filter/border/Policies.h"
#include "../filter/Kernels.h"
#include "iostream"

using namespace std;

class Lab1 {
public:
    static void work() {
        testSobelOper("butterfly", ".jpg", Policies::COPY);
        testSobelOper("girl", ".jpg", Policies::MIRROR);
        testSobelOper("cat_dog", ".jpg", Policies::SYMMETRY);
        testSobelOper("shrek", ".jpg", Policies::ZERO);
        testGauss("butterfly", ".jpg", 1.3, Policies::SYMMETRY);
        testGauss("butterfly", ".jpg", 0.4, Policies::MIRROR);
        testGauss("butterfly", ".jpg", 5, Policies::COPY);
        testGauss("butterfly", ".jpg", 2.6, Policies::ZERO);
        cout << "end work" << endl;
    }

    static void testSobelOper(const QString &imageName, const QString &extention, IBorderPolicy &borderPolicy) {
        auto input = InputImage::fromResources(imageName + extention);
        auto doubleInputImage = input.toDoubleImage();
        auto sobelXImage = FilterUtil::derivX(doubleInputImage);
        auto sobelYSeparableImage = FilterUtil::applySeparable(doubleInputImage, Kernels::GetSobelSeparableY());
        auto sobelYImage = FilterUtil::derivY(doubleInputImage);
        auto result = DoubleImage(input.getWidth(), input.getHeight());
        for (int i = 0; i < result.getSize(); ++i)
            result.setPixel(i, sqrt(sobelXImage.getPixel(i) * sobelXImage.getPixel(i) +
                                    sobelYImage.getPixel(i) * sobelYImage.getPixel(i)));
        InputImage::fromDoubleImage(sobelXImage).saveToResources(
                imageName + "_derivativeX_" + borderPolicy.toString() + extention);
        InputImage::fromDoubleImage(sobelYSeparableImage).saveToResources(
                imageName + "_separable_derivativeY_" + borderPolicy.toString() + extention);
        InputImage::fromDoubleImage(sobelYImage).saveToResources(
                imageName + "_derivativeY_" + borderPolicy.toString() + extention);
        InputImage::fromDoubleImage(result).saveToResources(
                imageName + "_sobel_" + borderPolicy.toString() + extention);
    }

    static void testGauss(const QString &imageName, const QString &extention, double sigma, IBorderPolicy &borderPolicy) {
        auto input = InputImage::fromResources(imageName + extention);
        auto doubleInputImage = input.toDoubleImage();
        double sigmaForTwiceFiltering = sigma;
        double sigmaSum = sigmaForTwiceFiltering * sqrt(2);
        cout << "start for " << imageName.toStdString() << " with sigmaForTwiceFiltering " << sigma << endl;
        cout << "start for " << imageName.toStdString() << " with sigmaSum " << sigmaSum << endl;
        auto gaussA = FilterUtil::applyGauss(doubleInputImage, sigmaForTwiceFiltering, borderPolicy);
        auto twiceGauss = FilterUtil::applyGauss(gaussA, sigmaForTwiceFiltering, borderPolicy);
        auto gaussSum = FilterUtil::applyGauss(doubleInputImage, sigmaSum, borderPolicy);
//        auto separableGauss = FilterUtil::applyGaussSeparable(doubleInputImage, sigmaSum, borderPolicy);
        InputImage::fromDoubleImage(twiceGauss).saveToResources(
                imageName + "_gauss_twice_sigma" + QString::fromStdString(to_string(sigmaForTwiceFiltering)) + '_' +
                borderPolicy.toString() + extention);
        InputImage::fromDoubleImage(gaussSum).saveToResources(
                imageName + "_gauss_sigma" + QString::fromStdString(to_string(sigmaSum)) + '_' +
                borderPolicy.toString() + extention);
//        InputImage::fromDoubleImage(gaussSum).saveToResources(
//                imageName + "_separable_gauss_sigma" + QString::fromStdString(to_string(sigmaSum)) + '_' +
//                borderPolicy.toString() + extention);
    }
};


#endif //ITOI_LAB1_H
