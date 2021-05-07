#include "SiftCreator.h"

const shared_ptr<DoubleImage> &SiftCreator::getFirstImage() const {
    return firstImage;
}

const shared_ptr<DoubleImage> &SiftCreator::getSecondImage() const {
    return secondImage;
}

SiftCreator::SiftCreator(const shared_ptr<DoubleImage> &firstImage, const shared_ptr<DoubleImage> &secondImage,
                         int gridSize, int cellSize, int basketSize, int pointsCount) : firstImage(firstImage),
                                                                                        secondImage(secondImage),
                                                                                        gridSize(gridSize),
                                                                                        cellSize(cellSize),
                                                                                        basketSize(basketSize),
                                                                                        pointsCount(pointsCount) {}

shared_ptr<MatchInfo>
SiftCreator::create(const shared_ptr<DoubleImage> &first, const shared_ptr<DoubleImage> &second, int _gridSize,
                    int _cellSize, int _basketSize, int _pointsCount) {
    auto creator = SiftCreator(first, second, _gridSize, _cellSize, _basketSize, _pointsCount);
    auto firstDescriptor = creator.createDescriptors(creator.getFirstImage());

    auto secondDescriptor = creator.createDescriptors(creator.getSecondImage());

    return DescriptorUtil::match(firstDescriptor, secondDescriptor);
}


vector<shared_ptr<AbstractDescriptor>>
SiftCreator::createDescriptors(const shared_ptr<DoubleImage> &img) {
    auto x = FilterUtil::derivX(img);
    auto y = FilterUtil::derivY(img);

    auto gradient = DescriptorUtil::getGradient(x, y);
    auto gradientAngle = DescriptorUtil::getGradientAngle(x, y);

    auto points = (new Harris(img))->findPoints(pointsCount);

    return createDescriptors(gradient, gradientAngle, points);
}


vector<shared_ptr<AbstractDescriptor>> SiftCreator::createDescriptors(const shared_ptr<DoubleImage> &gradient,
                                                                      const shared_ptr<DoubleImage> &gradientAngle,
                                                                      const vector<Point> &points) {
    vector<shared_ptr<AbstractDescriptor>> descriptors;
    descriptors.reserve(points.size());
    auto borderedGradient = make_shared<DoubleImageBorderPolicy>(gradient);
    auto borderedGradientAngle = make_shared<DoubleImageBorderPolicy>(gradientAngle);
    for (const auto &point : points) {
        for (const auto &angle : getMainAngles(borderedGradient, borderedGradientAngle, point)) {
            auto descriptor = SiftDescriptor(borderedGradient, borderedGradientAngle, AnglePoint(point, angle),
                                             gridSize, cellSize, basketSize);
            descriptors.push_back(make_shared<AbstractDescriptor>(descriptor));
        }
    }
    return descriptors;
}

vector<double> SiftCreator::getMainAngles(const shared_ptr<DoubleImageBorderPolicy> &gradient,
                                          const shared_ptr<DoubleImageBorderPolicy> &gradientAngle,
                                          const Point &point) const {
    auto basket = SiftBasket(BASKET_SIZE);
    int border = gridSize * cellSize;
    int halfBorder = border / 2;
    auto gauss = Kernels::GetGaussSeparableXY(halfBorder);

    for (int x = -halfBorder; x < border - halfBorder; x++) {
        for (int y = -halfBorder; y < border - halfBorder; y++) {
            int realX = point.getX() + x;
            int realY = point.getY() + y;
            double phi = gradientAngle->getBorderedPixel(realX, realY);
            double gradientValue = gradient->getBorderedPixel(realX, realY);
            double gaussValue = FilterUtil::getSeparableValue(gauss, halfBorder + x, halfBorder + y);

            basket.add(phi, gradientValue * gaussValue);
        }
    }

    auto peeks = basket.getPeeks();

    return peeks;
}



