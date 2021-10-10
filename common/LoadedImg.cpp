#include <QLabel>
#include "LoadedImg.h"

void LoadedImg::setImage(const QImage &image) {
    img = image;
    height = image.height();
    width = image.width();
    data = std::make_unique<unsigned char[]>(get_size());
    for (int x = 0; x < width; x++) {
        for (int y = 0; y < height; y++) {
            set_pixel(x, y, grayscale(image.pixelColor(x, y)));
        }
    }
}

unsigned char LoadedImg::grayscale(const QColor &rgbPixel) {
    auto result = 0.213 * rgbPixel.red() + 0.715 * rgbPixel.green() + 0.072 * rgbPixel.blue();
    return result;
}

LoadedImg LoadedImg::by_image_name(const QString &imageName) {
    QString path = RESOURCES + INPUT + imageName;
    QImage image(path);
    if (image.isNull())
        throw invalid_argument("Fail to load image. Check path: " + path.toStdString());
    LoadedImg loadedImg = LoadedImg();
    loadedImg.setImage(image);
    loadedImg.set_name(imageName.left(imageName.indexOf(".")));
    return loadedImg;
}

int LoadedImg::get_height() const {
    return height;
}

int LoadedImg::get_width() const {
    return width;
}

void LoadedImg::set_pixel(int x, int y, unsigned char value) {
    set_pixel(to_index(x, y), value);
}

void LoadedImg::set_pixel(int i, unsigned char value) {
    data.get()[i] = value;
}

unsigned char LoadedImg::get_pixel(int x, int y) {
    return get_pixel(to_index(x, y));
}

unsigned char LoadedImg::get_pixel(int i) {
    return data.get()[i];
}

ProcessingImg LoadedImg::to_processing_img() {
    auto res = ProcessingImg(width, height);
    for (int i = 0; i < width * height; i++) {
        res.set_pixel(i, get_pixel(i));
    }
    return res.normalize();
}

LoadedImg LoadedImg::from_processing_img(ProcessingImg &image) {
    image = image.normalize(255);
    LoadedImg result;
    result.height = image.get_height();
    result.width = image.get_width();
    result.data = std::make_unique<unsigned char[]>(result.width * result.height);
    result.img = QImage(result.width, result.height, QImage::Format_RGB32);
    for (int x = 0; x < result.width; x++)
        for (int y = 0; y < result.height; y++) {
            unsigned char pixel = image.get_pixel(x, y);
            result.set_pixel(x, y, pixel);
            result.img.setPixel(x, y, qRgb(pixel, pixel, pixel));
        }
    return result;
}

QImage LoadedImg::native_image() {
    return img;
}

void LoadedImg::save(const QImage& image, const QString &imageName) {
    if (image.isNull()) {
        cerr << "Try to save null image" << endl;
        throw invalid_argument("Try to save null image");
    }
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
    auto img = LoadedImg();
    img.setImage(pixmap.toImage());
    return img;
}


const QString &LoadedImg::get_name() const {
    return name;
}

void LoadedImg::set_name(const QString &_name) {
    LoadedImg::name = _name;
}
