#pragma once

#include <cmath>

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