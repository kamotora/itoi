#ifndef ITOI_INPUTIMAGE_H
#define ITOI_INPUTIMAGE_H

#include <cstdlib>
#include <cmath>
#include <memory>
#include <algorithm>
#include <QImage>
#include "QString"
#include "helper.h"
#include "DoubleImage.h"
#include "iostream"

using namespace std;

class InputImage {
private:
    inline static const QString RESOURCES = "../resources";
    inline static const QString INPUT = "/input/";
    inline static const QString OUTPUT = "/output/lab2/";
    QImage img;
    int width, height;
    unique_ptr<unsigned char[]> data;

    void setImage(const QImage &image);

    void setPixel(int x, int y, unsigned char value);

    void setPixel(int i, unsigned char value);

public:
    static InputImage fromResources(const QString &imageName);

    InputImage *saveToResources(const QString &imageName);
    InputImage *saveToResources(const string &imageName);

    [[nodiscard]] int getWidth() const;

    [[nodiscard]] int getHeight() const;

    unsigned char getPixel(int x, int y);

    unsigned char getPixel(int i);

    DoubleImage toDoubleImage();

    static InputImage fromDoubleImage(DoubleImage &image);

    QImage getImage();

    InputImage *open(const QString &imageName = "output");

    static void saveToResources(const QImage &image, const QString &imageName);
};


#endif //ITOI_INPUTIMAGE_H
