#pragma once
#include "Controller.hpp"
#include <SFML/Graphics.hpp>

class Ball;
class Paddle;

class BallController : public Controller {
public:
    BallController();
    ~BallController() override;
    
    void Initialize() override;
    void Update(float deltaTime) override;
    void HandleEvent(const sf::Event& event) override;
    
private:
    void UpdateAttachedToPaddle();
    void UpdateBallPhysics(float deltaTime);
    void HandleWallCollisions();
    void HandlePaddleCollision();
    void LaunchBall();
    
    Paddle* GetPaddle();
    sf::Vector2f lastPaddlePosition_;
    sf::Vector2f paddleVelocity_;
    float currentSpeed_;
    
    const float INITIAL_SPEED = 300.0f;
    const float SPEED_INCREASE = 20.0f;
    const float MAX_SPEED = 800.0f;
}; 