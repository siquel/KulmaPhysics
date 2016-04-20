#include <stdio.h>

#include "vec2.h"
#include <SFML/Graphics.hpp>
#include "physics_scene.h"
#include "polygon.h"

int main(int argc, char** argv) {
    using namespace kphys;
    
    const float fps = 60.f;
    const float dt = 1.f / fps;
    float accumulator = 0.f;
    PhysicsScene scene(dt, 5);

    const uint32_t boxCount = 10;

    std::vector<PolygonShape> boxes;
    boxes.resize(boxCount);

    for (uint32_t i = 0; i < boxCount; ++i) {
        boxes[i].setAsBox(32.f, 32.f);
        Body* b = scene.add(&boxes[i], 100.f + 70.f * i, 100.f + 50.f * i);
        b->setOrient(radians(45));
    }
    

    PolygonShape ground;
    ground.setAsBox(1280 / 2, 50);
    Body* groundbody = scene.add(&ground, 1280 / 2, 720 - 50);
    groundbody->setStatic();

    sf::Event e;

    sf::Clock clock;
    float frameStart = clock.getElapsedTime().asSeconds();

    while (scene.m_window.isOpen()) {
        while (scene.m_window.pollEvent(e)) {
            if (e.type == sf::Event::Closed)
                scene.m_window.close();
        }

        float currentTime = clock.getElapsedTime().asSeconds();
        accumulator += currentTime - frameStart;
        frameStart = currentTime;

        if (accumulator > 0.2f)
            accumulator = 0.2f;

        while (accumulator > dt) {
            scene.step();
            accumulator -= dt;
        }

        scene.render();
    }

    return 0;
}