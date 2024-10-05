#ifndef ISHAPE_H
#define ISHAPE_H


class IShape //только для фигур в плоскости XY
{
public:
    virtual ~IShape() = default;

    virtual void shift(double, double, double) = 0;
    virtual void scaleX(double) = 0;
    virtual void scaleY(double) = 0;
    virtual void scaleZ(double) = 0;
    virtual void scale(double) = 0;
};
#endif //ISHAPE_H