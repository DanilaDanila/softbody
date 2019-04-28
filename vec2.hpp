#pragma once

#include <cmath>

struct Vec2;

Vec2 operator/(Vec2 v, float f);

struct Vec2
{
    float x=0;
    float y=0;

    Vec2() {}

    Vec2(float x_, float y_): x(x_), y(y_) {}

    float len()
    {
        return sqrt(x*x + y*y);
    }

    Vec2 normalize()
    {
        return (*this)/this->len();
    }

    ~Vec2() {}
};

Vec2 operator+(Vec2 v0, Vec2 v1)
{
    return Vec2(v0.x + v1.x, v0.y + v1.y); 
}

Vec2 operator-(Vec2 v0, Vec2 v1)
{
    return Vec2(v0.x - v1.x, v0.y - v1.y);
}

Vec2 operator*(Vec2 v, float f)
{
    return Vec2(v.x*f, v.y*f);
}

Vec2 operator*(float f, Vec2 v)
{
    return v*f;
}

Vec2 operator/(Vec2 v, float f)
{
    return Vec2(v.x/f, v.y/f);
}

Vec2 normalToLine(Vec2 point, Vec2 line_begin, Vec2 line_end)
{
    float A = (line_begin.y - line_end.y);
    float B = (line_end.x - line_begin.x);
    float C = (line_begin.x*line_end.y - line_end.x*line_begin.y);

    float x = B*(B*point.x - A*point.y) - A*C;
    float y = A*(-B*point.x + A*point.y) - B*C;
    Vec2 normal_end(x, y);
    normal_end = normal_end/(A*A + B*B);

    return normal_end - point;
}