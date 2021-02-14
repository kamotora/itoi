#include "InputImage.h"

void InputImage::setImage(const QImage& image) {
    img = image;
    height = image.height();
    width = image.width();
    data = std::make_unique<unsigned char[]>(width * height);
    for (int x = 0; x < width; x++) {
        for (int y = 0; y < height; y++) {
            setPixel(x, y, Helper::toSRGB(image.pixelColor(x, y)));
        }
    }
}

InputImage *InputImage::fromPath(const QString &pathToImage) {
    QImage image(pathToImage);
    auto inputImage = new InputImage();
    inputImage->setImage(image);
    return inputImage;
}

int InputImage::getHeight() const {
    return height;
}

int InputImage::getWidth() const {
    return width;
}

void InputImage::setPixel(int x, int y, unsigned char value) {
    setPixel(x + y * width, value);
}

void InputImage::setPixel(int i, unsigned char value) {
    data.get()[i] = value;
}

unsigned char InputImage::getPixel(int x, int y) {
    return getPixel(x + y * width);
}

unsigned char InputImage::getPixel(int i) {
    return data.get()[i];
}
