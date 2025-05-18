#include "../../include/Controllers/PaddleController.hpp"
#include "../../include/Actors/Paddle.hpp"
#include "../../include/Utils/Constants.hpp"

PaddleController::PaddleController(Paddle* paddle) 
    : paddle_(paddle) {}

PaddleController::~PaddleController() {}

void PaddleController::Initialize() {
    if (paddle_) {
        float paddleWidth = paddle_->paddleWidth;
        float paddleHeight = paddle_->paddleHeight;
        float bottomOffset = paddle_->paddleBottomOffset;
        float paddleStartX = Constants::WINDOW_WIDTH / 2 - paddleWidth / 2;
        float paddleStartY = Constants::WINDOW_HEIGHT - paddleHeight - bottomOffset;
        paddle_->SetPosition(paddleStartX, paddleStartY);
    }
}

void PaddleController::Update(float deltaTime) {
}

void PaddleController::HandleEvent(const sf::Event& event) {
    if (const auto* mouseMoved = event.getIf<sf::Event::MouseMoved>()) {
        if (paddle_) {
            sf::Vector2f position = paddle_->GetPosition();
            
            float paddleWidth = paddle_->paddleWidth;
            float newX = mouseMoved->position.x - paddleWidth / 2;

            float maxX = Constants::WINDOW_WIDTH - paddleWidth;
            
            if (newX < 0) {
                newX = 0;
            } else if (newX > maxX) {
                newX = maxX;
            }


            paddle_->SetPosition(newX, position.y);
        }
    }
} 