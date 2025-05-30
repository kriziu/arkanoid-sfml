#include "../../include/Controllers/BallController.hpp"
#include "../../include/Actors/Ball.hpp"
#include "../../include/Actors/Paddle.hpp"
#include "../../include/Scenes/Scene.hpp"
#include "../../include/Utils/Constants.hpp"
#include <cmath>


BallController::BallController() : Controller(), lastPaddlePosition_(0, 0), paddleVelocity_(0, 0) {}

BallController::~BallController() {}

void BallController::Initialize() {
    currentSpeed_ = INITIAL_SPEED;
    if (Ball* ball = GetActor<Ball>()) {
        UpdateAttachedToPaddle();
    }
}

void BallController::Update(float deltaTime) {
    Ball* ball = GetActor<Ball>();
    if (!ball) return;
    
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
    }
}

void BallController::HandleEvent(const sf::Event& event) {
    if (const auto* mouseButtonPressed = event.getIf<sf::Event::MouseButtonPressed>()) {
        if (mouseButtonPressed->button == sf::Mouse::Button::Left) {
            Ball* ball = GetActor<Ball>();
            if (ball && ball->IsAttachedToPaddle()) {
                LaunchBall();
            }
        }
    }
}

void BallController::UpdateAttachedToPaddle() {
    Ball* ball = GetActor<Ball>();
    Paddle* paddle = GetPaddle();
    
    if (!ball || !paddle) return;
    
    sf::Vector2f paddlePos = paddle->GetPosition();
    float ballX = paddlePos.x + paddle->PADDLE_WIDTH / 2;
    float ballY = paddlePos.y - ball->BALL_RADIUS;
    
    ball->SetPosition(ballX, ballY);
    ball->SetVelocity(0, 0);
}

void BallController::UpdateBallPhysics(float deltaTime) {
    Ball* ball = GetActor<Ball>();
    if (!ball) return;
    
    sf::Vector2f position = ball->GetPosition();
    sf::Vector2f velocity = ball->GetVelocity();
    
    position += velocity * deltaTime;
    ball->SetPosition(position.x, position.y);
}

void BallController::HandleWallCollisions() {
    Ball* ball = GetActor<Ball>();
    if (!ball) return;
    
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
    
    if (velocityChanged) {
        ball->SetVelocity(velocity.x, velocity.y);
    }
}

void BallController::HandlePaddleCollision() {
    Ball* ball = GetActor<Ball>();
    Paddle* paddle = GetPaddle();
    
    if (!ball || !paddle) return;
    
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
            
            ball->SetVelocity(velocity.x, velocity.y);
            ball->SetPosition(ballPos.x, paddlePos.y - ball->BALL_RADIUS);
        }
    }
}

void BallController::LaunchBall() {
    Ball* ball = GetActor<Ball>();
    if (!ball) return;
    
    ball->SetAttachedToPaddle(false);
    ball->SetVelocity(0, -currentSpeed_);
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