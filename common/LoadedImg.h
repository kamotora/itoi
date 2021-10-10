#ifndef ITOI_LOADEDIMG_H
#define ITOI_LOADEDIMG_H

#include <cstdlib>
#include <cmath>
#include <memory>
#include <algorithm>
#include <QImage>
#include "QString"
#include "ProcessingImg.h"
#include "iostream"

using namespace std;

class LoadedImg : public AbstractImg {
private:
    LoadedImg(int width, int height);

    explicit LoadedImg(const QImage &image);

    inline static const QString RESOURCES = "../resources";
    inline static const QString INPUT = "/input/";
    inline static const QString OUTPUT = "/output/lab5/";
    QImage img;
    unique_ptr<unsigned char[]> data;
    QString name;

    void set_pixel(int i, unsigned char value);

    static unsigned char grayscale(const QColor &rgbPixel);

public:
    static LoadedImg by_image_name(const QString &imageName);

    static LoadedImg copy(const QPixmap &pixmap);

    LoadedImg *save(const QString &imageName);

    LoadedImg *save(const string &imageName);

    unsigned char pixel(int x, int y);

    unsigned char pixel(int i);

    [[nodiscard]]
    const QString &get_name() const;

    void set_name(const QString &_name);

    ProcessingImg to_processing_img();

    static LoadedImg from_processing_img(ProcessingImg &image);

    QImage native_image();

    static void save(const QImage &image, const QString &imageName);

    void set_pixel(int x, int y, unsigned char value);

    LoadedImg();
};


#endif //ITOI_LOADEDIMG_H
