#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
#include "Ball.hpp"

class Game {
private:
    sf::RenderWindow window;
    std::vector<std::unique_ptr<Ball>> balls;
    sf::Clock ballSpawnTimer;
    float ballSpawnInterval;
    
public:
    Game();
    void run();

private:
    void processEvents();
    void update(float deltaTime);
    void render();
    void spawnBall();
}; 