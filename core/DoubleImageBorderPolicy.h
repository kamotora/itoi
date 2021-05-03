//
// Created by kamotora on 01.04.2021.
//

#ifndef ITOI_DOUBLEIMAGEBORDERPOLICY_H
#define ITOI_DOUBLEIMAGEBORDERPOLICY_H


#include "DoubleImage.h"
#include "../filter/border/CopyPolicy.h"
#include "../filter/border/MirrorPolicy.h"

class DoubleImageBorderPolicy : public DoubleImage {
private:
    constexpr static MirrorPolicy DEFAULT_POLICY = MirrorPolicy();
    IBorderPolicy &borderPolicy;
public:
    explicit DoubleImageBorderPolicy(const shared_ptr<DoubleImage> &other,
                            IBorderPolicy &borderPolicy = (IBorderPolicy &) DEFAULT_POLICY);

    [[nodiscard]] double getBorderedPixel(int x, int y) const;

};


#endif //ITOI_DOUBLEIMAGEBORDERPOLICY_H
