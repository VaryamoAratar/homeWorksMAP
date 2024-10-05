#ifndef CYLINDER_H
#define CYLINDER_H

#include "Circle.h"

class Cylinder : public Circle {
public:
    Cylinder(Point _center, double _radius, int _height) : Circle(_center, _radius), height(_height) {};

    void shift(double, double, double) override;

    void scaleX(double) override;

    void scaleY(double) override;

    void scaleZ(double) override;

    void scale(double) override;

protected:
    int height;
};

#endif //CYLINDER_H