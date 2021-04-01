//
// Created by kamotora on 01.04.2021.
//

#include "DoubleImageBorderPolicy.h"

double DoubleImageBorderPolicy::getBorderedPixel(int x, int y) const {
   return borderPolicy.getPixel((DoubleImage &) *this, x, y);
}


DoubleImageBorderPolicy::DoubleImageBorderPolicy(const shared_ptr<DoubleImage> &other, IBorderPolicy &borderPolicy)
        : DoubleImage(*other), borderPolicy(borderPolicy) {
}
