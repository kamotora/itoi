//
// Created by kamotora on 28.04.2021.
//

#ifndef ITOI_PATCHCREATOR_H
#define ITOI_PATCHCREATOR_H

#include "PatchDescriptor.h"
#include "MatchInfo.h"
#include "DescriptorUtil.h"
#include "../point/Harris.h"

class PatchCreator {
public:
    static shared_ptr<MatchInfo> processWithPatches(const shared_ptr<DoubleImage> &first,
                                                      const shared_ptr<DoubleImage> &second,
                                                      int pointsCount,
                                                      int gridHalfSize,
                                                      int cellHalfSize);

    static vector<shared_ptr<struct AbstractDescriptor>> getDescriptors(const shared_ptr<DoubleImage> &gradient,
                                                                        const vector<Point> &interestingPoints,
                                                                        int gridHalfSize,
                                                                        int cellHalfSize);
};


#endif //ITOI_PATCHCREATOR_H
