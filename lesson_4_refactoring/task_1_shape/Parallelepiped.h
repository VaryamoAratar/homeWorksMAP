#ifndef PARALLELEPIPED_H
#define PARALLELEPIPED_H

#include "Rectangle.h"

class Parallelepiped : public Rectangle {
public:
    Parallelepiped(Point _first_point, Point _second_point, int _width, int _height) : Rectangle(_first_point, _second_point, _width) {};

    void shift(double, double, double) override;

    void scaleX(double) override;

    void scaleY(double) override;

    void scaleZ(double) override;

    void scale(double) override;

protected:
    Point fifth_point, sixth_point, seventh_point, eighth_point;
};

#endif //PARALLELEPIPED_H

