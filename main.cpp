#include <SFML/Graphics.hpp>
#include <GL/gl.h>
#include <unistd.h>

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

        glBegin(GL_LINES);
        glColor3f(1.0, 1.0, 1.0);
        glVertex2f(0.0, 0.0);
        glVertex2f(0.5, 0.5);
        glEnd();

        window.display();
        usleep(1000);
    }
    return 0;
}