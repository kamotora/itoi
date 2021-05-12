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
                                                                                        pointsCount(pointsCount) {
    this->gaussKernel = make_shared<pair<DoubleImage, DoubleImage>>(Kernels::GetGaussSeparableXY(gridSize * cellSize / 2));
}

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
//    auto testX = x->getCopyData();
//    auto testy = y->getCopyData();
    auto gradient = DescriptorUtil::getGradient(x, y);
    auto gradientAngle = DescriptorUtil::getGradientAngle(x, y);
    auto points = (new Harris(img))->findPoints(pointsCount);
//    auto testGrad = gradient->getCopyData();
//    auto testGradAngle = gradientAngle->getCopyData();

    return createDescriptors(gradient, gradientAngle, points);
}


vector<shared_ptr<AbstractDescriptor>> SiftCreator::createDescriptors(const shared_ptr<DoubleImage> &gradient,
                                                                      const shared_ptr<DoubleImage> &gradientAngle,
                                                                      const vector<Point> &points) const {
    vector<shared_ptr<AbstractDescriptor>> descriptors;
    auto borderedGradient = make_shared<DoubleImageBorderPolicy>(gradient);
    auto borderedGradientAngle = make_shared<DoubleImageBorderPolicy>(gradientAngle);
    for (const auto &point : points) {
        auto angles = calculateAreaOrientationAngle(borderedGradient, borderedGradientAngle, point);
        for (const auto &angle : angles) {
            auto descriptor = SiftDescriptor(borderedGradient, borderedGradientAngle, Point(point, angle),
                                             gridSize, cellSize, basketSize);
            descriptors.push_back(make_shared<AbstractDescriptor>(descriptor));
        }
    }
    return descriptors;
}

vector<double> SiftCreator::calculateAreaOrientationAngle(const shared_ptr<DoubleImageBorderPolicy> &gradient,
                                                          const shared_ptr<DoubleImageBorderPolicy> &gradientAngle,
                                                          const Point &point) const {
    auto basket = Basket(BASKET_SIZE);
    int border = gridSize * cellSize;
    int halfBorder = border / 2;
    for (int x = -halfBorder; x < border - halfBorder; x++) {
        for (int y = -halfBorder; y < border - halfBorder; y++) {
            int realX = point.getX() + x;
            int realY = point.getY() + y;
            double phi = gradientAngle->getBorderedPixel(realX, realY);
            double gradientValue = gradient->getBorderedPixel(realX, realY);
            double gaussValue = FilterUtil::getSeparableValue(*gaussKernel,halfBorder + x, halfBorder + y);

            basket.add(phi, gradientValue * gaussValue);
        }
    }

    auto peeks = basket.getHighestAngles();
    return peeks;
}



