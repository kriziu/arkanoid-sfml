#include "Game.hpp"
#include <ctime>

Game::Game() 
    : window(sf::VideoMode::getDesktopMode(), "Falling Balls")
    , ballSpawnInterval(0.00001f)
{
    window.setFramerateLimit(144);
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
}

void Game::run() {
    sf::Clock clock;
    
    while (window.isOpen()) {
        float deltaTime = clock.restart().asSeconds();
        
        processEvents();
        update(deltaTime);
        render();
    }
}

void Game::processEvents() {
    while (const std::optional event = window.pollEvent()) {
        if (event->is<sf::Event::Closed>()) {
            window.close();
        }
    }
}

void Game::update(float deltaTime) {
    // Spawn new balls
    if (ballSpawnTimer.getElapsedTime().asSeconds() >= ballSpawnInterval) {
        spawnBall();
        ballSpawnTimer.restart();
    }
    
    // Update existing balls
    for (auto it = balls.begin(); it != balls.end();) {
        (*it)->update(deltaTime);
        
        if ((*it)->isOutOfBounds(window)) {
            it = balls.erase(it);
        } else {
            ++it;
        }
    }
}

void Game::render() {
    window.clear(sf::Color(30, 30, 30));
    
    for (const auto& ball : balls) {
        ball->render(window);
    }
    
    window.display();
}

void Game::spawnBall() {
    float x = static_cast<float>(rand() % window.getSize().x);
    balls.push_back(std::make_unique<Ball>(x, 0.0f));
} 