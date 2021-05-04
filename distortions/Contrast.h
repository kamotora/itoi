
#ifndef IP_CONTRAST_H
#define IP_CONTRAST_H


#include "Distortion.h"
#include "cmath"
#include "../core/helper.h"

using namespace std;

class Contrast : public Distortion {
public:
    explicit Contrast(double factor) : _factor(factor) {};

    QPixmap distort(QPixmap pixmap) override;


    inline QString getName() override { return QStringLiteral("CONTRAST_%1").arg(_factor); }

private:
    double _factor;

    int change(double value) const;
};


#endif //IP_CONTRAST_H
