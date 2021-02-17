#ifndef ITOI_POLICIES_H
#define ITOI_POLICIES_H


#include "IBorderPolicy.h"
#include "CopyPolicy.h"
#include "MirrorPolicy.h"
#include "SymmetryPolicy.h"
#include "ZeroPolicy.h"

class Policies {
public:
    inline static CopyPolicy COPY = CopyPolicy();
    inline static ZeroPolicy ZERO = ZeroPolicy();
    inline static SymmetryPolicy SYMMETRY = SymmetryPolicy();
    inline static MirrorPolicy MIRROR = MirrorPolicy();
};


#endif //ITOI_POLICIES_H
