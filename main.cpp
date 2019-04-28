#include <SFML/Graphics.hpp>
#include <GL/gl.h>
#include <unistd.h>
#include "vec2.hpp"

inline void glVertexVec2(Vec2 v)
{
    glVertex2f(v.x, v.y);
}

int main()
{
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

        Vec2 center(0.0, 0.0);
        Vec2 line_to(0.4, 0.7);

        glBegin(GL_LINES);
        glColor3f(1.0, 1.0, 1.0);
        glVertexVec2(center);
        glVertexVec2(center+line_to);
        glEnd();

        window.display();
        usleep(1000);
    }
    return 0;
}