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

    const float PADDLE_WIDTH = 100.0f;
    const float PADDLE_HEIGHT = 20.0f;
    const float PADDLE_BOTTOM_OFFSET = 20.0f;
    
private:
    sf::RectangleShape shape_;
}; 