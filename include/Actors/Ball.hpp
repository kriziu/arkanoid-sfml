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
    bool IsInitialLaunchBlocked() const;
    void SetAttachedToPaddle(bool attached);
    void SetInitialLaunchBlocked(bool blocked);
    
    sf::FloatRect GetBounds() const;
    
    int GetLives() const;
    void SetLives(int lives);
    void DecrementLives();
    
    const float BALL_RADIUS = 12.0f;
    
private:
    sf::CircleShape shape_;
    sf::Vector2f velocity_;
    bool attachedToPaddle_;
    bool initialLaunchBlocked_;
    int lives_;
}; 