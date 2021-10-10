#include <QLabel>
#include <filesystem>
#include "LoadedImg.h"

unsigned char LoadedImg::grayscale(const QColor &rgbPixel) {
    return 0.213 * rgbPixel.red() + 0.715 * rgbPixel.green() + 0.072 * rgbPixel.blue();
}

LoadedImg LoadedImg::by_image_name(const QString &imageName) {
    QString path = RESOURCES + INPUT + imageName;
    QImage image(path);
    if (image.isNull())
        throw invalid_argument("Fail to load image. Check path: " + path.toStdString());
    LoadedImg loadedImg = LoadedImg(image);
    loadedImg.set_name(imageName.left(imageName.indexOf(".")));
    return loadedImg;
}

void LoadedImg::set_pixel(int x, int y, unsigned char value) {
    set_pixel(to_index(x, y), value);
}

void LoadedImg::set_pixel(int i, unsigned char value) {
    data.get()[i] = value;
}

unsigned char LoadedImg::pixel(int x, int y) {
    return pixel(to_index(x, y));
}

unsigned char LoadedImg::pixel(int i) {
    return data.get()[i];
}

ProcessingImg LoadedImg::to_processing_img() {
    auto res = ProcessingImg(_width, _height);
    for (int i = 0; i < _width * _height; i++) {
        res.set_pixel(i, pixel(i));
    }
    return res.normalize();
}

LoadedImg LoadedImg::from_processing_img(ProcessingImg &image) {
    image = image.normalize(255);
    LoadedImg result = LoadedImg(image.width(), image.height());
    result.data = std::make_unique<unsigned char[]>(result._width * result._height);
    result.img = QImage(result._width, result._height, QImage::Format_RGB32);
    for (int x = 0; x < result._width; x++)
        for (int y = 0; y < result._height; y++) {
            unsigned char pixel = image.pixel(x, y);
            result.set_pixel(x, y, pixel);
            result.img.setPixel(x, y, qRgb(pixel, pixel, pixel));
        }
    return result;
}

QImage LoadedImg::native_image() {
    return img;
}

void LoadedImg::save(const QImage &image, const QString &imageName) {
    if (image.isNull()) {
        cerr << "Try to save null image" << endl;
        throw invalid_argument("Try to save null image");
    }
    auto dir = (RESOURCES + OUTPUT).toStdString();
    std::filesystem::create_directories(dir);
    image.save(RESOURCES + OUTPUT + imageName);
}

LoadedImg *LoadedImg::save(const QString &imageName) {
    save(img, imageName);
    return this;
}

LoadedImg *LoadedImg::save(const string &imageName) {
    return save(QString::fromStdString(imageName));
}

LoadedImg LoadedImg::copy(const QPixmap &pixmap) {
    return LoadedImg(pixmap.toImage());
}


const QString &LoadedImg::get_name() const {
    return name;
}

void LoadedImg::set_name(const QString &_name) {
    LoadedImg::name = _name;
}

LoadedImg::LoadedImg(int width, int height) : AbstractImg(width, height) {}

LoadedImg::LoadedImg(const QImage &image) : AbstractImg(image.width(), image.height()) {
    this->img = image;
    this->data = std::make_unique<unsigned char[]>(size());
    for (int x = 0; x < _width; x++) {
        for (int y = 0; y < _height; y++) {
            set_pixel(x, y, grayscale(image.pixelColor(x, y)));
        }
    }
}

LoadedImg::LoadedImg() : AbstractImg() {

}
