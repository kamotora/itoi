#ifndef ITOI_HISTOGRAMCREATOR_H
#define ITOI_HISTOGRAMCREATOR_H


#include "../core/DoubleImage.h"
#include "MatchInfo.h"
#include "HistogramDescriptor.h"

class HistogramCreator {
private:
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

public:
    HistogramCreator(const shared_ptr<DoubleImage> &firstImage,
                     const shared_ptr<DoubleImage> &second,
                     int gridSize,
                     int cellSize,
                     int basketSize,
                     int pointsCount);

    static shared_ptr<MatchInfo> create(const shared_ptr<DoubleImage> &first,
                                        const shared_ptr<DoubleImage> &second,
                                        int _gridSize, int _cellSize,
                                        int _basketSize, int _pointsCount);
};


#endif //ITOI_HISTOGRAMCREATOR_H
