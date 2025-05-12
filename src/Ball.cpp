#include "Ball.hpp"
#include <cstdint>

Ball::Ball(float x, float y) {
    float radius = 10.0f + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / 40.0f));
    shape.setRadius(radius);
    shape.setPosition({x, y});
    shape.setOrigin({radius, radius});
    
    // Random color
    uint8_t r = rand() % 256;
    uint8_t g = rand() % 256;
    uint8_t b = rand() % 256;
    shape.setFillColor(sf::Color(r, g, b));
    
    // Random horizontal velocity, consistent downward velocity
    float vx = -100.0f + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / 200.0f));
    float vy = 100.0f + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / 200.0f));
    velocity = sf::Vector2f(vx, vy);
}

void Ball::update(float deltaTime) {
    shape.move(velocity * deltaTime);
}

void Ball::render(sf::RenderWindow& window) {
    window.draw(shape);
}

sf::FloatRect Ball::getBounds() const {
    return shape.getGlobalBounds();
}

bool Ball::isOutOfBounds(const sf::RenderWindow& window) const {
    sf::FloatRect bounds = getBounds();
    sf::Vector2u windowSize = window.getSize();
    
    return bounds.position.y > windowSize.y || 
           bounds.position.x + bounds.size.x < 0 || 
           bounds.position.x > windowSize.x;
} 