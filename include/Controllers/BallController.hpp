#pragma once
#include "Controller.hpp"
#include <SFML/Graphics.hpp>

class Ball;
class Paddle;
class Brick;

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
    void HandleBrickCollisions();
    void LaunchBall();
    void HandleBallLost();
    void RespawnBall();
    void ClampVelocity(sf::Vector2f& velocity);
    
    Brick* FindCollidingBrick();
    void ProcessBrickCollision(Brick* brick);
    void CalculateCollisionResponse(Brick* brick, sf::Vector2f& velocity, sf::Vector2f& newPosition);
    bool IsHorizontalCollision(const sf::FloatRect& brickBounds);
    
    Paddle* GetPaddle();
    sf::Vector2f lastPaddlePosition_;
    sf::Vector2f paddleVelocity_;
    float currentSpeed_;
    
    const float INITIAL_SPEED = 300.0f;
    const float SPEED_INCREASE = 10.0f;
    const float MAX_SPEED = 600.0f;
}; 