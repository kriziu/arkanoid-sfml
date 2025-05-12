#pragma once

#include <SFML/Graphics.hpp>

class Ball {
private:
    sf::CircleShape shape;
    sf::Vector2f velocity;
    
public:
    Ball(float x, float y);
    void update(float deltaTime);
    void render(sf::RenderWindow& window);
    
    sf::FloatRect getBounds() const;
    bool isOutOfBounds(const sf::RenderWindow& window) const;
}; 