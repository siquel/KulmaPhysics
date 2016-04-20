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
    PhysicsScene scene(dt, 1);

    const uint32_t boxCount = 10;

    std::vector<PolygonShape> boxes;
    boxes.resize(boxCount);
    srand(time(NULL));
    for (uint32_t i = 0; i < boxCount; ++i) {
        boxes[i].setAsBox(32.f, 32.f);
        Body* b = scene.add(&boxes[i], 100.f + 70.f * i, 100.f);
        b->setOrient(radians(0));
        b->m_restitution = 0.5f;
        // mass 1 - 10
        b->m_shape->computeMass(2);
    }
    

    PolygonShape ground;
    ground.setAsBox(1280 / 2, 50);
    Body* groundbody = scene.add(&ground, 1280 / 2, 720 - 50);
    groundbody->setStatic();

    PolygonShape juttu;
    juttu.setAsBox(200, 50);
    Body* juttub = scene.add(&juttu, 300, 400);
    juttub->setOrient(radians(70));
    juttub->m_restitution = 0;
    juttub->setStatic();

    PolygonShape asd;
    asd.setAsBox(100, 20);
    Body* asdb = scene.add(&asd, 600, 300);
    asdb->setOrient(radians(-70));
    asdb->m_restitution = 1.f;
    asdb->m_torque = 5;
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