#include "Parallelepiped.h"

Parallelepiped::Parallelepiped(Point _first_point, Point _second_point, int _width, int _height) : Rectangle(_first_point, _second_point, _width) {

    if (_height == 0)
    {
        throw std::invalid_argument("The zero height of the parallelepiped");
    }

    fifth_point = fifth_point;
    fifth_point.z += _height;
    sixth_point = second_point;
    sixth_point.z += _height;
    seventh_point = third_point;
    seventh_point.z += _height;
    eighth_point = fourth_point;
    eighth_point.z += _height;
}

void Parallelepiped::shift(double _x = 0, double _y = 0, double _z = 0) {
    first_point.x += _x;
    first_point.y += _y;
    first_point.z += _z;

    second_point.x += _x;
    second_point.y += _y;
    second_point.z += _z;

    third_point.x += _x;
    third_point.y += _y;
    third_point.z += _z;

    fourth_point.x += _x;
    fourth_point.y += _y;
    fourth_point.z += _z;

    fifth_point.x += _x;
    fifth_point.y += _y;
    fifth_point.z += _z;

    sixth_point.x += _x;
    sixth_point.y += _y;
    sixth_point.z += _z;

    seventh_point.x += _x;
    seventh_point.y += _y;
    seventh_point.z += _z;

    eighth_point.x += _x;
    eighth_point.y += _y;
    eighth_point.z += _z;
}

void Parallelepiped::scaleX(double factor) {
    first_point.x *= factor;
    second_point.x *= factor;
    third_point.x *= factor;
    fourth_point.x *= factor;
    fifth_point.x *= factor;
    sixth_point.x *= factor;
    seventh_point.x *= factor;
    eighth_point.x *= factor;
}

void Parallelepiped::scaleY(double factor)
{
    first_point.y *= factor;
    second_point.y *= factor;
    third_point.y *= factor;
    fourth_point.y *= factor;
    fifth_point.y *= factor;
    sixth_point.y *= factor;
    seventh_point.y *= factor;
    eighth_point.y *= factor;
}

void Parallelepiped::scaleZ(double factor)
{
    first_point.z *= factor;
    second_point.z *= factor;
    third_point.z *= factor;
    fourth_point.z *= factor;
    fifth_point.z *= factor;
    sixth_point.z *= factor;
    seventh_point.z *= factor;
    eighth_point.z *= factor;
}

void Parallelepiped::scale(double factor)
{
    first_point.x *= factor;
    first_point.y *= factor;
    first_point.z *= factor;

    second_point.x *= factor;
    second_point.y *= factor;
    second_point.z *= factor;

    third_point.x *= factor;
    third_point.y *= factor;
    third_point.z *= factor;

    fourth_point.x *= factor;
    fourth_point.y *= factor;
    fourth_point.z *= factor;

    fifth_point.x *= factor;
    fifth_point.y *= factor;
    fifth_point.z *= factor;

    sixth_point.x *= factor;
    sixth_point.y *= factor;
    sixth_point.z *= factor;

    seventh_point.x *= factor;
    seventh_point.y *= factor;
    seventh_point.z *= factor;

    eighth_point.x *= factor;
    eighth_point.y *= factor;
    eighth_point.z *= factor;
}

