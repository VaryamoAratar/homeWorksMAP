#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "Line.h"
#include <iostream>

class Rectangle : public Line {
public:
    Rectangle(Point _first_point, Point _second_point, int _height) : Line(_first_point, _second_point) {};

    void shift(double, double, double) override;

    void scaleX(double) override;

    void scaleY(double) override;

    void scaleZ(double) override;

    void scale(double) override;

protected:
    Point third_point, fourth_point;
    Point findThirdVertex(const Point&, const  Point&, const double&);
};

#endif //RECTANGLE_H