#ifndef LINE_H
#define LINE_H

#include "IShape.h"
#include <stdexcept>
#include "Point.h"

class Line : public IShape {
public:
    Line(Point _first_point, Point _second_point);
    
    void shift(double, double, double) override;

    void scaleX(double) override;

    void scaleY(double) override;

    void scaleZ(double) override;

    void scale(double) override;

protected:
    Point first_point, second_point;
};

#endif //LINE_H

