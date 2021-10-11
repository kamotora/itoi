
#ifndef IP_DISTORTION_H
#define IP_DISTORTION_H


#include <QtGui/QPixmap>

class AbstractDistortion {
public:
    AbstractDistortion() = default;

    virtual QPixmap distort(QPixmap pixmap) = 0;

    virtual QString getName() = 0;

    virtual ~AbstractDistortion() = default;
};


#endif //IP_DISTORTION_H
