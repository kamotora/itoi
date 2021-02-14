#ifndef ITOI_INPUTIMAGE_H
#define ITOI_INPUTIMAGE_H

#include <cstdlib>
#include <cmath>
#include <memory>
#include <algorithm>
#include <QImage>
#include "QString"
#include "helper.h"

using namespace std;

class InputImage {
private:
    QImage img;
    int width, height;
    unique_ptr<unsigned char[]> data;

    void setImage(const QImage& image);

    void setPixel(int x, int y, unsigned char value);

    void setPixel(int i, unsigned char value);

public:
    static InputImage *fromPath(const QString &pathToImage);

    [[nodiscard]] int getWidth() const;

    [[nodiscard]] int getHeight() const;

    unsigned char getPixel(int x, int y);

    unsigned char getPixel(int i);
};


#endif //ITOI_INPUTIMAGE_H
