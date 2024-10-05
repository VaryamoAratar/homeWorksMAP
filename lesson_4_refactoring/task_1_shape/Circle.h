#ifndef CIRCLE_H
#define CIRCLE_H

#include "IShape.h"
#include <stdexcept>
#include "Point.h"

class Circle : public IShape {
public:
    Circle(Point _center, double _radius);

    void shift(double, double, double) override;

    void scaleX(double) override;

    void scaleY(double) override;

    void scaleZ(double) override;

    void scale(double) override;

protected:
    Point center;
    double radius{ 0 };
};

#endif //CIRCLE_H