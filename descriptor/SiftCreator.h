#ifndef ITOI_SIFTCREATOR_H
#define ITOI_SIFTCREATOR_H


#include "../core/DoubleImage.h"
#include "MatchInfo.h"
#include "SiftDescriptor.h"
#include "SiftBasket.h"
#include "../point/Harris.h"
#include "DescriptorUtil.h"

class SiftCreator {
private:
    static inline int BASKET_SIZE = 36;
    const shared_ptr<DoubleImage> &firstImage;
    const shared_ptr<DoubleImage> &secondImage;
    int gridSize;
    int cellSize;
    int basketSize;
    int pointsCount;

    vector<shared_ptr<AbstractDescriptor>> createDescriptors(const shared_ptr<DoubleImage> &img);

    vector<shared_ptr<AbstractDescriptor>> createDescriptors(const shared_ptr<DoubleImage> &gradient,
                                                             const shared_ptr<DoubleImage> &gradientAngle,
                                                             const vector<Point> &points);

public:
    [[nodiscard]] const shared_ptr<DoubleImage> &getFirstImage() const;

    [[nodiscard]] const shared_ptr<DoubleImage> &getSecondImage() const;

    SiftCreator(const shared_ptr<DoubleImage> &firstImage,
                const shared_ptr<DoubleImage> &second,
                int gridSize,
                int cellSize,
                int basketSize,
                int pointsCount);

    static shared_ptr<MatchInfo> create(const shared_ptr<DoubleImage> &first,
                                        const shared_ptr<DoubleImage> &second,
                                        int _gridSize, int _cellSize,
                                        int _basketSize, int _pointsCount);

    [[nodiscard]]
    vector<double> getMainAngles(const shared_ptr<DoubleImageBorderPolicy> &gradient,
                                 const shared_ptr<DoubleImageBorderPolicy> &gradientAngle,
                                 const Point &point) const;
};


#endif //ITOI_SIFTCREATOR_H
