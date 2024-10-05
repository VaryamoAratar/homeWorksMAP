#include "Line.h"

Line::Line(Point _first_point, Point _second_point) : first_point(_first_point), second_point(_second_point) {

    if (_first_point.z != _second_point.z)
    {
        throw std::invalid_argument("The vertices have different z coordinates");
    }
}

void Line::shift(double _x = 0, double _y = 0, double _z = 0)
{
    first_point.x += _x;
    first_point.y += _y;
    first_point.z += _z;

    second_point.x += _x;
    second_point.y += _y;
    second_point.z += _z;
}

void Line::scaleX(double factor)
{
    first_point.x *= factor;
    second_point.x *= factor;
}

void Line::scaleY(double factor)
{
    first_point.y *= factor;
    second_point.y *= factor;
}

void Line::scaleZ(double factor)
{
    first_point.z *= factor;
    second_point.z *= factor;
}

void Line::scale(double factor)
{
    first_point.x *= factor;
    first_point.y *= factor;
    first_point.z *= factor;

    second_point.x *= factor;
    second_point.y *= factor;
    second_point.z *= factor;
}