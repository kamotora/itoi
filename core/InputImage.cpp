#include <QLabel>
#include "InputImage.h"

void InputImage::setImage(const QImage &image) {
    img = image;
    height = image.height();
    width = image.width();
    data = std::make_unique<unsigned char[]>(width * height);
    for (int x = 0; x < width; x++) {
        for (int y = 0; y < height; y++) {
            setPixel(x, y, Helper::toGrayscale(image.pixelColor(x, y)));
        }
    }
}

InputImage InputImage::fromResources(const QString &imageName) {
    QString path = RESOURCES + INPUT + imageName;
    QImage image(path);
    if (image.isNull())
        throw invalid_argument("Fail to load image. Check path: " + path.toStdString());
    auto inputImage = InputImage();
    inputImage.setImage(image);
    inputImage.setName(imageName.left(imageName.indexOf(".")));
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

DoubleImage InputImage::toDoubleImage() {
    auto res = DoubleImage(width, height);
    for (int i = 0; i < width * height; i++) {
        res.setPixel(i, getPixel(i));
    }
    return res.normalize();
}

InputImage InputImage::fromDoubleImage(DoubleImage &image) {
    image = image.normalize(255);
    InputImage result;
    result.height = image.getHeight();
    result.width = image.getWidth();
    result.data = std::make_unique<unsigned char[]>(result.width * result.height);
    result.img = QImage(result.width, result.height, QImage::Format_RGB32);
    for (int x = 0; x < result.width; x++)
        for (int y = 0; y < result.height; y++) {
            unsigned char pixel = image.getPixel(x, y);
            result.setPixel(x, y, pixel);
            result.img.setPixel(x, y, qRgb(pixel, pixel, pixel));
        }
    return result;
}

QImage InputImage::getImage() {
    return img;
}

void InputImage::saveToResources(const QImage& image, const QString &imageName) {
    if (image.isNull()) {
        cerr << "Try to saveToResources null image" << endl;
        throw invalid_argument("Try to saveToResources null image");
    }
    image.save(RESOURCES + OUTPUT + imageName);
}

InputImage *InputImage::saveToResources(const QString &imageName) {
    saveToResources(img, imageName);
    return this;
}

InputImage *InputImage::open(const QString &imageName) {
    cerr << "open func not implemented" << endl;
    return this;
//    if (img.isNull()) {
//        cerr << "Try to open null image" << endl;
//        throw invalid_argument("Try to open null image");
//    }
//    QLabel myLabel2(imageName);
//    myLabel2.setPixmap(QPixmap::fromImage(img));
//    myLabel2.show();
//    return this;
}

InputImage *InputImage::saveToResources(const string &imageName) {
    return saveToResources(QString::fromStdString(imageName));
}

InputImage InputImage::from(const QPixmap &pixmap) {
    auto inputImage = InputImage();
    inputImage.setImage(pixmap.toImage());
    return inputImage;
}


InputImage InputImage::from(const QImage &image) {
    auto inputImage = InputImage();
    inputImage.setImage(image);
    return inputImage;
}

const QString &InputImage::getName() const {
    return name;
}

void InputImage::setName(const QString &_name) {
    InputImage::name = _name;
}
