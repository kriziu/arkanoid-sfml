#define _USE_MATH_DEFINES

#include "../../include/Controllers/BallController.hpp"
#include "../../include/Actors/Ball.hpp"
#include "../../include/Actors/Paddle.hpp"
#include "../../include/Actors/Brick.hpp"
#include "../../include/Scenes/Scene.hpp"
#include "../../include/Utils/Constants.hpp"
#include "../../include/Utils/MessageBus.hpp"
#include "../../include/Utils/SoundManager.hpp"
#include <cmath>

BallController::BallController() : Controller(), lastPaddlePosition_(0, 0), paddleVelocity_(0, 0) {}

BallController::~BallController() {}

void BallController::ClampVelocity(sf::Vector2f& velocity) {
    const float maxVelocity = Constants::BALL_MAX_VELOCITY;
    if (velocity.x > maxVelocity) velocity.x = maxVelocity;
    else if (velocity.x < -maxVelocity) velocity.x = -maxVelocity;
    
    if (velocity.y > maxVelocity) velocity.y = maxVelocity;
    else if (velocity.y < -maxVelocity) velocity.y = -maxVelocity;
}

void BallController::Initialize() {
    currentSpeed_ = INITIAL_SPEED;
    if (Ball* ball = GetActor<Ball>()) {
        UpdateAttachedToPaddle();
    }
}

void BallController::Update(float deltaTime) {
    Ball* ball = GetActor<Ball>();
    
    Paddle* paddle = GetPaddle();
    if (paddle) {
        sf::Vector2f currentPaddlePos = paddle->GetPosition();
        paddleVelocity_ = (currentPaddlePos - lastPaddlePosition_) / deltaTime;
        lastPaddlePosition_ = currentPaddlePos;
    }
    
    if (ball->IsAttachedToPaddle()) {
        UpdateAttachedToPaddle();
    } else {
        UpdateBallPhysics(deltaTime);
        HandleWallCollisions();
        HandlePaddleCollision();
        HandleBrickCollisions();
    }
}

void BallController::HandleEvent(const sf::Event& event) {
    if (const auto* mouseButtonPressed = event.getIf<sf::Event::MouseButtonPressed>()) {
        if (mouseButtonPressed->button == sf::Mouse::Button::Left) {
            Ball* ball = GetActor<Ball>();

            if (ball->IsInitialLaunchBlocked()) {
                ball->SetInitialLaunchBlocked(false);
            } else if (ball->IsAttachedToPaddle()) {
                LaunchBall();
            }
        }
    }
}

void BallController::UpdateAttachedToPaddle() {
    Ball* ball = GetActor<Ball>();
    Paddle* paddle = GetPaddle();
    
    sf::Vector2f paddlePos = paddle->GetPosition();
    float ballX = paddlePos.x + paddle->PADDLE_WIDTH / 2;
    float ballY = paddlePos.y - ball->BALL_RADIUS;
    
    ball->SetPosition(ballX, ballY);
    ball->SetVelocity(0, 0);
}

void BallController::UpdateBallPhysics(float deltaTime) {
    Ball* ball = GetActor<Ball>();
    
    sf::Vector2f position = ball->GetPosition();
    sf::Vector2f velocity = ball->GetVelocity();
    
    position += velocity * deltaTime;
    ball->SetPosition(position.x, position.y);
}

void BallController::HandleWallCollisions() {
    Ball* ball = GetActor<Ball>();
    
    sf::Vector2f position = ball->GetPosition();
    sf::Vector2f velocity = ball->GetVelocity();
    bool velocityChanged = false;
    
    if (position.x - ball->BALL_RADIUS <= 0) {
        ball->SetPosition(ball->BALL_RADIUS, position.y);
        velocity.x = std::abs(velocity.x);
        velocityChanged = true;
    }
    else if (position.x + ball->BALL_RADIUS >= Constants::WINDOW_WIDTH) {
        ball->SetPosition(Constants::WINDOW_WIDTH - ball->BALL_RADIUS, position.y);
        velocity.x = -std::abs(velocity.x);
        velocityChanged = true;
    }
    
    if (position.y - ball->BALL_RADIUS <= 0) {
        ball->SetPosition(position.x, ball->BALL_RADIUS);
        velocity.y = std::abs(velocity.y);
        velocityChanged = true;
    }
    
    if (position.y + ball->BALL_RADIUS >= Constants::WINDOW_HEIGHT) {
        HandleBallLost();
        return;
    }
    
    if (velocityChanged) {
        ClampVelocity(velocity);
        ball->SetVelocity(velocity.x, velocity.y);
    }
}


void BallController::HandleBallLost() {
    Ball* ball = GetActor<Ball>();
    
    ball->DecrementLives();
    
    if (ball->GetLives() <= 0) {
        SoundManager::PlaySound("game_over");
        Message gameOverMessage;
        gameOverMessage.type = MessageType::GameOver;
        gameOverMessage.sender = this;
        MessageBus::Publish(gameOverMessage);
    } else {
        SoundManager::PlaySound("life_loss");
        RespawnBall();
    }
}

void BallController::RespawnBall() {
    Ball* ball = GetActor<Ball>();
    
    ball->SetAttachedToPaddle(true);
    ball->SetVelocity(0, 0);
    currentSpeed_ = INITIAL_SPEED;
    UpdateAttachedToPaddle();
}

void BallController::HandlePaddleCollision() {
    Ball* ball = GetActor<Ball>();
    Paddle* paddle = GetPaddle();
    
    sf::FloatRect ballBounds = ball->GetBounds();
    sf::Vector2f paddlePos = paddle->GetPosition();
    sf::FloatRect paddleBounds(paddlePos, sf::Vector2f(paddle->PADDLE_WIDTH, paddle->PADDLE_HEIGHT));
    
    if(ballBounds.findIntersection(paddleBounds)) {
        sf::Vector2f ballPos = ball->GetPosition();
        sf::Vector2f velocity = ball->GetVelocity();
        
        if (velocity.y > 0) {
            currentSpeed_ = std::min(currentSpeed_ + SPEED_INCREASE, MAX_SPEED);
            
            velocity.y = -std::abs(velocity.y);
            
            float paddleCenter = paddlePos.x + paddle->PADDLE_WIDTH / 2;
            float ballRelativeX = ballPos.x - paddleCenter;
            float normalizedX = ballRelativeX / (paddle->PADDLE_WIDTH / 2);
            
            float maxAngle = 60.0f * M_PI / 180.0f;
            float angle = normalizedX * maxAngle;
            
            velocity.x = currentSpeed_ * std::sin(angle);
            velocity.y = -currentSpeed_ * std::cos(angle);
            
            velocity.x += paddleVelocity_.x * 0.3f;
            
            ClampVelocity(velocity);
            ball->SetVelocity(velocity.x, velocity.y);
            ball->SetPosition(ballPos.x, paddlePos.y - ball->BALL_RADIUS);
        }
    }
}

void BallController::LaunchBall() {
    Ball* ball = GetActor<Ball>();
    
    ball->SetAttachedToPaddle(false);
    ball->SetVelocity(0, -currentSpeed_);
    
    Message ballLaunchedMessage;
    ballLaunchedMessage.type = MessageType::BallLaunched;
    ballLaunchedMessage.sender = this;
    MessageBus::Publish(ballLaunchedMessage);
}

void BallController::HandleBrickCollisions() {
    if (!scene_) return;

    Ball* ball = GetActor<Ball>();
    
    Brick* collidingBrick = FindCollidingBrick();
    
    if (collidingBrick) {
        ProcessBrickCollision(collidingBrick);
    }
}

Brick* BallController::FindCollidingBrick() {
    Ball* ball = GetActor<Ball>();
    sf::FloatRect ballBounds = ball->GetBounds();
    auto& actors = scene_->GetActors();
    for (Actor* actor : actors) {
        Brick* brick = dynamic_cast<Brick*>(actor);
        if (!brick || brick->IsDestroyed()) continue;
        
        sf::FloatRect brickBounds = brick->GetBounds();
        if (ballBounds.findIntersection(brickBounds)) {
            return brick;
        }
    }
    return nullptr;
}

void BallController::ProcessBrickCollision(Brick* brick) {
    Ball* ball = GetActor<Ball>();

    if (brick->GetType() != BrickType::Unbreakable) {
        SoundManager::PlaySound("brick_break");
    }

    brick->TakeDamage(1);
    
    sf::Vector2f velocity = ball->GetVelocity();
    sf::Vector2f newPosition;
    
    CalculateCollisionResponse(brick, velocity, newPosition);
    
    ClampVelocity(velocity);
    ball->SetVelocity(velocity.x, velocity.y);
    ball->SetPosition(newPosition.x, newPosition.y);
}

void BallController::CalculateCollisionResponse(Brick* brick, sf::Vector2f& velocity, sf::Vector2f& newPosition) {
    Ball* ball = GetActor<Ball>();
    sf::Vector2f ballPos = ball->GetPosition();
    sf::FloatRect brickBounds = brick->GetBounds();
    
    newPosition = ballPos;
    
    if (IsHorizontalCollision(brickBounds)) {
        velocity.x = -velocity.x;
        
        if (ballPos.x < brickBounds.position.x + brickBounds.size.x / 2) {
            newPosition.x = brickBounds.position.x - ball->BALL_RADIUS;
        } else {
            newPosition.x = brickBounds.position.x + brickBounds.size.x + ball->BALL_RADIUS;
        }
    } else {
        velocity.y = -velocity.y;
        
        if (ballPos.y < brickBounds.position.y + brickBounds.size.y / 2) {
            newPosition.y = brickBounds.position.y - ball->BALL_RADIUS;
        } else {
            newPosition.y = brickBounds.position.y + brickBounds.size.y + ball->BALL_RADIUS;
        }
    }
}

bool BallController::IsHorizontalCollision(const sf::FloatRect& brickBounds) {
    Ball* ball = GetActor<Ball>();
    sf::Vector2f ballPos = ball->GetPosition();
    float ballRadius = ball->BALL_RADIUS;

    sf::Vector2f brickCenter = sf::Vector2f(
        brickBounds.position.x + brickBounds.size.x / 2,
        brickBounds.position.y + brickBounds.size.y / 2
    );
    
    sf::Vector2f collisionVector = ballPos - brickCenter;
    
    float overlapX = (brickBounds.size.x / 2 + ballRadius) - std::abs(collisionVector.x);
    float overlapY = (brickBounds.size.y / 2 + ballRadius) - std::abs(collisionVector.y);
    
    return overlapX < overlapY;
}

Paddle* BallController::GetPaddle() {
    if (!scene_) return nullptr;
    
    auto& actors = scene_->GetActors();
    for (Actor* actor : actors) {
        if (Paddle* paddle = dynamic_cast<Paddle*>(actor)) {
            return paddle;
        }
    }
    return nullptr;
} 