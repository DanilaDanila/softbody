#include <SFML/Graphics.hpp>
#include <GL/gl.h>
#include <unistd.h>
#include "engine.hpp"

inline void glVertexVec2(Vec2 v)
{
    glVertex2f(v.x, v.y);
}


void drawBody(const Body *b)
{
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
    float shift_x = 0.0, shift_y = 0.0;

    BodyDef bdef;
    bdef.addPoint(Vec2(0.0 + shift_x, 0.0 + shift_y));
    bdef.addPoint(Vec2(size + shift_x, 0.0 + shift_y));
    bdef.addPoint(Vec2(size + shift_x, size + shift_y));
    bdef.addPoint(Vec2(0.0 + shift_x, size + shift_y));

    bdef.addEdge(0, 1);
    bdef.addEdge(1, 2);
    bdef.addEdge(2, 3);
    bdef.addEdge(3, 0);

    bdef.setRigidity(1);

    bdef.setBodyType(BODY_DYNAMIC);

    Sandbox world(Vec2(0.0, -1.0));
    world.addBody(bdef.createBody());

    sf::RenderWindow window(sf::VideoMode(700, 700), "");
    window.setFramerateLimit(60);

    while(window.isOpen())
    {
        sf::Event event;
        while(window.pollEvent(event))
        {
            if(event.type == sf::Event::Closed) window.close();
        }
        window.clear();

        world.update(0.03);

        glColor3f(1.0, 1.0, 1.0);
        for(int i=0; i<world.getBodys()->size(); i++)
            drawBody(&(world.getBodys()->at(i)));

        window.display();
        usleep(1000);
    }
    return 0;
}