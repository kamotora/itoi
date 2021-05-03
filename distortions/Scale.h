
#ifndef IP_SCALE_H
#define IP_SCALE_H

#include "Distortion.h"

using namespace std;

class Scale : public Distortion {
public:
    explicit Scale(double coeff) : _coeff(coeff) {};

    virtual QPixmap distort(QPixmap pixmap) override;

    inline QString getName() override { return QStringLiteral("SCALED_COEFF_%1").arg(_coeff); }

private:
    double _coeff;
};


#endif //IP_SCALE_H
