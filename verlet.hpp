#pragma once

#include "vec2.hpp"

namespace verlet
{
    struct Point
    {
        Vec2 position;
        Vec2 old_position;
        Vec2 acceleration;

        Point() {}

        Point(Vec2 pos, Vec2 last, Vec2 acc): position(pos),
                                              old_position(last),
                                              acceleration(acc) {}

        ~Point() {}
    };

    class Physics
    {
    public:
        int points_count;
        Point *points;
        float dt = 0.2;

        void updateVerlet()
        {
            for(int i=0; i<points_count; i++)
            {
                Point &p = points[i];

                Vec2 temp = p.position;
                p.position = p.position + (p.position - p.old_position)*dt + p.acceleration*dt*dt;
                p.old_position = temp;
            }
        }
    };
};