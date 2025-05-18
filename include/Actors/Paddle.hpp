#pragma once
#include "Actor.hpp"

class Paddle : public Actor {
public:
    Paddle();
    ~Paddle() override;
    
    void Initialize() override;
    void Draw(sf::RenderWindow& window) override;
    
    void SetPosition(float x, float y);
    sf::Vector2f GetPosition() const;
    
    const float paddleWidth = 100.0f;
    const float paddleHeight = 20.0f;
    const float paddleBottomOffset = 20.0f;
    
private:
    sf::RectangleShape shape_;
}; 