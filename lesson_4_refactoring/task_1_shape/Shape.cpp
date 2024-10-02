struct Point
{
    int x;
    int y;
    int z;

    Point(int _x = 0, int _y = 0, int _z = 0) : x(_x), y(_y), z(_z) {}
};

class Shape
{
public:
    virtual ~Shape() = default;

    virtual void shift(double _x = 0, double _y = 0, double _z = 0) = 0;
    virtual void scaleX(double factor) = 0;
    virtual void scaleY(double factor) = 0;
    virtual void scaleZ(double factor) = 0;
    virtual void scale(double factor) = 0;
};

class Line : public Shape
{
public:
    Line(Point _first_point, Point _second_point) : first_point(_first_point), second_point(_second_point) {}

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

private:
    Point first_point, second_point;
};


int main()
{
    Point line_first_point {1, 2, 3};
    Point line_second_point {4, 5, 6};

    Line lines(line_first_point, line_second_point);

    return 0;
}
