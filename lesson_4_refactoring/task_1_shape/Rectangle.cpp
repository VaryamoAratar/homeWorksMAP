#include "Rectangle.h"

Rectangle::Rectangle(Point _first_point, Point _second_point, int _height) : Line(_first_point, _second_point) {

    if (_height == 0)
    {
        throw std::invalid_argument("The zero height of the rectangle");
    }

    this->third_point = findThirdVertex(_first_point, _second_point, _height);
    this->fourth_point = findThirdVertex(_second_point, _first_point, (_height * -1));
}

void Rectangle::shift(double _x = 0, double _y = 0, double _z = 0) {
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

}

void Rectangle::scaleX(double factor) {
    first_point.x *= factor;
    second_point.x *= factor;
    third_point.x *= factor;
    fourth_point.x *= factor;
}

void Rectangle::scaleY(double factor) {
    first_point.y *= factor;
    second_point.y *= factor;
    third_point.y *= factor;
    fourth_point.y *= factor;
}

void Rectangle::scaleZ(double factor) {
    first_point.z *= factor;
    second_point.z *= factor;
    third_point.z *= factor;
    fourth_point.z *= factor;
}

void Rectangle::scale(double factor) {
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
}

Point Rectangle::findThirdVertex(const Point& A, const  Point& B, const double& legLength) {

    double AB = sqrt(pow(B.x - A.x, 2) + pow(B.y - A.y, 2));

    if (AB == 0) {
        std::cout << "ќшибка: точки A и B совпадают!" << std::endl;
        return { 0, 0 };
    }

    double normX = (B.x - A.x) / AB;
    double normY = (B.y - A.y) / AB;

    double perpX = -normY;
    double perpY = normX;

    Point C1;
    if (legLength > 0) {
        C1.x = A.x + legLength * perpX; // ѕерпендикул€рно вверх
        C1.y = A.y + legLength * perpY; // ѕерпендикул€рно вверх
    }
    else {
        C1.x = A.x - legLength * perpX; // ѕерпендикул€рно вниз
        C1.y = A.y - legLength * perpY; // ѕерпендикул€рно вниз
    }
    return C1;
}