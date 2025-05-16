#pragma once
#include "Actor.hpp"

class Paddle : public Actor {
public:
    Paddle();
    ~Paddle() override;
    
    void Initialize() override;
    void Draw(sf::RenderWindow& window) override;
    
private:
    sf::RectangleShape shape_;
}; 