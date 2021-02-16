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
        testSobelOper("shrek", ".jpg", Policies::SYMMETRY);
        cout << "end work" << endl;
    }

    static void testSobelOper(const QString& imageName, const QString& extention, IBorderPolicy &borderPolicy){
        auto input = InputImage::fromResources(imageName + extention);
        auto doubleInputImage = input.toDoubleImage();
        auto sobelXImage = FilterUtil::derivX(doubleInputImage);
        auto sobelYImage = FilterUtil::derivY(doubleInputImage);
        auto result = DoubleImage(input.getWidth(), input.getHeight());
        for (int i = 0; i < result.getSize(); ++i)
            result.setPixel(i, sqrt(sobelXImage.getPixel(i) * sobelXImage.getPixel(i) + sobelYImage.getPixel(i) * sobelYImage.getPixel(i)));
        InputImage::fromDoubleImage(sobelXImage).saveToResources(imageName + "_derivativeX" + extention);
        InputImage::fromDoubleImage(sobelYImage).saveToResources(imageName + "_derivativeY" + extention);
        InputImage::fromDoubleImage(result).saveToResources(imageName + "_sobel" + extention);
    }
};


#endif //ITOI_LAB1_H
