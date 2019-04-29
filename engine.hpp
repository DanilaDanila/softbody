#pragma once

#include "vec2.hpp"
#include <vector>

#define BODY_STATIC 0
#define BODY_DYNAMIC 1

struct Point
{
    Vec2 position;
    Vec2 last_position;
    Vec2 acceleration;

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

    int type;

    float rigidity;

    Body() {}

    ~Body() {}
};

struct BodyDef
{
private:
    std::vector<Point> points;
    std::vector<Vec2> edges;

    int body_type = BODY_STATIC;

    float rigidity = 1.0;

public:
    Body createBody()
    {
        Body new_body;

        new_body.type = body_type;
        new_body.rigidity = rigidity;
        
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

    void setBodyType(int body_type_)
    {
        body_type = body_type_;
    }

    void setRigidity(float rigidity_)
    {
        rigidity = rigidity_;
    }
};

class Sandbox
{
private:
    std::vector<Body> bodys;

    void updateBodyPoints(Body *b, float dt)
    {
        if(b->type == BODY_STATIC) return;

        for(int i=0; i<b->points_count; i++)
        {
            Point &p = b->points[i];
            Vec2 temp = p.position;
            p.position = p.position + (p.position - p.last_position)*dt + p.acceleration*dt*dt;
            p.last_position = temp;
        }
    }

    void updateBodyEdges(Body *b)
    {
        if(b->type == BODY_STATIC) return;

        for(int i=0; i<b->edges_count; i++)
        {
            Edge &e = b->edges[i];

            Vec2 connection = e.p0->position - e.p1->position;
            float connection_len = connection.len();

            float diff = connection_len - e.length;
            connection = connection.normalize();

            e.p0->position = e.p0->position - connection*diff*0.5f*b->rigidity;
            e.p1->position = e.p1->position + connection*diff*0.5f*b->rigidity;
        }
    }

    void applyAcc(Body *b)
    {
        if(b->type == BODY_STATIC) return;

        for(int i=0; i<b->points_count; i++)
            b->points[i].acceleration = acceleration;
    }

public:
    Vec2 acceleration;

    Sandbox() {}

    Sandbox(Vec2 acceleration_): acceleration(acceleration_) {}

    void addBody(Body b)
    {
        bodys.push_back(b);
    }

    const std::vector<Body> *getBodys()
    {
        return &bodys;
    }

    void update(float _time)
    {
        for(int i=0; i<bodys.size(); i++)
        {
            applyAcc(&bodys[i]);

            updateBodyPoints(&bodys[i], _time);
            updateBodyEdges(&bodys[i]);
        }
    }

    ~Sandbox() {}
};