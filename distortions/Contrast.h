
#ifndef IP_CONTRAST_H
#define IP_CONTRAST_H


#include "AbstractDistortion.h"
#include "cmath"


using namespace std;

class Contrast : public AbstractDistortion {
public:
    explicit Contrast(double factor) : _factor(factor) {};

    QPixmap distort(QPixmap pixmap) override;


    inline QString getName() override { return QStringLiteral("CONTRAST_%1").arg(_factor); }

private:
    double _factor;

    int change(double value) const;
};


#endif //IP_CONTRAST_H
