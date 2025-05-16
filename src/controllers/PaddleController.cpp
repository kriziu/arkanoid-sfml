#include "PaddleController.hpp"
#include "../actors/Paddle.hpp"
#include <SFML/Window/Keyboard.hpp>

namespace arkanoid {

PaddleController::PaddleController()
    : Controller("PaddleController"), m_paddle(nullptr) {
}

void PaddleController::onAttach() {
    m_paddle = dynamic_cast<Paddle*>(getOwnerActor());
    if (!m_paddle) {
        throw std::runtime_error("PaddleController can only be attached to Paddle actors");
    }
}

void PaddleController::update(float dt) {
    if (!m_paddle) {
        return;
    }
    
    // Handle keyboard input for paddle movement
    float movement = 0.f;
    
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        movement -= 1.f;
    }
    
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        movement += 1.f;
    }
    
    // Apply movement
    if (movement != 0.f) {
        sf::Vector2f position = m_paddle->getPosition();
        position.x += movement * m_paddle->getSpeed() * dt;
        
        // Constrain paddle to window bounds (assuming window width of 800)
        const float windowWidth = 800.f;
        const float paddleWidth = m_paddle->getSize().x;
        
        if (position.x < 0.f) {
            position.x = 0.f;
        } else if (position.x + paddleWidth > windowWidth) {
            position.x = windowWidth - paddleWidth;
        }
        
        m_paddle->setPosition(position);
    }
}

} // namespace arkanoid 