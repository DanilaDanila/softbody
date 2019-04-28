#pragma once

#include "vec2.hpp"
#include <vector>

struct Point
{
    Vec2 position;
    Vec2 last_position;
    Vec2 acceleration;
    float mass;

    Point() {}

    Point(Vec2 pos, Vec2 last, Vec2 acc): position(pos),
                                             last_position(last),
                                             acceleration(acc) {}

    ~Point() {}
};

struct Edge
{
    Point *p0;
    Point *p1;

    float length;

    Edge() {}

    Edge(Point *p0_, Point *p1_): p0(p0_), p1(p1_)
    {
        Vec2 len = p0->position - p1->position;
        length = len.len();
    }

    Edge(Point *p0_, Point *p1_, float length_): p0(p0_), p1(p1_), length(length_) {}

    ~Edge() {}
};

struct Body
{
    int points_count;
    Point *points;

    int edges_count;
    Edge *edges;

    Body() {}

    ~Body() {}
};

struct BodyDef
{
    std::vector<Point> points;
    std::vector<Vec2> edges;

    Body createBody()
    {
        Body new_body;
        
        new_body.points_count = points.size();
        new_body.points = new Point[new_body.points_count];
        for(int i=0; i<new_body.points_count; i++)
            new_body.points[i] = points[i];

        new_body.edges_count = edges.size();
        new_body.edges = new Edge[new_body.edges_count];
        for(int i=0; i<new_body.edges_count; i++)
            new_body.edges[i] = Edge(&new_body.points[int(edges[i].x)], &new_body.points[int(edges[i].y)]);
    
        return new_body;
    }

    void addPoint(Vec2 v)
    {
        points.push_back(Point(v, v, Vec2()));
    }

    void addEdge(int point_num0, int point_num1)
    {
        edges.push_back(Vec2(point_num0, point_num1));
    }

    void clear()
    {
        points.clear();
        edges.clear();
    }
};