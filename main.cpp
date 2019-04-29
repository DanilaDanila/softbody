#include <SFML/Graphics.hpp>
#include <GL/gl.h>
#include <unistd.h>
#include "engine.hpp"
#include <iostream>

inline void glVertexVec2(Vec2 v)
{
    glVertex2f(v.x, v.y);
}


void drawBody(const Body *b)
{
    glBegin(GL_POINTS);
    for(int i=0; i<b->points_count; i++)
        glVertexVec2(b->points[i].position);
    glEnd();

    glBegin(GL_LINES);
    for(int i=0; i<b->points_count; i++)
    {
        glVertexVec2(b->points[i].position + Vec2(-0.02, 0.0));
        glVertexVec2(b->points[i].position + Vec2(0.0, 0.02));


        glVertexVec2(b->points[i].position + Vec2(0.0, 0.02));
        glVertexVec2(b->points[i].position + Vec2(0.02, 0.0));


        glVertexVec2(b->points[i].position + Vec2(0.02, 0.0));
        glVertexVec2(b->points[i].position + Vec2(0.0, -0.02));


        glVertexVec2(b->points[i].position + Vec2(0.0, -0.02));
        glVertexVec2(b->points[i].position + Vec2(-0.02, 0.0));
    }
    glEnd();

    glBegin(GL_LINES);
    for(int i=0; i<b->points_count-1; i++)
    {
        glVertexVec2(b->points[i].position);
        glVertexVec2(b->points[i+1].position);
    }
    glVertexVec2(b->points[b->points_count-1].position);
    glVertexVec2(b->points[0].position);
    glEnd();
}

int main()
{
    float size = 0.2;
    float shift_x = -0.05, shift_y = 0.2;

    BodyDef bdef;
    bdef.addPoint(Vec2(shift_x, shift_y), Vec2(shift_x - 0.001, shift_y));
    bdef.addPoint(Vec2(shift_x + size, shift_y), Vec2(shift_x + size - 0.001, shift_y));
    bdef.addPoint(Vec2(shift_x + size, shift_y + size), Vec2(shift_x + size - 0.001, shift_y + size));
    bdef.addPoint(Vec2(shift_x, shift_y + size), Vec2(shift_x - 0.001, shift_y + size));

    bdef.addEdge(0, 1);
    bdef.addEdge(1, 2);
    bdef.addEdge(2, 3);
    bdef.addEdge(3, 0);
    bdef.addEdge(0, 2);

    bdef.setBodyType(BODY_DYNAMIC);

    Sandbox world(Vec2(0.0, -1.0));
    world.addBody(bdef.createBody());

    bdef.clear();
    bdef.addPoint(Vec2(-1.0, -1.0));
    bdef.addPoint(Vec2(-1.0, 0.0));
    bdef.addPoint(Vec2(0.0, 0.0));
    bdef.addPoint(Vec2(0.0, -1.0));

    bdef.setBodyType(BODY_STATIC);
    world.addBody(bdef.createBody());

    sf::RenderWindow window(sf::VideoMode(700, 700), "");
    window.setFramerateLimit(60);

    sf::Clock clock_;
    float time_;
    while(window.isOpen())
    {
        sf::Event event;
        while(window.pollEvent(event))
        {
            if(event.type == sf::Event::Closed) window.close();
        }
        time_ = clock_.getElapsedTime().asMilliseconds()/1000.0;
        clock_.restart();

        window.clear();

        glColor3f(1.0, 1.0, 1.0);
        world.update(time_);

        for(int i=0; i<world.getBodys()->size(); i++)
            drawBody(&(world.getBodys()->at(i)));

        window.display();
        usleep(5000);
    }
    return 0;
}