#pragma once

struct Point
{
    double x;
    double y;
    double z = 0.0;

    Point(double _x = 0.0, double _y = 0.0) : x(_x), y(_y) {}
};
