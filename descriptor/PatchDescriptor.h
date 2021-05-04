//
// Created by kamotora on 28.04.2021.
//

#ifndef ITOI_PATCHDESCRIPTOR_H
#define ITOI_PATCHDESCRIPTOR_H


#include "AbstractDescriptor.h"
#include "../core/DoubleImage.h"
#include "../core/DoubleImageBorderPolicy.h"

class PatchDescriptor : public AbstractDescriptor {
public:
    PatchDescriptor(const shared_ptr<DoubleImage>& gradient, Point point, int gridHalfSize, int cellHalfSize);
};


#endif //ITOI_PATCHDESCRIPTOR_H
