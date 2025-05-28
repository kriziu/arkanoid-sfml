#include "../../include/Controllers/PaddleController.hpp"
#include "../../include/Actors/Paddle.hpp"
#include "../../include/Utils/Constants.hpp"

PaddleController::PaddleController(): Controller() {}

PaddleController::~PaddleController() {}

void PaddleController::Initialize() {
    if (Paddle* paddle = GetActor<Paddle>()) {
        float paddleWidth = paddle->PADDLE_WIDTH;
        float paddleHeight = paddle->PADDLE_HEIGHT;
        float bottomOffset = paddle->PADDLE_BOTTOM_OFFSET;
        float paddleStartX = Constants::WINDOW_WIDTH / 2 - paddleWidth / 2;
        float paddleStartY = Constants::WINDOW_HEIGHT - paddleHeight - bottomOffset;
        paddle->SetPosition(paddleStartX, paddleStartY);
    }
}

void PaddleController::HandleEvent(const sf::Event& event) {
    if (const auto* mouseMoved = event.getIf<sf::Event::MouseMoved>()) {
        if (Paddle* paddle = GetActor<Paddle>()) {
            sf::Vector2f position = paddle->GetPosition();
            
            float paddleWidth = paddle->PADDLE_WIDTH;
            float newX = mouseMoved->position.x - paddleWidth / 2;

            float maxX = Constants::WINDOW_WIDTH - paddleWidth;
            
            if (newX < 0) {
                newX = 0;
            } else if (newX > maxX) {
                newX = maxX;
            }

            paddle->SetPosition(newX, position.y);
        }
    }
}