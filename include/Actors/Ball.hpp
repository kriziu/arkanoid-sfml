#pragma once
#include "Actor.hpp"

class Ball : public Actor {
public:
    Ball();
    ~Ball() override;

    void Initialize() override;
    void Draw(sf::RenderWindow& window) override;
    
    void SetPosition(float x, float y);
    sf::Vector2f GetPosition() const;
    void SetVelocity(float x, float y);
    sf::Vector2f GetVelocity() const;
    
    bool IsAttachedToPaddle() const;
    void SetAttachedToPaddle(bool attached);
    
    sf::FloatRect GetBounds() const;
    
    const float BALL_RADIUS = 12.0f;
    const float BALL_SPEED = 300.0f;
    
private:
    sf::CircleShape shape_;
    sf::Vector2f velocity_;
    bool attachedToPaddle_;
}; 