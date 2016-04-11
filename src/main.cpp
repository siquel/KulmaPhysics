#include <stdio.h>

#include "vec2.h"
#include <SFML/Graphics.hpp>
#include "physics_scene.h"

int main(int argc, char** argv) {
    using namespace kphys;
    
    const float fps = 60.f;
    const float dt = 1.f / fps;
    float accumulator = 0.f;
    PhysicsScene scene(dt, 10);
    scene.run();
/* sf::Clock clock;


    float frameStart = clock.getElapsedTime().asSeconds();

    sf::RenderWindow App(sf::VideoMode(800, 600, 32), "Hello World - SFML");

    while (App.isOpen())
    {
        float currentTime = clock.getElapsedTime().asSeconds();

        accumulator += currentTime - frameStart;
        frameStart = currentTime;

        if (accumulator > 0.2f)
            accumulator = 0.2f;

        while (accumulator > dt) {
            // update physics
            accumulator -= dt;
        }

        sf::Event Event;
        while (App.pollEvent(Event))
        {
            if (Event.type == sf::Event::Closed)
                App.close();
        }

        App.clear(sf::Color(0, 0, 255));

        App.display();
    }*/
       
    return 0;
}