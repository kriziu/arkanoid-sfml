#include "BallController.hpp"
#include "../actors/Ball.hpp"
#include "../actors/Paddle.hpp"
#include "../actors/Brick.hpp"
#include "../core/Scene.hpp"
#include "../core/MessageBus.hpp"

namespace arkanoid {

BallController::BallController()
    : Controller("BallController"), m_ball(nullptr) {
}

void BallController::onAttach() {
    m_ball = dynamic_cast<Ball*>(getOwnerActor());
    if (!m_ball) {
        throw std::runtime_error("BallController can only be attached to Ball actors");
    }
    
    subscribeToMessage(MessageType::CollisionOccurred);
}

void BallController::update(float dt) {
    if (!m_ball) {
        return;
    }
    
    // Update ball position based on velocity
    sf::Vector2f position = m_ball->getPosition();
    sf::Vector2f velocity = m_ball->getVelocity();
    
    position += velocity * dt;
    m_ball->setPosition(position);
    
    checkCollisions();
}

void BallController::handleMessage(const Message& message) {
    // Process messages here if needed
}

void BallController::checkCollisions() {
    checkWallCollisions();
    checkPaddleCollision();
    checkBrickCollisions();
}

void BallController::checkWallCollisions() {
    // This is a simplified collision detection
    // In a real implementation, you would get the window size from the scene
    const float windowWidth = 800.f;  // Example values
    const float windowHeight = 600.f; // Example values
    
    sf::Vector2f position = m_ball->getPosition();
    sf::Vector2f velocity = m_ball->getVelocity();
    float radius = m_ball->getRadius();
    
    // Left and right walls
    if (position.x - radius < 0) {
        position.x = radius;
        velocity.x = -velocity.x;
    } else if (position.x + radius > windowWidth) {
        position.x = windowWidth - radius;
        velocity.x = -velocity.x;
    }
    
    // Top wall
    if (position.y - radius < 0) {
        position.y = radius;
        velocity.y = -velocity.y;
    }
    
    // Bottom wall (ball is lost)
    if (position.y + radius > windowHeight) {
        publish(MessageType::BallLost);
    }
    
    m_ball->setPosition(position);
    m_ball->setVelocity(velocity);
}

void BallController::checkPaddleCollision() {
    Scene* scene = m_ball->getScene();
    if (!scene) {
        return;
    }
    
    std::shared_ptr<Actor> paddleActor = scene->getActor("Paddle");
    if (!paddleActor) {
        return;
    }
    
    Paddle* paddle = dynamic_cast<Paddle*>(paddleActor.get());
    if (!paddle) {
        return;
    }
    
    // Simple bounding box collision for now
    sf::FloatRect ballBounds = m_ball->getBounds();
    sf::FloatRect paddleBounds = paddle->getBounds();
    
    if (ballBounds.findIntersection(paddleBounds)) {
        sf::Vector2f ballPosition = m_ball->getPosition();
        sf::Vector2f paddlePosition = paddle->getPosition();
        sf::Vector2f velocity = m_ball->getVelocity();
        
        // If the ball is moving downward
        if (velocity.y > 0) {
            // Set ball position to top of paddle
            ballPosition.y = paddlePosition.y - m_ball->getRadius() * 2;
            
            // Reflect velocity
            velocity.y = -velocity.y;
            
            // Adjust x velocity based on where the ball hit the paddle
            float hitPosition = (ballPosition.x - paddlePosition.x) / paddle->getSize().x;
            velocity.x = (hitPosition - 0.5f) * 400.f;  // Adjust this multiplier as needed
            
            m_ball->setPosition(ballPosition);
            m_ball->setVelocity(velocity);
            
            publish(MessageType::CollisionOccurred);
        }
    }
}

void BallController::checkBrickCollisions() {
    Scene* scene = m_ball->getScene();
    if (!scene) {
        return;
    }
    
    // This is a simplified approach - in a real game, you would use a more efficient method
    // such as spatial partitioning to find only relevant bricks
    for (const auto& actor : scene->getActors()) {
        if (actor->getName().find("Brick") != std::string::npos) {
            Brick* brick = dynamic_cast<Brick*>(actor.get());
            if (brick && !brick->isDestroyed()) {
                sf::FloatRect ballBounds = m_ball->getBounds();
                sf::FloatRect brickBounds = brick->getBounds();
                
                if (ballBounds.findIntersection(brickBounds)) {
                    sf::Vector2f velocity = m_ball->getVelocity();
                    sf::Vector2f ballCenter = m_ball->getPosition();
                    sf::Vector2f brickCenter = brick->getPosition() + 
                                            sf::Vector2f(brick->getSize().x / 2.f, 
                                                       brick->getSize().y / 2.f);
                    
                    // Calculate collision direction (simplified)
                    float overlapLeft = ballCenter.x + m_ball->getRadius() - brickBounds.left;
                    float overlapRight = brickBounds.left + brickBounds.width - (ballCenter.x - m_ball->getRadius());
                    float overlapTop = ballCenter.y + m_ball->getRadius() - brickBounds.top;
                    float overlapBottom = brickBounds.top + brickBounds.height - (ballCenter.y - m_ball->getRadius());
                    
                    bool fromLeft = overlapLeft < overlapRight;
                    bool fromTop = overlapTop < overlapBottom;
                    
                    float minOverlapX = fromLeft ? overlapLeft : overlapRight;
                    float minOverlapY = fromTop ? overlapTop : overlapBottom;
                    
                    // Determine the collision side
                    if (minOverlapX < minOverlapY) {
                        velocity.x = fromLeft ? -std::abs(velocity.x) : std::abs(velocity.x);
                    } else {
                        velocity.y = fromTop ? -std::abs(velocity.y) : std::abs(velocity.y);
                    }
                    
                    m_ball->setVelocity(velocity);
                    
                    // Damage the brick
                    brick->hit();
                    
                    publish(MessageType::CollisionOccurred);
                    break;  // Only handle one brick collision per frame for simplicity
                }
            }
        }
    }
}

} // namespace arkanoid 