#include "Circle.h"

Circle::Circle(Point _center, double _radius) : center(_center), radius(_radius) {
        if (_radius == 0) {
            throw std::invalid_argument("The zero radius of the circle");
        }
    }
void Circle::shift(double _x = 0, double _y = 0, double _z = 0) {
    center.x += _x;
    center.y += _y;
    center.z += _z;
}
void Circle::scaleX(double factor) {
    center.x *= factor;
    radius *= factor;
}
void Circle::scaleY(double factor) {
    center.y *= factor;
    radius *= factor;
}
void Circle::scaleZ(double factor) {
    center.z *= factor;
    radius *= factor;
}
void Circle::scale(double factor) {
    center.x *= factor;
    center.y *= factor;
    center.z *= factor;
    radius *= factor;
}
