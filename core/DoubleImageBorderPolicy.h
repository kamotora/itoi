//
// Created by kamotora on 01.04.2021.
//

#ifndef ITOI_DOUBLEIMAGEBORDERPOLICY_H
#define ITOI_DOUBLEIMAGEBORDERPOLICY_H


#include "DoubleImage.h"
#include "../filter/border/CopyPolicy.h"

class DoubleImageBorderPolicy : public DoubleImage {
private:
    IBorderPolicy &borderPolicy;
public:
    DoubleImageBorderPolicy(const shared_ptr<DoubleImage>& other, IBorderPolicy &borderPolicy);
    [[nodiscard]] double getBorderedPixel(int x, int y) const;

};


#endif //ITOI_DOUBLEIMAGEBORDERPOLICY_H
