#include "Cylinder.h"

Cylinder::Cylinder(Point _center, double _radius, int _height) : Circle(_center, _radius), height(_height) {
    if (_height == 0) {
        throw std::invalid_argument("The zero height of the cylinder");
    }
}
void Cylinder::shift(double _x = 0, double _y = 0, double _z = 0) {
    center.x += _x;
    center.y += _y;
    center.z += _z;
}
void Cylinder::scaleX(double factor) {
    center.x *= factor;
    radius *= factor;
}
void Cylinder::scaleY(double factor) {
    center.y *= factor;
    radius *= factor;
}
void Cylinder::scaleZ(double factor) {
    center.z *= factor;
    height *= factor;
}
void Cylinder::scale(double factor) {
    center.x *= factor;
    center.y *= factor;
    center.z *= factor;
    radius *= factor;
    height *= factor;
}
