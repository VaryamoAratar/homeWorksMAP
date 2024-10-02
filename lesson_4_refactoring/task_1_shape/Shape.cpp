#include <stdexcept>
#include <iostream>
#include <cmath>

struct Point
{
    double x;
    double y;
    double z = 0.0;

    Point(double _x = 0.0, double _y = 0.0) : x(_x), y(_y) {}
};

class IShape //только для фигур в плоскости XY
{
public:
    virtual ~IShape() = default;

    virtual void shift(double, double, double) = 0;
    virtual void scaleX(double factor) = 0;
    virtual void scaleY(double factor) = 0;
    virtual void scaleZ(double factor) = 0;
    virtual void scale(double factor) = 0;
};

class Line : public IShape
{
public:
    Line(Point _first_point, Point _second_point) : first_point(_first_point), second_point(_second_point) {
    
        if (_first_point.z != _second_point.z)
        {
            throw std::invalid_argument("The vertices have different z coordinates");
        }
    }

    void shift(double _x = 0, double _y = 0, double _z = 0) override
    {
        first_point.x += _x;
        first_point.y += _y;
        first_point.z += _z;

        second_point.x += _x;
        second_point.y += _y;
        second_point.z += _z;
    }

    void scaleX(double factor) override
    {
        first_point.x *= factor;
        second_point.x *= factor;
    }

    void scaleY(double factor) override
    {
        first_point.y *= factor;
        second_point.y *= factor;
    }

    void scaleZ(double factor) override
    {
        first_point.z *= factor;
        second_point.z *= factor;
    }

    void scale(double factor) override
    {
        first_point.x *= factor;
        first_point.y *= factor;
        first_point.z *= factor;

        second_point.x *= factor;
        second_point.y *= factor;
        second_point.z *= factor;
    }

protected:
    Point first_point, second_point;
};

class Rectangle : public Line
{
public:
    Rectangle(Point _first_point, Point _second_point, int _height) : Line(_first_point, _second_point) {
        
        if (_height == 0)
        {
            throw std::invalid_argument("The zero height of the rectangle");
        }

        this->third_point = findThirdVertex(_first_point, _second_point, _height);
        this->fourth_point = findThirdVertex(_second_point, _first_point, (_height * -1));
    }

    void shift(double _x = 0, double _y = 0, double _z = 0) override
    {
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

    void scaleX(double factor) override
    {
        first_point.x *= factor;
        second_point.x *= factor;
        third_point.x *= factor;
        fourth_point.x *= factor;

    }

    void scaleY(double factor) override
    {
        first_point.y *= factor;
        second_point.y *= factor;
        third_point.y *= factor;
        fourth_point.y *= factor;

    }

    void scaleZ(double factor) override
    {
        first_point.z *= factor;
        second_point.z *= factor;
        third_point.z *= factor;
        fourth_point.z *= factor;

    }

    void scale(double factor) override
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

    }

protected:
    Point third_point, fourth_point;

    Point findThirdVertex(const Point& A, const  Point& B, const double& legLength) {

        double AB = sqrt(pow(B.x - A.x, 2) + pow(B.y - A.y, 2));

        if (AB == 0) {
            std::cout << "Ошибка: точки A и B совпадают!" << std::endl;
            return { 0, 0 };
        }

        double normX = (B.x - A.x) / AB;
        double normY = (B.y - A.y) / AB;

        double perpX = -normY;
        double perpY = normX;

        Point C1;
        if (legLength > 0) {
            C1.x = A.x + legLength * perpX; // Перпендикулярно вверх
            C1.y = A.y + legLength * perpY; // Перпендикулярно вверх
        }
        else {
            C1.x = A.x - legLength * perpX; // Перпендикулярно вниз
            C1.y = A.y - legLength * perpY; // Перпендикулярно вниз
        }
        return C1;
    }
};

class Parallelepiped : public  Rectangle
{
public:
    Parallelepiped(Point _first_point, Point _second_point, int _width, int _height) : Rectangle(_first_point, _second_point, _width) {

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

    void shift(double _x = 0, double _y = 0, double _z = 0) override
    {
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

    void scaleX(double factor) override
    {
        first_point.x *= factor;
        second_point.x *= factor;
        third_point.x *= factor;
        fourth_point.x *= factor;
        fifth_point.x *= factor;
        sixth_point.x *= factor;
        seventh_point.x *= factor;
        eighth_point.x *= factor;

    }

    void scaleY(double factor) override
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

    void scaleZ(double factor) override
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

    void scale(double factor) override
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

protected:
    Point fifth_point, sixth_point, seventh_point, eighth_point;
};